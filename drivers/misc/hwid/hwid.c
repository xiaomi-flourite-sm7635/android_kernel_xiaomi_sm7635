// SPDX-License-Identifier: GPL-2.0
/*
 * Xiaomi hardware identification compatibility driver.
 *
 * The Xiaomi flourite kernel drop references this directory but omits it.
 * This implementation keeps the public ABI used by the in-tree drivers and
 * by the stock flourite module.  Values are supplied by the boot loader as
 * module parameters.
 */

#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/sysfs.h>

#include "hwid.h"

#define HW_MAJOR_VERSION_SHIFT		16
#define HW_MINOR_VERSION_SHIFT		0
#define HW_COUNTRY_VERSION_SHIFT	20
#define HW_BUILD_VERSION_SHIFT		16
#define HW_MAJOR_VERSION_MASK		0xffff0000
#define HW_MINOR_VERSION_MASK		0x0000ffff
#define HW_COUNTRY_VERSION_MASK		0xfff00000
#define HW_BUILD_VERSION_MASK		0x000f0000

static u32 hwid_value;
module_param(hwid_value, uint, 0444);
MODULE_PARM_DESC(hwid_value, "Xiaomi packed hardware revision");

static u32 project;
module_param(project, uint, 0444);
MODULE_PARM_DESC(project, "Xiaomi project identifier");

static u32 build_adc;
module_param(build_adc, uint, 0444);
MODULE_PARM_DESC(build_adc, "Build resistor ADC value");

static u32 project_adc;
module_param(project_adc, uint, 0444);
MODULE_PARM_DESC(project_adc, "Project resistor ADC value");

static char flourite_product_name[] = "flourite";
static struct kobject *hwid_kobj;

char *product_name_get(void)
{
	return flourite_product_name;
}
EXPORT_SYMBOL(product_name_get);

u32 get_hw_project_adc(void)
{
	return project_adc;
}
EXPORT_SYMBOL(get_hw_project_adc);

u32 get_hw_build_adc(void)
{
	return build_adc;
}
EXPORT_SYMBOL(get_hw_build_adc);

u32 get_hw_version_platform(void)
{
	return project;
}
EXPORT_SYMBOL(get_hw_version_platform);

u32 get_hw_id_value(void)
{
	return hwid_value;
}
EXPORT_SYMBOL(get_hw_id_value);

u32 get_hw_country_version(void)
{
	return (hwid_value & HW_COUNTRY_VERSION_MASK) >>
		HW_COUNTRY_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_country_version);

u32 get_hw_version_major(void)
{
	return (hwid_value & HW_MAJOR_VERSION_MASK) >> HW_MAJOR_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_major);

u32 get_hw_version_minor(void)
{
	return (hwid_value & HW_MINOR_VERSION_MASK) >> HW_MINOR_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_minor);

u32 get_hw_version_build(void)
{
	return (hwid_value & HW_BUILD_VERSION_MASK) >> HW_BUILD_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_build);

static ssize_t hwid_project_show(struct kobject *kobj,
				 struct kobj_attribute *attr, char *buf)
{
	return sysfs_emit(buf, "%u\n", project);
}

static ssize_t hwid_value_show(struct kobject *kobj,
			       struct kobj_attribute *attr, char *buf)
{
	return sysfs_emit(buf, "0x%x\n", hwid_value);
}

static ssize_t hwid_project_adc_show(struct kobject *kobj,
				     struct kobj_attribute *attr, char *buf)
{
	return sysfs_emit(buf, "%u\n", project_adc);
}

static ssize_t hwid_build_adc_show(struct kobject *kobj,
				   struct kobj_attribute *attr, char *buf)
{
	return sysfs_emit(buf, "%u\n", build_adc);
}

static struct kobj_attribute hwid_project_attr = __ATTR_RO(hwid_project);
static struct kobj_attribute hwid_value_attr = __ATTR_RO(hwid_value);
static struct kobj_attribute hwid_project_adc_attr = __ATTR_RO(hwid_project_adc);
static struct kobj_attribute hwid_build_adc_attr = __ATTR_RO(hwid_build_adc);

static struct attribute *hwid_attrs[] = {
	&hwid_project_attr.attr,
	&hwid_value_attr.attr,
	&hwid_project_adc_attr.attr,
	&hwid_build_adc_attr.attr,
	NULL,
};

static const struct attribute_group hwid_attr_group = {
	.attrs = hwid_attrs,
};

static int __init hwid_init(void)
{
	int ret;

	hwid_kobj = kobject_create_and_add("hwid", NULL);
	if (!hwid_kobj)
		return -ENOMEM;

	ret = sysfs_create_group(hwid_kobj, &hwid_attr_group);
	if (ret) {
		kobject_put(hwid_kobj);
		hwid_kobj = NULL;
	}

	return ret;
}

static void __exit hwid_exit(void)
{
	if (!hwid_kobj)
		return;

	sysfs_remove_group(hwid_kobj, &hwid_attr_group);
	kobject_put(hwid_kobj);
}

module_init(hwid_init);
module_exit(hwid_exit);

MODULE_AUTHOR("Xiaomi and flourite contributors");
MODULE_DESCRIPTION("Xiaomi flourite hardware identification compatibility");
MODULE_LICENSE("GPL v2");

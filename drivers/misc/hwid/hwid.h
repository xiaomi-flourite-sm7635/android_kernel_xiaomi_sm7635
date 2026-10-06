/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 Xiaomi, Inc.
 * Copyright (C) 2022 The LineageOS Project
 * Copyright (C) 2026 flourite contributors
 */

#ifndef __XIAOMI_HWID_H__
#define __XIAOMI_HWID_H__

#include <linux/types.h>

/* Xiaomi project IDs used by the shared Qualcomm drivers. */
#define HARDWARE_PROJECT_UNKNOWN	0
#define HARDWARE_PROJECT_N3	2
#define HARDWARE_PROJECT_N11U	3
#define HARDWARE_PROJECT_N18	7
#define HARDWARE_PROJECT_O81	10
#define HARDWARE_PROJECT_O82	11
#define HARDWARE_PROJECT_P16U	14

enum xiaomi_country_type {
	COUNTRY_CN = 0x00,
	COUNTRY_GLOBAL = 0x01,
	COUNTRY_INDIA = 0x02,
	COUNTRY_JAPAN = 0x03,
	COUNTRY_INVALID = 0x04,
};

/* Keep the vendor spelling used by Xiaomi's out-of-tree drivers. */
typedef enum {
	CountryCN = COUNTRY_CN,
	CountryGlobal = COUNTRY_GLOBAL,
	CountryIndia = COUNTRY_INDIA,
	CountryJapan = COUNTRY_JAPAN,
	INVALID = COUNTRY_INVALID,
	CountryIDMax = 0x7fffffff,
} CountryType;

char *product_name_get(void);
u32 get_hw_project_adc(void);
u32 get_hw_build_adc(void);
u32 get_hw_version_platform(void);
u32 get_hw_id_value(void);
u32 get_hw_country_version(void);
u32 get_hw_version_major(void);
u32 get_hw_version_minor(void);
u32 get_hw_version_build(void);

#endif /* __XIAOMI_HWID_H__ */

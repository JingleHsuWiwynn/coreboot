/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 - 2017 Intel Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <console/console.h>
#include <fsp/api.h>
#include <soc/ramstage.h>
#include <pc80/mc146818rtc.h>
#include <cf9_reset.h>
#include <smbios.h>
#include <drivers/vpd/vpd.h>
#include <console/console.h>
#include <drivers/ipmi/ipmi_ops.h>
#include <string.h>
#include "emmc.h"
#include "ipmi.h"
/* VPD variable for enabling/disabling FRB2 timer. */
#define FRB2_TIMER "FRB2_TIMER"
/* VPD variable for setting FRB2 timer countdown value. */
#define FRB2_COUNTDOWN "FRB2_COUNTDOWN"
#define VPD_LEN 10
/* Default countdown is 15 minutes. */
#define DEFAULT_COUNTDOWN 9000

static int get_emmc_dll_info(uint16_t signature, size_t num_of_entry,
			     BL_EMMC_INFORMATION **config)
{
	uint8_t entry;

	if ((signature == 0) || (num_of_entry == 0) || (*config == NULL))
		return 1;

	for (entry = 0; entry < num_of_entry; entry++) {
		if ((*config)[entry].Signature == signature) {
			*config = &(*config)[entry];
			return 0;
		}
	}

	return 1;
}

void mainboard_silicon_init_params(FSPS_UPD *params)
{
	size_t num;
	uint16_t emmc_dll_sign;
	BL_EMMC_INFORMATION *emmc_config;

	/* Configure eMMC DLL PCD */
	emmc_dll_sign = DEFAULT_EMMC_DLL_SIGN;
	num = ARRAY_SIZE(tiogapass_emmc_config);
	emmc_config = tiogapass_emmc_config;

	if (get_emmc_dll_info(emmc_dll_sign, num, &emmc_config))
		die("eMMC DLL Configuration is invalid, please correct it!");

	params->FspsConfig.PcdEMMCDLLConfigPtr =
		(uint32_t)&emmc_config->eMMCDLLConfig;
}

static void init_frb2_wdt(void)
{

	char val[VPD_LEN];
	/* Enable FRB2 timer by default. */
	u8 enable = 1;
	uint16_t countdown;

	if (vpd_get_bool(FRB2_TIMER, VPD_RW, &enable)) {
		if (!enable) {
			printk(BIOS_DEBUG, "Disable FRB2 timer\n");
			ipmi_stop_bmc_wdt(BMC_KCS_BASE);
		}
	}
	if (enable) {
		if (vpd_gets(FRB2_COUNTDOWN, val, VPD_LEN, VPD_RW)) {
			countdown = (uint16_t)atol(val);
			printk(BIOS_DEBUG, "FRB2 timer countdown set to: %d\n",
				countdown);
		} else {
			printk(BIOS_DEBUG, "FRB2 timer use default value: %d\n",
				DEFAULT_COUNTDOWN);
			countdown = DEFAULT_COUNTDOWN;
		}
		ipmi_init_and_start_bmc_wdt(BMC_KCS_BASE, countdown,
			TIMEOUT_HARD_RESET);
	}
}

static void mainboard_enable(struct device *dev)
{
	ipmi_oem_rsp_t rsp;

	init_frb2_wdt();
	if (is_ipmi_clear_cmos_set(&rsp)) {
		cmos_init(1);
		clear_ipmi_flags(&rsp);
		system_reset();
	}

}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};

/* Override SMBIOS uuid from the value from BMC. */
void smbios_system_set_uuid(u8 *uuid)
{
	ipmi_get_system_guid(BMC_KCS_BASE, uuid);
}

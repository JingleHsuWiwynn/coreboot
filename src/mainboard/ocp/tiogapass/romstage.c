/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017 Intel Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "tiogapass_boardid.h"
#include <console/console.h>
#include <fsp/api.h>
#include <fsp/soc_binding.h>
#include <FspmUpd.h>
#define PCH_SERVER_BIOS_FLAG 1
#include <soc/skxsp_gpio_lib.h>
#include <soc/skxsp_gpio_pins.h>
#include "skxsp_tp_gpio.h"
#include "skxsp_tp_iio.h"


void mainboard_config_gpios(FSPM_UPD *mupd);
void mainboard_config_iio(FSPM_UPD *mupd);
void mainboard_memory_init_params(FSPM_UPD *mupd);

/*
* Configure GPIO depend on platform
*/
void mainboard_config_gpios(FSPM_UPD *mupd)
{
	mupd->FspmConfig.GpioConfig.GpioTable = (UPD_GPIO_INIT_CONFIG *) tp_gpio_table;
	mupd->FspmConfig.GpioConfig.NumberOfEntries = sizeof(tp_gpio_table)/sizeof(UPD_GPIO_INIT_CONFIG);
}

void mainboard_config_iio(FSPM_UPD *mupd)
{
	mupd->FspmConfig.IioBifurcationConfig.IIoBifurcationTable = (UPD_IIO_BIFURCATION_DATA_ENTRY *) tp_iio_bifur_table;
	mupd->FspmConfig.IioBifurcationConfig.NumberOfEntries = sizeof(tp_iio_bifur_table)/sizeof(UPD_IIO_BIFURCATION_DATA_ENTRY);

	mupd->FspmConfig.IioSlotConfig.IIoSlotConfigTable = (UPD_IIO_SLOT_CONFIG_DATA_ENTRY *) tp_iio_slot_table;
	mupd->FspmConfig.IioSlotConfig.NumberOfEntries = sizeof(tp_iio_slot_table)/sizeof(UPD_IIO_SLOT_CONFIG_DATA_ENTRY);
}

void mainboard_memory_init_params(FSPM_UPD *mupd)
{
	post_code(0xd1);
	mainboard_config_gpios(mupd);
	mainboard_config_iio(mupd);
	post_code(0xd2);
}

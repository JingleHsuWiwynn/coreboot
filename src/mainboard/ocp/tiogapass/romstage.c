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
#include <string.h>

void mainboard_config_gpios(void);
void mainboard_memory_init_params(FSPM_UPD *mupd);

/*
* Configure GPIO depend on platform
*/
void mainboard_config_gpios(void)
{
}

void mainboard_memory_init_params(FSPM_UPD *mupd)
{
}

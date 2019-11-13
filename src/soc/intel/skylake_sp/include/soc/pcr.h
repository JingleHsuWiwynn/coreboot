/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 - 2017 Intel Corporation.
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

#ifndef _SKYLAKESP_PCR_H_
#define _SKYLAKESP_PCR_H_

/* PCR BASE */
#include <soc/iomap.h>

/* PCR address */
#define PCH_PCR_ADDRESS(Pid, Offset) \
	(P2SB_BAR | ((uint8_t)(Pid) << 16) | (uint16_t)(Offset))

#endif /* _SKYLAKESP_PCR_H_ */

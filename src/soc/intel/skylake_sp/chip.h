/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 - 2017 Intel Corporation.
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

#ifndef SOC_INTEL_SKYLAKE_SP_CHIP_H
#define SOC_INTEL_SKYLAKE_SP_CHIP_H

#include <stdint.h>
#include <commonlib/helpers.h>
#include <intelblocks/cfg.h>
#include <intelblocks/gspi.h>
#include <soc/gpe.h>
#include <soc/gpio.h>
#include <soc/pm.h>
#include <soc/irq.h>
#include <soc/pci_devs.h>
#include <soc/pmc.h>

struct soc_intel_skylake_sp_config {
	/* Common struct containing soc config data required by common code */
  struct soc_intel_common_config common_soc_config;

	/**
	 * Interrupt Routing configuration
	 * If bit7 is 1, the interrupt is disabled.
	 */
	uint8_t pirqa_routing;
	uint8_t pirqb_routing;
	uint8_t pirqc_routing;
	uint8_t pirqd_routing;
	uint8_t pirqe_routing;
	uint8_t pirqf_routing;
	uint8_t pirqg_routing;
	uint8_t pirqh_routing;

	/**
	 * Device Interrupt Routing configuration
	 * Interrupt Pin x Route.
	 * 0h = PIRQA#
	 * 1h = PIRQB#
	 * 2h = PIRQC#
	 * 3h = PIRQD#
	 * 4h = PIRQE#
	 * 5h = PIRQF#
	 * 6h = PIRQG#
	 * 7h = PIRQH#
	 */
	uint16_t ir00_routing;
	uint16_t ir01_routing;
	uint16_t ir02_routing;
	uint16_t ir03_routing;
	uint16_t ir04_routing;

	/**
	* Device Interrupt Polarity Control
	* ipc0 - IRQ-00-31 - 1: Active low to IOAPIC, 0: Active high to IOAPIC
	* ipc1 - IRQ-32-63 - 1: Active low to IOAPIC, 0: Active high to IOAPIC
	* ipc2 - IRQ-64-95 - 1: Active low to IOAPIC, 0: Active high to IOAPIC
	* ipc3 - IRQ-96-119 - 1: Active low to IOAPIC, 0: Active high to IOAPIC
	*/
	uint32_t ipc0;
	uint32_t ipc1;
	uint32_t ipc2;
	uint32_t ipc3;
};

extern struct chip_operations soc_intel_skylake_sp_ops;

typedef struct soc_intel_skylake_sp_config config_t;

#endif /* SOC_INTEL_FSP_SKYLAKE_SP_CHIP_H */

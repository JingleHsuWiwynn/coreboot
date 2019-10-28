/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 - 2017 Intel Corp.
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

#include <arch/ebda.h>
#include <arch/io.h>
#include <cbmem.h>
#include <assert.h>
#include <cpu/x86/smm.h>
#include <device/device.h>
#include <device/pci_def.h>
#include <device/pci_ops.h>
#include <soc/pci_devs.h>
#include <soc/memmap.h>
#include <soc/systemagent.h>
#include <soc/smm.h>
#include <soc/skxsp_util.h>
#include <lib.h>
#include <intelblocks/ebda.h>
#include <intelblocks/systemagent.h>

/* Returns base of requested region encoded in the system agent. */
static inline uintptr_t system_agent_region_base(size_t reg)
{
#if defined(__SIMPLE_DEVICE__)
	pci_devfn_t dev = SA_DEV_ROOT;
#else
	struct device *dev = SA_DEV_ROOT;
#endif
	/* All regions concerned for have 1 MiB alignment. */
	return ALIGN_DOWN(pci_read_config32(dev, reg), 1 * MiB);
}

/* Returns min power of 2 >= size */
static inline u32 power_of_2(u32 size)
{
	return size ? 1 << (1 + log2(size - 1)) : 0;
}

u32 top_of_32bit_ram(void)
{
	u32 bus0 = 0, bus1 = 0;
	get_cpubusnos(&bus0, &bus1, NULL, NULL);

	uintptr_t mmcfg = get_cha_mmcfg_base(bus1);
	uintptr_t tolm = get_tolm(bus0);
	printk(BIOS_DEBUG, "bus0: 0x%x, bus1: 0x%x, mmcfg: 0x%lx, tolm: 0x%lx\n", bus0, bus1, mmcfg, tolm);
	u32 base = 0, limit = 0;
	get_tseg_base_lim(bus0, &base, &limit);
	printk(BIOS_DEBUG, "tseg base: 0x%x, limit: 0x%x\n", base, limit);

	/* We will use TSEG base as the top of DRAM */
	return base;
}

/*
 *     +-------------------------+  TOLM
 *     | System Management Mode  |
 *     |      code and data      |
 *     |         (TSEG)          |
 *     +-------------------------+  SMM base (aligned)
 *     |                         |
 *     | Chipset Reserved Memory |
 *     |                         |
 *     +-------------------------+  top_of_ram (aligned)
 *     |                         |
 *     |       CBMEM Root        |
 *     |                         |
 *     +-------------------------+
 *     |                         |
 *     |   FSP Reserved Memory   |
 *     |                         |
 *     +-------------------------+
 *     |                         |
 *     |  Various CBMEM Entries  |
 *     |                         |
 *     +-------------------------+  top_of_stack (8 byte aligned)
 *     |                         |
 *     |   stack (CBMEM Entry)   |
 *     |                         |
 *     +-------------------------+
 */

void *cbmem_top(void)
{
  outb(0xa, 0x70);
  printk(BIOS_DEBUG, "^^^ %s:%s CMOS read: 0x%x\n", __FILE__, __func__, inb(0x71));

	u32 addr = top_of_32bit_ram();
	printk(BIOS_DEBUG, "cbmem_top addr: 0x%x\n", addr);
	return (void *) addr;
}

size_t soc_reserved_mmio_size(void)
{
  struct ebda_config cfg;
  retrieve_ebda_object(&cfg);
  return cfg.reserved_mem_size;
}

void fill_soc_memmap_ebda(struct ebda_config *cfg)
{
  cfg->tolum_base = top_of_32bit_ram();
  cfg->reserved_mem_size = 0;
}

void cbmem_top_init(void)
{
	printk(BIOS_DEBUG, "^^^ cbmem_top_init calling fill_ebda_area\n");
  fill_ebda_area();
}

static inline uintptr_t smm_region_start(void)
{
	return system_agent_region_base(SKXSP_VTD_TSEG_BASE_CSR);
}

static inline size_t smm_region_size(void)
{
	return system_agent_region_base(SKXSP_VTD_TOLM_CSR) - smm_region_start();
}

void smm_region(uintptr_t *start, size_t *size)
{
	*start = smm_region_start();
	*size = smm_region_size();
}

int smm_subregion(int sub, uintptr_t *start, size_t *size)
{
	uintptr_t sub_base;
	size_t sub_size;
	const size_t cache_size = CONFIG_SMM_RESERVED_SIZE;

	sub_base = smm_region_start();
	sub_size = smm_region_size();
	printk(BIOS_DEBUG, "sub_base: 0x%lx, sub_size: 0x%lx, CONFIG_SMM_RESERVED_SIZE: 0x%x\n",
			   sub_base, sub_size, CONFIG_SMM_RESERVED_SIZE);

	assert(sub_size > CONFIG_SMM_RESERVED_SIZE);

	switch (sub) {
	case SMM_SUBREGION_HANDLER:
		/* Handler starts at the base of TSEG. */
		sub_size -= cache_size;
		break;
	case SMM_SUBREGION_CACHE:
		/* External cache is in the middle of TSEG. */
		sub_base += sub_size - cache_size;
		sub_size = cache_size;
		break;
	default:
		return -1;
	}

	*start = sub_base;
	*size = sub_size;

	return 0;
}

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

#include <arch/io.h>
#include <cbmem.h>
#include <assert.h>
#include <device/device.h>
#include <device/pci_def.h>
#include <device/pci_ops.h>
#include <soc/pci_devs.h>
#include <soc/systemagent.h>
#include <soc/smm.h>
#include <lib.h>

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

static inline u32 get_data(int bus, int d, int func, int offset)
{
#if 0
  outl(0x80000000 | bus << 16 | d << 11 | func << 8 | (offset & 0xfc), 0xCF8);
  return inl(0xCFC);
#endif
	uintptr_t loc = DEFAULT_PCIEXBAR + (bus*32*8*0x1000) + (d*8*0x1000) + (func * 0x1000);
	printk(BIOS_DEBUG, "map for [bus: %d, device: %d, func: %d] => loc: %p\n", bus, d, func, (void *)loc);
	u32 val = *((u32 *)(loc + offset));
	printk(BIOS_DEBUG, "\tvalue for offset 0x%x is 0x%x\n", offset, val);
	return pci_mmio_read_config32(PCI_DEV(bus, d, func), offset);
}

#if 0
u32 top_of_32bit_ram(void)
{
	u32 iqat_region_size = 0;
	u32 tseg_region_size = system_agent_region_base(TOLUD) -
			       system_agent_region_base(TSEGMB);

/*
 * Add IQAT region size if enabled.
 */
#if IS_ENABLED(CONFIG_IQAT_ENABLE)
	iqat_region_size = CONFIG_IQAT_MEMORY_REGION_SIZE;
#endif

	/*
	 * Get Socket 0 CPUBUSNO(0), CPUBUSNO(1) PCI bus numbers UBOX (B0:D8:F2:Offset_CCh)
	 */
	
	/*
	256 buses × 32 devices × 8 functions × 4 KiB = 256 MiB
	Each socket takes 32 buses = 256/<8 sockets> = 32
	*/

	for (int b = 0; b < 256; ++b) {
		for (int d=0; d < 32; ++d) {
			for (int f=0; f < 8; ++f) {
				uintptr_t loc = DEFAULT_PCIEXBAR + (b*32*8*0x1000) + (d*8*0x1000) + (f * 0x1000);
				if ((u32) *((u32 *)loc) != 0xffffffff)
					printk(BIOS_DEBUG, "[bus: %d, device: %d, func: %d], addr: 0x%lx, val: 0x%x\n", b, d, f, loc, (u32) *((u32 *)loc));
			}
		}
	}

	u32 bnum = get_data(0, 8, 2, 0xcc);
	printk(BIOS_DEBUG, "DEFAULT_PCIEXBAR: bus0: %d, bus1: %d, bus2: %d, bus3: %d\n", bnum & 0xff, (bnum >> 8) & 0xff,
				 (bnum >> 16) & 0xff, (bnum >> 24) & 0xff);
  outl(0x80000000 | 0 << 16 | 8 << 11 | 2 << 8 | (0xcc & 0xfc), 0xCF8);
  printk(BIOS_DEBUG, "inl retured 0x%x\n", inl(0xCFC));
	
	printk(BIOS_DEBUG, "DEFAULT_PCIEXBAR: 0x%x, mmcfg target list: 0x%x\n", DEFAULT_PCIEXBAR, get_data(1, 29, 1, 0xec));
	return system_agent_region_base(TOLUD) -
	       power_of_2(iqat_region_size + tseg_region_size);
}
#endif

u32 read_csr32(u32 bus, u32 dev, u32 func, u32 reg);
u32 read_csr32(u32 bus, u32 dev, u32 func, u32 reg)
{
  outl(0x80000000 | bus << 16 | dev << 11 | func << 8 | (reg & 0xfc), 0xcf8);
	return inl(0xcfc);
}

#define UBOX_DECS_BUS             0
#define UBOX_DECS_DEV             8
#define UBOX_DECS_FUNC            2
#define UBOX_DECS_CPUBUSNO_CSR    0xcc

/*
 * Get Socket 0 CPUBUSNO(0), CPUBUSNO(1) PCI bus numbers UBOX (B0:D8:F2:Offset_CCh)
 */
void get_cpubusnos(u32 *bus0, u32 *bus1, u32 *bus2, u32 *bus3);
void get_cpubusnos(u32 *bus0, u32 *bus1, u32 *bus2, u32 *bus3)
{
	u32 bus =  read_csr32(UBOX_DECS_BUS, UBOX_DECS_DEV, UBOX_DECS_FUNC, UBOX_DECS_CPUBUSNO_CSR);
	if (bus0)
		*bus0 = (bus & 0xff);
	if (bus1)
		*bus1 = (bus >> 8) & 0xff;	
	if (bus2)
		*bus2 = (bus >> 16) & 0xff;	
	if (bus3)
		*bus3 = (bus >> 24) & 0xff;	
}

#define CHA_UTIL_ALL_DEV          29
#define CHA_UTIL_ALL_FUNC         1
#define CHA_UTIL_ALL_MMCFG_CSR    0xc0

/*
 * Get MMCFG CSR B1:D29:F1:Offset_C0h
 */
uintptr_t get_mmcfg_base(u32 bus);
uintptr_t get_mmcfg_base(u32 bus)
{
	u32 wl = read_csr32(bus, CHA_UTIL_ALL_DEV, CHA_UTIL_ALL_FUNC, CHA_UTIL_ALL_MMCFG_CSR);
	u32 wh = read_csr32(bus, CHA_UTIL_ALL_DEV, CHA_UTIL_ALL_FUNC, CHA_UTIL_ALL_MMCFG_CSR + 4);
	uintptr_t addr = ((((wh & 0x3fff) << 6) | ((wl >> 26) & 0x3f)) << 26);
	printk(BIOS_DEBUG, "CHA_UTIL_ALL_MMCFG_CSR wl: 0x%x, wh: 0x%x, addr: 0x%lx\n", wl, wh, addr);
	return addr;
}

#define VTD_DEV          5
#define VTD_FUNC         0
#define VTD_TOLM_CSR     0xd0
#define VTD_TSEG_CSR     0xa8

/*
 * Get TOLM CSR B0:D5:F0:Offset_d0h
 */
uintptr_t get_tolm(u32 bus);
uintptr_t get_tolm(u32 bus)
{
	u32 w = read_csr32(bus, VTD_DEV, VTD_FUNC, VTD_TOLM_CSR);
	uintptr_t addr =  w & 0xfc000000;
	printk(BIOS_DEBUG, "VTD_TOLM_CSR 0x%x, addr: 0x%lx\n", w, addr);
	return addr;
}

void get_tseg_base_lim(u32 bus, u32 *base, u32 *limit);
void get_tseg_base_lim(u32 bus, u32 *base, u32 *limit)
{
	u32 w1 = read_csr32(bus, VTD_DEV, VTD_FUNC, VTD_TSEG_CSR);
	u32 wh = read_csr32(bus, VTD_DEV, VTD_FUNC, VTD_TSEG_CSR + 4);
	*base = w1 & 0xfff00000;
	*limit = wh & 0xfff00000;
}

u32 top_of_32bit_ram(void)
{
	u32 bus0 = 0, bus1 = 0;
	get_cpubusnos(&bus0, &bus1, NULL, NULL);

	uintptr_t mmcfg = get_mmcfg_base(bus1);
	uintptr_t tolm = get_tolm(bus0);
	printk(BIOS_DEBUG, "bus0: 0x%x, bus1: 0x%x, mmcfg: 0x%lx, tolm: 0x%lx\n", bus0, bus1, mmcfg, tolm);
	u32 base = 0, limit = 0;
	get_tseg_base_lim(bus0, &base, &limit);
	printk(BIOS_DEBUG, "base: 0x%x, limit: 0x%x\n", base, limit);

#if 0
  for (int b = 0; b < 256; ++b) {
    for (int d=0; d < 32; ++d) {
      for (int f=0; f < 8; ++f) {
        uintptr_t loc = DEFAULT_PCIEXBAR + (b*32*8*0x1000) + (d*8*0x1000) + (f * 0x1000);
        if ((u32) *((u32 *)loc) != 0xffffffff)
          printk(BIOS_DEBUG, "[bus: %d, device: %d, func: %d], addr: 0x%lx, val: 0x%x\n", b, d, f, loc, (u32) *((u32 *)loc));
      }
    }
  }
#endif

	/*
   * We will use TSEG base as the top of DRAM
   */
	return base;
}

void *cbmem_top(void) 
{ 
	u32 addr = top_of_32bit_ram();
	printk(BIOS_DEBUG, "addr: 0x%x\n", addr);
	return (void *) addr;
}

static inline uintptr_t smm_region_start(void)
{
	return system_agent_region_base(TSEGMB);
}

static inline size_t smm_region_size(void)
{
	return system_agent_region_base(TOLUD) - smm_region_start();
}

void smm_region(void **start, size_t *size)
{
	*start = (void *)smm_region_start();
	*size = smm_region_size();
}

int smm_subregion(int sub, void **start, size_t *size)
{
	uintptr_t sub_base;
	size_t sub_size;
	const size_t cache_size = CONFIG_SMM_RESERVED_SIZE;

	sub_base = smm_region_start();
	sub_size = smm_region_size();

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

	*start = (void *)sub_base;
	*size = sub_size;

	return 0;
}

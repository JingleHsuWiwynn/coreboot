/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 - 2019 Intel Corporation.
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

#ifndef _SKXSP_UTIL_H_
#define _SKXSP_UTIL_H_

#include <soc/hob_mem.h>
#include <soc/hob_iiouds.h>
#include <soc/hob_memorymapdata.h>
#include <arch/acpi.h>

#define LOG_MEM_RESOURCE(type, dev, index, base_kb, size_kb) \
 printk(BIOS_SPEW, "%s:%d res: %s, dev: %s, index: 0x%x, base: 0x%llx, end: 0x%llx, size_kb: 0x%llx\n", \
        __func__, __LINE__, type, dev_path(dev), index, (base_kb << 10), (base_kb << 10) + (size_kb << 10) - 1, size_kb)

#define LOG_IO_RESOURCE(type, dev, index, base, size) \
 printk(BIOS_SPEW, "%s:%d res: %s, dev: %s, index: 0x%x, base: 0x%llx, end: 0x%llx, size: 0x%llx\n", \
        __func__, __LINE__, type, dev_path(dev), index, base, base + size - 1, size)

#define ADD_MMIO_RESOURCE(dev, index, base, size) \
	mmio_resource(dev, index, (uint64_t) ((uint64_t)base >> 10), (uint64_t) ((uint64_t)size >> 10)); \
	LOG_MEM_RESOURCE("mmio", dev, index,  (uint64_t) ((uint64_t)base >> 10), (uint64_t) ((uint64_t)size >> 10))

#define DEV_FUNC_ENTER(dev) \
	printk(BIOS_SPEW, "%s:%s:%d: ENTER (dev: %s)\n", __FILE__, __func__, __LINE__, dev_path(dev))

#define DEV_FUNC_EXIT(dev) \
	printk(BIOS_SPEW, "%s:%s:%d: EXIT (dev: %s)\n", __FILE__, __func__, __LINE__, dev_path(dev))

#define FUNC_ENTER() \
	printk(BIOS_SPEW, "%s:%s:%d: ENTER\n", __FILE__, __func__, __LINE__)

#define FUNC_EXIT() \
	printk(BIOS_SPEW, "%s:%s:%d: EXIT\n", __FILE__, __func__, __LINE__)

struct iiostack_resource {
  u8                  no_of_stacks;
  STACK_RES           *sres;
};

uintptr_t get_tolm(u32 bus);
void get_tseg_base_lim(u32 bus, u32 *base, u32 *limit);
uintptr_t get_cha_mmcfg_base(u32 bus);
void get_cpubusnos(u32 *bus0, u32 *bus1, u32 *bus2, u32 *bus3);
u32 pci_read_csr32(u32 bus, u32 dev, u32 func, u32 reg);
void pci_write_csr32(u32 bus, u32 dev, u32 func, u32 reg, u32 val);
u32 pci_read_mmio_reg(int bus, u32 dev, u32 func, int offset);
void debug_pci_scan_buses(void);
void get_stack_busnos(u32 *bus);
void dump_iio_stack_basic(void);
void dump_iio_stack_detailed(void);
void unlock_pam_regions(void);
int get_threads_per_package(void);
int get_platform_thread_count(void);
void dump_pch_int_regs(const char *header);
void get_iiostack_info(struct iiostack_resource *info);
void xeonsp_init_cpu_config(void);
unsigned int get_srat_memory_entries(acpi_srat_mem_t *srat_mem);
void get_core_thread_bits(uint32_t *core_bits, uint32_t *thread_bits);
void get_cpu_info_from_apicid(uint32_t apicid, uint32_t core_bits, uint32_t thread_bits,
                              uint8_t *package, uint8_t *core, uint8_t *thread);

#endif /* _SKXSP_UTIL_H_ */

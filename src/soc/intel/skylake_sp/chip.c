/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 - 2017 Intel Corp.
 * Copyright (C) 2017 Online SAS.
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

#include <arch/acpi.h>
#include <bootstate.h>
#include <cbfs.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <fsp/api.h>
#include <fsp/util.h>
#include <intelblocks/fast_spi.h>
#include <soc/iomap.h>
#include <soc/intel/common/vbt.h>
#include <soc/pci_devs.h>
#include <soc/ramstage.h>
#include <spi-generic.h>
#include <soc/hob_mem.h>

static void pci_domain_set_resources(struct device *dev)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
#if 0
	assign_resources(dev->link_list);
#endif
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
}

static struct device_operations pci_domain_ops = {
	.read_resources = &pci_domain_read_resources,
	.set_resources = &pci_domain_set_resources,
	.scan_bus = &pci_domain_scan_bus,
};

static struct device_operations cpu_bus_ops = {
	.read_resources = DEVICE_NOOP,
	.set_resources = DEVICE_NOOP,
	.enable_resources = DEVICE_NOOP,
	.init = skylake_sp_init_cpus,
	.scan_bus = NULL,
#if IS_ENABLED(CONFIG_HAVE_ACPI_TABLES)
	.acpi_fill_ssdt_generator = generate_cpu_entries,
#endif
};

static void soc_enable_dev(struct device *dev)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
	/* Set the operations if it is a special bus type */
	if (dev->path.type == DEVICE_PATH_DOMAIN)
		dev->ops = &pci_domain_ops;
	else if (dev->path.type == DEVICE_PATH_CPU_CLUSTER)
		dev->ops = &cpu_bus_ops;
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
}

static void soc_init(void *data)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s\n", __FILE__, __LINE__, __func__);
	printk(BIOS_DEBUG, "coreboot: calling fsp_silicon_init\n");
	fsp_silicon_init(false);
	printk(BIOS_DEBUG, "coreboot: calling soc_save_dimm_info \n");
	soc_save_dimm_info();
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s\n", __FILE__, __LINE__, __func__);
}

static void soc_final(void *data) 
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s\n", __FILE__, __LINE__, __func__);
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s\n", __FILE__, __LINE__, __func__);
}

static void soc_silicon_init_params(FSPS_UPD *silupd)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s\n", __FILE__, __LINE__, __func__);
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s\n", __FILE__, __LINE__, __func__);
}

void platform_fsp_silicon_init_params_cb(FSPS_UPD *silupd)
{
	const struct microcode *microcode_file;
	size_t microcode_len;

	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s\n", __FILE__, __LINE__, __func__);
	microcode_file = cbfs_boot_map_with_leak("cpu_microcode_blob.bin",
		CBFS_TYPE_MICROCODE, &microcode_len);

	if ((microcode_file != NULL) && (microcode_len != 0)) {
		/* Update CPU Microcode patch base address/size */
		silupd->FspsConfig.PcdCpuMicrocodePatchBase =
		       (uint32_t)microcode_file;
		silupd->FspsConfig.PcdCpuMicrocodePatchSize =
		       (uint32_t)microcode_len;
	}

	printk(BIOS_DEBUG, "platform_fsp_silicon_init_params_cb calling soc_silicon_init_params\n");
	soc_silicon_init_params(silupd);
	printk(BIOS_DEBUG, "platform_fsp_silicon_init_params_cb calling mainboard_silicon_init_params\n");
	mainboard_silicon_init_params(silupd);
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s\n", __FILE__, __LINE__, __func__);
}

struct chip_operations soc_intel_skylake_sp_ops = {
	CHIP_NAME("Intel Skylake-SP SOC")
	.enable_dev = soc_enable_dev,
	.init = soc_init,
	.final = soc_final
};

static void soc_set_subsystem(struct device *dev, uint32_t vendor,
			      uint32_t device)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
	if (!vendor || !device) {
		pci_write_config32(dev, PCI_SUBSYSTEM_VENDOR_ID,
				   pci_read_config32(dev, PCI_VENDOR_ID));
	} else {
		pci_write_config32(dev, PCI_SUBSYSTEM_VENDOR_ID,
				   ((device & 0xffff) << 16) |
					   (vendor & 0xffff));
	}
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
}

struct pci_operations soc_pci_ops = {
	.set_subsystem = soc_set_subsystem,
};

/*
 * spi_flash init() needs to run unconditionally on every boot (including
 * resume) to allow write protect to be disabled for eventlog and nvram
 * updates. This needs to be done as early as possible in ramstage. Thus, add a
 * callback for entry into BS_PRE_DEVICE.
 */
static void spi_flash_init_cb(void *unused)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s\n", __FILE__, __LINE__, __func__);
	fast_spi_init();
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s\n", __FILE__, __LINE__, __func__);
}

BOOT_STATE_INIT_ENTRY(BS_PRE_DEVICE, BS_ON_ENTRY, spi_flash_init_cb, NULL);

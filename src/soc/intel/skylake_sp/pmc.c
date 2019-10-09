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

#include <reg_script.h>

#include <arch/acpi.h>
#include <arch/io.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>

#include <soc/iomap.h>
#include <soc/pmc.h>
#include <soc/pm.h>
#include <soc/pci_devs.h>
#include <soc/ramstage.h>
#include <cpu/x86/smm.h>
#include <soc/skxsp_util.h>


/* While we read BAR dynamically in case it changed, let's
 * initialize it with a same value
 */
static u16 acpi_base = ACPI_BASE_ADDRESS;
static u32 pwrm_base = PCH_PWRM_BASE_ADDRESS;

static const struct reg_script pch_pmc_misc_init_script[] = {
  /* Enable SCI and clear SLP requests. */
  REG_IO_RMW32(ACPI_BASE_ADDRESS + PM1_CNT, ~SLP_TYP, SCI_EN),
  REG_SCRIPT_END
};


static void pch_power_options(struct device *dev) { /* TODO */ }

static void pch_set_acpi_mode(void)
{
	if (IS_ENABLED(CONFIG_HAVE_SMI_HANDLER) && !acpi_is_wakeup_s3()) {
		printk(BIOS_DEBUG, "Disabling ACPI via APMC:\n");
		outb(APM_CNT_ACPI_DISABLE, APM_CNT);
		printk(BIOS_DEBUG, "done.\n");
	}
}

static void pmc_init(struct device *dev)
{
	FUNC_ENTER();
	u32 actl;
	printk(BIOS_DEBUG, "pch: pmc_init\n");

	/* Get the base address */
	acpi_base = pci_read_config16(dev, PMC_ACPI_BASE) & MASK_PMC_ACPI_BASE;
	pwrm_base = pci_read_config32(dev, PMC_PWRMBASE) & MASK_PMC_PWRMBASE;
	printk(BIOS_DEBUG, "pmc_init acpi_base (reg - 0x%x): 0x%x, pwrm_base (reg - 0x%x): 0x%x\n", 
				 PMC_ACPI_BASE, acpi_base, PMC_PWRMBASE, pwrm_base);

	actl = pci_read_config32(dev, ACTL);
	printk(BIOS_DEBUG, "pmc_init ACTL csr: 0x%x, ACPI: %s, PWRM: %s, SCI IRQ Select: %d\n", actl, 
				 (actl & ACPI_EN) ? "enabled" : "NOT enabled",
				 (actl & PWRM_EN) ? "enabled" : "NOT enabled", (actl & 0x3));

	if (0) {
	/* Set the value for PCI command register. */
	pci_write_config16(dev, PCI_COMMAND, PCI_COMMAND_MASTER |
						     PCI_COMMAND_MEMORY |
						     PCI_COMMAND_IO);

	/* Setup power options. */
	pch_power_options(dev);

	reg_script_run_on_dev(dev, pch_pmc_misc_init_script);

	/* Configure ACPI mode. */
	pch_set_acpi_mode();
	}
	FUNC_EXIT();
}

static void pci_pmc_read_resources(struct device *dev)
{
	struct resource *res;

	FUNC_ENTER();

	/* Get the normal PCI resources of this device. */
	pci_dev_read_resources(dev);

	/* Add MMIO resource
	 * Use 0xaa as an unused index for PWRM BAR.
	 */
	u32 reg32 = pci_read_config32(dev, PMC_PWRMBASE) & MASK_PMC_PWRMBASE;
	if ((reg32 != 0x0) && (reg32 != 0xffffffff)) {
		res = new_resource(dev, 0xaa);
		res->base = reg32;
		res->size = 64 * 1024; /* 64K bytes memory config space */
		res->flags =
			IORESOURCE_MEM | IORESOURCE_ASSIGNED | IORESOURCE_FIXED;
		printk(BIOS_DEBUG,
		       "Adding PMC PWRM config space BAR 0x%08lx-0x%08lx.\n",
		       (unsigned long)(res->base),
		       (unsigned long)(res->base + res->size - 1));
	}

	/* Add MMIO resource
	 * Use 0xab as an unused index for ACPI BAR.
	 */
	u16 reg16 = pci_read_config16(dev, PMC_ACPI_BASE) & MASK_PMC_ACPI_BASE;
	if ((reg16 != 0x0) && (reg16 != 0xffff)) {
		res = new_resource(dev, 0xab);
		res->base = reg16;
		res->size = 0x100; /* 256 bytes I/O config space */
		res->flags = IORESOURCE_IO | IORESOURCE_SUBTRACTIVE |
			     IORESOURCE_ASSIGNED | IORESOURCE_FIXED;
		printk(BIOS_DEBUG, "Adding PMC  ACPI_BASE I/O config base: 0x%llx , size: 0x%llx\n", res->base, res->size);
	}

	FUNC_EXIT();
}

static struct device_operations pmc_ops = {
	.read_resources = pci_pmc_read_resources,
	.set_resources = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.scan_bus = 0,
	.init = pmc_init,
	.ops_pci = &soc_pci_ops,
};

static const struct pci_driver pch_pmc __pci_driver = {
	.ops = &pmc_ops,
	.vendor = PCI_VENDOR_ID_INTEL,
	.device = PCI_DEVICE_ID_INTEL_C620_PMC,
};

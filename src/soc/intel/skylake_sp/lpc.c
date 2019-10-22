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

#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <arch/io.h>
#include <arch/ioapic.h>
#include <arch/acpi.h>
#include <cpu/x86/smm.h>
#include <bootstate.h>

#include <intelblocks/p2sb.h>
#include <intelblocks/lpc_lib.h>
#include <intelblocks/itss.h>

#include <soc/skxsp_util.h>
#include <soc/lpc.h>
#include <soc/pci_devs.h>
#include <soc/pcr_ids.h>
#include <soc/ramstage.h>
#include <soc/iomap.h>
#include <soc/pcr.h>
#include <soc/p2sb.h>
#include <soc/acpi.h>
#include <soc/irq.h>
#include <lib.h>

#include "chip.h"

/* PCH-LP redirection entries */
#define PCH_LP_REDIR_ETR 120

/**
 * Set miscellaneous static southbridge features.
 *
 * @param dev PCI device with I/O APIC control registers
 */
static void pch_enable_ioapic(struct device *dev)
{
	/* Configured via FSP */
	/* PCH_IOAPIC_ID                   0x08 */
	printk(BIOS_DEBUG, "IOAPICID 0x%x, 0x%x\n", io_apic_read((void *)IO_APIC_ADDR, 0x00),
			   ((io_apic_read((void *)IO_APIC_ADDR, 0x00) & 0x0f000000) >> 24));
#if 0
	u32 reg32;

	/* src/arch/x86/ioapic.c IO_APIC_ADDR = 0xfec00000 IO_APIC0 1*/
	set_ioapic_id((void *)IO_APIC_ADDR, IO_APIC0);

	/* affirm full set of redirection table entries ("write once") */
	reg32 = io_apic_read((void *)IO_APIC_ADDR, 0x01);

	reg32 &= ~0x00ff0000;
	reg32 |= (PCH_LP_REDIR_ETR - 1) << 16;

	io_apic_write((void *)IO_APIC_ADDR, 0x01, reg32);

	/*
	 * Select Boot Configuration register (0x03) and
	 * use Processor System Bus (0x01) to deliver interrupts.
	 */
	io_apic_write((void *)IO_APIC_ADDR, 0x03, 0x01);
#endif
}

/* PIRQ[n]_ROUT[3:0] - PIRQ Routing Control
 * 0x00 - 0000 = Reserved
 * 0x01 - 0001 = Reserved
 * 0x02 - 0010 = Reserved
 * 0x03 - 0011 = IRQ3
 * 0x04 - 0100 = IRQ4
 * 0x05 - 0101 = IRQ5
 * 0x06 - 0110 = IRQ6
 * 0x07 - 0111 = IRQ7
 * 0x08 - 1000 = Reserved
 * 0x09 - 1001 = IRQ9
 * 0x0A - 1010 = IRQ10
 * 0x0B - 1011 = IRQ11
 * 0x0C - 1100 = IRQ12
 * 0x0D - 1101 = Reserved
 * 0x0E - 1110 = IRQ14
 * 0x0F - 1111 = IRQ15
 * PIRQ[n]_ROUT[7] - PIRQ Routing Control
 * 0x80 - The PIRQ is not routed.
 */

void soc_pch_pirq_init(const struct device *dev)
{
/* NOTE: FSP does PCHInterrupt Config */
#if 0
	const config_t *config = dev->chip_info;
	uint8_t pch_interrupt_routing[MAX_PXRC_CONFIG];
	struct device *irq_dev;

	/**
  ITSS.PxRC registers (PIRQx Routing Control) contains data for 8259 routing (how PIRQx is mapped to IRQy).
  This information is used by systems which choose to use legacy PIC
  interrupt controller. Only IRQ3-7,9-12,14,15 are valid. Values from this table
  will be programmed into ITSS.PxRC registers.
  11,  // PARC: PIRQA -> IRQ11
  10,  // PBRC: PIRQB -> IRQ10
  11,  // PCRC: PIRQC -> IRQ11
  11,  // PDRC: PIRQD -> IRQ11
  11,  // PERC: PIRQE -> IRQ11
  11,  // PFRC: PIRQF -> IRQ11
  11,  // PGRC: PIRQG -> IRQ11
  11   // PHRC: PIRQH -> IRQ11
  **/

	pch_interrupt_routing[0] = config->pirqa_routing;
	pch_interrupt_routing[1] = config->pirqb_routing;
	pch_interrupt_routing[2] = config->pirqc_routing;
	pch_interrupt_routing[3] = config->pirqd_routing;
	pch_interrupt_routing[4] = config->pirqe_routing;
	pch_interrupt_routing[5] = config->pirqf_routing;
	pch_interrupt_routing[6] = config->pirqg_routing;
	pch_interrupt_routing[7] = config->pirqh_routing;

	/*
		Programming Interrupt Registers in LPC via P2SB interface
	  Refer to C620 EDS 20.11 document for details
		Interrupt PCR Registers Summary
		These registers are within the PCH Private Configuration Space which is accessible
		through the PCH Sideband Interface. They can be accessed via (SBREG_BAR + PortID
		+ Register Offset).
	 */
	dump_pch_int_regs("Before itss_irq_init\n");
	itss_irq_init(pch_interrupt_routing);

  /* Initialize device's Interrupt Routings */
  write16((void *)PCH_PCR_ADDRESS(PID_ITSS, PCR_ITSS_PIR00),
    config->ir00_routing);
  write16((void *)PCH_PCR_ADDRESS(PID_ITSS, PCR_ITSS_PIR01),
    config->ir01_routing);
  write16((void *)PCH_PCR_ADDRESS(PID_ITSS, PCR_ITSS_PIR02),
    config->ir02_routing);
  write16((void *)PCH_PCR_ADDRESS(PID_ITSS, PCR_ITSS_PIR03),
    config->ir03_routing);
  write16((void *)PCH_PCR_ADDRESS(PID_ITSS, PCR_ITSS_PIR04),
    config->ir04_routing);

  /* Initialize device's Interrupt Polarity Control */
  write32((void *)PCH_PCR_ADDRESS(PID_ITSS, PCH_PCR_ITSS_IPC0),
    config->ipc0);
  write32((void *)PCH_PCR_ADDRESS(PID_ITSS, PCH_PCR_ITSS_IPC1),
    config->ipc1);
  write32((void *)PCH_PCR_ADDRESS(PID_ITSS, PCH_PCR_ITSS_IPC2),
    config->ipc2);
  write32((void *)PCH_PCR_ADDRESS(PID_ITSS, PCH_PCR_ITSS_IPC3),
    config->ipc3);

	for (irq_dev = all_devices; irq_dev; irq_dev = irq_dev->next) {
		u8 int_pin = 0, int_line = 0;

		if (irq_dev->path.type == DEVICE_PATH_PCI && !irq_dev->enabled)
			printk(BIOS_DEBUG, "irq_dev: %s not enabled\n",  dev_path(irq_dev));

		if (!irq_dev->enabled || irq_dev->path.type != DEVICE_PATH_PCI)
			continue;

		int_pin = pci_read_config8(irq_dev, PCI_INTERRUPT_PIN);

		switch (int_pin) {
		case 1: /* INTA# */
			int_line = config->pirqa_routing;
			break;
		case 2: /* INTB# */
			int_line = config->pirqb_routing;
			break;
		case 3: /* INTC# */
			int_line = config->pirqc_routing;
			break;
		case 4: /* INTD# */
			int_line = config->pirqd_routing;
			break;
		}

		if (!int_line) {
			printk(BIOS_DEBUG,  "irq_dev: %s invalid int_pin: 0x%x\n",  dev_path(irq_dev), int_pin);
			continue;
		}

		printk(BIOS_DEBUG, "irq_dev: %s, PCI_INTERRUPT_PIN: 0x%x, int_pin: 0x%x, "
					 "PCI_INTERRUPT_LINE: 0x%x, int_line: [0x%x => 0x%x]\n",
					 dev_path(irq_dev), PCI_INTERRUPT_PIN, int_pin, PCI_INTERRUPT_LINE,
					 pci_read_config8(irq_dev, PCI_INTERRUPT_LINE), int_line);
		pci_write_config8(irq_dev, PCI_INTERRUPT_LINE, int_line);
	}
#endif
}

static void pci_p2sb_read_resources(struct device *dev)
{
	struct resource *res;

	/* Add MMIO resource
	 * Use 0xda as an unused index for PCR BAR.
	 */
	res = new_resource(dev, 0xda);
	res->base = P2SB_BAR;
	res->size = P2SB_SIZE;
	res->flags = IORESOURCE_MEM | IORESOURCE_FIXED | IORESOURCE_STORED |
		     IORESOURCE_ASSIGNED;
	LOG_MEM_RESOURCE("P2SB PCR config space BAR", dev, 0xda, (res->base >> 10), (res->size >> 10));

	/* Add MMIO resource
	 * Use 0xdb as an unused index for IOAPIC.
	 */
	res = new_resource(dev, 0xdb); /* IOAPIC */
	res->base = IO_APIC_ADDR;
	res->size = IOAPIC_SIZE; //0x00001000;
	res->flags = IORESOURCE_MEM | IORESOURCE_ASSIGNED | IORESOURCE_FIXED;
	LOG_MEM_RESOURCE("IOAPIC", dev, 0xdb, (res->base >> 10), (res->size >> 10));
}

static void pch_enable_serial_irqs(struct device *dev)
{
	/* Set packet length and toggle silent mode bit for one frame. */
	pci_write_config8(dev, SERIRQ_CNTL,
			  (1 << 7) | (1 << 6) | ((21 - 17) << 2) | (0 << 0));
#if !CONFIG(SERIRQ_CONTINUOUS_MODE)
	pci_write_config8(dev, SERIRQ_CNTL,
			  (1 << 7) | (0 << 6) | ((21 - 17) << 2) | (0 << 0));
#endif
}

void lpc_soc_init(struct device *dev)
{
	printk(BIOS_DEBUG, "pch: lpc_init\n");
	return;

	/* Get the base address */

	/* Set the value for PCI command register. */
	pci_write_config16(dev, PCI_COMMAND,
			   PCI_COMMAND_SPECIAL | PCI_COMMAND_MASTER |
				   PCI_COMMAND_MEMORY | PCI_COMMAND_IO);

	/* Serial IRQ initialization. */
	pch_enable_serial_irqs(dev);

	/* IO APIC initialization. */
	pch_enable_ioapic(dev);

	/* Setup the PIRQ. */
	soc_pch_pirq_init(dev);
}

static const struct lpc_mmio_range skx_lpc_fixed_mmio_ranges[] = {
  { 0, 0 }
};

const struct lpc_mmio_range *soc_get_fixed_mmio_ranges(void)
{
  return skx_lpc_fixed_mmio_ranges;
}

static void pch_lpc_add_mmio_resources(struct device *dev)
{
  ADD_MMIO_RESOURCE(dev, 0xfd00, PCH_PRESERVED_BASE_ADDRESS, PCH_PRESERVED_BASE_SIZE);
  //ADD_MMIO_RESOURCE(dev, 0xfec0, IOXAPIC_BASE_ADDRESS, IOAPIC_SIZE);
  ADD_MMIO_RESOURCE(dev, 0xfed0, PCH_BASE_ADDRESS, PCH_BASE_SIZE);
  ADD_MMIO_RESOURCE(dev, 0xfee0, LXAPIC_BASE_ADDRESS, LXAPIC_BASE_SIZE);
  ADD_MMIO_RESOURCE(dev, 0xfef0, RESERVED2_BASE_ADDRESS, RESERVED2_BASE_SIZE);
  //ADD_MMIO_RESOURCE(dev, 0xff00, FIRMWARE_BASE_ADDRESS, FIRMWARE_BASE_SIZE);
}

static void pch_lpc_add_io_resources(struct device *dev)
{
	struct resource *res;
	u8 io_index = 0;

	/* Add an extra subtractive resource for both memory and I/O. */
	res = new_resource(dev, IOINDEX_SUBTRACTIVE(io_index++, 0));
	res->base = 0xff000000;
	res->size = FIRMWARE_BASE_SIZE; /* 16 MB for flash */
	res->flags = IORESOURCE_MEM | IORESOURCE_SUBTRACTIVE |
		     IORESOURCE_ASSIGNED | IORESOURCE_FIXED;
	LOG_MEM_RESOURCE("[MEM] subtractive_res", dev, io_index-1, (res->base >> 10), (res->size >> 10));
}

void pch_lpc_soc_fill_io_resources(struct device *dev)
{
	/* Add non-standard MMIO resources. */
	pch_lpc_add_mmio_resources(dev);

	/* Add IO resources. */
	pch_lpc_add_io_resources(dev);

	/* Add MMIO resource for IOAPIC. */
	pci_p2sb_read_resources(dev);
}

void southcluster_enable_dev(struct device *dev)
{
	u32 reg32;

	if (!dev->enabled) {
		printk(BIOS_DEBUG, "%s: Disabling device\n", dev_path(dev));

		/* Ensure memory, io, and bus master are all disabled */
		reg32 = pci_read_config32(dev, PCI_COMMAND);
		reg32 &= ~(PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY |
			   PCI_COMMAND_IO);
		pci_write_config32(dev, PCI_COMMAND, reg32);
	} else {
		/* Enable SERR */
		reg32 = pci_read_config32(dev, PCI_COMMAND);
		reg32 |= PCI_COMMAND_SERR;
		pci_write_config32(dev, PCI_COMMAND, reg32);
	}
}

static void finalize_chipset(void *unused)
{
	printk(BIOS_DEBUG, "Finalizing SMM.\n");
	outb(APM_CNT_FINALIZE, APM_CNT);
}

BOOT_STATE_INIT_ENTRY(BS_OS_RESUME, BS_ON_ENTRY, finalize_chipset, NULL);
BOOT_STATE_INIT_ENTRY(BS_PAYLOAD_LOAD, BS_ON_EXIT, finalize_chipset, NULL);

/*
 * This file is part of the coreboot project.
 *
 * Copyright 2016 Google Inc.
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

#include <intelblocks/fast_spi.h>
#include <spi-generic.h>
#include <arch/io.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <soc/pci_devs.h>
#include <soc/ramstage.h>
#include <soc/iomap.h>
#include <soc/skxsp_util.h>


const struct spi_ctrlr_buses spi_ctrlr_bus_map[] = {
	{ .ctrlr = &fast_spi_flash_ctrlr, .bus_start = 0, .bus_end = 0 },
};

const size_t spi_ctrlr_bus_map_count = ARRAY_SIZE(spi_ctrlr_bus_map);

#if ENV_RAMSTAGE
static void pci_spi_read_resources(struct device *dev)
{
  struct resource *res;

  FUNC_ENTER();

	/*
	00:1f.5 Serial bus controller [0c80]: Intel Corporation Lewisburg SPI Controller (rev 09)
		Subsystem: Intel Corporation Lewisburg SPI Controller
		Flags: fast devsel, NUMA node 0
		Memory at fe010000 (32-bit, non-prefetchable) [size=4K]
	pci 0000:00:1f.5: [8086:a1a4] type 00 class 0x0c8000
	pci 0000:00:1f.5: reg 0x10: [mem 0xfe010000-0xfe010fff]
	*/

  /* Get the normal PCI resources of this device. */
  pci_dev_read_resources(dev);
	for (res = dev->resource_list; res; res = res->next) {
		printk(BIOS_DEBUG, "%s%s resource base %llx size %llx "
          "align %d gran %d limit %llx flags %lx type %s%s%s%s%s%s index %lx\n",
          "\t", dev_path(dev), res->base, res->size,
          res->align, res->gran, res->limit, res->flags, resource_type(res),
          (res->flags & IORESOURCE_STORED) ? " stored" : "",
          (res->flags & IORESOURCE_RESERVE) ? " reserved" : "",
          (res->flags & IORESOURCE_FIXED) ? " fixed" : "",
          (res->flags & IORESOURCE_ASSIGNED) ? " assigned" : "",
          (res->flags & IORESOURCE_PREFETCH) ? " prefetchable " : " non-prefetchable",
          res->index);
		if (res->flags & IORESOURCE_MEM) {
			res->base = SPI_BASE_ADDRESS;
			res->flags |= IORESOURCE_ASSIGNED;
			break;
		}
	}

	//ADD_MMIO_RESOURCE(dev, 0x10, SPI_BASE_ADDRESS, SPI_BASE_SIZE);

  FUNC_EXIT();
}

static struct device_operations spi_ops = {
  .read_resources = pci_spi_read_resources,
  .set_resources = pci_dev_set_resources,
  .enable_resources = pci_dev_enable_resources,
  .scan_bus = 0,
  .init = NULL,
  .ops_pci = &soc_pci_ops,
};

static const struct pci_driver pch_spi __pci_driver = {
  .ops = &spi_ops,
  .vendor = PCI_VENDOR_ID_INTEL,
  .device = PCI_DEVICE_ID_INTEL_C620_SPI,
};

#endif

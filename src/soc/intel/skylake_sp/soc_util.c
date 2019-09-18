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

#include <stdint.h>
#include <arch/io.h>
#include <device/pci.h>
#include <device/pci_def.h>
#include <device/device.h>

#include <soc/iomap.h>
#include <soc/soc_util.h>
#include <soc/pmc.h>
#include <soc/smbus.h>
#include <soc/lpc.h>
#include <soc/pci_devs.h>
#include <soc/systemagent.h>

#if 0
uint16_t get_pmbase(void)
{
#ifdef __SIMPLE_DEVICE__
  pci_devfn_t dev;
#else
  struct device *dev;
#endif
  dev = PCH_DEV_PMC;

  if (!dev)
    return 0;

  return pci_read_config16(dev, PMC_ACPI_BASE) & 0xfff8;
}
#endif

uint16_t get_tcobase(void)
{
#ifdef __SIMPLE_DEVICE__
  pci_devfn_t dev;
#else
  struct device *dev;
#endif
  dev = PCH_DEV_SMBUS;

  if (!dev)
    return 0;

  return pci_read_config16(dev, TCOBASE) & MASK_TCOBASE;
}

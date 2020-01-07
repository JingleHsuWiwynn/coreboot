/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017 Intel Corp.
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

#include "tiogapass_boardid.h"
#include <console/console.h>
#include <fsp/api.h>
#include <fsp/soc_binding.h>
#include <FspmUpd.h>
#define PCH_SERVER_BIOS_FLAG 1
#include <soc/skxsp_gpio_lib.h>
#include <soc/skxsp_gpio_pins.h>
#include "skxsp_tp_gpio.h"
#include "skxsp_tp_iio.h"
#include <soc/lpc.h>
#include <device/pci_type.h>
#include <device/pci_ops.h>
#include "soc/intel/common/block/include/intelblocks/pcr.h"

typedef struct {
	u32 BaseAddr :16;
	u32 Length :15;
	u32 Enable :1;
} PCH_LPC_GEN_IO_RANGE;

typedef struct {
	PCH_LPC_GEN_IO_RANGE Range[4];
} PCH_LPC_GEN_IO_RANGE_LIST;


void mainboard_config_gpios(FSPM_UPD *mupd);
void mainboard_config_iio(FSPM_UPD *mupd);
void mainboard_memory_init_params(FSPM_UPD *mupd);
int PchLpcGenIoRangeSet(u16 Address, UINTN Length, u8 SlaveDevice);
int PchLpcGenIoRangeGet(PCH_LPC_GEN_IO_RANGE_LIST *LpcGenIoRangeList, u8 SlaveDevice);

/**
  Get PCH LPC/eSPI generic IO range list.
  This function returns a list of base address, length, and enable for all LPC/eSPI generic IO range regsiters.

  @param[out] LpcGenIoRangeList         Return all LPC/eSPI generic IO range register status.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid base address passed.
**/
int PchLpcGenIoRangeGet (
  PCH_LPC_GEN_IO_RANGE_LIST *LpcGenIoRangeList, u8 SlaveDevice
  )
{
  UINTN Index;
  u32 Data32;

  //
  // Note: Inside this function, don't use debug print since it's could used before debug print ready.
  //

  if (LpcGenIoRangeList == NULL) {
	printk(BIOS_DEBUG, "LpcGenIoRangeList == NULL\n");  
    return 2;
  }

  if (SlaveDevice == 0) {
    for (Index = 0; Index < 4; Index++) {
	  Data32 = pci_read_config32(PCH_LPC_DEV, 0x84 + Index * 4);		
//      Data32 = MmioRead32 (LpcBase + 0x84 + Index * 4);
      LpcGenIoRangeList->Range[Index].BaseAddr = Data32 & 0x0000fffc;
      LpcGenIoRangeList->Range[Index].Length   = ((Data32 & 0x00fc0000) >> 16) + 4;
      LpcGenIoRangeList->Range[Index].Enable   = Data32 & 0x00000001;
    }
  } else {
	Data32 = pci_read_config32(PCH_LPC_DEV, 0xA4);  
//    Data32 = MmioRead32 (LpcBase + 0xA4);
    LpcGenIoRangeList->Range[0].BaseAddr = Data32 & 0x0000fffc;
    LpcGenIoRangeList->Range[0].Length   = ((Data32 & 0x00fc0000) >> 16) + 4;
    LpcGenIoRangeList->Range[0].Enable   = Data32 & 0x00000001;
  }
  return 0;
}

/**
  Set PCH LPC/eSPI generic IO range.
  For generic IO range, the base address must align to 4 and less than 0xFFFF, and the length must be power of 2
  and less than or equal to 256. Moreover, the address must be length aligned.
  This function basically checks the address and length, which should not overlap with all other generic ranges.
  If no more generic range register available, it returns out of resource error.
  This cycle decoding is allowed to set when DMIC.SRL is 0.
  Some IO ranges below 0x100 have fixed target. The target might be ITSS,RTC,LPC,PMC or terminated inside P2SB
  but all predefined and can't be changed. IO range below 0x100 will be rejected in this function except below ranges:
    0x00-0x1F,
    0x44-0x4B,
    0x54-0x5F,
    0x68-0x6F,
    0x80-0x8F,
    0xC0-0xFF
  Steps of programming generic IO range:
  1. Program LPC/eSPI PCI Offset 84h ~ 93h of Mask, Address, and Enable.
  2. Program LPC/eSPI Generic IO Range #, PCR[DMI] + 2730h ~ 273Fh to the same value programmed in LPC/eSPI PCI Offset 84h~93h.

  @param[in] Address                    Address for generic IO range base address.
  @param[in] Length                     Length of generic IO range.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid base address or length passed.
  @retval EFI_OUT_OF_RESOURCES          No more generic range available.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/

int PchLpcGenIoRangeSet (u16 Address, UINTN Length, u8 SlaveDevice)
{
  PCH_LPC_GEN_IO_RANGE_LIST             LpcGenIoRangeList;
  UINTN                                 Index;
  UINTN                                 BaseAddr;
  UINTN                                 MaskLength;
  UINTN                                 TempMaxAddr;
  u32                               	Data32;
  UINTN                                 ArraySize;
  u8									Status; 
  static struct EXCEPT_RANGE {
    u8 Start;
    u8 Length;
  } ExceptRanges[] = { {0x00, 0x20}, {0x44, 0x08}, {0x54, 0x0C}, {0x68, 0x08}, {0x80, 0x10}, {0xC0, 0x40} };

  Index = 0;
  //
  // Note: Inside this function, don't use debug print since it's could used before debug print ready.
  //

  //
  // For generic IO range, the base address must align to 4 and less than 0xFFFF,
  // the length must be power of 2 and less than or equal to 256, and the address must be length aligned.
  // IO range below 0x100 will be rejected in this function except below ranges:
  //   0x00-0x1F,
  //   0x44-0x4B,
  //   0x54-0x5F,
  //   0x68-0x6F,
  //   0x80-0x8F,
  //   0xC0-0xFF
  //
  if (((Length & (Length - 1)) != 0)  ||
      ((Address & (UINT16)~(0x0000fffc)) != 0) ||
      (Length > 256))
  {
	printk(BIOS_DEBUG, "Length > 256\n");  
    return 2;
  }
  if (Address < 0x100) {
    ArraySize = sizeof (ExceptRanges) / sizeof (struct EXCEPT_RANGE);
    for (Index = 0; Index < ArraySize; Index++) {
      if ((Address >= ExceptRanges[Index].Start) &&
          ((Address + Length) <= ((UINTN)ExceptRanges[Index].Start + (UINTN)ExceptRanges[Index].Length)))
      {
        break;
      }
    }
    if (Index >= ArraySize) {
	  printk(BIOS_DEBUG, "Index >= ArraySize\n");	
      return 2;
    }
  }

  //
  // check if range overlap
  //
  Status  = PchLpcGenIoRangeGet (&LpcGenIoRangeList, SlaveDevice);
  if (Status != 0) {
    return Status;
  }
  if (SlaveDevice == 0) {
    for (Index = 0; Index < 4; Index++) {
      BaseAddr = LpcGenIoRangeList.Range[Index].BaseAddr;
      MaskLength   = LpcGenIoRangeList.Range[Index].Length;
      if (BaseAddr == 0) {
        continue;
      }
      if (((Address >= BaseAddr) && (Address < (BaseAddr + MaskLength))) ||
          (((Address + Length) > BaseAddr) && ((Address + Length) <= (BaseAddr + MaskLength))))
      {
        if ((Address >= BaseAddr) && (Length <= MaskLength)) {
          //
          // return SUCCESS while range is covered.
          //
          return 0;
        }

        if ((Address + Length) > (BaseAddr + MaskLength)) {
          TempMaxAddr = Address + Length;
        } else {
          TempMaxAddr = BaseAddr + MaskLength;
        }
        if (Address > BaseAddr) {
          Address = (u16) BaseAddr;
        }
        Length = TempMaxAddr - Address;
        break;
      }
    }
    //
    // If no range overlap
    //
    if (Index >= 4) {
      //
      // Find a empty register
      //
      for (Index = 0; Index < 4; Index++) {
        BaseAddr = LpcGenIoRangeList.Range[Index].BaseAddr;
        if (BaseAddr == 0) {
          break;
        }
      }
      if (Index >= 4) {
		printk(BIOS_DEBUG, "Index >= 4\n");  
        return 9;
      }
    }
  } else {
    BaseAddr = LpcGenIoRangeList.Range[0].BaseAddr;
    MaskLength   = LpcGenIoRangeList.Range[0].Length;
    if (BaseAddr != 0) {
      if (((Address >= BaseAddr) && (Address < (BaseAddr + MaskLength))) ||
          (((Address + Length) > BaseAddr) && ((Address + Length) <= (BaseAddr + MaskLength))))
      {
        if ((Address >= BaseAddr) && (Length <= MaskLength)) {
          //
          // return SUCCESS while range is covered.
          //
          return 0;
        } else {
		  printk(BIOS_DEBUG, "Address <= BaseAddr\n");	
          return 9;
        }
      }
    }
  }
  //
  // This cycle decoding is only allowed to set when DMIC.SRL is 0.
  //
  Data32 = pcr_read32 (0xef, 0x2234);
  if ((Data32 & BIT31) != 0) {
	printk(BIOS_DEBUG, "(Data32 & BIT31) != 0\n");  
    return 3;
  }

  //
  // Program LPC/eSPI generic IO range register accordingly.
  //
  Data32 =  (u32) (((Length - 1) << 16) & 0x00FC0000);
  Data32 |= (u32) Address;
  Data32 |= 0x00000001;

  if (SlaveDevice == 0) {
    //
    // Program LPC/eSPI PCI Offset 84h ~ 93h of Mask, Address, and Enable.
    //
    pci_write_config32(PCH_LPC_DEV, 0x84 + Index * 4, Data32);

    //
    // Program LPC Generic IO Range #, PCR[DMI] + 2730h ~ 273Fh to the same value programmed in LPC/eSPI PCI Offset 84h~93h.
    //
    pcr_write32 (
      0xef, (u16) (0x2730+ Index * 4),
      Data32
      );
  } else {
    //
    // Program LPC/eSPI PCI Offset A4h of Mask, Address, and Enable.
    //
    pci_write_config32(PCH_LPC_DEV, 0xA4, Data32);

    //
    // Program LPC Generic IO Range #, PCR[DMI] + 27BCh to the same value programmed in LPC/eSPI PCI Offset A4h.
    //
    pcr_write32 (
      0xef, (u16) (0x27bc),
      Data32
      );
  }
  return 0;
}

/*
* Configure GPIO depend on platform
*/
void mainboard_config_gpios(FSPM_UPD *mupd)
{
	mupd->FspmConfig.GpioConfig.GpioTable = (UPD_GPIO_INIT_CONFIG *) tp_gpio_table;
	mupd->FspmConfig.GpioConfig.NumberOfEntries = sizeof(tp_gpio_table)/sizeof(UPD_GPIO_INIT_CONFIG);
}

void mainboard_config_iio(FSPM_UPD *mupd)
{
	mupd->FspmConfig.IioBifurcationConfig.IIoBifurcationTable = (UPD_IIO_BIFURCATION_DATA_ENTRY *) tp_iio_bifur_table;
	mupd->FspmConfig.IioBifurcationConfig.NumberOfEntries = sizeof(tp_iio_bifur_table)/sizeof(UPD_IIO_BIFURCATION_DATA_ENTRY);

	mupd->FspmConfig.IioPciConfig.ConfigurationTable = (UPD_PCI_PORT_CONFIG *) tp_iio_pci_port_skt0;
	mupd->FspmConfig.IioPciConfig.NumberOfEntries = sizeof(tp_iio_pci_port_skt0)/sizeof(UPD_PCI_PORT_CONFIG);

	mupd->FspmConfig.PchPciConfig.PciPortConfig = (UPD_PCH_PCIE_PORT *) tp_pch_pci_port_skt0;
	mupd->FspmConfig.PchPciConfig.NumberOfEntries = sizeof(tp_pch_pci_port_skt0)/sizeof(UPD_PCH_PCIE_PORT);

	mupd->FspmConfig.PchPciConfig.RootPortFunctionSwapping = 0x00;
	mupd->FspmConfig.PchPciConfig.PciePllSsc = 0x00;
}

void mainboard_memory_init_params(FSPM_UPD *mupd)
{

	printk(BIOS_DEBUG, "Enable LPC BMC base address\n");
	PchLpcGenIoRangeSet((0xca2 & 0xFFF0), 0x10, 0);
			   
	mainboard_config_gpios(mupd);
	mainboard_config_iio(mupd);
}

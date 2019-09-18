/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007 - 2009 coresystems GmbH
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

// 00:1F.0 ISA bridge: Intel Corporation Lewisburg LPC Controller (rev 09)

Device (LPCB)
{
	Name(_ADR, 0x001f0000)

	OperationRegion(LPC0, PCI_Config, 0x00, 0x100)
	Field (LPC0, AnyAcc, NoLock, Preserve)
	{
		Offset (0x80),	// IO Decode Ranges
		IOD0,	8,
		IOD1,	8,
	}

	#include "irqlinks.asl"

	Device(LDRC)	// LPC device: Resource consumption
	{
		Name (_HID, EISAID("PNP0C02"))
		Name (_UID, 2)
		Name (_CRS, ResourceTemplate()
		{
			IO (Decode16, 0x2e, 0x2e, 0x1, 0x02)		// First SuperIO
			IO (Decode16, 0x4e, 0x4e, 0x1, 0x02)		// Second SuperIO
			IO (Decode16, 0x61, 0x61, 0x1, 0x01)		// NMI Status
			IO (Decode16, 0x63, 0x63, 0x1, 0x01)		// CPU Reserved
			IO (Decode16, 0x65, 0x65, 0x1, 0x01)		// CPU Reserved
			IO (Decode16, 0x67, 0x67, 0x1, 0x01)		// CPU Reserved
			IO (Decode16, 0x70, 0x70, 0x1, 0x01)		// NMI Enable.
			IO (Decode16, 0x80, 0x80, 0x1, 0x01)		// Port 80 Post
			IO (Decode16, 0x92, 0x92, 0x1, 0x01)		// CPU Reserved
			IO (Decode16, 0xb2, 0xb2, 0x1, 0x02)		// SWSMI
			//IO (Decode16, 0x800, 0x800, 0x1, 0x10)		// ACPI I/O trap

			// BIOS ROM shadow memory range
			Memory32Fixed(ReadOnly, 0x000E0000, 0x20000)

			// BIOS flash 16MB
			Memory32Fixed(ReadOnly,0xFF000000,0x1000000)
		})
	}

	 Device (DMAC)
	 {
				Name (_HID, EisaId ("PNP0200") /* PC-class DMA Controller */)  // _HID: Hardware ID
				Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
				{
						IO (Decode16,
								0x0000,             // Range Minimum
								0x0000,             // Range Maximum
								0x00,               // Alignment
								0x10,               // Length
								)
						IO (Decode16,
								0x0081,             // Range Minimum
								0x0081,             // Range Maximum
								0x00,               // Alignment
								0x03,               // Length
								)
						IO (Decode16,
								0x0087,             // Range Minimum
								0x0087,             // Range Maximum
								0x00,               // Alignment
								0x01,               // Length
								)
						IO (Decode16,
								0x0089,             // Range Minimum
								0x0089,             // Range Maximum
								0x00,               // Alignment
								0x03,               // Length
								)
						IO (Decode16,
								0x008F,             // Range Minimum
								0x008F,             // Range Maximum
								0x00,               // Alignment
								0x01,               // Length
								)
						IO (Decode16,
								0x00C0,             // Range Minimum
								0x00C0,             // Range Maximum
								0x00,               // Alignment
								0x20,               // Length
								)
						DMA (Compatibility, NotBusMaster, Transfer8, )
								{4}
				})
		}

		Device (RTC)
		{
				Name (_HID, EisaId ("PNP0B00") /* AT Real-Time Clock */)  // _HID: Hardware ID
				Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
				{
						IO (Decode16,
								0x0070,             // Range Minimum
								0x0070,             // Range Maximum
								0x01,               // Alignment
								0x02,               // Length
								)
						IO (Decode16,
								0x0074,             // Range Minimum
								0x0074,             // Range Maximum
								0x01,               // Alignment
								0x04,               // Length
								)
						IRQNoFlags ()
								{8}
				})
		}

    Device (PIC)
    {
        Name (_HID, EisaId ("PNP0000") /* 8259-compatible Programmable Interrupt Controller */)  // _HID: Hardware ID
        Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
        {
            IO (Decode16,
                0x0020,             // Range Minimum
                0x0020,             // Range Maximum
                0x01,               // Alignment
                0x1E,               // Length
                )
            IO (Decode16,
                0x00A0,             // Range Minimum
                0x00A0,             // Range Maximum
                0x01,               // Alignment
                0x1E,               // Length
                )
            IO (Decode16,
                0x04D0,             // Range Minimum
                0x04D0,             // Range Maximum
                0x01,               // Alignment
                0x02,               // Length
                )
        })
    }

    Device (FPU)
    {
        Name (_HID, EisaId ("PNP0C04") /* x87-compatible Floating Point Processing Unit */)  // _HID: Hardware ID
        Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
        {
            IO (Decode16,
                0x00F0,             // Range Minimum
                0x00F0,             // Range Maximum
                0x01,               // Alignment
                0x01,               // Length
                )
            IRQNoFlags ()
                {13}
        })
    }

    Device (TIMR) // Intel 8254 timer
    {
        Name (_HID, EisaId ("PNP0100") /* PC-class System Timer */)  // _HID: Hardware ID
        Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
        {
            IO (Decode16,
                0x0040,             // Range Minimum
                0x0040,             // Range Maximum
                0x01,               // Alignment
                0x04,               // Length
                )
            IO (Decode16,
                0x0050,             // Range Minimum
                0x0050,             // Range Maximum
                0x01,               // Alignment
                0x04,               // Length
                )
            IRQNoFlags ()
                {0}
        })
    }

    Device (SPKR)
    {
        Name (_HID, EisaId ("PNP0800") /* Microsoft Sound System Compatible Device */)  // _HID: Hardware ID
        Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
        {
            IO (Decode16,
                0x0061,             // Range Minimum
                0x0061,             // Range Maximum
                0x01,               // Alignment
                0x01,               // Length
                )
        })
    }

		Device (XTRA)
		{
				Name (_HID, EisaId ("PNP0C02") /* PNP Motherboard Resources */)  // _HID: Hardware ID
				Name (_UID, 0x10)  // _UID: Unique ID
				Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
				{
						IO (Decode16,
								0x0500,             // Range Minimum
								0x0500,             // Range Maximum
								0x01,               // Alignment
								0x40,               // Length
								)
						IO (Decode16,
								0x0400,             // Range Minimum
								0x0400,             // Range Maximum
								0x01,               // Alignment
								0x80,               // Length
								)
						IO (Decode16,
								0x0092,             // Range Minimum
								0x0092,             // Range Maximum
								0x01,               // Alignment
								0x01,               // Length
								)
						IO (Decode16,
								0x0010,             // Range Minimum
								0x0010,             // Range Maximum
								0x01,               // Alignment
								0x10,               // Length
								)
						IO (Decode16,
								0x0072,             // Range Minimum
								0x0072,             // Range Maximum
								0x01,               // Alignment
								0x02,               // Length
								)
						IO (Decode16,
								0x0080,             // Range Minimum
								0x0080,             // Range Maximum
								0x01,               // Alignment
								0x01,               // Length
								)
						IO (Decode16,
								0x0084,             // Range Minimum
								0x0084,             // Range Maximum
								0x01,               // Alignment
								0x03,               // Length
								)
						IO (Decode16,
								0x0088,             // Range Minimum
								0x0088,             // Range Maximum
								0x01,               // Alignment
								0x01,               // Length
								)
						IO (Decode16,
								0x008C,             // Range Minimum
								0x008C,             // Range Maximum
								0x01,               // Alignment
								0x03,               // Length
								)
						IO (Decode16,
								0x0090,             // Range Minimum
								0x0090,             // Range Maximum
								0x01,               // Alignment
								0x10,               // Length
								)
						IO (Decode16,
								0x0540,             // Range Minimum
								0x0540,             // Range Maximum
								0x01,               // Alignment
								0x40,               // Length
								)
						IO (Decode16,
								0x0600,             // Range Minimum
								0x0600,             // Range Maximum
								0x01,               // Alignment
								0x20,               // Length
								)
						IO (Decode16,
								0x0880,             // Range Minimum
								0x0880,             // Range Maximum
								0x01,               // Alignment
								0x04,               // Length
								)
						IO (Decode16,
								0x0800,             // Range Minimum
								0x0800,             // Range Maximum
								0x01,               // Alignment
								0x20,               // Length
								)
						Memory32Fixed (ReadOnly,
								0xFED1C000,         // Address Base
								0x00024000,         // Address Length
								)
						Memory32Fixed (ReadOnly,
								0xFED45000,         // Address Base
								0x00047000,         // Address Length
								)
						Memory32Fixed (ReadOnly,
								0xFF000000,         // Address Base
								0x01000000,         // Address Length
								)
						Memory32Fixed (ReadOnly,
								0xFEE00000,         // Address Base
								0x00100000,         // Address Length
								)
						Memory32Fixed (ReadWrite,
								0xFED12000,         // Address Base
								0x00000010,         // Address Length
								)
						Memory32Fixed (ReadWrite,
								0xFED12010,         // Address Base
								0x00000010,         // Address Length
								)
						Memory32Fixed (ReadOnly,
								0xFED1B000,         // Address Base
								0x00001000,         // Address Length
								)
				})
		}

	// NOTE: this covers only one HPET, refer to prior BIOS output to create more
	// flexible ACPI config
	Device (HPET)
	{
		Name (_HID, EisaId ("PNP0103") /* HPET System Timer */)  // _HID: Hardware ID
		Name (_CID, 0x010CD041)

		Method (_STA, 0)	// Device Status
		{
			Return (0xF)	// Enable and show device
		}

		Name(_CRS, ResourceTemplate()
		{
			Memory32Fixed(ReadOnly, HPET_BASE_ADDRESS, 0x400)
		})
	}

	Device(IUR3) // Internal UART 1
	{
	  Name(_HID, EISAID("PNP0501"))

	  Name(_UID,1)

	  // Status Method for internal UART 1.

	  Method(_STA,0,Serialized)
	  {
			Return(0x000F)
	  }

	  // Current Resource Setting Method for internal UART 1.

	  Method(_CRS,0,Serialized)
	  {
			// Create the Buffer that stores the Resources to
			// be returned.

			Name(BUF0,ResourceTemplate()
			{
				IO(Decode16,0x03F8,0x03F8,0x01,0x08)
				Interrupt (ResourceConsumer, Level, ActiveLow, Shared) {16}
			})

			Return(BUF0)
	  }
        Name (_PRS, ResourceTemplate ()  // _PRS: Possible Resource Settings
        {
            StartDependentFn (0x00, 0x00)
            {
                IO (Decode16,
                    0x03F8,             // Range Minimum
                    0x03F8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                IRQNoFlags ()
                    {4}
                DMA (Compatibility, NotBusMaster, Transfer8, )
                    {}
            }
            StartDependentFnNoPri ()
            {
                IO (Decode16,
                    0x03F8,             // Range Minimum
                    0x03F8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                IRQNoFlags ()
                    {3,4,5,7,9,10,11,12}
                DMA (Compatibility, NotBusMaster, Transfer8, )
                    {}
            }
            StartDependentFnNoPri ()
            {
                IO (Decode16,
                    0x02F8,             // Range Minimum
                    0x02F8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                IRQNoFlags ()
                    {3,4,5,7,9,10,11,12}
                DMA (Compatibility, NotBusMaster, Transfer8, )
                    {}
            }
            StartDependentFnNoPri ()
            {
                IO (Decode16,
                    0x03E8,             // Range Minimum
                    0x03E8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                IRQNoFlags ()
                    {3,4,5,7,9,10,11,12}
                DMA (Compatibility, NotBusMaster, Transfer8, )
                    {}
            }
            StartDependentFnNoPri ()
            {
                IO (Decode16,
                    0x02E8,             // Range Minimum
                    0x02E8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                IRQNoFlags ()
                    {3,4,5,7,9,10,11,12}
                DMA (Compatibility, NotBusMaster, Transfer8, )
                    {}
            }
            EndDependentFn ()
        })

	}


	Device(IUR4) // Internal UART 2
	{
	  Name(_HID, EISAID("PNP0501"))
	  Name(_UID,2)
	  // Status Method for internal UART 2.
	  Method(_STA,0,Serialized)
	  {
			Return(0x000F)
	  }
	  // Current Resource Setting Method for internal UART 2.
	  Method(_CRS,0,Serialized)
	  {
			// Create the Buffer that stores the Resources to
			// be returned.
			Name(BUF0,ResourceTemplate()
			{
				IO(Decode16,0x02F8,0x02F8,0x01,0x08)
				Interrupt (ResourceConsumer, Level, ActiveLow, Shared) {17}
			})
			Return(BUF0)
	  }

        Name (_PRS, ResourceTemplate ()  // _PRS: Possible Resource Settings
        {
            StartDependentFn (0x00, 0x00)
            {
                IO (Decode16,
                    0x02F8,             // Range Minimum
                    0x02F8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                IRQNoFlags ()
                    {3}
                DMA (Compatibility, NotBusMaster, Transfer8, )
                    {}
            }
            StartDependentFnNoPri ()
            {
                IO (Decode16,
                    0x03F8,             // Range Minimum
                    0x03F8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                IRQNoFlags ()
                    {3,4,5,7,9,10,11,12}
                DMA (Compatibility, NotBusMaster, Transfer8, )
                    {}
            }
            StartDependentFnNoPri ()
            {
                IO (Decode16,
                    0x02F8,             // Range Minimum
                    0x02F8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                IRQNoFlags ()
                    {3,4,5,7,9,10,11,12}
                DMA (Compatibility, NotBusMaster, Transfer8, )
                    {}
            }
            StartDependentFnNoPri ()
            {
                IO (Decode16,
                    0x03E8,             // Range Minimum
                    0x03E8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                IRQNoFlags ()
                    {3,4,5,7,9,10,11,12}
                DMA (Compatibility, NotBusMaster, Transfer8, )
                    {}
            }
            StartDependentFnNoPri ()
            {
                IO (Decode16,
                    0x02E8,             // Range Minimum
                    0x02E8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                IRQNoFlags ()
                    {3,4,5,7,9,10,11,12}
                DMA (Compatibility, NotBusMaster, Transfer8, )
                    {}
            }
            EndDependentFn ()
        })
	}

	Device(IUR5) // Internal UART 3
	{
	  Name(_HID, EISAID("PNP0501"))
	  Name(_UID,3)
	  // Status Method for internal UART 3.
	  Method(_STA,0,Serialized)
	  {
			Return(0x000F)
	  }
	  // Current Resource Setting Method for internal UART 3.
	  Method(_CRS,0,Serialized)
	  {
			// Create the Buffer that stores the Resources to
			// be returned.
			Name(BUF0,ResourceTemplate()
			{
				IO(Decode16,0x03E8,0x03E8,0x01,0x08)
				Interrupt (ResourceConsumer, Level, ActiveLow, Shared) {18}
			})
			Return(BUF0)
	  }
	}

   Device (LPC2)
   {
        Name (_HID, EisaId ("PNP0C08") /* ACPI Core Hardware */)  // _HID: Hardware ID
        Name (_UID, 0x02)  // _UID: Unique ID
        Name (LDN, 0x0D)
        Method (_STA, 0, NotSerialized)  // _STA: Status
        {
            Return (0x00)
        }
   }

		Device (SIO1)
		{
				Name (_HID, EisaId ("PNP0C02") /* PNP Motherboard Resources */)  // _HID: Hardware ID
				Name (_UID, 0x00)  // _UID: Unique ID
				Name (CRS, ResourceTemplate ()
				{
						IO (Decode16,
								0x002E,             // Range Minimum
								0x002E,             // Range Maximum
								0x00,               // Alignment
								0x02,               // Length
								_Y01)
						IO (Decode16,
								0x0A00,             // Range Minimum
								0x0A00,             // Range Maximum
								0x00,               // Alignment
								0x10,               // Length
								_Y02)
						IO (Decode16,
								0x0A10,             // Range Minimum
								0x0A10,             // Range Maximum
								0x00,               // Alignment
								0x10,               // Length
								_Y03)
						IO (Decode16,
								0x0A20,             // Range Minimum
								0x0A20,             // Range Maximum
								0x00,               // Alignment
								0x10,               // Length
								_Y04)
						IO (Decode16,
								0x0A30,             // Range Minimum
								0x0A30,             // Range Maximum
								0x00,               // Alignment
								0x10,               // Length
								_Y05)
						IO (Decode16,
								0x0A40,             // Range Minimum
								0x0A40,             // Range Maximum
								0x00,               // Alignment
								0x10,               // Length
								_Y06)
				})

			Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
			{
					Return (CRS) /* \_SB_.PC00.LPC0.SIO1.CRS_ */
			}
	}
	
	Device (SPMI)
	{
			Name (_HID, EisaId ("IPI0001"))  // _HID: Hardware ID
			Name (_STR, Unicode ("IPMI_KCS"))  // _STR: Description String
			Name (_UID, 0x00)  // _UID: Unique ID

			Method (_STA, 0, NotSerialized)  // _STA: Status
			{
				Return (0x0F)
			}

			Name (ICRS, ResourceTemplate ()
			{
					IO (Decode16,
							0x0CA2,             // Range Minimum
							0x0CA2,             // Range Maximum
							0x00,               // Alignment
							0x01,               // Length
							_Y11)
					IO (Decode16,
							0x0CA3,             // Range Minimum
							0x0CA3,             // Range Maximum
							0x00,               // Alignment
							0x01,               // Length
							_Y12)
			})
			Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
			{
				Return (ICRS) /* \_SB_.PC00.LPC0.SPMI.ICRS */
			}
	}

}

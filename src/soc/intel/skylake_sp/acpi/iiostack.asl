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

#include <intelblocks/itss.h>
#include <intelblocks/pcr.h>
#include <soc/iomap.h>
#include <soc/irq.h>
#include <soc/itss.h>
#include <soc/gpe.h>
#include <soc/pcr_ids.h>

Scope(\)
{
  // Private Chipset Register(PCR). Memory Mapped through ILB
  OperationRegion(PCRR, SystemMemory, P2SB_BAR, 0x01000000)
  Field(PCRR, DWordAcc, Lock, Preserve)
  {
    Offset (0xD03100),  // Interrupt Routing Registers
    PRTA, 8,
    PRTB, 8,
    PRTC, 8,
    PRTD, 8,
    PRTE, 8,
    PRTF, 8,
    PRTG, 8,
    PRTH, 8,
  }
}

Scope (_SB)
{
	#include "pirq_irqs.asl"

Name (P12E, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				LNKB, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				LNKC, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				LNKD, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				LNKA, 
				0x00
		}
})
Name (G12E, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				0x00, 
				0x11
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				0x00, 
				0x12
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				0x00, 
				0x13
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				0x00, 
				0x10
		}
})
Name (P14C, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				LNKA, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				LNKB, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				LNKC, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				LNKD, 
				0x00
		}
})
Name (G14C, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				0x00, 
				0x10
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				0x00, 
				0x11
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				0x00, 
				0x12
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				0x00, 
				0x13
		}
})
Name (P022, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				LNKA, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				LNKB, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				LNKC, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				LNKD, 
				0x00
		}
})
Name (G022, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				0x00, 
				0x10
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				0x00, 
				0x11
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				0x00, 
				0x12
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				0x00, 
				0x13
		}
})
Name (P026, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				LNKA, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				LNKB, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				LNKC, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				LNKD, 
				0x00
		}
})
Name (G026, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				0x00, 
				0x10
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				0x00, 
				0x11
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				0x00, 
				0x12
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				0x00, 
				0x13
		}
})
Name (P027, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				LNKB, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				LNKC, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				LNKD, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				LNKA, 
				0x00
		}
})
Name (G027, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				0x00, 
				0x11
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				0x00, 
				0x12
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				0x00, 
				0x13
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				0x00, 
				0x10
		}
})
Name (P02C, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				LNKC, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				LNKD, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				LNKA, 
				0x00
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				LNKB, 
				0x00
		}
})

Name (G02C, Package (0x04)
{
		Package (0x04)
		{
				0xFFFF, 
				0x00, 
				0x00, 
				0x12
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x01, 
				0x00, 
				0x13
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x02, 
				0x00, 
				0x10
		}, 

		Package (0x04)
		{
				0xFFFF, 
				0x03, 
				0x00, 
				0x11
		}
})

	Name (PR00, Package (0x28)
	{
			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0018FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (AR00, Package (0x28)
	{
			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0018FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					0x00, 
					0x16
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					0x00, 
					0x17
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x1F
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x00, 
					0x00, 
					0x1A
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x01, 
					0x00, 
					0x1B
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x02, 
					0x00, 
					0x1A
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x03, 
					0x00, 
					0x1B
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0x18
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0x1C
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0x1D
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0x1E
			}
	})
	Name (PR10, Package (0x40)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (AR10, Package (0x40)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x27
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0x27
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0x27
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0x27
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x03, 
					0x00, 
					0x26
			}
	})
	Name (P04A, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G04A, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x20
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x26
			}
	})
	Name (P04B, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G04B, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x21
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x24
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x25
			}
	})
	Name (P04C, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G04C, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x22
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x25
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x26
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x24
			}
	})
	Name (PR20, Package (0x24)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (AR20, Package (0x24)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x2F
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0x2F
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0x2F
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0x2F
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x03, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x03, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0x2E
			}
	})
	Name (P05E, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G05E, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x2E
			}
	})
	Name (PR28, Package (0x20)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (AR28, Package (0x20)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x37
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0x37
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0x37
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0x37
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					0x00, 
					0x30
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					0x00, 
					0x34
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					0x00, 
					0x35
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					0x00, 
					0x36
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					0x00, 
					0x30
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					0x00, 
					0x34
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					0x00, 
					0x35
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					0x00, 
					0x36
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					0x00, 
					0x30
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					0x00, 
					0x34
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					0x00, 
					0x35
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					0x00, 
					0x36
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x00, 
					0x00, 
					0x30
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x01, 
					0x00, 
					0x34
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x02, 
					0x00, 
					0x35
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x03, 
					0x00, 
					0x36
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					0x00, 
					0x30
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					0x00, 
					0x34
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					0x00, 
					0x35
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					0x00, 
					0x36
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0x30
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0x34
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0x35
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0x36
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0x30
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0x34
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0x35
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0x36
			}
	})
	Name (P06B, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G06B, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x30
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x34
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x35
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x36
			}
	})
	Name (PR30, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (AR30, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x3F
			}
	})
	Name (P077, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G077, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x38
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x3C
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x3D
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x3E
			}
	})
	Name (PR38, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (AR38, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x47
			}
	})
	Name (PR40, Package (0x09)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (AR40, Package (0x09)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x4F
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x00, 
					0x00, 
					0x4A
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x01, 
					0x00, 
					0x4B
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x02, 
					0x00, 
					0x4A
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x03, 
					0x00, 
					0x4B
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0x48
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0x4C
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0x4D
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0x4E
			}
	})
	Name (P07B, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G07B, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x48
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x4C
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x4D
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x4E
			}
	})
	Name (PR50, Package (0x40)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (AR50, Package (0x40)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x57
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0x57
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0x57
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0x57
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					0x00, 
					0x56
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x03, 
					0x00, 
					0x56
			}
	})
	Name (P086, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G086, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x50
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x54
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x55
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x56
			}
	})
	Name (PR60, Package (0x24)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (AR60, Package (0x24)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x5F
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0x5F
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0x5F
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0x5F
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0x58
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0x5C
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0x5D
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0x5E
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					0x00, 
					0x58
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					0x00, 
					0x5C
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					0x00, 
					0x5D
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					0x00, 
					0x5E
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					0x00, 
					0x58
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					0x00, 
					0x5C
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					0x00, 
					0x5D
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					0x00, 
					0x5E
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					0x00, 
					0x58
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					0x00, 
					0x5C
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					0x00, 
					0x5D
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					0x00, 
					0x5E
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x00, 
					0x00, 
					0x58
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x01, 
					0x00, 
					0x5C
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x02, 
					0x00, 
					0x5D
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x03, 
					0x00, 
					0x5E
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x00, 
					0x00, 
					0x58
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x01, 
					0x00, 
					0x5C
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x02, 
					0x00, 
					0x5D
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x03, 
					0x00, 
					0x5E
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0x58
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0x5C
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0x5D
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0x5E
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0x58
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0x5C
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0x5D
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0x5E
			}
	})
	Name (P09A, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G09A, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x58
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x5C
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x5D
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x5E
			}
	})
	Name (PR68, Package (0x20)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (AR68, Package (0x20)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x67
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0x67
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0x67
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0x67
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					0x00, 
					0x60
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					0x00, 
					0x64
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					0x00, 
					0x65
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					0x00, 
					0x66
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					0x00, 
					0x60
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					0x00, 
					0x64
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					0x00, 
					0x65
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					0x00, 
					0x66
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					0x00, 
					0x60
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					0x00, 
					0x64
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					0x00, 
					0x65
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					0x00, 
					0x66
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x00, 
					0x00, 
					0x60
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x01, 
					0x00, 
					0x64
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x02, 
					0x00, 
					0x65
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x03, 
					0x00, 
					0x66
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					0x00, 
					0x60
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					0x00, 
					0x64
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					0x00, 
					0x65
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					0x00, 
					0x66
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0x60
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0x64
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0x65
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0x66
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0x60
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0x64
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0x65
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0x66
			}
	})
	Name (P0A7, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G0A7, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x60
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x64
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x65
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x66
			}
	})
	Name (P0A9, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G0A9, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x62
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x65
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x66
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x64
			}
	})
	Name (PR70, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (AR70, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x6F
			}
	})
	Name (P0B3, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G0B3, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x68
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x6C
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x6D
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x6E
			}
	})
	Name (PR78, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (AR78, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x77
			}
	})
	Name (PR80, Package (0x09)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (AR80, Package (0x09)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x7F
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x00, 
					0x00, 
					0x7A
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x01, 
					0x00, 
					0x7B
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x02, 
					0x00, 
					0x7A
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x03, 
					0x00, 
					0x7B
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0x78
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0x7C
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0x7D
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0x7E
			}
	})
	Name (PR90, Package (0x38)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (AR90, Package (0x38)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x87
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0x87
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0x87
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0x87
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					0x00, 
					0x86
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					0x00, 
					0x80
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x01, 
					0x00, 
					0x84
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x02, 
					0x00, 
					0x85
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x03, 
					0x00, 
					0x86
			}
	})
	Name (PRA0, Package (0x24)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (ARA0, Package (0x24)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x8F
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0x8F
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0x8F
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0x8F
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0x88
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0x8C
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0x8D
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0x8E
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					0x00, 
					0x88
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					0x00, 
					0x8C
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					0x00, 
					0x8D
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					0x00, 
					0x8E
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					0x00, 
					0x88
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					0x00, 
					0x8C
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					0x00, 
					0x8D
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					0x00, 
					0x8E
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					0x00, 
					0x88
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					0x00, 
					0x8C
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					0x00, 
					0x8D
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					0x00, 
					0x8E
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x00, 
					0x00, 
					0x88
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x01, 
					0x00, 
					0x8C
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x02, 
					0x00, 
					0x8D
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x03, 
					0x00, 
					0x8E
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x00, 
					0x00, 
					0x88
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x01, 
					0x00, 
					0x8C
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x02, 
					0x00, 
					0x8D
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x03, 
					0x00, 
					0x8E
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0x88
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0x8C
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0x8D
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0x8E
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0x88
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0x8C
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0x8D
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0x8E
			}
	})
	Name (PRA8, Package (0x20)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (ARA8, Package (0x20)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x97
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0x97
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0x97
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0x97
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					0x00, 
					0x90
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					0x00, 
					0x94
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					0x00, 
					0x95
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					0x00, 
					0x96
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					0x00, 
					0x90
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					0x00, 
					0x94
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					0x00, 
					0x95
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					0x00, 
					0x96
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					0x00, 
					0x90
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					0x00, 
					0x94
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					0x00, 
					0x95
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					0x00, 
					0x96
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x00, 
					0x00, 
					0x90
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x01, 
					0x00, 
					0x94
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x02, 
					0x00, 
					0x95
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x03, 
					0x00, 
					0x96
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					0x00, 
					0x90
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					0x00, 
					0x94
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					0x00, 
					0x95
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					0x00, 
					0x96
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0x90
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0x94
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0x95
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0x96
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0x90
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0x94
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0x95
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0x96
			}
	})
	Name (PRB0, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (ARB0, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x9F
			}
	})
	Name (PRB8, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (ARB8, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0xA7
			}
	})
	Name (PRC0, Package (0x09)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (ARC0, Package (0x09)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0xAF
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x00, 
					0x00, 
					0xAA
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x01, 
					0x00, 
					0xAB
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x02, 
					0x00, 
					0xAA
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x03, 
					0x00, 
					0xAB
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0xA8
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0xAC
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0xAD
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0xAE
			}
	})
	Name (PRD0, Package (0x40)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (ARD0, Package (0x40)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0xB7
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0xB7
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0xB7
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0xB7
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					0x00, 
					0xB6
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					0x00, 
					0xB0
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x01, 
					0x00, 
					0xB4
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x02, 
					0x00, 
					0xB5
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x03, 
					0x00, 
					0xB6
			}
	})
	Name (PRE0, Package (0x24)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (ARE0, Package (0x24)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0xBF
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0xBF
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0xBF
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0xBF
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0xB8
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0xBC
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0xBD
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0xBE
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x00, 
					0x00, 
					0xB8
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x01, 
					0x00, 
					0xBC
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x02, 
					0x00, 
					0xBD
			}, 

			Package (0x04)
			{
					0x0009FFFF, 
					0x03, 
					0x00, 
					0xBE
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x00, 
					0x00, 
					0xB8
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x01, 
					0x00, 
					0xBC
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x02, 
					0x00, 
					0xBD
			}, 

			Package (0x04)
			{
					0x000AFFFF, 
					0x03, 
					0x00, 
					0xBE
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x00, 
					0x00, 
					0xB8
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x01, 
					0x00, 
					0xBC
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x02, 
					0x00, 
					0xBD
			}, 

			Package (0x04)
			{
					0x000BFFFF, 
					0x03, 
					0x00, 
					0xBE
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x00, 
					0x00, 
					0xB8
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x01, 
					0x00, 
					0xBC
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x02, 
					0x00, 
					0xBD
			}, 

			Package (0x04)
			{
					0x000CFFFF, 
					0x03, 
					0x00, 
					0xBE
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x00, 
					0x00, 
					0xB8
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x01, 
					0x00, 
					0xBC
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x02, 
					0x00, 
					0xBD
			}, 

			Package (0x04)
			{
					0x000DFFFF, 
					0x03, 
					0x00, 
					0xBE
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0xB8
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0xBC
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0xBD
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0xBE
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0xB8
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0xBC
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0xBD
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0xBE
			}
	})
	Name (PRE8, Package (0x20)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (ARE8, Package (0x20)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0xC7
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0xC7
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0xC7
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0xC7
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x00, 
					0x00, 
					0xC0
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x01, 
					0x00, 
					0xC4
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x02, 
					0x00, 
					0xC5
			}, 

			Package (0x04)
			{
					0x000EFFFF, 
					0x03, 
					0x00, 
					0xC6
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					0x00, 
					0xC0
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x01, 
					0x00, 
					0xC4
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x02, 
					0x00, 
					0xC5
			}, 

			Package (0x04)
			{
					0x000FFFFF, 
					0x03, 
					0x00, 
					0xC6
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					0x00, 
					0xC0
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					0x00, 
					0xC4
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					0x00, 
					0xC5
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					0x00, 
					0xC6
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x00, 
					0x00, 
					0xC0
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x01, 
					0x00, 
					0xC4
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x02, 
					0x00, 
					0xC5
			}, 

			Package (0x04)
			{
					0x0012FFFF, 
					0x03, 
					0x00, 
					0xC6
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x00, 
					0x00, 
					0xC0
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x01, 
					0x00, 
					0xC4
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x02, 
					0x00, 
					0xC5
			}, 

			Package (0x04)
			{
					0x0015FFFF, 
					0x03, 
					0x00, 
					0xC6
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0xC0
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0xC4
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0xC5
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0xC6
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0xC0
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x01, 
					0x00, 
					0xC4
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x02, 
					0x00, 
					0xC5
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x03, 
					0x00, 
					0xC6
			}
	})
	Name (PRF0, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (ARF0, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0xCF
			}
	})
	Name (PRF8, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (ARF8, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0xD7
			}
	})

	Name (P136, Package (0x10)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G136, Package (0x10)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x0001FFFF, 
					0x03, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x0002FFFF, 
					0x03, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x00, 
					0x00, 
					0x28
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x01, 
					0x00, 
					0x2C
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x02, 
					0x00, 
					0x2D
			}, 

			Package (0x04)
			{
					0x0003FFFF, 
					0x03, 
					0x00, 
					0x2E
			}
	})
	Name (P137, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (G137, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x28
			}
	})
	Name (P139, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (G139, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x29
			}
	})
	Name (P13B, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}
	})
	Name (G13B, Package (0x01)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x2D
			}
	})
	Name (P13D, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})
	Name (G13D, Package (0x04)
	{
			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x01, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x02, 
					0x00, 
					0x2E
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x03, 
					0x00, 
					0x2E
			}
	})
}

Device (PC00)
{
	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_ADR, 0x00)  // _ADR: Address
	Method (^BN00, 0, NotSerialized)
	{
			Return (0x00)
	}

	Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
	{
			Return (BN00 ())
	}

	Name (_UID, 0x00)  // _UID: Unique ID
	Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
	{
			If (PICM)
			{
					Return (AR00) /* \_SB_.AR00 */
			}

			Return (PR00) /* \_SB_.PR00 */
	}

	Name (SUPP, 0x00)
	Name (CTRL, 0x00)
	Name (_PXM, 0x00)  // _PXM: Device Proximity
  #include "pcie_osc.asl"

	Device (APIC)
	{
			Name (_HID, EisaId ("PNP0003") /* IO-APIC Interrupt Controller */)  // _HID: Hardware ID
			Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
			{
					Memory32Fixed (ReadOnly,
							0xFEC00000,         // Address Base
							0x00100000,         // Address Length
							)
			})
	}

	Name (P0RS, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x0000,             // Range Minimum
					0x0016,             // Range Maximum
					0x0000,             // Translation Offset
					0x0017,             // Length
					,, )
			IO (Decode16,
					0x0CF8,             // Range Minimum
					0x0CF8,             // Range Maximum
					0x01,               // Alignment
					0x08,               // Length
					)
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x0000,             // Range Minimum
					0x03AF,             // Range Maximum
					0x0000,             // Translation Offset
					0x03B0,             // Length
					,, , TypeStatic, DenseTranslation)
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x03E0,             // Range Minimum
					0x0CF7,             // Range Maximum
					0x0000,             // Translation Offset
					0x0918,             // Length
					,, , TypeStatic, DenseTranslation)
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x03B0,             // Range Minimum
					0x03BB,             // Range Maximum
					0x0000,             // Translation Offset
					0x000C,             // Length
					,, , TypeStatic, DenseTranslation)
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x03C0,             // Range Minimum
					0x03DF,             // Range Maximum
					0x0000,             // Translation Offset
					0x0020,             // Length
					,, , TypeStatic, DenseTranslation)
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x1000,             // Range Minimum
					0x3FFF,             // Range Maximum
					0x0000,             // Translation Offset
					0x3000,             // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000A0000,         // Range Minimum
					0x000BFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00020000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0xFE010000,         // Range Minimum
					0xFE010FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00001000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0x90000000,         // Range Minimum
					0x9D7FFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x0D800000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x0000380000000000, // Range Minimum
					0x000038003FFFFFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000040000000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})
	OperationRegion (TMEM, PCI_Config, 0x00, 0x0100)
	Field (TMEM, ByteAcc, NoLock, Preserve)
	{
			Offset (0x40), 
					,   4, 
			BSEG,   4, 
			PAMS,   48, 
			Offset (0x52), 
			DIM0,   4, 
			DIM1,   4, 
			Offset (0x54), 
			DIM2,   4
	}

	Name (MTBL, Package (0x10)
	{
			0x00, 
			0x20, 
			0x20, 
			0x30, 
			0x40, 
			0x40, 
			0x60, 
			0x80, 
			0x80, 
			0x80, 
			0x80, 
			0xC0, 
			0x0100, 
			0x0100, 
			0x0100, 
			0x0200
	})
	Name (ERNG, Package (0x0D)
	{
			0x000C0000, 
			0x000C4000, 
			0x000C8000, 
			0x000CC000, 
			0x000D0000, 
			0x000D4000, 
			0x000D8000, 
			0x000DC000, 
			0x000E0000, 
			0x000E4000, 
			0x000E8000, 
			0x000EC000, 
			0x000F0000
	})
	Name (PAMB, Buffer (0x07){})

	Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
	{
			Return (P0RS) /* \_SB_.PC00.P0RS */
	}

	Name (BUF0, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x0000,             // Range Minimum
					0x00FF,             // Range Maximum
					0x0000,             // Translation Offset
					0x0100,             // Length
					,, )
			DWordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x00000000,         // Granularity
					0x00000000,         // Range Minimum
					0x00000CF7,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00000CF8,         // Length
					,, , TypeStatic, DenseTranslation)
			IO (Decode16,
					0x0CF8,             // Range Minimum
					0x0CF8,             // Range Maximum
					0x01,               // Alignment
					0x08,               // Length
					)
			DWordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x00000000,         // Granularity
					0x00000D00,         // Range Minimum
					0x0000FFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x0000F300,         // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000A0000,         // Range Minimum
					0x000BFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00020000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000C0000,         // Range Minimum
					0x000C3FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000C4000,         // Range Minimum
					0x000C7FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000C8000,         // Range Minimum
					0x000CBFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000CC000,         // Range Minimum
					0x000CFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000D0000,         // Range Minimum
					0x000D3FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000D4000,         // Range Minimum
					0x000D7FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000D8000,         // Range Minimum
					0x000DBFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000DC000,         // Range Minimum
					0x000DFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000E0000,         // Range Minimum
					0x000E3FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000E4000,         // Range Minimum
					0x000E7FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000E8000,         // Range Minimum
					0x000EBFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000EC000,         // Range Minimum
					0x000EFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000F0000,         // Range Minimum
					0x000FFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00010000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x00000000,         // Range Minimum
					0xFEAFFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0xFEB00000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x0000000000010000, // Range Minimum
					0x000000000001FFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000000010000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})

	#include <soc/intel/skylake_sp/acpi/Pch.asl>
}

Device (PC01)
{
	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_ADR, 0x00)  // _ADR: Address
	Method (^BN10, 0, NotSerialized)
	{
			Return (0x17)
	}

	Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
	{
			Return (BN10 ())
	}

	Name (_UID, 0x01)  // _UID: Unique ID
	Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
	{
			If (PICM)
			{
					Return (AR10) /* \_SB_.AR10 */
			}

			Return (PR10) /* \_SB_.PR10 */
	}

	Name (SUPP, 0x00)
	Name (CTRL, 0x00)
	Name (_PXM, 0x00)  // _PXM: Device Proximity
  #include "pcie_osc.asl"

	Name (PR01, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x0017,             // Range Minimum
					0x0039,             // Range Maximum
					0x0000,             // Translation Offset
					0x0023,             // Length
					,, )
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x4000,             // Range Minimum
					0x5FFF,             // Range Maximum
					0x0000,             // Translation Offset
					0x2000,             // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0x9D800000,         // Range Minimum
					0xAAFFFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x0D800000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x0000380040000000, // Range Minimum
					0x000038007FFFFFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000040000000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})
	Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
	{
			Return (PR01) /* \_SB_.PC01.PR01 */
	}
}

Device (PC02)
{
	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_ADR, 0x00)  // _ADR: Address
	Method (^BN20, 0, NotSerialized)
	{
			Return (0x3a)
	}

	Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
	{
			Return (BN20 ())
	}

	Name (_UID, 0x02)  // _UID: Unique ID
	Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
	{
			If (PICM)
			{
					Return (AR20) /* \_SB_.AR20 */
			}

			Return (PR20) /* \_SB_.PR20 */
	}

	Name (SUPP, 0x00)
	Name (CTRL, 0x00)
	Name (_PXM, 0x00)  // _PXM: Device Proximity
  #include "pcie_osc.asl"

	Name (PR02, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x003A,             // Range Minimum
					0x005C,             // Range Maximum
					0x0000,             // Translation Offset
					0x0023,             // Length
					,, )
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x6000,             // Range Minimum
					0x7FFF,             // Range Maximum
					0x0000,             // Translation Offset
					0x2000,             // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0xAB000000,         // Range Minimum
					0xB87FFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x0D800000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x0000380080000000, // Range Minimum
					0x00003800BFFFFFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000040000000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})
	Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
	{
			Return (PR02) /* \_SB_.PC02.PR02 */
	}
}

Device (PC03)
{
	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_ADR, 0x00)  // _ADR: Address
	Method (^BN28, 0, NotSerialized)
	{
			Return (0x5d)
	}

	Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
	{
			Return (BN28 ())
	}

	Name (_UID, 0x03)  // _UID: Unique ID
	Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
	{
			If (PICM)
			{
					Return (AR28) /* \_SB_.AR28 */
			}

			Return (PR28) /* \_SB_.PR28 */
	}
  #include "pcie_osc.asl"

	Name (SUPP, 0x00)
	Name (CTRL, 0x00)

	Name (PR03, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x005D,             // Range Minimum
					0x007F,             // Range Maximum
					0x0000,             // Translation Offset
					0x0023,             // Length
					,, )
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x8000,             // Range Minimum
					0x9FFF,             // Range Maximum
					0x0000,             // Translation Offset
					0x2000,             // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0xB8800000,         // Range Minimum
					0xC5FFFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x0D800000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x00003800C0000000, // Range Minimum
					0x00003800FFFFFFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000040000000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})
	Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
	{
			Return (PR03) /* \_SB_.PC03.PR03 */
	}
}

Device (PC06)
{
	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_ADR, 0x00)  // _ADR: Address
	Method (^BN40, 0, NotSerialized)
	{
			Return (0x80)
	}

	Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
	{
			Return (BN40 ())
	}

	Name (_UID, 0x06)  // _UID: Unique ID
	Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
	{
			If (PICM)
			{
					Return (AR40) /* \_SB_.AR40 */
			}

			Return (PR40) /* \_SB_.PR40 */
	}

	Name (SUPP, 0x00)
	Name (CTRL, 0x00)
  #include "pcie_osc.asl"

	Name (PR06, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x0080,             // Range Minimum
					0x0084,             // Range Maximum
					0x0000,             // Translation Offset
					0x0005,             // Length
					,, )
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0xA000,             // Range Minimum
					0xBFFF,             // Range Maximum
					0x0000,             // Translation Offset
					0x2000,             // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0xC6000000,         // Range Minimum
					0xD37FFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x0D800000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x0000380100000000, // Range Minimum
					0x000038013FFFFFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000040000000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})
	Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
	{
			Return (PR06) /* \_SB_.PC06.PR06 */
	}
}

Device (PC07)
{
	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_ADR, 0x00)  // _ADR: Address
	Method (^BN50, 0, NotSerialized)
	{
			Return (0x85)
	}

	Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
	{
			Return (BN50 ())
	}

	Name (_UID, 0x07)  // _UID: Unique ID
	Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
	{
			If (PICM)
			{
					Return (AR50) /* \_SB_.AR50 */
			}

			Return (PR50) /* \_SB_.PR50 */
	}

	Name (SUPP, 0x00)
	Name (CTRL, 0x00)
  #include "pcie_osc.asl"

	Name (PR07, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x0085,             // Range Minimum
					0x00AD,             // Range Maximum
					0x0000,             // Translation Offset
					0x0029,             // Length
					,, )
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0xC000,             // Range Minimum
					0xDFFF,             // Range Maximum
					0x0000,             // Translation Offset
					0x2000,             // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0xD3800000,         // Range Minimum
					0xE0FFFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x0D800000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x0000380140000000, // Range Minimum
					0x000038017FFFFFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000040000000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})
	Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
	{
			Return (PR07) /* \_SB_.PC07.PR07 */
	}
}

Device (PC08)
{
	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_ADR, 0x00)  // _ADR: Address
	Method (^BN60, 0, NotSerialized)
	{
			Return (0xae)
	}

	Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
	{
			Return (BN60 ())
	}

	Name (_UID, 0x08)  // _UID: Unique ID
	Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
	{
			If (PICM)
			{
					Return (AR60) /* \_SB_.AR60 */
			}

			Return (PR60) /* \_SB_.PR60 */
	}

	Name (SUPP, 0x00)
	Name (CTRL, 0x00)
  #include "pcie_osc.asl"

	Name (PR08, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x00AE,             // Range Minimum
					0x00D6,             // Range Maximum
					0x0000,             // Translation Offset
					0x0029,             // Length
					,, )
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0xE000,             // Range Minimum
					0xEFFF,             // Range Maximum
					0x0000,             // Translation Offset
					0x1000,             // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0xE1000000,         // Range Minimum
					0xEE7FFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x0D800000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x0000380180000000, // Range Minimum
					0x00003801BFFFFFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000040000000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})
	Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
	{
			Return (PR08) /* \_SB_.PC08.PR08 */
	}
}

Device (PC09)
{
	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_ADR, 0x00)  // _ADR: Address
	Method (^BN68, 0, NotSerialized)
	{
			Return (0xd7)
	}

	Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
	{
			Return (BN68 ())
	}

	Name (_UID, 0x09)  // _UID: Unique ID
	Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
	{
			If (PICM)
			{
					Return (AR68) /* \_SB_.AR68 */
			}

			Return (PR68) /* \_SB_.PR68 */
	}

	Name (SUPP, 0x00)
	Name (CTRL, 0x00)
  #include "pcie_osc.asl"

	Name (PR09, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x00D7,             // Range Minimum
					0x00FF,             // Range Maximum
					0x0000,             // Translation Offset
					0x0029,             // Length
					,, )
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0xF000,             // Range Minimum
					0xFFFF,             // Range Maximum
					0x0000,             // Translation Offset
					0x1000,             // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0xEE800000,         // Range Minimum
					0xFBFFFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x0D800000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x00003801C0000000, // Range Minimum
					0x00003801FFFFFFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000040000000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})
	Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
	{
			Return (PR09) /* \_SB_.PC09.PR09 */
	}
}

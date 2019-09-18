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

// 00:11.5 SATA controller: Intel Corporation Lewisburg SSATA Controller [AHCI mode]
Device (SAT2)
{
		Name (_ADR, 0x00110005)  // _ADR: Address
}


Scope (SAT2)
{
		Device (PRT0)
		{
				Name (_ADR, 0xFFFF)  // _ADR: Address
		}

		Device (PRT1)
		{
				Name (_ADR, 0x0001FFFF)  // _ADR: Address
		}

		Device (PRT2)
		{
				Name (_ADR, 0x0002FFFF)  // _ADR: Address
		}

		Device (PRT3)
		{
				Name (_ADR, 0x0003FFFF)  // _ADR: Address
		}

		Device (PRT4)
		{
				Name (_ADR, 0x0004FFFF)  // _ADR: Address
		}

		Device (PRT5)
		{
				Name (_ADR, 0x0005FFFF)  // _ADR: Address
		}

		Device (NVM1)
		{
				Name (_ADR, 0x00C1FFFF)  // _ADR: Address
				Name (PRBI, 0x00)
				Name (PRBD, 0x00)
				Name (PCMD, 0x00)
				Name (NCRN, 0x00)
				Name (NITV, 0x00)
				Name (NPMV, 0x00)
				Name (NPCV, 0x00)
				Name (NL1V, 0x00)
				Name (ND2V, 0x00)
				Name (ND1V, 0x00)
				Name (NLRV, 0x00)
				Name (NLDV, 0x00)
				Name (NEAV, 0x00)
				Name (NEBV, 0x00)
				Name (NECV, 0x00)
				Name (NRAV, 0x00)
				Name (NMBV, 0x00)
				Name (NMVV, 0x00)
				Name (NPBV, 0x00)
				Name (NPVV, 0x00)
		}

		Device (NVM2)
		{
				Name (_ADR, 0x00C2FFFF)  // _ADR: Address
				Name (PRBI, 0x00)
				Name (PRBD, 0x00)
				Name (PCMD, 0x00)
				Name (NCRN, 0x00)
				Name (NITV, 0x00)
				Name (NPMV, 0x00)
				Name (NPCV, 0x00)
				Name (NL1V, 0x00)
				Name (ND2V, 0x00)
				Name (ND1V, 0x00)
				Name (NLRV, 0x00)
				Name (NLDV, 0x00)
				Name (NEAV, 0x00)
				Name (NEBV, 0x00)
				Name (NECV, 0x00)
				Name (NRAV, 0x00)
				Name (NMBV, 0x00)
				Name (NMVV, 0x00)
				Name (NPBV, 0x00)
				Name (NPVV, 0x00)
		}

		Device (NVM3)
		{
				Name (_ADR, 0x00C3FFFF)  // _ADR: Address
				Name (PRBI, 0x00)
				Name (PRBD, 0x00)
				Name (PCMD, 0x00)
				Name (NCRN, 0x00)
				Name (NITV, 0x00)
				Name (NPMV, 0x00)
				Name (NPCV, 0x00)
				Name (NL1V, 0x00)
				Name (ND2V, 0x00)
				Name (ND1V, 0x00)
				Name (NLRV, 0x00)
				Name (NLDV, 0x00)
				Name (NEAV, 0x00)
				Name (NEBV, 0x00)
				Name (NECV, 0x00)
				Name (NRAV, 0x00)
				Name (NMBV, 0x00)
				Name (NMVV, 0x00)
				Name (NPBV, 0x00)
				Name (NPVV, 0x00)
		}
}

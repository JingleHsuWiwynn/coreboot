/*
 * This file is part of the coreboot project.
 *
 * Copyright 2015 Google Inc.
 * Copyright (C) 2015-2017 Intel Corporation.
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

#ifndef _SKYLAKESP_GPIO_DEFS_H_
#define _SKYLAKESP_GPIO_DEFS_H_

#include <soc/pcr.h>

/*
* There are 3 GPIO groups. North Community, South Community DFX/Group0/Group1.
* The GPIO groups are accessed through register blocks called communities.
*/

#define V_PCH_GPIO_NC_PAD_MAX 41
#define V_PCH_GPIO_SC_DFX_PAD_MAX 18
#define V_PCH_GPIO_SC0_PAD_MAX 53
#define V_PCH_GPIO_SC1_PAD_MAX 42
#define V_PCH_GPIO_GROUP_MAX 4

//
// GPIO Community 0 Private Configuration Registers
//

//
// Power Group NORTH_ALL
//
#define R_PCH_PCR_GPIO_NC_PAD_OWN 0x20
#define R_PCH_PCR_GPIO_NC_GPI_VWM_EN 0x70
#define R_PCH_PCR_GPIO_NC_PADCFGLOCK 0x90
#define R_PCH_PCR_GPIO_NC_PADCFGLOCKTX 0x94
#define R_PCH_PCR_GPIO_NC1_PADCFGLOCK_1 0x98
#define R_PCH_PCR_GPIO_NC1_PADCFGLOCKTX_1 0x9C
#define R_PCH_PCR_GPIO_NC_HOSTSW_OWN 0xC0
#define R_PCH_PCR_GPIO_NC_GPI_IS 0x0100
#define R_PCH_PCR_GPIO_NC_GPI_IE 0x0120
#define R_PCH_PCR_GPIO_NC_GPI_GPE_STS 0x0140
#define R_PCH_PCR_GPIO_NC_GPI_GPE_EN 0x0160
#define R_PCH_PCR_GPIO_NC_SMI_STS 0x0180
#define R_PCH_PCR_GPIO_NC_SMI_EN 0x01A0
#define R_PCH_PCR_GPIO_NC_NMI_STS 0x01C0
#define R_PCH_PCR_GPIO_NC_NMI_EN 0x01E0
#define R_PCH_PCR_GPIO_NC_PADCFG_OFFSET 0x400

//
// GPIO Community 1 Private Configuration Registers
//

//
// Power Group SOUTH_DFX
//
#define R_PCH_PCR_GPIO_SC_DFX_PAD_OWN 0x20
#define R_PCH_PCR_GPIO_SC_DFX_GPI_VWM_EN 0x70
#define R_PCH_PCR_GPIO_SC_DFX_PADCFGLOCK 0x90
#define R_PCH_PCR_GPIO_SC_DFX_PADCFGLOCKTX 0x94
#define R_PCH_PCR_GPIO_SC_DFX_HOSTSW_OWN 0xC0
#define R_PCH_PCR_GPIO_SC_DFX_GPI_IS 0x0100
#define R_PCH_PCR_GPIO_SC_DFX_GPI_IE 0x0120
#define R_PCH_PCR_GPIO_SC_DFX_GPI_GPE_STS 0x0140
#define R_PCH_PCR_GPIO_SC_DFX_GPI_GPE_EN 0x0160
#define R_PCH_PCR_GPIO_SC_DFX_PADCFG_OFFSET 0x400
//
// Power Group SOUTH_GROUP0
//
#define R_PCH_PCR_GPIO_SC0_PAD_OWN 0x2C
#define R_PCH_PCR_GPIO_SC0_GPI_VWM_EN 0x74
#define R_PCH_PCR_GPIO_SC0_PADCFGLOCK 0x98
#define R_PCH_PCR_GPIO_SC0_PADCFGLOCKTX 0x9C
#define R_PCH_PCR_GPIO_SC0_HOSTSW_OWN 0xC4
#define R_PCH_PCR_GPIO_SC0_GPI_IS 0x0104
#define R_PCH_PCR_GPIO_SC0_GPI_IE 0x0124
#define R_PCH_PCR_GPIO_SC0_GPI_GPE_STS 0x0144
#define R_PCH_PCR_GPIO_SC0_GPI_GPE_EN 0x0164
#define R_PCH_PCR_GPIO_SC0_SMI_STS 0x0184
#define R_PCH_PCR_GPIO_SC0_SMI_EN 0x01A4
#define R_PCH_PCR_GPIO_SC0_NMI_STS 0x01C4
#define R_PCH_PCR_GPIO_SC0_NMI_EN 0x01E4
#define R_PCH_PCR_GPIO_SC0_PADCFG_OFFSET 0x490
//
// Power Group SOUTH_GROUP1
//
#define R_PCH_PCR_GPIO_SC1_PAD_OWN 0x48
#define R_PCH_PCR_GPIO_SC1_GPI_VWM_EN 0x7C
#define R_PCH_PCR_GPIO_SC1_PADCFGLOCK 0xA8
#define R_PCH_PCR_GPIO_SC1_PADCFGLOCKTX 0xAC
#define R_PCH_PCR_GPIO_SC1_HOSTSW_OWN 0xCC
#define R_PCH_PCR_GPIO_SC1_GPI_IS 0x010C
#define R_PCH_PCR_GPIO_SC1_GPI_IE 0x012C
#define R_PCH_PCR_GPIO_SC1_GPI_GPE_STS 0x014C
#define R_PCH_PCR_GPIO_SC1_GPI_GPE_EN 0x016C
#define R_PCH_PCR_GPIO_SC1_SMI_STS 0x018C
#define R_PCH_PCR_GPIO_SC1_SMI_EN 0x01AC
#define R_PCH_PCR_GPIO_SC1_NMI_STS 0x01CC
#define R_PCH_PCR_GPIO_SC1_NMI_EN 0x01EC
#define R_PCH_PCR_GPIO_SC1_PADCFG_OFFSET 0x638

#define R_PCH_PCR_GPIO_GPP_PADCFGLOCK_NORTH_ALL_0 0x90
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCKTX_NORTH_ALL_0 0x94
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCK_NORTH_ALL_1 0x98
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCKTX_NORTH_ALL_1 0x9C

#define R_PCH_PCR_GPIO_GPP_PADCFGLOCK_SOUTH_DFX_0 0x90
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCKTX_SOUTH_DFX_0 0x94
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCK_SOUTH_GROUP0_0 0x98
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCKTX_SOUTH_GROUP0_0 0x9C
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCK_SOUTH_GROUP0_1 0xA0
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCKTX_SOUTH_GROUP0_1 0xA4
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCK_SOUTH_GROUP1_0 0xA8
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCKTX_SOUTH_GROUP1_0 0xAC
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCK_SOUTH_GROUP1_1 0xB0
#define R_PCH_PCR_GPIO_GPP_PADCFGLOCKTX_SOUTH_GROUP1_1 0xB4

//
// Pad Configuration Register DW0
//

// Pad Reset Config
#define B_PCH_GPIO_RST_CONF ((1 << 31) | (1 << 30))
#define N_PCH_GPIO_RST_CONF 30
#define V_PCH_GPIO_RST_CONF_POW_GOOD 0x00
#define V_PCH_GPIO_RST_CONF_DEEP_RST 0x01
#define V_PCH_GPIO_RST_CONF_GPIO_RST 0x02
#define V_PCH_GPIO_RST_CONF_RESUME_RST 0x03 // Only for GPD Group

// RX Pad State Select
#define B_PCH_GPIO_RX_PAD_STATE (1 << 29)
#define N_PCH_GPIO_RX_PAD_STATE 29
#define V_PCH_GPIO_RX_PAD_STATE_RAW 0x00
#define V_PCH_GPIO_RX_PAD_STATE_INT 0x01

// RX Raw Override to 1
#define B_PCH_GPIO_RX_RAW1 (1 << 28)
#define N_PCH_GPIO_RX_RAW1 28
#define V_PCH_GPIO_RX_RAW1_DIS 0x00
#define V_PCH_GPIO_RX_RAW1_EN 0x01

// RX Level/Edge Configuration
#define B_PCH_GPIO_RX_LVL_EDG ((1 << 26) | (1 << 25))
#define N_PCH_GPIO_RX_LVL_EDG 25
#define V_PCH_GPIO_RX_LVL_EDG_LVL 0x00
#define V_PCH_GPIO_RX_LVL_EDG_EDG 0x01
#define V_PCH_GPIO_RX_LVL_EDG_0 0x02
#define V_PCH_GPIO_RX_LVL_EDG_RIS_FAL 0x03

// RX Level/Edge Configuration
#define B_PCH_GPIO_PRE_GFRX_SEL (1 << 24)
#define N_PCH_GPIO_PRE_GFRX_SEL 24
#define V_PCH_GPIO_PRE_GFRX_SEL_DIS 0x00
#define V_PCH_GPIO_PRE_GFRX_SEL_EN 0x01

// RX Invert
#define B_PCH_GPIO_RXINV (1 << 23)
#define N_PCH_GPIO_RXINV 23
#define V_PCH_GPIO_RXINV_NO 0x00
#define V_PCH_GPIO_RXINV_YES 0x01

// RXTXENCFG
#define B_PCH_GPIO_RXTXENCFG ((1 << 22) | (1 << 21))
#define N_PCH_GPIO_RXTXENCFG 21
#define V_PCH_GPIO_RXTXENCFG_DEF_FUN 0x00
#define V_PCH_GPIO_RXTXENCFG_TX_EN_L 0x01
#define V_PCH_GPIO_RXTXENCFG_TX_EN_H 0x02
#define V_PCH_GPIO_RXTXENCFG_TXRXEN 0x03

// GPIO Input Route IOxAPIC
#define B_PCH_GPIO_RX_APIC_ROUTE (1 << 20)
#define N_PCH_GPIO_RX_APIC_ROUTE 20
#define V_PCH_GPIO_RX_APIC_ROUTE_DIS 0x00
#define V_PCH_GPIO_RX_APIC_ROUTE_EN 0x01

// GPIO Input Route SCI
#define B_PCH_GPIO_RX_SCI_ROUTE (1 << 10)
#define N_PCH_GPIO_RX_SCI_ROUTE 19
#define V_PCH_GPIO_RX_SCI_ROUTE_DIS 0x00
#define V_PCH_GPIO_RX_SCI_ROUTE_EN 0x01

// GPIO Input Route SMI
#define B_PCH_GPIO_RX_SMI_ROUTE (1 << 18)
#define N_PCH_GPIO_RX_SMI_ROUTE 18
#define V_PCH_GPIO_RX_SMI_ROUTE_DIS 0x00
#define V_PCH_GPIO_RX_SMI_ROUTE_EN 0x01

// GPIO Input Route NMI
#define B_PCH_GPIO_RX_NMI_ROUTE (1 << 17)
#define N_PCH_GPIO_RX_NMI_ROUTE 17
#define V_PCH_GPIO_RX_NMI_ROUTE_DIS 0x00
#define V_PCH_GPIO_RX_NMI_ROUTE_EN 0x01

// GPIO Pad Mode
#define B_PCH_GPIO_PAD_MODE ((1 << 12) | (1 << 11) | (1 << 10))
#define N_PCH_GPIO_PAD_MODE 10
#define V_PCH_GPIO_PAD_MODE_GPIO 0
#define V_PCH_GPIO_PAD_MODE_NAT_1 1
#define V_PCH_GPIO_PAD_MODE_NAT_2 2
#define V_PCH_GPIO_PAD_MODE_NAT_3 3
#define V_PCH_GPIO_PAD_MODE_NAT_4 4
#define V_PCH_GPIO_PAD_MODE_NAT_5 5
#define V_PCH_GPIO_PAD_MODE_NAT_6 6
#define V_PCH_GPIO_PAD_MODE_NAT_7 7

// GPIO RX Disable
#define B_PCH_GPIO_RXDIS (1 << 9)
#define N_PCH_GPIO_RXDIS 9
#define V_PCH_GPIO_RXDIS_EN 0x00
#define V_PCH_GPIO_RXDIS_DIS 0x01

// GPIO TX Disable
#define B_PCH_GPIO_TXDIS (1 << 8)
#define N_PCH_GPIO_TXDIS 8
#define V_PCH_GPIO_TXDIS_EN 0x00
#define V_PCH_GPIO_TXDIS_DIS 0x01

// GPIO RX State
#define B_PCH_GPIO_RX_STATE (1 << 1)
#define N_PCH_GPIO_RX_STATE 1
#define V_PCH_GPIO_RX_STATE_LOW 0x00
#define V_PCH_GPIO_RX_STATE_HIGH 0x01

// GPIO TX State
#define B_PCH_GPIO_TX_STATE (1 << 0)
#define N_PCH_GPIO_TX_STATE 0
#define V_PCH_GPIO_TX_STATE_LOW 0x00
#define V_PCH_GPIO_TX_STATE_HIGH 0x01

//
// Pad Configuration Register DW1
//

// Padtol
#define B_PCH_GPIO_PADTOL (1 << 25)
#define N_PCH_GPIO_PADTOL 25
#define V_PCH_GPIO_PADTOL_NONE 0x00
#define V_PCH_GPIO_PADTOL_CLEAR 0x00
#define V_PCH_GPIO_PADTOL_SET 0x01

// Termination
#define B_PCH_GPIO_TERM ((1 << 13) | (1 << 12) | (1 << 11) | (1 << 10))
#define N_PCH_GPIO_TERM 10
#define V_PCH_GPIO_TERM_WPD_NONE 0x00
#define V_PCH_GPIO_TERM_WPD_5K 0x02
#define V_PCH_GPIO_TERM_WPD_20K 0x04
#define V_PCH_GPIO_TERM_WPU_NONE 0x08
#define V_PCH_GPIO_TERM_WPU_1K 0x09
#define V_PCH_GPIO_TERM_WPU_2K 0x0B
#define V_PCH_GPIO_TERM_WPU_5K 0x0A
#define V_PCH_GPIO_TERM_WPU_20K 0x0C
#define V_PCH_GPIO_TERM_WPU_1K_2K 0x0D
#define V_PCH_GPIO_TERM_NATIVE 0x0F

#define PID_NorthCommunity PID_GPIOCOM0
#define PID_SouthCommunity PID_GPIOCOM1

// GPIO_MISC0
// HSUART0: 101, 102, 13, 98
// HSUART1: 96, 97,95 94

#define GPIO_SMB3_CLTT_DATA 12
#define R_PAD_CFG_DW0_SMB3_CLTT_DATA 0x490
#define PID_SMB3_CLTT_DATA PID_SouthCommunity

#define GPIO_SMB3_CLTT_CLK 13
#define R_PAD_CFG_DW0_SMB3_CLTT_CLK 0x498
#define PID_SMB3_CLTT_CLK PID_SouthCommunity

#define GPIO_PCIE_CLKREQ5_N 98
#define R_PAD_CFG_DW0_PCIE_CLKREQ5_N 0x4A0
#define PID_PCIE_CLKREQ5_N PID_SouthCommunity

#define GPIO_PCIE_CLKREQ6_N 99
#define R_PAD_CFG_DW0_PCIE_CLKREQ6_N 0x4a8
#define PID_PCIE_CLKREQ6_N PID_SouthCommunity

#define GPIO_PCIE_CLKREQ7_N 100
#define R_PAD_CFG_DW0_PCIE_CLKREQ7_N 0x4b0
#define PID_PCIE_CLKREQ7_N PID_SouthCommunity

#define GPIO_UART0_RXD 101
#define R_PAD_CFG_DW0_UART0_RXD 0x4b8
#define PID_UART0_RXD PID_SouthCommunity

#define GPIO_UART0_TXD 102
#define R_PAD_CFG_DW0_UART0_TXD 0x4c0
#define PID_UART0_TXD PID_SouthCommunity

#define GPIO_UART1_RXD 96
#define R_PAD_CFG_DW0_UART1_RXD 0x5b8
#define PID_UART1_RXD PID_SouthCommunity

#define GPIO_UART1_TXD 97
#define R_PAD_CFG_DW0_UART1_TXD 0x5c0
#define PID_UART1_TXD PID_SouthCommunity

#define GPIO_SATA1_SDOUT 95
#define R_PAD_CFG_DW0_SATA1_SDOUT 0x5b0
#define PID_SATA1_SDOUT PID_SouthCommunity

#define GPIO_SATA0_SDOUT 94
#define R_PAD_CFG_DW0_SATA0_SDOUT 0x5a8
#define PID_SATA0_SDOUT PID_SouthCommunity

///
/// Denverton GPIO Groups
///

#define GPIO_DNV_GROUP_NC 0x0100
#define GPIO_DNV_GROUP_SC_DFX 0x0101
#define GPIO_DNV_GROUP_SC0 0x0102
#define GPIO_DNV_GROUP_SC1 0x0103
#define GPIO_DNV_GROUP_MIN GPIO_DNV_GROUP_NC
#define GPIO_DNV_GROUP_MAX GPIO_DNV_GROUP_SC1
#define NORTH_ALL_GBE0_SDP0 0x01000000
#define NORTH_ALL_GBE1_SDP0 0x01000001
#define NORTH_ALL_GBE0_SDP1 0x01000002
#define NORTH_ALL_GBE1_SDP1 0x01000003
#define NORTH_ALL_GBE0_SDP2 0x01000004
#define NORTH_ALL_GBE1_SDP2 0x01000005
#define NORTH_ALL_GBE0_SDP3 0x01000006
#define NORTH_ALL_GBE1_SDP3 0x01000007
#define NORTH_ALL_GBE2_LED0 0x01000008
#define NORTH_ALL_GBE2_LED1 0x01000009
#define NORTH_ALL_GBE0_I2C_CLK 0x0100000A
#define NORTH_ALL_GBE0_I2C_DATA 0x0100000B
#define NORTH_ALL_GBE1_I2C_CLK 0x0100000C
#define NORTH_ALL_GBE1_I2C_DATA 0x0100000D
#define NORTH_ALL_NCSI_RXD0 0x0100000E
#define NORTH_ALL_NCSI_CLK_IN 0x0100000F
#define NORTH_ALL_NCSI_RXD1 0x01000010
#define NORTH_ALL_NCSI_CRS_DV 0x01000011
#define NORTH_ALL_NCSI_ARB_IN 0x01000012
#define NORTH_ALL_NCSI_TX_EN 0x01000013
#define NORTH_ALL_NCSI_TXD0 0x01000014
#define NORTH_ALL_NCSI_TXD1 0x01000015
#define NORTH_ALL_NCSI_ARB_OUT 0x01000016
#define NORTH_ALL_GBE0_LED0 0x01000017
#define NORTH_ALL_GBE0_LED1 0x01000018
#define NORTH_ALL_GBE1_LED0 0x01000019
#define NORTH_ALL_GBE1_LED1 0x0100001A
#define NORTH_ALL_GPIO_0 0x0100001B
#define NORTH_ALL_PCIE_CLKREQ0_N 0x0100001C
#define NORTH_ALL_PCIE_CLKREQ1_N 0x0100001D
#define NORTH_ALL_PCIE_CLKREQ2_N 0x0100001E
#define NORTH_ALL_PCIE_CLKREQ3_N 0x0100001F
#define NORTH_ALL_PCIE_CLKREQ4_N 0x01000020
#define NORTH_ALL_GPIO_1 0x01000021
#define NORTH_ALL_GPIO_2 0x01000022
#define NORTH_ALL_SVID_ALERT_N 0x01000023
#define NORTH_ALL_SVID_DATA 0x01000024
#define NORTH_ALL_SVID_CLK 0x01000025
#define NORTH_ALL_THERMTRIP_N 0x01000026
#define NORTH_ALL_PROCHOT_N 0x01000027
#define NORTH_ALL_MEMHOT_N 0x01000028
#define SOUTH_DFX_DFX_PORT_CLK0 0x01010000
#define SOUTH_DFX_DFX_PORT_CLK1 0x01010001
#define SOUTH_DFX_DFX_PORT0 0x01010002
#define SOUTH_DFX_DFX_PORT1 0x01010003
#define SOUTH_DFX_DFX_PORT2 0x01010004
#define SOUTH_DFX_DFX_PORT3 0x01010005
#define SOUTH_DFX_DFX_PORT4 0x01010006
#define SOUTH_DFX_DFX_PORT5 0x01010007
#define SOUTH_DFX_DFX_PORT6 0x01010008
#define SOUTH_DFX_DFX_PORT7 0x01010009
#define SOUTH_DFX_DFX_PORT8 0x0101000A
#define SOUTH_DFX_DFX_PORT9 0x0101000B
#define SOUTH_DFX_DFX_PORT10 0x0101000C
#define SOUTH_DFX_DFX_PORT11 0x0101000D
#define SOUTH_DFX_DFX_PORT12 0x0101000E
#define SOUTH_DFX_DFX_PORT13 0x0101000F
#define SOUTH_DFX_DFX_PORT14 0x01010010
#define SOUTH_DFX_DFX_PORT15 0x01010011
#define SOUTH_GROUP0_SMB3_CLTT_DATA 0x01020000
#define SOUTH_GROUP0_SMB3_CLTT_CLK 0x01020001
#define SOUTH_GROUP0_GPIO_12 0x01020000
#define SOUTH_GROUP0_SMB5_GBE_ALRT_N 0x01020001
#define SOUTH_GROUP0_PCIE_CLKREQ5_N 0x01020002
#define SOUTH_GROUP0_PCIE_CLKREQ6_N 0x01020003
#define SOUTH_GROUP0_PCIE_CLKREQ7_N 0x01020004
#define SOUTH_GROUP0_UART0_RXD 0x01020005
#define SOUTH_GROUP0_UART0_TXD 0x01020006
#define SOUTH_GROUP0_SMB5_GBE_CLK 0x01020007
#define SOUTH_GROUP0_SMB5_GBE_DATA 0x01020008
#define SOUTH_GROUP0_ERROR2_N 0x01020009
#define SOUTH_GROUP0_ERROR1_N 0x0102000A
#define SOUTH_GROUP0_ERROR0_N 0x0102000B
#define SOUTH_GROUP0_IERR_N 0x0102000C
#define SOUTH_GROUP0_MCERR_N 0x0102000D
#define SOUTH_GROUP0_SMB0_LEG_CLK 0x0102000E
#define SOUTH_GROUP0_SMB0_LEG_DATA 0x0102000F
#define SOUTH_GROUP0_SMB0_LEG_ALRT_N 0x01020010
#define SOUTH_GROUP0_SMB1_HOST_DATA 0x01020011
#define SOUTH_GROUP0_SMB1_HOST_CLK 0x01020012
#define SOUTH_GROUP0_SMB2_PECI_DATA 0x01020013
#define SOUTH_GROUP0_SMB2_PECI_CLK 0x01020014
#define SOUTH_GROUP0_SMB4_CSME0_DATA 0x01020015
#define SOUTH_GROUP0_SMB4_CSME0_CLK 0x01020016
#define SOUTH_GROUP0_SMB4_CSME0_ALRT_N 0x01020017
#define SOUTH_GROUP0_USB_OC0_N 0x01020018
#define SOUTH_GROUP0_FLEX_CLK_SE0 0x01020019
#define SOUTH_GROUP0_FLEX_CLK_SE1 0x0102001A
#define SOUTH_GROUP0_GPIO_4 0x0102001B
#define SOUTH_GROUP0_GPIO_5 0x0102001C
#define SOUTH_GROUP0_GPIO_6 0x0102001D
#define SOUTH_GROUP0_GPIO_7 0x0102001E
#define SOUTH_GROUP0_SATA0_LED_N 0x0102001F
#define SOUTH_GROUP0_SATA1_LED_N 0x01020020
#define SOUTH_GROUP0_SATA_PDETECT0 0x01020021
#define SOUTH_GROUP0_SATA_PDETECT1 0x01020022
#define SOUTH_GROUP0_SATA0_SDOUT 0x01020023
#define SOUTH_GROUP0_SATA1_SDOUT 0x01020024
#define SOUTH_GROUP0_UART1_RXD 0x01020025
#define SOUTH_GROUP0_UART1_TXD 0x01020026
#define SOUTH_GROUP0_GPIO_8 0x01020027
#define SOUTH_GROUP0_GPIO_9 0x01020028
#define SOUTH_GROUP0_TCK 0x01020029
#define SOUTH_GROUP0_TRST_N 0x0102002A
#define SOUTH_GROUP0_TMS 0x0102002B
#define SOUTH_GROUP0_TDI 0x0102002C
#define SOUTH_GROUP0_TDO 0x0102002D
#define SOUTH_GROUP0_CX_PRDY_N 0x0102002E
#define SOUTH_GROUP0_CX_PREQ_N 0x0102002F
#define SOUTH_GROUP0_CTBTRIGINOUT 0x01020030
#define SOUTH_GROUP0_CTBTRIGOUT 0x01020031
#define SOUTH_GROUP0_DFX_SPARE2 0x01020032
#define SOUTH_GROUP0_DFX_SPARE3 0x01020033
#define SOUTH_GROUP0_DFX_SPARE4 0x01020034
#define SOUTH_GROUP1_SUSPWRDNACK 0x01030000
#define SOUTH_GROUP1_PMU_SUSCLK 0x01030001
#define SOUTH_GROUP1_ADR_TRIGGER 0x01030002
#define SOUTH_GROUP1_PMU_AC_PRESENT 0x01030002
#define SOUTH_GROUP1_PMU_SLP_S45_N 0x01030003
#define SOUTH_GROUP1_PMU_SLP_S3_N 0x01030004
#define SOUTH_GROUP1_PMU_WAKE_N 0x01030005
#define SOUTH_GROUP1_PMU_PWRBTN_N 0x01030006
#define SOUTH_GROUP1_PMU_RESETBUTTON_N 0x01030007
#define SOUTH_GROUP1_PMU_PLTRST_N 0x01030008
#define SOUTH_GROUP1_SUS_STAT_N 0x01030009
#define SOUTH_GROUP1_SLP_S0IX_N 0x0103000A
#define SOUTH_GROUP1_SPI_CS0_N 0x0103000B
#define SOUTH_GROUP1_SPI_CS1_N 0x0103000C
#define SOUTH_GROUP1_SPI_MOSI_IO0 0x0103000D
#define SOUTH_GROUP1_SPI_MISO_IO1 0x0103000E
#define SOUTH_GROUP1_SPI_IO2 0x0103000F
#define SOUTH_GROUP1_SPI_IO3 0x01030010
#define SOUTH_GROUP1_SPI_CLK 0x01030011
#define SOUTH_GROUP1_SPI_CLK_LOOPBK 0x01030012
#define SOUTH_GROUP1_ESPI_IO0 0x01030013
#define SOUTH_GROUP1_ESPI_IO1 0x01030014
#define SOUTH_GROUP1_ESPI_IO2 0x01030015
#define SOUTH_GROUP1_ESPI_IO3 0x01030016
#define SOUTH_GROUP1_ESPI_CS0_N 0x01030017
#define SOUTH_GROUP1_ESPI_CLK 0x01030018
#define SOUTH_GROUP1_ESPI_RST_N 0x01030019
#define SOUTH_GROUP1_ESPI_ALRT0_N 0x0103001A
#define SOUTH_GROUP1_GPIO_10 0x0103001B
#define SOUTH_GROUP1_GPIO_11 0x0103001C
#define SOUTH_GROUP1_ESPI_CLK_LOOPBK 0x0103001D
#define SOUTH_GROUP1_EMMC_CMD 0x0103001E
#define SOUTH_GROUP1_EMMC_STROBE 0x0103001F
#define SOUTH_GROUP1_EMMC_CLK 0x01030020
#define SOUTH_GROUP1_EMMC_D0 0x01030021
#define SOUTH_GROUP1_EMMC_D1 0x01030022
#define SOUTH_GROUP1_EMMC_D2 0x01030023
#define SOUTH_GROUP1_EMMC_D3 0x01030024
#define SOUTH_GROUP1_EMMC_D4 0x01030025
#define SOUTH_GROUP1_EMMC_D5 0x01030026
#define SOUTH_GROUP1_EMMC_D6 0x01030027
#define SOUTH_GROUP1_EMMC_D7 0x01030028
#define SOUTH_GROUP1_GPIO_3 0x01030029

// BIT15-0  - pad number
// BIT31-16 - group info
//   BIT23- 16 - group index
//   BIT31- 24 - chipset ID (default to 0x01)
#define PAD_INFO_MASK 0x0000FFFF
#define GROUP_INFO_POSITION 16
#define GROUP_INFO_MASK 0xFFFF0000
#define GROUP_INDEX_MASK 0x00FF0000
#define UNIQUE_ID_MASK 0xFF000000
#define UNIQUE_ID_POSITION 24

#define GPIO_PAD_DEF(Group, Pad) (uint32_t)((Group << 16) + Pad)
#define GPIO_GET_GROUP_INDEX(Group) (Group & 0xFF)
#define GPIO_GET_GROUP_FROM_PAD(Pad) (Pad >> 16)
#define GPIO_GET_GROUP_INDEX_FROM_PAD(Pad) GPIO_GET_GROUP_INDEX((Pad >> 16))
#define GPIO_GET_PAD_NUMBER(Pad) (Pad & 0xFFFF)
#define GPIO_GET_CHIPSET_ID(Pad) (Pad >> 24)

#endif /* _SKYLAKESP_GPIO_DEFS_H_ */

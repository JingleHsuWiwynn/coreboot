//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
    IIO Config Update.

  Copyright (c) 2016-  2018, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
**/

#ifndef _SKXSP_TP_IIO_H
#define _SKXSP_TP_IIO_H

#include <FspmUpd.h>
#include <soc/skxsp_iioregs.h>

/**
 * Standard Tioga Pass Iio Bifurcation Table
 * This is SS 2x16 config. As documented in OCP TP spec, there are
 * 3 configs. SS 2x16 is the most common.
 * TODO: figure out config through board SKU ID and through PCIe
 * config GPIO setting (SLT_CFG0 / SLT_CFG1).
**/
static const UPD_IIO_BIFURCATION_DATA_ENTRY tp_iio_bifur_table[] =
{
  { Iio_Socket0, Iio_Iou0, IIO_BIFURCATE_xxxxxx16 }, /* 1A x16 */
  { Iio_Socket0, Iio_Iou1, IIO_BIFURCATE_xxxxxx16 }, /* 2A x16 */
  { Iio_Socket0, Iio_Iou2, IIO_BIFURCATE_xxxxxx16 }, /* 3A x16 */
  { Iio_Socket0, Iio_Mcp0, IIO_BIFURCATE_xxxxxxxx }, /* No MCP */
  { Iio_Socket0, Iio_Mcp1, IIO_BIFURCATE_xxxxxxxx }, /* No MCP */
  { Iio_Socket1, Iio_Iou0, IIO_BIFURCATE_xxxxxxxx }, /* no IOU0 */
  { Iio_Socket1, Iio_Iou1, IIO_BIFURCATE_xxxxxxxx }, /* no IOU1 */
  { Iio_Socket1, Iio_Iou2, IIO_BIFURCATE_xxx8xxx8 }, /* 3A x8, 3C x8 */
  { Iio_Socket1, Iio_Mcp0, IIO_BIFURCATE_xxxxxxxx }, /* No MCP */
  { Iio_Socket1, Iio_Mcp1, IIO_BIFURCATE_xxxxxxxx }, /* No MCP */
};

/**
 * Standard Tioga Pass Iio PCIe Port Table
**/
static const UPD_PCI_PORT_CONFIG tp_iio_pci_port_skt0[] = {
  // PortIndex |  HidePort  | DeEmphasis | PortLinkSpeed | MaxPayload | DfxDnTxPreset | DfxRxPreset | DfxUpTxPreset | Sris | PcieCommonClock | NtbPpd               | NtbSplitBar | NtbBarSizePBar23 | NtbBarSizePBar4 | NtbBarSizePBar5 | NtbBarSizePBar45 | NtbBarSizeSBar23 | NtbBarSizeSBar4 | NtbBarSizeSbar5 | NtbBarSizeSBar45 | NtbSBar01Prefetch | NtbXlinkCtlOverride
 { PORT_1A    , NOT_HIDE   , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_1B    , HIDE       , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_1C    , HIDE       , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_1D    , HIDE       , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_2A    , NOT_HIDE   , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_2B    , HIDE       , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_2C    , HIDE       , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_2D    , HIDE       , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_3A    , NOT_HIDE   , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_3B    , HIDE       , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_3C    , NOT_HIDE   , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
 { PORT_3D    , HIDE       , 0x00       , PcieAuto      , 0x0        , 0xFF          , 0xFF        , 0xFF          , 0x00 , 0x00            , NTB_PORT_TRANSPARENT , 0x00        , 0x16              , 0x16            , 0x16            , 0x16             , 0x16             , 0x16            , 0x16            , 0x16             , 0x00              , 0x03 },
};

/**
 * Standard Tioga Pass PCH PCIe Port Table
**/
static const UPD_PCH_PCIE_PORT tp_pch_pci_port_skt0[] = {
 // PortIndex ; ForceEnable ; PortLinkSpeed
 { 0x00       , 0x01        , PcieAuto },
 { 0x04       , 0x01        , PcieAuto },
 { 0x05       , 0x01        , PcieAuto },
};

#endif // end of _SKXSP_TP_IIO_H

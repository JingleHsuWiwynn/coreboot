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
**/
static const UPD_IIO_BIFURCATION_DATA_ENTRY tp_iio_bifur_table[] =
{
  { Iio_Socket0, Iio_Iou0, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Iou1, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Iou2, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Mcp0, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Mcp1, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket1, Iio_Iou0, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket1, Iio_Iou1, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket1, Iio_Iou2, IIO_BIFURCATE_xxxxx8x8 },
  { Iio_Socket1, Iio_Mcp0, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket1, Iio_Mcp1, IIO_BIFURCATE_xxxxxx16 },
};

/**
 * Standard Tioga Pass Iio Slot Table
**/
static const UPD_IIO_SLOT_CONFIG_DATA_ENTRY tp_iio_slot_table[] = {
  // Port         |  Slot      | Inter      | Power Limit | Power Limit | Hot     | Vpp          | Vpp          | PcieSSD | PcieSSD     | PcieSSD       | Hidden
  // Index        |            | lock       | Scale       |  Value      | Plug    | Port         | Addr         | Cap     | VppPort     | VppAddr       |
  { PORT_S0_1A_IDX,  4         , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S0_1B_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S0_1C_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PROT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S0_1D_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S0_2A_IDX,  2         , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S0_2B_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S0_2C_IDX,  2         , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S0_2D_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S0_3A_IDX,  2         , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S0_3B_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_PORT_MAX , NOT_HIDE },
  { PORT_S0_3C_IDX,  2         , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_PORT_MAX , NOT_HIDE },
  { PORT_S0_3D_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_PORT_MAX , NOT_HIDE },
  { PORT_S1_1A_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S1_1B_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S1_1C_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S1_1D_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S1_2A_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S1_2B_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S1_2C_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S1_2D_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S1_3A_IDX,  2         , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_S1_3B_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_PORT_MAX , NOT_HIDE },
  { PORT_S1_3C_IDX,  2         , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_PORT_MAX , NOT_HIDE },
  { PORT_S1_3D_IDX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_PORT_MAX , NOT_HIDE },
};

#endif // end of _SKXSP_TP_IIO_H

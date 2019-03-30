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
  { Iio_Socket0, Iio_Iou0, IIO_BIFURCATE_xxx8x4x4 },
  { Iio_Socket0, Iio_Iou1, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Iou2, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Mcp0, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Mcp1, IIO_BIFURCATE_xxxxxx16 },
};

/**
 * Standard Tioga Pass Iio Slot Table
**/
static const UPD_IIO_SLOT_CONFIG_DATA_ENTRY tp_iio_slot_table[] = {
  // Port        |  Slot      | Inter      | Power Limit | Power Limit | Hot     | Vpp          | Vpp          | PcieSSD | PcieSSD     | PcieSSD       | Hidden
  // Index       |            | lock       | Scale       |  Value      | Plug    | Port         | Addr         | Cap     | VppPort     | VppAddr       |
  { PORT_1A_INDEX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_1B_INDEX,  2         , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_1C_INDEX,  1         , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_2A_INDEX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_3A_INDEX,  4         , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_ADDR_MAX , NOT_HIDE },
  { PORT_3B_INDEX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_PORT_MAX , NOT_HIDE },
  { PORT_3C_INDEX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_PORT_MAX , NOT_HIDE },
  { PORT_3D_INDEX, NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_MAX  , VPP_PORT_MAX , NOT_HIDE },
};

#endif // end of _SKXSP_TP_IIO_H

/* MODIFIED-BEGIN by yongzhi.li, 2016-09-02, BUG-2641941*/
/* Copyright (C) 2016 Tcl Corporation Limited */

/*============================================================================

Copyright (c) 2015 Qualcomm Technologies, Inc.
  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.
// MODIFIED-END by yongzhi.li, BUG-2641941

============================================================================*/

/*============================================================================
 *                      INCLUDE FILES
 *===========================================================================*/
#include "chromatix.h"

static chromatix_parms_type chromatix_imx378_simba6x_parms = {
#include "chromatix_imx378_simba6x_snapshot_hdr.h"
};

/*============================================================================
 * FUNCTION    - load_chromatix -
 *
 * DESCRIPTION:
 *==========================================================================*/
void *load_chromatix(void)
{
  return &chromatix_imx378_simba6x_parms;
}

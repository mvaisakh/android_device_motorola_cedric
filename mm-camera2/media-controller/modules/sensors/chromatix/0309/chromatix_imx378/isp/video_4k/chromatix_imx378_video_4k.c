/* Copyright (C) 2016 Tcl Corporation Limited */
/*============================================================================

Copyright (c) 2015 Qualcomm Technologies, Inc.
  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.

============================================================================*/

/*============================================================================
 *                      INCLUDE FILES
 *===========================================================================*/
#include "chromatix.h"

static chromatix_parms_type chromatix_imx378_parms = {
#include "chromatix_imx378_video_4k.h"
};

/*============================================================================
 * FUNCTION    - load_chromatix -
 *
 * DESCRIPTION:
 *==========================================================================*/
void *load_chromatix(void)
{
  return &chromatix_imx378_parms;
}

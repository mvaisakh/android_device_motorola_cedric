/* Copyright (C) 2016 Tcl Corporation Limited */

/*============================================================================
Copyright (c) 2015 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.

============================================================================*/

/*============================================================================
 *                      INCLUDE FILES
 *===========================================================================*/
#include "chromatix.h"


static chromatix_parms_type chromatix_s5k4h8_idol4pro_cn_parms = {
#include "chromatix_s5k4h8_idol4pro_cn_hfr_90.h"
};

/*============================================================================
 * FUNCTION    - load_chromatix -
 *
 * DESCRIPTION:
 *==========================================================================*/
void *load_chromatix(void)
{
  //SLOW("chromatix ptr %p", &chromatix_s5k4h8_idol4pro_cn_parms);
  return &chromatix_s5k4h8_idol4pro_cn_parms;
}

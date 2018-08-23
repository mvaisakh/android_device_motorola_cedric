/*============================================================================

Copyright (c) 2013 Qualcomm Technologies, Inc. All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.

============================================================================*/

/*============================================================================
 *                      INCLUDE FILES
 *===========================================================================*/
#include "chromatix_common.h"

static chromatix_VFE_common_type chromatix_imx230_idol4pro_cn_parms = {
#include "chromatix_imx230_idol4pro_cn_common.h"
};

/*============================================================================
 * FUNCTION    - load_chromatix -
 *
 * DESCRIPTION:
 *==========================================================================*/
void *load_chromatix(void)
{
  return &chromatix_imx230_idol4pro_cn_parms;
}

/* aec_ext.h
 *
 * Copyright (c) 2015 Qualcomm Technologies, Inc. All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */

#ifndef __AEC_EXT_H__
#define __AEC_EXT_H__

#include "aec_port.h"
#include "aec.h"
#include "stats_util.h"

/**
 * Custom output mask.
 */
typedef enum {
  AEC_OUTPUT_CUSTOM_MAX
} aec_ext_output_mask_type;

/**
 * Custom output structure. External core should define
 * the parameters here.
 */
typedef struct {
  uint32_t mask;
  /* Add parameters here */
} aec_ext_output_t;


typedef struct _aec_ext_param {
  aec_ext_output_t custom_output;
  int32_t          led_mode;
} aec_ext_param_t;

/**
 * Custom aec get paramter structure. External parameters should be
 * defined here.
 */
typedef struct {
  /* Add aec custom get parameters here */
  int dummy;
} aec_ext_get_param_t;

boolean aec_port_ext_is_extension_required(void *aec_libptr,
  cam_position_t cam_position, boolean *use_default_algo);
boolean aec_port_ext_update_func_table(void *ptr);
void * aec_port_ext_load_function(aec_object_t *aec_object, void *aec_lib,
  cam_position_t cam_position, boolean use_default_algo);
void aec_port_ext_unload_function(aec_port_private_t *private);


#endif /*__AEC_EXT_H__*/

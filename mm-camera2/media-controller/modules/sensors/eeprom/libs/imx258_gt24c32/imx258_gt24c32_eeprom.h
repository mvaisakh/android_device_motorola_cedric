/*============================================================================

Copyright (c) 2016 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.

============================================================================*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../eeprom_util/eeprom.h"
#include "eeprom_lib.h"
#include "eeprom_util.h"
#include "debug_lib.h"
#include "sensor_lib.h"

#define MODULE_INFO_OFFSET  0x0000
#define FLAG_OFFSET         0x000A
#define AWB_OFFSET          0x0033
#define AF_OFFSET           0x0026
#define LSC_OFFSET          0x0053
#define MESH_HWROLLOFF_SIZE (17*13)
#define PDGAIN_WITDH        17
#define PDGAIN_HEIGHT       13
#define PDGAIN_LENGTH2D     (PDGAIN_HEIGHT * PDGAIN_WITDH)
#define PDAF_KCOEF_OFFSET   0x0543
#define PD_KCALCOFF_MAX     4
#define PDAF_GAIN_OFFSET    0x054D
#define INVALID_DATA        0xFFFF
#define QVALUE              1024.0
#define INF_MARGIN          (-0.1)
#define MACRO_MARGIN        (0.30)
#define DC_OFFSET           0x08D3
#define DC_MAIN             (DC_OFFSET + 4)
#define DC_AUX              (DC_OFFSET + 20)
#define DC_ROTATION_MATRIX  9
#define DC_GEOMETRIC_MATRIX 32
#define DC_OTHERS           (DC_OFFSET + 200)
#define AE_SYNC             0x0534
#define DC_SIZE             471 /* Size is the total number of bytes in OTP */

typedef struct {
  unsigned char vendor_id_h;
  unsigned char vendor_id_l;
  unsigned char year;
  unsigned char month;
  unsigned char day;
  unsigned char hour;
  unsigned char minute;
  unsigned char second;
  unsigned char lens_id;
  unsigned char vcm_id;
  unsigned char driver_ic_id;
  unsigned char fw_ver;
  unsigned char sensor_id;
  unsigned char product_id;
  unsigned char version_id;
} module_info_t;

static unsigned char awb_present      = FALSE;
static unsigned char af_present       = FALSE;
static unsigned char lsc_present      = FALSE;
static unsigned char insensor_present = FALSE;
static unsigned char dualc_present    = FALSE;

void imx258_gt24c32_eeprom_get_calibration_items(void *e_ctrl);
void imx258_gt24c32_eeprom_format_calibration_data(void *e_ctrl);

static eeprom_lib_func_t imx258_gt24c32_eeprom_lib_func_ptr = {
  .get_calibration_items    = imx258_gt24c32_eeprom_get_calibration_items,
  .format_calibration_data  = imx258_gt24c32_eeprom_format_calibration_data,
  .do_af_calibration        = eeprom_autofocus_calibration,
  .do_wbc_calibration       = eeprom_whitebalance_calibration,
  .do_lsc_calibration       = eeprom_lensshading_calibration,
  .get_raw_data             = NULL,
  .get_ois_raw_data         = NULL,
  .eeprom_info =
  {
    .power_setting_array =
    {
      .power_setting_a =
      {
        {
          .seq_type = CAMERA_POW_SEQ_VREG,
          .seq_val = CAMERA_VIO,
          .config_val = 0,
          .delay = 0,
        },
      },
      .size = 1,
      .power_down_setting_a =
      {
        {
          .seq_type = CAMERA_POW_SEQ_VREG,
          .seq_val = CAMERA_VIO,
          .config_val = 0,
          .delay = 0,
        },
      },
      .size_down = 1,
    },
    .i2c_freq_mode = SENSOR_I2C_MODE_STANDARD,
    .mem_map_array =
    {
      .memory_map =
      {
        {
          .slave_addr = 0xa0,
          .mem_settings =
          {
            { 0x0, CAMERA_I2C_WORD_ADDR,
              2902, CAMERA_I2C_BYTE_DATA, CAMERA_I2C_OP_READ, 0 },
          },
          .memory_map_size = 1,
        },
      },
      .size_map_array = 1,
    },
  },
};

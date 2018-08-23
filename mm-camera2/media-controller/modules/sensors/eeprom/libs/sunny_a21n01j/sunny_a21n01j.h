/*============================================================================

  Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/
#include <stdio.h>
#include <string.h>
#include "chromatix.h"
#include "../eeprom_util/eeprom.h"
#include "eeprom_lib.h"
#include "debug_lib.h"
#include "sensor_lib.h"

#if !defined RETURN_ON_NULL
#define RETURN_ON_NULL(expr)\
    if ((expr) == NULL) {\
        SERR("failed NULL pointer detected " #expr);\
        return FALSE;\
     }
#endif
#define INFO_OFFSET     0x00
#define INFO_CHK        0x07

#define WB58_OFFSET     0x08
#define WB58_CHK        0x15
#define WB40_OFFSET     0x16
#define WB40_CHK        0x23
#define WB31_OFFSET     0x24
#define WB31_CHK        0x31
#define WB_R_GR_H       0x0001
#define WB_R_GR_L       0x0002
#define WB_B_GR_H       0x0003
#define WB_B_GR_L       0x0004
#define WB_GR_GB_H      0x0005
#define WB_GR_GB_L      0x0006

#define AF_OFFSET       0x34
#define AF_CHK          0x39

#define G_MACRO         700
#define G_INFINI        440

#define LSC_USE_RAW         1
#define LSC_EN_ADDR_NORM    0x0B00
#define LSC_EN_VAL_NORM     0x01
#define LSC_SRAM_SWCH_ADDR  0x6303
#define LSC_SRAM_SWCH_VAL   0x01
#define LSC_REG_PNT_ADDR    0x7800
#define LSC_OFFSET          0x40
#define LSC_CHK             0x41
#define MESH_HWROLLOFF_SIZE (11*8)
#define LSC_R_OFFSET        0x100      //R/GR Gb/B interpolated
#define LSC_GR_OFFSET       (LSC_R_OFFSET+2)
#define LSC_GB_OFFSET       (LSC_R_OFFSET+MESH_HWROLLOFF_SIZE*4)
#define LSC_B_OFFSET        (LSC_GB_OFFSET+2)

#define SPC_OFFSET          0x400
#define SPC_CHK             0x561

#define SPC_SETTING_SIZE    352

#define DCC_OFFSET          0x562
#define DCC_CHK             0x5c3

#define FULL_SIZE_WIDTH     5344
#define FULL_SIZE_HEIGHT    4016

//////for referenct///////////////////
#define QVALUE              1024.0

#define PAGE_EMPTY          0
#define PAGE_NOT_EMPTY      1
#define MAX_EMPTY_BYTES     32

#define HALL_OFFSET         1792

#define VALID_FLAG          0x01
#define SPC_ADDR            0x7c00
#define PD_KNOT_X           8
#define PD_KNOT_Y           6
#define PD_OFFSET_X         112
#define PD_OFFSET_Y         88
#define PD_AREA_X           640
#define PD_AREA_Y           640

#define FAR_MARGIN          (-0.15)
#define NEAR_MARGIN         (0.35)

#define MARGIN              2

#if LSC_USE_RAW
#define TOTAL_REG_SIZE      (SPC_SETTING_SIZE+MESH_HWROLLOFF_SIZE*4*2+2+MARGIN)
#else
#define TOTAL_REG_SIZE      (SPC_SETTING_SIZE+MARGIN)
#endif

//static unsigned int datapresent = 0;

static unsigned char awb_present = 0;
static unsigned char af_present = 0;
static unsigned char lsc_present = 0;
static unsigned char spc_present = 0;
static unsigned char dcc_present = 0;

/* in-sensor SPC (shield pixel correction) */
static struct camera_i2c_reg_setting g_reg_setting;
static struct camera_i2c_reg_array g_reg_array[TOTAL_REG_SIZE];
static unsigned char hall_offset = 0, hall_bias = 0;

void a21n01j_get_calibration_items(void *e_ctrl);
static void a21n01j_format_calibration_data(void *e_ctrl);
static int a21n01j_autofocus_calibration(void *e_ctrl);
static int a21n01j_get_raw_data(void *e_ctrl, void *data);

static eeprom_lib_func_t a21n01j_lib_func_ptr = {
  .get_calibration_items = a21n01j_get_calibration_items,
  .format_calibration_data = a21n01j_format_calibration_data,
  .do_af_calibration = a21n01j_autofocus_calibration,
  .do_wbc_calibration = eeprom_whitebalance_calibration,
  .do_lsc_calibration = eeprom_lensshading_calibration,
  .get_raw_data = a21n01j_get_raw_data,
  .get_ois_raw_data = NULL,
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
              0x5c4, CAMERA_I2C_BYTE_DATA, CAMERA_I2C_OP_READ, 0 },
          },
          .memory_map_size = 1,
        },
      },
      .size_map_array = 1,
    },
  },
};

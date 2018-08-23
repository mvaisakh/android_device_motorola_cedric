/*
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <stdio.h>
#include <string.h>
#include "../eeprom_util/eeprom.h"
#include "eeprom_lib.h"
#include "eeprom_util.h"
#include "debug_lib.h"
#include "sensor_lib.h"

#define MODULE_INFO_FLAG_OFFSET     0x00
#define MODULE_INFO_OFFSET          0x01

#define AF_FLAG_OFFSET              0x0718
#define AF_OFFSET                   AF_FLAG_OFFSET + 1
#define FAR_MARGIN                  (-0.20)
#define NEAR_MARGIN                 (0.25)

#define AWB_FLAG_OFFSET             0x00
#define AWB_OFFSET                  0x09
#define AWB_5800K_OFFSET            0x09
#define AWB_4000K_OFFSET            0x15
#define AWB_3100K_OFFSET            0x21
#define AWB_START_BYTE              0x01
#define AWB_LAST_BYTE               0x2C
#define AWB_CRC_OFFSET              0x2D

#define LSC_FLAG_OFFSET             0x2E
#define LSC_OFFSET                  LSC_FLAG_OFFSET + 1
#define LSC_GRID_SIZE               221
#define LSC_LAST_BYTE               0X0716
#define LSC_CRC_OFFSET              0X0717


#define VALID_FLAG                  0x01
#define QVALUE                      1023.0

#define SPC_FLAG_OFFSET             0x724
#define SPC_OFFSET                  SPC_FLAG_OFFSET + 1
#define SPC_SETTING_SIZE            96
#define SPC_ADDR                    0x7d4c

#define PD_KNOT_X                   8
#define PD_KNOT_Y                   6
#define PD_OFFSET_X                 64
#define PD_OFFSET_Y                 16
#define PD_AREA_X                   488
#define PD_AREA_Y                   496

#define DCC_FLAG_OFFSET             0x787
#define DCC_OFFSET                  DCC_FLAG_OFFSET + 1

typedef struct {
   unsigned char module_id;
   unsigned char year;
   unsigned char month;
   unsigned char day;
} module_info_t;

typedef struct {
   unsigned char macro_h;
   unsigned char macro_l;
   unsigned char infinity_h;
   unsigned char infinity_l;
} af_data_t;

typedef struct {
   unsigned char r_over_gr_h;
   unsigned char r_over_gr_l;
   unsigned char b_over_gb_h;
   unsigned char b_over_gb_l;
   unsigned char gr_over_gb_h;
   unsigned char gr_over_gb_l;
   unsigned char golden_r_over_gr_h;
   unsigned char golden_r_over_gr_l;
   unsigned char golden_b_over_gb_h;
   unsigned char golden_b_over_gb_l;
   unsigned char golden_gr_over_gb_h;
   unsigned char golden_gr_over_gb_l;
} awb_data_t;

static unsigned char awb_present = 0;
static unsigned char af_present = 0;
static unsigned char lsc_present = 0;
static unsigned char spc_present = 0;
static unsigned char dcc_present = 0;


/* in-sensor SPC (shield pixel correction) */
static struct camera_i2c_reg_setting g_reg_setting;
static struct camera_i2c_reg_array g_reg_array[SPC_SETTING_SIZE];

void sony_imx386_eeprom_get_calibration_items(void *e_ctrl);
void sony_imx386_eeprom_format_calibration_data(void *e_ctrl);
static int sony_imx386_eeprom_get_raw_data(void *e_ctrl, void *data);

static eeprom_lib_func_t sony_imx386_eeprom_lib_func_ptr = {
  .get_calibration_items    = sony_imx386_eeprom_get_calibration_items,
  .format_calibration_data  = sony_imx386_eeprom_format_calibration_data,
  .do_af_calibration        = eeprom_autofocus_calibration,
  .do_wbc_calibration       = eeprom_whitebalance_calibration,
  .do_lsc_calibration       = NULL,
  .get_raw_data             = sony_imx386_eeprom_get_raw_data,
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
            { 0x0, CAMERA_I2C_WORD_ADDR, 2025, CAMERA_I2C_BYTE_DATA, CAMERA_I2C_OP_READ, 0 },
          },
          .memory_map_size = 1,
        },
      },
      .size_map_array = 1,
    },
  },
};

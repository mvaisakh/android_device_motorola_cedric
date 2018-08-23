/* Copyright (C) 2016 Tcl Corporation Limited */
#ifndef __s5k4h8_LIB_H__
#define __s5k4h8_LIB_H__

#include "sensor_lib.h"
#define SENSOR_MODEL "s5k4h8_idol4pro_cn"

/* s5k4h8 Regs */
#define s5k4h8_DIG_GAIN_GR_ADDR       0x020E /* 0x4000020E */
#define s5k4h8_DIG_GAIN_R_ADDR        0x0210 /* 0x40000210 */
#define s5k4h8_DIG_GAIN_B_ADDR        0x0212 /* 0x40000212 */
#define s5k4h8_DIG_GAIN_GB_ADDR       0x0214 /* 0x40000214 */

/* s5k4h8 CONSTANTS */
#define s5k4h8_MAX_INTEGRATION_MARGIN   4  /* Unknown */

#define s5k4h8_DATA_PEDESTAL            0x40 /* 10bit */

#define s5k4h8_MIN_AGAIN_REG_VAL        32 /* 1.0x */
#define s5k4h8_MAX_AGAIN_REG_VAL        384 /* 16.0x */

#define s5k4h8_MIN_DGAIN_REG_VAL        256 /* 1.0x */
#define s5k4h8_MAX_DGAIN_REG_VAL        256 /* 1.0x */

/* s5k4h8 FORMULAS */
#define s5k4h8_MIN_AGAIN    (1.0)
#define s5k4h8_MAX_AGAIN    (s5k4h8_MAX_AGAIN_REG_VAL / 32)

#define s5k4h8_MIN_DGAIN    (s5k4h8_MIN_DGAIN_REG_VAL / 256)
#define s5k4h8_MAX_DGAIN    (s5k4h8_MAX_DGAIN_REG_VAL / 256)

#define s5k4h8_MIN_GAIN     s5k4h8_MIN_AGAIN * s5k4h8_MIN_DGAIN
#define s5k4h8_MAX_GAIN     s5k4h8_MAX_AGAIN * s5k4h8_MAX_DGAIN

int32_t s5k4h8_calculate_exposure(float real_gain,
  uint32_t line_count, sensor_exposure_info_t *exp_info, float s_real_gain);

int32_t s5k4h8_fill_exposure_array(uint32_t gain,
  __attribute__((unused)) uint32_t digital_gain, uint32_t line,
  uint32_t fl_lines,  __attribute__((unused)) int32_t luma_avg,
  __attribute__((unused)) uint32_t hdr_param,
  struct camera_i2c_reg_setting* reg_setting,
  __attribute__((unused)) unsigned int s_gain,
  __attribute__((unused)) int s_linecount,
  __attribute__((unused)) int is_hdr_enabled);

#define START_REG_ARRAY \
{ \
  {0x0100, 0x0103, 0x00}, \
}

#define STOP_REG_ARRAY \
{ \
  {0x0100, 0x0000, 0x00}, \
}

#define GROUPON_REG_ARRAY \
{ \
  {0x0104, 0x01, 0x00}, \
}

#define GROUPOFF_REG_ARRAY \
{ \
  {0x0104, 0x00, 0x00}, \
}

#define INIT0_REG_ARRAY \
{ \
  {0x6028, 0x4000, 0x00}, \
  {0x602A, 0x6214, 0x00}, \
  {0x6F12, 0x7971, 0x00}, \
  {0x602A, 0x6218, 0x00}, \
  {0x6F12, 0x7150, 0x00}, \
  {0x6028, 0x2000, 0x00}, \
  {0x602A, 0x1FD0, 0x00},   \
  {0x6F12, 0x0448, 0x00},   \
  {0x6F12, 0x0349, 0x00},   \
  {0x6F12, 0x0160, 0x00},   \
  {0x6F12, 0xC26A, 0x00},   \
  {0x6F12, 0x511A, 0x00},   \
  {0x6F12, 0x8180, 0x00},   \
  {0x6F12, 0x00F0, 0x00},   \
  {0x6F12, 0x88B8, 0x00},   \
  {0x6F12, 0x2000, 0x00},   \
  {0x6F12, 0x2171, 0x00},   \
  {0x6F12, 0x2000, 0x00},   \
  {0x6F12, 0x13A0, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x2DE9, 0x00},   \
  {0x6F12, 0xF041, 0x00},   \
  {0x6F12, 0x8046, 0x00},   \
  {0x6F12, 0x4648, 0x00},   \
  {0x6F12, 0x92B0, 0x00},   \
  {0x6F12, 0x0C46, 0x00},   \
  {0x6F12, 0x0078, 0x00},   \
  {0x6F12, 0x80B3, 0x00},   \
  {0x6F12, 0x0020, 0x00},   \
  {0x6F12, 0x0090, 0x00},   \
  {0x6F12, 0x0190, 0x00},   \
  {0x6F12, 0x0546, 0x00},   \
  {0x6F12, 0x0646, 0x00},   \
  {0x6F12, 0x6F46, 0x00},   \
  {0x6F12, 0x0290, 0x00},   \
  {0x6F12, 0x06EB, 0x00},   \
  {0x6F12, 0xC601, 0x00},   \
  {0x6F12, 0x01EB, 0x00},   \
  {0x6F12, 0x0800, 0x00},   \
  {0x6F12, 0x0922, 0x00},   \
  {0x6F12, 0x6946, 0x00},   \
  {0x6F12, 0x00F0, 0x00},   \
  {0x6F12, 0x83F8, 0x00},   \
  {0x6F12, 0x0022, 0x00},   \
  {0x6F12, 0x0021, 0x00},   \
  {0x6F12, 0xB85C, 0x00},   \
  {0x6F12, 0xC1F1, 0x00},   \
  {0x6F12, 0x0703, 0x00},   \
  {0x6F12, 0xD840, 0x00},   \
  {0x6F12, 0x00F0, 0x00},   \
  {0x6F12, 0x0103, 0x00},   \
  {0x6F12, 0x4819, 0x00},   \
  {0x6F12, 0x012B, 0x00},   \
  {0x6F12, 0x2354, 0x00},   \
  {0x6F12, 0x08D1, 0x00},   \
  {0x6F12, 0x38B1, 0x00},   \
  {0x6F12, 0x2428, 0x00},   \
  {0x6F12, 0x05D0, 0x00},   \
  {0x6F12, 0x4828, 0x00},   \
  {0x6F12, 0x03D0, 0x00},   \
  {0x6F12, 0x6C28, 0x00},   \
  {0x6F12, 0x01D0, 0x00},   \
  {0x6F12, 0x0F23, 0x00},   \
  {0x6F12, 0x2354, 0x00},   \
  {0x6F12, 0x491C, 0x00},   \
  {0x6F12, 0x0829, 0x00},   \
  {0x6F12, 0xE9DB, 0x00},   \
  {0x6F12, 0x0835, 0x00},   \
  {0x6F12, 0x521C, 0x00},   \
  {0x6F12, 0x092A, 0x00},   \
  {0x6F12, 0xE4DB, 0x00},   \
  {0x6F12, 0x761C, 0x00},   \
  {0x6F12, 0x022E, 0x00},   \
  {0x6F12, 0xD8DB, 0x00},   \
  {0x6F12, 0x12B0, 0x00},   \
  {0x6F12, 0xBDE8, 0x00},   \
  {0x6F12, 0xF081, 0x00},   \
  {0x6F12, 0xFFE7, 0x00},   \
  {0x6F12, 0x4822, 0x00},   \
  {0x6F12, 0x6946, 0x00},   \
  {0x6F12, 0x4046, 0x00},   \
  {0x6F12, 0x00F0, 0x00},   \
  {0x6F12, 0x5BF8, 0x00},   \
  {0x6F12, 0x0020, 0x00},   \
  {0x6F12, 0x6946, 0x00},   \
  {0x6F12, 0x04EB, 0x00},   \
  {0x6F12, 0x4003, 0x00},   \
  {0x6F12, 0x0A5C, 0x00},   \
  {0x6F12, 0x02F0, 0x00},   \
  {0x6F12, 0x0F02, 0x00},   \
  {0x6F12, 0x04F8, 0x00},   \
  {0x6F12, 0x1020, 0x00},   \
  {0x6F12, 0x0A5C, 0x00},   \
  {0x6F12, 0x401C, 0x00},   \
  {0x6F12, 0x1209, 0x00},   \
  {0x6F12, 0x5A70, 0x00},   \
  {0x6F12, 0x4828, 0x00},   \
  {0x6F12, 0xF2D3, 0x00},   \
  {0x6F12, 0xE6E7, 0x00},   \
  {0x6F12, 0x2DE9, 0x00},   \
  {0x6F12, 0xF047, 0x00},   \
  {0x6F12, 0x0200, 0x00},   \
  {0x6F12, 0x1F48, 0x00},   \
  {0x6F12, 0x8946, 0x00},   \
  {0x6F12, 0x00F1, 0x00},   \
  {0x6F12, 0x1107, 0x00},   \
  {0x6F12, 0x00F1, 0x00},   \
  {0x6F12, 0xA208, 0x00},   \
  {0x6F12, 0x1BD0, 0x00},   \
  {0x6F12, 0x0578, 0x00},   \
  {0x6F12, 0x1226, 0x00},   \
  {0x6F12, 0xC5B1, 0x00},   \
  {0x6F12, 0x1B48, 0x00},   \
  {0x6F12, 0x0068, 0x00},   \
  {0x6F12, 0xB0F8, 0x00},   \
  {0x6F12, 0x6A40, 0x00},   \
  {0x6F12, 0x1748, 0x00},   \
  {0x6F12, 0x0078, 0x00},   \
  {0x6F12, 0x20B1, 0x00},   \
  {0x6F12, 0x2046, 0x00},   \
  {0x6F12, 0x00F0, 0x00},   \
  {0x6F12, 0x39F8, 0x00},   \
  {0x6F12, 0x84B2, 0x00},   \
  {0x6F12, 0x00E0, 0x00},   \
  {0x6F12, 0x4826, 0x00},   \
  {0x6F12, 0xE807, 0x00},   \
  {0x6F12, 0x09D0, 0x00},   \
  {0x6F12, 0x3946, 0x00},   \
  {0x6F12, 0x2046, 0x00},   \
  {0x6F12, 0x00F0, 0x00},   \
  {0x6F12, 0x35F8, 0x00},   \
  {0x6F12, 0xA019, 0x00},   \
  {0x6F12, 0x4FF4, 0x00},   \
  {0x6F12, 0x9072, 0x00},   \
  {0x6F12, 0x4146, 0x00},   \
  {0x6F12, 0x00F0, 0x00},   \
  {0x6F12, 0x25F8, 0x00},   \
  {0x6F12, 0xB9F1, 0x00},   \
  {0x6F12, 0x000F, 0x00},   \
  {0x6F12, 0x05D0, 0x00},   \
  {0x6F12, 0x4146, 0x00},   \
  {0x6F12, 0x3846, 0x00},   \
  {0x6F12, 0xBDE8, 0x00},   \
  {0x6F12, 0xF047, 0x00},   \
  {0x6F12, 0x00F0, 0x00},   \
  {0x6F12, 0x2BB8, 0x00},   \
  {0x6F12, 0xBDE8, 0x00},   \
  {0x6F12, 0xF087, 0x00},   \
  {0x6F12, 0x10B5, 0x00},   \
  {0x6F12, 0x0022, 0x00},   \
  {0x6F12, 0xAFF2, 0x00},   \
  {0x6F12, 0x0711, 0x00},   \
  {0x6F12, 0x0848, 0x00},   \
  {0x6F12, 0x00F0, 0x00},   \
  {0x6F12, 0x27F8, 0x00},   \
  {0x6F12, 0x0022, 0x00},   \
  {0x6F12, 0xAFF2, 0x00},   \
  {0x6F12, 0x7501, 0x00},   \
  {0x6F12, 0xBDE8, 0x00},   \
  {0x6F12, 0x1040, 0x00},   \
  {0x6F12, 0x0548, 0x00},   \
  {0x6F12, 0x00F0, 0x00},   \
  {0x6F12, 0x1FB8, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x2000, 0x00},   \
  {0x6F12, 0x2170, 0x00},   \
  {0x6F12, 0x2000, 0x00},   \
  {0x6F12, 0x0C40, 0x00},   \
  {0x6F12, 0x2000, 0x00},   \
  {0x6F12, 0x0560, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x1481, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x152D, 0x00},   \
  {0x6F12, 0x48F6, 0x00},   \
  {0x6F12, 0x296C, 0x00},   \
  {0x6F12, 0xC0F2, 0x00},   \
  {0x6F12, 0x000C, 0x00},   \
  {0x6F12, 0x6047, 0x00},   \
  {0x6F12, 0x41F2, 0x00},   \
  {0x6F12, 0xE94C, 0x00},   \
  {0x6F12, 0xC0F2, 0x00},   \
  {0x6F12, 0x000C, 0x00},   \
  {0x6F12, 0x6047, 0x00},   \
  {0x6F12, 0x41F2, 0x00},   \
  {0x6F12, 0x814C, 0x00},   \
  {0x6F12, 0xC0F2, 0x00},   \
  {0x6F12, 0x000C, 0x00},   \
  {0x6F12, 0x6047, 0x00},   \
  {0x6F12, 0x41F2, 0x00},   \
  {0x6F12, 0x950C, 0x00},   \
  {0x6F12, 0xC0F2, 0x00},   \
  {0x6F12, 0x000C, 0x00},   \
  {0x6F12, 0x6047, 0x00},   \
  {0x6F12, 0x49F2, 0x00},   \
  {0x6F12, 0x514C, 0x00},   \
  {0x6F12, 0xC0F2, 0x00},   \
  {0x6F12, 0x000C, 0x00},   \
  {0x6F12, 0x6047, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x4088, 0x00},   \
  {0x6F12, 0x0002, 0x00},   \
  {0x6F12, 0x0000, 0x00},   \
  {0x6F12, 0x0001, 0x00},   \
  {0x6028, 0x2000, 0x00}, \
  {0x602A, 0x0EC6, 0x00}, \
  {0x6F12, 0x0000, 0x00}, \
  {0x5360, 0x0000, 0x00}, \
  {0x306A, 0x01C4, 0x00}, \
  {0xFCFC, 0x4000, 0x00}, \
  {0xF490, 0x0030, 0x00}, \
  {0xF47A, 0x0012, 0x00}, \
  {0xF428, 0x0200, 0x00}, \
  {0xF48E, 0x0010, 0x00}, \
  {0xF45C, 0x0004, 0x00}, \
  {0x0B04, 0x0101, 0x00}, \
  {0x0B00, 0x0180, 0x00}, \
  {0x6028, 0x2000, 0x00}, \
  {0x602A, 0x0C40, 0x00}, \
  {0x6F12, 0x0140, 0x00}, \
}
#define RES0_REG_ARRAY \
{ \
  {0xFCFC, 0x4000, 0x00}, \
  {0x0200, 0x0824, 0x00}, \
  {0x0202, 0x0246, 0x00}, \
  {0x31AA, 0x0004, 0x00}, \
  {0x1006, 0x0006, 0x00}, \
  {0x31FA, 0x0000, 0x00}, \
  {0x0204, 0x0020, 0x00}, \
  {0x020E, 0x0100, 0x00}, \
  {0x0344, 0x0008, 0x00}, \
  {0x0348, 0x0CC7, 0x00}, \
  {0x0346, 0x0008, 0x00}, \
  {0x034A, 0x0997, 0x00}, \
  {0x034C, 0x0CC0, 0x00}, \
  {0x034E, 0x0990, 0x00}, \
  {0x0342, 0x12CA, 0x00}, \
  {0x0340, 0x09B4, 0x00}, \
  {0x0900, 0x0111, 0x00}, \
  {0x0380, 0x0001, 0x00}, \
  {0x0382, 0x0001, 0x00}, \
  {0x0384, 0x0001, 0x00}, \
  {0x0386, 0x0001, 0x00}, \
  {0x0400, 0x0000, 0x00}, \
  {0x0404, 0x0010, 0x00}, \
  {0x0114, 0x0130, 0x00}, \
  {0x0136, 0x1800, 0x00}, \
  {0x0300, 0x0005, 0x00}, \
  {0x0302, 0x0001, 0x00}, \
  {0x0304, 0x0006, 0x00}, \
  {0x0306, 0x00B1, 0x00}, \
  {0x030C, 0x0006, 0x00}, \
  {0x030E, 0x00FA, 0x00}, \
  {0x3008, 0x0000, 0x00}, \
  {0x1004, 0x0001, 0x00},  \
  {0x0B00, 0x0180, 0x00}, \
}

#define RES1_REG_ARRAY \
{ \
  {0xFCFC, 0x4000, 0x00}, \
  {0x0200, 0x0618, 0x00}, \
  {0x0202, 0x0465, 0x00}, \
  {0x31AA, 0x0004, 0x00}, \
  {0x1006, 0x0006, 0x00}, \
  {0x31FA, 0x0000, 0x00}, \
  {0x0204, 0x0020, 0x00}, \
  {0x0344, 0x0008, 0x00}, \
  {0x0348, 0x0CC7, 0x00}, \
  {0x0346, 0x0008, 0x00}, \
  {0x034A, 0x0997, 0x00}, \
  {0x034C, 0x0660, 0x00}, \
  {0x034E, 0x04C8, 0x00}, \
  {0x0342, 0x0EA0, 0x00}, \
  {0x0340, 0x04DE, 0x00}, \
  {0x0900, 0x0212, 0x00}, \
  {0x0380, 0x0001, 0x00}, \
  {0x0382, 0x0001, 0x00}, \
  {0x0384, 0x0001, 0x00}, \
  {0x0386, 0x0003, 0x00}, \
  {0x0400, 0x0002, 0x00}, \
  {0x0404, 0x0020, 0x00}, \
  {0x0114, 0x0130, 0x00}, \
  {0x0136, 0x1800, 0x00}, \
  {0x0300, 0x0005, 0x00}, \
  {0x0302, 0x0002, 0x00}, \
  {0x0304, 0x0004, 0x00}, \
  {0x0306, 0x0075, 0x00}, \
  {0x030C, 0x0004, 0x00}, \
  {0x030E, 0x006B, 0x00}, \
  {0x3008, 0x0000, 0x00}, \
  {0x317A, 0x0101, 0x00}, \
  {0x0B00, 0x0180, 0x00}, \
}

#define RES2_REG_ARRAY \
{ \
  {0xFCFC, 0x4000, 0x00}, \
  {0x0200, 0x0618, 0x00}, \
  {0x0202, 0x0100, 0x00}, \
  {0x31AA, 0x0004, 0x00}, \
  {0x1006, 0x0006, 0x00}, \
  {0x31FA, 0x0000, 0x00}, \
  {0x0204, 0x0020, 0x00}, \
  {0x020E, 0x0100, 0x00}, \
  {0x0344, 0x0008, 0x00}, \
  {0x0348, 0x0CC7, 0x00}, \
  {0x0346, 0x0008, 0x00}, \
  {0x034A, 0x0997, 0x00}, \
  {0x034C, 0x0330, 0x00}, \
  {0x034E, 0x0264, 0x00}, \
  {0x0342, 0x0EA0, 0x00}, \
  {0x0340, 0x026F, 0x00}, \
  {0x0900, 0x0214, 0x00}, \
  {0x0380, 0x0001, 0x00}, \
  {0x0382, 0x0001, 0x00}, \
  {0x0384, 0x0001, 0x00}, \
  {0x0386, 0x0007, 0x00}, \
  {0x0400, 0x0002, 0x00}, \
  {0x0404, 0x0040, 0x00}, \
  {0x0114, 0x0130, 0x00}, \
  {0x0136, 0x1800, 0x00}, \
  {0x0300, 0x0005, 0x00}, \
  {0x0302, 0x0002, 0x00}, \
  {0x0304, 0x0004, 0x00}, \
  {0x0306, 0x0075, 0x00}, \
  {0x030C, 0x0004, 0x00}, \
  {0x030E, 0x006B, 0x00}, \
  {0x3008, 0x0000, 0x00}, \
  {0x317A, 0x0100, 0x00}, \
  {0x0B00, 0x0180, 0x00}, \
}

#define RES3_REG_ARRAY \
{ \
  {0x602A, 0x0200, 0x00}, \
  {0x6F12, 0x0618, 0x00},  \
  {0x6F12, 0x0100, 0x00}, \
  {0x6F12, 0x0020, 0x00}, \
  {0x602A, 0x0344, 0x00}, \
  {0x6F12, 0x0338, 0x00}, \
  {0x602A, 0x0348, 0x00}, \
  {0x6F12, 0x0997, 0x00}, \
  {0x602A, 0x0346, 0x00}, \
  {0x6F12, 0x0264, 0x00}, \
  {0x602A, 0x034A, 0x00}, \
  {0x6F12, 0x073B, 0x00}, \
  {0x6F12, 0x0198, 0x00}, \
  {0x6F12, 0x0132, 0x00}, \
  {0x602A, 0x0342, 0x00}, \
  {0x6F12, 0x0EA0, 0x00}, \
  {0x602A, 0x0340, 0x00}, \
  {0x6F12, 0x033E, 0x00}, \
  {0x602A, 0x0900, 0x00}, \
  {0x6F12, 0x0214, 0x00}, \
  {0x602A, 0x0380, 0x00}, \
  {0x6F12, 0x0001, 0x00}, \
  {0x6F12, 0x0001, 0x00}, \
  {0x6F12, 0x0001, 0x00}, \
  {0x6F12, 0x0007, 0x00}, \
  {0x602A, 0x0400, 0x00}, \
  {0x6F12, 0x0002, 0x00}, \
  {0x602A, 0x0404, 0x00}, \
  {0x6F12, 0x0040, 0x00}, \
  {0x6028, 0x2000, 0x00}, \
  {0x602A, 0x0E42, 0x00}, \
  {0x6F12, 0x0001, 0x00}, \
  {0x6028, 0x4000, 0x00}, \
  {0x602A, 0x0114, 0x00}, \
  {0x6F12, 0x0130, 0x00}, \
  {0x602A, 0x317A, 0x00}, \
  {0x6F12, 0x0100, 0x00}, \
  {0x602A, 0x0B00, 0x00}, \
  {0x6F12, 0x0180, 0x00}, \
  {0x602A, 0x0B04, 0x00}, \
  {0x6F12, 0x0101, 0x00}, \
  {0x602A, 0x3058, 0x00}, \
  {0x6F12, 0x0100, 0x00}, \
  {0x602A, 0x0306, 0x00}, \
  {0x6F12, 0x00AF, 0x00}, \
  {0x602a, 0x030E, 0x00}, \
  {0x6F12, 0x00AF, 0x00}, \
  {0x0B00, 0x0180, 0x00}, \
}














#define RES4_REG_ARRAY \
{ \
  {0x602A, 0x0200, 0x00}, \
  {0x6F12, 0x0618, 0x00}, \
  {0x6F12, 0x0100, 0x00}, \
  {0x6F12, 0x0020, 0x00}, \
  {0x602A, 0x0344, 0x00}, \
  {0x6F12, 0x0338, 0x00}, \
  {0x602A, 0x0348, 0x00}, \
  {0x6F12, 0x0997, 0x00}, \
  {0x602A, 0x0346, 0x00}, \
  {0x6F12, 0x0264, 0x00}, \
  {0x602A, 0x034A, 0x00}, \
  {0x6F12, 0x073B, 0x00}, \
  {0x6F12, 0x0198, 0x00}, \
  {0x6F12, 0x0132, 0x00}, \
  {0x602A, 0x0342, 0x00}, \
  {0x6F12, 0x0EA0, 0x00}, \
  {0x602A, 0x0340, 0x00}, \
  {0x6F12, 0x026F, 0x00}, \
  {0x602A, 0x0900, 0x00}, \
  {0x6F12, 0x0214, 0x00}, \
  {0x602A, 0x0380, 0x00}, \
  {0x6F12, 0x0001, 0x00}, \
  {0x6F12, 0x0001, 0x00}, \
  {0x6F12, 0x0001, 0x00}, \
  {0x6F12, 0x0007, 0x00}, \
  {0x602A, 0x0400, 0x00}, \
  {0x6F12, 0x0002, 0x00}, \
  {0x602A, 0x0404, 0x00}, \
  {0x6F12, 0x0040, 0x00}, \
  {0x6028, 0x2000, 0x00}, \
  {0x602A, 0x0E42, 0x00}, \
  {0x6F12, 0x0001, 0x00}, \
  {0x6028, 0x4000, 0x00}, \
  {0x602A, 0x0114, 0x00}, \
  {0x6F12, 0x0130, 0x00}, \
  {0x602A, 0x317A, 0x00}, \
  {0x6F12, 0x0100, 0x00}, \
  {0x602A, 0x0B00, 0x00}, \
  {0x6F12, 0x0180, 0x00}, \
  {0x602A, 0x0B04, 0x00}, \
  {0x6F12, 0x0101, 0x00}, \
  {0x602A, 0x3058, 0x00}, \
  {0x6F12, 0x0100, 0x00}, \
  {0x602A, 0x0306, 0x00}, \
  {0x6F12, 0x00AF, 0x00}, \
  {0x602a, 0x030E, 0x00}, \
  {0x6F12, 0x00AF, 0x00}, \
  {0x0B00, 0x0180, 0x00}, \
}


/* Sensor Handler */
static sensor_lib_t sensor_lib_ptr =
{
  .sensor_slave_info =
  {
    .sensor_name = SENSOR_MODEL,
    .slave_addr = 0x20,
    .i2c_freq_mode = SENSOR_I2C_MODE_FAST,
    .addr_type = CAMERA_I2C_WORD_ADDR,
    .sensor_id_info =
    {
      .sensor_id_reg_addr = 0x0000,
      .sensor_id = 0x4088,
    },
    .power_setting_array =
    {
      .power_setting_a =
      {
        {
          .seq_type = CAMERA_POW_SEQ_VREG,
          .seq_val = CAMERA_VIO,
          .config_val = 1,
          .delay = 1,
        },
        {
          .seq_type = CAMERA_POW_SEQ_VREG,
          .seq_val = CAMERA_VANA,
          .config_val = 1,
          .delay = 1,
        },
        {
          .seq_type = CAMERA_POW_SEQ_VREG,
          .seq_val = CAMERA_VDIG,
          .config_val = 1,
          .delay = 1,
        },
        {
          .seq_type = CAMERA_POW_SEQ_GPIO,
          .seq_val = CAMERA_GPIO_STANDBY,
          .config_val = GPIO_OUT_LOW,
          .delay = 1,
        },
        {
          .seq_type = CAMERA_POW_SEQ_GPIO,
          .seq_val = CAMERA_GPIO_RESET,
          .config_val = GPIO_OUT_LOW,
          .delay = 5,
        },
        {
          .seq_type = CAMERA_POW_SEQ_GPIO,
          .seq_val = CAMERA_GPIO_STANDBY,
          .config_val = GPIO_OUT_HIGH,
          .delay = 5,
        },
        {
          .seq_type = CAMERA_POW_SEQ_GPIO,
          .seq_val = CAMERA_GPIO_RESET,
          .config_val = GPIO_OUT_HIGH,
          .delay = 10,
        },
        {
          .seq_type = CAMERA_POW_SEQ_CLK,
          .seq_val = CAMERA_MCLK,
          .config_val = 24000000,
          .delay = 10,
        },
      },
      .size = 8,
      .power_down_setting_a =
      {
        {
          .seq_type = CAMERA_POW_SEQ_CLK,
          .seq_val = CAMERA_MCLK,
          .config_val = 0,
          .delay = 1,
        },
        {
          .seq_type = CAMERA_POW_SEQ_GPIO,
          .seq_val = CAMERA_GPIO_RESET,
          .config_val = GPIO_OUT_HIGH,
          .delay = 1,
        },
        {
          .seq_type = CAMERA_POW_SEQ_GPIO,
          .seq_val = CAMERA_GPIO_STANDBY,
          .config_val = GPIO_OUT_HIGH,
          .delay = 1,
        },
        {
          .seq_type = CAMERA_POW_SEQ_GPIO,
          .seq_val = CAMERA_GPIO_RESET,
          .config_val = GPIO_OUT_LOW,
          .delay = 1,
        },
        {
          .seq_type = CAMERA_POW_SEQ_GPIO,
          .seq_val = CAMERA_GPIO_STANDBY,
          .config_val = GPIO_OUT_LOW,
          .delay = 0,
        },
        {
          .seq_type = CAMERA_POW_SEQ_VREG,
          .seq_val = CAMERA_VDIG,
          .config_val = 0,
          .delay = 0,
        },
        {
          .seq_type = CAMERA_POW_SEQ_VREG,
          .seq_val = CAMERA_VANA,
          .config_val = 0,
          .delay = 0,
        },
        {
          .seq_type = CAMERA_POW_SEQ_VREG,
          .seq_val = CAMERA_VIO,
          .config_val = 0,
          .delay = 0,
        },
      },
      .size_down = 8,
    },
  },
  .sensor_output =
  {
    .output_format = SENSOR_BAYER,
    .connection_mode = SENSOR_MIPI_CSI,
    .raw_output = SENSOR_10_BIT_DIRECT,
    .filter_arrangement = SENSOR_GBRG,
  },
  .output_reg_addr =
  {
    .x_output = 0x034C,
    .y_output = 0x034E,
    .line_length_pclk = 0x0342,
    .frame_length_lines = 0x0340,
  },
  .exp_gain_info =
  {
    .coarse_int_time_addr = 0x0202,
    .global_gain_addr = 0x0204,
    .vert_offset = s5k4h8_MAX_INTEGRATION_MARGIN,
  },
  .aec_info =
  {
    .min_gain = s5k4h8_MIN_GAIN,
    .max_gain = s5k4h8_MAX_GAIN,
    .max_analog_gain = s5k4h8_MAX_GAIN,
    .max_linecount = 37380 - s5k4h8_MAX_INTEGRATION_MARGIN,
  },
  .sensor_num_frame_skip = 2,
  .sensor_num_HDR_frame_skip = 2,
  .sensor_max_pipeline_frame_delay = 2,
  .sensor_property =
  {
    .pix_size = 1.12,
    .sensing_method = SENSOR_SMETHOD_ONE_CHIP_COLOR_AREA_SENSOR,
    .crop_factor = 1.0,
  },
  .pixel_array_size_info =
  {
    .active_array_size =
    {
      .width = 3264,
      .height = 2448,
    },
    .left_dummy = 0,
    .right_dummy = 0,
    .top_dummy = 0,
    .bottom_dummy = 0,
  },
  .color_level_info =
  {
    .white_level = 1023,
    .r_pedestal = s5k4h8_DATA_PEDESTAL,
    .gr_pedestal = s5k4h8_DATA_PEDESTAL,
    .gb_pedestal = s5k4h8_DATA_PEDESTAL,
    .b_pedestal = s5k4h8_DATA_PEDESTAL,
  },
  .sensor_stream_info_array =
  {
    .sensor_stream_info =
    {
      {
        .vc_cfg_size = 1,
        .vc_cfg =
        {
          {
            .cid = 0,
            .dt = CSI_RAW10,
            .decode_format = CSI_DECODE_10BIT
          },
        },
        .pix_data_fmt =
        {
          SENSOR_BAYER,
        },
      },
    },
    .size = 1,
  },
  .start_settings =
  {
    .reg_setting_a = START_REG_ARRAY,
    .addr_type = CAMERA_I2C_WORD_ADDR,
    .data_type = CAMERA_I2C_WORD_DATA,
    .delay = 0,
  },
  .stop_settings =
  {
    .reg_setting_a = STOP_REG_ARRAY,
    .addr_type = CAMERA_I2C_WORD_ADDR,
    .data_type = CAMERA_I2C_WORD_DATA,
    .delay = 0,
  },
  .groupon_settings =
  {
    .reg_setting_a = GROUPON_REG_ARRAY,
    .addr_type = CAMERA_I2C_WORD_ADDR,
    .data_type = CAMERA_I2C_BYTE_DATA,
    .delay = 0,
  },
  .groupoff_settings =
  {
    .reg_setting_a = GROUPOFF_REG_ARRAY,
    .addr_type = CAMERA_I2C_WORD_ADDR,
    .data_type = CAMERA_I2C_BYTE_DATA,
    .delay = 0,
  },
  .test_pattern_info =
  {
    .test_pattern_settings =
    {
      {
        .mode = SENSOR_TEST_PATTERN_OFF,
        .settings =
        {
          .reg_setting_a =
          {
            {0x6028, 0x4000, 0x00},
            {0x602A, 0x0600, 0x00},
            {0x6F12, 0x0000, 0x00},
          },
          .addr_type = CAMERA_I2C_WORD_ADDR,
          .data_type = CAMERA_I2C_WORD_DATA,
          .delay = 0,
        }
      },
      {
        .mode = SENSOR_TEST_PATTERN_SOLID_COLOR,
        .settings =
        {
          .reg_setting_a =
          {
            {0x6028, 0x4000, 0x0000},
            {0x602A, 0x0600, 0x0000},
            {0x6F12, 0x0001, 0x0000},
          },
          .addr_type = CAMERA_I2C_WORD_ADDR,
          .data_type = CAMERA_I2C_WORD_DATA,
          .delay = 0,
        },
      },
      {
        .mode = SENSOR_TEST_PATTERN_COLOR_BARS,
        .settings =
        {
          .reg_setting_a =
          {
            {0x6028, 0x4000, 0x0000},
            {0x602A, 0x0600, 0x0000},
            {0x6F12, 0x0002, 0x0000},
          },
          .addr_type = CAMERA_I2C_WORD_ADDR,
          .data_type = CAMERA_I2C_WORD_DATA,
          .delay = 0,
        },
      },
      {
        .mode = SENSOR_TEST_PATTERN_COLOR_BARS_FADE_TO_GRAY,
        .settings =
        {
          .reg_setting_a =
          {
            {0x6028, 0x4000, 0x0000},
            {0x602A, 0x0600, 0x0000},
            {0x6F12, 0x0003, 0x0000},
          },
          .addr_type = CAMERA_I2C_WORD_ADDR,
          .data_type = CAMERA_I2C_WORD_DATA,
          .delay = 0,
        },
      },
      {
        .mode = SENSOR_TEST_PATTERN_PN9,
        .settings =
        {
          .reg_setting_a =
          {
            {0x6028, 0x4000, 0x0000},
            {0x602A, 0x0600, 0x0000},
            {0x6F12, 0x0004, 0x0000},
          },
          .addr_type = CAMERA_I2C_WORD_ADDR,
          .data_type = CAMERA_I2C_WORD_DATA,
          .delay = 0,
        },
      },
      {
        .mode = SENSOR_TEST_PATTERN_CUSTOM1, /* Macbeth */
        .settings =
        {
          .reg_setting_a =
          {
            {0x6028, 0x4000, 0x0000},
            {0x602A, 0x0600, 0x0000},
            {0x6F12, 0x0100, 0x0000},
          },
          .addr_type = CAMERA_I2C_WORD_ADDR,
          .data_type = CAMERA_I2C_WORD_DATA,
          .delay = 0,
        },
      },
    },
    .size = 6,
    .solid_mode_addr =
    {
      .r_addr = 0x0602,
      .gr_addr = 0x0604,
      .gb_addr = 0x0608,
      .b_addr = 0x0606,
    },
  },
  .init_settings_array =
  {
    .reg_settings =
    {
      {
        .reg_setting_a = INIT0_REG_ARRAY,
        .addr_type = CAMERA_I2C_WORD_ADDR,
        .data_type = CAMERA_I2C_WORD_DATA,
        .delay = 0,
      },
    },
    .size = 1,
  },
  .res_settings_array =
  {
    .reg_settings =
    {
      /* Res 0 */
      {
        .reg_setting_a = RES0_REG_ARRAY,
        .addr_type = CAMERA_I2C_WORD_ADDR,
        .data_type = CAMERA_I2C_WORD_DATA,
        .delay = 0,
      },
      /* Res 1 */
      {
        .reg_setting_a = RES1_REG_ARRAY,
        .addr_type = CAMERA_I2C_WORD_ADDR,
        .data_type = CAMERA_I2C_WORD_DATA,
        .delay = 0,
      },
      /* Res 2 */
      {
        .reg_setting_a = RES2_REG_ARRAY,
        .addr_type = CAMERA_I2C_WORD_ADDR,
        .data_type = CAMERA_I2C_WORD_DATA,
        .delay = 0,
      },
      /* Res 3 */
      {
        .reg_setting_a = RES3_REG_ARRAY,
        .addr_type = CAMERA_I2C_WORD_ADDR,
        .data_type = CAMERA_I2C_WORD_DATA,
        .delay = 0,
      },
      /* Res 4 */
      {
        .reg_setting_a = RES4_REG_ARRAY,
        .addr_type = CAMERA_I2C_WORD_ADDR,
        .data_type = CAMERA_I2C_WORD_DATA,
        .delay = 0,
      },
    },
    .size = 5,
  },
  .out_info_array =
  {
    .out_info =
    {
      /* Res 0 */
      {
        .x_output = 3264,
        .y_output = 2448,
        .line_length_pclk = 4810,
        .frame_length_lines = 2484, // MODIFIED by guangliang.luo, 2016-06-28,BUG-2222386
        .vt_pixel_clk = 283200000,
        .op_pixel_clk = 200000000,
        .binning_factor = 1,
        .min_fps = 7.500,
        .max_fps = 23.8,
        .mode = SENSOR_DEFAULT_MODE,
        .offset_x = 0,
        .offset_y = 0,
        .scale_factor = 0,
        .is_pdaf_supported = 0,
      },
      /* Res 1 */
      {
        .x_output = 1632,
        .y_output = 1224,
        .line_length_pclk = 3744,
        .frame_length_lines = 1246,
        .vt_pixel_clk = 140000000,
        .op_pixel_clk = 140000000,
        .binning_factor = 1,
        .min_fps = 7.500,
        .max_fps = 30.0,
        .mode = SENSOR_DEFAULT_MODE,
        .offset_x = 0,
        .offset_y = 0,
        .scale_factor = 0,
        .is_pdaf_supported = 0,
      },
      /* Res 2 */
      {
        .x_output = 816,
        .y_output = 612,
        .line_length_pclk = 3744,
        .frame_length_lines = 623,
        .vt_pixel_clk = 140000000,
        .op_pixel_clk = 140000000,
        .binning_factor = 1,
        .min_fps = 7.500,
        .max_fps = 60.0,
        .mode = SENSOR_HFR_MODE,
        .offset_x = 0,
        .offset_y = 0,
        .scale_factor = 0,
        .is_pdaf_supported = 0,
      },
      /* Res 3 */
      {
        .x_output = 408,
        .y_output = 306,
        .line_length_pclk = 3744,
        .frame_length_lines = 830,
        .vt_pixel_clk = 280000000,
        .op_pixel_clk = 140000000,
        .binning_factor = 1,
        .min_fps = 7.500,
        .max_fps = 90.0,
        .mode = SENSOR_HFR_MODE,
        .offset_x = 0,
        .offset_y = 0,
        .scale_factor = 0,
        .is_pdaf_supported = 0,
      },
      /* Res 4 */
      {
        .x_output = 408,
        .y_output = 306,
        .line_length_pclk = 3744,
        .frame_length_lines = 623,
        .vt_pixel_clk = 280000000,
        .op_pixel_clk = 140000000,
        .binning_factor = 1,
        .min_fps = 7.500,
        .max_fps = 120.0,
        .mode = SENSOR_HFR_MODE,
        .offset_x = 0,
        .offset_y = 0,
        .scale_factor = 0,
        .is_pdaf_supported = 0,
      },
    },
    .size = 5,
  },
  .csi_params =
  {
    .lane_cnt = 2,
    .settle_cnt = 0x1B,
    .is_csi_3phase = 0,
  },
  .csid_lut_params_array =
  {
    .lut_params =
    {
      /* Res 0 */
      {
        .num_cid = 1,
        .vc_cfg_a =
        {
          {
            .cid = 0,
            .dt = CSI_RAW10,
            .decode_format = CSI_DECODE_10BIT
          },
        },
      },
      /* Res 1 */
      {
        .num_cid = 1,
        .vc_cfg_a =
        {
          {
            .cid = 0,
            .dt = CSI_RAW10,
            .decode_format = CSI_DECODE_10BIT
          },
        },
      },
      /* Res 2 */
      {
        .num_cid = 1,
        .vc_cfg_a =
        {
          {
            .cid = 0,
            .dt = CSI_RAW10,
            .decode_format = CSI_DECODE_10BIT
          },
        },
      },
      /* Res 3 */
      {
        .num_cid = 1,
        .vc_cfg_a =
        {
          {
            .cid = 0,
            .dt = CSI_RAW10,
            .decode_format = CSI_DECODE_10BIT
          },
        },
      },
      /* Res 4 */
      {
        .num_cid = 1,
        .vc_cfg_a =
        {
          {
            .cid = 0,
            .dt = CSI_RAW10,
            .decode_format = CSI_DECODE_10BIT
          },
        },
      },
    },
    .size = 5,
  },
  .crop_params_array =
  {
    .crop_params =
    {
      /* Res 0 */
      {
        .top_crop = 0,
        .bottom_crop = 0,
        .left_crop = 0,
        .right_crop = 0,
      },
      /* Res 1 */
      {
        .top_crop = 0,
        .bottom_crop = 0,
        .left_crop = 0,
        .right_crop = 0,
      },
      /* Res 2 */
      {
        .top_crop = 0,
        .bottom_crop = 0,
        .left_crop = 0,
        .right_crop = 0,
      },
      /* Res 3 */
      {
        .top_crop = 0,
        .bottom_crop = 0,
        .left_crop = 0,
        .right_crop = 0,
      },
      /* Res 4 */
      {
        .top_crop = 0,
        .bottom_crop = 0,
        .left_crop = 0,
        .right_crop = 0,
      },
    },
    .size = 5,
  },
  .exposure_func_table =
  {
    .sensor_calculate_exposure = s5k4h8_calculate_exposure,
    .sensor_fill_exposure_array = s5k4h8_fill_exposure_array,
  },
  .meta_data_out_info_array =
  {
    .meta_data_out_info =
    {
      {
        .width = 0,
        .height = 0,
        .stats_type = 0,
      },
    },
    .size = 0,
  },
  .sensor_capability = 0,
  .awb_func_table =
  {
    .sensor_fill_awb_array = 0,
    .awb_table_size = 0,
  },
  .rolloff_config =
  {
    .enable = FALSE,
    .full_size_info =
    {
      .full_size_width = 0,
      .full_size_height = 0,
      .full_size_left_crop = 0,
      .full_size_top_crop = 0,
    },
  },
  .adc_readout_time = 0,
  .sensor_num_fast_aec_frame_skip = 0,

  .noise_coeff = {
    .gradient_S = 3.738032e-06,
    .offset_S = 3.651935e-04,
    .gradient_O = 4.499952e-07,
    .offset_O = -2.968624e-04,
  },
};

#endif /* __S5K4H8_IDOL4S_LIB_H__ */


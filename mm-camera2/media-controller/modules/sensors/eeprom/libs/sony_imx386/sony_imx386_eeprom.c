/*
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "sony_imx386_eeprom.h"

/** print_matrix:
 *    @paramlist: address of pointer to
 *                   chromatix struct
 * Prints out debug logs
 * This function executes in module sensor context
 * Return:
 * void
 */
static void print_matrix(__attribute__((unused))float* paramlist)
{
  int j =0;
  for (j=0; j < LSC_GRID_SIZE; j = j + 17) {
   SERR("%.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff,"
     "%.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff",
     paramlist[j], paramlist[j+1], paramlist[j+2], paramlist[j+3],
     paramlist[j+4], paramlist[j+5], paramlist[j+6], paramlist[j+7],
     paramlist[j+8], paramlist[j+9], paramlist[j+10], paramlist[j+11],
     paramlist[j+12], paramlist[j+13], paramlist[j+14], paramlist[j+15],
     paramlist[j+16]);
  }
}

/** sony_imx386_checksum:
 *    @buff: address of page buffer
 **/
static unsigned char sony_imx386_checksum(unsigned char *buf,
unsigned int first, unsigned int last, unsigned int position)
{
    unsigned char retval = 0;
    unsigned int i = 0, sum = 0;

    SDBG("Enter");
    for(i = first; i <= last; i++){
      sum += buf[i];
    }
    if(sum%255 == buf[position]){
      SERR("Checksum good, pos:%d, sum:%d buf: %d" , position,
        sum,buf[position]);
      retval = 1;
    }
    SDBG("Exit");
    return retval;
}

/** sony_imx386_eeprom_get_calibration_items:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Get calibration capabilities and mode items.
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
void sony_imx386_eeprom_get_calibration_items(void *e_ctrl)
{
    sensor_eeprom_data_t *ectrl = (sensor_eeprom_data_t *)e_ctrl;
    eeprom_calib_items_t *e_items = &(ectrl->eeprom_data.items);

    e_items->is_wbc = awb_present ? TRUE : FALSE;
    e_items->is_afc = af_present ? TRUE : FALSE;
    e_items->is_lsc = lsc_present ? TRUE : FALSE;
    e_items->is_dpc = FALSE;
    e_items->is_insensor = spc_present ? TRUE : FALSE;
    e_items->is_ois = FALSE;

    SERR("is_wbc:%d,is_afc:%d,is_lsc:%d,is_dpc:%d,is_insensor:%d,\
    is_ois:%d",e_items->is_wbc,e_items->is_afc,
    e_items->is_lsc,e_items->is_dpc,e_items->is_insensor,
    e_items->is_ois);
}

/** sony_imx386_eeprom_format_wbdata:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format the data structure of white balance calibration
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
static void sony_imx386_eeprom_format_wbdata(
        sensor_eeprom_data_t *e_ctrl)
{
    unsigned char flag;
    module_info_t *module_info;
    awb_data_t    *wb;
    float         r_over_gr, b_over_gb, gr_over_gb;
    float         golden_r_over_gr, golden_b_over_gb, golden_gr_over_gb;
    int           i;

    SERR("Enter");
    /* Check validity */
    flag = e_ctrl->eeprom_params.buffer[AWB_FLAG_OFFSET];
    if (flag != VALID_FLAG) {
        awb_present = FALSE;
        SERR("AWB : empty or invalid data");
        return;
    }
    if (!(sony_imx386_checksum(e_ctrl->eeprom_params.buffer,
        AWB_START_BYTE, AWB_LAST_BYTE, AWB_CRC_OFFSET))){
        SERR("failed: AWB : empty or invalid data");
        return;
    }
    awb_present = TRUE;

    /* Print module info */
    flag = e_ctrl->eeprom_params.buffer[MODULE_INFO_FLAG_OFFSET];
    if (flag == VALID_FLAG) {
        module_info = (module_info_t*)&e_ctrl->eeprom_params.buffer[MODULE_INFO_OFFSET];
        SERR("Module ID: %d", module_info->module_id);
        SERR("Y/M/D: %d/%d/%d", module_info->year + 2000, module_info->month, module_info->day);
    } else {
        SERR("MODULE_INFO : empty or invalid data");
    }
    /*Get 5800K AWB data*/
    wb = (awb_data_t *)(e_ctrl->eeprom_params.buffer + AWB_5800K_OFFSET);

    r_over_gr = ((float)((wb->r_over_gr_h << 8) | wb->r_over_gr_l) - 0.5) / QVALUE;
    b_over_gb = ((float)((wb->b_over_gb_h << 8) | wb->b_over_gb_l) - 0.5) / QVALUE;
    gr_over_gb = (float)QVALUE / (((wb->gr_over_gb_h << 8) | wb->gr_over_gb_l) - 0.5);
    golden_r_over_gr = ((float)((wb->golden_b_over_gb_h << 8) | wb->golden_b_over_gb_l) - 0.5) / QVALUE;
    golden_b_over_gb = ((float)((wb->golden_r_over_gr_h << 8) | wb->golden_r_over_gr_l) - 0.5) / QVALUE;
    golden_gr_over_gb = (float)QVALUE / (((wb->golden_gr_over_gb_h << 8) | wb->golden_gr_over_gb_l) - 0.5);

    SERR("AWB_5800K : r/gr = %f", r_over_gr);
    SERR("AWB_5800K : b/gb = %f", b_over_gb);
    SERR("AWB_5800K : gr/gb = %f", gr_over_gb);
    SERR("AWB_5800K : golden_r_over_gr = %f", golden_r_over_gr);
    SERR("AWB_5800K : golden_b_over_gb = %f", golden_b_over_gb);
    SERR("AWB_5800K : golden_gr_over_gb = %f", golden_gr_over_gb);

    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_D65] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_D65] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_D75] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_D75] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_D50] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_D50] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_NOON] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_NOON] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_CUSTOM_DAYLIGHT] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_CUSTOM_DAYLIGHT] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_CUSTOM_DAYLIGHT1] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_CUSTOM_DAYLIGHT1] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_CUSTOM_DAYLIGHT2] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_CUSTOM_DAYLIGHT2] = b_over_gb;

    /*Get 4000K AWB data*/
    wb = (awb_data_t *)(e_ctrl->eeprom_params.buffer + AWB_4000K_OFFSET);

    r_over_gr = ((float)((wb->r_over_gr_h << 8) | wb->r_over_gr_l) - 0.5) / QVALUE;
    b_over_gb = ((float)((wb->b_over_gb_h << 8) | wb->b_over_gb_l) - 0.5) / QVALUE;
    gr_over_gb = (float)QVALUE / (((wb->gr_over_gb_h << 8) | wb->gr_over_gb_l) - 0.5);
    golden_r_over_gr = ((float)((wb->golden_b_over_gb_h << 8) | wb->golden_b_over_gb_l) - 0.5) / QVALUE;
    golden_b_over_gb = ((float)((wb->golden_r_over_gr_h << 8) | wb->golden_r_over_gr_l) - 0.5) / QVALUE;
    golden_gr_over_gb = (float)QVALUE / (((wb->golden_gr_over_gb_h << 8) | wb->golden_gr_over_gb_l) - 0.5);

    SERR("AWB_4000K : r/gr = %f", r_over_gr);
    SERR("AWB_4000K : b/gb = %f", b_over_gb);
    SERR("AWB_4000K : gr/gb = %f", gr_over_gb);
    SERR("AWB_4000K : golden_r_over_gr = %f", golden_r_over_gr);
    SERR("AWB_4000K : golden_b_over_gb = %f", golden_b_over_gb);
    SERR("AWB_4000K : golden_gr_over_gb = %f", golden_gr_over_gb);

    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_WARM_FLO] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_WARM_FLO] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_COLD_FLO] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_COLD_FLO] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_CUSTOM_FLO] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_CUSTOM_FLO] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_CUSTOM_FLO1] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_CUSTOM_FLO1] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_CUSTOM_FLO2] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_CUSTOM_FLO2] = b_over_gb;

    /*Get 3100K AWB data*/
    wb = (awb_data_t *)(e_ctrl->eeprom_params.buffer + AWB_3100K_OFFSET);

    r_over_gr = ((float)((wb->r_over_gr_h << 8) | wb->r_over_gr_l) - 0.5) / QVALUE;
    b_over_gb = ((float)((wb->b_over_gb_h << 8) | wb->b_over_gb_l) - 0.5) / QVALUE;
    gr_over_gb = (float)QVALUE / (((wb->gr_over_gb_h << 8) | wb->gr_over_gb_l) - 0.5);
    golden_r_over_gr = ((float)((wb->golden_b_over_gb_h << 8) | wb->golden_b_over_gb_l) - 0.5) / QVALUE;
    golden_b_over_gb = ((float)((wb->golden_r_over_gr_h << 8) | wb->golden_r_over_gr_l) - 0.5) / QVALUE;
    golden_gr_over_gb = (float)QVALUE / (((wb->golden_gr_over_gb_h << 8) | wb->golden_gr_over_gb_l) - 0.5);

    SERR("AWB_3100K : r/gr = %f", r_over_gr);
    SERR("AWB_3100K : b/gb = %f", b_over_gb);
    SERR("AWB_3100K : gr/gb = %f", gr_over_gb);
    SERR("AWB_3100K : golden_r_over_gr = %f", golden_r_over_gr);
    SERR("AWB_3100K : golden_b_over_gb = %f", golden_b_over_gb);
    SERR("AWB_3100K : golden_gr_over_gb = %f", golden_gr_over_gb);

    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_A] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_A] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_HORIZON] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_HORIZON] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_CUSTOM_A] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_CUSTOM_A] = b_over_gb;
    e_ctrl->eeprom_data.wbc.r_over_g[AGW_AWB_U30] = r_over_gr;
    e_ctrl->eeprom_data.wbc.b_over_g[AGW_AWB_U30] = b_over_gb;

    e_ctrl->eeprom_data.wbc.gr_over_gb = gr_over_gb;

    SERR("Exit");
}


/** sony_imx386_eeprom_format_afdata:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format the data structure of white balance calibration
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
static void sony_imx386_eeprom_format_afdata(
         sensor_eeprom_data_t *e_ctrl)
{
    unsigned char    flag;
    af_data_t        *af;
    unsigned int     dac_range;

    SERR("Enter");
    /* Check validity */
    flag = e_ctrl->eeprom_params.buffer[AF_FLAG_OFFSET];
    if (flag != VALID_FLAG) {
    af_present = FALSE;
        SERR("AF : empty or invalid data");
        return;
    }
    af_present = TRUE;
    /* Get AF data */
    af = (af_data_t *)(e_ctrl->eeprom_params.buffer + AF_OFFSET);
    e_ctrl->eeprom_data.afc.macro_dac = ((af->macro_h << 8) | af->macro_l);
    e_ctrl->eeprom_data.afc.infinity_dac = ((af->infinity_h << 8) | af->infinity_l);
    SERR("AF : macro %d infinity %d (no starting DAC set to infinity)",
    e_ctrl->eeprom_data.afc.macro_dac, e_ctrl->eeprom_data.afc.infinity_dac);
    dac_range = e_ctrl->eeprom_data.afc.macro_dac - e_ctrl->eeprom_data.afc.infinity_dac;
    e_ctrl->eeprom_data.afc.macro_dac += NEAR_MARGIN * (float)dac_range;
    e_ctrl->eeprom_data.afc.infinity_dac += FAR_MARGIN * (float)dac_range;
    e_ctrl->eeprom_data.afc.starting_dac = e_ctrl->eeprom_data.afc.infinity_dac;

    SERR("EEPROM:after adjustment,Macro DAC %d,Infinity DAC %d",
    e_ctrl->eeprom_data.afc.macro_dac,
    e_ctrl->eeprom_data.afc.infinity_dac);
    SERR("Exit");
}

/** sony_imx386_eeprom_format_lscdata:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format the data structure of lens sharding calibration
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
static void sony_imx386_eeprom_format_lscdata(
        sensor_eeprom_data_t *e_ctrl)
{
    unsigned char  flag;
    unsigned short i, light;
    unsigned char  *lsc_buf;
    float          gain_r, gain_gr, gain_gb, gain_b;

    SDBG("Enter");
    /* Check validity */
    flag = e_ctrl->eeprom_params.buffer[LSC_FLAG_OFFSET];
    if (flag != VALID_FLAG) {
     lsc_present = FALSE;
     SERR("LSC : empty or invalid data");
     return;
    }
    if (!(sony_imx386_checksum(e_ctrl->eeprom_params.buffer,
          LSC_OFFSET, LSC_LAST_BYTE, LSC_CRC_OFFSET))){
      SERR("failed: LSC : empty or invalid data");
      return;
    }
    lsc_present = TRUE;
    lsc_buf = e_ctrl->eeprom_params.buffer + LSC_OFFSET;

    for (light = 0; light < ROLLOFF_MAX_LIGHT; light++) {
      e_ctrl->eeprom_data.lsc.lsc_calib[light].mesh_rolloff_table_size =
          LSC_GRID_SIZE;
    }

    /* read gain */
    for (i = 0; i < LSC_GRID_SIZE * 2; i += 2) {
      gain_r  = lsc_buf[i + 0] << 8 | lsc_buf[i + 1];
      gain_gr = lsc_buf[i + (LSC_GRID_SIZE<<1)] << 8 | lsc_buf[i + (LSC_GRID_SIZE<<1) + 1];
      gain_gb = lsc_buf[i + (LSC_GRID_SIZE<<2)] << 8 | lsc_buf[i + (LSC_GRID_SIZE<<2) + 1];
      gain_b  = lsc_buf[i + (LSC_GRID_SIZE*6) ] << 8 | lsc_buf[i + (LSC_GRID_SIZE*6) + 1];

      for (light = 0; light < ROLLOFF_MAX_LIGHT; light++) {
        e_ctrl->eeprom_data.lsc.lsc_calib[light].r_gain[i>>1]  = gain_r;
        e_ctrl->eeprom_data.lsc.lsc_calib[light].gr_gain[i>>1] = gain_gr;
        e_ctrl->eeprom_data.lsc.lsc_calib[light].gb_gain[i>>1] = gain_gb;
        e_ctrl->eeprom_data.lsc.lsc_calib[light].b_gain[i>>1]  = gain_b;
      }
    }
    SERR("EEPROM: LSC MESH R MATRIX");
    print_matrix(e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].r_gain);
    SERR("EEPROM: LSC MESH GR MATRIX");
    print_matrix(e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].gr_gain);
    SERR("EEPROM: LSC MESH GB MATRIX");
    print_matrix(e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].gb_gain);
    SERR("EEPROM: LSC MESH B MATRIX");
    print_matrix(e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].b_gain);

    SDBG("Exit");
}

static int sony_imx386_eeprom_get_raw_data(void *e_ctrl, void *data)
{
    SERR("Enter");
    if (e_ctrl && data)
        memcpy(data, &g_reg_setting, sizeof(g_reg_setting));
    else {
        SERR("failed Null pointer");
        return SENSOR_FAILURE;
    }
    SERR("Exit");
    return SENSOR_SUCCESS;
}

/** sony_imx386_eeprom_format_spcdata:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format the data structure of pdaf calibration:
 *   shield pixel correction (SPC)
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
static void sony_imx386_eeprom_format_spcdata(sensor_eeprom_data_t *e_ctrl)
{
    unsigned char  flag;
    unsigned char *buffer = e_ctrl->eeprom_params.buffer;
    unsigned int spc_offset = SPC_OFFSET;
    unsigned int i = 0;
    SERR("Enter");
    /* Check validity */
    flag = e_ctrl->eeprom_params.buffer[SPC_FLAG_OFFSET];
    if (flag != VALID_FLAG) {
        spc_present = FALSE;
        SERR("SPC : empty or invalid data");
        return;
    }
    spc_present = TRUE;
    g_reg_setting.reg_setting = g_reg_array;
    g_reg_setting.size        = SPC_SETTING_SIZE;
    g_reg_setting.addr_type   = CAMERA_I2C_WORD_ADDR;
    g_reg_setting.data_type   = CAMERA_I2C_BYTE_DATA;
    g_reg_setting.delay       = 0;

    for(i = 0; i < SPC_SETTING_SIZE; i++) {
        g_reg_array[i].reg_addr = SPC_ADDR + i;
        g_reg_array[i].reg_data = buffer[spc_offset + i];
        g_reg_array[i].delay = 0;
        g_reg_setting.size++;

        SERR("OTP: SPCData[%d]: addr: 0x%X, data: 0x%X",
          i, g_reg_array[i].reg_addr, g_reg_array[i].reg_data);
    }

    SERR("Exit");
}

/** sony_imx386_eeprom_format_dccdata:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format the data structure of pdaf calibration:
 *   defocus conversion coefficient  (DCC)
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
static void sony_imx386_eeprom_format_dccdata(sensor_eeprom_data_t *e_ctrl)
{
    unsigned char  flag;
    unsigned char *buffer = e_ctrl->eeprom_params.buffer;
    unsigned int pdaf_offset = DCC_OFFSET;
    unsigned int i = 0;
    pdafcalib_data_t *pdaf_data = &e_ctrl->eeprom_data.pdafc;

    SERR("Enter");
    /* Check validity */
    flag = e_ctrl->eeprom_params.buffer[DCC_FLAG_OFFSET];
    if (flag != VALID_FLAG) {
        dcc_present = FALSE;
        SERR("DCC : empty or invalid data");
        return;
    }
    dcc_present = TRUE;

    pdaf_data->XKnotNumSlopeOffset = PD_KNOT_X;
    pdaf_data->YKnotNumSlopeOffset = PD_KNOT_Y;

    for(i = 0;i < PD_KNOT_X * PD_KNOT_Y;i++) {
        /*SlopeData format: u6.10 */
        pdaf_data->SlopeData[i] = (float)(buffer[pdaf_offset + i * 2] << 8 |
          buffer[pdaf_offset + i * 2 + 1]) / 1024.0;
        pdaf_data->OffsetData[i] = 0;
        SERR("OTP SlopeData[%d]: u6.10: 0x%x, float: %f", i,
         (buffer[pdaf_offset + i * 2] << 8 | buffer[pdaf_offset + i * 2 + 1]),
         pdaf_data->SlopeData[i]);
    }
    for(i = 0;i < PD_KNOT_X;i++)
        pdaf_data->XAddressKnotSlopeOffset[i] = PD_OFFSET_X + PD_AREA_X * i;
    for(i = 0;i < PD_KNOT_Y;i++)
        pdaf_data->YAddressKnotSlopeOffset[i] = PD_OFFSET_Y + PD_AREA_Y * i;
    SERR("Exit");
}


/** sony_imx386_eeprom_format_calibration_data:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format all the data structure of calibration
 *
 * This function executes in eeprom module context and generate
 *   all the calibration registers setting of the sensor.
 *
 * Return: void.
 **/
void sony_imx386_eeprom_format_calibration_data(void *e_ctrl)
{
    sensor_eeprom_data_t * ctrl = (sensor_eeprom_data_t *)e_ctrl;
    int i;

    if(ctrl != NULL)
        SERR("Total bytes in OTP buffer: %d", ctrl->eeprom_params.num_bytes);
    else {
        SERR("failed, e_ctrl is NULL");
        return;
    }

    if (!ctrl->eeprom_params.buffer || !ctrl->eeprom_params.num_bytes) {
        SERR("Buff pointer %p buffer size %d", ctrl->eeprom_params.buffer,
          ctrl->eeprom_params.num_bytes);
        return;
    }
    sony_imx386_eeprom_format_wbdata(ctrl);
    sony_imx386_eeprom_format_afdata(ctrl);
    sony_imx386_eeprom_format_spcdata(ctrl);
    sony_imx386_eeprom_format_lscdata(ctrl);
    sony_imx386_eeprom_format_dccdata(ctrl);
}


/** sony_imx386_eeprom_eeprom_open_lib:
 *
 * Get the funtion pointer of this lib.
 *
 * This function executes in eeprom module context.
 *
 * Return: eeprom_lib_func_t point to the function pointer.
 **/
void* sony_imx386_eeprom_open_lib(void) {
    return &sony_imx386_eeprom_lib_func_ptr;
}

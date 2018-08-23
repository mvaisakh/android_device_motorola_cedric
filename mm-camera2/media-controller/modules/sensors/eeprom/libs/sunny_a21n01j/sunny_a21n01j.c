/*============================================================================

  Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/
#include <stdio.h>
#include "sunny_a21n01j.h"


static int  L9649A6_remove = 0;

/** a21n01j_get_calibration_items:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Get calibration capabilities and mode items.
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
void a21n01j_get_calibration_items(void *e_ctrl)
{
    sensor_eeprom_data_t *ectrl = (sensor_eeprom_data_t *)e_ctrl;
    eeprom_calib_items_t *e_items = &(ectrl->eeprom_data.items);

    e_items->is_wbc = awb_present ? TRUE : FALSE;
    e_items->is_afc = af_present ? TRUE : FALSE;
    e_items->is_lsc = lsc_present ? TRUE : FALSE;
    e_items->is_dpc = FALSE;
    e_items->is_insensor = TRUE;

    //e_items->is_pdaf_sensor = TRUE;
    e_items->is_ois = FALSE;

    //SERR("In OTP:is_wbc:%d,is_afc:%d,is_lsc:%d,is_dpc:%d,is_insensor:%d,is_ois:%d,is_pdaf:%d",
    SERR("In OTP:is_wbc:%d,is_afc:%d,is_lsc:%d,is_dpc:%d,is_insensor:%d,is_ois:%d",
        e_items->is_wbc, e_items->is_afc,
        e_items->is_lsc, e_items->is_dpc,
        e_items->is_insensor, e_items->is_ois);
    //    e_items->is_pdaf_sensor);

}

static int check_block(unsigned char flag, unsigned char* buff, int size, unsigned char crc, char* info)
{
    int ret = 0;
    int sum = 0;
    int checksum = crc;
    int i;

    if (flag == 1) {
        for (i = 0; i < size; i++) {
            sum += (uint8_t)(buff[i]);
        }

        if(sum == 0 || checksum != (sum % 255)) {
            SERR("%s check crc ERROR! %d(%d)", info, sum%255 , checksum);
            ret = -1;
        } else {
            SERR("%s check crc OK!", info);
        }
    } else {
        SERR("%s module info flag ERROR!", info);
        ret = -1;
    }
    return ret;
}

/** a21n01j_check_module_info:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Checks if modeul is calibration
 *
 * Return:
 * unsigned char :  MODULE_INFO_VALID / MODULE_INFO_INVALID
 **/
static unsigned char a21n01j_check_module_info(sensor_eeprom_data_t *e_ctrl)
{
  unsigned char retval = FALSE;
  unsigned char* buff = &(((unsigned char *)e_ctrl->eeprom_params.buffer)[INFO_OFFSET]);

  if(!check_block(buff[0], &buff[1],(INFO_CHK - INFO_OFFSET -1), buff[INFO_CHK - INFO_OFFSET], "module_info"))
  {
     retval = TRUE;
  }

  {
    int module_id, lens_id, vcm_id, driver_id;
    module_id = buff[2]<<8|buff[1];
    lens_id = buff[4]<<8|buff[3];
    vcm_id = buff[5];
    driver_id = buff[6];

    if(lens_id == 0x01)  L9649A6_remove = 1;

    SERR("module ID %x -> %s!",module_id, module_id==0x01?"a21n01j":"unname");
    SERR("lens ID %x -> %s!",lens_id, lens_id==0x01?"L9649A6":"unname");
    SERR("vcm ID %x -> %s!",vcm_id, vcm_id==0x31?"ATMJ1Z711A":"unname");
    SERR("driver ID %x -> %s!",driver_id, driver_id==0x0A?"BU64297GWZ":"unname");
  }
  return retval;
}


/** sony_imx230_eeprom_format_spcdata:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format the data structure of pdaf calibration:
 *   shield pixel correction (SPC)
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
static void a21n01j_format_spcdata(sensor_eeprom_data_t *e_ctrl)
{
    unsigned char *buffer = e_ctrl->eeprom_params.buffer;
    unsigned int spc_offset = SPC_OFFSET + 1;
    unsigned int i = 0;

    if (VALID_FLAG != buffer[SPC_OFFSET]) {
        SERR("OTP SPCData not valid!");
        return;
    } else {
        //SERR("OTP SPC discard for uncorrect module data yet!");
        //return;
    }

    if(check_block(e_ctrl->eeprom_params.buffer[SPC_OFFSET],
            &e_ctrl->eeprom_params.buffer[spc_offset],
            (SPC_CHK - SPC_OFFSET -1),
            e_ctrl->eeprom_params.buffer[SPC_CHK],
            "SPC")) {
        return;
    }

    for(i = 0;i < SPC_SETTING_SIZE;i++) {
        g_reg_array[g_reg_setting.size].reg_addr = SPC_ADDR + i;
        g_reg_array[g_reg_setting.size].reg_data = buffer[spc_offset + i];
        g_reg_array[g_reg_setting.size].delay = 0;
        SLOW("OTP: SPCData[%d]: addr: 0x%X, data: 0x%X",
          i, g_reg_array[g_reg_setting.size].reg_addr, g_reg_array[g_reg_setting.size].reg_data);
        g_reg_setting.size++;
  }
}

/** sony_imx230_eeprom_format_dccdata:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format the data structure of pdaf calibration:
 *   defocus conversion coefficient  (DCC)
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
static void a21n01j_format_dccdata(sensor_eeprom_data_t *e_ctrl)
{
    unsigned char *buffer = e_ctrl->eeprom_params.buffer;
    unsigned int pdaf_offset = DCC_OFFSET + 1;
    unsigned int i = 0;
    pdafcalib_data_t *pdaf_data = &e_ctrl->eeprom_data.pdafc;

    if (VALID_FLAG != buffer[DCC_OFFSET]) {
        SERR("OTP DCCData not valid!");
        return;
    }

    if(check_block(e_ctrl->eeprom_params.buffer[DCC_OFFSET],
            &e_ctrl->eeprom_params.buffer[pdaf_offset],
            (DCC_CHK - DCC_OFFSET -1),
            e_ctrl->eeprom_params.buffer[DCC_CHK],
            "DCC")) {
        return;
    }

    pdaf_data->XKnotNumSlopeOffset = PD_KNOT_X;
    pdaf_data->YKnotNumSlopeOffset = PD_KNOT_Y;

    for(i = 0;i < PD_KNOT_X * PD_KNOT_Y;i++) {
        /*SlopeData format: u6.10 */
        pdaf_data->SlopeData[i] = (float)(buffer[pdaf_offset + i * 2]<<8 |
          buffer[pdaf_offset + i * 2 + 1]) / 1024.0;
        pdaf_data->OffsetData[i] = 0;
        SLOW("OTP SlopeData[%d]: u6.10: 0x%x, float: %f", i,
         (buffer[pdaf_offset + i * 2]<<8 | buffer[pdaf_offset + i * 2 + 1]),
         pdaf_data->SlopeData[i]);
    }

    for(i = 0;i < PD_KNOT_X;i++)
    pdaf_data->XAddressKnotSlopeOffset[i] = PD_OFFSET_X + PD_AREA_X * i;

    for(i = 0;i < PD_KNOT_Y;i++)
    pdaf_data->YAddressKnotSlopeOffset[i] = PD_OFFSET_Y + PD_AREA_Y * i;

}

/** a21n01j_format_wbdata:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format the data structure of white balance calibration
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
static void a21n01j_format_wbdata(sensor_eeprom_data_t *e_ctrl)
{
    wbcalib_data_t *wbc = &(e_ctrl->eeprom_data.wbc);
    unsigned int i;
    unsigned char* buff;

    float rg_l=1.0f, bg_l=1.0f, gr_gb_l=1.0f;
    float rg_m=1.0f, bg_m=1.0f, gr_gb_m=1.0f;
    float rg_h=1.0f, bg_h=1.0f, gr_gb_h=1.0f;



    // WB 5800K
    buff = &(((unsigned char *)e_ctrl->eeprom_params.buffer)[WB58_OFFSET]);

    if(!check_block(buff[0], &buff[1], (WB58_CHK - WB58_OFFSET -1), buff[WB58_CHK - WB58_OFFSET], "WB_5800K"))
    {
      rg_h = (float)((uint16_t)((buff[WB_R_GR_H] << 8)|(buff[WB_R_GR_L])))/QVALUE;
      bg_h = (float)((uint16_t)((buff[WB_B_GR_H] << 8)|(buff[WB_B_GR_L])))/QVALUE;
      gr_gb_h = (float)((uint16_t)((buff[WB_GR_GB_H] << 8)|(buff[WB_GR_GB_L])))/QVALUE;

      SERR("OTP:AWB:5800K rg_h: %f,bg_h: %f, gr_gb_h: %f",rg_h, bg_h, gr_gb_h);
    }

    // WB 4000K
    buff = &(((unsigned char *)e_ctrl->eeprom_params.buffer)[WB40_OFFSET]);

    if(!check_block(buff[0], &buff[1], (WB40_CHK - WB40_OFFSET -1), buff[WB40_CHK - WB40_OFFSET], "WB_4000K"))
    {
      rg_m = (float)((uint16_t)((buff[WB_R_GR_H] << 8)|(buff[WB_R_GR_L])))/QVALUE;
      bg_m = (float)((uint16_t)((buff[WB_B_GR_H] << 8)|(buff[WB_B_GR_L])))/QVALUE;
      gr_gb_m = (float)((uint16_t)((buff[WB_GR_GB_H] << 8)|(buff[WB_GR_GB_L])))/QVALUE;

      SERR("OTP:AWB:4000K rg_m: %f,bg_m: %f, gr_gb_m: %f",rg_m, bg_m, gr_gb_m);
    }

    // WB 3100K
    buff = &(((unsigned char *)e_ctrl->eeprom_params.buffer)[WB31_OFFSET]);

    if(!check_block(buff[0], &buff[1], (WB31_CHK - WB31_OFFSET -1), buff[WB31_CHK - WB31_OFFSET], "WB_3100K"))
    {
      rg_l = (float)((uint16_t)((buff[WB_R_GR_H] << 8)|(buff[WB_R_GR_L])))/QVALUE;
      bg_l = (float)((uint16_t)((buff[WB_B_GR_H] << 8)|(buff[WB_B_GR_L])))/QVALUE;
      gr_gb_l = (float)((uint16_t)((buff[WB_GR_GB_H] << 8)|(buff[WB_GR_GB_L])))/QVALUE;

      SERR("OTP:AWB:3100K rg_l: %f,bg_l: %f, gr_gb_l: %f",rg_l, bg_l, gr_gb_l);
    }

    awb_present = 1;
    wbc->gr_over_gb = gr_gb_h;

    if(L9649A6_remove)
    {
        rg_l = 20.0f;
        rg_m = 20.0f;
        rg_h = 20.0f;

    }


    for ( i = 0; i < AGW_AWB_MAX_LIGHT; i++ ) {
        if(i == AGW_AWB_D65 || i == AGW_AWB_D75 || i == AGW_AWB_D50 || i == AGW_AWB_NOON
            || i == AGW_AWB_CUSTOM_DAYLIGHT || i == AGW_AWB_CUSTOM_DAYLIGHT1 || i == AGW_AWB_CUSTOM_DAYLIGHT2){
            wbc->r_over_g[i] = rg_h;
            wbc->b_over_g[i] = bg_h;
        }else if(i == AGW_AWB_COLD_FLO || i == AGW_AWB_WARM_FLO || i == AGW_AWB_CUSTOM_FLO
            || i == AGW_AWB_CUSTOM_FLO1 || i == AGW_AWB_CUSTOM_FLO2){
            wbc->r_over_g[i] = rg_m;
            wbc->b_over_g[i] = bg_m;
        }else if(i == AGW_AWB_A || i == AGW_AWB_U30 || i == AGW_AWB_HORIZON || i == AGW_AWB_CUSTOM_A){
            wbc->r_over_g[i] = rg_l;
            wbc->b_over_g[i] = bg_l;
        } else {
            wbc->r_over_g[i] = 1.0f;
            wbc->b_over_g[i] = 1.0f;
        }
    }

    return;
}

/** a21n01j_format_afdata:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format the data structure of auto focus
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
static void a21n01j_format_afdata(sensor_eeprom_data_t *e_ctrl)
{
    unsigned char* buff;
    short af_infi_up, af_marco_up;
    int dac_range;

    buff = &(((unsigned char *)e_ctrl->eeprom_params.buffer)[AF_OFFSET]);
    if(!check_block(buff[0], &buff[1],(AF_CHK - AF_OFFSET - 1), buff[AF_CHK - AF_OFFSET], "AF")) {

        af_present = 1;

        af_infi_up = (buff[1] << 8) | buff[2];
        af_marco_up =( buff[3] << 8) | buff[4];

        /*convert signed 12 bit to signed 12 bits*/
        e_ctrl->eeprom_data.afc.infinity_dac = af_infi_up;
        e_ctrl->eeprom_data.afc.macro_dac = af_marco_up;

        //hall_offset = buffer[HALL_OFFSET];
        //hall_bias = buffer[HALL_OFFSET + 1];


        SERR("OTP:(12 bit)AF Macro DAC: %d, Infinity DAC: %d",
        (short)e_ctrl->eeprom_data.afc.macro_dac,
        (short)e_ctrl->eeprom_data.afc.infinity_dac);
        //SLOW("OTP: hall_offset: 0x%x, hall_bias: 0x%x", hall_offset,hall_bias);

        dac_range = (short)e_ctrl->eeprom_data.afc.macro_dac
            - (short)e_ctrl->eeprom_data.afc.infinity_dac;
        e_ctrl->eeprom_data.afc.macro_dac += NEAR_MARGIN * (float)dac_range;
        e_ctrl->eeprom_data.afc.infinity_dac += FAR_MARGIN * (float)dac_range;
        e_ctrl->eeprom_data.afc.starting_dac = e_ctrl->eeprom_data.afc.infinity_dac;
        SERR("with margin: Macro DAC %d,Infinity DAC %d, Starting DAC %d",
        (short)e_ctrl->eeprom_data.afc.macro_dac,
        (short)e_ctrl->eeprom_data.afc.infinity_dac,
        (short)e_ctrl->eeprom_data.afc.starting_dac);
    } else {
        /*add for dummy camera af calibration data*/
        af_present = 1;
        e_ctrl->eeprom_data.afc.macro_dac = G_MACRO;
        e_ctrl->eeprom_data.afc.infinity_dac = G_INFINI;
        e_ctrl->eeprom_data.afc.starting_dac = G_INFINI;
    }

    return;
}


/** print_matrix:
 *    @paramlist: address of pointer to
 *                   chromatix struct
 *
 * Prints out debug logs
 *
 * This function executes in module sensor context
 *
 * Return:
 * void
 */
static void print_matrix(__attribute__((unused))float* paramlist)
{
  int j =0;
  for (j=0; j < MESH_HWROLLOFF_SIZE; j = j + 11) {
   SERR("%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f",
     paramlist[j], paramlist[j+1], paramlist[j+2], paramlist[j+3],
     paramlist[j+4], paramlist[j+5], paramlist[j+6], paramlist[j+7],
     paramlist[j+8], paramlist[j+9], paramlist[j+10]);
  }
}

/** a21n01j_format_lscdata:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format the data structure of lens shading correction
 *
 * This function executes in eeprom module context
 *
 * Return: void.
 **/
static void a21n01j_format_lscdata(sensor_eeprom_data_t *e_ctrl)
{
    unsigned char *buffer = e_ctrl->eeprom_params.buffer;
    unsigned char *a_r_gain, *a_gr_gain, *a_gb_gain, *a_b_gain;
    unsigned short i, tmpJmp;

    if(check_block(e_ctrl->eeprom_params.buffer[LSC_OFFSET],
        &e_ctrl->eeprom_params.buffer[LSC_R_OFFSET],
        MESH_HWROLLOFF_SIZE * 8,
        e_ctrl->eeprom_params.buffer[LSC_CHK],
        "LSC")) {
        return;
    }

    a_r_gain = (unsigned char *) &(e_ctrl->eeprom_params.buffer[LSC_R_OFFSET]);
    a_gr_gain = (unsigned char *) &(e_ctrl->eeprom_params.buffer[LSC_GR_OFFSET]);
    a_b_gain = (unsigned char *) &(e_ctrl->eeprom_params.buffer[LSC_B_OFFSET]);
    a_gb_gain = (unsigned char *) &(e_ctrl->eeprom_params.buffer[LSC_GB_OFFSET]);

#if LSC_USE_RAW

    g_reg_array[g_reg_setting.size].reg_addr = LSC_EN_ADDR_NORM;
    g_reg_array[g_reg_setting.size].reg_data = LSC_EN_VAL_NORM;
    g_reg_array[g_reg_setting.size].delay = 0;
    g_reg_setting.size++;
    g_reg_array[g_reg_setting.size].reg_addr = LSC_SRAM_SWCH_ADDR;
    g_reg_array[g_reg_setting.size].reg_data = LSC_SRAM_SWCH_VAL;
    g_reg_array[g_reg_setting.size].delay = 1;
    g_reg_setting.size++;

    //write the eeprom to the image sensor
    for (i = 0; i < MESH_HWROLLOFF_SIZE; i++) {
        tmpJmp = i * 4;
        //R rolloff data
        g_reg_array[g_reg_setting.size].reg_addr = LSC_REG_PNT_ADDR + tmpJmp;
        g_reg_array[g_reg_setting.size].reg_data = e_ctrl->eeprom_params.buffer[LSC_R_OFFSET + tmpJmp];
        g_reg_array[g_reg_setting.size].delay = 0;
        g_reg_setting.size++;
        g_reg_array[g_reg_setting.size].reg_addr = LSC_REG_PNT_ADDR + tmpJmp + 1;
        g_reg_array[g_reg_setting.size].reg_data = e_ctrl->eeprom_params.buffer[LSC_R_OFFSET + tmpJmp + 1];
        g_reg_array[g_reg_setting.size].delay = 0;
        g_reg_setting.size++;
        e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].r_gain[i] =
            (float)(((*a_r_gain & 0x3) << 8) | *(a_r_gain + 1)) / 256;

        //Gr rolloff data
        g_reg_array[g_reg_setting.size].reg_addr = LSC_REG_PNT_ADDR + tmpJmp + 2;
        g_reg_array[g_reg_setting.size].reg_data = e_ctrl->eeprom_params.buffer[LSC_GR_OFFSET + tmpJmp];
        g_reg_array[g_reg_setting.size].delay = 0;
        g_reg_setting.size++;
        g_reg_array[g_reg_setting.size].reg_addr = LSC_REG_PNT_ADDR + tmpJmp + 3;
        g_reg_array[g_reg_setting.size].reg_data = e_ctrl->eeprom_params.buffer[LSC_GR_OFFSET + tmpJmp + 1];
        g_reg_array[g_reg_setting.size].delay = 0;
        g_reg_setting.size++;
        e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].gr_gain[i] =
            (float)(((*a_gr_gain & 0x3) << 8) | *(a_gr_gain + 1)) / 256;

        //Gb rolloff data
        g_reg_array[g_reg_setting.size].reg_addr = LSC_REG_PNT_ADDR + tmpJmp + MESH_HWROLLOFF_SIZE * 4;
        g_reg_array[g_reg_setting.size].reg_data = e_ctrl->eeprom_params.buffer[LSC_GB_OFFSET + tmpJmp];
        g_reg_array[g_reg_setting.size].delay = 0;
        g_reg_setting.size++;
        g_reg_array[g_reg_setting.size].reg_addr = LSC_REG_PNT_ADDR + tmpJmp + MESH_HWROLLOFF_SIZE * 4 + 1;
        g_reg_array[g_reg_setting.size].reg_data = e_ctrl->eeprom_params.buffer[LSC_GB_OFFSET + tmpJmp + 1];
        g_reg_array[g_reg_setting.size].delay = 0;
        g_reg_setting.size++;
        e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].gb_gain[i] =
            (float)(((*a_gb_gain & 0x3) << 8) | *(a_gb_gain + 1)) / 256;

        //B rolloff data
        g_reg_array[g_reg_setting.size].reg_addr = LSC_REG_PNT_ADDR + tmpJmp + MESH_HWROLLOFF_SIZE * 4 + 2;
        g_reg_array[g_reg_setting.size].reg_data = e_ctrl->eeprom_params.buffer[LSC_B_OFFSET + tmpJmp];
        g_reg_array[g_reg_setting.size].delay = 0;
        g_reg_setting.size++;
        g_reg_array[g_reg_setting.size].reg_addr = LSC_REG_PNT_ADDR + tmpJmp + MESH_HWROLLOFF_SIZE * 4 + 3;
        g_reg_array[g_reg_setting.size].reg_data = e_ctrl->eeprom_params.buffer[LSC_B_OFFSET + tmpJmp + 1];
        g_reg_array[g_reg_setting.size].delay = 0;
        g_reg_setting.size++;
        e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].b_gain[i] =
            (float)(((*a_b_gain & 0x3) << 8) | *(a_b_gain + 1)) / 256;

        a_r_gain += 4;
        a_gr_gain += 4;
        a_gb_gain += 4;
        a_b_gain += 4;
    }

#else
    lsc_present = 1;

    for (i = 0; i < MESH_HWROLLOFF_SIZE; i++) {
        e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].r_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_D65_LIGHT].r_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_A_LIGHT].r_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_H_LIGHT].r_gain[i] =
            (float)(((*a_r_gain & 0x3) << 8) | *(a_r_gain + 1)) / 256;
        e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].gr_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_D65_LIGHT].gr_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_A_LIGHT].gr_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_H_LIGHT].gr_gain[i] =
            (float)(((*a_gr_gain & 0x3) << 8) | *(a_gr_gain + 1)) / 256;
        e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].gb_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_D65_LIGHT].gb_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_A_LIGHT].gb_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_H_LIGHT].gb_gain[i] =
            (float)(((*a_gb_gain & 0x3) << 8) | *(a_gb_gain + 1)) / 256;
        e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].b_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_D65_LIGHT].b_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_A_LIGHT].b_gain[i] =
            e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_H_LIGHT].b_gain[i] =
            (float)(((*a_b_gain & 0x3) << 8) | *(a_b_gain + 1)) / 256;
        a_r_gain += 4;
        a_gr_gain += 4;
        a_gb_gain += 4;
        a_b_gain += 4;
    }

    e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].mesh_rolloff_table_size
    = MESH_HWROLLOFF_SIZE;
    e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_A_LIGHT].mesh_rolloff_table_size
    = MESH_HWROLLOFF_SIZE;
    e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_D65_LIGHT].mesh_rolloff_table_size
    = MESH_HWROLLOFF_SIZE;
    e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_H_LIGHT].mesh_rolloff_table_size
    = MESH_HWROLLOFF_SIZE;
#endif

    SERR("OTP: LSC MESH R MATRIX");
    print_matrix(e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].r_gain);
    SERR("OTP: LSC MESH GR MATRIX");
    print_matrix(e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].gr_gain);
    SERR("OTP: LSC MESH GB MATRIX");
    print_matrix(e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].gb_gain);
    SERR("OTP: LSC MESH B MATRIX");
    print_matrix(e_ctrl->eeprom_data.lsc.lsc_calib[ROLLOFF_TL84_LIGHT].b_gain);

    return;
}

/** a21n01j_format_calibration_data:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *
 * Format all the data structure of calibration
 *
 * This function executes in eeprom module context and generate
 *   all the calibration registers setting of the sensor.
 *
 * Return: void.
 **/
static void a21n01j_format_calibration_data(void *e_ctrl) {
    sensor_eeprom_data_t * ctrl = (sensor_eeprom_data_t *)e_ctrl;
    unsigned char *buffer = ctrl->eeprom_params.buffer;

    SERR("OTP: total bytes: %d",ctrl->eeprom_params.num_bytes);
    if (ctrl->eeprom_params.num_bytes == 0 || !a21n01j_check_module_info(ctrl)) {
        SERR("failed. OTP/EEPROM ERROR.");
        a21n01j_format_afdata(ctrl);    /*for null eeprom af issue work around*/
        return;
    } else {
        g_reg_setting.reg_setting = &g_reg_array[0];
        g_reg_setting.size = 0;
        g_reg_setting.addr_type = CAMERA_I2C_WORD_ADDR;
        g_reg_setting.data_type = CAMERA_I2C_BYTE_DATA;
        g_reg_setting.delay = 0;
    }

    a21n01j_format_wbdata(ctrl);
    a21n01j_format_afdata(ctrl);
    a21n01j_format_lscdata(ctrl);
    a21n01j_format_spcdata(ctrl);
    a21n01j_format_dccdata(ctrl);

    return;
}

/** a21n01j_get_ois_raw_data:
 *    @e_ctrl: point to sensor_eeprom_data_t of the eeprom device
 *    @data: point to the destination camera_i2c_seq_reg_setting
 *
 * Get the all the calibration registers setting for ois
 *
 * This function executes in eeprom module context.
 *
 * No return value.
 **/
static int a21n01j_get_raw_data(void *e_ctrl, void *data)
{
    RETURN_ERR_ON_NULL(e_ctrl, SENSOR_FAILURE);
    RETURN_ERR_ON_NULL(data, SENSOR_FAILURE);

    memcpy(data, &g_reg_setting, sizeof(g_reg_setting));

    return SENSOR_SUCCESS;
}

/** a21n01j_autofocus_calibration:
 *    @e_ctrl: address of pointer to
 *                   sensor_eeprom_data_t struct
 *
 * performs autofocus calibration assuming 2 regions
 *
 * This function executes in module sensor context
 *
 * Return:
 * void
 **/
static int a21n01j_autofocus_calibration(void *e_ctrl) {
    sensor_eeprom_data_t *ectrl = (sensor_eeprom_data_t *) e_ctrl;
    int                 i = 0;
    actuator_tuned_params_t *af_driver_tune = NULL;
    actuator_params_t       *af_params = NULL;
    unsigned int                total_steps = 0;
    short                 macro_dac, infinity_dac;
    unsigned int                qvalue = 0;

    /* Validate params */
    RETURN_ON_NULL(e_ctrl);
    RETURN_ON_NULL(ectrl->eeprom_afchroma.af_driver_ptr);

    af_driver_tune =
    &(ectrl->eeprom_afchroma.af_driver_ptr->actuator_tuned_params);
    af_params = &(ectrl->eeprom_afchroma.af_driver_ptr->actuator_params);
    /* Get the total steps */
    total_steps = af_driver_tune->region_params[af_driver_tune->region_size - 1].step_bound[0]  \
        - af_driver_tune->region_params[0].step_bound[1];

    if (!total_steps) {
        SERR("Invalid total_steps count = 0");
        return FALSE;
    }

    /* Get the calibrated steps */
    total_steps = af_driver_tune->region_params[af_driver_tune->region_size - 1].step_bound[0]  \
        - af_driver_tune->region_params[0].step_bound[1];

    /* adjust af_driver_ptr */
    af_driver_tune->initial_code = ectrl->eeprom_data.afc.infinity_dac;

    /*adjust code_per_step, assuming one region only */
    macro_dac = ectrl->eeprom_data.afc.macro_dac;
    infinity_dac = ectrl->eeprom_data.afc.infinity_dac;

    qvalue = af_driver_tune->region_params[0].qvalue;
    if(qvalue >= 1 && qvalue <= 4096)
    af_driver_tune->region_params[0].code_per_step =
     (macro_dac - infinity_dac) / (float)total_steps * qvalue;

    SERR("adjusted code_per_step: %d, qvalue: %d",
    af_driver_tune->region_params[0].code_per_step, qvalue);

    return TRUE;
}

/** sunny_a21n01j_open_lib:
 *
 * Get the funtion pointer of this lib.
 *
 * This function executes in eeprom module context.
 *
 * Return: eeprom_lib_func_t point to the function pointer.
 **/
void* sunny_a21n01j_eeprom_open_lib(void) {
  return &a21n01j_lib_func_ptr;
}

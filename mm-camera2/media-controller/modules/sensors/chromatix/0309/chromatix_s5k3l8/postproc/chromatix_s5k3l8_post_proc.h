//=============================================================================
//                          C H R O M A T I X
//
//   DESCRIPTION
//   Auto-Generated by Chromatix tool defining camera tunable parameters.
//
// Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//=============================================================================

/* Header Version Info */
{
   0x0309, /* Chromatix Version */
   0, /* Revision */
   /* Chromatix App Version */
   {
      6, /* Major */
      13, /* Minor */
      1, /* Revision */
      0, /* Build */
   },
   HEADER_POST_PROC, /* Header Type */
   0, /* Is Compressed */
   0, /* Is Mono */
   0, /* Is Video */
   0, /* Reserved Align */
   MODE_UNKNOWN, /* Chromatix Mode */
   0, /* Target ID */
   0, /* Chromatix ID */
   /* Reserved */
   {
      0, 0, 0, 0
   }
},

/******************************************************************************/
// Feature name: Radial Noise Reduction( RNR1 ) Parameters.
//
// Variable name: hysteresis_point[MAX_HYSTERESIS_LIGHT_REGIONS].
// Hysteresis Point is used to control Sampling Ratio parameter for RNR to reduce the oscillations.
//
// Variable name: sigma_lut[MAX_SIGMA_TABLES][RNR_LUT_SIZE].
// This LUT is used to describe the spatial varying noise property based
//   on pixel�s distance to the image center. This LUT should be calibrated from Chromatix tool.
// Data range: 1 to 5. Values outside this range indicate there may be problems in the calibration.
//
// Variable name: Sampling Factor.
// Downsample/Upsampling factor.
// Data range: Possible values are 2, 4, or 8.
// Effect: Larger value means stronger noise reduction.
// Default value: 2 for region 1-2, 4 for region 3-4, 8 for region 5-6
//
// Variable name: Center Noise Sigma.
// This parameter is multiplied with sigma_lut to determine the noise threshold for each position.
// This parameter is to be interpolated between different regions.
// Data range: 0 to 100. 0 means turning RNR off.
// Effect: larger value means stronger noise reduction.
// Default value: 1, 1.5, 2, 2.5, 4, 4.5 for region 1-6
//
// Variable name: Center Noise Weight
// This parameter determines RNR strength at image center.
// Data range: 0 to 1.0.
// Effect: larger value means less noise reduction at image center.
// Default value: 1.0 (no noise reduction in image center).
//
// Variable name: Noise Reduction Order or weight order.
// This variable controls RNR strength at off-center positions.
// Data range: 0 to 20
// Effect: larger value means stronger noise reduction at image corner.
// Default value: 1.0
/*******************************************************************************/

/* RNR1 */
{
   1, /* Enable */
   1, /* Control Enable */
   1, /* Control Method - 1 = Gain, 0 = Lux Index */
   164, /* Sigma LUT Size */
   /* Hysteresis Triggers */
   {
      /* Normal Light */
      {
         10.60000f, /* Gain Start */
         11.80000f, /* Gain End */
         350, /* Lux Index Start */
         380, /* Lux Index End */
      },
      /* Bright Light Light */
      {
         2.600000f, /* Gain Start */
         3.000000f, /* Gain End */
         200, /* Lux Index Start */
         210, /* Lux Index End */
      },
   },
   /* Sigma LUT Triggers */
   {
      /* Normal Light */
      {
         10.60000f, /* Gain Start */
         11.80000f, /* Gain End */
         350, /* Lux Index Start */
         380, /* Lux Index End */
      },
      /* Bright Light Light */
      {
         2.600000f, /* Gain Start */
         3.000000f, /* Gain End */
         200, /* Lux Index Start */
         210, /* Lux Index End */
      },
   },
   /* Sigma LUTs */
   {
      /* Sigma LUT1 */
      {
         1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
         1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.001500f,
         1.003000f, 1.004500f, 1.005900f, 1.007400f, 1.008900f, 1.010400f, 1.011900f, 1.013400f, 1.014900f, 1.016400f,
         1.017800f, 1.019300f, 1.020800f, 1.022300f, 1.023800f, 1.025300f, 1.026800f, 1.028300f, 1.029700f, 1.031200f,
         1.032700f, 1.034200f, 1.035700f, 1.037200f, 1.038700f, 1.040200f, 1.041600f, 1.043000f, 1.044400f, 1.045900f,
         1.047300f, 1.048700f, 1.050200f, 1.051600f, 1.053000f, 1.054500f, 1.055900f, 1.057300f, 1.058800f, 1.060200f,
         1.061600f, 1.063000f, 1.064500f, 1.065900f, 1.067300f, 1.068800f, 1.070200f, 1.071600f, 1.073100f, 1.074500f,
         1.075900f, 1.077400f, 1.078800f, 1.080200f, 1.081600f, 1.083100f, 1.084500f, 1.085900f, 1.087400f, 1.088800f,
         1.090200f, 1.103600f, 1.117000f, 1.130400f, 1.143800f, 1.157200f, 1.170600f, 1.184000f, 1.197400f, 1.210800f,
         1.224200f, 1.237600f, 1.251000f, 1.264400f, 1.277800f, 1.287000f, 1.296200f, 1.305400f, 1.314500f, 1.323700f,
         1.332900f, 1.342100f, 1.351300f, 1.360400f, 1.369600f, 1.378800f, 1.388000f, 1.397100f, 1.406300f, 1.415500f,
         1.424700f, 1.433900f, 1.443000f, 1.452200f, 1.461400f, 1.470600f, 1.479800f, 1.488900f, 1.498100f, 1.507300f,
         1.516500f, 1.525600f, 1.534800f, 1.544000f, 1.553200f, 1.563700f, 1.574300f, 1.584800f, 1.595400f, 1.606000f,
         1.616500f, 1.627100f, 1.637600f, 1.648200f, 1.658700f, 1.669300f, 1.679800f, 1.690400f, 1.700900f, 1.711500f,
         1.722000f, 1.732600f, 1.743200f, 1.753700f, 1.766200f, 1.778600f, 1.791100f, 1.803500f, 1.816000f, 1.828500f,
         1.840900f, 1.853400f, 1.865800f, 1.878300f, 1.890700f, 1.903200f, 1.915700f, 1.928100f, 1.940600f, 1.953000f,
         1.965500f, 1.978000f, 1.978000f, 1.978000f
      },
      /* Sigma LUT2 */
      {
         1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
         1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.001500f,
         1.003000f, 1.004500f, 1.005900f, 1.007400f, 1.008900f, 1.010400f, 1.011900f, 1.013400f, 1.014900f, 1.016400f,
         1.017800f, 1.019300f, 1.020800f, 1.022300f, 1.023800f, 1.025300f, 1.026800f, 1.028300f, 1.029700f, 1.031200f,
         1.032700f, 1.034200f, 1.035700f, 1.037200f, 1.038700f, 1.040200f, 1.041600f, 1.043000f, 1.044400f, 1.045900f,
         1.047300f, 1.048700f, 1.050200f, 1.051600f, 1.053000f, 1.054500f, 1.055900f, 1.057300f, 1.058800f, 1.060200f,
         1.061600f, 1.063000f, 1.064500f, 1.065900f, 1.067300f, 1.068800f, 1.070200f, 1.071600f, 1.073100f, 1.074500f,
         1.075900f, 1.077400f, 1.078800f, 1.080200f, 1.081600f, 1.083100f, 1.084500f, 1.085900f, 1.087400f, 1.088800f,
         1.090200f, 1.103600f, 1.117000f, 1.130400f, 1.143800f, 1.157200f, 1.170600f, 1.184000f, 1.197400f, 1.210800f,
         1.224200f, 1.237600f, 1.251000f, 1.264400f, 1.277800f, 1.287000f, 1.296200f, 1.305400f, 1.314500f, 1.323700f,
         1.332900f, 1.342100f, 1.351300f, 1.360400f, 1.369600f, 1.378800f, 1.388000f, 1.397100f, 1.406300f, 1.415500f,
         1.424700f, 1.433900f, 1.443000f, 1.452200f, 1.461400f, 1.470600f, 1.479800f, 1.488900f, 1.498100f, 1.507300f,
         1.516500f, 1.525600f, 1.534800f, 1.544000f, 1.553200f, 1.563700f, 1.574300f, 1.584800f, 1.595400f, 1.606000f,
         1.616500f, 1.627100f, 1.637600f, 1.648200f, 1.658700f, 1.669300f, 1.679800f, 1.690400f, 1.700900f, 1.711500f,
         1.722000f, 1.732600f, 1.743200f, 1.753700f, 1.766200f, 1.778600f, 1.791100f, 1.803500f, 1.816000f, 1.828500f,
         1.840900f, 1.853400f, 1.865800f, 1.878300f, 1.890700f, 1.903200f, 1.915700f, 1.928100f, 1.940600f, 1.953000f,
         1.965500f, 1.978000f, 1.978000f, 1.978000f
      },
      /* Sigma LUT3 */
      {
         1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f,
         1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.001500f,
         1.003000f, 1.004500f, 1.005900f, 1.007400f, 1.008900f, 1.010400f, 1.011900f, 1.013400f, 1.014900f, 1.016400f,
         1.017800f, 1.019300f, 1.020800f, 1.022300f, 1.023800f, 1.025300f, 1.026800f, 1.028300f, 1.029700f, 1.031200f,
         1.032700f, 1.034200f, 1.035700f, 1.037200f, 1.038700f, 1.040200f, 1.041600f, 1.043000f, 1.044400f, 1.045900f,
         1.047300f, 1.048700f, 1.050200f, 1.051600f, 1.053000f, 1.054500f, 1.055900f, 1.057300f, 1.058800f, 1.060200f,
         1.061600f, 1.063000f, 1.064500f, 1.065900f, 1.067300f, 1.068800f, 1.070200f, 1.071600f, 1.073100f, 1.074500f,
         1.075900f, 1.077400f, 1.078800f, 1.080200f, 1.081600f, 1.083100f, 1.084500f, 1.085900f, 1.087400f, 1.088800f,
         1.090200f, 1.103600f, 1.117000f, 1.130400f, 1.143800f, 1.157200f, 1.170600f, 1.184000f, 1.197400f, 1.210800f,
         1.224200f, 1.237600f, 1.251000f, 1.264400f, 1.277800f, 1.287000f, 1.296200f, 1.305400f, 1.314500f, 1.323700f,
         1.332900f, 1.342100f, 1.351300f, 1.360400f, 1.369600f, 1.378800f, 1.388000f, 1.397100f, 1.406300f, 1.415500f,
         1.424700f, 1.433900f, 1.443000f, 1.452200f, 1.461400f, 1.470600f, 1.479800f, 1.488900f, 1.498100f, 1.507300f,
         1.516500f, 1.525600f, 1.534800f, 1.544000f, 1.553200f, 1.563700f, 1.574300f, 1.584800f, 1.595400f, 1.606000f,
         1.616500f, 1.627100f, 1.637600f, 1.648200f, 1.658700f, 1.669300f, 1.679800f, 1.690400f, 1.700900f, 1.711500f,
         1.722000f, 1.732600f, 1.743200f, 1.753700f, 1.766200f, 1.778600f, 1.791100f, 1.803500f, 1.816000f, 1.828500f,
         1.840900f, 1.853400f, 1.865800f, 1.878300f, 1.890700f, 1.903200f, 1.915700f, 1.928100f, 1.940600f, 1.953000f,
         1.965500f, 1.978000f, 1.978000f, 1.978000f
      },
   },
   /* Region Data */
   {
      /* Region 1 */
      {
         /* Trigger */
         {
            1.000000f, /* Gain Start */
            1.990000f, /* Gain End */
            250, /* Lux Index Start */
            262, /* Lux Index End */
         },
         2, /* Sampling Factor */
         1.000000f, /* Center Noise Sigma */
         1.000000f, /* Center Noise Weight */
         1.000000f, /* Weight Order */
      },
      /* Region 2 */
      {
         /* Trigger */
         {
            2.000000f, /* Gain Start */
            3.990000f, /* Gain End */
            285, /* Lux Index Start */
            297, /* Lux Index End */
         },
         2, /* Sampling Factor */
         1.500000f, /* Center Noise Sigma */
         1.000000f, /* Center Noise Weight */
         1.000000f, /* Weight Order */
      },
      /* Region 3 */
      {
         /* Trigger */
         {
            4.000000f, /* Gain Start */
            7.990000f, /* Gain End */
            305, /* Lux Index Start */
            317, /* Lux Index End */
         },
         4, /* Sampling Factor */
         2.000000f, /* Center Noise Sigma */
         1.000000f, /* Center Noise Weight */
         1.000000f, /* Weight Order */
      },
      /* Region 4 */
      {
         /* Trigger */
         {
            8.000000f, /* Gain Start */
            15.99000f, /* Gain End */
            380, /* Lux Index Start */
            392, /* Lux Index End */
         },
         4, /* Sampling Factor */
         2.500000f, /* Center Noise Sigma */
         1.000000f, /* Center Noise Weight */
         1.000000f, /* Weight Order */
      },
      /* Region 5 */
      {
         /* Trigger */
         {
            16.00000f, /* Gain Start */
            31.99000f, /* Gain End */
            395, /* Lux Index Start */
            407, /* Lux Index End */
         },
         8, /* Sampling Factor */
         4.000000f, /* Center Noise Sigma */
         1.000000f, /* Center Noise Weight */
         1.000000f, /* Weight Order */
      },
      /* Region 6 */
      {
         /* Trigger */
         {
            32.00000f, /* Gain Start */
            59.99000f, /* Gain End */
            420, /* Lux Index Start */
            432, /* Lux Index End */
         },
         8, /* Sampling Factor */
         4.500000f, /* Center Noise Sigma */
         1.000000f, /* Center Noise Weight */
         1.000000f, /* Weight Order */
      },
   },
},

/******************************************************************************/
// Feature name : Chroma Artifact Correction2.
// Applicable operation mode: Snapshot.
//
// Variable name: control_CAC2.
// Control with gain or lux_index.
// Default Value: 0.
// Data range: 0 (Lux Index) or 1 ( Gain ).
// Constraints: None.
// Effect: Use gain or lux_index for control.
//
// variable name: cac2_enable.
// CAC2 Enable Flag per region.
//
// Variable name: y_spot_thr_low //6uQ6
// The lower bound of bright spot threshold in bright spot detection.
//   Bright spot threshold is defined on brightness difference between one pixel and its surrounding pixels
//   for luma spot detection.
// Default value: 0.
// Data range: 0 to 63.
// Effect: By decreasing the threshold, more points will be detected.
//
// Variable name: y_spot_thr_up //6uQ6
// The upper bound of bright spot threshold in bright spot detection.
//   Bright spot threshold is defined as brightness difference between one pixel and its surrounding pixels.
// Note: This parameter is not used in CAC3.
// Default value: 30.
// Data range: 0 to 63.
// Effect: By decreasing the threshold, more points will be detected.
//
// Variable name: y_spot_thr_weight //6uQ6
// Dynamic control parameter for determining the final value of bright spot threshold (y_spot_thr) in the range [y_spot_thr_low, y_spot_thr_up).
//   y_spot_thr = (y_spot_thr_up - y_spot_thr_low)*y_spot_thr_weight/64 + y_spot_thr_low.
// Note: This parameter is not used in CAC3.
// Default value: 20.
// Data range: 0 to 63.
//
// Variable name: y_saturation_thr //8uQ0
// The brightness saturation threshold in bright spot detection.
// Default value: 240.
// Data range : 200 to 255.
// Effect: By decreasing the threshold, more points will be detected.
//
// Variable name: c_saturation_thr //7uQ0
// The color saturation threshold in color spot detection.
// Default value: 10.
// Data range : 0 to 63.
// Effect: For one pixel, if its color saturation is less than c_saturation_thr,
//   it won�t be detected as 'Color Artifacts' and will not be corrected.
//
// Variable name: c_spot_thr //8uQ0
// The color spot threshold on color difference between one pixel and its surrounding pixels
//   in color spot detection.
// Default value: 10.
// Data range : 0 to 63.
// Effect: For one pixel, if its color difference is less than c_spot_thr,
//   it won�t be detected as 'Color Artifacts' and will not be corrected.
//   This parameter is not used for 8994 SW CAC.
/*******************************************************************************/

/* CAC2 */
{
   1, /* Control Enable */
   1, /* Control Method - 1 = Gain, 0 = Lux Index */
   /* Region Data */
   {
      /* Region 1 */
      {
         1, /* Enable CAC2 for this region */
         /* Trigger */
         {
            1.000000f, /* Gain Start */
            1.990000f, /* Gain End */
            250, /* Lux Index Start */
            262, /* Lux Index End */
         },
         0, /* Y Spot Threshold Low */
         30, /* Y Spot Threshold Up */
         240, /* Y Saturation Threshold */
         10, /* C Saturation Threshold */
         20, /* Y Spot Threshold Weight */
         10, /* Unused for now */
      },
      /* Region 2 */
      {
         1, /* Enable CAC2 for this region */
         /* Trigger */
         {
            2.000000f, /* Gain Start */
            3.990000f, /* Gain End */
            285, /* Lux Index Start */
            297, /* Lux Index End */
         },
         0, /* Y Spot Threshold Low */
         30, /* Y Spot Threshold Up */
         240, /* Y Saturation Threshold */
         10, /* C Saturation Threshold */
         20, /* Y Spot Threshold Weight */
         10, /* Unused for now */
      },
      /* Region 3 */
      {
         0, /* Enable CAC2 for this region */
         /* Trigger */
         {
            4.000000f, /* Gain Start */
            7.990000f, /* Gain End */
            305, /* Lux Index Start */
            317, /* Lux Index End */
         },
         0, /* Y Spot Threshold Low */
         30, /* Y Spot Threshold Up */
         240, /* Y Saturation Threshold */
         10, /* C Saturation Threshold */
         20, /* Y Spot Threshold Weight */
         10, /* Unused for now */
      },
      /* Region 4 */
      {
         0, /* Enable CAC2 for this region */
         /* Trigger */
         {
            8.000000f, /* Gain Start */
            15.99000f, /* Gain End */
            380, /* Lux Index Start */
            392, /* Lux Index End */
         },
         0, /* Y Spot Threshold Low */
         30, /* Y Spot Threshold Up */
         240, /* Y Saturation Threshold */
         10, /* C Saturation Threshold */
         20, /* Y Spot Threshold Weight */
         10, /* Unused for now */
      },
      /* Region 5 */
      {
         0, /* Enable CAC2 for this region */
         /* Trigger */
         {
            16.00000f, /* Gain Start */
            31.99000f, /* Gain End */
            395, /* Lux Index Start */
            407, /* Lux Index End */
         },
         0, /* Y Spot Threshold Low */
         30, /* Y Spot Threshold Up */
         240, /* Y Saturation Threshold */
         10, /* C Saturation Threshold */
         20, /* Y Spot Threshold Weight */
         10, /* Unused for now */
      },
      /* Region 6 */
      {
         0, /* Enable CAC2 for this region */
         /* Trigger */
         {
            32.00000f, /* Gain Start */
            59.99000f, /* Gain End */
            420, /* Lux Index Start */
            432, /* Lux Index End */
         },
         0, /* Y Spot Threshold Low */
         30, /* Y Spot Threshold Up */
         240, /* Y Saturation Threshold */
         10, /* C Saturation Threshold */
         20, /* Y Spot Threshold Weight */
         10, /* Unused for now */
      },
   },
},

/******************************************************************************/
// Variable name : stillmore_enable
//  True: enable StillMore feature
//  False: otherwise
// Feature : Parameters for StillMore feature
//
// Variable name : seemore_LTM_enable
//  True: enable LTM brightening
//  False: otherwise
// Feature : Parameters for SeeMore feature
//
// Variable name : seemore_TNR_enable
//  True: enable temporal noise reduction
//  False: otherwise
// Feature : Parameters for SeeMore feature
//
// Variable name : control_mod
// Description: 0(lux index) or 1(Gain) to control stillmore/seemore features
//
// Variable name : stillmore_hyst_trigger/seemore_hyst_trigger
// Description : Hysteresis trigger to enable StillMore/SeeMore feature. trigger >= trigger_end,
//  will enable the feature, else will be disabled and once enabled, feature will be enabled
//  until trigger < trigger_start.
//  stillmore_hyst_trigger for stillmore feature & seemore_hyst_trigger for seemore features
//
// Variable name : mod_trigger
// Description : trigger point for each region
//
// Variable name : still_brIntensity
// Controls amount of brightening.
// Data range: 0 ~ 1.
// Larger value means brighter output.
// Feature : Parameters for StillMore feature
//
// Variable name : still_brColor
// Controls amount of color after brightening.
// Data range: 0 ~ 1.
// Larger value means more colorful output.
// Feature : Parameters for StillMore feature
//
// Variable name : see_brIntensity
//  Controls amount of brightening.
// Data range: 0 ~ 1.
//  Larger value means brighter output.
//  NOTE: only takes effect when enableLTM == true.
// Feature : Parameters for SeeMore feature
//
// Variable name : see_brColor
//  Controls amount of color after brightening.
// Data range: 0 ~ 1.
//  Larger value means more colorful output.
//  NOTE: only takes effect when enableLTM == true.
// Feature : Parameters for SeeMore feature
//
// Variable name : ext_data
// Description: Extended data for reserve and future usage
/******************************************************************************/

/* Advanced Software */
{
   0, /* Stillmore Enable */
   0, /* Seemore LTM Enable */
   0, /* Seemore TNR Enable */
   0, /* Mod Control */
   /* Still More Hyst Trigger */
   {
      0.990000f, /* Gain Start */
      1.000000f, /* Gain End */
      100, /* Lux Index Start */
      110, /* Lux Index End */
   },
   /* See More Hyst Trigger */
   {
      0.990000f, /* Gain Start */
      1.000000f, /* Gain End */
      100, /* Lux Index Start */
      110, /* Lux Index End */
   },
   /* Data */
   {
      /* Region 1 */
      {
         /* Trigger */
         {
            1.000000f, /* Gain Start */
            1.200000f, /* Gain End */
            250, /* Lux Index Start */
            262, /* Lux Index End */
         },
         /* Still More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* See More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* Ext Data */
         {
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
         },
      },
      /* Region 2 */
      {
         /* Trigger */
         {
            2.960000f, /* Gain Start */
            3.552000f, /* Gain End */
            285, /* Lux Index Start */
            297, /* Lux Index End */
         },
         /* Still More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* See More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* Ext Data */
         {
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
         },
      },
      /* Region 3 */
      {
         /* Trigger */
         {
            4.920000f, /* Gain Start */
            5.904000f, /* Gain End */
            305, /* Lux Index Start */
            317, /* Lux Index End */
         },
         /* Still More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* See More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* Ext Data */
         {
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
         },
      },
      /* Region 4 */
      {
         /* Trigger */
         {
            8.000000f, /* Gain Start */
            9.600000f, /* Gain End */
            380, /* Lux Index Start */
            392, /* Lux Index End */
         },
         /* Still More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* See More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* Ext Data */
         {
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
         },
      },
      /* Region 5 */
      {
         /* Trigger */
         {
            22.00000f, /* Gain Start */
            26.40000f, /* Gain End */
            395, /* Lux Index Start */
            407, /* Lux Index End */
         },
         /* Still More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* See More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* Ext Data */
         {
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
         },
      },
      /* Region 6 */
      {
         /* Trigger */
         {
            36.00000f, /* Gain Start */
            43.20000f, /* Gain End */
            420, /* Lux Index Start */
            432, /* Lux Index End */
         },
         /* Still More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* See More Data */
         {
            0.200000f, /* Brighten Intensity */
            0.200000f, /* Brighten Color */
         },
         /* Ext Data */
         {
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f,
            0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f
         },
      },
   },
},
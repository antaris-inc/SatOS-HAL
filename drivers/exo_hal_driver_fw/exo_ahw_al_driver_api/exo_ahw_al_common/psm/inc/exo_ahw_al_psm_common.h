/**
 * @file exo_ahw_al_psm_common.h
 *
 * @brief This file contains function prototypes ,structures and
 * enumerations for power sense monitor
 *
 * @copyright Copyright 2023 Antaris, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef HAL_DRIVER_FW_AHW_AL_DRIVER_API_AHW_AL_INC_AHW_AL_PSM_H_
#define HAL_DRIVER_FW_AHW_AL_DRIVER_API_AHW_AL_INC_AHW_AL_PSM_H_

#include <stdint.h>
#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_ahw_al_common.h"

/**
 * @brief  Power Monitor operating mode enumeration
 */
typedef enum
{
    OPERATING_MODE_TRIGGERED = 0,			/*!< operating mode triggered */
    OPERATING_MODE_CONTINUOUS,			/*!< operating mode continuous */
    OPERATING_MODE_MAX
} psm_operating_mode_t;

/**
 * @brief power sense monitor conversion time enumeration
 */
typedef enum
{
    CONVERT_TIME_140 = 0,					/*!< convert time 140 */
    CONVERT_TIME_204,						/*!< convert time 204 */
    CONVERT_TIME_332,						/*!< convert time 332 */
    CONVERT_TIME_588,						/*!< convert time 588 */
    CONVERT_TIME_1100,					/*!< convert time 1100 */
    CONVERT_TIME_2116,					/*!< convert time 2116 */
    CONVERT_TIME_4156,					/*!< convert time 4156 */
    CONVERT_TIME_8244,					/*!< convert time 8244 */
    CONVERT_TIME_MAX
} psm_convert_time_t;

/**
 * @brief power sense monitor averaging mode enumeration
 */
typedef enum
{
    AVERAGING_MODE_1 = 0, 				/*!< averaging mode 1 */
    AVERAGING_MODE_4,						/*!< averaging mode 4 */
    AVERAGING_MODE_16,					/*!< averaging mode 16 */
    AVERAGING_MODE_64,					/*!< averaging mode 64 */
    AVERAGING_MODE_128,					/*!< averaging mode 128 */
    AVERAGING_MODE_256,					/*!< averaging mode 256 */
    AVERAGING_MODE_512,					/*!< averaging mode 512 */
    AVERAGING_MODE_1024,					/*!< averaging mode 1024 */
    AVERAGING_MODE_MAX
}psm_averaging_mode_t;

/**
 * @brief power sense monitor alert polarity enumeration
 */
typedef enum
{
    PSM_ALERT_POLARITY_NORMAL = 0,		/*!< alert polarity normal */
    PSM_ALERT_POLARITY_INVERTED,			/*!< alert polarity inverted */
    PSM_ALERT_POLARITY_MAX
} psm_alert_polarity_t;

/**
 * @brief  Power Monitor Alert Latch Enable enumeration
 */
typedef enum
{
    PSM_ALERT_LATCH_DISABLE = 0,			/*!< alert latch disable */
    PSM_ALERT_LATCH_ENABLE,				/*!< alert latch enable */
    PSM_ALERT_LATCH_MAX
} psm_alert_latch_enable_t;

/**
 * @brief power sense monitor alert function enumeration
 */
typedef enum
{
    PSM_ALERT_FUNCTION_NONE = 0,			/*!< alert function none */
    PSM_ALERT_FUNCTION_SOL,				/*!< alert function sol */
    PSM_ALERT_FUNCTION_SUL,				/*!< alert function sul */
    PSM_ALERT_FUNCTION_BOL,				/*!< alert function bol */
    PSM_ALERT_FUNCTION_BUL,				/*!< alert function bul */
    PSM_ALERT_FUNCTION_POL,				/*!< alert function pol */
    PSM_ALERT_FUNCTION_MAX,
} psm_alert_function_t;

/**
 * @brief power sense monitor Voltage Input signal enumeration
 */
typedef enum
{
    VOLTAGE_INPUT_SHUNT = 0,			/*!< voltage input shunt */
    VOLTAGE_INPUT_BUS,				/*!< voltage input bus */
    VOLTAGE_INPUT_ALL,				/*!< voltage input all */
    VOLTAGE_INPUT_MAX
} psm_input_signal_t;

/**
 * @brief power sense Monitor Flag enumeration
 */
typedef enum
{
    FLAG_PSM_ALERT_FUNCTION = 0,		/*!< flag alert function */
    FLAG_CONVERSION_READY,			/*!< flag conversion ready */
    FLAG_MATH_OVERFLOW,				/*!< flag math overflow */
    FLAG_MAX
} psm_flag_t;

/**
 * @brief power sense Monitor Device configuration structure
 */
typedef struct
{
    psm_convert_time_t    shunt_convert_time;		/*!< shunt conversion_time enumeration of power sense monitor	*/
    psm_convert_time_t    bus_convert_time;		/*!< bus conversion_time enumeration  of power sense monitor	*/
    psm_averaging_mode_t  averaging_mode;			/*!< average_mode enumeration of power sense monitor			*/
} ahw_al_psm_tc_config_t;

/**
 * @brief power sense monitor time conversion and averaging mode configuration pointer type definition
 */
typedef ahw_al_psm_tc_config_t ahw_al_psm_tc_cfg_ptr_t;

/**
 * @brief power sense monitor device alert pin  structure
 */
typedef struct
{
    psm_alert_polarity_t    Polarity;			/*!< power sense monitor Alert Polarity enumeration 	*/
    psm_alert_latch_enable_t LatchEnable;		/*!< power sense monitor Alert Latch Enable enumeration */
} ahw_al_psm_alert_pin_cfg_t;

/**
 * @brief power sense monitor alert pin configuration pointer type definition
 */
typedef ahw_al_psm_alert_pin_cfg_t ahw_al_psm_config_ptr_t;

/**
 * @brief power sense monitor ahw_al device  structure
 */
typedef struct _ahw_al_psm_hdle
{
    ahw_al_gen_info ahw_gen_info;         			/*!< Application abstraction layer genral information structure */
    ahw_al_psm_alert_pin_cfg_t  psm_alert_cfg;		/*!< power sense Monitor Device alert pin  structure			*/
    float vbus_threshold;							/*!< vbus threshold												*/
    float current_threshold;						/*!< current threshold											*/
    uint32_t power_threshold;						/*!< power threshold											*/
    psm_alert_function_t alert_function;			/*!< power sense monitor alert function enumeration				*/
    psm_operating_mode_t mode;						/*!< Power Monitor operating mode enumeration					*/
    psm_input_signal_t inputsignal;					/*!< power sense monitor Voltage Input signal enumeration		*/
    psm_flag_t flag;								/*!< power sense Monitor Flag enumeration						*/
}ahw_al_psm_hdle;

/**
 * @brief ahw_al_psm handle pointer type definition
 */
typedef ahw_al_psm_hdle ahw_al_psm_hdl_ptr;

/**
 * @brief API to initialize the PSM and do the basic configurations
 * @param[in]hpsm_arg : structure handle of power sense monitor.
 * @param[in]ahw_id : application hardware instance ID
 * @param[in]hpsm_tc_cfg : pointer to structure ahw_al_psm_tc_config_t
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_init(ahw_al_psm_hdle* hpsm_arg, ahw_inst_id_t ahw_id,ahw_al_psm_tc_config_t* hpsm_tc_cfg );

/**
 * @brief API to de-Initialize the PSM and reset
 * @param[in] hpsm_arg : structure handle of power sense monitor .
 * @param[in] ahw_id : application hardware Instance ID
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_deinit(ahw_al_psm_hdle* hpsm_arg, ahw_inst_id_t ahw_id);

/**
 * @brief API to read the die id or chip id.
 * @param[in] hpsm : structure handle of power sense monitor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts	ahw_al_psm_read_id(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to generates a system reset.
 * @param[in] hpsm : structure handle of power sense monitor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_reset(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to program the PSM calibration register.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @param[in]calibration 	: calibration value for ina230
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_set_calibration(ahw_al_psm_hdle *hpsm, uint16_t calibration);

/**
 * @brief API to read the set value in the PSM calibration register.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the success or error code
 */
uint16_t ahw_al_psm_get_calibration(ahw_al_psm_hdle *hpsm);

/**
 * @brief Configure the Alert pin behavior
 * @param[in]  hpsm 	: structure handle of power sense monitor.
 * @param[in] alert_pin_cfg	: structure handle of Alert pin configuration.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_psm_alert_pinconfig(ahw_al_psm_hdle *hpsm, ahw_al_psm_alert_pin_cfg_t *alert_pin_cfg);

/**
 * @brief API to set the alert function
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @param[in] alert_function : alert function to be set
 * This parameter can be take one of the following values:
 *         ALERT_FUNCTION_NONE
 *         ALERT_FUNCTION_SOL
 *         ALERT_FUNCTION_SUL
 *         ALERT_FUNCTION_B0L
 *         ALERT_FUNCTION_BUL
 *         ALERT_FUNCTION_POL
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_psm_set_alertfunction(ahw_al_psm_hdle *hpsm,psm_alert_function_t alert_function);

/**
 * @brief API to get the programmed alert function
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @param[in] alert_function : alert function of the power sensor monitor
 * This parameter can be take one of the following values:
 *         ALERT_FUNCTION_NONE
 *         ALERT_FUNCTION_SOL
 *         ALERT_FUNCTION_SUL
 *         ALERT_FUNCTION_B0L
 *         ALERT_FUNCTION_BUL
 *         ALERT_FUNCTION_POL
 * @retval hal_ret_sts- returns the success or error code
 */
hal_ret_sts ahw_al_psm_get_alertfunction(ahw_al_psm_hdle *hpsm,psm_alert_function_t alert_function);

/**
 * @brief API to program the VBus threshold.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @param[in] vbusthreshold	: vbusthreshold value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_setvbusthreshold(ahw_al_psm_hdle *hpsm, float vbusthreshold);

/**
 * @brief API to get the VBus threshold.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts	: returns the success or error code.
 */
hal_ret_sts ahw_al_psm_getvbusthreshold(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to program the VShunt threshold.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @param[in] vshuntthreshold	: vshuntthreshold value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_setvshuntthreshold(ahw_al_psm_hdle *hpsm, float vshuntthreshold);

/**
 * @brief API to get the VShunt threshold.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_getshuntthreshold(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to set the current threshold
 * @param[in] hpsm 		: structure handle of power sense monitor.
 * @param[in] current_threshold	: current threshold value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_set_current_threshold(ahw_al_psm_hdle *hpsm, float current_threshold);

/**
 * @brief API to set the power threshold
 * @param[in] hpsm 		: structure handle of power sense monitor.
 * @param[in] powerthreshold	: power threshold value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_setpowerthreshold(ahw_al_psm_hdle *hpsm, uint32_t powerthreshold);

/**
 * @brief API to get the power threshold
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_getpowerthreshold(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to enable the Voltage/Power threshold interrupt.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts  - returns the success or error code
 */
hal_ret_sts ahw_al_psm_alert_threshold_enable_it(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to disable the Voltage/Power threshold interrupt
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts  - returns the success or error code
 */
hal_ret_sts  ahw_al_psm_alert_threshold_disable_it(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to enable the Conversion ready interrupt
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_conversion_ready_enable_it(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to disable the Conversion ready interrupt.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_conversion_ready_disable_it(ahw_al_psm_hdle *hpsm);

/**
 * @brief  API to launch the conversion on the selected voltage input
 * @param  hpsm 	: structure handle of power sense monitor.
 * @param  inputsignal :Input signal to convert.
 *         This parameter can be take one of the following values:
 *         INPUT_SIGNAL_SHUNT
 *         INPUT_SIGNAL_BUS
 *         INPUT_SIGNAL_ALL
 * @param  mode : operating mode.
 *         This parameter can be take one of the following values:
 *         OPERATING_MODE_CONTINUOUS
 *         OPERATING_MODE_TRIGGERED
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_psm_startconversion(ahw_al_psm_hdle *hpsm, psm_input_signal_t inputsignal, psm_operating_mode_t mode);

/**
 * @brief API to stop the conversion on the selected voltage input.
 * @param  hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts  - returns the success or error code
 */
hal_ret_sts ahw_al_psm_stopconversion(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to get the vbus voltage.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the vbus value
 */
float ahw_al_psm_get_vbus(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to get the VShunt voltage.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the vshunt value
 */
float ahw_al_psm_get_vshunt(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to get the power.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the power
 */
uint32_t ahw_al_psm_get_power(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to get the current value.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the current
 */
float ahw_al_psm_get_current(ahw_al_psm_hdle *hpsm);

/**
 * @brief  API to read the designed flag value
 * @param  flag : specifies the flag to check.
 *         This parameter can be one of the following values:
 *         FLAG_ALERT_FUNCTION
 *         FLAG_CONVERSION_READY
 *         FLAG_MATH_OVERFLOW
 * @retval Actual state of the flag (TRUE or FALSE).
 */
hal_ret_sts ahw_al_psm_get_flag(ahw_al_psm_hdle *hpsm, psm_flag_t flag);





#endif /* HAL_DRIVER_FW_AHW_AL_DRIVER_API_AHW_AL_INC_AHW_AL_PSM_H_ */

/**
 * @file exo_ahw_vdp_psm_ina230.h
 *
 * @brief This file contains function prototype of power sense monitor
 *
 * @copyright Copyright 2024 Antaris, Inc.
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

#ifndef HAL_DRIVER_FW_AHW_AL_DRIVER_API_PSM_INA230_INC_AHW_VDP_PSM_INA230_H_
#define HAL_DRIVER_FW_AHW_AL_DRIVER_API_PSM_INA230_INC_AHW_VDP_PSM_INA230_H_

#include "exo_hal_common.h"
#include "exo_ahw_al_psm_common.h"
#include "exo_io_al_i2c_common.h"

/**
 * @brief API to initialize the VDP-INA230 and configure.
 * @param[in]hpsm : structure handle of power sense monitor of ahw_al_psm.
 * @param[in]hpsm_tc_cfg	: Conversion time structure handle.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_init(ahw_al_psm_hdle *hpsm,ahw_al_psm_tc_config_t *hpsm_tc_cfg);

/**
 * @brief API to de-Initialize the VDP-INA230 and reset
 * @param[in]hpsm : structure handle of power sense monitor of ahw_al_psm
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_deinit(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to read the die id or chip id.
 * @param[in]hpsm : structure handle of power sense monitor of ahw_al_psm
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts	 ahw_vdp_psm_ina230_read_id(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to generates a system reset.
 * @param[in]hpsm : structure handle of power sense monitor of ahw_al_psm
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_reset(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to set calibration register.
 * @param[in]hpsm       	: structure handle of power sense monitor of ahw_al_psm
 * @param[in]calibration 	: calibration value for psm
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_set_calibration(ahw_al_psm_hdle *hpsm, uint16_t calibration);

/**
 * @brief API to read the calibration
 * @param[in]hpsm 	: structure handle of power sense monitor.
 * @retval			: calibration value
 */
uint16_t ahw_vdp_psm_ina230_get_calibration(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to configure the Alert pin behavior
 * @param[in]  hpsm 	: structure handle of power sense monitor of ina230.
 * @param[in] alert_pin_cfg	: structure al handle of Alert pin configuration.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_alert_pinconfig(ahw_al_psm_hdle *hpsm,ahw_al_psm_alert_pin_cfg_t *alert_pin_cfg);

/**
 * @brief API to set the alert function
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @param[in] AlertFunction Monitored alert function.
 * This parameter can be take one of the following values:
 *         ALERT_FUNCTION_NONE
 *         ALERT_FUNCTION_SOL
 *         ALERT_FUNCTION_SUL
 *         ALERT_FUNCTION_B0L
 *         ALERT_FUNCTION_BUL
 *         ALERT_FUNCTION_POL
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_set_alertfunction(ahw_al_psm_hdle *hpsm,psm_alert_function_t alert_function);

/**
 * @brief API to get the programmed alert function
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @param[in] AlertFunction Monitored alert function.
 * This parameter can be take one of the following values:
 *         ALERT_FUNCTION_NONE
 *         ALERT_FUNCTION_SOL
 *         ALERT_FUNCTION_SUL
 *         ALERT_FUNCTION_B0L
 *         ALERT_FUNCTION_BUL
 *         ALERT_FUNCTION_POL
 * @retval hal_ret_sts- returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_get_alertfunction(ahw_al_psm_hdle *hpsm,psm_alert_function_t alert_function);

/**
 * @brief API to program the VBus threshold.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @param[in] vbusthreshold	: vbusthreshold value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts  ahw_vdp_psm_ina230_setvbusthreshold(ahw_al_psm_hdle *hpsm, float vbusthreshold);

/**
 * @brief API to get the VBus threshold.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval		hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_getvbusthreshold(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to program the VShunt threshold.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @param[in] vshuntthreshold	: vshuntthreshold value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts  ahw_vdp_psm_ina230_setvshuntthreshold(ahw_al_psm_hdle *hpsm, float vshuntthreshold);

/**
 * @brief API to get the VShunt threshold.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts	ahw_vdp_psm_ina230_getshuntthreshold(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to program the power threshold.
 * @param[in] hpsm 		: structure handle of power sense monitor.
 * @param[in] powerthreshold	: powerthreshold value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_setpowerthreshold(ahw_al_psm_hdle *hpsm, uint32_t powerthreshold);

/**
 * @brief API to program the current threshold.
 * @param[in] hpsm 		: structure handle of power sense monitor.
 * @param[in] current_threshold	: current_threshold value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_get_current_threshold(ahw_al_psm_hdle *hpsm, float current_threshold);

/**
 * @brief API to get the power threshold
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_getpowerthreshold(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to enable the Voltage/Power threshold interrupt.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts  - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_alert_threshold_enable_it(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to disable the Voltage/Power threshold interrupt
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts  - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_alert_threshold_disable_it(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to enable the Conversion ready interrupt
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_conversion_ready_enable_it(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to disable the Conversion ready interrupt.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_conversion_ready_disable_it(ahw_al_psm_hdle *hpsm);

/**
 * @brief  API to launch the conversion on the selected voltage input
 * @param  hpsm 	: structure handle of power sense monitor.
 * @param  InputSignal Input signal to convert.
 *         This parameter can be take one of the following values:
 *         INPUT_SIGNAL_SHUNT
 *         INPUT_SIGNAL_BUS
 *         INPUT_SIGNAL_ALL
 * @param  Mode operating mode.
 *         This parameter can be take one of the following values:
 *         OPERATING_MODE_CONTINUOUS
 *         OPERATING_MODE_TRIGGERED
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_startconversion(ahw_al_psm_hdle *hpsm, psm_input_signal_t inputsignal, psm_operating_mode_t mode);

/**
 * @brief API to stop the conversion on the selected voltage input.
 * @param  hpsm 	: structure handle of power sense monitor.
 * @retval hal_ret_sts  - returns the success or error code
 */
hal_ret_sts ahw_vdp_psm_ina230_stopconversion(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to get the vbus voltage.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the success or error code
 */
float  ahw_vdp_psm_ina230_get_vbus(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to get the VShunt voltage.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the success or error code
 */
float  ahw_vdp_psm_ina230_get_vshunt(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to get the power.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the success or error code
 */
uint32_t ahw_vdp_psm_ina230_get_power(ahw_al_psm_hdle *hpsm);

/**
 * @brief API to get the current value.
 * @param[in] hpsm 	: structure handle of power sense monitor.
 * @retval	hal_ret_sts - returns the success or error code
 */
float ahw_vdp_psm_ina230_get_current(ahw_al_psm_hdle *hpsm);

/**
 * @brief  API to read the designed flag value
 * @param  Slave_Address on communication Bus from power Monitor Device structure.
 * @param  Flag specifies the flag to check.
 *         This parameter can be one of the following values:
 *         FLAG_ALERT_FUNCTION
 *         FLAG_CONVERSION_READY
 *         FLAG_MATH_OVERFLOW
 * @retval Actual state of the flag (TRUE or FALSE).
 */
hal_ret_sts ahw_vdp_psm_ina230_get_flag(ahw_al_psm_hdle *hpsm, psm_flag_t flag);

#endif /* HAL_DRIVER_FW_AHW_AL_DRIVER_API_PSM_INA230_INC_AHW_VDP_PSM_INA230_H_ */

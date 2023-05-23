/**
 * @file exo_ahw_vdp_ts_mcp9843.h
 *
 * @brief This file contains the function prototype of temperature sensor
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

#ifndef HAL_DRIVER_FW_AHW_AL_DRIVER_API_TS_INC_AHW_VDP_TS_H_
#define HAL_DRIVER_FW_AHW_AL_DRIVER_API_TS_INC_AHW_VDP_TS_H_

#include "exo_hal_common.h"
#include "exo_ahw_al_temp_sensor_common.h"
#include "exo_io_al_i2c_common.h"

/**
 * @brief API to initialize the MCP9843 and configure.
 * @param[in]al_ts_h : structure handle of Ahw Al temperature sensor handle.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_init(ahw_al_temp_sensor_hdl *al_ts_h);

/**
 * @brief API to de-Initialize the MCP9843 and configure.
 * @param[in]al_ts_h : structure handle of Ahw Al temperature sensor handle.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_deinit(ahw_al_temp_sensor_hdl *al_ts_h);

/**
 * @brief API to get event status of temperature sensor
 * @param[in]al_ts_h : structure handle of Ahw Al temperature sensor handle.
 * @param[in]evnt_sts : event status of temperature sensor
 * @retval e_ina230_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_ts_mcp9843_get_evnt_sts (ahw_al_temp_sensor_hdl *al_ts_h, uint8_t* evnt_sts);

/**
 * @brief API to configure device
 * @param[in]al_ts_h : structure handle of Ahw Al temperature sensor handle.
 * @retval e_ina230_sts - returns the success or error code
 */
hal_ret_sts	 ahw_vdp_ts_mcp9843_config (ahw_al_temp_sensor_hdl *al_ts_h);

/**
 * @brief API to set the mode of operation
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[in] mode: mode of operation cont or shut_down mode.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	 ahw_vdp_ts_mcp9843_set_mode(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_mode_t mode);

/**
 * @brief API to clear the interrupt  bit
 * @param[in] al_ts_h 			: structure handle of Ahw Al temperature sensor handle.
 * @param[in] interrupt_clear	: interrupt_clear value.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_intrupt_clear(ahw_al_temp_sensor_hdl *al_ts_h, uint8_t intrupt_clear);

/**
 * @brief API to set the event output pin
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[in] event_mode	: event_mode set value
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_set_event_output_mode(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_event_output_mode_t event_mode);

/**
 * @brief API to set the event polarity
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[in] polarity		: polarity set value
 * This parameter can be take one of the following values:
 * 		ACTIVE HIGH
 * 		ACTIVE LOW
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_set_event_polarity(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_event_polarity_t polarity);

/**
 * @brief API to set the win_lock_bit
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[in] win_lock_bit	: win_lock_bit set value
 * This parameter can be take one of the following values:
 * 		WIN_UNLOCK
 * 		WIN_LOCK
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_set_win_lockbit(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_win_lock_t win_lock);

/**
 * @brief API to set the crit_lock_bit
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[in] crit_lock	: crit_lock_bit set value
 * This parameter can be take one of the following values:
 * 		CRIT_UNLOCK
 * 		CRIT_LOCK
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_set_crit_lockbit(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_crit_lock_t crit_lock);

/**
 * @brief API to set the Temperature high threshold
 * @param[in] al_ts_h 				: structure handle of Ahw Al temperature sensor handle.
 * @param[in] high_temp_threshold	: high_temp_threshold set value
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	 ahw_vdp_ts_mcp9843_set_temp_high_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float high_temp_threshold);

/**
 * @brief API to set the Temperature low threshold
 * @param[in] al_ts_h 				: structure handle of Ahw Al temperature sensor handle.
 * @param[in] low_temp_threshold	: low_temp_threshold set value
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_set_temp_low_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float low_temp_threshold);

/**
 * @brief API to set the Temperature critical threshold
 * @param[in] al_ts_h 				: structure handle of Ahw Al temperature sensor handle.
 * @param[in] critical_temp_threshold	: low_temp_threshold set value
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	 ahw_vdp_ts_mcp9843_set_temp_critical_threshold (ahw_al_temp_sensor_hdl* ahw_al_hts, float critical_temp_threshold);

/**
 * @brief API to set the Temperature hysteresis.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[in] hysteresis	: hysteresis
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_set_hysteresis(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_hyst_t hysteresis);

/**
 * @brief API to get the Temperature hysteresis.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out] hysteresis	: hysteresis
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_get_hysteresis(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_hyst_t *hysteresis);

/**
 * @brief API to set the Temperature resolution.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[in] resolution	: resolution
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_set_resolution(ahw_al_temp_sensor_hdl *al_ts_h, temp_sensor_res_t resolution);

/**
 * @brief API to get the Temperature resolution.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out] res      	: res
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_get_resolution(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_res_t *res);

/**
 * @brief API to get the current Temperature.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out]temp_value 	: temperature value
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_vdp_ts_mcp9843_get_temperature(ahw_al_temp_sensor_hdl *al_ts_h,float *temperature);

/**
 * @brief API to get the Temperature value in fahrenheit.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out]temp_value 	: temperature value in fahrenheit.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_vdp_ts_mcp9843_get_fahrenheit(ahw_al_temp_sensor_hdl *al_ts_h,float* temperature);

/**
 * @brief API to get the Temperature value in celsius.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out]temp_value 	: temperature value in celsius.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_vdp_ts_mcp9843_get_celsius(ahw_al_temp_sensor_hdl *al_ts_h,float* temperature);

/**
 * @brief API to read the manufacture ID
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out]temperature 	: temperature value in celsius.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_vdp_ts_mcp9843_read_manufacture_id(ahw_al_temp_sensor_hdl *al_ts_h,int16_t* temperature);

#endif /* HAL_DRIVER_FW_AHW_AL_DRIVER_API_TS_INC_AHW_VDP_PTS_H_ */

/**
 * @file exo_ahw_al_temp_sensor_wrapper.h
 *
 * @brief This file has mapping functions for temperature sensor
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


#ifndef _AHW_AL_WRAPPER_H_
#define _AHW_AL_WRAPPER_H_

#define TEMP_SENSOR_MCP9843_A

#ifdef TEMP_SENSOR_MCP9843_A
#include "exo_ahw_vdp_ts_mcp9843.h"
#endif

/**
 * @brief Mapping API to initialize the temperature sensor
 * @param[in]al_ts_h : structure handle of temperature sensor handle.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts	ahw_al_ts_common_init(ahw_al_temp_sensor_hdl *al_ts_h);

/**
 * @brief Mapping API to de-Initialize the temperature sensor
 * @param[in]al_ts_h : structure handle of temperature sensor handle.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_deinit(ahw_al_temp_sensor_hdl *al_ts_h);

/**
 * @brief Mapping API to configure device
 * @param[in]al_ts_h : structure handle of temperature sensor handle.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_config (ahw_al_temp_sensor_hdl *al_ts_h);

/**
 * @brief Mapping API to get event status of temperature sensor
 * @param[in]al_ts_h : structure handle of temperature sensor handle.
 * @param[in]evnt_sts : event status of temperature sensor
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_get_evnt_sts (ahw_al_temp_sensor_hdl *al_ts_h, uint8_t* evnt_sts);

/**
 * @brief Mapping API to set the mode of operation
 * @param[in] al_ts_h : structure handle of temperature sensor handle.
 * @param[in] mode	: mode of operation cont or shut_down mode.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_set_mode(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_mode_t mode);

/**
 * @brief Mapping API to clear the interrupt bit
 * @param[in] al_ts_h 			: structure handle of temperature sensor handle.
 * @param[in] interrupt_clear	: interrupt_clear value.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts	ahw_al_ts_common_intrupt_clear(ahw_al_temp_sensor_hdl *al_ts_h, uint8_t interrupt_clear);

/**
 * @brief Mapping API to set the event output pin
 * @param[in] al_ts_h 		: structure handle of temperature sensor handle.
 * @param[in] event_mode	: event_mode set value
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_set_event_output_mode(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_event_output_mode_t event_mode);

/**
 * @brief Mapping API to set the event polarity
 * @param[in] al_ts_h 		: structure handle of temperature sensor handle.
 * @param[in] polarity		: polarity set value
 * This parameter can be take one of the following values:
 * 		ACTIVE HIGH
 * 		ACTIVE LOW
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_set_event_polarity(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_event_polarity_t polarity);

/**
 * @brief Mapping API to set the win lock bit
 * @param[in] al_ts_h 		: structure handle of temperature sensor handle.
 * @param[in] win_lock	: win_lock_bit set value
 * This parameter can be take one of the following values:
 * 		WIN_UNLOCK
 * 		WIN_LOCK
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_set_win_lockbit(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_win_lock_t win_lock);

/**
 * @brief Mapping API to set the critical lock bit
 * @param[in] al_ts_h 		: structure handle of temperature sensor handle.
 * @param[in] crit_lock	: crit_lock_bit set value
 * This parameter can be take one of the following values:
 * 		CRIT_UNLOCK
 * 		CRIT_LOCK
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_set_crit_lockbit(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_crit_lock_t crit_lock);

/**
 * @brief Mapping API to set the Temperature high threshold
 * @param[in] al_ts_h 				: structure handle of Ahw Al temperature sensor handle.
 * @param[in] high_temp_threshold	: high_temp_threshold set value
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_set_temp_high_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float high_temp_threshold);

/**
 * @brief Mapping API to set the Temperature low threshold
 * @param[in] al_ts_h 				: structure handle of Ahw Al temperature sensor handle.
 * @param[in] low_temp_threshold	: low_temp_threshold set value
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_set_temp_low_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float low_temp_threshold);

/**
 * @brief Mapping API to set the Temperature critical threshold
 * @param[in] al_ts_h 				: structure handle of Ahw Al temperature sensor handle.
 * @param[in] critical_temp_threshold	: low_temp_threshold set value
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_set_temp_critical_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float critical_temp_threshold);

/**
 * @brief Mapping API to set the Temperature hysteresis.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[in] hysteresis	: hysteresis
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_set_hysteresis(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_hyst_t hysteresis);

/**
 * @brief Mapping API to get the Temperature hysteresis.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out] hysteresis	: hysteresis
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_get_hysteresis(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_hyst_t *hysteresis);

/**
 * @brief Mapping API to set the Temperature resolution.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[in] resolution	: resolution
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_set_resolution(ahw_al_temp_sensor_hdl *al_ts_h, temp_sensor_res_t resolution);

/**
 * @brief Mapping API to get the Temperature resolution.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out] res      	: res
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_get_resolution(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_res_t *res);

/**
 * @brief Mapping API to get the current Temperature.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out]temperature 	: temperature value
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_gettemperature(ahw_al_temp_sensor_hdl *al_ts_h,float *temperature);

/**
 * @brief Mapping API to get the Temperature value in fahrenheit.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out]temperature 	: temperature value in fahrenheit.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_get_fahrenheit(ahw_al_temp_sensor_hdl *al_ts_h,float* temperature);

/**
 * @brief Mapping API to get the Temperature value in celsius.
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out]temperature 	: temperature value in celsius.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_get_celsius(ahw_al_temp_sensor_hdl *al_ts_h,float* temperature);

/**
 * @brief Mapping API to read the manufacture ID
 * @param[in] al_ts_h 		: structure handle of Ahw Al temperature sensor handle.
 * @param[out]temperature 	: temperature value in celsius.
 * @retval hal_ret_sts		:returns the success or error code
 */
hal_ret_sts ahw_al_ts_common_read_manufacture_id(ahw_al_temp_sensor_hdl *al_ts_h,int16_t* temperature);
#endif /* _AHW_AL_WRAPPER_H_ */

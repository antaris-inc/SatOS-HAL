/**
 * @file exo_ahw_al_dt_wrapper.h
 *
 * @brief This file has mapping functions for digital thermostat
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

#define DIGI_THERMOS_DS620

#ifdef DIGI_THERMOS_DS620
#include "exo_ahw_vdp_dt_ds620.h"
#endif

/**
 * @brief Mapping API to initialize the control block memory of DS620
 * @param[in]  ahw_al_hdt - instance pointer of digital thermostat
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_init(ahw_al_dt_hdle *ahw_al_hdt);

/**
 * @brief Mapping API to deinitalizes the control block memory of DS620
 * @param[in]  ahw_al_hdt - instance pointer of digital thermostat
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_deinit(ahw_al_dt_hdle *ahw_al_hdt);

/**
 * @brief Mapping API to set high temperature threshold
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[in] high_temp_threshold – high temperature threshold in celsius
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_set_temperature_high_threshold (ahw_al_dt_hdle *al_dt, double high_temp_threshold);

/**
 * @brief Mapping API to set low temperature threshold
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[out] low_temp_threshold – low temperature threshold in celsius
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_set_temperature_low_threshold (ahw_al_dt_hdle *al_dt, double low_temp_threshold);

/**
 * @brief Mapping API to read the temperature
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[out] temperature – temperature in celsius is updated in this variable
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_get_temperature (ahw_al_dt_hdle *al_dt,double* temperature);

/**
 * @brief Mapping API to configure the sensor
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_sensor_config (ahw_al_dt_hdle *al_dt);

/**
 * @brief Mapping API to set resolution
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[in] res – ADC resolution value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_set_resolution (ahw_al_dt_hdle *al_dt, digital_thermos_resolution res);

/**
 * @brief Mapping API to get resolution
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[in] res – ADC resolution pointer
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_get_resolution(ahw_al_dt_hdle *al_dt , digital_thermos_resolution *res);

/**
 * @brief Mapping API to set operating mode
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[in] mode – operating mode it can be either oneshot or continuous conversion
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_set_conv_mode (ahw_al_dt_hdle *al_dt,uint8_t mode);

/**
 * @brief Mapping API to set PO pin logic level
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[in] lvl – PO pin level type
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_set_po_lvl (ahw_al_dt_hdle *al_dt, uint8_t lvl);

/**
 * @brief Mapping API to reset the DS620
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_reset(ahw_al_dt_hdle *al_dt);

/**
 * @brief Mapping API to start temperature conversion
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_start_conversion(ahw_al_dt_hdle *al_dt);

/**
 * @brief Mapping API to stop temperature conversion
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_stop_conversion(ahw_al_dt_hdle *al_dt);

/**
 * @brief Mapping API to get PO pin logic level
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_get_po_lvl(ahw_al_dt_hdle *al_dt,uint8_t *lvl);

/**
 * @brief Mapping API to get operating mode of temperature sensor
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[out] mode - pointer of PO pin logic level
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_get_mode(ahw_al_dt_hdle *al_dt,uint8_t *mode);

/**
 * @brief Mapping API to set the PO pin level alert status
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[in]  lvl - pointer of PO pin logic level
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_set_po_lvl_alert_sts (ahw_al_dt_hdle *al_dt, uint8_t* lvl);

/**
 * @brief Mapping API to get low temperature threshold
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[out] low_temp_thrshld - pointer to low temperature threshold
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_get_temperature_low_thrshd(ahw_al_dt_hdle *al_dt,double *low_temp_thrshld);

/**
 * @brief Mapping API to get high temperature threshold
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @param[out] high_temp_thrshld - pointer to high temperature threshold
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_get_temperature_high_thrshd(ahw_al_dt_hdle *al_dt,double *high_temp_thrshld);

/**
 * @brief Mapping API to reset the alert flag
 * @param[in]  al_dt - instance pointer of digital thermostat
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_common_reset_alert_flag(ahw_al_dt_hdle *al_dt);





#endif /* _AHW_AL_WRAPPER_H_ */

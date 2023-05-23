/**
 * @file exo_ahw_vdp_dt_ds620.h
 *
 * @brief This file contains the vendor driver porting function prototype of digital thermostat
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

#ifndef _AHW_AL_DS620_H_
#define _AHW_AL_DS620_H_


#include "exo_hal_common.h"
#include "exo_ahw_al_dt_common.h"
#include "exo_io_al_i2c_common.h"

/**
 * @brief API to initialize the control block memory of DS620
 * @param[in]  al_dt - instance pointer of DS620
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_init (ahw_al_dt_hdle *al_dt);

/**
 * @brief API to deinitalizes the control block memory of DS620
 * @param[in]  al_dt - instance pointer of DS620
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_deinit (ahw_al_dt_hdle *al_dt);

/**
 * @brief API to set high temperature threshold
 * @param[in]  al_dt - instance pointer of DS620
 * @param[in] high_temp_thrshd – high temperature threshold in celsius
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_set_temperature_high_threshold (ahw_al_dt_hdle *al_dt, double high_temp_threshold);

/**
 * @brief API to set low temperature threshold
 * @param[in]  al_dt - instance pointer of DS620
 * @param[in] low_temp_thrshd – low temperature threshold in celsius
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_set_temperature_low_threshold (ahw_al_dt_hdle *al_dt, double low_temp_threshold);

/**
 * @brief API to read the temperature
 * @param[in]  al_dt - instance pointer of DS620
 * @param[out] temperature – temperature in celsius is udpated in this variable
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_get_temperature (ahw_al_dt_hdle *al_dt,double* temperature);

/**
 * @brief API to set temperature,this is used only for testing purpose
 * @param[in]  al_dt - instance pointer of DS620
 * @param[in] temperature –set temperature for the DS620, this will be used for testing
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_set_temperature (ahw_al_dt_hdle *al_dt, double temperature);

/**
 * @brief Configurations is done in this function
 * @param[in]  al_dt - instance pointer of DS620
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_config (ahw_al_dt_hdle *al_dt);

/**
 * @brief API to set resolution
 * @param[in]  al_dt - instance pointer of DS620
 * @param[in] res – ADC resolution value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_set_resolution (ahw_al_dt_hdle *al_dt, digital_thermos_resolution res);

/**
 * @brief API to get resolution
 * @param[in]  al_dt - instance pointer of DS620
 * @param[in] res – ADC resolution pointer
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_get_resolution(ahw_al_dt_hdle *al_dt , digital_thermos_resolution *res);

/**
 * @brief API to set operating mode
 * @param[in]  al_dt - instance pointer of DS620
 * @param[in] mode – operating mode it can be either oneshot or continuous conversion
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_set_conv_mode (ahw_al_dt_hdle *al_dt,uint8_t mode);

/**
 * @brief API to set PO pin logic level
 * @param[in]  al_dt - instance pointer of DS620
 * @param[in] lvl – PO pin level type
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_set_po_lvl (ahw_al_dt_hdle *al_dt, uint8_t lvl);

/**
 * @brief API to reset the DS620
 * @param[in]  al_dt - instance pointer of DS620
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_reset(ahw_al_dt_hdle *al_dt);

/**
 * @brief API to start temperature conversion
 * @param[in]  al_dt - instance pointer of DS620
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_start_conversion(ahw_al_dt_hdle *al_dt);

/**
 * @brief API to stop temperature conversion
 * @param[in]  al_dt - instance pointer of DS620
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_stop_conversion(ahw_al_dt_hdle *al_dt);

/**
 * @brief API to get PO pin logic level
 * @param[in]  al_dt - instance pointer of DS620
 * @param[out]  lvl - pointer of PO pin logic level
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_get_po_lvl(ahw_al_dt_hdle *al_dt,uint8_t *lvl);

/**
 * @brief API to get operating mode of temperature sensor
 * @param[in]  al_dt - instance pointer of DS620
 * @param[out]  mode - pointer of PO pin logic level
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_get_mode(ahw_al_dt_hdle *al_dt,uint8_t *mode);

/**
 * @brief API to set the PO pin level alert status
 * @param[in]  al_dt - instance pointer of DS620
 * @param[in]  alert_sts - pointer of alert status
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_get_po_lvl_alert_sts(ahw_al_dt_hdle *al_dt,uint8_t *alert_sts);

/**
 * @brief API to get low temperature threshold
 * @param[in]  al_dt - instance pointer of DS620
 * @param[out] low_temp_thrshld - pointer to low temperature threshold
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_get_temperature_low_thrshd(ahw_al_dt_hdle *al_dt, double *low_temp_thrshld);

/**
 * @brief API to get high temperature threshold
 * @param[in]  al_dt - instance pointer of DS620
 * @param[out] high_temp_thrshld - pointer to high temperature threshold
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_get_temperature_high_thrshd(ahw_al_dt_hdle *al_dt, double *high_temp_thrshld);

/**
 * @brief API to reset the alert flag
 * @param[in]  al_dt - instance pointer of DS620
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_dt_ds620_reset_alert_flag(ahw_al_dt_hdle *al_dt);


#endif /* _AHW_AL_IMU_BMX160_H_ */

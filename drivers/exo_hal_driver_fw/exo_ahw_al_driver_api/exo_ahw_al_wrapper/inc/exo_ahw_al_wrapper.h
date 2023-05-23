/**
 * @file exo_ahw_al_wrapper.h
 *
 * @brief This file has mapping functions for IMU sensor
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

#ifndef _AHW_AL_WRAPPER_H_
#define _AHW_AL_WRAPPER_H_

#define IMU_MBX160

#ifdef IMU_MBX160
#include "exo_ahw_vdp_imu_bmx160.h"
#endif

/**
 * @brief Mapping API initializes the control block memory of IMU sensor
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_init(ahw_al_imu_hdle *ahw_al_himu);

/**
 * @brief Mapping API resets and restart the device
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_soft_reset(ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API configure the power mode, range and bandwidth of sensor
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_set_sensor_config(ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API get gyro and acceleration configuration
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_get_sensor_config(ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API set the power mode of IMU
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_set_power_mode(ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API get power mode of IMU
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_get_power_mode(ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API get the IMU data
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_get_sensor_data(ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API configures any motion detect interrupt
 * @param[in] al_himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_any_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API configures significant motion detect interrupt
 * @param[in] al_himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_sig_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API configures no motion detect interrupt
 * @param[in] al_himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_no_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API configures orient detect interrupt
 * @param[in] al_himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_orient_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API configures flat detect interrupt
 * @param[in] al_himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_flat_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API configures freefall detect interrupt
 * @param[in] al_himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_freefall_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief Mapping API configures shock detect interrupt
 * @param[in] al_himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_common_shock_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

#endif /* _AHW_AL_WRAPPER_H_ */

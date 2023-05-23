/**
 * @file exo_ahw_vdp_imu_bmx160.h
 *
 * @brief This file contains vendor driver porting function prototype of IMU sensor
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


#ifndef _AHW_AL_IMU_BMX160_H_
#define _AHW_AL_IMU_BMX160_H_

#include "exo_hal_common.h"
#include "exo_ahw_al_imu_common.h"
#include "exo_io_al_i2c_common.h"
/**
 * @brief This API initializes the control block memory of IMU sensor
 * @param[in] ahw_al_himu - instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_init(ahw_al_imu_hdle *ahw_al_himu);

/**
 * @brief This API configure the power mode, range and bandwidth of sensor
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_set_sensor_config(ahw_al_imu_hdle *al_himu);

/**
 * @brief This API reset and restart the device
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_soft_reset(ahw_al_imu_hdle *al_himu);

/**
 * @brief This API get gyroscope and accelerometer configuration
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_get_sensor_config(ahw_al_imu_hdle *al_himu);

/**
 * @brief This API set the power mode of sensor
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_set_power_mode(ahw_al_imu_hdle *al_himu);

/**
 * @brief This API get power mode of sensor
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_get_power_mode(ahw_al_imu_hdle *al_himu);

/**
 * @brief This API get the sensor data
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_get_sensor_data(ahw_al_imu_hdle *al_himu);

/**
 * @brief This API configures any motion detect interrupt
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_any_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu);

/**
 * @brief This API configures significant motion detect interrupt
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_sig_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu);

/**
 * @brief This API configures no motion detect interrupt
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_no_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu);

/**
 * @brief This API configures orientation detect interrupt
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_orient_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu);

/**
 * @brief This API configures flat detect interrupt
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_flat_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu);

/**
 * @brief This API configures freefall detect interrupt
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_freefall_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu);

/**
 * @brief This API configures shock detect interrupt
 * @param[in] al_himu - instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_imu_bmx160_shock_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu);

/**
 * @brief This API read the data through I2C
 * @param[in] hi2c - instance pointer of ioal_i2c_hdle
 * @param[in] dev_addr - device address
 * @param[in] reg_addr - register address
 * @param[out] data - pointer to a data
 * @param[in] len - length of a data
 * @retval hal_ret_sts - returns the success or error code
 */
int8_t bmi160_i2c_read(ioal_i2c_hdle *hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/**
 * @brief This API write the data through I2C
 * @param[in] hi2c - instance pointer of ioal_i2c_hdle
 * @param[in] dev_addr - device address
 * @param[in] reg_addr - register address
 * @param[in] data - pointer to a data
 * @param[in] len - length of a data
 * @retval hal_ret_sts - returns the success or error code
 */
int8_t bmi160_i2c_write(ioal_i2c_hdle *hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);



#endif /* _AHW_AL_IMU_BMX160_H_ */

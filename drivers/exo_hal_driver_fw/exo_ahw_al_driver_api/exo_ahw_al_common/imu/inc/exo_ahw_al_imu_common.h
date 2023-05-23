/**
 * @file exo_ahw_al_imu_common.h
 *
 * @brief This file contains function prototypes ,structures and
 * enumerations for IMU sensor
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

#ifndef _AHW_AL_IMU_COMMON_H_
#define _AHW_AL_IMU_COMMON_H_

#include <stdint.h>
#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_ahw_al_common.h"

/**
 * @brief IMU sensor interrupt types
 */
typedef enum _imu_int_types
{
    IMU_ACC_ANY_MOTION_INT,						/*!< accelerometer any motion interrupt */
    IMU_ACC_SIG_MOTION_INT,						/*!< accelerometer significant motion interrupt */
    IMU_ACC_ORIENT_INT,							/*!< accelerometer orientation interrupt */
    IMU_ACC_FLAT_INT,							/*!< accelerometer flat interrupt */
    IMU_ACC_HIGH_G_INT,							/*!< accelerometer high-g interrupt */
    IMU_ACC_LOW_G_INT,							/*!< accelerometer low-g interrupt */
    IMU_ACC_SLOW_NO_MOTION_INT,					/*!< accelerometer slow/no-motion interrupt */
    IMU_ACC_GYRO_DATA_RDY_INT,					/*!< accelerometer and gyroscope data ready interrupt */
    IMU_ACC_GYRO_FIFO_FULL_INT,					/*!< accelerometer and gyroscope fifo full interrupt */
    IMU_ACC_GYRO_FIFO_WATERMARK_INT				/*!< accelerometer and gyroscope fifo watermark interrupt */
}imu_int_types;

/*!
 * @brief IMU sensor select structure
 */
typedef enum _imu_select_sensor
{
    IMU_ACCEL_ONLY = 1,						/*!< accelerometer only */
    IMU_GYRO_ONLY,							/*!< gyroscope only */
    IMU_BOTH_ACCEL_AND_GYRO,				/*!< both acceleration and gyroscope */
    IMU_MAG_ONLY,							/*!< magnetometer only */
    IMU_ACCEL_GYRO_AND_MAG					/*!< acceleration gyroscope and magnetometer */
}imu_select_sensor;

/*!
 * @brief IMU sensor data structure - accelerometer, gyroscope
 */
typedef struct _imu_sensor_data
{
    int16 x;					/*!< x-axis sensor data			*/
    int16 y;					/*!< y-axis sensor data			*/
    int16 z;					/*!< z-axis sensor data			*/
    uint32 sensortime;			/*!< sensor time				*/
}imu_sensor_data;

/*!
 * @brief IMU sensor data structure which comprises of magnetometer data
 */
typedef struct _imu_mag_sensor_data
{
    int16_t x;					/*!< x-axis sensor data			*/
    int16_t y;					/*!< y-axis sensor data			*/
    int16_t z;					/*!< z-axis sensor data			*/
    int16_t rhall;				/*!< rhall data					*/
    uint32_t sensortime;		/*!< sensor time			    */
}imu_mag_sensor_data;

/*!
 * @brief IMU sensor configuration structure
 */
typedef struct _imu_cfg
{
    uint8 power;				/*!< power						*/
    uint8 odr;					/*!< operating data rate		*/
    uint8 range;				/*!< range						*/
    uint8 bw;					/*!< bandwidth					*/
}imu_cfg;

/*!
 * @brief IMU sensor magnetometer interface sensor configuration structure
 */
typedef struct _mag_if_cfg
{
    uint8_t mag_if_sensor_enable : 1;		/*!< magnetometer enable				*/
    uint8_t manual_enable : 1;				/*!< magnetometer manual enable			*/
    uint8_t mag_if_rd_burst_len : 2;		/*!< magnetometer read bus length				*/
    uint8_t mag_if_odr : 4;					/*!< magnetometer operating data rate				*/
    uint8_t if_pwr_mode;					/*!< power mode			*/
    uint8_t aux_i2c_addr;					/*!< i2c address		*/
}mag_if_cfg;

/*!
 * @brief IMU sensor magnetometer configuration structure
 */
typedef struct _imu_mag_cfg
{
    struct _mag_if_cfg mag_if_cfg;			/*!< magnetometer configuration structure						*/
    uint8_t pwr_mode;						/*!< power mode				*/
    uint8_t op_mode;						/*!< operation mode			*/
    uint8_t data_rate;						/*!< data rate				*/
    uint8_t xy_rep;							/*!< xy axis repetion						*/
    uint8_t z_rep;							/*!< z axis repetion							*/
    uint8_t preset_mode;					/*!< present mode			*/

}imu_mag_cfg;

/*!
 * @brief IMU sensor any motion interrupt configuration structure
 */
typedef struct _imu_any_mot_int_cfg
{
    uint8 anymotion_en : 1;					/*!< any motion enable		*/
    uint8 anymotion_x : 1;					/*!< any motion x axis		*/
    uint8 anymotion_y : 1;					/*!< any motion y axis		*/
    uint8 anymotion_z : 1;					/*!< any motion z axis		*/
    uint8 anymotion_dur : 2;				/*!< any motion duration	*/
    uint8 anymotion_data_src : 1;			/*!< any motion data source	*/
    uint8 anymotion_thr;					/*!< any motion threshold	*/
}imu_any_mot_int_cfg;

/*!
 * @brief IMU sensor significant motion interrupt configuration structure
 */
typedef struct _imu_sig_mot_int_cfg
{
    uint8 sig_mot_skip : 2;					/*!< significant motion skip			*/
    uint8 sig_mot_proof : 2;				/*!< significant motion proof			*/
    uint8 sig_data_src : 1;					/*!< significant data source			*/
    uint8 sig_en : 1;						/*!< significant enable				    */
    uint8 sig_mot_thres;					/*!< significant motion threshold		*/
}imu_sig_mot_int_cfg;

/*!
 * @brief IMU sensor no motion interrupt configuration structure
 */
typedef struct _imu_no_motion_int_cfg
{
    uint16 no_motion_x : 1;					/*!< no motion x axis				*/
    uint16 no_motion_y : 1;					/*!< no motion y axis				*/
    uint16 no_motion_z : 1;					/*!< no motion z axis				*/
    uint16 no_motion_dur : 6;				/*!< no motion duration				*/
    uint16 no_motion_sel : 1;				/*!< no motion selection			*/
    uint16 no_motion_src : 1;				/*!< no motion source				*/
    uint8 no_motion_thres;					/*!< no motion threshold			*/
}imu_no_motion_int_cfg;

/*!
 * @brief IMU sensor orient interrupt configuration structure
 */
typedef struct _imu_orient_int_cfg
{
    uint16 orient_mode : 2;					/*!< orient mode								*/
    uint16 orient_blocking : 2;				/*!< orient blocking							*/
    uint16 orient_hyst : 4;					/*!< orient hysteresis							*/
    uint16 orient_theta : 6;				/*!< orient theta								*/
    uint16 orient_ud_en : 1;				/*!< enable/disable orientation interrupt		*/
    uint16 axes_ex : 1;						/*!< exchange x-axis and z-axis					*/
    uint8 orient_en : 1;					/*!< orient enable/disable						*/
}imu_orient_int_cfg;

/*!
 * @brief IMU sensor flat detect interrupt configuration structure
 */
typedef struct _imu_flat_detect_int_cfg
{
    uint16 flat_theta : 6;					/*!< flat theta					*/
    uint16 flat_hy : 3;						/*!< flat hysteresis			*/
    uint16 flat_hold_time : 2;				/*!< flat hold time				*/
    uint16 flat_en : 1;						/*!< flat enable				*/
}imu_flat_detect_int_cfg;

/*!
 * @brief IMU sensor low-g interrupt configuration structure
 */
typedef struct _imu_low_g_int_cfg
{
    uint8 low_dur;							/*!< low duration				*/
    uint8 low_thres;						/*!< low threshold				*/
    uint8 low_hyst : 2;					    /*!< low hysteresis				*/
    uint8 low_mode : 1;						/*!< low mode					*/
    uint8 low_data_src : 1;					/*!< low data source			*/
    uint8 low_en : 1;						/*!< low enable					*/
}imu_low_g_int_cfg;

/*!
 * @brief IMU sensor high-g interrupt configuration structure
 */
typedef struct _imu_high_g_int_cfg
{
    uint8 high_g_x : 1;						/*!< high-g interrupt-x			*/
    uint8 high_g_y : 1;						/*!< high-g interrupt-y			*/
    uint8 high_g_z : 1;						/*!< high-g interrupt-z			*/
    uint8 high_hy : 2;						/*!< high-g hysteresis			*/
    uint8 high_data_src : 1;				/*!< high data source			*/
    uint8 high_thres;						/*!< high threshold				*/
    uint8 high_dur;							/*!< high duration				*/
}imu_high_g_int_cfg;

/*!
 * @brief IMU sensor interrupt type configuration union
 */
typedef union _imu_int_type_cfg
{
    imu_any_mot_int_cfg any_motion_int;			/*!< any motion interrupt configuration structure variable			*/
    imu_sig_mot_int_cfg sig_motion_int;			/*!< significant motion interrupt configuration structure variable	*/
    imu_no_motion_int_cfg no_motion_int;		/*!< no motion interrupt configuration structure variable			*/
    imu_orient_int_cfg orient_int;				/*!< orient interrupt configuration structure variable				*/
    imu_flat_detect_int_cfg flat_int;			/*!< flat interrupt configuration structure variable				*/
    imu_low_g_int_cfg low_g_int;				/*!< low-g interrupt configuration structure variable				*/
    imu_high_g_int_cfg high_g_int;				/*!< high-g interrupt configuration structure variable				*/

}imu_int_type_cfg;

/*!
 * @brief IMU sensor interrupt setting structure
 */
typedef struct _imu_int_settg
{
    imu_int_types int_type;						/*!< interrupt type structure variable				   */
    imu_int_type_cfg int_type_cfg;				/*!< interrupt type configuration structure variable   */

}imu_int_settg;

/*!
 * @brief IMU sensor control block structure
 */
typedef struct _ahw_al_imu_hdle
{
    ahw_al_gen_info ahw_gen_info;			/*!< application hardware general information	     */
    imu_cfg accel_cfg;						/*!< accelerometer configuration				  		 */
    imu_cfg gyro_cfg;						/*!< gyroscope configuration structure variable			 */
    imu_mag_cfg mag_cfg;					/*!< magnetometer configuration structure variable			 */
    imu_sensor_data accel_data;				/*!< accelerometer data structure variable			 */
    imu_sensor_data gyro_data;				/*!< gyroscope data structure variable					 */
    imu_mag_sensor_data mag_data;			/*!< magnetometer data structure variable					 */
}ahw_al_imu_hdle;

/**
 * @brief This API initializes the control block memory and do the
 * basic configurations for IMU sensor instance.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_init(void);

/**
 * @brief This API resets and restart the device
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_soft_reset(ahw_al_imu_hdle *himu);

/**
 * @brief This API configure the power mode, range and bandwidth of sensor
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_set_sensor_config(ahw_al_imu_hdle *himu);

/**
 * @brief This API get gyro and accelerometer configuration
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_get_sensor_config(ahw_al_imu_hdle *himu);

/**
 * @brief This API set the power mode of sensor
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_set_power_mode(ahw_al_imu_hdle *himu);

/**
 * @brief This API get the power mode of sensor
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_get_power_mode(ahw_al_imu_hdle *himu);

/**
 * @brief This API get the sensor data
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_get_sensor_data(ahw_al_imu_hdle *himu);

/**
 * @brief This API configures any motion detect interrupt
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_any_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief This API configures significant  motion detect interrupt
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_sig_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief This API configures no motion detect interrupt
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_no_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief This API configures orientation motion detect interrupt
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_orient_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief This API configures flat motion detect interrupt
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_flat_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief This API configures freefall detect interrupt
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_freefall_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

/**
 * @brief This API configures shock detect interrupt
 * @param[in] himu - AHAL instance pointer of IMU sensor.
 * @param[in] int_config - pointer to a imu_int_type_cfg structure
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_imu_shock_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu);

#endif /* _AHW_AL_IMU_COMMON_H_ */

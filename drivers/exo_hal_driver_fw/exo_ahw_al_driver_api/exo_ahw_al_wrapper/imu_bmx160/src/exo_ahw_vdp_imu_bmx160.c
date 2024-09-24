/**
 * @file exo_ahw_vdp_imu_bmx160.c
 *
 * @brief This file contains the vendor driver porting function of BMX160 IMU sensor
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

#include <stdio.h>
#include <unistd.h>
#include "exo_ahw_vdp_imu_bmx160.h"
#include "bmx160.h"
#include "exo_osal.h"

struct bmi160_dev himu; ///< BMI 160 dev
extern ahw_io_map *ahw_io_lookup_tble[MAX_AH_INST_ID]; ///< Hardware IO lookup table
extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];   ///< Interface instance handle pointer
struct bmi160_int_settg vdp_int_config; ///< BMI160 VDP interface configuration


/**
 * @brief This API configure the interface
 * @param[in] dev - pointer of bmi160_dev
 * @retval hal_ret_sts - returns the success or error code
 */
void bmi160_interface_cfg(struct bmi160_dev *dev);


/**
 * @brief Delay function
 */
void delay(uint32_t period)
{
#ifndef LINUX_TEMP_PORT
    os_delay(period);
#endif
}

/**
 * @brief API to configure the interface
 */
void bmi160_interface_cfg(struct bmi160_dev *dev)
{
    dev->read = bmi160_i2c_read;
    dev->write = bmi160_i2c_write;
    dev->delay_ms=delay;
}

/**
 * @brief API to read the data through I2C
 */
int8_t bmi160_i2c_read(ioal_i2c_hdle *hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    int8_t rslt;
    if(BMI160_OK == io_hal_i2c_transmit(hi2c, (uint16)dev_addr, &reg_addr, 1, 500))
    {
        if(BMI160_OK == io_hal_i2c_receive(hi2c, (uint16)dev_addr, data, len, 500))
        {
            rslt = BMI160_OK;
        }
        else
        {
            rslt = BMI160_E_COM_FAIL;
        }
    }
    else
    {
        rslt = BMI160_E_COM_FAIL;
    }
    return rslt;
}

/**
 * @brief API to write the data through I2C
 */
int8_t bmi160_i2c_write(ioal_i2c_hdle *hi2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    int8_t rslt;
    if(BMI160_OK == io_hal_i2c_transmit(hi2c, (uint16)dev_addr, &reg_addr, 1, 500))
    {
        if(BMI160_OK == io_hal_i2c_transmit(hi2c, (uint16)dev_addr, data, len, 500))
        {
            rslt = BMI160_OK;
        }
        else
        {
            rslt = BMI160_E_COM_FAIL;
        }
    }
    else
    {
        rslt = BMI160_E_COM_FAIL;
    }
    return rslt;
}

/**
 * @brief API to initialize the IMU sensor
 */
hal_ret_sts ahw_vdp_imu_bmx160_init(ahw_al_imu_hdle *ahw_al_himu)
{
    hal_ret_sts sts = HAL_MAX_ERR;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IMU - AH-Vendor driver porting layer Initialise");
    printf("\n EXO IMU - AH-Vendor driver Initialise");
    printf("\n EXO IMU - AH-Vendor driver Initialisation completed successfully ");
    usleep(100000);
    printf("\n EXO IMU - AH-Vendor driver porting layer initialisation completed successfully");

#else

    himu.intf = BMI160_I2C_INTF;
    himu.io_intf_hdle = intf_inst_hdle_ptr[ahw_io_lookup_tble[ahw_al_himu->ahw_gen_info.ahw_inst_id]->io_instance_id];
    himu.id=ahw_io_lookup_tble[ahw_al_himu->ahw_gen_info.ahw_inst_id]->slv_addr;
    bmi160_interface_cfg(&himu);
    if(HAL_SCS == bmi160_init(&himu))
    {
        ahw_al_himu->ahw_gen_info.vdp_inst_hdle = (void*)&himu;
        ahw_al_himu->ahw_gen_info.io_intf_hdle=himu.io_intf_hdle;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
#endif
    return sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief API to reset and restart the IMU sensor
 */
hal_ret_sts ahw_vdp_imu_bmx160_soft_reset(ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;

    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == bmi160_soft_reset(vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API configure the power mode, range and bandwidth of sensor
 */
hal_ret_sts ahw_vdp_imu_bmx160_set_sensor_config(ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;

    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;

    vdh_imu->accel_cfg.bw = al_himu->accel_cfg.bw;
    vdh_imu->accel_cfg.odr = al_himu->accel_cfg.odr;
    vdh_imu->accel_cfg.range = al_himu->accel_cfg.range;

    vdh_imu->gyro_cfg.bw = al_himu->gyro_cfg.bw;
    vdh_imu->gyro_cfg.odr = al_himu->gyro_cfg.odr;
    vdh_imu->gyro_cfg.range = al_himu->gyro_cfg.range;

    vdh_imu->mag_cfg.xy_rep = al_himu->mag_cfg.xy_rep;
    vdh_imu->mag_cfg.z_rep = al_himu->mag_cfg.z_rep;
    vdh_imu->mag_cfg.op_mode = al_himu->mag_cfg.op_mode;
    vdh_imu->mag_cfg.data_rate = al_himu->mag_cfg.data_rate;
    vdh_imu->mag_cfg.bmx_mag_if_cfg.mag_if_odr = al_himu->mag_cfg.mag_if_cfg.mag_if_odr;
    vdh_imu->mag_cfg.bmx_mag_if_cfg.mag_if_rd_burst_len = al_himu->mag_cfg.mag_if_cfg.mag_if_rd_burst_len;

    if(HAL_SCS == bmi160_set_sens_conf(vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API get gyroscope and accelerometer configuration
 */
hal_ret_sts ahw_vdp_imu_bmx160_get_sensor_config(ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;

    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == bmi160_get_sens_conf(vdh_imu))
    {
        al_himu->accel_cfg.bw = vdh_imu->accel_cfg.bw;
        al_himu->accel_cfg.odr = vdh_imu->accel_cfg.odr;
        al_himu->accel_cfg.range = vdh_imu->accel_cfg.range;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API set the power mode of sensor
 */
hal_ret_sts ahw_vdp_imu_bmx160_set_power_mode(ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;

    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;

    vdh_imu->accel_cfg.power = al_himu->accel_cfg.power;
    vdh_imu->gyro_cfg.power = al_himu->gyro_cfg.power;
    vdh_imu->mag_cfg.bmx_mag_if_cfg.if_pwr_mode = al_himu->mag_cfg.mag_if_cfg.if_pwr_mode;
    vdh_imu->mag_cfg.op_mode = al_himu->mag_cfg.op_mode;

    if(HAL_SCS == bmi160_set_power_mode(vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API get the power mode of sensor
 */
hal_ret_sts ahw_vdp_imu_bmx160_get_power_mode(ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;

    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;

    if(HAL_SCS == bmi160_get_power_mode(vdh_imu))
    {
        al_himu->accel_cfg.power = vdh_imu->accel_cfg.power;
        al_himu->gyro_cfg.power = vdh_imu->gyro_cfg.power;
        al_himu->mag_cfg.mag_if_cfg.if_pwr_mode = vdh_imu->mag_cfg.bmx_mag_if_cfg.if_pwr_mode;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API get the sensor data
 */
hal_ret_sts ahw_vdp_imu_bmx160_get_sensor_data(ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;

    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;

    if(HAL_SCS == bmi160_get_sensor_data(BMI160_BOTH_ACCEL_AND_GYRO,
            (struct bmi160_sensor_data*)&al_himu->accel_data,
            (struct bmi160_sensor_data*)&al_himu->gyro_data,
            (struct bmx160_mag_sensor_data*)&al_himu->mag_data,vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API to read the data through I2C
 */
static inline void ahw_vdp_imu_bmx160_default_intr_config(void)
{
    vdp_int_config.fifo_full_int_en = 0;
    vdp_int_config.fifo_wtm_int_en = 0;
    vdp_int_config.int_channel = BMI160_INT_CHANNEL_1;
    vdp_int_config.int_type = BMI160_ACC_ANY_MOTION_INT;
    vdp_int_config.int_pin_settg.edge_ctrl = 1;
    vdp_int_config.int_pin_settg.input_en = 0;
    vdp_int_config.int_pin_settg.output_en = 1;
    vdp_int_config.int_pin_settg.output_mode = 0;
    vdp_int_config.int_pin_settg.output_type = 0;
    vdp_int_config.int_pin_settg.edge_ctrl = 1;
    vdp_int_config.int_pin_settg.latch_dur = 0;
}

/**
 * @brief API configures any motion detect interrupt
 */
hal_ret_sts ahw_vdp_imu_bmx160_any_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;
    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;
    ahw_vdp_imu_bmx160_default_intr_config();

    vdp_int_config.int_type_cfg.acc_any_motion_int.anymotion_data_src = int_config->any_motion_int.anymotion_data_src;
    vdp_int_config.int_type_cfg.acc_any_motion_int.anymotion_dur = int_config->any_motion_int.anymotion_dur;
    vdp_int_config.int_type_cfg.acc_any_motion_int.anymotion_en = int_config->any_motion_int.anymotion_en;
    vdp_int_config.int_type_cfg.acc_any_motion_int.anymotion_thr = int_config->any_motion_int.anymotion_thr;
    vdp_int_config.int_type_cfg.acc_any_motion_int.anymotion_x = int_config->any_motion_int.anymotion_x;
    vdp_int_config.int_type_cfg.acc_any_motion_int.anymotion_y = int_config->any_motion_int.anymotion_y;
    vdp_int_config.int_type_cfg.acc_any_motion_int.anymotion_z = int_config->any_motion_int.anymotion_z;

    if(HAL_SCS == bmi160_set_int_config(&vdp_int_config, vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API configures significant  motion detect interrupt
 */
hal_ret_sts ahw_vdp_imu_bmx160_sig_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;
    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;
    ahw_vdp_imu_bmx160_default_intr_config();

    vdp_int_config.int_type_cfg.acc_sig_motion_int.sig_data_src = int_config->sig_motion_int.sig_data_src;
    vdp_int_config.int_type_cfg.acc_sig_motion_int.sig_en = int_config->sig_motion_int.sig_en;
    vdp_int_config.int_type_cfg.acc_sig_motion_int.sig_mot_proof = int_config->sig_motion_int.sig_mot_proof;
    vdp_int_config.int_type_cfg.acc_sig_motion_int.sig_mot_skip = int_config->sig_motion_int.sig_mot_skip;
    vdp_int_config.int_type_cfg.acc_sig_motion_int.sig_mot_thres = int_config->sig_motion_int.sig_mot_thres;

    if(HAL_SCS == bmi160_set_int_config(&vdp_int_config, vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API configures no motion detect interrupt
 */
hal_ret_sts ahw_vdp_imu_bmx160_no_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;
    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;
    ahw_vdp_imu_bmx160_default_intr_config();

    vdp_int_config.int_type_cfg.acc_no_motion_int.no_motion_dur = int_config->no_motion_int.no_motion_dur;
    vdp_int_config.int_type_cfg.acc_no_motion_int.no_motion_sel = int_config->no_motion_int.no_motion_sel;
    vdp_int_config.int_type_cfg.acc_no_motion_int.no_motion_src = int_config->no_motion_int.no_motion_src;
    vdp_int_config.int_type_cfg.acc_no_motion_int.no_motion_thres = int_config->no_motion_int.no_motion_thres;
    vdp_int_config.int_type_cfg.acc_no_motion_int.no_motion_x = int_config->no_motion_int.no_motion_x;
    vdp_int_config.int_type_cfg.acc_no_motion_int.no_motion_y = int_config->no_motion_int.no_motion_y;
    vdp_int_config.int_type_cfg.acc_no_motion_int.no_motion_z = int_config->no_motion_int.no_motion_z;

    if(HAL_SCS == bmi160_set_int_config(&vdp_int_config, vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API configures orientation motion detect interrupt
 */
hal_ret_sts ahw_vdp_imu_bmx160_orient_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;
    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;
    ahw_vdp_imu_bmx160_default_intr_config();

    vdp_int_config.int_type_cfg.acc_orient_int.axes_ex = int_config->orient_int.axes_ex;
    vdp_int_config.int_type_cfg.acc_orient_int.orient_blocking = int_config->orient_int.orient_blocking;
    vdp_int_config.int_type_cfg.acc_orient_int.orient_en = int_config->orient_int.orient_en;
    vdp_int_config.int_type_cfg.acc_orient_int.orient_hyst = int_config->orient_int.orient_hyst;
    vdp_int_config.int_type_cfg.acc_orient_int.orient_mode = int_config->orient_int.orient_mode;
    vdp_int_config.int_type_cfg.acc_orient_int.orient_theta = int_config->orient_int.orient_theta;
    vdp_int_config.int_type_cfg.acc_orient_int.orient_ud_en = int_config->orient_int.orient_ud_en;

    if(HAL_SCS == bmi160_set_int_config(&vdp_int_config, vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API configures flat motion detect interrupt
 */
hal_ret_sts ahw_vdp_imu_bmx160_flat_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;
    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;
    ahw_vdp_imu_bmx160_default_intr_config();

    vdp_int_config.int_type_cfg.acc_flat_int.flat_en = int_config->flat_int.flat_en;
    vdp_int_config.int_type_cfg.acc_flat_int.flat_hold_time = int_config->flat_int.flat_hold_time;
    vdp_int_config.int_type_cfg.acc_flat_int.flat_hy = int_config->flat_int.flat_hy;
    vdp_int_config.int_type_cfg.acc_flat_int.flat_theta = int_config->flat_int.flat_theta;

    if(HAL_SCS == bmi160_set_int_config(&vdp_int_config, vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API configures freefall detect interrupt
 */
hal_ret_sts ahw_vdp_imu_bmx160_freefall_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;
    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;
    ahw_vdp_imu_bmx160_default_intr_config();

    vdp_int_config.int_type_cfg.acc_low_g_int.low_data_src = int_config->low_g_int.low_data_src;
    vdp_int_config.int_type_cfg.acc_low_g_int.low_dur = int_config->low_g_int.low_dur;
    vdp_int_config.int_type_cfg.acc_low_g_int.low_en = int_config->low_g_int.low_en;
    vdp_int_config.int_type_cfg.acc_low_g_int.low_hyst = int_config->low_g_int.low_hyst;
    vdp_int_config.int_type_cfg.acc_low_g_int.low_mode = int_config->low_g_int.low_mode;
    vdp_int_config.int_type_cfg.acc_low_g_int.low_thres = int_config->low_g_int.low_thres;

    if(HAL_SCS == bmi160_set_int_config(&vdp_int_config, vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API configures shock detect interrupt
 */
hal_ret_sts ahw_vdp_imu_bmx160_shock_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *al_himu)
{
    hal_ret_sts sts;
    struct bmi160_dev *vdh_imu;
    vdh_imu = (struct bmi160_dev*) al_himu->ahw_gen_info.vdp_inst_hdle;
    ahw_vdp_imu_bmx160_default_intr_config();

    vdp_int_config.int_type_cfg.acc_high_g_int.high_data_src = int_config->high_g_int.high_data_src;
    vdp_int_config.int_type_cfg.acc_high_g_int.high_dur = int_config->high_g_int.high_dur;
    vdp_int_config.int_type_cfg.acc_high_g_int.high_g_x = int_config->high_g_int.high_g_x;
    vdp_int_config.int_type_cfg.acc_high_g_int.high_g_y = int_config->high_g_int.high_g_y;
    vdp_int_config.int_type_cfg.acc_high_g_int.high_g_z = int_config->high_g_int.high_g_z;
    vdp_int_config.int_type_cfg.acc_high_g_int.high_hy = int_config->high_g_int.high_hy;
    vdp_int_config.int_type_cfg.acc_high_g_int.high_thres = int_config->high_g_int.high_thres;

    if(HAL_SCS == bmi160_set_int_config(&vdp_int_config, vdh_imu))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}
#endif

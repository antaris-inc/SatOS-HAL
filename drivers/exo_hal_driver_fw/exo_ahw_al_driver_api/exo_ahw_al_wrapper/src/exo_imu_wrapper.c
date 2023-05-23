/**
 * @file exo_imu_wrapper.c
 *
 * @brief This file has wrapper function of IMU sensor BMX160This file has mapping functions which resolves the
 * instance Id and invokes the vendor driver API for IMU sensor based on the partnumber
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

#include "exo_ahw_vdp_imu_bmx160.h"

/**
 * @brief Mapping API to initializes the control block memory of IMU sensor
 */
hal_ret_sts ahw_al_imu_common_init(ahw_al_imu_hdle *ahw_al_himu)
{
    hal_ret_sts sts;
    switch(ahw_al_himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_init(ahw_al_himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief Mapping API to reset and restart the device
 */
hal_ret_sts ahw_al_imu_common_soft_reset(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_soft_reset(himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to configure the power mode, range and bandwidth of sensor
 */
hal_ret_sts ahw_al_imu_common_set_sensor_config(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_set_sensor_config(himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to get gyro and acceleration configuration
 */
hal_ret_sts ahw_al_imu_common_get_sensor_config(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_get_sensor_config(himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to set the power mode of sensor
 */
hal_ret_sts ahw_al_imu_common_set_power_mode(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_set_power_mode(himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to get power mode of sensor
 */
hal_ret_sts ahw_al_imu_common_get_power_mode(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_get_power_mode(himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to get the sensor data
 */
hal_ret_sts ahw_al_imu_common_get_sensor_data(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_get_sensor_data(himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to configures any motion detect interrupt
 */
hal_ret_sts ahw_al_imu_common_any_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_any_motion_detect_ste_cfg(int_config, himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to configures significant motion detect interrupt
 */
hal_ret_sts ahw_al_imu_common_sig_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_sig_motion_detect_ste_cfg(int_config, himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to configures no motion detect interrupt
 */
hal_ret_sts ahw_al_imu_common_no_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_no_motion_detect_ste_cfg(int_config, himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to configures orient detect interrupt
 */
hal_ret_sts ahw_al_imu_common_orient_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_orient_detect_ste_cfg(int_config, himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to configures flat detect interrupt
 */
hal_ret_sts ahw_al_imu_common_flat_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_flat_detect_ste_cfg(int_config, himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to configures freefall detect interrupt
 */
hal_ret_sts ahw_al_imu_common_freefall_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_freefall_detect_ste_cfg(int_config, himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API to configures shock detect interrupt
 */
hal_ret_sts ahw_al_imu_common_shock_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    switch(himu->ahw_gen_info.ahw_inst_id)
    {
        case IMU_BMX160_OBC_1:
        case IMU_BMX160_OBC_2:
            sts = ahw_vdp_imu_bmx160_shock_detect_ste_cfg(int_config, himu);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}
#endif

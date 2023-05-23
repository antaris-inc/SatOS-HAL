/**
 * @file exo_ahw_al_imu_common.c
 *
 * @brief This file contains abstracted driver function for IMU sensor
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

#include <stdio.h>
#include "exo_ahw_al_imu_common.h"
#include "exo_ahw_al_wrapper.h"
#include "exo_ah_iob_csn.h"
#include "exo_ahdlsd.h"

extern void* ahw_inst_hdle_ptr[MAX_AH_INST_ID];
ahw_al_imu_hdle ahw_al_himu_obc_1;
ahw_al_imu_hdle ahw_al_himu_obc_2;

/**
 * @brief This API inititializes the control block memory of IMU sensor
 */
hal_ret_sts ahw_al_imu_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL IMU Initialise");
#endif
    hal_ret_sts sts;
    ahw_al_himu_obc_1.ahw_gen_info.ahw_inst_id = IMU_BMX160_OBC_1;
    if(HAL_SCS == ahw_al_imu_common_init(&ahw_al_himu_obc_1))
    {
        ahw_inst_hdle_ptr[IMU_BMX160_OBC_1] = &ahw_al_himu_obc_1;
        sts = HAL_SCS;
        if(HAL_SCS != ahdlsd_updt_ah_state(IMU_BMX160_OBC_1, AH_ACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
        if(HAL_SCS != ahiobcsn_updt_ahste(&ahw_al_himu_obc_1.ahw_gen_info, AH_FREE_STATE))
        {
            sts = HAL_AHIOBCSN_FW_ERR;
        }
    }
    else
    {
        sts = HAL_AH_INIT_ERR;
        if(HAL_SCS != ahdlsd_updt_ah_state(IMU_BMX160_OBC_1, AH_ERROR))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
    }

    ahw_al_himu_obc_2.ahw_gen_info.ahw_inst_id = IMU_BMX160_OBC_2;
    if(HAL_SCS == ahw_al_imu_common_init(&ahw_al_himu_obc_2))
    {
        ahw_inst_hdle_ptr[IMU_BMX160_OBC_2] = &ahw_al_himu_obc_2;
        sts = HAL_SCS;
        if(HAL_SCS != ahdlsd_updt_ah_state(IMU_BMX160_OBC_2, AH_ACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
        if(HAL_SCS != ahiobcsn_updt_ahste(&ahw_al_himu_obc_2.ahw_gen_info, AH_FREE_STATE))
        {
            sts = HAL_AHIOBCSN_FW_ERR;
        }
    }
    else
    {
        sts = HAL_AH_INIT_ERR;
        if(HAL_SCS != ahdlsd_updt_ah_state(IMU_BMX160_OBC_2, AH_ERROR))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
    }
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL IMU Initialisation completed successfully");
#endif
    return sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief This API reset and restart the device.
 */
hal_ret_sts ahw_al_imu_soft_reset(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;

    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_soft_reset(himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            if(HAL_SCS != ahdlsd_updt_ah_state(himu->ahw_gen_info.ahw_inst_id, AH_ERROR))
            {
                sts = HAL_AHDLSD_FW_ERR;
            }
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API configures the power mode, range and bandwidth
 * of sensor.
 */
hal_ret_sts ahw_al_imu_set_sensor_config(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_set_sensor_config(himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API gets accelerometer and gyroscope configurations.
 */
hal_ret_sts ahw_al_imu_get_sensor_config(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_get_sensor_config(himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API sets the power mode of sensor
 */
hal_ret_sts ahw_al_imu_set_power_mode(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_set_power_mode(himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API gets the power mode of sensor
 */
hal_ret_sts ahw_al_imu_get_power_mode(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_get_power_mode(himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API gets the sensor data
 */
hal_ret_sts ahw_al_imu_get_sensor_data(ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_get_sensor_data(himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API configures any motion detection interrupt
 */
hal_ret_sts ahw_al_imu_any_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_any_motion_detect_ste_cfg(int_config, himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API configures the signal motion detection interrupt
 */
hal_ret_sts ahw_al_imu_sig_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_sig_motion_detect_ste_cfg(int_config, himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API configures the no motion detection interrupt
 */
hal_ret_sts ahw_al_imu_no_motion_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_no_motion_detect_ste_cfg(int_config, himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API configures the orient detection interrupt
 */
hal_ret_sts ahw_al_imu_orient_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_orient_detect_ste_cfg(int_config, himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API configures the flat detection interrupt
 */
hal_ret_sts ahw_al_imu_flat_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_flat_detect_ste_cfg(int_config, himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API configures the freefall detection interrupt
 */
hal_ret_sts ahw_al_imu_freefall_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_freefall_detect_ste_cfg(int_config, himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief This API configures the shock detection interrupt
 */
hal_ret_sts ahw_al_imu_shock_detect_ste_cfg(imu_int_type_cfg *int_config, ahw_al_imu_hdle *himu)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&himu->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_imu_common_shock_detect_ste_cfg(int_config, himu))
        {
            ahiobcsn_updt_ahste(&himu->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}


#endif

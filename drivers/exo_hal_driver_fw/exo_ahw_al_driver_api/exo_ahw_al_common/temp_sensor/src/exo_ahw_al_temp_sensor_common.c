/**
 * @file exo_ahw_al_temp_sensor_common.c
 *
 * @brief This file contains abstracted driver functions for temperature sensor
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

#include "exo_ahw_al_temp_sensor_common.h"
#include "exo_ahw_al_temp_sensor_wrapper.h"
#include "exo_ah_iob_csn.h"
#include "exo_ahdlsd.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief  Ahw Instance handle pointer.
 */
extern void* ahw_inst_hdle_ptr[MAX_AH_INST_ID];

/**
 * @brief  API to initialize the temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_init(ahw_al_temp_sensor_hdl* ht_arg, ahw_inst_id_t ahw_id)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL TEMPERATURE SENSOR Initialize");
#endif
    hal_ret_sts sts;
    ht_arg->ahw_gen_info.ahw_inst_id =ahw_id;
    if(HAL_SCS ==ahw_al_ts_common_init(ht_arg))
    {
        ahw_inst_hdle_ptr[ahw_id] =ht_arg;
        sts = HAL_SCS;
        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_ACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
        if(HAL_SCS != ahiobcsn_updt_ahste(&ht_arg->ahw_gen_info, AH_FREE_STATE))
        {
            sts = HAL_AHIOBCSN_FW_ERR;
        }
    }
    else
    {
        sts = HAL_AH_INIT_ERR;
        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_ERROR))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
    }
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL TEMPERATURE SENSOR  Initialization completed successfully");
#endif
    return sts;
}

/**
 * @brief  API to de-Initialize the temperature sensor
 */
hal_ret_sts  ahw_al_temp_sensor_deinit(ahw_al_temp_sensor_hdl* ht_arg, ahw_inst_id_t ahw_id)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL TEMPERATURE SENSOR de-initialization");
#endif
    hal_ret_sts sts;
    if(HAL_SCS == ahw_al_ts_common_deinit(ht_arg))
    {
        sts = HAL_SCS;
        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_DEACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
    }
    else
    {
        sts = HAL_AH_INIT_ERR;
        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_ERROR))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
    }
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL TEMPERATURE SENSOR de-initialization completed successfully");
#endif
    return sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief  API to get the event status of the temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_get_evnt_sts(ahw_al_temp_sensor_hdl *ahw_al_hts, uint8_t* evnt_sts)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == (hal_ret_sts)ahw_al_ts_common_get_evnt_sts(ahw_al_hts,evnt_sts))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief API to configure temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_config (ahw_al_temp_sensor_hdl *ahw_al_hts)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == (hal_ret_sts)ahw_al_ts_common_config(ahw_al_hts))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief API to set mode of operation for temperature sensor(continues mode or shutdown mode)
 */
hal_ret_sts ahw_al_temp_sensor_set_mode(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_mode_t mode)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS ==(hal_ret_sts) ahw_al_ts_common_set_mode(ahw_al_hts,mode))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief API to set interrupt clear bit in shutdown mode
 */
hal_ret_sts ahw_al_temp_sensor_intrupt_clear(ahw_al_temp_sensor_hdl *ahw_al_hts, uint8_t interrupt_clear)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == (hal_ret_sts)ahw_al_ts_common_intrupt_clear(ahw_al_hts,interrupt_clear))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief API to set event output mode of temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_set_event_output_mode(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_event_output_mode_t event_mode)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS ==(hal_ret_sts) ahw_al_ts_common_set_event_output_mode(ahw_al_hts,event_mode))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief  API to set event polarity of temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_set_event_polarity(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_event_polarity_t polarity)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS ==(hal_ret_sts) ahw_al_ts_common_set_event_polarity(ahw_al_hts,polarity))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief API to set win lock bit of temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_set_win_lockbit(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_win_lock_t win_lock)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_ts_h->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_ts_h->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == (hal_ret_sts)ahw_al_ts_common_set_win_lockbit(al_ts_h,win_lock))
        {
            ahiobcsn_updt_ahste(&al_ts_h->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&al_ts_h->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief API to set critical lock bit of temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_set_crit_lockbit(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_crit_lock_t crit_lock)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == (hal_ret_sts)ahw_al_ts_common_set_crit_lockbit(ahw_al_hts,crit_lock))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief  API to set temperature high threshold
 */
hal_ret_sts ahw_al_temp_sensor_set_temp_high_threshold (ahw_al_temp_sensor_hdl *ahw_al_hts, float high_temp_threshold)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == (hal_ret_sts)ahw_al_ts_common_set_temp_high_threshold(ahw_al_hts,high_temp_threshold))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief  API to set temperature low threshold
 */
hal_ret_sts ahw_al_temp_sensor_set_temp_low_threshold (ahw_al_temp_sensor_hdl *ahw_al_hts, float low_temp_threshold)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == (hal_ret_sts)ahw_al_ts_common_set_temp_low_threshold(ahw_al_hts,low_temp_threshold))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief API to set temperature critical threshold
 */
hal_ret_sts ahw_al_temp_sensor_set_temp_critical_threshold (ahw_al_temp_sensor_hdl *ahw_al_hts, float critical_temp_threshold)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS ==(hal_ret_sts) ahw_al_ts_common_set_temp_critical_threshold(ahw_al_hts,critical_temp_threshold))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief API to set hysteresis of temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_set_hysteresis(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_hyst_t hysteresis)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS ==(hal_ret_sts) ahw_al_ts_common_set_hysteresis(ahw_al_hts,hysteresis))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief  API to get Temperature sensor hysteresis
 */
hal_ret_sts ahw_al_temp_sensor_get_hysteresis(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_hyst_t *hysteresis)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS ==(hal_ret_sts) ahw_al_ts_common_get_hysteresis(ahw_al_hts,hysteresis))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief API to set the resolution of temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_set_resolution(ahw_al_temp_sensor_hdl *ahw_al_hts, temp_sensor_res_t resolution)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS ==(hal_ret_sts) ahw_al_ts_common_set_resolution(ahw_al_hts,resolution))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief API to get resolution of temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_get_resolution(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_res_t *res)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == (hal_ret_sts)ahw_al_ts_common_get_resolution(ahw_al_hts,res))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief  API to reads the current temperature using Temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_gettemperature(ahw_al_temp_sensor_hdl *ahw_al_hts,float *temperature)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == (hal_ret_sts)ahw_al_ts_common_gettemperature(ahw_al_hts,temperature))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief API to get temperature in fahrenheit using temperature sensor
 */
hal_ret_sts ahw_al_temp_sensor_get_fahrenheit(ahw_al_temp_sensor_hdl *ahw_al_hts, float* temperature)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_ts_common_get_fahrenheit(ahw_al_hts,temperature))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/*
 * @brief API to read Manufacture ID and return 16-bit hex value representing the temperature data from the MCP9843 register,
 * here it returns the hal_ret_sts for communicating wrapper common layer.
 */
hal_ret_sts ahw_al_temp_sensor_read_manufacture_id(ahw_al_temp_sensor_hdl *ahw_al_hts, int16_t* temperature)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&ahw_al_hts->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_ts_common_read_manufacture_id(ahw_al_hts,temperature))
        {
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
            ahiobcsn_updt_ahste(&ahw_al_hts->ahw_gen_info, AH_FREE_STATE);
        }
    }
    else
    {
    }
    return sts;
}

#endif

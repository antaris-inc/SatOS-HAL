/**
 * @file exo_ahw_al_dt_common.c
 *
 * @brief This file has abstracted driver functions for digital thermostat
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

#include <stdlib.h>
#include <stdio.h>
#include "exo_ahw_al_dt_common.h"
#include "exo_ahw_al_dt_wrapper.h"
#include "exo_ah_iob_csn.h"
#include "exo_ahdlsd.h"

extern void* ahw_inst_hdle_ptr[MAX_AH_INST_ID];

/*!
 *  @brief This API reads initialize the control block memory and do basic configurations for the digital thermostat instance
 */
hal_ret_sts ahw_al_dt_init(ahw_al_dt_hdle* hdt_arg, ahw_inst_id_t ahw_id)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL digi thermostat Initialise");
#endif
    hal_ret_sts sts;
    hdt_arg->ahw_gen_info.ahw_inst_id = ahw_id;
    if(HAL_SCS == ahw_al_dt_common_init(hdt_arg))
    {
        ahw_inst_hdle_ptr[ahw_id] = hdt_arg;
        sts = HAL_SCS;
        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_ACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
        if(HAL_SCS != ahiobcsn_updt_ahste(&hdt_arg->ahw_gen_info, AH_FREE_STATE))
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
    printf("\n EXO AH-AL digi thermostat Initialisation completed successfully");
#endif
    return sts;
}

#ifndef LINUX_TEMP_PORT
/*!
 *  @brief This API release the control block memory of ds620 instance
 */
hal_ret_sts ahw_al_dt_deinit(ahw_al_dt_hdle* hdt_arg, ahw_inst_id_t ahw_id)
{
    hal_ret_sts sts=HAL_MAX_ERR;
    if(HAL_SCS == ahw_al_dt_common_deinit(hdt_arg))
    {
        sts = HAL_SCS;
        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_DEACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
        if(HAL_SCS != ahiobcsn_updt_ahste(&hdt_arg->ahw_gen_info, AH_INVLD_STATE))
        {
            ahiobcsn_updt_ahste(&(hdt_arg->ahw_gen_info), AH_INVLD_STATE);
            sts = HAL_AHIOBCSN_FW_ERR;
        }

    }
    return sts;

}

/*!
 *  @brief This API set the high temperature threshold for temperature sensor
 */
hal_ret_sts ahw_al_dt_set_temperature_high_threshold (ahw_al_dt_hdle *hdt, double high_temp_threshold)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_set_temperature_high_threshold(hdt,high_temp_threshold))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/*!
 *  @brief This API set the low temperature threshold for temperature sensor
 */
hal_ret_sts ahw_al_dt_set_temperature_low_threshold (ahw_al_dt_hdle *hdt, double low_temp_threshold)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_set_temperature_low_threshold(hdt,low_temp_threshold))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/*!
 *  @brief This API get the temperature from temperature sensor
 */
hal_ret_sts ahw_al_dt_get_temperature (ahw_al_dt_hdle *hdt, double* temperature)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_get_temperature(hdt,temperature))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/*!
 *  @brief This API do the basic configurations for digital thermostat and temperature sensor
 */
hal_ret_sts ahw_al_dt_config (ahw_al_dt_hdle *hdt)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_sensor_config(hdt))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/*!
 *  @brief This API sets the ADC resolution of temperature sensor
 */
hal_ret_sts ahw_al_dt_set_resolution (ahw_al_dt_hdle *hdt, digital_thermos_resolution res)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_set_resolution(hdt,res))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/*!
 *  @brief This API gets the ADC resolution of temperature sensor
 */
hal_ret_sts ahw_al_dt_get_resolution(ahw_al_dt_hdle *hdt, digital_thermos_resolution *res )
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_get_resolution(hdt,res))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/*!
 *  @brief This API set the operating mode for temperature sensor
 */
hal_ret_sts ahw_al_dt_set_conv_mode (ahw_al_dt_hdle *hdt, uint8_t  mode)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_set_conv_mode(hdt,mode))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/*!
 *  @brief This API sets the PO pin logic level of digital thermostat
 */
hal_ret_sts ahw_al_dt_set_po_lvl (ahw_al_dt_hdle *hdt, uint8_t lvl)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_set_po_lvl(hdt,lvl))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}
/*!
 *  @brief This API sets the PO pin logic level of digital thermostat
 */
hal_ret_sts ahw_al_dt_set_po_lvl_alert_sts(ahw_al_dt_hdle *hdt, uint8_t* lvl)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_set_po_lvl_alert_sts(hdt,lvl))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/*!
 *  @brief This API resets the digital thermostat and temperature sensor
 */
hal_ret_sts ahw_al_dt_reset(ahw_al_dt_hdle *hdt)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_reset(hdt))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/*!
 *  @brief This API start the temperature conversion
 */
hal_ret_sts ahw_al_dt_start_conversion(ahw_al_dt_hdle *hdt)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_start_conversion(hdt))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
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

/*!
 *  @brief This API stop the temperature conversion
 */
hal_ret_sts ahw_al_dt_stop_conversion(ahw_al_dt_hdle *hdt)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_stop_conversion(hdt))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
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

/*!
 *  @brief This API get PO pin logic level
 */
hal_ret_sts ahw_al_dt_get_po_lvl(ahw_al_dt_hdle *hdt,uint8_t *lvl)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_get_po_lvl(hdt,lvl))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
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

/*!
 *  @brief This API get the operating mode of temperature sensor
 */
hal_ret_sts ahw_al_dt_get_mode(ahw_al_dt_hdle *hdt,uint8_t *mode)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_get_mode(hdt,mode))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
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

/*!
 *  @brief This API get the low temperature threshold
 */
hal_ret_sts ahw_al_dt_get_temperature_low_thrshd(ahw_al_dt_hdle *hdt,double *low_temp_thrshld)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_get_temperature_low_thrshd(hdt,low_temp_thrshld))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
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

/*!
 *  @brief This API get the high temperature threshold
 */
hal_ret_sts ahw_al_dt_get_temperature_high_thrshd(ahw_al_dt_hdle *hdt,double *high_temp_thrshld)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_get_temperature_high_thrshd(hdt,high_temp_thrshld))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
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

/*!
 *  @brief This API reset the alert flag
 */
hal_ret_sts ahw_al_dt_reset_alert_flag(ahw_al_dt_hdle *hdt)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hdt->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_dt_common_reset_alert_flag(hdt))
        {
            ahiobcsn_updt_ahste(&hdt->ahw_gen_info, AH_FREE_STATE);
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

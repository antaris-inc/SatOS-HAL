/**
 * @file exo_ahw_al_psm_common.c
 *
 * @brief This file contains abstracted driver function for power sense monitor
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
#include "exo_ahw_al_psm_common.h"
#include "exo_ahw_al_psm_wrapper.h"
#include "exo_ah_iob_csn.h"
#include "exo_ahdlsd.h"
#include <stdlib.h>

/**
 * @brief  Ahw Instance handle pointer.
 */
extern void* ahw_inst_hdle_ptr[MAX_AH_INST_ID];

/**
 * @brief  API to initialize the power sense monitor.
 */
hal_ret_sts ahw_al_psm_init(ahw_al_psm_hdle* hpsm_arg, ahw_inst_id_t ahw_id, ahw_al_psm_tc_config_t* hpsm_tc_cfg )
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL POWER SENSE MONITOR Initialize");
#endif
    hal_ret_sts sts;
    hpsm_arg->ahw_gen_info.ahw_inst_id =ahw_id;
    if(HAL_SCS ==ahw_al_psm_common_init(hpsm_arg,hpsm_tc_cfg))
    {
        ahw_inst_hdle_ptr[ahw_id] = hpsm_arg;
        sts = HAL_SCS;

        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_ACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
        if(HAL_SCS != ahiobcsn_updt_ahste(&hpsm_arg->ahw_gen_info, AH_FREE_STATE))
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
    printf("\n EXO AH-AL POWER SENSE MONITOR  Initialization completed successfully");
#endif
    return sts;
}

/**
 * @brief  API to de-Initialize the power sense monitor.
 */
hal_ret_sts ahw_al_psm_deinit(ahw_al_psm_hdle* hpsm_arg, ahw_inst_id_t ahw_id)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL POWER SENSE MONITOR De-Initialize");
#endif
    hal_ret_sts sts;
    if(HAL_SCS == ahw_al_psm_common_deinit(hpsm_arg))
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
    printf("\n EXO AH-AL POWER SENSE MONITOR De-Initialization completed successfully");
#endif
    return sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief API to read the power sense monitor die identifier
 */
hal_ret_sts	 ahw_al_psm_read_id(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_read_id(hpsm))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief API to generates a system reset.
 */
hal_ret_sts ahw_al_psm_reset(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS ==ahw_al_psm_common_reset(hpsm))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to program the Power Sense Monitor calibration register
 */
hal_ret_sts ahw_al_psm_set_calibration(ahw_al_psm_hdle *hpsm, uint16_t calibration)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_set_calibration(hpsm,calibration))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to read programmed calibration value
 */
uint16_t ahw_al_psm_get_calibration(ahw_al_psm_hdle *hpsm)
{
    uint16_t res=0;
    hal_ret_sts sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        res = ahw_al_psm_common_get_calibration(hpsm);
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
    }
    else
    {
    }
    return res;
}

/**
 *  @brief  API to configure the alert pin behavior
 */
hal_ret_sts  ahw_al_psm_alert_pinconfig(ahw_al_psm_hdle *hpsm,ahw_al_psm_alert_pin_cfg_t *alert_pin_cfg)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_alert_pinconfig(hpsm,alert_pin_cfg))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to set the alert function
 */
hal_ret_sts ahw_al_psm_set_alertfunction(ahw_al_psm_hdle *hpsm,psm_alert_function_t alert_function)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_set_alertfunction(hpsm,alert_function))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief API to get the programmed alert function
 */
hal_ret_sts ahw_al_psm_get_alertfunction(ahw_al_psm_hdle *hpsm,psm_alert_function_t alert_function)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS ==ahw_al_psm_common_get_alertfunction(hpsm,alert_function))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to program the VBus threshold
 */
hal_ret_sts ahw_al_psm_setvbusthreshold(ahw_al_psm_hdle *hpsm, float vbusthreshold)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_setvbusthreshold(hpsm,vbusthreshold))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to get the VBUS threshold
 */
hal_ret_sts  ahw_al_psm_getvbusthreshold(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_getvbusthreshold(hpsm))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to program the VShunt threshold
 */
hal_ret_sts  ahw_al_psm_setvshuntthreshold(ahw_al_psm_hdle *hpsm, float vshuntthreshold)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_setvbusthreshold(hpsm,vshuntthreshold))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief API to get the VShunt threshold
 */
hal_ret_sts ahw_al_psm_getshuntthreshold(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_getvbusthreshold(hpsm))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to program the current threshold
 */
hal_ret_sts ahw_al_psm_set_current_threshold(ahw_al_psm_hdle *hpsm, float current_threshold)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_set_current_threshold(hpsm,current_threshold))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief API to program the Power threshold
 */
hal_ret_sts ahw_al_psm_setpowerthreshold(ahw_al_psm_hdle *hpsm, uint32_t powerthreshold)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_setpowerthreshold(hpsm,powerthreshold))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to get the Power threshold
 */
hal_ret_sts ahw_al_psm_getpowerthreshold(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_getpowerthreshold(hpsm))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to enable the Voltage/Power threshold interrupt
 */
hal_ret_sts ahw_al_psm_alert_threshold_enable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_alert_threshold_enable_it(hpsm))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to disable the Voltage/Power threshold interrupt
 */
hal_ret_sts ahw_al_psm_alert_threshold_disable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_alert_threshold_disable_it(hpsm))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to enable the Conversion ready interrupt
 */
hal_ret_sts ahw_al_psm_conversion_ready_enable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_conversion_ready_enable_it(hpsm))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to disable the Conversion ready interrupt
 */
hal_ret_sts ahw_al_psm_conversion_ready_disable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_conversion_ready_disable_it(hpsm))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief  API to start the conversion on the selected voltage input
 */
hal_ret_sts ahw_al_psm_startconversion(ahw_al_psm_hdle *hpsm, psm_input_signal_t inputsignal, psm_operating_mode_t mode)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_startconversion(hpsm,inputsignal,mode))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief API to stop the conversion on the selected voltage input
 */
hal_ret_sts  ahw_al_psm_stopconversion(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_stopconversion(hpsm))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/**
 * @brief API to read the bus voltage
 */
float   ahw_al_psm_get_vbus(ahw_al_psm_hdle *hpsm)
{
    float res=0;
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        res = ahw_al_psm_common_get_vbus(hpsm);
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
    }
    else
    {
    }
    return res;
}

/**
 * @brief  API to read the shunt voltage
 */
float ahw_al_psm_get_vshunt(ahw_al_psm_hdle *hpsm)
{
    float res=0;
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        res = ahw_al_psm_common_get_vshunt(hpsm);
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
    }
    else
    {
    }
    return res;
}

/**
 * @brief API to read the power value
 */
uint32_t  ahw_al_psm_get_power(ahw_al_psm_hdle *hpsm)
{
    uint32_t res=0;
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        res = ahw_al_psm_common_get_power(hpsm);
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);

    }
    else
    {
    }
    return res;
}

/**
 * @brief  API to read the current value
 */
float ahw_al_psm_get_current(ahw_al_psm_hdle *hpsm)
{
    float res=0;
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        res = ahw_al_psm_common_get_current(hpsm);
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);

    }
    else
    {
    }
    return res;
}

/**
 * @brief  API to read the designed flag value
 */
hal_ret_sts   ahw_al_psm_get_flag(ahw_al_psm_hdle *hpsm, psm_flag_t flag)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hpsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_psm_common_get_flag(hpsm,flag))
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hpsm->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

#endif



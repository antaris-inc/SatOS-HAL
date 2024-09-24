/**
 * @file exo_ahw_al_hsc_common.c
 *
 * @brief This file contains abstracted driver function for hotswap controller and voltage ,current monitor
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
#include "exo_ahw_al_hsc_common.h"
#include "exo_ahw_al_hsc_wrapper.h"
#include "exo_ah_iob_csn.h"
#include "exo_ahdlsd.h"

extern void* ahw_inst_hdle_ptr[MAX_AH_INST_ID];

/*!
 *  @brief This API initializes the control block memory and do the basic configurations for ADM1176 instance
 */
hal_ret_sts ahw_al_hsc_init(ahw_al_hsc_hdl* hsc_arg, ahw_inst_id_t ahw_id)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL hot swap controller Initialise");
#endif
    hal_ret_sts sts;
    hsc_arg->ahw_gen_info.ahw_inst_id = ahw_id;
    if(HAL_SCS == ahw_al_hsc_common_init(hsc_arg))
    {
        ahw_inst_hdle_ptr[ahw_id] = hsc_arg;
        sts = HAL_SCS;
        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_ACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
        if(HAL_SCS != ahiobcsn_updt_ahste(&hsc_arg->ahw_gen_info, AH_FREE_STATE))
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
    printf("\n EXO AH-AL hot swap controller Initialization completed successfully");
#endif 
    return sts;
}

#ifndef LINUX_TEMP_PORT
/*!
 *  @brief This API deinitializes the control block memory
 */
hal_ret_sts ahw_al_hsc_deinit(ahw_al_hsc_hdl* hsc_arg, ahw_inst_id_t ahw_id)
{
    hal_ret_sts sts=HAL_MAX_ERR;
    if(HAL_SCS == ahw_al_hsc_common_deinit(hsc_arg))
    {
        sts = HAL_SCS;
        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_DEACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
        if(HAL_SCS != ahiobcsn_updt_ahste(&hsc_arg->ahw_gen_info, AH_INVLD_STATE))
        {
            sts = HAL_AHIOBCSN_FW_ERR;
        }
    }
    return sts;
}

/*!
 *  @brief This API reads and returns the voltage
 */
hal_ret_sts ahw_al_hsc_read_voltage(ahw_al_hsc_hdl *hsc, float *voltage )
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hsc->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_hsc_common_read_voltage(hsc,voltage))
        {
            ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/*!
 *  @brief This API reads and returns the current
 */
hal_ret_sts ahw_al_hsc_read_current(ahw_al_hsc_hdl *hsc, float *current)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hsc->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_hsc_common_read_current(hsc,current))
        {
            ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/*!
 *  @brief This API reads and returns the hotswap status.
 */
hal_ret_sts ahw_al_hsc_get_hotswap_sts(ahw_al_hsc_hdl *hsc, uint8_t *hotswap_sts)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hsc->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_hsc_common_get_hotswap_sts(hsc,hotswap_sts))
        {
            ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/*!
 *  @brief This API is used to manually turn ON/OFF the hotswap operation.
 */
hal_ret_sts ahw_al_hsc_hotswap_control(ahw_al_hsc_hdl *hsc, uint8_t on_off)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hsc->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_hsc_common_hotswap_control(hsc,on_off))
        {
            ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

/*!
 *  @brief This API reads and returns the overcurrent status of ADM1176.
 */
hal_ret_sts ahw_al_hsc_get_overcurrent_sts(ahw_al_hsc_hdl *hsc, uint8_t *under_vlt_sts)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hsc->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_hsc_common_get_overcurrent_sts(hsc,under_vlt_sts))
        {
            ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hsc->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {
    }
    return sts;
}

#endif

/**
 * @file exo_ahw_al_voltage_sequencer_common.c
 *
 * @brief This file has abstracted driver functions of voltage sequencer
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
#include <stdlib.h>
#include "exo_ahw_al_voltage_sequencer_common.h"
#include "exo_ahw_al_voltage_sequencer_wrapper.h"
#include "exo_ah_iob_csn.h"
#include "exo_ahdlsd.h"

extern void* ahw_inst_hdle_ptr[MAX_AH_INST_ID];

ahw_al_vsm_hdle *hvsm_obc;

/*!
 *  @brief This API initialize the control block memory and do basic configurations
 */
hal_ret_sts ahw_al_vsm_init()
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL digi thermostat Initialise");
#endif
    hal_ret_sts sts;
    ahw_al_vsm_hdle* hvsm_obc=(ahw_al_vsm_hdle*)malloc(sizeof(ahw_al_vsm_hdle));
    hvsm_obc->ahw_gen_info.ahw_inst_id = VSM_UCD9081_OBC;
    if(HAL_SCS == ahw_al_vsm_common_init(hvsm_obc))
    {
        ahw_inst_hdle_ptr[VSM_UCD9081_OBC] = hvsm_obc;
        sts = HAL_SCS;
        if(HAL_SCS != ahdlsd_updt_ah_state(VSM_UCD9081_OBC, AH_ACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
        if(HAL_SCS != ahiobcsn_updt_ahste(&hvsm_obc->ahw_gen_info, AH_FREE_STATE))
        {
            sts = HAL_AHIOBCSN_FW_ERR;
        }
    }
    else
    {
        sts = HAL_AH_INIT_ERR;
        if(HAL_SCS != ahdlsd_updt_ah_state(VSM_UCD9081_OBC, AH_ERROR))
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
 *  @brief This API configure the rail  and voltage sequencer instance
 */
hal_ret_sts ahw_al_vsm_rail_config(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_rail_config(al_vsm,rail_info))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set the undervoltage threshold
 */
hal_ret_sts ahw_al_vsm_set_undervoltage_thrsld(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float udr_vltg_thrsld)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_undervoltage_thrsld(al_vsm, rail_info,udr_vltg_thrsld))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set the overvoltage threshold
 */
hal_ret_sts ahw_al_vsm_set_overvoltage_thrsld(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float ovr_vltg_thrsld)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_overvoltage_thrsld(al_vsm,rail_info,ovr_vltg_thrsld))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set the polarity enable
 */
hal_ret_sts ahw_al_vsm_set_enable_polarity(ahw_al_vsm_hdle *al_vsm,  vltg_seq_rail_cfg* rail_info, uint8_t polarity)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_enable_polarity(al_vsm,rail_info,polarity))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set unsequence time
 */
hal_ret_sts ahw_al_vsm_set_unsequence_time(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t time)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_unsequence_time(al_vsm,rail_info,time))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set the out of regulation width
 */
hal_ret_sts ahw_al_vsm_set_out_of_reg_width(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t width)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_out_of_reg_width(al_vsm,rail_info,width))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set the ramp time
 */
hal_ret_sts ahw_al_vsm_set_ramp_time(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t ramp_tm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_undervoltage_thrsld(al_vsm,rail_info,ramp_tm))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API force restart
 */
hal_ret_sts ahw_al_vsm_force_restart(ahw_al_vsm_hdle *al_vsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_force_restart(al_vsm))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API restart
 */
hal_ret_sts ahw_al_vsm_restart(ahw_al_vsm_hdle *al_vsm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_restart(al_vsm))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API get the firmware version
 */
hal_ret_sts ahw_al_vsm_get_fw_version(ahw_al_vsm_hdle *al_vsm, uint8_t* version)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_get_fw_version(al_vsm,version))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API get voltage
 */
hal_ret_sts ahw_al_vsm_get_voltage(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float *voltage)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_get_voltage(al_vsm,rail_info,voltage))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API get alarm pending status
 */
hal_ret_sts ahw_al_vsm_get_alrm_pndng_sts(ahw_al_vsm_hdle *al_vsm, uint8_t* rail_err_sts)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_get_alrm_pndng_sts(al_vsm,rail_err_sts))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set sequence type
 */
hal_ret_sts ahw_al_vsm_set_seq_type(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info,uint8_t seq_tp)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_seq_type(al_vsm,rail_info,seq_tp))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set sequence delay
 */
hal_ret_sts ahw_al_vsm_set_seq_delay(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t dly_tm)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_seq_delay(al_vsm,rail_info,dly_tm))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set the sequence parent voltage level
 */
hal_ret_sts ahw_al_vsm_set_seq_prnt_vltg_lvl(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* actual_rail_info, vltg_seq_rail_cfg* parent_rail_info, float voltage)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_seq_prnt_vltg_lvl(al_vsm,actual_rail_info,parent_rail_info,voltage))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set the sequence parent rail
 */
hal_ret_sts ahw_al_vsm_set_seq_prnt_rail(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, vltg_seq_rail_num prnt_rail)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_seq_prnt_rail(al_vsm,rail_info,prnt_rail))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API configure the voltage reference
 */
hal_ret_sts ahw_al_vsm_vref_cfg(ahw_al_vsm_hdle *al_vsm,uint8_t v_ref)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_vref_cfg(al_vsm,v_ref))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API configure glitch alarm
 */
hal_ret_sts ahw_al_vsm_glitch_alrm_cfg(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint8_t glth_alrm_sts)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_glitch_alrm_cfg(al_vsm,rail_info,glth_alrm_sts))
        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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
 *  @brief This API set rail alarm type
 */
hal_ret_sts ahw_al_vsm_set_rail_alrm_typ(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint8_t alrm_typ)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&al_vsm->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_vsm_common_set_rail_alrm_typ(al_vsm,rail_info,alrm_typ))        {
            ahiobcsn_updt_ahste(&al_vsm->ahw_gen_info, AH_FREE_STATE);
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



/**
 * @file exo_ahw_al_voltage_sequencer_wrapper.c
 *
 * @brief This file has mapping functions which resolves the
 * instance Id and invokes the vendor driver API for voltage sequencer on the partnumber
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

#include "exo_ahw_al_voltage_sequencer_common.h"
#include "exo_ahw_al_voltage_sequencer_wrapper.h"

/*!
 *  @brief Mapping API to initializes the control block memory and do the basic configurations
 */
hal_ret_sts ahw_al_vsm_common_init(ahw_al_vsm_hdle *hvsm)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_init(hvsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

#ifndef LINUX_TEMP_PORT
/*!
 *  @brief Mapping API to configure the rail of voltage sequencer
 */
hal_ret_sts ahw_al_vsm_common_rail_config(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_rail_config(hvsm, rail_info);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;

}

/*!
 *  @brief Mapping API to set the undervoltage threshold
 */
hal_ret_sts ahw_al_vsm_common_set_undervoltage_thrsld(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info, float udr_vltg_thrsld)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_undervoltage_thrsld(hvsm,rail_info,udr_vltg_thrsld);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the overvoltage threshold
 */
hal_ret_sts ahw_al_vsm_common_set_overvoltage_thrsld(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info, float ovr_vltg_thrsld)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_overvoltage_thrsld(hvsm,rail_info,ovr_vltg_thrsld);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the polarity enable
 */
hal_ret_sts ahw_al_vsm_common_set_enable_polarity(ahw_al_vsm_hdle *hvsm,  vltg_seq_rail_cfg* rail_info, uint8_t polarity)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_enable_polarity(hvsm,rail_info,polarity);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set unsequence time
 */
hal_ret_sts ahw_al_vsm_common_set_unsequence_time(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info, uint16_t time)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_unsequence_time(hvsm,rail_info,time);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the out of regulation width
 */
hal_ret_sts ahw_al_vsm_common_set_out_of_reg_width(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info, uint16_t width)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_out_of_reg_width(hvsm,rail_info,width);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the ramp time
 */
hal_ret_sts ahw_al_vsm_common_set_ramp_time(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info, uint16_t ramp_tm)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_ramp_time(hvsm,rail_info,ramp_tm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to force restart
 */
hal_ret_sts ahw_al_vsm_common_force_restart(ahw_al_vsm_hdle *hvsm)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_force_restart(hvsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to restart
 */
hal_ret_sts ahw_al_vsm_common_restart(ahw_al_vsm_hdle *hvsm)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_restart(hvsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to get the firmware version
 */
hal_ret_sts ahw_al_vsm_common_get_fw_version(ahw_al_vsm_hdle *hvsm, uint8_t* version)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_get_fw_version(hvsm, version);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to get voltage
 */
hal_ret_sts ahw_al_vsm_common_get_voltage(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info, float *voltage)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_get_voltage(hvsm,rail_info,voltage);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to get alarm pending status
 */
hal_ret_sts ahw_al_vsm_common_get_alrm_pndng_sts(ahw_al_vsm_hdle *hvsm, uint8_t* rail_err_sts)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_get_alrm_pndng_sts(hvsm,rail_err_sts);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set sequence type
 */
hal_ret_sts ahw_al_vsm_common_set_seq_type(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info,uint8_t seq_tp)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_seq_type(hvsm,rail_info,seq_tp);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set sequence delay
 */
hal_ret_sts ahw_al_vsm_common_set_seq_delay(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info, uint16_t dly_tm)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_seq_delay(hvsm,rail_info,dly_tm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the sequence parent voltage level
 */
hal_ret_sts ahw_al_vsm_common_set_seq_prnt_vltg_lvl(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* actual_rail_info, vltg_seq_rail_cfg* parent_rail_info, float voltage)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_seq_prnt_vltg_lvl(hvsm,actual_rail_info,parent_rail_info,voltage);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the sequence parent rail
 */
hal_ret_sts ahw_al_vsm_common_set_seq_prnt_rail(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info, vltg_seq_rail_num prnt_rail)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_seq_prnt_rail(hvsm,rail_info,prnt_rail);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to configure the voltage reference
 */
hal_ret_sts ahw_al_vsm_common_vref_cfg(ahw_al_vsm_hdle *hvsm,uint8_t v_ref)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_vref_cfg(hvsm,v_ref);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to configure glitch alarm
 */
hal_ret_sts ahw_al_vsm_common_glitch_alrm_cfg(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info, uint8_t glth_alrm_sts)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_glitch_alrm_cfg(hvsm,rail_info,glth_alrm_sts);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set rail alarm type
 */
hal_ret_sts ahw_al_vsm_common_set_rail_alrm_typ(ahw_al_vsm_hdle *hvsm, vltg_seq_rail_cfg* rail_info, uint8_t alrm_typ)
{
    hal_ret_sts sts;
    switch(hvsm->ahw_gen_info.ahw_inst_id)
    {
        case VSM_UCD9081_OBC:
            sts = ahw_vdp_vsm_ucd9081_set_rail_alrm_typ(hvsm,rail_info,alrm_typ);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

#endif

/**
 * @file exo_ahw_vdp_vsm_ucd9081.c
 *
 * @brief This file contains the vendor driver porting function of UCD9081 voltage sequencer
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
#include <unistd.h>
#include "exo_ahw_vdp_vsm_ucd9081.h"
#include "exo_osal_mem_management.h"
#include "ucd9081.h"


extern ahw_io_map *ahw_io_lookup_tble[MAX_AH_INST_ID];
extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

#ifndef LINUX_TEMP_PORT

/*!
 *  @brief I2C read hook function for UCD9081 module
 */
int8_t ucd9081_i2c_read(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)(slv_addr<<1), &reg_addr, 1, 500))
    {
        if(HAL_SCS == io_hal_i2c_receive(hi2c, (uint16)(slv_addr<<1), data, len, 500))
        {
            rslt = UCD9081_SCS;
        }
        else
        {
            rslt = UCD9081_COM_ERR;
        }
    }
    else
    {
        rslt = UCD9081_COM_ERR;
    }
    return rslt;
}

/*!
 *  @brief I2C write hook function for UCD9081 module
 */
int8_t ucd9081_i2c_write(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;

    if(data==NULL)
    {
        rslt = io_hal_i2c_transmit(hi2c, (uint16)(slv_addr<<1),&reg_addr, 1, 500);
        return rslt;
    }
    if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)(slv_addr<<1), &reg_addr, 1, 500))
    {
        if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)(slv_addr<<1), data, len, 500))
        {
            rslt = UCD9081_SCS;
        }
        else
        {
            rslt = UCD9081_COM_ERR;
        }
    }
    else
    {
        rslt = UCD9081_COM_ERR;
    }
    return rslt;
}
#endif

/*!
 *  @brief This API to initalize UCD9081 and control block memory
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_init(ahw_al_vsm_hdle *ahw_al_hvsm)
{

    hal_ret_sts sts = HAL_MAX_ERR;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO UCD9081 Digital thermostat - AH-Vendor driver porting layer Initialise");
    printf("\n EXO UCD9081 Digital thermostat - AH-Vendor driver Initialise");
    printf("\n EXO UCD9081 Digital thermostat - AH-Vendor driver Initialisation completed successfully ");
    usleep(100000);
    printf("\n EXO UCD9081 Digital thermostat - AH-Vendor driver porting layer initialisation completed successfully");

#else

    s_ucd9081* hvsm=(s_ucd9081*)os_malloc(sizeof(s_ucd9081));
    hvsm->write = ucd9081_i2c_write;
    hvsm->read = ucd9081_i2c_read;
    hvsm->intf_hdl = intf_inst_hdle_ptr[ahw_io_lookup_tble[ahw_al_hvsm->ahw_gen_info.ahw_inst_id]->io_instance_id];
    hvsm->slv_addr=ahw_io_lookup_tble[ahw_al_hvsm->ahw_gen_info.ahw_inst_id]->slv_addr;
    if(HAL_SCS == (hal_ret_sts)ucd9081_init(hvsm))
    {
        ahw_al_hvsm->ahw_gen_info.vdp_inst_hdle = (void*)hvsm;
        ahw_al_hvsm->ahw_gen_info.io_intf_hdle=hvsm->intf_hdl;
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
/*!
 *  @brief This API configure the rail
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_rail_config(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;

    vd_rail_info.alrm_typ = rail_info->alrm_typ;
    vd_rail_info.seq_dly_tm = rail_info->seq_dly_tm;
    vd_rail_info.dpdncy_mask = rail_info->dpdncy_mask;
    vd_rail_info.ext_vd_en = rail_info->ext_vd_en;
    vd_rail_info.glt_alrm_sts = rail_info->glt_alrm_sts;
    vd_rail_info.mntr_sts = rail_info->mntr_sts;
    vd_rail_info.out_reg_width = rail_info->out_reg_width;
    vd_rail_info.ovr_vlt_thrsld = rail_info->ovr_vlt_thrsld;
    vd_rail_info.polarity = rail_info->polarity;
    vd_rail_info.prnt_rail = rail_info->prnt_rail;
    vd_rail_info.prnt_vlt  = rail_info->prnt_vlt;
    vd_rail_info.r_pull_down = rail_info->r_pull_down;
    vd_rail_info.r_pull_up = rail_info->r_pull_up;
    vd_rail_info.rail_nu = rail_info->rail_nu;
    vd_rail_info.ramp_time = rail_info->ramp_time;
    vd_rail_info.reseq_sts = rail_info->reseq_sts;
    vd_rail_info.seq_type = rail_info->seq_type;
    vd_rail_info.udr_vlt_thrsld = rail_info->udr_vlt_thrsld;
    vd_rail_info.unseq_time = rail_info->unseq_time;

    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_rail_config(ucd9081_hdl_vdp,&vd_rail_info))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set the undervoltage threshold
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_undervoltage_thrsld(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float udr_vltg_thrsld)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.ext_vd_en =rail_info->ext_vd_en;
    vd_rail_info.r_pull_down = rail_info->r_pull_down;
    vd_rail_info.r_pull_up = rail_info->r_pull_up;
    vd_rail_info.rail_nu = rail_info->rail_nu;
    vd_rail_info.udr_vlt_thrsld =rail_info->udr_vlt_thrsld;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_undervoltage_thrsld (ucd9081_hdl_vdp,&vd_rail_info, udr_vltg_thrsld))
    {
        rail_info->udr_vlt_thrsld = udr_vltg_thrsld;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set the overvoltage threshold
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_overvoltage_thrsld(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float ovr_vltg_thrsld)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_overvoltage_thrsld(ucd9081_hdl_vdp, &vd_rail_info, ovr_vltg_thrsld))
    {
        rail_info->ovr_vlt_thrsld = ovr_vltg_thrsld;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set the polarity enable
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_enable_polarity(ahw_al_vsm_hdle *al_vsm,  vltg_seq_rail_cfg* rail_info, uint8_t polarity)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.rail_nu  = rail_info->rail_nu;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_enable_polarity(ucd9081_hdl_vdp, &vd_rail_info, polarity))
    {
        rail_info->polarity = polarity;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set unsequence time
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_unsequence_time(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t time)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.rail_nu  = rail_info->rail_nu;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_unsequence_time(ucd9081_hdl_vdp, &vd_rail_info,time))
    {
        rail_info->unseq_time = time;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set the out of regulation width
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_out_of_reg_width(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t width)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.rail_nu  = rail_info->rail_nu;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_out_of_reg_width(ucd9081_hdl_vdp, &vd_rail_info, width))
    {
        rail_info->out_reg_width = width;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set the ramp time
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_ramp_time(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t ramp_tm)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.rail_nu  = rail_info->rail_nu;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_ramp_time(ucd9081_hdl_vdp,&vd_rail_info,ramp_tm))
    {
        rail_info->ramp_time = ramp_tm;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API is to force restart the UCD9081
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_force_restart(ahw_al_vsm_hdle *al_vsm)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_force_restart(ucd9081_hdl_vdp))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API is to restart the UCD9081
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_restart(ahw_al_vsm_hdle *al_vsm)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_restart(ucd9081_hdl_vdp))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API get the firmware version
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_get_fw_version(ahw_al_vsm_hdle *al_vsm, uint8_t *version)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_get_fw_version(ucd9081_hdl_vdp,version))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API get voltage from specified rail
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_get_voltage(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float *voltage)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.ext_vd_en =rail_info->ext_vd_en;
    vd_rail_info.r_pull_down = rail_info->r_pull_down;
    vd_rail_info.r_pull_up = rail_info->r_pull_up;
    vd_rail_info.rail_nu = rail_info->rail_nu;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts) ucd9081_get_voltage(ucd9081_hdl_vdp,&vd_rail_info,voltage))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API get alarm pending status
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_get_alrm_pndng_sts(ahw_al_vsm_hdle *al_vsm, uint8_t* rail_err_sts)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_get_alrm_pndng_sts(ucd9081_hdl_vdp,rail_err_sts))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set sequence type
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_seq_type(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info,uint8_t seq_tp)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.rail_nu = rail_info->rail_nu;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_seq_type(ucd9081_hdl_vdp,&vd_rail_info,seq_tp))
    {
        rail_info->seq_type=seq_tp;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set sequence delay
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_seq_delay(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t dly_tm)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.rail_nu = rail_info->rail_nu;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_seq_delay(ucd9081_hdl_vdp,&vd_rail_info, dly_tm))
    {
        rail_info->seq_dly_tm=dly_tm;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set the sequence parent voltage level
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_seq_prnt_vltg_lvl(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* actual_rail_info, vltg_seq_rail_cfg* parent_rail_info, float voltage)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_act_rail_info;
    s_ucd9081_rail_cfg vd_prnt_rail_info;
    vd_act_rail_info.rail_nu = actual_rail_info->rail_nu;
    vd_prnt_rail_info.rail_nu=parent_rail_info->rail_nu;
    vd_prnt_rail_info.ext_vd_en = parent_rail_info->ext_vd_en;
    vd_prnt_rail_info.r_pull_down = parent_rail_info->r_pull_down;
    vd_prnt_rail_info.r_pull_up = parent_rail_info->r_pull_up;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_seq_prnt_vltg_lvl(ucd9081_hdl_vdp,&vd_act_rail_info,&vd_prnt_rail_info, voltage))
    {
        actual_rail_info->prnt_vlt = voltage;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set the sequence parent rail
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_seq_prnt_rail(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, vltg_seq_rail_num prnt_rail)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.rail_nu = rail_info->rail_nu;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_seq_prnt_rail(ucd9081_hdl_vdp,&vd_rail_info, prnt_rail))
    {
        rail_info->prnt_rail=prnt_rail;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API configure the voltage reference
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_vref_cfg(ahw_al_vsm_hdle *al_vsm,uint8_t v_ref)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_vref_cfg(ucd9081_hdl_vdp,v_ref))
    {
        al_vsm->v_ref_typ=v_ref;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API configure glitch alarm
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_glitch_alrm_cfg(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint8_t glth_alrm_sts)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.rail_nu = rail_info->rail_nu;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_glitch_alrm_cfg(ucd9081_hdl_vdp, &vd_rail_info, glth_alrm_sts))
    {
        rail_info->glt_alrm_sts=glth_alrm_sts;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set rail alarm type
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_rail_alrm_typ(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint8_t alrm_typ)
{
    e_ucd9081_err sts;
    s_ucd9081* ucd9081_hdl_vdp;
    s_ucd9081_rail_cfg vd_rail_info;
    vd_rail_info.rail_nu = rail_info->rail_nu;
    ucd9081_hdl_vdp = (s_ucd9081*) al_vsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ucd9081_set_rail_alrm_typ(ucd9081_hdl_vdp,&vd_rail_info, alrm_typ))
    {
        rail_info->alrm_typ = alrm_typ;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

#endif

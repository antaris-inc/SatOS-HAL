/**
 * @file ucd9081.c
 *
 * @brief This file has driver function of voltage sequencer UCD9081
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
#include "ucd9081.h"

const uint16_t cfg_flsh_addr[12][10] =  {{0xE110,   0xE120, 0xE130, 0xE140, 0xE150, 0xE168, 0xE080, 0xE08C, 0xE098, 0xE100},
    {0xE112,   0xE122, 0xE132, 0xE142, 0xE152, 0xE16A, 0xE081, 0xE08D, 0xE09A, 0xE102},
    {0xE114,   0xE124, 0xE134, 0xE144, 0xE154, 0xE16C, 0xE082, 0xE08E, 0xE09C, 0xE104},
    {0xE116,   0xE126, 0xE136, 0xE146, 0xE156, 0xE16E, 0xE083, 0xE08F, 0xE09E, 0xE106},
    {0xE118,   0xE128, 0xE138, 0xE148, 0xE158, 0xE170, 0xE084, 0xE090, 0xE0A0, 0xE108},
    {0xE11A,   0xE12A, 0xE13A, 0xE14A, 0xE15A, 0xE172, 0xE085, 0xE091, 0xE0A2, 0xE10A},
    {0xE11C,   0xE12C, 0xE13C, 0xE14C, 0xE15C, 0xE174, 0xE086, 0xE092, 0xE0A4, 0xE10C},
    {0xE11E,   0xE12E, 0xE13E, 0xE14E, 0xE15E, 0xE176, 0xE087, 0xE093, 0xE0A6, 0xE10E},
    {0,    0,  0,  0,  0xE160, 0xE178, 0xE088, 0xE094, 0xE0A8, 0},
    {0,    0,  0,  0,  0xE162, 0xE17A, 0xE089, 0xE095, 0xE0AA, 0},
    {0,    0,  0,  0,  0xE164, 0xE17C, 0xE08A, 0xE096, 0xE0AC, 0},
    {0,    0,  0,  0,  0xE166, 0xE17E, 0xE08B, 0xE097, 0xE0AE, 0}};


/*!
 * @brief This API is used to check null pointer
 */
static e_ucd9081_err ucd9081_null_ptr_check(const s_ucd9081* dev)
{
    e_ucd9081_err ret;
    if ((dev == NULL) || (dev->read == NULL) || (dev->write == NULL))
    {
        ret = UCD9081_NULL_PTR;
    }
    else
    {
        ret = UCD9081_SCS;
    }
    return ret;
}

/*!
 * @brief This API write the data
 */
static e_ucd9081_err ucd9081_config_data_write(s_ucd9081* ucd9081_hdl, uint8_t* addr, uint8_t *data, uint8_t d_len)
{
    e_ucd9081_err ret = UCD9081_COM_ERR;
    if(ucd9081_hdl->write(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,UCD9081_WADDR1,addr,2)==UCD9081_SCS)
    {
        ret=ucd9081_hdl->write(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,UCD9081_WDATA1,data,(uint16_t)d_len);
    }
    return ret;
}

/*!
 * @brief This API read the data
 */
static e_ucd9081_err ucd9081_config_data_read(s_ucd9081* ucd9081_hdl, uint8_t* addr, uint8_t *data, uint8_t d_len)
{
    e_ucd9081_err ret = UCD9081_COM_ERR;
    if(ucd9081_hdl->write(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,UCD9081_WADDR1,addr,2)==UCD9081_SCS)
    {
        ret=ucd9081_hdl->read(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,UCD9081_WDATA1,data,(uint16_t)d_len);
    }
    return ret;
}

/*!
 * @brief This API lock the ucd9081 flash
 */
static e_ucd9081_err ucd9081_flash_lock(s_ucd9081* ucd9081_hdl)
{
    e_ucd9081_err ret =UCD9081_ERR;
    uint8_t en;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS)
    {
        if(ucd9081_hdl->flash_lock_sts!=0)
        {
            en=0x00;
            ret= ucd9081_hdl->write(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,UCD9081_FLASHLOCK,&en,1);
            if(ret==UCD9081_SCS)
            {
                ucd9081_hdl->flash_lock_sts=0;
            }
        }
        else
        {
            ret=UCD9081_ALRDY_USD;
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This API unlock the ucd9081 flash
 */
static e_ucd9081_err ucd9081_flash_unlock(s_ucd9081* ucd9081_hdl)
{
    e_ucd9081_err ret =UCD9081_ERR;
    uint8_t en;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS)
    {
        if(ucd9081_hdl->flash_lock_sts!=1)
        {
            en=0x02;
            ret= ucd9081_hdl->write(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,UCD9081_FLASHLOCK,&en,1);
            if(ret==UCD9081_SCS)
            {
                ucd9081_hdl->flash_lock_sts=1;
            }
        }
        else
        {
            ret=UCD9081_ALRDY_USD;
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 initialization is set in this function
 */
e_ucd9081_err ucd9081_init(s_ucd9081* ucd9081_hdl)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS)
    {
        uint8_t addr[2]={0x86, 0xE1};
        uint8_t data[2]={0};
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_read(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
            {
                if(data[0]==0xF2)
                {
                    ret=UCD9081_SCS;
                    ret= ucd9081_restart(ucd9081_hdl);
                }
                else
                {
                    ret=UCD9081_ERR;
                }
                ucd9081_flash_unlock(ucd9081_hdl);
            }
            else
            {
                ret=UCD9081_COM_ERR;
            }
        }
        else
        {
            ret =UCD9081_NULL_PTR;
        }
    }
    return ret;
}

/*!
 * @brief This function configure the rail specified in the parameters
 */
e_ucd9081_err ucd9081_rail_config(s_ucd9081* ucd9081_hdl,s_ucd9081_rail_cfg* rail)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS)
    {
        ret = ucd9081_set_undervoltage_thrsld(ucd9081_hdl, rail, rail->udr_vlt_thrsld);
        ret = ucd9081_set_overvoltage_thrsld(ucd9081_hdl, rail, rail->ovr_vlt_thrsld);
        ret = ucd9081_set_enable_polarity(ucd9081_hdl, rail, rail->polarity);
        ret = ucd9081_set_unsequence_time(ucd9081_hdl, rail, rail->unseq_time);
        ret = ucd9081_set_out_of_reg_width(ucd9081_hdl, rail, rail->out_reg_width);
        ret = ucd9081_set_ramp_time(ucd9081_hdl, rail, rail->ramp_time);
        ret = ucd9081_glitch_alrm_cfg(ucd9081_hdl, rail, rail->glt_alrm_sts);
        ret = ucd9081_set_seq_type(ucd9081_hdl, rail, rail->seq_type);
        ret = ucd9081_set_seq_prnt_rail(ucd9081_hdl, rail, rail->prnt_rail);
        ret = ucd9081_set_rail_alrm_typ(ucd9081_hdl, rail, rail->alrm_typ);
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 undervoltage threshold is set in this function
 */
e_ucd9081_err ucd9081_set_undervoltage_thrsld(s_ucd9081* ucd9081_hdl,s_ucd9081_rail_cfg* rail, float voltage)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        float vref;
        if(ucd9081_hdl->v_ref_typ==UCD9081_VREF_INT)
        {
            vref=UCD9081_VREF_INTNL;
        }
        else
        {
            vref=UCD9081_VREF_EXTNL;
        }
        uint16_t vraw;
        uint8_t addr[2]={0};
        uint8_t data[2]={0};
        addr[0]=cfg_flsh_addr[rail->rail_nu][UDR_VOLT_THRSLD_ADR];
        addr[1]=cfg_flsh_addr[rail->rail_nu][UDR_VOLT_THRSLD_ADR]>>8;
        vraw=(rail->ext_vd_en==0)?(1024*voltage)/vref:((1024*voltage)/vref)+((rail->r_pull_down)/(rail->r_pull_up+rail->r_pull_down));
        data[0]=vraw;
        data[1]=0x07 & (vraw>>8);
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_write(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
            {
                rail->udr_vlt_thrsld=voltage;
                ret=ucd9081_flash_lock(ucd9081_hdl);
            }
            else
            {
                ret=UCD9081_COM_ERR;
            }
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 overvoltage threshold is set in this function
 */
e_ucd9081_err ucd9081_set_overvoltage_thrsld(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, float voltage)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        float vref;
        if(ucd9081_hdl->v_ref_typ==UCD9081_VREF_INT)
        {
            vref=UCD9081_VREF_INTNL;
        }
        else
        {
            vref=UCD9081_VREF_EXTNL;
        }
        uint16_t vraw;
        uint8_t addr[2]={0};
        uint8_t data[2]={0};
        addr[0]=cfg_flsh_addr[rail->rail_nu][OVR_VOLT_THRSLD_ADR];
        addr[1]=cfg_flsh_addr[rail->rail_nu][OVR_VOLT_THRSLD_ADR]>>8;
        vraw=(rail->ext_vd_en==0)?(1024*voltage)/vref:((1024*voltage)/vref)+((rail->r_pull_down)/(rail->r_pull_up+rail->r_pull_down));
        data[0]=vraw;
        data[1]=0x07 & (vraw>>8);
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_write(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
            {
                rail->ovr_vlt_thrsld=voltage;
                ret=ucd9081_flash_lock(ucd9081_hdl);
            }
            else
            {
                ret=UCD9081_COM_ERR;
            }
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 polarity enable is set in this function
 */
e_ucd9081_err ucd9081_set_enable_polarity(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail,uint8_t polarity)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail!=NULL)
    {
        uint8_t addr[2]={0};
        uint8_t data[2]={0};
        addr[0]=cfg_flsh_addr[rail->rail_nu][EN_PLRTY_ADR];
        addr[1]=cfg_flsh_addr[rail->rail_nu][EN_PLRTY_ADR]>>8;
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_read(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
            {
                if(polarity==0)
                {
                    data[1]=data[1] & 0x7F;
                }
                else if(polarity==1)
                {
                    data[1]=data[1] & 0xFF;
                }
                if(ucd9081_config_data_write(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
                {
                    rail->polarity=polarity;
                }
            }
            else
            {
                ret=UCD9081_COM_ERR;
            }
            ret=ucd9081_flash_lock(ucd9081_hdl);
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 unsequence time is set in this function
 */
e_ucd9081_err ucd9081_set_unsequence_time(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail,uint16_t time)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        if(time<MAX_DLY_TIME)
        {
            uint8_t addr[2]={0};
            uint8_t data[2]={0};
            addr[0]=cfg_flsh_addr[rail->rail_nu][UNSEQ_TM_ADR];
            addr[1]=cfg_flsh_addr[rail->rail_nu][UNSEQ_TM_ADR]>>8;
            if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
            {
                if(ucd9081_config_data_read(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
                {
                    data[0]=time;
                    data[1]=(data[1] & 0xE0)|time>>8;
                    if(ucd9081_config_data_write(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
                    {
                        rail->unseq_time=time;
                        ret=ucd9081_flash_lock(ucd9081_hdl);
                    }
                    else
                    {
                        ret=UCD9081_COM_ERR;
                    }
                }
            }
        }
        else
        {
            ret = UCD9081_INVLD_ARG;
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 out of regulation width is set in this function
 */
e_ucd9081_err ucd9081_set_out_of_reg_width(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, uint16_t width)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        uint8_t addr[2]={0};
        uint8_t data[2]={0};
        addr[0]=cfg_flsh_addr[rail->rail_nu][OUT_REG_WDTH_ADR];
        addr[1]=cfg_flsh_addr[rail->rail_nu][OUT_REG_WDTH_ADR]>>8;
        data[0]=width;
        data[1]=0x0F & (width>>8);
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_write(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
            {
                rail->out_reg_width=width;
                ret=ucd9081_flash_lock(ucd9081_hdl);
            }
            else
            {
                ret=UCD9081_COM_ERR;
            }
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 ramp time is set in this function
 */
e_ucd9081_err ucd9081_set_ramp_time(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, uint16_t ramp_tm)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        if(ramp_tm<MAX_DLY_TIME)
        {
            uint8_t addr[2]={0};
            uint8_t data[2]={0};
            addr[0]=cfg_flsh_addr[rail->rail_nu][RAMP_TIME_ADR];
            addr[1]=cfg_flsh_addr[rail->rail_nu][RAMP_TIME_ADR]>>8;
            data[0]=ramp_tm;
            data[1]=0x0F & (ramp_tm>>8);
            if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
            {
                if(ucd9081_config_data_write(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
                {
                    rail->ramp_time=ramp_tm;
                    ret=ucd9081_flash_lock(ucd9081_hdl);
                }
                else
                {
                    ret=UCD9081_COM_ERR;
                }
            }
        }
        else
        {
            ret=UCD9081_INVLD_ARG;
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief  UCD9081 dependancy mask is set in this function
 */
e_ucd9081_err ucd9081_set_dependency_mask(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail,uint16_t dpdncy_msk)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        uint8_t addr[2]={0};
        uint8_t data[2]={0};
        addr[0]=cfg_flsh_addr[rail->rail_nu][DPNDNCY_MSK_ADR];
        addr[1]=cfg_flsh_addr[rail->rail_nu][DPNDNCY_MSK_ADR]>>8;
        data[0]=dpdncy_msk;
        data[1]=0x0F & (dpdncy_msk>>8);
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_write(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
            {
                rail->dpdncy_mask=dpdncy_msk;
                ret=ucd9081_flash_lock(ucd9081_hdl);
            }
            else
            {
                ret=UCD9081_COM_ERR;
            }
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 voltage reference configuration in this function
 */
e_ucd9081_err ucd9081_vref_cfg(s_ucd9081* ucd9081_hdl,uint8_t v_ref)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS)
    {
        uint8_t addr[2]={0x86, 0xE1};
        uint8_t data[2]={0};
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_read(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
            {
                if(v_ref==0)
                {
                    data[1]=data[1] & 0x0F;
                }
                else
                {
                    data[1]= data[1] | 0x20;
                }
                ret=ucd9081_config_data_write(ucd9081_hdl, addr, data, 2);
                if(ret==UCD9081_SCS)
                {
                    ucd9081_hdl->v_ref_typ=v_ref;
                }
                ucd9081_flash_lock(ucd9081_hdl);
            }
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 glitch alarm configuration in this function
 */
e_ucd9081_err ucd9081_glitch_alrm_cfg(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, uint8_t glth_alrm_sts)
{
    e_ucd9081_err ret =UCD9081_ERR;
    uint8_t mask=0x01;
    uint8_t addr[]={0x6A,0xEA};
    uint8_t data;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_read(ucd9081_hdl, addr, &data, 1)==UCD9081_SCS)
            {
                if(glth_alrm_sts==0)
                {
                    data = data | mask << rail->rail_nu;
                }
                else if(glth_alrm_sts==1)
                {
                    data = (data) & (~(mask << rail->rail_nu));
                }
                ret=ucd9081_config_data_write(ucd9081_hdl, addr, &data, 1);
                ucd9081_flash_lock(ucd9081_hdl);
            }
            else
            {
                ret =UCD9081_COM_ERR;
            }
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 restart in this function
 */
e_ucd9081_err ucd9081_restart(s_ucd9081* ucd9081_hdl)
{
    e_ucd9081_err ret =UCD9081_ERR;
    uint8_t restart=0xC0;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS)
    {
        ret= ucd9081_hdl->write(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,UCD9081_RESTART,&restart,1);
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 force restart in this function
 */
e_ucd9081_err ucd9081_force_restart(s_ucd9081* ucd9081_hdl)
{
    e_ucd9081_err ret =UCD9081_ERR;
    uint8_t restart=0x0;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS)
    {
        ret= ucd9081_hdl->write(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,UCD9081_RESTART,&restart,1);
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief get the UCD9081 firmware version
 */
e_ucd9081_err ucd9081_get_fw_version(s_ucd9081* ucd9081_hdl,uint8_t *version)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS)
    {
        ret= ucd9081_hdl->read(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,UCD9081_VERSION,version,1);
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This API is used to read the voltage of ucd9081
 */
static float ucd9081_read_voltage(s_ucd9081* ucd9081_hdl,uint8_t addr_h, uint8_t addr_l,s_ucd9081_rail_cfg* rail, float vref)
{
    uint8_t rail_vn_l;
    uint8_t rail_vn_h;
    float voltage;
    uint16_t v_raw;
    ucd9081_hdl->read(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,addr_h,&rail_vn_l,1);
    ucd9081_hdl->read(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr,addr_l,&rail_vn_h,1);
    v_raw=rail_vn_l|(rail_vn_h<<8);
    voltage=(rail->ext_vd_en==0)?(v_raw/1024)*vref:(v_raw/1024)*vref + ((rail->r_pull_down+rail->r_pull_up)/rail->r_pull_down);
    return voltage;
}

/*!
 * @brief get UCD9081 voltage
 */
e_ucd9081_err ucd9081_get_voltage(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, float* voltage)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail !=NULL)
    {
        float vref;
        if(ucd9081_hdl->v_ref_typ==UCD9081_VREF_INT)
        {
            vref=UCD9081_VREF_INTNL;
        }
        else
        {
            vref=UCD9081_VREF_EXTNL;
        }
        switch(rail->rail_nu)
        {
            case UCD9081_RAIL1:
                *voltage = ucd9081_read_voltage(ucd9081_hdl, UCD9081_RAIL1H, UCD9081_RAIL1L, rail, vref);
                break;
            case UCD9081_RAIL2:
                *voltage = ucd9081_read_voltage(ucd9081_hdl, UCD9081_RAIL2H, UCD9081_RAIL2L, rail, vref);
                break;
            case UCD9081_RAIL3:
                *voltage = ucd9081_read_voltage(ucd9081_hdl, UCD9081_RAIL3H, UCD9081_RAIL3L, rail, vref);
                break;
            case UCD9081_RAIL4:
                *voltage = ucd9081_read_voltage(ucd9081_hdl, UCD9081_RAIL4H, UCD9081_RAIL4L, rail, vref);
                break;
            case UCD9081_RAIL5:
                *voltage = ucd9081_read_voltage(ucd9081_hdl, UCD9081_RAIL5H, UCD9081_RAIL5L, rail, vref);
                break;
            case UCD9081_RAIL6:
                *voltage = ucd9081_read_voltage(ucd9081_hdl, UCD9081_RAIL6H, UCD9081_RAIL6L, rail, vref);
                break;
            case UCD9081_RAIL7:
                *voltage = ucd9081_read_voltage(ucd9081_hdl, UCD9081_RAIL7H, UCD9081_RAIL7L, rail, vref);
                break;
            case UCD9081_RAIL8:
                *voltage = ucd9081_read_voltage(ucd9081_hdl, UCD9081_RAIL8H, UCD9081_RAIL8L, rail, vref);
                break;
            default:
                ret=UCD9081_INVLD_ARG;
                break;
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief get UCD9081 alarm pending status
 */
e_ucd9081_err ucd9081_get_alrm_pndng_sts(s_ucd9081* ucd9081_hdl, uint8_t* rail_err_sts)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS)
    {
        ret= ucd9081_hdl->read(ucd9081_hdl->intf_hdl, ucd9081_hdl->slv_addr, UCD9081_RAILSTATUS2, rail_err_sts, 1);
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 sequence type is set in this function
 */
e_ucd9081_err ucd9081_set_seq_type(s_ucd9081* ucd9081_hdl,s_ucd9081_rail_cfg* rail, uint8_t seq_tp)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        uint8_t addr[2]={0};
        uint8_t data;
        addr[0]=cfg_flsh_addr[rail->rail_nu][SEQ_EVT_PARA_ADR];
        addr[1]=cfg_flsh_addr[rail->rail_nu][SEQ_EVT_PARA_ADR]>>8;
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_read(ucd9081_hdl, addr, &data, 1)==UCD9081_SCS)
            {
                data= data & 0x2F;
                data= data | (seq_tp<<6);
                if(ucd9081_config_data_write(ucd9081_hdl, addr, &data, 1)==UCD9081_SCS)
                {
                    rail->seq_type=seq_tp;
                    ret=ucd9081_flash_lock(ucd9081_hdl);
                }
            }
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 sequence delay is set in this function
 */
e_ucd9081_err ucd9081_set_seq_delay(s_ucd9081* ucd9081_hdl,s_ucd9081_rail_cfg* rail, uint16_t dly_tm)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        if(dly_tm<MAX_DLY_TIME)
        {
            uint8_t addr[2]={0};
            uint8_t data[2]={0};
            addr[0]=cfg_flsh_addr[rail->rail_nu][SEQ_EVT_DTA_ADR];
            addr[1]=cfg_flsh_addr[rail->rail_nu][SEQ_EVT_DTA_ADR]>>8;
            if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
            {
                if(ucd9081_config_data_read(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
                {
                    data[0]=dly_tm;
                    data[1]= (data[1] & 0xE0)| (dly_tm>>8);
                    if(ucd9081_config_data_write(ucd9081_hdl, addr, data, 1)==UCD9081_SCS)
                    {
                        rail->seq_dly_tm=dly_tm;
                        ret=ucd9081_flash_lock(ucd9081_hdl);
                    }
                }
            }
        }
        else
        {
            ret =UCD9081_INVLD_ARG;
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 sequence parent voltage level is set in this function
 */
e_ucd9081_err ucd9081_set_seq_prnt_vltg_lvl(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* actual_rail, s_ucd9081_rail_cfg* prnt_rail, float voltage )
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && actual_rail != NULL && prnt_rail != NULL)
    {
        float vref;
        if(ucd9081_hdl->v_ref_typ==UCD9081_VREF_INT)
        {
            vref=UCD9081_VREF_INTNL;
        }
        else
        {
            vref=UCD9081_VREF_EXTNL;
        }
        uint8_t addr[2]={0};
        uint8_t data[2]={0};
        uint16_t vraw;
        addr[0]=cfg_flsh_addr[actual_rail->rail_nu][SEQ_EVT_DTA_ADR];
        addr[1]=cfg_flsh_addr[actual_rail->rail_nu][SEQ_EVT_DTA_ADR]>>8;
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_read(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
            {
                vraw=(prnt_rail->ext_vd_en==0)?(1024*voltage)/vref:((1024*voltage)/vref)+((prnt_rail->r_pull_down)/(prnt_rail->r_pull_up+prnt_rail->r_pull_down));
                data[0]=vraw;
                data[1]= (data[1] & 0xE0)|(vraw>>8);
                if(ucd9081_config_data_write(ucd9081_hdl, addr, data, 1)==UCD9081_SCS)
                {
                    actual_rail->prnt_vlt = voltage;
                    ret=ucd9081_flash_lock(ucd9081_hdl);
                }
            }
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 sequence parent rail is set in this function
 */
e_ucd9081_err ucd9081_set_seq_prnt_rail(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* actual_rail, e_ucd9081_rail_no prnt_rail)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && actual_rail != NULL)
    {
        uint8_t addr[2]={0};
        uint8_t data;
        addr[0]=cfg_flsh_addr[actual_rail->rail_nu][SEQ_EVT_LNK_ADR];
        addr[1]=cfg_flsh_addr[actual_rail->rail_nu][SEQ_EVT_LNK_ADR]>>8;
        if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
        {
            if(ucd9081_config_data_read(ucd9081_hdl, addr, &data, 1)==UCD9081_SCS)
            {
                data= (data & 0x40)| ((uint8_t)prnt_rail);
                if(ucd9081_config_data_write(ucd9081_hdl, addr, &data, 1)==UCD9081_SCS)
                {
                    actual_rail->prnt_rail=prnt_rail;
                    ret=ucd9081_flash_lock(ucd9081_hdl);
                }
            }
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This API is used to check null pointer
 */
e_ucd9081_err ucd9081_rail_mntr_enable_disable(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, uint8_t mntr_sts)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        if(mntr_sts < 0 || mntr_sts > 1)
        {
            uint8_t addr[2]={0};
            uint8_t data;
            addr[0]=cfg_flsh_addr[rail->rail_nu][SEQ_EVT_PARA_ADR];
            addr[1]=cfg_flsh_addr[rail->rail_nu][SEQ_EVT_PARA_ADR]>>8;
            if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
            {
                if(ucd9081_config_data_read(ucd9081_hdl, addr, &data, 1)==UCD9081_SCS)
                {
                    data= data & 0xCF;
                    data= data| mntr_sts<<4;
                    if(ucd9081_config_data_write(ucd9081_hdl, addr, &data, 1)==UCD9081_SCS)
                    {
                        rail->mntr_sts=mntr_sts;
                        ret=ucd9081_flash_lock(ucd9081_hdl);
                    }
                }
            }
        }
        else
        {
            ret=UCD9081_INVLD_ARG;
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This API is used to enable or disable the resequence rail
 */
e_ucd9081_err ucd9081_rail_reseq_enable_disable(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail,uint8_t reseq_sts)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        if(reseq_sts < 0 || reseq_sts > 1)
        {
            uint8_t addr[2]={0};
            uint8_t data;
            addr[0]=cfg_flsh_addr[rail->rail_nu][SEQ_EVT_LNK_ADR];
            addr[1]=cfg_flsh_addr[rail->rail_nu][SEQ_EVT_LNK_ADR]>>8;
            if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
            {
                if(ucd9081_config_data_read(ucd9081_hdl, addr, &data, 1)==UCD9081_SCS)
                {
                    data= (data & 0x0F)| (reseq_sts<<6);
                    if(ucd9081_config_data_write(ucd9081_hdl, addr, &data, 1)==UCD9081_SCS)
                    {
                        rail->reseq_sts = reseq_sts;
                        ret=ucd9081_flash_lock(ucd9081_hdl);
                    }
                }
            }
        }
        else
        {
            ret=UCD9081_INVLD_ARG;
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief UCD9081 rail alarm type is set in this function
 */
e_ucd9081_err ucd9081_set_rail_alrm_typ(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, uint8_t alrm_typ)
{
    e_ucd9081_err ret =UCD9081_ERR;
    if(ucd9081_null_ptr_check(ucd9081_hdl)==UCD9081_SCS && rail != NULL)
    {
        if(alrm_typ > UCD9081_MAX_ALRM_TYP)
        {
            uint8_t addr[2]={0};
            uint8_t data[2]={0};
            addr[0]=cfg_flsh_addr[rail->rail_nu][SEQ_EVT_DTA_ADR];
            addr[1]=cfg_flsh_addr[rail->rail_nu][SEQ_EVT_DTA_ADR]>>8;
            if(ucd9081_flash_unlock(ucd9081_hdl)==UCD9081_SCS)
            {
                if(ucd9081_config_data_read(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
                {
                    data[1] = data[1] & 0x0F;
                    data[1] = data[1] | alrm_typ<<5;
                    if(ucd9081_config_data_write(ucd9081_hdl, addr, data, 2)==UCD9081_SCS)
                    {
                        rail->alrm_typ = alrm_typ;
                        ret=ucd9081_flash_lock(ucd9081_hdl);
                    }
                }
            }
        }
        else
        {
            ret=UCD9081_INVLD_ARG;
        }
    }
    else
    {
        ret =UCD9081_NULL_PTR;
    }
    return ret;
}


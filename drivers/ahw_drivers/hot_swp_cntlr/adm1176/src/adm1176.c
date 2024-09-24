/**
 * @file adm1176.c
 *
 *  @brief This file contains the function definition of hotswap controller ADM1176
 *
 *	@copyright Copyright 2024 Antaris, Inc.
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

#include "adm1176.h"

/*!
 * @brief This API is used to check null pointer
 */
static e_adm1176_err null_ptr_check(const s_adm1176_drv_cb_ptr dev)
{
    e_adm1176_err rslt;
    if ((dev == NULL) || (dev->read == NULL) || (dev->write == NULL))
    {
        rslt = NULL_PTR_ER;
    }
    else
    {

        rslt = ADM1176_SCS;
    }
    return rslt;
}

/*!
 *  @brief This API creates the control block memory and initialize the startup configurations for adm1176 instance.
 */
e_adm1176_err adm1176_init(s_adm1176_drv_cb_ptr adm1176_hdl)
{
    e_adm1176_err sts= ADM1176_ERR;
    sts=null_ptr_check(adm1176_hdl);
    if(sts!=ADM1176_SCS)
    {
        sts=NULL_PTR_ER;
    }
    else
    {
        adm1176_hdl->voltage_read_mode=1;
        sts=ADM1176_SCS;
    }
    return sts;
}

/*!
 *  @brief This API releases the control block memory for adm1176 instance
 */
e_adm1176_err adm1176_deinit(s_adm1176_drv_cb_ptr adm1176_hdl)
{
    e_adm1176_err sts= ADM1176_ERR;
    sts=null_ptr_check(adm1176_hdl);
    if(sts!=ADM1176_SCS)
    {
        sts=ADM1176_SCS;
    }
    else
    {
        sts=ADM1176_ERR;
    }
    return sts;
}

/*!
 *  @brief This API reads and returns the voltage in volts by pass by reference
 */
e_adm1176_err adm1176_read_voltage(s_adm1176_drv_cb_ptr adm1176_hdl, float *voltage )
{
    e_adm1176_err sts= ADM1176_ERR;
    uint8_t cmd =0x00;
    uint8_t volt_arr[2]={0};
    *voltage=0;
    sts=null_ptr_check(adm1176_hdl);
    if(sts!=ADM1176_SCS || voltage==NULL)
    {
        sts=NULL_PTR_ER;
    }
    else
    {
        if(adm1176_hdl->voltage_read_mode == 1)
        {
            cmd =0x02;
            sts=adm1176_hdl->write(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr, &cmd, 1);
            adm1176_hdl->delay(200);
            if(sts==ADM1176_SCS)
            {
                sts=adm1176_hdl->read(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr, volt_arr, 2);
            }
        }
        else
        {
            cmd =0x01;
            adm1176_hdl->write(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr, &cmd, 1);
            while(volt_arr[0]==0 && volt_arr[1]==0 )
            {
                sts=adm1176_hdl->read(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr, volt_arr, 2);
                if(sts!=ADM1176_SCS);
                break;
            }
        }
        if(sts==ADM1176_SCS)
        {
            adm1176_hdl->rdbck_type=0;
            *voltage= (volt_arr[0]<<4 | volt_arr[1]>>4);
            *voltage=(V_FULL_SCALE/4096)*(*voltage);
        }
    }
    return(sts);
}

/*!
 *  @brief This API reads and returns the current by pass by reference
 */
e_adm1176_err adm1176_read_current(s_adm1176_drv_cb_ptr adm1176_hdl, float *current)
{
    e_adm1176_err sts= ADM1176_ERR;
    uint8_t cmd =0x00;
    uint8_t curr_arr[2]={0};
    *current=0;
    sts=null_ptr_check(adm1176_hdl);
    if(sts!=ADM1176_SCS||current == NULL)
    {
        sts=NULL_PTR_ER;
    }
    else
    {
        if(adm1176_hdl->current_read_mode == 1)
        {
            cmd =0x08;
            adm1176_hdl->write(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr, &cmd, 1);
            adm1176_hdl->delay(200);
            if(sts==ADM1176_SCS)
            {
                sts=adm1176_hdl->read(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr, curr_arr, 2);
            }
        }
        else
        {
            cmd =0x04;
            adm1176_hdl->write(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr, &cmd, 1);
            while(curr_arr[0]==0 && curr_arr[1]==0 )
            {
                sts=adm1176_hdl->read(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr, curr_arr, 2);
                if(sts!=ADM1176_SCS);
                break;
            }
        }
        if(sts==ADM1176_SCS)
        {
            adm1176_hdl->rdbck_type=0;
            *current= (curr_arr[0]<<4 | curr_arr[1]>>4);
            *current = (((I_FULL_SCALE)/4096.0)*(*current))/SENSE_RESISTOR;
        }
    }
    return(sts);
}

/*!
 *  @brief This API turn on/off hotswapping operations manually.
 */
e_adm1176_err adm1176_hotswap_control(s_adm1176_drv_cb_ptr adm1176_hdl, uint8_t on_off)
{
    e_adm1176_err sts= ADM1176_ERR;
    uint8_t reg_data[2]={0};
    reg_data[0]=CONTROL;
    reg_data[1]=on_off;
    sts=null_ptr_check(adm1176_hdl);
    if(sts!=ADM1176_SCS)
    {
        sts=NULL_PTR_ER;
    }
    else
    {
        if(adm1176_hdl->hot_swp_sts!=on_off)
        {
            sts=adm1176_hdl->write(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr,reg_data,2);
            if(sts==ADM1176_SCS)
            {
                adm1176_hdl->hot_swp_sts=on_off;
            }
        }
        else
        {
            sts=ADM1176_ERR;
        }
    }
    return (sts);
}

/*!
 *  @brief This API reads and stores the status byte
 */
e_adm1176_err adm1176_get_sts(s_adm1176_drv_cb_ptr adm1176_hdl,uint8_t *sts)
{
    e_adm1176_err err_sts;
    uint8_t cmd =0x40;
    err_sts=null_ptr_check(adm1176_hdl);
    if(sts!=ADM1176_SCS || sts==NULL)
    {
        err_sts=NULL_PTR_ER;
    }
    else
    {
        if(adm1176_hdl->rdbck_type==1)
        {
            err_sts=adm1176_hdl->read(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr, sts, 1);
        }
        else
        {
            err_sts=adm1176_hdl->write(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr,&cmd,1);
            if(err_sts==ADM1176_SCS)
            {
                adm1176_hdl->rdbck_type=1;
                err_sts=adm1176_hdl->read(adm1176_hdl->intf_hdl, adm1176_hdl->slv_addr, sts, 1);
            }

        }
    }
    return err_sts;
}

/*!
 *  @brief This API reads and stores the hotswap status
 */
e_adm1176_err adm1176_get_hotswap_sts(s_adm1176_drv_cb_ptr adm1176_hdl, uint8_t *hotswap_sts)
{
    uint8_t var;
    e_adm1176_err sts;
    sts=null_ptr_check(adm1176_hdl);
    if(sts!=ADM1176_SCS || hotswap_sts==NULL)
    {
        sts=NULL_PTR_ER;
    }
    else
    {
        sts=adm1176_get_sts(adm1176_hdl, &var);
        if(sts==ADM1176_SCS)
        {
            adm1176_hdl->over_curr_sts=(0x01 & (var));
            adm1176_hdl->hot_swp_sts=(0x10 & (var));
            *hotswap_sts = (uint8_t)adm1176_hdl->hot_swp_sts;
        }
    }
    return (sts);
}

/*!
 *  @brief This API reads and stores the overcurrent status
 */
e_adm1176_err adm1176_get_overcurrent_sts(s_adm1176_drv_cb_ptr adm1176_hdl, uint8_t *under_vlt_sts)
{
    uint8_t var;
    e_adm1176_err sts;
    sts=null_ptr_check(adm1176_hdl);
    if(sts!=ADM1176_SCS ||under_vlt_sts==NULL)
    {
        sts=NULL_PTR_ER;
    }
    else
    {
        sts=adm1176_get_sts(adm1176_hdl, &var);
        if(sts==ADM1176_SCS)
        {
            adm1176_hdl->over_curr_sts=(0x01 & (var));
            adm1176_hdl->hot_swp_sts=(0x10 & (var));
            *under_vlt_sts = (uint8_t)adm1176_hdl->over_curr_sts;
        }
    }
    return (sts);
}

/**
 * @file exo_ahw_vdp_dt_ds620.c
 *
 * @brief This file contains vendor driver porting function of DS620 digital thermostat
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
#include "exo_ahw_vdp_dt_ds620.h"
#include "exo_ahw_al_linux_wrpr.h"
#include "exo_osal_mem_management.h"
#include "exo_osal_thread.h"
#include "ds620.h"

extern ahw_io_map *ahw_io_lookup_tble[MAX_AH_INST_ID];
extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

#ifndef LINUX_TEMP_PORT

/*!
 *  @brief I2C read hook function for DS620 module
 */
int8_t ds620_i2c_read(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)(slv_addr), &reg_addr, 1, 500))
    {
        if(HAL_SCS == io_hal_i2c_receive(hi2c, (uint16)(slv_addr), data, len, 500))
        {
            rslt = DS620_SCS;
        }
        else
        {
            rslt = DS620_E_COM_FAIL;
        }
    }
    else
    {
        rslt = DS620_E_COM_FAIL;
    }
    return rslt;
}

/*!
 *  @brief I2C write hook function for DS620 module
 */
int8_t ds620_i2c_write(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    uint8_t data_send[3];
    data_send[0]=reg_addr;
    data_send[1]=data[0];
    if(len>1)
        data_send[2]=data[1];
    len++;
    if(data==NULL)
    {
        rslt = io_hal_i2c_transmit(hi2c, (uint16)(slv_addr),&reg_addr, 1, 500);
        return rslt;
    }
    if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)(slv_addr), data_send,len , 500))
    {
        rslt = DS620_SCS;
    }
    else
    {
        rslt = DS620_E_COM_FAIL;
    }
    return rslt;
}
#endif

/*!
 *  @brief This API initialize the control block memory and do basic configurations
 */
hal_ret_sts ahw_vdp_dt_ds620_init(ahw_al_dt_hdle *ahw_al_hdt)
{

    hal_ret_sts sts = HAL_MAX_ERR;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO DS620 Digital thermostat - AH-Vendor driver porting layer Initialise");
    printf("\n EXO DS620 Digital thermostat - AH-Vendor driver Initialise");
    printf("\n EXO DS620 Digital thermostat - AH-Vendor driver Initialisation completed successfully ");
    usleep(100000);
    printf("\n EXO DS620 Digital thermostat - AH-Vendor driver porting layer initialisation completed successfully");

#else 
    s_ds620_drv_cb* hdt=(s_ds620_drv_cb*)os_malloc(sizeof(s_ds620_drv_cb));
    hdt->write = ds620_i2c_write;
    hdt->read = ds620_i2c_read;
    hdt->delay_ms = (ds620_delay_ms_fptr)os_delay;
    hdt->intf_hdl = intf_inst_hdle_ptr[ahw_io_lookup_tble[ahw_al_hdt->ahw_gen_info.ahw_inst_id]->io_instance_id];
    hdt->slv_addr=ahw_io_lookup_tble[ahw_al_hdt->ahw_gen_info.ahw_inst_id]->slv_addr;
    hdt->temp_high_thrshd=ahw_al_hdt->high_temp_thrsld;
    hdt->temp_low_thrshd=ahw_al_hdt->low_temp_thrsld;
    hdt->resolution=BIT_13;
    hdt->mode=CONTINOUS_CONV;
    hdt->conv_type=AUTO_CONV_ENABLE;
    hdt->po_level_type=PO_HIGH;

    ahw_al_hdt->ahw_gen_info.vdp_inst_hdle = (void*)hdt;
    ahw_al_hdt->ahw_gen_info.slave_address=hdt->slv_addr;
    ahw_al_hdt->ahw_gen_info.io_intf_hdle=hdt->intf_hdl;

    if(HAL_SCS == (hal_ret_sts)ds620_init(hdt))
    {
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
 *  @brief This API release the control block memory of ds620 instance
 */
hal_ret_sts ahw_vdp_dt_ds620_deinit (ahw_al_dt_hdle *al_dt)
{
    hal_ret_sts sts =HAL_SCS;
    sts=ds620_deinit((s_ds620_drv_cb*)al_dt->ahw_gen_info.vdp_inst_hdle);
    os_free(al_dt->ahw_gen_info.vdp_inst_hdle);
    return sts;
}

/*!
 *  @brief This API set the high temperature threshold of DS620 for thermostat operation
 */
hal_ret_sts ahw_vdp_dt_ds620_set_temperature_high_threshold (ahw_al_dt_hdle *al_dt, double high_temp_threshold)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_set_temperature_high_thrshd (ds620_hdl_vdp, high_temp_threshold))
    {
        al_dt->high_temp_thrsld=high_temp_threshold;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API set the low temperature threshold of DS620 for thermostat operation
 */
hal_ret_sts ahw_vdp_dt_ds620_set_temperature_low_threshold (ahw_al_dt_hdle *al_dt, double low_temp_threshold)
{
    e_ds620_err sts ;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_set_temperature_low_thrshd (ds620_hdl_vdp, low_temp_threshold)){

        al_dt->low_temp_thrsld=low_temp_threshold;
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API reads temperature and returns it
 */
hal_ret_sts ahw_vdp_dt_ds620_get_temperature (ahw_al_dt_hdle *al_dt, double* temperature)
{
    e_ds620_err sts ;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_get_temperature (ds620_hdl_vdp,temperature))
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
 *  @brief This API writes the temperature value in the temperature register, It will be use to auto test the thermostat
 */
hal_ret_sts ahw_vdp_dt_ds620_set_temperature (ahw_al_dt_hdle *al_dt, double temperature)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_set_temperature (ds620_hdl_vdp,temperature))
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
 *  @brief This API configures the DS620 with initial configuration values
 */
hal_ret_sts ahw_vdp_dt_ds620_config (ahw_al_dt_hdle *al_dt)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_config (ds620_hdl_vdp))
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
 *  @brief This API sets the ADC resolution of the DS620
 */
hal_ret_sts ahw_vdp_dt_ds620_set_resolution (ahw_al_dt_hdle *al_dt, digital_thermos_resolution res)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    e_ds620_res vd_res=0;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;

    switch(res)
    {
        case DT_BIT_10:
            vd_res = BIT_10;
            break;
        case DT_BIT_11:
            vd_res = BIT_11;
            break;
        case DT_BIT_12:
            vd_res = BIT_12;
            break;
        case DT_BIT_13:
            vd_res = BIT_13;
            break;
        default:
            break;
    }
    if(HAL_SCS == (hal_ret_sts)ds620_set_resolution (ds620_hdl_vdp, vd_res))
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
 *  @brief This API gets the ADC resolution of the DS620
 */
hal_ret_sts ahw_vdp_dt_ds620_get_resolution(ahw_al_dt_hdle *al_dt, digital_thermos_resolution *res )
{
    e_ds620_err sts;
    e_ds620_res vd_res;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_get_resolution(ds620_hdl_vdp,&vd_res))
    {
        switch(vd_res)
        {
            case BIT_10:
                *res = DT_BIT_10;
                break;
            case BIT_11:
                *res = DT_BIT_11;
                break;
            case BIT_12:
                *res = DT_BIT_12;
                break;
            case BIT_13:
                *res = DT_BIT_13;
                break;
            default:
                break;
        }
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API sets the operating mode of DS620, the value can be ONESHOT_CONV or continuous conversion
 */
hal_ret_sts ahw_vdp_dt_ds620_set_conv_mode (ahw_al_dt_hdle *al_dt, uint8_t mode)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_set_conv_mode(ds620_hdl_vdp,mode))
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
 *  @brief This API set the PO pin level type, the values can be high, low and force low
 */
hal_ret_sts ahw_vdp_dt_ds620_set_po_lvl (ahw_al_dt_hdle *al_dt, uint8_t lvl)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_set_po_lvl (ds620_hdl_vdp, lvl))
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
 *  @brief This API resets the DS620
 */
hal_ret_sts ahw_vdp_dt_ds620_reset(ahw_al_dt_hdle *al_dt)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_reset(ds620_hdl_vdp))
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
 *  @brief This API start temperature conversion
 */
hal_ret_sts ahw_vdp_dt_ds620_start_conversion(ahw_al_dt_hdle *al_dt)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_start_conversion(ds620_hdl_vdp))
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
 *  @brief This API stop temperature conversion
 */
hal_ret_sts ahw_vdp_dt_ds620_stop_conversion(ahw_al_dt_hdle *al_dt)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_stop_conversion(ds620_hdl_vdp))
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
 *  @brief This API get the PO pin level
 */
hal_ret_sts ahw_vdp_dt_ds620_get_po_lvl(ahw_al_dt_hdle *al_dt,uint8_t *lvl)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_get_po_lvl(ds620_hdl_vdp,lvl))
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
 *  @brief This API get the PO pin level alert status
 */
hal_ret_sts ahw_vdp_dt_ds620_get_po_lvl_alert_sts(ahw_al_dt_hdle *al_dt, uint8_t *alert_sts)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_get_po_lvl_alert_sts(ds620_hdl_vdp,(e_ds620_po_lvl*)alert_sts))
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
 *  @brief This API get the operating mode
 */
hal_ret_sts ahw_vdp_dt_ds620_get_mode(ahw_al_dt_hdle *al_dt,uint8_t *mode)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_get_mode(ds620_hdl_vdp,mode))
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
 *  @brief This API get low temperature threshold
 */
hal_ret_sts ahw_vdp_dt_ds620_get_temperature_low_thrshd(ahw_al_dt_hdle *al_dt, double *low_temp_thrshld)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_get_temperature_low_thrshd(ds620_hdl_vdp, low_temp_thrshld))
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
 *  @brief This API get high temperature threshold
 */
hal_ret_sts ahw_vdp_dt_ds620_get_temperature_high_thrshd(ahw_al_dt_hdle *al_dt, double *high_temp_thrshld)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_get_temperature_high_thrshd(ds620_hdl_vdp, high_temp_thrshld))
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
 *  @brief This API resets alert flag
 */
hal_ret_sts ahw_vdp_dt_ds620_reset_alert_flag(ahw_al_dt_hdle *al_dt)
{
    e_ds620_err sts;
    s_ds620_drv_cb_ptr ds620_hdl_vdp;
    ds620_hdl_vdp = (s_ds620_drv_cb_ptr) al_dt->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ds620_reset_alert_flag(ds620_hdl_vdp))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}


#endif

/**
 * @file exo_ahw_vdp_adm1176.c
 *
 * @brief This file contains the vendor driver porting function of ADM1176 hot swap controller
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

#include <unistd.h>
#include "exo_ahw_vdp_hsc_adm1176.h"
#include "exo_osal_mem_management.h"
#include "exo_osal_thread.h"
#include "exo_ahw_al_linux_wrpr.h"
#include "adm1176.h"

extern ahw_io_map *ahw_io_lookup_tble[MAX_AH_INST_ID];
extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

#ifndef LINUX_TEMP_PORT
/*!
 *  @brief I2C read hook function for ADM1176 module
 */
int8_t adm1176_i2c_read(void* intf_hdl, uint16_t slv_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    if(HAL_SCS == io_hal_i2c_receive(hi2c,slv_addr, data, len, 500))
    {
        rslt = ADM1176_SCS;
    }
    else
    {
        rslt = ADM1176_E_COM_FAIL;
    }

    return rslt;
}

/*!
 *  @brief I2C write hook function for ADM1176 module
 */
int8_t adm1176_i2c_write(void* intf_hdl, uint16_t slv_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    if(HAL_SCS == io_hal_i2c_transmit(hi2c,slv_addr, data, len, 500))
    {
        rslt = ADM1176_SCS;
    }
    else
    {
        rslt = ADM1176_E_COM_FAIL;
    }
    return rslt;
}

#endif 
/*!
 *  @brief This API initializes the control block memory and do the basic configurations for ADM1176 instance
 */
hal_ret_sts ahw_vdp_hsc_adm1176_init(ahw_al_hsc_hdl *ahw_al_hsc)
{
    hal_ret_sts sts = HAL_MAX_ERR;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO Hot swap controller - AH-Vendor driver porting layer Initialise");
    printf("\n EXO Hot swap controller - AH-Vendor driver Initialise");
    printf("\n EXO Hot swap controller - AH-Vendor driver Initialisation completed successfully ");
    usleep(100000);
    printf("\n EXO Hot swap controller - AH-Vendor driver porting layer initialisation completed successfully");

#else 
    s_adm1176_drv_cb* hsc=(s_adm1176_drv_cb*)os_malloc(sizeof(s_adm1176_drv_cb));
    hsc->write = adm1176_i2c_write;
    hsc->read = adm1176_i2c_read;
    hsc->delay = (adm1176_delay_fptr_t)os_delay;
    hsc->intf_hdl = intf_inst_hdle_ptr[ahw_io_lookup_tble[ahw_al_hsc->ahw_gen_info.ahw_inst_id]->io_instance_id];
    hsc->slv_addr=ahw_io_lookup_tble[ahw_al_hsc->ahw_gen_info.ahw_inst_id]->slv_addr;

    ahw_al_hsc->ahw_gen_info.vdp_inst_hdle = (void*)hsc;
    ahw_al_hsc->ahw_gen_info.io_intf_hdle=hsc->intf_hdl;

    if(HAL_SCS == (hal_ret_sts)adm1176_init(hsc))
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
 *  @brief This API deinitializes the control block memory.
 */
hal_ret_sts ahw_vdp_hsc_adm1176_deinit(ahw_al_hsc_hdl *ahw_al_hsc)
{
    hal_ret_sts sts =HAL_SCS;
    sts=adm1176_deinit((s_adm1176_drv_cb*)ahw_al_hsc->ahw_gen_info.vdp_inst_hdle);

    os_free(ahw_al_hsc->ahw_gen_info.vdp_inst_hdle);
    return sts;
}

/*!
 *  @brief This API reads and returns the voltage
 */
hal_ret_sts ahw_vdp_hsc_adm1176_read_voltage(ahw_al_hsc_hdl *al_hsc, float *voltage )
{
    e_adm1176_err sts;
    s_adm1176_drv_cb_ptr adm1176_hdl_vdp;
    adm1176_hdl_vdp = (s_adm1176_drv_cb_ptr) al_hsc->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS==(hal_ret_sts)adm1176_read_voltage(adm1176_hdl_vdp, voltage))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API reads and returns the current
 */
hal_ret_sts ahw_vdp_hsc_adm1176_read_current(ahw_al_hsc_hdl *al_hsc, float *current)
{
    e_adm1176_err sts ;
    s_adm1176_drv_cb_ptr adm1176_hdl_vdp;
    adm1176_hdl_vdp = (s_adm1176_drv_cb_ptr) al_hsc->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS==(hal_ret_sts)adm1176_read_current(adm1176_hdl_vdp, current))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API is used to manually turn ON/OFF the hotswap operation.
 */
hal_ret_sts ahw_vdp_hsc_adm1176_hotswap_control(ahw_al_hsc_hdl *al_hsc, uint8_t on_off)
{
    e_adm1176_err sts ;
    s_adm1176_drv_cb_ptr adm1176_hdl_vdp;
    adm1176_hdl_vdp = (s_adm1176_drv_cb_ptr) al_hsc->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS==(hal_ret_sts)adm1176_hotswap_control(adm1176_hdl_vdp,on_off))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API reads and returns the hotswap status.
 */
hal_ret_sts ahw_vdp_hsc_adm1176_get_hotswap_sts(ahw_al_hsc_hdl *al_hsc, uint8_t *hotswap_sts)
{
    e_adm1176_err sts ;
    s_adm1176_drv_cb_ptr adm1176_hdl_vdp;
    adm1176_hdl_vdp = (s_adm1176_drv_cb_ptr) al_hsc->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS==(hal_ret_sts)adm1176_get_hotswap_sts(adm1176_hdl_vdp,hotswap_sts))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API reads and returns the adm1176 status.
 */
hal_ret_sts ahw_vdp_hsc_adm1176_get_sts(ahw_al_hsc_hdl *al_hsc, uint8_t *sts)
{
    e_adm1176_err err_sts;
    s_adm1176_drv_cb_ptr adm1176_hdl_vdp;
    adm1176_hdl_vdp = (s_adm1176_drv_cb_ptr) al_hsc->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS==(hal_ret_sts)adm1176_get_sts(adm1176_hdl_vdp, sts))
    {
        err_sts = HAL_SCS;
    }
    else
    {
        err_sts=HAL_AH_DRIVER_ERR;
    }
    return err_sts;
}

/*!
 *  @brief This API reads and returns the overcurrent status of ADM1176.
 */
hal_ret_sts ahw_vdp_hsc_adm1176_get_overcurrent_sts(ahw_al_hsc_hdl *al_hsc, uint8_t *under_vlt_sts)
{
    e_adm1176_err sts;
    s_adm1176_drv_cb_ptr adm1176_hdl_vdp;
    adm1176_hdl_vdp = (s_adm1176_drv_cb_ptr) al_hsc->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS==(hal_ret_sts)adm1176_get_overcurrent_sts(adm1176_hdl_vdp,under_vlt_sts))
    {
        sts =HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

#endif

/**
 * @file exo_ahw_vdp_ts_mcp9843.c
 *
 * @brief This file contains the vendor driver porting function of MCP9843 temperature sensor
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
#include "exo_ahw_vdp_ts_mcp9843.h"
#include "exo_ahw_al_linux_wrpr.h"
#include "exo_osal_mem_management.h"
#include"mcp9843.h"

/**
 * @brief Temperature sensor structure
 */
mcp9843_dev_t vdh_ts;

/**
 * @brief Ahw_io mapping with the Ahw_io_lookup_table
 */
extern ahw_io_map *ahw_io_lookup_tble[MAX_AH_INST_ID];

/**
 * @brief  Ahw Instance handle pointer.
 *
 */
extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

/**
 * @brief  This API is used for i2c read.
 *
 */
uint16_t mcp9843_i2c_read(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)slv_addr, &reg_addr, 1, 500))
    {
        if(HAL_SCS == io_hal_i2c_receive(hi2c, (uint16)slv_addr, data, len, 500))
        {
            rslt =MCP9843_SCS;
        }
        else
        {
            rslt =MCP9843_E_COM_FAIL;
        }
    }
    else
    {
        rslt =MCP9843_E_COM_FAIL;
    }
    return rslt;
}

/**
 * @brief  This API is used for i2c write.
 *
 */
uint16_t mcp9843_i2c_write(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    uint8_t tx_arr[3];
    tx_arr[0]= reg_addr;
    tx_arr[1]= data[0];
    if (len>1)
        tx_arr[2]= data[1];
    len++;

    if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)slv_addr, tx_arr, len, 500))
    {
        rslt =MCP9843_SCS;

    }
    else
    {
        rslt =MCP9843_E_COM_FAIL;
    }
    return rslt;
}

/**
 * @brief API to initialize the Temperature Sensor
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_init(ahw_al_temp_sensor_hdl *al_ts_h)
{
    hal_ret_sts sts = HAL_SCS;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO TEMPERATURE SENSOR - AH-Vendor driver porting layer initialize");
    printf("\n EXO TEMPERATURE SENSOR - AH-Vendor driver initialize");
    printf("\n EXO TEMPERATURE SENSOR - AH-Vendor driver initialization completed successfully ");
    usleep(100000);
    printf("\n EXO TEMPERATURE SENSOR  - AH-Vendor driver porting layer initialization completed successfully");

#else
    mcp9843_dev_t* vdh_ts=(mcp9843_dev_t*)os_malloc(sizeof(mcp9843_dev_t));
    vdh_ts->write = mcp9843_i2c_write;
    vdh_ts->read = mcp9843_i2c_read;
    vdh_ts->io_intf_hdle = intf_inst_hdle_ptr[ahw_io_lookup_tble[al_ts_h->ahw_gen_info.ahw_inst_id]->io_instance_id];
    vdh_ts->slave_address=ahw_io_lookup_tble[al_ts_h->ahw_gen_info.ahw_inst_id]->slv_addr;
    vdh_ts->low_temp_threshold=al_ts_h->low_temp_threshold;
    vdh_ts->high_temp_threshold=al_ts_h->high_temp_threshold;
    vdh_ts->critical_temp_threshold=al_ts_h->critical_temp_threshold;
    vdh_ts->event_mode=al_ts_h->event_mode;

    al_ts_h->ahw_gen_info.vdp_inst_hdle = (void*)vdh_ts;
    al_ts_h->ahw_gen_info.io_intf_hdle=vdh_ts->io_intf_hdle;
    al_ts_h->ahw_gen_info.slave_address=vdh_ts->slave_address;

    if(HAL_SCS == (hal_ret_sts)mcp9843_init(vdh_ts))
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

/**
 * @brief  API to de-Initialize the Temperature Sensor
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_deinit(ahw_al_temp_sensor_hdl *al_ts_h)
{
    hal_ret_sts sts=HAL_SCS;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO TEMPERATURE SENSOR - AH-Vendor driver porting layer de-initialize");
    printf("\n EXO TEMPERATURE SENSOR - AH-Vendor driver de-initialize");
    printf("\n EXO TEMPERATURE SENSOR - AH-Vendor driver de-initialization completed successfully ");
    usleep(100000);
    printf("\n EXO TEMPERATURE SENSOR - AH-Vendor driver porting layer de-initialization completed successfully");

#else

    if(HAL_SCS == (hal_ret_sts)mcp9843_deinit(&vdh_ts))
    {
        al_ts_h->ahw_gen_info.vdp_inst_hdle = (void*)&vdh_ts;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    os_free(al_ts_h->ahw_gen_info.vdp_inst_hdle);
#endif    
    return sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief API to get the event status of temperature Sensor
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_get_evnt_sts (ahw_al_temp_sensor_hdl *al_ts_h, uint8_t* evnt_sts)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_get_event_sts(vdh_ts,evnt_sts))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API to configure Temperature Sensor
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_config (ahw_al_temp_sensor_hdl *al_ts_h)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_config(vdh_ts))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API to set mode of operation for Temperature Sensor(continues mode or shutdown mode)
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_set_mode(ahw_al_temp_sensor_hdl *al_ts_h ,temp_sensor_mode_t mode)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_set_mode(vdh_ts,mode))
    {
        al_ts_h->mode_of_operation=vdh_ts->mode;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API to set event output mode
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_set_event_output_mode(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_event_output_mode_t event_mode)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_set_event_output_mode(vdh_ts,event_mode))
    {
        al_ts_h->event_mode=vdh_ts->event_mode;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API to set event_polarity
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_set_event_polarity(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_event_polarity_t polarity)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)mcp9843_set_event_polarity(vdh_ts,polarity))
    {
        al_ts_h->polarity=vdh_ts->polarity;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to set interrupt clear bit in shutdown mode
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_intrupt_clear(ahw_al_temp_sensor_hdl *al_ts_h, uint8_t interrupt_clear)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_interrupt_clear(vdh_ts,interrupt_clear))
    {
        al_ts_h->interrupt_clear=vdh_ts->interrupt_clear;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief  API to set lock_bit
 *
 */
hal_ret_sts	ahw_vdp_ts_mcp9843_set_win_lockbit(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_win_lock_t win_lock)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_set_win_lockbit(vdh_ts,win_lock))
    {
        al_ts_h->win_lock=vdh_ts->win_lock;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to set critical lock bit
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_set_crit_lockbit(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_crit_lock_t crit_lock)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_set_crit_lockbit(vdh_ts,crit_lock))
    {
        al_ts_h->crit_lock=vdh_ts->crit_lock;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to set temperature high threshold
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_set_temp_high_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float high_temp_threshold)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_set_temp_high_threshold(vdh_ts,high_temp_threshold))
    {
        al_ts_h->high_temp_threshold=vdh_ts->high_temp_threshold;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to set temperature low threshold
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_set_temp_low_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float low_temp_threshold)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_set_temp_low_threshold(vdh_ts,low_temp_threshold))
    {
        al_ts_h->low_temp_threshold=vdh_ts->low_temp_threshold;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to set temperature critical threshold
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_set_temp_critical_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float critical_temp_threshold)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_set_temp_critical_threshold(vdh_ts,critical_temp_threshold))
    {
        al_ts_h->critical_temp_threshold=vdh_ts->critical_temp_threshold;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to get the temperature
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_get_temperature(ahw_al_temp_sensor_hdl *al_ts_h,float *temperature)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_gettemperature(vdh_ts,temperature))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to set temperature sensor hysteresis
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_set_hysteresis(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_hyst_t hysteresis)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_set_hysteresis(vdh_ts,hysteresis))
    {
        al_ts_h->hysteresis=vdh_ts->hysteresis;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to get temperature sensor hysteresis
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_get_hysteresis(ahw_al_temp_sensor_hdl *al_ts_h, temp_sensor_hyst_t *hysteresis)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)mcp9843_get_hysteresis(vdh_ts,(mcp9843_hyst_t*)hysteresis))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to set the resolution of temperature sensor
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_set_resolution(ahw_al_temp_sensor_hdl *al_ts_h, temp_sensor_res_t resolution)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts) mcp9843_set_resolution(vdh_ts,resolution))
    {
        al_ts_h->resolution=vdh_ts->resolution;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to get the resolution of temperature sensor
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_get_resolution(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_res_t *res)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;

    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts) mcp9843_get_resolution(vdh_ts,(mcp9843_res_t*)res))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to get temperature in fahrenheit
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_get_fahrenheit(ahw_al_temp_sensor_hdl *al_ts_h,float* temp_value)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts) mcp9843_get_fahrenheit(vdh_ts,temp_value))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief API to get temperature in celsius
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_get_celsius(ahw_al_temp_sensor_hdl *al_ts_h,float* temperature)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)mcp9843_get_celsius(vdh_ts,temperature))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*
 * @brief  API to read Manufacture ID and return 16-bit hex value representing the temperature data from the MCP9843 register,
 * here it returns the hal_ret_sts for communicating vd layer.
 *
 */
hal_ret_sts ahw_vdp_ts_mcp9843_read_manufacture_id(ahw_al_temp_sensor_hdl *al_ts_h,int16_t* temperature)
{
    hal_ret_sts sts;
    mcp9843_dev_t *vdh_ts;
    vdh_ts = (mcp9843_dev_t*) al_ts_h->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp9843_read_manufacture_id(vdh_ts,temperature))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

#endif


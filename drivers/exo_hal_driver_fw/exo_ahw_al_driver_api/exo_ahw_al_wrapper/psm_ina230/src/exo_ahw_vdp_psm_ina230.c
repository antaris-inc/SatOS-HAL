/**
 * @file exo_ahw_vdp_psm_ina230.c
 *
 * @brief This file contains the vendor driver porting function of INA230 power sense monitor
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
#include "exo_ahw_vdp_psm_ina230.h"
#include "exo_ahw_al_linux_wrpr.h"
#include <stdlib.h>
#include "exo_osal_mem_management.h"
#include "psm_ina230.h"

/**
 * @brief power Monitor Device  structure
 */
psm_ina230_dev_t vdh_psm;

/**
 * @brief Ahw_io mapping with the Ahw_io_lookup_table
 */
extern ahw_io_map *ahw_io_lookup_tble[MAX_AH_INST_ID];

/**
 * @brief  Instance handle pointer.
 */
extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

/**
 * @brief power Monitor Device configuration structure
 */
ina230_convert_time_config_t vdh_tc_cfg;

/**
 * @brief power Monitor Alert pin configuration structure
 */
ina230_alertpinconfig_t vdh_alert_pin_cfg;

#ifndef LINUX_TEMP_PORT
/**
 * @brief This API is used for i2c read.
 */
uint8_t ina230_i2c_read(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)slv_addr, &reg_addr, 1, 500))
    {
        if(HAL_SCS == io_hal_i2c_receive(hi2c, (uint16)slv_addr, data, len, 500))
        {
            rslt = INA230_SCS;
        }
        else
        {
            rslt =INA230_E_COM_FAIL;
        }
    }
    else
    {
        rslt =INA230_E_COM_FAIL;
    }
    return rslt;
}

/**
 * @brief This API is used for i2c write.
 */
uint8_t ina230_i2c_write(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    uint8_t t_data[3];
    t_data[0]=reg_addr;
    t_data[1]=data[0];
    t_data[2]=data[1];
    if(data==NULL)
    {
        rslt = io_hal_i2c_transmit(hi2c, (uint16)slv_addr, &reg_addr, 1, 500);
        return rslt;
    }
    if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)slv_addr, t_data, 3, 500))
    {
        rslt=HAL_SCS;
    }
    else
    {
        rslt =INA230_E_COM_FAIL;
    }
    return rslt;
}
#endif

/**
 * @brief API to initialize the power sense monitor.
 *
 */
hal_ret_sts   ahw_vdp_psm_ina230_init(ahw_al_psm_hdle *hpsm,ahw_al_psm_tc_config_t *hpsm_tc_cfg)
{
    hal_ret_sts sts = HAL_MAX_ERR;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO PSM - AH-Vendor driver porting layer Initialize");
    printf("\n EXO PSM - AH-Vendor driver Initialize");
    printf("\n EXO PSM - AH-Vendor driver Initialization completed successfully ");
    usleep(100000);
    printf("\n EXO PSM - AH-Vendor driver porting layer initialization completed successfully");

#else
    psm_ina230_dev_t* vdh_psm=(psm_ina230_dev_t*)os_malloc(sizeof(psm_ina230_dev_t));
    vdh_psm->write = ina230_i2c_write;
    vdh_psm->read = ina230_i2c_read;
    vdh_psm->io_intf_hdle = intf_inst_hdle_ptr[ahw_io_lookup_tble[hpsm->ahw_gen_info.ahw_inst_id]->io_instance_id];
    vdh_psm->slave_address=ahw_io_lookup_tble[hpsm->ahw_gen_info.ahw_inst_id]->slv_addr;
    vdh_psm->current_threshold=hpsm->current_threshold;
    vdh_psm->vbus_threshold=hpsm->vbus_threshold;
    vdh_psm->power_threshold=hpsm->power_threshold;
    vdh_psm->alert_function=hpsm->alert_function;

    hpsm->ahw_gen_info.vdp_inst_hdle = (void*)vdh_psm;
    hpsm->ahw_gen_info.io_intf_hdle=vdh_psm->io_intf_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_init(vdh_psm,&vdh_tc_cfg))
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
 * @brief API to de-Initialize the power sense monitor.
 *
 */
hal_ret_sts    ahw_vdp_psm_ina230_deinit(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts = HAL_MAX_ERR;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO PSM - AH-Vendor driver porting layer de-Initialize");
    printf("\n EXO PSM - AH-Vendor driver de-Initialize");
    printf("\n EXO PSM - AH-Vendor driver de-Initialization completed successfully ");
    usleep(100000);
    printf("\n EXO PSM - AH-Vendor driver porting layer de-Initialization completed successfully");

#else
    vdh_psm.io_intf_hdle = intf_inst_hdle_ptr[ahw_io_lookup_tble[POWER_SENSE_MONITOR_PS]->io_instance_id];
    if(HAL_SCS == (hal_ret_sts)ina230_deinit(&vdh_psm))
    {
        hpsm->ahw_gen_info.vdp_inst_hdle = (void*)&vdh_psm;
        hpsm->ahw_gen_info.io_intf_hdle=vdh_psm.io_intf_hdle;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }

    os_free(hpsm->ahw_gen_info.vdp_inst_hdle);
#endif
    return sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief API to read the INA230 die identifier
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_read_id(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ina230_read_id(vdh_psm))
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
 * @brief API to generate a system reset
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_reset(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ina230_reset(vdh_psm))
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
 * @brief API to program the power sense monitor calibration
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_set_calibration(ahw_al_psm_hdle *hpsm, uint16_t calibration)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ina230_set_calibration(vdh_psm,calibration))
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
 * @brief API to read programmed calibration value
 *
 */
uint16 ahw_vdp_psm_ina230_get_calibration(ahw_al_psm_hdle *hpsm)
{
    uint16 sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    sts=ina230_get_calibration(vdh_psm);
    return sts;
}

/**
 *  @brief API to configure the Alert pin behavior
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_alert_pinconfig(ahw_al_psm_hdle *hpsm,ahw_al_psm_alert_pin_cfg_t *alert_pin_cfg)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    vdh_alert_pin_cfg.latch_enable=hpsm->psm_alert_cfg.LatchEnable;
    vdh_alert_pin_cfg.polarity=hpsm->psm_alert_cfg.Polarity;
    if(HAL_SCS ==(hal_ret_sts)ina230_alert_pinconfig(vdh_psm, &vdh_alert_pin_cfg))
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
 * @brief API to set the alert function
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_set_alertfunction(ahw_al_psm_hdle *hpsm,psm_alert_function_t alert_function)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    vdh_psm->alert_function = hpsm->alert_function;
    if(HAL_SCS ==(hal_ret_sts)ina230_set_alertfunction(vdh_psm,alert_function))
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
 * @brief API to get the programmed alert function
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_get_alertfunction(ahw_al_psm_hdle *hpsm,psm_alert_function_t alert_function)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts) ina230_get_alertfunction(vdh_psm,alert_function))
    {
        hpsm->alert_function = vdh_psm->alert_function;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief API to program the VBus threshold
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_setvbusthreshold(ahw_al_psm_hdle *hpsm, float vbusthreshold)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_setvbusthreshold(vdh_psm, vbusthreshold))
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
 * @brief API to get the VBUS threshold
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_getvbusthreshold(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == ina230_getvbusthreshold(vdh_psm))
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
 * @brief API to program the VShunt threshold
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_setvshuntthreshold(ahw_al_psm_hdle *hpsm, float vshuntthreshold)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_setvshuntthreshold(vdh_psm,vshuntthreshold))
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
 * @brief API to get the VShunt threshold
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_getshuntthreshold(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==ina230_getshuntthreshold(vdh_psm))
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
 * @brief API to program the Power threshold
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_get_current_threshold(ahw_al_psm_hdle *hpsm, float current_threshold)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_set_current_threshold(vdh_psm, current_threshold))
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
 * @brief API to program the Power threshold
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_setpowerthreshold(ahw_al_psm_hdle *hpsm, uint32_t powerthreshold)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_setpowerthreshold(vdh_psm, powerthreshold))
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
 * @brief API to get the Power threshold
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_getpowerthreshold(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_getpowerthreshold(vdh_psm))
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
 * @brief API to enable the Voltage/Power threshold interrupt
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_alert_threshold_enable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_alert_threshold_enable_it(vdh_psm))
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
 * @brief API to disable the Voltage/Power threshold interrupt
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_alert_threshold_disable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_alert_threshold_disable_it(vdh_psm))
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
 * @brief API to enable the Conversion ready interrupt
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_conversion_ready_enable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_conversion_ready_enable_it(vdh_psm))
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
 * @brief API to disable the Conversion ready interrupt
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_conversion_ready_disable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_conversion_ready_disable_it(vdh_psm))
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
 * @brief API to start the conversion on the selected voltage input
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_startconversion(ahw_al_psm_hdle *hpsm, psm_input_signal_t inputsignal, psm_operating_mode_t mode)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;

    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    vdh_psm->inputsignal=hpsm->inputsignal;
    vdh_psm->mode =hpsm->mode;
    if(HAL_SCS ==(hal_ret_sts)ina230_startconversion(vdh_psm,inputsignal,mode))
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
 * @brief API to stop the conversion on the selected voltage input
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_stopconversion(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==(hal_ret_sts)ina230_stopconversion(vdh_psm))
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
 * @brief API to read the bus voltage
 *
 */
float ahw_vdp_psm_ina230_get_vbus(ahw_al_psm_hdle *hpsm)
{
    float res;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    res = ina230_get_vbus(vdh_psm);
    return res;
}

/**
 * @brief API to read the shunt voltage
 *
 */
float ahw_vdp_psm_ina230_get_vshunt(ahw_al_psm_hdle *hpsm)
{
    float sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    sts = ina230_get_vshunt(vdh_psm);
    return sts;
}

/**
 * @brief API to read the power value
 *
 */
uint32_t ahw_vdp_psm_ina230_get_power(ahw_al_psm_hdle *hpsm)
{
    uint32_t sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    sts = ina230_get_power(vdh_psm);
    return sts;
}

/**
 * @brief API to read the current value
 *
 */
float ahw_vdp_psm_ina230_get_current(ahw_al_psm_hdle *hpsm)
{
    float sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    sts= ina230_get_current(vdh_psm);
    return sts;
}

/**
 * @brief API to read the designed flag value
 *
 */
hal_ret_sts ahw_vdp_psm_ina230_get_flag(ahw_al_psm_hdle *hpsm, psm_flag_t flag)
{
    hal_ret_sts sts;
    psm_ina230_dev_t *vdh_psm;
    vdh_psm = (psm_ina230_dev_t*) hpsm->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS ==ina230_get_flag(vdh_psm,flag))
    {
        hpsm->flag = vdh_psm->flag ;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

#endif

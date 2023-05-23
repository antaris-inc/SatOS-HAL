/**
 * @file exo_dt_wrapper.c
 *
 * @brief This file has mapping functions which resolves the
 * instance Id and invokes the vendor driver API for digital thermostat on the partnumber
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
 *
 */

#include "exo_ahw_vdp_dt_ds620.h"
#include "exo_ahw_al_dt_wrapper.h"

/*!
 *  @brief Mapping API to initializes the control block memory and do the basic configurations
 */
hal_ret_sts ahw_al_dt_common_init(ahw_al_dt_hdle *al_dt)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_init(al_dt);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

#ifndef LINUX_TEMP_PORT
/*!
 *  @brief Mapping API to deinitializes the control block memory
 */
hal_ret_sts ahw_al_dt_common_deinit(ahw_al_dt_hdle *al_dt)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_deinit(al_dt);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the high temperature threshold for digital thermostat
 */
hal_ret_sts ahw_al_dt_common_set_temperature_high_threshold (ahw_al_dt_hdle *al_dt, double high_temp_threshold)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_set_temperature_high_threshold(al_dt,high_temp_threshold);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the low temperature threshold for digital thermostat
 */
hal_ret_sts ahw_al_dt_common_set_temperature_low_threshold (ahw_al_dt_hdle *al_dt, double low_temp_threshold)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_set_temperature_low_threshold(al_dt,low_temp_threshold);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to get the temperature from digital thermostat
 */
hal_ret_sts ahw_al_dt_common_get_temperature (ahw_al_dt_hdle *al_dt, double* temperature)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_get_temperature(al_dt,temperature);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to configure the digital thermostat and temperature sensor
 */
hal_ret_sts ahw_al_dt_common_sensor_config (ahw_al_dt_hdle *al_dt)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_config(al_dt);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the ADC resolution digital thermostat
 */
hal_ret_sts ahw_al_dt_common_set_resolution (ahw_al_dt_hdle *al_dt, digital_thermos_resolution res)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_set_resolution(al_dt, res);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to get the ADC resolution of digital thermostat
 */
hal_ret_sts ahw_al_dt_common_get_resolution(ahw_al_dt_hdle *al_dt , digital_thermos_resolution *res)
{
    hal_ret_sts sts;

    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_get_resolution(al_dt,res);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the operating mode of the digital thermostat
 */
hal_ret_sts ahw_al_dt_common_set_conv_mode (ahw_al_dt_hdle *al_dt, uint8_t mode)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_set_conv_mode(al_dt, mode);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the PO pin logic level alert status of digital thermostat
 */
hal_ret_sts ahw_al_dt_common_set_po_lvl_alert_sts (ahw_al_dt_hdle *al_dt, uint8_t* lvl)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_get_po_lvl_alert_sts(al_dt, lvl);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to set the PO pin logic level of digital thermostat
 */
hal_ret_sts ahw_al_dt_common_set_po_lvl (ahw_al_dt_hdle *al_dt, uint8_t lvl)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_set_po_lvl(al_dt, lvl);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to reset the digital thermostat and temperature sensor
 */
hal_ret_sts ahw_al_dt_common_reset(ahw_al_dt_hdle *al_dt)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_reset(al_dt);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to start the temperature conversion
 */
hal_ret_sts ahw_al_dt_common_start_conversion(ahw_al_dt_hdle *al_dt)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_start_conversion(al_dt);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to stop the temperature conversion
 */
hal_ret_sts ahw_al_dt_common_stop_conversion(ahw_al_dt_hdle *al_dt)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_stop_conversion(al_dt);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to get the PO pin logic level of digital thermostat and temperature sensor
 */
hal_ret_sts ahw_al_dt_common_get_po_lvl(ahw_al_dt_hdle *al_dt,uint8_t *lvl)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_get_po_lvl(al_dt,lvl);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to get the operating mode of digital thermostat and temperature sensor
 */
hal_ret_sts ahw_al_dt_common_get_mode(ahw_al_dt_hdle *al_dt,uint8_t *mode)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_get_mode(al_dt,mode);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to get the low temperature threshold
 */
hal_ret_sts ahw_al_dt_common_get_temperature_low_thrshd(ahw_al_dt_hdle *al_dt,double *low_temp_thrshld)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_get_temperature_low_thrshd(al_dt,low_temp_thrshld);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to get the high temperature threshold
 */
hal_ret_sts ahw_al_dt_common_get_temperature_high_thrshd(ahw_al_dt_hdle *al_dt,double *high_temp_thrshld)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_get_temperature_high_thrshd(al_dt,high_temp_thrshld);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*!
 *  @brief Mapping API to reset the alert flag of digital thermostat and temperature sensor
 */
hal_ret_sts ahw_al_dt_common_reset_alert_flag(ahw_al_dt_hdle *al_dt)
{
    hal_ret_sts sts;
    switch(al_dt->ahw_gen_info.ahw_inst_id)
    {
        case DT_DS620_EDGE:
        case DT_DS620_PS:
            sts = ahw_vdp_dt_ds620_reset_alert_flag(al_dt);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

#endif

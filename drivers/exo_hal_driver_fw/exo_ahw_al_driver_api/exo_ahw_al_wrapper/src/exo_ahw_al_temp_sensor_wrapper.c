/**
 * @file exo_ahw_al_temp_sensor_wrapper.c
 *
 * @brief This file has mapping functions which resolves the
 * instance Id and invokes the vendor driver API for temperature sensor based on the partnumber
 *
 * @copyright Copyright 2024 Antaris, Inc.
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

#include "exo_ahw_vdp_ts_mcp9843.h"
#include "exo_ahw_al_temp_sensor_wrapper.h"

/**
 * @brief Mapping API to initializes the control block memory and do the basic configurations
 *
 */
hal_ret_sts	ahw_al_ts_common_init(ahw_al_temp_sensor_hdl *al_ts_h)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_init(al_ts_h);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API de-Initialize the Temperature Sensor
 *
 */
hal_ret_sts ahw_al_ts_common_deinit(ahw_al_temp_sensor_hdl *al_ts_h)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_deinit(al_ts_h);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief Mapping API configure Temperature Sensor
 *
 */
hal_ret_sts ahw_al_ts_common_config (ahw_al_temp_sensor_hdl *al_ts_h)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_config (al_ts_h);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API get the event status
 */
hal_ret_sts ahw_al_ts_common_get_evnt_sts (ahw_al_temp_sensor_hdl *al_ts_h, uint8_t* evnt_sts)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_get_evnt_sts (al_ts_h,evnt_sts);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API set mode of operation for Temperature Sensor(continues mode or shutdown mode)
 *
 */
hal_ret_sts ahw_al_ts_common_set_mode(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_mode_t mode)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_set_mode(al_ts_h,mode);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API set intrupt_clear bit in shutdown mode
 *
 */
hal_ret_sts	ahw_al_ts_common_intrupt_clear(ahw_al_temp_sensor_hdl *al_ts_h, uint8_t interrupt_clear)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_intrupt_clear(al_ts_h,interrupt_clear);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API set event output mode
 *
 */
hal_ret_sts ahw_al_ts_common_set_event_output_mode(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_event_output_mode_t event_mode)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_set_event_output_mode(al_ts_h,event_mode);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API set event_polarity
 *
 */
hal_ret_sts ahw_al_ts_common_set_event_polarity(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_event_polarity_t polarity)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_set_event_polarity(al_ts_h,polarity);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API set win lock bit
 *
 */
hal_ret_sts ahw_al_ts_common_set_win_lockbit(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_win_lock_t win_lock)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_set_win_lockbit(al_ts_h,win_lock);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API set critical lock bit
 *
 */
hal_ret_sts ahw_al_ts_common_set_crit_lockbit(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_crit_lock_t crit_lock)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts =  ahw_vdp_ts_mcp9843_set_crit_lockbit(al_ts_h,crit_lock);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API set temperature high threshold
 *
 */
hal_ret_sts ahw_al_ts_common_set_temp_high_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float high_temp_threshold)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_set_temp_high_threshold(al_ts_h,high_temp_threshold);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API set temperature low threshold
 *
 */
hal_ret_sts ahw_al_ts_common_set_temp_low_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float low_temp_threshold)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_GPS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
            sts = ahw_vdp_ts_mcp9843_set_temp_low_threshold(al_ts_h,low_temp_threshold);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API set temperature critical threshold
 *
 */
hal_ret_sts ahw_al_ts_common_set_temp_critical_threshold (ahw_al_temp_sensor_hdl *al_ts_h, float critical_temp_threshold)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_set_temp_critical_threshold(al_ts_h,critical_temp_threshold);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API set the hysteresis of Temperature sensor
 *
 */
hal_ret_sts ahw_al_ts_common_set_hysteresis(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_hyst_t hysteresis)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_GPS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
            sts = ahw_vdp_ts_mcp9843_set_hysteresis(al_ts_h,hysteresis);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API get the Temperature sensor hysteresis
 *
 */
hal_ret_sts ahw_al_ts_common_get_hysteresis(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_hyst_t *hysteresis)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_GPS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
            sts =ahw_vdp_ts_mcp9843_get_hysteresis(al_ts_h,hysteresis);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API set the Temperature sensor resolution
 *
 */
hal_ret_sts ahw_al_ts_common_set_resolution(ahw_al_temp_sensor_hdl *al_ts_h, temp_sensor_res_t resolution)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_GPS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
            sts =ahw_vdp_ts_mcp9843_set_resolution(al_ts_h,resolution);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API read Temperature sensor resolution
 *
 */
hal_ret_sts ahw_al_ts_common_get_resolution(ahw_al_temp_sensor_hdl *al_ts_h,temp_sensor_res_t *res)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_GPS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
            sts = ahw_vdp_ts_mcp9843_get_resolution(al_ts_h,res);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API reads the current temperature
 *
 */
hal_ret_sts ahw_al_ts_common_gettemperature(ahw_al_temp_sensor_hdl *al_ts_h,float *temperature)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_GPS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
            sts = ahw_vdp_ts_mcp9843_get_temperature(al_ts_h,temperature);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API get temperature in fahrenheit
 *
 */
hal_ret_sts ahw_al_ts_common_get_fahrenheit(ahw_al_temp_sensor_hdl *al_ts_h,float* temperature)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_GPS:
        case TEMP_SENSOR_MCP9843_EDGE:
            sts = ahw_vdp_ts_mcp9843_get_fahrenheit(al_ts_h,temperature);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief Mapping API get temperature in celsius
 *
 */
hal_ret_sts ahw_al_ts_common_get_celsius(ahw_al_temp_sensor_hdl *al_ts_h,float* temperature)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_get_celsius(al_ts_h,temperature);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/*
 * @brief  Mapping API read manufacture ID and return 16-bit hex value representing the temperature data from the MCP9843 register,
 * here it returns the hal_ret_sts for communicating vdp layer.
 *
 */
hal_ret_sts ahw_al_ts_common_read_manufacture_id(ahw_al_temp_sensor_hdl *al_ts_h,int16_t* temperature)
{
    hal_ret_sts sts;
    switch(al_ts_h->ahw_gen_info.ahw_inst_id)
    {
        case TEMP_SENSOR_MCP9843_PS:
        case TEMP_SENSOR_MCP9843_OBC:
        case TEMP_SENSOR_MCP9843_EDGE:
        case TEMP_SENSOR_MCP9843_GPS:
            sts = ahw_vdp_ts_mcp9843_read_manufacture_id(al_ts_h,temperature);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}
#endif

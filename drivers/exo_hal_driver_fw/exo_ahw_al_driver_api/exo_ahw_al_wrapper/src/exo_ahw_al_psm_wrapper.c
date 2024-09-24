/**
 * @file exo_ahw_al_psm_wrapper.c
 *
 * @brief This file has mapping functions which resolves the
 * instance Id and invokes the vendor driver API for power sense monitor based on the partnumber
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

#include "exo_ahw_vdp_psm_ina230.h"
#include "exo_ahw_al_psm_wrapper.h"

/**
 * @brief Mapping API to initializes the control block memory and do the basic configurations
 *
 */
hal_ret_sts	ahw_al_psm_common_init(ahw_al_psm_hdle *hpsm,ahw_al_psm_tc_config_t *hpsm_tc_cfg)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case PSM_INA230_PS:
        case PSM_INA230_OBC :
            sts = ahw_vdp_psm_ina230_init(hpsm,hpsm_tc_cfg);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API de-Initialize the power sense monitor.
 *
 */
hal_ret_sts  ahw_al_psm_common_deinit(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_deinit(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief Mapping API  read the power sense monitor die identifier
 *
 */
hal_ret_sts	 ahw_al_psm_common_read_id(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_read_id(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API generates a system reset.
 *
 */
hal_ret_sts ahw_al_psm_common_reset(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_reset(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API program the Power Sense Monitor calibration register
 *
 */
hal_ret_sts ahw_al_psm_common_set_calibration(ahw_al_psm_hdle *hpsm, uint16_t calibration)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_set_calibration(hpsm,calibration);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API read programmed calibration value
 *
 */
uint16_t ahw_al_psm_common_get_calibration(ahw_al_psm_hdle *hpsm)
{
    uint16_t sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts =  ahw_vdp_psm_ina230_get_calibration(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 *  @brief Mapping API configure the alert pin behavior
 *
 */
hal_ret_sts ahw_al_psm_common_alert_pinconfig(ahw_al_psm_hdle *hpsm,ahw_al_psm_alert_pin_cfg_t *alert_pin_cfg)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_alert_pinconfig(hpsm,alert_pin_cfg);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API set the alert function
 *
 */
hal_ret_sts ahw_al_psm_common_set_alertfunction(ahw_al_psm_hdle *hpsm,psm_alert_function_t alert_function)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_set_alertfunction(hpsm,alert_function);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API get the programmed alert function
 *
 */
hal_ret_sts ahw_al_psm_common_get_alertfunction(ahw_al_psm_hdle *hpsm,psm_alert_function_t alert_function)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_get_alertfunction(hpsm,alert_function);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API program the VBus threshold
 *
 */
hal_ret_sts ahw_al_psm_common_setvbusthreshold(ahw_al_psm_hdle *hpsm, float vbusthreshold)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_setvbusthreshold(hpsm,vbusthreshold);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API get the VBUS threshold
 *
 */
hal_ret_sts ahw_al_psm_common_getvbusthreshold(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_getvbusthreshold(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API program the VShunt threshold
 *
 */
hal_ret_sts ahw_al_psm_common_setvshuntthreshold(ahw_al_psm_hdle *hpsm, float vshuntthreshold)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_setvshuntthreshold(hpsm,vshuntthreshold);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API get the VShunt threshold
 *
 */
hal_ret_sts	ahw_al_psm_common_getshuntthreshold(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_getshuntthreshold(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API program the current threshold
 *
 */
hal_ret_sts ahw_al_psm_common_set_current_threshold(ahw_al_psm_hdle *hpsm, float current_threshold)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts =ahw_vdp_psm_ina230_get_current_threshold(hpsm,current_threshold);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API program the Power threshold
 *
 */
hal_ret_sts ahw_al_psm_common_setpowerthreshold(ahw_al_psm_hdle *hpsm, uint32_t powerthreshold)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts =ahw_vdp_psm_ina230_setpowerthreshold(hpsm,powerthreshold);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API get the Power threshold
 *
 */
hal_ret_sts ahw_al_psm_common_getpowerthreshold(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_getpowerthreshold(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief  Mapping API enable the Voltage/Power threshold interrupt
 *
 */
hal_ret_sts ahw_al_psm_common_alert_threshold_enable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_alert_threshold_enable_it(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API disable the Voltage/Power threshold interrupt
 *
 */
hal_ret_sts ahw_al_psm_common_alert_threshold_disable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts =  ahw_vdp_psm_ina230_alert_threshold_disable_it(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API enable the conversion ready interrupt
 *
 */
hal_ret_sts ahw_al_psm_common_conversion_ready_enable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_conversion_ready_enable_it(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }

    return sts;
}

/**
 * @brief Mapping API disable the conversion ready interrupt
 *
 */
hal_ret_sts ahw_al_psm_common_conversion_ready_disable_it(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts =ahw_vdp_psm_ina230_conversion_ready_disable_it(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API start the conversion on the selected voltage input
 *
 */
hal_ret_sts ahw_al_psm_common_startconversion(ahw_al_psm_hdle *hpsm, psm_input_signal_t inputsignal, psm_operating_mode_t mode)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts =  ahw_vdp_psm_ina230_startconversion(hpsm,inputsignal,mode);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API stop the conversion on the selected voltage input
 *
 */
hal_ret_sts ahw_al_psm_common_stopconversion(ahw_al_psm_hdle *hpsm)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_stopconversion(hpsm);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
            break;
    }
    return sts;
}

/**
 * @brief Mapping API read the vbus voltage
 *
 */
float ahw_al_psm_common_get_vbus(ahw_al_psm_hdle *hpsm)
{
    float ret=0;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            ret = ahw_vdp_psm_ina230_get_vbus(hpsm);
            break;
        default:
            break;
    }
    return ret;
}

/**
 * @brief Mapping API read the vshunt voltage
 *
 */
float  ahw_al_psm_common_get_vshunt(ahw_al_psm_hdle *hpsm)
{
    float sts=0;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_get_vshunt(hpsm);
            break;
        default:
            break;
    }
    return sts;
}

/**
 * @brief Mapping API read the power value
 *
 */
uint32_t ahw_al_psm_common_get_power(ahw_al_psm_hdle *hpsm)
{
    uint32_t sts=0;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts =ahw_vdp_psm_ina230_get_power(hpsm);
            break;
        default:
            break;
    }
    return sts;
}

/**
 * @brief Mapping API read the current value
 *
 */
float ahw_al_psm_common_get_current(ahw_al_psm_hdle *hpsm)
{
    float sts=0;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts = ahw_vdp_psm_ina230_get_current(hpsm);
            break;
        default:
            break;
    }
    return sts;
}

/**
 * @brief Mapping API read the designed flag value
 *
 */
hal_ret_sts ahw_al_psm_common_get_flag(ahw_al_psm_hdle *hpsm, psm_flag_t flag)
{
    hal_ret_sts sts;
    switch(hpsm->ahw_gen_info.ahw_inst_id)
    {
        case  PSM_INA230_PS:
        case PSM_INA230_OBC:
            sts =ahw_vdp_psm_ina230_get_flag(hpsm,flag);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
            break;
    }
    return sts;
}

#endif

/**
 * @file exo_ahw_al_hsc_wrapper.c
 *
 * @brief This file has mapping functions which resolves the
 * instance Id and invokes the vendor driver API for hotswap controller based on the partnumber
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
 */

#include "exo_ahw_vdp_hsc_adm1176.h"
#include "exo_ahw_al_hsc_wrapper.h"

/*!
 *  @brief Mapping API to initializes the control block memory and do the basic configurations
 */
hal_ret_sts ahw_al_hsc_common_init(ahw_al_hsc_hdl *ahw_al_hsc)
{
    hal_ret_sts sts;
    switch(ahw_al_hsc->ahw_gen_info.ahw_inst_id)
    {
        case HSC_ADM1176_EDGE:
        case HSC_ADM1176_PS_1:
        case HSC_ADM1176_PS_2:
            sts = ahw_vdp_hsc_adm1176_init(ahw_al_hsc);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
            break;
    }
    return sts;
}

#ifndef LINUX_TEMP_PORT
/*!
 *  @brief Mapping API to deinitializes the control block memory
 *
 */
hal_ret_sts ahw_al_hsc_common_deinit(ahw_al_hsc_hdl *ahw_al_hsc)
{
    hal_ret_sts sts;
    switch(ahw_al_hsc->ahw_gen_info.ahw_inst_id)
    {
        case HSC_ADM1176_EDGE:
        case HSC_ADM1176_PS_1:
        case HSC_ADM1176_PS_2:
            sts = ahw_vdp_hsc_adm1176_deinit(ahw_al_hsc);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
            break;
    }
    return sts;
}

/*!
 *  @brief Mapping API to read and return the voltage
 *
 */
hal_ret_sts ahw_al_hsc_common_read_voltage(ahw_al_hsc_hdl *hsc, float *voltage)
{
    hal_ret_sts sts;
    switch(hsc->ahw_gen_info.ahw_inst_id)
    {
        case HSC_ADM1176_EDGE:
        case HSC_ADM1176_PS_1:
        case HSC_ADM1176_PS_2:
            sts = ahw_vdp_hsc_adm1176_read_voltage(hsc,voltage);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
            break;
    }
    return sts;
}

/*!
 *  @brief Mapping API to read and return the current
 *
 */
hal_ret_sts ahw_al_hsc_common_read_current(ahw_al_hsc_hdl *hsc, float *current)
{
    hal_ret_sts sts;
    switch(hsc->ahw_gen_info.ahw_inst_id)
    {
        case HSC_ADM1176_EDGE:
        case HSC_ADM1176_PS_1:
        case HSC_ADM1176_PS_2:
            sts = ahw_vdp_hsc_adm1176_read_current(hsc, current);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
            break;
    }
    return sts;
}

/*!
 *  @brief Mapping API to manually turn ON/OFF the hotswap operation.
 *
 */
hal_ret_sts ahw_al_hsc_common_hotswap_control(ahw_al_hsc_hdl *hsc, uint8_t on_off)
{
    hal_ret_sts sts;
    switch(hsc->ahw_gen_info.ahw_inst_id)
    {
        case HSC_ADM1176_EDGE:
        case HSC_ADM1176_PS_2:
        case HSC_ADM1176_PS_1:
            sts = ahw_vdp_hsc_adm1176_hotswap_control(hsc, on_off);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
            break;
    }
    return sts;
}

/*!
 *  @brief Mapping API to read and return the hotswap status.
 *
 */
hal_ret_sts ahw_al_hsc_common_get_hotswap_sts(ahw_al_hsc_hdl *hsc, uint8_t *hotswap_sts)
{
    hal_ret_sts sts;
    switch(hsc->ahw_gen_info.ahw_inst_id)
    {
        case HSC_ADM1176_EDGE:
        case HSC_ADM1176_PS_2:
        case HSC_ADM1176_PS_1:
            sts = ahw_vdp_hsc_adm1176_get_hotswap_sts(hsc, hotswap_sts);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
            break;
    }
    return sts;
}

/*!
 *  @brief Mapping API to read and return the under voltage status.
 *
 */
hal_ret_sts ahw_al_hsc_common_get_overcurrent_sts(ahw_al_hsc_hdl *hsc, uint8_t *under_vlt_sts)
{
    hal_ret_sts sts;
    switch(hsc->ahw_gen_info.ahw_inst_id)
    {
        case HSC_ADM1176_EDGE:
        case HSC_ADM1176_PS_2:
        case HSC_ADM1176_PS_1:
            sts = ahw_vdp_hsc_adm1176_get_overcurrent_sts(hsc,under_vlt_sts);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
            break;
    }
    return sts;
}

#endif

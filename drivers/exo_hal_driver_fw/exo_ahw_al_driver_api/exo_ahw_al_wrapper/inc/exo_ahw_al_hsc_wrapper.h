/**
 * @file exo_ahw_al_hsc_wrapper.h
 *
 * @brief This file has mapping functions for hotswap controller
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


#ifndef _AHW_AL_HSC_WRP_H_
#define _AHW_AL_HSC_WRP_H_

#define HSC_ADM1176_A

#ifdef HSC_ADM1176_A
#include "exo_ahw_vdp_hsc_adm1176.h"
#endif

/**
 * @brief Mapping API initializes the control block memory and do the basic
 * configurations for hot swap controller
 * @param[in]  ahw_al_hsc - instance pointer of hotswap controller
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_common_init(ahw_al_hsc_hdl *ahw_al_hsc);

/**
 * @brief Mapping API deinitializes the ADM1176 control block memory.
 * @param[in]  ahw_al_hsc - instance pointer of hotswap controller
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_common_deinit(ahw_al_hsc_hdl *ahw_al_hsc);

/**
 * @brief Mapping API reads and returns the voltage.
 * @param[in]  hsc - instance pointer of hotswap controller.
 * @param[out] voltage – voltage is updated in this variable.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_common_read_voltage(ahw_al_hsc_hdl *hsc, float *voltage);

/**
 * @brief Mapping API reads and returns the current.
 * @param[in]  hsc -  instance pointer of hotswap controller.
 * @param[out] current – current is updated in this variable.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_common_read_current(ahw_al_hsc_hdl *hsc, float *current);

/**
 * @brief Mapping API is used to manually turn ON/OFF of the hotswap operation.
 * @param[in]  hsc -  instance pointer of hotswap controller.
 * @param[in] on_off –  turn on/off control command.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_common_hotswap_control(ahw_al_hsc_hdl *hsc, uint8_t on_off);

/**
 * @brief Mapping API reads and returns the hotswap status.
 * @param[in] hsc - instance pointer of hotswap controller
 * @param[out] hotswap_sts – hotswap status is updated in this variable
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_common_get_hotswap_sts(ahw_al_hsc_hdl *hsc, uint8_t *hotswap_sts);

/**
 * @brief Mapping API reads and returns the over current status .
 * @param[in]  hsc -  instance pointer of hotswap controller
 * @param[out] under_vlt_sts – under voltage status is updated
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_common_get_overcurrent_sts(ahw_al_hsc_hdl *hsc, uint8_t *under_vlt_sts);



#endif /* _AHW_AL_WRAPPER_H_ */


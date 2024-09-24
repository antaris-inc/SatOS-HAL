/**
 * @file exo_ahw_vdp_hsc_adm1176.h
 *
 * @brief This file contains vendor driver porting function prototype of hot swap controller
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

#ifndef _AHW_AL_ADM1176_H_
#define _AHW_AL_ADM1176_H_

#include <stdlib.h>
#include "exo_hal_common.h"
#include "exo_ahw_al_hsc_common.h"
#include "exo_io_al_i2c_common.h"

/**
 * @brief This API initializes the control block memory and do the basic configurations for ADM1176 instance
 * @param[in]  ahw_al_hsc - AHAL instance pointer of hotswap controller
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_hsc_adm1176_init(ahw_al_hsc_hdl *ahw_al_hsc);

/**
 * @brief This API deinitializes the ADM1176 control block memory.
 * @param[in]  ahw_al_hsc - AHAL instance pointer of hotswap controller
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_hsc_adm1176_deinit(ahw_al_hsc_hdl *ahw_al_hsc);

/**
 * @brief This API reads and returns the voltage.
 * @param[in]  al_hsc - AHAL instance pointer of hotswap controller.
 * @param[out] voltage – voltage is updated in this variable.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_hsc_adm1176_read_voltage(ahw_al_hsc_hdl *al_hsc, float *voltage );

/**
 * @brief This API reads and returns the current.
 * @param[in]  al_hsc - AHAL instance pointer of hotswap controller.
 * @param[out] current – current is updated in this variable.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_hsc_adm1176_read_current(ahw_al_hsc_hdl *al_hsc, float *current);

/**
 * @brief This API is used to manually turn ON/OFF of the hotswap operation.
 * @param[in]  al_hsc - AHAL instance pointer of hotswap controller.
 * @param[in] on_off –  turn on/off control command.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_hsc_adm1176_hotswap_control(ahw_al_hsc_hdl *al_hsc,uint8_t on_off);

/**
 * @brief This API reads and returns the hotswap status.
 * @param[in]  al_hsc - AHAL instance pointer of hotswap controller
 * @param[out] hotswap_sts – hotswap status is updated in this variable
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_hsc_adm1176_get_hotswap_sts(ahw_al_hsc_hdl *al_hsc, uint8_t *hotswap_sts);

/**
 * @brief This API reads and returns the adm1176 status.
 * @param[in]  al_hsc - AHAL instance pointer of hotswap controller.
 * @param[out] sts –  status byte of ADM1176 updated in this variable.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_hsc_adm1176_get_sts(ahw_al_hsc_hdl *al_hsc, uint8_t *sts);

/**
 * @brief This API reads and returns the under voltage status of ADM1176.
 * @param[in]  al_hsc - AHAL instance pointer of hotswap controller
 * @param[out] under_vlt_sts – under voltage status is updated
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_hsc_adm1176_get_overcurrent_sts(ahw_al_hsc_hdl *al_hsc, uint8_t *under_vlt_sts);


#endif

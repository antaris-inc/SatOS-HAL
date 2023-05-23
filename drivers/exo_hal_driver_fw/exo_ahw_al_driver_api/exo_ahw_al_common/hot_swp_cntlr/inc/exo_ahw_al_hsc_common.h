/**
 * @file exo_ahw_al_hsc_common.h
 *
 * @brief This file contains function prototypes ,structures and
 * enumerations for hotswap controller and voltage ,current monitor
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

#ifndef _AHW_AL_HSC_COMMON_H_
#define _AHW_AL_HSC_COMMON_H_

#include <stdlib.h>
#include <stdint.h>
#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_ahw_al_common.h"

/**
 * @brief Hot swap controller configuration structure definition
 */
typedef struct _ahw_al_hsc_hdle
{
    ahw_al_gen_info ahw_gen_info;      /*!< IO interface handle pointer   	*/
    uint8_t over_curr_sts:1;           /*!< over current status   			*/
    uint8_t hot_swp_sts:1;             /*!< Hot swap status  				*/
}ahw_al_hsc_hdl;

/**
 * @brief This API initializes the control block memory and
 * do the basic configurations for ADM1176 instance
 * @param[in]  hsc_arg - AHAL instance pointer of hotswap controller
 * @param[in]  ahw_id - application hardware instance ID
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_init(ahw_al_hsc_hdl* hsc_arg, ahw_inst_id_t ahw_id);

/**
 * @brief This API deinitializes the control block memory
 * @param[in]  hsc_arg - AHAL instance pointer of hotswap controller
 * @param[in]  ahw_id - application hardware instance ID
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_deinit(ahw_al_hsc_hdl* hsc_arg, ahw_inst_id_t ahw_id);

/**
 * @brief This API reads and returns the voltage.
 * @param[in]  hsc - AHAL instance pointer of hotswap controller
 * @param[out] voltage – voltage in volt
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_read_voltage(ahw_al_hsc_hdl *hsc, float *voltage);

/**
 * @brief This API reads and returns the current.
 * @param[in]  hsc - AHAL instance pointer of hotswap controller.
 * @param[out] current – current in mA
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_read_current(ahw_al_hsc_hdl *hsc, float *current);

/**
 * @brief This API is used to manually turn ON/OFF the hotswap operation.
 * @param[in]  hsc - AHAL instance pointer of hotswap controller.
 * @param[out] hotswap_sts – hot swap status .
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_get_hotswap_sts(ahw_al_hsc_hdl *hsc, uint8_t *hotswap_sts);

/**
 * @brief This API reads and returns the overcurrent status of ADM1176.
 * @param[in]  hsc - AHAL instance pointer of hotswap controller.
 * @param[out] on_off –  turn on/off control command.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_hotswap_control(ahw_al_hsc_hdl *hsc, uint8_t on_off);

/**
 * @brief This API reads and returns the overcurrent status of ADM1176.
 * @param[in]  hsc - AHAL instance pointer of hotswap controller.
 * @param[out] under_vlt_sts – overcurrent status
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_hsc_get_overcurrent_sts(ahw_al_hsc_hdl *hsc, uint8_t *under_vlt_sts);


#endif

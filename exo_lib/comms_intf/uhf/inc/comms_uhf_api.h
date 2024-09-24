/**
 * @file comms_uhf_api.h
 *
 * @brief This file contains APIs for UHF parameters configuration
 *        programming and readback
 *
 * @copyright Copyright 2024 Antaris, Inc.
 *
 * Licensed under the Apache License, Version 2.0(the "License");
 *you may not use this file except in compliance with the License.
 *you may obtain a copy of the License at
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

#ifndef COMMS_UHF_API_H_
#define COMMS_UHF_API_H_

#include<comms_uhf_rf_cfg.h>
#include<comms_uhf_main.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set UHF call sign data.
 *
 * @param[in] call_sign - pointer with received call sign data
 *
 * @return status.
 */
int32_t sdr_uhf_set_call_sign_req(s_radio_callsign_t *call_sign);

/**
 * @brief Set UHF set time info.
 *
 * @param[in] time - pointer with received time
 *
 * @return status.
 */
int32_t sdr_uhf_set_time_req(s_timespec_t *time);

/**
 * @brief Set UHF bootload write page info.
 *
 * @param[in] write_page_cfg - Pointer with received page cfg
 *
 * @return status.
 */
int32_t sdr_uhf_bootload_msg_write(s_msg_data_t *write_page_cfg);

/**
 * @brief set UHF timer values.
 *
 * @param[in] tmr_cfg -  Pointer with received timer cfg
 *
 * @return status.
 */
int32_t sdr_app_tc_set_uhf_tmr_cfg(s_sdr_tmr_cfg *tmr_cfg);

#ifdef __cplusplus
}
#endif
#endif /*COMMS_UHF_API_H_*/

/**
 * @file comms_uhf_ipc.h
 *
 * @brief This file has the function prototypes of IPC message
 * transfer with other layers
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

#ifndef COMMS_UHF_IPC_H
#define COMMS_UHF_IPC_H

#include "exo_osal.h"
#include "exo_ral_cmn.h"
#include "comms_uhf_main.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief This function handles the comms telecommand, telemetry set response
 *
 * @param msg_id     : Identity of state
 * @param status     : status of state
 * @param tc_tm_data : pointer to telecommand, tekemetry data
 */
void comms_uhf_tc_tm_set_rsp_hdlr(uint16_t msg_id, int32_t status, \
        uint8_t *tc_tm_data);

/**
 * @brief This function handles the comms telecommand, telemetry get response
 *
 * @param msg_id : Identity of state
 * @param status  : Status of state
 * @param tc_tm_data : pointer to telecommand, tekemetry data
 * @param size : Size of data
 */
void comms_uhf_tc_tm_get_rsp_hdlr(uint16_t msg_id,int32_t status, \
        uint8_t *tc_tm_data, uint16_t size);

/**
 * @brief Abstracted API for COMMS layer that sends message payload
 *  to destination thread using os IPC functionalities
 *
 * @brief Send an IPC message over the UHF radio
 *
 * This function sends an IPC message with the given message ID
 * to the specified destination address over the UHF radio.
 *
 * @param[in] msg_id Message ID to send
 * @param[in] dest Destination address for the message
 */
void uhf_send_ipc(uint16_t msg_id, uint16_t dest);

/**
 * @brief This function handles the comms telecommand, telemetry response
 * @brief Handle generic TC/TM response
 *
 * @param msg_id Message ID
 * @param size Response data size in bytes
 */
void comms_uhf_tc_tm_rsp_hdlr(uint16_t msg_id,uint16_t size);

/**
 * @brief This function handles the comms telecommand, telemetry response
 * @brief Handle get TM storage response
 *
 * @param msg_id Message ID
 * @param tm_pld Pointer to TM data
 * @param size TM data size in bytes
 */
void comms_uhf_tm_stor_get_rsp_hdlr(uint16_t msg_id, uint8_t *tm_pld, \
        uint16_t size);

/**
 * @brief This API for UHF layer that sends message payload
 * to destination thread using os IPC functionalities
 * @brief Send IPC payload over UHF
 *
 * @param msg_id Message ID
 * @param dest Destination module ID
 * @param pld_size Payload size in bytes
 * @param pld_ptr Pointer to payload data
 */
void uhf_send_ipc_pld(uint16_t msg_id, uint16_t dest, uint16_t pld_size, \
        uint8_t *pld_ptr);

/**
 * @brief This function handles the comms telecommand, telemetry get response
 * @brief Transmit UHF beacon
 *
 * @param beacon_data Pointer to beacon data
 * @param size Length of beacon data in bytes
 */
void comms_uhf_beacon_tx(uint8_t *beacon_data, uint16_t size);

#ifdef __cplusplus
}
#endif
#endif /*COMMS_UHF_IPC_H */

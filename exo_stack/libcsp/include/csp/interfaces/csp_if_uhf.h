/**
 * @file csp_if_uhf.h
 *
 * @brief This file contains function prototypes and types that is used
 *        for sending and receiving data through can interface
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

#ifndef CSP_IF_UHF_H_
#define CSP_IF_UHF_H_

#include <stdint.h>
#include <errno.h>

#define UHF_START_BYTE_0     0x22           /** First start byte  */
#define UHF_START_BYTE_1     0x69           /** Second start byte  */
/** Size of UHF packet header */
#define UHF_HEADER_SIZE      6
/** Max payload size for UHF packet */ 
#define UHF_MAX_PAYLOAD      251
/** MTU size for UHF interface */
#define CSP_IF_SLTCP_UHF_MTU     251
/**
  * @brief Socket option for comms
  * UHF interface receive state machine states
  */
typedef enum {
    UHF_WAIT_FOR_START0,
    UHF_WAIT_FOR_START1,
    UHF_WAIT_FOR_LENGTH,
    UHF_RECEIVE_DATA
}e_uhf_uart_state_t;

/**
 * @brief Send packet over UHF interface
 * 
 * This function sends a CSP packet over the UHF radio interface.
 *
 * @param[in] ifroute - Pointer to CSP route 
 * @param[in] packet - Pointer to CSP packet
 *
 * @return Error code
*/
int csp_uhf_tx(const csp_route_t * ifroute, csp_packet_t * packet);

/**
 * Decode received data and eventually route the packet.
 * @brief Handle received UHF packet
 *
 * This function handles a packet received on the UHF radio interface.
 * 
 * @param[in] iface - Pointer to CSP interface 
 * @param[in] buf - Pointer to received packet data
 * @param[in] len - Length of received data  
 * @param[in] pxTaskWoken - Task woken flag
 */
void csp_uhf_rx(csp_iface_t * iface, const uint8_t * buf, size_t len, void * pxTaskWoken);

#endif /* CSP_IF_UHF_H_ */

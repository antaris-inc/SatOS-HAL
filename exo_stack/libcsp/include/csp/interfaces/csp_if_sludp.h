/**
 * @file csp_if_sludp.h 
 *
 * @brief This file contains functions to used for sending and
 * receiving data through UART interface
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
/*********************************************************************/
#ifndef _CSP_IF_SLUDP_H_
#define _CSP_IF_SLUDP_H_

#include "csp.h"
#include "csp_interface.h"


/**
   Default name of SLUDP interface.
*/
#define CSP_IF_SLUDP_DEFAULT_NAME	"SLUDP"

/**
   Setup SLUDP interface.
   @param[in] device Ethernet device to bind and read address prefix from.
   @param[in] ifname Name of CSP interface, use NULL for default name #CSP_IF_SLUDP_DEFAULT_NAME.
   @param[out] ifc Created CSP interface.
   @return #CSP_ERR_NONE on succcess - else assert.
*/
int csp_sludp_init(const char *device, const char *ifname, csp_iface_t **ifc);

#ifdef LWIP_THROW_TEST
/**
 * @brief This API invoke a thread to handle the test socket udp IPC
 * messages
 * @return void
 */
int32 test_udp_socket(void);
/**
 * @brief This function create and handle test UDP socket
 *
 * @param[in] arg : pointer to handle the argument
 */
void test_sock_udp(void* arg);
#endif
#endif /* _CSP_IF_SLUDP_H_ */

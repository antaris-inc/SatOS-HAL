/**
 * @file csp_if_sltcp.h
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

#ifndef _CSP_IF_SLTCP_H_
#define _CSP_IF_SLTCP_H_

#include "csp.h"
#include "csp_interface.h"


/**
   Default name of SLTCP interface.
*/
/** Default interface name for ground station 1 */
#define CSP_IF_SLTCP_DEFAULT_NAME	"SLTCP_GS1"
/** Default interface name for ground station 2 */  
#define CSP_IF_SLTCP_DEFAULT_NAME_GS2	"SLTCP_GS2"
/** Default interface name for UHF */
#define CSP_IF_SLTCP_DEFAULT_NAME_UHF	"SLTCP_UHF"

/**
 * @brief This API initialize the TCP socket
 *
 * @param[in] device : pointer to device name
 * @param[in] ifname : pointer to ifname
 * @param[in] ifc : Double pointer to CSP iface handle
 *
 * @return status of socket
 * @retval #CSP_ERR_NONE on succcess - else assert.
 */
int csp_sltcp_init_uhf(const char *device, const char *ifname, csp_iface_t **ifc);

int csp_sltcp_init_gs2(const char *device, const char *ifname, csp_iface_t **ifc);

#endif /* _CSP_IF_SLTCP_H_ */

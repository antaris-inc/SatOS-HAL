/**
 * @file csp_comms.h
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

#ifndef CSP_COMMS_H_
#define CSP_COMMS_H_

#include <stdint.h>
#include <unistd.h>

/**
  * @brief Socket option for comms
  */
typedef enum
{
    S1_HWIL_GS1,
    S2_DEFAULT_BK,
    S3_UHF_HWIL_GS3
}e_comms_socket_opt;

/**
* @brief This function used for setting up the CSP interface
 * @brief Initialize CSP 
 * 
 * This function performs initialization of the Cubesat Space Protocol
 * (CSP) communication system. It should be called before sending/
 * receiving any CSP packets.
 *
*/
void CSP_Setup(void);

/**
 * @brief Send telemetry data to comms interface
 *
 * This function sends telemetry data to the communications interface.
 * It handles segmenting the data if needed based on MTU size.
 *
 * @param[in] tm_data - Pointer to telemetry data buffer 
 * @param[in] len - Length of telemetry data in bytes
 * 
 * @return Number of bytes sent or negative error code
*/
int32_t comms_send_tm(uint8_t* tm_data, uint16_t len);

/**
 * @brief This function is used for receiving Telecommand from UHF module
 * @brief Receive telemetry/command data 
 *
 * This function receives incoming telemetry/command data from the 
 * communications interface.
 *
 * @return Number of bytes received or negative error code
*/
int32_t comms_recv_tc(void);

/**
 * @brief This function is used for sending Telemetry to UHF module
 *
 * @param [in] tm_data : pointer to telemetry data
 * @param [in] len : Length of the data
 *
 * @return send status
 * @retval status success 0 or failure
 */
int32_t comms_send_tm_uhf(uint8_t* tm_data, uint16_t len);

/**
 * @brief This function is used for sending Telemetry to backdoor
 *
 * @param [in] tm_data : pointer to telemetry data
 * @param [in] len : Length of the data
 *
 * @return send status
 * @retval status success 0 or failure
 */
int32_t comms_send_tm_bc(uint8_t* tm_data, uint16_t len);

/**
 * @brief This API handle the back door socket data
 *
 * @param [in] data : pointer to data
 * @param [in] length : Length of the data
 *
 * @return No return
 */
void comms_back_door_data_receive(uint8_t *data, uint16_t length);

#endif /* CSP_COMMS_H_ */

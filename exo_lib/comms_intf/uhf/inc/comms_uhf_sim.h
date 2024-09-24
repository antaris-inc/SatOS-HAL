/**
 * @file comms_uhf_uhf_sim.h
 *
 * @brief The file contains prototypes of functions used for
 *        interface programming of UHF module
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

#ifndef COMMS_UHF_SIM_H_
#define COMMS_UHF_SIM_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Pack UHF command response packet
 *
 * This function packs a UHF command response packet with the
 * provided command ID.
 *
 * The response packet format contains:
 * - Command ID
 * - Response payload
 * - CRC
 *
 * The response payload is populated with dummy data.
 * CRC is calculated and set in the packet.
 * cmd_id
 * The packed response packet is written to the global RX buffer
 * for subsequent reading.
 *
 * @param cmd_id Command ID to set in response
 */
void uhf_sim_pack_cmd_rsp(uint8_t cmd_id);

#ifdef __cplusplus
}
#endif
#endif /*COMMS_UHF_SIM_H_*/

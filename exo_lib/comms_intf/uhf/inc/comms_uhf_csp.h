/**
 * @file comms_uhf_csp.h
 *
 * @brief This file contains function prototypes and types that is used
 *        for sending and receiving data through UART interface
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

#ifndef COMMS_UHF_CSP_H_
#define COMMS_UHF_CSP_H_

#include <stdint.h>
#include <errno.h>
#include <csp_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UHF_UART_TX_ADDRESS 15 ///< UHF UART TX address
#define UHF_CMD_TX_ADDRESS 14 ///< UHF CMD TX address

#define UHF_CSP_TX_DATA_PORT 35 ///< UHF TX data port number
#define UHF_CSP_RX_DATA_PORT 25 ///< UHF RX data port number

#define UHF_UART_MTU 241 ///< UART Maximum transmit size for UHF

#define BK_ETH_TX_ADDRESS 12 ///< Backdoor ethernet address
#define BK_ETH_TX_DATA_PORT 21

/**
 * @brief This function is used for updating the CSP address of UHF radio
 * @brief Update the CSP port and address used for UHF communication.
 *
 * This function updates the CSP port and address that will be used when
 * sending/receiving UHF packets over CSP.
 *
 * @param[in,out] csp_tx_port Pointer to CSP port variable. Will be updated.
 * @param[in,out] csp_tx_addr Pointer to CSP address variable. Will be updated.
 */
void comms_uhf_upd_port_addr(uint8_t *csp_tx_port,uint8_t *csp_tx_addr);

/**
 * @brief This function is used for updating the CSP address of UHF radio simulation
 * @brief Update simulated CSP port and address for UHF.
 *
 * In simulation mode, update the port and address used for UHF communication.
 *
 * @param[in,out] csp_tx_port Simulated CSP port.
 * @param[in,out] csp_tx_addr Simulated CSP address.
 */
void comms_uhf_sim_upd_port_addr(uint8_t *csp_tx_port,uint8_t *csp_tx_addr);

/**
 * @brief This function is used for sending the CSP data via UHF module
 * This function is used for testing
 */
void uhf_csp_tx_data(void);

/**
 * @brief This function is used for sending CSP ping for UHF Module
 * @brief Send UHF ping command.
 *
 * Sends a ping command to the UHF radio module.
 *
 * @param[in] tc_cmd Pointer to ping command buffer.
 */
void uhf_csp_ping(uint8_t *tc_cmd);

/**
 * @brief This function is used for packing the UART data to send via UHF module
 * @brief Pack CSP packet into UHF UART frame format.
 *
 * Takes a CSP packet and packs it into the UHF UART frame format.
 *
 * @param[in] packet Pointer to CSP packet to pack.
 * @param[out] frame_buff Buffer to store packed UHF UART frame.
 */
void uhf_pack_uart_csp_frame(csp_packet_t *packet, uint8_t *frame_buff);

/**
 * @brief This function is used for unpacking the UART data to send via UHF module
 * @brief Unpack UHF UART frame into CSP packet.
 *
 * Takes a UHF UART frame and unpacks it into a CSP packet structure.
 *
 * @param[out] packet CSP packet structure to unpack frame into.
 * @param[in] frame_buff Buffer containing UHF UART frame to unpack.
 */
void uhf_unpack_uart_csp_frame(csp_packet_t *packet, uint8_t *frame_buff);

/**
 * @brief This function is used for packing the UART data to send via UHF module
 * @brief Pack CSP packet into generic UHF UART frame.
 *
 * Packs a CSP packet into a generic UHF UART frame format.
 *
 * @param[in] packet Pointer to CSP packet to pack.
 * @param[out] frame_buff Buffer to store packed UHF UART frame.
 */
void uhf_pack_uart_frame(csp_packet_t *packet, uint8_t *frame_buff);

/**
 * @brief This function is used for unpacking the UART data to send via UHF module
 * @brief Unpack generic UHF UART frame into CSP packet.
 *
 * Unpacks a generic UHF UART frame into a CSP packet structure.
 *
 * @param[out] packet CSP packet structure to unpack frame into.
 * @param[in] frame_buff Buffer containing UHF UART frame to unpack.
 */
void uhf_unpack_uart_frame(csp_packet_t *packet, uint8_t *frame_buff);

/**
 * @brief This function updates the command ID.
 * @brief Send UHF radio command over UART.
 *
 * Sends a UHF radio command to the UHF radio module over the UART interface.
 *
 * @param[in] cmd_id The UHF radio command ID to send.
 */
void uhf_upd_send_uart_cmd(uint8_t cmd_id);

/**
 * @brief Send UHF command over UART.
 *
 * Sends a UHF radio command to the module over UART.
 *
 * @param[in] data Pointer to command data buffer.
 * @param[in] len Length of command data in bytes.
 * @return 0 on success, negative error code on failure.
 */
int32_t uhf_csp_uart_cmd_tx(uint8_t* data, uint16_t len);

/**
 * @brief Process UHF command response from UART.
 *
 * Parses a UHF radio command response received over UART.
 *
 * @param[in] pld Pointer to the UART response payload data.
 * @return UHF command response status.
 */
uint8_t uhf_proc_uart_cmd_rsp(uint8_t *pld);

/**
 * @brief Send UHF received packet over UART.
 *
 * Sends a received UHF packet from the radio module to the host MCU over UART.
 *
 * @param[in] frame Pointer to the received packet data.
 * @param[in] uhf_packet_length Length of the received packet.
 */
void uhf_send_rx_uart_cmd(uint8_t *frame,uint8_t uhf_packet_length);

#ifdef __cplusplus
}
#endif
#endif /* COMMS_UHF_CSP_H_ */

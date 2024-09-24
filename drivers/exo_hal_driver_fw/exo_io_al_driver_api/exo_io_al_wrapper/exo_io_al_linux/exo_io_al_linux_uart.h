/**
 * @file exo_io_al_linux_uart.h
 *
 * @brief This file contains linux wrapper functions declarations for IO interface
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

#ifndef _IO_AL_LINUX_UART_H_
#define _IO_AL_LINUX_UART_H_

#include "exo_hal_common.h"
#include "exo_io_al_uart_common.h"

/**
 * @brief IO-HAL UART6 initialization function for linux
 * @param[in] ioal_huart6 - pointer to UART6 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_uart6_init(ioal_uart_hdle *ioal_huart6);

/**
 * @brief IO-HAL UART1 initialization function for linux
 * @param[in] ioal_huart1 - pointer to UART1 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_uart1_init(ioal_uart_hdle *ioal_huart6);

/**
 * @brief IO-HAL UART transmit function for linux
 * @param[in] ioal_huart - pointer to UART instance
 * @param[in] pdata - pointer to a buffer
 * @param[in] size - size of the data
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_uart_transmit(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout);

/**
 * @brief IO-HAL UART receive function for linux
 * @param[in] ioal_huart - pointer to UART instance
 * @param[out]pdata - pointer to a buffer
 * @param[in] size - size of the data
 * @param[in] timeout - timeout duration
 * @retval Total bytes received
 */
uint32 io_hal_linux_uart_receive(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout);

/**
 * @brief IO-HAL UART get state function for linux
 * @param[in] ioal_huart - pointer to UART instance
 * @retval UART state
 */
ioal_uart_state io_hal_linux_uart_get_state(ioal_uart_hdle *ioal_huart);

/**
 * @brief This function transmit the data in DMA mode for linux
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 *                                                      the configuration information for UART
 * @param[in] pdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_uart_transmit_dma(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size);

/** Functions mapping **/
#define io_hal_common_uart6_init                io_hal_linux_uart6_init
#define io_hal_common_uart1_init                io_hal_linux_uart1_init
#define io_hal_common_uart_transmit             io_hal_linux_uart_transmit
#define io_hal_common_uart_receive              io_hal_linux_uart_receive
#define io_hal_common_uart_get_state            io_hal_linux_uart_get_state
#define io_hal_common_uart_transmit_dma         io_hal_linux_uart_transmit_dma

#endif

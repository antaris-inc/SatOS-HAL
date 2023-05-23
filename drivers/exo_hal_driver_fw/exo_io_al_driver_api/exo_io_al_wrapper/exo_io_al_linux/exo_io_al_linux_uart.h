/*
 * @file exo_io_al_linux_uart.h
 *
 * @brief This file contains linux wrapper functions declarations for IO interface
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

#ifndef _IO_AL_LINUX_UART_H_
#define _IO_AL_LINUX_UART_H_

#include "exo_hal_common.h"
//#include "exo_io_al_i2c_common.h"



/**
 * @brief IO-HAL UART6 initialization function for linux
 * @param[in] ioal_huart6 - pointer to UART6 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_uart6_init(void *ioal_huart6);

/**
 * @brief IO-HAL UART1 initialization function for linux
 * @param[in] ioal_huart1 - pointer to UART1 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_uart1_init(void *ioal_huart1);

/**
 * @brief IO-HAL UART transmit function for linux
 * @param[in] ioal_huart - pointer to UART instance
 * @param[in] pdata - pointer to a buffer
 * @param[in] size - size of the data
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_uart_transmit(void *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout);

/**
 * @brief IO-HAL UART receive function for linux
 * @param[in] ioal_huart - pointer to UART instance
 * @param[out]pdata - pointer to a buffer
 * @param[in] size - size of the data
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_uart_receive(void *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout);



#define io_hal_common_uart6_init 				io_hal_linux_uart6_init
#define io_hal_common_uart1_init 				io_hal_linux_uart1_init
#define io_hal_common_uart_transmit		 		io_hal_linux_uart_transmit
#define io_hal_common_uart_receive		 		io_hal_linux_uart_receive


#endif

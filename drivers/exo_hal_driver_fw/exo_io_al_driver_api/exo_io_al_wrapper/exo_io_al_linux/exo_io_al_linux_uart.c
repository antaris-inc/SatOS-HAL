/*
 * @file exo_io_al_linux_uart.c
 *
 * @brief This file contains linux wrapper functions for IO interface
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

#include <stdio.h>
#include <unistd.h>
#include "exo_io_al_linux_uart.h"
#include "exo_io_al_uart_common.h"
#include "exo_hal_io_al_common.h"


/**
 * @brief IO-HAL UART6 initialization function for linux
 */
hal_ret_sts io_hal_linux_uart6_init(void *ioal_huart6)
{
    printf("\n EXO UART IO Vendor driver porting layer initialise");
    printf("\n EXO UART IO Vendor driver initialise");
    usleep(100000);
    printf("\n EXO UART IO Vendor driver initialisation completed successfully");
    printf("\n EXO UART IO Vendor driver porting layer initialisation completed successfully");
    return 0;
}

/**
 * @brief IO-HAL UART1 initialization function for linux
 */
hal_ret_sts io_hal_linux_uart1_init(void *ioal_huart1)
{
    printf("\n EXO UART 1 IO Vendor driver porting layer initialise");
    printf("\n EXO UART 1 IO Vendor driver initialise");
    usleep(100000);
    printf("\n EXO UART 1 IO Vendor driver initialisation completed successfully");
    printf("\n EXO UART 1 IO Vendor driver porting layer initialisation completed successfully");
    return 0;
}

/**
 * @brief IO-HAL UART transmit function for linux
 */
hal_ret_sts io_hal_linux_uart_transmit(void *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout)
{
    return 0;
}

/**
 * @brief IO-HAL UART receive function for linux
 */
hal_ret_sts io_hal_linux_uart_receive(void *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout)
{
    return 0;
}


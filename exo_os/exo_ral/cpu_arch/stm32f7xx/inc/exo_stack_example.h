/**
 * @file exo_stack_example.h
 *
 * @brief This file contains test function prototypes for communication protocols.
 *
 *  @copyright Copyright 2024 Antaris, Inc.
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

#ifndef EXO_OS_EXO_RAL_CPU_ARCH_STM32F7XX_INC_EXO_STACK_EXAMPLE_H_
#define EXO_OS_EXO_RAL_CPU_ARCH_STM32F7XX_INC_EXO_STACK_EXAMPLE_H_

#include "csp_if.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "cmsis_os.h"
#include "lwip.h"
#include "osal_test.h"
#include "exo_osal.h"
#include "usb_netif.h"


/**
 * @brief This API use to test the CSP client.
 */
void csp_client_test();

/**
 * @brief This API use to test the CSP server.
 */
void csp_server_test();

#endif /* EXO_OS_EXO_RAL_CPU_ARCH_STM32F7XX_INC_EXO_STACK_EXAMPLE_H_ */

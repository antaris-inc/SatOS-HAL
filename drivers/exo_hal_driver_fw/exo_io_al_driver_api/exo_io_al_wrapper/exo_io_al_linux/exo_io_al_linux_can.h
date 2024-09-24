/**
 * @file exo_io_al_linux_can.h
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

#ifndef _IO_AL_LINUX_CAN_H_
#define _IO_AL_LINUX_CAN_H_

#include "exo_hal_common.h"

/**
 * @brief IO-HAL CAN1 initialization function for linux
 * @param[in] ioal_hcan1 - pointer to CAN1 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_can1_init(void *ioal_hcan1);

/**
 * @brief IO-HAL CAN2 initialization function for linux
 * @param[in] ioal_hcan2 - pointer to CAN2 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_can2_init(void *ioal_hcan2);

/**
 * @brief IO-HAL CAN3 initialization function for linux
 * @param[in] ioal_hcan3 - pointer to CAN3 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_can3_init(void *ioal_hcan3);

/**
 * @brief IO-HAL CAN start function for linux
 * @param[in] ioal_hcan - pointer to CAN instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_can_start(void *ioal_hcan);

/**
 * @brief IO-HAL CAN stop function for linux
 * @param[in] ioal_hcan - pointer to CAN instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_can_stop(void *ioal_hcan);

/** IOAL CAN function mapping **/
#define io_hal_common_can1_init             io_hal_linux_can1_init
#define io_hal_common_can2_init             io_hal_linux_can2_init
#define io_hal_common_can3_init             io_hal_linux_can3_init
#define io_hal_common_can_start             io_hal_linux_can_start
#define io_hal_common_can_stop              io_hal_linux_can_stop

#endif

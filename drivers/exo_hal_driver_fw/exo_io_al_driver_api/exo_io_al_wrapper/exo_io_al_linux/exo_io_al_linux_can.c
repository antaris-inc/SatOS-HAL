/**
 * @file exo_io_al_linux_can.c
 *
 * @brief This file contains linux wrapper functions for IO interface
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

#include <stdio.h>
#include <unistd.h>
#include "exo_io_al_linux_can.h"
#include "exo_io_al_can_common.h"
#include "exo_hal_io_al_common.h"


/**
 * @brief IO-HAL CAN1 initialization function for linux
 */
hal_ret_sts io_hal_linux_can1_init(void *ioal_hcan1)
{
    printf("\n EXO CAN IO Vendor driver porting layer initialise");
    printf("\n EXO CAN IO Vendor driver initialise");
    usleep(100000);
    printf("\n EXO CAN IO Vendor driver initialisation completed successfully");
    printf("\n EXO CAN IO Vendor driver porting layer initialisation completed successfully");
    return 0;
}

/**
 * @brief IO-HAL CAN2 initialization function for linux
 */
hal_ret_sts io_hal_linux_can2_init(void *ioal_hcan2)
{
    printf("\n EXO CAN IO Vendor driver porting layer initialise");
    printf("\n EXO CAN IO Vendor driver initialise");
    usleep(100000);
    printf("\n EXO CAN IO Vendor driver initialisation completed successfully");
    printf("\n EXO CAN IO Vendor driver porting layer initialisation completed successfully");
    return 0;
}

/**
 * @brief IO-HAL CAN3 initialization function for linux
 */
hal_ret_sts io_hal_linux_can3_init(void *ioal_hcan3)
{
    printf("\n EXO CAN IO Vendor driver porting layer initialise");
    printf("\n EXO CAN IO Vendor driver initialise");
    usleep(100000);
    printf("\n EXO CAN IO Vendor driver initialisation completed successfully");
    printf("\n EXO CAN IO Vendor driver porting layer initialisation completed successfully");
    return 0;
}

/**
 * @brief IO-HAL CAN start function for linux
 */
hal_ret_sts io_hal_linux_can_start(void *ioal_hcan)
{
    return 0;
}

/**
 * @brief IO-HAL CAN stop function for linux
 */
hal_ret_sts io_hal_linux_can_stop(void *ioal_hcan)
{
    return 0;
}

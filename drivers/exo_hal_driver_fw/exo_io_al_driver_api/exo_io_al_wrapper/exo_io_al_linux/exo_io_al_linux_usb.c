/**
 * @file exo_io_al_linux_usb.c
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
#include "exo_io_al_linux_usb.h"
#include "exo_io_al_usb_common.h"
#include "exo_hal_io_al_common.h"


/**
 * @brief IO-HAL USB initialization function for linux
 */
hal_ret_sts io_hal_linux_usb_device_init(void *ioal_husbdev)
{
    printf("\n EXO USB IO Vendor driver porting layer initialise");
    printf("\n EXO USB IO Vendor driver initialise");
    usleep(100000);
    printf("\n EXO USB IO Vendor driver initialisation completed successfully");
    printf("\n EXO USB IO Vendor driver porting layer initialisation completed successfully");
    return 0;
}

/**
 * @brief IO-HAL USB deinit function for linux
 */
hal_ret_sts io_hal_linux_usb_device_deinit(void *ioal_husbdev)
{
    printf("\n EXO USB IO Vendor driver porting layer deinitialise");
    printf("\n EXO USB IO Vendor driver deinitialise");
    usleep(100000);
    printf("\n EXO USB IO Vendor driver deinitialisation completed successfully");
    printf("\n EXO USB IO Vendor driver porting layer deinitialisation completed successfully");
    return 0;
}

/**
 * @brief IO-HAL USB start function for linux
 */
hal_ret_sts io_hal_linux_usb_device_start(void *ioal_husbdev)
{
    return 0;
}

/**
 * @brief IO-HAL USB stop function for linux
 */
hal_ret_sts io_hal_linux_usb_device_stop(void *ioal_husbdev)
{
    return 0;
}

/**
 * @file exo_io_al_linux_rtc.c
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
#include "exo_io_al_linux_rtc.h"
#include "exo_io_al_rtc_common.h"
#include "exo_hal_io_al_common.h"

/**
 * @brief IO-HAL RTC initialization function for linux
 */
hal_ret_sts io_hal_linux_rtc_init(void *ioal_hrtc)
{
    printf("\n EXO RTC IO Vendor driver porting layer initialise");
    printf("\n EXO RTC IO Vendor driver initialise");
    usleep(100000);
    return HAL_SCS;
}

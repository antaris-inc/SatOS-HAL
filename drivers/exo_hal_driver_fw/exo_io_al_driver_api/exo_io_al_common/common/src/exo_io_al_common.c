/**
 * @file exo_io_al_common.c
 *
 * @brief This file contains function definition for application hardware management
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
#include "exo_io_al_common.h"
#include "exo_hal_io_al_common.h"
#include "exo_io_al_i2c_common.h"
#include "exo_io_al_uart_common.h"
#include "exo_io_al_spi_common.h"
#include "exo_io_al_usb_common.h"
#include "exo_io_al_eth_common.h"
#include "exo_io_al_rtc_common.h"
#include "exo_io_al_can_common.h"
#include "exo_common.h"

extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

/**
 * @brief IO-HAL initialization function
 */
hal_ret_sts io_hal_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL Framework Initialise");
#endif
    hal_ret_sts sts = 0;
    io_hal_i2c_init();
    io_hal_spi_init();
    io_hal_usb_device_init();
    io_hal_uart_init();
    io_hal_can_init();
    io_hal_rtc_init();
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL Framework Initialisation completed successfully");
#endif
    return sts;
}

/**
 * @brief Function to get IOAL instance handle pointer
 */
void* get_ioal_inst_hdle(io_inst_id inst_id)
{
    return intf_inst_hdle_ptr[inst_id];
}

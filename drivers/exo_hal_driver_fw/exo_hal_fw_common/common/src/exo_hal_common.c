/**
 * @file exo_hal_common.c
 *
 * @brief This file contains structures,enumerations,function declaration for HAL
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


#define ALL_INTF_ENB


#include <stdio.h>
#include <unistd.h>
#include "exo_hal_common.h"
#include "exo_io_al_common.h"
#include "exo_ahw_al_common.h"
#include "exo_io_al_can_common.h"
#include "exo_io_al_uart_common.h"
#include "exo_io_al_spi_common.h"
#include "exo_io_al_rtc_common.h"
#include "exo_io_al_usb_common.h"
#include "exo_io_al_i2c_common.h"
#include "exo_io_al_eth_common.h"

/**
 * @brief This API initialize the HAL
 */
void hal_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO HAL Framework Initialise");
    usleep(100000);
#endif
    ahw_io_lookup_table_updt();
    io_hal_init();
#ifdef LINUX_TEMP_PORT
    printf("\n EXO HAL Framework Initialisation completed successfully");
#endif
}

/**
 * @brief This API is error handler
 */
void ioal_error_handler(void)
{
    // Placeholder for interface error handling
    return;
}


/**
 * @brief This is dummy function for linux
 */
void linux_dummy_fn(void* arg)
{
}




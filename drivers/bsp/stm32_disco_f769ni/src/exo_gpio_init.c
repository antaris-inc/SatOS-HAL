/*
 * @file exo_gpio_init.c
 *
 * @brief This file contains STM32 Discovery board GPIO initialization functionality's
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

#include "exo_io_al_gpio_common.h"
#include "exo_gpio.h"
#include "exo_osal.h"
#include "exo_common.h"


#ifndef __weak
    #define __weak   __attribute__((weak))
#endif

#ifndef EXO_UNUSED
#define EXO_UNUSED(X) (void)X
#endif


/* NEW IMPLEMENTATION*/
/**
 * @brief Initializes the GPIO pins for the payload server.
 *
 * This function configures the GPIO pins used by the payload server.
 * It should be called during system initialization to ensure the
 * payload server's GPIO pins are properly set up.
 */
void payload_server_gpio_init()
{
    // Function implementation here
}

/**
 * @brief Initializes the GPIO pins for the OBC (On-Board Computer).
 *
 * This function configures the GPIO pins used by the OBC. It should
 * be called during system initialization to ensure the OBC's GPIO
 * pins are properly set up.
 */
void obc_gpio_init()
{
    // Function implementation here
}

/**
 * @brief Initializes the GPIO pins for the edge server.
 *
 * This function configures the GPIO pins used by the edge server.
 * It should be called during system initialization to ensure the
 * edge server's GPIO pins are properly set up.
 */
void edge_server_gpio_init()
{
    // Function implementation here
}

/**
 * @brief Initializes the GPIO pins for the GPS module.
 *
 * This function configures the GPIO pins used by the GPS module.
 * It should be called during system initialization to ensure the
 * GPS module's GPIO pins are properly set up.
 */
void gps_gpio_init()
{
    // Function implementation here
}

/**
 * @brief De-initializes interrupt settings for the power supply (PS) system.
 *
 * This function de-configures the interrupt settings related to the
 * power supply system. It should be called to clean up interrupt
 * settings when the PS system is no longer in use or during system shutdown.
 */
void ps_intr_deinit()
{
    // Function implementation here
}

/**
 * @brief De-initializes interrupt settings for the edge system.
 *
 * This function de-configures the interrupt settings related to the
 * edge system. It should be called to clean up interrupt settings
 * when the edge system is no longer in use or during system shutdown.
 */
void edge_intr_deinit()
{
    // Function implementation here
}

/**
 * @brief De-initializes interrupt settings for the GPS module.
 *
 * This function de-configures the interrupt settings related to the
 * GPS module. It should be called to clean up interrupt settings when
 * the GPS module is no longer in use or during system shutdown.
 */
void gps_intr_deinit()
{
    // Function implementation here
}

/**
 * @brief Initializes the board support package (BSP).
 *
 * This function initializes the BSP, which includes setting up
 * necessary hardware and software configurations required for
 * the system to operate correctly. This function should be called
 * early in the system initialization process.
 */
void bsp_init()
{
    // Function implementation here
}

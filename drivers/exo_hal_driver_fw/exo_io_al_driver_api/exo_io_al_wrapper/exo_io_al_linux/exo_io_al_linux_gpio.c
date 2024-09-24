/**
 * @file exo_io_al_linux_gpio.c
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
#include "exo_io_al_linux_gpio.h"
#include "exo_hal_io_al_common.h"
#include "exo_common.h"
//table to save callback function and io_handle used by application hardware if pin configured as external interrupt
exti_handler_details_t *ioal_gpio_exti_io_intf_hdle_ptr[MC_AVAILABLE_EXTI_PINS];

/*!
 *  @brief This API configure pin as output by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_linux_gpio_config(gpio_config_info_hdl config_details)
{

    return GPIO_OK;
}

/*!
 *  @brief This API configure pin as interrpt by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_linux_gpio_interrupt_config(gpio_config_info_hdl config_details)
{
    return GPIO_OK;
}

/*!
 *  @brief This API drive pin number as LOW/HIGH by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_linux_gpio_write(gpio_port_details *port, uint32_t drive_logic)
{
    return GPIO_OK;
}

/*!
 *  @brief This API read pin number state by invoking STM32 HAL API
 */
uint32_t io_hal_linux_gpio_read(gpio_port_details *port)
{
    return 1;
}

/*!
 *  @brief This API toggles pin number by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_linux_gpio_toggle(gpio_port_details *port)
{
    return GPIO_OK;
}

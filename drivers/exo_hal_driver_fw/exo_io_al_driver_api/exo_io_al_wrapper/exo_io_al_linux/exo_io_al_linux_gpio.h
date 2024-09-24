/**
 * @file exo_io_al_linux_gpio.h
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

#ifndef _IO_AL_LINUX_GPIO_H_
#define _IO_AL_LINUX_GPIO_H_

#include "exo_hal_common.h"
#include "exo_io_al_gpio_common.h"

/* Provide total number of GPIO pins available in uc */
#define MC_AVAILABLE_GPIO_PINS                        ((uint16_t)114U)

/* Provide total number of  external interrupts available in uc */
#define MC_AVAILABLE_EXTI_PINS                        ((uint16_t)15U)

/* Provide total number of pins available in a single port (i.e) 16 pins in PORTA*/
#define MC_PORT_REGISTER_PIN_COUNT                    ((uint16_t)16U)

/* Provide starting base address of gpio peripheral*/
#define MC_GPIO_BASE_ADDRESS                          AHB1PERIPH_BASE

/* Provide window size between two ports (i.e) length between PORTA and PORTB is 0x400*/
#define GPIO_PORT_ADDR_WINDOW_SIZE                    0x400u

/* Provide model configuration value of uc*/
#define  IOAL_GPIO_MODE_INPUT          1
#define  IOAL_GPIO_MODE_OUTPUT_PP      2
#define  IOAL_GPIO_MODE_OUTPUT_OD      3
#define  IOAL_GPIO_MODE_IT_RISING      4
#define  IOAL_GPIO_MODE_IT_FALLING     5
#define  IOAL_GPIO_MODE_IT_RISING_FALLING 6

/* Provide push/pull configuration value of uc*/
#define  IOAL_GPIO_NOPULL   0
#define  IOAL_GPIO_PULLUP   1
#define  IOAL_GPIO_PULLDOWN 2

/**
 * @brief External interrupt pointer table structure.
 */
typedef enum _gpio_ret_sts
{
    GPIO_OK = 0x00u,
    GPIO_NOK =0x01u,
    GPIO_INVALID = 0xFFu
}gpio_ret_sts;

/**
 * @brief Structure to hold basic details required to configure pin as input/output/interrupt for stm32
 *
 */
typedef struct
{
    gpio_port_details port;
    uint32_t mode;      /*!< Specifies the operating mode for the selected pins.
	                           This parameter can be a value of @ref GPIO_mode_define */
    uint32_t speed;
    uint32_t pull_sts;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
	                           This parameter can be a value of @ref GPIO_pull_define */
}gpio_config_info;

typedef gpio_config_info* gpio_config_info_hdl;

/*!
 *  @brief This API configure pin as output by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_linux_gpio_config(gpio_config_info_hdl config_details);

/*!
 *  @brief This API configure pin as interrpt by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_linux_gpio_interrupt_config(gpio_config_info_hdl config_details);

/*!
 *  @brief This API drive pin number as LOW/HIGH by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_linux_gpio_write(gpio_port_details *port, uint32_t drive_logic);

/*!
 *  @brief This API read pin number state by invoking STM32 HAL API
 */
uint32_t io_hal_linux_gpio_read(gpio_port_details *port);

/*!
 *  @brief This API toggles pin number by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_linux_gpio_toggle(gpio_port_details *port);

/** IOAL GPIO interface handler pointer**/
extern exti_handler_details_t *ioal_gpio_exti_io_intf_hdle_ptr[MC_AVAILABLE_EXTI_PINS];

/** Common GPIO function mapping **/
#define io_hal_common_gpio_write io_hal_linux_gpio_write
#define io_hal_common_gpio_read io_hal_linux_gpio_read
#define io_hal_common_gpio_toggle io_hal_linux_gpio_toggle
#define io_hal_common_gpio_interrupt_config io_hal_linux_gpio_interrupt_config
#define io_hal_common_gpio_config io_hal_linux_gpio_config

#endif /* _IO_AL_LINUX_GPIO_H_ */

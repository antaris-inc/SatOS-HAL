/**
 * @file exo_io_al_stm32f7xx_gpio.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for ETHERNET interface
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

#ifndef IO_AL_STM32F7xx_GPIO_H
#define IO_AL_STM32F7xx_GPIO_H

#include "exo_types.h"
#include "exo_hal_common.h"
#include "exo_io_al_common.h"
#include "exo_io_al_gpio_common.h"

#ifndef LINUX_TEMP_PORT
#include "stm32f7xx_hal_ext.h"
#endif

/* Provide total number of GPIO pins available in uc */
#define MC_AVAILABLE_GPIO_PINS                        ((uint16_t)168U)

/* Provide total number of  external interrupts available in uc */
#define MC_AVAILABLE_EXTI_PINS                        ((uint16_t)16U)

/* Provide total number of pins available in a single port (i.e) 16 pins in PORTA*/
#define MC_PORT_REGISTER_PIN_COUNT                    ((uint16_t)16U)

/* Provide starting base address of gpio peripheral*/
#define MC_GPIO_BASE_ADDRESS                          AHB1PERIPH_BASE

/* Provide window size between two ports (i.e) length between PORTA and PORTB is 0x400*/
#define GPIO_PORT_ADDR_WINDOW_SIZE                    0x400u

///* Provide model configuration value of uc*/
//#define  IOAL_GPIO_MODE_INPUT                         GPIO_MODE_INPUT     /*!< Input Floating Mode    */
//#define  IOAL_GPIO_MODE_OUTPUT_PP                     GPIO_MODE_OUTPUT_PP     /*!< Output Push Pull Mode                 */
//#define  IOAL_GPIO_MODE_OUTPUT_OD                     GPIO_MODE_OUTPUT_OD     /*!< Output Open Drain Mode                */
//#define  IOAL_GPIO_MODE_IT_RISING                     GPIO_MODE_IT_RISING   /*!< No Pull-up or Pull-down activation  */
//#define  IOAL_GPIO_MODE_IT_FALLING                    GPIO_MODE_IT_FALLING   /*!< Pull-up activation                  */
//#define  IOAL_GPIO_MODE_IT_RISING_FALLING             GPIO_MODE_IT_RISING_FALLING   /*!< Pull-down activation                */
//
///* Provide push/pull configuration value of uc*/
//#define  IOAL_GPIO_NOPULL                             GPIO_NOPULL   /*!< No Pull-up or Pull-down activation  */
//#define  IOAL_GPIO_PULLUP                             GPIO_PULLUP   /*!< Pull-up activation                  */
//#define  IOAL_GPIO_PULLDOWN                           GPIO_PULLDOWN   /*!< Pull-down activation                */


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
 * @brief this API function Mapping for gpio confiq 
 * @param[in] gpio_config_info_hdl - structure for gpio config Mode,speed,pull_sts.
 * @param[in] config_details       - gpio confiq details
 */
gpio_ret_sts io_hal_stm32f7xx_gpio_config(gpio_config_info_hdl config_details);

/*!
 * @brief this API function Mapping for gpio interrupt config
 * @param[in] gpio_config_info_hdl - structure for gpio config Mode,speed,pull_sts.
 * @param[in] config_details       - gpio confiq details
 */
gpio_ret_sts io_hal_stm32f7xx_gpio_interrupt_config(gpio_config_info_hdl config_details);

/*!
 * @brief this API function Mapping for gpio write 
 * @param[in] port                 - gpio port details.
 * @param[in] drive_logic          - gpio output pin drive state
 */
gpio_ret_sts io_hal_stm32f7xx_gpio_write(gpio_port_details *port, uint32_t drive_logic);

/*!
 * @brief this API function Mapping for gpio read 
 * @param[in] port                 - gpio port details.
 */
GPIO_PinState io_hal_stm32f7xx_gpio_read(gpio_port_details *port);

/*!
 * @brief this API function Mapping for gpio toggle 
 * @param[in] port                 - gpio port details.
 */
gpio_ret_sts io_hal_stm32f7xx_gpio_toggle(gpio_port_details *port);

extern exti_handler_details_t *ioal_gpio_exti_io_intf_hdle_ptr[MC_AVAILABLE_EXTI_PINS];

/** IO HAL common gpio function mapping **/
#define io_hal_common_gpio_write io_hal_stm32f7xx_gpio_write
#define io_hal_common_gpio_read io_hal_stm32f7xx_gpio_read
#define io_hal_common_gpio_toggle io_hal_stm32f7xx_gpio_toggle
#define io_hal_common_gpio_interrupt_config io_hal_stm32f7xx_gpio_interrupt_config
#define io_hal_common_gpio_config io_hal_stm32f7xx_gpio_config

#endif /* IO_AL_STM32F7xx_GPIO_H */

/**
 * @file exo_io_al_stm32f7xx_gpio.c
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

#include "exo_io_al_stm32f7xx_gpio.h"
#include "stm32f7xx_hal_gpio.h"

//table to save callback function and io_handle used by application hardware if pin configured as external interrupt
exti_handler_details_t *ioal_gpio_exti_io_intf_hdle_ptr[MC_AVAILABLE_EXTI_PINS];

/*!
 *  @brief external interrupt line number value will be converted into decimal value >> 0x0080 covert to 5U
 *
 *  @param[in] input : : line number
 *  @return Decimal value
 */
static uint16_t exti_line_number_to_decimal(uint16_t input);

/*!
 *  @brief This API enable clock to PORT
 *
 *  @param[in] port_name : Port name
 */
static void enable_gpio_clock(uint16_t port_name);

/*!
 * Mapping API for gpio speed confiq
 *
 * @param[in] speed : speed
 * @return position of speed
 * @retval Type of speed (Eg: GPIO_SPEED_FREQ_LOW)
 */
static uint32_t stm32f7xx_gpio_speed_config(uint32_t speed);

/*!
 * Mapping API for gpio pull status config
 *
 * @param[in] pull_sts : Pull status
 * @return GPIO pull status
 * @retval pull status (Eg: GPIO_NOPULL)
 */
static uint32_t stm32f7xx_gpio_pull_sts_config(uint32_t pull_sts);

/*!
 * Mapping API for gpio mode config
 *
 * @param[in] mode : GPIO mode
 *
 * @return Mode of GPIO
 * @retval Mode (Eg: GPIO_MODE_INPUT)
 */
static uint32_t stm32f7xx_gpio_mode_config(uint32_t mode);

/*!
 * Mapping API for gpio speed confiq
 */
static uint32_t stm32f7xx_gpio_speed_config(uint32_t speed)
{
    uint32_t ret=IOAL_GPIO_SPEED_FREQ_MAX;
    switch(speed)
    {
        case IOAL_GPIO_SPEED_FREQ_LOW:
            ret = GPIO_SPEED_FREQ_LOW;
            break;
        case IOAL_GPIO_SPEED_FREQ_MEDIUM:
            ret = GPIO_SPEED_FREQ_MEDIUM;
            break;
        case IOAL_GPIO_SPEED_FREQ_HIGH:
            ret = GPIO_SPEED_FREQ_HIGH;
            break;
        case IOAL_GPIO_SPEED_FREQ_VERY_HIGH:
            ret = GPIO_SPEED_FREQ_VERY_HIGH;
            break;
    }
    return ret;

}

/*!
 * Mapping API for gpio pull status config
 */
static uint32_t stm32f7xx_gpio_pull_sts_config(uint32_t pull_sts)
{
    uint32_t ret=IOAL_PULL_MAX;
    switch(pull_sts)
    {
        case IOAL_GPIO_NOPULL:
            ret = GPIO_NOPULL;
            break;
        case IOAL_GPIO_PULLUP:
            ret = GPIO_PULLUP;
            break;
        case IOAL_GPIO_PULLDOWN:
            ret = GPIO_PULLDOWN;
            break;
    }
    return ret;

}

/*!
 * Mapping API for gpio mode config
 */
static uint32_t stm32f7xx_gpio_mode_config(uint32_t mode)
{
    uint32_t ret=IOAL_GPIO_MODE_MAX;
    switch(mode)
    {
        case IOAL_GPIO_MODE_INPUT:
            ret = GPIO_MODE_INPUT;
            break;
        case IOAL_GPIO_MODE_OUTPUT_PP:
            ret = GPIO_MODE_OUTPUT_PP;
            break;
        case IOAL_GPIO_MODE_OUTPUT_OD:
            ret = GPIO_MODE_OUTPUT_OD;
            break;
        case IOAL_GPIO_MODE_IT_RISING:
            ret = GPIO_MODE_IT_RISING;
            break;
        case IOAL_GPIO_MODE_IT_FALLING:
            ret = GPIO_MODE_IT_FALLING;
            break;
        case IOAL_GPIO_MODE_IT_RISING_FALLING:
            ret = GPIO_MODE_IT_RISING_FALLING;
            break;
    }
    return ret;

}

/*!
 *  @brief external interrupt line number value will be converted into decimal value >> 0x0080 covert to 5U
 */
uint16_t exti_line_number_to_decimal(uint16_t input)
{
    /* local variable declaration */
    uint16_t shift=1;
    uint8_t count=0;
    uint16_t ret=0;
    if(input != 0)
    {
        for (count = 0; count < 31; count++)
        {
            if(input & shift)
            {
                ret = count;
                break;
            }
            else
            {
                shift <<= 1;
            }
        }
    }
    else
    {
        // invalid
        ret= 0;
    }
    return ret;
}

/*!
 *  @brief This API enable clock to PORT
 */
void enable_gpio_clock(uint16_t port_name)
{
    switch(port_name)
    {
        /* enable clock to PORTA */
        case ((uint16_t)0u):
			        __HAL_RCC_GPIOA_CLK_ENABLE();
        break;

        /* enable clock to PORTB */
        case ((uint16_t)01):
			        __HAL_RCC_GPIOB_CLK_ENABLE();
        break;

        /* enable clock to PORTC */
        case ((uint16_t)2u):
			        __HAL_RCC_GPIOC_CLK_ENABLE();
        break;

        /* enable clock to PORTD */
        case ((uint16_t)3u):
			        __HAL_RCC_GPIOD_CLK_ENABLE();
        break;

        /* enable clock to PORTE */
        case ((uint16_t)4u):
			        __HAL_RCC_GPIOE_CLK_ENABLE();
        break;

        /* enable clock to PORTF */
        case ((uint16_t)5u):
			        __HAL_RCC_GPIOF_CLK_ENABLE();
        break;

        /* enable clock to PORTG */
        case ((uint16_t)6u):
			        __HAL_RCC_GPIOG_CLK_ENABLE();
        break;

        /* enable clock to PORTH */
        case ((uint16_t)7u):
			        __HAL_RCC_GPIOH_CLK_ENABLE();
        break;

        /* enable clock to PORTI */
        case ((uint16_t)8u):
			        __HAL_RCC_GPIOI_CLK_ENABLE();
        break;

        /* enable clock to PORTJ */
        case ((uint16_t)9u):
			        __HAL_RCC_GPIOJ_CLK_ENABLE();
        break;

        default:
            break;
    }
}

/*!
 *  @brief This API configure pin as output by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_stm32f7xx_gpio_config(gpio_config_info_hdl config_details)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_TypeDef *PORT_NAME;
    //uint32_t pin_number;
    PORT_NAME = (GPIO_TypeDef *)(MC_GPIO_BASE_ADDRESS + (config_details->port.port_name * GPIO_PORT_ADDR_WINDOW_SIZE));

    /* Enable clock to gpio */
    enable_gpio_clock(config_details->port.port_name);

    GPIO_InitStruct.Pin = ((uint16_t)1u) << config_details->port.port_pin_number;
    GPIO_InitStruct.Mode = stm32f7xx_gpio_mode_config(config_details->mode);
    GPIO_InitStruct.Pull = stm32f7xx_gpio_pull_sts_config(config_details->pull_sts);
    GPIO_InitStruct.Speed = stm32f7xx_gpio_speed_config(config_details->speed);
    HAL_GPIO_Init(PORT_NAME, &GPIO_InitStruct);

    return GPIO_OK;
}

/*!
 *  @brief This API configure pin as interrpt by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_stm32f7xx_gpio_interrupt_config(gpio_config_info_hdl config_details)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_TypeDef *PORT_NAME;
    //uint8_t index_value;

    //index_value = exti_line_number_to_decimal(config_details->port.port_pin_number);

    PORT_NAME = (GPIO_TypeDef *)(MC_GPIO_BASE_ADDRESS + (config_details->port.port_name * GPIO_PORT_ADDR_WINDOW_SIZE));

    /* Enable clock to gpio */
    enable_gpio_clock(config_details->port.port_name);

    GPIO_InitStruct.Pin = ((uint16_t)1u) << config_details->port.port_pin_number;
    GPIO_InitStruct.Mode = stm32f7xx_gpio_mode_config(config_details->mode);
    GPIO_InitStruct.Pull = stm32f7xx_gpio_pull_sts_config(config_details->pull_sts);
    GPIO_InitStruct.Speed = stm32f7xx_gpio_speed_config(config_details->speed);

    //Call stm32 HAL gpio init func to configure pins
    HAL_GPIO_Init(PORT_NAME, &GPIO_InitStruct);

    if(config_details->port.port_pin_number < (5u))
    {
        HAL_NVIC_SetPriority((IRQn_Type)(config_details->port.port_pin_number + 6u), 5, 0);
        HAL_NVIC_EnableIRQ((IRQn_Type)(config_details->port.port_pin_number + 6u));
    }
    else if(config_details->port.port_pin_number < (10u))
    {
        HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    }
    else
    {
        HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    }

    return GPIO_OK;
}

/*!
 *  @brief This API drive pin number as LOW/HIGH by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_stm32f7xx_gpio_write(gpio_port_details *port, uint32_t drive_logic)
{
    GPIO_TypeDef *PORT_NAME;
    uint32_t pin_number;

    PORT_NAME = (GPIO_TypeDef *)(MC_GPIO_BASE_ADDRESS + (port->port_name * GPIO_PORT_ADDR_WINDOW_SIZE));
    pin_number = ((uint16_t)1u) << port->port_pin_number;
    HAL_GPIO_WritePin(PORT_NAME, pin_number, drive_logic);

    return GPIO_OK;
}


/*!
 *  @brief This API read pin number state by invoking STM32 HAL API
 */
GPIO_PinState io_hal_stm32f7xx_gpio_read(gpio_port_details *port)
{
    GPIO_TypeDef *PORT_NAME;
    uint32_t pin_number;

    PORT_NAME = (GPIO_TypeDef *)(MC_GPIO_BASE_ADDRESS + (port->port_name * GPIO_PORT_ADDR_WINDOW_SIZE));
    pin_number = ((uint16_t)1u) << port->port_pin_number;
    return HAL_GPIO_ReadPin(PORT_NAME, pin_number);
}

/*!
 *  @brief This API toggles pin number by invoking STM32 HAL API
 */
gpio_ret_sts io_hal_stm32f7xx_gpio_toggle(gpio_port_details *port)
{
    GPIO_TypeDef *PORT_NAME;
    uint32_t pin_number;

    PORT_NAME = (GPIO_TypeDef *)(MC_GPIO_BASE_ADDRESS + (port->port_name * GPIO_PORT_ADDR_WINDOW_SIZE));
    pin_number = ((uint16_t)1u) << port->port_pin_number;
    HAL_GPIO_TogglePin(PORT_NAME, pin_number);

    return GPIO_OK;
}

/**
 * @brief EXTI  External Interrupt ISR Handler CallBackFun
 * @param None
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint16_t index_value=0;
    index_value = exti_line_number_to_decimal(GPIO_Pin);
    if(index_value<=MC_AVAILABLE_EXTI_PINS)
    {
        if(ioal_gpio_exti_io_intf_hdle_ptr[index_value] != NULL)
        {
            ioal_gpio_exti_io_intf_hdle_ptr[index_value]->isr_handler((void*)ioal_gpio_exti_io_intf_hdle_ptr[index_value]->isr_args);
        }
    }
}


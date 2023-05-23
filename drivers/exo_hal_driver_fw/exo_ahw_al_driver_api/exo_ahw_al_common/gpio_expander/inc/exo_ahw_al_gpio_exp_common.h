/**
 * @file exo_ahw_al_gpio_exp_common.h
 *
 * @brief This file contains function prototypes ,structures and enumerations for gpio expander
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
#ifndef EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_COMMON_GPIO_EXPANDER_INC_EXO_AHW_AL_GPIO_EXP_COMMON_H_
#define EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_COMMON_GPIO_EXPANDER_INC_EXO_AHW_AL_GPIO_EXP_COMMON_H_

#include <stdint.h>
#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_ahw_al_common.h"

/**
 * @brief  GPIO Bit SET and Bit RESET enumeration
 */
typedef enum
{
    GPIO_EXP_PIN_RESET = 0,			/*!< Pin state is zero */
    GPIO_EXP_PIN_SET	,		/*!< Pin state is one */
    GPIO_EXP_PIN_MAX
}gpio_exp_gpio_pinstate;

/**
 * @brief  GPIO interrupt state status enumeration
 */
typedef enum
{
    GPIO_EXP_SOURCE_FALSE = 0,		/*!< Pin is not the source of the interrupt */
    GPIO_EXP_SOURCE_TRUE			/*!< Pin is the source of the interrupt */
}gpio_exp_gpio_intrstate;

/**
 * @brief GPIO pin polarity status enumeration
 */
typedef enum
{
    GPIO_EXP_ORIGINAL = 0,			/*!< Polarity is in the original state */
    GPIO_EXP_INVERTED			/*!< Polarity is in the inverted state */
}gpio_exp_pin_pol;

/**
 * @brief GPIO latch status enumeration
 */
typedef enum
{
    GPIO_EXP_NO_LATCH = 0,			/*!< latch is not enabled */
    GPIO_EXP_LATCH				/*!< pin is latched */
}gpio_exp_pin_lat;

/**
 * @brief GPIO pull enable status enumeration
 */
typedef enum
{
    GPIO_EXP_PULL_DISABLED = 0,		/*!< pull configuration is disabled */
    GPIO_EXP_PULL_ENABLED			/*!< pull configuration is enabled */
}gpio_exp_pin_pull;

/**
 * @brief  pullup - pull down status enumeration
 */
typedef enum
{
    GPIO_EXP_PULL_DOWN = 0,			/*!< pin is configured for pull up */
    GPIO_EXP_PULL_UP			/*!< pin is configured for pull down */
}gpio_exp_pin_up_dwn;

/**
 * @brief  GPIO MASK Interrupt status enumeration
 */
typedef enum
{
    GPIO_EXP_INTRUPT_ENABLE = 0,		/*!< Interrup mask is disabled */
    GPIO_EXP_INTRUPT_DISABLE		/*!< Interrup mask is enabled */
}gpio_exp_mask;

/**
 * @brief  Port configuration status enumeration
 */
typedef enum
{
    GPIO_EXP_PUSH_PULL = 0,			/*!< Pin is configured as push pull */
    GPIO_EXP_OPEN_DRAIN			/*!< Pin is configured as open drain */
}gpio_exp_port_cfg;

/**
 * @brief  Expander gpio pin enumeration
 */
typedef enum
{
    GPIO_EXP_GPIO_0 = 0b00000001,			/*!< Expander gpio pin 0 */
    GPIO_EXP_GPIO_1 = 0b00000010,			/*!< Expander gpio pin 1 */
    GPIO_EXP_GPIO_2 = 0b00000100,			/*!< Expander gpio pin 2 */
    GPIO_EXP_GPIO_3 = 0b00001000,			/*!< Expander gpio pin 3 */
    GPIO_EXP_GPIO_4 = 0b00010000,			/*!< Expander gpio pin 4 */
    GPIO_EXP_GPIO_5 = 0b00100000,			/*!< Expander gpio pin 5 */
    GPIO_EXP_GPIO_6 = 0b01000000,			/*!< Expander gpio pin 6 */
    GPIO_EXP_GPIO_7	= 0b10000000,			/*!< Expander gpio pin 7 */
    GPIO_EXP_GPIO_MAX = 0b11111111,

}gpio_exp_gpio_pin;

/**
 * @brief  Expander gpio pin I/O selection enumeration
 */
typedef enum
{
    GPIO_EXP_INPUT,				/*!< Pin input state */
    GPIO_EXP_OUTPUT				/*!< Pin output state */
}gpio_exp_pin_dir;

/**
 * @brief   Output drive strength enumeration
 */
typedef enum
{
    GPIO_EXP_C25LEVEL,			/*!< 0.25 of drive capability of the I/O */
    GPIO_EXP_C50LEVEL,			/*!< 0.50 of drive capability of the I/O */
    GPIO_EXP_C75LEVEL,			/*!< 0.75 of drive capability of the I/O */
    GPIO_EXP_C100LEVEL			/*!< same drive capability of the I/O */
}gpio_exp_pin_strgth;

/**
 * @brief gpio_expander gpio configuration structure definition
 */
typedef struct
{
    gpio_exp_gpio_pin   pin_num      : 8;	 	/*!< gpio pin number 						*/
    gpio_exp_pin_dir    dir          : 1;		/*!< gpio pin direction 					*/
    gpio_exp_pin_strgth strength     : 2;		/*!< gpio pin strength 						*/
    gpio_exp_pin_pol    polarity_inv : 1;		/*!< gpio pin polarity inversion		 	*/
    gpio_exp_pin_lat    latch        : 1;		/*!< gpio pin latch status 					*/
    gpio_exp_pin_pull   pull_enable  : 1;		/*!< gpio pin pull enable status 			*/
    gpio_exp_pin_up_dwn up_dwn       : 1;		/*!< gpio pin pull up/dwn status 			*/
    gpio_exp_mask       intr_set     : 1;		/*!< gpio pin interrupt mask status 		*/
    gpio_exp_port_cfg   pull_drain   : 1;		/*!< gpio pin push-pull or open-drain status*/
}gpio_exp_gpio_cfg;

/**
 * @brief gpio_expander device structure definition
 */
typedef struct
{
    ahw_al_gen_info		 	ahw_gen_info;		/*!< Application abstraction layer general information structure */
    gpio_exp_gpio_cfg 		gpio_cfg_hdl;		/*!< gpio_expander gpio configuration structure definition 		*/
    gpio_exp_gpio_pinstate		pin_state;		/*!< GPIO Bit SET and Bit RESET enumeration						*/
    gpio_exp_gpio_intrstate		intr_state;		/*!< GPIO Interrupt state status enumeration 					*/
    gpio_exp_pin_pol		pin_pol;		/*!< Pin polarity status enumeration						 	*/
    gpio_exp_pin_lat		pin_lat;		/*!< latch status enumeration									*/
    gpio_exp_pin_pull		pin_pull;		/*!< pull enable status enumeration 							*/
    gpio_exp_pin_up_dwn		pin_up_dwn;		/*!< pullup - pull down status enumeration	 					*/
    gpio_exp_mask			mask;			/*!< GPIO MASK Interrupt status enumeration						*/
    gpio_exp_port_cfg		port_cfg;		/*!< port configuration status enumeration 						*/
    gpio_exp_gpio_pin		gpio_pin;		/*!< Expander gpio pin enumeration 								*/
    gpio_exp_pin_dir		pin_dir;		/*!< Expander gpio pin I/O selection enumeration 				*/
    gpio_exp_pin_strgth     	pin_strgth;		/*!< Output drive strength enumeration 							*/
}ahw_al_gpio_exp_hdle;

/**
 * @brief This API initializes the gpio pin as per the gpio_cfg_hdl.
 * @param[in] hgpio_arg        : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] ahw_id 		   : application hardware instance ID
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_init(ahw_al_gpio_exp_hdle *hgpio_arg,ahw_inst_id_t ahw_id);

/**
 * @brief This API is used to read the state of the gpio pin
 * @param[in] hgpio_exp    : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin     : pin whose state needs to be read
 * @param[out] pin_state  : state of the gpio pin
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_readpin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate *pin_state);

/**
 * @brief This API is used to write the state of the gpio pin
 * @param[in] hgpio_exp    : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin     : pin whose state needs to be changed
 * @param[in] pin_state   : state of the gpio pin that will be set to the gpio pin
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_writepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate pin_state);

/**
 * @brief This API is used to toggle the state of the gpio pin
 * @param[in] hgpio_exp    : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin     : pin whose state needs to be toggled
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_togglepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin);

/**
 * @brief This API configures the gpio pin to be either input (dir = 0) or
 * output (dir = 1)
 * @param[in] hgpio_exp  : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin   : gpio pin to be configured.
 * @param[in] pin_dir   : direction to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_set_dir(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_dir pin_dir);

/**
 * @brief This API configures the output drive level of the GPIO pin.
 * @param[in] hgpio_exp  : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin   : gpio pin to be configured.
 * @param[in] pin_strength   : strength to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_set_strength(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_strgth pin_strength);

/**
 * @brief This API configures the polarity inversion of pins defined as inputs
 * @param[in] hgpio_exp     : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin      : gpio pin to be configured.
 * @param[in] polarity : polarity to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_set_pol_inv(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pol polarity);

/**
 * @brief This API enables or disables the input latch of the corresponding
 * gpio pin.
 * @param[in] hgpio_exp  : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin   : gpio pin to be configured.
 * @param[in] latch : latch to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_set_input_lat(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_lat latch);

/**
 * @brief This API enables or disables pull-up/pull-down resistors on the
 * corresponding gpio.
 * @param[in] hgpio_exp : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin  : gpio pin to be configured.
 * @param[in] flag : pull enable or disable to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_enable_pull(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pull flag);

/**
 * @brief This API configures the gpio to have pull-up or pull-down resistor by
 * programming the pull-up/pull-down selection register.
 * @param[in] hgpio_exp : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin  : gpio pin to be configured.
 * @param[in] flag : pull up or pull down to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_set_pull_up_dwn(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_up_dwn flag);

/**
 * @brief This API configures the interrupt mask of the corresponding gpio pin
 * Setting the flag to INTRUPT_ENABLE will not mask the interrupt and
 * flag = INTRUPT_DISABLE will mask the interrupt
 * @param[in] hgpio_exp : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin  : gpio pin to be configured.
 * @param[in] flag : Enable or disable the interrupt.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_set_intr_msk(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_mask flag);

/**
 * @brief This API is used to identify the source of an interrupt.
 * state = SOURCE_TRUE indicates that the corresponding input pin
 * was the source of the interrupt.
 * @param[in] hgpio_exp   : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin    : gpio pin to be configured.
 * @param[out] intr_state : interrupt source state of the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_read_intr_sts(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_intrstate *intr_state);

/**
 * @brief This API configures the output port as push-pull or open-drain.
 * @param[in] hgpio_exp : Structure instance of ahw_al_gpio_exp_hdle.
 * @param[in] pin  : gpio pin to be configured.
 * @param[in] flag : sets the gpio pin as PUSH_PULL or OPEN_DRAIN.
 *
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_set_port_cfg(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_port_cfg flag);

#endif /* EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_COMMON_GPIO_EXPANDER_INC_EXO_AHW_AL_GPIO_EXP_COMMON_H_ */

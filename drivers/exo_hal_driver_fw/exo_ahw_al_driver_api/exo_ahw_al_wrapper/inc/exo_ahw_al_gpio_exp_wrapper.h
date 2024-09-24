/**
 * @file exo_ahw_al_gpio_exp_wrapper.h
 *
 * @brief This file has mapping functions for GPIO expander
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

#ifndef _AHW_AL_WRAPPER_H_
#define _AHW_AL_WRAPPER_H_

#define GPIO_EXPANDER_A

#ifdef GPIO_EXPANDER_A
#include "exo_ahw_vdp_gpio_exp_pcal6408a.h"
#endif

/**
 * @brief Mapping API to initialize the GPIO expander
 * @param[in]  hgpio_exp - instance pointer of GPIO expander
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_gpio_exp_common_init(ahw_al_gpio_exp_hdle *hgpio_exp);
/**
 * @brief Mapping API to configure the GPIO
 * @param[in]  hgpio_exp - instance pointer of GPIO expander
 * @param[in]  pin_cfg - GPIO pin num
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_gpio_exp_common_pin_init(ahw_al_gpio_exp_hdle *hgpio_exp,ahw_al_gpio_exp_gpio_cfg* pin_cfg);

/**
 * @brief Mapping API to read the state of the GPIO pin
 * @param[in]  hgpio_exp - instance pointer of GPIO expander
 * @param[in]  pin - GPIO pin num
 * @param[out]  pin_state - state of the pin
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_gpio_exp_common_readpin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate *pin_state);

/**
 * @brief Mapping API to read and write the data from register
 * @param[in]  hgpio_exp - instance pointer of GPIO expander
 * @param[in]  pin - GPIO pin num
 * @param[out]  pin_state - state of the pin
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_gpio_exp_common_self_test(ahw_al_gpio_exp_hdle *hgpio_exp);
/**
 * @brief Mapping API to write the state of the GPIO pin
 * @param[in]  hgpio_exp - instance pointer of GPIO expander
 * @param[in] pin - GPIO pin num
 * @param[in] pin_state - GPIO pin state
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_gpio_exp_common_writepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate pin_state);

/**
 * @brief Mapping API to toggle the state of the GPIO pin
 * @param[in]  hgpio_exp - instance pointer of GPIO expander
 * @param[in]  pin - GPIO pin num
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_gpio_exp_common_togglepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin);

/**
 * @brief Mapping API to set the GPIO direction
 * @param[in]  hgpio_exp - instance pointer of GPIO expander
 * @param[in]  pin - GPIO pin num
 * @param[in]  pin_dir - GPIO pin direction to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_gpio_exp_common_set_dir(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_dir pin_dir);

/**
 * @brief Mapping API configures the output drive level of the GPIO pin.
 * @param[in] hgpio_exp  : Structure instance of gpio_exp_hdl.
 * @param[in] pin   : GPIO pin to be configured.
 * @param[in] pin_strength   : strength to be assigned to the gpio pin.
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_common_set_strength(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_strgth pin_strength);

/**
 * @brief Mapping API configures the polarity inversion of pins defined as
 * inputs.
 * @param[in] hgpio_exp     : Structure instance of gpio_exp_hdl.
 * @param[in] pin      : GPIO pin to be configured.
 * @param[in] polarity : polarity to be assigned to the GPIO pin.
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_common_set_pol_inv(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pol polarity);

/**
 * @brief Mapping API enables or disables pull-up/pull-down resistors on the
 * corresponding GPIO.
 * @param[in] hgpio_exp  : Structure instance of gpio_exp_hdl.
 * @param[in] pin  : GPIO pin to be configured.
 * @param[in] flag : pull enable or disable to be assigned to the GPIO pin.
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_common_enable_pull(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pull flag);

/**
 * @brief Mapping API configures the GPIO to have pull-up or pull-down resistor by
 * programming the pull-up/pull-down selection register.
 * @param[in] hgpio_exp : Structure instance of gpio_exp_hdl.
 * @param[in] pin  : GPIO pin to be configured.
 * @param[in] flag : pull up or pull down to be assigned to the GPIO pin.
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_common_set_pull_up_dwn(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_up_dwn flag);

/**
 * @brief Mapping API is used to identify the source of an interrupt.
 * @param[in] hgpio_exp   : Structure instance of gpio_exp_hdl.
 * @param[in] pin    : GPIO pin to be configured.
 * @param[out] intr_state : interrupt source state of the GPIO pin.
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_common_read_intr_sts(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_intrstate*intr_state);

/**
 * @brief Mapping API configures the output port as push-pull or open-drain.
 * @param[in] hgpio_exp : Structure instance of gpio_exp_hdl.
 * @param[in] pin  : GPIO pin to be configured.
 * @param[in] flag : sets the gpio pin as PUSH_PULL or OPEN_DRAIN.
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_common_set_port_cfg(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_port_cfg flag);

/**
 * @brief Mapping API for Interrupt handler.
 * @param[in] hgpio_exp : Structure instance of gpio_exp_hdl.
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_al_gpio_exp_common_isr_hdlr(ahw_al_gpio_exp_hdle *hgpio_exp);
#endif /* _AHW_AL_WRAPPER_H_ */

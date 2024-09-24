/**
 * @file exo_ahw_vdp_gpio_exp_pcal6408a.h
 *
 * @brief This file contains the vendor driver porting function prototype of GPIO expander
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

#ifndef EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_GPIO_PCAL_6408_INC_EXO_AHW_VDP_GPIO_EXP_PCAL6408A_H_
#define EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_GPIO_PCAL_6408_INC_EXO_AHW_VDP_GPIO_EXP_PCAL6408A_H_

#include "exo_hal_common.h"
#include "exo_ahw_al_gpio_exp_common.h"
#include "exo_io_al_i2c_common.h"

/**
 * @brief This API initializes the gpio pin as per the gpio_cfg_hdl.
 * @param[in] hgpio_exp        : Structure instance of gpio_exp_hdl.
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_init(ahw_al_gpio_exp_hdle *hgpio_exp);

/**
 * @brief This API is used to read the state of the GPIO pin
 * @param[in] hgpio_exp    : Structure instance of pcal6408a_dev.
 * @param[in] pin     : pin whose state needs to be read
 * @param[out] pin_state  : state of the gpio pin
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_readpin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate *pin_state);

/**
 * @brief This API is used to write the state of the GPIO pin
 * @param[in] hgpio_exp    : Structure instance of gpio_exp_hdl.
 * @param[in] pin     : pin whose state needs to be changed
 * @param[in] pin_state   : state of the gpio pin that will be set to the gpio pin
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_writepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate pin_state);

/**
 * @brief This API is used to writes and reads data from register
 * @param[in] hgpio_exp    : Structure instance of gpio_exp_hdl.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */

hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_self_test(ahw_al_gpio_exp_hdle *hgpio_exp);
/**
 * @brief This API is used to toggle the state of the GPIO pin
 * @param[in] hgpio_exp    : Structure instance of gpio_exp_hdl.
 * @param[in] pin     : pin whose state needs to be toggled
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_togglepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin);

/**
 * @brief This API configures the GPIO pin to be either input (dir = 0) or
 * output (dir = 1)
 * @param[in] hgpio_exp  : Structure instance of gpio_exp_hdl.
 * @param[in] pin   : gpio pin to be configured.
 * @param[in] pin_dir   : direction to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_dir(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_dir pin_dir);

/**
 * @brief This API configures the output drive level of the GPIO pin.
 * @param[in] hgpio_exp  : Structure instance of gpio_exp_hdl.
 * @param[in] pin   : gpio pin to be configured.
 * @param[in] pin_strength   : strength to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_strength(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_strgth pin_strength);

/**
 * @brief This API configures the polarity inversion of pins defined as
 * inputs.
 * @param[in] hgpio_exp     : Structure instance of gpio_exp_hdl.
 * @param[in] pin      : gpio pin to be configured.
 * @param[in] polarity : polarity to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_pol_inv(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pol polarity);

/**
 * @brief This API enables or disables the input latch of the corresponding
 * gpio pin.
 * @param[in] hgpio_exp  : Structure instance of gpio_exp_hdl.
 * @param[in] pin   : gpio pin to be configured.
 * @param[in] latch : latch to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_input_lat(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_lat latch);

/**
 * @brief This API enables or disables pull-up/pull-down resistors on the
 * corresponding gpio.
 * @param[in] hgpio_exp  : Structure instance of gpio_exp_hdl.
 * @param[in] pin  : gpio pin to be configured.
 * @param[in] flag : pull enable or disable to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_enable_pull(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pull flag);

/**
 * @brief This API configures the GPIO to have pull-up or pull-down resistor by
 * programming the pull-up/pull-down selection register.
 * @param[in] hgpio_exp : Structure instance of gpio_exp_hdl.
 * @param[in] pin  : gpio pin to be configured.
 * @param[in] flag : pull up or pull down to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_pull_up_dwn(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_up_dwn flag);

/**
 * @brief This API configures the output port as push-pull or open-drain.
 * @param[in] hgpio_exp : Structure instance of gpio_exp_hdl.
 * @param[in] pin  : gpio pin to be configured.
 * @param[in] flag : sets the gpio pin as PUSH_PULL or OPEN_DRAIN.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_port_cfg(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_port_cfg flag);

/**
 * @brief This API for ISR handler.
 * @param[in] hgpio_exp : Structure instance of gpio_exp_hdl.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_isr_hdlr(ahw_al_gpio_exp_hdle *hgpio_exp);

/**
 * @brief This API for GPIO pin configuration.
 * @param[in] hgpio_exp : Structure instance of gpio_exp_hdl.
 * @param[in] gpio_pin : Structure pointer for gpio pin configurations
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_gpio_pin_cfg(ahw_al_gpio_exp_hdle* hgpio_exp, ahw_al_gpio_exp_gpio_cfg* gpio_pin);

#endif /* EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_GPIO_PCAL_6408_INC_EXO_AHW_VDP_GPIO_EXP_PCAL6408A_H_ */

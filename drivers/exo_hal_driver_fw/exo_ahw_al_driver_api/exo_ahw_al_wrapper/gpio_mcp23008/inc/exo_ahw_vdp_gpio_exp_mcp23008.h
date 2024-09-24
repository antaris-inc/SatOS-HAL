/**
 * @file exo_ahw_vdp_gpio_exp_mcp23008.h
 *
 * @brief This file has vendor driver porting function declaration of GPIO expander
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

#include "mcp23008_gpio_expander.h"
#include "exo_hal_common.h"
#include "exo_ahw_al_gpio_exp_common.h"
#include "exo_io_al_i2c_common.h"

#ifndef DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_GPIO_MCP23008_INC_EXO_AHW_VDP_GPIO_EXP_MCP23008_H_
#define DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_GPIO_MCP23008_INC_EXO_AHW_VDP_GPIO_EXP_MCP23008_H_

/**
 * @brief API to initialize the gpio expander MCP23008
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_gpio_exp_mcp23008_init(ahw_al_gpio_exp_hdle *hgpio_exp);

/**
 * @brief API to set the direction
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  gpio_pin - gpio pin num
 * @param[in]  gpio_dir - gpio pin directrion to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_set_direction(ahw_al_gpio_exp_hdle* hgpio_exp, gpio_exp_gpio_pin gpio_pin, gpio_exp_pin_dir gpio_dir);

/**
 * @brief API to read the state of the gpio pin
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  gpio_pin - gpio pin num
 * @param[out]  pin_ste - state of the pin
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_read_pin(ahw_al_gpio_exp_hdle* hgpio_exp, gpio_exp_gpio_pin gpio_pin, gpio_exp_gpio_pinstate* pin_ste);

/**
 * @brief API to read and write data from register
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  gpio_pin - gpio pin num
 * @param[out]  pin_ste - state of the pin
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_self_test(ahw_al_gpio_exp_hdle* hgpio_exp);
/**
 * @brief API to write the state of the gpio pin
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  gpio_pin - gpio pin num
 * @param[in]  gpio_ste - gpio pin state
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_write_pin(ahw_al_gpio_exp_hdle* hgpio_exp, gpio_exp_gpio_pin gpio_pin, gpio_exp_gpio_pinstate gpio_ste);

/**
 * @brief API to toggle the state of the pin
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  gpio_pin - gpio pin num
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_toggle_pin(ahw_al_gpio_exp_hdle* hgpio_exp, gpio_exp_gpio_pin gpio_pin);

/**
 * @brief  API to configure the pin
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  gpio_pin - gpio pin configuration
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_config_pin(ahw_al_gpio_exp_hdle* hgpio_exp, ahw_al_gpio_exp_gpio_cfg* gpio_pin);

/**
 * @brief  API to to enable the pin to pullup mode
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  gpio_pin - gpio pin number
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_pullup_enable(ahw_al_gpio_exp_hdle* hgpio_exp, uint8_t gpio_pin);

/**
 * @brief  API to disable the pullup mode of the pin
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  gpio_pin - gpio pin number
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_pullup_disable(ahw_al_gpio_exp_hdle* hgpio_exp, uint8_t gpio_pin);

/**
 * @brief  API to configure the pin as interrupt
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  gpio_pin - gpio pin number
 * @param[in]  intr_typ - interrupt type to be configured
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_interrupt_cfg(ahw_al_gpio_exp_hdle* hgpio_exp, uint8_t gpio_pin, gpio_exp_mask intr_typ);

/**
 * @brief  API to check the interrupt status
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  intr_sts - interrupt status
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_check_intr_sts(ahw_al_gpio_exp_hdle* hgpio_exp, gpio_exp_gpio_intrstate *intr_sts);

/**
 * @brief  API to clear the interrupt
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_clear_interrupt(ahw_al_gpio_exp_hdle* hgpio_exp);

/**
 * @brief  API to configure the input pin polarity
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @param[in]  polarity - polarity to be configured
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_int_pin_polarity_cfg(ahw_al_gpio_exp_hdle* hgpio_exp,gpio_exp_pin_pol polarity);

/**
 * @brief  This API executes the interrupt callback function
 * @param[in]  hgpio_exp - AHAL instance pointer of gpio expander
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_mcp23008_interrupt_cb(ahw_al_gpio_exp_hdle* hgpio_exp);

#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_GPIO_MCP23008_INC_EXO_AHW_VDP_GPIO_EXP_MCP23008_H_ */

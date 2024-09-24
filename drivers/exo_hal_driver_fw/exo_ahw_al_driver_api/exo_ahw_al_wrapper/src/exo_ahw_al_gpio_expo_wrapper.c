/**
 * @file exo_ahw_al_gpio_expo_wrapper.c
 *
 * @brief This file has mapping functions which resolves the
 * instance Id and invokes the vendor driver api for GPIO expander based on the partnumber
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

#include "exo_ahw_vdp_gpio_exp_pcal6408a.h"
#include "exo_ahw_al_gpio_exp_wrapper.h"
#include "exo_ahw_vdp_gpio_exp_mcp23008.h"

/**
 * @brief Mapping API to initializes the control block memory and do the basic configurations
 */
hal_ret_sts ahw_al_gpio_exp_common_init(ahw_al_gpio_exp_hdle *hgpio_exp)
{
    hal_ret_sts sts;

    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case GPIO_EXPANDER_PCAL6408A_PS:
            sts = ahw_vdp_gpio_exp_pcal6408a_init(hgpio_exp);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
        case GPIO_EXPANDER_MCP23008_GPS:
            sts = ahw_vdp_gpio_exp_mcp23008_init(hgpio_exp);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API is used to read the state of the GPIO pin
 */
hal_ret_sts ahw_al_gpio_exp_common_pin_init(ahw_al_gpio_exp_hdle *hgpio_exp, ahw_al_gpio_exp_gpio_cfg* pin_cfg)
{
    hal_ret_sts sts;

    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts = ahw_vdp_gpio_exp_pcal6408a_gpio_pin_cfg(hgpio_exp, pin_cfg);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = ahw_vdp_mcp23008_config_pin(hgpio_exp,pin_cfg);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API is used to read the state of the GPIO pin
 */
hal_ret_sts ahw_al_gpio_exp_common_readpin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate *pin_state)
{
    hal_ret_sts sts;

    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts = ahw_vdp_gpio_exp_pcal6408a_readpin(hgpio_exp,pin,pin_state);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = ahw_vdp_mcp23008_read_pin(hgpio_exp,pin,pin_state);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API is used to read and write data to register
 */
hal_ret_sts ahw_al_gpio_exp_common_self_test(ahw_al_gpio_exp_hdle *hgpio_exp )
{
    hal_ret_sts sts;

    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts = ahw_vdp_gpio_exp_pcal6408a_self_test(hgpio_exp);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = ahw_vdp_mcp23008_self_test(hgpio_exp);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}
/**
 * @brief Mapping API is used to write the state of the GPIO pin
 */
hal_ret_sts ahw_al_gpio_exp_common_writepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate pin_state)
{
    hal_ret_sts sts;
    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts = ahw_vdp_gpio_exp_pcal6408a_writepin(hgpio_exp,pin,pin_state);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = ahw_vdp_mcp23008_write_pin(hgpio_exp,(uint8_t)pin,pin_state);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API is used to toggle the state of the GPIO pin
 */
hal_ret_sts ahw_al_gpio_exp_common_togglepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin)
{
    hal_ret_sts sts;
    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts = ahw_vdp_gpio_exp_pcal6408a_togglepin(hgpio_exp,pin);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = ahw_vdp_mcp23008_toggle_pin(hgpio_exp,pin);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API configures the GPIO pin to be either input (dir = 0) or
 * output (dir = 1)
 */
hal_ret_sts ahw_al_gpio_exp_common_set_dir(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_dir pin_dir)
{
    hal_ret_sts sts;
    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts = ahw_vdp_gpio_exp_pcal6408a_set_dir(hgpio_exp,pin,pin_dir);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = ahw_vdp_mcp23008_set_direction(hgpio_exp,pin,pin_dir);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API configures the output drive level of the GPIO pin.
 */
hal_ret_sts ahw_al_gpio_exp_common_set_strength(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_strgth pin_strength)
{
    hal_ret_sts sts;
    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts = ahw_vdp_gpio_exp_pcal6408a_set_strength(hgpio_exp,pin,pin_strength);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = HAL_AH_DRIVER_ERR;
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API configures the polarity inversion of pins defined as
 * inputs.
 */
hal_ret_sts ahw_al_gpio_exp_common_set_pol_inv(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pol polarity)
{
    hal_ret_sts sts;
    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts =ahw_vdp_gpio_exp_pcal6408a_set_pol_inv(hgpio_exp,pin,polarity);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = ahw_vdp_mcp23008_int_pin_polarity_cfg(hgpio_exp,polarity);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API enables or disables pull-up/pull-down resistors on the
 * corresponding GPIO.
 */
hal_ret_sts ahw_al_gpio_exp_common_enable_pull(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pull flag)
{
    hal_ret_sts sts;
    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts =ahw_vdp_gpio_exp_pcal6408a_enable_pull(hgpio_exp,pin,flag);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = HAL_AH_DRIVER_ERR;
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API configures the GPIO to have pull-up or pull-down resistor by
 * programming the pull-up/pull-down selection register.
 */
hal_ret_sts ahw_al_gpio_exp_common_set_pull_up_dwn(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_up_dwn flag)
{
    hal_ret_sts sts;
    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts = ahw_vdp_gpio_exp_pcal6408a_set_pull_up_dwn(hgpio_exp,pin,flag);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = HAL_AH_DRIVER_ERR;
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API configures the output port as push-pull or open-drain.
 */
hal_ret_sts ahw_al_gpio_exp_common_set_port_cfg(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_port_cfg flag)
{
    hal_ret_sts sts;
    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            sts = ahw_vdp_gpio_exp_pcal6408a_set_port_cfg(hgpio_exp,pin,flag);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
            sts = HAL_AH_DRIVER_ERR;
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief Mapping API is used to identify the source of an interrupt.
 */
hal_ret_sts ahw_al_gpio_exp_common_read_intr_sts(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_intrstate *intr_state)
{
    hal_ret_sts sts = HAL_IO_VDP_ERR;
    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = ahw_vdp_mcp23008_check_intr_sts(hgpio_exp,intr_state);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}
/**
 * @brief Mapping API for Interrupt handler .
 */
hal_ret_sts ahw_al_gpio_exp_common_isr_hdlr(ahw_al_gpio_exp_hdle *hgpio_exp)
{
    hal_ret_sts sts = HAL_IO_VDP_ERR;
    switch(hgpio_exp->ahw_gen_info.ahw_inst_id)
    {
        case  GPIO_EXPANDER_PCAL6408A_PS:
            ahw_vdp_gpio_exp_pcal6408a_isr_hdlr(hgpio_exp);
            break;
        case GPIO_EXPANDER_MCP23008_EDGE_1:
        case GPIO_EXPANDER_MCP23008_EDGE_2:
        case GPIO_EXPANDER_MCP23008_GPS:
        case GPIO_EXPANDER_MCP23008_OBC_1:
        case GPIO_EXPANDER_MCP23008_OBC_2:
            sts = ahw_vdp_mcp23008_interrupt_cb(hgpio_exp);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @file exo_ahw_al_gpio_exp_common.c
 *
 * @brief This file contains abstracted driver function for gpio expander
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

#include <stdio.h>
#include <stdlib.h>
#include "exo_ahw_al_gpio_exp_common.h"
#include "exo_ahw_al_gpio_exp_wrapper.h"
#include "exo_ah_iob_csn.h"
#include "exo_ahdlsd.h"

extern void* ahw_inst_hdle_ptr[MAX_AH_INST_ID];

/**
 * @brief  Ahw Al GPIO_Expander GPIO Config handle.
 */
gpio_exp_gpio_cfg gpio_cfg_hdl;

/**
 * @brief This API initializes the gpio expander
 */
hal_ret_sts ahw_al_gpio_exp_init(ahw_al_gpio_exp_hdle *hgpio_arg,ahw_inst_id_t ahw_id)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL GPIO EXPANDER Initialize");
#endif
    hal_ret_sts sts;
    hgpio_arg->ahw_gen_info.ahw_inst_id = ahw_id;
    if(HAL_SCS == ahw_al_gpio_exp_common_init(hgpio_arg))
    {
        ahw_inst_hdle_ptr[ahw_id] = hgpio_arg;
        sts = HAL_SCS;
        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_ACTIVATED))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
        if(HAL_SCS != ahiobcsn_updt_ahste(&hgpio_arg->ahw_gen_info, AH_FREE_STATE))
        {
            sts = HAL_AHIOBCSN_FW_ERR;
        }
    }
    else
    {
        sts = HAL_AH_INIT_ERR;
        if(HAL_SCS != ahdlsd_updt_ah_state(ahw_id, AH_ERROR))
        {
            sts = HAL_AHDLSD_FW_ERR;
        }
    }
#ifdef LINUX_TEMP_PORT
    printf("\n EXO AH-AL GPIO EXPANDER Initialization completed successfully");
#endif
    return sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief This API is used to read the state of the gpio pin
 */
hal_ret_sts ahw_al_gpio_exp_readpin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate *pin_state)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_readpin(hgpio_exp,pin,pin_state))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API is used to write the state of the gpio pin
 */
hal_ret_sts ahw_al_gpio_exp_writepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate pin_state)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_writepin(hgpio_exp,pin,pin_state))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API is used to toggle the state of the gpio pin
 */
hal_ret_sts ahw_al_gpio_exp_togglepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_togglepin(hgpio_exp,pin))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API configures the gpio pin to be either input (dir = 0) or
 * output (dir = 1)
 */
hal_ret_sts ahw_al_gpio_exp_set_dir(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_dir pin_dir)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_set_dir(hgpio_exp,pin,pin_dir))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API configures the output drive level of the GPIO pin.
 */
hal_ret_sts ahw_al_gpio_exp_set_strength(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_strgth pin_strength)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_set_strength(hgpio_exp,pin,pin_strength))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API configures the polarity inversion of pins defined as
 * inputs.
 */
hal_ret_sts ahw_al_gpio_exp_set_pol_inv(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pol polarity)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_set_pol_inv(hgpio_exp,pin,polarity))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API enables or disables the input latch of the corresponding
 * gpio pin. This is effective only when the pin is configured as an INPUT
 */
hal_ret_sts ahw_al_gpio_exp_set_input_lat(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_lat latch)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_set_input_lat(hgpio_exp,pin,latch))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API enables or disables pull-up/pull-down resistors on the
 * corresponding gpio.
 */
hal_ret_sts ahw_al_gpio_exp_enable_pull(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pull flag)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_enable_pull(hgpio_exp,pin,flag))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API configures the gpio to have pull-up or pull-down resistor by
 * programming the pull-up/pull-down selection register.
 */
hal_ret_sts ahw_al_gpio_exp_set_pull_up_dwn(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_up_dwn flag)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_set_pull_up_dwn(hgpio_exp,pin,flag))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API configures the interrupt mask of the corresponding gpio pin
 */
hal_ret_sts ahw_al_gpio_exp_set_intr_msk(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_mask flag)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_set_intr_msk(hgpio_exp,pin,flag))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API is used to identify the source of an interrupt.
 */
hal_ret_sts ahw_al_gpio_exp_read_intr_sts(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_intrstate *intr_state)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_read_intr_sts(hgpio_exp,pin,intr_state))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

/**
 * @brief This API configures the output port as push-pull or open-drain.
 */
hal_ret_sts ahw_al_gpio_exp_set_port_cfg(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_port_cfg flag)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&hgpio_exp->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_gpio_exp_common_set_port_cfg(hgpio_exp,pin,flag))
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            ahiobcsn_updt_ahste(&hgpio_exp->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}

#endif


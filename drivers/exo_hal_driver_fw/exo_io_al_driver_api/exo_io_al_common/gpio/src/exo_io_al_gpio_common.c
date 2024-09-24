/**
 * @file exo_io_al_gpio_common.c
 *
 * @brief This file contains function definitions for IOAL GPIO
 * common functions.
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

#include "exo_osal.h"
#include "exo_io_al_gpio_common.h"
#include "exo_ahw_al_gpio_exp_common.h"
#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_common.h"
#ifndef LINUX_TEMP_PORT
#include "exo_io_al_stm32f7xx_gpio.h"
#else
#include "exo_io_al_linux_gpio.h"
#endif


#ifndef LINUX_TEMP_PORT

static ioal_gpio_gen_info *ioal_gpio_inst_hdle_ptr[MC_AVAILABLE_GPIO_PINS]; ///< IOAL GPIO instance handle pointer

/*!
 *  @brief This API receives user input and configure the pin as INTERRUPT
 *  1. call CPU wrapper function to configure pin as interrupt
 *  2. save port, pin and configuration details on gpio_ptr table after successful
 *      configuration of pin as interrupt
 *  3. save callback function and io interface details in external interrupt pointer table
 *
 *  @param[in] gpio_input_config_data : pointer to GPIO input configuration data
 *
 *  @return GPIO status
 */
static gpio_ret_sts gpio_interrupt_config(ioal_gpio_config* gpio_input_config_data);

/*!
 *  @brief This API returns decimal number(o,1,2...) for the input (0x01, 0x02, 0x04, 0x08,,, 0x004)
 *  @param[in] pin_number : PIN number
 *  @param[in] port_details : Port details
 *
 *  @return GPIO status
 */
static gpio_ret_sts gpio_convert_pinnumber_to_portdetails(uint16_t pin_number, gpio_port_details_hdl port_details);

/*!
 *  @brief This API receives user input and configure the pin as INPUT
 *  1. call CPU wrapper function to configure pin as input
 *  2. save port, pin and configuration details on gpio_ptr table after successful
 *      configuration of pin as input
 *  @param[in] gpio_input_config_data : pointer to GPIO input configuration data
 *
 *  @return GPIO status
 */
static gpio_ret_sts gpio_input_config(ioal_gpio_config* gpio_input_config_data);

/*!
 *  @brief This API receives user input and configure the pin as OUTPUT
 *  1. call CPU wrapper function to configure pin as output
 *  2. save port, pin and configuration details on gpio_ptr table after successful
 *      configuration of pin as output
 *  @param[in] gpio_input_config_data : pointer to GPIO input configuration data
 *
 *  @return GPIO status
 */
static gpio_ret_sts gpio_output_config(ioal_gpio_config* gpio_output_config_data);

/*!
 *  @brief This API returns decimal number(o,1,2...) for the input (0x01, 0x02, 0x04, 0x08,,, 0x004)
 */
static gpio_ret_sts gpio_convert_pinnumber_to_portdetails(uint16_t pin_number, gpio_port_details_hdl port_details)
{
    gpio_ret_sts ret = GPIO_OK;
    if((pin_number < 1u) || (pin_number > MC_AVAILABLE_GPIO_PINS))
    {
        ret = GPIO_INVALID;
        port_details->port_name = 0xffffu;
        port_details->port_pin_number = 0xffffu;
    }
    else
    {
        port_details->port_name = (pin_number / MC_PORT_REGISTER_PIN_COUNT);
        port_details->port_pin_number = (pin_number % MC_PORT_REGISTER_PIN_COUNT) ; /* decremented value 1 to start port pin number from P0, P1,,, */
    }
    return ret;
}

/*!
 *  @brief This API receives user input and configure the pin as INPUT
 *  1. call CPU wrapper function to configure pin as input
 *  2. save port, pin and configuration details on gpio_ptr table after successful
 *      configuration of pin as input
 */
static gpio_ret_sts gpio_input_config(ioal_gpio_config* gpio_input_config_data)
{
    gpio_ret_sts ret = GPIO_NOK;
    gpio_config_info config_info;
    ioal_gpio_gen_info *input_cfg_ptr;
    gpio_port_details port_details_temp;
    if(ioal_gpio_inst_hdle_ptr[gpio_input_config_data->pin_number] != NULL)
    {
        // do nothing
    }
    else
    {
        ret = gpio_convert_pinnumber_to_portdetails(gpio_input_config_data->pin_number, &port_details_temp);
        if(ret != GPIO_INVALID)
        {
            /* call stm32 abstraction layer to configure pin as INPUT */
            config_info.port.port_name = port_details_temp.port_name;
            config_info.port.port_pin_number = port_details_temp.port_pin_number;
            config_info.mode = gpio_input_config_data->mode;
            config_info.pull_sts= gpio_input_config_data->pull_sts;
            config_info.speed = gpio_input_config_data->speed;
            ret = io_hal_common_gpio_config(&config_info);
            if(ret != GPIO_OK)
            {
                //don't save configuration
            }
            else
            {
                /* save pin and configuration details on gpio ptr table*/
                input_cfg_ptr = (ioal_gpio_gen_info*) os_malloc(sizeof(ioal_gpio_gen_info));
                input_cfg_ptr->port.port_name = port_details_temp.port_name;
                input_cfg_ptr->port.port_pin_number = port_details_temp.port_pin_number;
                input_cfg_ptr->mode = IOAL_GPIO_INPUT_CFG;
                ioal_gpio_inst_hdle_ptr[gpio_input_config_data->pin_number] = input_cfg_ptr;
            }
        }
    }
    return ret;
}

/*!
 *  @brief This API receives user input and configure the pin as OUTPUT
 *  1. call CPU wrapper function to configure pin as output
 *  2. save port, pin and configuration details on gpio_ptr table after successful
 *      configuration of pin as output
 */
static gpio_ret_sts gpio_output_config(ioal_gpio_config* gpio_output_config_data)
{
    gpio_ret_sts ret = GPIO_NOK;
    gpio_config_info config_info;
    ioal_gpio_gen_info *output_cfg_ptr;

    gpio_port_details port_details_temp;

    if(ioal_gpio_inst_hdle_ptr[gpio_output_config_data->pin_number] != NULL)
    {
        // do nothing
    }
    else
    {
        ret = gpio_convert_pinnumber_to_portdetails(gpio_output_config_data->pin_number, &port_details_temp);

        if(ret != GPIO_INVALID)
        {
            /* call stm32 abstraction layer to configure pin as OUTPUT */
            config_info.port.port_name = port_details_temp.port_name;
            config_info.port.port_pin_number = port_details_temp.port_pin_number;
            config_info.mode = gpio_output_config_data->mode;
            config_info.pull_sts= gpio_output_config_data->pull_sts;
            config_info.speed = gpio_output_config_data->speed;
            ret = io_hal_common_gpio_config(&config_info);
            if(ret != GPIO_OK)
            {
                //don't save configuration
            }
            else
            {
                /* save pin and configuration details on gpio ptr table*/
                output_cfg_ptr = (ioal_gpio_gen_info*) os_malloc(sizeof(ioal_gpio_gen_info));
                output_cfg_ptr->port.port_name = port_details_temp.port_name;
                output_cfg_ptr->port.port_pin_number = port_details_temp.port_pin_number;
                output_cfg_ptr->mode = IOAL_GPIO_OUTPUT_CFG;
                ioal_gpio_inst_hdle_ptr[gpio_output_config_data->pin_number] = output_cfg_ptr;
            }
        }
    }
    return ret;
}


/*!
 *  @brief This API receives user input and configure the pin as INTERRUPT
 *  1. call CPU wrapper function to configure pin as interrupt
 *  2. save port, pin and configuration details on gpio_ptr table after successful
 *      configuration of pin as interrupt
 *  3. save callback function and io interface details in external interrupt pointer table
 */
static gpio_ret_sts gpio_interrupt_config(ioal_gpio_config* gpio_input_config_data)
{
    gpio_ret_sts ret = GPIO_NOK;
    gpio_config_info config_info;
    ioal_gpio_gen_info *input_cfg_ptr;
    exti_handler_details_t *interrupt_iointrf_isr_hdle;

    gpio_port_details port_details_temp;

    if(ioal_gpio_inst_hdle_ptr[gpio_input_config_data->pin_number] != NULL)
    {
        // do nothing
    }
    else
    {
        ret = gpio_convert_pinnumber_to_portdetails(gpio_input_config_data->pin_number, &port_details_temp);
        if(ret != GPIO_INVALID)
        {
            /* call stm32 abstraction layer to configure pin as INTERRUPT */
            config_info.port.port_name = port_details_temp.port_name;
            config_info.port.port_pin_number = port_details_temp.port_pin_number;
            config_info.mode = gpio_input_config_data->mode;
            config_info.pull_sts= gpio_input_config_data->pull_sts;
            config_info.speed = gpio_input_config_data->speed;
            ret = io_hal_common_gpio_interrupt_config(&config_info);
            if(ret != GPIO_OK)
            {
                //don't save configuration
            }
            else
            {
                /* save pin and configuration details on gpio ptr table*/
                input_cfg_ptr = (ioal_gpio_gen_info*) os_malloc(sizeof(ioal_gpio_gen_info));
                input_cfg_ptr->port.port_name = port_details_temp.port_name;
                input_cfg_ptr->port.port_pin_number = port_details_temp.port_pin_number;
                input_cfg_ptr->mode = IOAL_GPIO_INTERRUPT_CFG;
                ioal_gpio_inst_hdle_ptr[gpio_input_config_data->pin_number] = input_cfg_ptr;

                /* save callback func and io_interface handle details on interrupt ptr table*/
                interrupt_iointrf_isr_hdle = (exti_handler_details_t*) os_malloc(sizeof(exti_handler_details_t));
                interrupt_iointrf_isr_hdle->isr_handler =  gpio_input_config_data->external_int.isr_handler;
                interrupt_iointrf_isr_hdle->isr_args = gpio_input_config_data->external_int.isr_args;
                ioal_gpio_exti_io_intf_hdle_ptr[port_details_temp.port_pin_number] = interrupt_iointrf_isr_hdle;
            }
        }
    }
    return ret;
}
#endif

/*!
 *  @brief This API receives user input and determine the user option to configure
 *  the pin as input or output or interrupt
 */
void io_hal_gpio_init(ioal_gpio_config* gpio_cfg)
{
#ifndef LINUX_TEMP_PORT    
    uint8_t hw_id=gpio_cfg->pin_number & 0x000000FF;
    ahw_al_gpio_exp_gpio_cfg pin_cfg;
    gpio_cfg->pin_number = gpio_cfg->pin_number>>8;
    if(hw_id == MCU_ID)
    {
        /* determine the pin configuration such as INPUT/OUTPUT/INTERRUPT */
        if(gpio_cfg->mode == IOAL_GPIO_MODE_INPUT)
        {
            gpio_input_config(gpio_cfg);
        }
        else if((gpio_cfg->mode == IOAL_GPIO_MODE_OUTPUT_PP) || (gpio_cfg->mode == IOAL_GPIO_MODE_OUTPUT_OD))
        {
            gpio_output_config(gpio_cfg);
        }
        else if((gpio_cfg->mode == IOAL_GPIO_MODE_IT_RISING) || (gpio_cfg->mode == IOAL_GPIO_MODE_IT_FALLING) || (gpio_cfg->mode == IOAL_GPIO_MODE_IT_RISING_FALLING))
        {
            gpio_interrupt_config(gpio_cfg);
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        pin_cfg.cb_func=gpio_cfg->external_int.isr_handler;
        pin_cfg.cb_func_args=gpio_cfg->external_int.isr_args;
        pin_cfg.pull_sts=gpio_cfg->pull_sts;
        pin_cfg.pin_num=gpio_cfg->pin_number;
        pin_cfg.mode=gpio_cfg->mode;
        ahw_al_gpio_exp_pin_init(hw_id,&pin_cfg);
    }
#endif
}


/*!
 *  @brief This API drive the requested output pin as LOW/HIGH
 */
void io_hal_gpio_writepin(uint32_t pin_number,uint32_t drive_logic)
{
#ifndef LINUX_TEMP_PORT    
    uint8_t hw_id=pin_number & 0x000000FF;
    pin_number = pin_number>>8;
    if(hw_id == MCU_ID)
    {
        if(ioal_gpio_inst_hdle_ptr[pin_number] != NULL)
        {
            io_hal_common_gpio_write(&ioal_gpio_inst_hdle_ptr[pin_number]->port, drive_logic);
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        ahw_al_gpio_exp_writepin(hw_id,pin_number,drive_logic);
    }
#endif
}

/*!
 *  @brief This API returns the requested input pin state as LOW/HIGH
 */
ioal_gpio_pinstate io_hal_gpio_readpin(uint32_t pin_number)
{
    ioal_gpio_pinstate pin_state = IOAL_INVLD_GPIO_PIN_STE;
#ifndef LINUX_TEMP_PORT
    uint8_t hw_id=pin_number & 0x000000FF;
    pin_number = pin_number>>8;
    if(hw_id == MCU_ID)
    {
        if(ioal_gpio_inst_hdle_ptr[pin_number] != NULL)
        {
            pin_state =  (ioal_gpio_pinstate) io_hal_common_gpio_read(&ioal_gpio_inst_hdle_ptr[pin_number]->port);
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        ahw_al_gpio_exp_readpin(hw_id,pin_number,(gpio_exp_gpio_pinstate*)&pin_state);
    }

#endif
    return pin_state;
}

/*!
 *  @brief This API toggles the requested input pin number
 */
void io_hal_gpio_togglepin(uint32_t pin_number)
{
#ifndef LINUX_TEMP_PORT    
    uint8_t hw_id=pin_number & 0x000000FF;
    pin_number = pin_number>>8;
    if(hw_id == MCU_ID)
    {
        if(ioal_gpio_inst_hdle_ptr[pin_number] != NULL)
        {
            io_hal_common_gpio_toggle(&ioal_gpio_inst_hdle_ptr[pin_number]->port);
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        ahw_al_gpio_exp_togglepin(hw_id,pin_number);
    }
#endif
}

/*!
 *  @brief This API de-init pin number details stored in gpio ptr table
 */
void io_hal_gpio_deinit(uint32_t pin_number)
{
#ifndef LINUX_TEMP_PORT    
    uint16_t temp;
    if(ioal_gpio_inst_hdle_ptr[pin_number] != NULL)
    {
        if(ioal_gpio_inst_hdle_ptr[pin_number]->mode == IOAL_GPIO_INTERRUPT_CFG)
        {
            temp = ioal_gpio_inst_hdle_ptr[pin_number]->port.port_pin_number;
            os_free(ioal_gpio_exti_io_intf_hdle_ptr[temp]);
            ioal_gpio_exti_io_intf_hdle_ptr[temp] = NULL;
        }
        os_free(ioal_gpio_inst_hdle_ptr[pin_number]);
        ioal_gpio_inst_hdle_ptr[pin_number] = NULL;
    }
    else
    {
        //do nothing
    }
#endif
}

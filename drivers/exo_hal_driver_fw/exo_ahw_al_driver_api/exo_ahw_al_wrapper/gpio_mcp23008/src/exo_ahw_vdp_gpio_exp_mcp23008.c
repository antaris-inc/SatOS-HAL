/**
 * @file exo_ahw_vdp_gpio_exp_mcp23008.c
 *
 * @brief This file contains the vendor driver porting function of MCP23008 GPIO expander
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

#include <stdio.h>
#include <unistd.h>
#include "exo_ahw_vdp_gpio_exp_mcp23008.h"
#include "exo_io_al_gpio_common.h"
#include "exo_osal_mem_management.h"
#include "exo_ahw_al_linux_wrpr.h"
#include "exo_common.h"

const uint8_t mcp23008_gpio_mode_lut[IOAL_GPIO_MODE_MAX] = {
		[IOAL_GPIO_MODE_INPUT]=MCP23008_GPIO_MODE_INPUT,
		[IOAL_GPIO_MODE_OUTPUT_PP]=MCP23008_GPIO_MODE_OUTPUT,
		[IOAL_GPIO_MODE_OUTPUT_OD]=MCP23008_GPIO_MODE_OUTPUT,
		[IOAL_GPIO_MODE_IT_RISING]=MCP23008_GPIO_MODE_IT_RISING,
		[IOAL_GPIO_MODE_IT_FALLING]=MCP23008_GPIO_MODE_IT_FALLING,
		[IOAL_GPIO_MODE_IT_RISING_FALLING]=MCP23008_GPIO_MODE_IT_RISING_FALLING,

};
const uint8_t mcp23008_pull_sts_lut[IOAL_PULL_MAX] = {
		[IOAL_GPIO_NOPULL]=MCP23008_PULLUP_DISABLE,
		[IOAL_GPIO_PULLUP]=MCP23008_PULLUP_ENABLE,
		[IOAL_GPIO_PULLDOWN]=MCP23008_PULLUP_MAX,
};
extern ahw_io_map *ahw_io_lookup_tble[MAX_AH_INST_ID];
/**
 * @brief  Instance handle pointer.
 */
extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

int8_t mcp23008_i2c_read(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
int8_t mcp23008_i2c_write(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

#ifndef LINUX_TEMP_PORT
/*!
 *  @brief I2C read hook function for MCP23008 module
 */
int8_t mcp23008_i2c_read(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)(slv_addr), &reg_addr, 1, 500))
    {
        if(HAL_SCS == io_hal_i2c_receive(hi2c, (uint16)(slv_addr), data, len, 500))
        {
            rslt = MCP23008_SCS;
        }
        else
        {
            rslt = MCP23008_COM_ERR;
        }
    }
    else
    {
        rslt = MCP23008_COM_ERR;
    }
    return rslt;
}

/*!
 *  @brief I2C write hook function for MCP23008 module
 */
int8_t mcp23008_i2c_write(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    uint8_t data_array[2];
    int8_t rslt;
    data_array[0]=reg_addr;
    data_array[1]=data[0];

    if(io_hal_i2c_transmit(intf_hdl,slv_addr,data_array,2,500) == HAL_SCS)
    {
        rslt=HAL_SCS;
    }

    return rslt;
}
#endif

/**
 * @brief Initialize the control block memory of gpio expander
 */
hal_ret_sts ahw_vdp_gpio_exp_mcp23008_init(ahw_al_gpio_exp_hdle *hgpio_exp)
{
    hal_ret_sts sts = HAL_MAX_ERR;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO GPIO EXPANDER - AH-Vendor driver porting layer Initialize");
    printf("\n EXO GPIO EXPANDER - AH-Vendor driver Initialize");
    printf("\n EXO GPIO EXPANDER - AH-Vendor driver Initialization completed successfully ");
    usleep(100000);
    printf("\n EXO GPIO EXPANDER - AH-Vendor driver porting layer initialization completed successfully");

#else
    s_mcp23008* hge=(s_mcp23008*)os_malloc(sizeof(s_mcp23008));
    hge->write = mcp23008_i2c_write;
    hge->read =  mcp23008_i2c_read;
    hge->intf_hdl = intf_inst_hdle_ptr[ahw_io_lookup_tble[hgpio_exp->ahw_gen_info.ahw_inst_id]->io_instance_id];
    hge->slv_addr=ahw_io_lookup_tble[hgpio_exp->ahw_gen_info.ahw_inst_id]->slv_addr;

    hgpio_exp->ahw_gen_info.vdp_inst_hdle =(void*)hge;
    hgpio_exp->ahw_gen_info.io_intf_hdle=hge->intf_hdl;
    hgpio_exp->ahw_gen_info.slave_address=hge->slv_addr;
    sts = HAL_SCS;
#endif
    return sts;
}

/*!
 *  @brief This API set the IO direction of the GPIO pin
 */
hal_ret_sts ahw_vdp_mcp23008_set_direction(ahw_al_gpio_exp_hdle* hgpio_exp, gpio_exp_gpio_pin gpio_pin, gpio_exp_pin_dir gpio_dir)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp23008_set_direction(gpio_hdl_vdp,(uint8_t)gpio_pin,(e_gpio_dir)gpio_dir))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API read the state of the GPIO pin
 */
hal_ret_sts ahw_vdp_mcp23008_read_pin(ahw_al_gpio_exp_hdle* hgpio_exp, gpio_exp_gpio_pin gpio_pin, gpio_exp_gpio_pinstate* pin_ste)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    *pin_ste = mcp23008_read_pin(gpio_hdl_vdp,(e_gpio_num)gpio_pin);
    if(*pin_ste  < GPIO_EXP_PIN_MAX )
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API writes and read data from register to validate GPIO EXPENDER.
 */
hal_ret_sts ahw_vdp_mcp23008_self_test(ahw_al_gpio_exp_hdle* hgpio_exp)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    sts = mcp23008_self_test(gpio_hdl_vdp);
    if(sts == HAL_SCS)
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API write the state of the GPIO pin
 */
hal_ret_sts ahw_vdp_mcp23008_write_pin(ahw_al_gpio_exp_hdle* hgpio_exp, gpio_exp_gpio_pin gpio_pin, gpio_exp_gpio_pinstate gpio_ste)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp23008_write_pin(gpio_hdl_vdp,(uint8_t)gpio_pin,(e_gpio_pin_ste)gpio_ste))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API toggle the state of GPIO pin
 */
hal_ret_sts ahw_vdp_mcp23008_toggle_pin(ahw_al_gpio_exp_hdle* hgpio_exp, gpio_exp_gpio_pin gpio_pin)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp23008_toggle_pin(gpio_hdl_vdp,(uint8_t)gpio_pin))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API configure the GPIO pin
 */
hal_ret_sts ahw_vdp_mcp23008_config_pin(ahw_al_gpio_exp_hdle* hgpio_exp, ahw_al_gpio_exp_gpio_cfg* gpio_pin)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    s_gpio_config gpio_cfg;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    gpio_cfg.gpio_bit_msk = gpio_pin->pin_num;
	gpio_cfg.pull_up_sts = mcp23008_pull_sts_lut[gpio_pin->pull_sts];
	gpio_cfg.cb_func = gpio_pin->cb_func;
	gpio_cfg.mode = mcp23008_gpio_mode_lut[gpio_pin->mode];
	gpio_cfg.cb_func_args=gpio_pin->cb_func_args;
    if(HAL_SCS == (hal_ret_sts)mcp23008_config_pin(gpio_hdl_vdp,&gpio_cfg))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API enable the pullup mode to the GPIO pin
 */
hal_ret_sts ahw_vdp_mcp23008_pullup_enable(ahw_al_gpio_exp_hdle* hgpio_exp, uint8_t gpio_pin)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp23008_pullup_enable(gpio_hdl_vdp,gpio_pin))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API disable the pullup mode of the GPIO pin
 */
hal_ret_sts ahw_vdp_mcp23008_pullup_disable(ahw_al_gpio_exp_hdle* hgpio_exp, uint8_t gpio_pin)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp23008_pullup_disable(gpio_hdl_vdp,gpio_pin))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API configure interrupt to the GPIO pin
 */
hal_ret_sts ahw_vdp_mcp23008_interrupt_cfg(ahw_al_gpio_exp_hdle* hgpio_exp, uint8_t gpio_pin, gpio_exp_mask intr_typ)//
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp23008_interrupt_cfg(gpio_hdl_vdp,gpio_pin,(e_gpio_intr_typ)intr_typ))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API check the interrupt status of the GPIO pin
 */
hal_ret_sts ahw_vdp_mcp23008_check_intr_sts(ahw_al_gpio_exp_hdle* hgpio_exp, gpio_exp_gpio_intrstate *intr_sts)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp23008_check_intr_sts(gpio_hdl_vdp,(uint8_t*)intr_sts))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API clear the interrupt
 */
hal_ret_sts ahw_vdp_mcp23008_clear_interrupt(ahw_al_gpio_exp_hdle* hgpio_exp)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp23008_clear_interrupt(gpio_hdl_vdp))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API configure the input pin polarity
 */
hal_ret_sts ahw_vdp_mcp23008_int_pin_polarity_cfg(ahw_al_gpio_exp_hdle* hgpio_exp,gpio_exp_pin_pol polarity)
{
    hal_ret_sts sts;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp23008_int_pin_polarity_cfg(gpio_hdl_vdp,(e_int_pin_plrty)polarity))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/*!
 *  @brief This API executes the interrupt callback function
 */
hal_ret_sts ahw_vdp_mcp23008_interrupt_cb(ahw_al_gpio_exp_hdle* hgpio_exp)
{
    hal_ret_sts sts=HAL_AH_DRIVER_ERR;
    uint8_t intr_flg,pin=0;
    s_mcp23008 *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)mcp23008_check_intr_sts(gpio_hdl_vdp,&intr_flg))
    {
        while(intr_flg)
        {
           if((intr_flg & 0x01) == 0x01)
           {
        	   if(gpio_hdl_vdp->callback_func_info[pin].callback_func != NULL)
        	   {
        	   gpio_hdl_vdp->callback_func_info[pin].callback_func(gpio_hdl_vdp->callback_func_info[pin].cb_func_args);
        	   sts=HAL_SCS;
        	   }
        	   else
        	   {
        		   sts=HAL_AH_DRIVER_ERR;
        	   }
           }
           intr_flg=intr_flg>>1;
           pin++;
        }
    	mcp23008_clear_interrupt(gpio_hdl_vdp);
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

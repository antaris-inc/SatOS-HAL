/**
 * @file mcp23008_gpio_expander.c
 *
 * @brief This file contains driver function of GPIO expander MCP23008
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

#include "mcp23008_gpio_expander.h"

/*!
 * @brief This API is used to check null pointer
 */
static e_mcp23008_err mcp23008_null_ptr_check(const s_mcp23008* dev)
{
    e_mcp23008_err ret;
    if ((dev == NULL) || (dev->read == NULL) || (dev->write == NULL))
    {
        ret = MCP23008_NULL_PTR;
    }
    else
    {

        ret = MCP23008_SCS;
    }
    return ret;
}

/*!
 * @brief This function is used to set the GPIO direction
 */
e_mcp23008_err mcp23008_set_direction(s_mcp23008* mcp23008_hdl, uint8_t gpio_pin, e_gpio_dir gpio_dir)
{
    e_mcp23008_err ret= MCP23008_ERR;
    uint8_t data;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS)
    {
        if(gpio_pin <= MCP23008_GPIO_MAX && gpio_dir < MCP23008_GPIO_DIR_MAX)
        {
            if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,IODIR,&data,1)==MCP23008_SCS)
            {
                if(gpio_dir==MCP23008_GPIO_INPUT)
                {

                    data = data | gpio_pin;
                }
                else
                {
                    data= data & (~gpio_pin);
                }
                ret= mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,IODIR,&data,1);
            }
            else
            {
                ret = MCP23008_COM_ERR;
            }
        }
        else
        {
            ret = MCP23008_INVLD_ARG;
        }
    }
    else
    {
        ret = MCP23008_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This function is used to read the GPIO
 */
e_gpio_pin_ste mcp23008_read_pin(s_mcp23008* mcp23008_hdl, e_gpio_num gpio_pin)
{
    e_gpio_pin_ste gpio_ste=MCP23008_GPIO_STE_MAX;
    uint8_t data;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS)
    {
        if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPIO_PORT,&data,1) == MCP23008_SCS)
        {
            data = (data & gpio_pin);

            if(data>0)
            {
                gpio_ste = MCP23008_GPIO_HIGH;
            }
            else
            {
                gpio_ste = MCP23008_GPIO_LOW;
            }
        }
    }
    return gpio_ste;
}

/*!
 * @brief This function is used to write the GPIO with specified state
 */
e_mcp23008_err mcp23008_write_pin(s_mcp23008* mcp23008_hdl, uint8_t gpio_pin, e_gpio_pin_ste gpio_ste)
{
    e_mcp23008_err ret= MCP23008_ERR;
    uint8_t data;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS)
    {
        if(gpio_pin <= MCP23008_GPIO_MAX && gpio_ste < MCP23008_GPIO_STE_MAX)
        {
            if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPIO_PORT,&data,1)==MCP23008_SCS)
            {
                if(gpio_ste==MCP23008_GPIO_HIGH)
                {
                    data = data | gpio_pin;
                }
                else
                {
                    data= data & (~gpio_pin);
                }
                ret= mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPIO_PORT,&data,1);
            }
            else
            {
                ret = MCP23008_COM_ERR;
            }
        }
        else
        {
            ret = MCP23008_INVLD_ARG;
        }
    }
    else
    {
        ret = MCP23008_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This function is used to toggle the GPIO
 */
e_mcp23008_err mcp23008_toggle_pin(s_mcp23008* mcp23008_hdl, uint8_t gpio_pin)
{
    e_mcp23008_err ret= MCP23008_ERR;
    uint8_t data;
    uint8_t mask=0x01;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS)
    {
        if(gpio_pin <= MCP23008_GPIO_MAX)
        {
            if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPIO_PORT,&data,1) == MCP23008_SCS)
            {
                data = data >> gpio_pin;
                data = data & 0x01;
                data = !data;

                if(data==MCP23008_GPIO_HIGH)
                {
                    mask = mask << gpio_pin;
                    data = data | mask;
                }
                else
                {
                    mask = mask << gpio_pin;
                    mask = ~mask;
                    data= data & mask;
                }
                ret= mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPIO_PORT,&data,1);
            }
            else
            {
                ret=MCP23008_COM_ERR ;
            }
        }
        else
        {
            ret=MCP23008_INVLD_ARG;
        }
    }
    else
    {
        ret=MCP23008_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This function is used to configure the pin
 */
e_mcp23008_err mcp23008_config_pin(s_mcp23008* mcp23008_hdl, s_gpio_config* gpio_pin)
{
    e_mcp23008_err ret= MCP23008_ERR;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS && gpio_pin != NULL)
    {
        ret = mcp23008_set_direction (mcp23008_hdl,gpio_pin->gpio_bit_msk,gpio_pin->gpio_dir);
        if(gpio_pin->gpio_dir==MCP23008_GPIO_OUTPUT)
        {
            ret = mcp23008_write_pin(mcp23008_hdl,gpio_pin->gpio_bit_msk,gpio_pin->gpio_state);
        }
        else
        {
            ret = mcp23008_interrupt_cfg(mcp23008_hdl,gpio_pin->gpio_bit_msk, gpio_pin->intr_type);
            if(gpio_pin->pull_up_sts==MCP23008_PULLUP_ENABLE)
            {
                ret = mcp23008_pullup_enable (mcp23008_hdl,gpio_pin->gpio_bit_msk);
            }
            else
            {
                ret = mcp23008_pullup_disable (mcp23008_hdl,gpio_pin->gpio_bit_msk);
            }
        }
    }
    else
    {
        ret = MCP23008_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This function is used for enable pullup configuration
 */
e_mcp23008_err mcp23008_pullup_enable(s_mcp23008* mcp23008_hdl, uint8_t gpio_pin)
{
    e_mcp23008_err ret= MCP23008_ERR;
    uint8_t data;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS)
    {
        if(gpio_pin <= MCP23008_GPIO_MAX )
        {
            if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPPU,&data,1) == MCP23008_SCS)
            {
                data = data | gpio_pin;
            }
            else
            {
                ret=MCP23008_COM_ERR;
            }
            ret=mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPPU,&data,1);
        }
        else
        {
            ret=MCP23008_INVLD_ARG;
        }
    }
    else
    {
        ret=MCP23008_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This function is used for disable pullup configuration
 */
e_mcp23008_err mcp23008_pullup_disable(s_mcp23008* mcp23008_hdl, uint8_t gpio_pin)
{
    e_mcp23008_err ret= MCP23008_ERR;
    uint8_t data;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS)
    {
        if(gpio_pin <= MCP23008_GPIO_MAX)
        {
            if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPPU,&data,1) == MCP23008_SCS)
            {
                data= data & (~gpio_pin);
            }
            else
            {
                ret=MCP23008_COM_ERR;
            }
            ret=mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPPU,&data,1);
        }
        else
        {
            ret=MCP23008_INVLD_ARG;
        }
    }
    else
    {
        ret=MCP23008_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This function configure the interrupt
 */
e_mcp23008_err mcp23008_interrupt_cfg(s_mcp23008* mcp23008_hdl, uint8_t gpio_pin, e_gpio_intr_typ intr_typ)
{
    e_mcp23008_err ret= MCP23008_COM_ERR;
    uint8_t data;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS)
    {
        if(gpio_pin <= MCP23008_GPIO_MAX && intr_typ < MCP23008_GPIO_INTR_MAX)
        {
            if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPINTEN,&data,1) == MCP23008_SCS)
            {
                switch(intr_typ)
                {
                    case MCP23008_GPIO_INTR_DISABLE:
                        data= data & (~gpio_pin);
                        ret=mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPINTEN,&data,1);
                        break;

                    case MCP23008_GPIO_INTR_PIN_CHANGE:
                        data = data | gpio_pin;
                        if(mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPINTEN,&data,1) == MCP23008_SCS)
                        {
                            if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,INTCON,&data,1) == MCP23008_SCS)
                            {
                                data= data & (~gpio_pin);
                                ret=mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,INTCON,&data,1);
                            }
                        }
                        break;

                    case MCP23008_GPIO_INTR_RISING:
                        data = data | gpio_pin;
                        if(mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPINTEN,&data,1) == MCP23008_SCS)
                        {
                            if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,INTCON,&data,1) == MCP23008_SCS)
                            {
                                data = data | gpio_pin;
                                if(mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,INTCON,&data,1) == MCP23008_SCS)
                                {
                                    if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,DEFVAL,&data,1) == MCP23008_SCS)
                                    {
                                        data = data | gpio_pin;
                                        ret=mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,DEFVAL,&data,1);
                                    }
                                }
                            }
                        }
                        break;

                    case MCP23008_GPIO_INTR_FALLING:
                        data = data | gpio_pin;
                        if(mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,GPINTEN,&data,1) == MCP23008_SCS)
                        {
                            if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,INTCON,&data,1) == MCP23008_SCS)
                            {
                                data = data | gpio_pin;
                                if(mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,INTCON,&data,1) == MCP23008_SCS)
                                {
                                    if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,DEFVAL,&data,1) == MCP23008_SCS)
                                    {
                                        data= data & (~gpio_pin);
                                        ret=mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,DEFVAL,&data,1);
                                    }
                                }
                            }
                        }
                        break;

                    default:
                        break;
                }
            }
            else
            {
                ret=MCP23008_INVLD_ARG;
            }
        }
    }
    else
    {
        ret=MCP23008_NULL_PTR;
    }
    return ret;
}

/*!
 *   @brief This function is used to check the interrupt status
 */
e_mcp23008_err mcp23008_check_intr_sts(s_mcp23008* mcp23008_hdl, uint8_t* intr_sts)
{
    e_mcp23008_err ret= MCP23008_ERR;
    uint8_t data;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS)
    {
        if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,INTF,&data,1) == MCP23008_SCS)
        {
            *intr_sts = data;
            ret =  MCP23008_SCS;
        }
        else
        {
            ret = MCP23008_COM_ERR;
        }
    }
    else
    {
        ret = MCP23008_NULL_PTR;
    }
    return ret;
}

/*!
 *   @brief This function is used to check the interrupt status
 */
e_mcp23008_err mcp23008_clear_interrupt(s_mcp23008* mcp23008_hdl)
{
    e_mcp23008_err ret= MCP23008_ERR;
    uint8_t data;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS)
    {
        if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,INTCAP,&data,1) == MCP23008_SCS)
        {
            ret =  MCP23008_SCS;
        }
        else
        {
            ret = MCP23008_COM_ERR;
        }
    }
    else
    {
        ret = MCP23008_NULL_PTR;
    }
    return ret;
}

/*!
 * @brief This function is used to set the interrupt polarity
 */
e_mcp23008_err mcp23008_int_pin_polarity_cfg(s_mcp23008* mcp23008_hdl,e_int_pin_plrty polarity)
{
    e_mcp23008_err ret= MCP23008_ERR;
    uint8_t data;
    if(mcp23008_null_ptr_check(mcp23008_hdl)==MCP23008_SCS)
    {
        if(polarity<MCP23008_INT_PLRTY_MAX)
        {
            if(mcp23008_hdl->read(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,IOCON,&data,1) == MCP23008_SCS)
            {
                if(polarity == MCP23008_INT_HIGH_IMPEDANCE)
                {
                    data = (data & 0xFB) | 0x04 ;
                }
                else if (polarity == MCP23008_INT_ACT_HIGH)
                {
                    data = (data & 0xF9) | 0x02 ;
                }
                else
                {
                    data = (data & 0xF9);
                }
                ret= mcp23008_hdl->write(mcp23008_hdl->intf_hdl, mcp23008_hdl->slv_addr,IOCON,&data,1);
            }
        }
        else
        {
            ret = MCP23008_INVLD_ARG;
        }
    }
    else
    {
        ret=MCP23008_NULL_PTR;
    }
    return ret;
}



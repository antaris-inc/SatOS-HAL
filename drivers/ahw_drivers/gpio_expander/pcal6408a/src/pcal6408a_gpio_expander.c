/**
 * @file pcal6408a_gpio_expander.c
 *
 * @brief This file contains functions that drives the PCAL6408A GPIO expander
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

#include "pcal6408a_gpio_expander.h"


/* Static function declarations */

/*!
 * @brief This utility API is used to set or reset a bit in the data
 * @param[in] data  : Data whose bit needs to be set or reset
 * @param[in] pin   : bit position.
 * @param[in] flag  : set or reset
 * @return data after the required bit is set or reset
 * @retval data after the required bit is set or reset
 */
static uint8_t bit_write (uint8_t data, pcal6408a_gpio_pin pin, uint8_t flag);

/*!
 * @brief This utility API is used to check the validity of the gpio pin number
 * @param[in] pin  : pin number that needs to validated.
 * @return Result of pin number validation
 * @retval PCAL6408A_OK -> Success / -PCAL6408A_E_OUT_OF_RANGE -> Error.
 */
static int8_t is_gpio_valid (pcal6408a_gpio_pin pin);

/*********************** User function definitions ****************************/

/**
 * @brief This API initializes the gpio pin as per the gpio_config. This api
 * needs to be called for all the gpio expander pins.
 */
int8_t pcal6408a_gpio_init(pcal6408a_dev *hdev)
{
    int8_t rslt;

    if(hdev == NULL)
    {
        rslt = PCAL6408A_E_NULL_PTR;
    }
    else
    {
        rslt=PCAL6408A_OK;
    }
    return rslt;
}
/**
 * @brief This API is used to read the pcal6408a registers and writes data to it ,to validate GPIO expender
 */
int8_t pcal6408a_self_test(pcal6408a_dev *hdev)
{
    int8_t sts=PCAL6408A_E_COM_FAIL;
    uint8_t data;
    uint8_t write_data =0x41;
    uint8_t read_data =0;
    sts = pcal6408a_read(hdev,PCAL6408_REG_INPUT_LATCH, &data,2);
    if(sts ==PCAL6408A_OK)
    {
        pcal6408a_write(hdev,PCAL6408_REG_INPUT_LATCH ,&write_data, 1);
        pcal6408a_read(hdev, PCAL6408_REG_INPUT_LATCH, &read_data, 1);
    }
    if(write_data==read_data)
    {
        sts= PCAL6408A_OK;
    }
    else
    {
        sts=PCAL6408A_E_COM_FAIL;
    }
    pcal6408a_write(hdev, PCAL6408_REG_INPUT_LATCH, &data, 1);
    return sts ;
}
/**
 * @brief This API is used to read the pcal6408a registers through i2c interface
 */
int8_t pcal6408a_read(pcal6408a_dev *hdev, uint8_t reg, uint8_t *data, uint16_t len)
{
    int8_t rslt = PCAL6408A_OK;

    if ((hdev == NULL) || (hdev->read == NULL))
    {
        rslt = PCAL6408A_E_NULL_PTR;
    }
    else if (len == 0)
    {
        rslt = PCAL6408A_E_READ_WRITE_LENGTH_INVALID;
    }
    else
    {

        rslt = hdev->read(hdev->io_intf_hdle, hdev->slave_addr, reg, data, len);
    }

    return rslt;
}

/**
 * @brief This API is used to write the pcal6408a registers through i2c
 * interface
 */
int8_t pcal6408a_write(pcal6408a_dev *hdev, uint8_t reg, uint8_t *data, uint16_t len)
{
    int8_t rslt = PCAL6408A_OK;

    if ((hdev == NULL) || (hdev->read == NULL))
    {
        rslt = PCAL6408A_E_NULL_PTR;
    }
    else if (len == 0)
    {
        rslt = PCAL6408A_E_READ_WRITE_LENGTH_INVALID;
    }
    else
    {
        rslt = hdev->write(hdev->io_intf_hdle, hdev->slave_addr, reg, data, len);
    }

    return rslt;
}

/**
 * @brief This API is used to read the state of the gpio pin
 */
int8_t pcal6408a_readpin(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_gpio_pinstate *state)
{
    uint8_t data;
    int8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        if(pcal6408a_get_input_latch(hdev, pin)== LATCH)
        {
            pcal6408a_set_input_latch(hdev, pin, NO_LATCH);
            status = pcal6408a_read(hdev, PCAL6408_REG_INPUT, &data, 1);
            pcal6408a_set_input_latch(hdev, pin, LATCH);
        }
        if (PCAL6408A_OK == status)
        {
            data = (data & pin);
            if(data>0)
            {
                *state  = PIN_SET;
            }
            else
            {
                *state  = PIN_RESET;
            }
        }
        else
        {

        }
    }

    return status;
}

/**
 * @brief This API is used to write the state of the gpio pin
 */
int8_t pcal6408a_writepin(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_gpio_pinstate state)
{
    uint8_t data;
    int8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        status = pcal6408a_read(hdev, PCAL6408_REG_OUTPUT, &data, 1);
        if (PCAL6408A_OK == status)
        {
            data = bit_write(data, pin, state);
            status = pcal6408a_write(hdev, PCAL6408_REG_OUTPUT, &data, 1);
        }
        else
        {

        }
    }
    return status;
}

/**
 * @brief This API is used to toggle the state of the gpio pin
 */
int8_t pcal6408a_togglepin(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin)
{
    uint8_t data;
    int8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        status = pcal6408a_read(hdev, PCAL6408_REG_OUTPUT, &data, 1);
        if (PCAL6408A_OK == status)
        {
            data = (data ^ (1 << pin));
            status = pcal6408a_write(hdev, PCAL6408_REG_OUTPUT, &data, 1);
        }
        else
        {

        }
    }
    return status;
}

/**
 * @brief This API configures the gpio pin to be either input (dir = 0) or
 * output (dir = 1)
 */
int8_t pcal6408a_set_dir(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_dir dir)
{
    uint8_t data;
    int8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        status = pcal6408a_read(hdev, PCAL6408_REG_CONFIG, &data, 1);
        if (PCAL6408A_OK == status)
        {
            data = bit_write(data, pin, dir);
            status = pcal6408a_write(hdev, PCAL6408_REG_CONFIG, &data, 1);
        }
        else
        {

        }
    }

    return status;
}

/**
 * @brief This API configures the output drive level of the GPIO pin.
 */
int8_t pcal6408a_set_strength(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_strgth strength)
{
    uint8_t data;
    int8_t status;
    uint8_t mask = PCAL6408_REG_OUT_STRENGTH_MASK;

    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        if(pin > PCAL6408A_GPIO_3)
        {
            status = pcal6408a_read(hdev, PCAL6408_REG_OUT_STRENGTH1, &data, 1);
        }
        else
        {
            status = pcal6408a_read(hdev, PCAL6408_REG_OUT_STRENGTH0, &data, 1);
        }

        if (PCAL6408A_OK == status)
        {
            if(pin > PCAL6408A_GPIO_3)
            {
                mask = (mask << ((pin-4)*2));
                data = ((data & ~mask) | (strength << ((pin-4)*2)));
                status = pcal6408a_write(hdev, PCAL6408_REG_OUT_STRENGTH1, &data, 1);
            }
            else
            {
                mask = (mask << (pin*2));
                data = ((data & ~mask) | (strength << (pin*2)));
                status = pcal6408a_write(hdev, PCAL6408_REG_OUT_STRENGTH0, &data, 1);
            }
        }
        else
        {

        }
    }
    return status;
}

/**
 * @brief This API configures the polarity inversion of pins defined as 
 * inputs.
 */
int8_t pcal6408a_set_pol_inv(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_pol polarity)
{
    uint8_t data;
    int8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        status = pcal6408a_read(hdev, PCAL6408_REG_POLARITY_INVERSION, &data, 1);
    }

    if (PCAL6408A_OK == status)
    {
        data = bit_write(data, pin, polarity);
        status = pcal6408a_write(hdev, PCAL6408_REG_POLARITY_INVERSION, &data, 1);
    }
    else
    {

    }

    return status;
}

/**
 * @brief This API enables or disables the input latch of the corresponding 
 * gpio pin. This is effective only when the pin is configured as an INPUT
 */
int8_t pcal6408a_set_input_latch(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_lat latch)
{
    uint8_t data;
    int8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        status = pcal6408a_read(hdev, PCAL6408_REG_INPUT_LATCH, &data, 1);
    }

    if (PCAL6408A_OK == status)
    {
        data = bit_write(data, pin, latch);
        status = pcal6408a_write(hdev, PCAL6408_REG_INPUT_LATCH, &data, 1);
    }
    else
    {

    }

    return status;
}

/**
 * @brief This API enables or disables the input latch of the corresponding
 * gpio pin. This is effective only when the pin is configured as an INPUT
 */
pcal6408a_pin_lat pcal6408a_get_input_latch(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin)
{
    uint8_t data = 0;
    uint8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        status = pcal6408a_read(hdev,PCAL6408_REG_INPUT_LATCH,&data,1);
        data = pin & data;
        if(data>0)
        {
            status = LATCH;
        }
        else
        {
            status = NO_LATCH;
        }
    }

    return status;
}

/**
 * @brief This API enables or disables pull-up/pull-down resistors on the
 * corresponding gpio.
 */
int8_t pcal6408a_enable_pull(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_pull flag)
{
    uint8_t data;
    int8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        status = pcal6408a_read(hdev, PCAL6408_REG_PULL_ENABLE, &data, 1);
        if (PCAL6408A_OK == status)
        {
            data = bit_write(data, pin, flag);
            status = pcal6408a_write(hdev, PCAL6408_REG_PULL_ENABLE, &data, 1);
        }
        else
        {

        }
    }

    return status;
}

/**
 * @brief This API configures the gpio to have pull-up or pull-down resistor by
 * programming the pull-up/pull-down selection register.
 */
int8_t pcal6408a_set_pull_up_dwn(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_up_dwn flag)
{
    uint8_t data;
    int8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        if(flag==NO_PULL)
        {
            pcal6408a_enable_pull(hdev,pin,PULL_DISABLED);
        }
        else
        {
            pcal6408a_enable_pull(hdev,pin,PULL_ENABLED);
            status = pcal6408a_read(hdev, PCAL6408_REG_PULL_UP_DOWN, &data, 1);
            if (PCAL6408A_OK == status)
            {
                data = bit_write(data, pin, flag);
                status = pcal6408a_write(hdev, PCAL6408_REG_PULL_UP_DOWN, &data, 1);
            }
            else
            {

            }
        }
    }

    return status;
}

/**
 * @brief This API configures the interrupt mask of the corresponding gpio pin
 */
int8_t pcal6408a_intr_config(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_intr_mode intr_mode)
{
    uint8_t data;
    int8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        if(intr_mode<INTRUPT_DISABLE)
        {
            status = pcal6408a_read(hdev, PCAL6408_REG_INT_MASK, &data, 1);
            if (PCAL6408A_OK == status)
            {
                data = bit_write(data,pin,0);
                status = pcal6408a_write(hdev, PCAL6408_REG_INT_MASK, &data, 1);
                pcal6408a_set_input_latch(hdev, pin, LATCH);
            }
        }
    }
    return status;
}

/**
 * @brief This API is used to identify the source of an interrupt.
 */
int8_t pcal6408a_read_intr_sts(pcal6408a_dev *hdev,uint8_t* intr_flg)
{
    int8_t status=PCAL6408A_E_COM_FAIL;
    status = pcal6408a_read(hdev, PCAL6408_REG_INT_STATUS, intr_flg, 1);
    return status;
}

/**
 * @brief This API configures the output port as push-pull or open-drain.
 */
int8_t pcal6408a_set_port_cfg(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_port_cfg flag)
{
    uint8_t data;
    int8_t status;
    status = is_gpio_valid(pin);
    if (PCAL6408A_OK != status)
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        status = pcal6408a_read(hdev, PCAL6408_REG_OUT_CONFIG, &data, 1);
        if (PCAL6408A_OK == status)
        {
            data = bit_write(data, pin, flag);
            status = pcal6408a_write(hdev, PCAL6408_REG_OUT_CONFIG, &data, 1);
        }
        else
        {

        }
    }

    return status;
}

/**
 * @brief This API is used to get the configurations parameters of the gpio pin.
 */
int8_t pcal6408a_gpio_pin_cfg(pcal6408a_dev *hdev, pcal6408a_gpio_cfg *gpio_config)
{
    int8_t status;
    uint8_t gpio_bit_msk,pin=0;
    if(NULL == gpio_config || NULL == hdev)
    {
        status = PCAL6408A_E_NULL_PTR;
    }
    else
    {
        switch(gpio_config->mode)
        {
            case PCAL6408A_GPIO_MODE_INPUT:
            {
                status = pcal6408a_set_dir(hdev,gpio_config->pin_num,INPUT);
                break;
            }
            case PCAL6408A_GPIO_MODE_OUTPUT:
            {
                status = pcal6408a_set_dir(hdev,gpio_config->pin_num,OUTPUT);
                break;
            }
            case PCAL6408A_GPIO_MODE_IT_RISING:
            {
                status = pcal6408a_set_dir(hdev,gpio_config->pin_num,INPUT);
                status = pcal6408a_intr_config(hdev,gpio_config->pin_num,INTRUPT_RISING);
                break;
            }
            case PCAL6408A_GPIO_MODE_IT_FALLING:
            {
                status = pcal6408a_set_dir(hdev,gpio_config->pin_num,INPUT);
                status = pcal6408a_intr_config(hdev,gpio_config->pin_num,INTRUPT_FALLING);
                break;
            }
            case PCAL6408A_GPIO_MODE_IT_RISING_FALLING:
            {
                status = pcal6408a_set_dir(hdev,gpio_config->pin_num,INPUT);
                status = pcal6408a_intr_config(hdev,gpio_config->pin_num,INTRUPT_ANY_EDGE);
                break;
            }
        }
        status = pcal6408a_set_pull_up_dwn(hdev,gpio_config->pin_num,gpio_config->pull_sts);

        gpio_bit_msk=gpio_config->pin_num;
        while(gpio_bit_msk)
        {
            if((gpio_bit_msk & 0x01) == 0x01)
            {
                hdev->intr_info[pin].callback_func=gpio_config->cb_func;
                hdev->intr_info[pin].cb_func_args=gpio_config->cb_func_args;
                hdev->intr_info[pin].intr_typ =gpio_config->mode;
            }
            gpio_bit_msk=gpio_bit_msk>>1;
            pin++;
        }
    }


    return status;
}

/**
 * @brief This utility API is used to set or reset a bit in the data
 */
static uint8_t bit_write(uint8_t data, pcal6408a_gpio_pin pin, uint8_t flag)
{
    if(flag)
    {
        data = (data | (pin));
    }
    else
    {
        data = (data & ~(pin));
    }

    return data;
}

/**
 * @brief This utility API is used to check the validity of the gpio pin number
 */
static int8_t is_gpio_valid(pcal6408a_gpio_pin pin)
{
    int8_t status;

    if((PCAL6408A_GPIO_MAX < pin))
    {
        status = PCAL6408A_E_OUT_OF_RANGE;
    }
    else
    {
        status = PCAL6408A_OK;
    }

    return status;
}

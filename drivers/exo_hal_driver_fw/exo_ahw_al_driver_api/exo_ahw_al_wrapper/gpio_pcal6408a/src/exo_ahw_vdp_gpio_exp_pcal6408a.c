/**
 * @file exo_ahw_vdp_gpio_exp_pcal6408a.c
 *
 * @brief This file contains the vendor driver porting function of PCAL6408A GPIO expander
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
#include <stdlib.h>
#include "exo_ahw_vdp_gpio_exp_pcal6408a.h"
#include "exo_io_al_gpio_common.h"
#include "exo_osal_mem_management.h"
#include "exo_ahw_al_linux_wrpr.h"
#include "pcal6408a_gpio_expander.h"
#include "exo_common.h"

const uint8_t pcal480_gpio_mode_lut[IOAL_GPIO_MODE_MAX] = {
        [IOAL_GPIO_MODE_INPUT]=PCAL6408A_GPIO_MODE_INPUT,
        [IOAL_GPIO_MODE_OUTPUT_PP]=PCAL6408A_GPIO_MODE_OUTPUT,
        [IOAL_GPIO_MODE_OUTPUT_OD]=PCAL6408A_GPIO_MODE_OUTPUT,
        [IOAL_GPIO_MODE_IT_RISING]=PCAL6408A_GPIO_MODE_IT_RISING,
        [IOAL_GPIO_MODE_IT_FALLING]=PCAL6408A_GPIO_MODE_IT_FALLING,
        [IOAL_GPIO_MODE_IT_RISING_FALLING]=PCAL6408A_GPIO_MODE_IT_RISING_FALLING,

};
const uint8_t pcal480_pull_sts_lut[IOAL_PULL_MAX] = {
        [IOAL_GPIO_NOPULL]=NO_PULL,
        [IOAL_GPIO_PULLUP]=PULL_UP,
        [IOAL_GPIO_PULLDOWN]=PULL_DOWN,
};


/**
 * @brief  IO Map lookup table.
 */
extern ahw_io_map *ahw_io_lookup_tble[MAX_AH_INST_ID];

/**
 * @brief  Instance handle pointer.
 */
extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

/**
 * @brief  GPIO_EXP PCAL6408A handle.
 */
pcal6408a_gpio_cfg vdh_gpio_cfg;

/**
 * @brief  This API is used for i2c write.
 */
uint8_t pcal6408a_i2c_write(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    int8_t rslt;
    uint8_t data_array[2];

    data_array[0]=reg_addr;
    data_array[1]=data[0];

    if(io_hal_i2c_transmit(intf_hdl,slv_addr,data_array,2,500) == HAL_SCS)
    {
        rslt=PCAL6408A_OK;
    }
    return rslt;
}

/**
 * @brief  This API is used for i2c read.
 */
uint8_t pcal6408a_i2c_read(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    ioal_i2c_hdle *hi2c = (ioal_i2c_hdle*)intf_hdl;
    int8_t rslt;
    if(HAL_SCS == io_hal_i2c_transmit(hi2c, (uint16)slv_addr, &reg_addr, 1, 500))
    {
        if(HAL_SCS == io_hal_i2c_receive(hi2c, (uint16)slv_addr, data, len, 500))
        {
            rslt =PCAL6408A_OK;
        }
        else
        {
            rslt =PCAL6408A_E_COM_FAIL;
        }
    }
    else
    {
        rslt =PCAL6408A_E_COM_FAIL;
    }
    return rslt;
}

/**
 * @brief This API initializes the GPIO pin as per the gpio_config.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_init(ahw_al_gpio_exp_hdle *hgpio_exp)
{
    hal_ret_sts sts = HAL_MAX_ERR;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO GPIO EXPANDER - AH-Vendor driver porting layer Initialize");
    printf("\n EXO GPIO EXPANDER - AH-Vendor driver Initialize");
    printf("\n EXO GPIO EXPANDER - AH-Vendor driver Initialization completed successfully ");
    usleep(100000);
    printf("\n EXO GPIO EXPANDER - AH-Vendor driver porting layer initialization completed successfully");

#else
    pcal6408a_dev* hge=(pcal6408a_dev*)os_malloc(sizeof(pcal6408a_dev));
    hge->write = pcal6408a_i2c_write;
    hge->read = pcal6408a_i2c_read;
    hge->io_intf_hdle = intf_inst_hdle_ptr[ahw_io_lookup_tble[hgpio_exp->ahw_gen_info.ahw_inst_id]->io_instance_id];
    hge->slave_addr=ahw_io_lookup_tble[hgpio_exp->ahw_gen_info.ahw_inst_id]->slv_addr;
    if(HAL_SCS == (hal_ret_sts)pcal6408a_gpio_init(hge))
    {
        hgpio_exp->ahw_gen_info.vdp_inst_hdle =(void*)hge;
        hgpio_exp->ahw_gen_info.io_intf_hdle=hge->io_intf_hdle;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
#endif
    return sts;
}

/**
 * @brief This API is used to reads and writes data to register
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_self_test(ahw_al_gpio_exp_hdle *hgpio_exp)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts) pcal6408a_self_test(vdh_gex))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}
/**
 * @brief This API is used to read the state of the GPIO pin
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_readpin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate *pin_state)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts) pcal6408a_readpin(vdh_gex, pin, (pcal6408a_gpio_pinstate*)pin_state))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief This API is used to write the state of the GPIO pin
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_writepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_gpio_pinstate pin_state)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == pcal6408a_writepin(vdh_gex,pin,pin_state))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief This API is used to toggle the state of the GPIO pin
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_togglepin(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;

    if(HAL_SCS == pcal6408a_togglepin(vdh_gex,pin))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief This API configures the GPIO pin to be either input (dir = 0) or
 * output (dir = 1)
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_dir(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_dir pin_dir)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == pcal6408a_set_dir(vdh_gex,pin,pin_dir))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief This API configures the output drive level of the GPIO pin.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_strength(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_strgth pin_strength)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == pcal6408a_set_strength(vdh_gex,pin,pin_strength))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief This API configures the polarity inversion of pins defined as
 * inputs.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_pol_inv(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pol polarity)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;

    if(HAL_SCS ==pcal6408a_set_pol_inv(vdh_gex,pin,polarity))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief This API enables or disables pull-up/pull-down resistors on the
 * corresponding GPIO.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_enable_pull(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_pull flag)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;

    if(HAL_SCS ==pcal6408a_enable_pull(vdh_gex,pin,flag))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief This API configures the GPIO to have pull-up or pull-down resistor by
 * programming the pull-up/pull-down selection register.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_pull_up_dwn(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_pin_up_dwn flag)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == pcal6408a_set_pull_up_dwn(vdh_gex,pin,flag))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief This API configures the output port as push-pull or open-drain.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_set_port_cfg(ahw_al_gpio_exp_hdle *hgpio_exp, gpio_exp_gpio_pin pin, gpio_exp_port_cfg flag)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;

    if(HAL_SCS == pcal6408a_set_port_cfg(vdh_gex,pin,flag))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}

/**
 * @brief This API configures the output port as push-pull or open-drain.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_gpio_pin_cfg(ahw_al_gpio_exp_hdle* hgpio_exp, ahw_al_gpio_exp_gpio_cfg* gpio_pin)
{
    hal_ret_sts sts;
    pcal6408a_dev *vdh_gex;
    pcal6408a_gpio_cfg vd_gpio_config;
    vdh_gex = (pcal6408a_dev*) hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    vd_gpio_config.pin_num=gpio_pin->pin_num;
    vd_gpio_config.cb_func =gpio_pin->cb_func ;
    vd_gpio_config.cb_func_args= gpio_pin->cb_func_args;
    vd_gpio_config.pull_sts= pcal480_pull_sts_lut[gpio_pin->pull_sts];
    vd_gpio_config.mode= pcal480_gpio_mode_lut[gpio_pin->mode];
    if(HAL_SCS == pcal6408a_gpio_pin_cfg(vdh_gex,&vd_gpio_config))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_DRIVER_ERR;
    }
    return sts;
}
/**
 * @brief This API for ISR handler.
 */
hal_ret_sts ahw_vdp_gpio_exp_pcal6408a_isr_hdlr(ahw_al_gpio_exp_hdle *hgpio_exp)
{
    hal_ret_sts sts;
    uint8_t intr_flg,data,pin=0;
    pcal6408a_dev *gpio_hdl_vdp;
    gpio_hdl_vdp = hgpio_exp->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)pcal6408a_read_intr_sts(gpio_hdl_vdp,&intr_flg))
    {
        pcal6408a_read(gpio_hdl_vdp, PCAL6408_REG_INPUT,&data, 1);
        while(intr_flg)
        {
            if((intr_flg & 0x01) == 0x01)
            {
                if(((data & 0x01) == 0x01 && gpio_hdl_vdp->intr_info[pin].intr_typ == PCAL6408A_GPIO_MODE_IT_RISING )  || \
                        ((data & 0x01) == 0x0 && gpio_hdl_vdp->intr_info[pin].intr_typ == PCAL6408A_GPIO_MODE_IT_FALLING )  || \
                        (gpio_hdl_vdp->intr_info[pin].intr_typ == PCAL6408A_GPIO_MODE_IT_RISING_FALLING) )
                {
                    gpio_hdl_vdp->intr_info[pin].callback_func(gpio_hdl_vdp->intr_info[pin].cb_func_args);
                }
            }
            intr_flg=intr_flg>>1;
            data=data>>1;
            pin++;
        }
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}

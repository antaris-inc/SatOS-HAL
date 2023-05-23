/**
 * @file exo_io_al_i2c_common.c
 *
 * @brief This file contains abstracted function definition for I2C interface
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
#include <unistd.h>
#include "exo_io_al_i2c_common.h"
#include "exo_hal_io_al_common.h"
#ifndef LINUX_TEMP_PORT
#include "exo_io_al_stm32f7xx_i2c.h"
#else
#include "exo_io_al_linux_i2c.h"
#endif



#ifndef LINUX_TEMP_PORT

#define I2C1_TX_CPLT_CB			check_i2c1_dummy					///< I2C1 TX complete callback event
#define I2C1_RX_CPLT_CB			check_i2c1_dummy					///< I2C1 RX complete callback event
#define I2C1_ABORT_CPLT_CB		check_i2c1_dummy					///< I2C1 Abort complete callback event
#define I2C1_LISTEN_CPLT_CB		check_i2c1_dummy					///< I2C1 Listen complete callback event
#define I2C1_ERROR_CB			check_i2c1_dummy					///< I2C1 Error complete callback event

#define I2C2_TX_CPLT_CB	    	check_i2c2_dummy					///< I2C2 TX complete callback event
#define I2C2_RX_CPLT_CB	    	check_i2c2_dummy					///< I2C2 RX complete callback event
#define I2C2_ABORT_CPLT_CB		check_i2c2_dummy					///< I2C2 Abort complete callback event
#define I2C2_LISTEN_CPLT_CB		check_i2c2_dummy					///< I2C2 Listen complete callback event
#define I2C2_ERROR_CB			check_i2c2_dummy					///< I2C2 Error complete callback event

#define I2C3_TX_CPLT_CB			check_i2c3_dummy					///< I2C3 TX complete callback event
#define I2C3_RX_CPLT_CB			check_i2c3_dummy					///< I2C3 RX complete callback event
#define I2C3_ABORT_CPLT_CB		check_i2c3_dummy					///< I2C3 Abort complete callback event
#define I2C3_LISTEN_CPLT_CB		check_i2c3_dummy					///< I2C3 Listen complete callback event
#define I2C3_ERROR_CB			check_i2c3_dummy					///< I2C3 Error complete callback event

#define I2C4_TX_CPLT_CB			check_i2c4_dummy					///< I2C4 TX complete callback event
#define I2C4_RX_CPLT_CB			check_i2c4_dummy					///< I2C4 RX complete callback event
#define I2C4_ABORT_CPLT_CB		check_i2c4_dummy					///< I2C4 Abort complete callback event
#define I2C4_LISTEN_CPLT_CB		check_i2c4_dummy					///< I2C4 Listen complete callback event
#define I2C4_ERROR_CB			check_i2c4_dummy					///< I2C4 Error complete callback event

#else


#define I2C1_TX_CPLT_CB			linux_i2c_dummy_fn							///< I2C1 TX complete callback event
#define I2C1_RX_CPLT_CB			linux_i2c_dummy_fn							///< I2C1 RX complete callback event
#define I2C1_ABORT_CPLT_CB		linux_i2c_dummy_fn							///< I2C1 Abort complete callback event
#define I2C1_LISTEN_CPLT_CB		linux_i2c_dummy_fn							///< I2C1 Listen complete callback event
#define I2C1_ERROR_CB			linux_i2c_dummy_fn							///< I2C1 Error complete callback event

#define I2C2_TX_CPLT_CB	    	linux_i2c_dummy_fn					///< I2C2 TX complete callback event
#define I2C2_RX_CPLT_CB	    	linux_i2c_dummy_fn					///< I2C2 RX complete callback event
#define I2C2_ABORT_CPLT_CB		linux_i2c_dummy_fn					///< I2C2 Abort complete callback event
#define I2C2_LISTEN_CPLT_CB		linux_i2c_dummy_fn					///< I2C2 Listen complete callback event
#define I2C2_ERROR_CB			linux_i2c_dummy_fn					///< I2C2 Error complete callback event


#define I2C3_TX_CPLT_CB			linux_i2c_dummy_fn							///< I2C3 TX complete callback event
#define I2C3_RX_CPLT_CB			linux_i2c_dummy_fn							///< I2C3 RX complete callback event
#define I2C3_ABORT_CPLT_CB		linux_i2c_dummy_fn							///< I2C3 Abort complete callback event
#define I2C3_LISTEN_CPLT_CB		linux_i2c_dummy_fn							///< I2C3 Listen complete callback event
#define I2C3_ERROR_CB			linux_i2c_dummy_fn							///< I2C3 Error complete callback event

#define I2C4_TX_CPLT_CB			linux_i2c_dummy_fn							///< I2C4 TX complete callback event
#define I2C4_RX_CPLT_CB			linux_i2c_dummy_fn							///< I2C4 RX complete callback event
#define I2C4_ABORT_CPLT_CB		linux_i2c_dummy_fn							///< I2C4 Abort complete callback event
#define I2C4_LISTEN_CPLT_CB		linux_i2c_dummy_fn							///< I2C4 Listen complete callback event
#define I2C4_ERROR_CB			linux_i2c_dummy_fn							///< I2C4 Error complete callback event


#endif

extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

ioal_i2c_hdle ioal_hi2c1;
ioal_i2c_hdle ioal_hi2c2;
ioal_i2c_hdle ioal_hi2c3;
ioal_i2c_hdle ioal_hi2c4;

/**
 * @brief This API initializes the control block memory
 * and do the basic configurations for I2C
 */
hal_ret_sts io_hal_i2c_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL I2C Initialise");
    usleep(100000);
#endif
    hal_ret_sts sts;

    if(HAL_SCS == io_hal_common_i2c1_init(&ioal_hi2c1))
    {
        intf_inst_hdle_ptr[IOAL_INST_I2C1] = &ioal_hi2c1;
        io_hal_i2c1_cb_init(&ioal_hi2c1);
    }
    else
    {
        sts = HAL_IO_INIT_ERR;
    }
#ifdef COREBOARD
    if(HAL_SCS == io_hal_common_i2c2_init(&ioal_hi2c2))
    {
        intf_inst_hdle_ptr[IOAL_INST_I2C2] = &ioal_hi2c2;
        io_hal_i2c2_cb_init(&ioal_hi2c2);
    }
    else
    {
        sts = HAL_IO_INIT_ERR;
    }

    if(HAL_SCS == io_hal_common_i2c3_init(&ioal_hi2c3))
    {
        intf_inst_hdle_ptr[IOAL_INST_I2C3] = &ioal_hi2c3;
        io_hal_i2c3_cb_init(&ioal_hi2c3);
    }
    else
    {
        sts = HAL_IO_INIT_ERR;
    }
    if(HAL_SCS == io_hal_common_i2c4_init(&ioal_hi2c4))
    {
        intf_inst_hdle_ptr[IOAL_INST_I2C4] = &ioal_hi2c4;
        io_hal_i2c2_cb_init(&ioal_hi2c4);
    }
    else
    {
        sts = HAL_IO_INIT_ERR;
    }
#endif

#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL I2C Initialisation completed successfully");
#endif
    return sts;
}

/**
 * @brief This API initializes the I2C1 callback events
 */
void io_hal_i2c1_cb_init(ioal_i2c_hdle *hi2c1)
{
    hi2c1->mst_tx_cplt_cb = I2C1_TX_CPLT_CB;
    hi2c1->mst_rx_cplt_cb = I2C1_RX_CPLT_CB;
    hi2c1->abort_cplt_cb = I2C1_ABORT_CPLT_CB;
    hi2c1->listen_cplt_cb = I2C1_LISTEN_CPLT_CB;
    hi2c1->error_cb = I2C1_ERROR_CB;

#ifndef LINUX_TEMP_PORT
    io_hal_common_i2c_reg_cb(hi2c1, IOHAL_STM32_I2C_MASTER_TX_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c1, IOHAL_STM32_I2C_MASTER_RX_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c1, IOHAL_STM32_I2C_ABORT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c1, IOHAL_STM32_I2C_LISTEN_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c1, IOHAL_STM32_I2C_ERROR_CB_ID);
#endif
}

/**
 * @brief This API initializes the I2C2 callback events
 */
void io_hal_i2c2_cb_init(ioal_i2c_hdle *hi2c2)
{
    hi2c2->mst_tx_cplt_cb = I2C2_TX_CPLT_CB;
    hi2c2->mst_rx_cplt_cb = I2C2_RX_CPLT_CB;
    hi2c2->abort_cplt_cb = I2C2_ABORT_CPLT_CB;
    hi2c2->listen_cplt_cb = I2C2_LISTEN_CPLT_CB;
    hi2c2->error_cb = I2C2_ERROR_CB;

#ifndef LINUX_TEMP_PORT
    io_hal_common_i2c_reg_cb(hi2c2, IOHAL_STM32_I2C_MASTER_TX_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c2, IOHAL_STM32_I2C_MASTER_RX_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c2, IOHAL_STM32_I2C_ABORT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c2, IOHAL_STM32_I2C_LISTEN_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c2, IOHAL_STM32_I2C_ERROR_CB_ID);
#endif
}

/**
 * @brief This API initializes the I2C3 callback events
 */
void io_hal_i2c3_cb_init(ioal_i2c_hdle *hi2c3)
{
    hi2c3->mst_tx_cplt_cb = I2C3_TX_CPLT_CB;
    hi2c3->mst_rx_cplt_cb = I2C3_RX_CPLT_CB;
    hi2c3->abort_cplt_cb = I2C3_ABORT_CPLT_CB;
    hi2c3->listen_cplt_cb = I2C3_LISTEN_CPLT_CB;
    hi2c3->error_cb = I2C3_ERROR_CB;
#ifndef LINUX_TEMP_PORT
    io_hal_common_i2c_reg_cb(hi2c3, IOHAL_STM32_I2C_MASTER_TX_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c3, IOHAL_STM32_I2C_MASTER_RX_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c3, IOHAL_STM32_I2C_ABORT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c3, IOHAL_STM32_I2C_LISTEN_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c3, IOHAL_STM32_I2C_ERROR_CB_ID);
#endif
}

/**
 * @brief This API initializes the I2C4 callback events
 */
void io_hal_i2c4_cb_init(ioal_i2c_hdle *hi2c4)
{
    hi2c4->mst_tx_cplt_cb = I2C4_TX_CPLT_CB;
    hi2c4->mst_rx_cplt_cb = I2C4_RX_CPLT_CB;
    hi2c4->abort_cplt_cb = I2C4_ABORT_CPLT_CB;
    hi2c4->listen_cplt_cb = I2C4_LISTEN_CPLT_CB;
    hi2c4->error_cb = I2C4_ERROR_CB;
#ifndef LINUX_TEMP_PORT
    io_hal_common_i2c_reg_cb(hi2c4, IOHAL_STM32_I2C_MASTER_TX_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c4, IOHAL_STM32_I2C_MASTER_RX_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c4, IOHAL_STM32_I2C_ABORT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c4, IOHAL_STM32_I2C_LISTEN_CPLT_CB_ID);
    io_hal_common_i2c_reg_cb(hi2c4, IOHAL_STM32_I2C_ERROR_CB_ID);
#endif
}

/**
 * @brief This API transmits data in master mode.
 */
hal_ret_sts io_hal_i2c_transmit(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hi2c->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_i2c_transmit(hi2c,addr,pdata,size,timeout))
    {
        ret_sts = HAL_SCS;
        hi2c->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
        hi2c->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API receives data in master mode.
 */
hal_ret_sts io_hal_i2c_receive(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hi2c->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_i2c_receive(hi2c,addr,pdata,size,timeout))
    {
        ret_sts = HAL_SCS;
        hi2c->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hi2c->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief This API transmit data in master mode with Interrupt
 */
hal_ret_sts io_hal_i2c_transmit_it(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hi2c->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_i2c_transmit_it(hi2c,addr,pdata,size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API receive data in master mode with Interrupt
 */
hal_ret_sts io_hal_i2c_receive_it(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hi2c->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_i2c_receive_it(hi2c,addr,pdata,size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API transmit data in master mode with DMA
 */
hal_ret_sts io_hal_i2c_transmit_dma(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hi2c->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_i2c_transmit_dma(hi2c,addr,pdata,size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API receive data in master mode with DMA
 */
hal_ret_sts io_hal_i2c_receive_dma(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hi2c->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_i2c_receive_dma(hi2c,addr,pdata,size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API checks if device is ready for communication.
 */
hal_ret_sts io_hal_i2c_is_device_ready(ioal_i2c_hdle *hi2c, uint16 addr, uint32 trials, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_i2c_is_device_ready(hi2c,addr,trials,timeout))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API enable the Address listen mode with interrupt.
 */
hal_ret_sts io_hal_i2c_enablelisten_it(ioal_i2c_hdle *hi2c)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_i2c_enablelisten_it(hi2c))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API abort a master I2C with interrupt.
 */
hal_ret_sts io_hal_i2c_abort_it(ioal_i2c_hdle *hi2c, uint16 addr)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_i2c_abort_it(hi2c, addr))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}
#endif


#ifndef LINUX_TEMP_PORT


void check_i2c1_dummy(ioal_i2c_hdle *hi2c)
{
    return;
}
void check_i2c2_dummy(ioal_i2c_hdle *hi2c)
{
    return;
}
void check_i2c3_dummy(ioal_i2c_hdle *hi2c)
{
    return;
}
void check_i2c4_dummy(ioal_i2c_hdle *hi2c)
{
    return;
}

#else

/**
 * @brief This is I2C interface dummy function for linux
 */
void linux_i2c_dummy_fn(struct _ioal_i2c_hdle *hi2c)
{
}

#endif

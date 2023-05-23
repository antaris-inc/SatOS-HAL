/**
 * @file exo_io_al_uart_common.c
 *
 * @brief This file contains abstracted function definition for UART interface
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
#include "exo_io_al_uart_common.h"
#include "exo_hal_io_al_common.h"
#ifndef LINUX_TEMP_PORT
#include "exo_io_al_stm32f7xx_uart.h"
#else
#include "exo_io_al_linux_uart.h"
#endif

#ifndef LINUX_TEMP_PORT

#define UART6_TX_CPLT_CB		check_uart6_dummy					///< UART6 TX complete callback event
#define UART6_RX_CPLT_CB		check_uart6_dummy					///< UART6 RX complete callback event
#define UART6_ABORT_CPLT_CB		check_uart6_dummy					///< UART6 Abort complete callback event
#define UART6_ABORT_TX_CPLT_CB	check_uart6_dummy					///< UART6 Abort TX complete callback event
#define UART6_ABORT_RX_CPLT_CB	check_uart6_dummy					///< UART6 Abort RX complete callback event
#define UART6_ERROR_CB			check_uart6_dummy					///< UART6 error callback event

#define UART1_TX_CPLT_CB		check_uart1_dummy					///< UART1 TX complete callback event
#define UART1_RX_CPLT_CB		check_uart1_dummy					///< UART1 RX complete callback event
#define UART1_ABORT_CPLT_CB		check_uart1_dummy					///< UART1 Abort complete callback event
#define UART1_ABORT_TX_CPLT_CB	check_uart1_dummy					///< UART1 Abort TX complete callback event
#define UART1_ABORT_RX_CPLT_CB	check_uart1_dummy					///< UART1 Abort RX complete callback event
#define UART1_ERROR_CB			check_uart1_dummy					///< UART1 error callback event

#define UART4_TX_CPLT_CB		check_uart4_dummy					///< UART4 TX complete callback event
#define UART4_RX_CPLT_CB		check_uart4_dummy					///< UART4 RX complete callback event
#define UART4_ABORT_CPLT_CB		check_uart4_dummy					///< UART4 Abort complete callback event
#define UART4_ABORT_TX_CPLT_CB	check_uart4_dummy					///< UART4 Abort TX complete callback event
#define UART4_ABORT_RX_CPLT_CB	check_uart4_dummy					///< UART4 Abort RX complete callback event
#define UART4_ERROR_CB			check_uart4_dummy					///< UART4 error callback event

#define UART5_TX_CPLT_CB		check_uart5_dummy					///< UART5 TX complete callback event
#define UART5_RX_CPLT_CB		check_uart5_dummy					///< UART5 RX complete callback event
#define UART5_ABORT_CPLT_CB		check_uart5_dummy					///< UART5 Abort complete callback event
#define UART5_ABORT_TX_CPLT_CB	check_uart5_dummy					///< UART5 Abort TX complete callback event
#define UART5_ABORT_RX_CPLT_CB	check_uart5_dummy					///< UART5 Abort RX complete callback event
#define UART5_ERROR_CB			check_uart5_dummy					///< UART5 error callback event

#else

#define UART6_TX_CPLT_CB		linux_uart_dummy_fn							///< UART6 TX complete callback event
#define UART6_RX_CPLT_CB		linux_uart_dummy_fn							///< UART6 RX complete callback event
#define UART6_ABORT_CPLT_CB	    linux_uart_dummy_fn							///< UART6 Abort complete callback event
#define UART6_ABORT_TX_CPLT_CB	linux_uart_dummy_fn							///< UART6 Abort TX complete callback event
#define UART6_ABORT_RX_CPLT_CB  linux_uart_dummy_fn							///< UART6 Abort RX complete callback event
#define UART6_ERROR_CB			linux_uart_dummy_fn							///< UART6 error callback event

#endif

extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];
ioal_uart_hdle ioal_huart6;
ioal_uart_hdle ioal_huart1;
ioal_uart_hdle ioal_huart4;
ioal_uart_hdle ioal_huart5;

/*
 * @brief This API initializes the control block memory
 * and do the basic configurations for UART interface
 */
hal_ret_sts io_hal_uart_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL UART Initialise");
    usleep(100000);
#endif
    hal_ret_sts sts=HAL_IO_INIT_ERR;


#if(STM32F765xx)

#if COREBOARD

    if(HAL_SCS == io_hal_common_uart4_init(&ioal_huart4))
    {
        intf_inst_hdle_ptr[IOAL_INST_UART4] = &ioal_huart4;
        sts=HAL_SCS;

    }
    else
    {

        sts = HAL_IO_INIT_ERR;
    }

    if(HAL_SCS == io_hal_common_uart5_init(&ioal_huart5))
    {
        intf_inst_hdle_ptr[IOAL_INST_UART5] = &ioal_huart5;
        sts=HAL_SCS;

    }
    else
    {

        sts = HAL_IO_INIT_ERR;
    }

#else

    if(HAL_SCS == io_hal_common_uart6_init(&ioal_huart6))
    {
        intf_inst_hdle_ptr[IOAL_INST_UART6] = &ioal_huart6;
        sts=HAL_SCS;

    }
    else
    {
        sts = HAL_IO_INIT_ERR;
    }

#endif
#endif

#ifdef STM32F769xx
    if(HAL_SCS == io_hal_common_uart1_init(&ioal_huart1))
    {
        intf_inst_hdle_ptr[IOAL_INST_UART1] = &ioal_huart1;
        sts=HAL_SCS;

    }
    else
    {

        sts = HAL_IO_INIT_ERR;
    }
#endif

#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL UART Initialisation completed successfully");
#endif
    return sts;
}

/*
 * @brief This API initialize the callback events for UART6
 */
void io_hal_uart6_cb_init(ioal_uart_hdle *huart6)
{
    huart6->tx_cplt_cb = UART6_TX_CPLT_CB;
    huart6->rx_cplt_cb = UART6_RX_CPLT_CB;
    huart6->abort_cplt_cb = UART6_ABORT_CPLT_CB;
    huart6->abort_tx_cplt_cb = UART6_ABORT_TX_CPLT_CB;
    huart6->abort_rx_cplt_cb = UART6_ABORT_RX_CPLT_CB;
    huart6->error_cb = UART6_ERROR_CB;

#ifndef LINUX_TEMP_PORT
    io_hal_common_uart_reg_cb(huart6, IOHAL_STM32_UART_TX_CPLT_CB_ID);
    io_hal_common_uart_reg_cb(huart6, IOHAL_STM32_UART_RX_CPLT_CB_ID);
    io_hal_common_uart_reg_cb(huart6, IOHAL_STM32_UART_ABORT_CPLT_CB_ID);
    io_hal_common_uart_reg_cb(huart6, IOHAL_STM32_UART_ABORT_TX_CPLT_CB_ID);
    io_hal_common_uart_reg_cb(huart6, IOHAL_STM32_UART_ABORT_RX_CPLT_CB_ID);
    io_hal_common_uart_reg_cb(huart6, IOHAL_STM32_UART_ERROR_CB_ID);
#endif
}


/*
 * @brief This API transmit the data in UART interface with blocking mode
 */
hal_ret_sts io_hal_uart_transmit(ioal_uart_hdle *huart, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    huart->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_uart_transmit(huart,pdata,size,timeout))
    {
        ret_sts = HAL_SCS;
        huart->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
        huart->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/*
 * @brief This API receive the data in UART interface with blocking mode
 */
hal_ret_sts io_hal_uart_receive(ioal_uart_hdle *huart, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    huart->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_uart_receive(huart,pdata,size,timeout))
    {
        ret_sts = HAL_SCS;
        huart->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        huart->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

#ifndef LINUX_TEMP_PORT
/*
 * @brief This API transmit the data with interrupt mode
 */
hal_ret_sts io_hal_uart_transmit_it(ioal_uart_hdle *huart, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    huart->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_uart_transmit_it(huart,pdata,size))
    {
        ret_sts = HAL_SCS;

    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API receive the data with interrupt mode
 */
hal_ret_sts io_hal_uart_receive_it(ioal_uart_hdle *huart, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    huart->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_uart_receive_it(huart,pdata,size))
    {
        ret_sts = HAL_SCS;

    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API transmit the data in UART interface with DMA mode
 */
hal_ret_sts io_hal_uart_transmit_dma(ioal_uart_hdle *huart, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    huart->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_uart_transmit_dma(huart,pdata,size))
    {
        ret_sts = HAL_SCS;

    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API receive the data in UART interface in DMA mode
 */
hal_ret_sts io_hal_uart_receive_dma(ioal_uart_hdle *huart, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_uart_receive_dma(huart,pdata,size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API pause the transmission of data in DMA mode
 */
hal_ret_sts io_hal_uart_dma_pause(ioal_uart_hdle *huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_uart_dma_pause(huart))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API resume the transmission of data in DMA mode
 */
hal_ret_sts io_hal_uart_dma_resume(ioal_uart_hdle *huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_uart_dma_resume(huart))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API stop the transmission of data in DMA mode
 */
hal_ret_sts io_hal_uart_dma_stop(ioal_uart_hdle *huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_uart_dma_stop(huart))
    {
        ret_sts = HAL_SCS;

    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API abort the transmission of data
 */
hal_ret_sts io_hal_uart_abort(ioal_uart_hdle *huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_uart_abort(huart))
    {
        ret_sts = HAL_SCS;

    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API abort the ongoing transmit of data
 */
hal_ret_sts io_hal_uart_abort_transmit(ioal_uart_hdle *huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_uart_abort_transmit(huart))
    {
        ret_sts = HAL_SCS;

    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API abort the receive of data
 */
hal_ret_sts io_hal_uart_abort_receive(ioal_uart_hdle *huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_uart_abort_receive(huart))
    {
        ret_sts = HAL_SCS;

    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API abort transmission of data with interrupt mode
 */
hal_ret_sts io_hal_uart_abort_it(ioal_uart_hdle *huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_uart_abort_it(huart))
    {
        ret_sts = HAL_SCS;

    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API abort the transmission of data with interrupt mode
 */
hal_ret_sts io_hal_uart_abort_transmit_it(ioal_uart_hdle *huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_uart_abort_transmit_it(huart))
    {
        ret_sts = HAL_SCS;

    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*
 * @brief This API abort the receive of data with interrupt mode
 */
hal_ret_sts io_hal_uart_abort_receive_it(ioal_uart_hdle *huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_uart_abort_receive_it(huart))
    {
        ret_sts = HAL_SCS;

    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

#endif


#ifndef LINUX_TEMP_PORT
/**
 * @brief UART call back api
 */
void check_uart6_dummy(ioal_uart_hdle *huart)
{
    //    recv_flg=1;
}

#else

/**
 * @brief This is UART interface dummy function for linux
 */
void linux_uart_dummy_fn(struct _ioal_uart_hdle *huart)
{
}

#endif

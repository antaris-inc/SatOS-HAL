/**
 * @file exo_io_al_spi_common.c
 *
 * @brief This file contains abstracted function definition for SPI interface
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
#include "exo_io_al_spi_common.h"
#include "exo_hal_io_al_common.h"

#ifndef LINUX_TEMP_PORT
#include "exo_io_al_stm32f7xx_spi.h"
#else
#include "exo_io_al_linux_spi.h"
#endif

#ifndef LINUX_TEMP_PORT
#define SPI1_TX_CPLT_CB			check_spi1_dummy					///< SPI1 TX complete callback event
#define SPI1_RX_CPLT_CB			check_spi1_dummy					///< SPI1 RX complete callback event
#define SPI1_TX_RX_CPLT_CB		check_spi1_dummy					///< SPI1 TX RX complete callback event
#define SPI1_ABORT_CPLT_CB		check_spi1_dummy					///< SPI1 Abort complete callback event
#define SPI1_ERROR_CB			check_spi1_dummy					///< SPI1 error callback event
#else
#define SPI1_TX_CPLT_CB			linux_spi_dummy_fn							///< SPI1 TX complete callback event
#define SPI1_RX_CPLT_CB			linux_spi_dummy_fn							///< SPI1 RX complete callback event
#define SPI1_TX_RX_CPLT_CB		linux_spi_dummy_fn							///< SPI1 TX RX complete callback event
#define SPI1_ABORT_CPLT_CB		linux_spi_dummy_fn							///< SPI1 Abort complete callback event
#define SPI1_ERROR_CB			linux_spi_dummy_fn							///< SPI1 error callback event
#endif

extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];
ioal_spi_hdle ioal_hspi1;

/*
 * @brief This API initialize the SPI interface
 */
hal_ret_sts io_hal_spi_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL SPI Initialise");
    usleep(100000);
#endif
    hal_ret_sts sts;
    if(HAL_SCS == io_hal_common_spi1_init(&ioal_hspi1))
    {
        intf_inst_hdle_ptr[IOAL_INST_SPI1] = &ioal_hspi1;
        io_hal_spi1_cb_init(&ioal_hspi1);

    }
    else
    {

        sts = HAL_IO_INIT_ERR;
    }
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL SPI Initialisation completed successfully");
#endif
    return sts;
}

/*
 * @brief This API initialize the callback event
 */
void io_hal_spi1_cb_init(ioal_spi_hdle *hspi1)
{
    hspi1->spi_tx_cplt_cb = SPI1_TX_CPLT_CB;
    hspi1->spi_rx_cplt_cb = SPI1_RX_CPLT_CB;
    hspi1->spi_tx_rx_cplt_cb = SPI1_TX_RX_CPLT_CB;
    hspi1->spi_abort_cplt_cb = SPI1_ABORT_CPLT_CB;
    hspi1->spi_error_cb = SPI1_ERROR_CB;

#ifndef LINUX_TEMP_PORT
    io_hal_common_spi_reg_cb(hspi1, IOHAL_STM32_SPI_TX_CPLT_CB_ID);
    io_hal_common_spi_reg_cb(hspi1, IOHAL_STM32_SPI_RX_CPLT_CB_ID);
    io_hal_common_spi_reg_cb(hspi1, IOHAL_STM32_SPI_TX_RX_CPLT_CB_ID);
    io_hal_common_spi_reg_cb(hspi1, IOHAL_STM32_SPI_ABORT_CPLT_CB_ID);
    io_hal_common_spi_reg_cb(hspi1, IOHAL_STM32_SPI_ERROR_CB_ID);
#endif
}

/*
 * @brief This API transmit the data in SPI interface with blocking mode
 */
hal_ret_sts io_hal_spi_transmit(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hspi->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_spi_transmit(hspi,pdata,size,timeout))
    {
        ret_sts = HAL_SCS;
        hspi->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
        hspi->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/*
 * @brief This API receive the data from SPI interface with blocking mode
 */
hal_ret_sts io_hal_spi_receive(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hspi->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_spi_receive(hspi,pdata,size,timeout))
    {
        ret_sts = HAL_SCS;
        hspi->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hspi->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

#ifndef LINUX_TEMP_PORT
/*
 * @brief This API transmit and receive the data
 */
hal_ret_sts io_hal_spi_transmit_receive(ioal_spi_hdle *hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hspi->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_spi_transmit_receive(hspi,ptxdata,prxdata,size,timeout))
    {
        ret_sts = HAL_SCS;
        hspi->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hspi->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/*
 * @brief This API transmit the data in SPI interface with interrupt mode
 */
hal_ret_sts io_hal_spi_transmit_it(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hspi->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_spi_transmit_it(hspi,pdata,size))
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
 * @brief This API receive the data from SPI interface with interrupt mode
 */
hal_ret_sts io_hal_spi_receive_it(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hspi->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_spi_receive_it(hspi,pdata,size))
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
 * @brief This API transmit and receive the data in interrupt mode
 */
hal_ret_sts io_hal_spi_transmit_receive_it(ioal_spi_hdle *hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hspi->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_spi_transmit_receive_it(hspi,ptxdata, prxdata, size))
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
 * @brief This API transmit the data in SPI interface in DMA mode
 */
hal_ret_sts io_hal_spi_transmit_dma(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hspi->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_spi_transmit_dma(hspi,pdata, size))
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
 * @brief This API receive the data from SPI interface in DMA mode
 */
hal_ret_sts io_hal_spi_receive_dma(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hspi->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_spi_receive_dma(hspi,pdata, size))
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
 * @brief This API transmit and receive the data in DMA mode
 */
hal_ret_sts io_hal_spi_transmit_receive_dma(ioal_spi_hdle *hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hspi->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_spi_transmit_receive_dma(hspi,ptxdata, prxdata, size))
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
 * @brief This API abort the transmission of data in SPI interface
 */
hal_ret_sts io_hal_spi_abort(ioal_spi_hdle *hspi)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_spi_abort(hspi))
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
hal_ret_sts io_hal_spi_dma_pause(ioal_spi_hdle *hspi)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_spi_dma_pause(hspi))
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
hal_ret_sts io_hal_spi_dma_resume(ioal_spi_hdle *hspi)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_spi_dma_resume(hspi))
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
hal_ret_sts io_hal_spi_dma_stop(ioal_spi_hdle *hspi)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_spi_dma_stop(hspi))
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

void check_spi1_dummy(ioal_spi_hdle *hspi)
{
    return;
}

#else
/**
 * @brief This is SPI interface dummy function for linux
 */
void linux_spi_dummy_fn(struct _ioal_spi_hdle *hspi)
{
}

#endif

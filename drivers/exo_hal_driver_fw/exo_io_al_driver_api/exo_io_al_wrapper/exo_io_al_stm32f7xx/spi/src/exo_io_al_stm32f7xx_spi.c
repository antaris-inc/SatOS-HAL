/**
 * @file exo_io_al_stm32f7xx_spi.c
 *
 * @brief This file contains wrapper function definition for SPI interface
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

#include "exo_io_al_stm32f7xx_spi.h"
#include "exo_io_al_stm32f7xx_common.h"

#ifndef LINUX_TEMP_PORT
#include "stm32f7xx_hal.h"
#endif


/**
 * @brief TX complete callback event function
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @retval No return
 */
void io_hal_stm32f7xx_spi_tx_cplt_cb(SPI_HandleTypeDef *hspi);
/**
 * @brief RX complete callback event function
 * @param[in] hspi - hspi pointer to a SPI_HandleTypeDef structure that
 * 					contains the configuration information for SPI
 * @retval No return
 */
void io_hal_stm32f7xx_spi_rx_cplt_cb(SPI_HandleTypeDef *hspi);
/**
 * @brief TX and RX complete callback event function
 * @param[in] hspi - hspi pointer to a SPI_HandleTypeDef structure that
 * 					contains the configuration information for SPI
 * @retval No return
 */
void io_hal_stm32f7xx_spi_tx_rx_cplt_cb(SPI_HandleTypeDef *hspi);
/**
 * @brief Abort complete callback event function
 * @param[in] hspi - hspi pointer to a SPI_HandleTypeDef structure that
 * 					contains the configuration information for SPI
 * @retval No return
 */
void io_hal_stm32f7xx_spi_abort_cplt_cb(SPI_HandleTypeDef *hspi);
/**
 * @brief Error callback event function
 * @param[in] hspi - hspi pointer to a SPI_HandleTypeDef structure that
 * 					contains the configuration information for SPI
 * @retval No return
 */
void io_hal_stm32f7xx_spi_error_cb(SPI_HandleTypeDef *hspi);



/**
 * @brief This API initialize the control block memory of SPI1
 * @param ioal_hspi1 - ioal_hspi1 pointer to a ioal_spi_hdle structure that contains
 */
static void MX_SPI1_Init(ioal_spi_hdle *ioal_hspi1);

SPI_HandleTypeDef hspi1;

/**
 * @brief This API initialize the control block memory of SPI1
 */     
hal_ret_sts io_hal_stm32f7xx_spi1_init(ioal_spi_hdle *ioal_hspi1)
{
    MX_SPI1_Init(ioal_hspi1);
    return HAL_SCS;
}

/**
 * @brief SPI1 initialization Function
 */
static void MX_SPI1_Init(ioal_spi_hdle *ioal_hspi1)
{

    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;
    hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        ioal_error_handler();
    }
    ioal_hspi1->intf_gen_info.vdp_intf_inst_hdle = (void*)&hspi1;
    ioal_hspi1->intf_gen_info.state = IO_FREE_STATE;

}
/**
 * @brief This API transmit the data in blocking mode
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_Transmit(hspi, pdata, size, timeout))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API receive the data in blocking mode
 */
hal_ret_sts io_hal_stm32f7xx_spi_receive(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_Receive(hspi, pdata, size, timeout))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API transmit and receive data in blocking mode
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit_receive(ioal_spi_hdle *ioal_hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_TransmitReceive(hspi, ptxdata, prxdata, size, timeout))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API transmit the data in interrupt mode
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit_it(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_Transmit_IT(hspi, pdata, size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API receive the data in interrupt mode
 */
hal_ret_sts io_hal_stm32f7xx_spi_receive_it(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_Receive_IT(hspi, pdata, size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API transmit and receive data in interrupt mode
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit_receive_it(ioal_spi_hdle *ioal_hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_TransmitReceive_IT(hspi, ptxdata, prxdata, size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API transmit the data in DMA mode
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit_dma(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_Transmit_DMA(hspi, pdata, size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API receive the data in DMA mode
 */
hal_ret_sts io_hal_stm32f7xx_spi_receive_dma(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_Receive_DMA(hspi, pdata, size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API transmit and receive data in DMA mode
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit_receive_dma(ioal_spi_hdle *ioal_hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_TransmitReceive_DMA(hspi, ptxdata, prxdata, size))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API abort the transmission of data
 */
hal_ret_sts io_hal_stm32f7xx_spi_abort(ioal_spi_hdle *ioal_hspi)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_Abort(hspi))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API abort the transmission of data in interrupt mode
 */
hal_ret_sts io_hal_stm32f7xx_spi_abort_it(ioal_spi_hdle *ioal_hspi)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_Abort_IT(hspi))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API pause the transmission of data
 */
hal_ret_sts io_hal_stm32f7xx_spi_dma_pause(ioal_spi_hdle *ioal_hspi)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_DMAPause(hspi))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API resume the transmission of data
 */
hal_ret_sts io_hal_stm32f7xx_spi_dma_resume(ioal_spi_hdle *ioal_hspi)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_DMAResume(hspi))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API stop the transmission of data
 */
hal_ret_sts io_hal_stm32f7xx_spi_dma_stop(ioal_spi_hdle *ioal_hspi)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_SPI_DMAStop(hspi))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API register the callback event
 */
hal_ret_sts io_hal_stm32f7xx_spi_reg_cb(ioal_spi_hdle *ioal_hspi, iohal_stm32_spi_cbid cbid)
{
    hal_ret_sts sts = HAL_SCS;
    SPI_HandleTypeDef *hspi = ioal_hspi->intf_gen_info.vdp_intf_inst_hdle;

    switch (cbid)
    {
        case IOHAL_STM32_SPI_TX_CPLT_CB_ID :
            sts = HAL_SPI_RegisterCallback(hspi, HAL_SPI_TX_COMPLETE_CB_ID, io_hal_stm32f7xx_spi_tx_cplt_cb);
            break;

        case IOHAL_STM32_SPI_RX_CPLT_CB_ID :
            sts = HAL_SPI_RegisterCallback(hspi, HAL_SPI_RX_COMPLETE_CB_ID, io_hal_stm32f7xx_spi_rx_cplt_cb);
            break;

        case IOHAL_STM32_SPI_TX_RX_CPLT_CB_ID :
            sts = HAL_SPI_RegisterCallback(hspi, HAL_SPI_TX_RX_COMPLETE_CB_ID, io_hal_stm32f7xx_spi_tx_rx_cplt_cb);
            break;

        case IOHAL_STM32_SPI_ABORT_CPLT_CB_ID :
            sts = HAL_SPI_RegisterCallback(hspi, HAL_SPI_ABORT_CB_ID, io_hal_stm32f7xx_spi_abort_cplt_cb);
            break;

        case IOHAL_STM32_SPI_ERROR_CB_ID :
            sts = HAL_SPI_RegisterCallback(hspi, HAL_SPI_ERROR_CB_ID, io_hal_stm32f7xx_spi_error_cb);
            break;

        default :

            sts =  HAL_IO_INVLD_CB_FN;
            break;
    }
    return sts;
}

/**
 * @brief TX complete callback event function
 */
void io_hal_stm32f7xx_spi_tx_cplt_cb(SPI_HandleTypeDef *hspi)
{
    ioal_spi_hdle *ioal_hspi = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hspi, (void**)&ioal_hspi))
    {
        ioal_hspi->spi_tx_cplt_cb(ioal_hspi);
    }
    else
    {

    }
}

/**
 * @brief RX complete callback event function
 */
void io_hal_stm32f7xx_spi_rx_cplt_cb(SPI_HandleTypeDef *hspi)
{
    ioal_spi_hdle *ioal_hspi = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hspi, (void**)&ioal_hspi))
    {
        ioal_hspi->spi_rx_cplt_cb(ioal_hspi);
    }
    else
    {

    }
}

/**
 * @brief TX and RX complete callback event function
 */
void io_hal_stm32f7xx_spi_tx_rx_cplt_cb(SPI_HandleTypeDef *hspi)
{
    ioal_spi_hdle *ioal_hspi = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hspi, (void**)&ioal_hspi))
    {
        ioal_hspi->spi_tx_rx_cplt_cb(ioal_hspi);
    }
    else
    {

    }
}

/**
 * @brief Abort complete callback event function
 */
void io_hal_stm32f7xx_spi_abort_cplt_cb(SPI_HandleTypeDef *hspi)
{
    ioal_spi_hdle *ioal_hspi = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hspi, (void**)&ioal_hspi))
    {
        ioal_hspi->spi_abort_cplt_cb(ioal_hspi);
    }
    else
    {

    }
}

/**
 * @brief Error callback event function
 */
void io_hal_stm32f7xx_spi_error_cb(SPI_HandleTypeDef *hspi)
{
    ioal_spi_hdle *ioal_hspi = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hspi, (void**)&ioal_hspi))
    {
        ioal_hspi->spi_error_cb(ioal_hspi);
    }
    else
    {

    }
}

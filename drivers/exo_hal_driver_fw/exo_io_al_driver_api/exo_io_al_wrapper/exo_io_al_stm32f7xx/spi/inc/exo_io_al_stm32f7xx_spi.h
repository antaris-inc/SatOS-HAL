/**
 * @file exo_io_al_stm32f7xx_spi.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for SPI interface
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

#ifndef _IO_AL_STM32F7XX_SPI_H_
#define _IO_AL_STM32F7XX_SPI_H_

#include "exo_types.h"
#include "exo_io_al_spi_common.h"
#include "exo_hal_common.h"
#include "exo_io_al_common.h"

/**
 * @brief  VDP layer SPI callback ID
 */
typedef enum
{
    IOHAL_STM32_SPI_TX_CPLT_CB_ID      	= 0x00U,    /*!< SPI Tx Transfer completed callback ID */
    IOHAL_STM32_SPI_RX_CPLT_CB_ID      	= 0x01U,    /*!< SPI Rx Transfer completed callback ID */
    IOHAL_STM32_SPI_TX_RX_CPLT_CB_ID    = 0x02U,    /*!< SPI Tx Rx Transfer completed callback ID */
    IOHAL_STM32_SPI_ABORT_CPLT_CB_ID    = 0x03U,    /*!< SPI Abort Complete callback ID */
    IOHAL_STM32_SPI_ERROR_CB_ID         = 0x04U,    /*!< SPI Error callback ID */

} iohal_stm32_spi_cbid;

/* Prototype Definitions */
/**
 * @brief This function initialize the control block memory and do basic configurations of SPI
 * @param[in] ioal_spi1 - ioal_spi1 pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi1_init(ioal_spi_hdle *ioal_spi1);
/**
 * @brief This function transmit the data in SPI interface with blocking mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @param[in] pdata - pointer to a data
 * @param[in] size -  size of the data
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief This function receive the data from SPI interface with blocking mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @param[out] pdata - pointer to a data
 * @param[in] size -  size of the data
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_receive(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief This function transmit and receive the data
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @param[in] ptxdata - pointer to a data
 * @param[out]prxdata - pointer to a data
 * @param[in] size -  size of the data
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit_receive(ioal_spi_hdle *ioal_hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size, uint32 timeout);
/**
 * @brief This function transmit the data in SPI interface with interrupt mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @param[in] pdata - pointer to a data
 * @param[in] size -  size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit_it(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size);
/**
 * @brief This function receive the data from SPI interface with interrupt mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @param[out]pdata - pointer to a data
 * @param[in] size -  size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_receive_it(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size);
/**
 * @brief This function transmit and receive the data in interrupt mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @param[in] ptxdata - pointer to a data
 * @param[out]prxdata - pointer to a data
 * @param[in] size -  size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit_receive_it(ioal_spi_hdle *ioal_hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size);
/**
 * @brief This function transmit the data in SPI interface in DMA mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @param[in] pdata - pointer to a data
 * @param[in] size -  size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit_dma(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size);
/**
 * @brief This function receive the data from SPI interface in DMA mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @param[out]pdata - pointer to a data
 * @param[in] size -  size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_receive_dma(ioal_spi_hdle *ioal_hspi, uint8 *pdata, uint16 size);
/**
 * @brief This function transmit and receive the data in DMA mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @param[in] ptxdata - pointer to a data
 * @param[out]prxdata - pointer to a data
 * @param[in] size -  size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_transmit_receive_dma(ioal_spi_hdle *ioal_hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size);
/**
 * @brief This function abort the transmission of data in SPI interface
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_abort(ioal_spi_hdle *ioal_hspi);
/**
 * @brief This function abort the transmission of data in interrupt mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_abort_it(ioal_spi_hdle *ioal_hspi);
/**
 * @brief This function pause the transmission of data in DMA mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_dma_pause(ioal_spi_hdle *ioal_hspi);
/**
 * @brief This function resume the transmission of data in DMA mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_dma_resume(ioal_spi_hdle *ioal_hspi);
/**
 * @brief This function stop the transmission of data in DMA mode
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_dma_stop(ioal_spi_hdle *ioal_hspi);
/**
 * @brief This function register the callback event
 * @param[in] ioal_spi - ioal_spi pointer to a ioal_spi_hdle structure that
 * 					contains the configuration information for SPI
 * @param[in] cbid - ID of the callback event
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_spi_reg_cb(ioal_spi_hdle *ioal_hspi, iohal_stm32_spi_cbid cbid);

/* API Mapping */
#define io_hal_common_spi1_init 				io_hal_stm32f7xx_spi1_init
#define io_hal_common_spi_transmit 				io_hal_stm32f7xx_spi_transmit
#define io_hal_common_spi_receive 				io_hal_stm32f7xx_spi_receive
#define io_hal_common_spi_transmit_receive 		io_hal_stm32f7xx_spi_transmit_receive
#define io_hal_common_spi_transmit_it			io_hal_stm32f7xx_spi_transmit_it
#define io_hal_common_spi_receive_it			io_hal_stm32f7xx_spi_receive_it
#define io_hal_common_spi_transmit_receive_it	io_hal_stm32f7xx_spi_transmit_receive_it
#define io_hal_common_spi_transmit_dma			io_hal_stm32f7xx_spi_transmit_dma
#define io_hal_common_spi_receive_dma			io_hal_stm32f7xx_spi_receive_dma
#define io_hal_common_spi_transmit_receive_dma	io_hal_stm32f7xx_spi_transmit_receive_dma
#define io_hal_common_spi_abort 				io_hal_stm32f7xx_spi_abort
#define io_hal_common_spi_abort_it 				io_hal_stm32f7xx_spi_abort_it
#define io_hal_common_spi_dma_pause				io_hal_stm32f7xx_spi_dma_pause
#define io_hal_common_spi_dma_resume			io_hal_stm32f7xx_spi_dma_resume
#define io_hal_common_spi_dma_stop				io_hal_stm32f7xx_spi_dma_stop
#define io_hal_common_spi_reg_cb 				io_hal_stm32f7xx_spi_reg_cb

#endif /* _IO_AL_STM32F7XX_SPI_H_ */

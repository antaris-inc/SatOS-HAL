/**
 * @file exo_io_al_spi_common.h
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

#ifndef _IO_AL_SPI_COMMON_H_
#define _IO_AL_SPI_COMMON_H_

#include "exo_io_al_common.h"
#include "exo_hal_common.h"

#define SPI_INTF_ENB

/**
 * @brief IO-HAl SPI interface control block handle structure definition
 */
typedef struct _ioal_spi_hdle
{
    ioal_intf_gen_info intf_gen_info;						/*!< Hold general information of interface  						*/
    void (*spi_tx_cplt_cb)(struct _ioal_spi_hdle *hspi);    /*!< Hold Fn address for Transmit complete event					*/
    void (*spi_rx_cplt_cb)(struct _ioal_spi_hdle *hspi);    /*!< Hold Fn address for Receive complete event						*/
    void (*spi_tx_rx_cplt_cb)(struct _ioal_spi_hdle *hspi); /*!< Hold Fn address for Transmit and Receive complete event		*/
    void (*spi_abort_cplt_cb)(struct _ioal_spi_hdle *hspi); /*!< Hold Fn address for Abort complete event						*/
    void (*spi_error_cb)(struct _ioal_spi_hdle *hspi);      /*!< Hold Fn address for error event								*/
}ioal_spi_hdle;

/**
 * @brief This function initialize the SPI control block memory structure and
 * 			do basic configurations of SPI
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_init(void);
/**
 * @brief This function initialize the callback event
 * @param[in] hspi1 - hspi1 pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @retval HAL status
 */
void io_hal_spi1_cb_init(ioal_spi_hdle *hspi1);
/**
 * @brief This function transmit the data in SPI interface with blocking mode
 * @param[in] hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @param[in] pdata - pointer to a data
 * @param[in] size - size of the data
 * @param[in] timeout -  timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_transmit(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief This function receive the data from SPI interface with blocking mode
 * @param[in] hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @param[out]pdata - pointer to a data
 * @param[in] size - size of the data
 * @param[in] timeout -  timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_receive(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief This function transmit and receive the data
 * @param[in] hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @param[in] ptxdata - pointer to a data
 * @param[out]prxdata - pointer to a data
 * @param[in] size - size of the data
 * @param[in] timeout -  timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_transmit_receive(ioal_spi_hdle *hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size, uint32 timeout);
/**
 * @brief This function transmit the data in SPI interface with interrupt mode
 * @param[in] hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @param[in] pdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_transmit_it(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size);
/**
 * @brief This function receive the data from SPI interface with interrupt mode
 * @param[in] hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @param[out]pdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_receive_it(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size);
/**
 * @brief This function transmit and receive the data in interrupt mode
 * @param[in] hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @param[in] ptxdata - pointer to a data
 * @param[out]prxdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_transmit_receive_it(ioal_spi_hdle *hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size);
/**
 * @brief This function transmit the data in SPI interface in DMA mode
 * @param[in] hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @param[in] pdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_transmit_dma(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size);
/**
 * @brief This function receive the data from SPI interface in DMA mode
 * @param[in] hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @param[out]pdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_receive_dma(ioal_spi_hdle *hspi, uint8 *pdata, uint16 size);
/**
 * @brief This function transmit and receive the data in DMA mode
 * @param[in] hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @param[in] ptxdata - pointer to a data
 * @param[out]prxdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_transmit_receive_dma(ioal_spi_hdle *hspi, uint8 *ptxdata, uint8 *prxdata, uint16 size);
/**
 * @brief This function abort the transmission of data in SPI interface
 * @param hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_abort(ioal_spi_hdle *hspi);
/**
 * @brief This function pause the transmission of data in DMA mode
 * @param hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_dma_pause(ioal_spi_hdle *hspi);
/**
 * @brief This function resume the transmission of data in DMA mode
 * @param hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_dma_resume(ioal_spi_hdle *hspi);
/**
 * @brief This function stop the transmission of data in DMA mode
 * @param hspi - hspi pointer to a ioal_spi_hdle structure that contains
 *             the configuration information for SPI module
 * @retval HAL status
 */
hal_ret_sts io_hal_spi_dma_stop(ioal_spi_hdle *hspi);




#ifndef LINUX_TEMP_PORT

void check_spi1_dummy(ioal_spi_hdle *hspi);
#else
/**
 * @brief This is SPI interface dummy function for linux
 */
void linux_spi_dummy_fn(struct _ioal_spi_hdle *hspi);
#endif


#endif /* _IO_AL_SPI_COMMON_H_ */

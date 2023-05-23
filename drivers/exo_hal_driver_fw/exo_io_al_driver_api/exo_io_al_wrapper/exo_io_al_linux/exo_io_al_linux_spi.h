/*
 * @file exo_io_al_linux_spi.h
 *
 * @brief This file contains linux wrapper functions declarations for IO interface
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

#ifndef _IO_AL_LINUX_SPI_H_
#define _IO_AL_LINUX_SPI_H_

#include "exo_hal_common.h"
//#include "exo_io_al_i2c_common.h"


/**
 * @brief IO-HAL SPI1 initialization function for linux
 * @param[in] ioal_hspi1 - pointer to SPI1 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_spi1_init(void *ioal_hspi1);

/**
 * @brief IO-HAL SPI transmit function for linux
 * @param[in] ioal_hspi - pointer to SPI instance
 * @param[in] pdata - pointer to a buffer
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_spi_transmit(void *ioal_hspi, uint8 *pdata, uint16 size, uint32 timeout);

/**
 * @brief IO-HAL SPI receive function for linux
 * @param[in] ioal_hspi - pointer to SPI instance
 * @param[out]pdata - pointer to a buffer
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_spi_receive(void *ioal_hspi, uint8 *pdata, uint16 size, uint32 timeout);





#define io_hal_common_spi1_init 				io_hal_linux_spi1_init
#define io_hal_common_spi_transmit 				io_hal_linux_spi_transmit
#define io_hal_common_spi_receive 				io_hal_linux_spi_receive


#endif

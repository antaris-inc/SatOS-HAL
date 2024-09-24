/**
 * @file exo_io_al_fmc_nor_flash.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for FMC-NOR-FLASH interface
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

#define NOR_INTF_ENB

#include "exo_hal_io_al_common.h"
#include "exo_hal_common.h"


#ifndef LINUX_TEMP_PORT
#include "stm32f7xx_hal.h"
#endif


#define FMC_NOR_PAGE_SIZE 512 ///< FMC NOR page size

/**
 * @brief  This function initializes the control block memory and do the basic
 * configurations for FMC-NOR-FLASH
 * @param[in]  flsh_hdlr -  pointer to a FLASH module
 * @retval HAL status
 */
hal_ret_sts io_hal_fmc_nor_flash_init(void* flsh_hdlr);

/**
 * @brief  This function write data in NOR memory
 * @param[in]  flsh_hdlr -  pointer to a FLASH module
 * @param[in]  w_address - Address to be written in the flash
 * @param[in]  data - pointer to write data
 * @param[in]  data_len - length of the data in bytes
 * @retval HAL status
 */
hal_ret_sts io_hal_fmc_nor_flash_write(void* flsh_hdlr, uint32_t w_address, uint8_t *data, uint32_t data_len);

/**
 * @brief  This function read data from NOR memory
 * @param[in]  flsh_hdlr -  pointer to a FLASH handle
 * @param[in]  r_address - Address to be read from the flash
 * @param[out] data - pointer to read data
 * @param[in]  data_len - length of the data in bytes
 * @retval HAL status
 */
hal_ret_sts io_hal_fmc_nor_flash_read(void* flsh_hdlr, uint32_t r_address, uint8_t *data, uint32_t data_len);

/**
 * @brief  This function erase the specified block of the NOR memory
 * @param[in]  flsh_hdlr - pointer to a FLASH handle
 * @param[in]  b_address - Block to erase address
 * @retval HAL status
 */
hal_ret_sts io_hal_fmc_nor_flash_erase_block(void* flsh_hdlr, uint32_t b_address);

/**
 * @brief This function erase the entire NOR chip.
 * @param[in]  flsh_hdlr -  pointer to a FLASH handle
 * @retval  HAL status
 */
hal_ret_sts io_hal_fmc_nor_flash_erase_chip(void* flsh_hdlr);


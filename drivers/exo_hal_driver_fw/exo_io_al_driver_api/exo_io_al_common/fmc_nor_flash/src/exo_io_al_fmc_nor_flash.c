/**
 * @file exo_io_al_fmc_nor_flash.c
 *
 * @brief This file contains abstracted function definition for FMC-NOR-FLASH interface
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

#include "exo_io_al_fmc_nor_flash.h"
#include "exo_osal.h"

#ifndef LINUX_TEMP_PORT

NOR_IDTypeDef nor_esign;

uint8_t nor_buff[FMC_NOR_PAGE_SIZE*2];

/**
 * @brief  This API initializes the control block memory
 * and do the basic configurations for FMC-NOR-FLASH
 */
hal_ret_sts io_hal_fmc_nor_flash_init(void* flsh_hdlr)
{
    HAL_StatusTypeDef sts;
    sts = HAL_NOR_Read_ID((NOR_HandleTypeDef*)flsh_hdlr,&nor_esign);
    return sts;

}

/**
 * @brief  This API write data in FMC-NOR-FLASH
 */
hal_ret_sts io_hal_fmc_nor_flash_write(void* flsh_hdlr, uint32_t w_address, uint8_t *data, uint32_t data_len)
{
    HAL_StatusTypeDef sts =0;
    int count;
    uint32_t end_addr, current_size, current_addr;

    current_size = FMC_NOR_PAGE_SIZE - (w_address % (FMC_NOR_PAGE_SIZE));

    if (current_size > data_len)
    {
        current_size = data_len;
    }

    current_addr = w_address - NOR_MEMORY_ADRESS1;
    if(current_addr>=0)
    {
        end_addr = (w_address-NOR_MEMORY_ADRESS1) + data_len;
        HAL_NOR_WriteOperation_Enable((NOR_HandleTypeDef*)flsh_hdlr);

        do
        {
            os_delay(15);

            if(current_size==FMC_NOR_PAGE_SIZE)
            {
                for(count=0;count<FMC_NOR_PAGE_SIZE*2;count++)
                {
                    nor_buff[count]=data[count];
                }
            }
            else
            {
                for(count=0;count<current_size;count++)
                {
                    nor_buff[count]=data[count];
                }
            }
            HAL_NOR_ProgramBuffer((NOR_HandleTypeDef*)flsh_hdlr,current_addr,(uint16_t*)nor_buff,current_size);
            os_delay(10);

            current_addr += current_size*2;
            data += current_size*2;
            current_size = ((current_addr + FMC_NOR_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : FMC_NOR_PAGE_SIZE;
        } while (current_addr < end_addr);
    }
    else
    {
        sts=0;
    }
    return sts;

}

/**
 * @brief  This API read data from FMC-NOR-FLASH
 */
hal_ret_sts io_hal_fmc_nor_flash_read(void* flsh_hdlr, uint32_t r_address, uint8_t *data, uint32_t data_len)
{
    HAL_StatusTypeDef sts;
    HAL_NOR_WriteOperation_Enable((NOR_HandleTypeDef*)flsh_hdlr);
    HAL_NOR_ReturnToReadMode((NOR_HandleTypeDef*)flsh_hdlr);
    sts=HAL_NOR_ReadBuffer((NOR_HandleTypeDef*)flsh_hdlr,r_address,(uint16_t*)data,data_len);
    return sts;

}

/**
 * @brief  This API erase the specified block of the NOR memory
 */
hal_ret_sts io_hal_fmc_nor_flash_erase_block(void* flsh_hdlr, uint32_t b_address)
{
    HAL_StatusTypeDef sts;
    HAL_NOR_WriteOperation_Enable((NOR_HandleTypeDef*)flsh_hdlr);
    sts=HAL_NOR_Erase_Block((NOR_HandleTypeDef*)flsh_hdlr,b_address, 0);
    return sts;
}

/**
 * @brief  This API erase the entire NOR chip.
 */
hal_ret_sts io_hal_fmc_nor_flash_erase_chip(void* flsh_hdlr)
{
    HAL_StatusTypeDef sts;
    HAL_NOR_WriteOperation_Enable((NOR_HandleTypeDef*)flsh_hdlr);
    sts=HAL_NOR_Erase_Chip((NOR_HandleTypeDef*)flsh_hdlr,0);
    return sts;
}

#endif

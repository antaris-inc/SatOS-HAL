/**
 * @file exo_osal_mem_debug.c
 *
 * @brief This file contains function definitions for memory debugging.
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

#include <stdint.h>
#include "exo_osal_mem_debug.h"
#include "exo_common.h"
#include "exo_osal_mem_cpy.h"
#include "exo_osal.h"
#ifndef LINUX_TEMP_PORT
#include "exo_types.h"
#include "FreeRTOS.h"
#endif

uint8_t mem_debug_data;
uint32_t obc_mem_debug_tm_enc_frame;
#ifndef LINUX_TEMP_PORT
#define PLACE_IN_FMC
#define PLACE_IN_QSPI
uint8_t PLACE_IN_SDRAM_FTP obc_mem_debug_sdram_test_array[OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH];
uint8_t PLACE_IN_FMC obc_mem_debug_fmc_nor_flash_test_array[OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH];
uint8_t PLACE_IN_QSPI obc_mem_debug_qspi_nor_flash_test_array[OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH];
#else
uint8_t obc_mem_debug_sdram_test_array[OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH];
uint8_t obc_mem_debug_fmc_nor_flash_test_array[OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH];
uint8_t obc_mem_debug_qspi_nor_flash_test_array[OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH];
#endif

/**
 * @brief This API is used to test the requested memory by writing 
 * and reading using test different pattern
 */
static uint8_t test_func(uint8_t* addr)
{
    uint8_t sts;
    uint8_t write_buff[OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH],read_buff[OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH];
    os_memset((uint8_t*)write_buff,MEM_TEST_PATTERN_A,OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH);
    obc_memcpy_wrapper(write_buff,addr,OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH,NULL,1,1);
    obc_memcpy_wrapper(addr,read_buff,OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH,NULL,1,1);
    for(uint8_t i=0;i<OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH;i++)
    {
        if(write_buff[i] != read_buff[i])
        {
            sts = 0;
            break;
        }
        sts = 1;
    }
    os_memset((uint8_t*)read_buff,0x00,OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH);
    os_memset((uint8_t*)read_buff,0x00,OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH);
    if(sts == 1)
    {
        os_memset((uint8_t*)write_buff,MEM_TEST_PATTERN_B,OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH);
        obc_memcpy_wrapper((uint8_t*)write_buff,addr,OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH,NULL,1,1);
        obc_memcpy_wrapper(addr,(uint8_t*)read_buff,OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH,NULL,1,1);
        for(uint8_t i=0;i<OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH;i++)
        {
            if(write_buff[i] != read_buff[i])
            {
                sts = 0;
                break;
            }
            sts = 1;
        }
    }
    return sts;
}

/**
 * @brief This API returns the encoded data frame
 */
uint8_t obc_mem_debug_tm_pack_data()
{
    return obc_mem_debug_tm_enc_frame ;

}

/**
 * @brief This API decode the test command and call the respective memory test function
 */
int8_t obc_mem_debug_tc_decode(void *mem_type_1)
{
    uint8_t sts;
    os_thread_handle_ptr temp = (os_thread_handle_ptr)mem_type_1;
    uint8_t* ptr = temp->app_entry_args;
    mem_debug_data = (*ptr >> 4 & 0x0f);
    printf("dataptr %d\n",*ptr);
    printf("mem_deug %d\n",mem_debug_data);
    switch(mem_debug_data)
    {
        case e_mem_debug_sdram_test:
            {
                printf("The memory type is : %d\n",mem_debug_data);
                sts = test_func(obc_mem_debug_sdram_test_array);
                obc_mem_debug_tm_enc_frame = mem_debug_data << 4 & 0xf0;
                obc_mem_debug_tm_enc_frame = obc_mem_debug_tm_enc_frame | (sts<<3);
            }
            break;

        case e_mem_debug_fmc_nor_flash_test:
            {
                printf("The memory type is : %d\n",mem_debug_data);
                sts = test_func(obc_mem_debug_fmc_nor_flash_test_array);
                obc_mem_debug_tm_enc_frame = mem_debug_data << 4 & 0xf0;
                obc_mem_debug_tm_enc_frame = obc_mem_debug_tm_enc_frame | (sts<<3);
            }
            break;

        case e_mem_debug_qspi_nor_flash_test:
            {
                printf("The memory type is : %d\n",mem_debug_data);
                sts = test_func(obc_mem_debug_qspi_nor_flash_test_array);
                obc_mem_debug_tm_enc_frame = mem_debug_data << 4 & 0xf0;
                obc_mem_debug_tm_enc_frame = obc_mem_debug_tm_enc_frame | (sts<<3);
            }
            break;

        case e_iram_heap_availablity_test:
            {
#ifndef LINUX_TEMP_PORT
                obc_mem_debug_tm_enc_frame = xPortGetFreeHeapSize();
#else
                /* Dummy value for Linux environment */
                obc_mem_debug_tm_enc_frame = 1000;
#endif
            }
            break;

        default:
            printf("test:%d\n",mem_debug_data);
            break;
    }
    os_free(ptr);
    ptr = NULL;
    os_thread_delete(OBC_MEM_DEBUG_TC);
    return 1;

}


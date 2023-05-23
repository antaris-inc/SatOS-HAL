/**
 * @file exo_osal_mem_debug.h
 *
 * @brief This file contains enumeration and function prototypes
 *        for memory debugging.
 *
 *  @copyright Copyright 2023 Antaris, Inc.
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
 *
 */

#ifndef EXO_OS_EXO_OSAL_MEMORY_MANAGEMENT_INC_EXO_OSAL_MEM_DEBUG_H_
#define EXO_OS_EXO_OSAL_MEMORY_MANAGEMENT_INC_EXO_OSAL_MEM_DEBUG_H_

#include "stdint.h"
#include "stdio.h"

#define OBC_MEMORY_DEBUG_TEST_BYTE_LENGTH 10      ///< length of the buffer in bytes
#define MEM_TEST_PATTERN_A 0x55                   ///< Memory test pattern type A
#define MEM_TEST_PATTERN_B 0xAA                   ///< Memory test pattern type B

/**
 * @brief Different memory type enumeration.
 */
typedef enum
{
    e_mem_debug_sdram_test=1,          /*!< Memory type SDRAM  				*/
    e_mem_debug_fmc_nor_flash_test,    /*!< Memory type FMC NOR flash   	*/
    e_mem_debug_qspi_nor_flash_test,   /*!< Memory type QSPI NOR flash 		*/
    e_iram_heap_availablity_test,      /*!< check heap availability 	 			*/
    e_max_memory_flash                 

}obc_debug_mem_type_e;

/**
 * @brief This API decode the test command and call the respective memory test function
 * @param[in]  mem_type_1 : Type of memory
 * @return success status
 */
int8_t obc_mem_debug_tc_decode(void *mem_type_1);

/**
 * @brief This API returns the encoded data frame
 * @return Return the telemetry frame
 */
uint8_t obc_mem_debug_tm_pack_data();

#endif /* EXO_OS_EXO_OSAL_MEMORY_MANAGEMENT_INC_EXO_OSAL_MEM_DEBUG_H_ */

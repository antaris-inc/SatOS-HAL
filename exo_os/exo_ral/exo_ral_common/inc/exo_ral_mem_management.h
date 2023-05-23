/**
 * @file exo_ral_mem_management.h
 *
 * @brief This file contains abstracted function prototypes for memory management.
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
#ifndef RAL_MEM_MANAGEMENT_H_
#define RAL_MEM_MANAGEMENT_H_

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "exo_ral_cmn.h"

/**
 * @brief This function is used for allocating a block of memory
 *
 * @param[in]  byte_size : Byte size for allocation
 *
 * @return void pointer
 */
void* ral_malloc(uint32_t  byte_size);

/**
 * @brief This API use to release the allocated memory
 *
 * @param[in]  ptr : pointer to memory to get freed
 */
void  ral_free(void* ptr);

/**
 * @brief This API use to load the memory block with given value
 *
 * @param[in]  ptr : pointer to memory
 * @param[in]  val : value to be load
 * @param[in]  num_bytes : size of memory block in bytes
 * @return void pointer
 */
void* ral_memset(void *ptr, int val, size_t num_bytes);

/**
 * @brief This API to copy data from one memory location to another
 *        memory location
 *
 * @param[in]  destination_ptr : pointer to destination
 * @param[in]  src_ptr : pointer to source
 * @param[in]  num_bytes : size of memory block in bytes
 * @return void pointer
 */
void* ral_memcpy(void* destination_ptr, const void* src_ptr, size_t num_bytes);


#endif /*RAL_MEM_MANAGEMENT_H_*/

/**
 * @file exo_ral_mem_management.c
 *
 * @brief This file contains abstracted function definitions for memory management.
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

#include "exo_ral_mem_management.h"

/*!
 *  @brief This function is used for allocating a block of memory
 */
void* ral_malloc(uint32_t  byte_size)
{
    return(malloc(byte_size));
}

/*!
 *  @brief This API use to release the allocated memory
 */
void ral_free(void* ptr)
{
    return(free(ptr));
}

/*!
 * @brief This API use to load the memory block with given value
 */
void* ral_memset(void *ptr, int val, size_t num_bytes )
{
    return(memset(ptr, val, num_bytes));
}

/*!
 * @brief This API to copy data from one memory location to another
 *        memory location
 */
void* ral_memcpy(void* destination_ptr, const void * src_ptr, size_t num_bytes)
{
    return(memcpy(destination_ptr,src_ptr, num_bytes));
}

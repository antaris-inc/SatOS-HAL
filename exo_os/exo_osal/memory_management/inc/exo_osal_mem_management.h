/**
 * @file exo_osal_mem_management.h
 *
 * @brief This file contains function prototypes for memory management.
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
 */

#ifndef OSAL_MEM_MANAGEMENT_H_
#define OSAL_MEM_MANAGEMENT_H_

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "exo_ral_cmn.h"
#include <stdio.h>

/**
 * @brief This API use to release the allocated memory.
 *
 * @param  ptr : pointer to memory to get freed
 * @param  file_name : pointer to file name
 * @param  line_num : Line number
 */
void os_free_debug(void *ptr,char *file_name, uint32_t line_num);

/**
 * @brief This function is used for allocating a block of memory in SDRAM.
 *
 * @param[in]  byte_size : Byte size for allocation
 *
 * @return pointer to allocated memory
 */
void* os_malloc_eram(uint32_t byte_size);

/**
 * @brief This API use to load the memory block with given value
 *
 * @param[in]  ptr : pointer to memory
 * @param[in]  val : value to be load
 * @param[in]  num_bytes : size of memory block in bytes
 * @return pointer to memory
 */
void* os_memset(void *ptr, int val, size_t num_bytes);

/**
 * @brief This API to copy data from one memory location to another
 *        memory location
 *
 * @param[in]  destination_ptr : pointer to destination
 * @param[in]  src_ptr : pointer to source
 * @param[in]  num_bytes : size of memory block in bytes
 * @return pointer to allocated memory
 */
void* os_memcpy(void * destination_ptr, const void * src_ptr, size_t num_bytes);

#ifndef LINUX_TEMP_PORT
#define MEM_DEBUG_ENB                              ///< Enable memory debugging
#define MEM_FILE_LOG                               ///< Enable memory file log
#define MEM_LEAK_TRACKER_ENB                       ///< Enable memory leak tracker
#if defined(COREBOARD) || defined(LINUX_TEMP_PORT)
#define MEM_TRAC_DRAM                              ///< Enable DRAM memory tracker
#endif
#endif

#define FAIL_FLAG_OFST (30)                        ///< Fail flag offset
#define FREE_STS_FLAG_OFST (31)                    ///< Free status flag offset

/**
 * @brief Memory track handle structure definition
 */
typedef struct mem_alloc_track
{
    uint32_t time_stamp;               /*!< Memory allocated time */
    /* [31:31] - Free flag (1-means freed),  [30:30] -  Fail flag, [29:0] - Length, */
    uint32_t len;                      /*!< Allocated memory length in bytes */
    void *ptr;                         /*!< Pointer to allocate a memory */
    char *file_name;                   /*!< File name */
    uint32_t line_number;              /*!< Line number */
}s_mem_alloc_track;

/**
 * @brief Memory deallocate track structure definition
 */
typedef struct mem_freec_track
{
    uint32_t time_stamp;               /*!< Memory deallocated time */
    /* [30:0] - Length, [31:31] -  Fail flag*/
    uint32_t len;                      /*!< Deallocated memory length in bytes */
    void *ptr;                         /*!< Pointer to deallocate a memory */
}s_mem_free_track;

/**
 * @brief Memory tracker structure definition
 */
typedef struct mem_tracker
{
    s_mem_alloc_track *mem_alloc_info;          /*!< pointer to memory allocation structure */
    s_mem_free_track *mem_free_info;            /*!< pointer to memory deallocation structure */
}s_mem_info;

/**
 * @brief This API Initialize the memory debugging tracker.
 */
void mem_debug_tracker_init(void);

/**
 * @brief API to store the deallocation information to the structure.
 *
 * @param[in]  ptr : pointer to memory
 * @param[in]  len : length of deallocation memory
 * @param[in]  fail_sts : Fail status
 */
void append_mem_free_track(void *ptr, uint32_t len, uint8_t fail_sts);

/**
 * @brief API to store the allocation information to the structure.
 *
 * @param[in]  ptr : pointer to memory
 * @param[in]  fail_sts : Fail status
 * @param[in]  file_name : pointer to file name
 * @param[in]  line_num : Block of memory
 */
void append_mem_alloc_track(void *ptr, uint32_t len, uint8_t fail_sts, char* file_name, uint32_t line_num);

/**
 * @brief This API use to update the free status flag to deallocate structure.
 *
 * @param[in]  ptr : pointer to memory
 * @param[in]  file_name : pointer to file name
 * @param[in]  line : Block of memory
 */
void mem_free_flag_upd(void *ptr,uint8_t *file_name, uint32_t line);

/**
 * @brief This API use to print the memory leak information.
 */
void print_mem_leak(void);

/**
 * @brief This API use to print the allocated memory information.
 */
void print_mem_alloc_info(void);

/**
 * @brief This API use to print the deallocated memory information.
 */
void print_mem_free_info(void);

/**
 * @brief This API allocate and reset the memory then store allocation
 *         information to the structure.
 *
 * @param[in]  ptr : pointer to memory
 * @param[in]  val : value to be load
 * @param[in]  num_bytes : size of memory block in bytes
 * @return pointer to allocated memory
 */
void *os_calloc_debug(uint32_t nmemb,uint32_t byte_size,char *file_name, uint32_t line_num);

/**
 * @brief This API allocate and reset the memory.
 *
 * @param[in]  nmemb : Memory
 * @param[in]  byte_size : Byte size for allocation
 * @return pointer to allocated memory
 */
void *os_calloc_api(uint32_t nmemb,uint32_t byte_size);

/**
 * @brief This API allocate the memory then store allocation
 *         information to the structure.
 *
 * @param[in] size : size of allocated memory
 * @param[in] file_name : pointer to file name
 * @param[in] line_num : line number for memory debug
 * @return pointer to allocated memory
 */
void *os_malloc_debug(uint32_t size,char *file_name, uint32_t line_num);

/**
 * @brief This API allocate the memory.
 *
 * @param[in]  byte_size : Byte size for allocation
 *
 * @return pointer to allocated memory
 */
void *os_malloc_api(uint32_t byte_size);

/**
 * @brief Memory file logging
 */
#ifdef MEM_FILE_LOG
#define os_malloc(size) os_malloc_debug(size, __FILE__ , __LINE__)
#define os_calloc(nmemb,size) os_calloc_debug(nmemb, size, __FILE__ , __LINE__)
#define os_free(ptr) os_free_debug(ptr, __FILE__ , __LINE__)
#else
#define os_malloc(size) os_malloc_api(size)
#define os_calloc(nmemb,size) os_calloc_api(nmemb, size)
#define os_free(ptr) os_free_debug(ptr, NULL ,__LINE__)
#endif

#endif /*OSAL_MEM_MANAGEMENT_H_*/

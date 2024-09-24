/**
 * @file exo_osal_mem_management.c
 *
 * @brief This file contains function definitions for OS memory management.
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
#include <stdio.h>
#include "exo_osal_mem_management.h"
#ifndef LINUX_TEMP_PORT
#include "exo_types.h"
#include "FreeRTOSConfig.h"
#endif

#define HEAP_WARN_THRES (2)
volatile uint8_t mem_dbg_init = 0;
uint8_t print_mem_warn_flag = 0;

#ifdef MEM_DEBUG_ENB
uint32_t mem_alloc_track_idx=0;
uint32_t mem_free_track_idx=0;
s_mem_info mem_info;

#if defined(COREBOARD) || defined(LINUX_TEMP_PORT)
#define MAX_MALLOC_TRACK_CNT (1000)
#else
#define MAX_MALLOC_TRACK_CNT (100)
#endif

#ifdef MEM_TRAC_DRAM
s_mem_alloc_track PLACE_IN_SDRAM_MEM mem_alloc_info[MAX_MALLOC_TRACK_CNT];
s_mem_free_track PLACE_IN_SDRAM_MEM mem_free_info[MAX_MALLOC_TRACK_CNT];
#define MEM_TRACKER_DRAM_ALLOC_START_ADDRESS (&mem_alloc_info)
#define MEM_TRACKER_DRAM_FREE_START_ADDRESS (&mem_free_info)
#else
s_mem_alloc_track mem_alloc_info[MAX_MALLOC_TRACK_CNT];
s_mem_free_track mem_free_info[MAX_MALLOC_TRACK_CNT];
#define MEM_TRACKER_DRAM_ALLOC_START_ADDRESS (&mem_alloc_info)
#define MEM_TRACKER_DRAM_FREE_START_ADDRESS (&mem_free_info)
#endif

/**
 * @brief This API Initialize the memory debugging tracker.
 */
void mem_debug_tracker_init(void)
{
    mem_info.mem_alloc_info = (s_mem_alloc_track *)MEM_TRACKER_DRAM_ALLOC_START_ADDRESS;
    mem_info.mem_free_info = (s_mem_free_track *)MEM_TRACKER_DRAM_FREE_START_ADDRESS;
    mem_alloc_track_idx=0;
    mem_free_track_idx=0;
    memset(mem_info.mem_alloc_info, 0, MAX_MALLOC_TRACK_CNT*sizeof(s_mem_alloc_track));
    memset(mem_info.mem_free_info, 0, MAX_MALLOC_TRACK_CNT*sizeof(s_mem_free_track));
    mem_dbg_init = 1;
}

/**
 * @brief API to store the deallocation information to the structure.
 */
void append_mem_free_track(void *ptr, uint32_t len, uint8_t fail_sts)
{
    if(mem_info.mem_free_info != NULL)
    {
        mem_info.mem_free_info[mem_free_track_idx%MAX_MALLOC_TRACK_CNT].time_stamp = 10;
        mem_info.mem_free_info[mem_free_track_idx%MAX_MALLOC_TRACK_CNT].len = len | (fail_sts << FAIL_FLAG_OFST);
        mem_info.mem_free_info[mem_free_track_idx%MAX_MALLOC_TRACK_CNT].ptr = ptr;
        mem_free_track_idx++;
    }
}

/**
 * @brief API to store the allocation information to the structure.
 */
void append_mem_alloc_track(void *ptr, uint32_t len, uint8_t fail_sts, char* file_name, uint32_t line_num)
{
    if(mem_info.mem_alloc_info != NULL)
    {
        mem_info.mem_alloc_info[mem_alloc_track_idx%MAX_MALLOC_TRACK_CNT].time_stamp = 5;
        mem_info.mem_alloc_info[mem_alloc_track_idx%MAX_MALLOC_TRACK_CNT].len = len | (fail_sts << FAIL_FLAG_OFST);
        mem_info.mem_alloc_info[mem_alloc_track_idx%MAX_MALLOC_TRACK_CNT].ptr = ptr;
        mem_info.mem_alloc_info[mem_alloc_track_idx%MAX_MALLOC_TRACK_CNT].file_name = file_name;
        mem_info.mem_alloc_info[mem_alloc_track_idx%MAX_MALLOC_TRACK_CNT].line_number = line_num;
        mem_alloc_track_idx++;
    }
}

#ifdef MEM_LEAK_TRACKER_ENB
/**
 * @brief This API use to update the free status flag to deallocate structure.
 */
void mem_free_flag_upd(void *ptr,uint8_t *file_name, uint32_t line)
{
    uint8_t upd_sts = 1;
    uint32_t idx = (mem_alloc_track_idx % MAX_MALLOC_TRACK_CNT) - 1;
    int i;
    for(i=idx; i>=0; i--)
    {
        if(mem_info.mem_alloc_info[i].time_stamp == 0)
        {
            break;
        }
        if(mem_info.mem_alloc_info[i].ptr == ptr)
        {
            if(mem_info.mem_alloc_info[i].len >> FREE_STS_FLAG_OFST)
            {
                printf("WARN Already ptr may be freed %p idx %d LEN %lu File %s ",ptr,i,line,file_name);
            }
            else
            {
                mem_info.mem_alloc_info[i].len |= (1 << FREE_STS_FLAG_OFST);
                upd_sts =0;
                break;
            }
        }
    }
    if(upd_sts)
    {
        for(i=MAX_MALLOC_TRACK_CNT-1; i>idx; i--)
        {
            if(mem_info.mem_alloc_info[i].time_stamp == 0)
            {
                break;
            }
            if(mem_info.mem_alloc_info[i].ptr == ptr)
            {
                if(mem_info.mem_alloc_info[i].len >> FREE_STS_FLAG_OFST)
                {
                    printf("WARN Already ptr may be freed %p idx %d LEN %lu File %s ",ptr,i,line,file_name);
                }
                else
                {
                    mem_info.mem_alloc_info[i].len |= (1 << FREE_STS_FLAG_OFST);
                    upd_sts =0;
                    break;
                }
            }

        }
    }
    if(upd_sts)
    {
        printf("WARN Freed ptr may not be allocated or already freed %p LEN %lu File %s ",ptr,line, file_name);
    }
}

/**
 * @brief This API use to print the memory leak information.
 */
void print_mem_leak(void)
{
    uint8_t upd_sts = 1;
    uint32_t idx = (mem_alloc_track_idx % MAX_MALLOC_TRACK_CNT) - 1;
    int i;
    for(i=idx; i>=0; i--)
    {
        if(mem_info.mem_alloc_info[i].time_stamp)
        {
            if(0 == (mem_info.mem_alloc_info[i].len & (1 << FREE_STS_FLAG_OFST)))
            {
                printf("\r\n MLEAK ts:%lu ptr:%p, siz:%lu file_name:%s line_num:%ld", \
                        mem_info.mem_alloc_info[i].time_stamp , \
                        mem_info.mem_alloc_info[i].ptr, \
                        mem_info.mem_alloc_info[i].len,mem_info.mem_alloc_info[i].file_name,mem_info.mem_alloc_info[i].line_number);
            }
        }
        else
        {
            upd_sts =0;
            break;
        }
    }
    if(upd_sts)
    {
        for(i=MAX_MALLOC_TRACK_CNT-1; i>idx; i--)
        {
            if(mem_info.mem_alloc_info[i].time_stamp)
            {
                if(0 == (mem_info.mem_alloc_info[i].len & (1 << FREE_STS_FLAG_OFST)))
                {
                    printf("\r\n MLEAK ts:%lu ptr:%p, siz:%lu file_name:%s line_num:%ld", \
                            mem_info.mem_alloc_info[i].time_stamp , \
                            mem_info.mem_alloc_info[i].ptr, \
                            mem_info.mem_alloc_info[i].len,mem_info.mem_alloc_info[i].file_name,mem_info.mem_alloc_info[i].line_number);
                }
            }
            else
            {
                upd_sts =0;
                break;
            }
        }
    }
}
#else
void print_mem_leak(void)
{
    printf("No MEM leak analyzer enabled");
}
#endif

#endif
/**
 * @brief This API allocate and reset the memory then store allocation
 *         information to the structure.
 */
void *os_calloc_debug(uint32_t nmemb,uint32_t byte_size,char *file_name, uint32_t line_num)
{
    void * ptr =  os_malloc_debug(nmemb * byte_size,file_name, line_num);
    if(ptr)
    {
        os_memset((uint8_t *)ptr,0,byte_size);
    }
    return ptr;
}

/**
 * @brief This API allocate the memory then store allocation
 *         information to the structure.
 */
void *os_malloc_debug(uint32_t byte_size,char *file_name, uint32_t line_num)
{
    void * ptr = NULL;
    ptr = os_malloc_api(byte_size);
#ifdef MEM_DEBUG_ENB

    if(mem_dbg_init)
    {
        if(ptr)
        {
            append_mem_alloc_track(ptr,byte_size,0,file_name,line_num);
        }
        else
        {
            append_mem_alloc_track(ptr,byte_size,1,file_name,line_num);
            printf("\r\nM_F F_N: %s Ln: %ld Le: %lu ",file_name,line_num,byte_size);
#ifdef MEM_LEAK_TRACKER_ENB
            print_mem_leak();
#endif
        }
    }

#endif
    return ptr;
}

/**
 * @brief This API allocate and reset the memory.
 */
void *os_calloc_api(uint32_t nmemb,uint32_t byte_size)
{
    void * ptr =  os_malloc_api(nmemb * byte_size);
    if(ptr)
    {
        os_memset((uint8_t *)ptr,0,byte_size);
    }
    return ptr;
}

/**
 * @brief This API allocate the memory.
 */
void *os_malloc_api(uint32_t byte_size)
{
    void * ptr = NULL;
#ifdef LINUX_TEMP_PORT
    ptr = malloc(byte_size);
#else
    if(byte_size % 4)
    {
        byte_size = (((byte_size +4) >>2) << 2);
    }
    ptr = (void *)pvPortMalloc(byte_size);
#endif
    return ptr;
}

/**
 * @brief This API use to release the allocated memory
 */
void os_free_debug(void *ptr,char *file_name, uint32_t line_num)
{
    if(ptr)
    {
#ifdef LINUX_TEMP_PORT
        free(ptr);
#ifdef MEM_DEBUG_ENB
        append_mem_free_track(ptr,0,0);
#ifdef MEM_LEAK_TRACKER_ENB
        mem_free_flag_upd(ptr,file_name, line_num);
#endif
    }
#endif
#else
    if( 1 == is_valid_addr_heap_range(ptr))
    {
        vPortFree(ptr);
        uint32_t remain_heap_size =xPortGetFreeHeapSize();
        if(remain_heap_size >=  (configTOTAL_HEAP_SIZE>>HEAP_WARN_THRES))
        {
            print_mem_warn_flag=0;
        }
#ifdef MEM_DEBUG_ENB
        append_mem_free_track(ptr,0,0);
#ifdef MEM_LEAK_TRACKER_ENB
        mem_free_flag_upd(ptr,(uint8_t*)file_name, line_num);
#endif
#endif
    }
    else if (1 == is_valid_addr_eram_heap_range(ptr))
    {
        vPortFree_eram(ptr);
    }
    else
    {
        printf("Err Invalid Free Pointer called %p Line %lu File %s ", ptr,line_num, file_name );
    }
#endif
}
else
{
#ifndef LINUX_TEMP_PORT
    printf("Err NULL Pointer free called Line %lu File %s",line_num, file_name);
#endif
}
}

/**
 * @brief This API use to load the memory block with given value
 */
void* os_memset(void *ptr, int val, size_t num_bytes)
{
    return(memset(ptr, val, num_bytes));
}

/**
 * @brief This API to copy data from one memory location to another
 *        memory location
 */
void* os_memcpy(void * destination_ptr, const void * src_ptr, size_t num_bytes)
{
    return(memcpy(destination_ptr,src_ptr, num_bytes));
}

/**
 * @brief This function is used for allocating a block of memory in SDRAM.
 */
void* os_malloc_eram(uint32_t byte_size)
{
    void * ptr = NULL;
#ifndef LINUX_TEMP_PORT
    if(byte_size % 4)
    {
        byte_size = (((byte_size +4) >>2) << 2);
    }
    ptr = (void *)pvPortMalloc_eram(byte_size);
#else
    ptr = os_malloc_api(byte_size);
#endif
    return ptr;
}

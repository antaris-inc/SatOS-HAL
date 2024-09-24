/**
 * @file exo_debug.h
 *
 * @brief This file contains structure definition for error handler also
 *  function prototype. 
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
 *  
 *
 */
#ifndef _EXO_DEBUG_H_
#define _EXO_DEBUG_H_


#define MAX_DBG_SIZE (256)

#define MAX_DBG_IDX (20)

/**
 * @brief  EXO error status enumeration
 */
typedef enum
{
    UNKNOWN_ERROR,
    SW_TEST_RESET,
    SW_OTSU_RESET,
    IRAM_HEAP_MEMORY_FULL,
    SRAM_HEAP_MEMORY_FULL,
    QUEUE_SRAM_HEAP_MEMORY_FULL,
    CPU_NMI_UNHANDLED_FAULT,
    CPU_HARD_FAULT,
    CPU_MEM_MNGT_ERR,
    CPU_BUS_FAULT,
    CPU_USAGE_FAULT,
    LWIP_ASSERT,
    CSPLIB_ASSERT,
    RTOS_ASSERT,
    EARLY_WDT_TIMER_ASSERT,
    ERR_HDLR_MAX_SIZE_EXCEED,

}e_exo_err;


typedef struct {
    uint8_t reserved[16];
}s_exo_hwd_debug ;

typedef struct {
    uint8_t  last_thread_id_exec; /** cpu mode[7:7] 0-task,1-irq; thread id [6:0]*/
    uint16_t reset_cause; /** 4-bits for cause, 12-bits for error code */
    uint64_t boot_rtc_time; /** utc epouch time format */
    uint64_t shutdown_rtc_time; /** utc epouch time format */
    uint32_t sram_avail_heap_size;
    uint32_t iram_avail_heap_size;
    uint8_t reserved[16];
}s_exo_swd_debug ;

typedef struct {
    uint8_t reserved[16];
}s_exo_sen_debug ;

typedef struct {
    s_exo_hwd_debug hw_dbg;
    s_exo_swd_debug sw_dbg;
    s_exo_sen_debug sen_dbg;
}s_exo_debug;

extern s_exo_debug exo_dbg_cb;

/** Catch All error here and does reboot with necessary shutdown actions */
void exo_err_hdlr(uint8_t err_no);

#define EXO_ASSERT(err_no) exo_err_hdlr(err_no)

#endif /* _EXO_DEBUG_H_ */

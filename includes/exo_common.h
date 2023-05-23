/**
 * @file exo_common.h
 *
 * @brief This file contains definition for common structures, enumeration.
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
 *
 */
#ifndef _EXO_COMMON_H_
#define _EXO_COMMON_H_
#include "stdint.h"

#include "exo_debug.h"

#define T_STACK_1K  ( 1*1024)
#define T_STACK_2K  ( 2*1024)
#define T_STACK_4K  (   4096)
#define T_STACK_5K  ( 5*1024)
#define T_STACK_8K  ( 8*1024)
#define T_STACK_10K (10*1024)

#define T_MAIN_STACK_SIZE  					( 512)
#define T_OSAL_TEST_STACK_SIZE  			( 512)
#define T_OSAL_MEM_STACK_SIZE     			T_STACK_4K
#define T_SENSOR_STACK_SIZE    				T_STACK_5K

#define RTC_HR    4
#define RTC_MIN   6
#define RTC_SEC   0
#define RTC_DATE  10
#define RTC_MON   (2 - 1)  // Do not remove -1 
#define RTC_YEAR  (2023 - 1900) // Do not remove 1900

#define EXT_SDRAM_BUFF_SENSOR_ENB
#define EXT_SDRAM_BUFF_EPS_ENB

#ifndef UNUSED
#define UNUSED(X) (void)X
#endif

/**
 * @brief task ID enumeration
 */
typedef enum
{
    OS_TIMER,
    ETHERNET_TASK,
    USB_TASK,
    EPS_TASK,
    OBC_MEMCPY_THREAD,
    IDLE_TASK,
    OBC_MEM_DEBUG_TC,
    OBC_SENSOR_HDLR,
    OS_TASK_MAX
}e_exo_task_id;

/**
 * @brief task priority enumeration*/
typedef enum
{
    P_IDLE                     = 1,
    P_OBC_MEMCPY_THREAD	          ,
    P_DEFAULT_PRIO              =10,
    P_OBC_SENSOR_HDLR             ,
    P_OBC_MAIN                    ,
    P_EPS                         ,
    P_OS_TIMER                    ,
    P_OS_TASK_MAX
}e_exo_task_priority;

extern volatile uint8_t EPS_PS_ON_DEFLT_DISABLE ;
extern volatile uint8_t EPS_HRM_ON_DEFLT ;
extern volatile uint8_t CAN_BYPASS_SOCK_DISABLE ;

extern uint8_t kernel_init_done;

#endif /* _EXO_COMMON_H_ */

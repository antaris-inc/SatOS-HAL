/**
 * @file exo_common.h
 *
 * @brief This file contains definition for common structures, enumeration.
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
 */
#ifndef _EXO_COMMON_H_
#define _EXO_COMMON_H_
#include "stdint.h"

#include "exo_debug.h"

#define ETH_INTF_ENB

#define DEBUG_CPRINT(x) do {printf x;} while(0)
#define CPRINT_VARIABLE_UNUSED(x)

#define T_STACK_1K  ( 1*1024)  ///< Stack 1k
#define T_STACK_2K  ( 2*1024)  ///< Stack 2k
#define T_STACK_4K  (   4096)  ///< Stack 3k
#define T_STACK_5K  ( 5*1024)  ///< Stack 4k
#define T_STACK_8K  ( 8*1024)  ///< Stack 8k
#define T_STACK_10K (10*1024)  ///< Stack 10k

#define T_MAIN_STACK_SIZE            ( 512) ///< Main stack size
#define T_OSAL_TEST_STACK_SIZE       ( 512) ///< OSAL test stack size
#define T_OSAL_MEM_STACK_SIZE        T_STACK_4K ///< OSAL memory stack size
#define T_SENSOR_STACK_SIZE          T_STACK_5K ///< sensor stack size
#define T_COMMS_UHF_STACK_SIZE       T_STACK_5K ///< UHF stack size
#define T_COMMS_UHF_TX_STACK_SIZE    T_STACK_5K ///< UHF TX stack size
#define T_COMMS_RX_STACK_SIZE        T_STACK_5K ///< COMMS RX stack size
#define T_HAL_INTR_SIZE              T_STACK_5K ///< HAL interface size

#define RTC_HR    4  ///< RTC hour
#define RTC_MIN   6  ///< RTC minute
#define RTC_SEC   0  ///< RTC seconds
#define RTC_DATE  10 ///< RTC date
#define RTC_MON   (2 - 1)  ///< RTC month Do not remove -1
#define RTC_YEAR  (2023 - 1900) ///< RTC year Do not remove 1900

#define EXT_SDRAM_BUFF_SENSOR_ENB ///< External SDRAM buffer sensor enable
#define EXT_SDRAM_BUFF_EPS_ENB ///< External SDRAM buffer EPS enable

#define TC_ID_IDX              0 ///< TC ID index
#define TC_LEN_IDX             2 ///< TC length index
#define TC_PLD_IDX             4 ///< TC payload index

#define TM_ID_IDX              0 ///< TM ID index
#define TM_LEN_IDX             2 ///< TM length index
#define TM_PLD_IDX             4 ///< TM payload index

#ifndef UNUSED
#define UNUSED(X) (void)X
#endif

//socket details
typedef struct obc_sock_info
{
    char ip_addr[16];
    unsigned short port;
}s_obc_sock_info;

extern s_obc_sock_info obc_uhf_soc_inf;

extern volatile uint8_t EPS_PS_ON_DEFLT_DISABLE; ///< EPS PS on default disable
extern volatile uint8_t EPS_HRM_ON_DEFLT; ///< EPS HRM on default
extern volatile uint8_t CAN_BYPASS_SOCK_DISABLE; ///< CAN bypass socket disable

extern uint8_t kernel_init_done; ///< kernal initialize done flag

/*MACRO defined to check whether the NVM value is within range*/

#define RANGE_CHECK_AND_ASSIGN(value,min,max,def_val) \
        ((value>=min)&&(value<=max))?value:def_val

/**
 * @enum e_exo_task_id
 * @brief Enumeration for various task IDs in the system.
 *
 * This enum represents different task identifiers used within the system.
 */
typedef enum
{
    OS_TIMER,            /*!< Task ID for the OS timer */
    CSP_TASK,            /*!< Task ID for the CSP task */
    CSP_TASK1,           /*!< Task ID for the CSP task 1 */
    CSP_TASK2,           /*!< Task ID for the CSP task 2 */
    CSP_TASK3,           /*!< Task ID for the CSP task 3 */
    CSP_ETH_RX,          /*!< Task ID for the CSP Ethernet receive task */
    ETHERNET_TASK,       /*!< Task ID for the Ethernet task */
    USB_TASK,            /*!< Task ID for the USB task */
    EPS_TASK,            /*!< Task ID for the EPS task */
    LWIP_MBOX_TASK,      /*!< Task ID for the LWIP mailbox task */
    LWIP_TASK,           /*!< Task ID for the LWIP task */
    COMMS_RX,            /*!< Task ID for the communications receive task */
    COMMS_UHF_CTLR,      /*!< Task ID for the UHF controller task */
    COMMS_UHF_TX,        /*!< Task ID for the UHF transmit task */
    OBC_MEMCPY_THREAD,   /*!< Task ID for the OBC memcpy thread */
    IDLE_TASK,           /*!< Task ID for the idle task */
    OBC_MEM_DEBUG_TC,    /*!< Task ID for the OBC memory debug task */
    OBC_SENSOR_HDLR,     /*!< Task ID for the OBC sensor handler task */
    HAL_INTR_HDLR,       /*!< Task ID for the hardware interrupt handler */
    OS_TASK_MAX          /*!< Maximum number of OS tasks */
} e_exo_task_id;

/**
 * @enum e_exo_task_priority
 * @brief Enumeration for task priorities in the system.
 *
 * This enum defines various task priorities used in the system, with specific
 * priority levels assigned to different tasks.
 */
typedef enum
{
    P_IDLE                     = 1,  /*!< Priority for the idle task */
    P_OBC_MEMCPY_THREAD         ,     /*!< Priority for the OBC memcpy thread */
    P_DEFAULT_PRIO              = 10, /*!< Default task priority */
    P_COMMS_UHF_CTLR            ,     /*!< Priority for the communications UHF controller */
    P_COMMS_UHF_TX              ,     /*!< Priority for the communications UHF transmitter */
    P_COMMS_UHF_RX              ,     /*!< Priority for the communications UHF receiver */
    P_COMMS_RX                  ,     /*!< Priority for the communications receiver */
    P_LWIP                      ,     /*!< Priority for the LWIP task */
    P_LWIP_MBOX                 ,     /*!< Priority for the LWIP mailbox task */
    P_CSP_ROUTE                 ,     /*!< Priority for the CSP routing task */
    P_USB                       ,     /*!< Priority for the USB task */
    P_CSP_INTF_UART_RX          ,     /*!< Priority for the CSP UART interface receiver */
    P_CSP_INTF_CAN_RX           ,     /*!< Priority for the CSP CAN interface receiver */
    P_CSP_INTF_ETH_RX           ,     /*!< Priority for the CSP Ethernet interface receiver */
    P_UART_RX                   ,     /*!< Priority for the UART receiver */
    P_ETHERNET                  ,     /*!< Priority for the Ethernet task */
    P_HAL_INTR_HDLR             ,     /*!< Priority for the hardware interrupt handler */
    P_OS_TIMER                  ,     /*!< Priority for the OS timer task */
    P_OS_TASK_MAX               /*!< Maximum number of OS tasks */
} e_exo_task_priority;

/**
 * @brief Enumerations for hardware device status
 */
typedef enum
{
    PWR_OFF     = 0,  /*!< Power off */
    PWR_ON  = 1,  /*!< Power ON */
    PWR_RSTRT   = 2,  /*!< Power restart */
    PWR_BOOT    = 3,  /*!< Power boot */
    PWR_SD  = 4,  /*!< Power SD */
    PWR_ERR  /*!< Power error */
}dev_hw_sts_s;

#endif /* _EXO_COMMON_H_ */

/**
 * @file exo_osal_thread.h
 *
 * @brief This file contains structure, function prototypes for OS thread management.
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

#ifndef os_THREAD_H_
#define os_THREAD_H_

#include <stddef.h>
#include "exo_osal_queue.h"
#include "exo_osal_common.h"

#define MAX_ITC_Q_LEN 25      ///< Maximum Queue length for ITC

typedef void(*app_entry_func_t)(void* args);
typedef void(*app_init_func_t)(void* args);

/**
 * @brief OS queue information structure definition
 */
typedef struct
{
    os_queue_handle_ptr itc_queue_id;   /*!< Identity of queue */
    uint16_t queue_length;              /*!< Number of item*/
    size_t item_size;                   /*!< Size of the item in bytes*/

}os_itc_queue_info_t;

/**
 * @brief OS Thread handle structure definition
 */
typedef struct
{
    app_entry_func_t app_entry_func;         /*!< Thread entry function pointer */
    app_init_func_t app_init_func;           /*!< Thread initialize function pointer */
    os_itc_queue_info_t* queue_info_t;       /*!< pointer to queue information */
    void* app_entry_args;                    /*!< pointer to entry function argument */
    void* app_init_args;                     /*!< pointer to Init function argument */
    ral_thread_handle_ptr ral_thread_handle; /*!< pointer to RAL thread handle */

}os_thread_handle_t;

/**
 * @brief OS thread handle pointer type definition
 */
typedef os_thread_handle_t *os_thread_handle_ptr ;
/**
 * @brief OS tick time pointer type definition
 */
typedef uint32_t os_tick_time_t;

#include "exo_osal_itc.h"
#define MAX_ITC_Q_ITEM_SIZE sizeof(os_itc_msg_handle_t)   ///< Maximum item count for ITC message

/**
 * @brief Function to create the thread
 *
 * @param[in]  task_id : Identity of thread task
 * @param[in]  stack_size : size for stack in bytes
 * @param[in]  priority : priority of thread
 * @param[in]  thread_name : pointer to name of the thread
 * @param[in]  entry_func : Entry function pointer to thread
 * @param[in]  parameter : pointer to default parameter
 *
 * @return status of thread creation
 *
 * @retval ral_success->success, ral_error->error
 */
os_status_t os_thread_create(uint8_t task_id,uint32_t stack_size,os_thread_priority_t priority,const char* thread_name,app_entry_func_t app_entry_func,void* entry_args,app_init_func_t app_init_func,void* init_args);

/**
 * @brief Function to delete the thread
 *
 * @param[in]  task_id : Identity of thread task
 *
 * @return status of thread deletion
 */
os_status_t os_thread_delete(uint8_t task_id);

/**
 * @brief Function puts the thread from running to waiting state
 *
 * @param[in]  task_id : Identity of thread task
 *
 * @return status of thread suspend
 *
 * @retval ral_success->success, ral_error->error
 */
os_status_t os_thread_suspend(uint8_t task_id);

/**
 * @brief Function use to resume the thread
 *
 * @param[in]  task_id : Identity of thread task
 *
 * @return status of thread resume
 *
 * @retval ral_success->success, ral_error->error
 */
os_status_t os_thread_resume(uint8_t task_id);

/**
 * @brief This API to create thread delay
 *
 * @param[in]  tick_time : waiting to certain time
 *
 * @return status of delay
 *
 * @retval ral_success->success, ral_error->error
 */
os_status_t os_delay(os_tick_time_t tick_time);

/**
 * @brief This API to get the thread handle.
 *
 * @param[in]  task_id : Identity of thread.
 *
 * @return status of thread
 */
os_thread_handle_ptr os_get_thread_hdl(uint8_t task_id);

/**
 * @brief This API to get the queue id for given thread handle.
 *
 * @param[in]  tick_time : waiting to certain time
 *
 * @return status of queue
 */
os_queue_handle_ptr os_get_queue_id(uint8_t task_id);
#endif /*os_THREAD_H_*/

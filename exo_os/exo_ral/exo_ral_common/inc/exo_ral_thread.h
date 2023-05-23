/**
 * @file exo_ral_thread.h
 *
 * @brief This file contains abstracted function prototypes and structure for thread
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
#ifndef RAL_THREAD_H
#define RAL_THREAD_H

#include "exo_ral_cmn.h"
#define MAX_TASK_NAME_LEN 20

typedef void(*ral_thread_entry_func_t)(void* args);
typedef int ral_thread_priority_t;

/**
 * @brief  thread handle structure definition
 */
typedef struct
{
    const char* thread_name;            /*!< Thread name */
    uint32_t stack_size;                /*!< stack size in bytes */
    ral_thread_priority_t priority;     /*!< Thread priority */
    ral_thread_entry_func_t entry_func; /*!< Thread entry function pointer */
    void* parameter;                    /*!< pointer to the parameters for thread entry functions */
    void* rtos_thread_handle;           /*!< Pointer to RTOS thread handle */
}ral_thread_handle;

typedef ral_thread_handle *ral_thread_handle_ptr;

/**
 * @brief This function create the thread
 *
 * @param[in]  ral_thread_id : Double pointer to Identity of thread
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
ral_status_t ral_thread_create(ral_thread_handle_ptr *ral_thread_id ,
        uint32_t stack_size, ral_thread_priority_t priority,
        const char* thread_name, ral_thread_entry_func_t entry_func,
        void *parameters);

/**
 * @brief This API to create thread delay
 *
 * @param[in]  tick_time : waiting to certain time
 *
 * @return status of delay
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_delay(ral_tick_time_t tick_time);

/**
 * @brief This function delete the thread
 *
 * @param[in]  ral_thread_id : pointer to thread handle
 *
 * @return status of thread deletion
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_thread_delete(ral_thread_handle_ptr ral_thread_id );

/**
 * @brief This function puts the thread from running to waiting state
 *
 * @param[in]  ral_thread_id : pointer to thread handle
 *
 * @return status of thread suspend
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_thread_suspend(ral_thread_handle_ptr ral_thread_id);

/**
 * @brief This function use to resume the thread
 *
 * @param[in]  ral_thread_id : pointer to thread handle
 *
 * @return status of thread resume
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_thread_resume(ral_thread_handle_ptr ral_thread_id);

/**
 * @brief This function get the thread state
 *
 * @param[in]  ral_thread_id : pointer to thread handle
 *
 * @return status of thread state
 *
 * @retval ral_success->success, ral_error->error
 */
ral_thread_state_t ral_thread_get_state(ral_thread_handle_ptr ral_thread_id);

/**
 * @brief This function get the thread name
 *
 * @param[in]  ral_thread_id : pointer to thread handle
 */
const char* ral_thread_get_name(ral_thread_handle_ptr ral_thread_id);

/**
 * @brief This function set the thread priority level
 *
 * @param[in]  ral_thread_id : pointer to thread handle
 * @param[in]  new_priority_level : change the thread priority
 *
 * @return status of set thread priority level
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_thread_set_priority_level(ral_thread_handle_ptr ral_thread_id,
        ral_thread_priority_t new_priority_level);

/**
 * @brief This function get the thread priority level
 *
 * @param[in]  ral_thread_id : pointer to thread handle
 *
 * @return status of priority level
 *
 * @retval ral_success->success, ral_error->error
 */
ral_thread_priority_t ral_thread_get_priority_level(ral_thread_handle_ptr ral_thread_id);

/**
 * @brief This function get the thread stack size
 *
 * @param[in]  ral_thread_id : pointer to thread handle
 *
 * @return status of stack size
 *
 * @retval ral_success->success, ral_error->error
 */
uint32_t ral_thread_get_stack_size(ral_thread_handle_ptr ral_thread_id);

/**
 * @brief This function get the remaining thread stack size
 *
 * @param[in]  ral_thread_id : pointer to thread handle
 *
 * @return status of remaining stack size
 *
 * @retval ral_success->success, ral_error->error
 */
uint32_t ral_thread_get_stack_remaining_size(ral_thread_handle_ptr ral_thread_id);

/**
 * @brief This API handle the thread delay time
 *
 * @param[in]  tick_time : waiting to certain time
 *
 * @return status of thread delay
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_thread_delay_until(ral_tick_time_t tick_time);

#endif /*RAL_THREAD_H*/

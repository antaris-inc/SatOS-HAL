/**
 * @file exo_ral_thread_common.c
 *
 * @brief This file contains abstracted function definitions for thread managing.
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
#include "exo_ral_thread.h"
#include "exo_os_common.h"

/*!
 *  @brief This function create the thread
 */
ral_status_t ral_thread_create(ral_thread_handle_ptr *ral_thread_id,
        uint32_t stack_size,ral_thread_priority_t priority,
        const char* thread_name,ral_thread_entry_func_t entry_func,
        void *parameters)
{
    ral_status_t sts;
    *ral_thread_id=(ral_thread_handle_ptr)ral_malloc(sizeof(ral_thread_handle));
    (*ral_thread_id)->thread_name=thread_name;
    (*ral_thread_id)->stack_size=stack_size;
    (*ral_thread_id)->priority=priority;
    (*ral_thread_id)->entry_func=entry_func;
    (*ral_thread_id)->parameter=parameters;
    sts= ral_common_thread_create(ral_thread_id, (*ral_thread_id)->stack_size,
            (*ral_thread_id)->priority, (*ral_thread_id)->thread_name,
            (*ral_thread_id)->entry_func, (*ral_thread_id)->parameter);
    return(sts);

}

/*!
 *  @brief This function delete the thread
 */
ral_status_t ral_thread_delete(ral_thread_handle_ptr ral_thread_id )
{
    ral_status_t sts;
    sts=ral_common_thread_delete(ral_thread_id);
    ral_free(ral_thread_id);
    return(sts);
}

/*!
 *  @brief This API to create thread delay
 */
ral_status_t ral_delay(ral_tick_time_t tick_time)
{
    ral_status_t sts;
    sts=ral_common_thread_delay(tick_time);
    return(sts);
}

/*!
 *  @brief This function puts the thread from running to waiting state
 */
ral_status_t ral_thread_suspend(ral_thread_handle_ptr ral_thread_id)
{
    ral_status_t sts;
    sts=ral_common_thread_suspend(ral_thread_id);
    return(sts);
}

/*!
 *  @brief This function deletes the queue and release its memory
 */
ral_status_t ral_thread_resume(ral_thread_handle_ptr ral_thread_id )
{
    ral_status_t sts;
    sts=ral_common_thread_resume(ral_thread_id);
    return(sts);
}


/**
 * @file exo_ral_rsrc_sync_common.c
 *
 * @brief This file contains abstracted function definitions for semaphore and mutex.
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

#include "exo_ral_rsrc_sync.h"
#include "exo_ral_thread.h"
#include "exo_os_common.h"

/*!
 *  @brief This function create binary semaphore
 */
ral_status_t ral_sem_create_bin(ral_sem_handle_ptr *ral_sem_id)
{
    ral_status_t sts;
    *ral_sem_id=(ral_sem_handle_ptr)ral_malloc(sizeof(ral_sem_handle_t));
    (*ral_sem_id)->sem_type=0;
    (*ral_sem_id)->sem_max_value=1;
    (*ral_sem_id)->sem_initial_value=0;
    (*ral_sem_id)->sem_curr_value=0;
    sts=ral_common_sem_create_bin(ral_sem_id);
    return(sts);
}

/*!
 *  @brief This function create counting semaphore
 */
ral_status_t ral_sem_create_count(ral_sem_handle_ptr *ral_sem_id,
        int max_count, int start_val)
{
    ral_status_t sts;
    *ral_sem_id=(ral_sem_handle_ptr)ral_malloc(sizeof(ral_sem_handle_t));
    (*ral_sem_id)->sem_type=1;
    (*ral_sem_id)->sem_max_value=max_count;
    (*ral_sem_id)->sem_initial_value=start_val;
    (*ral_sem_id)->sem_curr_value=start_val;
    sts=ral_common_sem_create_count(ral_sem_id, (*ral_sem_id)->sem_max_value,
            (*ral_sem_id)->sem_initial_value);
    return(sts);
}

/*!
 *  @brief This function delete the semaphore
 */
ral_status_t ral_sem_delete(ral_sem_handle_ptr ral_sem_id )
{
    ral_status_t sts;
    ral_free(ral_sem_id);
    sts=ral_common_sem_delete(ral_sem_id);
    return(sts);
}

/*!
 *  @brief This function acquire the semaphore
 */
ral_status_t ral_sem_take(ral_sem_handle_ptr ral_sem_id,
        ral_tick_time_t tick_time)
{
    ral_status_t sts;
    sts=ral_common_sem_take(ral_sem_id, tick_time);
    return(sts);
}

/*!
 *  @brief This function release the semaphore
 */
ral_status_t ral_sem_give(ral_sem_handle_ptr ral_sem_id)
{
    ral_status_t sts;
    sts=ral_common_sem_give(ral_sem_id);
    return(sts);
}

/*!
 *  @brief This function gives the current value of the semaphore
 */
ral_status_t ral_sem_get_count(ral_sem_handle_ptr ral_sem_id, uint32_t* count)
{
    ral_status_t sts;
    sts=ral_common_sem_get_count(ral_sem_id, count);
    return(sts);
}

/*!
 *  @brief This function creates the mutex
 */
ral_status_t ral_mutex_create(ral_mutex_handle_ptr *ral_mtx_id)
{
    ral_status_t sts;
    *ral_mtx_id=(ral_mutex_handle_ptr)ral_malloc(sizeof(ral_mutex_handle_t));
    sts=ral_common_mutex_create(ral_mtx_id);
    return(sts);

}

/*!
 *  @brief This function delete the mutex
 */
ral_status_t ral_mutex_delete(ral_mutex_handle_ptr ral_mtx_id)
{
    ral_free(ral_mtx_id);
    ral_status_t sts;
    sts=ral_common_mutex_delete(ral_mtx_id);
    return(sts);
}

/*!
 *  @brief This function release the mutex
 */
ral_status_t ral_mutex_give(ral_mutex_handle_ptr ral_mtx_id)
{
    ral_status_t sts;
    sts=ral_common_mutex_give(ral_mtx_id);
    return(sts);
}

/*!
 *  @brief This function acquire the mutex
 */
ral_status_t ral_mutex_take(ral_mutex_handle_ptr ral_mtx_id,
        ral_tick_time_t timeout_ticks)
{
    ral_status_t sts;
    sts=ral_common_mutex_take(ral_mtx_id, timeout_ticks);
    return(sts);
}

/*!
 *  @brief This function get the owner of the mutex
 */
ral_status_t ral_mutex_get_owner(ral_mutex_handle_ptr ral_mtx_id,
        ral_thread_handle_ptr thread_id)
{
    ral_status_t sts;
    sts=ral_common_mutex_get_owner(ral_mtx_id, thread_id);
    return(sts);
}


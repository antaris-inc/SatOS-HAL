/**
 * @file exo_ral_linux_rsrc_sync.c
 *
 * @brief This file contains functions of linux for semaphore and mutex.
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

#include <semaphore.h>
#include "exo_os_common.h"

/*!
 * @brief Linux wrapper function to create the binary semaphore
 */
ral_status_t ral_linux_sem_create_bin(ral_sem_handle_ptr *id)
{
    sem_t *bin_sem_ptr;
    bin_sem_ptr=(sem_t*)ral_malloc(sizeof(sem_t));
    int bin_sem_sts=sem_init(bin_sem_ptr,0,1);
    if(bin_sem_sts==0)
    {
        (*id)->rtos_sem_handle = (void*)bin_sem_ptr;
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief Linux wrapper function to create the counting semaphore
 */
ral_status_t ral_linux_sem_create_count(ral_sem_handle_ptr *id, int max_count, int start_val)
{
    sem_t *count_sem_ptr;
    count_sem_ptr=(sem_t*)ral_malloc(sizeof(sem_t));
    int count_sem_sts=sem_init(count_sem_ptr,0,start_val);
    if(count_sem_sts==0)
    {
        (*id)->rtos_sem_handle=(void*)count_sem_ptr;
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief Linux wrapper function to delete the semaphore
 */
ral_status_t ral_linux_sem_delete(ral_sem_handle_ptr id )
{
    sem_t *sem_id = (sem_t*)id->rtos_sem_handle;
    int sem_sts=sem_destroy(sem_id);
    if(sem_sts==0)
    {
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief Linux wrapper function to acquire the semaphore
 */
ral_status_t ral_linux_sem_take(ral_sem_handle_ptr id, ral_tick_time_t tick_time)
{
    sem_t *sem_id = (sem_t*)id->rtos_sem_handle;
    int sem_sts=sem_wait(sem_id);
    if(sem_sts==0)
    {
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief Linux wrapper function to release the semaphore
 */
ral_status_t ral_linux_sem_give(ral_sem_handle_ptr id)
{
    sem_t *sem_id = (sem_t*)id->rtos_sem_handle;
    int sem_sts = sem_post(sem_id);
    if(sem_sts==0)
    {
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief Linux wrapper function to get the current value of the semaphore
 */
ral_status_t ral_linux_sem_get_count(ral_sem_handle_ptr id, uint32_t* count)
{
    //uint32_t sem_count;
    sem_t *sem_id = (sem_t*)id->rtos_sem_handle;
    int sem_sts=sem_getvalue(sem_id,(int*)count);
    if(sem_sts==0)
    {
        //*count=sem_count;
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief Linux wrapper function to create the mutex
 */
ral_status_t ral_linux_mutex_create(ral_mutex_handle_ptr *id)
{
    sem_t *bin_mutex_ptr;
    bin_mutex_ptr=(sem_t*)ral_malloc(sizeof(sem_t));
    int bin_mutex_sts=sem_init(bin_mutex_ptr,0,1);
    if(bin_mutex_sts==0)
    {
        (*id)->rtos_mutex_handle = (void*)bin_mutex_ptr;
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief Linux wrapper function to delete the mutex
 */
ral_status_t ral_linux_mutex_delete(ral_mutex_handle_ptr id )
{
    sem_t *sem_id = (sem_t*)id->rtos_mutex_handle;
    int sem_sts=sem_destroy(sem_id);
    if(sem_sts==0)
    {
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief Linux wrapper function to acquire the mutex
 */
ral_status_t ral_linux_mutex_take(ral_mutex_handle_ptr id, ral_tick_time_t tick_time)
{
    sem_t *sem_id = (sem_t*)id->rtos_mutex_handle;
    int sem_sts=sem_wait(sem_id);
    if(sem_sts==0)
    {
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief Linux wrapper function to release the mutex
 */
ral_status_t ral_linux_mutex_give(ral_mutex_handle_ptr id)
{
    sem_t *sem_id = (sem_t*)id->rtos_mutex_handle;
    int sem_sts = sem_post(sem_id);
    if(sem_sts==0)
    {
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief Linux wrapper function to get the mutex owner task id
 */
ral_status_t ral_linux_mutex_get_owner(ral_mutex_handle_ptr id, ral_thread_handle_ptr thread_id)
{
    //todo
    return ral_success;
}


/**
 * @file exo_ral_cmsis_rsrc_sync_.c
 *
 * @brief This file contains wrapper functions of CMSIS RTOS v2 for
 *  semaphore and mutex.
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

#include "exo_os_common.h"

/*!
 * @brief This function create the binary semaphore
 */
ral_status_t ral_cmsis_sem_create_bin(ral_sem_handle_ptr *id)
{
    osSemaphoreId_t sem_bin;
    sem_bin=osSemaphoreNew (1U, 1U, NULL);
    if(sem_bin!=NULL)
    {
        (*id)->rtos_sem_handle = (void*)sem_bin;
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief This function create the counting semaphore
 */
ral_status_t ral_cmsis_sem_create_count(ral_sem_handle_ptr *id, int max_count,
		                                                         int start_val)
{
    osSemaphoreId_t countbin;
    countbin = osSemaphoreNew (max_count,start_val, NULL);
    if(countbin!=NULL)
    {
        (*id)->rtos_sem_handle=(ral_sem_handle_ptr)countbin;
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief This function delete the semaphore
 */
ral_status_t ral_cmsis_sem_delete(ral_sem_handle_ptr id )
{
    osStatus_t sts;
    osSemaphoreId_t sem_id = (osSemaphoreId_t)id->rtos_sem_handle;
    sts=osSemaphoreDelete (sem_id);
    switch(sts)
    {
        case osOK:
            return ral_success;
        case osErrorParameter:
            return ral_err_invld_arg;
        case osErrorResource:
        case osErrorISR:
            return ral_error;
        default:
            return ral_error;
            break;
     }
}

/*!
 * @brief This function acquire the semaphore
 */
ral_status_t ral_cmsis_sem_take(ral_sem_handle_ptr id, ral_tick_time_t tick_time)
{
    osStatus_t sts;
    osSemaphoreId_t sem_id = (osSemaphoreId_t)id->rtos_sem_handle;
    sts=osSemaphoreAcquire (sem_id, tick_time);
    switch(sts)
    {
        case osOK:
            return ral_success;
        case osErrorParameter:
            return ral_err_invld_arg;
        case osErrorResource:
            return ral_error;
        case osErrorTimeout:
            return ral_err_timeout;
        default:
            return ral_error;
            break;
     }
}

/*!
 * @brief This function release the semaphore
 */
ral_status_t ral_cmsis_sem_give(ral_sem_handle_ptr id)
{
    osStatus_t sts;
    osSemaphoreId_t sem_id = (osSemaphoreId_t)id->rtos_sem_handle;
    sts=osSemaphoreRelease(sem_id);
    switch(sts)
    {
        case osOK:
            return ral_success;
        case osErrorParameter:
            return ral_err_invld_arg;
        case osErrorResource:
            return ral_error;
        case osErrorTimeout:
            return ral_err_timeout;
        default:
            return ral_error;
            break;
     }
}

/*!
 * @brief This function gives the current value of the semaphore
 */
ral_status_t ral_cmsis_sem_get_count(ral_sem_handle_ptr id, uint32_t* count)
{
    uint32_t sem_count;
    osSemaphoreId_t sem_id=(osSemaphoreId_t)id->rtos_sem_handle;
    sem_count=osSemaphoreGetCount (sem_id);
    if(sem_count>0)
    {
    	*count=sem_count;
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief This function create the mutex
 */
ral_status_t ral_cmsis_mutex_create(ral_mutex_handle_ptr *id)
{
    osMutexId_t mtx_id;
    mtx_id=osMutexNew (NULL);
    if(mtx_id!=NULL)
    {
        (*id)->rtos_mutex_handle=(void*)mtx_id;
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief This function delete the mutex
 */
ral_status_t ral_cmsis_mutex_delete(ral_mutex_handle_ptr id)
{
    osStatus_t sts;
    osMutexId_t mtx_id = (osMutexId_t)id->rtos_mutex_handle;
    sts=osMutexDelete (mtx_id);
    switch(sts)
    {
        case osOK:
            return ral_success;
        case osErrorParameter:
            return ral_err_invld_arg;
        case osErrorResource:
        case osErrorISR:
            return ral_error;
        default:
            return ral_error;
            break;
     }
}

/*!
 * @brief This function release the mutex
 */
ral_status_t ral_cmsis_mutex_give(ral_mutex_handle_ptr id)
{
    osStatus_t sts;
    osMutexId_t mtx_id = (osMutexId_t)id->rtos_mutex_handle;
    sts=osMutexRelease (mtx_id);
    switch(sts)
    {
        case osOK:
            return ral_success;
        case osErrorParameter:
            return ral_err_invld_arg;
        case osErrorResource:
            return ral_error;
        case osErrorTimeout:
            return ral_err_timeout;
        default:
            return ral_error;
            break;
     }
}

/*!
 * @brief This function acquire the mutex
 */
ral_status_t ral_cmsis_mutex_take(ral_mutex_handle_ptr id,
		                             ral_tick_time_t tick_time)
{
    osStatus_t sts;
    osMutexId_t mtx_id = (osMutexId_t)id->rtos_mutex_handle;
    sts=osMutexAcquire (mtx_id, tick_time);
    switch(sts)
    {
        case osOK:
            return ral_success;
        case osErrorParameter:
            return ral_err_invld_arg;
        case osErrorResource:
            return ral_error;
        case osErrorTimeout:
            return ral_err_timeout;
        default:
            return ral_error;
            break;
     }
}

/*!
 * @brief this function gives the mutex owner task id
 */
ral_status_t ral_cmsis_mutex_get_owner(ral_mutex_handle_ptr id,
		                           ral_thread_handle_ptr thread_id)
{
    osThreadId_t task_id;
    osMutexId_t mtx_id = (osMutexId_t)id->rtos_mutex_handle;
    task_id=osMutexGetOwner (mtx_id);
    if(task_id!=NULL)
    {
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

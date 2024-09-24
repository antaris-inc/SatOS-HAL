/**
 * @file exo_ral_cmsis_queue.c
 *
 * @brief This file contains wrapper functions of CMSIS RTOS v2 for queue management.
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

#include "exo_os_common.h"
#include "cmsis_os2.h"

/*!
 * @brief This function create the queue
 */
ral_status_t ral_cmsis_queue_create(ral_queue_handle_ptr *id,uint32_t no_of_item, uint32_t item_size)
{
    osMessageQueueId_t queue_id;
    queue_id=osMessageQueueNew (no_of_item,item_size,NULL);
    if(queue_id==NULL)
    {
        return ral_error;
    }
    else
    {
        (*id)->rtos_queue_handle = (void*)queue_id;
        return ral_success;
    }
}

/*!
 * @brief This function delete the queue and release its memory
 */
ral_status_t ral_cmsis_queue_delete(ral_queue_handle_ptr id)
{
    osStatus_t sts;
    osMessageQueueId_t queue_id=(osMessageQueueId_t)id->rtos_queue_handle;
    sts= osMessageQueueDelete (queue_id);
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
 * @brief This function flush all the messages from the queue
 */
ral_status_t ral_cmsis_queue_flush(ral_queue_handle_ptr id)
{
    osStatus_t sts;
    osMessageQueueId_t queue_id=(osMessageQueueId_t)id->rtos_queue_handle;
    sts=osMessageQueueReset(queue_id);
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
 * @brief This function enqueue the data from queue
 */
ral_status_t ral_cmsis_queue_send(ral_queue_handle_ptr id, void *msg_ptr, ral_tick_time_t tick_time)
{
    osStatus_t sts;
    osMessageQueueId_t queue_id=(osMessageQueueId_t)id->rtos_queue_handle;
    sts=osMessageQueuePut (queue_id,msg_ptr,0U,tick_time);
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
 * @brief This function dequeue the data from queue
 */
ral_status_t ral_cmsis_queue_receive(ral_queue_handle_ptr id, void *msg_ptr ,ral_tick_time_t tick_time)
{
    osStatus_t sts;
    osMessageQueueId_t queue_id=(osMessageQueueId_t)id->rtos_queue_handle;
    sts= osMessageQueueGet(queue_id, msg_ptr, NULL,tick_time);
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
 * @brief This API get the number of elements that are actually in the queue.
 */
uint32_t ral_cmsis_queue_get_count(ral_queue_handle_ptr id)
{
    osMessageQueueId_t queue_id=(osMessageQueueId_t)id->rtos_queue_handle;
    return osMessageQueueGetCount(queue_id);
}
/*!
 * @brief This function get remaining number of element in the queue
 */
uint32_t ral_cmsis_queue_get_remain_count(ral_queue_handle_ptr id)
{
    osMessageQueueId_t queue_id=(osMessageQueueId_t)id->rtos_queue_handle;
    return osMessageQueueGetSpace(queue_id);
}


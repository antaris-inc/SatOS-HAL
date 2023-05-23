/**
 * @file exo_ral_linux_queue.c
 *
 * @brief This file contains functions of linux for queue.
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
#include "linux_queue.h"

/*!
 * @brief Linux wrapper function to create the queue
 */
ral_status_t ral_linux_queue_create(ral_queue_handle_ptr *id,uint32_t no_of_item, uint32_t item_size)
{
    ral_status_t sts=ral_error;
    pthread_queue_t *q_hdl = (pthread_queue_t *)ral_malloc(sizeof(pthread_queue_t));
    q_hdl=pthread_queue_create(no_of_item,item_size);
    if(q_hdl!=NULL)
    {
        (*id)->rtos_queue_handle = (void*)q_hdl;
        sts=ral_success;
    }
    else
    {

    }
    return sts;
}

/*!
 * @brief Linux wrapper function to delete the queue and release its memory
 */
ral_status_t ral_linux_queue_delete(ral_queue_handle_ptr id)
{
    pthread_queue_t *q_hdl =(pthread_queue_t*)id->rtos_queue_handle;
    pthread_queue_delete(q_hdl);
    return ral_success;
}

/*!
 * @brief Linux wrapper function to flush all the messages from the queue
 */
ral_status_t ral_linux_queue_flush(ral_queue_handle_ptr id)
{
    return ral_success;
}

/*!
 * @brief Linux wrapper function to enqueue the element from queue
 */
ral_status_t ral_linux_queue_send(ral_queue_handle_ptr id, void* msg_ptr, ral_tick_time_t tick_time)
{
    pthread_queue_t *q_hdl =(pthread_queue_t *)id->rtos_queue_handle;
    pthread_queue_enqueue(q_hdl,msg_ptr,tick_time);
    //printf("\n EXO Queue send success");
    return ral_success;
}

/*!
 * @brief Linux wrapper function to dequeue the element from queue
 */
ral_status_t ral_linux_queue_receive(ral_queue_handle_ptr id, void *msg_ptr ,ral_tick_time_t tick_time)
{
    int32_t sts;
    pthread_queue_t *q_hdl =(pthread_queue_t *)id->rtos_queue_handle;
    sts =  pthread_queue_dequeue(q_hdl,msg_ptr,tick_time);
    switch(sts)
    {
        case PTHREAD_QUEUE_EMPTY:
            return ral_err_timeout;
        case PTHREAD_QUEUE_OK:
            return ral_success;
        default:
            return sts;
            break;
    }
}

/*!
 * @brief This API get the number of elements that are actually
 *  in the queue.
 */
uint32_t ral_linux_queue_get_count(ral_queue_handle_ptr id)
{
    pthread_queue_t *q_hdl =(pthread_queue_t *)id->rtos_queue_handle;
    uint32_t ret=pthread_queue_items(q_hdl);
    return ret;

}

/*!
 * @brief Linux wrapper function to get remaining number of element
 *  in the queue
 */
uint32_t ral_linux_queue_get_remain_count(ral_queue_handle_ptr id)
{
    pthread_queue_t *q_hdl =(pthread_queue_t *)id->rtos_queue_handle;
    uint32_t ret=pthread_queue_free(q_hdl);
    return ret;

}

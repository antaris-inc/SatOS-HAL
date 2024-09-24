/**
 * @file exo_ral_queue_common.c
 *
 * @brief This file contains abstraction function definitions to manage the queue.
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
#include "exo_ral_queue.h"
#include "exo_os_common.h"

/*!
 *  @brief This abstraction function to create the queue
 */
ral_status_t ral_queue_create(ral_queue_handle_ptr *ral_q_id,
        uint32_t no_of_item, uint32_t item_size)
{
    ral_status_t sts;
    *ral_q_id=(ral_queue_handle_ptr)ral_malloc(sizeof(ral_queue_handle_t));
    (*ral_q_id)->q_no_of_item = no_of_item;
    (*ral_q_id)->q_item_size = item_size;
    sts=ral_common_queue_create(ral_q_id, no_of_item, item_size);
    return(sts);
}

/*!
 *  @brief Abstraction function to delete the queue and release its memory
 */
ral_status_t ral_queue_delete(ral_queue_handle_ptr ral_q_id)
{
    ral_status_t sts;
    ral_free(ral_q_id);
    sts=ral_common_queue_delete(ral_q_id);
    return(sts);
}

/*!
 *  @brief Abstraction function flush all the messages from the queue
 */
ral_status_t ral_queue_flush(ral_queue_handle_ptr ral_q_id)
{
    ral_status_t sts;
    sts = ral_common_queue_flush(ral_q_id);
    return(sts);
}

/*!
 *  @brief This function enqueue the data from queue
 */
ral_status_t ral_queue_send(ral_queue_handle_ptr ral_q_id, void *msg_ptr,
        ral_tick_time_t timeout_ticks)
{
    ral_status_t sts;
    sts=ral_common_queue_send(ral_q_id, msg_ptr, timeout_ticks);
    return(sts);
}

/*!
 * @brief This function dequeue the data from queue
 */
ral_status_t ral_queue_receive(ral_queue_handle_ptr ral_q_id, void *msg_ptr,
        ral_tick_time_t timeout_ticks)
{
    ral_status_t sts;
    sts=ral_common_queue_receive(ral_q_id, msg_ptr, timeout_ticks);
    return(sts);
}

/*!
 * @brief This abstraction API get the number of elements that are
 *  actually in the Queue.
 */
uint32_t ral_queue_get_count(ral_queue_handle_ptr ral_q_id)
{
    return ral_common_queue_get_count(ral_q_id);
}

/*!
 * @brief This abstraction function get remaining number of element
 *  in the queue
 */
uint32_t ral_queue_get_remain_count(ral_queue_handle_ptr ral_q_id)
{
    return ral_common_queue_get_remain_count(ral_q_id);
}

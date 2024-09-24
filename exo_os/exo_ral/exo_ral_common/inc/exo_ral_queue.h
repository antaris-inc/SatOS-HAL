/**
 * @file exo_ral_queue.h
 *
 * @brief This file contains abstracted function prototypes and structure
 *        for queue management.
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
#ifndef RAL_QUEUE_H
#define RAL_QUEUE_H

#include "exo_ral_cmn.h"

/** 
 * @brief queue handle structure definition
 */
typedef struct
{
    uint32_t q_no_of_item;  /*!<Maximum number items can be stored in the queue*/
    uint32_t q_item_size;   /*!<Maximum size of items in bytes */
    void* rtos_queue_handle;/*!<Pointer to store the RTOS reference */

}ral_queue_handle_t;

typedef ral_queue_handle_t *ral_queue_handle_ptr;

/**
 * @brief This abstraction function to create the queue
 *
 * @param[in]  ral_q_id : Double pointer to queue handle
 * @param[in]  no_of_item : Number of item to create
 * @param[in]  item_size : size of item in bytes
 *
 * @return status of queue creation
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_queue_create(ral_queue_handle_ptr *ral_q_id,
        uint32_t no_of_item, uint32_t item_size);

/**
 * @brief Abstraction function to delete the queue and release its memory
 *
 * @param[in]  ral_q_id : pointer to queue handle
 *
 * @return status of queue deletion
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_queue_delete(ral_queue_handle_ptr ral_q_id);

/**
 * @brief Abstraction function flush all the messages from the queue
 *
 * @param[in]  ral_q_id : pointer to queue handle
 *
 * @return status of queue flush
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_queue_flush(ral_queue_handle_ptr ral_q_id);

/**
 * @brief This function enqueue the data from queue
 *
 * @param[in]  ral_q_id : pointer to queue handle
 * @param[in]  msg_ptr : pointer to message
 * @param[in]  timeout_ticks : Timeout in ticks
 *
 * @return status of send queue
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_queue_send(ral_queue_handle_ptr ral_q_id, void *msg_ptr,
        ral_tick_time_t timeout_ticks);

/**
 * @brief This function dequeue the data from queue
 *
 * @param[in]  ral_q_id : pointer to queue handle
 * @param[in]  msg_ptr : pointer to message
 * @param[in]  timeout_ticks : Timeout in ticks
 *
 * @return status of receive queue
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_queue_receive(ral_queue_handle_ptr ral_q_id, void *msg_ptr,
        ral_tick_time_t timeout_ticks);

/**
 * @brief This function peek the front of the element
 *
 * @param[in]  ral_q_id : pointer to queue handle
 *
 * @return status of peek queue
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_queue_peek(ral_queue_handle_ptr ral_q_id);

/**
 * @brief This abstraction API get the number of elements that are
 *  actually in the Queue.
 *
 * @param[in]  ral_q_id : pointer to queue handle
 *
 * @return Element count
 */
uint32_t ral_queue_get_count(ral_queue_handle_ptr ral_q_id);

/**
 * @brief This abstraction function get remaining number of element
 *  in the queue
 *
 * @param[in]  ral_q_id : pointer to queue handle
 *
 * @return No.of remaining queue elements
 */
uint32_t ral_queue_get_remain_count(ral_queue_handle_ptr ral_q_id);

#endif /*RAL_QUEUE_H*/

/**
 * @file linux_queue.h
 *
 * @brief This file contains queue function prototypes and related macros.
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
 *
 */
#ifndef LINUX_QUEUE_H
#define LINUX_QUEUE_H

#include <pthread.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_TIMEOUT UINT32_MAX     ///< Mapping the timeout
#define PTHREAD_QUEUE_ERROR -1     ///< General error code - something went wrong.
#define PTHREAD_QUEUE_EMPTY -2     ///< Queue is empty - cannot extract element.
#define PTHREAD_QUEUE_FULL -3      ///< Queue is full - cannot insert element.
#define PTHREAD_QUEUE_OK 1         ///< Pthread queue No error

/*
 * @brief Queue handle structure
 */
typedef struct pthread_queue_s
{
    void * buffer;                   /*!<Memory area*/
    int size;                        /*!<Memory size*/
    int item_size;                   /*!<Item/element size*/
    int items;                       /*!<Items/elements in queue*/
    int in;                          /*!<Insert point*/
    int out;                         /*!<Extract point*/
    pthread_mutex_t mutex;           /*!<Lock*/
    pthread_cond_t cond_full;        /*!<Wait because queue is full (insert)*/
    pthread_cond_t cond_empty;       /*!<Wait because queue is empty (extract)*/
} pthread_queue_t;

/*!
 * @brief This API create the queue
 *
 * @param[in] length : length of the queue
 * @param[in] item_size : size of the element
 * @return ret->status of queue
 *
 * @retval PTHREAD_QUEUE_ERROR->error, PTHREAD_QUEUE_OK-> success
 */
pthread_queue_t * pthread_queue_create(int length, size_t item_size);

/*!
 * @brief This API delete the queue
 *
 * @param[in] q : pointer to queue identity
 */
void pthread_queue_delete(pthread_queue_t * q);

/*!
 * @brief This API Enqueue/insert the element in queue
 *
 * @param[in] queue : pointer to queue identity
 * @param[in] value : pointer to queue value
 * @param[in] timeout : Maximum blocking time
 *
 * @return ret->status of enqueue
 *
 * @retval PTHREAD_QUEUE_ERROR->error, PTHREAD_QUEUE_OK-> success
 */
int pthread_queue_enqueue(pthread_queue_t * queue, const void * value, uint32_t timeout);

/*!
 * @brief This API dequeue/extract the element in queue
 *
 * @param[in] queue : pointer to queue identity
 * @param[in] buf : pointer to buffer
 * @param[in] timeout : Maximum blocking time
 *
 * @return ret->status of dequeue
 *
 * @retval PTHREAD_QUEUE_ERROR->error, PTHREAD_QUEUE_OK-> success
 */
int pthread_queue_dequeue(pthread_queue_t * queue, void * buf, uint32_t timeout);
/*!
 * @brief This API count the elements in the pthread queue.
 *
 * @param[in] queue : pointer to queue identity
 * @return Number of elements in the queue.
 */
int pthread_queue_items(pthread_queue_t * queue);

/*!
 * @brief This API release the pthread queue.
 *
 * @param[in] queue : pointer to queue identity
 * @return status of free
 */
int pthread_queue_free(pthread_queue_t * queue);


#endif /*LINUX_QUEUE_H*/

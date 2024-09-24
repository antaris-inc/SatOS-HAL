/**
 * @file linux_queue.c
 *
 * @brief This file contains queue management functions for linux.
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

#include "linux_queue.h"
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <stdint.h>

/*
 * @brief This API get the deadline for thread.
 *
 * @param[in] ts : pointer to time specifier
 * @param[in] timeout_ms : Timeout in millisecond
 *
 * @return ret->status of deadline
 */
static inline int get_deadline(struct timespec * ts, uint32_t timeout_ms) {
    int ret = clock_gettime(CLOCK_MONOTONIC, ts);

    if (ret < 0) {
        return ret;
    }

    uint32_t sec = timeout_ms / 1000;
    uint32_t nsec = (timeout_ms - 1000 * sec) * 1000000;

    ts->tv_sec += sec;

    if (ts->tv_nsec + nsec >= 1000000000) {
        ts->tv_sec++;
    }

    ts->tv_nsec = (ts->tv_nsec + nsec) % 1000000000;

    return ret;
}

/*
 * @brief This API initialize the condition clock monotonic
 *
 * @param[in] cond : pointer to condition
 *
 * @return ret->status of clock
 */
static inline int init_cond_clock_monotonic(pthread_cond_t * cond) {

    int ret;
    pthread_condattr_t attr;

    pthread_condattr_init(&attr);
    ret = pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);

    if (ret == 0) {
        ret = pthread_cond_init(cond, &attr);
    }

    pthread_condattr_destroy(&attr);
    return ret;
}

/*
 * @brief This API create the queue
 */
pthread_queue_t * pthread_queue_create(int length, size_t item_size) {

    pthread_queue_t * q = malloc(sizeof(pthread_queue_t));

    if (q != NULL) {
        q->buffer = malloc(length * item_size);
        if (q->buffer != NULL) {
            q->size = length;
            q->item_size = item_size;
            q->items = 0;
            q->in = 0;
            q->out = 0;
            if (pthread_mutex_init(&(q->mutex), NULL) || init_cond_clock_monotonic(&(q->cond_full)) || init_cond_clock_monotonic(&(q->cond_empty))) {
                free(q->buffer);
                free(q);
                q = NULL;
            }
        } else {
            free(q);
            q = NULL;
        }
    }

    return q;
}

/*
 * @brief This API delete the queue
 */
void pthread_queue_delete(pthread_queue_t * q) {

    if (q == NULL)
        return;

    free(q->buffer);
    free(q);
}

/*
 * @brief This API check the slot available.
 *
 * @param[in] queue : pointer to queue
 * @param[in] ts : pointer to time specifier
 *
 * @return ret->status of slot availability.
 * @retval PTHREAD_QUEUE_FULL->No slot, PTHREAD_QUEUE_OK->slot
 */
static inline int wait_slot_available(pthread_queue_t * queue, struct timespec * ts) {

    int ret;

    while (queue->items == queue->size) {

        if (ts != NULL) {
            ret = pthread_cond_timedwait(&(queue->cond_full), &(queue->mutex), ts);
        } else {
            ret = pthread_cond_wait(&(queue->cond_full), &(queue->mutex));
        }

        if (ret != 0 && errno != EINTR) {
            return PTHREAD_QUEUE_FULL;  // Timeout
        }
    }

    return PTHREAD_QUEUE_OK;
}

/*
 * @brief This API Enqueue/insert the element in queue
 */
int pthread_queue_enqueue(pthread_queue_t * queue, const void * value, uint32_t timeout) {

    int ret;
    struct timespec ts;
    struct timespec * pts = NULL;

    /* Calculate timeout */
    if (timeout != MAX_TIMEOUT) {
        if (get_deadline(&ts, timeout) != 0) {
            return PTHREAD_QUEUE_ERROR;
        }
        pts = &ts;
    } else {
        pts = NULL;
    }

    /* Get queue lock */
    pthread_mutex_lock(&(queue->mutex));

    ret = wait_slot_available(queue, pts);
    if (ret == PTHREAD_QUEUE_OK) {
        /* Copy object from input buffer */
        memcpy(queue->buffer + (queue->in * queue->item_size), value, queue->item_size);
        queue->items++;
        queue->in = (queue->in + 1) % queue->size;
    }

    pthread_mutex_unlock(&(queue->mutex));

    if (ret == PTHREAD_QUEUE_OK) {
        /* Nofify blocked threads */
        pthread_cond_broadcast(&(queue->cond_empty));
    }

    return ret;
}

/*
 * @brief This API check the available waiting item.
 *
 * @param[in] queue : pointer to queue
 * @param[in] ts : pointer to time specifier
 *
 * @return ret->status of wait item
 * @retval PTHREAD_QUEUE_EMPTY->Timeout, PTHREAD_QUEUE_OK->Running
 */
static inline int wait_item_available(pthread_queue_t * queue, struct timespec * ts) {

    int ret;

    while (queue->items == 0) {

        if (ts != NULL) {
            ret = pthread_cond_timedwait(&(queue->cond_empty), &(queue->mutex), ts);
        } else {
            ret = pthread_cond_wait(&(queue->cond_empty), &(queue->mutex));
        }

        if (ret != 0 && errno != EINTR) {
            return PTHREAD_QUEUE_EMPTY;  // Timeout
        }
    }

    return PTHREAD_QUEUE_OK;
}

/*
 * @brief This API dequeue/extract the element in queue
 */
int pthread_queue_dequeue(pthread_queue_t * queue, void * buf, uint32_t timeout) {

    int ret;
    struct timespec ts;
    struct timespec * pts;

    /* Calculate timeout */
    if (timeout != MAX_TIMEOUT) {
        if (get_deadline(&ts, timeout) != 0) {
            return PTHREAD_QUEUE_ERROR;
        }
        pts = &ts;
    } else {
        pts = NULL;
    }

    /* Get queue lock */
    pthread_mutex_lock(&(queue->mutex));

    ret = wait_item_available(queue, pts);
    if (ret == PTHREAD_QUEUE_OK) {
        /* Coby object to output buffer */
        memcpy(buf, queue->buffer + (queue->out * queue->item_size), queue->item_size);
        queue->items--;
        queue->out = (queue->out + 1) % queue->size;
    }

    pthread_mutex_unlock(&(queue->mutex));

    if (ret == PTHREAD_QUEUE_OK) {
        /* Nofify blocked threads */
        pthread_cond_broadcast(&(queue->cond_full));
    }

    return ret;
}

/*
 * @brief This API count the elements in the queue.
 */
int pthread_queue_items(pthread_queue_t * queue) {

    pthread_mutex_lock(&(queue->mutex));
    int items = queue->items;
    pthread_mutex_unlock(&(queue->mutex));

    return items;
}

/*
 * @brief This API release the queue.
 */
int pthread_queue_free(pthread_queue_t * queue) {

    pthread_mutex_lock(&(queue->mutex));
    int free = queue->size - queue->items;
    pthread_mutex_unlock(&(queue->mutex));

    return free;
}

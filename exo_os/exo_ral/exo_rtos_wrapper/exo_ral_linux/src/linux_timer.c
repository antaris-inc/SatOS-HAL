/**
 * @file linux_timer.c
 *
 * @brief This file contains timer management functions for linux.
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

#include <stdint.h>
#include <string.h>
#include <sys/timerfd.h>
#include <pthread.h>
#include <poll.h>
#include <stdio.h>
#include <unistd.h>

#include "linux_timer.h"

#define MAX_TIMER_COUNT 1000    ///< Set Maximum timer count 1000

/*
 * @brief Timer structure definition
 */
struct timer_node
{
    int                 fd;
    time_handler        callback;
    void *              user_data;
    unsigned int        interval;
    t_timer             type;
    struct timer_node * next;
};

/*!
 * @brief This API handling the timer thread
 *
 * @param[in] data : pointer to timer thread data
 */
static void * _timer_thread(void * data);
static pthread_t g_thread_id;
static struct timer_node *g_head = NULL;

/*!
 * @brief This API initialize the timer
 */
int initialize()
{
    if(pthread_create(&g_thread_id, NULL, _timer_thread, NULL))
    {
        /*Thread creation failed*/
        return 0;
    }

    return 1;
}

/*!
 * @brief This API start the timer
 */
size_t start_timer(unsigned int interval, time_handler handler, t_timer type, void * user_data)
{
    struct timer_node * new_node = NULL;
    struct itimerspec new_value;

    new_node = (struct timer_node *)malloc(sizeof(struct timer_node));

    if(new_node == NULL) return 0;

    new_node->callback  = handler;
    new_node->user_data = user_data;
    new_node->interval  = interval;
    new_node->type      = type;

    new_node->fd = timerfd_create(CLOCK_REALTIME, 0);

    if (new_node->fd == -1)
    {
        free(new_node);
        return 0;
    }

    new_value.it_value.tv_sec = interval / 1000;
    new_value.it_value.tv_nsec = (interval % 1000)* 1000000;

    if (type == TIMER_PERIODIC)
    {
        new_value.it_interval.tv_sec= interval / 1000;
        new_value.it_interval.tv_nsec = (interval %1000) * 1000000;
    }
    else
    {
        new_value.it_interval.tv_sec= 0;
        new_value.it_interval.tv_nsec = 0;
    }

    timerfd_settime(new_node->fd, 0, &new_value, NULL);

    /*Inserting the timer node into the list*/
    new_node->next = g_head;
    g_head = new_node;

    return (size_t)new_node;
}

/*!
 * @brief This function stop the timer
 */
void stop_timer(size_t timer_id)
{
    struct timer_node * tmp = NULL;
    struct timer_node * node = (struct timer_node *)timer_id;

    if (node == NULL) return;

    if(node == g_head)
    {
        g_head = g_head->next;
    } else {

        tmp = g_head;

        while(tmp && tmp->next != node) tmp = tmp->next;

        if(tmp)
        {
            /*tmp->next can not be NULL here*/
            tmp->next = tmp->next->next;
            close(node->fd);
            free(node);
        }
    }
}

/*!
 * @brief This API finalize the timer task
 */
void finalize()
{
    while(g_head) stop_timer((size_t)g_head);

    pthread_cancel(g_thread_id);
    pthread_join(g_thread_id, NULL);
}

/*!
 * @brief This API handling the get timer from file descriptor
 */
struct timer_node * _get_timer_from_fd(int fd)
{
    struct timer_node * tmp = g_head;

    while(tmp)
    {
        if(tmp->fd == fd) return tmp;

        tmp = tmp->next;
    }
    return NULL;
}

/*!
 * @brief This API handling the timer thread
 */
void * _timer_thread(void * data)
{
    struct pollfd ufds[MAX_TIMER_COUNT] = {{0}};
    int iMaxCount = 0;
    struct timer_node * tmp = NULL;
    int read_fds = 0, i, s;
    uint64_t exp;

    while(1)
    {
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

        iMaxCount = 0;
        tmp = g_head;

        memset(ufds, 0, sizeof(struct pollfd)*MAX_TIMER_COUNT);
        while(tmp)
        {
            ufds[iMaxCount].fd = tmp->fd;
            ufds[iMaxCount].events = POLLIN;
            iMaxCount++;

            tmp = tmp->next;
        }
        read_fds = poll(ufds, iMaxCount, 100);

        if (read_fds <= 0) continue;

        for (i = 0; i < iMaxCount; i++)
        {
            if (ufds[i].revents & POLLIN)
            {
                s = read(ufds[i].fd, &exp, sizeof(uint64_t));

                if (s != sizeof(uint64_t)) continue;

                tmp = _get_timer_from_fd(ufds[i].fd);

                if(tmp && tmp->callback) tmp->callback((size_t)tmp, tmp->user_data);
            }
        }
    }

    return NULL;
}


/**
 * @file linux_timer.h
 *
 * @brief This file contains the timer function prototypes.
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
#ifndef LINUX_TIME_H
#define LINUX_TIME_H
#include <stdlib.h>

/*
 * @brief Timer mode enumeration
 */
typedef enum
{
    TIMER_SINGLE_SHOT = 0, /*!<Single Shot Timer*/
    TIMER_PERIODIC         /*!<Periodic Timer*/
} t_timer;

typedef void (*time_handler)(size_t timer_id, void * user_data);

/*!
 * @brief This API initialize the timer
 *
 * @return status of pthread creation
 *
 * @retval 0-> Thread creation failed, 1-> pthread created
 */
int initialize();

/*!
 * @brief This API start the timer
 *
 * @param[in]  interval : Time period
 * @param[in]  handler : Timer handler
 * @param[in]  type : Type of timer
 * @param[in]  user_data : void pointer to user input data
 *
 * @return Return the new node
 */
size_t start_timer(unsigned int interval, time_handler handler, t_timer type, void * user_data);

/*!
 * @brief This function stop the timer
 *
 * @param[in] timer_id : Identity of timer
 */
void stop_timer(size_t timer_id);

/*!
 * @brief This API finalize the timer task
 */
void finalize();

#endif /*LINUX_TIME_H*/

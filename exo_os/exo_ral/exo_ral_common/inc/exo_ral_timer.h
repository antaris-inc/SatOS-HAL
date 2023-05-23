/**
 * @file exo_ral_timer.h
 *
 * @brief This file contains abstracted enumeration, structures, function
 *  prototypes for timer.
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
#ifndef RAL_TIMER_H
#define RAL_TIMER_H

#include "exo_ral_cmn.h"
#define MAX_TIMER_NAME_LEN 25        ///< Maximum timer name length in bytes

typedef void(*ral_timer_cbfunc_t)(void* args);
typedef uint32_t ral_tick_time_t ;

/**
 * @brief  Timer mode enumeration
 */
typedef enum
{
    ONESHOT,          /*!< one time expiry */
    PERIODIC          /*!< Repeatedly expiry */
}ral_timer_mode_t;
/**
 * @brief  Timer handle structure definition
 */
typedef struct
{
    char timer_name[MAX_TIMER_NAME_LEN];   /*!< Timer name array */
    ral_timer_cbfunc_t expiry_hdlr;        /*!< Timer expiry handle function pointer*/
    ral_timer_mode_t mode;                 /*!< Timer mode */
    uint8_t timer_state;                   /*!< Timer state->It can be active or inactive */
    void* parameter;                       /*!< pointer to expiry handle parameter */
    void* rtos_timer_handle;               /*!< pointer to RTOS timer handle */

}ral_timer_handle_t;

typedef ral_timer_handle_t *ral_timer_handle_ptr;
/**
 * @brief This function create the timer
 *
 * @param[in]  ral_tmr_id : Double pointer to timer handle
 * @param[in]  timer_name : pointer to name of timer
 * @param[in]  mode : mode of timer
 * @param[in]  cbfunc : callback the timer function
 * @param[in]  args : pointer to timer argument
 *
 * @return status of timer creation
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_timer_create(ral_timer_handle_ptr *ral_tmr_id,
        const char* timer_name, ral_timer_mode_t mode,
        ral_timer_cbfunc_t cbfunc,void *args);
/**
 * @brief This function start the timer
 *
 * @param[in]  ral_tmr_id : pointer to timer handle
 * @param[in]  tick_time : Track the timer
 *
 * @return status of timer start
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_timer_start(ral_timer_handle_ptr ral_tmr_id,
        ral_tick_time_t tick_time);

/**
 * @brief This function stop the timer
 *
 * @param[in]  ral_tmr_id : pointer to timer handle
 *
 * @return status of timer stop
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_timer_stop(ral_timer_handle_ptr ral_tmr_id);

/**
 * @brief This function delete the timer
 *
 * @param[in]  ral_tmr_id : pointer to timer handle
 *
 * @return status of timer deletion
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_timer_delete(ral_timer_handle_ptr ral_tmr_id);


#endif /*RAL_TIMER_H*/

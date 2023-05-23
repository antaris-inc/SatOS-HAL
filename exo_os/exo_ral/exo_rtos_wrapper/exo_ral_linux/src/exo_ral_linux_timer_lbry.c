/**
 * @file exo_ral_linux_timer_lbry.c
 *
 * @brief This file contains functions of linux for timer.
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

#include "exo_os_common.h"
#include "linux_timer.h"

/*!
 * @brief Linux wrapper function to create the timer
 */
ral_status_t ral_linux_timer_create(ral_timer_handle_ptr *id, const char* timer_name, ral_timer_mode_t mode,ral_timer_cbfunc_t cbfunc,void *args)
{
    initialize();
    size_t* tmr_id;
    tmr_id=(size_t*)malloc(sizeof(size_t));
    //  *tmr_id=start_timer(interval, cbfunc, mode, args);
    (*id)->rtos_timer_handle=(void*)tmr_id;
    return (ral_success);
}

/*!
 * @brief Linux wrapper function to start the timer
 */
ral_status_t ral_linux_timer_start(ral_timer_handle_ptr id,ral_tick_time_t tick_time)
{
    size_t *tmr_id = (size_t*)id->rtos_timer_handle;
    unsigned int periodicity= tick_time;
    *tmr_id=start_timer(periodicity, (time_handler )id->expiry_hdlr, id->mode, id->parameter);
    return(ral_success);
}

/*!
 * @brief Linux wrapper function to stop the timer
 */
ral_status_t ral_linux_timer_stop(ral_timer_handle_ptr id)
{
    size_t *tmr_id = (size_t*)id->rtos_timer_handle;
    stop_timer(*tmr_id);
    return(ral_success);
}

/*!
 * @brief Linux wrapper function to delete the timer
 */
ral_status_t ral_linux_timer_delete(ral_timer_handle_ptr id)
{
    //dummy function
    return 0;
}


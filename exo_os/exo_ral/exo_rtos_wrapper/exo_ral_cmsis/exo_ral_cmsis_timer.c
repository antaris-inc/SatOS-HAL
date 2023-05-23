/**
 * @file exo_ral_cmsis_timer.c
 *
 * @brief This file contains wrapper functions of CMSIS RTOS v2 for timer.
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
 * limitations under the License.*
 */

#include "exo_os_common.h"

/*!
 * @brief This function create the timer.
 */
ral_status_t ral_cmsis_timer_create(ral_timer_handle_ptr *id, const char* timer_name, ral_timer_mode_t mode, ral_timer_cbfunc_t cbfunc, void *args)
{
    osTimerId_t tmr_id;
    osTimerAttr_t myTimer_attributes ={
        .name= timer_name
    };
    tmr_id=osTimerNew (cbfunc, mode, args, &myTimer_attributes);
    if(tmr_id!=NULL)
    {
        (*id)->rtos_timer_handle=(void*)tmr_id;
        return ral_success;
    }
    else
    {
        return ral_error;
    }
}

/*!
 * @brief This function start the timer
 */
ral_status_t ral_cmsis_timer_start(ral_timer_handle_ptr id, ral_tick_time_t tick_time)
{
    osTimerId_t tmr_id= (osTimerId_t)id->rtos_timer_handle;
    osStatus_t sts;
    sts = osTimerStart(tmr_id, tick_time);
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
 * @brief This function stop the timer
 */
ral_status_t ral_cmsis_timer_stop(ral_timer_handle_ptr id)
{
    osStatus_t 	sts;
    osTimerId_t tmr_id= (osTimerId_t)id->rtos_timer_handle;
    sts=osTimerStop (tmr_id);
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
 * @brief This function delete the timer
 */
ral_status_t ral_cmsis_timer_delete(ral_timer_handle_ptr id)
{
    osTimerId_t tmr_id= (osTimerId_t)id->rtos_timer_handle;
    osStatus_t 	sts;
    sts=osTimerDelete (tmr_id);
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


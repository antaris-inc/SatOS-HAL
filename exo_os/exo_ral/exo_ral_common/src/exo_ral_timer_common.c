/**
 * @file exo_ral_timer_common.c
 *
 * @brief This file contains abstracted function definitions for timer management.
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

#include "exo_ral_timer.h"
#include "exo_os_common.h"

/*!
 *  @brief This function create the timer
 */
ral_status_t ral_timer_create(ral_timer_handle_ptr *ral_tmr_id,const char* timer_name, ral_timer_mode_t mode,ral_timer_cbfunc_t cbfunc,void *args)
{
    ral_status_t tmr_sts;
    *ral_tmr_id=(ral_timer_handle_ptr)ral_malloc(sizeof(ral_timer_handle_t));
    //id->timer_name=timer_name;
    (*ral_tmr_id)->expiry_hdlr=cbfunc;
    (*ral_tmr_id)->mode=mode;
    (*ral_tmr_id)->timer_state=0;                         /* Active State or Inactive State */
    (*ral_tmr_id)->parameter=args;
    tmr_sts = ral_common_timer_create (ral_tmr_id,timer_name,(*ral_tmr_id)->mode,(*ral_tmr_id)->expiry_hdlr,(*ral_tmr_id)->parameter);
    return(tmr_sts);
}

/*!
 *  @brief This function start the timer
 */
ral_status_t ral_timer_start(ral_timer_handle_ptr ral_tmr_id,ral_tick_time_t timeout_ticks)
{
    ral_status_t tmr_sts;
    tmr_sts=ral_common_timer_start(ral_tmr_id,timeout_ticks);
    return(tmr_sts);
}

/*!
 *  @brief This function stop the timer
 */
ral_status_t ral_timer_stop(ral_timer_handle_ptr ral_tmr_id)
{
    ral_status_t tmr_sts;
    tmr_sts=ral_common_timer_stop(ral_tmr_id);
    return(tmr_sts);
}

/*!
 *  @brief This function delete the timer
 */
ral_status_t ral_timer_delete(ral_timer_handle_ptr ral_tmr_id)
{
    ral_status_t tmr_sts;
    ral_free(ral_tmr_id);
    tmr_sts=ral_common_timer_delete(ral_tmr_id);
    return(tmr_sts);
}


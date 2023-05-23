/**
 * @file exo_osal_thread.c
 *
 * @brief This file contains function definitions for OS thread management.
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

#include "exo_common.h"
#include "exo_osal_thread.h"
#include "exo_osal_mem_management.h"

volatile uint8_t system_error=0;
os_thread_handle_ptr thread_ptr[OS_TASK_MAX];

/**
 * @brief Function to create the thread
 */
os_status_t os_thread_create(uint8_t task_id,uint32_t stack_size,os_thread_priority_t priority,const char* thread_name,app_entry_func_t app_entry_func,void* entry_args,app_init_func_t app_init_func,void* init_args)
{
    os_status_t thread_sts=ral_error;
    os_thread_handle_ptr cb_args;
    cb_args = (os_thread_handle_ptr)os_malloc_api(sizeof(os_thread_handle_t));
    if(cb_args!=NULL)
    {
        cb_args->app_entry_func = app_entry_func;
        cb_args->app_init_func = app_init_func;
        cb_args->app_entry_args = entry_args;
        cb_args->app_init_args = init_args;

        os_queue_handle_ptr itc_queue;
        thread_sts =os_queue_create(&itc_queue,MAX_ITC_Q_LEN,MAX_ITC_Q_ITEM_SIZE);
        if(thread_sts == ral_success)
        {
            os_itc_queue_info_t *itc_q_info;
            itc_q_info = (os_itc_queue_info_t*)ral_malloc(sizeof(os_itc_queue_info_t));
            if(itc_q_info!=NULL)
            {
                itc_q_info->itc_queue_id=itc_queue;
                itc_q_info->queue_length=MAX_ITC_Q_LEN;
                itc_q_info->item_size=MAX_ITC_Q_ITEM_SIZE;
                cb_args->queue_info_t=itc_q_info;
                thread_ptr[task_id]=cb_args;

            }
            /* Need to add os entry function */
            ral_thread_handle_ptr ral_thread_id;
            thread_sts = ral_thread_create(&ral_thread_id,stack_size,priority,thread_name,app_entry_func,cb_args);
            if(thread_sts == ral_success)
            {
                /* ITC queue Creation */
                cb_args->ral_thread_handle=ral_thread_id;
            }
            else
            {
                thread_sts=ral_error;
                os_queue_delete(itc_queue);
                os_free(cb_args);
                cb_args = NULL;
            }
        }
        else
        {
            thread_sts =ral_error;
        }
    }

    return (thread_sts);
}

/**
 * @brief Function to delete the thread
 */
os_status_t os_thread_delete(uint8_t id)
{
    os_status_t sts;
    os_thread_handle_ptr cb = thread_ptr[id];

    os_queue_delete(cb->queue_info_t->itc_queue_id);
    sts=ral_thread_delete(cb->ral_thread_handle);
    os_free(cb);
    cb = NULL;
    return sts;
}

/**
 * @brief This API create software OS delay
 */
void sw_os_delay(uint32_t tick_time)
{
    volatile uint64_t delay_sw=20000*tick_time;    //need to be tuned based on the CPU frequency
    while(delay_sw)
    {
        delay_sw--;
    }
}

/**
 * @brief This API to create thread delay
 */
os_status_t os_delay(os_tick_time_t tick_time)
{
    os_status_t sts=ral_error;
    if(system_error==1)
    {
        sw_os_delay(tick_time);
    }
    else
    {
#ifndef LINUX_TEMP_PORT
        if(kernel_init_done!=1)
        {
            HAL_Delay(tick_time);
        }
        else
        {
            sts=ral_delay(tick_time);
        }
#else
        sts=ral_delay(tick_time);
#endif
    }
    return sts;
}

/**
 * @brief This API to get the thread handle.
 */
os_thread_handle_ptr os_get_thread_hdl(uint8_t id)
{
    return(thread_ptr[id]);
}

/**
 * @brief This API to get the queue id for given thread handle.
 */
os_queue_handle_ptr os_get_queue_id(uint8_t id)
{
    return(thread_ptr[id]->queue_info_t->itc_queue_id);
}

/**
 * @brief Function puts the thread from running to waiting state
 */
os_status_t os_thread_suspend(uint8_t task_id)
{
    os_status_t sts;
    os_thread_handle_ptr cb = thread_ptr[task_id];
    sts = ral_thread_suspend(cb->ral_thread_handle);
    return sts;
}

/**
 * @brief Function use to resume the thread
 */
os_status_t os_thread_resume(uint8_t task_id)
{
    os_status_t sts;
    os_thread_handle_ptr cb = thread_ptr[task_id];
    sts = ral_thread_resume(cb->ral_thread_handle);
    return sts;
}


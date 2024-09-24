/**
 * @file exo_ral_cmsis_thread.c
 *
 * @brief This file contains wrapper functions of CMSIS RTOS v2 for thread.
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

#include "exo_os_common.h"

/*!
 * @brief This function create the thread
 */
ral_status_t ral_cmsis_thread_create(ral_thread_handle_ptr *id,
		     uint32_t stack_size,ral_thread_priority_t priority,
		      const char* thread_name,ral_thread_entry_func_t entry_func,
		                                                void *parameters)
{
    osThreadId_t task_id;
    osThreadAttr_t attr = {
        .name=thread_name,
        .stack_size=stack_size,
        .priority=(osPriority_t)priority,
    };
    task_id= osThreadNew (entry_func,parameters,&attr);
    if(task_id!=NULL)
    {
    	(*id)->rtos_thread_handle=(void*)task_id;
        return(ral_success);
    }
    else
    {
        return(ral_error);
    }

}

/*!
 * @brief This API is create the thread delay
 */
ral_status_t ral_cmsis_delay(ral_tick_time_t tick_time)
{
    osStatus_t sts;
    sts=osDelay ((uint32_t)tick_time);
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
 * @brief This API handle the thread delay time
 */
ral_status_t ral_cmsis_delay_until(ral_tick_time_t tick_time)
{
    osStatus_t sts;
    sts= osDelayUntil ((uint32_t)tick_time);
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
 * @brief This function delete the thread
 */
ral_status_t ral_cmsis_thread_delete(ral_thread_handle_ptr id )
{
    osStatus_t sts;
    osThreadId_t task_id=(osThreadId_t)id->rtos_thread_handle;
    sts= osThreadTerminate(task_id);
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
 * @brief This function puts the thread from running to waiting state
 */
ral_status_t ral_cmsis_thread_suspend(ral_thread_handle_ptr id)
{
    osStatus_t sts;
    osThreadId_t task_id=(osThreadId_t)id->rtos_thread_handle;
    sts = osThreadSuspend (task_id);
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
 * @brief This function use to resume the thread
 */
ral_status_t ral_cmsis_thread_resume(ral_thread_handle_ptr id )
{
    osStatus_t sts;
    osThreadId_t task_id=(osThreadId_t)id->rtos_thread_handle;
    sts = osThreadResume(task_id);
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
 * @brief This function get the thread state
 */
ral_thread_state_t ral_cmsis_thread_get_state(ral_thread_handle_ptr id)
{
    osThreadId_t task_id=(osThreadId_t)id->rtos_thread_handle;
    return((ral_thread_state_t)osThreadGetState(task_id));
}

/*!
 * @brief This function get the thread name
 */
const char* ral_cmsis_thread_get_name(ral_thread_handle_ptr id)
{
    osThreadId_t task_id=(osThreadId_t)id->rtos_thread_handle;
    return( osThreadGetName (task_id));
}

/*!
 * @brief This function set the thread priority level
 */
ral_status_t ral_cmsis_thread_set_priority_level(ral_thread_handle_ptr id, ral_thread_priority_t new_priority_level)
{
    osStatus_t sts;
    osThreadId_t task_id=(osThreadId_t)id->rtos_thread_handle;
    osPriority_t prity=(osPriority_t)new_priority_level;
    sts= osThreadSetPriority (task_id,prity);
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
 * @brief This function get the thread priority level
 */
ral_thread_priority_t ral_cmsis_thread_get_priority_level(ral_thread_handle_ptr id)
{
    osThreadId_t task_id=(osThreadId_t)id->rtos_thread_handle;
    osPriority_t prity;
    prity = osThreadGetPriority(task_id);
    return((ral_thread_priority_t)prity);
}

/*!
 * @brief This function get the remaining stack size of the thread
 */
uint32_t ral_cmsis_thread_get_stack_remaining_size(ral_thread_handle_ptr id)
{
    osThreadId_t task_id = (osThreadId_t)id->rtos_thread_handle;
    return ( osThreadGetStackSpace(task_id));
}



/**
 * @file exo_ral_linux_thread.c
 *
 * @brief This file contains functions of linux for thread.
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

#include <pthread.h>
#include "exo_os_common.h"
#include "unistd.h"
/*!
 * @brief Linux wrapper function to create the thread
 */
ral_status_t ral_linux_thread_create(ral_thread_handle_ptr *id,uint32_t stack_size,ral_thread_priority_t priority,const char* thread_name,ral_thread_entry_func_t entry_func,void *parameters)
{
    pthread_t* thread_id;
    thread_id=(pthread_t*) ral_malloc(sizeof(pthread_t));
    int task_id = pthread_create(thread_id,NULL,(void*)entry_func,(void*)parameters);
    if(task_id==0)
    {
        (*id)->rtos_thread_handle=(void*)thread_id;
        //printf("EXO OS Thread create success\n");
        return(ral_success);
    }
    else
    {
        return(ral_error);
    }
}

/*!
 * @brief This API is set to waiting time for thread process
 */
ral_status_t ral_linux_thread_delay(ral_tick_time_t tick_time)
{
    sleep(tick_time/1000);
    return(ral_success);
}

/*!
 * @brief Linux wrapper function to delete the queue
 */
ral_status_t ral_linux_thread_delete(ral_thread_handle_ptr id)
{
    char *ret = NULL;
    pthread_exit(ret);
    return(ral_success);
}

/*!
 * @brief Linux wrapper function to put the thread from running to waiting state
 */
ral_status_t ral_linux_thread_suspend(ral_thread_handle_ptr id)
{
	//TODO
	return(ral_success);
}

/*!
 * @brief Linux wrapper function to use to resume the thread
 */
ral_status_t ral_linux_thread_resume(ral_thread_handle_ptr id)
{
	//TODO
	return(ral_success);
}


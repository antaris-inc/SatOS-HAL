/*
Cubesat Space Protocol - A small network-layer protocol designed for Cubesats
Copyright (C) 2012 Gomspace ApS (http://www.gomspace.com)
Copyright (C) 2012 AAUSAT3 Project (http://aausat3.space.aau.dk) 

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "csp_thread.h"
#include "exo_common.h"
#include "exo_osal_thread.h"
#include "csp.h"



#ifndef OSAL_EN //ANTARIS_PORT

int csp_thread_create(csp_thread_func_t routine, const char * const thread_name, unsigned int stack_size, void * parameters, unsigned int priority, csp_thread_handle_t * return_handle) {

	csp_thread_handle_t handle;
#if (tskKERNEL_VERSION_MAJOR >= 8)
	portBASE_TYPE ret = xTaskCreate(routine, thread_name, stack_size, parameters, priority, &handle);
#else
	portBASE_TYPE ret = xTaskCreate(routine, (signed char *) thread_name, stack_size, parameters, priority, &handle);
#endif
    if (ret != pdTRUE) {
        return CSP_ERR_NOMEM;
    }
    if (return_handle) {
        *return_handle = handle;
    }
    return CSP_ERR_NONE;
}

void csp_thread_exit(void) {

	vTaskDelete(NULL);  // Function must exist, otherwise code wont behave the same on all platforms.
}

void csp_sleep_ms(unsigned int time_ms) {

	vTaskDelay(time_ms / portTICK_RATE_MS);
}
#else
int csp_task_count =0;
int csp_thread_create(csp_thread_func_t routine, const char * const thread_name, unsigned int stack_size, void * parameters, unsigned int priority, csp_thread_handle_t * return_handle)
{
    csp_thread_handle_t handle;
    os_status_t sts=os_thread_create(CSP_TASK+csp_task_count,(uint32_t)stack_size*4,(os_thread_priority_t)priority,thread_name,(app_entry_func_t)routine,parameters,NULL,NULL);
    if(sts!=ral_success)
    {
        return CSP_ERR_NOMEM;
    }
    if (return_handle)
    {
        handle =(csp_thread_handle_t)os_get_thread_hdl(CSP_TASK+csp_task_count);
        csp_task_count ++;
        *return_handle = handle;
    }
    return CSP_ERR_NONE;
}
void csp_thread_exit(void)
{
	os_thread_delete(CSP_TASK+csp_task_count);
	//vTaskDelete(NULL);
}
void csp_sleep_ms(unsigned int time_ms) {
//	vTaskDelay(time_ms / portTICK_RATE_MS);
    // TBD: OS delay need to be in ms need to check at osal
        os_delay(time_ms);
}
#endif

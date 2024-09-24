/**
 * @file exo_ral_main.c
 *
 * @brief This file has linux RAL test functions.
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
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "exo_os_common.h"

void task_test( void *ptr );

ral_thread_handle_ptr task_2;
ral_status_t task_sts_2;
ral_sem_handle_ptr sem1;
ral_status_t sem_sts;
uint32_t sem_count;
ral_timer_handle_ptr tmr_id;
ral_status_t tmr_sts;
ral_queue_handle_ptr q_id;
ral_status_t q_sts;
int v1 = 1;
int* var;

/**
 * @brief Testing function
 */
void tmr_handler(void* args)
{
    static int tmr_count= 0;
    if(tmr_count<=5)
    {
        printf("\n EXO Timer Expired");
        tmr_count++;
    }
    else
    {
        ral_timer_stop(tmr_id);
    }
}

/**
 * @brief Testing function
 */
void ral_main()
{
    task_sts_2 = ral_thread_create(&task_2,1024,40,"task_2",task_test,NULL);
    printf("\n EXO Thread created\n");

    sem_sts = ral_sem_create_bin(&sem1);
    sem_sts = ral_sem_take(sem1,1000);
    sem_sts = ral_sem_get_count(sem1,&sem_count);
    sem_sts = ral_sem_give(sem1);
    sem_sts = ral_sem_get_count(sem1,&sem_count);

    q_sts = ral_queue_create(&q_id,4,10);
    q_sts = ral_queue_send(q_id,(void*)&v1,1000);
    q_sts = ral_queue_receive(q_id,(void*)&var,1000);

}

/**
 * @brief Testing function
 */
void task_test( void *ptr )
{
    printf("\n EXO Thread INIT ");
    tmr_sts = ral_timer_create(&tmr_id,"tmr_1",1,tmr_handler,NULL);
    tmr_sts = ral_timer_start(tmr_id,1000);
}


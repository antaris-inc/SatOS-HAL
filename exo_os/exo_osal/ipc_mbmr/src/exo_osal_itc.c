/**
 * @file exo_osal_itc.c
 *
 * @brief This file contains function definitions for inter thread communication.
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

#include <stdio.h>
#include "exo_osal.h"

#define ITC_PRINT_EN      ///< Enable the ITC print

/**
 * @brief This API get the number of available ITC message for the given task id.
 */
os_status_t os_itc_msg_get_free_count( uint8_t task_id, uint16_t *avail_cnt)
{
    os_queue_handle_ptr rcv_q_id;
    rcv_q_id = os_get_queue_id(task_id);
    *avail_cnt = os_queue_get_remain_count(rcv_q_id);

    return os_success;
}

/**
 * @brief This API send the ITC message to the specified thread.
 */
os_status_t os_itc_msg_send(os_itc_msg_handle_t *id, uint8_t task_id, os_tick_time_t timeout)
{
    os_queue_handle_ptr rcv_q_id;
#ifdef ITC_PRINT_EN
    printf("ItcTx%u-%u\n",id->src_entity,task_id);
#endif
    rcv_q_id = os_get_queue_id(task_id);
    os_status_t sts;
    sts=os_queue_send(rcv_q_id,id,timeout);
    if(sts==os_success)
    {
        return (ral_success);
    }
    else
    {
        printf("Q Full task %d", task_id);
        return (ral_error);
    }
}

/**
 * @brief This API receive the ITC message to the specified thread.
 */
os_status_t os_itc_msg_rcv(uint8_t task_id, os_itc_msg_handle_t *id, os_tick_time_t timeout)
{
    os_queue_handle_ptr rcv_q_id;
    rcv_q_id = os_get_queue_id(task_id);
    os_status_t sts;
    sts=os_queue_receive(rcv_q_id,id,timeout);

    if(sts==os_success)
    {
#ifdef ITC_PRINT_EN
        printf("ItcRx%u-%u\n",id->src_entity,task_id);
#endif
        return (ral_success);
    }
    else
    {
        if(sts != ral_err_timeout)
        {
            printf("Q read failed task %d", task_id);
        }
        return (ral_error);
    }
}




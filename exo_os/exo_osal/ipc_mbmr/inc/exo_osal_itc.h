/**
 * @file exo_osal_itc.h
 *
 * @brief This file contains stucture, union and function prototypes
 *        for Interthread communication.
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
#ifndef OSAL_ITC_H
#define OSAL_ITC_H

#include "exo_osal_common.h"
#include "exo_osal_thread.h"
#include "exo_ral_cmn.h"

/**
 * @brief ITC payload union definition
 */
typedef union
{
    uint32_t pld_data;        /*!<Payload info*/
    void* pld_ptr;            /*!<payload pointer*/
}u_pld_info_t;

/**
 * @brief ITC message handle structure definition
 */
typedef struct
{
    //bit0- 0 means pld ptr not present,1 means pld present
    //bit1- 0 means pld ptr automatic free , 1 means must need to be handled by receiver thread.
    uint8_t src_entity;           /*!<Source thread id */
    uint8_t pld_info;             /*!<payload information */
    uint16_t Msg_id;              /*!<Messsage id */
    uint16_t Msg_len;             /*!<Message length */
    u_pld_info_t pld;             /*!<union to payload */

}os_itc_msg_handle_t ;

/**
 * @brief This API send the ITC message to the specified thread.
 *
 * @param[in]  task_id : Destination task id
 * @param[in]  id : pointer to ITC message handle
 * @param[in]  timeout : Maximum blocking time
 *
 * @return status of thread message
 *
 * @retval ral_success->success, ral_error->error
 */
os_status_t os_itc_msg_send(os_itc_msg_handle_t *id, uint8_t task_id ,os_tick_time_t timeout);

/**
 * @brief This API receive the ITC message to the specified thread.
 *
 * @param[in]  task_id : Destination task id
 * @param[in]  id : pointer to ITC message handle
 * @param[in]  timeout : Maximum blocking time
 *
 * @return status of thread message
 *
 * @retval ral_success->success, ral_error->error
 */
os_status_t os_itc_msg_rcv(uint8_t task_id, os_itc_msg_handle_t *id, os_tick_time_t timeout);

/**
 * @brief This API get the number of available ITC message for the given task id.
 *
 * @param[in]  task_id : Identity of task
 * @param[out]  avail_cnt : pointer to available message count.
 *
 * @return status of thread message
 *
 * @retval os_success->success
 */
os_status_t os_itc_msg_get_free_count( uint8_t task_id, uint16_t *avail_cnt);


#endif /*OSAL_ITC_H*/

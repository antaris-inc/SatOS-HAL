/**
 * @file exo_osal_common.h
 *
 * @brief This file contains common definitions for OSAL.
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

#ifndef OSAL_COMMON_H
#define OSAL_COMMON_H

#include "exo_ral_cmn.h"
#include "exo_ral_common.h"

#define os_success 1                 ///< OS SUCCESS
#define os_error 0                   ///< OS ERROR
#define os_wait_forever 0xFFFFFFFFU  ///< Indefinite waiting time

/**
 * @brief Mapping the RAL status to OS status.
 */
typedef ral_status_t os_status_t;
/**
 * @brief Mapping the RAL timer handle to OS timer handle.
 */
typedef ral_timer_handle_ptr os_timer_handle_ptr;
/**
 * @brief Mapping the RAL semaphore handle to OS semaphore handle.
 */
typedef ral_sem_handle_ptr os_sem_handle_ptr;
/**
 * @brief Mapping the RAL tick time thread to OS tick time thread.
 */
typedef ral_tick_time_t os_tick_time_t;
/**
 * @brief Mapping the RAL queue handle to OS queue handle.
 */
typedef ral_queue_handle_ptr os_queue_handle_ptr;
/**
 * @brief Mapping the RAL thread priority to OS thread priority.
 */
typedef ral_thread_priority_t os_thread_priority_t;


#endif /*OSAL_COMMON_H*/

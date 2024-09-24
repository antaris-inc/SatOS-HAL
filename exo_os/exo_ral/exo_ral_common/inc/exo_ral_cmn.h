/**
 * @file exo_ral_cmn.h
 *
 * @brief This file contains enumeration, macros for RTOS abstraction
 *        layer (RAL).
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
#ifndef RAL_CMN_H
#define RAL_CMN_H

#include <stdint.h>
#define ral_wait_forever 0xFFFFFFFFU ///< Indefinite waiting time

typedef uint32_t ral_tick_time_t;

/*
 * @brief RAL thread states enumeration
 */
typedef enum
{
    ral_thread_ready,             /*!< RAL Thread ready */
    ral_thread_running,           /*!< RAL Thread running */
    ral_thread_blocked,           /*!< RAL Thread Blocked */
    ral_thread_terminated,        /*!< RAL Thread terminated */
    ral_thread_error,             /*!< RAL Thread error */
    ral_thread_state_max          /*!< RAL Thread state */

}ral_thread_state_t;

/*
 * @brief RAL status code enumeration
 */
typedef enum
{
    ral_error,                         /*!< RAL Error */
    ral_success,                       /*!< RAL success */
    ral_err_invld_ptr,                 /*!< RAL Error- Invalid pointer */
    ral_err_timeout,                   /*!< RAL Error- Timeout */
    ral_err_name_not_found,            /*!< RAL Error- Name not found */
    ral_err_name_to_long,              /*!< RAL Error- Name to long */
    ral_err_name_taken,                /*!< RAL Error- Name taken */
    ral_err_max_limit_reached,         /*!< RAL Error- Maximum limit is reached */
    ral_err_queue_invld_size,          /*!< RAL Error- Invalid Queue size */
    ral_err_invld_arg,                 /*!< RAL Error- Invalid argument */
    ral_feature_not_supported,         /*!< RAL Error- Feature not supported */
    ral_status_max                     /*!< RAL status */

}ral_status_t;

#endif /*RAL_CMN_H*/

/**
 * @file exo_osal_timer.h
 *
 * @brief This file contains RAL to OSAL mapping for timer management.
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

#ifndef OS_OSAL_OSAL_COMMON_INC_OSAL_TIMER_H_
#define OS_OSAL_OSAL_COMMON_INC_OSAL_TIMER_H_

#include "exo_ral_timer.h"

/**
 * @brief Define the type of RAL timer handle to OS timer handle.
 */
typedef ral_timer_handle_ptr os_timer_handle_ptr;

/**
 * @brief RAL to OSAL function mapping for timer create
 */
#define os_timer_create ral_timer_create
/**
 * @brief RAL to OSAL function mapping for timer start
 */
#define os_timer_start ral_timer_start
/**
 * @brief RAL to OSAL function mapping for timer stop
 */
#define os_timer_stop ral_timer_stop
/**
 * @brief RAL to OSAL function mapping for timer restart
 */
#define os_timer_restart ral_timer_restart
/**
 * @brief RAL to OSAL function mapping for get remaining time
 */
#define os_get_remaining_time ral_get_remaining_time
/**
 * @brief RAL to OSAL function mapping for timer adjust
 */
#define os_timer_adjust ral_timer_adjust
/**
 * @brief RAL to OSAL function mapping for timer delete
 */
#define os_timer_delete ral_timer_delete
/**
 * @brief RAL to OSAL function mapping for change timer mode
 */
#define os_change_timer_mode ral_change_timer_mode

#endif /* OS_OSAL_OSAL_COMMON_INC_OSAL_TIMER_H_ */

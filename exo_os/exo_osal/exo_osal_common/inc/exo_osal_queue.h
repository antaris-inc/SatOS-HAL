/**
 * @file exo_osal_queue.h
 *
 * @brief This file contains RAL to OSAL mapping for queue management.
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

#ifndef OSAL_QUEUE_H_
#define OSAL_QUEUE_H_

#include "exo_ral_queue.h"

/**
 * @brief Define the type RAL queue handle to OS queue handle.
 */
typedef ral_queue_handle_ptr os_queue_handle_ptr;

/**
 * @brief RAL to OSAL function mapping for queue create
 */
#define os_queue_create ral_queue_create
/**
 * @brief RAL to OSAL function mapping for queue delete
 */
#define os_queue_delete ral_queue_delete
/**
 * @brief RAL to OSAL function mapping for queue flush
 */
#define os_queue_flush ral_queue_flush
/**
 * @brief RAL to OSAL function mapping for queue send
 */
#define os_queue_send ral_queue_send
/**
 * @brief RAL to OSAL function mapping for queue receive
 */
#define os_queue_receive ral_queue_receive
/**
 * @brief RAL to OSAL function mapping for queue get count
 */
#define os_queue_get_count ral_queue_get_count
/**
 * @brief RAL to OSAL function mapping for queue get remain count
 */
#define os_queue_get_remain_count ral_queue_get_remain_count

#endif /*OSAL_QUEUE_H_ */

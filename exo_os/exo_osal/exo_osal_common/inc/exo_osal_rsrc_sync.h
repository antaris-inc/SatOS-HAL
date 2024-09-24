/**
 * @file exo_osal_rsrc_sync.h
 *
 * @brief This file contains RAL to OSAL mapping for semaphore and mutex management.
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

#ifndef OSAL_RSRC_SYNC_H
#define OSAL_RSRC_SYNC_H

#include "exo_ral_rsrc_sync.h"

/**
 * @brief Define the type of RAL semaphore handle to OS semaphore handle.
 */
typedef ral_sem_handle_ptr os_sem_handle_ptr;

/**
 * @brief Define the type RAL mutex handle to OS mutex handle.
 */
typedef ral_mutex_handle_ptr os_mutex_handle_ptr;

/**
 * @brief RAL to OSAL function mapping for Binary semaphore create
 */
#define os_sem_create_bin ral_sem_create_bin
/**
 * @brief RAL to OSAL function mapping for counting semaphore create
 */
#define os_sem_create_count ral_sem_create_count
/**
 * @brief RAL to OSAL function mapping for semaphore delete
 */
#define os_sem_delete ral_sem_delete
/**
 * @brief RAL to OSAL function mapping for semaphore take
 */
#define os_sem_take ral_sem_take
/**
 * @brief RAL to OSAL function mapping for semaphore give
 */
#define os_sem_give ral_sem_give
/**
 * @brief RAL to OSAL function mapping for semaphore get count
 */
#define os_sem_get_count ral_sem_get_count
/**
 * @brief RAL to OSAL function mapping for mutex create
 */
#define os_mutex_create ral_mutex_create
/**
 * @brief RAL to OSAL function mapping for mutex delete
 */
#define os_mutex_delete ral_mutex_delete
/**
 * @brief RAL to OSAL function mapping for mutex give
 */
#define os_mutex_give ral_mutex_give
/**
 * @brief RAL to OSAL function mapping for mutex take
 */
#define os_mutex_take ral_mutex_take
/**
 * @brief RAL to OSAL function mapping for mutex get owner
 */
#define os_mutex_get_owner ral_mutex_get_owner

#endif /*OSAL_RSRC_SYNC_H*/

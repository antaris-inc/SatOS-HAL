/**
 * @file exo_ral_rsrc_sync.h
 *
 * @brief This file contains abstracted function prototypes for semaphore
 *        and mutex
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
#ifndef RSRC_SYNC_H
#define RSRC_SYNC_H

#include "exo_ral_cmn.h"
#include "exo_ral_thread.h"

typedef uint32_t ral_tick_time_t ;

/*
 * @brief semaphore type enumeration
 */
typedef enum
{
    BIN,     /*!< Binary type */
    COUNT    /*!< Counting type */
}semaphore_type;

/**
 * @brief semaphore handle structure definition
 */
typedef struct
{
    semaphore_type sem_type;    /*!< semaphore type */
    int sem_max_value;          /*!< Max value of counting semaphore  */
    int sem_initial_value;      /*!< Initial value of semaphore  */
    int sem_curr_value;         /*!< Current value of semaphore  */
    void* rtos_sem_handle;      /*!< Pointer to store the RTOS reference */

}ral_sem_handle_t;

typedef ral_sem_handle_t *ral_sem_handle_ptr;

/**
 * @brief  Mutex handle structure definition
 */
typedef struct
{
    int mutex_curr_value;              /*!< Current value of mutex  */
    ral_thread_handle_ptr mutex_owner; /*!< Mutex owner thread reference */
    void* rtos_mutex_handle;           /*!< Pointer to store the RTOS reference*/

}ral_mutex_handle_t;


/**
 * @brief Define the type of RAL mutex handle to pointer mutex handle.
 */
typedef ral_mutex_handle_t *ral_mutex_handle_ptr;

/**
 * @brief This function create binary semaphore
 *
 * @param[in]  ral_sem_id : Double pointer to semaphore handle
 *
 * @return status of create binary semaphore
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_sem_create_bin(ral_sem_handle_ptr *ral_sem_id);

/**
 * @brief This function create the counting semaphore
 *
 * @param[in]  ral_sem_id : pointer to semaphore handle
 * @param[in]  max_count : Maximum count
 * @param[in]  start_val : starting value
 *
 * @return status of semaphore count
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_sem_create_count(ral_sem_handle_ptr *ral_sem_id, int max_count,
        int start_val);

/**
 * @brief This function delete the semaphore
 *
 * @param[in]  ral_sem_id : pointer to semaphore handle
 *
 * @return status of delete semaphore
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_sem_delete(ral_sem_handle_ptr ral_sem_id );

/**
 * @brief This function acquire the semaphore
 *
 * @param[in]  ral_sem_id : pointer to semaphore handle
 * @param[in]  timeout_ticks : timeout for semaphore process
 *
 * @return status of semaphore
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_sem_take(ral_sem_handle_ptr ral_sem_id,
        ral_tick_time_t timeout_ticks);

/**
 * @brief This function release the semaphore
 *
 * @param[in]  ral_sem_id : pointer to semaphore handle
 *
 * @return status of release
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_sem_give(ral_sem_handle_ptr ral_sem_id);

/**
 * @brief This function gives the current value of the semaphore
 *
 * @param[in]  ral_q_id : pointer to semaphore handle
 * @param[in]  count : pointer to count of semaphore
 *
 * @return status of count
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_sem_get_count(ral_sem_handle_ptr ral_sem_id, uint32_t* count);

/**
 * @brief This function creates the mutex
 *
 * @param[in]  ral_mtx_id : Double pointer to mutex handle
 *
 * @return status of mutex creation
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_mutex_create(ral_mutex_handle_ptr *ral_mtx_id);

/**
 * @brief This function delete the mutex
 *
 * @param[in]  ral_mtx_id : pointer to mutex handle
 *
 * @return status of mutex deletion
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_mutex_delete(ral_mutex_handle_ptr ral_mtx_id);

/**
 * @brief This function release the mutex
 *
 * @param[in]  ral_mtx_id : pointer to mutex handle
 *
 * @return status of mutex release
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_mutex_give(ral_mutex_handle_ptr ral_mtx_id);

/**
 * @brief This function acquire the mutex
 *
 * @param[in]  ral_mtx_id : pointer to mutex handle
 * @param[in]  timeout_ticks : Timeout for acquiring
 *
 * @return status of mutex
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_mutex_take(ral_mutex_handle_ptr ral_mtx_id,
        ral_tick_time_t timeout_ticks);

/**
 * @brief This function get the owner of the mutex
 *
 * @param[in]  ral_mtx_id : pointer to mutex handle
 * @param[out] thread_id : Mutex owner id
 *
 * @return status of mutex
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_mutex_get_owner(ral_mutex_handle_ptr ral_mtx_id,
        ral_thread_handle_ptr thread_id);

#endif /*RSRC_SYNC_H*/

/**
 * @file exo_ral_linux_os.h
 *
 * @brief This file contains Linux wrapper function prototypes, macros for
 * thread, queue, semaphore, mutex.
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
#ifndef RAL_LINUX_OS_H
#define RAL_LINUX_OS_H

#include "exo_ral_common.h"


/**
 * @brief This function create the thread
 *
 * @param[in]  id : Double pointer to thread handle
 * @param[in]  stack_size : size for stack
 * @param[in]  priority : priority of thread
 * @param[in]  thread_name : pointer to name of the thread
 * @param[in]  entry_func : Entry function for thread
 * @param[in]  parameter : pointer to default parameter
 *
 * @return status of thread creation
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_thread_create(ral_thread_handle_ptr *id,
        uint32_t stack_size,ral_thread_priority_t priority,
        const char* thread_name,ral_thread_entry_func_t entry_func,
        void *parameters);

/**
 * @brief This API create the thread delay
 *
 * @param[in]  tick_time : waiting to certain time
 *
 * @return status of delay
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_thread_delay(ral_tick_time_t tick_time);

/**
 * @brief This function delete the thread
 *
 * @param[in] id : pointer to thread handle
 *
 * @return status of thread deletion
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_thread_delete(ral_thread_handle_ptr id);

/**
 * @brief This function puts the thread from running to waiting state
 *
 * @param[in] id : pointer to thread handle
 *
 * @return status of thread suspend
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_thread_suspend(ral_thread_handle_ptr id );

/**
 * @brief This function use to resume the thread
 *
 * @param[in] id : pointer to thread handle
 *
 * @return status of thread resume
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_thread_resume(ral_thread_handle_ptr id);


/*
 * @brief Mapping the Linux wrapper functionalities of thread to RAL.
 */
#define ral_common_thread_create ral_linux_thread_create
#define ral_common_thread_delay ral_linux_thread_delay
#define ral_common_thread_delete ral_linux_thread_delete
#define ral_common_thread_suspend ral_linux_thread_suspend
#define ral_common_thread_resume ral_linux_thread_resume




/**
 * @brief This function create the binary semaphore
 *
 * @param[in]  id : Double pointer to semaphore handle
 *
 * @return status of create binary semaphore
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_sem_create_bin(ral_sem_handle_ptr *id);

/**
 * @brief This function create the counting semaphore
 *
 * @param[in]  id : Double pointer to semaphore handle
 * @param[in]  max_count : Maximum count
 * @param[in]  start_val : starting value
 *
 * @return status of semaphore count
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_sem_create_count(ral_sem_handle_ptr *id, int max_count, int start_val);

/**
 * @brief This function delete the semaphore
 *
 * @param[in]  id : pointer to semaphore handle
 *
 * @return status of delete semaphore
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_sem_delete(ral_sem_handle_ptr id);

/**
 * @brief This function acquire the semaphore
 *
 * @param[in]  id : pointer to semaphore handle
 * @param[in]  timeout_ticks : timeout for semaphore process
 *
 * @return status of semaphore
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_sem_take(ral_sem_handle_ptr id, ral_tick_time_t timeout_ticks);

/**
 * @brief This function release the semaphore
 *
 * @param[in]  id : pointer to semaphore handle
 *
 * @return status of release
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_sem_give(ral_sem_handle_ptr id);

/**
 * @brief This function give the current value of the semaphore
 *
 * @param[in]  id : pointer to semaphore handle
 * @param[in]  count : pointer to count of semaphore
 *
 * @return status of count
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_sem_get_count(ral_sem_handle_ptr id, uint32_t* count);

/*
 * @brief Mapping the Linux wrapper functionalities of semaphore to RAL.
 */
#define ral_common_sem_create_bin ral_linux_sem_create_bin
#define ral_common_sem_create_count ral_linux_sem_create_count
#define ral_common_sem_delete ral_linux_sem_delete
#define ral_common_sem_take ral_linux_sem_take
#define ral_common_sem_give ral_linux_sem_give
#define ral_common_sem_get_count ral_linux_sem_get_count


/**
 * @brief This function create the timer
 *
 * @param[in]  id : Double pointer to timer handle
 * @param[in]  timer_name : pointer to name of timer
 * @param[in]  mode : mode of timer
 * @param[in]  cbfunc : callback the timer function
 * @param[in]  args : pointer to timer argument
 *
 * @return status of timer creation
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_timer_create(ral_timer_handle_ptr *id,
        const char* timer_name, ral_timer_mode_t mode,ral_timer_cbfunc_t cbfunc,
        void *args);

/**
 * @brief This function start the timer
 *
 * @param[in]  id : pointer to timer handle
 * @param[in]  tick_time : Track the timer
 *
 * @return status of timer start
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_timer_start(ral_timer_handle_ptr id,ral_tick_time_t tick_time);
/**
 * @brief This function stop the timer
 *
 * @param[in]  id : pointer to timer handle
 *
 * @return status of timer stop
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_timer_stop(ral_timer_handle_ptr id);
/**
 * @brief This function delete the timer
 *
 * @param[in]  id : pointer to timer handle
 *
 * @return status of timer deletion
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_timer_delete(ral_timer_handle_ptr id);

/*
 * @brief Mapping the Linux wrapper functionalities of timer to RAL.
 */
#define ral_common_timer_create ral_linux_timer_create
#define ral_common_timer_start ral_linux_timer_start
#define ral_common_timer_stop ral_linux_timer_stop
#define ral_common_timer_delete ral_linux_timer_delete

/*!
 * @brief This function create the queue
 *
 * @param[in]  id : Double pointer to queue handle
 * @param[in]  no_of_item : Number of item to create
 * @param[in]  item_size : size of the item
 *
 * @return status of queue creation
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_queue_create(ral_queue_handle_ptr *id,uint32_t no_of_item, uint32_t item_size);

/*!
 * @brief This function delete the queue and release its memory
 *
 * @param[in]  id : pointer to queue handle
 *
 * @return status of queue deletion
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_queue_delete(ral_queue_handle_ptr id);
/*!
 * @brief This function flush all the messages from the queue
 *
 * @param[in]  id : pointer to queue handle
 *
 * @return status of queue flush
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_queue_flush(ral_queue_handle_ptr id);
/*!
 * @brief This function adds the message in the queue
 *
 * @param[in]  id : pointer to queue handle
 * @param[in]  msg_ptr : pointer to message
 * @param[in]  timeout_ticks : Timeout for send queue
 *
 * @return status of send queue
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_queue_send(ral_queue_handle_ptr id, void *msg_ptr, ral_tick_time_t timeout_ticks);
/*!
 * @brief This function moves the message from the queue to the
 *  destination pointer
 *
 * @param[in]  id : pointer to queue handle
 * @param[in]  msg_ptr : pointer to message
 * @param[in]  timeout_ticks : Timeout for receive queue
 *
 * @return status of receive queue
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_queue_receive(ral_queue_handle_ptr id, void *msg_ptr ,ral_tick_time_t tick_time);
/*!
 * @brief This API get the number of elements that are actually
 *  in the Queue .
 *
 * @param[in]  id : pointer to queue handle
 *
 * @return Element count
 */
uint32_t ral_linux_queue_get_count(ral_queue_handle_ptr id);
/*!
 * @brief This function get remaining number of element
 *  in the queue
 *
 * @param[in]  id : pointer to queue handle
 *
 * @return No.of remaining queue elements
 */
uint32_t ral_linux_queue_get_remain_count(ral_queue_handle_ptr id);

/*
 * @brief Mapping the Linux wrapper functionalities of queue to RAL.
 */
#define ral_common_queue_create ral_linux_queue_create
#define ral_common_queue_delete ral_linux_queue_delete
#define ral_common_queue_flush ral_linux_queue_flush
#define ral_common_queue_send ral_linux_queue_send
#define ral_common_queue_receive ral_linux_queue_receive
#define ral_common_queue_get_count ral_linux_queue_get_count
#define ral_common_queue_get_remain_count ral_linux_queue_get_remain_count


/**
 * @brief This function create the mutex
 *
 * @param[in]  id : Double pointer to mutex handle
 *
 * @return status of mutex creation
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_mutex_create(ral_mutex_handle_ptr *id);

/**
 * @brief This function delete the mutex
 *
 * @param[in]  id : pointer to mutex handle
 *
 * @return status of mutex deletion
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_mutex_delete(ral_mutex_handle_ptr id);

/**
 * @brief This function release the mutex
 *
 * @param[in]  id : pointer to mutex handle
 *
 * @return status of mutex release
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_mutex_give(ral_mutex_handle_ptr id);

/**
 * @brief This function acquire the mutex
 *
 * @param[in]  id : pointer to mutex handle
 * @param[in]  timeout_ticks : Timeout for acquiring
 *
 * @return status of mutex
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_mutex_take(ral_mutex_handle_ptr id, ral_tick_time_t timeout_ticks);

/**
 * @brief This function give the mutex owner task id
 *
 * @param[in]  id : pointer to mutex handle
 * @param[out] thread_id : Mutex owner id
 *
 * @return status of mutex
 *
 * @retval ral_success->success, ral_error->error
 */
ral_status_t ral_linux_mutex_get_owner(ral_mutex_handle_ptr id, ral_thread_handle_ptr thread_id);

/*
 * @brief Mapping the Linux wrapper functionalities of mutex to RAL.
 */
#define ral_common_mutex_create ral_linux_mutex_create
#define ral_common_mutex_delete ral_linux_mutex_delete
#define ral_common_mutex_give ral_linux_mutex_give
#define ral_common_mutex_take ral_linux_mutex_take
#define ral_common_mutex_get_owner ral_linux_mutex_get_owner


#endif /*RAL_LINUX_OS_H*/

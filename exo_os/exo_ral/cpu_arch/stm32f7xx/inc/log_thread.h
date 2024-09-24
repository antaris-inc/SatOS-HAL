/**
 * @file log_thread.h
 *
 * @brief This file contains structure definitions and function prototypes
 *        for debug logging.
 * 
 *  @copyright Copyright 2024 Antaris, Inc.
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

#ifndef _LOG_THREAD_
#define _LOG_THREAD_

#include "exo_osal.h"
#include "notify_apps.h"

#define LOG_ENB         ///< Enable logger

/**
 * @brief Logger control block structure definition.
 */
typedef struct
{
	uint8_t *logger_buff;                        /*!< pointer to logger buffer */
	uint32_t total_buff_size;                    /*!< Size of total buffer in bytes */
	uint32_t start_idx;                          /*!< Starting index */
	uint32_t end_idx;                            /*!< End Index */
	uint32_t uart_idx;                           /*!< UART interface index */
	uint8_t roll_back_flag;                      /*!< Roll back flag */
	uint8_t uart_roll_back_flag;                 /*!< UART Roll back flag */
	volatile uint32_t drop_print_cnt;            /*!< count of drop print */
	volatile uint32_t trancated_print_cnt;       /*!< count of truncated print */
	ral_sem_handle_ptr sync_prot;                /*!< pointer to semaphore handle */
	ral_sem_handle_ptr wakeup;                   /*!< pointer to semaphore handle */
	uint32_t time_out;                           /*!< semaphore timer error count */
	uint32_t is_irq_mode;                        /*!< Interrupt mode error count */
	uint32_t semtake_error;                      /*!< semaphore take error count */
}logger_cb_t;

/**
 * @brief This API push the data to buffer.
 *
 * @param[in] ptr : pointer to data buffer
 * @param[in] len : length of data in bytes
 *
 * @return status of push data
 * @retval 0->Fail, 1->success
 */
uint8_t push_data_to_buff(char *ptr,int len);

/**
 * @brief This API send the debug log to ground station.
 *
 * @param[in] len : length of data in bytes
 * @param[in] mtu : Maximum transfer unit.
 */
void send_buff_data(uint32_t len,uint32_t mtu);

/**
 * @brief This API initialize the logger thread.
 */
void log_thread_init();
/**
 * @brief Logger thread entry function.
 */
void log_hdlr_thrd(void* args);
/**
 * @brief This API is unblock the looger thread.
 */
void wakeup_print();
/**
 * @brief This function print the error metric.
 */
void printf_metrix_sts();

/**
 * @brief This API notify the file transfer error status.
 *
 * @param[in] ft_sts : pointer to file transfer info
 */
void log_thread_notificataion_api_upld(ft_notification_info *ft_sts);

#endif /*_LOG_THREAD_*/

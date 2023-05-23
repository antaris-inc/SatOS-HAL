/**
 * @file exo_io_al_sos_timer.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for RTC interface
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

#ifndef DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_COMMON_RTC_INC_EXO_IO_AL_SOS_TIMER_H_
#define DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_COMMON_RTC_INC_EXO_IO_AL_SOS_TIMER_H_



#include <stdint.h>
#include <time.h>

/**
 * @brief IO-HAl RTC time structure definition
 */
typedef struct
{
    uint8_t hour;		/*!< RTC hour 		*/
    uint8_t min;		/*!< RTC minute 	*/
    uint8_t sec;		/*!< RTC seconds 	*/

}sys_time_s;

/**
 * @brief IO-HAl RTC date structure definition
 */
typedef struct
{
    uint8_t date;		/*!< RTC date 	*/
    uint8_t month;		/*!< RTC month 	*/
    uint16_t year;		/*!< RTC year 	*/

}sys_date_s;

/**
 * @brief IO-HAl RTC time and date structure definition
 */
typedef struct
{
    uint8_t hour;			/*!< RTC hour 			*/
    uint8_t minute;			/*!< RTC minute 		*/
    uint8_t seconds;		/*!< RTC seconds 		*/
    uint8_t date;			/*!< RTC date 			*/
    uint8_t month;			/*!< RTC month 			*/
    uint16_t year;			/*!< RTC year 			*/
    uint8_t rsvrd;			/*!< RTC reserved bit 	*/

}__attribute__((__packed__))sys_time_date_s;

/**
 * @brief  This function get the current date
 * @param[out]  get_date - get_date pointer to a sys_date_s structure that contains
 *             the configuration information for RTC module
 * @retval HAL status
 */
uint8_t crnt_date(sys_date_s *get_date);
/**
 * @brief  This function get the current time
 * @param[out]  get_time - get_time pointer to a sys_time_s structure that contains
 *             the configuration information for RTC module
 * @retval HAL status
 */
uint8_t crnt_time(sys_time_s *get_time);
/**
 * @brief  This function get the current time and date
 * @param[out]  time_date - time_date pointer to a sys_time_date_s structure that contains
 *             the configuration information for RTC module
 * @retval HAL status
 */
uint8_t get_crnt_time_date(sys_time_date_s *time_date);
/**
 * @brief  This function get the current date and time and then store in nvm
 * @retval No return
 */
void rtc_set_time_date_nvm_shutdown();
/**
 * @brief  This function set the current time and date in nvm
 * @param[in]  time_date - time_date pointer to a sys_time_date_s structure that contains
 *             the configuration information for RTC module
 * @retval Epoch time
 */
uint64_t set_crnt_time_date_withnvm(sys_time_date_s *time_date);
/**
 * @brief  This function set the current time and date
 * @param[in]  epoch_time - Receive the time in epoch format
 * @retval Epoch time
 */
uint8_t set_crnt_time_date(uint64_t epoch_time);
/**
 * @brief  This function add the offset to the running time
 * @param[in]  time_err_secs - No of seconds to be added
 * @retval No return
 */
void rtc_err_crt(uint8_t time_err_secs);
/**
 * @brief  This function get the current time and date in epoch format
 * @retval Epoch time
 */
uint64_t get_crnt_time_date_in_epoch(void);
/**
 * @brief  This function get the time and date from the nvm
 * @retval No return
 */
void rtc_nvm_reload(void);
/**
 * @brief  This function set the current time and date
 * @retval No return
 */
void preload_saved_rtc(void);



#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_COMMON_RTC_INC_EXO_IO_AL_SOS_TIMER_H_ */

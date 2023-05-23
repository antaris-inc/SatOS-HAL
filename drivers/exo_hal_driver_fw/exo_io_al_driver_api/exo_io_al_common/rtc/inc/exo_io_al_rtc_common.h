/**
 * @file exo_io_al_rtc_common.h
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

#ifndef DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_COMMON_RTC_INC_EXO_IO_AL_RTC_COMMON_H_
#define DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_COMMON_RTC_INC_EXO_IO_AL_RTC_COMMON_H_

#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "stdint.h"

#define RTC_INTF_ENB



#ifndef LINUX_TEMP_PORT

#define RTC_ALARM_A_EVENT_CB     		check_rtc_dummy				///< RTC alarm A callback event
#define RTC_ALARM_B_EVENT_CB          	check_rtc_dummy				///< RTC alarm B callback event
#define RTC_TIMESTAMP_EVENT_CB          check_rtc_dummy				///< RTC timestamp callback event
#define RTC_WAKEUPTIMER_EVENT_CB        check_rtc_dummy				///< RTC wakeup timer callback event
#define RTC_TAMPER1_EVENT_CB            check_rtc_dummy				///< RTC tamper 1 callback event
#define RTC_TAMPER2_EVENT_CB            check_rtc_dummy				///< RTC tamper 2 callback event
#define RTC_TAMPER3_EVENT_CB            check_rtc_dummy				///< RTC tamper 3 callback event
#define RTC_MSPINIT_CB                  check_rtc_dummy				///< RTC MSP init callback event
#define RTC_MSPDEINIT_CB                check_rtc_dummy				///< RTC MSP deinit callback event

#else

#define RTC_ALARM_A_EVENT_CB     	     linux_rtc_dummy_fn					///< RTC alarm A callback event
#define RTC_ALARM_B_EVENT_CB          	linux_rtc_dummy_fn					///< RTC alarm B callback event
#define RTC_TIMESTAMP_EVENT_CB          linux_rtc_dummy_fn					///< RTC timestamp callback event
#define RTC_WAKEUPTIMER_EVENT_CB        linux_rtc_dummy_fn					///< RTC wakeup timer callback event
#define RTC_TAMPER1_EVENT_CB            linux_rtc_dummy_fn					///< RTC tamper 1 callback event
#define RTC_TAMPER2_EVENT_CB            linux_rtc_dummy_fn					///< RTC tamper 2 callback event
#define RTC_TAMPER3_EVENT_CB            linux_rtc_dummy_fn					///< RTC tamper 3 callback event
#define RTC_MSPINIT_CB                  linux_rtc_dummy_fn					///< RTC MSP init callback event
#define RTC_MSPDEINIT_CB                linux_rtc_dummy_fn					///< RTC MSP deinit callback event


#endif



/**
 * @brief IO-HAl RTC interface control block handle structure definition
 */
typedef struct _ioal_rtc_hdle
{
    ioal_intf_gen_info intf_gen_info; 							/*!< Hold general information of interface  	*/
    void (*alarm_a_event_cb)(struct _ioal_rtc_hdle *hrtc);		/*!< Fn address of alarm A event callback   	*/
    void (*alarm_b_event_cb)(struct _ioal_rtc_hdle *hrtc);		/*!< Fn address of alarm B event callback   	*/
    void (*timestamp_event_cb)(struct _ioal_rtc_hdle *hrtc);	/*!< Fn address of timestamp event callback 	*/
    void (*wakeup_timer_event_cb)(struct _ioal_rtc_hdle *hrtc); /*!< Fn address of wakeup timer event callback 	*/
    void (*tamper_1_event_cb)(struct _ioal_rtc_hdle *hrtc);		/*!< Fn address of tamper 1 event callback 		*/
    void (*tamper_2_event_cb)(struct _ioal_rtc_hdle *hrtc);		/*!< Fn address of tamper 2 event callback 		*/
    void (*tamper_3_event_cb)(struct _ioal_rtc_hdle *hrtc);		/*!< Fn address of tamper 3 event callback 		*/
    void (*msp_init_cb)(struct _ioal_rtc_hdle *hrtc);			/*!< Fn address of msp init event callback 		*/
    void (*msp_deinit_cb)(struct _ioal_rtc_hdle *hrtc);			/*!< Fn address of msp deinit event callback 	*/

}ioal_rtc_hdle;

typedef void (*iohal_rtc_cb)(void* args);

/**
 * @brief IO-HAl RTC time structure definition
 */
typedef struct
{
    uint8_t hours;            /*!< RTC time hour 				*/
    uint8_t minutes;          /*!< RTC Time Minutes				*/
    uint8_t seconds;          /*!< RTC Time Seconds.			*/
    uint32_t subseconds;      /*!< RTC_SSR RTC Sub Second 		*/
    uint32_t secondfraction;  /*!< RTC second fraction 			*/
    uint8_t timeformat;       /*!< RTC AM/PM Time.				*/
    uint32_t daylightsaving;  /*!< RTC Daylight Saving Time	    */
    uint32_t storeoperation;  /*!< RTC store operation          */
}iohal_rtc_timetypedef;

/**
 * @brief IO-HAl RTC date structure definition
 */
typedef struct
{
    uint8_t weekday;  		/*!< RTC Date WeekDay.						 */
    uint8_t month;    		/*!< RTC Date Month 						 */
    uint8_t date;     		/*!< RTC Date.								 */
    uint8_t year;     		/*!< RTC Date Year		 					 */

}iohal_rtc_datetypedef;

/**
 * @brief IO-HAl RTC alarm structure definition
 */
typedef struct
{
    iohal_rtc_timetypedef alarmtime;    /*!< RTC Alarm Time members 				*/
    uint32_t alarmmask;            	   	/*!< RTC Alarm Masks						*/
    uint32_t alarmsubsecondmask;   	   	/*!< RTC Alarm SubSeconds Masks				*/
    uint32_t alarmdateweekdaysel;       /*!< RTC Alarm is on Date or WeekDay		*/
    uint8_t alarmdateweekday;           /*!< RTC Alarm Date/WeekDay					*/
    uint32_t alarm;               	   	/*!< RTC alarm 						 		*/
}iohal_rtc_alarmtypedef;

/**
 * @brief  This function initializes the RTC
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_init(void);
/**
 * @brief  This function initializes RTC callback events
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @retval HAL status
 */
void io_hal_rtc_cb_init(ioal_rtc_hdle *hrtc);
/**
 * @brief  This function set the time in RTC
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @param[in]  stime - stime pointer to a iohal_rtc_timetypedef structure that contains
 *             the configuration information for RTC module
 * @param[in]  format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_set_time(ioal_rtc_hdle *hrtc,iohal_rtc_timetypedef *stime,uint32_t format);
/**
 * @brief  This function get the time from RTC
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @param[out] stime - stime pointer to a iohal_rtc_timetypedef structure that contains
 *             the configuration information for RTC module
 * @param[in]  format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_get_time(ioal_rtc_hdle *hrtc,iohal_rtc_timetypedef *stime,uint32_t format);
/**
 * @brief  This function set the date in RTC
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @param[in]  sdate - sdate pointer to a iohal_rtc_datetypedef structure that contains
 *             the configuration information for RTC module
 * @param[in]  format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_set_date(ioal_rtc_hdle *hrtc,iohal_rtc_datetypedef *sdate,uint32_t format);
/**
 * @brief  This function get the date from RTC
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @param[out] sdate - sdate pointer to a iohal_rtc_datetypedef structure that contains
 *             the configuration information for RTC module
 * @param[in]  format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_get_date(ioal_rtc_hdle *hrtc,iohal_rtc_datetypedef *sdate,uint32_t format);
/**
 * @brief  This function set the alarm in RTC
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @param[in]  salarm - salarm pointer to a iohal_rtc_alarmtypedef structure that contains
 *             the configuration information for RTC module
 * @param[in]  format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_set_alarm(ioal_rtc_hdle *hrtc,iohal_rtc_alarmtypedef *salarm,uint32_t format);
/**
 * @brief  This function set the alarm in interrupt mode
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @param[in]  salarm - salarm pointer to a iohal_rtc_alarmtypedef structure that contains
 *             the configuration information for RTC module
 * @param[in]  format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_set_alarmit(ioal_rtc_hdle *hrtc,iohal_rtc_alarmtypedef *salarm,uint32_t format);
/**
 * @brief  This function deativates the alarm from RTC
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @param[in]  alarm - It specifies the Alarm
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_deactivate_alarm(ioal_rtc_hdle *hrtc,uint32_t alarm);
/**
 * @brief  This function get the alarm from RTC
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @param[out] salarm - salarm pointer to a iohal_rtc_alarmtypedef structure that contains
 *             the configuration information for RTC module
 * @param[in]  alarm - It specifies the Alarm
 * @param[in]  format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_get_alarm(ioal_rtc_hdle *hrtc,iohal_rtc_alarmtypedef *salarm,uint32_t alarm,uint32_t format);
/**
 * @brief  This function poll the alarm event in RTC
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @param[in]  timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_poll_alarmevent(ioal_rtc_hdle *hrtc,uint32_t timeout);
/**
 * @brief  This function configure the resynchronisation mode in RTC
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_wait_synchro(ioal_rtc_hdle *hrtc);
/**
 * @brief  This function get the RTC state
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_get_state(ioal_rtc_hdle *hrtc);
/**
 * @brief  This function puts the RTC to initialization mode
 * @param[in]  hrtc - hrtc pointer to a ioal_rtc_hdle structure that contains
 *             the configuration information for RTC module
 * @retval HAL status
 */
hal_ret_sts io_hal_rtc_init_mode(ioal_rtc_hdle *hrtc);



#ifndef LINUX_TEMP_PORT

void check_rtc_dummy(ioal_rtc_hdle *hrtc);

#else

/**
 * @brief This is RTC interface dummy function for linux
 */
void linux_rtc_dummy_fn(struct _ioal_rtc_hdle *hrtc);
#endif



#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_COMMON_RTC_INC_EXO_IO_AL_RTC_COMMON_H_ */

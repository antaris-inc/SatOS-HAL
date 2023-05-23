/**
 * @file exo_io_al_stm32f7xx_rtc.h
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

#ifndef DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_WRAPPER_EXO_IO_AL_STM32F7XX_RTC_INC_EXO_IO_AL_STM32F7XX_RTC_H_
#define DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_WRAPPER_EXO_IO_AL_STM32F7XX_RTC_INC_EXO_IO_AL_STM32F7XX_RTC_H_

#include "exo_types.h"
#include "exo_hal_common.h"
#include "exo_io_al_common.h"
#include "exo_io_al_rtc_common.h"
#include "exo_io_al_stm32f7xx_common.h"

/**
 * @brief  VDP layer RTC callback ID
 */
typedef enum
{
    IOHAL_RTC_ALARM_A_EVENT_CB_ID           = 0x00u,    ///< RTC Alarm A Event Callback ID
    IOHAL_RTC_ALARM_B_EVENT_CB_ID           = 0x01u,    ///< RTC Alarm B Event Callback ID
    IOHAL_RTC_TIMESTAMP_EVENT_CB_ID         = 0x02u,    ///< RTC TimeStamp Event Callback ID
    IOHAL_RTC_WAKEUPTIMER_EVENT_CB_ID       = 0x03u,    ///< RTC Wake-Up Timer Event Callback ID
    IOHAL_RTC_TAMPER1_EVENT_CB_ID           = 0x04u,    ///< RTC Tamper 1 Callback ID
    IOHAL_RTC_TAMPER2_EVENT_CB_ID           = 0x05u,    ///< RTC Tamper 2 Callback ID
    IOHAL_RTC_TAMPER3_EVENT_CB_ID           = 0x06u,    ///< RTC Tamper 3 Callback ID
    IOHAL_RTC_MSPINIT_CB_ID                 = 0x0Eu,    ///< RTC Msp Init callback ID
    IOHAL_RTC_MSPDEINIT_CB_ID               = 0x0Fu     ///< RTC Msp DeInit callback ID

}iohal_rtc_callbackidtypedef;


/**
 * @brief This function initializes the control block memory and do the basic
 *   		configurations RTC
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_rtc_init(ioal_rtc_hdle *ioal_hrtc);
/**
 * @brief This function initializes RTC callback events
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @param[in] callbackid - ID of the callback events
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_rtc_reg_cb(ioal_rtc_hdle *ioal_hrtc,iohal_rtc_callbackidtypedef callbackid);
/**
 * @brief This function set the time in RTC
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @param[in] stime - stime pointer to a iohal_rtc_timetypedef structure that contains
 *             the configuration information for RTC module
 * @param[in] format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_set_time(ioal_rtc_hdle *ioal_hrtc,iohal_rtc_timetypedef *stime, uint32 format);
/**
 * @brief This function get the time from RTC
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @param[out]stime - stime pointer to a iohal_rtc_timetypedef structure that contains
 *             the configuration information for RTC module
 * @param[in] format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_get_time(ioal_rtc_hdle *ioal_hrtc,iohal_rtc_timetypedef *stime, uint32 format);
/**
 * @brief This function set the date in RTC
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @param[in] sdate - sdate pointer to a iohal_rtc_datetypedef structure that contains
 *             the configuration information for RTC module
 * @param[in] format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_set_date(ioal_rtc_hdle *ioal_hrtc, iohal_rtc_datetypedef *sdate ,uint32 format);
/**
 * @brief This function get the date from RTC
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @param[out]sdate - sdate pointer to a iohal_rtc_datetypedef structure that contains
 *             the configuration information for RTC module
 * @param[in] format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_get_date(ioal_rtc_hdle *ioal_hrtc, iohal_rtc_datetypedef *sdate, uint32 format);
/**
 * @brief This function set the alarm in RTC
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @param[in] salarm - salarm pointer to a iohal_rtc_alarmtypedef structure that contains
 *             the configuration information for RTC module
 * @param[in] format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_set_alarm(ioal_rtc_hdle *ioal_hrtc, iohal_rtc_alarmtypedef *salarm, uint32 format);
/**
 * @brief This function set the alarm with interrupt mode
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @param[in] salarm - salarm pointer to a iohal_rtc_alarmtypedef structure that contains
 *             the configuration information for RTC module
 * @param[in] format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_set_alarmit(ioal_rtc_hdle *ioal_hrtc, iohal_rtc_alarmtypedef *salarm, uint32 format);
/**
 * @brief This function deativates the alarm
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @param[in] salarm - It specifies the Alarm
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_deactivate_alarm(ioal_rtc_hdle *ioal_hrtc, uint32 alarm);
/**
 * @brief This function get the alarm from RTC
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @param[out]salarm - salarm pointer to a iohal_rtc_alarmtypedef structure that contains
 *             the configuration information for RTC module
 * @param[in] salarm - It specifies the Alarm
 * @param[in] format - Format of the time
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_get_alarm(ioal_rtc_hdle *ioal_hrtc, iohal_rtc_alarmtypedef *salarm, uint32_t alarm,uint32 format);
/**
 * @brief This function poll the alarm event
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @param[in]  timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_poll_alarmevent(ioal_rtc_hdle *ioal_hrtc, uint32 timeout);
/**
 * @brief This function configure the RTC resynchronization mode
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_wait_synchro(ioal_rtc_hdle *ioal_hrtc);
/**
 * @brief This function get the RTC state
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_get_state(ioal_rtc_hdle *ioal_hrtc);
/**
 * @brief This function put the RTC to initialization mode
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_rtc_init_mode(ioal_rtc_hdle *ioal_hrtc);

#define io_hal_common_rtc_init                  io_hal_stm32f7xx_rtc_init
#define io_hal_common_rtc_unregcallback			io_hal_stm32f7xx_rtc_unregcallback
#define io_hal_common_rtc_set_time				io_hal_stm32f7xx_rtc_set_time
#define io_hal_common_rtc_get_time				io_hal_stm32f7xx_rtc_get_time
#define io_hal_common_rtc_set_date 				io_hal_stm32f7xx_rtc_set_date
#define io_hal_common_rtc_get_date				io_hal_stm32f7xx_rtc_get_date
#define io_hal_common_rtc_set_alarm				io_hal_stm32f7xx_rtc_set_alarm
#define io_hal_common_rtc_set_alarmit			io_hal_stm32f7xx_rtc_set_alarmit
#define io_hal_common_rtc_deactivate_alarm		io_hal_stm32f7xx_rtc_deactivate_alarm
#define io_hal_common_rtc_get_alarm				io_hal_stm32f7xx_rtc_get_alarm
#define io_hal_common_rtc_poll_alarmevent		io_hal_stm32f7xx_rtc_poll_alarmevent
#define io_hal_common_rtc_wait_synchro			io_hal_stm32f7xx_rtc_wait_synchro
#define io_hal_common_rtc_get_state				io_hal_stm32f7xx_rtc_get_state
#define io_hal_common_rtc_init_mode				io_hal_stm32f7xx_rtc_init_mode
#define io_hal_common_rtc_reg_cb			    io_hal_stm32f7xx_rtc_reg_cb

#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_WRAPPER_EXO_IO_AL_STM32F7XX_RTC_INC_EXO_IO_AL_STM32F7XX_RTC_H_ */

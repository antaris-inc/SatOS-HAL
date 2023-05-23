/**
 * @file exo_io_al_rtc_commons.c
 *
 * @brief This file contains abstracted function definition for RTC interface
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

#include <stdio.h>
#include <unistd.h>
#include "exo_io_al_rtc_common.h"
#include "exo_hal_io_al_common.h"
#ifndef LINUX_TEMP_PORT
#include "exo_io_al_stm32f7xx_rtc.h"
#else
#include "exo_io_al_linux_rtc.h"
#endif

extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];
ioal_rtc_hdle ioal_hrtc;

/**
 * @brief This API initializes the control block memory
 * and do the basic configurations for RTC
 */
hal_ret_sts io_hal_rtc_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL RTC Initialise");
    usleep(100000);
#endif
    hal_ret_sts ret_sts;
    if(HAL_SCS == io_hal_common_rtc_init(&ioal_hrtc))
    {
        intf_inst_hdle_ptr[IOAL_INST_RTC] = &ioal_hrtc;

    }
    else
    {

        ret_sts = HAL_IO_INIT_ERR;
    }
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL RTC Initialisation completed successfully");
#endif
    return ret_sts;
}

/**
 * @brief This API initializes the RTC callback events
 */
void io_hal_rtc_cb_init(ioal_rtc_hdle *hrtc)
{
    hrtc->alarm_a_event_cb = RTC_ALARM_A_EVENT_CB;
    hrtc->alarm_b_event_cb = RTC_ALARM_B_EVENT_CB;
    hrtc->timestamp_event_cb= RTC_TIMESTAMP_EVENT_CB;
    hrtc->wakeup_timer_event_cb = RTC_WAKEUPTIMER_EVENT_CB;
    hrtc->tamper_1_event_cb= RTC_TAMPER1_EVENT_CB;
    hrtc->tamper_2_event_cb = RTC_TAMPER2_EVENT_CB;
    hrtc->tamper_3_event_cb = RTC_TAMPER3_EVENT_CB;
    hrtc->msp_init_cb = RTC_MSPINIT_CB;
    hrtc->msp_init_cb = RTC_MSPDEINIT_CB;

#ifndef LINUX_TEMP_PORT
    io_hal_common_rtc_reg_cb(hrtc, IOHAL_RTC_ALARM_A_EVENT_CB_ID);
    io_hal_common_rtc_reg_cb(hrtc,  IOHAL_RTC_ALARM_B_EVENT_CB_ID);
    io_hal_common_rtc_reg_cb(hrtc,  IOHAL_RTC_TIMESTAMP_EVENT_CB_ID);
    io_hal_common_rtc_reg_cb(hrtc, IOHAL_RTC_WAKEUPTIMER_EVENT_CB_ID);
    io_hal_common_rtc_reg_cb(hrtc, IOHAL_RTC_TAMPER1_EVENT_CB_ID);
    io_hal_common_rtc_reg_cb(hrtc, IOHAL_RTC_TAMPER2_EVENT_CB_ID);
    io_hal_common_rtc_reg_cb(hrtc, IOHAL_RTC_TAMPER3_EVENT_CB_ID);
    io_hal_common_rtc_reg_cb(hrtc, IOHAL_RTC_MSPINIT_CB_ID);
    io_hal_common_rtc_reg_cb(hrtc, IOHAL_RTC_MSPDEINIT_CB_ID);
#endif
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief This API set the time in RTC
 */
hal_ret_sts io_hal_rtc_set_time(ioal_rtc_hdle *hrtc,iohal_rtc_timetypedef *stime,uint32_t format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_set_time(hrtc,stime,format))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }

    return ret_sts;
}

/**
 * @brief This API get the time from RTC
 */
hal_ret_sts io_hal_rtc_get_time(ioal_rtc_hdle *hrtc,iohal_rtc_timetypedef *stime,uint32_t format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_get_time(hrtc,stime,format))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API set the date in RTC
 */
hal_ret_sts io_hal_rtc_set_date(ioal_rtc_hdle *hrtc,iohal_rtc_datetypedef *sdate,uint32_t format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_set_date(hrtc,sdate,format))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API get the date from RTC
 */
hal_ret_sts io_hal_rtc_get_date(ioal_rtc_hdle *hrtc,iohal_rtc_datetypedef *sdate,uint32_t format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;

    if(HAL_SCS == io_hal_common_rtc_get_date(hrtc,sdate,format))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API set the alarm in RTC
 */
hal_ret_sts io_hal_rtc_set_alarm(ioal_rtc_hdle *hrtc,iohal_rtc_alarmtypedef *salarm,uint32_t format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_set_alarm(hrtc,salarm,format))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API set the alarm in interrupt mode
 */
hal_ret_sts io_hal_rtc_set_alarmit(ioal_rtc_hdle *hrtc,iohal_rtc_alarmtypedef *salarm,uint32_t format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_set_alarmit(hrtc,salarm,format))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API deativates the alarm from RTC
 */
hal_ret_sts io_hal_rtc_deactivate_alarm(ioal_rtc_hdle *hrtc,uint32_t alarm)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_deactivate_alarm(hrtc,alarm))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API get the alarm from RTC
 */
hal_ret_sts io_hal_rtc_get_alarm(ioal_rtc_hdle *hrtc,iohal_rtc_alarmtypedef *salarm,uint32_t alarm,uint32_t format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_get_alarm(hrtc,salarm,alarm,format))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API poll the alarm event in RTC
 */
hal_ret_sts io_hal_rtc_poll_alarmevent(ioal_rtc_hdle *hrtc,uint32_t timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_poll_alarmevent(hrtc,timeout))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API configure the resynchronization mode in RTC
 */
hal_ret_sts io_hal_rtc_wait_synchro(ioal_rtc_hdle *hrtc)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_wait_synchro(hrtc))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This api get the RTC state
 */
hal_ret_sts io_hal_rtc_get_state(ioal_rtc_hdle *hrtc)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_get_state(hrtc))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API put the RTC to initialization mode
 */
hal_ret_sts io_hal_rtc_init_mode(ioal_rtc_hdle *hrtc)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    hrtc->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_rtc_init_mode(hrtc))
    {
        ret_sts = HAL_SCS;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
        hrtc->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

#endif

#ifndef LINUX_TEMP_PORT

void check_rtc_dummy(ioal_rtc_hdle *hrtc)
{
    return;
}

#else

/**
 * @brief This is RTC interface dummy function for linux
 */
void linux_rtc_dummy_fn(struct _ioal_rtc_hdle *hrtc)
{
}

#endif

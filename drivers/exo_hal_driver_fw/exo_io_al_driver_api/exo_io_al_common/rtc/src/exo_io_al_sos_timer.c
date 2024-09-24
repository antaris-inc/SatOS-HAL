/**
 * @file exo_io_al_sos_timer.c
 *
 * @brief This file contains abstracted function definition for RTC interface
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

#ifndef LINUX_TEMP_PORT

#endif
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "exo_io_al_sos_timer.h"
#include "exo_hal_common.h"
#include "exo_io_al_rtc_common.h"
#include "exo_common.h"
#include <time.h>
#include "exo_io_al_sos_timer.h"

#define RTC_FORMAT_BIN      0x00000000U  ///< RTC format binary
#define RTC_FORMAT_BCD      0x00000001U ///< RTC format BCD

extern ioal_rtc_hdle ioal_hrtc; ///< IOAL RTC handlers
uint8_t rtc_nvm_flag;   ///< RTC NVM flag

#ifdef LINUX_TEMP_PORT
uint64_t linux_epoch_start=0; ///< Linux epoch start
#endif

uint64_t nvm_start_epoch_time=0; ///< NVM start epoch time

/*!
 *  @brief This API gets the current time and date
 */
uint8_t get_crnt_time_date(sys_time_date_s *time_date)
{
    uint8_t sts;
#ifndef LINUX_TEMP_PORT
    sts =HAL_MAX_ERR;
    iohal_rtc_datetypedef sdate;
    iohal_rtc_timetypedef stime;
    if(time_date != NULL )
    {
        if(io_hal_rtc_get_time(&ioal_hrtc,&stime,RTC_FORMAT_BIN)==HAL_SCS)
        {
            if(io_hal_rtc_get_date(&ioal_hrtc,&sdate,RTC_FORMAT_BIN)==HAL_SCS)
            {
                time_date->hour     =stime.hours;
                time_date->minute   =stime.minutes;
                time_date->seconds  =stime.seconds;
                time_date->date     =sdate.date;
                time_date->month    =sdate.month;
                time_date->year     =sdate.year + 2000;
                sts = HAL_SCS;
            }
            else
            {
                sts = HAL_IO_TX_ERR;
            }
        }
        else
        {
            sts = HAL_IO_TX_ERR;
        }
    }
    else
    {
        sts = HAL_IO_INVLD_INST_ID;
    }

#else
    sts = 1;
    struct tm *crnt_dt_tm;
    uint64_t rawtime;
    time((time_t*)&rawtime );
    rawtime = rawtime - linux_epoch_start;
    rawtime = rawtime + nvm_start_epoch_time;
    crnt_dt_tm = localtime((time_t*)&rawtime);
    if(time_date != NULL)
    {
        time_date->hour     = crnt_dt_tm->tm_hour;
        time_date->minute   = crnt_dt_tm->tm_min;
        time_date->seconds  = crnt_dt_tm->tm_sec;
        time_date->date     = crnt_dt_tm->tm_mday;
        time_date->month    = crnt_dt_tm->tm_mon +1;
        time_date->year     = crnt_dt_tm->tm_year + 1900;

        sts = 0;
    }
    else
    {
        sts = 1;
    }

#endif
    return sts;
}

/*!
 *  @brief This API get the current date
 */
uint8_t crnt_date(sys_date_s *get_date)
{
    uint8_t sts =HAL_MAX_ERR;
    sys_time_date_s time_date={0};
    sts = get_crnt_time_date(&time_date);

    get_date->date = time_date.date;
    get_date->month = time_date.month;
    get_date->year = time_date.year;

    return sts;
}

/*!
 *  @brief This API get the current time
 */
uint8_t crnt_time(sys_time_s *get_time)
{
    uint8_t sts =HAL_MAX_ERR;
    sys_time_date_s time_date={0};

    sts = get_crnt_time_date(&time_date);
    get_time->hour = time_date.hour;
    get_time->min = time_date.minute;
    get_time->sec = time_date.seconds;

    return sts;
}

/*!
 *  @brief This API set the current date and time
 */
uint8_t set_crnt_time_date(uint64_t epoch_time)
{
    uint8_t sts;
#ifndef LINUX_TEMP_PORT
    sts =HAL_MAX_ERR;
    struct tm *tm_ptr;
    iohal_rtc_timetypedef stime = {0};
    memset(&stime,0,sizeof(iohal_rtc_timetypedef));
    iohal_rtc_datetypedef sdate = {0};
    tm_ptr=localtime((time_t*)&epoch_time);

    stime.hours = tm_ptr->tm_hour;
    stime.minutes = tm_ptr->tm_min;
    stime.seconds = tm_ptr->tm_sec;
    sdate.year    = tm_ptr->tm_year + 1900 - 2000;
    sdate.month   = tm_ptr->tm_mon  + 1;
    sdate.date    = tm_ptr->tm_mday ;

    if(io_hal_rtc_set_time(&ioal_hrtc,&stime,RTC_FORMAT_BIN)==HAL_SCS)
    {
        if(io_hal_rtc_set_date(&ioal_hrtc,&sdate,RTC_FORMAT_BIN)==HAL_SCS)
        {
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_IO_TX_ERR;
        }
    }
    else
    {
        sts = HAL_IO_TX_ERR;
    }

#else
    sts = 1;
    nvm_start_epoch_time=epoch_time;
    linux_epoch_start = time(NULL);

#endif
    return sts;
}

/*!
 *  @brief This API gets the current time and date in epoch format
 */
uint64_t get_crnt_time_date_in_epoch(void)
{
    uint64_t epoch_time;
    sys_time_date_s time_date={0};
    struct tm tm_time_date;
    memset(&tm_time_date,0,sizeof(struct tm));
    get_crnt_time_date(&time_date);
    tm_time_date.tm_sec  = time_date.seconds;
    tm_time_date.tm_min  = time_date.minute;
    tm_time_date.tm_hour = time_date.hour;
    tm_time_date.tm_mday = time_date.date;
    tm_time_date.tm_mon  = time_date.month - 1;
    tm_time_date.tm_year = time_date.year - 1900;
    epoch_time=mktime(&tm_time_date);
    return epoch_time;
}


/*!
 *  @brief This API get the time and date from the NVM
 */
void rtc_nvm_reload(void)
{
    uint64_t epoch_time = 0;
    if(epoch_time == 0x0 || epoch_time >= 0xFFFFFFFF)
    {
        struct tm tm_time_date;
        memset(&tm_time_date,0,sizeof(struct tm));

        tm_time_date.tm_hour = RTC_HR;
        tm_time_date.tm_min  = RTC_MIN;
        tm_time_date.tm_sec  = RTC_SEC;
        tm_time_date.tm_mon  = RTC_MON;
        tm_time_date.tm_mday = RTC_DATE;
        tm_time_date.tm_year = RTC_YEAR;

        epoch_time=mktime(&tm_time_date);

    }

    nvm_start_epoch_time = epoch_time;
#ifdef LINUX_TEMP_PORT
    linux_epoch_start = time(NULL);
#endif
}

/*!
 *  @brief This API set the current time and date
 */
void preload_saved_rtc(void)
{
    set_crnt_time_date(nvm_start_epoch_time);
}

/*!
 *  @brief This API set the current time and date in NVM
 */
uint64_t set_crnt_time_date_withnvm(sys_time_date_s *time_date)
{
    struct tm tm_time_date;
    uint64_t epoch_time;
    tm_time_date.tm_year = time_date->year - 1900;
    tm_time_date.tm_mon  = time_date->month -   1;
    tm_time_date.tm_mday = time_date->date       ;
    tm_time_date.tm_hour = time_date->hour       ;
    tm_time_date.tm_min  = time_date->minute     ;
    tm_time_date.tm_sec  = time_date->seconds    ;
    epoch_time=mktime(&tm_time_date);
    set_crnt_time_date(epoch_time);
    return epoch_time;
}

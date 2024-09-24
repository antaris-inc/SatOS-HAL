/**
 * @file exo_io_al_stm32f7xx_rtc.c
 *
 * @brief This file contains wrapper function definition for RTC interface
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


#include "exo_io_al_stm32f7xx_rtc.h"
#include "exo_io_al_sos_timer.h"

#ifndef LINUX_TEMP_PORT
#include "stm32f7xx_hal.h"
#endif

/**
 * @brief Alarm A callback event function
 * @param hrtc - hrtc pointer to a RTC_HandleTypeDef structure that contains
 *             the configuration information for RTC module
 */
void io_hal_stm32f7xx_rtc_alarm_a_event_cb(RTC_HandleTypeDef *hrtc);
/**
 * @brief Alarm B callback event function
 * @param hrtc - hrtc pointer to a RTC_HandleTypeDef structure that contains
 *             the configuration information for RTC module
 */
void io_hal_stm32f7xx_rtc_alarm_b_event_cb(RTC_HandleTypeDef *hrtc);
/**
 * @brief Timestamp callback event function
 * @param hrtc - hrtc pointer to a RTC_HandleTypeDef structure that contains
 *             the configuration information for RTC module
 */
void io_hal_stm32f7xx_rtc_timestamp_event_cb(RTC_HandleTypeDef *hrtc);
/**
 * @brief Wakeup timer callback event function
 * @param hrtc - hrtc pointer to a RTC_HandleTypeDef structure that contains
 *             the configuration information for RTC module
 */
void io_hal_stm32f7xx_rtc_wakeup_timer_event_cb(RTC_HandleTypeDef *hrtc);
/**
 * @brief Tamper 1 callback event function
 * @param hrtc - hrtc pointer to a RTC_HandleTypeDef structure that contains
 *             the configuration information for RTC module
 */
void io_hal_stm32f7xx_rtc_tamper_1_event_cb(RTC_HandleTypeDef *hrtc);
/**
 * @brief Tamper 2 callback event function
 * @param hrtc - hrtc pointer to a RTC_HandleTypeDef structure that contains
 *             the configuration information for RTC module
 */
void io_hal_stm32f7xx_rtc_tamper_2_event_cb(RTC_HandleTypeDef *hrtc);
/**
 * @brief Tamper 3 callback event function
 * @param hrtc - hrtc pointer to a RTC_HandleTypeDef structure that contains
 *             the configuration information for RTC module
 */
void io_hal_stm32f7xx_rtc_tamper_3_event_cb(RTC_HandleTypeDef *hrtc);
/**
 * @brief MSP init callback event function
 * @param hrtc - hrtc pointer to a RTC_HandleTypeDef structure that contains
 *             the configuration information for RTC module
 */
void io_hal_stm32f7xx_rtc_msp_init_cb(RTC_HandleTypeDef *hrtc);
/**
 * @brief MSP deinit callback event function
 * @param hrtc - hrtc pointer to a RTC_HandleTypeDef structure that contains
 *             the configuration information for RTC module
 */
void io_hal_stm32f7xx_rtc_msp_deinit_cb(RTC_HandleTypeDef *hrtc);

RTC_HandleTypeDef hrtc;
HAL_StatusTypeDef rtc_sts = 0;

/**
 * @brief This API configure the RTC parameters
 * @param[in] ioal_hrtc - ioal_hrtc pointer to a ioal_rtc_hdle structure that contains
 * @retval No return
 */
static void MX_RTC_Init(ioal_rtc_hdle *ioal_hrtc);

/**
 * @brief This API initializes the control block memory and do the basic
 *   		configurations RTC
 */
hal_ret_sts io_hal_stm32f7xx_rtc_init(ioal_rtc_hdle *ioal_hrtc)
{
    MX_RTC_Init(ioal_hrtc);
    return HAL_SCS;
}

/**
 * @brief This API configure the RTC parameters
 */
static void MX_RTC_Init(ioal_rtc_hdle *ioal_hrtc)
{

    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        ioal_error_handler();
    }

    ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle = (void*)&hrtc;
    ioal_hrtc->intf_gen_info.state = IO_FREE_STATE;

    if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0X32F2)
    {
        preload_saved_rtc();

        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2);
    }

}

/**
 * @brief This API initializes RTC callback events
 */
hal_ret_sts io_hal_stm32f7xx_rtc_reg_cb(ioal_rtc_hdle *ioal_hrtc,iohal_rtc_callbackidtypedef callbackid)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;

    switch(callbackid)
    {
        case IOHAL_RTC_ALARM_A_EVENT_CB_ID :
            ret_sts = HAL_RTC_RegisterCallback(hrtc, HAL_RTC_ALARM_A_EVENT_CB_ID,io_hal_stm32f7xx_rtc_alarm_a_event_cb);
            break;

        case IOHAL_RTC_ALARM_B_EVENT_CB_ID  :
            ret_sts = HAL_RTC_RegisterCallback(hrtc, HAL_RTC_ALARM_B_EVENT_CB_ID,io_hal_stm32f7xx_rtc_alarm_b_event_cb);
            break;

        case  IOHAL_RTC_TIMESTAMP_EVENT_CB_ID:
            ret_sts = HAL_RTC_RegisterCallback(hrtc, HAL_RTC_TIMESTAMP_EVENT_CB_ID,io_hal_stm32f7xx_rtc_timestamp_event_cb);
            break;

        case  IOHAL_RTC_WAKEUPTIMER_EVENT_CB_ID:
            ret_sts = HAL_RTC_RegisterCallback(hrtc, HAL_RTC_WAKEUPTIMER_EVENT_CB_ID,io_hal_stm32f7xx_rtc_wakeup_timer_event_cb);
            break;


        case IOHAL_RTC_TAMPER1_EVENT_CB_ID :
            ret_sts = HAL_RTC_RegisterCallback(hrtc, HAL_RTC_TAMPER1_EVENT_CB_ID,io_hal_stm32f7xx_rtc_tamper_1_event_cb);
            break;

        case  IOHAL_RTC_TAMPER2_EVENT_CB_ID:
            ret_sts = HAL_RTC_RegisterCallback(hrtc, HAL_RTC_TAMPER2_EVENT_CB_ID,io_hal_stm32f7xx_rtc_tamper_2_event_cb);
            break;

        case  IOHAL_RTC_TAMPER3_EVENT_CB_ID:
            ret_sts = HAL_RTC_RegisterCallback(hrtc, HAL_RTC_TAMPER3_EVENT_CB_ID,io_hal_stm32f7xx_rtc_tamper_3_event_cb);
            break;

        case IOHAL_RTC_MSPINIT_CB_ID  :
            ret_sts = HAL_RTC_RegisterCallback(hrtc, HAL_RTC_MSPINIT_CB_ID ,io_hal_stm32f7xx_rtc_msp_init_cb);
            break;

        case IOHAL_RTC_MSPDEINIT_CB_ID:
            ret_sts = HAL_RTC_RegisterCallback(hrtc, HAL_RTC_MSPDEINIT_CB_ID,io_hal_stm32f7xx_rtc_msp_deinit_cb);
            break;
        default :
            ret_sts =  HAL_IO_INVLD_CB_FN;
            break;
    }

    return ret_sts;
}

/**
 * @brief Alarm A callback event function
 */
void io_hal_stm32f7xx_rtc_alarm_a_event_cb(RTC_HandleTypeDef *hrtc)
{
    ioal_rtc_hdle *ioal_hrtc = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hrtc, (void**)&ioal_hrtc))
    {
        ioal_hrtc->alarm_a_event_cb(ioal_hrtc);
    }
    else
    {
    }
}

/**
 * @brief Alarm B callback event function
 */
void io_hal_stm32f7xx_rtc_alarm_b_event_cb(RTC_HandleTypeDef *hrtc)
{
    ioal_rtc_hdle *ioal_hrtc = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hrtc, (void**)&ioal_hrtc))
    {
        ioal_hrtc->alarm_b_event_cb(ioal_hrtc);
    }
    else
    {
    }
}

/**
 * @brief Timestamp callback event function
 */
void io_hal_stm32f7xx_rtc_timestamp_event_cb(RTC_HandleTypeDef *hrtc)
{
    ioal_rtc_hdle *ioal_hrtc = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hrtc, (void**)&ioal_hrtc))
    {
        ioal_hrtc->timestamp_event_cb(ioal_hrtc);
    }
    else
    {

    }
}

/**
 * @brief Wakeup timer callback event function
 */
void io_hal_stm32f7xx_rtc_wakeup_timer_event_cb(RTC_HandleTypeDef *hrtc)
{
    ioal_rtc_hdle *ioal_hrtc = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hrtc, (void**)&ioal_hrtc))
    {
        ioal_hrtc->wakeup_timer_event_cb(ioal_hrtc);
    }
    else
    {

    }
}

/**
 * @brief Tamper 1 callback event function
 */
void io_hal_stm32f7xx_rtc_tamper_1_event_cb(RTC_HandleTypeDef *hrtc)
{
    ioal_rtc_hdle *ioal_hrtc = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hrtc, (void**)&ioal_hrtc))
    {
        ioal_hrtc->tamper_1_event_cb(ioal_hrtc);
    }
    else
    {

    }
}

/**
 * @brief Tamper 2 callback event function
 */
void io_hal_stm32f7xx_rtc_tamper_2_event_cb(RTC_HandleTypeDef *hrtc)
{
    ioal_rtc_hdle *ioal_hrtc = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hrtc, (void**)&ioal_hrtc))
    {
        ioal_hrtc->tamper_2_event_cb(ioal_hrtc);
    }
    else
    {

    }
}

/**
 * @brief Tamper 3 callback event function
 */
void io_hal_stm32f7xx_rtc_tamper_3_event_cb(RTC_HandleTypeDef *hrtc)
{
    ioal_rtc_hdle *ioal_hrtc = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hrtc, (void**)&ioal_hrtc))
    {
        ioal_hrtc->tamper_3_event_cb(ioal_hrtc);
    }
    else
    {

    }
}

/**
 * @brief MSP init callback event function
 */
void io_hal_stm32f7xx_rtc_msp_init_cb(RTC_HandleTypeDef *hrtc)
{
    ioal_rtc_hdle *ioal_hrtc = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hrtc, (void**)&ioal_hrtc))
    {
        ioal_hrtc->msp_init_cb(ioal_hrtc);
    }
    else
    {

    }
}

/**
 * @brief MSP deinit callback event function
 */
void io_hal_stm32f7xx_rtc_msp_deinit_cb(RTC_HandleTypeDef *hrtc)
{
    ioal_rtc_hdle *ioal_hrtc = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hrtc, (void**)&ioal_hrtc))
    {
        ioal_hrtc->msp_deinit_cb(ioal_hrtc);
    }
    else
    {

    }
}

/**
 * @brief This API unregister the callback event
 */
hal_ret_sts io_hal_stm32f7xx_rtc_unregcallback(ioal_rtc_hdle *ioal_hrtc,iohal_rtc_callbackidtypedef callbackid )
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;

    switch(callbackid)
    {
        case IOHAL_RTC_ALARM_A_EVENT_CB_ID :
            ret_sts = HAL_RTC_UnRegisterCallback(hrtc, HAL_RTC_ALARM_A_EVENT_CB_ID);
            break;

        case IOHAL_RTC_ALARM_B_EVENT_CB_ID  :
            ret_sts = HAL_RTC_UnRegisterCallback(hrtc, HAL_RTC_ALARM_B_EVENT_CB_ID);
            break;

        case  IOHAL_RTC_TIMESTAMP_EVENT_CB_ID:
            ret_sts = HAL_RTC_UnRegisterCallback(hrtc, HAL_RTC_TIMESTAMP_EVENT_CB_ID);
            break;

        case  IOHAL_RTC_WAKEUPTIMER_EVENT_CB_ID:
            ret_sts = HAL_RTC_UnRegisterCallback(hrtc, HAL_RTC_WAKEUPTIMER_EVENT_CB_ID);
            break;

        case IOHAL_RTC_TAMPER1_EVENT_CB_ID :
            ret_sts = HAL_RTC_UnRegisterCallback(hrtc, HAL_RTC_TAMPER1_EVENT_CB_ID);
            break;

        case  IOHAL_RTC_TAMPER2_EVENT_CB_ID:
            ret_sts = HAL_RTC_UnRegisterCallback(hrtc, HAL_RTC_TAMPER2_EVENT_CB_ID);
            break;

        case  IOHAL_RTC_TAMPER3_EVENT_CB_ID:
            ret_sts = HAL_RTC_UnRegisterCallback(hrtc, HAL_RTC_TAMPER3_EVENT_CB_ID);
            break;

        case IOHAL_RTC_MSPINIT_CB_ID  :
            ret_sts = HAL_RTC_UnRegisterCallback(hrtc, HAL_RTC_MSPINIT_CB_ID);
            break;

        case IOHAL_RTC_MSPDEINIT_CB_ID:
            ret_sts = HAL_RTC_UnRegisterCallback(hrtc, HAL_RTC_MSPDEINIT_CB_ID);
            break;
        default :

            ret_sts =  HAL_IO_INVLD_CB_FN;
            break;
    }

    return ret_sts;
}

/**
 * @brief This API set the time in RTC
 */
hal_ret_sts io_hal_stm32f7xx_rtc_set_time(ioal_rtc_hdle *ioal_hrtc,iohal_rtc_timetypedef *stime, uint32 format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;

    if(HAL_OK == HAL_RTC_SetTime(hrtc,(RTC_TimeTypeDef*)stime,format))
    {
        HAL_RTCEx_BKUPWrite(hrtc, RTC_BKP_DR1, 0x32F2);
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API get the time from RTC
 */
hal_ret_sts io_hal_stm32f7xx_rtc_get_time(ioal_rtc_hdle *ioal_hrtc,iohal_rtc_timetypedef *stime, uint32 format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;

    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;

    if(HAL_OK == HAL_RTC_GetTime(hrtc,(RTC_TimeTypeDef*)stime,format))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API set the date in RTC
 */
hal_ret_sts io_hal_stm32f7xx_rtc_set_date(ioal_rtc_hdle *ioal_hrtc, iohal_rtc_datetypedef *sdate ,uint32 format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;

    if(HAL_OK == HAL_RTC_SetDate(hrtc,(RTC_DateTypeDef*)sdate,format))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API get the date from RTC
 */
hal_ret_sts io_hal_stm32f7xx_rtc_get_date(ioal_rtc_hdle *ioal_hrtc, iohal_rtc_datetypedef *sdate, uint32 format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;

    if(HAL_OK == HAL_RTC_GetDate(hrtc,(RTC_DateTypeDef*)sdate,format))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API set the alarm in RTC
 */
hal_ret_sts io_hal_stm32f7xx_rtc_set_alarm(ioal_rtc_hdle *ioal_hrtc, iohal_rtc_alarmtypedef *salarm, uint32 format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;

    if(HAL_OK == HAL_RTC_SetAlarm(hrtc,(RTC_AlarmTypeDef*)salarm,format))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API set the alarm with interrupt mode
 */
hal_ret_sts io_hal_stm32f7xx_rtc_set_alarmit(ioal_rtc_hdle *ioal_hrtc, iohal_rtc_alarmtypedef *salarm, uint32 format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_RTC_SetAlarm_IT(hrtc,(RTC_AlarmTypeDef*)salarm,format))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API deativates the alarm
 */
hal_ret_sts io_hal_stm32f7xx_rtc_deactivate_alarm(ioal_rtc_hdle *ioal_hrtc, uint32 alarm)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_RTC_DeactivateAlarm(hrtc,alarm))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API get the alarm from RTC
 */
hal_ret_sts io_hal_stm32f7xx_rtc_get_alarm(ioal_rtc_hdle *ioal_hrtc, iohal_rtc_alarmtypedef *salarm, uint32_t alarm,uint32 format)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_RTC_GetAlarm(hrtc,(RTC_AlarmTypeDef*)salarm,alarm,format))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API poll the alarm event
 */
hal_ret_sts io_hal_stm32f7xx_rtc_poll_alarmevent(ioal_rtc_hdle *ioal_hrtc, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_RTC_PollForAlarmAEvent(hrtc,timeout))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API configure the resynchronization mode
 */
hal_ret_sts io_hal_stm32f7xx_rtc_wait_synchro(ioal_rtc_hdle *ioal_hrtc)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_RTC_WaitForSynchro(hrtc))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API get the RTC state
 */
hal_ret_sts io_hal_stm32f7xx_rtc_get_state(ioal_rtc_hdle *ioal_hrtc)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_RTC_STATE_READY == HAL_RTC_GetState(hrtc))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API put the RTC to initialization mode
 */
hal_ret_sts io_hal_stm32f7xx_rtc_init_mode(ioal_rtc_hdle *ioal_hrtc)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    RTC_HandleTypeDef *hrtc = ioal_hrtc->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == RTC_EnterInitMode(hrtc))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

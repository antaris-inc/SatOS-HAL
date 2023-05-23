/**
 * @file exo_io_al_stm32f7xx_can.c
 *
 * @brief This file contains wrapper function definition for CAN interface
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

#include "exo_io_al_stm32f7xx_common.h"
#include "exo_io_al_stm32f7xx_can.h"

#ifndef LINUX_TEMP_PORT
#include "stm32f7xx_hal.h"
#endif

static void MX_CAN1_Init(ioal_can_hdle *ioal_hcan1);
static void MX_CAN3_Init(ioal_can_hdle *ioal_hcan3);
static void MX_CAN2_Init(ioal_can_hdle *ioal_hcan2);



/**
 * @brief  Transmission Mailbox 0 complete callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_tx_mb0_cplt_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Transmission Mailbox 1 complete callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_tx_mb1_cplt_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Transmission Mailbox 2 complete callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_tx_mb2_cplt_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Transmission Mailbox 0 Cancellation callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_mb0_abort_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Transmission Mailbox 1 Cancellation callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_mb1_abort_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Transmission Mailbox 2 Cancellation callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_mb2_abort_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Rx FIFO 0 message pending callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_fifo0_msg_pend_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Rx FIFO 0 full callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_fifo0_full_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Rx FIFO 1 message pending callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_fifo1_msg_pend_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Rx FIFO 1 full callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_fifo1_full_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Sleep callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_sleep_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  WakeUp from Rx message callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_wakeup_cb(CAN_HandleTypeDef *hcan);
/**
 * @brief  Error CAN callback function
 * @param[in]  hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void io_hal_stm32f7xx_can_error_cb(CAN_HandleTypeDef *hcan);


CAN_HandleTypeDef hcan1;
CAN_FilterTypeDef can1_filterconfig;

CAN_HandleTypeDef hcan3;
CAN_FilterTypeDef can3_filterconfig;

CAN_HandleTypeDef hcan2;
CAN_FilterTypeDef can2_filterconfig;


/**
 * @brief  This function initializes the CAN1 peripheral according to the specified
 *         parameters
 */
hal_ret_sts io_hal_stm32f7xx_can1_init(ioal_can_hdle *ioal_hcan1)
{
    MX_CAN1_Init(ioal_hcan1);
    return 0;
}

/**
 * @brief  This function initializes the CAN3 peripheral according to the specified
 *         parameters
 */
hal_ret_sts io_hal_stm32f7xx_can3_init(ioal_can_hdle *ioal_hcan3)
{
    MX_CAN3_Init(ioal_hcan3);
    return 0;
}

/**
 * @brief  This function initializes the CAN2 peripheral according to the specified
 *         parameters
 */
hal_ret_sts io_hal_stm32f7xx_can2_init(ioal_can_hdle *ioal_hcan2)
{
    MX_CAN2_Init(ioal_hcan2);
    return 0;
}

/**
 * @brief CAN1 Initialization Function
 */
static void MX_CAN1_Init(ioal_can_hdle *ioal_hcan1)
{

    hcan1.Instance = CAN1;
    hcan1.Init.Prescaler = 10;
    hcan1.Init.Mode = CAN_MODE_NORMAL;
    hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan1.Init.TimeSeg1 = CAN_BS1_2TQ;
    hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
    hcan1.Init.TimeTriggeredMode = DISABLE;
    hcan1.Init.AutoBusOff = DISABLE;
    hcan1.Init.AutoWakeUp = DISABLE;
    hcan1.Init.AutoRetransmission = DISABLE;
    hcan1.Init.ReceiveFifoLocked = DISABLE;
    hcan1.Init.TransmitFifoPriority = DISABLE;
    if (HAL_CAN_Init(&hcan1) != HAL_OK)
    {
        ioal_error_handler();
    }

    can1_filterconfig.FilterActivation = CAN_FILTER_ENABLE;
    can1_filterconfig.FilterBank = 10;
    can1_filterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    can1_filterconfig.FilterIdHigh = 0;
    can1_filterconfig.FilterIdLow = 0;
    can1_filterconfig.FilterMaskIdHigh = 0;
    can1_filterconfig.FilterMaskIdLow = 0;
    can1_filterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
    can1_filterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
    can1_filterconfig.SlaveStartFilterBank = 13;
    HAL_CAN_ConfigFilter(&hcan1, &can1_filterconfig);

    ioal_hcan1->intf_gen_info.vdp_intf_inst_hdle = (void*)&hcan1;
    ioal_hcan1->intf_gen_info.state = IO_FREE_STATE;
}

/**
 * @brief CAN3 Initialization Function
 */
static void MX_CAN3_Init(ioal_can_hdle *ioal_hcan3)
{
    hcan3.Instance = CAN3;
    hcan3.Init.Prescaler = 10;
    hcan3.Init.Mode = CAN_MODE_NORMAL;
    hcan3.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan3.Init.TimeSeg1 = CAN_BS1_2TQ;
    hcan3.Init.TimeSeg2 = CAN_BS2_2TQ;
    hcan3.Init.TimeTriggeredMode = DISABLE;
    hcan3.Init.AutoBusOff = DISABLE;
    hcan3.Init.AutoWakeUp = DISABLE;
    hcan3.Init.AutoRetransmission = DISABLE;
    hcan3.Init.ReceiveFifoLocked = DISABLE;
    hcan3.Init.TransmitFifoPriority = DISABLE;
    if (HAL_CAN_Init(&hcan3) != HAL_OK)
    {
        ioal_error_handler();
    }
    can3_filterconfig.FilterActivation = CAN_FILTER_ENABLE;
    can3_filterconfig.FilterBank = 10;
    can3_filterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    can3_filterconfig.FilterIdHigh = 0;
    can3_filterconfig.FilterIdLow = 0;
    can3_filterconfig.FilterMaskIdHigh = 0;
    can3_filterconfig.FilterMaskIdLow = 0;
    can3_filterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
    can3_filterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
    can3_filterconfig.SlaveStartFilterBank = 13;
    HAL_CAN_ConfigFilter(&hcan3, &can3_filterconfig);
    ioal_hcan3->intf_gen_info.vdp_intf_inst_hdle = (void*)&hcan3;
    ioal_hcan3->intf_gen_info.state = IO_FREE_STATE;

}

/**
 * @brief CAN2 Initialization Function
 */
static void MX_CAN2_Init(ioal_can_hdle *ioal_hcan2)
{
    hcan2.Instance = CAN2;
    hcan2.Init.Prescaler = 10;
    hcan2.Init.Mode = CAN_MODE_NORMAL;
    hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan2.Init.TimeSeg1 = CAN_BS1_2TQ;
    hcan2.Init.TimeSeg2 = CAN_BS2_2TQ;
    hcan2.Init.TimeTriggeredMode = DISABLE;
    hcan2.Init.AutoBusOff = DISABLE;
    hcan2.Init.AutoWakeUp = DISABLE;
    hcan2.Init.AutoRetransmission = DISABLE;
    hcan2.Init.ReceiveFifoLocked = DISABLE;
    hcan2.Init.TransmitFifoPriority = DISABLE;
    if (HAL_CAN_Init(&hcan2) != HAL_OK)
    {
        ioal_error_handler();
    }
    can2_filterconfig.FilterActivation = CAN_FILTER_ENABLE;
    can2_filterconfig.FilterBank = 10;
    can2_filterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    can2_filterconfig.FilterIdHigh = 0;
    can2_filterconfig.FilterIdLow = 0;
    can2_filterconfig.FilterMaskIdHigh = 0;
    can2_filterconfig.FilterMaskIdLow = 0;
    can2_filterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
    can2_filterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
    can2_filterconfig.SlaveStartFilterBank = 0;
    HAL_CAN_ConfigFilter(&hcan2, &can2_filterconfig);
    ioal_hcan2->intf_gen_info.vdp_intf_inst_hdle = (void*)&hcan2;
    ioal_hcan2->intf_gen_info.state = IO_FREE_STATE;

}

/**
 * @brief This function starts the CAN interface.
 */
hal_ret_sts io_hal_stm32f7xx_can_start(ioal_can_hdle *ioal_hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_CAN_Start(hcan))
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
 * @brief  This function stops the CAN interface
 */
hal_ret_sts io_hal_stm32f7xx_can_stop(ioal_can_hdle *ioal_hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_CAN_Stop(hcan))
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
 * @brief  This function request the sleep mode
 */
hal_ret_sts io_hal_stm32f7xx_can_request_sleep(ioal_can_hdle *ioal_hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_CAN_RequestSleep(hcan))
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
 * @brief  This function wake up from sleep mode.
 */
hal_ret_sts io_hal_stm32f7xx_can_wakeup(ioal_can_hdle *ioal_hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_CAN_WakeUp(hcan))
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
 * @brief   This function check the sleep state of CAN interface
 */
hal_ret_sts io_hal_stm32f7xx_can_is_sleep_active(ioal_can_hdle *ioal_hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_CAN_IsSleepActive(hcan))
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
 * @brief  This function register the CAN CallBack ID
 */
hal_ret_sts io_hal_stm32f7xx_can_reg_cb(ioal_can_hdle *ioal_hcan, iohal_stm32_can_cbid cbid)
{
    hal_ret_sts sts = HAL_SCS;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;

    switch (cbid)
    {
        case IOHAL_STM32_CAN_TX_MB0_CPLT_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_TX_MAILBOX0_COMPLETE_CB_ID,io_hal_stm32f7xx_can_tx_mb0_cplt_cb);
            break;

        case IOHAL_STM32_CAN_TX_MB1_CPLT_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_TX_MAILBOX1_COMPLETE_CB_ID,io_hal_stm32f7xx_can_tx_mb1_cplt_cb);
            break;

        case IOHAL_STM32_CAN_TX_MB2_CPLT_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_TX_MAILBOX2_COMPLETE_CB_ID,io_hal_stm32f7xx_can_tx_mb2_cplt_cb);
            break;

        case IOHAL_STM32_CAN_MB0_ABORT_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_TX_MAILBOX0_ABORT_CB_ID,io_hal_stm32f7xx_can_mb0_abort_cb);
            break;

        case IOHAL_STM32_CAN_MB1_ABORT_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_TX_MAILBOX1_ABORT_CB_ID,io_hal_stm32f7xx_can_mb1_abort_cb);
            break;

        case IOHAL_STM32_CAN_MB2_ABORT_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_TX_MAILBOX2_ABORT_CB_ID,io_hal_stm32f7xx_can_mb2_abort_cb);
            break;

        case IOHAL_STM32_CAN_FIFO0_MSG_PEND_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_RX_FIFO0_MSG_PENDING_CB_ID,io_hal_stm32f7xx_can_fifo0_msg_pend_cb);
            break;

        case IOHAL_STM32_CAN_FIFO0_FULL_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_RX_FIFO0_FULL_CB_ID,io_hal_stm32f7xx_can_fifo0_full_cb);
            break;

        case IOHAL_STM32_CAN_FIFO1_MSG_PEND_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_RX_FIFO1_MSG_PENDING_CB_ID,io_hal_stm32f7xx_can_fifo1_msg_pend_cb);
            break;

        case IOHAL_STM32_CAN_FIFO1_FULL_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_RX_FIFO1_FULL_CB_ID,io_hal_stm32f7xx_can_fifo1_full_cb);
            break;

        case IOHAL_STM32_CAN_SLEEP_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_SLEEP_CB_ID,io_hal_stm32f7xx_can_sleep_cb);
            break;

        case IOHAL_STM32_CAN_WAKEUP_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_WAKEUP_FROM_RX_MSG_CB_ID,io_hal_stm32f7xx_can_wakeup_cb);
            break;

        case IOHAL_STM32_CAN_ERROR_CB_ID :
            sts = HAL_CAN_RegisterCallback(hcan, HAL_CAN_ERROR_CB_ID,io_hal_stm32f7xx_can_error_cb);
            break;

        default :

            sts =  HAL_IO_INVLD_CB_FN;
            break;
    }
    return sts;
}

/**
 * @brief  Transmission Mailbox 0 complete callback function
 */
void io_hal_stm32f7xx_can_tx_mb0_cplt_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_tx_mb0_cplt_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief  Transmission Mailbox 1 complete callback function
 */
void io_hal_stm32f7xx_can_tx_mb1_cplt_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_tx_mb1_cplt_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief  Transmission Mailbox 2 complete callback function
 */
void io_hal_stm32f7xx_can_tx_mb2_cplt_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_tx_mb2_cplt_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief  Transmission Mailbox 0 Cancellation callback function
 */
void io_hal_stm32f7xx_can_mb0_abort_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_mb0_abort_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief  Transmission Mailbox 1 Cancellation callback function
 */
void io_hal_stm32f7xx_can_mb1_abort_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_mb1_abort_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief  Transmission Mailbox 2 Cancellation callback function
 */
void io_hal_stm32f7xx_can_mb2_abort_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_mb2_abort_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief  Rx FIFO 0 message pending callback function
 */
void io_hal_stm32f7xx_can_fifo0_msg_pend_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_fifo0_msg_pend_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief Rx FIFO 0 full callback function
 */
void io_hal_stm32f7xx_can_fifo0_full_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_fifo0_full_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief  Rx FIFO 1 message pending callback function
 */
void io_hal_stm32f7xx_can_fifo1_msg_pend_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_fifo1_msg_pend_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief  Rx FIFO 1 full callback function
 */
void io_hal_stm32f7xx_can_fifo1_full_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_fifo1_full_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief  Sleep callback function
 */
void io_hal_stm32f7xx_can_sleep_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_sleep_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief WakeUp from Rx message callback function
 */
void io_hal_stm32f7xx_can_wakeup_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_wakeup_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief Error CAN callback function
 */
void io_hal_stm32f7xx_can_error_cb(CAN_HandleTypeDef *hcan)
{
    ioal_can_hdle *ioal_hcan = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hcan, (void**)&ioal_hcan))
    {
        ioal_hcan->can_error_cb(ioal_hcan);
    }
    else
    {

    }
}

/**
 * @brief This function add a message to the first free Tx mailbox and activate the
 *         corresponding transmission request.
 */
hal_ret_sts io_hal_stm32f7xx_add_tx_message(ioal_can_hdle *ioal_hcan, iohal_can_tx_header *p_header, uint8_t adata[], uint32_t *ptxmailbox)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = (CAN_HandleTypeDef*)ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;

    CAN_TxHeaderTypeDef tx_header;
    tx_header.DLC=p_header->DLC;
    tx_header.ExtId=p_header->ExtId;
    tx_header.IDE=p_header->IDE;
    tx_header.RTR=p_header->RTR;
    tx_header.StdId=p_header->StdId;
    tx_header.TransmitGlobalTime=p_header->TransmitGlobalTime;

    if(HAL_OK ==HAL_CAN_AddTxMessage(hcan,&tx_header,adata,ptxmailbox))
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
 * @brief This function abort transmission requests
 */
hal_ret_sts io_hal_stm32f7xx_abort_tx_request(ioal_can_hdle *ioal_hcan, uint32_t txmailboxes)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK ==HAL_CAN_AbortTxRequest(hcan,txmailboxes))
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
 * @brief  This function returns the number of free Tx Mailboxes.
 */
uint32_t io_hal_stm32f7xx_get_tx_mailboxes_free_level(ioal_can_hdle *ioal_hcan)
{
    uint32_t free_lvl;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    free_lvl = HAL_CAN_GetTxMailboxesFreeLevel(hcan);
    return free_lvl;
}

/**
 * @brief  This function check if a transmission request is pending on Tx side
 */
uint32_t io_hal_stm32f7xx_is_tx_message_pending(ioal_can_hdle *ioal_hcan, uint32_t txmailboxes)
{
    uint32_t ret_sts;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    ret_sts=HAL_CAN_IsTxMessagePending(hcan,txmailboxes);
    return ret_sts;
}

/**
 * @brief This function get timestamp of Tx message sent
 */
uint32_t io_hal_stm32f7xx_get_tx_time_stamp(ioal_can_hdle *ioal_hcan, uint32_t txmailbox)
{
    uint32_t ret_sts;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    ret_sts=HAL_CAN_GetTxTimestamp(hcan,txmailbox);
    return ret_sts;
}

/**
 * @brief This function gets CAN frame from the Rx FIFO
 */
hal_ret_sts io_hal_stm32f7xx_get_rx_message(ioal_can_hdle *ioal_hcan, uint32_t rxfifo, iohal_can_rx_header *p_header, uint8_t adata[])
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    CAN_RxHeaderTypeDef rx_header;
    if(HAL_OK == HAL_CAN_GetRxMessage(hcan,rxfifo,&rx_header,adata))
    {
        p_header->DLC=rx_header.DLC;
        p_header->ExtId=rx_header.ExtId;
        p_header->IDE=rx_header.IDE;
        p_header->RTR=rx_header.RTR;
        p_header->StdId=rx_header.StdId;
        p_header->Timestamp=rx_header.Timestamp;
        p_header->FilterMatchIndex=rx_header.FilterMatchIndex;
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This function get Rx FIFO fill level.
 */
uint32_t io_hal_stm32f7xx_get_rx_fifo_fill_level(ioal_can_hdle *ioal_hcan, uint32_t rxfifo)
{
    uint32_t ret_sts;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    ret_sts=HAL_CAN_GetRxFifoFillLevel(hcan,rxfifo);
    return ret_sts;
}

/**
 * @brief  This function configures the CAN reception filter
 */
hal_ret_sts io_hal_stm32f7xx_can_configfilter(ioal_can_hdle *ioal_hcan, iohal_can_filter *sFilterConfig)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;

    if(HAL_OK == HAL_CAN_ConfigFilter(hcan,(void*)sFilterConfig))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/* Interrupts management ******************************************************/
/**
 * @brief This function activate notifications
 */
hal_ret_sts io_hal_stm32f7xx_can_activate_notification(ioal_can_hdle *ioal_hcan, uint32_t active_its)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_CAN_ActivateNotification(hcan,active_its))
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
 * @brief   This function deactivate notifications
 */
hal_ret_sts io_hal_stm32f7xx_can_deactivate_notification(ioal_can_hdle *ioal_hcan, uint32_t inactive_its)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK ==HAL_CAN_DeactivateNotification(hcan,inactive_its))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/* Peripheral State and Error functions ***************************************/
/**
 *@brief  This function get the CAN state.
 */
iohal_can_state io_hal_stm32f7xx_can_get_state(ioal_can_hdle *ioal_hcan)
{

    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    return ((iohal_can_state)HAL_CAN_GetState(hcan));
}

/**
 *@brief  This function get the CAN error code.
 */
hal_ret_sts io_hal_stm32f7xx_can_get_error(ioal_can_hdle *ioal_hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_CAN_GetError(hcan))
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
 *@brief  This function reset the CAN error code.
 */
hal_ret_sts io_hal_stm32f7xx_can_reset_error(ioal_can_hdle *ioal_hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    CAN_HandleTypeDef *hcan = ioal_hcan->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK ==  HAL_CAN_ResetError(hcan))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

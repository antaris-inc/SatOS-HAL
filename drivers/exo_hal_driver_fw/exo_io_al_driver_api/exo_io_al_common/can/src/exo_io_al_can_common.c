/**
 * @file exo_io_al_can_common.c
 *
 * @brief This file contains abstracted function definition for CAN interface
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

#include <stdio.h>
#include <unistd.h>
#include "exo_io_al_can_common.h"
#include "exo_hal_io_al_common.h"
#include "exo_osal.h"
#ifndef LINUX_TEMP_PORT
#include "exo_io_al_stm32f7xx_can.h"
#else
#include "exo_io_al_linux_can.h"
#endif


#ifndef LINUX_TEMP_PORT

#define CAN1_TX_MB0_CPLT_CB     check_can1_dummy    ///< TX MB0 complete callback event
#define CAN1_TX_MB1_CPLT_CB     check_can1_dummy    ///< TX MB1 callback event
#define CAN1_TX_MB2_CPLT_CB     check_can1_dummy    ///< TX MB2 complete callback event
#define CAN1_MB0_ABORT_CB       check_can1_dummy    ///< MB0 abort callback event
#define CAN1_MB1_ABORT_CB       check_can1_dummy    ///< MB1 abort callback event
#define CAN1_MB2_ABORT_CB       check_can1_dummy    ///< MB2 abort callback event
#define CAN1_FIFO0_MSG_PEND_CB  check_can1_dummy    ///< FIFO 0 message pending callback event
#define CAN1_FIFO0_FULL_CB      check_can1_dummy    ///< FIFO 0 message full callback event
#define CAN1_FIFO1_MSG_PEND_CB  check_can1_dummy    ///< FIFO 1 message pending callback event
#define CAN1_FIFO1_FULL_CB      check_can1_dummy    ///< FIFO 1 message full callback event
#define CAN1_SLEEP_CB           check_can1_dummy    ///< sleep callback event
#define CAN1_WAKEUP_CB          check_can1_dummy    ///< wakeup callback event
#define CAN1_ERROR_CB           check_can1_dummy    ///< error callback event

#define CAN3_TX_MB0_CPLT_CB     check_can3_dummy    ///< TX MB0 complete callback event
#define CAN3_TX_MB1_CPLT_CB     check_can3_dummy    ///< TX MB1 callback event
#define CAN3_TX_MB2_CPLT_CB     check_can3_dummy    ///< TX MB2 complete callback event
#define CAN3_MB0_ABORT_CB       check_can3_dummy    ///< MB0 abort callback event
#define CAN3_MB1_ABORT_CB       check_can3_dummy    ///< MB1 abort callback event
#define CAN3_MB2_ABORT_CB       check_can3_dummy    ///< MB2 abort callback event
#define CAN3_FIFO0_MSG_PEND_CB  check_can3_dummy    ///< FIFO 0 message pending callback event
#define CAN3_FIFO0_FULL_CB      check_can3_dummy    ///< FIFO 0 message full callback event
#define CAN3_FIFO1_MSG_PEND_CB  check_can3_dummy    ///< FIFO 1 message pending callback event
#define CAN3_FIFO1_FULL_CB      check_can3_dummy    ///< FIFO 1 message full callback event
#define CAN3_SLEEP_CB           check_can3_dummy    ///< sleep callback event
#define CAN3_WAKEUP_CB          check_can3_dummy    ///< wakeup callback event
#define CAN3_ERROR_CB           check_can3_dummy    ///< error callback event

#define CAN2_TX_MB0_CPLT_CB     check_can2_dummy    ///< TX MB0 complete callback event
#define CAN2_TX_MB1_CPLT_CB     check_can2_dummy    ///< TX MB1 callback event
#define CAN2_TX_MB2_CPLT_CB     check_can2_dummy    ///< TX MB2 complete callback event
#define CAN2_MB0_ABORT_CB       check_can2_dummy    ///< MB0 abort callback event
#define CAN2_MB1_ABORT_CB       check_can2_dummy    ///< MB1 abort callback event
#define CAN2_MB2_ABORT_CB       check_can2_dummy    ///< MB2 abort callback event
#define CAN2_FIFO0_MSG_PEND_CB  check_can2_dummy    ///< FIFO 0 message pending callback event
#define CAN2_FIFO0_FULL_CB      check_can2_dummy    ///< FIFO 0 message full callback event
#define CAN2_FIFO1_MSG_PEND_CB  check_can2_dummy    ///< FIFO 1 message pending callback event
#define CAN2_FIFO1_FULL_CB      check_can2_dummy    ///< FIFO 1 message full callback event
#define CAN2_SLEEP_CB           check_can2_dummy    ///< sleep callback event
#define CAN2_WAKEUP_CB          check_can2_dummy    ///< wakeup callback event
#define CAN2_ERROR_CB           check_can2_dummy    ///< error callback event

#else

#define CAN1_TX_MB0_CPLT_CB     linux_can_dummy_fn  ///< CAN1 TX MB0 complete callback event
#define CAN1_TX_MB1_CPLT_CB     linux_can_dummy_fn  ///< CAN1 TX MB1 callback event
#define CAN1_TX_MB2_CPLT_CB     linux_can_dummy_fn  ///< CAN1 TX MB2 complete callback event
#define CAN1_MB0_ABORT_CB       linux_can_dummy_fn  ///< CAN1 MB0 abort callback event
#define CAN1_MB1_ABORT_CB       linux_can_dummy_fn  ///< CAN1 MB1 abort callback event
#define CAN1_MB2_ABORT_CB       linux_can_dummy_fn  ///< CAN1 MB2 abort callback event
#define CAN1_FIFO0_MSG_PEND_CB  linux_can_dummy_fn  ///< CAN1 FIFO 0 message pending callback event
#define CAN1_FIFO0_FULL_CB      linux_can_dummy_fn  ///< CAN1 FIFO 0 message full callback event
#define CAN1_FIFO1_MSG_PEND_CB  linux_can_dummy_fn  ///< CAN1 FIFO 1 message pending callback event
#define CAN1_FIFO1_FULL_CB      linux_can_dummy_fn  ///< CAN1 FIFO 1 message full callback event
#define CAN1_SLEEP_CB           linux_can_dummy_fn  ///< CAN1 sleep callback event
#define CAN1_WAKEUP_CB          linux_can_dummy_fn  ///< CAN1 wakeup callback event
#define CAN1_ERROR_CB           linux_can_dummy_fn  ///< CAN1 error callback event

#define CAN3_TX_MB0_CPLT_CB     linux_can_dummy_fn  ///< CAN3 TX MB0 complete callback event
#define CAN3_TX_MB1_CPLT_CB     linux_can_dummy_fn  ///< CAN3 TX MB1 callback event
#define CAN3_TX_MB2_CPLT_CB     linux_can_dummy_fn  ///< CAN3 TX MB2 complete callback event
#define CAN3_MB0_ABORT_CB       linux_can_dummy_fn  ///< CAN3 MB0 abort callback event
#define CAN3_MB1_ABORT_CB       linux_can_dummy_fn  ///< CAN3 MB1 abort callback event
#define CAN3_MB2_ABORT_CB       linux_can_dummy_fn  ///< CAN3 MB2 abort callback event
#define CAN3_FIFO0_MSG_PEND_CB  linux_can_dummy_fn  ///< CAN3 FIFO 0 message pending callback event
#define CAN3_FIFO0_FULL_CB      linux_can_dummy_fn  ///< CAN3 FIFO 0 message full callback event
#define CAN3_FIFO1_MSG_PEND_CB  linux_can_dummy_fn  ///< CAN3 FIFO 1 message pending callback event
#define CAN3_FIFO1_FULL_CB      linux_can_dummy_fn  ///< CAN3 FIFO 1 message full callback event
#define CAN3_SLEEP_CB           linux_can_dummy_fn  ///< CAN3 sleep callback event
#define CAN3_WAKEUP_CB          linux_can_dummy_fn  ///< CAN3 wakeup callback event
#define CAN3_ERROR_CB           linux_can_dummy_fn  ///< CAN3 error callback event

#define CAN2_TX_MB0_CPLT_CB     linux_can_dummy_fn  ///< CAN2 TX MB0 complete callback event
#define CAN2_TX_MB1_CPLT_CB     linux_can_dummy_fn  ///< CAN2 TX MB1 callback event
#define CAN2_TX_MB2_CPLT_CB     linux_can_dummy_fn  ///< CAN2 TX MB2 complete callback event
#define CAN2_MB0_ABORT_CB       linux_can_dummy_fn  ///< CAN2 MB0 abort callback event
#define CAN2_MB1_ABORT_CB       linux_can_dummy_fn  ///< CAN2 MB1 abort callback event
#define CAN2_MB2_ABORT_CB       linux_can_dummy_fn  ///< CAN2 MB2 abort callback event
#define CAN2_FIFO0_MSG_PEND_CB  linux_can_dummy_fn  ///< CAN2 FIFO 0 message pending callback event
#define CAN2_FIFO0_FULL_CB      linux_can_dummy_fn  ///< CAN2 FIFO 0 message full callback event
#define CAN2_FIFO1_MSG_PEND_CB  linux_can_dummy_fn  ///< CAN2 FIFO 1 message pending callback event
#define CAN2_FIFO1_FULL_CB      linux_can_dummy_fn  ///< CAN2 FIFO 1 message full callback event
#define CAN2_SLEEP_CB           linux_can_dummy_fn  ///< CAN2 sleep callback event
#define CAN2_WAKEUP_CB          linux_can_dummy_fn  ///< CAN2 wakeup callback event
#define CAN2_ERROR_CB           linux_can_dummy_fn  ///< CAN2 error callback event

#endif

extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];
ioal_can_hdle ioal_hcan1;
ioal_can_hdle ioal_hcan3;
ioal_can_hdle ioal_hcan2;

os_sem_handle_ptr can_tx;
/**
 * @brief  This API initializes the CAN according to default
 *         parameters.
 */
hal_ret_sts io_hal_can_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO CAN IO AL Framework Initialise");
    usleep(100000);
#endif
    hal_ret_sts sts;

    os_sem_create_bin(&can_tx);
    os_sem_give(can_tx);
#ifdef COREBOARD
    if(HAL_SCS == io_hal_common_can2_init(&ioal_hcan2))
    {
        intf_inst_hdle_ptr[IOAL_INST_CAN2] = &ioal_hcan2;

    }
    else
    {
        sts = HAL_IO_INIT_ERR;
    }
#else
    if(HAL_SCS == io_hal_common_can3_init(&ioal_hcan3))
    {
        intf_inst_hdle_ptr[IOAL_INST_CAN3] = &ioal_hcan3;

    }
    else
    {
        sts = HAL_IO_INIT_ERR;
    }
#endif

#ifdef LINUX_TEMP_PORT
    printf("\n EXO CAN IO AL Framework Initialisation completed successfully");
#endif
    return sts;
}

/**
 * @brief  This API initializes callback event for CAN1
 */
void io_hal_can1_cb_init(ioal_can_hdle *hcan1)
{
    hcan1->can_tx_mb0_cplt_cb =  CAN1_TX_MB0_CPLT_CB;
    hcan1->can_tx_mb1_cplt_cb =  CAN1_TX_MB1_CPLT_CB;
    hcan1->can_tx_mb2_cplt_cb =  CAN1_TX_MB2_CPLT_CB;
    hcan1->can_mb0_abort_cb =  CAN1_MB0_ABORT_CB;
    hcan1->can_mb1_abort_cb =  CAN1_MB1_ABORT_CB;
    hcan1->can_mb2_abort_cb =  CAN1_MB2_ABORT_CB;
    hcan1->can_fifo0_msg_pend_cb =  CAN1_FIFO0_MSG_PEND_CB;
    hcan1->can_fifo0_full_cb =  CAN1_FIFO0_FULL_CB;
    hcan1->can_fifo1_msg_pend_cb =  CAN1_FIFO1_MSG_PEND_CB;
    hcan1->can_fifo1_full_cb =  CAN1_FIFO1_FULL_CB;
    hcan1->can_sleep_cb =  CAN1_SLEEP_CB;
    hcan1->can_wakeup_cb =  CAN1_WAKEUP_CB;
    hcan1->can_error_cb =  CAN1_ERROR_CB;

#ifndef LINUX_TEMP_PORT
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_TX_MB0_CPLT_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_TX_MB1_CPLT_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_TX_MB2_CPLT_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_MB0_ABORT_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_MB1_ABORT_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_MB2_ABORT_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_FIFO0_MSG_PEND_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_FIFO0_FULL_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_FIFO1_MSG_PEND_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_FIFO1_FULL_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_SLEEP_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_WAKEUP_CB_ID);
    io_hal_common_can_reg_cb(hcan1, IOHAL_STM32_CAN_ERROR_CB_ID);
#endif
}

/**
 * @brief  This API initializes callback event for CAN3
 */
void io_hal_can3_cb_init(ioal_can_hdle *hcan3)
{
    hcan3->can_tx_mb0_cplt_cb =  CAN3_TX_MB0_CPLT_CB;
    hcan3->can_tx_mb1_cplt_cb =  CAN3_TX_MB1_CPLT_CB;
    hcan3->can_tx_mb2_cplt_cb =  CAN3_TX_MB2_CPLT_CB;
    hcan3->can_mb0_abort_cb =  CAN3_MB0_ABORT_CB;
    hcan3->can_mb1_abort_cb =  CAN3_MB1_ABORT_CB;
    hcan3->can_mb2_abort_cb =  CAN3_MB2_ABORT_CB;
    hcan3->can_fifo0_msg_pend_cb =  CAN3_FIFO0_MSG_PEND_CB;
    hcan3->can_fifo0_full_cb =  CAN3_FIFO0_FULL_CB;
    hcan3->can_fifo1_msg_pend_cb =  CAN3_FIFO1_MSG_PEND_CB;
    hcan3->can_fifo1_full_cb =  CAN3_FIFO1_FULL_CB;
    hcan3->can_sleep_cb =  CAN3_SLEEP_CB;
    hcan3->can_wakeup_cb =  CAN3_WAKEUP_CB;
    hcan3->can_error_cb =  CAN3_ERROR_CB;
#ifndef LINUX_TEMP_PORT
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_TX_MB0_CPLT_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_TX_MB1_CPLT_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_TX_MB2_CPLT_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_MB0_ABORT_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_MB1_ABORT_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_MB2_ABORT_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_FIFO0_MSG_PEND_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_FIFO0_FULL_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_FIFO1_MSG_PEND_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_FIFO1_FULL_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_SLEEP_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_WAKEUP_CB_ID);
    io_hal_common_can_reg_cb(hcan3, IOHAL_STM32_CAN_ERROR_CB_ID);
#endif
}

/**
 * @brief  This API initializes callback event for CAN2
 */
void io_hal_can2_cb_init(ioal_can_hdle *hcan2)
{
    hcan2->can_tx_mb0_cplt_cb =  CAN2_TX_MB0_CPLT_CB;
    hcan2->can_tx_mb1_cplt_cb =  CAN2_TX_MB1_CPLT_CB;
    hcan2->can_tx_mb2_cplt_cb =  CAN2_TX_MB2_CPLT_CB;
    hcan2->can_mb0_abort_cb =  CAN2_MB0_ABORT_CB;
    hcan2->can_mb1_abort_cb =  CAN2_MB1_ABORT_CB;
    hcan2->can_mb2_abort_cb =  CAN2_MB2_ABORT_CB;
    hcan2->can_fifo0_msg_pend_cb =  CAN2_FIFO0_MSG_PEND_CB;
    hcan2->can_fifo0_full_cb =  CAN2_FIFO0_FULL_CB;
    hcan2->can_fifo1_msg_pend_cb =  CAN2_FIFO1_MSG_PEND_CB;
    hcan2->can_fifo1_full_cb =  CAN2_FIFO1_FULL_CB;
    hcan2->can_sleep_cb =  CAN2_SLEEP_CB;
    hcan2->can_wakeup_cb =  CAN2_WAKEUP_CB;
    hcan2->can_error_cb =  CAN2_ERROR_CB;
#ifndef LINUX_TEMP_PORT
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_TX_MB0_CPLT_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_TX_MB1_CPLT_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_TX_MB2_CPLT_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_MB0_ABORT_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_MB1_ABORT_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_MB2_ABORT_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_FIFO0_MSG_PEND_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_FIFO0_FULL_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_FIFO1_MSG_PEND_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_FIFO1_FULL_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_SLEEP_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_WAKEUP_CB_ID);
    io_hal_common_can_reg_cb(hcan2, IOHAL_STM32_CAN_ERROR_CB_ID);
#endif
}

/**
 * @brief  This API starts the CAN interface
 */
hal_ret_sts io_hal_can_start(ioal_can_hdle *hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_can_start(hcan))
    {
        ret_sts = HAL_SCS;

        hcan->intf_gen_info.state = IO_BUSY_STATE;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API stops the CAN interface
 */
hal_ret_sts io_hal_can_stop(ioal_can_hdle *hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_can_start(hcan))
    {
        ret_sts = HAL_SCS;

        hcan->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief  This API request CAN interface to sleep state
 */
hal_ret_sts io_hal_can_request_sleep(ioal_can_hdle *hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_can_request_sleep(hcan))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API wake up from sleep mode
 */
hal_ret_sts io_hal_can_wakeup(ioal_can_hdle *hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_can_wakeup(hcan))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API checks the sleep state of CAN interface
 */
uint32_t io_hal_can_is_sleep_active(ioal_can_hdle *hcan)
{
    uint32_t ret_sts;
    ret_sts=io_hal_common_can_is_sleep_active(hcan);

    return ret_sts;
}

/**
 * @brief  This API add a message to the first free Tx mailbox and activate the
 *         corresponding transmission request.
 */
hal_ret_sts io_hal_can_add_tx_message(ioal_can_hdle *hcan,iohal_can_tx_header *pheader, uint8_t adata[], uint32_t *ptxmailbox)
{
    os_sem_take(can_tx,os_wait_forever);
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS ==io_hal_common_add_tx_message(hcan,pheader,adata,ptxmailbox))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    os_sem_give(can_tx);
    return ret_sts;
}

/**
 * @brief  This API abort transmission requests
 */
hal_ret_sts io_hal_can_abort_tx_request(ioal_can_hdle *hcan, uint32_t txmailboxes)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS ==io_hal_common_abort_tx_request(hcan,txmailboxes))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API returns the number of free Tx Mailboxes.
 */
uint32_t io_hal_can_get_tx_mailboxes_free_level(ioal_can_hdle *hcan)
{

    uint32_t free_lvl=io_hal_common_get_tx_mailboxes_free_level(hcan);
    return free_lvl;
}

/**
 * @brief  This API check if a transmission request is pending on TX side
 */
uint32_t io_hal_can_is_tx_message_pending(ioal_can_hdle *hcan, uint32_t txmailboxes)
{
    uint32_t ret_sts;
    ret_sts=io_hal_common_is_tx_message_pending(hcan,txmailboxes);
    return ret_sts;
}

/**
 * @brief  This API return timestamp of Tx message sent
 */
uint32_t io_hal_can_get_tx_time_stamp(ioal_can_hdle *hcan, uint32_t txmailbox)
{
    uint32_t ret_sts;
    ret_sts=io_hal_common_get_tx_time_stamp(hcan,txmailbox);
    return ret_sts;
}

/**
 * @brief This API get an CAN frame from the Rx FIFO
 */
hal_ret_sts io_hal_can_get_rx_message(ioal_can_hdle *hcan, uint32_t rxfifo,iohal_can_rx_header *pheader, uint8_t adata[])
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS ==io_hal_common_get_rx_message(hcan,rxfifo,pheader,adata))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API return Rx FIFO fill level.
 */
uint32_t io_hal_can_get_rx_fifo_fill_level(ioal_can_hdle *hcan, uint32_t rxfifo)
{
    uint32_t ret_sts;
    ret_sts= io_hal_common_get_rx_fifo_fill_level (hcan,rxfifo);
    return ret_sts;
}

/**
 * @brief  This API configures the CAN reception filter
 */
hal_ret_sts io_hal_can_configfilter(ioal_can_hdle *hcan, iohal_can_filter *sfilterconfig)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_can_configfilter(hcan,sfilterconfig))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API activate notifications
 */
hal_ret_sts io_hal_can_activate_notification(ioal_can_hdle *hcan, uint32_t active_its)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_can_activate_notification(hcan,active_its))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API deactivate notifications
 */
hal_ret_sts io_hal_can_deactivate_notification(ioal_can_hdle *hcan, uint32_t inactive_its)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS ==io_hal_common_can_deactivate_notification(hcan,inactive_its))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 *@brief  This API get the CAN state.
 */
iohal_can_state io_hal_can_get_state(ioal_can_hdle *hcan)
{
    return ((iohal_can_state)io_hal_common_can_get_state(hcan));
}

/**
 *@brief  This API get the CAN error code.
 */
hal_ret_sts io_hal_can_get_error(ioal_can_hdle *hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS ==io_hal_common_can_get_error(hcan))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 *@brief  This API reset the CAN error code.
 */
hal_ret_sts io_hal_can_reset_error(ioal_can_hdle *hcan)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS ==io_hal_common_can_reset_error(hcan))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

#endif


#ifdef LINUX_TEMP_PORT
/**
 * @brief This is CAN interface dummy function for linux
 */
void linux_can_dummy_fn(struct _ioal_can_hdle *hcan)
{
}

#else

/**
 * @brief CAN1 temporary dummy function
 */
void check_can1_dummy(ioal_can_hdle *hcan)
{

}
/**
 * @brief CAN2 temporary dummy function
 */
void check_can2_dummy(ioal_can_hdle *hcan)
{

}

#endif

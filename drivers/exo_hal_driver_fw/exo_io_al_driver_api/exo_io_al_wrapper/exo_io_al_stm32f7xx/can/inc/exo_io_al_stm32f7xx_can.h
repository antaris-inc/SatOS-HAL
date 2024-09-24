/**
 * @file exo_io_al_stm32f7xx_can.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for CAN interface
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

#ifndef _IO_AL_STM32F7XX_CAN_H_
#define _IO_AL_STM32F7XX_CAN_H_

#include "exo_types.h"
#include "exo_hal_common.h"
#include "exo_io_al_common.h"
#include "exo_io_al_can_common.h"

/**
 * @brief CAN Callback ID enumeration definition
 */
typedef enum
{
    IOHAL_STM32_CAN_TX_MB0_CPLT_CB_ID,          /*!< CAN Mailbox0 Transfer completed callback ID    */
    IOHAL_STM32_CAN_TX_MB1_CPLT_CB_ID,          /*!< CAN Mailbox1 Transfer completed callback ID    */
    IOHAL_STM32_CAN_TX_MB2_CPLT_CB_ID,          /*!< CAN Mailbox2 Transfer completed callback ID    */
    IOHAL_STM32_CAN_MB0_ABORT_CB_ID,            /*!< CAN Mailbox0 Abort callback ID                 */
    IOHAL_STM32_CAN_MB1_ABORT_CB_ID,            /*!< CAN Mailbox1 Abort callback ID                 */
    IOHAL_STM32_CAN_MB2_ABORT_CB_ID,            /*!< CAN Mailbox2 Abort callback ID                 */
    IOHAL_STM32_CAN_FIFO0_MSG_PEND_CB_ID,       /*!< CAN FIFO0 message pending callback ID          */
    IOHAL_STM32_CAN_FIFO0_FULL_CB_ID,           /*!< CAN FIFO0 full callback ID                     */
    IOHAL_STM32_CAN_FIFO1_MSG_PEND_CB_ID,       /*!< CAN FIFO1 message pending callback ID          */
    IOHAL_STM32_CAN_FIFO1_FULL_CB_ID,           /*!< CAN FIFO1 full callback ID                     */
    IOHAL_STM32_CAN_SLEEP_CB_ID,                /*!< CAN sleep callback ID                          */
    IOHAL_STM32_CAN_WAKEUP_CB_ID,               /*!< CAN wakeup callback ID                         */
    IOHAL_STM32_CAN_ERROR_CB_ID,                /*!< CAN error callback ID                          */

} iohal_stm32_can_cbid;


/* Prototype Definitions */
/**
 * @brief  This function initializes the CAN1 peripheral according to the specified
 *         parameters
 * @param[in]  ioal_hcan1 - ioal_hcan1 pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN1.
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_can1_init(ioal_can_hdle *ioal_hcan1);
/**
 * @brief  This function initializes the CAN3 peripheral according to the specified
 *         parameters
 * @param[in]  ioal_hcan3 - ioal_hcan3 pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN3.
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_can3_init(ioal_can_hdle *ioal_hcan3);
/**
 * @brief  This function initializes the CAN2 peripheral according to the specified
 *         parameters
 * @param[in]  ioal_hcan2 - ioal_hcan2 pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN2.
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_can2_init(ioal_can_hdle *ioal_hcan2);
/**
 * @brief  This function starts the CAN interface.
 * @param[in]  ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_can_start(ioal_can_hdle *ioal_hcan);
/**
 * @brief  This function stops the CAN interface
 * @param[in]  ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_can_stop(ioal_can_hdle *ioal_hcan);
/**
 * @brief  This function request the sleep mode
 * @param[in]  ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_can_request_sleep(ioal_can_hdle *ioal_hcan);
/**
 * @brief  This function wake up from sleep mode.
 * @param[in]  ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_can_wakeup(ioal_can_hdle *ioal_hcan);
/**
 * @brief  This function check the sleep state of CAN interface
 * @param[in]  ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval Status
 *          - 0 : Sleep mode is not active.
 *          - 1 : Sleep mode is active.
 */
hal_ret_sts io_hal_stm32f7xx_can_is_sleep_active(ioal_can_hdle *ioal_hcan);
/**
 * @brief  This function register the CAN CallBack ID
 * @param[in]  ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  cbid - ID of the callback to be registered
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_can_reg_cb(ioal_can_hdle *ioal_hcan, iohal_stm32_can_cbid cbid);

/*****Control Function****************/
/**
 * @brief  This function add a message to the first free Tx mailbox and activate the
 *         corresponding transmission request.
 * @param[in] ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  p_header - pointer to a iohal_can_tx_header structure.
 * @param[in]  adata - array containing the payload of the Tx frame.
 * @param[in]  ptxmailbox - pointer to a variable where the function will return
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_add_tx_message(ioal_can_hdle *ioal_hcan, iohal_can_tx_header *p_header, uint8_t adata[], uint32_t *ptxmailbox);
/**
 * @brief  This function abort transmission requests
 * @param[in] ioal_hcan - ioal_hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  txmailboxes - List of the Tx Mailboxes to abort.
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_abort_tx_request(ioal_can_hdle *ioal_hcan, uint32_t txmailboxes);
/**
 * @brief  This function returns the number of free Tx Mailboxes.
 * @param[in] ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval Number of free Tx Mailboxes.
 */
uint32_t io_hal_stm32f7xx_get_tx_mailboxes_free_level(ioal_can_hdle *ioal_hcan);
/**
 * @brief  This function check if a transmission request is pending on Tx side
 * @param[in] ioal_hcan - ioal_hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  txmailboxes - List of Tx Mailboxes to check.
 * @retval Status
 *          - 0 : No pending transmission request on any selected Tx Mailboxes.
 *          - 1 : Pending transmission request on at least one of the selected
 *                Tx Mailbox.
 */
uint32_t io_hal_stm32f7xx_is_tx_message_pending(ioal_can_hdle *ioal_hcan, uint32_t txmailboxes);
/**
 * @brief  This function get timestamp of Tx message sent
 * @param[in] ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param  txmailbox - Tx Mailbox
 * @retval Timestamp of message sent from Tx Mailbox.
 */
uint32_t io_hal_stm32f7xx_get_tx_time_stamp(ioal_can_hdle *ioal_hcan, uint32_t txmailbox);
/**
 * @brief  This function gets CAN frame from the Rx FIFO
 * @param[in] ioal_hcan - ioal_hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  rxfifo - Fifo number of the received message to be read.
 * @param[in]  p_header -  pointer to a iohal_can_rx_header structure
 * @param[out]  adata - array where the payload of the Rx frame will be stored.
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_get_rx_message(ioal_can_hdle *ioal_hcan, uint32_t rxfifo, iohal_can_rx_header *p_header, uint8_t adata[]);
/**
 * @brief  This function get Rx FIFO fill level.
 * @param[in] ioal_hcan - ioal_hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  rxfifo - Rx FIFO.
 * @retval Number of messages available in Rx FIFO.
 */
uint32_t io_hal_stm32f7xx_get_rx_fifo_fill_level(ioal_can_hdle *ioal_hcan, uint32_t rxfifo);
/**
 * @brief  This function configures the CAN reception filter
 * @param[in] ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  sfilterconfig -  pointer to a iohal_can_filter structure
 * @retval HAL status
 */

hal_ret_sts io_hal_stm32f7xx_can_configfilter(ioal_can_hdle *ioal_hcan, iohal_can_filter *sFilterConfig);

/* Interrupts management ******************************************************/

/**
 * @brief  This function activate notifications
 * @param[in] ioal_hcan - ioal_hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  active_its - this indicates which interrupts will be enabled.
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_can_activate_notification(ioal_can_hdle *ioal_hcan, uint32_t active_its);
/**
 * @brief  This function deactivate notifications
 * @param[in] ioal_hcan - ioal_hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  inactive_its - this indicates which interrupts will be disabled.
 * @retval HAL status
 */

hal_ret_sts io_hal_stm32f7xx_can_deactivate_notification(ioal_can_hdle *ioal_hcan, uint32_t inactive_its);


/* Peripheral State and Error functions ***************************************/
/**
 * @brief  This function get the CAN state.
 * @param[in] ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL state
 */
iohal_can_state io_hal_stm32f7xx_can_get_state(ioal_can_hdle *ioal_hcan);
/**
 * @brief  This function get the CAN error code.
 * @param[in] ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval CAN Error Code
 */
hal_ret_sts io_hal_stm32f7xx_can_get_error(ioal_can_hdle *ioal_hcan);
/**
 * @brief  This function reset the CAN error code.
 * @param[in] ioal_hcan - ioal_hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_can_reset_error(ioal_can_hdle *ioal_hcan);

/* API Mapping */

#define io_hal_common_can1_init                     io_hal_stm32f7xx_can1_init
#define io_hal_common_can3_init                     io_hal_stm32f7xx_can3_init
#define io_hal_common_can2_init                     io_hal_stm32f7xx_can2_init
#define io_hal_common_can_start                     io_hal_stm32f7xx_can_start
#define io_hal_common_can_stop                      io_hal_stm32f7xx_can_stop
#define io_hal_common_can_request_sleep             io_hal_stm32f7xx_can_request_sleep
#define io_hal_common_can_wakeup                    io_hal_stm32f7xx_can_wakeup
#define io_hal_common_can_is_sleep_active               io_hal_stm32f7xx_can_is_sleep_active
#define io_hal_common_can_reg_cb                    io_hal_stm32f7xx_can_reg_cb

#define io_hal_common_add_tx_message                io_hal_stm32f7xx_add_tx_message
#define io_hal_common_abort_tx_request              io_hal_stm32f7xx_abort_tx_request
#define io_hal_common_get_tx_mailboxes_free_level   io_hal_stm32f7xx_get_tx_mailboxes_free_level
#define io_hal_common_is_tx_message_pending         io_hal_stm32f7xx_is_tx_message_pending
#define io_hal_common_get_tx_time_stamp             io_hal_stm32f7xx_get_tx_time_stamp
#define io_hal_common_get_rx_message                io_hal_stm32f7xx_get_rx_message
#define io_hal_common_get_rx_fifo_fill_level        io_hal_stm32f7xx_get_rx_fifo_fill_level

#define io_hal_common_can_activate_notification         io_hal_stm32f7xx_can_activate_notification
#define io_hal_common_can_deactivate_notification       io_hal_stm32f7xx_can_deactivate_notification
#define io_hal_common_can_get_state                     io_hal_stm32f7xx_can_get_state
#define io_hal_common_can_get_error                     io_hal_stm32f7xx_can_get_error
#define io_hal_common_can_reset_error                   io_hal_stm32f7xx_can_reset_error
#define io_hal_common_can_configfilter                  io_hal_stm32f7xx_can_configfilter

#endif /* _IO_AL_STM32F7XX_CAN_H_ */

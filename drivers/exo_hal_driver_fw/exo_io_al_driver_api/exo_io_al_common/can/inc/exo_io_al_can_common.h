/**
 * @file exo_io_al_can_common.h
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

#ifndef _IO_AL_CAN_COMMON_H_
#define _IO_AL_CAN_COMMON_H_


#define CAN_INTF_ENB


#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include <stdint.h>



/**
 * @brief IO-HAl CAN interface control block handle structure definition
 */
typedef struct _ioal_can_hdle
{
    ioal_intf_gen_info intf_gen_info;                           /*!< Hold general information of interface                              */
    void (*can_tx_mb0_cplt_cb)(struct _ioal_can_hdle *hcan);    /*!< Hold Fn address for Tx complete for mailbox0 event                 */
    void (*can_tx_mb1_cplt_cb)(struct _ioal_can_hdle *hcan);    /*!< Hold Fn address for Tx complete for mailbox1 event                 */
    void (*can_tx_mb2_cplt_cb)(struct _ioal_can_hdle *hcan);    /*!< Hold Fn address for Tx complete for mailbox2 event                 */
    void (*can_mb0_abort_cb)(struct _ioal_can_hdle *hcan);      /*!< Hold Fn address for mailbox0 abort event                           */
    void (*can_mb1_abort_cb)(struct _ioal_can_hdle *hcan);      /*!< Hold Fn address for mailbox1 abort event                           */
    void (*can_mb2_abort_cb)(struct _ioal_can_hdle *hcan);      /*!< Hold Fn address for mailbox2 abort event                           */
    void (*can_fifo0_msg_pend_cb)(struct _ioal_can_hdle *hcan); /*!< Hold Fn address for message pending indication for fifo0 event     */
    void (*can_fifo0_full_cb)(struct _ioal_can_hdle *hcan);     /*!< Hold Fn address for fifo0 full event                               */
    void (*can_fifo1_msg_pend_cb)(struct _ioal_can_hdle *hcan); /*!< Hold Fn address for message pending indication for fifo1 event     */
    void (*can_fifo1_full_cb)(struct _ioal_can_hdle *hcan);     /*1< Hold Fn address for fifo1 full event                               */
    void (*can_sleep_cb)(struct _ioal_can_hdle *hcan);          /*!< Hold Fn address for sleep event                                    */
    void (*can_wakeup_cb)(struct _ioal_can_hdle *hcan);         /*!< Hold Fn address for wakeup event                                   */
    void (*can_error_cb)(struct _ioal_can_hdle *hcan);          /*!< Hold Fn address for error event                                    */
}ioal_can_hdle;

/**
 * @brief IO-HAl CAN state structure definition
 */
typedef enum
{
    IOHAL_CAN_STATE_RESET             = 0x00U,  /*!< CAN not yet initialized or disabled */
    IOHAL_CAN_STATE_READY             = 0x01U,  /*!< CAN initialized and ready for use   */
    IOHAL_CAN_STATE_LISTENING         = 0x02U,  /*!< CAN receive process is ongoing      */
    IOHAL_CAN_STATE_SLEEP_PENDING     = 0x03U,  /*!< CAN sleep request is pending        */
    IOHAL_CAN_STATE_SLEEP_ACTIVE      = 0x04U,  /*!< CAN sleep mode is active            */
    IOHAL_CAN_STATE_ERROR             = 0x05U   /*!< CAN error state                     */

} iohal_can_state;
/**
 * @brief  IO-HAl CAN filter configuration structure definition
 */
typedef struct
{
    uint32_t FilterIdHigh;                  /*!< CAN filter id high             */
    uint32_t FilterIdLow;                   /*!< CAN filter id low              */
    uint32_t FilterMaskIdHigh;              /*!< CAN filter mask id high        */
    uint32_t FilterMaskIdLow;               /*!< CAN filter mask id low         */
    uint32_t FilterFIFOAssignment;          /*!< CAN filter FIFO assignment     */
    uint32_t FilterBank;                    /*!< CAN filter basnk               */
    uint32_t FilterMode;                    /*!< CAN filter mode                */
    uint32_t FilterScale;                   /*!< CAN filter scale               */
    uint32_t FilterActivation;              /*!< CAN filter acivation           */
    uint32_t SlaveStartFilterBank;          /*!< CAN slave start filter bank    */
} iohal_can_filter;

/**
 * @brief  IOHAL CAN Tx message header structure definition
 */
typedef struct
{
    uint32_t StdId;                                     /*!< CAN standard id.               */
    uint32_t ExtId;                                     /*!< CAN extended id.               */
    uint32_t IDE;                                       /*!< CAN identifier type            */
    uint32_t RTR;                                       /*!< CAN remote transition request  */
    uint32_t DLC;                                       /*!< CAN length of the frame        */
    io_hal_functional_state TransmitGlobalTime;         /*!< functional state               */

} iohal_can_tx_header;
/**
 * @brief  IOHAL CAN Rx message header structure definition
 */
typedef struct
{
    uint32_t StdId;                 /*!< CAN standard id.               */
    uint32_t ExtId;                 /*!< CAN extended id.               */
    uint32_t IDE;                   /*!< CAN identifier type            */
    uint32_t RTR;                   /*!< CAN remote transition request  */
    uint32_t DLC;                   /*!< CAN length of the frame        */
    uint32_t Timestamp;             /*!< CAN timestamp                  */
    uint32_t FilterMatchIndex;      /*!< CAN filter match index         */
} iohal_can_rx_header;

/**
 * @brief  This function initializes the CAN peripheral according to the specified
 *         parameters
 * @retval HAL status
 */
hal_ret_sts io_hal_can_init(void);
/**
 * @brief  This function initializes callback event for CAN1
 * @param[in] hcan1 - hcan1 pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN1
 * @retval No return
 */
void io_hal_can1_cb_init(ioal_can_hdle *hcan1);
/**
 * @brief  This function initializes callback event for CAN3
 * @param[in] hcan3 - hcan3 pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN3
 * @retval No return
 */
void io_hal_can3_cb_init(ioal_can_hdle *hcan3);
/**
 * @brief  This function initializes callback event for CAN2
 * @param[in] hcan2 - hcan2 pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN2
 * @retval No return
 */
void io_hal_can2_cb_init(ioal_can_hdle *hcan2);
/**
 * @brief  This function starts the CAN interface.
 * @param[in] hcan - hcan pointer to an CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL status
 */
hal_ret_sts io_hal_can_start(ioal_can_hdle *hcan);
/**
 * @brief  This function stops the CAN interface
 * @param[in] hcan - hcan pointer to an CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL status
 */
hal_ret_sts io_hal_can_stop(ioal_can_hdle *hcan);
/**
 * @brief  This function request the sleep mode
 * @param[in] hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL status.
 */
hal_ret_sts io_hal_can_request_sleep(ioal_can_hdle *hcan);
/**
 * @brief  This function wake up from sleep mode.
 * @param[in] hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL status.
 */
hal_ret_sts io_hal_can_wakeup(ioal_can_hdle *hcan);
/**
 * @brief  This function check the sleep state of CAN interface
 * @param[in] hcan - hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval Status
 *          - 0 : Sleep mode is not active.
 *          - 1 : Sleep mode is active.
 */
uint32_t io_hal_can_is_sleep_active(ioal_can_hdle *hcan);

/**
 * @brief  This function add a message to the first free Tx mailbox and activate the
 *         corresponding transmission request.
 * @param[in] hcan - hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  pheader - pointer to a iohal_can_tx_header structure.
 * @param[in]  adata - array containing the payload of the Tx frame.
 * @param[in]  ptxmailbox - pointer to a variable where the function will return
 * @retval HAL status
 */
hal_ret_sts io_hal_can_add_tx_message(ioal_can_hdle *hcan, iohal_can_tx_header *pheader, uint8_t adata[], uint32_t *ptxmailbox);
/**
 * @brief  This function abort transmission requests
 * @param[in] hcan - hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  txmailboxes - List of the Tx Mailboxes to abort.
 * @retval HAL status
 */
hal_ret_sts io_hal_can_abort_tx_request(ioal_can_hdle *hcan, uint32_t txmailboxes);
/**
 * @brief  This function returns the number of free Tx Mailboxes.
 * @param[in] hcan - hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval Number of free Tx Mailboxes.
 */
uint32_t io_hal_can_get_tx_mailboxes_free_level(ioal_can_hdle *hcan);
/**
 * @brief  This function check if a transmission request is pending on Tx side
 * @param[in] hcan - hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  txmailboxes - List of Tx Mailboxes to check.
 * @retval Status
 *          - 0 : No pending transmission request on any selected Tx Mailboxes.
 *          - 1 : Pending transmission request on at least one of the selected
 *                Tx Mailbox.
 */
uint32_t io_hal_can_is_tx_message_pending(ioal_can_hdle *hcan, uint32_t txmailboxes);
/**
 * @brief  This function get timestamp of Tx message sent
 * @param[in] hcan - hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param  txmailbox - Tx Mailbox
 * @retval Timestamp of message sent from Tx Mailbox.
 */
uint32_t io_hal_can_get_tx_time_stamp(ioal_can_hdle *hcan, uint32_t txmailbox);
/**
 * @brief  This function gets CAN frame from the Rx FIFO
 * @param[in] hcan - hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  rxfifo - Fifo number of the received message to be read.
 * @param[in]  pheader -  pointer to a iohal_can_rx_header structure
 * @param[out]  adata - array where the payload of the Rx frame will be stored.
 * @retval HAL status
 */
hal_ret_sts io_hal_can_get_rx_message(ioal_can_hdle *hcan, uint32_t rxfifo, iohal_can_rx_header *pheader, uint8_t adata[]);
/**
 * @brief  This function get Rx FIFO fill level.
 * @param[in] hcan - hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  rxfifo - Rx FIFO.
 * @retval Number of messages available in Rx FIFO.
 */
uint32_t io_hal_can_get_rx_fifo_fill_level(ioal_can_hdle *hcan, uint32_t rxfifo);
/**
 * @brief  This function configures the CAN reception filter
 * @param[in] hcan - hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  sfilterconfig -  pointer to a iohal_can_filter structure
 * @retval HAL status
 */
hal_ret_sts io_hal_can_configfilter(ioal_can_hdle *hcan, iohal_can_filter *sfilterconfig);
/**
 * @brief  This function activate notifications
 * @param[in] hcan - hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  active_its - this indicates which interrupts will be enabled.
 * @retval HAL status
 */
hal_ret_sts io_hal_can_activate_notification(ioal_can_hdle *hcan, uint32_t active_its);
/**
 * @brief  This function deactivate notifications
 * @param[in] hcan - hcan pointer to an ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @param[in]  inactive_its - this indicates which interrupts will be disabled.
 * @retval HAL status
 */
hal_ret_sts io_hal_can_deactivate_notification(ioal_can_hdle *hcan, uint32_t inactive_its);
/**
 * @brief  This function get the CAN state.
 * @param[in] hcan - hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL state
 */
iohal_can_state io_hal_can_get_state(ioal_can_hdle *hcan);
/**
 * @brief  This function get the CAN error code.
 * @param[in] hcan - hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval CAN Error Code
 */
hal_ret_sts io_hal_can_get_error(ioal_can_hdle *hcan);
/**
 * @brief  This function reset the CAN error code.
 * @param[in] hcan - hcan pointer to a ioal_can_hdle structure that contains
 *         the configuration information for the specified CAN.
 * @retval HAL status
 */
hal_ret_sts io_hal_can_reset_error(ioal_can_hdle *hcan);

#endif /* _IO_AL_CAN_COMMON_H_ */

#ifndef LINUX_TEMP_PORT
/**
 * @brief CAN1 temporary dummy function
 *
 * @param[in] hcan : pointer to CAN handle
 */
void check_can1_dummy(ioal_can_hdle *hcan);

/**
 * @brief CAN3 temporary dummy function
 *
 * @param[in] hcan : pointer to CAN handle
 */
void check_can3_dummy(ioal_can_hdle *hcan);

/**
 * @brief CAN2 temporary dummy function
 *
 * @param[in] hcan : pointer to CAN handle
 */
void check_can2_dummy(ioal_can_hdle *hcan);
#else

/**
 * @brief Linux CAN dummy function
 *
 * @param[in] hcan : pointer to CAN handle
 */
void linux_can_dummy_fn(struct _ioal_can_hdle *hcan);
#endif

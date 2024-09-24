/**
 * @file exo_tctm_ipc.h
 *
 * @brief This file contains TCTM IPC and ID enumerations.
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
 *
 *
 */

#ifndef INCLUDES_EXO_TCTM_IPC_H_
#define INCLUDES_EXO_TCTM_IPC_H_

/*!
 *  @brief This enum holds the enumeration values of TC and TM ID
 */
typedef enum {
    UHF_BOOTLOADER_MSG_PING        = 0X00,  /*!< Bootloader message ping */
    UHF_BOOTLOADER_MSG_ACK         = 0X01,  /*!< Bootloader message acknowledge */
    UHF_BOOTLOADER_MSG_WRITE_PAGE  = 0X02,  /*!< Bootloader message write page */
    UHF_BOOTLOADER_MSG_ERASE       = 0X0C,  /*!< Bootloader message erase */
    UHF_BOOTLOADER_MSG_NACK        = 0X0F,  /*!< Bootloader message nack */
    UHF_CMN_MSG_ACK                = 0X10,  /*!< Common message acknowledge */
    UHF_CMN_MSG_ASCII              = 0X11,  /*!< Common message ascii */
    UHF_RADIO_MSG_REBOOT           = 0X12,  /*!< Radio message reboot */
    UHF_RADIO_MSG_GET_TIME         = 0X13,  /*!< Radio message get time */
    UHF_RADIO_MSG_SET_TIME         = 0X14,  /*!< Radio message set time */
    UHF_RADIO_MSG_RANGING          = 0X15,  /*!< Radio message ranging */
    UHF_RADIO_MSG_RANGING_ACK      = 0X16,  /*!< Radio message ranging acknowledge */
    UHF_RADIO_MSG_GET_TELEM        = 0X17,  /*!< Radio message get telemetry */
    UHF_RADIO_MSG_TELEM            = 0X18,  /*!< Radio message telemetry */
    UHF_RADIO_MSG_GET_CALLSIGN     = 0X19,  /*!< Radio message get callsign */
    UHF_RADIO_MSG_SET_CALLSIGN     = 0X1A,  /*!< Radio message set callsign */
    UHF_RADIO_MSG_CALLSIGN         = 0X1B,  /*!< Radio message callsign */
    UHF_CMN_MSG_NACK               = 0XFF,  /*!< Common message nack */
    UHF_BEACON_DATA                = 0X100,  /*!< UHF Beacon data */
    UHF_SET_BEACON_TM_TMR_CFG      = 0x101,  /*!< Set beacon TM timer configuration */
    UHF_GET_BEACON_TM_TMR_CFG      = 0x102,  /*!< Get beacon TM timer configuration */
    UHF_BEACON_TX_ST               = 0x103,  /*!< Beacon TX start */
    UHF_BEACON_TX_STOP             = 0x104,  /*!< Beacon TX stop */
}e_comms_uhf_msg_no;

/**
 * @brief IPC/ITC message ID enumeration
 */
typedef enum
{
    OBC_UHF_INIT_REQ = 0x500,  /*!< INIT refers to resume state */
    OBC_UHF_DEINIT_REQ,/*!< DEINIT refers to suspend state */
    UHF_OBC_INIT_RSP, /*!< UHF OBC init response */
    UHF_OBC_DEINIT_RSP, /*!< UHF OBC deinit response */
    UHF_OBC_ERROR_IND, /*!< UHF OBC error index */
    UHF_TX_PERIODIC_BEACON_TMR_EXP, /*!< UHF TX periodic beacon timer expire */
    UHF_TX_PERIODIC_TIMER_EXP, /*!< UHF TX periodic timer expire */
    UHF_UART_CMD_RSP, /*!< UHF uart command response */
    UHF_UART_CMD_RSP_TIMEOUT, /*!< UHF uart command response timeout */
    UHF_TM_PERIODIC_READ, /*!< UHF TM periodic read */
    UHF_REP_TMR_EXP, /*!< UHF Response timer expire */
    UHF_CMD_TMR_EXP, /*!< UHF command timer expire */
}e_ipc_msg_id;

#endif /* INCLUDES_EXO_TCTM_IPC_H_ */

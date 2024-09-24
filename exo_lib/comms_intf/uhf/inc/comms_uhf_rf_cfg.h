/**
 * @file comms_uhf_rf_cfg.h
 *
 * @brief This file contains APIs for UHF parameters configuration
 *        programming and readback
 *
 * @copyright Copyright 2024 Antaris, Inc.
 *
 * Licensed under the Apache License, Version 2.0(the "License");
 *you may not use this file except in compliance with the License.
 *you may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef COMMS_UHF_RF_CFG_H_
#define COMMS_UHF_RF_CFG_H_

#include "comms_uhf_main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MASK_8_BITS 0xFF ///< Mask 8 bits value
#define MASK_7_BITS 0x7F ///< Mask 7 bits value
#define MASK_6_BITS 0x3F ///< Mask 6 bits value
#define MASK_5_BITS 0x1F ///< Mask 5 bits value
#define MASK_4_BITS 0x0F ///< Mask 4 bits value
#define MASK_3_BITS 0x07 ///< Mask 3 bits value
#define MASK_2_BITS 0x03 ///< Mask 2 bits value
#define MASK_1_BITS 0x01 ///< Mask 1 bits value
#define MASK_0_BITS 0x00 ///< Mask 0 bits value

#define FLASH_WRITE_PAGE_SIZE 128 ///< Flash write page size
#define ESP_MAX_PAYLOAD 251 ///< ESP maximum payload
#define BOOTLOADER_ACK_MSG_PONG   0 ///< Bootloader acknowledge message
#define BOOTLOADER_ACK_MSG_ERASED 1 ///< Bootloader acknowledge message erased

/**
 * @brief comms UHF header structure definition
 */
typedef struct __attribute__((packed))
{
    uint8_t sync1;   /*!< sync 1 */
    uint8_t sync2;   /*!< sync 2 */
    uint8_t length;   /*!< Length */
    uint16_t hwid;   /*!< Hardware ID */
    uint16_t seqnum;    /*!< Sequence number */
    uint8_t system;     /*!< System */
    uint8_t command;    /*!< command */
}__attribute__((packed))s_comms_uhf_header;

/**
 * @brief comms UHF uart header parameters
 */
typedef struct __attribute__((packed))
{
    uint16_t hwid;    /*!< Hardware ID */
    uint16_t seqnum;  /*!< Sequence number */
    uint8_t system;   /*!< system */
    uint8_t command;  /*!< Command */
}s_comms_uhf_uart_header;

/**
 * @brief comms UHF data details
 */
typedef struct __attribute__((packed))
{
    s_comms_uhf_header header;   /*!< UHF Header */
    uint8_t data[UHF_MAX_PLD - sizeof(s_comms_uhf_header)]; /*!< payload data */
}s_comms_uhf_data;

/**
 * @brief comms UHF UART data details
 */
typedef struct __attribute__((packed))
{
    uint8_t length;       /*!< Length */
    s_comms_uhf_uart_header header;  /*!< UHF UART header */
    uint8_t data[UHF_MAX_PLD - sizeof(s_comms_uhf_uart_header)]; /*!< Payload data */
}s_comms_uhf_uart_data;

/**
 * @brief comms UHF command buffer
 */
typedef union command_buffer
{
    uint8_t msg[UHF_MAX_PLD];  /*!< Message */
    s_comms_uhf_data cmd;      /*!< COMMS UHF data */
}u_comms_uhf_command_buffer_t;


/**
 * @brief UHF TM structure
 */
typedef struct __attribute__((packed))
{
    uint8_t reserved;
    uint32_t uptime;   /*!< Uptime */
    uint32_t uart0_rx_count; /*!< UART0 RX Count */
    uint32_t uart1_rx_count; /*!< UART1 RX Count */
    uint8_t  rx_mode;        /*!< RX mode */
    uint8_t  tx_mode;        /*!< TX mode */
    int16_t  adc[UHF_ADC_NUM_CHANNELS]; /*!< UHF ADC channels */
    int8_t   last_rssi;      /*!< Last RSSI */
    uint8_t  last_lqi;       /*!< Last LQI */
    int8_t   last_freqest;   /*!< Last frequency est */
    uint32_t packets_sent;   /*!< packets sent */
    uint32_t cs_count;       /*!< CS Count */
    uint32_t packets_good;   /*!< Packets good */
    uint32_t packets_rejected_checksum;  /*!< packets rejected checksum */
    uint32_t packets_rejected_reserved;  /*!< packets rejected reserved */
    uint32_t packets_rejected_other;     /*!< packets rejected other */
    uint32_t reserved0;                  /*!< Reserved bytes */
    uint32_t reserved1;                /*!< Reserved bytes */
    uint32_t custom0;                    /*!< Custom 1 */
    uint32_t custom1;                    /*!< Custom 2 */
}s_comms_uhf_tm;

/**
 * @brief uhf timestamp info
 */
typedef struct __attribute__((packed))
{
    uint32_t seconds; /*!< in seconds */
    uint32_t nanoseconds; /*!< in nanaseconds */
}s_timespec_t;

/**
 * @brief uhf ranging ack info
 */
typedef struct __attribute__((packed))
{
    uint8_t ack_type; /*!< ack type */
    uint8_t ack_version;/*!< ack version */
}s_radio_ranging_ack_t;

/**
 * @brief uhf call sign info
 */
typedef struct __attribute__((packed))
{
    char callsign[8]; /*!< call sign data */
}s_radio_callsign_t;

/**
 * @brief uhf bootloader page data info
 */
typedef struct __attribute__((packed))
{
    uint8_t flash_page; /*!< Flash page */
    uint8_t page_data[FLASH_WRITE_PAGE_SIZE]; /*!< Bootloader page buffer */
}s_msg_bootloader_write_page_t;

/**
 * @brief uhf bootloader ack info
 */
typedef struct __attribute__((packed))
{
    uint8_t ack_message; /*!< Acknowledge message */
}s_msg_bootloader_ack_t;

/**
 * @brief uhf data info
 */
typedef union
{
    s_msg_bootloader_write_page_t write_page; /*!< Write page */
    s_msg_bootloader_ack_t ack; /*!< Bootloader Acknowledge */
    //signature_key_t load_keys[SIGNATURE_KEY_COUNT];
    //hwid_t hwid;
    uint8_t data[1]; /*!< Data */
}s_msg_data_t;

#ifdef __cplusplus
}
#endif
#endif /*COMMS_UHF_RF_CFG_H_*/

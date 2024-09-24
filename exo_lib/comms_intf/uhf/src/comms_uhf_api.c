/**
 * @file comms_uhf_api.c
 *
 * @brief This file contains APIs for UHF parameters configuration
 *        programming and readback
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
#include <math.h>
#include "comms_uhf_main.h"
#include "comms_uhf_sim.h"
#include "comms_uhf_api.h"
#include "comms_uhf_csp.h"
#include <stdint.h>
#include "comms_uhf_ipc.h"
#include "usart.h"

#define XO_FREQ 27000000 ///< UHF crystal oscillator frequency

s_radio_callsign_t call_sign_cfg; ///< Readback UHF call sign structure
s_timespec_t set_time_cfg; ///< Readback UHF set time cfg
s_msg_data_t write_page_cfg; ///< Readback UHF write page cfg

extern s_sdr_tmr_cfg  uhf_tmr_cfg; // UHF timer
extern uint8_t  comms_uhf_csw_rx_buf[512]; // UHF CSW RX buffer
extern uint8_t  uhf_uart_rsp[400]; // UHF UART response buffer 
extern uint16_t  uhf_uart_rsp_len; // UHF UART response length


/**
 * @brief Set UHF call sign.
 * 
 * Function to store received UHF call sign data.
 */
int32_t sdr_uhf_set_call_sign_req(s_radio_callsign_t *call_sign)
{
    os_memset(&call_sign->callsign[0],0,sizeof(s_radio_callsign_t));
    for(uint16_t i =0; i<8; i++)
    {
        DEBUG_CPRINT(("base frequency :%d\n",call_sign->callsign[i]));
        call_sign_cfg.callsign[i] = call_sign->callsign[i];
    }

    return 0;
}

/**
 * @brief Set UHF set time.
 * 
 * Function to store received UHF set time data.
 */
int32_t sdr_uhf_set_time_req(s_timespec_t *time)
{
    os_memset(&set_time_cfg,0,sizeof(s_timespec_t));

    set_time_cfg.seconds = time->seconds;
    set_time_cfg.nanoseconds = time->nanoseconds;

    return 0;
}

/**
 * @brief Set bootload msg write.
 * 
 * Function to store received UHF bootload msg write data.
 */
int32_t sdr_uhf_bootload_msg_write(s_msg_data_t *page_cfg)
{
    os_memset(&write_page_cfg,0,sizeof(s_msg_data_t));
    os_memcpy(&write_page_cfg,page_cfg,sizeof(s_msg_data_t));

    return 0;
}

/**
 * @brief set UHF timer values.
 * 
 * Function to store received UHF beacon and periodic tm timers values.
 */
int32_t sdr_app_tc_set_uhf_tmr_cfg(s_sdr_tmr_cfg *tmr_cfg)
{
    os_memcpy(&uhf_tmr_cfg,tmr_cfg,sizeof(s_sdr_tmr_cfg));

    DEBUG_CPRINT(("beacon enable timer :%u\n",tmr_cfg->beacon_enb_tmr));
    DEBUG_CPRINT(("beacon periodicity timer :%u\n",tmr_cfg->beacon_prd_tmr));
    DEBUG_CPRINT(("beacon rep timer :%u\n",tmr_cfg->beacon_rep_tmr));
    DEBUG_CPRINT(("tx data rep cnt :%u\n",tmr_cfg->tx_data_rep_cnt));
    DEBUG_CPRINT(("Enter tm read timer: %u\n",tmr_cfg->uhf_tm_read_tmr));

    return 0;
}

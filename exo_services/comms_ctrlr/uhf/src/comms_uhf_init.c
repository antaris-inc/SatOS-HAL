/**
 * @file comms_uhf_init.c
 *
 * @brief This file contains functions to initialize and setup the UHF
 * communications interface.
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

#include "comms_uhf_init.h"
#include "comms_uhf_tmr.h"
#include "exo_common.h"
#include "csp_types.h"
#include "csp_if_uhf.h"


uint8_t  uhf_static_write_sts = 0; ///< UHF static write status

/** Extended structure declaration **/
extern s_sdr_tmr_cfg  uhf_tmr_cfg; // UHF timer configuration
extern s_sdr_beacon_pld uhf_beacon_data; // UHF beacon data

/** Extended UHF global variables **/
extern uint8_t  uhf_tc_cmd_id; // UHF TC command ID
extern uint32_t  csp_uhf_data_count; // UHF data count
extern uint8_t  uhf_tc_len; // UHF TC length
extern uint16_t  uhf_tc_tm_id; // UHF TC TM ID
extern uint16_t  uhf_seq_num; // UHF sequence number
extern uint16_t  uhf_data_seq_num; // UHF data sequence number
extern uint32_t  uhf_beacon_seq_num; // UHF Beacon sequence number
extern unsigned int  byte_count; // Byte count
extern uint8_t  comms_uhf_csw_rx_buf[512]; // UHF controller RX buffer
extern uint8_t  tx_buff[UHF_MAX_PLD]; // TX buffer
extern uint8_t  uhf_rx_cmd_buff[UHF_MAX_PAYLOAD+1]; // UHF RX command buffer
#ifndef LINUX_TEMP_PORT
extern uint8_t  uhf_uart_rsp[400]; // UHF uart response
extern uint16_t  uhf_uart_rsp_len; // UHF uart response length
#endif
/**
 * @brief This function is used to initialize and assign 
 * default values to UHF params and timer 
 */
void comms_uhf_init_uhf_cfg(void)
{   
    os_memset(&uhf_tmr_cfg,0,sizeof(s_sdr_tmr_cfg));

    os_memset(comms_uhf_csw_rx_buf,0,sizeof(comms_uhf_csw_rx_buf));
    os_memset(tx_buff,0,sizeof(tx_buff));
    os_memset(uhf_rx_cmd_buff,0,sizeof(uhf_rx_cmd_buff));

    os_memset(&uhf_beacon_data,0,sizeof(s_sdr_beacon_pld));

    os_memcpy(&uhf_beacon_data.bcon_utc.bcon_msg[0],"Hello Earth",sizeof("Hello Earth"));

    uhf_tc_cmd_id =0;
    uhf_static_write_sts =0;
    csp_uhf_data_count =0;
    uhf_tc_len =0;
    uhf_tc_tm_id =0;
    uhf_seq_num =0;
    uhf_data_seq_num =0;
    uhf_beacon_seq_num = 0;
#ifndef LINUX_TEMP_PORT
    uhf_uart_rsp_len =0;
    os_memset(uhf_uart_rsp,0,sizeof(uhf_uart_rsp));
#endif
    comms_uhf_timer_init_default();
    comms_uhf_timer_init();
}

/**
 * @brief Initialize UHF timers with default values
 * 
 * This function initializes the various timers used by the UHF
 * communication system to default values. It will be called as part 
 * of the system initialization sequence.
 */
void comms_uhf_timer_init_default(void)
{
    uhf_tmr_cfg.beacon_enb_tmr = 5*60*1000; // 5 min
    uhf_tmr_cfg.beacon_prd_tmr = 60*1000; // 60 seconds
    uhf_tmr_cfg.beacon_rep_tmr = 2*1000; // 2 second
    uhf_tmr_cfg.uhf_tm_read_tmr = 2*60*1000; // 2 min 
    uhf_tmr_cfg.tx_data_rep_cnt = 1;

    DEBUG_CPRINT(("\nuhf_tmr_cfg.beacon_enb_tmr %d", uhf_tmr_cfg.beacon_enb_tmr));
    DEBUG_CPRINT(("\nuhf_tmr_cfg.beacon_prd_tmr %d", uhf_tmr_cfg.beacon_prd_tmr));
    DEBUG_CPRINT(("\nuhf_tmr_cfg.beacon_rep_tmr %d", uhf_tmr_cfg.beacon_rep_tmr));
    DEBUG_CPRINT(("\nuhf_tmr_cfg.beacon_tm_read %d", uhf_tmr_cfg.uhf_tm_read_tmr));
}


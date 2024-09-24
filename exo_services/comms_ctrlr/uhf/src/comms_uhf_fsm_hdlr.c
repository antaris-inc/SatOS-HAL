/**
 * @file comms_uhf_fsm_hdlr.c
 *
 * @brief This file has the UHF driver FSM implementation and the
 * relevant functions
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
 */
/*********************************************************************/
#include <stdio.h>
#include "sm_api.h"
#include "comms_uhf_sim.h"
#include "comms_uhf_init.h"
#include "comms_uhf_intf.h"
#include "comms_uhf_ipc.h"
#include "comms_uhf_main.h"
#include "exo_common.h"
#include "exo_io_al_sos_timer.h"
#include "comms_uhf_csp.h"
#ifdef LINUX_TEMP_PORT
#include "comms_uhf_sim.h"
#endif
#include "exo_io_al_rtc_common.h"
#include "exo_io_al_sos_timer.h"
#include "exo_tctm_ipc.h"
#include "comms_uhf_tmr.h"


/** Global variables **/
uint8_t uhf_cmd_rsp_timeout_cnt = 0; ///< Command response timeout count
uint8_t uhf_reinit_ongoing = 0; ///< Reinit ongoing flag
uint8_t uhf_fw_upd_sts = 0; ///< Firmware update status
uint8_t uhf_hk_upd_id = 0; ///< UHF health update ID
uint8_t is_uhf_hk_upd_fill = 0; ///< UHF health update fill
s_sdr_beacon_pld uhf_beacon_data; ///< UHF beacon data

extern uint32_t uhf_rep_cnt; // struct for UHF repetition count
extern os_timer_handle_ptr uhf_cmd_timeout; // Timeout used for UHF command
extern uint8_t  uhf_tc_cmd_id ; // UHF TC ID

extern os_timer_handle_ptr uhf_tm_periodic_read; // Timer used for tm store Periodicity Timer

extern os_timer_handle_ptr uhf_beacon_timer; // Timer used for periodic transmission of Beacon signal

extern os_timer_handle_ptr uhf_beacon_enb_timer; // Timer used for enable transmission of Beacon signal

extern os_timer_handle_ptr uhf_rsp_timeout_recovery_tmr; // Timer used for rsp timeout recovery timer

extern os_timer_handle_ptr uhf_cmd_wait_timer; // Timer used for UHF cmd trigger delay

extern uint16_t  uhf_tc_tm_id; // UHF tc tm ID
extern uint8_t  comms_uhf_csw_rx_buf[512]; // UHF controller RX buffer

extern s_sdr_tmr_cfg  uhf_tmr_cfg; // Extended UHF configuration variable

/** Declaration of UHF-Driver FSM function pointer */
typedef uint8_t (*CSW_SM_HDLR)(uint16_t msg_id, void *payload);

/** Definition of UHF Driver FSM function pointer */
CSW_SM_HDLR comms_uhf_fsm_hdlr[COMMS_UHF_MAX_NUM_STATE] = {\
        &comms_uhf_tc_hdlr,\
};

/**
 * @brief This function handle comms TC handling state
 *
 * @param[in] msg_id - value of message id
 * @param[in] payload - pointer with received payload info
 * This handler function implements to handle the TC mesages
 * for the UHF communication system. Also handles timer 
 * expiry events.
 *
 */
uint8_t comms_uhf_tc_hdlr(uint16_t msg_id, void *payload)
{
    uint8_t state = COMMS_UHF_TC_HANDLER;
    int32_t status = 0; //COMMS_UHF_IPC_OK;
    status = status;
    int8_t ret =0;

    uint8_t *tc_tm_data;

    tc_tm_data = (uint8*)payload;

    DEBUG_CPRINT(("received response for COMMS_UHF_TC : %d \n", msg_id));
    switch (msg_id)
    {
        case UHF_UART_CMD_RSP:
        {
            uhf_proc_uart_cmd_rsp(payload);
        }
        break;

        case UHF_TX_PERIODIC_BEACON_TMR_EXP:
        {
            DEBUG_CPRINT(("\n UHF_TX_PERIODIC_BEACON_TMR_EXP"));

            os_timer_start(uhf_beacon_timer,uhf_tmr_cfg.beacon_prd_tmr);
            DEBUG_CPRINT(("UHF: Beacon per timer %d started",uhf_tmr_cfg.beacon_prd_tmr));
            
            uhf_beacon_data.bcon_utc.utc_time = get_crnt_time_date_in_epoch();
            comms_uhf_beacon_tx((uint8_t *)&uhf_beacon_data,sizeof(s_sdr_beacon_pld));
        }
        break;
        
        case UHF_REP_TMR_EXP:
        {
            DEBUG_CPRINT(("\n UHF_BEACON_REP_TMR_EXP"));
            
            uhf_beacon_data.bcon_utc.utc_time = get_crnt_time_date_in_epoch();
            comms_uhf_beacon_tx((uint8_t *)&uhf_beacon_data,sizeof(s_sdr_beacon_pld));
        }
        break;

        case UHF_SET_BEACON_TM_TMR_CFG:
        {
            DEBUG_CPRINT(("\n UHF_SET_BECON_TM_TMR_CFG received\n"));
            ret = sdr_app_tc_set_uhf_tmr_cfg((s_sdr_tmr_cfg *)&tc_tm_data[0]);
            comms_uhf_tc_tm_rsp_hdlr(UHF_SET_BEACON_TM_TMR_CFG, ret);
        }
        break;

        case UHF_GET_BEACON_TM_TMR_CFG:
        {
            DEBUG_CPRINT(("\n UHF_GET_BECON_TM_TMR_CFG received\n"));
            os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],&uhf_tmr_cfg,sizeof(s_sdr_tmr_cfg));
            comms_uhf_tc_tm_rsp_hdlr(uhf_tc_tm_id, sizeof(s_sdr_tmr_cfg));
        }
        break;
        
        case UHF_BOOTLOADER_MSG_PING:
        {
            uhf_upd_send_uart_cmd(msg_id);
        }
        break;

        case UHF_BOOTLOADER_MSG_WRITE_PAGE:
        {
            status = sdr_uhf_bootload_msg_write((s_msg_data_t *)(&tc_tm_data[0]));
            uhf_upd_send_uart_cmd(msg_id);
        }
        break;

        case UHF_BOOTLOADER_MSG_ERASE:
        {
            uhf_upd_send_uart_cmd(msg_id);
        }
        break;

        case UHF_RADIO_MSG_REBOOT:
        {
            uhf_upd_send_uart_cmd(msg_id);
        }
        break;

        case UHF_RADIO_MSG_GET_TIME:
        {
            uhf_upd_send_uart_cmd(msg_id);
        }
        break;
        
        case UHF_RADIO_MSG_SET_TIME:
        {
            status = sdr_uhf_set_time_req((s_timespec_t *)(&tc_tm_data[0]));
            uhf_upd_send_uart_cmd(msg_id);
        }
        break;

        case UHF_RADIO_MSG_GET_TELEM:
        {
            uhf_upd_send_uart_cmd(msg_id);
        }
        break;

        case UHF_RADIO_MSG_RANGING:
        {
            uhf_upd_send_uart_cmd(msg_id);
        }
        break;
        
        case UHF_RADIO_MSG_SET_CALLSIGN:
        {
            status = sdr_uhf_set_call_sign_req((s_radio_callsign_t *)(&tc_tm_data[0]));
            uhf_upd_send_uart_cmd(UHF_RADIO_MSG_SET_CALLSIGN);
        }
        break;

        case UHF_RADIO_MSG_GET_CALLSIGN:
        {
            uhf_upd_send_uart_cmd(UHF_RADIO_MSG_GET_CALLSIGN);
        }
        break;

        case UHF_BEACON_TX_ST:
        {
            DEBUG_CPRINT(("\n UHF_BEACON_TX_START request"));
            /* Function call to start OBC configured internal beacon timer */
            os_timer_start(uhf_beacon_timer, uhf_tmr_cfg.beacon_prd_tmr);
            comms_uhf_csw_rx_buf[TM_PLD_IDX] = 0;
            comms_uhf_tc_tm_rsp_hdlr(UHF_BEACON_TX_ST, 0);
        }
        break;
        
        case UHF_BEACON_TX_STOP:
        {
            DEBUG_CPRINT(("\n UHF_BEACON_TX_STOP received"));
            /* Function call to stop OBC configured internal beacon timer */
            os_timer_stop(uhf_beacon_timer);
            os_timer_start(uhf_beacon_enb_timer, uhf_tmr_cfg.beacon_enb_tmr);
            comms_uhf_csw_rx_buf[TM_PLD_IDX] = 0;
            comms_uhf_tc_tm_rsp_hdlr(UHF_BEACON_TX_STOP, 0);
        }
        break;
        
        case UHF_TM_PERIODIC_READ:
        {
            comms_uhf_health_report_tm();
        }
        break;

        default:
        {
            DEBUG_CPRINT(("\nDefault Msg id:%d ",msg_id));
        }
        break;
    }

    return state;
}

/**
 * @brief This API handle the comms finite states machine
 * 
 * Top-level handling function that runs the UHF state machine.
 * Calls the current state's handler function.
 */
uint8_t comms_uhf_fsm_hdlr_fn(uint8_t state,uint16_t msg_id, void *payload)
{
    return(comms_uhf_fsm_hdlr[state](msg_id,payload));
}

/**
 * @brief This function monitor and report the uhf health metrics
 * 
 * Transmits a health report telemetry packet containing 
 * UHF status information.
 */
void comms_uhf_health_report_tm(void)
{
    uhf_tc_tm_id = UHF_RADIO_MSG_GET_TELEM;
    uhf_upd_send_uart_cmd(UHF_RADIO_MSG_GET_TELEM);
    uhf_hk_upd_id++;
    if(uhf_hk_upd_id == PERI_UHF_HK_SYNC_ID)
    {
        uhf_hk_upd_id = 0;
        is_uhf_hk_upd_fill = 1;
    }
    os_timer_start(uhf_tm_periodic_read, uhf_tmr_cfg.uhf_tm_read_tmr);
}


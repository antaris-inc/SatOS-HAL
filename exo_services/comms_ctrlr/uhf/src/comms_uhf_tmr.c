/**
 * @file comms_uhf_tmr.c
 *
 * @brief This file has the UHF driver FSM implementation and the relevant
 * functions
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

#include "comms_uhf_tmr.h"
#include "comms_uhf_intf.h"
#include "exo_common.h"
#include "comms_uhf_ipc.h"
#include "exo_io_al_sos_timer.h"
#include "comms_uhf_init.h"
#include "exo_tctm_ipc.h"

uint32_t  uhf_rep_cnt = 0; ///< UHF reponse count
uint8_t   uhf_cmd_rsp_cnt = 0; ///< UHF command response count

extern s_sdr_tmr_cfg  uhf_tmr_cfg; ///< SDR UHF timer configuration

extern uint8_t  beacon_en; // Beacon enable status

os_timer_handle_ptr uhf_tm_periodic_read; ///< Timer used for tm store Periodicity Timer

os_timer_handle_ptr uhf_beacon_timer; ///< Timer used for periodic transmission of Beacon signal

os_timer_handle_ptr uhf_beacon_enb_timer; ///< Timer used for enable transmission of Beacon signal

os_timer_handle_ptr uhf_beacon_rep_timer; ///< Timer used for enable repition of Beacon signal

/**
 * @brief This function initializes the timers required for UHF communication.
 * 
 */
int8_t comms_uhf_timer_init(void)
{
    uint64_t time_diff = 0, epoch_time = 0;
    time_diff=time_diff;
    epoch_time=epoch_time;

    /** Timer creation for Beacon enable and periodic beacon transmission **/
    os_timer_create(&uhf_beacon_timer ,"uhf_beacon_timer",ONESHOT,(ral_timer_cbfunc_t)uhf_beacon_timer_exp_cb,NULL);

    /** Timer creation for Beacon enable and periodic beacon transmission **/
    os_timer_create(&uhf_beacon_rep_timer ,"uhf_beacon_rep_timer",ONESHOT,(ral_timer_cbfunc_t)uhf_beacon_rep_timer_cb,NULL);

    /** Timer creation for Beacon enable and periodic beacon transmission **/
    os_timer_create(&uhf_beacon_enb_timer ,"uhf_beacon_enb_timer",ONESHOT,(ral_timer_cbfunc_t)uhf_beacon_enb_timer_cb,NULL);

    /** Timer creation for UHF Periodic read of telemetry or house keeping information for RSSI tracking and TM storage */
    os_timer_create(&uhf_tm_periodic_read ,"uhf_tm_periodic_read",ONESHOT,(ral_timer_cbfunc_t)uhf_tm_periodic_read_cb,NULL);

    DEBUG_CPRINT(("\nbeacon enabled started at OBC UHF CFG %d", uhf_tmr_cfg.beacon_enb_tmr ));
    os_timer_start(uhf_beacon_enb_timer,uhf_tmr_cfg.beacon_enb_tmr);

    DEBUG_CPRINT(("\nperiodic tm started at OBC UHF CFG %d", uhf_tmr_cfg.uhf_tm_read_tmr ));
    os_timer_start(uhf_tm_periodic_read, uhf_tmr_cfg.uhf_tm_read_tmr);

    return 0;
}

/**
 * @brief This function handle the timer expiry of initial LEOP synchronization timer
 * Callback function for UHF beacon timer expiration
 * 
 * This function is called when the periodic timer for sending 
 * UHF beacons expires. It would handle sending the next beacon
 * message.
 */
void uhf_beacon_timer_exp_cb(void)
{
    uhf_send_ipc(UHF_TX_PERIODIC_BEACON_TMR_EXP,COMMS_UHF_CTLR);
}

/**
 * @brief call back function at short duration expiry
 * pass fsm state via IPC
 *
 */
void uhf_beacon_rep_timer_cb(void)
{
    DEBUG_CPRINT(("UHF: Beacon rep timer %u started %u cnt%u\n",uhf_tmr_cfg.beacon_rep_tmr,\
                 uhf_rep_cnt,uhf_tmr_cfg.tx_data_rep_cnt));

    uhf_rep_cnt++;

    if(uhf_rep_cnt <= uhf_tmr_cfg.tx_data_rep_cnt)
    {
        uhf_send_ipc(UHF_REP_TMR_EXP,COMMS_UHF_CTLR);
    }
    else
    {
        uhf_rep_cnt = 0;
    }
}


/**
 * @brief call back function at short duration expiry
 * pass fsm state via IPC
 *
 * Callback function for UHF beacon enable timer
 * 
 * This function is called when the timer for enabling UHF beacon
 * transmission expires. It would handle enabling periodic sending
 * of beacon messages. 
 * 
 */
void uhf_beacon_enb_timer_cb(void)
{
    os_timer_start(uhf_beacon_timer,uhf_tmr_cfg.beacon_prd_tmr);
    DEBUG_CPRINT(("UHF: Beacon enable timer %d started",uhf_tmr_cfg.beacon_prd_tmr));
}



/**
 * @brief This function is the callback function for the UHF RX sync periodic timer
 *        This sync will be used to store parameter for every 2mins
 * Callback function for periodic UHF TM read
 * 
 * This function is called periodically to read UHF telemetry data.
 * It would handle collecting and processing telemetry data.
 */
void uhf_tm_periodic_read_cb(void)
{
    uhf_send_ipc(UHF_TM_PERIODIC_READ,COMMS_UHF_CTLR);
} 


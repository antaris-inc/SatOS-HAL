/**
 * @file comms_uhf_intf.c
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

#include "sm_api.h"
#include "exo_common.h"
#include "comms_uhf_intf.h"
#include "comms_uhf_ipc.h"
#include "exo_io_al_sos_timer.h"
#include <stdio.h>
#include"comms_uhf_main.h"
#include"comms_uhf_sim.h"
#include"comms_uhf_init.h"
#include "exo_tctm_ipc.h"

s_sdr_tmr_cfg  uhf_tmr_cfg; ///< SDR timer structure decelaration

extern uint8_t  comms_uhf_csw_rx_buf[512]; // UHF controller receive buffer

extern os_timer_handle_ptr uhf_tm_periodic_read; ///< Timer used for tm store Periodicity Timer

extern os_timer_handle_ptr uhf_beacon_timer; ///< Timer used for periodic transmission of Beacon signal

extern os_timer_handle_ptr uhf_beacon_enb_timer; ///< Timer used for enable transmission of Beacon signal


/**
 * @brief Get current UHF state
 * 
 */
uint8_t uhf_get_state(void)
{
    return PWR_ON;
}


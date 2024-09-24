/**
 * @file comms_uhf_tmr.h
 *
 * @brief This file has the control blocks, enumeration and function
 * prototypes of SDR control layer of UHF module
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

#ifndef COMMS_UHF_TMR_H
#define COMMS_UHF_TMR_H

#include "comms_uhf_main.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize UHF communication timers
 *
 * This function initializes the timers required for UHF communication.
 *
 * @return Result of timer initialization (0 = success)
 */
int8_t comms_uhf_timer_init(void);


/**
 * @brief This function handle the timer expiry of initial LEOP
 * synchronization timer Callback function for UHF beacon timer expiration
 *
 * This function is called when the periodic timer for sending
 * UHF beacons expires. It would handle sending the next beacon
 * message.
 */
void uhf_beacon_timer_exp_cb(void);

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
void uhf_beacon_enb_timer_cb(void);

/**
 * @brief This function is the callback function for the UHF RX
 * sync periodic timer
 *        This sync will be used to store parameter for every 2mins
 * Callback function for periodic UHF TM read
 *
 * This function is called periodically to read UHF telemetry data.
 * It would handle collecting and processing telemetry data.
 */
void uhf_tm_periodic_read_cb(void);

/**
 * @brief call back function at short duration expiry
 * pass fsm state via IPC
 *
 */
void uhf_beacon_rep_timer_cb(void);


#ifdef __cplusplus
}
#endif
#endif /*COMMS_UHF_TMR_H */

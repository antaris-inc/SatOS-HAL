/**
 * @file comms_uhf_main.h
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

#ifndef COMMS_UHF_UHF_MAIN_H
#define COMMS_UHF_UHF_MAIN_H

#include "exo_osal.h"
#include "exo_ral_cmn.h"
#include "exo_ral_mem_management.h"
#include "exo_types.h"

typedef float f32;
typedef double f64;

#ifdef __cplusplus
extern "C" {
#endif

#define BCON_MSG_SZ             12 ///< Beacon message size
#define PERI_UHF_HK_SYNC_ID     32 ///< UHF sync ID
///< UHF IPC read error
#define  COMMS_UHF_UHF_IPC_READ_ERROR               -20 ///< UHF IPC read error
#define  COMMS_UHF_UHF_IPC_WRITE_ERROR              -21 ///< UHF IPC write error
#define  COMMS_UHF_UHF_INVALID_COMMAND              -10 ///< UHF invalid command
#define  COMMS_UHF_UHF_NULL_PTR                     -1 ///< UHF null pointer
#define  COMMS_UHF_OPERATION_SUCCESS                 1 ///< UHF operation success
#define  COMMS_UHF_IPC_OK                            2 ///< UHF IPC ok

///COMMS UHF command macro's
#define UHF_ADC_NUM_CHANNELS   10 ///< UHF ADCS number of channels
#define UHF_MAX_PLD            251 ///< UHF maximum payload
#define UHF_CMD_REB_TIMER      300 ///< UHF command rebace  timer
#define UHF_CMD_TIM_OUT_TIMER  1000 ///< UHF command time out
#define UHF_CMD_RESEND_TIMER   2000 ///< UHF command resend timer

/**
 * @brief  comms UHF functions in enum definition
 */
typedef enum
{
    COMMS_UHF_TC_HANDLER,       /*!< UHF TC handler */
    COMMS_UHF_MAX_NUM_STATE,    /*!< UHF Max state */
}e_comms_uhf_state;


/**
 * @brief Beacon UTC GPS
 */
typedef struct __attribute__((packed)) 
{
    uint8 bcon_msg[BCON_MSG_SZ]; /*!< Beacon messgae */
    uint64_t utc_time;        /*!< UTC time */
}s_sdr_bcon_utc;

/**
 * @brief Beacon UTC GPS structure definition
 */
typedef struct __attribute__((packed)) 
{
    s_sdr_bcon_utc bcon_utc; /*!< Beacon UTC */
}s_sdr_beacon_pld;

/**
 * @brief SDR timer configuration structure definition
 */
typedef struct __attribute__((packed)) 
{
    uint32 beacon_enb_tmr;   /*!< Beacon enable timer */
    uint32 beacon_prd_tmr;   /*!< Beacon periodic timer */
    uint32 beacon_rep_tmr;   /*!< Beacon repetition timer */
    uint32 tx_data_rep_cnt;   /*!< Beacon repetition count */
    uint32 uhf_tm_read_tmr;   /*!< SDR TM read timer */
}s_sdr_tmr_cfg;

/**
 * @brief This function create the COMMS state and event threads
 *
 * @return Thread status
 */
int32_t comms_uhf_csw_init(void);

/**
 * @brief This function step-by-step process the COMMS states to the help
 *  of event thread request
 *
 * @brief CSW main task
 *
 * This task handles the UHF command and software process.
 *
 * @param[in] param Task parameter (unused)
 */
void comms_uhf_csw_main(void *param);

/**
 * @brief This API handle the comms finite states machine
 *
 * Top-level handling function that runs the UHF state machine.
 * Calls the current state's handler function.
 *
 * @param state   : current state
 * @param msg_id  : Identity of state
 * @param payload : pointer to payload
 *
 */
uint8_t comms_uhf_fsm_hdlr_fn(uint8_t state,uint16_t msg_id, void *payload);

/**
 * @brief This function handle UHF TC messages
 *
 * This handler function implements the TC handling
 * for the UHF communication system and timer expiry events
 * @param msg_id  : Identity of message
 * @param payload : Pointer to payload
 * @return Next state for the UHF FSM
 */
uint8_t comms_uhf_tc_hdlr(uint16_t msg_id, void *payload);

/**
 * @brief This function monitor and report the uhf health metrics
 *
 * Transmits a health report telemetry packet containing
 * UHF status information.
 */
void comms_uhf_health_report_tm(void);

#ifdef __cplusplus
}
#endif

#endif /*COMMS_UHF_MAIN_H */

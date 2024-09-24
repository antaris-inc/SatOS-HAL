/**
 * @file comms_uhf_main.c
 *
 * @brief This file has the UHF driver thread functions and other main
 * functions for UHF control
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
#include <math.h>
#include "sm_api.h"
#include "comms_uhf_sim.h"
#include "comms_uhf_csp.h"
#include "comms_uhf_ipc.h"
#include "comms_uhf_main.h"
#include "exo_osal.h"
#include "exo_ral_cmn.h"
#include "exo_common.h"
#include "comms_uhf_init.h"
#include "comms_uhf_csp.h"
#include "exo_io_al_rtc_common.h"
#include "exo_io_al_sos_timer.h"
#include "exo_tctm_ipc.h"

extern uint8_t  sch_gs_contact; // Flag denotes the scheduler based ground pass window status

extern volatile uint8_t  flight_mode; // Flag used for discrimating actual flight SW and devlopment mode SW

extern uint8_t  comms_uhf_csw_rx_buf[512]; // UHF command and software receive buffer

sys_time_date_s   tim_get_u_m; ///< system time and date

uint8_t  uhf_tc_cmd_id = 0; ///< UHF telemetry and command message ID

/**
 * @brief This function step-by-step process the COMMS states to the help
 *  of event thread request
 *
 * @brief CSW main task
 */
void comms_uhf_csw_main(void *param)
{
    int8_t status = COMMS_UHF_IPC_OK;
    /* The below line is the fix for the warning "variable set but not used"
     * Note to developer : Can be removed if needed
     */
    status = status;

    uint8_t state;
    e_sm_sts sm_status;

    os_itc_msg_handle_t comms_uhf_csw_recv_msg;///< COMMS state receive message

    comms_uhf_init_uhf_cfg();

    sm_status = sm_alloc(COMMS_UHF_FSM, COMMS_UHF_MAX_NUM_STATE);

    if(SM_OK == sm_status)
    {
        state = COMMS_UHF_TC_HANDLER;

        sm_set_state(COMMS_UHF_FSM, state);

        while(1)
        {
            /** UHF driver IPC receive */
            status = os_itc_msg_rcv(COMMS_UHF_CTLR, &comms_uhf_csw_recv_msg, os_wait_forever);

            /** Invoke UHF driver FSM */
            state = comms_uhf_fsm_hdlr_fn(state,comms_uhf_csw_recv_msg.Msg_id,comms_uhf_csw_recv_msg.pld.pld_ptr);

            /** Update UHF driver state */
            sm_set_state(COMMS_UHF_FSM, state);

            /** Freeing of payload pointer */
            if(NULL!=comms_uhf_csw_recv_msg.pld.pld_ptr)
            {
                os_free(comms_uhf_csw_recv_msg.pld.pld_ptr);
                comms_uhf_csw_recv_msg.pld.pld_ptr = NULL;
            }
        }
    }
    /** Freeing memory of UHF driver FSM FW */
    sm_status = sm_free(COMMS_UHF_FSM);
}

/**
 * @brief This function create the COMMS state and event threads
 *
 * @brief Initialize UHF CSW module
 * 
 * Performs initialization of data structures and hardware
 * for the UHF command and software module.
 * 
 * @return Result of initialization
 */
int32_t comms_uhf_csw_init(void)
{
    os_status_t status;

    /** Thread creation of UHF driver main thread */
    status = os_thread_create(COMMS_UHF_CTLR,
            T_COMMS_UHF_STACK_SIZE,  //TODO stack size need to be optimized
            P_COMMS_UHF_CTLR,
            "comms_uhf_thread",
            comms_uhf_csw_main,
            NULL,
            NULL,
            NULL);

    return status;
}

/**
 * @brief This function is the callback function for the UHF rx sync periodic timer
 *        This sync will be used to store parameter for every 2mins
 * @brief UHF telemetry storage callback
 * 
 * Callback function that is called periodically to store
 * UHF telemetry data.
 */
void uhf_tm_periodic_stor_cb(void)
{
    uhf_send_ipc(UHF_TM_PERIODIC_READ, COMMS_UHF_CTLR);
}

/**
 * @brief This function deletes the UHF queue and release its memory
 * @brief Suspend UHF communications
 * 
 * This function suspends UHF communication operation
 * when the system enters low power mode.
 * 
 * @return Result of suspend operation
 */
os_status_t comms_uhf_suspend(void)
{
    os_status_t status;
    status = os_thread_suspend(COMMS_UHF_CTLR);
    return status;
}

/**
 * @brief This functionalities resumes the UHF thread
 * 
 * @brief Resume UHF communications
 * 
 * This function resumes UHF communication operation
 * when the system wakes from low power mode.
 * 
 * @return Result of resume operation
 */
os_status_t comms_uhf_resume(void)
{
    os_status_t status;
    status = os_thread_resume(COMMS_UHF_CTLR);
    return status;
}

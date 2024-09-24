/**
 * @file comms_uhf_ipc.c
 *
 * @brief This file has the functions related to IPC message encode/decode
 *        for IPCs to communicate with TC-TM manager, OBC and other SW layers
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
#include "comms_uhf_ipc.h"
#include "exo_common.h"
#include "exo_tctm_ipc.h"

/** Extended variables **/
extern s_sdr_tmr_cfg  uhf_tmr_cfg; // UHF timer configuration
extern uint16_t  uhf_tc_tm_id; // UHF TCTM ID
extern uint8_t  uhf_radio_id; // UHF radio ID
extern uint16_t  uhf_tc_seq_no; // UHF TC sequence number

extern os_timer_handle_ptr uhf_beacon_rep_timer; // Timer used for enable repition of Beacon signal

/** Global variables **/
uint32_t  uhf_beacon_seq_num = 0; ///< UHF beacon sequence number
uint8_t  comms_uhf_csw_rx_buf[512] = {0}; ///< UHF controller RX buffer

/**
 * @brief This function handles the comms telecommand, telemetry set response
 *
 * @brief Handle set TC/TM response
 * 
 * @param msg_id Message ID
 * @param status Response status 
 * @param tc_tm_data Pointer to response data
 */
void comms_uhf_tc_tm_set_rsp_hdlr(uint16_t msg_id, int32_t status, uint8_t *tc_tm_data)
{
    uint8_t *pld = NULL;

    UNUSED(tc_tm_data);
    os_itc_msg_handle_t comms_uhf_msg;

    //Init IPC
    comms_uhf_msg.src_entity= COMMS_UHF_CTLR;

    comms_uhf_msg.pld.pld_ptr = (uint8_t *)os_malloc(5);

    pld = comms_uhf_msg.pld.pld_ptr;

    pld[TM_PLD_IDX] = status;

    comms_uhf_msg.Msg_id = msg_id;
    comms_uhf_msg.Msg_len = 1;

    pld[TM_ID_IDX] = comms_uhf_msg.Msg_id;
    pld[TM_LEN_IDX] = comms_uhf_msg.Msg_len;

    status = os_itc_msg_send(&comms_uhf_msg,COMMS_UHF_TX,os_send_itc_wait);
    DEBUG_CPRINT(("[UHF] TM pld set response sent"));

    uhf_tc_tm_id = 0;
}

/**
 * @brief This function handles the comms telecommand, telemetry response
 * @brief Handle get TM storage response
 */
void comms_uhf_tm_stor_get_rsp_hdlr(uint16_t msg_id, uint8_t *tm_pld, uint16_t size)
{
    uint8_t *pld = NULL;

    os_itc_msg_handle_t uhf_tm_stor_ipc;             ///< COMMS state transmit message

    //Init IPC
    uhf_tm_stor_ipc.src_entity= COMMS_UHF_CTLR;

    uhf_tm_stor_ipc.pld.pld_ptr = (uint8_t *)os_malloc(size+5);

    pld = uhf_tm_stor_ipc.pld.pld_ptr;

    uhf_tm_stor_ipc.Msg_id = msg_id;
    uhf_tm_stor_ipc.Msg_len = size;

    os_memcpy(&pld,tm_pld, size);

    DEBUG_CPRINT(("[UHF] TM pld response sent %d",size));
    os_itc_msg_send(&uhf_tm_stor_ipc, COMMS_UHF_TX, os_send_itc_wait);
}


/**
 * @brief This function handles the comms telecommand, telemetry get response
 * @brief Handle get TC/TM response
 */
void comms_uhf_tc_tm_get_rsp_hdlr(uint16_t msg_id,int32_t status, uint8_t *tc_tm_data, uint16_t size)
{
    os_itc_msg_handle_t comms_uhf_msg;

    //Init IPC
    comms_uhf_msg.src_entity= COMMS_UHF_CTLR;

    //Update TC_ID and TC Length
    os_memcpy(comms_uhf_csw_rx_buf, &msg_id, sizeof(uint16_t));
    os_memcpy(&comms_uhf_csw_rx_buf[TM_LEN_IDX], &size, sizeof(uint16_t));

    comms_uhf_msg.Msg_id = msg_id;
    comms_uhf_msg.Msg_len = size;

    comms_uhf_msg.pld.pld_ptr = (uint8_t *)os_malloc(size + 5);
    os_memcpy(comms_uhf_msg.pld.pld_ptr,comms_uhf_csw_rx_buf, size+4);

    status = os_itc_msg_send(&comms_uhf_msg, COMMS_UHF_TX, os_send_itc_wait);

    uhf_tc_tm_id = 0;
}

/**
 * @brief This function handles the comms telecommand, telemetry response
 * @brief Handle generic TC/TM response
 */
void comms_uhf_tc_tm_rsp_hdlr(uint16_t msg_id, uint16_t size)
{
    os_itc_msg_handle_t comms_uhf_msg;

    //Init IPC
    comms_uhf_msg.src_entity= COMMS_UHF_CTLR;

    comms_uhf_msg.Msg_id = msg_id;
    comms_uhf_msg.Msg_len = size+4;

    DEBUG_CPRINT(("\n\r[UHF] TM size %d",size));
    comms_uhf_msg.pld.pld_ptr = (uint8_t *)os_malloc(size + 4);

    os_memcpy(comms_uhf_csw_rx_buf,&comms_uhf_msg.Msg_id,sizeof(comms_uhf_msg.Msg_id));
    os_memcpy(&comms_uhf_csw_rx_buf[TM_LEN_IDX],&comms_uhf_msg.Msg_len,sizeof(comms_uhf_msg.Msg_len));
    os_memcpy(comms_uhf_msg.pld.pld_ptr,comms_uhf_csw_rx_buf, size+4);

    os_itc_msg_send(&comms_uhf_msg, COMMS_UHF_TX, os_send_itc_wait);
    uhf_tc_tm_id = 0;
}

/**
 * @brief Abstracted API for COMMS layer that sends message payload
 *   to destination thread using os IPC functionalities
 */
void uhf_send_ipc(uint16_t msg_id, uint16_t dest)
{
    os_itc_msg_handle_t comms_uhf_msg;
    comms_uhf_msg.Msg_id = msg_id;
    comms_uhf_msg.src_entity = COMMS_UHF_CTLR;

    comms_uhf_msg.pld.pld_ptr = NULL;

    os_itc_msg_send(&comms_uhf_msg, dest, os_send_itc_wait);
}

/**
 * @brief This API for UHF layer that sends message payload
 * to destination thread using os IPC functionalities
 * @brief Send IPC payload over UHF
 */
void uhf_send_ipc_pld(uint16_t msg_id, uint16_t dest, uint16_t pld_size, uint8_t *pld_ptr)
{
    os_itc_msg_handle_t comms_uhf_msg;
    os_memset(&comms_uhf_msg, 0, sizeof(os_itc_msg_handle_t));
    comms_uhf_msg.Msg_id = msg_id;
    comms_uhf_msg.src_entity = COMMS_UHF_CTLR;

    comms_uhf_msg.pld.pld_ptr = (uint8_t *)os_malloc(pld_size);

    os_memcpy(comms_uhf_msg.pld.pld_ptr,pld_ptr, pld_size);

    os_itc_msg_send(&comms_uhf_msg, dest, os_send_itc_wait);
}

/**
 * @brief This function handles the comms telecommand, telemetry get response
 * @brief Transmit UHF beacon
 */
void comms_uhf_beacon_tx(uint8_t *beacon_data, uint16_t size)
{
    os_itc_msg_handle_t comms_uhf_msg;
    uint8_t *pld = NULL;
    os_memset(&comms_uhf_msg, 0, sizeof(os_itc_msg_handle_t));

    uhf_beacon_seq_num++;

    //Init IPC
    comms_uhf_msg.src_entity= COMMS_UHF_CTLR;

    comms_uhf_msg.Msg_id = UHF_BEACON_DATA;
    comms_uhf_msg.Msg_len = size+4;

    comms_uhf_msg.pld.pld_ptr = (uint8_t *)os_malloc(size + 
            sizeof(comms_uhf_msg.Msg_id) + sizeof(comms_uhf_msg.Msg_id) + 5);
    pld = comms_uhf_msg.pld.pld_ptr;

    os_memcpy(pld,&comms_uhf_msg.Msg_id,sizeof(comms_uhf_msg.Msg_id));
    pld = pld + sizeof(comms_uhf_msg.Msg_id);

    os_memcpy(pld,&comms_uhf_msg.Msg_len,sizeof(comms_uhf_msg.Msg_len));
    pld = pld + sizeof(comms_uhf_msg.Msg_len);

    os_memcpy(pld,beacon_data,sizeof(s_sdr_beacon_pld)+4);
    DEBUG_CPRINT(("\nUHF BEACON PLD SEND\n"));

    os_itc_msg_send(&comms_uhf_msg, COMMS_UHF_TX, os_send_itc_wait);
    uhf_tc_tm_id = 0;

    if(uhf_tmr_cfg.tx_data_rep_cnt)
    {
        os_timer_start(uhf_beacon_rep_timer,uhf_tmr_cfg.beacon_rep_tmr);
    }
}

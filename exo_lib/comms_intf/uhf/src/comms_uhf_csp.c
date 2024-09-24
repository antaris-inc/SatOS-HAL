/**
 * @file comms_uhf_csp.c
 *
 * @brief This file contains functions to used for sending and
 * receiving data through UART interface
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
#include "csp_endian.h"
#include "csp/interfaces/csp_if.h"
#include "csp/arch/csp_time.h"
#include "comms_uhf_main.h"
#include "comms_uhf_ipc.h"
#include "comms_uhf_csp.h"
#include "comms_uhf_sim.h"
#include "comms_uhf_init.h"
#include "errno.h"
#include "exo_common.h"
#include "csp_if_uhf.h"
#include <csp/csp.h>
#include "exo_io_al_sos_timer.h"
#include "exo_tctm_ipc.h"
#include "comms_uhf_intf.h"


#define DEFAULT_TIMEOUT 1000///< Default timeout value
uint8_t  tx_buff[UHF_MAX_PLD] = {0};///< TX buffer
uint8_t  uhf_rx_cmd_buff[UHF_MAX_PAYLOAD+1] = {0};///< UHF RX command buffer
uint32_t  csp_uhf_data_count = 0;///< CSP UHF data count
extern uint8_t  uhf_tc_cmd_id;// UHF TC command ID
uint8_t  uhf_tc_len = 0;///< UHF TC length

extern uint8_t  comms_uhf_csw_rx_buf[512];// UHF CSW RX buffer

extern uint8_t  uhf_hk_upd_id;// UHF HK update ID
extern s_radio_callsign_t call_sign_cfg; // UHF call sign cfg
extern s_timespec_t set_time_cfg; // UHF set time cfg
extern s_msg_data_t write_page_cfg;// UHF write page cfg

uint16_t  uhf_tc_tm_id = 0;///< UHF TC TM ID
extern s_comms_uhf_tm  comms_uhf_tm;// UHF TM properties

extern s_sdr_beacon_pld uhf_beacon_data; // UHF beacon data

uint16_t  uhf_seq_num =0;///< UHF sequence number
uint16_t  uhf_data_seq_num =0;///< UHF data sequence number

/**
 * @brief This function is used for updating the CSP address of UHF radio
 * @brief Update the CSP port and address used for UHF communication.
 * 
 * This function updates the CSP port and address that will be used when
 * sending/receiving UHF packets over CSP.
 */
void comms_uhf_upd_port_addr(uint8_t *csp_tx_port,uint8_t *csp_tx_addr)
{
    *csp_tx_port = UHF_CSP_TX_DATA_PORT;
    *csp_tx_addr = UHF_UART_TX_ADDRESS;
}

/**
 * @brief This function is used for updating the CSP address of UHF radio simulation
 * @brief Update simulated CSP port and address for UHF.
 * 
 * In simulation mode, update the port and address used for UHF communication.
 */
void comms_uhf_sim_upd_port_addr(uint8_t *csp_tx_port,uint8_t *csp_tx_addr)
{
    *csp_tx_port = UHF_CSP_TX_DATA_PORT;
    *csp_tx_addr = UHF_UART_TX_ADDRESS;
}

/**
 * @brief This function updates the command ID.
 * @brief Send UHF radio command over UART.
 * 
 * Sends a UHF radio command to the UHF radio module over the UART interface.
 */
void uhf_upd_send_uart_cmd(uint8_t cmd_id)
{
    uint16_t len = 0;
    uhf_tc_cmd_id = cmd_id;
    if(PWR_ON == uhf_get_state())
    {
        len = sizeof(uhf_tc_cmd_id);
        os_memcpy(tx_buff,&uhf_tc_cmd_id,len);

        switch(cmd_id)
        {
            case UHF_BOOTLOADER_MSG_PING:
            {
            }
            break;

            case UHF_BOOTLOADER_MSG_WRITE_PAGE:
            {
                os_memcpy(&tx_buff[len],&write_page_cfg,(sizeof(s_msg_data_t)));
                len += sizeof(s_msg_data_t);
            }
            break;

            case UHF_BOOTLOADER_MSG_ERASE:
            {
            }
            break;

            case UHF_RADIO_MSG_REBOOT:
            {
            }
            break;

            case UHF_RADIO_MSG_GET_TIME:
            {
            }
            break;

            case UHF_RADIO_MSG_SET_TIME:
            {
                os_memcpy(&tx_buff[len],&set_time_cfg,(sizeof(s_timespec_t)));
                len += sizeof(s_timespec_t);
            }
            break;

            case UHF_RADIO_MSG_RANGING:
            {
            }
            break;
            case UHF_RADIO_MSG_GET_TELEM:
            {
            }
            break;

            case UHF_RADIO_MSG_GET_CALLSIGN:
            {
            }
            break;

            case UHF_RADIO_MSG_SET_CALLSIGN:
            {
                os_memcpy(&tx_buff[len],&call_sign_cfg,(sizeof(s_radio_callsign_t)));
                len += sizeof(s_radio_callsign_t);
            }
            break;
        }

        DEBUG_CPRINT(("[UHF] TX length: %d",len));

#if !defined(LINUX_TEMP_PORT) || !defined(UHF_HW_BYPASS)
        uhf_csp_uart_cmd_tx(tx_buff, len);
#else
        uhf_sim_pack_cmd_rsp(cmd_id);
#endif

    }
    else
    { 
        DEBUG_CPRINT(("\nUHF_UPD_SEND_UART_CMD POWER_ON FAILS \n ")); 
    }


}

/**
 * @brief Send UHF received packet over UART. 
 * 
 * Sends a received UHF packet from the radio module to the host MCU over UART.
 * 
 * @param[in] frame Pointer to the received packet data. 
 * @param[in] uhf_packet_length Length of the received packet.
 */
void uhf_send_rx_uart_cmd(uint8_t *frame,uint8_t uhf_packet_length)
{
    uhf_send_ipc_pld(UHF_UART_CMD_RSP,COMMS_UHF_CTLR,uhf_packet_length,frame);
}


/**
 * @brief Process UHF command response from UART.
 * 
 * Parses a UHF radio command response received over UART.
 * 
 * @param[in] pld Pointer to the UART response payload data.
 * @return UHF command response status.
 */
uint8_t uhf_proc_uart_cmd_rsp(uint8_t *pld)
{
    s_comms_uhf_uart_data *uhf_rx_data = (s_comms_uhf_uart_data *)pld;


    DEBUG_CPRINT(("\n\r [UHF] Command response : %x, length: %d, TCTM_ID:%d",uhf_rx_data->header.command,uhf_rx_data->length,uhf_tc_tm_id));

    switch(uhf_rx_data->header.command)
    {
        case UHF_RADIO_MSG_CALLSIGN:
        {
            os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);

            comms_uhf_tc_tm_rsp_hdlr(UHF_RADIO_MSG_CALLSIGN, uhf_rx_data->length);
        }
        break;

        case UHF_CMN_MSG_ASCII:
        {
            //os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);
            int8 res;

            uint8 beacon_init_str[] = {"2269170101000001405265626f6f7420436f6d6d656e63656421"};
            res = memcmp(beacon_init_str, uhf_rx_data->data,18);
            if (!res)
            {

                DEBUG_CPRINT(("The UHF Board Reset the value is %c",beacon_init_str[16]));
            }
            DEBUG_CPRINT(("\n\r [UHF] ASCII message is received == %s\n ",uhf_rx_data->data));
        }

        case UHF_BOOTLOADER_MSG_ACK:
        {
            if((uhf_tc_cmd_id == UHF_BOOTLOADER_MSG_ERASE) || (uhf_tc_cmd_id == UHF_BOOTLOADER_MSG_PING) ||\
                   uhf_tc_cmd_id == UHF_BOOTLOADER_MSG_WRITE_PAGE )
            {
                os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);
                comms_uhf_tc_tm_rsp_hdlr(uhf_tc_cmd_id, uhf_rx_data->length);
            }
            else
            {
                comms_uhf_csw_rx_buf[TM_PLD_IDX] = 0;
                os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);
            }
        }
        break;

        case UHF_BOOTLOADER_MSG_NACK:
        {
            comms_uhf_csw_rx_buf[TM_PLD_IDX] = 1;
            if((uhf_tc_cmd_id == UHF_BOOTLOADER_MSG_ERASE) || (uhf_tc_cmd_id == UHF_BOOTLOADER_MSG_PING))
            {
                comms_uhf_tc_tm_rsp_hdlr(uhf_tc_cmd_id, uhf_rx_data->length);
            }
            else
            {
                os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);
            }
        }
        break;

        case UHF_CMN_MSG_ACK:
        {
            comms_uhf_csw_rx_buf[TM_PLD_IDX] = 0;
            if(uhf_tc_cmd_id == UHF_RADIO_MSG_REBOOT || uhf_tc_cmd_id == UHF_RADIO_MSG_SET_TIME ||\
                uhf_tc_cmd_id == UHF_RADIO_MSG_SET_CALLSIGN) 
            {
                comms_uhf_tc_tm_rsp_hdlr(uhf_tc_cmd_id, uhf_rx_data->length);
            }
            else
            {
                os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);
            }
        }
        break;
        
        case UHF_CMN_MSG_NACK:
        {
            comms_uhf_csw_rx_buf[TM_PLD_IDX] = 1;
            if(uhf_tc_cmd_id == UHF_RADIO_MSG_REBOOT || uhf_tc_cmd_id == UHF_RADIO_MSG_SET_TIME ||\
                uhf_tc_cmd_id == UHF_RADIO_MSG_SET_CALLSIGN)
            {
                comms_uhf_tc_tm_rsp_hdlr(uhf_tc_cmd_id, uhf_rx_data->length);
            }
            else
            {
                os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);
            }
        }
        break;

        case UHF_RADIO_MSG_RANGING_ACK:
        {
            os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);
            comms_uhf_tc_tm_rsp_hdlr(UHF_RADIO_MSG_RANGING_ACK, uhf_rx_data->length);
        }
        break;


        case UHF_RADIO_MSG_TELEM:
        {
            s_comms_uhf_tm *tm_info = (s_comms_uhf_tm *)uhf_rx_data->data;

            /** TODO prints */
            tm_info = tm_info;

            if(uhf_tc_tm_id == UHF_RADIO_MSG_GET_TELEM)
            {
                os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);
                comms_uhf_tc_tm_rsp_hdlr(UHF_RADIO_MSG_TELEM, uhf_rx_data->length);
            }
        }
        break;

        case UHF_RADIO_MSG_GET_CALLSIGN:
        {
            os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);
            comms_uhf_tc_tm_rsp_hdlr(uhf_tc_tm_id, uhf_rx_data->length);
        }
        break;

        case UHF_RADIO_MSG_SET_TIME:
        {
            if(UHF_RADIO_MSG_GET_TIME == uhf_tc_tm_id)
            {
                comms_uhf_csw_rx_buf[TM_PLD_IDX] = 1;
                os_memcpy(&comms_uhf_csw_rx_buf[TM_PLD_IDX],uhf_rx_data->data,uhf_rx_data->length);
                comms_uhf_tc_tm_rsp_hdlr(UHF_RADIO_MSG_SET_TIME, uhf_rx_data->length);
            }
            else
            {
                DEBUG_CPRINT(("\nUHF_UART_CMD_RSP_GET_TIME FAILS\n "));
            }
        }
        break;
    }
    DEBUG_CPRINT(("\n\r[UHF] TM length: %d",uhf_rx_data->length));
    uhf_tc_tm_id = 0;

    return uhf_rx_data->header.command;
}

/**
 * @brief This function is used for packing the UART data to send via UHF module
 * @brief Pack CSP packet into UHF UART frame format.
 * 
 * Takes a CSP packet and packs it into the UHF UART frame format.
 */
void uhf_pack_uart_csp_frame(csp_packet_t *packet, uint8_t *frame_buff)
{
    uint16_t length = 0;
    uint32_t id;
    s_comms_uhf_data *uhf_data = (s_comms_uhf_data *)frame_buff;

    uhf_data->header.sync1 = UHF_START_BYTE_0;
    uhf_data->header.sync2 = UHF_START_BYTE_1;
    uhf_data->header.length = packet->length + UHF_HEADER_SIZE + CSP_HEADER_LENGTH;
    uhf_data->header.hwid = 15;
    uhf_data->header.seqnum = uhf_data_seq_num;
    uhf_data->header.system = 0;
    uhf_data->header.command = 0;//uhf_tc_cmd_id;

    uhf_data_seq_num = (uhf_data_seq_num + 1) & 0xFFFF;

    id = csp_hton32(packet->id.ext);

    memcpy(&uhf_data->data[length], &id, sizeof(id));
    length += sizeof(id);

    memcpy(&uhf_data->data[length], packet->data, packet->length);
    length += packet->length;

    //    uhf_tc_cmd_id = 0;

    int i = 0;
    DEBUG_CPRINT(("\nUHF CSP pack: packet_len:%d, p_packet: ",uhf_data->header.length));
    for(i=0;i<uhf_data->header.length+3;i++)
    {
        DEBUG_CPRINT(("%x ",frame_buff[i]));
    }

    DEBUG_CPRINT(("\n\r"));
    DEBUG_CPRINT(("\n\r"));

}

/**
 * @brief This function is used for unpacking the UART data to send via UHF module
 * @brief Unpack UHF UART frame into CSP packet.
 * 
 * Takes a UHF UART frame and unpacks it into a CSP packet structure.
 */
void uhf_unpack_uart_csp_frame(csp_packet_t *packet, uint8_t *frame_buff)
{
    uint16_t length = 0;
    uint32_t id;
    s_comms_uhf_data *uhf_data = (s_comms_uhf_data *)frame_buff;

    if(uhf_data->header.length > 0)
    {
        length = uhf_data->header.length - UHF_HEADER_SIZE - CSP_HEADER_LENGTH;

        packet->length = length;

        length = 0;

        //if (!packet)
        //continue;

        /* Set packet ID */
        memcpy(&id, &uhf_data->data[length], sizeof(id));
        length += sizeof(id);
        packet->id.ext = csp_ntoh32(id);

        /* Copy received data into CSP buffer */
        memcpy(packet->data, &uhf_data->data[length], packet->length);

        int i = 0;
        DEBUG_CPRINT(("\nUHF CSP unpack: packet_len:%d, u_packet: ",uhf_data->header.length));
        for(i=0;i<uhf_data->header.length;i++)
        {
            DEBUG_CPRINT(("%x ",frame_buff[i]));
        }
        DEBUG_CPRINT(("\n\r"));
        DEBUG_CPRINT(("\n\r"));
    }
}

/**
 * @brief This function is used for packing the UART data to send via UHF module
 * @brief Pack CSP packet into generic UHF UART frame.
 * 
 * Packs a CSP packet into a generic UHF UART frame format.
 */
void uhf_pack_uart_frame(csp_packet_t *packet, uint8_t *frame_buff)
{
    s_comms_uhf_data *uhf_data = (s_comms_uhf_data *)frame_buff;

    if(packet->length > 0)
    {
        packet->length = packet->length - 1;

        uhf_data->header.sync1 = UHF_START_BYTE_0;
        uhf_data->header.sync2 = UHF_START_BYTE_1;
        uhf_data->header.length = packet->length + UHF_HEADER_SIZE;
        uhf_data->header.seqnum = uhf_seq_num;

        uhf_seq_num = (uhf_seq_num + 1) &0xFFFF;

        os_memcpy(&uhf_data->header.command,packet->data,sizeof(uhf_data->header.command));

        uhf_data->header.hwid = 1;//0xFFFF;
        uhf_data->header.system = 1;

        os_memcpy(&uhf_data->data[0], &packet->data[1], packet->length);

        int i = 0;
        DEBUG_CPRINT(("\n\rUHF HWID: %d",uhf_data->header.hwid));
        DEBUG_CPRINT(("\n\rUHF pack: packet_len:%d, p_packet: ",uhf_data->header.length));

        for(i=0;i<uhf_data->header.length+3;i++)
        {
            DEBUG_CPRINT(("%x ",frame_buff[i]));
        }

        DEBUG_CPRINT(("\n\r"));
        DEBUG_CPRINT(("\n\r"));


        DEBUG_CPRINT(("\n"));

    }
}

/**
 * @brief This function is used for unpacking the UART data to send via UHF module
 * @brief Unpack generic UHF UART frame into CSP packet.
 * 
 * Unpacks a generic UHF UART frame into a CSP packet structure.
 */
void uhf_unpack_uart_frame(csp_packet_t *packet, uint8_t *frame_buff)
{
    uint16_t length = 0;
    uint32_t id;
    s_comms_uhf_uart_data *uhf_data = (s_comms_uhf_uart_data *)frame_buff;
    if(uhf_data->length > (UHF_HEADER_SIZE + CSP_HEADER_LENGTH))
    {
        length = uhf_data->length - UHF_HEADER_SIZE - CSP_HEADER_LENGTH;

        packet->length = length;

        length = 0;

        //if (!packet)
        //continue;

        /* Set packet ID */
        memcpy(&id, &uhf_data->data[length], sizeof(id));
        length += sizeof(id);
        packet->id.ext = csp_ntoh32(id);

        /* Copy received data into CSP buffer */
        memcpy(packet->data, &uhf_data->data[length], packet->length);

        int i = 0;

        DEBUG_CPRINT(("\nUHF unpack: packet_len:%d, u_packet: ",uhf_data->length));
        for(i=0;i<uhf_data->length;i++)
        {
            DEBUG_CPRINT(("%x ",frame_buff[i]));
        }

        DEBUG_CPRINT(("\n\npacket->length:%d\r",packet->length));
        DEBUG_CPRINT(("\n\r"));
        DEBUG_CPRINT(("\n\r"));

        DEBUG_CPRINT(("\n"));
    }
}

/**
 * @brief This function is used for sending CSP ping for UHF Module
 * @brief Send UHF ping command.
 * 
 * Sends a ping command to the UHF radio module.
 */
void uhf_csp_ping(uint8_t *tc_cmd)
{
    uint8_t node;
    uint32_t size;
    uint32_t ping_count;
    uint32_t ping_time_out;
    uint32_t csp_ping_count = 0;
    int32_t result = 0;

    os_memcpy(&node,tc_cmd,1);
    os_memcpy(&size,&tc_cmd[1],4);
    os_memcpy(&ping_count,&tc_cmd[5],4);
    os_memcpy(&ping_time_out,&tc_cmd[9],4);

    /* Send ping to server, timeout 1000 mS, ping size 100 bytes */
    DEBUG_CPRINT(("\t\r\n Ping Start Time= "));
    csp_ping:
    result = csp_ping(node, ping_time_out, size, CSP_O_NONE);
    //DEBUG_CPRINT(("\t CSP PING address: %u, result %d [mS]", node, result));

    if(result > 0)
    {
        DEBUG_CPRINT(("\n\r CSP PING SUCCESS\n"));
    }
    else
    {
        DEBUG_CPRINT(("\n\r CSP PING FAILURE\n"));
    }

    csp_ping_count++;
    if(csp_ping_count < ping_count)
    {
        goto csp_ping;
    }
    DEBUG_CPRINT(("\n\r CSP PING TEST Complete\n"));
}

/**
 * @brief This function is used for sending CSP transmission data from the UHF
 * @brief Send CSP data over UHF.
 * 
 * Takes a CSP packet and transmits it over UHF.
 */
void uhf_csp_tx_data(void)
{
    /* Send data packet (string) to server */

    /* 1. Connect to host on 'UHF_UART_TX_ADDRESS', port UHF_CSP_TX_DATA_PORT with regular TCP-like protocol and 1000 ms timeout */
    csp_conn_t * conn = csp_connect(CSP_PRIO_NORM, UHF_UART_TX_ADDRESS , UHF_CSP_TX_DATA_PORT ,1000, CSP_O_NONE);

    /** Connection used for Space data transfer from UHF module */
    //csp_conn_t * conn = csp_connect(CSP_PRIO_NORM, 10, 11, 1000, CSP_O_NONE);
    if (conn == NULL) {
        /* Connect failed */
        DEBUG_CPRINT(("\r\n\rConnection failed\n"));
        return;
    }

    /* 2. Get packet buffer for message/data */
    csp_packet_t * packet = csp_buffer_get(100);
    if (packet == NULL) {
        /* Could not get buffer element */
        DEBUG_CPRINT(("\r\n\rFailed to get CSP buffer\n"));
        return;
    }

    /* 3. Copy data to packet */
    memcpy(packet->data, "Hello world ", 12);
    memcpy(packet->data + 12, &csp_uhf_data_count, 1);
    memset(packet->data + 13, 0, 1);
    csp_uhf_data_count++;

    /* 4. Set packet length */
    packet->length = (strlen((char *) packet->data) + 1); /* include the 0 termination */

    /* 5. Send packet */
    csp_send(conn, packet,0xFFFF);
    DEBUG_CPRINT(("\tPacket Sent - %s",packet->data));
    /* 6. Close connection */

    csp_close(conn);
}

/**
 * @brief Send UHF command over UART.
 * 
 * Sends a UHF radio command to the module over UART.
 */ 
int32_t uhf_csp_uart_cmd_tx(uint8_t* data, uint16_t len)
{
    csp_conn_t *conn;
    csp_packet_t *packet=NULL;
    size_t sent = 0 , datasize;
    size_t remain = 0;
    remain = remain;
    uint16_t mtu_size = UHF_MAX_PLD;

    conn = csp_connect(CSP_PRIO_NORM, UHF_CMD_TX_ADDRESS, UHF_CSP_TX_DATA_PORT , DEFAULT_TIMEOUT, CSP_O_NONE);
    if (!conn)
        return -ECONNREFUSED;

    remain = (len + mtu_size - 1) / mtu_size;

    while (sent < len) {
        if (len - sent > mtu_size)
            datasize = mtu_size;
        else
            datasize = len - sent;
        packet = csp_buffer_get(datasize);
        if (!packet) {
            csp_close(conn);
            return -ENOMEM;
        }

        memcpy(packet->data, &data[sent], datasize);
        packet->length = datasize;

        int i=0,j = 0;
        DEBUG_CPRINT(("UHF command data size is %d\n data: ", (uint16_t)datasize));

        for(i = sent; i<=datasize; i++)
        {
            DEBUG_CPRINT(("%x ",data[i]));
        }
        DEBUG_CPRINT(("\n UHF command packet->length is %d\r\n", packet->length));

        //DEBUG_CPRINT(("\n UHF command packet->id is %x\r\n", packet->id.ext));

        for(j = 0; j<=packet->length; j++)
        {
            DEBUG_CPRINT(("%x ",packet->data[j]));
        }/*
            packet[0] = 0;
            packet[1] = 0xc80101;
            packet[2] = 0;
            packet[3] = 0;
            packet[4] = 0;
            packet[5] = 0;
            packet[6] = 0;*/

        if (!csp_send(conn, packet, DEFAULT_TIMEOUT)) {
            csp_buffer_free(packet);
            csp_close(conn);
            return -EIO;
        }
        DEBUG_CPRINT(("UHF Command packet successfully sent \r\n"));
        sent += datasize;
    }

    csp_buffer_free(packet);

    csp_close(conn);

    return 0;
}

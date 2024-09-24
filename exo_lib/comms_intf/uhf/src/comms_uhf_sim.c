/**
 * @file comms_uhf_sim.c
 *
 * @brief This file has the functions of all UHF simulations
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
#include"comms_uhf_main.h"
#include"comms_uhf_sim.h"
#include"comms_uhf_rf_cfg.h"
#include"comms_uhf_csp.h"
#include"exo_tctm_ipc.h"


/**
 * @brief Pack UHF command response packet 
 * 
 * This function packs a UHF command response packet with the 
 * provided command ID.
 * 
 * The response packet format contains:
 * - Command ID
 * - Response payload
 * - CRC
 * 
 * The response payload is populated with dummy data.
 * CRC is calculated and set in the packet.
 * cmd_id
 * The packed response packet is written to the global RX buffer
 * for subsequent reading.
 */
void uhf_sim_pack_cmd_rsp(uint8_t cmd_id)
{
    uint8_t len = 0;
    uint8_t frame[UHF_MAX_PLD + 1] = {0};

    uint8_t rcvd_cmd_id = cmd_id;

    s_comms_uhf_uart_data *ptr = (s_comms_uhf_uart_data *)frame;

    if(cmd_id == UHF_BOOTLOADER_MSG_ERASE || cmd_id == UHF_BOOTLOADER_MSG_PING ||\
        cmd_id == UHF_RADIO_MSG_REBOOT  || cmd_id == UHF_RADIO_MSG_SET_TIME ||\
        cmd_id == UHF_RADIO_MSG_GET_CALLSIGN || cmd_id == UHF_RADIO_MSG_SET_CALLSIGN ||\
        cmd_id == UHF_BOOTLOADER_MSG_WRITE_PAGE)
    {
    }
    else
    {
        cmd_id +=1;
    }

    ptr->header.command = cmd_id;
    ptr->length = sizeof(cmd_id);

    DEBUG_CPRINT(("\n\r [UHF_SIM] TM cmd: %x",cmd_id));

    switch(cmd_id)
    {
        case UHF_RADIO_MSG_GET_CALLSIGN:
        {
            DEBUG_CPRINT(("\n\r [UHF_SIM] radio get callsign req\n "));
            ptr->header.command = UHF_RADIO_MSG_CALLSIGN;
            s_radio_callsign_t radio_callsign;

            for(uint16_t i =0; i<8 ; i++)
            {
                radio_callsign.callsign[i] = i+1;
            }
            os_memcpy(ptr->data,&radio_callsign,sizeof(s_radio_callsign_t));
            ptr->length = sizeof(radio_callsign);
        }
        break;
        
        case UHF_RADIO_MSG_SET_CALLSIGN:
        {
            DEBUG_CPRINT(("\n\r [UHF_SIM] radio set callsign req\n "));
            ptr->header.command = UHF_CMN_MSG_ACK;
        }
        break;

        case UHF_CMN_MSG_ASCII:
        {
        }
        break;

        case UHF_BOOTLOADER_MSG_ACK:
        {

        }
        break;

        case UHF_BOOTLOADER_MSG_NACK:
        {
        }
        break;

        case UHF_CMN_MSG_ACK:
        {
        }
        break;

        case UHF_RADIO_MSG_RANGING_ACK:
        {
            DEBUG_CPRINT(("\n\r [UHF_SIM] radio ranging req\n "));
            s_radio_ranging_ack_t rang_ack;
            rang_ack.ack_type = 1;
            rang_ack.ack_version = 1;
            os_memcpy(ptr->data,&rang_ack,sizeof(s_radio_ranging_ack_t));
            ptr->length = sizeof(rang_ack);
        }
        break;

        case UHF_RADIO_MSG_TELEM:
        {
            uint8_t tm_buff[] = {0x0,0x44,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x59,0x5,0xfe,0x6,0xff,0x7,0xf6,0xf,0xff,0x7,0xff,0x7,0xff,0x7,0xf5,0xf,0x6a,0x5,0x3b,0x7,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
            os_memcpy(ptr->data,tm_buff,sizeof(tm_buff));
            ptr->length = sizeof(tm_buff);
        }
        break;

        case UHF_CMN_MSG_NACK:
        {
        }
        break;

        case UHF_BOOTLOADER_MSG_PING:
        {
            DEBUG_CPRINT(("\n\r [UHF_SIM] Bootloader ping req\n "));
            ptr->header.command = UHF_BOOTLOADER_MSG_ACK;
            s_msg_bootloader_ack_t boot_ack;
            boot_ack.ack_message = BOOTLOADER_ACK_MSG_PONG;
            os_memcpy(ptr->data,&boot_ack,sizeof(s_msg_bootloader_ack_t));
            ptr->length = sizeof(boot_ack);
        }
        break;

        case UHF_BOOTLOADER_MSG_ERASE:
        {
            DEBUG_CPRINT(("\n\r [UHF_SIM] Bootloader erase req\n "));
            ptr->header.command = UHF_BOOTLOADER_MSG_ACK;
            s_msg_bootloader_ack_t boot_ack;
            boot_ack.ack_message = BOOTLOADER_ACK_MSG_ERASED;
            os_memcpy(ptr->data,&boot_ack,sizeof(s_msg_bootloader_ack_t));
            ptr->length = sizeof(boot_ack);
        }
        break;

        case UHF_BOOTLOADER_MSG_WRITE_PAGE:
        {
            DEBUG_CPRINT(("\n\r [UHF_SIM] bootload write page req\n "));
            ptr->header.command = UHF_BOOTLOADER_MSG_ACK;
            s_msg_bootloader_ack_t boot_ack;
            boot_ack.ack_message = 10;
            os_memcpy(ptr->data,&boot_ack,sizeof(s_msg_bootloader_ack_t));
            ptr->length = sizeof(boot_ack);
        }
        break;

        case UHF_RADIO_MSG_REBOOT:
        {
            DEBUG_CPRINT(("\n\r [UHF_SIM] radio boot req\n "));
            ptr->header.command = UHF_CMN_MSG_ACK;
        }
        break;
        case UHF_RADIO_MSG_SET_TIME:
        {
            if(rcvd_cmd_id == UHF_RADIO_MSG_SET_TIME)
            {
                DEBUG_CPRINT(("\n\r [UHF_SIM] radio set time req\n "));
                ptr->header.command = UHF_CMN_MSG_ACK;
            }
            else
            {
                DEBUG_CPRINT(("\n\r [UHF_SIM] radio get time req\n "));
                s_timespec_t time;
                time.seconds = 60;
                time.nanoseconds = 100;
                os_memcpy(ptr->data,&time,sizeof(s_timespec_t));
                ptr->length = sizeof(time);
            }
        }
        break;
    }

    len = ptr->length + sizeof(s_comms_uhf_uart_header) + sizeof(ptr->length);

    DEBUG_CPRINT(("[UHF_SIM] length: %d",len));
    uhf_send_rx_uart_cmd((uint8_t*)ptr,len); //ptr instead of frame
}


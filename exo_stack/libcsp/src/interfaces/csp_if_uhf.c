/**
 * @file csp_if_uhf.c
 *
 * @brief This file contains functions of UART interfacing for UHF radio module
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
#include "csp/interfaces/csp_if.h"
#include "csp/arch/csp_time.h"
#include "errno.h"
#include "exo_common.h"
#include <csp/csp.h>
#include <csp/csp_endian.h>
#include <csp/csp_comms.h>
#include"comms_uhf_csp.h"
#include"comms_uhf_rf_cfg.h"
#include"csp_if_uhf.h"

uint8_t uhf_packet_length = 0;
extern uint8_t uhf_rx_cmd_buff[UHF_MAX_PAYLOAD+1];

int csp_uhf_tx(const csp_route_t * ifroute, csp_packet_t * packet)
{
    uint16_t length = 0;
    uint8_t frame[CSP_IF_SLTCP_UHF_MTU];
    csp_kiss_interface_data_t * ifdata = ifroute->iface->interface_data;
    void * driver = ifroute->iface->driver_data;

    DEBUG_CPRINT(("\n\rUHF TX->\n\r"));

    /* Lock */
   /* if (csp_mutex_lock(&ifdata->lock, 1000) != CSP_MUTEX_OK) {
        csp_tm_global.csp_err_timedout++;
        return CSP_ERR_TIMEDOUT;
    }*/

    if(UHF_UART_TX_ADDRESS == packet->id.dst)
    {
        memset(frame,0,sizeof(frame));

        uhf_pack_uart_csp_frame(packet, frame);

        length = packet->length + UHF_HEADER_SIZE + CSP_HEADER_LENGTH;

        ifdata->tx_func(driver, frame, length+3);
    }
    else if(UHF_CMD_TX_ADDRESS == packet->id.dst)
    {
        memset(frame,0,sizeof(frame));

        uhf_pack_uart_frame(packet, frame);

        length = packet->length + UHF_HEADER_SIZE;

        ifdata->tx_func(driver, frame, length+3);
    }

    /* Free data */
    csp_buffer_free(packet);

    /* Unlock */
   // csp_mutex_unlock(&ifdata->lock);

    return CSP_ERR_NONE;
}

uint8_t frame[CSP_IF_SLTCP_UHF_MTU] = {0};

/**
 * Decode received data and eventually route the packet.
 */
void csp_uhf_rx(csp_iface_t * iface, const uint8_t * buf, size_t len, void * pxTaskWoken)
{
    csp_kiss_interface_data_t * ifdata = iface->interface_data;


    DEBUG_CPRINT(("\n\rUHF RX mode: %d, \n",ifdata->rx_mode));

    while (len--) {

        /* Input */
        DEBUG_CPRINT((" %x",*buf));
        //DEBUG_CPRINT(("\n\rUHF RX mode: %d, Data: %x\n",ifdata->rx_mode,*buf));
        uint8_t inputbyte = *buf++;

        /* If packet was too long */
        if (ifdata->rx_length > ifdata->max_rx_length) {
            DEBUG_CPRINT(("UHF UART RX overflow, rx:%d, max_rx:%d",ifdata->rx_length,ifdata->max_rx_length));
            iface->rx_error++;
            ifdata->rx_mode = UHF_WAIT_FOR_START0;
            ifdata->rx_length = 0;
        }

        switch (ifdata->rx_mode) {

            case UHF_WAIT_FOR_START0:

                /* Skip any characters until End char detected */
                if (inputbyte == UHF_START_BYTE_0) {
                    ifdata->rx_mode = UHF_WAIT_FOR_START1;
                }
                break;

            case UHF_WAIT_FOR_START1:
                {
                    /* Skip any characters until End char detected */
                    if (inputbyte == UHF_START_BYTE_1) {
                        ifdata->rx_mode = UHF_WAIT_FOR_LENGTH;
                    }
                    else if(inputbyte == UHF_START_BYTE_0)
                    {
                        ifdata->rx_mode = UHF_WAIT_FOR_START1;
                    }

                }
                break;

            case UHF_WAIT_FOR_LENGTH:
                {
                    if((inputbyte > UHF_MAX_PAYLOAD) || (inputbyte < 1))
                    {
                        ifdata->rx_mode = UHF_WAIT_FOR_START1;
                    }
                    else
                    {
                        /* Try to allocate new buffer */
                        if (ifdata->rx_packet == NULL) {
                            ifdata->rx_packet = pxTaskWoken ? csp_buffer_get_isr(0) : csp_buffer_get(0); // CSP only supports one size
                        }

                        /* If no more memory, skip frame */
                        if (ifdata->rx_packet == NULL) {
                            ifdata->rx_mode = UHF_WAIT_FOR_START0;
                            iface->drop++;
                            break;
                        }

                        /* Start transfer */
                        ifdata->rx_length = 0;
                        ifdata->rx_mode = UHF_RECEIVE_DATA;
                        ifdata->rx_first = true;
                        uhf_packet_length = inputbyte;
                        DEBUG_CPRINT(("\n\rUHF Packet length: %d",uhf_packet_length));

                    }
                }
                break;

            case UHF_RECEIVE_DATA:

                /* Valid data char */
                //((char *) &ifdata->rx_packet->id.ext)[ifdata->rx_length++] = inputbyte;
                frame[ifdata->rx_length++] = inputbyte;

                /* Accept message */
                if ((ifdata->rx_length > 0) && (uhf_packet_length == ifdata->rx_length))
                {
                    /* Count received frame */
                    iface->frame++;

                    s_comms_uhf_uart_header *uhf_data = (s_comms_uhf_uart_header *)frame;

                    if(((0xFFFF == uhf_data->hwid)||(0x1 == uhf_data->hwid) || (0x0 == uhf_data->hwid)) \
                            &&(1 == uhf_data->system))
                    {
                        os_memcpy(uhf_rx_cmd_buff,&uhf_packet_length,sizeof(uhf_packet_length));

                        os_memcpy(&uhf_rx_cmd_buff[1],frame,uhf_packet_length);

                        uhf_packet_length += sizeof(uhf_packet_length);

                        uhf_send_rx_uart_cmd(uhf_rx_cmd_buff,uhf_packet_length);

                        /* Free data */
                        csp_buffer_free(ifdata->rx_packet);
                    }
                    else
                    {
                        /* The CSP packet length is without the header */
                       // ifdata->rx_packet->length = ifdata->rx_length - UHF_HEADER_SIZE - CSP_HEADER_LENGTH;

                        os_memcpy(uhf_rx_cmd_buff,&uhf_packet_length,sizeof(uhf_packet_length));
                        os_memcpy(&uhf_rx_cmd_buff[1],frame,uhf_packet_length);
                        uhf_unpack_uart_frame(ifdata->rx_packet, uhf_rx_cmd_buff);

                        /* Convert the packet from network to host order */
                        //ifdata->rx_packet->id.ext = csp_ntoh32(ifdata->rx_packet->id.ext);

                        uhf_packet_length = 0;

                        /* Send back into CSP, notice calling from task so last argument must be NULL! */
                        csp_qfifo_write(ifdata->rx_packet, iface, pxTaskWoken);
                    }

                    ifdata->rx_packet = NULL;
                    ifdata->rx_length = 0;
                    ifdata->rx_mode = UHF_WAIT_FOR_START0;
                    os_memset(frame,0,sizeof(frame));
                    break;

                }
                break;

        }

    }

}

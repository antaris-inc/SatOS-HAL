/**
 * @file csp_comms.c
 *
 * @brief This file contains CSP send and receive handling functions.
 * CSP setup configuration function handling.
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
#include <csp/csp_comms.h>
#include <csp/csp_endian.h>
#include "comms_uhf_csp.h"
#include "comms_uhf_main.h"
#include "exo_io_al_sos_timer.h"
#include "exo_tctm_ipc.h"

/** SDR CSP debugging process enable or disable */
#define SDR_CSP_DBG 1

/** Default timeout */
#define DEFAULT_TIMEOUT 1000

extern os_timer_handle_ptr uhf_tx_tm_on;
extern os_timer_handle_ptr uhf_beacon_enb_timer;
extern s_sdr_tmr_cfg  uhf_tmr_cfg;
extern ioal_uart_hdle ioal_huart6;
extern ioal_uart_hdle ioal_huart4;
volatile uint8_t csp_setup_done =0;
extern uint16_t  uhf_tc_tm_id;

/**
 * @brief Thread that handles the received IPC and transmits the TM
 * to the TC originator through socket interface.
 *
 * @param[in] ptr   : Unused pointer.
 *
 * @return Doesn't return
 * @retval Doesn't return.
 */
static void comms_uhf_tx_thread(void* ptr);

/**
 * @brief This thread receives the tc data through the socket interface
 * and handles the received data through handle_tc_data()
 *
 * @param[in] ptr   : Unused pointer.
 *
 * @return Doesn't return
 * @retval Doesn't return.
 */
static void comms_rx_thread(void* ptr);

/**
 * @brief This function is used for configuring CSP
 */
void CSP_Setup(void)
{
    if(csp_setup_done != 1)
    {
        os_status_t status;
        status = status ;
        uint8_t ioal_eth_csp = 0 ;
        ioal_eth_csp = ioal_eth_csp;
        csp_conf_t *csp_conf1 = os_malloc(sizeof(csp_conf_t));

        /* Add interface(s) */
#if !defined(STM32F769xx) || defined(COMMS_UART6_ENB)
        csp_iface_t *uart_iface = os_malloc(sizeof(csp_iface_t));
#endif

        csp_conf_get_defaults(csp_conf1);

        /* Init CSP */
        csp_conf1->buffer_data_size = 1450*8;
        csp_init(csp_conf1);

        /* Start router */
        int res = csp_route_start_task(384, P_CSP_ROUTE);

#if SDR_CSP_DBG
        if (res != CSP_ERR_NONE) {
            DEBUG_CPRINT(("csp_route_start_task() %d", res));
        }
#endif

#ifdef COREBOARD
        res = csp_intf_init(UART,&ioal_huart4, &uart_iface);
#else
#if !defined(STM32F769xx) || defined(COMMS_UART6_ENB)
        res = csp_intf_init(UART,&ioal_huart6, &uart_iface);
#endif
#endif
        /** UHF UART interface initialisation */
        DEBUG_CPRINT(("\nUART Init :%d",res));

#ifdef BACKDOOR_SOCK_ENB
        csp_iface_t *eth_iface_uhf = os_malloc(sizeof(csp_iface_t));
        ioal_eth_csp = S3_UHF_HWIL_GS3;
        res = csp_intf_init(ETHERNET,&ioal_eth_csp, &eth_iface_uhf);
        DEBUG_CPRINT(("\nBackdoor Init :%d",res));

        csp_rtable_set(BK_ETH_TX_ADDRESS, 5, eth_iface_uhf, CSP_NO_VIA_ADDRESS);
        csp_route_set(BK_ETH_TX_ADDRESS, eth_iface_uhf, CSP_NO_VIA_ADDRESS);
#endif


#ifdef LINUX_TEMP_PORT

        csp_rtable_set(UHF_CMD_TX_ADDRESS , 5, uart_iface, CSP_NO_VIA_ADDRESS);
        csp_route_set(UHF_CMD_TX_ADDRESS, uart_iface , CSP_NO_VIA_ADDRESS);
        
        csp_rtable_set(UHF_UART_TX_ADDRESS, 5, uart_iface, CSP_NO_VIA_ADDRESS);
        csp_route_set(UHF_UART_TX_ADDRESS, uart_iface , CSP_NO_VIA_ADDRESS);
#else
#if !defined(STM32F769xx) || defined(COMMS_UART6_ENB)

        csp_rtable_set(UHF_CMD_TX_ADDRESS , 5, uart_iface, CSP_NO_VIA_ADDRESS);
        csp_route_set(UHF_CMD_TX_ADDRESS, uart_iface , CSP_NO_VIA_ADDRESS);
        
        csp_rtable_set(UHF_UART_TX_ADDRESS, 5, uart_iface, CSP_NO_VIA_ADDRESS);
        csp_route_set(UHF_UART_TX_ADDRESS, uart_iface , CSP_NO_VIA_ADDRESS);
#endif
#endif

        /** Thread creation of driver UHF TX Thread */
        status = os_thread_create(COMMS_UHF_TX,
                T_COMMS_UHF_TX_STACK_SIZE,
                P_COMMS_UHF_TX,
                "COMMS UHF transmit thread",
                comms_uhf_tx_thread,
                NULL,
                NULL,
                NULL);

        /** Common Thread creation of driver RX thread */
        status &= os_thread_create(COMMS_RX,
                T_COMMS_RX_STACK_SIZE,
                P_COMMS_RX,
                "COMMS recv thread-socket",
                comms_rx_thread,
                NULL,
                NULL,
                NULL);

#if SDR_CSP_DBG
        DEBUG_CPRINT(("Connection table\r\n"));
        csp_conn_print_table();

        DEBUG_CPRINT(("Interfaces\r\n"));
        csp_iflist_print();

        DEBUG_CPRINT(("Route table\r\n"));
        csp_rtable_print();
#endif
        os_free(csp_conf1);
        csp_conf1 = NULL;
        csp_setup_done = 1;
    }
}

/**
 * @brief This function is used for sending Telemetry to UHF module
 */
int32_t comms_send_tm_uhf(uint8_t* tm_data, uint16_t len)
{
    csp_conn_t *conn;
    csp_packet_t *packet=NULL;
    size_t sent = 0 , datasize;
    size_t remain = 0;
    remain = remain;
    uint16_t mtu_size = 0;

    uint8_t csp_tx_port = UHF_CSP_TX_DATA_PORT;
    uint8_t csp_tx_addr = UHF_UART_TX_ADDRESS;

    DEBUG_CPRINT(("The COMMS TM_LEN %d", len));

    comms_uhf_upd_port_addr(&csp_tx_port,&csp_tx_addr);
    mtu_size = UHF_UART_MTU ;

    DEBUG_CPRINT(("\n csp_tx_addr: %d, csp_tx_port: %d\n",csp_tx_addr,csp_tx_port));

    conn = csp_connect(CSP_PRIO_NORM, csp_tx_addr, csp_tx_port , DEFAULT_TIMEOUT, CSP_O_NONE);
    if (!conn)
        return -ECONNREFUSED;

    remain = (len + mtu_size - 1) / mtu_size;

    if(len!=0)
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

            memcpy(packet->data, &tm_data[sent], datasize);
            packet->length = datasize;

#if SDR_CSP_DBG
            //            int i=0,j = 0;
            DEBUG_CPRINT(("data size is %d\n tm_data: ", (uint16_t)datasize));

                        //for(uint16_t i = sent; i<datasize; i++)
                        {
                            //DEBUG_CPRINT(("%x ",tm_data[i]));
                        }
            DEBUG_CPRINT(("\n value of TX packet->length is %d\r\n", packet->length));


            //DEBUG_CPRINT(("\n value of TX packet->id is %x\r\n", packet->id.ext));

            //            for(j = 0; j<packet->length; j++)
            //            {
            //                DEBUG_CPRINT(("%x ",packet->data[j]));
            //            }
#endif

            if (!csp_send(conn, packet, DEFAULT_TIMEOUT)) {
                csp_buffer_free(packet);
                csp_close(conn);
                return -EIO;
            }
            DEBUG_CPRINT(("packet successfully sent \r\n"));
            sent += datasize;
        }

    csp_buffer_free(packet);
    csp_close(conn);
    return 0;
}

/**
 * @brief This function is used for sending Telemetry to backdoor
 */
int32_t comms_send_tm_bc(uint8_t* tm_data, uint16_t len)
{
    csp_conn_t *conn;
    csp_packet_t *packet=NULL;
    size_t sent = 0 , datasize;
    size_t remain = 0;
    remain = remain;
    uint16_t mtu_size = 0;

    DEBUG_CPRINT(("\nBK TM_LEN %d\n", len));

    uint8_t csp_tx_port = UHF_CSP_TX_DATA_PORT;
    uint8_t csp_tx_addr = BK_ETH_TX_ADDRESS;

    mtu_size = UHF_UART_MTU;

    DEBUG_CPRINT(("\n csp_tx_addr: %d, csp_tx_port: %d\n",csp_tx_addr,csp_tx_port));

    conn = csp_connect(CSP_PRIO_NORM, csp_tx_addr, csp_tx_port , DEFAULT_TIMEOUT, CSP_O_NONE);
    if (!conn)
        return -ECONNREFUSED;

    remain = (len + mtu_size - 1) / mtu_size;

    if(len!=0)
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

            memcpy(packet->data, &tm_data[sent], datasize);
            packet->length = datasize;

#if SDR_CSP_DBG
          //  int i=0,j = 0;
            DEBUG_CPRINT(("data size is %d\n tm_data: ", (uint16_t)datasize));

            for(uint16_t i = sent; i<datasize; i++)
            {
                DEBUG_CPRINT(("%x ",tm_data[i]));
            }
            DEBUG_CPRINT(("\n value of TX packet->length is %d\r\n", packet->length));
            //DEBUG_CPRINT(("\n value of TX packet->id is %x\r\n", packet->id.ext));

            //for(j = 0; j<packet->length; j++)
            //{
            //    DEBUG_CPRINT(("%x ",packet->data[j]));
           // }
    /*
                */
#endif

            if (!csp_send(conn, packet, DEFAULT_TIMEOUT)) {
                csp_buffer_free(packet);
                csp_close(conn);
                DEBUG_CPRINT(("BK packet sent fail\r\n"));
                return -EIO;
            }
            DEBUG_CPRINT(("BK packet successfully sent \r\n"));
            sent += datasize;
            csp_buffer_free(packet);
        }

    csp_close(conn);
    return 0;
}

/**
 * @brief This function is used for receiving Telecommand from UHF module
 */
int32_t comms_recv_tc(void)
{
    os_itc_msg_handle_t trans_msg;
    csp_conn_t *conn;
    csp_packet_t *packet;

    csp_socket_t *sock;

    sock = csp_socket(CSP_SO_NONE);

    /* Create socket with no specific socket options, e.g. accepts CRC32, HMAC, etc. if enabled during compilation */

    /* Bind socket to all ports, e.g. all incoming connections will be handled here */
    csp_bind(sock, CSP_ANY);

    /* Create a backlog of 10 connections, i.e. up to 10 new connections can be queued */
    csp_listen(sock, 10);

    while (1)
    {
        if ((conn = csp_accept(sock, 10)) == NULL) {
            /* timeout */
            os_delay(10);
        }

        while ((packet = csp_read(conn, 1)) != NULL)
        {
            /*Control variable - Increments on every packet received in csp comms*/
            int j = 0;
            switch (csp_conn_dport(conn))
            {
            case UHF_CSP_RX_DATA_PORT:
                DEBUG_CPRINT(("Packet received in port: %d",csp_conn_dport(conn)));

                trans_msg.src_entity= COMMS_RX;
                os_memcpy(&trans_msg.Msg_id,&packet->data[0], sizeof(uint16_t));
                os_memcpy(&trans_msg.Msg_len,&packet->data[2], sizeof(uint16_t));

                uhf_tc_tm_id = trans_msg.Msg_id;
                if(trans_msg.Msg_len)
                {
                    trans_msg.pld.pld_ptr = (uint8_t *)os_malloc(trans_msg.Msg_len);
                    os_memcpy(trans_msg.pld.pld_ptr,&packet->data[4], trans_msg.Msg_len);
                }
                else
                {
                    trans_msg.Msg_len = 1;//tried
                    trans_msg.pld.pld_ptr = (uint8_t *)os_malloc(trans_msg.Msg_len);
                }

#if SDR_CSP_DBG
                DEBUG_CPRINT(("\n value of RX packet->length is %d\r\n", packet->length));

                //DEBUG_CPRINT(("\n value of RX packet->id is %x\r\n", packet->id.ext));

                for(j = 0; j<packet->length; j++)
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
#endif
                os_status_t sts;
                sts = os_itc_msg_send(&trans_msg,
                        COMMS_UHF_CTLR,
                        os_wait_forever);
                if(sts == ral_error && trans_msg.pld.pld_ptr != NULL)
                {
                    os_free(trans_msg.pld.pld_ptr);
                    trans_msg.pld.pld_ptr = NULL;
                }
                os_timer_start(uhf_beacon_enb_timer,uhf_tmr_cfg.beacon_enb_tmr);

                csp_buffer_free(packet);

                break;

            default:
                /* Call the default CSP service handler, handle pings, buffer use, etc. */
                csp_service_handler(conn,packet);
                break;
            }
        }

        /* Close current connection */
        csp_close(conn);
    }
    return 0;
}

/**
 * @brief Thread that handles the received IPC and transmits the TM
 * to the TC originator through socket interface.
 */

static void comms_uhf_tx_thread(void* ptr)
{
    int32_t tm_size = 0;

    os_itc_msg_handle_t recv_msg;

    while(1)
    {
        /** IPC receive for sending TM to UHF module */
        os_itc_msg_rcv(COMMS_UHF_TX, &recv_msg, os_wait_forever);

        tm_size = recv_msg.Msg_len;

        DEBUG_CPRINT(("\n tm_len:%d ,src_entity:%d \n",recv_msg.Msg_len, recv_msg.src_entity));

        /** Sending the TM UHF module */
        if (tm_size>0)
        {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
            DEBUG_CPRINT(("comms_tm_len: %ld",tm_size));
#pragma GCC diagnostic pop

#if !defined(LINUX_TEMP_PORT) || !defined(UHF_HW_BYPASS)
            comms_send_tm_uhf(recv_msg.pld.pld_ptr, tm_size);
#endif

#ifdef BACKDOOR_SOCK_ENB 
            comms_send_tm_bc(recv_msg.pld.pld_ptr, tm_size);
#endif
        }
        else
        {
            printf("UHF TM length invalid");
        }

        /** Freeing of payload pointer */
        if(recv_msg.pld.pld_ptr)
        {
            os_free(recv_msg.pld.pld_ptr);
            recv_msg.pld.pld_ptr = NULL;
        }

    }
}

/**
 * @brief This thread receives the tc data through the socket interface
 * and handles the received data through handle_tc_data()
 */
static void comms_rx_thread(void* ptr)
{
    comms_recv_tc();
}

/**
 * @brief This API handle the back door socket data
 */
void comms_back_door_data_receive(uint8_t *data, uint16_t length)
{
    printf("back door function \n");

        //for(int c=0;c<length;c++)
            //printf("%x ",data[c]);
    printf("\n");
    uint16_t msgid = 0;
    uint16_t msglen = 0;
    os_memcpy(&msgid, &data[0], sizeof(uint16_t));
    os_memcpy(&msglen, &data[2], sizeof(uint16_t));
    os_itc_msg_handle_t trans_msg;
    trans_msg.Msg_id = msgid;
    trans_msg.Msg_len = msglen;
    uhf_tc_tm_id = trans_msg.Msg_id;
    trans_msg.src_entity= COMMS_RX;

    if(trans_msg.Msg_len)
    {
        trans_msg.pld.pld_ptr = (uint8_t *)os_malloc(trans_msg.Msg_len);
        os_memcpy(trans_msg.pld.pld_ptr,&data[4], trans_msg.Msg_len);
    }
    else
    {
        trans_msg.Msg_len = 1;//tried
        trans_msg.pld.pld_ptr = (uint8_t *)os_malloc(trans_msg.Msg_len);
    }
    //trans_msg.pld.pld_ptr = (uint8_t *)os_malloc(length);
    //os_memcpy(trans_msg.pld.pld_ptr,data, length);
    //trans_msg.Msg_len = length;

    os_itc_msg_send(&trans_msg,
            COMMS_UHF_CTLR,
            os_send_itc_wait);
}


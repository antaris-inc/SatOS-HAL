/**
 * @file csp_if_sltcp.c
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
#include <csp/interfaces/csp_if_sltcp.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>

#ifdef LINUX_TEMP_PORT
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#else
#include <sockets.h>
#endif

#include <pthread.h>

#include <csp/csp.h>
#include <csp/csp_endian.h>
#include <csp/csp_interface.h>
#include <csp/arch/csp_malloc.h>
#include <csp/arch/csp_thread.h>


#include <exo_osal_thread.h>
#include <exo_common.h>
#include"comms_uhf_csp.h"
#include"csp_if_uhf.h"
#include "csp_comms.h"

/* MTU of the sltcp interface */
#define CSP_IF_SLTCP_MTU   251

uint32_t sl_tcp_port =0;
uint32_t sl_tcp_addr =0;
FILE *sl_tcp_inf;

#ifdef LINUX_TEMP_PORT

s_obc_sock_info obc_uhf_soc_inf;
s_obc_sock_info obc_gs2_soc_inf;

#endif
struct csp_sltcp_ifdata {
    char ifname[CSP_IFLIST_NAME_MAX + 1];
    csp_iface_t iface;

    int dest_socket, server;
    struct sockaddr_in dest_addr;
    pthread_t rx_thread;
};

struct sockaddr_in si_other;
int slen = sizeof(struct sockaddr_in);

struct csp_sltcp_ifdata sltcp_data_uhf;

/**
 * @brief This API handle UHF RX in TCP interface
 *
 * @param[in] arg : Dummy argument
 *
 * @return status of RX
 * @retval #CSP_ERR_NONE on success - else assert.
 */
static void csp_sltcp_rx_uhf(void *arg);

/**
 * @brief This API handle UHF TX in TCP interface
 *
 * @param[in] route : pointer to handle csp route
 * @param[in] packet : pointer to handle csp packet
 *
 * @return status of TX
 * @retval #CSP_ERR_NONE on success - else assert.
 */
static int csp_sltcp_tx_uhf(const csp_route_t *route, csp_packet_t *packet);

/**
 * @brief This API handle UHF RX in TCP interface
 */
static void csp_sltcp_rx_uhf(void *arg)
{
    int32_t maxsd=0,sd = 0;
    int32_t i, socketcount ;
    int dest_addr_len ;
    struct csp_sltcp_ifdata *data = &sltcp_data_uhf;
    int32_t clientsocket[10] = {0};

    fd_set readfds;
    FD_ZERO(&readfds);
    int nbytes;
    csp_packet_t *packet;

    uint8_t frame[CSP_IF_SLTCP_UHF_MTU];

    // Accept a new client connection
    dest_addr_len = sizeof(data->dest_addr);

    while(1)
    {
        memset(frame, 0,sizeof(frame));
        FD_ZERO(&readfds);
        FD_SET( data->server, &readfds);

        maxsd = data->server;

        for(i=0;i<10;i++)
        {
            sd = clientsocket[i];
            if(sd>0)
                FD_SET(clientsocket[i],&readfds);
            if(sd>maxsd)
            {
                maxsd = sd;
            }
        }

        socketcount = select( maxsd+1, &readfds, NULL, NULL, NULL );

        if(socketcount<1)
        {
            DEBUG_CPRINT(("UHF_SIM: [-]Error in select"));
        }

        if(FD_ISSET(data->server, &readfds))
        {
            if((data->dest_socket = accept(data->server, (struct sockaddr *)&data->dest_addr, (socklen_t *)&dest_addr_len)) < 0) {
                DEBUG_CPRINT(("[SLTCP - UHF] Error in accepting TCTM Socket.\n"));
            }
            else
            {
                DEBUG_CPRINT(("[SLTCP - UHF] Accepted new connection from %s:%d\n", inet_ntoa(data->dest_addr.sin_addr), (data->dest_addr.sin_port)));
            }

            for(i=0;i<10;i++)
            {
                if(clientsocket[i]==0)
                {
                	clientsocket[i]=data->dest_socket;
                	break;
                }
            }
        }
        else
        {
            for(i=0;i<10;i++)
            {
                sd = clientsocket[i];
                if(FD_ISSET(sd, &readfds))
                {
                    nbytes = recv(sd,frame,sizeof(frame),MSG_DONTWAIT);
                    if(nbytes==0 )
                    {
                        close(sd);
                        clientsocket[i]=0;
                    }
                    else if(nbytes>=0)
                    {
                        if (nbytes <=0 || (unsigned int)nbytes < sizeof(frame))
                            continue;

                        printf("\nnbytes: %d\n",nbytes);

                        for(int c=0;c<nbytes;c++)
                            printf("%x ",frame[c]);

                        /* Allocate buffer for frame */
                        packet = csp_buffer_get(CSP_IF_SLTCP_UHF_MTU);

                        uhf_unpack_uart_csp_frame(packet, frame);

                        /* Pass frame to CSP stack */
                        csp_qfifo_write(packet, &data->iface, NULL);
                    }
                }
            }
        }
    }
    close(data->server);
}

/**
 * @brief This API handle UHF TX in TCP interface
 */
static int csp_sltcp_tx_uhf(const csp_route_t *route, csp_packet_t *packet)
{
    int nbytes;
    uint8_t frame[CSP_IF_SLTCP_UHF_MTU];
    struct csp_sltcp_ifdata *data = (struct csp_sltcp_ifdata*)route->iface->driver_data;
    struct sockaddr_in dest = data->dest_addr;

    memset(frame,0,sizeof(frame));

    uhf_pack_uart_csp_frame(packet, frame);

    /* Send message */
    nbytes = sendto(data->dest_socket, frame, sizeof(frame), 0,(struct sockaddr *) &dest, sizeof(dest));

    if (nbytes != (int)sizeof(frame))
    {
        return CSP_ERR_TIMEDOUT;
    }

    csp_buffer_free(packet);

    return CSP_ERR_NONE;
}

/**
 * @brief This API initialize the TCP socket
 */
int csp_sltcp_init_uhf(const char *device, const char *ifname, csp_iface_t **ifc)
{
    int ret ;
    struct sockaddr_in sa;

#ifndef LINUX_TEMP_PORT
    ip4_addr_t eth_ipaddr;
#endif

    /* Allocate interface data */
    struct csp_sltcp_ifdata *data = &sltcp_data_uhf;
    if (!data)
        return CSP_ERR_NOMEM;

    if (!ifname)
        ifname = CSP_IF_SLTCP_DEFAULT_NAME_UHF;

    strncpy(data->ifname, ifname, sizeof(data->ifname) - 1);
    data->iface.name = data->ifname;
    data->iface.driver_data = data;
    data->iface.nexthop = csp_sltcp_tx_uhf;
    data->iface.mtu = CSP_IF_SLTCP_UHF_MTU + 20;

    /* Create socket */
    data->server = socket(AF_INET, SOCK_STREAM, 0);
    if (data->server < 0) {
        csp_log_error("failed to allocate TCP socket\n");
        return CSP_ERR_DRIVER;
    }

#ifdef LINUX_TEMP_PORT
    DEBUG_CPRINT(("\n\r[SLTCP - UHF] OBC TC TM socket address is %s %u \n",obc_uhf_soc_inf.ip_addr,(obc_uhf_soc_inf.port)));
    sl_tcp_port = (obc_uhf_soc_inf.port);
    sl_tcp_addr = inet_addr(obc_uhf_soc_inf.ip_addr);
#else

#ifdef GSOBC_USB_EN
    IP4_ADDR(&eth_ipaddr, USB_IP_ADDR0, USB_IP_ADDR1, USB_IP_ADDR2, USB_IP_ADDR3);
#else
    IP4_ADDR(&eth_ipaddr, ETH_IP_ADDR0, ETH_IP_ADDR1, ETH_IP_ADDR2, ETH_IP_ADDR3);
#endif
    sl_tcp_port  = GS_SRVR_PORT;
    sl_tcp_addr  = eth_ipaddr.addr;
#endif

    /* Bind to incoming port on interface */
    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = sl_tcp_addr;
    sa.sin_port = htons(sl_tcp_port);

    ret = bind(data->server, (const struct sockaddr *)&sa, sizeof(struct sockaddr_in));
    if (ret < 0) {
        csp_log_error("[SLTCP-UHF] failed to bind receive socket\n");
        return CSP_ERR_DRIVER;
    }

    // Listen for incoming connections
    if (listen(data->server, 10) == -1) {
        perror("listen");
    }

    DEBUG_CPRINT(("[SLTCP-UHF] Server listening on port %d\n", htons(sa.sin_port)));

    /* Create destination address */
    memset(&data->dest_addr, 0, sizeof(data->dest_addr));
    data->dest_addr.sin_family = AF_INET;
    data->dest_addr.sin_addr.s_addr = sl_tcp_addr;
    data->dest_addr.sin_port = sl_tcp_port;

    /* Start receiver thread */
    ret = os_thread_create(CSP_ETH_RX, T_STACK_5K, P_CSP_INTF_ETH_RX,"CSP UHF Socket RX",csp_sltcp_rx_uhf, data,NULL,NULL);

    if (ret < 0) {
        csp_log_error("[SLTCP-UHF] failed to start receive thread\n");
        return CSP_ERR_DRIVER;
    }

    /* Register interface */
    csp_iflist_add(&data->iface);

    if (ifc)
        *ifc = &data->iface;

    return CSP_ERR_NONE;
}

#if 0
#ifdef BACKDOOR_SOCK_ENB
struct csp_sltcp_ifdata sltcp_data_gs2;
static void 
csp_sltcp_rx_gs2(void *arg);

static void csp_sltcp_rx_gs2(void *arg)
{
    int32_t maxsd=0,sd = 0;
    int32_t i, socketcount ;
    int dest_addr_len ;
    struct csp_sltcp_ifdata *data = &sltcp_data_gs2;
    int32_t clientsocket[10] = {0};

    fd_set readfds;
    FD_ZERO(&readfds);
    int nbytes;
    uint32_t id;
    uint16_t length;
    csp_packet_t *packet;

    uint8_t frame[sizeof(id) + CSP_IF_SLTCP_MTU];

    // Accept a new client connection
    dest_addr_len = sizeof(data->dest_addr);

    while(1)
    {
        memset(frame, 0,sizeof(frame));
        FD_ZERO(&readfds);
        FD_SET( data->server, &readfds);

        maxsd = data->server;

        for(i=0;i<10;i++)
        {
            sd = clientsocket[i];
            if(sd>0)
                FD_SET(clientsocket[i],&readfds);
            if(sd>maxsd)
            {
                maxsd = sd;
            }
        }

        socketcount = select( maxsd+1, &readfds, NULL, NULL, NULL );

        if(socketcount<1)
        {
            DEBUG_CPRINT(("COMMS_UHF: [-]Error in select"));
        }

        if(FD_ISSET(data->server, &readfds))
        {
            if((data->dest_socket = accept(data->server, (struct sockaddr *)&data->dest_addr, (socklen_t *)&dest_addr_len)) < 0) {
                DEBUG_CPRINT(("[SLTCP] Error in accepting TCTM Socket.\n"));
            }
            else
            {
                DEBUG_CPRINT(("[SLTCP] Accepted new connection from %s:%d\n", inet_ntoa(data->dest_addr.sin_addr), (data->dest_addr.sin_port)));
            }

            for(i=0;i<10;i++)
            {
                if(clientsocket[i]==0)
                {
                	clientsocket[i]=data->dest_socket;
                	break;
                }
            }
        }
        else
        {
            for(i=0;i<10;i++)
            {
                sd = clientsocket[i];
                if(FD_ISSET(sd, &readfds))
                {
                    nbytes = recv(sd,frame,sizeof(frame),MSG_DONTWAIT);
                    if(nbytes==0 )
                    {
                        close(sd);
                        clientsocket[i]=0;
                    }
                    else if(nbytes>=0)
                    {
                    	//DEBUG_CPRINT(("\n\r[SLUDP] BACKDOOR Received packet %d from %s:%d\n",nbytes, inet_ntoa(si_udp.sin_addr), ntohs(si_udp.sin_port)));
                    	DEBUG_CPRINT(("\n\r[SLTCP] BACKDOOR Received packet %d \n",nbytes));

                    	if (nbytes < 0 || (unsigned int)nbytes < sizeof(id))
                    		continue;
                        
                        for(int c=0;c<nbytes;c++)
                            printf("%x ",frame[c]);
                        printf("\n");

                    	/* Extract CSP length */
                    	length = nbytes - sizeof(id);

                    	/* Allocate buffer for frame */
                    	packet = csp_buffer_get(length);
                    	if (!packet)
                    		continue;
                    	packet->length = length;

                    	/* Set packet ID */
                    	memcpy(&id, &frame[0], sizeof(id));
                    	packet->id.ext = csp_ntoh32(id);

                    	/* Copy received data into CSP buffer */
                    	memcpy(packet->data, &frame[sizeof(id)], packet->length);
                    	/* Pass frame to CSP stack */
                    	//csp_qfifo_write(packet, &data->iface, NULL);
                    	/*Control variable - Increments on every packer received in csp-sludp*/
                    	//exo_sw_dbg_cb.comms_dbg.csp_sludp_rcvd++;
                    	comms_back_door_data_receive(packet->data, packet->length);
                    	csp_buffer_free(packet);
                    }
                }
            }
        }
    }
    close(data->server);

}

static int csp_sltcp_tx_gs2(const csp_route_t *route, csp_packet_t *packet)
{
    struct csp_sltcp_ifdata *data = (struct csp_sltcp_ifdata*)route->iface->driver_data;

    int nbytes;
    uint32_t id;
    uint16_t length = 0, size = 0;
    size = size;
    length = length;
    struct sockaddr_in dest = data->dest_addr;
    uint8_t frame[sizeof(id) + CSP_IF_SLTCP_MTU];
    id = csp_hton32(packet->id.ext);

    memcpy(&frame[length], &id, sizeof(id));
    length += sizeof(id);
    memcpy(&frame[length], packet->data, packet->length);
    length += packet->length;

    /* Send message */
    nbytes = sendto(data->dest_socket, frame, length, 0,(struct sockaddr *) &dest, sizeof(dest));

    if (nbytes != (int)length)
        return CSP_ERR_TIMEDOUT;


    csp_buffer_free(packet);

    return CSP_ERR_NONE;
}

int csp_sltcp_init_gs2(const char *device, const char *ifname, csp_iface_t **ifc)
{
    int ret ;
    struct sockaddr_in sa;

#ifndef LINUX_TEMP_PORT
    ip4_addr_t eth_ipaddr;
#endif

    /* Allocate interface data */
    struct csp_sltcp_ifdata *data = &sltcp_data_gs2;
    if (!data)
        return CSP_ERR_NOMEM;

    if (!ifname)
        ifname = CSP_IF_SLTCP_DEFAULT_NAME_GS2;

    strncpy(data->ifname, ifname, sizeof(data->ifname) - 1);
    data->iface.name = data->ifname;
    data->iface.driver_data = data;
    data->iface.nexthop = csp_sltcp_tx_gs2;
    data->iface.mtu = CSP_IF_SLTCP_MTU + 20;

    /* Create socket */
    data->server = socket(AF_INET, SOCK_STREAM, 0);
    if (data->server < 0) {
        csp_log_error("failed to allocate TCP socket\n");
        //csp_tm_global.csp_err_driver ++ ;
        return CSP_ERR_DRIVER;
    }

#ifdef LINUX_TEMP_PORT
    DEBUG_CPRINT(("\n\r[SLTCP - GS2] OBC TC TM socket address is %s %u \n",obc_gs2_soc_inf.ip_addr,(obc_gs2_soc_inf.port)));
    sl_tcp_port = (obc_gs2_soc_inf.port);
    sl_tcp_addr = inet_addr(obc_gs2_soc_inf.ip_addr);
#else

#ifdef GSOBC_USB_EN
    IP4_ADDR(&eth_ipaddr, USB_IP_ADDR0, USB_IP_ADDR1, USB_IP_ADDR2, USB_IP_ADDR3);
#else
    IP4_ADDR(&eth_ipaddr, ETH_IP_ADDR0, ETH_IP_ADDR1, ETH_IP_ADDR2, ETH_IP_ADDR3);
#endif
    sl_tcp_port  = GS_SRVR_PORT;
    sl_tcp_addr  = eth_ipaddr.addr;
#endif

    /* Bind to incoming port on interface */
    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = sl_tcp_addr;
    sa.sin_port = htons(sl_tcp_port);

    ret = bind(data->server, (const struct sockaddr *)&sa, sizeof(struct sockaddr_in));
    if (ret < 0) {
        csp_log_error("[SLTCP - GS2] failed to bind receive socket\n");
        //csp_tm_global.csp_err_driver ++ ;
        return CSP_ERR_DRIVER;
    }

    // Listen for incoming connections
    if (listen(data->server, 10) == -1) {
        perror("listen");
    }

    DEBUG_CPRINT(("[SLTCP - GS2] Server listening on port %d\n", sa.sin_port));

    /* Create destination address */
    memset(&data->dest_addr, 0, sizeof(data->dest_addr));
    data->dest_addr.sin_family = AF_INET;
    data->dest_addr.sin_addr.s_addr = sl_tcp_addr;
    data->dest_addr.sin_port = sl_tcp_port;

    /* Start receiver thread */
    ret = os_thread_create(CSP_ETH_RX, T_STACK_5K, P_CSP_INTF_ETH_RX,"CSP Ethernet RX",csp_sltcp_rx_gs2, data,NULL,NULL);

    if (ret < 0) {
        csp_log_error("[SLTCP - GS2] failed to start receive thread\n");
        //csp_tm_global.csp_err_driver ++ ;
        return CSP_ERR_DRIVER;
    }

    /* Register interface */
    csp_iflist_add(&data->iface);

    if (ifc)
        *ifc = &data->iface;

    return CSP_ERR_NONE;
}
#endif
#endif

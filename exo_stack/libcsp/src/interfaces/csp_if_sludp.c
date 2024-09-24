/**
 * @file csp_if_sludp.c
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
#ifdef BACKDOOR_SOCK_ENB
#include <csp/interfaces/csp_if_sludp.h>

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
#include <csp/csp_comms.h>
#include <csp/csp_endian.h>
#include <csp/csp_interface.h>
#include <csp/arch/csp_malloc.h>
#include <csp/arch/csp_thread.h>
#include "exo_osal_thread.h"

/* MTU of the SLUDP interface */
#define CSP_IF_SLUDP_MTU     1400

uint32_t sl_udp_port =0;
uint32_t sl_udp_addr =0;
FILE *sl_udp_inf;
s_obc_sock_info sludp_tctm_soc_inf;

struct csp_sludp_ifdata sludp_data;

struct csp_sludp_ifdata {
    char ifname[CSP_IFLIST_NAME_MAX + 1];
    csp_iface_t iface;

    int dest_socket;
    struct sockaddr_in dest_addr;
    pthread_t rx_thread;
};

struct sockaddr_in si_udp;
int slen_udp = sizeof(struct sockaddr_in);

static void csp_sludp_rx(void *arg)
{
    struct csp_sludp_ifdata *data = &sludp_data;

    int nbytes;
    uint32_t id;
    uint16_t length;
    csp_packet_t *packet;

    uint8_t frame[sizeof(id) + CSP_IF_SLUDP_MTU];
    while (1) {
        /* Wait for frames */
        nbytes = recvfrom(data->dest_socket, frame, sizeof(frame), 0, (struct sockaddr *)&si_udp,(socklen_t*)&slen_udp);


#if (CSP_DEBUG)
        DEBUG_CPRINT(("\n\r[SLUDP] Received packet %d from %s:%d\n",nbytes, inet_ntoa(si_udp.sin_addr), ntohs(si_udp.sin_port)));
#endif

        DEBUG_CPRINT(("\n\r[SLUDP] BACKDOOR Received packet %d from %s:%d\n",nbytes, inet_ntoa(si_udp.sin_addr), ntohs(si_udp.sin_port)));

        if (nbytes < 0 || (unsigned int)nbytes < sizeof(id))
            continue;

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
        comms_back_door_data_receive(packet->data, packet->length);
        csp_buffer_free(packet);
    }

}

static int csp_sludp_tx(const csp_route_t *route, csp_packet_t *packet)
{
    struct csp_sludp_ifdata *data = (struct csp_sludp_ifdata*)route->iface->driver_data;

    int nbytes;
    uint32_t id;
    uint16_t size = 0, length = 0;
    size=size;
    length=length;
    struct sockaddr_in dest = si_udp;

    uint8_t frame[sizeof(id) + CSP_IF_SLUDP_MTU];
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

int csp_sludp_init(const char *device, const char *ifname, csp_iface_t **ifc)
{
    int ret;
    struct sockaddr_in sa;

#ifndef LINUX_TEMP_PORT
    ip4_addr_t eth_ipaddr;
#endif

    /* Allocate interface data */
    struct csp_sludp_ifdata *data = &sludp_data;
    if (!data)
        return CSP_ERR_NOMEM;

    if (!ifname)
        ifname = CSP_IF_SLUDP_DEFAULT_NAME;

    strncpy(data->ifname, ifname, sizeof(data->ifname) - 1);
    data->iface.name = data->ifname;
    data->iface.driver_data = data;
    data->iface.nexthop = csp_sludp_tx;
    data->iface.mtu = CSP_IF_SLUDP_MTU + 20;

    /* Create socket */
    data->dest_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (data->dest_socket < 0) {
        csp_log_error("failed to allocate UDP socket\n");
        return CSP_ERR_DRIVER;
    }

#ifdef LINUX_TEMP_PORT

    ////////////////////////////////////////
    //Read socket information from file
    /////////////////////////////////////////
#if 0
    sl_udp_inf = fopen("obc_soc_cfg.txt", "r");

    if (sl_udp_inf == NULL) {
        DEBUG_CPRINT(("Error to open the file\n"));
        exit(1);
    }

    fread(&sludp_tctm_soc_inf, sizeof(s_csp_sock_info),1, sl_udp_inf);
    DEBUG_CPRINT(("\n\r[SLUDP] OBC TC TM socket address is %s %u \n",sludp_tctm_soc_inf.ip_addr,atoi(sludp_tctm_soc_inf.port_num)));

    fclose(sl_udp_inf);
#endif
    sl_udp_port = (sludp_tctm_soc_inf.port);
    sl_udp_addr = inet_addr(sludp_tctm_soc_inf.ip_addr);
#else

#ifdef GSOBC_USB_EN
    IP4_ADDR(&eth_ipaddr, USB_IP_ADDR0, USB_IP_ADDR1, USB_IP_ADDR2, USB_IP_ADDR3);
#else
    IP4_ADDR(&eth_ipaddr, ETH_IP_ADDR0, ETH_IP_ADDR1, ETH_IP_ADDR2, ETH_IP_ADDR3);
#endif
    uint32_t sl_udp_port  = GS_SRVR_PORT;
    uint32_t sl_udp_addr  = eth_ipaddr.addr;
#endif

    /* Bind to incoming port on interface */
    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = sl_udp_addr;
    sa.sin_port = htons(sl_udp_port);

    ret = bind(data->dest_socket, (const struct sockaddr *)&sa, sizeof(struct sockaddr_in));
    if (ret < 0) {
        csp_log_error("failed to bind receive socket\n");
        return CSP_ERR_DRIVER;
    }

    /* Start receiver thread */
    ret = os_thread_create(CSP_ETH_RX, T_STACK_5K, P_CSP_INTF_ETH_RX,"CSP Ethernet RX",csp_sludp_rx, data,NULL,NULL);

    if (ret < 0) {
        csp_log_error("failed to start receive thread\n");
        return CSP_ERR_DRIVER;
    }

    /* Register interface */
    csp_iflist_add(&data->iface);

    if (ifc)
        *ifc = &data->iface;

    return CSP_ERR_NONE;
}
#endif


#ifdef LWIP_THROW_TEST
#define TEST_SOC_PORT (6969)
uint32_t test_udp_recv_cnt = 0;
uint32_t test_udp_snd_cnt = 0;
/**
 * @brief This API invoke a thread to handle the test socket udp IPC
 * messages
 */
int32 test_udp_socket(void)
{
    os_status_t status;

    status = os_thread_create(TEST_SOC_UDP,
                                T_STACK_5K,
                              P_LWIP_MBOX,
                              "test_soc_udp",
                              test_sock_udp,
                              NULL,
                              NULL,
                              NULL);
    return status;
}


/**
 * @brief This function create and handle test UDP socket
 */
void test_sock_udp(void* arg)
{
    ip4_addr_t test_eth_ipaddr;
    int sockfd;
    char buffer[2000];
    char *hello = "Hello from server";
    struct sockaddr_in test_servaddr, test_cliaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    IP4_ADDR(&test_eth_ipaddr, 192, 168, 1, 111);
    uint32_t test_udp_addr  = test_eth_ipaddr.addr;
    memset(&test_servaddr, 0, sizeof(test_servaddr));
    memset(&test_cliaddr, 0, sizeof(test_cliaddr));

    // Filling server information
    test_servaddr.sin_family = AF_INET; // IPv4
    test_servaddr.sin_addr.s_addr = test_udp_addr;
    test_servaddr.sin_port = htons(TEST_SOC_PORT);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&test_servaddr,
            sizeof(test_servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(test_cliaddr); //len is value/result
    while(1)
    {
        n = recvfrom(sockfd, (char *)buffer, 2000,
                MSG_WAITALL, ( struct sockaddr *) &test_cliaddr,
                (socklen_t*)&len);
        test_udp_recv_cnt++;
        buffer[n] = '\0';
        printf("Client : %s\n", buffer);
        sendto(sockfd, (const char *)hello, strlen(hello),
                0, (const struct sockaddr *) &test_cliaddr,
                len);
        test_udp_snd_cnt++;
        printf("Hello message sent.\n");
    }

}
#endif

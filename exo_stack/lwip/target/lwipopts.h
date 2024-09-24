/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : lwipopts.h
  * Description        : This file overrides LwIP stack default configuration
  *                      done in opt.h file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef __LWIPOPTS__H__
#define __LWIPOPTS__H__

#include "main.h"
#include "exo_common.h"

/*-----------------------------------------------------------------------------*/
/* Current version of LwIP supported by CubeMx: 2.1.2 -*/
/*-----------------------------------------------------------------------------*/

/* Within 'USER CODE' section, code will be kept by default at each generation */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

#ifdef __cplusplus
 extern "C" {
#endif

/* STM32CubeMX Specific Parameters (not defined in opt.h) ---------------------*/
/* Parameters set in STM32CubeMX LwIP Configuration GUI -*/
/*----- WITH_RTOS enabled (Since FREERTOS is set) -----*/
#define WITH_RTOS 1
/*----- CHECKSUM_BY_HARDWARE disabled -----*/
#define CHECKSUM_BY_HARDWARE 1
/*-----------------------------------------------------------------------------*/

/* LwIP Stack Parameters (modified compared to initialization value in opt.h) -*/
/* Parameters set in STM32CubeMX LwIP Configuration GUI -*/
/*----- Value in opt.h for MEM_ALIGNMENT: 1 -----*/
#define MEM_ALIGNMENT 4
/*----- Default Value for MEM_SIZE: 1600 ---*/
#define MEM_SIZE (16*1024)
#define LWIP_RAM_HEAP_POINTER    (0x20074000)
#define NO_SYS                  0
#define MEMP_NUM_PBUF           10
/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
#define MEMP_NUM_UDP_PCB        6
/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#define MEMP_NUM_TCP_PCB        10
/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
#define MEMP_NUM_TCP_PCB_LISTEN 5
/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#define MEMP_NUM_TCP_SEG        8
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
#define MEMP_NUM_SYS_TIMEOUT    10
/*----- Default Value for MEMP_NUM_SYS_TIMEOUT: 5 ---*/
/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#define PBUF_POOL_SIZE          8

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE       1524





/*----- Value in opt.h for LWIP_ETHERNET: LWIP_ARP || PPPOE_SUPPORT -*/
#define LWIP_ETHERNET 1
/*----- Value in opt.h for LWIP_DNS_SECURE: (LWIP_DNS_SECURE_RAND_XID | LWIP_DNS_SECURE_NO_MULTIPLE_OUTSTANDING | LWIP_DNS_SECURE_RAND_SRC_PORT) -*/
#define LWIP_DNS_SECURE 7
/*----- Value in opt.h for TCP_SND_QUEUELEN: (4*TCP_SND_BUF + (TCP_MSS - 1))/TCP_MSS -----*/
#define TCP_SND_QUEUELEN 8
/*----- Value in opt.h for TCP_SNDLOWAT: LWIP_MIN(LWIP_MAX(((TCP_SND_BUF)/2), (2 * TCP_MSS) + 1), (TCP_SND_BUF) - 1) -*/
#define TCP_SNDLOWAT 1071
/*----- Value in opt.h for TCP_SNDQUEUELOWAT: LWIP_MAX(TCP_SND_QUEUELEN)/2, 5) -*/
#define TCP_SNDQUEUELOWAT 5
/*----- Value in opt.h for TCP_WND_UPDATE_THRESHOLD: LWIP_MIN(TCP_WND/4, TCP_MSS*4) -----*/
//#define TCP_WND_UPDATE_THRESHOLD 536
#define TCP_MSS                 (1500 - 40)
/*----- Value in opt.h for LWIP_NETIF_LINK_CALLBACK: 0 -----*/
#define LWIP_NETIF_LINK_CALLBACK 1
/*----- Value in opt.h for TCPIP_THREAD_STACKSIZE: 0 -----*/
#define TCPIP_THREAD_STACKSIZE 1024*5
/*----- Value in opt.h for TCPIP_THREAD_PRIO: 1 -----*/
#define TCPIP_THREAD_PRIO P_LWIP
/*----- Value in opt.h for TCPIP_MBOX_SIZE: 0 -----*/
#define TCPIP_MBOX_SIZE 2000
/*----- Value in opt.h for SLIPIF_THREAD_STACKSIZE: 0 -----*/
#define SLIPIF_THREAD_STACKSIZE 1024
/*----- Value in opt.h for SLIPIF_THREAD_PRIO: 1 -----*/
#define SLIPIF_THREAD_PRIO P_DEFAULT_PRIO
/*----- Value in opt.h for DEFAULT_THREAD_STACKSIZE: 0 -----*/
#define DEFAULT_THREAD_STACKSIZE 1024*5
/*----- Value in opt.h for DEFAULT_THREAD_PRIO: 1 -----*/
#define DEFAULT_THREAD_PRIO P_DEFAULT_PRIO
/*----- Value in opt.h for DEFAULT_UDP_RECVMBOX_SIZE: 0 -----*/
#define DEFAULT_UDP_RECVMBOX_SIZE 6
/*----- Value in opt.h for DEFAULT_TCP_RECVMBOX_SIZE: 0 -----*/
#define DEFAULT_TCP_RECVMBOX_SIZE 6
/*----- Value in opt.h for DEFAULT_ACCEPTMBOX_SIZE: 0 -----*/
#define DEFAULT_ACCEPTMBOX_SIZE 6
/*----- Value in opt.h for RECV_BUFSIZE_DEFAULT: INT_MAX -----*/
#define RECV_BUFSIZE_DEFAULT 2000000000
/*----- Default Value for PPP_SUPPORT: 0 ---*/
//#define PPP_SUPPORT 1
/*----- Value in opt.h for LWIP_STATS: 1 -----*/
/** Enabled to have time waited send/recv */
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1

/** Set the TCP Retransmission time */
#define LWIP_TCP_RTO_TIME               1000

/**  Number of SYN retry */
/** Note: Currently TCP SYN retransmission is disabled, since it is blocking the tasks
 * */
#define TCP_SYNMAXRTX                   6

//#define LWIP_STATS LWIP_STATS_ENB
/* USER CODE BEGIN 1 */
//#define LWIP_IPV4                1
//#define LWIP_TCP                1
//#define LWIP_MULTICAST_PING             1
/* USER CODE END 1 */
#ifndef CHECKSUM_BY_HARDWARE
#define LWIP_CHECKSUM_CTRL_PER_NETIF 1
 /*----- Value in opt.h for CHECKSUM_GEN_IP: 1 -----*/
 #define CHECKSUM_GEN_IP 1
 /*----- Value in opt.h for CHECKSUM_GEN_UDP: 1 -----*/
 #define CHECKSUM_GEN_UDP 1
 /*----- Value in opt.h for CHECKSUM_GEN_TCP: 1 -----*/
 #define CHECKSUM_GEN_TCP 1
 /*----- Value in opt.h for CHECKSUM_GEN_ICMP: 1 -----*/
 #define CHECKSUM_GEN_ICMP 1
 /*----- Value in opt.h for CHECKSUM_GEN_ICMP6: 1 -----*/
 #define CHECKSUM_GEN_ICMP6 1
 /*----- Value in opt.h for CHECKSUM_CHECK_IP: 1 -----*/
 #define CHECKSUM_CHECK_IP 1
 /*----- Value in opt.h for CHECKSUM_CHECK_UDP: 1 -----*/
 #define CHECKSUM_CHECK_UDP 1
 /*----- Value in opt.h for CHECKSUM_CHECK_TCP: 1 -----*/
 #define CHECKSUM_CHECK_TCP 1
 /*----- Value in opt.h for CHECKSUM_CHECK_ICMP: 1 -----*/
 #define CHECKSUM_CHECK_ICMP 1
 /*----- Value in opt.h for CHECKSUM_CHECK_ICMP6: 1 -----*/
 #define CHECKSUM_CHECK_ICMP6 1

 //Increase the LWIP MEMP memory
 /*LWIP_THROW_TEST = 1 (Enabled)
 1. In this case (PBUF_POOL_SIZE, MEMP_NUM_TCPIP_MSG_INPKT)
 macro are increased by 40, then can achieve 50 packets without delay
 2. Test UDP socket is enabled PORT 6969, IP 192.168.1.111 ->
 In test socket achieve more than 100000 packets with interval of
 1ms and also 100 packets without delay
 Observation: Need to send and receive more than 100 packets interval of 1ms in our actual with LWIP_THROW_TEST
 enabled facing error in LWIP MEMPS so, increase the MEMPS memory's based on error count can achieve it*/
#ifdef LWIP_THROW_TEST
#define MEMP_NUM_TCPIP_MSG_INPKT       40
#define PBUF_POOL_SIZE                 40
#endif
=======
#else 
    #define CHECKSUM_GEN_ICMP 0
#endif    

/* USER CODE END 1 */
#define LWIP_PERF 1
#ifdef __cplusplus
}
#endif
#endif /*__LWIPOPTS__H__ */

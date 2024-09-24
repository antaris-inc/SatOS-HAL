/**
  ******************************************************************************
  * @file    USB_Device/CDC_ECM_Server/app_ecm/usbd_cdc_ecm_if.c
  * @author  MCD Application Team
  * @brief   This file implements Ethernet network interface drivers for lwIP
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */



/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "usb_netif.h"
#include "lwip.h"
#include "netif/etharp.h"
#include "lwip/init.h"
#include "exo_common.h"
#include "exo_types.h"

#define USB_PRINT_EN

struct netif  USBnetif;
extern USBD_HandleTypeDef USBD_Device;
#ifndef EXT_SDRAM_BUFF_USB_ENB
__ALIGN_BEGIN static uint8_t UserRxBuffer[CDC_ECM_ETH_MAX_SEGSZE + 100]__ALIGN_END; /* Received Data over USB are stored in this buffer */

__ALIGN_BEGIN  static uint8_t UserTxBuffer[CDC_ECM_ETH_MAX_SEGSZE + 100]__ALIGN_END; /* Received Data over CDC_ECM (CDC_ECM interface) are stored in this buffer */
#else
__ALIGN_BEGIN static uint8_t PLACE_IN_EXT_RAM_MEM UserRxBuffer[CDC_ECM_ETH_MAX_SEGSZE + 100]__ALIGN_END; /* Received Data over USB are stored in this buffer */

__ALIGN_BEGIN  static uint8_t PLACE_IN_EXT_RAM_MEM UserTxBuffer[CDC_ECM_ETH_MAX_SEGSZE + 100]__ALIGN_END; /* Received Data over CDC_ECM (CDC_ECM interface) are stored in this buffer */
#endif

static uint8_t CDC_ECMInitialized = 0U;

/* Private function prototypes -----------------------------------------------*/
static int8_t CDC_ECM_Itf_Init(void);
static int8_t CDC_ECM_Itf_DeInit(void);
static int8_t CDC_ECM_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_ECM_Itf_Receive(uint8_t *pbuf, uint32_t *Len);
static int8_t CDC_ECM_Itf_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum);
static int8_t CDC_ECM_Itf_Process(USBD_HandleTypeDef *pdev);
void USB_netif_set_link();
static void CDC_ECM_NetifConfig(void);
//static void User_notification(struct netif *netif);


USBD_CDC_ECM_ItfTypeDef USBD_CDC_ECM_fops =
{
		CDC_ECM_Itf_Init,
		CDC_ECM_Itf_DeInit,
		CDC_ECM_Itf_Control,
		CDC_ECM_Itf_Receive,
		CDC_ECM_Itf_TransmitCplt,
		CDC_ECM_Itf_Process,
		(uint8_t *)CDC_ECM_MAC_STR_DESC,
};

static int8_t CDC_ECM_Itf_Init(void)
{
	CDC_ECM_NetifConfig();     /* Configure the Network interface */


	(void)USBD_CDC_ECM_SetTxBuffer(&USBD_Device, UserTxBuffer, 0U);
	(void)USBD_CDC_ECM_SetRxBuffer(&USBD_Device, UserRxBuffer);

	return (0);
}

/**
 * @brief  CDC_ECM_Itf_DeInit
 *         DeInitializes the CDC_ECM media low layer
 * @param  None
 * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_ECM_Itf_DeInit(void)
{
	USBD_CDC_ECM_HandleTypeDef *hcdc_cdc_ecm = (USBD_CDC_ECM_HandleTypeDef *)(USBD_Device.pClassData);

	/* Notify application layer that link is down */
	hcdc_cdc_ecm->LinkStatus = 0U;
	netif_set_down(&USBnetif);
	return (0);
}

/**
 * @brief  CDC_ECM_Itf_Control
 *         Manage the CDC_ECM class requests
 * @param  Cmd: Command code
 * @param  Buf: Buffer containing command data (request parameters)
 * @param  Len: Number of data to be sent (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_ECM_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
	USBD_CDC_ECM_HandleTypeDef *hcdc_cdc_ecm = (USBD_CDC_ECM_HandleTypeDef *)(USBD_Device.pClassData);

	//DEBUG_CPRINT(("\n\rCDC_ECM_Itf_Control - %d" , cmd));

	switch (cmd)
	{
	case CDC_ECM_SEND_ENCAPSULATED_COMMAND:
		/* Add your code here */
		break;

	case CDC_ECM_GET_ENCAPSULATED_RESPONSE:
		/* Add your code here */
		break;

	case CDC_ECM_SET_ETH_MULTICAST_FILTERS:
		/* Add your code here */
		break;

	case CDC_ECM_SET_ETH_PWRM_PATTERN_FILTER:
		/* Add your code here */
		break;

	case CDC_ECM_GET_ETH_PWRM_PATTERN_FILTER:
		/* Add your code here */
		break;

	case CDC_ECM_SET_ETH_PACKET_FILTER:
		/* Check if this is the first time we enter */

		if (hcdc_cdc_ecm->LinkStatus == 0U)
		{
			/* Setup the Link up at LwIP level */
			netif_set_link_up(&USBnetif);
			hcdc_cdc_ecm->LinkStatus = 1U;

			/* Modification for MacOS which doesn't send SetInterface before receiving INs */
			if (hcdc_cdc_ecm->NotificationStatus == 0U)
			{
				/* Send notification: NETWORK_CONNECTION Event */
				(void)USBD_CDC_ECM_SendNotification(&USBD_Device, NETWORK_CONNECTION,
						CDC_ECM_NET_CONNECTED, NULL);

				/* Prepare for sending Connection Speed Change notification */
				hcdc_cdc_ecm->NotificationStatus = 1U;
			}
			//DEBUG_CPRINT(("link enable"));

		}

		/* Add your code here */
		break;

	case CDC_ECM_GET_ETH_STATISTIC:
		/* Add your code here */
		break;

	default:
		break;
	}
	UNUSED(length);
	UNUSED(pbuf);

	return (0);
}

/**
 * @brief  Setup the network interface
 * @param  None
 * @retval None
 *
 */

static void CDC_ECM_NetifConfig(void)
{
	ip_addr_t ipaddr;
	ip_addr_t netmask;
	ip_addr_t gw;

	if (CDC_ECMInitialized == 0U)
	{
		/* Initialize the LwIP stack */
#if 0
		tcpip_init( NULL, NULL );
#endif

		IP4_ADDR(&ipaddr, USB_IP_ADDR0, USB_IP_ADDR1, USB_IP_ADDR2, USB_IP_ADDR3);
		IP4_ADDR(&netmask, 255U, 255U ,255U, 0U);
		IP4_ADDR(&gw, USB_IP_ADDR0, USB_IP_ADDR1, USB_IP_ADDR2, 1U);

		/* add the network interface */
#if (WITH_RTOS==1)
		(void)netif_add(&USBnetif, &ipaddr, &netmask, &gw, NULL, &USB_netif_init, &tcpip_input);
#else
		(void)netif_add(&USBnetif, &ipaddr, &netmask, &gw, NULL, &USB_netif_init, &ethernet_input);
#endif
		/*  Registers the default network interface */
		netif_set_default(&USBnetif);
		CDC_ECMInitialized = 1U;
	}

	if (netif_is_link_up(&USBnetif)== 1U)
	{
		netif_set_up(&USBnetif);
#ifdef USB_PRINT_EN
		DEBUG_CPRINT(("\nUSB netif link down\n"));
#endif
	}
	else
	{
		netif_set_down(&USBnetif);
#ifdef USB_PRINT_EN
		DEBUG_CPRINT(("\nUSB netif link up\n"));
#endif
	}
	netif_set_link_callback(&USBnetif, USB_netif_set_link);
}



static int8_t CDC_ECM_Itf_Receive(uint8_t *Buf, uint32_t *Len)
{
	/* Get the CDC_ECM handler pointer */
	USBD_CDC_ECM_HandleTypeDef *hcdc_cdc_ecm = (USBD_CDC_ECM_HandleTypeDef *)(USBD_Device.pClassData);

	/* Call Eth buffer processing */
	hcdc_cdc_ecm->RxState = 1U;
	//DEBUG_CPRINT(("\n\rCDC_ECM_Itf_Receive"));
	UNUSED(Len);
	UNUSED(Buf);

	return (0);
}


static int8_t CDC_ECM_Itf_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum)
{
	UNUSED(Buf);
	UNUSED(Len);
	UNUSED(epnum);

	return (0);
}


static int8_t CDC_ECM_Itf_Process(USBD_HandleTypeDef *pdev)
{
	/* Get the CDC_ECM handler pointer */
	USBD_CDC_ECM_HandleTypeDef   *hcdc_cdc_ecm = (USBD_CDC_ECM_HandleTypeDef *)(pdev->pClassData);

	if ((hcdc_cdc_ecm != NULL) && (hcdc_cdc_ecm->LinkStatus != 0U))
	{
		/* Read a received packet from the Ethernet buffers and send it to the lwIP for handling */
		if ((hcdc_cdc_ecm->RxLength > 0U) && (hcdc_cdc_ecm->RxState == 1U))
		{
			USB_netif_input(&USBnetif);
		}
	}

	return (0);
}




void USB_netif_set_link()
{
	ip_addr_t ipaddr;
	ip_addr_t netmask;
	ip_addr_t gw;

	if (netif_is_link_up(&USBnetif)== 1U)
	{
		/* When the netif is fully configured this function must be called */
		IP4_ADDR(&ipaddr, USB_IP_ADDR0, USB_IP_ADDR1, USB_IP_ADDR2, USB_IP_ADDR3);
		IP4_ADDR(&netmask,255U ,255U,255U,0);
		IP4_ADDR(&gw, USB_IP_ADDR0, USB_IP_ADDR1, USB_IP_ADDR2, 1U);
		netif_set_addr(&USBnetif, &ipaddr , &netmask, &gw);
		netif_set_up(&USBnetif);
#ifdef USB_PRINT_EN
		DEBUG_CPRINT(("\nUSB netif link up\n"));
#endif
	}
	else
	{
		/* When the netif link is down this function must be called */
		netif_set_down(&USBnetif);
#ifdef USB_PRINT_EN
		DEBUG_CPRINT(("\nUSB netif link down\n"));
#endif
	}

#if 0
	USBD_CDC_ECM_HandleTypeDef  *hcdc_cdc_ecm = (USBD_CDC_ECM_HandleTypeDef *)(USBD_Device.pClassData);
	if((hcdc_cdc_ecm != NULL))
	{
		if((netif_is_link_up(&USBnetif) != 1) && (hcdc_cdc_ecm->LinkStatus != 0U))
		{
			/* When the netif is fully configured this function must be called */
			netif_set_up(&USBnetif);
			DEBUG_CPRINT(("\nUSB netif link up\n"));
		}
		else if ((netif_is_link_up(&USBnetif) == 1) && (hcdc_cdc_ecm->LinkStatus == 0U))
		{
			/* When the netif link is down this function must be called */
			netif_set_down(&USBnetif);
			DEBUG_CPRINT(("\nUSB netif link down\n"));
		}
	}
#endif
}


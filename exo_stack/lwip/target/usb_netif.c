/**
  ******************************************************************************
  * @file    usb_netif.c
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
#include "stm32f7xx_hal_ext.h"
#include "lwip/timeouts.h"
#include "netif/etharp.h"
#include "usb_netif.h"
#include "cmsis_os.h"
#include <string.h>
#include "lwip/tcpip.h"
#include "ethernetif.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Network interface name */
#define IFNAME0 's'
#define IFNAME1 't'

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USBD_HandleTypeDef USBD_Device;

/* USER CODE BEGIN PV */
/* Definitions for USB_RX */
osThreadId_t USB_RXHandle;
const osThreadAttr_t USB_RX_attributes = {
  .name = "USB_RX",
  .stack_size = 1280 * 4,
  .priority = (osPriority_t) P_USB,
  //.priority = (osPriority_t) osPriorityRealtime,
};

/* Definitions for USB_xSemaphore */
osSemaphoreId_t USB_xSemaphoreHandle;
const osSemaphoreAttr_t USB_xSemaphore_attributes = {
  .name = "USB_xSemaphore"
};

#if 0
extern struct netif  USBnetif;
struct link_str link_arg_USB;
/* Definitions for USBnetifLink */
osThreadId_t USBnetifLinkHandle;
const osThreadAttr_t USBnetifLink_attributes = {
  .name = "USBnetifLink",
  .stack_size = 1024 * 4,
  //.priority = (osPriority_t) osPriorityBelowNormal,
  .priority = (osPriority_t) P_DEFAULT_PRIO,
};

/* Definitions for USB_Netif_LinkSemaphore */
osSemaphoreId_t USB_Netif_LinkSemaphoreHandle;
const osSemaphoreAttr_t USB_Netif_LinkSemaphore_attributes = {
  .name = "USB_Netif_LinkSemaphore"
};


#endif



/* Private function prototypes -----------------------------------------------*/
u32_t sys_now(void);

void usb_fs_start(void)
{
	USB_xSemaphoreHandle = osSemaphoreNew(1, 1, &USB_xSemaphore_attributes);
	USB_RXHandle = osThreadNew(StartUSB_RX, NULL, &USB_RX_attributes);
#if 0
    link_arg_USB.netif = &USBnetif;
	link_arg_USB.semaphore = USB_Netif_LinkSemaphoreHandle;
	USB_Netif_LinkSemaphoreHandle = osSemaphoreNew(1, 1, &USB_Netif_LinkSemaphore_attributes);
	USBnetifLinkHandle = osThreadNew(Start_USBnetifLink, (void*) &link_arg_USB, &USBnetifLink_attributes);
#endif
}


void USB_ETH_RxCpltCallback()
{
  osSemaphoreRelease(USB_xSemaphoreHandle);
}
    /* USER CODE BEGIN 3 */

/* USER CODE END Header_StartUSB_RX */
void StartUSB_RX(void *argument)
{
  /* USER CODE BEGIN StartUSB_RX */
  /* Infinite loop */
  for(;;)
  {
	  if (osSemaphoreAcquire(USB_xSemaphoreHandle, osWaitForever) == osOK)
  	  {
			USBD_CDC_ECM_fops.Process(&USBD_Device);
  	  }
  }
  /* USER CODE END StartUSB_RX */
}

/* USER CODE BEGIN Header_Start_USBnetifLink */
/**
* @brief Function implementing the USBnetifLink thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_USBnetifLink */
#if 0
void Start_USBnetifLink(void *argument)
{
  /* USER CODE BEGIN Start_USBnetifLink */
  /* Infinite loop */
  for(;;)
  {
	USB_netif_set_link();
    osDelay(200);
  }
  /* USER CODE END Start_USBnetifLink */
}
#endif
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
                       Ethernet MSP Routines
*******************************************************************************/

/*******************************************************************************
                       LL Driver Interface ( LwIP stack --> USB)
*******************************************************************************/
/**
  * @brief In this function, the hardware should be initialized.
  * Called from ethernetif_init().
  *
  * @param netif the already initialized lwip network interface structure
  *        for this ethernetif
  */
static void USB_low_level_init(struct netif *netif)
{
  /* set MAC hardware address length */

  netif->hwaddr_len = ETH_HWADDR_LEN;

  /* Set MAC hardware address */
  netif->hwaddr[0] =  USB_MAC_ADDR0;
  netif->hwaddr[1] =  USB_MAC_ADDR1;
  netif->hwaddr[2] =  USB_MAC_ADDR2;
  netif->hwaddr[3] =  USB_MAC_ADDR3;
  netif->hwaddr[4] =  USB_MAC_ADDR4;
  netif->hwaddr[5] =  USB_MAC_ADDR5;

  /* maximum transfer unit */
  netif->mtu = 1500;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

//  usb_fs_start();

}

/**
  * @brief This function should do the actual transmission of the packet. The packet is
  * contained in the pbuf that is passed to the function. This pbuf
  * might be chained.
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
  * @return ERR_OK if the packet could be sent
  *         an err_t value if the packet couldn't be sent
  *
  * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
  *       strange results. You might consider waiting for space in the DMA queue
  *       to become available since the stack doesn't retry to send a packet
  *       dropped because of memory failure (except for the TCP timers).
  */
static err_t USB_low_level_output(struct netif *netif, struct pbuf *p)
{
  struct pbuf *q;
  uint8_t *pdata;
  uint32_t Trials = CDC_ECM_MAX_TX_WAIT_TRIALS;
  USBD_CDC_ECM_HandleTypeDef *hcdc = (USBD_CDC_ECM_HandleTypeDef*) (USBD_Device.pClassData);
  //DEBUG_CPRINT(("\n\rUSB_low_level_output"));
  /* Check if the TX State is not busy */
  while ((hcdc->TxState != 0U) && (Trials > 0U))
  {
    Trials--;
  }

  /* If no success getting the TX state ready, return error */
  if (Trials == 0U)
  {
	  //DEBUG_CPRINT(("Tx not ready"));
    return (err_t)ERR_USE;
  }

  pdata = hcdc->TxBuffer;
  hcdc->TxLength = 0;

  for(q = p; q != NULL; q = q->next)
  {
    (void)memcpy(pdata, q->payload, q->len);
    pdata += q->len;
    hcdc->TxLength += q->len;
  }

  /* Set the TX buffer information */

  (void)USBD_CDC_ECM_SetTxBuffer(&USBD_Device, hcdc->TxBuffer, (uint16_t)hcdc->TxLength);

  /* Start transmitting the Tx buffer */
  if(USBD_CDC_ECM_TransmitPacket(&USBD_Device) == (uint8_t)USBD_OK)
  {
	//DEBUG_CPRINT(("TX completed"));
    return (err_t)ERR_OK;
  }

  UNUSED(netif);
  return (err_t)ERR_USE;
}

/**
  * @brief Should allocate a pbuf and transfer the bytes of the incoming
  *        packet from the interface into the pbuf.
  *
  * @param pnetif the lwip network interface structure for this ethernetif
  * @return a pbuf filled with the received packet (including MAC header)
  *         NULL on memory error
  */
static struct pbuf *USB_low_level_input(struct netif *pnetif)
{
  struct pbuf *p = NULL;

  USBD_CDC_ECM_HandleTypeDef *hcdc = (USBD_CDC_ECM_HandleTypeDef*) (USBD_Device.pClassData);

  /* Get the length of the current buffer */
  if ((hcdc->RxLength > 0U) && (hcdc->RxState == 1U))
  {
    /* Allocate a pbuf chain of pbufs from the Lwip buffer pool */
    p = pbuf_alloc(PBUF_RAW, (uint16_t)hcdc->RxLength, PBUF_POOL);
  }

  /* Check that allocation was done correctly */
  if (p != NULL)
  {
    /* Copy the buffer data in the allocated buffer */
    (void)memcpy(p->payload, (uint8_t *)hcdc->RxBuffer, (uint16_t)hcdc->RxLength);
    p->len = (uint16_t)hcdc->RxLength;

    #if 0
     uint16_t i=0;
	 DEBUG_CPRINT(("\n\rUSB_RX[%d]-",p->len));

     while(i< p->len)
    	DEBUG_CPRINT(("%X ", hcdc->RxBuffer[i++]));

     DEBUG_CPRINT(("\n\r"));
    #endif
  }
  UNUSED(pnetif);

  return p;
}

/**
  * @brief This function should be called when a packet is ready to be read
  * from the interface. It uses the function low_level_input() that
  * should handle the actual reception of bytes from the network
  * interface. Then the type of the received packet is determined and
  * the appropriate input function is called.
  *
  * @param pnetif the lwip network interface structure for this ethernetif
  */
void USB_netif_input(struct netif *pnetif)
{
//  err_t err;
  struct pbuf *p;

  USBD_CDC_ECM_HandleTypeDef *hcdc = (USBD_CDC_ECM_HandleTypeDef*) (USBD_Device.pClassData);


  /* move received packet into a new pbuf */
  //DEBUG_CPRINT(("\n\rUSB_netif_input"));
do
{

  p = USB_low_level_input(pnetif);

  if(p==NULL)
      break;

  LOCK_TCPIP_CORE();


  /* entry point to the LwIP stack */

  if (pnetif->input(p, pnetif) != (err_t)ERR_OK)
  {
    (void)pbuf_free(p);
    p = NULL;
  }
  UNLOCK_TCPIP_CORE();


  /* Reset the Received buffer length to zero for next transfer */
  hcdc->RxLength = 0U;
  hcdc->RxState = 0U;

  /* Prepare Out endpoint to receive next packet in current/new frame */
  (void)USBD_LL_PrepareReceive(&USBD_Device, CDC_ECM_OUT_EP,
                               (uint8_t*)(hcdc->RxBuffer), hcdc->MaxPcktLen);

} while(p!=NULL);
  /* Free the allocated buffer :
     The allocated buffer is freed by low layer ethernet functions.
  */

}

/**
  * @brief Should be called at the beginning of the program to set up the
  * network interface. It calls the function low_level_init() to do the
  * actual setup of the hardware.
  *
  * This function should be passed as a parameter to netif_add().
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @return ERR_OK if the loopif is initialized
  *         ERR_MEM if private data couldn't be allocated
  *         any other err_t on error
  */
err_t USB_netif_init(struct netif *netif)
{
  //DEBUG_CPRINT(("\n\rUSB_netif_init"));
  //DEBUG_CPRINT(("\n\rnetif != NULL", (netif != NULL)));
  LWIP_ASSERT("netif != NULL", (netif != NULL));

  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;

  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = USB_low_level_output;

  /* initialize the hardware */
  USB_low_level_init(netif);


  return (err_t)ERR_OK;
}




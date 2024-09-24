/**
  ******************************************************************************
  * @file    usb_netif.h
  * @author  MCD Application Team
  * @brief   Header for ethernetif.c.
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

#ifndef __USB_NETIF_H__
#define __USB_NETIF_H__

#include "lwip/err.h"
#include "lwip/netif.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_cdc_ecm_if.h"
#include "usbd_desc.h"
#include "usbd_cdc_ecm.h"
#include "usbd_core.h"


/* Exported types ------------------------------------------------------------*/
err_t USB_netif_init(struct netif *netif);
void USB_netif_input(struct netif *pnetif);
void USB_netif_update_config(struct netif *netif);
void USB_netif_notify_conn_changed(struct netif *netif);


void USB_netif_proc();
void usb_fs_start(void);
void StartUSB_RX(void *argument);
void Start_USBnetifLink(void *argument);
void USB_ETH_RxCpltCallback();


#endif

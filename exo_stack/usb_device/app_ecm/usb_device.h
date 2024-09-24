/**
  ******************************************************************************
  * @file    USB_Device/CDC_ECM_Server/app_ecm/usb_device.h
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DEVICE__H__
#define __USB_DEVICE__H__


/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal_ext.h"
#include "stm32f7xx.h"

#include "usbd_def.h"


void MX_USB_DEVICE_Init(void);
#endif /* __USB_DEVICE__H__ */


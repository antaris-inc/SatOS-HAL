/**
  ******************************************************************************
  * @file    USB_Device/CDC_ECM_Server/app_ecm/usbd_desc.h
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

#ifndef __USBD_DESC_H
#define __USBD_DESC_H

/* Includes ------------------------------------------------------------------*/
#include "../stm32_usb_device_library/core_ecm/Inc/usbd_def.h"

#define  USB_SIZ_STRING_SERIAL       0x1A

extern USBD_DescriptorsTypeDef CDC_ECM_Desc;

#endif /* __USBD_DESC_H */
 

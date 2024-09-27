/**
  ******************************************************************************
  * @file    USB_Device/CDC_ECM_Server/app_ecm/usb_device.c
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

#include "usb_device.h"

#include "usbd_cdc_ecm_if.h"
#include "usbd_desc.h"
#include "usbd_cdc_ecm.h"
#include "usbd_core.h"
#include "usb_netif.h"

/* Private variables ---------------------------------------------------------*/

extern USBD_HandleTypeDef USBD_Device;
/* Private function prototypes -----------------------------------------------*/

extern void Error_Handler(void);
/* USB Device Core handle declaration. */

/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */

void MX_USB_DEVICE_Init(void)
{

#ifdef STM32F765xx
  /* Init Device Library */
  if (USBD_Init(&USBD_Device, &CDC_ECM_Desc, 0) != USBD_OK)
  {
    Error_Handler();
  }
#else
#ifdef STM32F769xx
  if (USBD_Init(&USBD_Device, &CDC_ECM_Desc, 1) != USBD_OK)
   {
     Error_Handler();
   }
#endif
#endif
  /* Add Supported Class */
  if (USBD_RegisterClass(&USBD_Device, USBD_CDC_ECM_CLASS) != USBD_OK)
  {
    Error_Handler();
  }

  /* Add CDC Interface Class */
  if (USBD_CDC_ECM_RegisterInterface(&USBD_Device, &USBD_CDC_ECM_fops) != (uint8_t) USBD_OK)
  {
    Error_Handler();
  }

  /* Start Device Process */
  if (USBD_Start(&USBD_Device) != USBD_OK)
  {
    Error_Handler();
  }

  usb_fs_start();
}

/**
  * @}
  */

/**
  * @}
  */


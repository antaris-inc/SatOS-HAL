/**
  ******************************************************************************
  * @file    USB_Device/CDC_ECM_Server/app_ecm/usbd_desc.c
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
#include "../app_ecm/usbd_desc.h"

#include "../app_ecm/usbd_cdc_ecm_if.h"
#include "../stm32_usb_device_library/core_ecm/Inc/usbd_core.h"
#include "../target_ecm/usbd_conf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USBD_VID                      0x0483U
#define USBD_PID                      0x5741U
#define USBD_LANGID_STRING            0x409U
#define USBD_MANUFACTURER_STRING      "STMicroelectronics"
#define USBD_PRODUCT_HS_STRING        "STM32 CDC ECM in HS Mode"
#define USBD_PRODUCT_FS_STRING        "STM32 CDC ECM in FS Mode"
#define USBD_CONFIGURATION_HS_STRING  "CDC ECM Config"
#define USBD_INTERFACE_HS_STRING      "CDC ECM Interface"
#define USBD_CONFIGURATION_FS_STRING  "CDC ECM Config"
#define USBD_INTERFACE_FS_STRING      "CDC ECM Interface"

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint8_t *USBD_CDC_ECM_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CDC_ECM_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CDC_ECM_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CDC_ECM_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CDC_ECM_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CDC_ECM_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CDC_ECM_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);

/* Private variables ---------------------------------------------------------*/
USBD_DescriptorsTypeDef CDC_ECM_Desc = {
  USBD_CDC_ECM_DeviceDescriptor,
  USBD_CDC_ECM_LangIDStrDescriptor,
  USBD_CDC_ECM_ManufacturerStrDescriptor,
  USBD_CDC_ECM_ProductStrDescriptor,
  USBD_CDC_ECM_SerialStrDescriptor,
  USBD_CDC_ECM_ConfigStrDescriptor,
  USBD_CDC_ECM_InterfaceStrDescriptor,
};

/* USB Standard Device Descriptor */
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN static uint8_t USBD_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END = {
  0x12,                       /* bLength */
  USB_DESC_TYPE_DEVICE,       /* bDescriptorType */
  0x00,                       /* bcdUSB */
  0x02,
  0xEF,                       /* bDeviceClass */
  0x02,                       /* bDeviceSubClass */
  0x01,                       /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,           /* bMaxPacketSize */
  LOBYTE(USBD_VID),           /* idVendor */
  HIBYTE(USBD_VID),           /* idVendor */
  LOBYTE(USBD_PID),           /* idVendor */
  HIBYTE(USBD_PID),           /* idVendor */
  0x00,                       /* bcdDevice rel. 2.00 */
  0x02,
  USBD_IDX_MFC_STR,           /* Index of manufacturer string */
  USBD_IDX_PRODUCT_STR,       /* Index of product string */
  USBD_IDX_SERIAL_STR,        /* Index of serial number string */
  USBD_MAX_NUM_CONFIGURATION  /* bNumConfigurations */
}; /* USB_DeviceDescriptor */

/* USB Standard Device Descriptor */
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN static uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END = {
  USB_LEN_LANGID_STR_DESC,
  USB_DESC_TYPE_STRING,
  LOBYTE(USBD_LANGID_STRING),
  HIBYTE(USBD_LANGID_STRING),
};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN static uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;

uint8_t *USBD_CDC_ECM_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_DeviceDesc);
  UNUSED(speed);
  UNUSED(USBD_LangIDDesc);
  return (uint8_t*)USBD_DeviceDesc;
}

uint8_t *USBD_CDC_ECM_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_LangIDDesc);
  UNUSED(speed);
  UNUSED(USBD_DeviceDesc);
  return (uint8_t*)USBD_LangIDDesc;
}
uint8_t *USBD_CDC_ECM_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == USBD_SPEED_HIGH)
  {
    USBD_GetString((uint8_t *)USBD_PRODUCT_HS_STRING, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_PRODUCT_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

uint8_t *USBD_CDC_ECM_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  USBD_GetString((uint8_t *)USBD_MANUFACTURER_STRING, USBD_StrDesc, length);
  UNUSED(speed);
  return USBD_StrDesc;
}
uint8_t *USBD_CDC_ECM_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  USBD_GetString (CDC_ECM_MAC_STR_DESC, USBD_StrDesc, length);
  UNUSED(speed);
  return USBD_StrDesc;
}
uint8_t *USBD_CDC_ECM_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == USBD_SPEED_HIGH)
  {
    USBD_GetString((uint8_t *)USBD_CONFIGURATION_HS_STRING, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_CONFIGURATION_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

uint8_t *USBD_CDC_ECM_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == USBD_SPEED_HIGH)
  {
    USBD_GetString((uint8_t *)USBD_INTERFACE_HS_STRING, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_INTERFACE_FS_STRING, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}



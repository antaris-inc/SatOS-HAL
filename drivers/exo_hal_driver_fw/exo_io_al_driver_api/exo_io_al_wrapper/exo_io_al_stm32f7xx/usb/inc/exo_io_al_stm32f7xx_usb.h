/**
 * @file exo_io_al_stm32f7xx_usb.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for USB interface
 *
 * @copyright Copyright 2023 Antaris, Inc.
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
 */

#ifndef _IO_AL_STM32F7XX_USB_H_
#define _IO_AL_STM32F7XX_USB_H_

#include "exo_types.h"
#include "exo_io_al_usb_common.h"
#include "exo_hal_common.h"
#include "exo_io_al_common.h"

/**
 * @brief  VDP layer USB callback ID
 */
typedef enum
{
    IOHAL_STM32_USBDEV_SOF_CB_ID,			 	/*!< USB SOF complete callback ID */
    IOHAL_STM32_USBDEV_SETUP_STAGE_CB_ID,		/*!< USB setup stage callback ID */
    IOHAL_STM32_USBDEV_RESET_CB_ID,				/*!< USB reset callback ID */
    IOHAL_STM32_USBDEV_SUSPEND_CB_ID,			/*!< USB suspend callback ID */
    IOHAL_STM32_USBDEV_RESUME_CB_ID,			/*!< USB resume callback ID */
    IOHAL_STM32_USBDEV_CONNECT_CB_ID,			/*!< USB connect callback ID */
    IOHAL_STM32_USBDEV_DISCONNECT_CB_ID,		/*!< USB disconnect callback ID */
    IOHAL_STM32_USBDEV_DATA_OUT_STAGE_CB_ID,	/*!< USB data outstage callback ID */
    IOHAL_STM32_USBDEV_DATA_IN_STAGE_CB_ID, 	/*!< USB data instage callback ID */
    IOHAL_STM32_USBDEV_ISO_OUT_INCPLT_CB_ID,	/*!< USB iso out incomplete callback ID */
    IOHAL_STM32_USBDEV_ISO_IN_INCPLT_CB_ID  	/*!< USB iso in incomplete callback ID */

}iohal_stm32_usbdev_cbid;

/**
 * @brief This function initialize the control block memory and do basic configurations of USB
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_init(ioal_usb_hdle *ioal_husbdev);
/**
 * @brief This function deinit the USB
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_deinit (ioal_usb_hdle *ioal_husbdev);
/**
 * @brief This function start the USB device
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_start(ioal_usb_hdle *ioal_husbdev);
/**
 * @brief This function stop the USB device
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_stop(ioal_usb_hdle *ioal_husbdev);
/**
 * @brief This function register the callback event
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] cbid - ID of the callback event
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_reg_cb(ioal_usb_hdle *ioal_husbdev, iohal_stm32_usbdev_cbid cbid);

/**
 * @brief This function connect the USB device
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_devconnect (ioal_usb_hdle *ioal_husbdev);
/**
 * @brief This function disconnect the USB device
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_devdisconnect (ioal_usb_hdle *ioal_husbdev);
/**
 * @brief This function set the USB device address
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] address - address of the device
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_setaddress (ioal_usb_hdle *ioal_husbdev, uint8_t address);
/**
 * @brief This function opens and configures an endpoint
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] ep_addr - endpoint address
 * @param[in] ep_mps - endpoint maximum packet size
 * @param[in] ep_type - endpoint type
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_open (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type);
/**
 * @brief This function deactivate an endpoint
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] ep_addr - endpoint address
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_close (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr);
/**
 * @brief This function receive an amount of data from the specified endpoint address
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] ep_addr - endpoint address
 * @param[in] pbuf - pointer to a buffer
 * @param[in] len - length of the data
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_receive (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr, uint8_t * pbuf,uint32_t len);
/**
 * @brief This function get number of receive count for the specified endpoint address
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] ep_addr - endpoint address
 * @retval Hal status
 */
uint32_t io_hal_stm32f7xx_usbdev_ep_getrxcount (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr);
/**
 * @brief This function send an amount of data for the specified endpoint address
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] ep_addr - endpoint address
 * @param[in] pbuf - pointer to a buffer
 * @paam[in] len - length of the data
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_transmit (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr, uint8_t * pbuf, uint32_t len);
/**
 * @brief This function set a stall condition for the specified endpoint address
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] ep_addr - endpoint address
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_setstall (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr);
/**
 * @brief This function clear a stall condition for the specified endpoint address
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] ep_addr - endpoint address
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_clrstall (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr);
/**
 * @brief This function flush the specified endpoint
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] ep_addr - endpoint address
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_flush (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr);
/**
 * @brief This function activate remote wakeup
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_activate_remote_wakeup (ioal_usb_hdle *ioal_husbdev);
/**
 * @brief This function deactivate remote wakeup
 * @param[in] ioal_husbdev - ioal_husbdev pointer to a ioal_usb_hdle structure that contains
 * 							the configuration information for UART
 * @retval Hal status
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_deactivate_remote_wakeup (ioal_usb_hdle *ioal_husbdev);


/* API Mapping */
#define io_hal_common_usb_device_init 						io_hal_stm32f7xx_usbdev_init
#define io_hal_common_usb_device_deinit 				    io_hal_stm32f7xx_usbdev_deinit
#define io_hal_common_usb_device_start 						io_hal_stm32f7xx_usbdev_start
#define io_hal_common_usb_device_stop 						io_hal_stm32f7xx_usbdev_stop
#define io_hal_common_usb_device_reg_cb						io_hal_stm32f7xx_usbdev_reg_cb
#define  io_hal_common_usb_device_devconnect                io_hal_stm32f7xx_usbdev_devconnect
#define  io_hal_common_usb_device_devdisconnect             io_hal_stm32f7xx_usbdev_devdisconnect
#define  io_hal_common_usb_device_setaddress                io_hal_stm32f7xx_usbdev_setaddress
#define  io_hal_common_usb_device_ep_open                   io_hal_stm32f7xx_usbdev_ep_open
#define  io_hal_common_usb_device_ep_close                  io_hal_stm32f7xx_usbdev_ep_close
#define  io_hal_common_usb_device_ep_receive                io_hal_stm32f7xx_usbdev_ep_receive
#define  io_hal_common_usb_device_ep_getrxcount             io_hal_stm32f7xx_usbdev_ep_getrxcount
#define  io_hal_common_usb_device_ep_transmit               io_hal_stm32f7xx_usbdev_ep_transmit
#define  io_hal_common_usb_device_ep_setstall               io_hal_stm32f7xx_usbdev_ep_setstall
#define  io_hal_common_usb_device_ep_clrstall               io_hal_stm32f7xx_usbdev_ep_clrstall
#define  io_hal_common_usb_device_ep_flush                  io_hal_stm32f7xx_usbdev_ep_flush
#define  io_hal_common_usb_device_activate_remote_wakeup    io_hal_stm32f7xx_usbdev_activate_remote_wakeup
#define  io_hal_common_usb_device_deactivate_remote_wakeup  io_hal_stm32f7xx_usbdev_deactivate_remote_wakeup
#endif /* _IO_AL_STM32F7XX_USB_H_ */

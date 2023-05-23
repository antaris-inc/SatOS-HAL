/**
 * @file exo_io_al_usb_common.h
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

#ifndef _IO_AL_USB_COMMON_H_
#define _IO_AL_USB_COMMON_H_



#define USB_INTF_ENB
#include <stdint.h>
#include "exo_io_al_common.h"
#include "exo_hal_common.h"

/**
 * @brief IO-HAl USB interface control block handle structure definition
 */
typedef struct _ioal_usb_hdle
{
    ioal_intf_gen_info intf_gen_info;                                       /*!< Hold general information of interface  			*/
    void (*sof_cb)(struct _ioal_usb_hdle *husbdev);							/*!< Fn address of sof event callback   				*/
    void (*setup_stage_cb)(struct _ioal_usb_hdle *husbdev);					/*!< Fn address of setup stage event callback   		*/
    void (*reset_cb)(struct _ioal_usb_hdle *husbdev);						/*!< Fn address of reset callback   					*/
    void (*suspend_cb)(struct _ioal_usb_hdle *husbdev);						/*!< Fn address of suspend callback   					*/
    void (*resume_cb)(struct _ioal_usb_hdle *husbdev);						/*!< Fn address of resume event callback   				*/
    void (*connect_cb)(struct _ioal_usb_hdle *husbdev);						/*!< Fn address of connect event callback   			*/
    void (*disconnect_cb)(struct _ioal_usb_hdle *husbdev);					/*!< Fn address of disconnect event callback   			*/
    void (*data_out_stage_cb)(struct _ioal_usb_hdle *husbdev, uint8 epnum); /*!< Fn address of data out stage event callback   		*/
    void (*data_in_stage_cb)(struct _ioal_usb_hdle *husbdev, uint8 epnum);	/*!< Fn address of data in stage event callback   		*/
    void (*iso_out_incplt_cb)(struct _ioal_usb_hdle *husbdev, uint8 epnum); /*!< Fn address of iso out incomplete event callback   	*/
    void (*iso_in_incplt_cb)(struct _ioal_usb_hdle *husbdev, uint8 epnum);  /*!< Fn address of iso in incompleteevent callback   	*/
}ioal_usb_hdle;

/**
 * @brief This function initialize the control block memory and do the basic configurations for USB
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_init();
/**
 * @brief This function deinitialize the control block memory of USB
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_deinit();
/**
 * @brief This function start the USB device
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_start(ioal_usb_hdle *husbdev);
/**
 * @brief This function stop the USB device
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_stop(ioal_usb_hdle *husbdev);
/**
 * @brief This function initialize the callback event
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval No return
 */
void io_hal_usb_dev_cb_init(ioal_usb_hdle *husbdev);
/**
 * @brief This function connect the USB device
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_devconnect (ioal_usb_hdle *husbdev);
/**
 * @brief This function disconnect the USB device
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_devdisconnect (ioal_usb_hdle *husbdev);
/**
 * @brief This function set the USB device address
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] address - address of the device
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_setaddress (ioal_usb_hdle *husbdev, uint8_t address);
/**
 * @brief This function opens and configures an endpoint
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] ep_addr - endpoint address
 * @param[in] ep_mps - endpoint maximum packet size
 * @param[in] ep_type - endpoint type
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_ep_open (ioal_usb_hdle *husbdev, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type);
/**
 * @brief This function deactivate an endpoint
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] ep_addr - endpoint address
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_ep_close (ioal_usb_hdle *husbdev, uint8_t ep_addr);
/**
 * @brief This function receive an amount of data from the specified endpoint address
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] ep_addr - endpoint address
 * @param[out]pbuf - pointer to a data
 * @param[in] len - length of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_ep_receive (ioal_usb_hdle *husbdev, uint8_t ep_addr, uint8_t *pbuf,uint32_t len);
/**
 * @brief This function get number of receive count for the specified endpoint address
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] ep_addr - endpoint address
 * @retval HAL status
 */
uint32_t io_hal_usb_device_ep_getrxcount (ioal_usb_hdle *husbdev, uint8_t ep_addr);
/**
 * @brief This function send an amount of data for the specified endpoint address
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] ep_addr - endpoint address
 * @param[in] pbuf - pointer to a data
 * @param[in] len - length of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_ep_transmit (ioal_usb_hdle *husbdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t len);
/**
 * @brief This function set a stall condition for the specified endpoint address
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] ep_addr - endpoint address
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_ep_setstall (ioal_usb_hdle *husbdev, uint8_t ep_addr);
/**
 * @brief This function clear a stall condition for the specified endpoint address
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] ep_addr - endpoint address
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_ep_clrstall (ioal_usb_hdle *husbdev, uint8_t ep_addr);
/**
 * @brief This function flush the specified endpoint
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] ep_addr - endpoint address
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_ep_flush (ioal_usb_hdle *husbdev, uint8_t ep_addr);
/**
 * @brief This function activate the remote wakeup
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_activate_remote_wakeup (ioal_usb_hdle *husbdev);
/**
 * @brief This function deactivate the remote wakeup
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval HAL status
 */
hal_ret_sts io_hal_usb_device_deactivate_remote_wakeup (ioal_usb_hdle *husbdev);
/**
 * @brief Setup stage event callback function
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval No return
 */
void io_hal_pcd_setupstage_cb(ioal_usb_hdle *ioal_husbdev);
/**
 * @brief Disconnect event callback  function
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval No return
 */
void io_hal_pcd_disconnect_cb(ioal_usb_hdle *ioal_husbdev);
/**
 * @brief Connect event callback  function
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval No return
 */
void io_hal_pcd_connect_cb(ioal_usb_hdle *ioal_husbdev);
/**
 * @brief ISO in incomplete callback event
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] epnum - endpoint number
 * @retval No return
 */
void io_hal_pcd_iso_in_incomplete_cb(ioal_usb_hdle *ioal_husbdev, uint8_t epnum);
/**
 * @brief ISO out incomplete callback event
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] epnum - endpoint number
 * @retval No return
 */
void io_hal_pcd_iso_out_incomplete_cb(ioal_usb_hdle *ioal_husbdev, uint8_t epnum);
/**
 * @brief Resume callback event function
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval No return
 */
void io_hal_pcd_resume_cb(ioal_usb_hdle *ioal_husbdev);
/**
 * @brief Reset callback event function
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval No return
 */
void io_hal_pcd_reset_cb(ioal_usb_hdle *ioal_husbdev);
/**
 * @brief SOF callback event function
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval No return
 */
void io_hal_pcd_sof_cb(ioal_usb_hdle *ioal_husbdev);
/**
 * @brief Suspend the callback event function
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @retval No return
 */
void io_hal_pcd_suspend_cb(ioal_usb_hdle *ioal_husbdev);
/**
 * @brief Data outstage callback event function
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] epnum - endpoint number
 * @retval No return
 */
void io_hal_pcd_dataoutstage_cb(ioal_usb_hdle *ioal_husbdev, uint8_t epnum);
/**
 * @brief Data instage callback event function
 * @param[in] husbdev - husbdev pointer to a ioal_usb_hdle structure that contains
 *             the configuration information for USB module
 * @param[in] epnum - endpoint number
 * @retval No return
 */
void io_hal_pcd_datainstage_cb(ioal_usb_hdle *ioal_husbdev, uint8_t epnum);

#ifdef LINUX_TEMP_PORT
void linux_usb_dummy_fn(struct _ioal_usb_hdle *husb);
void linux_usb_io_dummy_fn(struct _ioal_usb_hdle *husb, uint8_t val);
#endif

#endif /* _IO_AL_USB_COMMON_H_ */

/**
 * @file exo_io_al_usb_common.c
 *
 * @brief This file contains abstracted function definition for USB interface
 *
 * @copyright Copyright 2024 Antaris, Inc.
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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "exo_io_al_usb_common.h"
#include "exo_hal_io_al_common.h"

#ifndef LINUX_TEMP_PORT
#include "exo_io_al_stm32f7xx_usb.h"
#else
#include "exo_io_al_linux_usb.h"
#endif

#ifndef LINUX_TEMP_PORT
#define USB_DEV_SOF_CB              io_hal_pcd_sof_cb                               ///< USB SOF callback event
#define USB_DEV_SETUP_STAGE_CB      io_hal_pcd_setupstage_cb                        ///< USB setup stage callback event
#define USB_DEV_RESET_CB            io_hal_pcd_reset_cb                             ///< USB reset callback event
#define USB_DEV_SUSPEND_CB          io_hal_pcd_suspend_cb                           ///< USB suspend callback event
#define USB_DEV_RESUME_CB           io_hal_pcd_resume_cb                            ///< USB resume callback event
#define USB_DEV_CONNECT_CB          io_hal_pcd_connect_cb                           ///< USB connect callback event
#define USB_DEV_DISCONNECT_CB       io_hal_pcd_disconnect_cb                        ///< USB disconnect callback event
#define USB_DEV_DATA_OUT_STAGE_CB   io_hal_pcd_dataoutstage_cb                      ///< USB data out stage callback event
#define USB_DEV_DATA_IN_STAGE_CB    io_hal_pcd_datainstage_cb                       ///< USB data in stage callback event
#define USB_DEV_ISO_OUT_INCPLT_CB   io_hal_pcd_iso_out_incomplete_cb                    ///< USB ISO out incomplete callback event
#define USB_DEV_ISO_IN_INCPLT_CB    io_hal_pcd_iso_in_incomplete_cb                 ///< USB ISO in incomplete callback event

#else

#define USB_DEV_SOF_CB              linux_usb_dummy_fn                      ///< USB SOF callback event
#define USB_DEV_SETUP_STAGE_CB      linux_usb_dummy_fn                      ///< USB setup stage callback event
#define USB_DEV_RESET_CB            linux_usb_dummy_fn                      ///< USB reset callback event
#define USB_DEV_SUSPEND_CB          linux_usb_dummy_fn                      ///< USB suspend callback event
#define USB_DEV_RESUME_CB           linux_usb_dummy_fn                      ///< USB resume callback event
#define USB_DEV_CONNECT_CB          linux_usb_dummy_fn                      ///< USB connect callback event
#define USB_DEV_DISCONNECT_CB       linux_usb_dummy_fn                      ///< USB disconnect callback event
#define USB_DEV_DATA_OUT_STAGE_CB   linux_usb_io_dummy_fn                   ///< USB data out stage callback event
#define USB_DEV_DATA_IN_STAGE_CB    linux_usb_io_dummy_fn                   ///< USB data in stage callback event
#define USB_DEV_ISO_OUT_INCPLT_CB   linux_usb_io_dummy_fn                   ///< USB ISO out incomplete callback event
#define USB_DEV_ISO_IN_INCPLT_CB    linux_usb_io_dummy_fn                   ///< USB ISO in incomplete callback event

#endif

extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];
ioal_usb_hdle io_hal_husbdev;

/**
 * @brief This API initialize the control block memory and do basic configurations of USB
 */
hal_ret_sts io_hal_usb_device_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL USB Initialise");
    usleep(100000);
#endif

    hal_ret_sts sts;
    if(HAL_SCS == io_hal_common_usb_device_init(&io_hal_husbdev))
    {
        intf_inst_hdle_ptr[IOAL_INST_USB1] = &io_hal_husbdev;
        io_hal_usb_dev_cb_init(&io_hal_husbdev);

    }
    else
    {

        sts = HAL_IO_INIT_ERR;
    }
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL USB Initialisation completed successfully");
#endif
    return sts;
}

/**
 * @brief This API deinit the USB
 */
hal_ret_sts io_hal_usb_device_deinit()
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL USB deInitialise");
    usleep(100000);
#endif
    hal_ret_sts sts;
    if(HAL_SCS == io_hal_common_usb_device_deinit(&io_hal_husbdev))
    {
        sts=HAL_SCS;

    }
    else
    {

        sts = HAL_IO_INIT_ERR;
    }
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL USB DeInitialisation completed successfully");
#endif
    return sts;
}

/**
 * @brief This API initialize the callback event
 */
void io_hal_usb_dev_cb_init(ioal_usb_hdle *husbdev)
{
    husbdev->sof_cb = USB_DEV_SOF_CB;
    husbdev->setup_stage_cb = USB_DEV_SETUP_STAGE_CB;
    husbdev->reset_cb = USB_DEV_RESET_CB;
    husbdev->suspend_cb = USB_DEV_SUSPEND_CB;
    husbdev->resume_cb = USB_DEV_RESUME_CB;
    husbdev->connect_cb = USB_DEV_CONNECT_CB;
    husbdev->disconnect_cb = USB_DEV_DISCONNECT_CB;
    husbdev->data_out_stage_cb = USB_DEV_DATA_OUT_STAGE_CB;
    husbdev->data_in_stage_cb = USB_DEV_DATA_IN_STAGE_CB;
    husbdev->iso_out_incplt_cb = USB_DEV_ISO_OUT_INCPLT_CB;
    husbdev->iso_in_incplt_cb = USB_DEV_ISO_IN_INCPLT_CB;

#ifndef LINUX_TEMP_PORT
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_SOF_CB_ID);
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_SETUP_STAGE_CB_ID);
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_RESET_CB_ID);
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_SUSPEND_CB_ID);
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_RESUME_CB_ID);
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_CONNECT_CB_ID);
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_DISCONNECT_CB_ID);
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_DATA_OUT_STAGE_CB_ID);
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_DATA_IN_STAGE_CB_ID);
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_ISO_OUT_INCPLT_CB_ID);
    io_hal_common_usb_device_reg_cb(husbdev, IOHAL_STM32_USBDEV_ISO_IN_INCPLT_CB_ID);
#endif
}
#ifndef LINUX_TEMP_PORT

/**
 * @brief This API start the USB device
 */
hal_ret_sts io_hal_usb_device_start(ioal_usb_hdle *husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_start(husbdev))
    {

        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API de-activate remote wakeup signalling.
 */
hal_ret_sts io_hal_usb_device_stop(ioal_usb_hdle *husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_stop(husbdev))
    {

        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API connects the USB device
 */
hal_ret_sts io_hal_usb_device_devconnect (ioal_usb_hdle *husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_devconnect(husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API disconnects the USB device
 */
hal_ret_sts io_hal_usb_device_devdisconnect (ioal_usb_hdle *husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_devdisconnect(husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API sets the USB device address
 */
hal_ret_sts io_hal_usb_device_setaddress (ioal_usb_hdle *husbdev, uint8_t address)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_setaddress(husbdev,address))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API opens and configures an endpoint
 */
hal_ret_sts io_hal_usb_device_ep_open (ioal_usb_hdle *husbdev, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_ep_open(husbdev,ep_addr,ep_mps,ep_type))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API deactivate an endpoint
 */
hal_ret_sts io_hal_usb_device_ep_close (ioal_usb_hdle *husbdev, uint8_t ep_addr)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_ep_close(husbdev,ep_addr))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API receive an amount of data from the specified endpoint address
 */
hal_ret_sts io_hal_usb_device_ep_receive (ioal_usb_hdle *husbdev, uint8_t ep_addr, uint8_t *pbuf,uint32_t len)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_ep_receive(husbdev,ep_addr,pbuf,len))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API get number of receive count for the specified endpoint address
 */
uint32_t io_hal_usb_device_ep_getrxcount (ioal_usb_hdle *husbdev, uint8_t ep_addr)
{
    return io_hal_common_usb_device_ep_getrxcount(husbdev,ep_addr);
}

/*!
 *  @brief This API send an amount of data for the specified endpoint address
 */
hal_ret_sts io_hal_usb_device_ep_transmit (ioal_usb_hdle *husbdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t len)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_ep_transmit(husbdev,ep_addr,pbuf,len))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API set a stall condition for the specified endpoint address
 */
hal_ret_sts io_hal_usb_device_ep_setstall (ioal_usb_hdle *husbdev, uint8_t ep_addr)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_ep_setstall(husbdev,ep_addr))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API clear a stall condition for the specified endpoint address
 */
hal_ret_sts io_hal_usb_device_ep_clrstall (ioal_usb_hdle *husbdev, uint8_t ep_addr)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_ep_clrstall(husbdev,ep_addr))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API flush the specified endpoint
 */
hal_ret_sts io_hal_usb_device_ep_flush (ioal_usb_hdle *husbdev, uint8_t ep_addr)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_ep_flush(husbdev,ep_addr))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API activate remote wakeup
 */
hal_ret_sts io_hal_usb_device_activate_remote_wakeup (ioal_usb_hdle *husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_activate_remote_wakeup(husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API de-activate remote wakeup signalling
 */
hal_ret_sts io_hal_usb_device_deactivate_remote_wakeup (ioal_usb_hdle *husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_usb_device_deactivate_remote_wakeup(husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}
#endif


#ifdef LINUX_TEMP_PORT
/**
 * @brief This is USB interface dummy function for linux
 */
void linux_usb_dummy_fn(struct _ioal_usb_hdle *husb)
{
}

/**
 * @brief This is USB IO dummy function for linux
 */
void linux_usb_io_dummy_fn(struct _ioal_usb_hdle *husb, uint8_t val)
{
}

#endif

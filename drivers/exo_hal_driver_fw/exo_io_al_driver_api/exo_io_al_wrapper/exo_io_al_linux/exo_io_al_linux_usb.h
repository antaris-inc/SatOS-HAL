/**
 * @file exo_io_al_linux_usb.h
 *
 * @brief This file contains linux wrapper functions declarations for IO interface
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

#ifndef _IO_AL_LINUX_USB_H_
#define _IO_AL_LINUX_USB_H_

#include "exo_hal_common.h"

/**
 * @brief IO-HAL USB initialization function for linux
 * @param[in] ioal_husbdev - pointer to USB instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_usb_device_init(void *ioal_husbdev);

/**
 * @brief IO-HAL USB start function for linux
 * @param[in] ioal_husbdev - pointer to USB instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_usb_device_start(void *ioal_husbdev);

/**
 * @brief IO-HAL USB stop function for linux
 * @param[in] ioal_husbdev - pointer to USB instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_usb_device_stop(void *ioal_husbdev);

/**
 * @brief IO-HAL USB deinit function for linux
 * @param[in] ioal_husbdev - pointer to USB instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_usb_device_deinit(void *ioal_husbdev);

/** IO HAL common USB function mapping **/
#define io_hal_common_usb_device_init    io_hal_linux_usb_device_init
#define io_hal_common_usb_device_start   io_hal_linux_usb_device_start
#define io_hal_common_usb_device_stop    io_hal_linux_usb_device_stop
#define io_hal_common_usb_device_deinit  io_hal_linux_usb_device_deinit
#define io_hal_common_usb_device_deinit  io_hal_linux_usb_device_deinit

#endif

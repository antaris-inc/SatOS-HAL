/*
 * @file exo_io_al_linux_ethernet.h
 *
 * @brief This file contains linux wrapper functions declarations for IO interface
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

#ifndef _IO_AL_LINUX_ETH_H_
#define _IO_AL_LINUX_ETH_H_

#include "exo_hal_common.h"
//#include "exo_io_al_i2c_common.h"

/**
 * @brief IO-HAL ethernet initialization function for linux
 * @param[in] ioal_heth - pointer to Ethernet instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_eth_init (void *ioal_heth);


#define io_hal_common_eth_init                  io_hal_linux_eth_init

#endif

/*
 * @file exo_ahw_al_wrpr.h
 *
 * @brief This file contains the function prototype of temperature sensor
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

#ifndef HAL_DRIVER_WRPR_H_
#define HAL_DRIVER_WRPR_H_


#include "stdint.h"



uint8_t skt_intf_write(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
uint8_t skt_intf_read(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

#endif

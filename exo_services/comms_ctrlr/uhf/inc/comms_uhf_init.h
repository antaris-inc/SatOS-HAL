/**
 * @file comms_uhf_init.h
 *
 * @brief This file has the prototypes of functions used for UHF driver initialization
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
 *
 */

#ifndef COMMS_UHF_INIT_H_
#define COMMS_UHF_INIT_H_

#include <stdio.h>
#include "comms_uhf_main.h"
#include "comms_uhf_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  This function is used for UHF parameters initialisation
 */
void comms_uhf_init_uhf_cfg(void);

/**
 * @brief Initialize UHF timers with default values
 * This function initializes the various timers used by the UHF
 * communication system to default values. It will be called as part
 * of the system initialization sequence.
 */
void comms_uhf_timer_init_default(void);

#ifdef __cplusplus
}
#endif
#endif /*COMMS_UHF_INIT_H_*/

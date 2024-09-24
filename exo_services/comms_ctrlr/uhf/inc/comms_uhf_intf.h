/**
 * @file comms_uhf_intf.h
 *
 * @brief This file has the control blocks, enumeration and function
 * prototypes of SDR control layer of UHF module
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

#ifndef COMMS_UHF_INTF_H_
#define COMMS_UHF_INTF_H_

#include "comms_uhf_main.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get current UHF state
 *
 * @return UHF state machine current state
 */
uint8_t uhf_get_state(void);


#ifdef __cplusplus
}
#endif
#endif /*COMMS_UHF_INTF_H */

/**
 * @file exo_ah_iob_csn.h
 *
 * @brief This file contains functions to handle application hardware and IO contention states
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
#ifndef _AH_IOB_CSN_H_
#define _AH_IOB_CSN_H_

#include "exo_io_al_common.h"
#include "exo_ahw_al_common.h"
#include "exo_hal_io_al_common.h"

/**
 * @brief This function update the application hardware state
 * @param[in] ah_gen_info - ah_gen_info pointer to a ahw_al_gen_info structure that contains
 *             the configuration information of application hardware
 * @param[in] state - State of the module
 * @retval HAL status
 */

hal_ret_sts ahiobcsn_updt_ahste(ahw_al_gen_info *ah_gen_info, hal_ah_usage_state state);
/**
 * @brief This function update the IO interface state
 * @param[in] ah_gen_info - ah_gen_info pointer to a ioal_intf_gen_info structure that contains
 *             the configuration information IO interface
 * @param[in] state - State of the interface
 * @retval HAL status
 */

hal_ret_sts ahiobcsn_updt_ioste(ioal_intf_gen_info *io_gen_info, hal_io_state state);
/**
 * @brief This function checks the state of the HAL module
 * @param[in] ah_inst_hdle - ah_inst_hdle pointer to a ahw_al_gen_info structure that contains
 *             the configuration information
 * @retval HAL status
 */
hal_ret_sts ahiobcsn_check_ste(ahw_al_gen_info *ah_inst_hdle);

#endif /* _AH_IOB_CSN_H_ */

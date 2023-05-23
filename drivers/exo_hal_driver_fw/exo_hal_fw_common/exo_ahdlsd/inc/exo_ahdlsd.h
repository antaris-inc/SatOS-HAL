/**
 * @file exo_ahdlsd.h
 *
 * @brief This file contains structures and function declaration for
 * device discovery management of application hardware
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

#ifndef _AHDLSD_H_
#define _AHDLSD_H_

#include "exo_ahw_al_common.h"

/**
 * @brief AH discovery information structure definition
 */
typedef struct _ah_disc_info
{
    ahw_inst_id_t id;			/*!< Instance ID structure variable        */
    hal_ah_disc_state state;	/*!< AH discovery state structure variable */
}ah_disc_info_s;

/**
 * @brief AHDLSD information structure definition
 */
typedef struct _ahdlsd_info
{
    ah_disc_info_s ah_disc_info[MAX_AH_INST_ID];    /*!< AH discovery information structure variable   */
}ahdlsd_info_s;

/**
 * @brief This function update the application hardware discovery state
 * @param ah_type - ah_type pointer to a ahw_inst_id_t structure that contains
 *             the configuration information
 * @param state - discovery state of the application hardware
 * @retval HAL status
 */
hal_ret_sts ahdlsd_updt_ah_state(ahw_inst_id_t ah_type, hal_ah_disc_state state);
/**
 * @brief This function send the IPC incase of device discovery
 * @param ah_disc_info - ah_disc_info pointer to a ah_disc_info_s structure that contains
 *             the configuration information
 * @retval HAL status
 */
hal_ret_sts ahdlsd_snd_ntf(ah_disc_info_s *ah_disc_info);
/**
 * @brief This function get the application hardware discovery state
 * @param ah_disc_info - ah_disc_info pointer to a ah_disc_info_s structure that contains
 *             the configuration information
 * @retval HAL status
 */
hal_ret_sts ahdlsd_get_ah_sts(ah_disc_info_s *ah_disc_info);

/**
 * @brief This function gets the application hardware list
 * @retval HAL status
 */
hal_ret_sts ahdlsd_get_cplt_ah_list(void);


#endif /* _AHDLSD_H_ */

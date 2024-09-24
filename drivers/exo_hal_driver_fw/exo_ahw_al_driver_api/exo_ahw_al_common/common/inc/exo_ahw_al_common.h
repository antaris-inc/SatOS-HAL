/**
 * @file exo_ahw_al_common.h
 *
 * @brief This file has structure declaration ,enumerations,
 * function declaration for application hardware management
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

#ifndef _AHW_AL_COMMON_H_
#define _AHW_AL_COMMON_H_

#include "exo_types.h"

#include "exo_hal_common.h"
#include "exo_hal_io_al_common.h"
#include "exo_hal_io_al_intr.h"

#define MAX_HAL_AH_NUM 256  ///< Maximum HAL AH number

/**
 * @brief Application hardware discovery state enumeration
 */
typedef enum
{
    AH_DEREGISTERED,            /*!< Application hardware deregistered */
    AH_REGISTERED,              /*!< Application hardware registered */
    AH_ACTIVATED,               /*!< Application hardware activated */
    AH_DEACTIVATED,             /*!< Application hardware deactivated */
    AH_ERROR,                   /*!< Application hardware error */
    AH_MAX_STATE
}hal_ah_disc_state;

/**
 * @brief Application hardware usage state enumeration
 */
typedef enum _hal_ah_usage_state
{
    AH_FREE_STATE,              /*!< Application hardware free state */
    AH_BUSY_STATE,              /*!< Application hardware busy state */
    AH_INVLD_STATE              /*!< Application hardware invalid state */
}hal_ah_usage_state;

/**
 * @brief Application hardware contention state enumeration
 */
typedef enum _ahw_conten_ste
{
    AHW_NO_CONTEN_STE,          /*!< Application hardware no contention state */
    AHW_CONTEN_STE              /*!< Application hardware contention state */
}ahw_conten_ste;

/**
 * @brief Application hardware information structure definition
 */
typedef struct _ahw_inst_hdle
{
    ahw_inst_id_t ahw_inst_id;      /*!< Contains the Application hardware id                     */
    hal_ah_usage_state state;       /*!< Contains the free/busy state of Application hardware     */
    ahw_conten_ste conten_state;    /*!< Contains the contention state of Application hardware    */
    uint16 slave_address;           /*!< Slave address                                            */
    void *io_intf_hdle;             /*!< IO interface handle                                      */
    void *vdp_inst_hdle;            /*!< VDP interface handle                                     */
    io_inst_id io_intf_id;                      /*!< IO interface ID   */
    io_al_intr_info intr_hdl;                 /*!< IO interrupt handle   */
}ahw_al_gen_info;

/**
 * @brief HAL initialization function
 *
 * @return HAL status
 * @retval Zero is success, otherwise fail
 */
hal_ret_sts ah_hal_init(void);

/**
 * @brief HAL function to get AHW handle from AHW id
 *
 * @param[in] id : Identity
 */
void* ahal_get_hdle(ahw_inst_id_t id);

/**
 * @brief HAL function to store AHW handle with AHW id as index
 *
 * @param[in] id : Hardware instance id
 * @param[in] ahw_hdle : Hardware handler
 */
void ahal_set_hdle(ahw_inst_id_t id, void* ahw_hdle);

/**
 * @brief HAL application callback registration function
 *
 * @param[in] ahal_info : HAL information
 * @param[in] cb_id : Callback Id
 * @param[in] args : pointer to callback function
 * @param[in] cb_context : callback context
 *
 * @return HAL status
 * @retval Zero is success, otherwise fail
 */
hal_ret_sts ahal_register_io_cb(ahw_al_gen_info* ahal_info, uint8 cb_id,void (*cb_fptr)(void* args),uint8 cb_context);

#endif /* _AHW_AL_COMMON_H_ */

/**
 * @file exo_ahw_al_common.h
 *
 * @brief This file has structure declaration ,enumerations,
 * function declaration for application hardware management
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

#ifndef _AHW_AL_COMMON_H_
#define _AHW_AL_COMMON_H_

#include "exo_types.h"

#include "exo_hal_common.h"
#include "exo_hal_io_al_common.h"

#define MAX_HAL_AH_NUM 256

/**
 * @brief Application hardware discovery state enumeration
 */
typedef enum
{
    AH_DEREGISTERED,			/*!< Application hardware deregistered */
    AH_REGISTERED,				/*!< Application hardware registered */
    AH_ACTIVATED,				/*!< Application hardware activated */
    AH_DEACTIVATED,				/*!< Application hardware deactivated */
    AH_ERROR,					/*!< Application hardware error */
    AH_MAX_STATE
}hal_ah_disc_state;

/**
 * @brief Application hardware usage state enumeration
 */
typedef enum _hal_ah_usage_state
{
    AH_FREE_STATE,				/*!< Application hardware free state */
    AH_BUSY_STATE,				/*!< Application hardware busy state */
    AH_INVLD_STATE				/*!< Application hardware invalid state */
}hal_ah_usage_state;

/**
 * @brief Application hardware contention state enumeration
 */
typedef enum _ahw_conten_ste
{
    AHW_NO_CONTEN_STE,			/*!< Application hardware no contention state */
    AHW_CONTEN_STE				/*!< Application hardware contention state */
}ahw_conten_ste;

/**
 * @brief Application hardware information structure definition
 */
typedef struct _ahw_inst_hdle
{
    ahw_inst_id_t ahw_inst_id;      		/*!< Contains the Application hardware id				      */
    hal_ah_usage_state state;       		/*!< Contains the free/busy state of Application hardware  	  */
    ahw_conten_ste conten_state;		/*!< Contains the contention state of Application hardware    */
    uint16 slave_address;			/*!< Slave address											  */
    void *io_intf_hdle;   			/*!< IO interface handle								 	  */
    void *vdp_inst_hdle;   			/*!< VDP interface handle  									  */
}ahw_al_gen_info;

/**
 * @brief HAL initialization function
 */
hal_ret_sts ah_hal_init(void);

#endif /* _AHW_AL_COMMON_H_ */

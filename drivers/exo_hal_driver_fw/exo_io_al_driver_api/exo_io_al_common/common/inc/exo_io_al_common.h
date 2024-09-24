/**
 * @file exo_io_al_common.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for application hardware management
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

#ifndef IO_AL_COMMON_H
#define IO_AL_COMMON_H

#include "exo_types.h"

#include "exo_hal_common.h"
#include "exo_hal_io_al_common.h"

/**
 * @brief HAL IO state enumeration
 */
typedef enum _hal_io_state
{
    IO_FREE_STATE,              /*!< IO free state */
    IO_BUSY_STATE,              /*!< IO busy state */
    IO_ERR_STATE,               /*!< IO error state */
    IO_INVLD_STATE,             /*!< IO invalid state */
}hal_io_state;

/**
 * @brief IO usage enumeration
 */
typedef struct _iob_usage
{
    uint8 curr_ah_id;       /*!< Contains the application hardware ID that is currently using the IO bus */
    uint8 mapped_ah_id[10]; /*!< Contains list of IDs of application hardware that can use the IO bus    */
}iob_usage;

/**
 * @brief IO-HAL interface information enumeration
 */
typedef struct _ioal_intf_gen_info
{
#ifdef LINUX_TEMP_PORT
    uint8_t io_id;              /*!< Contains IO interface ID                                */
#endif    
    hal_io_state state;         /*!< Contains the free/busy state of IO interface            */
    void *vdp_intf_inst_hdle;   /*!< Contains the handle of vendor driver interface instance */

}ioal_intf_gen_info;

/**
 * @brief IO-HAL functional state enumeration
 */
typedef enum
{
    FUNC_STE_DISABLE = 0U,                 /*!< function disable state */
    FUNC_STE_ENABLE = !FUNC_STE_DISABLE  /*!< function enable state */
} io_hal_functional_state;

/**
 * @brief IO-HAL initialization function
 * @retval No return
 */
hal_ret_sts io_hal_init(void);

/**
 * @brief Function to get IOAL instance handle pointer
 * @retval instance handle pointer
 */
void* get_ioal_inst_hdle(io_inst_id inst_id);

#endif

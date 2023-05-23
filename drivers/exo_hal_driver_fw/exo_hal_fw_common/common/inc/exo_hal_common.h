/**
 * @file exo_hal_common.h
 *
 * @brief This file contains structures,enumerations,function declaration for HAL
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

#ifndef _HAL_COMMON_H_
#define _HAL_COMMON_H_

#include "exo_types.h"

/**
 * @brief IO-HAL and VDP return status
 */
typedef enum
{
    HAL_SCS = 0,							/*!< Success */
    HAL_IO_INSTANCE_ALREADY_REG,			/*!< IO instance has been already in use */
    HAL_IO_INVLD_INST_ID,				    /*!< IO invalid instance ID */
    HAL_IO_VDP_ERR,							/*!< IO VDP layer error */
    HAL_IO_TX_ERR,							/*!< IO transmission error */
    HAL_IO_RX_ERR,							/*!< IO reception error */
    HAL_IO_INIT_ERR,						/*!< IO initialization error */
    HAL_IO_INVLD_CB_FN,						/*!< IO invalid callback function */
    HAL_AH_INVLD_INST_ID = 100,				/*!< AH invalid instance ID */
    HAL_AH_INIT_ERR,						/*!< AH initialization error */
    HAL_AH_INSTANCE_ALREADY_REG,			/*!< AH	invalid instance ID */
    HAL_INVLD_AH_IO_TYPE,					/*!< Invalid AH and IO type */
    HAL_AHW_STE_BUSY,						/*!< AHW in busy state */
    HAL_IO_INTF_BUSY,						/*!< IO in busy state */
    HAL_AHW_CONTENTION_STE,					/*!< AHW contention state */
    HAL_AH_DRIVER_ERR,						/*!< AH	driver error */
    HAL_AHIOBCSN_FW_ERR = 200,				/*!< AHIOBCSN firmware error */
    HAL_AHDLSD_FW_ERR,						/*!< AHDLSD firmware error */
    HAL_MEM_ALLOC_ERR,						/*!< Memory allocation error */
    HAL_MAX_ERR
}hal_ret_sts;

/**
 * @brief AH-IO type enumeration
 */
typedef enum
{
    TYPE_IO,			/*!< IO type */
    TYPE_AH,			/*!< AH type */
    TYPE_INVLD			/*!< invalid type */
}hal_ah_io_type;

/**
 * @brief HAL initialization function
 */
void hal_init(void);

/**
 * @brief IOAL error handler function
 */
void ioal_error_handler(void);

#endif

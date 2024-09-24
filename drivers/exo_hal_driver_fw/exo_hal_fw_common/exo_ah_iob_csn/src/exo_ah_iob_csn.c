/**
 * @file exo_ah_iob_csn.c
 *
 * @brief This file contains functions to handle application hardware and IO contention states
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
#include "exo_ah_iob_csn.h"

extern void* ahw_inst_hdle_ptr[MAX_AH_INST_ID];
extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

/* Note: This module operates under following conditions are met
 * All the AHW HAL instance structure should have ahw_al_gen_info as the first member in its structure
 * All the IO HAL instance structure should have ioal_intf_gen_info as the first member in its structure
 */

/**
 * @brief This API update the state of application hardware
 */
inline hal_ret_sts ahiobcsn_updt_ahste(ahw_al_gen_info *ah_gen_info, hal_ah_usage_state state)
{
    ah_gen_info->state = state;
    return HAL_SCS;
}

/**
 * @brief This API update the state of IO interface
 */
hal_ret_sts ahiobcsn_updt_ioste(ioal_intf_gen_info *io_gen_info, hal_io_state state)
{
    hal_ret_sts sts;
    int id = 0;
    ahw_al_gen_info *ah_id = (ahw_al_gen_info*)ahw_inst_hdle_ptr;
    uint8 ah_io_map_flag = 0;

    if((IO_BUSY_STATE == io_gen_info->state) && (IO_FREE_STATE == state))
    {
        for(id = 0; id < MAX_AH_INST_ID; id ++)
        {
            if(io_gen_info == (ioal_intf_gen_info*) ah_id->io_intf_hdle)
            {
                ah_io_map_flag = 1;
                if(AHW_CONTEN_STE == ah_id->conten_state)
                {
                    ah_id->conten_state = AHW_NO_CONTEN_STE;

                }
            }
        }
        if(0 == ah_io_map_flag)
        {
            sts = HAL_AHIOBCSN_FW_ERR;
        }
    }
    else
    {

    }
    io_gen_info->state = state;
    return sts;
}

/**
 * @brief This API checks the state of the HAL module
 */
hal_ret_sts ahiobcsn_check_ste(ahw_al_gen_info *ah_gen_info)
{
    hal_ret_sts sts = HAL_MAX_ERR;
    ioal_intf_gen_info *io_gen_info;
    io_gen_info = (ioal_intf_gen_info *)ah_gen_info->io_intf_hdle;
    if((AH_FREE_STATE == ah_gen_info->state) && (IO_BUSY_STATE == io_gen_info->state))
    {
        ah_gen_info->conten_state = AHW_CONTEN_STE;
        sts = HAL_AHW_CONTENTION_STE;
    }
    else if((AH_FREE_STATE == ah_gen_info->state) && (IO_FREE_STATE == io_gen_info->state))
    {
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AHIOBCSN_FW_ERR;
    }
    return sts;
}

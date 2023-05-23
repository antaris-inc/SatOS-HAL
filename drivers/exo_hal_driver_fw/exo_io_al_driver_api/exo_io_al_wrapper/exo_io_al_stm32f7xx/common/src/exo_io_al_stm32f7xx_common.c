/**
 * @file exo_io_al_stm32f7xx_common.c
 *
 * @brief This file contains function definition to get the IO-AL instance
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

#include "exo_io_al_stm32f7xx_common.h"
#include "exo_hal_io_al_common.h"

extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

/**
 * @brief This function get the IO-AL instance from VDP instance
 */
hal_ret_sts get_ioal_inst_from_vd_inst(void *vdp_io_inst_hdle, void** io_hal_inst_hdle)
{
    uint32 i = 0;
    hal_ret_sts sts = HAL_MAX_ERR;
    ioal_intf_gen_info *io_hal_inst_hdle_temp;
    for(i = 0; i <MAX_IO_INST_ID; i++)
    {
        io_hal_inst_hdle_temp = (ioal_intf_gen_info*) intf_inst_hdle_ptr[i];
        if(io_hal_inst_hdle_temp->vdp_intf_inst_hdle == vdp_io_inst_hdle)
        {
            *io_hal_inst_hdle = (void*)io_hal_inst_hdle_temp;
            sts=HAL_SCS;
            break;
        }
    }
    if (MAX_IO_INST_ID == i)
    {
        sts = HAL_IO_INVLD_INST_ID;
    }
    return sts;
}

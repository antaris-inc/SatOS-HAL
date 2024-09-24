/**
 * @file exo_ahw_al_common.c
 *
 * @brief This file has function declaration for application hardware management
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

#include <stdio.h>
#include "exo_ahw_al_common.h"
#include "exo_hal_common.h"
#include "exo_ahw_al_imu_common.h"
#include "exo_ahw_al_dt_common.h"
#include "exo_ahw_al_hsc_common.h"
#include "exo_ahw_al_psm_common.h"
#include "exo_ahw_al_gpio_exp_common.h"
#include "exo_ahw_al_temp_sensor_common.h"
#include "exo_ahw_al_voltage_sequencer_common.h"
#include "exo_ahw_al_data_acq_dvc_common.h"

ahw_al_gen_info ahal_inst_id[MAX_HAL_AH_NUM]; ///< HAL instance id
void* ahw_inst_hdle_ptr[MAX_AH_INST_ID]; ///< Hardware instancce handler pointer

ahw_al_gpio_exp_hdle ps_gpx;  ///< PS GPS
ahw_al_gpio_exp_hdle hgpio_exp_obc_1; ///< GPIO expander OBC1
ahw_al_gpio_exp_hdle hgpio_exp_obc_2; ///< GPIO expander OBC2
ahw_al_gpio_exp_hdle hgpio_exp_edge_1; ///< GPIO expander EDGE1
ahw_al_gpio_exp_hdle hgpio_exp_edge_2; ///< GPIO expander EDGe2
ahw_al_gpio_exp_hdle hgpio_exp_gps;   ///< GPIO expander GPS

/**
 * @brief HAL initialization function
 */
hal_ret_sts ah_hal_init(void)
{

    hal_ret_sts sts = HAL_AH_INIT_ERR;
#ifdef LINUX_TEMP_PORT
    printf("\n EXO Application Hardware Abstraction Layer Framework Initialize");

#endif

#ifdef COREBOARD
    sts=ahw_al_gpio_exp_init(&ps_gpx,GPIO_EXPANDER_PCAL6408A_PS);
    sts=ahw_al_gpio_exp_init(&hgpio_exp_obc_1,GPIO_EXPANDER_MCP23008_OBC_1);
    sts=ahw_al_gpio_exp_init(&hgpio_exp_obc_2,GPIO_EXPANDER_MCP23008_OBC_2);
    sts=ahw_al_gpio_exp_init(&hgpio_exp_edge_1,GPIO_EXPANDER_MCP23008_EDGE_1);
    sts=ahw_al_gpio_exp_init(&hgpio_exp_edge_2,GPIO_EXPANDER_MCP23008_EDGE_2);
    sts=ahw_al_gpio_exp_init(&hgpio_exp_gps,GPIO_EXPANDER_MCP23008_GPS);
#endif

#ifdef LINUX_TEMP_PORT
    printf("\n EXO Application Hardware Abstraction Layer Framework Initialization completed successfully");
#endif
    return sts;
}

/**
 * @brief HAL initialization function
 */
void ahal_set_hdle(ahw_inst_id_t id, void* ahw_hdle)
{
    if(id<MAX_AH_INST_ID)
    {
        ahw_inst_hdle_ptr[id]=ahw_hdle;
    }
}
/**
 * @brief HAL function to return AHW handle from AHW id
 */
void* ahal_get_hdle(ahw_inst_id_t id)
{
    void* ret = NULL;
    if(id<MAX_AH_INST_ID)
    {
        ret = ahw_inst_hdle_ptr[id];
    }
    return ret;
}

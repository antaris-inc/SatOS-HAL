/**
 * @file exo_ahw_al_common.c
 *
 * @brief This file has function declaration for application hardware management
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

ahw_al_gen_info ahal_inst_id[MAX_HAL_AH_NUM];


void* ahw_inst_hdle_ptr[MAX_AH_INST_ID];
extern ahw_al_dt_hdle *digi_therm1;
extern ahw_al_psm_hdle *ahw_al_hpsm;
extern ahw_al_gpio_exp_hdle *hgpio_exp;
extern ahw_al_temp_sensor_hdl *ahw_al_hts;

/**
 * @brief HAL initialization function
 */
hal_ret_sts ah_hal_init(void)
{

#ifdef LINUX_TEMP_PORT
    printf("\n EXO Application Hardware Abstraction Layer Framework Initialize");
    printf("\n EXO Application Hardware Abstraction Layer Framework Initialization completed successfully");
#endif
    return 0;
}


/**
 * @file exo_ahw_al_data_acq_dvc_wrapper.c
 *
 * @brief This file has mapping functions which resolves the
 * instance Id and invokes the vendor driver api for data acquisition device based on the partnumber
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

#include "exo_ahw_vdp_data_acq_dvc_ads7828.h"
#include "exo_ahw_al_data_acq_dvc_wrapper.h"

#ifndef LINUX_TEMP_PORT
/*!
 *  @brief Mapping API to get the data from specified channel
 */
hal_ret_sts ahw_al_common_ads7828_get_data(ahw_al_ads7828_hdle *al_ads7828,ahw_al_ads7828_chnl chnl,ahw_al_ads7828_pd_sel pd_opt,uint16_t* data)
{
    hal_ret_sts sts;
    switch(al_ads7828->ahw_gen_info.ahw_inst_id)
    {
        case DATA_ACQ_DVC_ADS7828:
            sts = ahw_vdp_ads7828_get_data(al_ads7828,chnl,pd_opt,data);
            break;
        default:
            sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}
#endif

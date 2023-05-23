/**
 * @file exo_ahw_vdp_data_acq_dvc_ads7828.c
 *
 * @brief This file contains vendor driver porting functions for ADS7828 data acquisition device
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
#include "ads7828.h"

#ifndef LINUX_TEMP_PORT

/*!
 *  @brief This API is used to get the data from specified channel number
 */
hal_ret_sts ahw_vdp_ads7828_get_data(ahw_al_ads7828_hdle *al_ads7828,ahw_al_ads7828_chnl chnl,ahw_al_ads7828_pd_sel pd_opt,uint16_t* data)
{
    hal_ret_sts sts;
    s_ads7828 *ads7828_hdl_vdp;
    ads7828_hdl_vdp = al_ads7828->ahw_gen_info.vdp_inst_hdle;
    if(HAL_SCS == (hal_ret_sts)ads7828_get_data(ads7828_hdl_vdp,(e_ads7828_chnl)chnl,(e_ads7828_pd_sel)pd_opt,data))
    {
        sts=HAL_SCS;
    }
    else
    {
        sts=HAL_AH_DRIVER_ERR;
    }
    return sts;
}
#endif



/**
 * @file exo_ahw_al_data_acq_dvc_common.c
 *
 * @brief This file has abstracted driver functions for data acquisition device
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

#include <stdlib.h>
#include "exo_ahw_al_data_acq_dvc_common.h"
#include "exo_ahw_al_data_acq_dvc_wrapper.h"
#include "exo_ah_iob_csn.h"
#include "exo_ahdlsd.h"

#ifndef LINUX_TEMP_PORT
/*!
 *  @brief API to get the data from the specified channel number
 */
hal_ret_sts ahw_al_ads7828_get_data(ahw_al_ads7828_hdle *h_dl,ahw_al_ads7828_chnl chnl,ahw_al_ads7828_pd_sel pd_opt,uint16_t* data)
{
    hal_ret_sts sts;
    sts = ahiobcsn_check_ste(&h_dl->ahw_gen_info);
    if(HAL_SCS == sts)
    {
        ahiobcsn_updt_ahste(&h_dl->ahw_gen_info, AH_BUSY_STATE);
        if(HAL_SCS == ahw_al_common_ads7828_get_data(h_dl,chnl,pd_opt,data))
        {
            ahiobcsn_updt_ahste(&h_dl->ahw_gen_info, AH_FREE_STATE);
            sts = HAL_SCS;
        }
        else
        {
            sts = HAL_AH_DRIVER_ERR;
        }
    }
    else
    {

    }
    return sts;
}
#endif

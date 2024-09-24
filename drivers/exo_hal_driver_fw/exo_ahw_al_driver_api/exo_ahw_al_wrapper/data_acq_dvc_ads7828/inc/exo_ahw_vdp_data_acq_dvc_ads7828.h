/**
 * @file exo_ahw_vdp_data_acq_dvc_ads7828.h
 *
 * @brief This file has vendor driver porting function declaration of data acquisition device
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

#include "exo_hal_common.h"
#include "exo_ahw_al_data_acq_dvc_common.h"

#ifndef DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_DL_ADS7828_INC_EXO_AHW_VDP_DL_ADS7828_H_
#define DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_DL_ADS7828_INC_EXO_AHW_VDP_DL_ADS7828_H_

/**
 * @brief This function is used to get the data from the specified channel number
 * @param[in] al_ads7828 - instance pointer of ads7828
 * @param[in] chnl - selects the channel of ads7828
 * @param[in] pd_opt - power down option
 * @param[out] data - pointer to the data
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_ads7828_get_data(ahw_al_ads7828_hdle *al_ads7828,ahw_al_ads7828_chnl chnl,ahw_al_ads7828_pd_sel pd_opt,uint16_t* data);


#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_DL_ADS7828_INC_EXO_AHW_VDP_DL_ADS7828_H_ */

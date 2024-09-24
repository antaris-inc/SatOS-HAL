/**
 * @file exo_ahw_al_data_acq_dvc_common.h
 *
 * @brief This file has structure declaration ,enumerations,
 * function declaration for ADS7828 Data Acquisition Device
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

#ifndef INC_EXO_AHW_AL_DL_ADS7828_COMMON_H_
#define INC_EXO_AHW_AL_DL_ADS7828_COMMON_H_

#include <stdint.h>
#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_ahw_al_common.h"

/**
 * @brief AHW ADS7828 control block structure definition
 */
typedef struct
{
    ahw_al_gen_info ahw_gen_info;       /*!< AHW general information */

}ahw_al_ads7828_hdle;

/**
 * @brief AHW ADS7828 channel enumeration
 */
typedef enum
{
    DE_PI_CH0=0b0000,                   /*!< ads7828 channel 0 */
    DE_NI_CH0=0b0100,                   /*!< ads7828 channel 0 */
    DE_PI_CH1=0b0001,                   /*!< ads7828 channel 1 */
    DE_NI_CH1=0b0101 ,                  /*!< ads7828 channel 1 */
    DE_PI_CH2=0b0010,                   /*!< ads7828 channel 2 */
    DE_NI_CH2=0b0110,                   /*!< ads7828 channel 2 */
    DE_PI_CH3=0b0011,                   /*!< ads7828 channel 3 */
    DE_NI_CH3=0b0111,                   /*!< ads7828 channel 3 */
    SE_CH0=0b1000,                      /*!< ads7828 channel 0 */
    SE_CH1=0b1100,                      /*!< ads7828 channel 1 */
    SE_CH2=0b1001,                      /*!< ads7828 channel 2 */
    SE_CH3=0b1101,                      /*!< ads7828 channel 3 */
    SE_CH4=0b1010,                      /*!< ads7828 channel 4 */
    SE_CH5=0b1110,                      /*!< ads7828 channel 5 */
    SE_CH6=0b1011,                      /*!< ads7828 channel 6 */
    SE_CH7=0b1111,                      /*!< ads7828 channel 7 */
    CH_MAX=0b10000,

}ahw_al_ads7828_chnl;

/**
 * @brief AHW ADS7828 power down selection enumeration
 */
typedef enum
{
    AL_PD_DWN,                              /*!< ads7828 power down */
    AL_INT_REF_OFF_ADC_ON,                  /*!< ads7828 internal reference OFF ADC ON */
    AL_INT_REF_ON_ADC_OFF,                  /*!< ads7828 internal reference ON ADC OFF */
    AL_INT_REF_ON_ADC_ON,                   /*!< ads7828 internal reference OFN ADC ON */
    AL_PD_SEL_MAX

}ahw_al_ads7828_pd_sel;

/**
 * @brief API to get the data from the specified channel number
 * @param[in]  h_dl - instance pointer of ads7828
 * @param[in]  chnl - channel number of ads7828
 * @param[in]  pd_opt -  power down option
 * @param[out]  data - pointer to the data
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_ads7828_get_data(ahw_al_ads7828_hdle *h_dl,ahw_al_ads7828_chnl chnl,ahw_al_ads7828_pd_sel pd_opt,uint16_t* data);

#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_COMMON_DL_ADS7828_INC_EXO_AHW_AL_DL_ADS7828_COMMON_H_ */

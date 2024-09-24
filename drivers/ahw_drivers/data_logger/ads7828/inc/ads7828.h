/**
 * @file ads7828.h
 *
 * @brief This file contains the macros,structure declaration,enumeration,
 * function declaration of data acquisition device ADS7828
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

#ifndef DRIVERS_AHW_DRIVERS_DATA_LOGGER_ADS7828_INC_ADS7828_H_
#define DRIVERS_AHW_DRIVERS_DATA_LOGGER_ADS7828_INC_ADS7828_H_
#include <stddef.h>
#include <stdint.h>

/**
 * @brief  read API function pointer
 */
typedef int8_t (*ads7828_read_fptr_t)(void* intf_hdl, uint16_t slv_addr, uint8_t *data, uint16_t len);

/**
 * @brief  write API function pointer
 */
typedef int8_t (*ads7828_write_fptr_t)(void* intf_hdl, uint16_t slv_addr, uint8_t *data, uint16_t len);

/**
 * @brief ADS7828 error status enumeration
 */
typedef enum
{
    ADS7828_SCS,							///< ads7828 success
    ADS7828_ERR,			    			///< ads7828 error
    ADS7828_INVLD_ARG,						///< ads7828 invalid argument
    ADS7828_ALRDY_USD,						///< ads7828 already used
    ADS7828_COM_ERR,						///< ads7828 communication error
    ADS7828_NULL_PTR,						///< ads7828 NULL pointer
    ADS7828_ERR_MAX

}e_ads7828_err;

/*
   SD C2 C1 C0 CH0 CH1 CH2 CH3 CH4 CH5 CH6 CH7 COM
   0 0 0 0 +IN –IN  —   —   —   —   —   —   —
   0 0 0 1  —  —   +IN –IN  —   —   —   —   —
   0 0 1 0  —  —   —   —   +IN –IN  —   —   —
   0 0 1 1  —  —   —   —   —    —  +IN –IN  —
   0 1 0 0 –IN +IN —   —   —    —    —   —  —
   0 1 0 1  —  —  –IN  +IN —    —   —   —   —
   0 1 1 0  — — — — –IN +IN — — —
   0 1 1 1 — — — — — — –IN +IN —
   1 0 0 0 +IN — — — — — — — –IN
   1 0 0 1 — — +IN — — — — — –IN
   1 0 1 0 — — — — +IN — — — –IN
   1 0 1 1 — — — — — — +IN — –IN
   1 1 0 0 — +IN — — — — — — –IN
   1 1 0 1 — — — +IN — — — — –IN
   1 1 1 0 — — — — — +IN — — –IN
   1 1 1 1 — — — — — — — +IN –IN
   */
/**
 * @brief ADS7828 channel enumeration
 */
typedef enum
{
    ADS7828_DE_PI_CH0=0b0000,					///< ads7828 channel 0
    ADS7828_DE_NI_CH0=0b0100,					///< ads7828 channel 0
    ADS7828_DE_PI_CH1=0b0001,					///< ads7828 channel 1
    ADS7828_DE_NI_CH1=0b0101,					///< ads7828 channel 1
    ADS7828_DE_PI_CH2=0b0010,					///< ads7828 channel 2
    ADS7828_DE_NI_CH2=0b0110,					///< ads7828 channel 2
    ADS7828_DE_PI_CH3=0b0011,					///< ads7828 channel 3
    ADS7828_DE_NI_CH3=0b0111,					///< ads7828 channel 3
    ADS7828_SE_CH0=0b1000,				    	///< ads7828 channel 0
    ADS7828_SE_CH1=0b1100,				    	///< ads7828 channel 1
    ADS7828_SE_CH2=0b1001,				    	///< ads7828 channel 2
    ADS7828_SE_CH3=0b1101,				    	///< ads7828 channel 3
    ADS7828_SE_CH4=0b1010,				    	///< ads7828 channel 4
    ADS7828_SE_CH5=0b1110,				    	///< ads7828 channel 5
    ADS7828_SE_CH6=0b1011,				    	///< ads7828 channel 6
    ADS7828_SE_CH7=0b1111,				    	///< ads7828 channel 7
    ADS7828_CH_MAX=0b10000,

}e_ads7828_chnl;

/**
 * @brief ADS7828 instance control block structure definition
 */
typedef struct
{
    void* intf_hdl;			    		/*!< IO interface handle pointer 	*/
    uint16_t slv_addr;					/*!< slave address  	        	*/
    ads7828_read_fptr_t read;           /*!< Read API function pointer      */
    ads7828_write_fptr_t write;       	/*!< Write API function pointer     */
}s_ads7828;

/**
 * @brief ADS7828 power down selection enumeration
 */
typedef enum
{
    PD_DWN,					    		///< ads7828 power down
    INT_REF_OFF_ADC_ON,					///< ads7828 internal reference OFF ADC ON
    INT_REF_ON_ADC_OFF,					///< ads7828 internal reference ON ADC OFF
    INT_REF_ON_ADC_ON,					///< ads7828 internal reference OFN ADC ON
    PD_SEL_MAX

}e_ads7828_pd_sel;

/**
 * @brief get ads7828 data
 * @param[in]  ads7828_hdl - instance pointer of ads7828
 * @param[in]  chnl - channel of ads7828
 * @param[in]  pd_opt -  power down option
 * @param[out]  data - data is updated
 * @retval e_ads7828_err - returns the success or error code
 */
e_ads7828_err ads7828_get_data(s_ads7828* ads7828_hdl,e_ads7828_chnl chnl,e_ads7828_pd_sel pd_opt,uint16_t* data);





#endif /* DRIVERS_AHW_DRIVERS_DATA_LOGGER_ADS7828_INC_ADS7828_H_ */

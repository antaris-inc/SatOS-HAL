/**
 * @file exo_ahw_al_voltage_sequencer_common.h
 *
 * @brief This file has enumeration,structure definition,
 * function declaration of voltage sequencer
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

#ifndef DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_COMMON_VSM_UCD9081_INC_EXO_AHW_AL_VSM_UCD9081_COMMON_H_
#define DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_COMMON_VSM_UCD9081_INC_EXO_AHW_AL_VSM_UCD9081_COMMON_H_

#include <stdint.h>
#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_ahw_al_common.h"

/**
 * @brief Part number of voltage sequencer and monitoring
 */
typedef enum
{
    VSM_UCD9081_1

}vltg_seq_part_no;

/**
 * @brief  voltage sequencer operating mode enumeration
 */
typedef enum
{
    VOLTAGE_SEQ_RAIL1,						/*!< ucd9081 rail1 */
    VOLTAGE_SEQ_RAIL2,						/*!< ucd9081 rail2 */
    VOLTAGE_SEQ_RAIL3,						/*!< ucd9081 rail3 */
    VOLTAGE_SEQ_RAIL4,						/*!< ucd9081 rail4 */
    VOLTAGE_SEQ_RAIL5,						/*!< ucd9081 rail5 */
    VOLTAGE_SEQ_RAIL6,						/*!< ucd9081 rail6 */
    VOLTAGE_SEQ_RAIL7,						/*!< ucd9081 rail7 */
    VOLTAGE_SEQ_RAIL8,						/*!< ucd9081 rail8 */
    VOLTAGE_SEQ_GPO1,						/*!< ucd9081 gpo1 */
    VOLTAGE_SEQ_GPO2,						/*!< ucd9081 gpo2 */
    VOLTAGE_SEQ_GPO3,						/*!< ucd9081 gpo3 */
    VOLTAGE_SEQ_GPO4,						/*!< ucd9081 gpo4 */
    VOLTAGE_SEQ_RAIL_MAX

}vltg_seq_rail_num;

/**
 * @brief voltage sequencer control block structure definition
 */
typedef struct
{
    ahw_al_gen_info ahw_gen_info;		 /*!< General information of voltage sequencer  */
    uint8_t v_ref_typ:1;			/*!< voltage reference type 					*/
    uint8_t flash_lock_sts:1;            	/*!< flash lock status	    	 				*/
}ahw_al_vsm_hdle;

/**
 * @brief  voltage sequencer reference enumeration
 */
typedef enum
{
    VOLTAGE_SEQ_VREF_INT,		    		/*!< internal voltage reference */
    VOLTAGE_SEQ_VREF_EXT		    		/*!< external voltage reference */
}vltg_seq_vref;

/**
 * @brief voltage sequencer rail configuration structure definition
 */
typedef struct
{
    vltg_seq_rail_num rail_nu;			/*!< voltage_seq rail number         	    	*/
    float r_pull_up;				/*!< voltage_seq rail pull up        	    	*/
    float r_pull_down;             			/*!< voltage_seq rail pull down   	    		*/
    uint16_t seq_dly_tm;            	        /*!< voltage_seq rail delay time    			*/
    float prnt_vlt;			    		/*!< voltage_seq rail parent voltage 	    	*/
    float udr_vlt_thrsld;                   	/*!< voltage_seq rail undervoltage threshold 	*/
    float ovr_vlt_thrsld;			    	/*!< voltage_seq rail overvoltage threshold     */
    uint8_t seq_type;           			/*!< voltage_seq rail sequence type 			*/
    uint16_t out_reg_width;  			/*!< voltage_seq rail out of regulation width   */
    uint16_t ramp_time;			    	/*!< voltage_seq rail ramp time		    		*/
    vltg_seq_rail_num prnt_rail;			/*!< voltage_seq rail parent rail	        	*/
    uint16_t unseq_time ;		    		/*!< voltage_seq rail unsequence time	     	*/
    uint16_t dpdncy_mask;	    			/*!< voltage_seq rail dependancy mask	    	*/
    uint8_t alrm_typ;		    		/*!< voltage_seq rail alarm type	       	 	*/
    uint8_t mntr_sts:1;       			/*!< voltage sequence rail monitor status   	*/
    uint8_t polarity:1;         			/*!< voltage_seq rail polarity		    		*/
    uint8_t reseq_sts:1;    			/*!< voltage_seq rail resequence status	    	*/
    uint8_t ext_vd_en:1;			    	/*!< voltage_seq rail external voltage enable   */
    uint8_t glt_alrm_sts:1;    			/*!< voltage_seq rail glitch alarm status		*/

}vltg_seq_rail_cfg;

/**
 * @brief API to initialization is set in this function
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_init();

/**
 * @brief API to configur the rail specified in the argument   z
 * @param[in]  al_vsm - AHAL instance pointer of voltage sequencer
 * @param[in]  rail_info - structure pointer of rail configuration
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_rail_config(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info);

/**
 * @brief API to set undervoltage threshold
 * @param[in]  al_vsm - AHAL instance pointer of voltage sequencer
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  udr_vltg_thrsld - voltage to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_undervoltage_thrsld(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float udr_vltg_thrsld);

/**
 * @brief API to set overvoltage threshold
 * @param[in]  al_vsm - AHAL instance pointer of voltage sequencer
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  ovr_vltg_thrsld - voltage to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_overvoltage_thrsld(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float ovr_vltg_thrsld);

/**
 * @brief API to set polarity enable
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  polarity - polarity to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_enable_polarity(ahw_al_vsm_hdle *al_vsm,  vltg_seq_rail_cfg* rail_info, uint8_t polarity);

/**
 * @brief API to set unsequence time
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  time - time to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_unsequence_time(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t time);

/**
 * @brief API to set out of regulation width
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  width - width to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_out_of_reg_width(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t width);

/**
 * @brief API to set ramp time
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  ramp_tm - ramp time to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_ramp_time(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t ramp_tm);

/**
 * @brief API to force restart
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_force_restart(ahw_al_vsm_hdle *al_vsm);

/**
 * @brief API to restart
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_restart(ahw_al_vsm_hdle *al_vsm);

/**
 * @brief API to get firmware version
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[out]  version - data gets updated in version
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_get_fw_version(ahw_al_vsm_hdle *al_vsm, uint8_t* version);

/**
 * @brief API to get voltage for the specified rail number
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[out]  voltage - data gets updated in voltage
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_get_voltage(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float *voltage);

/**
 * @brief API to get alarm pending status
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[out]  rail_err_sts - data gets updated in rail_err_sts
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_get_alrm_pndng_sts(ahw_al_vsm_hdle *al_vsm, uint8_t* rail_err_sts);

/**
 * @brief API to set sequence type
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  seq_tp - sequence type to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_seq_type(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info,uint8_t seq_tp);

/**
 * @brief API to set sequence delay
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  dly_tm - delay time to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_seq_delay(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t dly_tm);

/**
 * @brief API to set sequence parent voltage level
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  actual_rail_info - structure pointer of rail configuration for actual rail
 * @param[in]  parent_rail_info - structure pointer of rail configuration for parnt rail
 * @param[in]  voltage - voltage to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_seq_prnt_vltg_lvl(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* actual_rail_info, vltg_seq_rail_cfg* parent_rail_info, float voltage);

/**
 * @brief API to set sequence parent rail
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  prnt_rail - structure pointer of rail configuration for parent rail
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_seq_prnt_rail(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, vltg_seq_rail_num prnt_rail);

/**
 * @brief API to configure voltage reference
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  v_ref - voltage reference to be configured
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_vref_cfg(ahw_al_vsm_hdle *al_vsm,uint8_t v_ref);

/**
 * @brief API to configure glitch alarm
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  glth_alrm_sts - configure the glitch alarm status
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_glitch_alrm_cfg(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint8_t glth_alrm_sts);

/**
 * @brief API to set rail alarm type
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  alrm_typ - alarm type to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_vsm_set_rail_alrm_typ(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint8_t alrm_typ);


#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_COMMON_VSM_UCD9081_INC_EXO_AHW_AL_VSM_UCD9081_COMMON_H_ */

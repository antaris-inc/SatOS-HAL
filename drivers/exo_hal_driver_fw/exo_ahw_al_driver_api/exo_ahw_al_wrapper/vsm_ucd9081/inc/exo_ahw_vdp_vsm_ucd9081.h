/**
 * @file exo_ahw_vdp_vsm_ucd9081.h
 *
 * @brief This file has function prototype of voltage sequencer
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

#ifndef DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_VSM_UCD9081_INC_EXO_AHW_VDP_VSM_UCD9081_H_
#define DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_VSM_UCD9081_INC_EXO_AHW_VDP_VSM_UCD9081_H_

#include "exo_hal_common.h"
#include "exo_ahw_al_voltage_sequencer_common.h"
#include <stdlib.h>
#include "exo_io_al_i2c_common.h"
/**
 * @brief API to initialize the UCD9081
 * @param[in] ahw_al_hvsm - AHAL instance pointer of voltage sequencer
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_init (ahw_al_vsm_hdle *ahw_al_hvsm);

/**
 * @brief API to configure the rail specified in the argument
 * @param[in]  al_vsm - AHAL instance pointer of voltage sequencer
 * @param[in]  rail_info - structure pointer of rail configuration
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_rail_config(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info);

/**
 * @brief API to set the undervoltage threshold
 * @param[in]  al_vsm - AHAL instance pointer of voltage sequencer
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  udr_vltg_thrsld - voltage to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_undervoltage_thrsld(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float udr_vltg_thrsld);

/**
 * @brief API to set the overvoltage threshold
 * @param[in]  al_vsm - AHAL instance pointer of voltage sequencer
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  ovr_vltg_thrsld - voltage to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_overvoltage_thrsld(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float ovr_vltg_thrsld);

/**
 * @brief API to enable polarity
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  polarity - polarity to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_enable_polarity(ahw_al_vsm_hdle *al_vsm,  vltg_seq_rail_cfg* rail_info, uint8_t polarity);

/**
 *  @brief API to set unsequence time
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  time - time to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_unsequence_time(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t time);

/**
 * @brief API to set the out of regulation width
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  width - width to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_out_of_reg_width(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t width);

/**
 * @brief API to set the ramp time
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  ramp_tm - ramp time to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_ramp_time(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t ramp_tm);

/**
 * @brief This API is to force restart
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_force_restart(ahw_al_vsm_hdle *al_vsm);

/**
 * @brief This API is to restart
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_restart(ahw_al_vsm_hdle *al_vsm);

/**
 * @brief API to get firmware version
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[out]  version - data gets updated in version
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_get_fw_version(ahw_al_vsm_hdle *al_vsm, uint8_t* version);

/**
 * @brief API to get voltage of specified rail
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[out]  voltage - data gets updated in voltage
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_get_voltage(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, float *voltage);

/**
 * @brief API to get alarm pending status
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[out]  rail_err_sts - data gets updated in rail_err_sts
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_get_alrm_pndng_sts(ahw_al_vsm_hdle *al_vsm, uint8_t* rail_err_sts);

/**
 * @brief API to set the sequence type
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  seq_tp - sequence type to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_seq_type(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info,uint8_t seq_tp);

/**
 * @brief API to set the sequence delay
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  dly_tm - delay time to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_seq_delay(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint16_t dly_tm);

/**
 * @brief API to set the sequence parent voltage level
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  actual_rail_info - structure pointer of rail configuration for actual rail
 * @param[in]  parent_rail_info - structure pointer of rail configuration for parnt rail
 * @param[in]  voltage - voltage to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_seq_prnt_vltg_lvl(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* actual_rail_info, vltg_seq_rail_cfg* parent_rail_info, float voltage);

/**
 * @brief API to set sequence parent rail
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  prnt_rail - structure pointer of rail configuration for parent rail
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_seq_prnt_rail(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, vltg_seq_rail_num prnt_rail);

/**
 * @brief API to configure voltage reference
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  v_ref - voltage reference to be configured
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_vref_cfg(ahw_al_vsm_hdle *al_vsm,uint8_t v_ref);

/**
 * @brief API to configure glitch alarm
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  glth_alrm_sts - configure the glitch alarm status
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_glitch_alrm_cfg(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint8_t glth_alrm_sts);

/**
 * @brief API to set rail alarm type
 * @param[in]  al_vsm - AHAL instance pointer of UCD9081
 * @param[in]  rail_info - structure pointer of rail configuration
 * @param[in]  alrm_typ - alarm type to be set
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_vdp_vsm_ucd9081_set_rail_alrm_typ(ahw_al_vsm_hdle *al_vsm, vltg_seq_rail_cfg* rail_info, uint8_t alrm_typ);


#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_AHW_AL_DRIVER_API_EXO_AHW_AL_WRAPPER_VSM_UCD9081_INC_EXO_AHW_VDP_VSM_UCD9081_H_ */

/**
 * @file ucd9081.h
 *
 * @brief This file has structure definition,enumeration,
 * macros,function declaration of voltage sequencer UCD9081
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

#ifndef DRIVERS_AHW_DRIVERS_VOLTAGE_SEQUENCER_UCD9081_INC_UCD9081_H_
#define DRIVERS_AHW_DRIVERS_VOLTAGE_SEQUENCER_UCD9081_INC_UCD9081_H_

#include <stdint.h>
#include <stddef.h>

#define UCD9081_RAIL1H           0x00					///< register address of ucd9081 rail1
#define UCD9081_RAIL1L           0x01					///< register address of ucd9081 rail1
#define UCD9081_RAIL2H           0x02					///< register address of ucd9081 rail2
#define UCD9081_RAIL2L           0x03					///< register address of ucd9081 rail2
#define UCD9081_RAIL3H           0x04					///< register address of ucd9081 rail3
#define UCD9081_RAIL3L           0x05					///< register address of ucd9081 rail3
#define UCD9081_RAIL4H           0x06					///< register address of ucd9081 rail4
#define UCD9081_RAIL4L           0x07					///< register address of ucd9081 rail4
#define UCD9081_RAIL5H           0x08					///< register address of ucd9081 rail5
#define UCD9081_RAIL5L           0x09					///< register address of ucd9081 rail5
#define UCD9081_RAIL6H           0x0A					///< register address of ucd9081 rail6
#define UCD9081_RAIL6L           0x0B					///< register address of ucd9081 rail6
#define UCD9081_RAIL7H           0x0C					///< register address of ucd9081 rail7
#define UCD9081_RAIL7L           0x0D					///< register address of ucd9081 rail7
#define UCD9081_RAIL8H           0x0E					///< register address of ucd9081 rail8
#define UCD9081_RAIL8L           0x0F					///< register address of ucd9081 rail8
#define UCD9081_ERROR1           0x20					///< register address of ucd9081 error1
#define UCD9081_ERROR2           0x21					///< register address of ucd9081 error2
#define UCD9081_ERROR3           0x22					///< register address of ucd9081 error3
#define UCD9081_ERROR4           0x23					///< register address of ucd9081 error4
#define UCD9081_ERROR5           0x24					///< register address of ucd9081 error5
#define UCD9081_ERROR6           0x25					///< register address of ucd9081 error6
#define UCD9081_STATUS           0x26					///< register address of ucd9081 status
#define UCD9081_VERSION          0x27					///< register address of ucd9081 version
#define UCD9081_RAILSTATUS1      0x28					///< register address of ucd9081 railstatus1
#define UCD9081_RAILSTATUS2      0x29					///< register address of ucd9081 railstatus2
#define UCD9081_FLASHLOCK        0x2E					///< register address of ucd9081 flashlock
#define UCD9081_RESTART          0x2F					///< register address of ucd9081 restart
#define UCD9081_WADDR1           0x30					///< register address of ucd9081 write address 1
#define UCD9081_WADDR2           0x31					///< register address of ucd9081 write address 2
#define UCD9081_WDATA1           0x32					///< register address of ucd9081 write data 1
#define UCD9081_WDATA2           0x33					///< register address of ucd9081 write data 2

#define MAX_DLY_TIME             2048	    	    			///< maximum delay time
#define UCD9081_VREF_INTNL       2.5					///< ucd9081 internal voltage reference
#define UCD9081_VREF_EXTNL       3.3				    	///< ucd9081 external voltage reference


/**
 * @brief  mcp23008  flash address enumeration
 */
typedef enum
{
	UDR_VOLT_THRSLD_ADR,					/*!< undervoltage threshold address */
	OVR_VOLT_THRSLD_ADR,					/*!< overvoltage threshold address */
	RAMP_TIME_ADR,					    	/*!< ramp time address */
	OUT_REG_WDTH_ADR,						/*!< out of regulation width address */
	UNSEQ_TM_ADR,					    	/*!< unsequence transmitter address */
	EN_PLRTY_ADR,					    	/*!< enable polarity address */
	SEQ_EVT_PARA_ADR,						/*!< sequence event  address */
	SEQ_EVT_LNK_ADR,						/*!< sequence event link address */
	SEQ_EVT_DTA_ADR,						/*!< sequence event data address */
	DPNDNCY_MSK_ADR,						/*!< dependancy mask address */
	CFG_FLSH_MAX_ADDR						/*!< configuration flash maximum address */

}e_cfg_flash_addr;

/**
 * @brief  mcp23008  voltage reference enumeration
 */
typedef enum
{
	UCD9081_VREF_INT,						/*!< internal voltage reference */
	UCD9081_VREF_EXT						/*!< external voltage reference */
}e_vref;

/**
 * @brief  read API function pointer
 */
typedef int8_t (*ucd9081_read_fptr_t)(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/**
 * @brief  write API function pointer
 */
typedef int8_t (*ucd9081_write_fptr_t)(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/**
 * @brief  UCD9081 operating mode enumeration
 */
typedef enum
{
    UCD9081_RAIL1,						/*!< ucd9081 rail1 */
    UCD9081_RAIL2,						/*!< ucd9081 rail2 */
    UCD9081_RAIL3,						/*!< ucd9081 rail3 */
    UCD9081_RAIL4,						/*!< ucd9081 rail4 */
    UCD9081_RAIL5,						/*!< ucd9081 rail5 */
    UCD9081_RAIL6,						/*!< ucd9081 rail6 */
    UCD9081_RAIL7,						/*!< ucd9081 rail7 */
    UCD9081_RAIL8,						/*!< ucd9081 rail8 */
    UCD9081_GPO1,						/*!< ucd9081 gpo1 */
    UCD9081_GPO2,						/*!< ucd9081 gpo2 */
    UCD9081_GPO3,						/*!< ucd9081 gpo3 */
    UCD9081_GPO4,						/*!< ucd9081 gpo4 */
    UCD9081_RAIL_MAX

}e_ucd9081_rail_no;

/**
 *  @brief  UCD9081 error status enumeration
 */
typedef enum
{
    UCD9081_SCS        =  0,					/*!< ucd9081 success */
    UCD9081_ERR        = -1,					/*!< ucd9081 error */
    UCD9081_INVLD_ARG  = -2,					/*!< ucd9081 invalid argument */
    UCD9081_ALRDY_USD  = -3,					/*!< ucd9081 already used */
    UCD9081_COM_ERR    = -4,					/*!< ucd9081 communication error */
    UCD9081_NULL_PTR   = -5,					/*!< ucd9081 NULL pointer */
    UCD9081_ERR_MAX    = -6

}e_ucd9081_err;

/**
 * @brief  UCD9081 control block structure definition
 */
typedef struct
{
    void* intf_hdl;		    	/*!< IO interface handle pointer 	*/
    uint16_t slv_addr;			/*!< slave address	    			*/
    uint8_t v_ref_typ:1;		/*!< voltage reference type 		*/
    uint8_t flash_lock_sts:1;           /*!< flash lock status		 		*/
    ucd9081_read_fptr_t read;           /*!< Read API function pointer      */
    ucd9081_write_fptr_t write;         /*!< Write API function pointer     */
}s_ucd9081;

/**
 * @brief  mcp23008  rail configuration structure definition
 */
typedef struct
{
    e_ucd9081_rail_no rail_nu;			/*!< ucd9081 rail number         			*/
    float r_pull_up;			    	/*!< ucd9081 rail pull up        			*/
    float r_pull_down;             			/*!< ucd9081 rail pull down   	 			*/
    uint16_t seq_dly_tm;            	        /*!< ucd9081 rail delay time 	 			*/
    float prnt_vlt;				 	/*!< ucd9081 rail parent voltage 			*/
    float udr_vlt_thrsld;                   	/*!< ucd9081 rail undervoltage threshold    */
    float ovr_vlt_thrsld;				/*!< ucd9081 rail overvoltage threshold     */
    uint8_t seq_type;           			/*!< ucd9081 rail sequence type				*/
    uint16_t out_reg_width;     	        	/*!< ucd9081 rail out of regulation width   */
    uint16_t ramp_time;			    	/*!< ucd9081 rail ramp time					*/
    e_ucd9081_rail_no prnt_rail;			/*!< ucd9081 rail parent rail			    */
    uint16_t unseq_time ;		    		/*!< ucd9081 rail unsequence time		 	*/
    uint16_t dpdncy_mask;				/*!< ucd9081 rail dependancy mask			*/
    uint8_t alrm_typ;			    	/*!< ucd9081 rail alarm type			    */
    uint8_t mntr_sts:1;       			/*!< ucd9081 monitor status   				*/
    uint8_t polarity:1;         			/*!< ucd9081 rail polarity			    	*/
    uint8_t reseq_sts:1;    			/*!< ucd9081 rail resequence status			*/
    uint8_t ext_vd_en:1;			    	/*!< ucd9081 rail external voltage enable   */
    uint8_t glt_alrm_sts:1;    			/*!< ucd9081 rail glitch alarm status		*/

}s_ucd9081_rail_cfg;

/**
 * @brief  UCD9081 rail error status enumeration
 */
typedef enum
{
    UCD9081_NULL_ALRM,						///< ucd9081 rail NULL alarm
    UCD9081_SPLY_NOT_STD,					///< ucd9081 supply not started
    UCD9081_OVR_VOLT_DTD,					///< ucd9081 overvoltage detected
    UCD9081_UDR_VOLT_DTD,					///< ucd9081 undervoltage detected
    UCD9081_OVR_VOLT_GTH_DTD,		       			///< ucd9081 overvoltage glitch detected
    UCD9081_UDR_VOLT_GTH_DTD,			    		///< ucd9081 undervoltage glitch detected
    UCD9081_I2C_PHY_ERR,					///< ucd9081 firmware error
    UCD9081_FRMWR_ERR,						///< ucd9081 maximum rail error
    UCD9081_MAX_RAIL_ERR					///< ucd9081 maximum rail error

}e_rail_err;

/**
 * @brief  UCD9081 rail error status structure definition
 */
typedef struct
{
    e_rail_err err_code;					/*!< ucd9081 rail error code	    	*/
    e_ucd9081_rail_no rail_no;					/*!< ucd9081 rail number    			*/
    uint16_t value ;					   	/*!< ucd9081 rail value					*/
    uint8_t hours;					    	/*!< ucd9081 rail hours					*/
    uint8_t minutes;						/*!< ucd9081 rail minutes	    		*/
    uint8_t seconds;						/*!< ucd9081 rail seconds		    	*/
    uint8_t milliseconds;					/*!< ucd9081 rail milliseconds			*/

}s_err_info;

/**
 * @brief  mcp23008  rail sequence type enumeration
 */
typedef enum
{
    UCD9081_NO_SEQ,          ///< Sequence is disabled
    UCD9081_SEQ_AFT_DLY,     ///< Sequence is triggered after delay after sequence event
    UCD9081_SEQ_PRNT_VLTG,   ///< Sequence is triggered after parent rail achieves voltage level
    UCD9081_SEQ_PRNT_DLY,    ///< Sequence is triggered after delay after parent rail achieves voltage regulation
    UCD9081_MAX_SEQ_TP
}e_rail_seq_type;

/**
 * @brief  mcp23008  rail alarm type enumeration
 */
typedef enum
{
    UCD9081_LOG_ONLY   = 0b000,			///< ucd9081 log only
    UCD9081_SEQUENCE   = 0b001,			///< ucd9081 sequence
    UCD9081_RTRY_1_TM  = 0b101,			///< ucd9081 retry one time
    UCD9081_RTRY_0_TM  = 0b110,			///< ucd9081 retry zero time
    UCD9081_MAX_ALRM_TYP = 0b1000		///< ucd9081 maximum alarm type
}e_rail_alrm_typ;


/**
 * @brief UCD9081 initialization is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_init(s_ucd9081* ucd9081_hdl);

/**
 * @brief UCD9081 undervoltage threshold is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in]  voltage - voltage in float to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_undervoltage_thrsld(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, float voltage);

/**
 * @brief UCD9081 overvoltage threshold is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in]  voltage - voltage in float to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_overvoltage_thrsld(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, float voltage);

/**
 * @brief UCD9081 polarity enable is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in]  polarity - polarity to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_enable_polarity(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail,uint8_t polarity);

/**
 * @brief UCD9081 unsequence time is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in]  time - time to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_unsequence_time(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, uint16_t time);

/**
 * @brief UCD9081 out of regulation width is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in]  width - width to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_out_of_reg_width(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, uint16_t width);

/**
 * @brief UCD9081 ramp time is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in]  ramp_tm - ramp time to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_ramp_time(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, uint16_t ramp_tm);

/**
 * @brief UCD9081 force restart in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_force_restart(s_ucd9081* ucd9081_hdl);

/**
 * @brief UCD9081 restart in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_restart(s_ucd9081* ucd9081_hdl);

/**
 * @brief get the UCD9081 firmware version
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  version – data of version
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_get_fw_version(s_ucd9081* ucd9081_hdl,uint8_t *version);

/**
 * @brief get UCD9081 error status
 * This function get the error status of the ucd9081
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_get_err_sts(s_ucd9081* ucd9081_hdl);

/**
 * @brief get UCD9081 voltage
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in]  voltage - data is updated in voltage
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_get_voltage(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, float* voltage);

/**
 * @brief This function configure the rail specified in the parameter
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_rail_config(s_ucd9081* ucd9081_hdl,s_ucd9081_rail_cfg* rail);

/**
 * @brief UCD9081 dependancy mask is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in] dpdncy_msk -  dependancy mask to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_dependency_mask(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail,uint16_t dpdncy_msk);

/**
 * @brief get UCD9081 alarm pending status
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[out]  rail_err_sts - pointer of rail error status configuration
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_get_alrm_pndng_sts(s_ucd9081* ucd9081_hdl, uint8_t* rail_err_sts);

/**
 * @brief UCD9081 sequence type is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in] seq_tp -  sequence type to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_seq_type(s_ucd9081* ucd9081_hdl,s_ucd9081_rail_cfg* rail, uint8_t seq_tp);

/**
 * @brief UCD9081 sequence delay is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in] dly_tm - delay time to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_seq_delay(s_ucd9081* ucd9081_hdl,s_ucd9081_rail_cfg* rail, uint16_t dly_tm);

/**
 * @brief UCD9081 sequence parent voltage level is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  actual_rail - pointer of actual rail configuration
 * @param[in]  prnt_rail - pointer of actual rail configuration
 * @param[in] voltage - voltage to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_seq_prnt_vltg_lvl(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* actual_rail, s_ucd9081_rail_cfg* prnt_rail, float voltage);

/**
 * @brief UCD9081 sequence parent rail is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  actual_rail - pointer of actual rail configuration
 * @param[in]  prnt_rail - parent rail to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_seq_prnt_rail(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* actual_rail, e_ucd9081_rail_no prnt_rail);

/**
 * @brief UCD9081 voltage reference configuration in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  v_ref - data of voltage reference
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_vref_cfg(s_ucd9081* ucd9081_hdl,uint8_t v_ref);

/**
 * @brief UCD9081 glitch alarm configuration in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in]  glth_alrm_sts - data of glitch alarm status
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_glitch_alrm_cfg(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail, uint8_t glth_alrm_sts);

/**
 * @brief UCD9081 rail alarm type is set in this function
 * @param[in]  ucd9081_hdl - instance pointer of UCD9081
 * @param[in]  rail - pointer of rail configuration
 * @param[in] 	alrm_typ - alarm type to be set
 * @retval e_UCD9081_err - returns the success or error code
 */
e_ucd9081_err ucd9081_set_rail_alrm_typ(s_ucd9081* ucd9081_hdl, s_ucd9081_rail_cfg* rail,uint8_t alrm_typ);


#endif /* DRIVERS_AHW_DRIVERS_VOLTAGE_SEQUENCER_UCD9081_INC_UCD9081_H_ */

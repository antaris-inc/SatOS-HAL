/**
 * @file psm_ina230.h
 *
 *  @brief This file contains the macros,structure declaration,enumeration,
 *  function declaration of power sense monitor INA230
 *
 *	@copyright Copyright 2023 Antaris, Inc.
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

#ifndef PSM_INA230_H_
#define PSM_INA230_H_
#include <stdint.h>
#include "psm_register_map.h"

#define DEF_CALIB 0x0A00

/**
 * @brief read function pointer
 */
typedef uint8_t (*psm_ina230_read_fptr_t)(void* intf_hdl,uint16_t slave_address, uint8_t reg_addr, uint8_t *data, uint16_t len);

/**
 * @brief read function pointer
 */
typedef uint8_t (*psm_ina230_write_fptr_t)(void* intf_hdl,uint16_t slave_address, uint8_t reg_addr, uint8_t *read_data, uint16_t len);


/** @brief  Power Monitor Alert Latch Enable enumeration
 *
 */
typedef enum
{
    ALERT_LATCH_DISABLE = 0,				/*!< ALERT_LATCH Disable */
    ALERT_LATCH_ENABLE,					/*!< ALERT_LATCH Enable */
    ALERT_LATCH_MAX						/*!< ALERT_LATCH_MAX */
} ina230_ale_t;

/**
 * @brief power sense monitor operating mode enumeration
 */

typedef enum
{
    INA230_OPERATING_MODE_TRIGGERED = 0,		/*!< OPERATING_MODE_TRIGGERED is initialized */
    INA230_OPERATING_MODE_CONTINUOUS,		/*!< OPERATING_MODE_CONTINUOUS is initialized */
    INA230_OPERATING_MODE_MAX			/*!< OPERATING_MODE_MAX is initialized */
} ina230_operatingmode_t;

/**
 * @brief power sense monitor conversion time enumeration
 */
typedef enum
{
    INA230_CONVERT_TIME_140 = 0,					/*!< CONVERT_TIME at 140 */
    INA230_CONVERT_TIME_204,					/*!< CONVERT_TIME at 204 */
    INA230_CONVERT_TIME_332,					/*!< CONVERT_TIME at 332 */
    INA230_CONVERT_TIME_588,					/*!< CONVERT_TIME at 588 */
    INA230_CONVERT_TIME_1100,					/*!< CONVERT_TIME at 1100 */
    INA230_CONVERT_TIME_2116,					/*!< CONVERT_TIME at 2116 */
    INA230_CONVERT_TIME_4156,					/*!< CONVERT_TIME at 4156 */
    INA230_CONVERT_TIME_8244,					/*!< CONVERT_TIME at 8244 */
    INA230_CONVERT_TIME_MAX						/*!< CONVERT_TIME at MAX */
} ina230_tc_t;

/**
 * @brief power sense monitor averaging mode enumeration
 */
typedef enum
{
    INA230_AVERAGING_MODE_1 = 0,					/*!< AVERAGING_MODE at 1 */
    INA230_AVERAGING_MODE_4,					/*!< AVERAGING_MODE at 4 */
    INA230_AVERAGING_MODE_16,					/*!< AVERAGING_MODE at 16 */
    INA230_AVERAGING_MODE_64,					/*!< AVERAGING_MODE at 64 */
    INA230_AVERAGING_MODE_128,					/*!< AVERAGING_MODE at 128 */
    INA230_AVERAGING_MODE_256,					/*!< AVERAGING_MODE at 256 */
    INA230_AVERAGING_MODE_512,					/*!< AVERAGING_MODE at 512 */
    INA230_AVERAGING_MODE_1024,					/*!< AVERAGING_MODE at 1024 */
    INA230_AVERAGING_MODE_MAX					/*!< AVERAGING_MODE at MAX */
} ina230_am_t;

/**
 * @brief power sense monitor alert polarity enumeration
 */
typedef enum
{
    ALERT_POLARITY_NORMAL = 0,				/*!< ALERT_POLARITY_NORMAL */
    ALERT_POLARITY_INVERTED,				/*!< ALERT_POLARITY_INVERTED */
    ALERT_POLARITY_MAX					/*!< ALERT_POLARITY_MAX */
} ina230_ap_t;

/**
 * @brief power sense monitor alert function enumeration
 */
typedef enum
{
    ALERT_FUNCTION_NONE = 0,				/*!< ALERT_FUNCTION_NONE */
    ALERT_FUNCTION_SOL,					/*!< ALERT_FUNCTION_SOL */
    ALERT_FUNCTION_SUL,					/*!< ALERT_FUNCTION_SUL */
    ALERT_FUNCTION_BOL,					/*!< ALERT_FUNCTION_BOL */
    ALERT_FUNCTION_BUL,					/*!< ALERT_FUNCTION_BUL */
    ALERT_FUNCTION_POL,					/*!< ALERT_FUNCTION_POL */
    ALERT_FUNCTION_MAX					/*!< ALERT_FUNCTION_MAX */
} ina230_af_t;

/**
 * @brief power sense monitor Voltage Input signal enumeration
 */
typedef enum
{
    INA230_VOLTAGE_INPUT_SHUNT = 0,			/*!< VOLTAGE_INPUT_SHUNT */
    INA230_VOLTAGE_INPUT_BUS,					/*!< VOLTAGE_INPUT_BUS */
    INA230_VOLTAGE_INPUT_ALL,					/*!< VOLTAGE_INPUT_ALL */
    INA230_VOLTAGE_INPUT_MAX					/*!< VOLTAGE_INPUT_MAX */
} ina230_inputsignal_t;

/**
 * @brief power Monitor Flag enumeration
 */
typedef enum
{
    INA230_FLAG_ALERT_FUNCTION = 0,			/*!<FLAG_ALERT_FUNCTION */
    INA230_FLAG_CONVERSION_READY,		    /*!<FLAG_CONVERSION_READY */
    INA230_FLAG_MATH_OVERFLOW,				/*!<FLAG_MATH_OVERFLOW */
    INA230_FLAG_MAX							/*!<FLAG_MAX */
} ina230_flag_t;

/**
 * @brief power sense monitor error status enumeration
 */
typedef enum
{
    INA230_SCS=0,								/*!< success status */
    INA230_ERR=1,								/*!< error status */
}e_ina230_sts;

/**
 * @brief power Monitor Device configuration structure
 */
typedef struct
{
    ina230_tc_t    shunt_tc;				/*!< shunt conversion_time enumeration of INA230*/
    ina230_tc_t    bus_tc;				/*!< bus conversion_time enumeration  of INA230 */
    ina230_am_t    averaging_mode;			/*!< average_mode enumeration of INA230			*/
} ina230_convert_time_config_t;

/**
 * @brief ina230 convert time configuration pointer type definition
 */
typedef ina230_convert_time_config_t *ina230_Cfg_ptr_t;

/**
 * @brief power Monitor Device  structure
 */
typedef struct
{

    uint16_t slave_address;			/*!< slave address of INA230 		*/
    float current_threshold;			/*!< current threshold				*/
    float vbus_threshold;				/*!< vbus threshold					*/
    uint32_t power_threshold;			/*!< power threshold				*/
    psm_ina230_read_fptr_t read;			/*!< read function pointer			*/
    psm_ina230_write_fptr_t write;		/*!< write function pointer			*/
    uint8_t die_id;				/*!< chip id						*/
    void *io_intf_hdle;				/*!< interface handle				*/
    ina230_af_t alert_function;			/*!< alert function enumeration		*/
    ina230_inputsignal_t inputsignal; 		/*!< input signal enumeration		*/
    ina230_operatingmode_t mode;			/*!< Operating mode enumeration		*/
    ina230_flag_t flag;				/*!< INA230 flag enumeration		*/
} psm_ina230_dev_t;

/**
 * @brief ina230 control block memory pointer type definition
 */
typedef psm_ina230_dev_t *ina230_dev_ptr_t;

/**
 * @brief power Monitor Alert pin configuration structure
 */
typedef struct
{
    ina230_ap_t    polarity;	/*!< INA230_power sense monitor alert polarity enumeration */
    ina230_ale_t latch_enable;	/*!< INA230_Power Monitor Alert Latch Enable enumeration  */
} ina230_alertpinconfig_t;

/**
 * @brief ina230 alert pin configuration pointer type definition
 */
typedef ina230_alertpinconfig_t *ina230_alert_pinconfig_ptr_t;

/**
 * @brief Write access to INA230 register
 * @param[in] ina230_hdl : structure handle of power sense monitor of ina230`
 * @param[in] reg 		: Register address from where the data to be read.
 * @param[in] data		: data value to store.
 * @retval e_ina230_sts - returns the success or error code
 */
e_ina230_sts ina230_writereg(ina230_dev_ptr_t ina230_hdl, uint8_t Reg, uint16_t Data);

/**
 * @brief read access to INA230 register
 * @param[in] ina230_hdl : structure handle of power sense monitor of ina230`
 * @param[in] reg 		: Register address from where the data to be read.
 * @retval e_ina230_sts - returns the success or error code
 */
e_ina230_sts ina230_readreg(ina230_dev_ptr_t ina230_hdl, uint8_t Reg,uint16_t* data);

/**
 * @brief Initialize the INA230 and configure.
 * @param[in] ina230_hdl : structure handle of power sense monitor of ina230.
 * @param[in] reg 			: Register address from where the data to be read.
 * @retval e_ina230_sts - returns the success or error code
 */
e_ina230_sts ina230_init(ina230_dev_ptr_t ina230_hdl,ina230_Cfg_ptr_t ina230_cfg);

/**
 * @brief De-Initialize the INA230 and reset
 * @param[in] ina230_hdl : structure handle of power sense monitor of ina230
 * @retval hal_ret_sts - returns the success or error code
 */
e_ina230_sts ina230_deinit(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief read the die id or chip id.
 * @param[in] ina230_hdl : structure handle of power sense monitor of ina230
 * @retval hal_ret_sts - returns the success or error code
 */
uint16_t ina230_read_id(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief Generates a system reset.
 * @param[in] ina230_hdl : structure handle of power sense monitor of ina230
 * @retval hal_ret_sts - returns the success or error code
 */
e_ina230_sts ina230_reset(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief Program the INA230 calibration register
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230
 * @param[in] calibration 	: calibration value for ina230
 * @retval hal_ret_sts - returns the success or error code
 */
e_ina230_sts ina230_set_calibration(ina230_dev_ptr_t ina230_hdl, uint16_t calibration);

/**
 * @brief read the set value in the INA230 calibration register
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230
 * @retval					: calibration value
 */
uint16_t ina230_get_calibration(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief Configure the alert pin behavior
 * @param[in]  ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @param[in] alert_pin_cfg_vd	: structure handle of Alert pin configuration.
 * @retval e_ina230_sts		:returns the success or error code
 */
e_ina230_sts ina230_alert_pinconfig(ina230_dev_ptr_t ina230_hdl,ina230_alert_pinconfig_ptr_t alert_pin_cfg_vd);

/**
 * @brief Set the alert function
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @param[in] AlertFunction Monitored alert function.
 * This parameter can be take one of the following values:
 *         ALERT_FUNCTION_NONE
 *         ALERT_FUNCTION_SOL
 *         ALERT_FUNCTION_SUL
 *         ALERT_FUNCTION_B0L
 *         ALERT_FUNCTION_BUL
 *         ALERT_FUNCTION_POL
 * @retval e_ina230_sts		:returns the success or error code
 */
e_ina230_sts ina230_set_alertfunction(ina230_dev_ptr_t ina230_hdl,ina230_af_t alert_function);

/**
 * @brief Get the programmed alert function
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @param[in] AlertFunction Monitored alert function.
 * This parameter can be take one of the following values:
 *         ALERT_FUNCTION_NONE
 *         ALERT_FUNCTION_SOL
 *         ALERT_FUNCTION_SUL
 *         ALERT_FUNCTION_B0L
 *         ALERT_FUNCTION_BUL
 *         ALERT_FUNCTION_POL
 * @retval e_ina230_sts- returns the success or error code
 */
e_ina230_sts ina230_get_alertfunction(ina230_dev_ptr_t ina230_hdl,ina230_af_t alert_function);

/**
 * @brief Program the VBus threshold.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @param[in] vbusthreshold	: vbusthreshold value
 * @retval e_ina230_sts - returns the success or error code
 */
e_ina230_sts ina230_setvbusthreshold(ina230_dev_ptr_t ina230_hdl, float vbusthreshold);

/**
 * @brief get the VBus threshold.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval					:  VBusThreshold VBus threshold value (in mV).
 */
uint16_t ina230_getvbusthreshold(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief set the current threshold.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @param[in] current       : value of current
 * @retval					:  error Status
 */
e_ina230_sts ina230_set_current_threshold(ina230_dev_ptr_t ina230_hdl, float current);

/**
 * @brief Program the VShunt threshold
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @param[in] vshuntthreshold	: vshuntthreshold value
 * @retval e_ina230_sts - returns the success or error code
 */
e_ina230_sts ina230_setvshuntthreshold(ina230_dev_ptr_t ina230_hdl, float vshuntthreshold);

/**
 * @brief get the vshunt threshold.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval vshuntthreshold	:   VShunt threshold value (in mV).
 */
int16_t ina230_getshuntthreshold(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief Program the power threshold.
 * @param[in] ina230_hdl 		: structure handle of power sense monitor of ina230.
 * @param[in] powerthreshold	: powerthreshold value
 * @retval e_ina230_sts - returns the success or error code
 */
e_ina230_sts ina230_setpowerthreshold(ina230_dev_ptr_t ina230_hdl, uint32_t powerthreshold);

/**
 * @brief get the vshunt threshold.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval	powerthreshold	: powerThreshold value (in mV).
 */
uint32_t ina230_getpowerthreshold(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief Enable the voltage/power threshold interrupt.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval e_ina230_sts  - returns the success or error code
 */
e_ina230_sts ina230_alert_threshold_enable_it(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief Disable the voltage/power threshold interrupt
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval e_ina230_sts  - returns the success or error code
 */
e_ina230_sts ina230_alert_threshold_disable_it(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief Enable the conversion ready interrupt
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval hal_ret_sts - returns the success or error code
 */
e_ina230_sts ina230_conversion_ready_enable_it(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief disable the conversion ready interrupt.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval e_ina230_sts - returns the success or error code
 */
e_ina230_sts ina230_conversion_ready_disable_it(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief  Launch the conversion on the selected voltage input
 * @param  ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @param  InputSignal Input signal to convert.
 *         This parameter can be take one of the following values:
 *         INPUT_SIGNAL_SHUNT
 *         INPUT_SIGNAL_BUS
 *         INPUT_SIGNAL_ALL
 * @param  Mode operating mode.
 *         This parameter can be take one of the following values:
 *         OPERATING_MODE_CONTINUOUS
 *         OPERATING_MODE_TRIGGERED
 * @retval e_ina230_sts - returns the success or error code
 */
e_ina230_sts ina230_startconversion(ina230_dev_ptr_t ina230_hdl, ina230_inputsignal_t inputsignal, ina230_operatingmode_t mode);

/**
 * @brief Stop the conversion on the selected voltage input.
 * @param  ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval e_ina230_sts  - returns the success or error code
 */
e_ina230_sts ina230_stopconversion(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief get the vbus voltage.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval	vbus voltage	: vbus voltage value (in V).
 */
float ina230_get_vbus(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief get the VShunt voltage.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval	VShunt voltage	: VShunt voltage value (in mV).
 */
float ina230_get_vshunt(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief get the power.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval	power	: power value (in mW).
 */
uint32_t ina230_get_power(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief get the current value.
 * @param[in] ina230_hdl 	: structure handle of power sense monitor of ina230.
 * @retval	current	: current value (in A).
 */
float ina230_get_current(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief  Read the designed flag value
 * @param  Flag specifies the flag to check.
 *         This parameter can be one of the following values:
 *         FLAG_ALERT_FUNCTION
 *         FLAG_CONVERSION_READY
 *         FLAG_MATH_OVERFLOW
 * @retval Actual state of the flag (TRUE or FALSE).
 */
uint8_t ina230_get_flag(ina230_dev_ptr_t ina230_hdl, ina230_flag_t flag);






#endif /* PSM_INA230_H_ */

/**
 * @file mcp9843.h
 *
 *  @brief This file contains the macros,structure declaration,enumeration,
 *  function declaration of temperature sensor MCP9843
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

#ifndef INC_MCP9843_H_
#define INC_MCP9843_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



/*ADDRESS REGISTER */

#define MCP9843_CAPA_REG                  (0x00)              ///< Sensor Capability Register address is 0x00
#define MCP9843_CONF_REG                  (0x01)              ///< Sensor Configuration Register address
#define MCP9843_T_UPPER                   (0x02)              ///< temperature_upper Register address
#define MCP9843_T_LOWER                   (0x03)              ///< temperature_lower Register address
#define MCP9843_T_CRITICAL                (0x04)              ///< temperature_critical Register address
#define MCP9843_TEMP_REG                  (0x05)              ///< Sensor temperature/Ambient temperature Register address
#define MCP9843_MANUFACTURE_ID_REG        (0x06)              ///< Manufacture ID Register, valu=0x0054 address
#define MCP9843_DVE_ID_REG_ADRR           (0x07)              ///< Device / Revision ID
#define MCP9843_RESO_REG                  (0x08)              ///< Register to control the resolution of the temperature sensor address
#define MCP9843_DEV_ID					  (0x07)              ///< Device ID for MCP9843 address

/************Resolution Register Bit definitions****************/

#define MCP9843_RESO_REG_BIT_0                    (1<<0)	///< Resolution bit 0 set
#define MCP9843_RESO_REG_BIT_1                    (1<<1)	///< Resolution bit 1 set

/************Lock_bit_definitions****************/

#define MCP9843_WIN_LOCK_BIT_6                    (1<<6)	///< window_lock bit 6 set
#define MCP9843_CRIT_LOCK_BIT_7                   (1<<7)	///< critical_lock bit 7 set

/***************shut_down_mode_bit_definition******************/

#define MCP9843_SHUT_DOWN_BIT_8					  (1<<8)	///< shut_down bit 8 set

/******************EVENT_mode_bit_definition******************/

#define MCP9843_INTERRUPT_OUTPUT_MODE_BIT_0		  (1<<0)	///< INTERRUPT_OUTPUT_MODE bit 0 set

#define MCP9843_EVENT_POLARITY_BIT_1			  (1<<1)	///< EVENT_POLARITY bit 1 set

#define MCP9843_TEMP_ALARM_ALERT                  (1<<0)	///< TEMP_ALARM_ALERT bit 0 set

/***************bit_lock_definition**************************/

#define MCP9843_LOCK_BIT_WIN_POS                (6U)		///!< win_lock bit position

#define MCP9843_LOCK_BIT_WIN					(0x1U<<6U)	///< win_lock bit_6 set

#define MCP9843_LOCK_BIT_CRIT_POS               (7U)		///< crit_lock bit position

#define MCP9843_LOCK_BIT_CRIT			        (0x1U<<7U)	///< critical_lock bit_6 set
/***********HYSTERESIS REGISTER config Bit 10 and 9***********/

#define MCP9843_HYST_BIT_9                        (1<<9)	///< HYSTERESIS bit_9 set

#define MCP9843_HYST_BIT_10                       (1<<10)	///< HYSTERESIS bit_10 set

/***********INTERRUPT CLEAR Bit 05***********/
#define MCP9843_INT_CLEAR_BIT_05				  (1<<5)	///< INTERRUPT CLEAR bit_05 set

/***********Temperature byte conversion***********/

#define CLEAR_FLAG_BITS_MASK                  	  (0x1F)	///< Mask to CLEAR the FLAG bits during temperature conversion capture.

#define MSB_MASK                           		  (0xFF00)	///< Masking access to only the MSB values returned by the ambient temperature register

/**
 * @brief read function pointer
 */
typedef uint16_t (*mcp9843_read_fptr_t)(void* intf_hdl,uint16_t slave_address, uint8_t reg_addr, uint8_t *data, uint16_t len);
/**
 * @brief write function pointer
 */
typedef uint16_t (*mcp9843_write_fptr_t)(void* intf_hdl,uint16_t slave_address, uint8_t reg_addr, uint8_t *read_data, uint16_t len);


/**
 * @brief temperature sensor error status enumeration
 */
typedef enum
{
    MCP9843_SCS=0,						/*!< MCP9843 success */
    MCP9843_OK=MCP9843_SCS,				/*!< MCP9843 ok */
    MCP9843_E_NULL_PTR=-1,				/*!< MCP9843 NULL pointer */
    MCP9843_E_DEV_NOT_FOUND=-2,			/*!< MCP9843 device not found */
    MCP9843_E_COM_FAIL=-3,				/*!< MCP9843 communication fail */
    MCP9843_TEMP_READ_FAIL=-4,			/*!< MCP9843 temperature read fail */
    MCP9843_ERR=-5,						/*!< MCP9843 error */
    MCP9843_READ_FAIL,					/*!< MCP9843 read fail */
    ERR_MAX
}e_temp_sensor_sts;
/**
 * @brief MCP9843 temperature sensor mode of operation enumeration
 */
typedef enum
{
    MCP9843_CONTINUOUS_CONVERSTION=(0X00 & MCP9843_SHUT_DOWN_BIT_8),		/*!< MCP9843 continous conversion */
    MCP9843_SHUTDOWN_MODE=MCP9843_SHUT_DOWN_BIT_8,							/*!< MCP9843 shutdown mode */
    MCP9843_MODE_MAX
}mcp9843_mode_t;
/**
 * @brief MCP9843 temperature sensor event output mode enumeration
 */
typedef enum
{
    MCP9843_COMPARATOR_EVENT_MODE = 0x80, /*!< MCP9843 comparator event mode */
    MCP9843_INTRUPT_EVENT_MODE = 0x09,	  /*!< MCP9843 interrupt event mode */
    MCP9843_EVENT_NONE=0x0
}mcp9843_event_output_mode_t;
/**
 * @brief MCP9843 temperature sensor resolution enumeration
 */
typedef enum
{
    MCP9843_RES_0_5    = 0,													/*!< MCP9843 resolution 0-5 */
    MCP9843_RES_0_25   = MCP9843_RESO_REG_BIT_0,							/*!< MCP9843 resolution 0-25 */
    MCP9843_RES_0_125  = MCP9843_RESO_REG_BIT_1,							/*!< MCP9843 resolution 0-125 */
    MCP9843_RES_0_0625 = MCP9843_RESO_REG_BIT_1 | MCP9843_RESO_REG_BIT_0	/*!< MCP9843 resolution 0-625 */
}mcp9843_res_t;

/**
 * @brief MCP9843 temperature sensor hysteresis enumeration
 */
typedef enum
{
    MCP9843_HYS_0_0  = 0,											/*!< MCP9843 hysteresis 0-0 */
    MCP9843_HYS_1_5  = MCP9843_HYST_BIT_9,							/*!< MCP9843 hysteresis 1-5 */
    MCP9843_HYS_3_0  = MCP9843_HYST_BIT_10,							/*!< MCP9843 hysteresis 3-0 */
    MCP9843_HYS_6_0  = MCP9843_HYST_BIT_10  | MCP9843_HYST_BIT_9	/*!< MCP9843 hysteresis 6-0 */
}mcp9843_hyst_t;

/**
 * @brief MCP9843 temperature sensor event_polarity enumeration
 */
typedef enum
{
    MCP9843_ACTIVE_HIGH=MCP9843_EVENT_POLARITY_BIT_1,				/*!< MCP9843 active high */
    MCP9843_ACTIVE_LOW=(0x00 & MCP9843_EVENT_POLARITY_BIT_1)		/*!< MCP9843 active low */
}mcp9843_event_polarity_t;
/**
 * @brief MCP9843 temperature sensor win_lock_bit enumeration
 */
typedef enum
{
    MCP9843_WIN_UNLOCK_0=(0X00 & MCP9843_WIN_LOCK_BIT_6),			/*!< MCP9843 win unlock */
    MCP9843_WIN_LOCK_1=MCP9843_WIN_LOCK_BIT_6					    /*!< MCP9843 win lock */
}mcp9843_win_lock_t;

/**
 * @brief MCP9843 temperature sensor crit_lock_bit enumeration
 */
typedef enum
{
    MCP9843_CRIT_UNLOCK_0=(0X00 & MCP9843_CRIT_LOCK_BIT_7),			/*!< MCP9843 critical unlock */
    MCP9843_CRIT_LOCK_1=MCP9843_CRIT_LOCK_BIT_7						/*!< MCP9843 critical lock */
}mcp9843_crit_lock_t;
/**
 * @brief MCP9843 temperature sensor alarm_alert enumeration
 */
typedef enum
{
    MCP9843_TEMP_BOUNDARY_LIMIT_DEFAULT=0,								/*!< MCP9843 temperature boundary limit default */
    MCP9843_TEMP_BOUNDARY_LIMIT_ALARM=MCP9843_TEMP_ALARM_ALERT      	/*!< MCP9843 temperature boundary limit alarm */
}mcp9843_alarm_alert_t;
/**
 * @brief MCP9843 temperature sensor device structure.
 */
typedef struct
{
    uint8_t interrupt_clear;					/*!< intrupt_clear					*/
    void  *io_intf_hdle;						/*!< interface handle				*/
    uint8_t slave_address;					/*!< slave_address					*/
    uint16_t device_id;						/*!< device_id						*/
    uint16_t manufacture_id;					/*!<manufacture_id					*/
    float high_temp_threshold;				/*!<high_temp_threshold				*/
    float low_temp_threshold;					/*!<low_temp_threshold				*/
    float critical_temp_threshold;			/*!<critical_temp_threshold			*/
    mcp9843_mode_t mode;						/*!<mcp9843 mode of operation		*/
    mcp9843_event_output_mode_t event_mode;	/*!<event pin mode of operation		*/
    mcp9843_event_polarity_t polarity;		/*!<event polarity					*/
    mcp9843_win_lock_t win_lock;				/*!<window lock bit enumeration		*/
    mcp9843_crit_lock_t crit_lock;			/*!<window lock bit enumeration		*/
    mcp9843_hyst_t hysteresis;				/*!<hysteresis enumeration			*/
    mcp9843_alarm_alert_t alarm_alert;		/*!<alarm_alert enumeration			*/
    mcp9843_res_t resolution;					/*!<resolution enumeration			*/
    mcp9843_read_fptr_t read;					/*!<read function pointer			*/
    mcp9843_write_fptr_t write;				/*!<write function pointer			*/

} mcp9843_dev_t;

/**
 * @brief MCP9843_temp_sensorpointer type definition
 */
typedef mcp9843_dev_t *mcp9843_dev_ptr_t;

/**
 * @brief Write access to MCP9843 register
 * @param[in] mcp9843_hdl: structure handle MCP9843 temperature sensor
 * @param[in] reg 		: Register address from where the data to be read.
 * @param[in] data		: data value to write.
 * @retval e_temp_sensor_sts - returns the success or error code
 */
e_temp_sensor_sts mcp9843_writereg(mcp9843_dev_ptr_t mcp9843_hdl, uint8_t reg, int16_t data);

/**
 * @brief read access to MCP9843 register
 * @param[in] mcp9843_hdl: structure handle MCP9843 temperature sensor
 * @param[in] reg 		: Register address from where the data to be read.
 * @param[out] data		: data value to write.
 * @retval e_temp_sensor_sts - returns the success or error code
 */
e_temp_sensor_sts mcp9843_readreg(mcp9843_dev_ptr_t mcp9843_hdl, uint8_t reg,int16_t* data);

/**
 * @brief Initialize the MCP9843 and configure.
 * @param[in,out] MCP9843_hdl : structure handle of temperature sensor MCP9843.
 * @retval e_ina230_sts - returns the success or error code
 */
e_temp_sensor_sts mcp9843_init(mcp9843_dev_ptr_t mcp9843_hdl);

/**
 * @brief De-Initialize the MCP9843 and configure.
 * @param[in] MCP9843_hdl : structure handle of temperature sensor MCP9843.
 * @retval e_ina230_sts - returns the success or error code
 */
e_temp_sensor_sts mcp9843_deinit(mcp9843_dev_ptr_t mcp9843_hdl);

/**
 * @brief MCP9843 device configure.
 * @param[in] MCP9843_hdl : structure handle of temperature sensor MCP9843.
 * @retval e_ina230_sts - returns the success or error code
 */
e_temp_sensor_sts mcp9843_config (mcp9843_dev_ptr_t mcp9843_hdl);

/**
 * @brief MCP9843 event status is received
 * @param[in] MCP9843_hdl : structure handle of temperature sensor MCP9843.
 * @param[out] evnt_sts   : event status
 * @retval e_ina230_sts - returns the success or error code
 */
e_temp_sensor_sts mcp9843_get_event_sts (mcp9843_dev_ptr_t mcp9843_hdl, uint8_t* evnt_sts);

/**
 * @brief Set the mode of operation
 * @param[in] mcp9843_hdl 		: structure handle of temperature sensor MCP9843.
 * @param[in] mode				: mode of operation continuous or shut_down mode.
 * This parameter can be take one of the following values:
 * 		MCP9843_CONTINUOUS_CONVERSTION
 * 		MCP9843_SHUTDOWN_MODE
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_set_mode(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_mode_t mode);

/**
 * @brief clear the interrupt  bit
 * @param[in] mcp9843_hdl 		: structure handle of temperature sensor MCP9843.
 * @param[in] interrupt_clear	: interrupt_clear value.
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_interrupt_clear(mcp9843_dev_ptr_t mcp9843_hdl, uint8_t interrupt_clear);

/**
 * @brief set the event output pin
 * @param[in] mcp9843_hdl 		: structure handle of temperature sensor MCP9843.
 * @param[in] event_mode		: event_mode set value
 * This parameter can be take one of the following values:
 * 		COMPARATOR EVENT MODE
 * 		INTERRUPT EVENT MODE
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_set_event_output_mode(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_event_output_mode_t event_mode);

/**
 * @brief set the alarm alert control
 * @param[in] mcp9843_hdl 		: structure handle of temperature sensor MCP9843.
 * @param[in] on_off			: on/off status
 * This parameter can be take one of the following values:
 * 		ACTIVE HIGH
 * 		ACTIVE LOW
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_temperature_alarm_alert_ctrl(mcp9843_dev_ptr_t mcp9843_hdl, uint8_t on_off);

/**
 * @brief set event polarity
 * @param[in] mcp9843_hdl 				: structure handle of temperature sensor MCP9843.
 * @param[in] polarity					: polarity to be set
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_set_event_polarity(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_event_polarity_t polarity);

/**
 * @brief set the win lock bit
 * @param[in] mcp9843_hdl 		: structure handle of temperature sensor MCP9843.
 * @param[in] win_lock_bit		: win_lock_bit set value
 * This parameter can be take one of the following values:
 * 		WIN_UNLOCK
 * 		WIN_LOCK
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_set_win_lockbit(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_win_lock_t win_lock);

/**
 * @brief set the critical lock bit
 * @param[in] mcp9843_hdl 		: structure handle of temperature sensor MCP9843.
 * @param[in] win_lock_bit		: crit_lock_bit set value
 * This parameter can be take one of the following values:
 * 		CRIT_UNLOCK
 * 		CRIT_LOCK
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_set_crit_lockbit(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_crit_lock_t crit_lock);

/**
 * @brief set the Temperature high threshold
 * @param[in] mcp9843_hdl 				: structure handle of temperature sensor MCP9843.
 * @param[in] high_temp_threshold		: high_temp_threshold set value
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_set_temp_high_threshold (mcp9843_dev_ptr_t mcp9843_hdl, float high_temp_threshold);

/**
 * @brief set the Temperature low threshold
 * @param[in] mcp9843_hdl 				: structure handle of temperature sensor MCP9843.
 * @param[in] low_temp_threshold		: low_temp_threshold set value
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_set_temp_low_threshold (mcp9843_dev_ptr_t mcp9843_hdl, float low_temp_threshold);

/**
 * @brief set the Temperature critical threshold
 * @param[in] mcp9843_hdl 				: structure handle of temperature sensor MCP9843.
 * @param[in] critical_temp_threshold	: low_temp_threshold set value
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_set_temp_critical_threshold (mcp9843_dev_ptr_t mcp9843_hdl, float critical_temp_threshold);

/**
 * @brief Temperature alarm alert
 * @param[in] mcp9843_hdl 				: structure handle of temperature sensor MCP9843.
 * @param[in] alarm						: alarm limit set
 * This parameter can be take one of the following values:
 * 		TEMP_BOUNDARY_LIMIT_DEFAULT
 * 		TEMP_BOUNDARY_LIMIT_ALARM
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_temperature_alarm_alert(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_alarm_alert_t alarm);

/**
 * @brief set the Temperature hysteresis.
 * @param[in] mcp9843_hdl 				: structure handle of temperature sensor MCP9843.
 * @param[in] hysteresis				: hysteresis
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_set_hysteresis(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_hyst_t hysteresis);

/**
 * @brief get the Temperature hysteresis
 * @param[in] mcp9843_hdl 				: structure handle of temperature sensor MCP9843.
 * @param[out] hysteresis				: hysteresis
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_get_hysteresis(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_hyst_t *hysteresis);

/**
 * @brief set the Temperature hysteresis.
 * @param[in] mcp9843_hdl 				: structure handle of temperature sensor MCP9843.
 * @param[in] resolution				: resolution
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_set_resolution(mcp9843_dev_ptr_t mcp9843_hdl, mcp9843_res_t resolution);

/**
 * @brief get the Temperature resolution.
 * @param[in] mcp9843_hdl 		: structure handle of temperature sensor MCP9843.
 * @param[out] res      		: res
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_get_resolution(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_res_t *res);

/**
 * @brief read the Manufacture ID.
 * @param[in] mcp9843_hdl 	: structure handle of temperature sensor MCP9843.
 * @retval uint16_t - read value from MCP9843_MANUFACTURE_ID_REG location
 */
uint16_t mcp9843_read_manufacture_id(mcp9843_dev_ptr_t mcp9843_hdl,int16_t* temperature);

/**
 * @brief get the current Temperature.
 * @param[in] mcp9843_hdl 		: structure handle of temperature sensor MCP9843.
 * @param[out] temp_value 		: temperature value
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_gettemperature(mcp9843_dev_ptr_t mcp9843_hdl,float *temperature);

/**
 * @brief Get the Temperature value in fahrenheit.
 * @param[in] mcp9843_hdl 		: structure handle of temperature sensor MCP9843.
 * @param[out] temp_value 		: temperature value in fahrenheit.
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts mcp9843_get_fahrenheit(mcp9843_dev_ptr_t mcp9843_hdl,float *temp_value);

/**
 * @brief Get the Temperature value in celsius.
 * @param[in] mcp9843_hdl 	: structure handle of temperature sensor MCP9843.
 * @param[out] temp_value 	: temperature value in celsius.
 * @retval e_temp_sensor_sts	:returns the success or error code
 */
e_temp_sensor_sts  mcp9843_get_celsius(mcp9843_dev_ptr_t mcp9843_hdl,float *temp_value);

#endif /* INC_MCP9843_H_ */

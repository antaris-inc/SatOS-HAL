/**
 * @file exo_hal_io_al_common.h
 *
 * @brief This file contains function mapping for IO-AL
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

#ifndef _HAL_IO_AL_COMMON_H_
#define _HAL_IO_AL_COMMON_H_

#include "exo_types.h"

/**
 * @brief This is AHW lookup table function
 */
void ahw_io_lookup_table_updt(void);

/**
 * @brief IO interface type enumeration
 */
typedef enum
{
    UART,				/*!< UART interface */
    I2C,				/*!< I2C interface */
    SPI,				/*!< SPI interface */
    CAN,				/*!< CAN interface */
    USB,				/*!< USB interface */
    QSPI,				/*!< OSPI interface */
    FMC_NOR,			/*!< FMC_NOR interface */
    FMC_SDRAM,			/*!< FMC-SDRAM interface */
    ETHERNET,			/*!< ETHERNET interface */
    MAX_INTF_TYPE
}io_intf_type;

/**
 * @brief IO instance ID enumeration
 */
typedef enum _io_inst_id
{
    INVLD_IO_INST_ID,		/*!< invalid IO interface */
    IOAL_INST_I2C1,			/*!< I2C1 interface */
    IOAL_INST_I2C2,			/*!< I2C2 interface */
    IOAL_INST_I2C3,			/*!< I2C3 interface */
    IOAL_INST_I2C4,			/*!< I2C4 interface */
    IOAL_INST_SPI1,			/*!< SPI1 interface */
    IOAL_INST_SPI2,			/*!< SPI2 interface */
    IOAL_INST_UART1,		/*!< UART1 interface */
    IOAL_INST_UART2,		/*!< UART2 interface */
    IOAL_INST_UART3,		/*!< UART3 interface */
    IOAL_INST_UART4,		/*!< UART4 interface */
    IOAL_INST_UART5,		/*!< UART5 interface */
    IOAL_INST_UART6,		/*!< UART6 interface */
    IOAL_INST_USB_DEVICE,	/*!< USB interface */
    IOAL_INST_CAN1,			/*!< CAN1 interface */
    IOAL_INST_CAN2,			/*!< CAN2 interface */
    IOAL_INST_CAN3,			/*!< CAN3 interface */
    IOAL_INST_ETH,			/*!< ETHERNET interface */
    IOAL_INST_RTC,			/*!< RTC interface */

    MAX_IO_INST_ID
}io_inst_id;

/**
 * @brief AHW instance ID enumeration
 */
typedef enum _ahw_inst_id
{
    INVLD_AH_INST_ID,					/*!< invalid AH instance ID     */
    IMU_BMX160_OBC_1,					/*!< IMU sensor BMX160 in on-board controller */
    IMU_BMX160_OBC_2,					/*!< IMU sensor BMX160 in on-board controller */
    IMU_BMI160,							/*!< IMU sensor BMX160 */
    DT_DS620_EDGE,						/*!< Digital thermostat DS620 in edge board */
    DT_DS620_PS,						/*!< Digital thermostat DS620 in payload server */
    HSC_ADM1176_EDGE,					/*!< Hot swap controller ADM1176 in edge board */
    HSC_ADM1176_PS_2,					/*!< Hot swap controller ADM1176 in payload server */
    HSC_ADM1176_PS_1,					/*!< Hot swap controller ADM1176 in payload server */
    TEMP_SENSOR_MCP9843_OBC,			/*!< Temperature sensor MCP9843 in on-board controller */
    TEMP_SENSOR_MCP9843_PS,				/*!< Temperature sensor MCP9843 in payload server */
    TEMP_SENSOR_MCP9843_EDGE,			/*!< Temperature sensor MCP9843 in edge board */
    TEMP_SENSOR_MCP9843_GPS,			/*!< Temperature sensor MCP9843 in GPS */
    TEMP_SENSOR_MCP9843_SPE01,			/*!< Temperature sensor MCP9843 in solar panel */
    TEMP_SENSOR_MCP9843_SPE02,			/*!< Temperature sensor MCP9843 in solar panel */
    TEMP_SENSOR_MCP9843_SPW01,			/*!< Temperature sensor MCP9843 in solar panel */
    TEMP_SENSOR_MCP9843_SPW02,			/*!< Temperature sensor MCP9843 in solar panel */
    TEMP_SENSOR_MCP9843_SPB01,			/*!< Temperature sensor MCP9843 in solar panel */
    POWER_SENSE_MONITOR_OBC,			/*!< Power sensor INA230 in on-board controller */
    POWER_SENSE_MONITOR_PS,				/*!< Power sensor INA230 in payload server */
    GPIO_EXP_PCAL6408A_PS,				/*!< GPIO Expander PCAL6408A in payload server */
    GPIO_EXP_MCP23008_EDGE_1,			/*!< GPIO Expander MCP23008 in edge board */
    GPIO_EXP_MCP23008_EDGE_2,			/*!< GPIO Expander MCP23008 in edge board */
    GPIO_EXP_MCP23008_GPS,				/*!< GPIO Expander MCP23008 in GPS */
    VSM_UCD9081_OBC,					/*!< Voltage sequence monitor UCD9081 in on-board controller */
    DATA_ACQ_DVC_ADS7828,				/*!< Data logger ADS7828 */
    MAX_AH_INST_ID
}ahw_inst_id_t;

/**
 * @brief AHW type enumeration
 */
typedef enum _ahw_type
{
    INVLD_AHW_TYPE,			/*!< invalid AHW type */
    IMU,					/*!< IMU sensor       */
    TEMP_SENSOR,			/*!< Temperature sensor */
    POWER_SENSE_MONITOR,	/*!< Power sensor monitor */
    GPIO_EXPANDER,			/*!< GPIO expander */
    STAR_CAMERA,			/*!< Star camera */
    DIGI_THERM,				/*!< Digital thermostat */
    HOT_SWP_CNTLR,		    /*!< Hot swap controller */
    VOLTAGE_SEQ_MONITOR,	/*!< Voltage sequencer monitor */
    DATA_ACQ_DVC,			/*!< Data logger */
    GNSS,					/*!< GNSS */
    MAX_AHW_TYPE
}ahw_type;

/**
 * @brief AHW IO map structure definition
 */
typedef struct _ahw_map
{
    io_inst_id io_instance_id;			/*!< IO instance ID structure variable      */
    ahw_inst_id_t ahw_id;				/*!< AHW ID structure variable				*/
    ahw_type ahw_type;					/*!< AHW type structure variable			*/
    uint8 ahw_model_id;					/*!< AHW model ID 							*/
    uint16 slv_addr;					/*!< slave address							*/
}ahw_io_map;

#endif /* _HAL_IO_AL_COMMON_H_ */

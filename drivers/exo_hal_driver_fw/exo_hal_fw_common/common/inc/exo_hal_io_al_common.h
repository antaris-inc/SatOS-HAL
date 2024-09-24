/**
 * @file exo_hal_io_al_common.h
 *
 * @brief This file contains function mapping for IO-AL
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
    UART,               ///< UART interface
    I2C,                ///< I2C interface
    SPI,                ///< SPI interface
    CAN,                ///< CAN interface
    USB,                ///< USB interface
    QSPI,               ///< OSPI interface
    FMC_NOR,            ///< FMC_NOR interface
    FMC_SDRAM,          ///< FMC-SDRAM interface
    ETHERNET,           ///< ETHERNET interface
    MAX_INTF_TYPE
}io_intf_type;

/**
 * @brief Enumeration for IO instance IDs.
 */
typedef enum _io_inst_id
{
    INVLD_IO_INST_ID,       ///< Invalid IO interface identifier
    IOAL_INST_I2C1,         ///< I2C interface 1
    IOAL_INST_I2C2,         ///< I2C interface 2
    IOAL_INST_I2C3,         ///< I2C interface 3
    IOAL_INST_I2C4,         ///< I2C interface 4
    IOAL_INST_SPI1,         ///< SPI interface 1
    IOAL_INST_SPI2,         ///< SPI interface 2
    IOAL_INST_UART1,        ///< UART interface 1
    IOAL_INST_UART2,        ///< UART interface 2
    IOAL_INST_UART3,        ///< UART interface 3
    IOAL_INST_UART4,        ///< UART interface 4
    IOAL_INST_UART5,        ///< UART interface 5
    IOAL_INST_UART6,        ///< UART interface 6
    IOAL_INST_USB1,         ///< USB interface 1
    IOAL_INST_CAN1,         ///< CAN interface 1
    IOAL_INST_CAN2,         ///< CAN interface 2
    IOAL_INST_CAN3,         ///< CAN interface 3
    IOAL_INST_ETHERNET1,    ///< Ethernet interface 1
    IOAL_INST_RTC1,         ///< RTC interface 1
    IOAL_INST_QSPI1,        ///< QSPI interface 1
    IOAL_INST_FMC_NOR1,     ///< FMC NOR interface 1
    IOAL_INST_GPIO,         ///< GPIO interface
    IOAL_INST_CRC,          ///< CRC interface
    IOAL_INST_ADC1,         ///< ADC interface 1
    MAX_IO_INST_ID          ///< Maximum IO instance identifier (used for boundary checks)
} io_inst_id;

/**
 * @brief AHW instance ID enumeration
 */
typedef enum _ahw_inst_id
{
    INVLD_AH_INST_ID,                    ///< Invalid AH instance ID
    MCU_ID,                              ///< MCU instance ID
    IMU_BMX160_OBC_1,                    ///< IMU BMX160 OBC 1 instance ID
    IMU_BMX160_OBC_2,                    ///< IMU BMX160 OBC 2 instance ID
    IMU_BMX160_XXX,                      ///< IMU BMX160 XXX instance ID
    DIGITAL_THERMOSTAT_DS620_EDGE,       ///< Digital thermostat DS620 EDGE instance ID
    DIGITAL_THERMOSTAT_DS620_PS,         ///< Digital thermostat DS620 PS instance ID
    HSC_ADM1176_EDGE,                    ///< HSC ADM1176 EDGE instance ID
    HSC_ADM1176_PS_2,                    ///< HSC ADM1176 PS 2 instance ID
    HSC_ADM1176_PS_1,                    ///< HSC ADM1176 PS 1 instance ID
    TEMP_SENSOR_MCP9843_OBC,             ///< Temperature sensor MCP9843 OBC instance ID
    TEMP_SENSOR_MCP9843_PS,              ///< Temperature sensor MCP9843 PS instance ID
    TEMP_SENSOR_MCP9843_EDGE,            ///< Temperature sensor MCP9843 EDGE instance ID
    TEMP_SENSOR_MCP9843_GPS,             ///< Temperature sensor MCP9843 GPS instance ID
    DIGITAL_THERMOSTAT_DS620_SPE01,      ///< Digital thermostat DS620 SPE01 instance ID
    DIGITAL_THERMOSTAT_DS620_SPE02,      ///< Digital thermostat DS620 SPE02 instance ID
    DIGITAL_THERMOSTAT_DS620_SPW01,      ///< Digital thermostat DS620 SPW01 instance ID
    DIGITAL_THERMOSTAT_DS620_SPW02,      ///< Digital thermostat DS620 SPW02 instance ID
    DIGITAL_THERMOSTAT_DS620_SPB01,      ///< Digital thermostat DS620 SPB01 instance ID
    PSM_INA230_OBC,                      ///< PSM INA230 OBC instance ID
    PSM_INA230_PS,                       ///< PSM INA230 PS instance ID
    GPIO_EXPANDER_PCAL6408A_PS,          ///< GPIO Expander PCAL6408A PS instance ID
    GPIO_EXPANDER_MCP23008_EDGE_1,       ///< GPIO Expander MCP23008 EDGE 1 instance ID
    GPIO_EXPANDER_MCP23008_EDGE_2,       ///< GPIO Expander MCP23008 EDGE 2 instance ID
    GPIO_EXPANDER_MCP23008_OBC_1,        ///< GPIO Expander MCP23008 OBC 1 instance ID
    GPIO_EXPANDER_MCP23008_OBC_2,        ///< GPIO Expander MCP23008 OBC 2 instance ID
    GPIO_EXPANDER_MCP23008_GPS,          ///< GPIO Expander MCP23008 GPS instance ID
    GPIO_EXPANDER_PCA9673,               ///< GPIO Expander PCA9673 instance ID
    THRUSTER_MORPHEUS_OBC,               ///< Thruster Morpheus OBC instance ID
    VOLTAGE_SEQUENCER_UCD9801_OBC,       ///< Voltage Sequencer UCD9801 OBC instance ID
    DATA_LOGGER_ADS7828_PS,              ///< Data Logger ADS7828 PS instance ID
    EXT_MEM_MX25L512_QSPI,               ///< External Memory MX25L512 QSPI instance ID
    EXT_MEM_MT25QL512_QSPI,              ///< External Memory MT25QL512 QSPI instance ID
    EXT_MEM_S25HL512T_QSPI,              ///< External Memory S25HL512T QSPI instance ID
    EXT_MEM_MT28EW128_FMC,               ///< External Memory MT28EW128 FMC instance ID
    UART_EXPANDER_MAX14830_OBC,          ///< UART Expander MAX14830 OBC instance ID
    MAX_AH_INST_ID                       ///< Maximum AH instance ID marker
} ahw_inst_id_t;

/**
 * @brief AHW type enumeration
 */
typedef enum _ahw_type
{
    INVLD_AHW_TYPE,         ///< invalid AHW type
    IMU,                    ///< IMU sensor
    TEMP_SENSOR,            ///< Temperature sensor
    POWER_SENSE_MONITOR,    ///< Power sensor monitor
    GPIO_EXPANDER,          ///< GPIO expander
    STAR_CAMERA,            ///< Star camera
    DIGI_THERM,             ///< Digital thermostat
    HOT_SWP_CNTLR,          ///< Hot swap controller
    THRUSTER,       ///< Thruster sensor
    VOLTAGE_SEQ_MONITOR,    ///< Voltage sequencer monitor
    DATA_ACQ_DVC,           ///< Data logger
    GNSS,                   ///< GNSS
    EXT_FLASH_MEMORY,       ///< External flash memories memories
    UART_EXPANDER,
    MAX_AHW_TYPE
}ahw_type;


/**
 * @brief AHW IO map structure definition
 */
typedef struct _ahw_map
{
    io_inst_id io_instance_id;          /*!< IO instance ID structure variable      */
    ahw_inst_id_t ahw_id;               /*!< AHW ID structure variable              */
    ahw_type ahw_type;                  /*!< AHW type structure variable            */
    uint8 ahw_model_id;                 /*!< AHW model ID                           */
    uint16 slv_addr;                    /*!< slave address                          */
}ahw_io_map;

#endif /* _HAL_IO_AL_COMMON_H_ */

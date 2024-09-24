/*
 * @file io_look_up_table.c
 *
 * @brief This file contains instance creation for AHAL
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

#include "exo_hal_io_al_common.h"

ahw_io_map imu_bmx160_obc_1; ///< IMU BMX160 for OBC 1
ahw_io_map imu_bmx160_obc_2;  ///< IMU BMX160 for OBC 2
ahw_io_map temp_sensor_mcp9843_obc; ///< Temperature sensor MCP9843 for OBC
ahw_io_map temp_sensor_mcp9843_ps; ///< Temperature sensor MCP9843 for Payload Server
ahw_io_map temp_sensor_mcp9843_edge; ///< Temperature sensor MCP9843 for EDGE
ahw_io_map temp_sensor_mcp9843_gps; ///< Temperature sensor MCP9843 for GPS
ahw_io_map psm_ina230_obc; ///< Power Supply Monitor INA230 for OBC
ahw_io_map psm_ina230_ps; ///< Power Supply Monitor INA230 for Payload Server
ahw_io_map psm_ina230_ps_2; ///< Power Supply Monitor INA230 for Payload Server (2)
ahw_io_map gpio_expander_pcal6408a_ps; ///< GPIO Expander PCAL6408A for Payload Server
ahw_io_map gpio_expander_mcp23008_edge_1; ///< GPIO Expander MCP23008 for EDGE 1
ahw_io_map gpio_expander_mcp23008_edge_2; ///< GPIO Expander MCP23008 for EDGE 2
ahw_io_map gpio_expander_mcp23008_gps; ///< GPIO Expander MCP23008 for GPS
ahw_io_map gpio_expander_mcp23008_obc_1; ///< GPIO Expander MCP23008 for OBC 1
ahw_io_map gpio_expander_mcp23008_obc_2; ///< GPIO Expander MCP23008 for OBC 2
ahw_io_map digital_thermostat_ds620_ps; ///< Digital Thermostat DS620 for Payload Server
ahw_io_map digital_thermostat_ds620_edge; ///< Digital Thermostat DS620 for EDGE
ahw_io_map hsc_adm1176_edge; ///< HSC ADM1176 for EDGE
ahw_io_map hsc_adm1176_ps_1; ///< HSC ADM1176 for Payload Server 1
ahw_io_map hsc_adm1176_ps_2; ///< HSC ADM1176 for Payload Server 2
ahw_io_map thruster_morpheus_obc; ///< Thruster Morpheus for OBC
ahw_io_map voltage_sequencer_ucd9801_obc; ///< Voltage Sequencer UCD9801 for OBC
ahw_io_map data_logger_ads7828_ps; ///< Data Logger ADS7828 for Payload Server
ahw_io_map digital_thermostat_ds620_spe01; ///< Digital Thermostat DS620 for SPE01
ahw_io_map digital_thermostat_ds620_spe02; ///< Digital Thermostat DS620 for SPE02
ahw_io_map digital_thermostat_ds620_spw01; ///< Digital Thermostat DS620 for SPW01
ahw_io_map digital_thermostat_ds620_spw02; ///<  Digital Thermostat DS620 for SPW02
ahw_io_map digital_thermostat_ds620_spb01; ///< Digital Thermostat DS620 for SPB01
ahw_io_map ext_mem_mx25l512_qspi; ///< External Memory MX25L512 for QSPI
ahw_io_map ext_mem_mt25ql512_qspi; ///< External Memory MT25QL512 for QSPI
ahw_io_map ext_mem_mt28ew128_fmc; ///< External Memory MT28EW128 for FMC
ahw_io_map uart_expander_max14830_obc; ///< UART Expander MAX14830 for OBC

ahw_io_map *ahw_io_lookup_tble[MAX_AH_INST_ID]; ///< IO lookup table pointer buffer
void *intf_inst_hdle_ptr[MAX_IO_INST_ID];   ///< Iinterface instance handle pointer

/**
 * @brief This API is AHW IO lookup table
 */
void ahw_io_lookup_table_updt(void)
{
    ahw_io_lookup_tble[IMU_BMX160_OBC_1] = &imu_bmx160_obc_1;
    ahw_io_lookup_tble[IMU_BMX160_OBC_2] = &imu_bmx160_obc_2;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_OBC] = &temp_sensor_mcp9843_obc;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_PS] = &temp_sensor_mcp9843_ps;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_EDGE] = &temp_sensor_mcp9843_edge;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_GPS] = &temp_sensor_mcp9843_gps;
    ahw_io_lookup_tble[PSM_INA230_OBC] = &psm_ina230_obc;
    ahw_io_lookup_tble[PSM_INA230_PS] = &psm_ina230_ps;
    ahw_io_lookup_tble[GPIO_EXPANDER_PCAL6408A_PS] = &gpio_expander_pcal6408a_ps;
    ahw_io_lookup_tble[GPIO_EXPANDER_MCP23008_EDGE_1] = &gpio_expander_mcp23008_edge_1;
    ahw_io_lookup_tble[GPIO_EXPANDER_MCP23008_EDGE_2] = &gpio_expander_mcp23008_edge_2;
    ahw_io_lookup_tble[GPIO_EXPANDER_MCP23008_GPS] = &gpio_expander_mcp23008_gps;
    ahw_io_lookup_tble[GPIO_EXPANDER_MCP23008_OBC_1] = &gpio_expander_mcp23008_obc_1;
    ahw_io_lookup_tble[GPIO_EXPANDER_MCP23008_OBC_2] = &gpio_expander_mcp23008_obc_2;
    ahw_io_lookup_tble[DIGITAL_THERMOSTAT_DS620_PS] = &digital_thermostat_ds620_ps;
    ahw_io_lookup_tble[DIGITAL_THERMOSTAT_DS620_EDGE] = &digital_thermostat_ds620_edge;
    ahw_io_lookup_tble[HSC_ADM1176_EDGE] = &hsc_adm1176_edge;
    ahw_io_lookup_tble[HSC_ADM1176_PS_1] = &hsc_adm1176_ps_1;
    ahw_io_lookup_tble[HSC_ADM1176_PS_2] = &hsc_adm1176_ps_2;
    ahw_io_lookup_tble[THRUSTER_MORPHEUS_OBC] = &thruster_morpheus_obc;
    ahw_io_lookup_tble[VOLTAGE_SEQUENCER_UCD9801_OBC] = &voltage_sequencer_ucd9801_obc;
    ahw_io_lookup_tble[DATA_LOGGER_ADS7828_PS] = &data_logger_ads7828_ps;
    ahw_io_lookup_tble[DIGITAL_THERMOSTAT_DS620_SPE01] = &digital_thermostat_ds620_spe01;
    ahw_io_lookup_tble[DIGITAL_THERMOSTAT_DS620_SPE02] = &digital_thermostat_ds620_spe02;
    ahw_io_lookup_tble[DIGITAL_THERMOSTAT_DS620_SPW01] = &digital_thermostat_ds620_spw01;
    ahw_io_lookup_tble[DIGITAL_THERMOSTAT_DS620_SPW02] = &digital_thermostat_ds620_spw02;
    ahw_io_lookup_tble[DIGITAL_THERMOSTAT_DS620_SPB01] = &digital_thermostat_ds620_spb01;
    ahw_io_lookup_tble[EXT_MEM_MX25L512_QSPI] = &ext_mem_mx25l512_qspi;
    ahw_io_lookup_tble[EXT_MEM_MT25QL512_QSPI] = &ext_mem_mt25ql512_qspi;
    ahw_io_lookup_tble[EXT_MEM_MT28EW128_FMC] = &ext_mem_mt28ew128_fmc;
    ahw_io_lookup_tble[UART_EXPANDER_MAX14830_OBC] = &uart_expander_max14830_obc;

    /***COREBOARD  SENSORS CONFIGURATION***/

    voltage_sequencer_ucd9801_obc.ahw_id = VOLTAGE_SEQUENCER_UCD9801_OBC;
    voltage_sequencer_ucd9801_obc.ahw_type = VOLTAGE_SEQ_MONITOR;
    voltage_sequencer_ucd9801_obc.io_instance_id = IOAL_INST_I2C1;
    voltage_sequencer_ucd9801_obc.slv_addr = (0x6E<<1);

    temp_sensor_mcp9843_obc.ahw_id = TEMP_SENSOR_MCP9843_OBC;
    temp_sensor_mcp9843_obc.ahw_type = TEMP_SENSOR;
    temp_sensor_mcp9843_obc.io_instance_id = IOAL_INST_I2C4;
    temp_sensor_mcp9843_obc.slv_addr = 0x36;

    psm_ina230_obc.ahw_id = PSM_INA230_OBC;
    psm_ina230_obc.ahw_type = POWER_SENSE_MONITOR;
    psm_ina230_obc.io_instance_id = IOAL_INST_I2C4;
    psm_ina230_obc.slv_addr = 0x84;

    gpio_expander_mcp23008_obc_1.ahw_id = GPIO_EXPANDER_MCP23008_OBC_1;
    gpio_expander_mcp23008_obc_1.ahw_type = GPIO_EXPANDER;
    gpio_expander_mcp23008_obc_1.io_instance_id = IOAL_INST_I2C1;
    gpio_expander_mcp23008_obc_1.slv_addr = 0x40;

    gpio_expander_mcp23008_obc_2.ahw_id = GPIO_EXPANDER_MCP23008_OBC_2;
    gpio_expander_mcp23008_obc_2.ahw_type = GPIO_EXPANDER;
    gpio_expander_mcp23008_obc_2.io_instance_id = IOAL_INST_I2C1;
    gpio_expander_mcp23008_obc_2.slv_addr = 0x4E;

    /***PAYLOAD SERVER  SENSORS CONFIGURATION***/

    psm_ina230_ps.ahw_id = PSM_INA230_PS;
    psm_ina230_ps.ahw_type = POWER_SENSE_MONITOR;
    psm_ina230_ps.io_instance_id = IOAL_INST_I2C4;
    psm_ina230_ps.slv_addr = 0x82;

    temp_sensor_mcp9843_ps.ahw_id = TEMP_SENSOR_MCP9843_PS;
    temp_sensor_mcp9843_ps.ahw_type = TEMP_SENSOR;
    temp_sensor_mcp9843_ps.io_instance_id = IOAL_INST_I2C4;
    temp_sensor_mcp9843_ps.slv_addr = 0x32;

    gpio_expander_pcal6408a_ps.ahw_id = GPIO_EXPANDER_PCAL6408A_PS;
    gpio_expander_pcal6408a_ps.ahw_type = GPIO_EXPANDER;
    gpio_expander_pcal6408a_ps.io_instance_id = IOAL_INST_I2C4;
    gpio_expander_pcal6408a_ps.slv_addr = 0x42;

    digital_thermostat_ds620_ps.ahw_id = DIGITAL_THERMOSTAT_DS620_PS;
    digital_thermostat_ds620_ps.ahw_type = DIGI_THERM;
    digital_thermostat_ds620_ps.io_instance_id = IOAL_INST_I2C4;
    digital_thermostat_ds620_ps.slv_addr = 0x90;

    hsc_adm1176_ps_1.ahw_id = HSC_ADM1176_PS_1;
    hsc_adm1176_ps_1.ahw_type = HOT_SWP_CNTLR;
    hsc_adm1176_ps_1.io_instance_id = IOAL_INST_I2C4;
    hsc_adm1176_ps_1.slv_addr = 0x80;

    hsc_adm1176_ps_2.ahw_id = HSC_ADM1176_PS_2;
    hsc_adm1176_ps_2.ahw_type = HOT_SWP_CNTLR;
    hsc_adm1176_ps_2.io_instance_id = IOAL_INST_I2C4;
    hsc_adm1176_ps_2.slv_addr = 0x8A;
    /***EDGE SERVER SENSORS CONFIGURATION***/

    gpio_expander_mcp23008_edge_1.ahw_id = GPIO_EXPANDER_MCP23008_EDGE_1;
    gpio_expander_mcp23008_edge_1.ahw_type = GPIO_EXPANDER;
    gpio_expander_mcp23008_edge_1.io_instance_id = IOAL_INST_I2C1;
    gpio_expander_mcp23008_edge_1.slv_addr = 0x46;

    gpio_expander_mcp23008_edge_2.ahw_id = GPIO_EXPANDER_MCP23008_EDGE_2;
    gpio_expander_mcp23008_edge_2.ahw_type = GPIO_EXPANDER;
    gpio_expander_mcp23008_edge_2.io_instance_id = IOAL_INST_I2C1;
    gpio_expander_mcp23008_edge_2.slv_addr = 0x42;

    digital_thermostat_ds620_edge.ahw_id = DIGITAL_THERMOSTAT_DS620_EDGE;
    digital_thermostat_ds620_edge.ahw_type = DIGI_THERM;
    digital_thermostat_ds620_edge.io_instance_id = IOAL_INST_I2C1;
    digital_thermostat_ds620_edge.slv_addr = 0x98;

    hsc_adm1176_edge.ahw_id = HSC_ADM1176_EDGE;
    hsc_adm1176_edge.ahw_type = HOT_SWP_CNTLR;
    hsc_adm1176_edge.io_instance_id = IOAL_INST_I2C1;
    hsc_adm1176_edge.slv_addr = 0x8A;

    temp_sensor_mcp9843_edge.ahw_id = TEMP_SENSOR_MCP9843_EDGE;
    temp_sensor_mcp9843_edge.ahw_type = TEMP_SENSOR;
    temp_sensor_mcp9843_edge.io_instance_id = IOAL_INST_I2C1;
    temp_sensor_mcp9843_edge.slv_addr = 0x3A;

    /***GPS BOARD SENSORS CONFIGURATION ***/

    temp_sensor_mcp9843_gps.ahw_id = TEMP_SENSOR_MCP9843_GPS;
    temp_sensor_mcp9843_gps.ahw_type = TEMP_SENSOR;
    temp_sensor_mcp9843_gps.io_instance_id = IOAL_INST_I2C4;
    temp_sensor_mcp9843_gps.slv_addr = 0x30;

    gpio_expander_mcp23008_gps.ahw_id = GPIO_EXPANDER_MCP23008_GPS;
    gpio_expander_mcp23008_gps.ahw_type = GPIO_EXPANDER;
    gpio_expander_mcp23008_gps.io_instance_id = IOAL_INST_I2C4;
    gpio_expander_mcp23008_gps.slv_addr = 0x4E;

    /***Thurster sensor configuration***/

    thruster_morpheus_obc.ahw_id = THRUSTER_MORPHEUS_OBC;
    thruster_morpheus_obc.ahw_type = THRUSTER;
    thruster_morpheus_obc.io_instance_id = IOAL_INST_I2C1;
    thruster_morpheus_obc.slv_addr = 0x52;

    data_logger_ads7828_ps.ahw_id = DATA_LOGGER_ADS7828_PS;
    data_logger_ads7828_ps.ahw_type = DATA_ACQ_DVC;
    data_logger_ads7828_ps.io_instance_id = IOAL_INST_I2C1;
    data_logger_ads7828_ps.slv_addr = 0x02;

    /***HRM***/

    digital_thermostat_ds620_spe01.ahw_id = DIGITAL_THERMOSTAT_DS620_SPE01;
    digital_thermostat_ds620_spe01.ahw_type = TEMP_SENSOR;
    digital_thermostat_ds620_spe01.io_instance_id = IOAL_INST_I2C3;
    digital_thermostat_ds620_spe01.slv_addr = 0x90;

    digital_thermostat_ds620_spe02.ahw_id = DIGITAL_THERMOSTAT_DS620_SPE02;
    digital_thermostat_ds620_spe02.ahw_type = TEMP_SENSOR;
    digital_thermostat_ds620_spe02.io_instance_id = IOAL_INST_I2C3;
    digital_thermostat_ds620_spe02.slv_addr = 0x92;

    digital_thermostat_ds620_spb01.ahw_id = DIGITAL_THERMOSTAT_DS620_SPB01;
    digital_thermostat_ds620_spb01.ahw_type = TEMP_SENSOR;
    digital_thermostat_ds620_spb01.io_instance_id = IOAL_INST_I2C3;
    digital_thermostat_ds620_spb01.slv_addr = 0x98;

    digital_thermostat_ds620_spw01.ahw_id = DIGITAL_THERMOSTAT_DS620_SPW01;
    digital_thermostat_ds620_spw01.ahw_type = TEMP_SENSOR;
    digital_thermostat_ds620_spw01.io_instance_id = IOAL_INST_I2C3;
    digital_thermostat_ds620_spw01.slv_addr = 0x94;

    digital_thermostat_ds620_spw02.ahw_id = DIGITAL_THERMOSTAT_DS620_SPW02;
    digital_thermostat_ds620_spw02.ahw_type = TEMP_SENSOR;
    digital_thermostat_ds620_spw02.io_instance_id = IOAL_INST_I2C3;
    digital_thermostat_ds620_spw02.slv_addr = 0x96;

    /** External Memory **/
    // NOR flash MX25l512 with qspi interface
    ext_mem_mx25l512_qspi.ahw_id = EXT_MEM_MX25L512_QSPI;
    ext_mem_mx25l512_qspi.ahw_type = EXT_FLASH_MEMORY;
    ext_mem_mx25l512_qspi.io_instance_id = IOAL_INST_QSPI1;

    // NOR flash MT25QL512 with qspi interface
    ext_mem_mt25ql512_qspi.ahw_id = EXT_MEM_MT25QL512_QSPI;
    ext_mem_mt25ql512_qspi.ahw_type = EXT_FLASH_MEMORY;
    ext_mem_mt25ql512_qspi.io_instance_id = IOAL_INST_QSPI1;

    ext_mem_mt28ew128_fmc.ahw_id = EXT_MEM_MT28EW128_FMC;
    ext_mem_mt28ew128_fmc.ahw_type = EXT_FLASH_MEMORY;
    ext_mem_mt28ew128_fmc.io_instance_id = IOAL_INST_FMC_NOR1;

    uart_expander_max14830_obc.ahw_id = UART_EXPANDER_MAX14830_OBC;
    uart_expander_max14830_obc.ahw_type = UART_EXPANDER;
    uart_expander_max14830_obc.io_instance_id = IOAL_INST_SPI1;
    //uart_expander_max14830_obc.slv_addr = 0x00;

}

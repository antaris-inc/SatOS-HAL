/**
 * @file exo_ahw_io_look_up_table.c
 *
 * @brief This file contains instance creation for AHAL
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

#include "exo_hal_io_al_common.h"

ahw_io_map imu_bmx160_1;
ahw_io_map imu_bmx160_2;
ahw_io_map temp_sensor_mcp9843_obc;
ahw_io_map temp_sensor_mcp9843_ps;
ahw_io_map temp_sensor_mcp9843_edge;
ahw_io_map temp_sensor_mcp9843_gps;
ahw_io_map power_sense_monitor_obc;
ahw_io_map power_sense_monitor_ps;
ahw_io_map power_sense_monitor_2;
ahw_io_map gpio_exp_pcal6408a_ps;
ahw_io_map gpio_exp_mcp23008_edge_1;
ahw_io_map gpio_exp_mcp23008_edge_2;
ahw_io_map gpio_exp_mcp23008_gps;
ahw_io_map digi_therm_ds620_ps;
ahw_io_map digi_therm_ds620_edge;
ahw_io_map hot_swap_ctlr_edge;
ahw_io_map hot_swap_ctlr_ps_1;
ahw_io_map hot_swap_ctlr_ps_2;
ahw_io_map vsm_ucd9081_obc;
ahw_io_map data_acq_dvc_ads7828;
ahw_io_map hrm_temp_sns_spe01;
ahw_io_map hrm_temp_sns_spe02;
ahw_io_map hrm_temp_sns_spw01;
ahw_io_map hrm_temp_sns_spw02;
ahw_io_map hrm_temp_sns_spb01;



ahw_io_map *ahw_io_lookup_tble[MAX_AH_INST_ID];
void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

/**
 * @brief This API is AHW IO lookup table
 */
void ahw_io_lookup_table_updt(void)
{
    ahw_io_lookup_tble[IMU_BMX160_OBC_1] = &imu_bmx160_1;
    ahw_io_lookup_tble[IMU_BMX160_OBC_2] = &imu_bmx160_2;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_OBC] = &temp_sensor_mcp9843_obc;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_PS] = &temp_sensor_mcp9843_ps;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_EDGE] = &temp_sensor_mcp9843_edge;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_GPS] = &temp_sensor_mcp9843_gps;
    ahw_io_lookup_tble[POWER_SENSE_MONITOR_OBC] = &power_sense_monitor_obc;
    ahw_io_lookup_tble[POWER_SENSE_MONITOR_PS] = &power_sense_monitor_ps;
    ahw_io_lookup_tble[GPIO_EXP_PCAL6408A_PS] = &gpio_exp_pcal6408a_ps;
    ahw_io_lookup_tble[GPIO_EXP_MCP23008_EDGE_1] = &gpio_exp_mcp23008_edge_1;
    ahw_io_lookup_tble[GPIO_EXP_MCP23008_EDGE_2] = &gpio_exp_mcp23008_edge_2;
    ahw_io_lookup_tble[GPIO_EXP_MCP23008_GPS] = &gpio_exp_mcp23008_gps;
    ahw_io_lookup_tble[DT_DS620_PS] = &digi_therm_ds620_ps;
    ahw_io_lookup_tble[DT_DS620_EDGE] = &digi_therm_ds620_edge;
    ahw_io_lookup_tble[HSC_ADM1176_EDGE] = &hot_swap_ctlr_edge;
    ahw_io_lookup_tble[HSC_ADM1176_PS_1] = &hot_swap_ctlr_ps_1;
    ahw_io_lookup_tble[HSC_ADM1176_PS_2] = &hot_swap_ctlr_ps_2;
    ahw_io_lookup_tble[VSM_UCD9081_OBC] = &vsm_ucd9081_obc;
    ahw_io_lookup_tble[DATA_ACQ_DVC_ADS7828] = &data_acq_dvc_ads7828;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_SPE01] = &hrm_temp_sns_spe01;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_SPE02] = &hrm_temp_sns_spe02;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_SPW01] = &hrm_temp_sns_spw01;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_SPW02] = &hrm_temp_sns_spw02;
    ahw_io_lookup_tble[TEMP_SENSOR_MCP9843_SPB01] = &hrm_temp_sns_spb01;


    /***COREBOARD  SENSORS CONFIGURATION***/

    vsm_ucd9081_obc.ahw_id =VSM_UCD9081_OBC;
    vsm_ucd9081_obc.ahw_type =VOLTAGE_SEQ_MONITOR;
    vsm_ucd9081_obc.io_instance_id =IOAL_INST_I2C1;
    vsm_ucd9081_obc.slv_addr =(0x6E<<1);

    imu_bmx160_1.ahw_id = IMU_BMX160_OBC_1;
    imu_bmx160_1.ahw_type = IMU;
    imu_bmx160_1.io_instance_id = IOAL_INST_I2C4;
    imu_bmx160_1.slv_addr =(0x68<<1);

    imu_bmx160_2.ahw_id = IMU_BMX160_OBC_2;
    imu_bmx160_2.ahw_type = IMU;
    imu_bmx160_2.io_instance_id = IOAL_INST_I2C4;
    imu_bmx160_2.slv_addr =(0x69<<1);

    temp_sensor_mcp9843_obc.ahw_id = TEMP_SENSOR_MCP9843_OBC;
    temp_sensor_mcp9843_obc.ahw_type = TEMP_SENSOR;
    temp_sensor_mcp9843_obc.io_instance_id = IOAL_INST_I2C4;
    temp_sensor_mcp9843_obc.slv_addr =0x36;

    power_sense_monitor_obc.ahw_id = POWER_SENSE_MONITOR_OBC;
    power_sense_monitor_obc.ahw_type = POWER_SENSE_MONITOR;
    power_sense_monitor_obc.io_instance_id = IOAL_INST_I2C4;
    power_sense_monitor_obc.slv_addr =0x84;

    /***PAYLOAD SERVER  SENSORS CONFIGURATION***/

    power_sense_monitor_ps.ahw_id = POWER_SENSE_MONITOR_PS;
    power_sense_monitor_ps.ahw_type = POWER_SENSE_MONITOR;
    power_sense_monitor_ps.io_instance_id = IOAL_INST_I2C4;
    power_sense_monitor_ps.slv_addr =0x82;

    temp_sensor_mcp9843_ps.ahw_id = TEMP_SENSOR_MCP9843_PS;
    temp_sensor_mcp9843_ps.ahw_type = TEMP_SENSOR;
    temp_sensor_mcp9843_ps.io_instance_id = IOAL_INST_I2C4;
    temp_sensor_mcp9843_ps.slv_addr =0x32;

    gpio_exp_pcal6408a_ps.ahw_id = GPIO_EXP_PCAL6408A_PS;
    gpio_exp_pcal6408a_ps.ahw_type = GPIO_EXPANDER;
    gpio_exp_pcal6408a_ps.io_instance_id = IOAL_INST_I2C4;
    gpio_exp_pcal6408a_ps.slv_addr=0x42;

    digi_therm_ds620_ps.ahw_id =DT_DS620_PS;
    digi_therm_ds620_ps.ahw_type =DIGI_THERM;
    digi_therm_ds620_ps.io_instance_id =IOAL_INST_I2C4;
    digi_therm_ds620_ps.slv_addr =0x90;

    hot_swap_ctlr_ps_1.ahw_id =HSC_ADM1176_PS_1;
    hot_swap_ctlr_ps_1.ahw_type =HOT_SWP_CNTLR;
    hot_swap_ctlr_ps_1.io_instance_id =IOAL_INST_I2C4;
    hot_swap_ctlr_ps_1.slv_addr =0x80;

    hot_swap_ctlr_ps_2.ahw_id =HSC_ADM1176_PS_2;
    hot_swap_ctlr_ps_2.ahw_type =HOT_SWP_CNTLR;
    hot_swap_ctlr_ps_2.io_instance_id =IOAL_INST_I2C4;
    hot_swap_ctlr_ps_2.slv_addr =0x8A;

    /***EDGE SERVER SENSORS CONFIGURATION***/

    gpio_exp_mcp23008_edge_1.ahw_id = GPIO_EXP_MCP23008_EDGE_1;
    gpio_exp_mcp23008_edge_1.ahw_type = GPIO_EXPANDER;
    gpio_exp_mcp23008_edge_1.io_instance_id = IOAL_INST_I2C1;
    gpio_exp_mcp23008_edge_1.slv_addr = 0x46;

    gpio_exp_mcp23008_edge_2.ahw_id = GPIO_EXP_MCP23008_EDGE_2;
    gpio_exp_mcp23008_edge_2.ahw_type = GPIO_EXPANDER;
    gpio_exp_mcp23008_edge_2.io_instance_id = IOAL_INST_I2C1;
    gpio_exp_mcp23008_edge_2.slv_addr = 0x42;

    digi_therm_ds620_edge.ahw_id =DT_DS620_EDGE;
    digi_therm_ds620_edge.ahw_type =DIGI_THERM;
    digi_therm_ds620_edge.io_instance_id =IOAL_INST_I2C1;
    digi_therm_ds620_edge.slv_addr =0x98;

    hot_swap_ctlr_edge.ahw_id =HSC_ADM1176_EDGE;
    hot_swap_ctlr_edge.ahw_type =HOT_SWP_CNTLR;
    hot_swap_ctlr_edge.io_instance_id =IOAL_INST_I2C1;
    hot_swap_ctlr_edge.slv_addr = 0x8A;

    temp_sensor_mcp9843_edge.ahw_id = TEMP_SENSOR_MCP9843_EDGE;
    temp_sensor_mcp9843_edge.ahw_type = TEMP_SENSOR;
    temp_sensor_mcp9843_edge.io_instance_id = IOAL_INST_I2C1;
    temp_sensor_mcp9843_edge.slv_addr =0x3A;

    /***GPS BOARD SENSORS CONFIGURATION ***/

    temp_sensor_mcp9843_gps.ahw_id = TEMP_SENSOR_MCP9843_GPS;
    temp_sensor_mcp9843_gps.ahw_type = TEMP_SENSOR;
    temp_sensor_mcp9843_gps.io_instance_id = IOAL_INST_I2C4;
    temp_sensor_mcp9843_gps.slv_addr =0x30;

    gpio_exp_mcp23008_gps.ahw_id = GPIO_EXP_MCP23008_GPS;
    gpio_exp_mcp23008_gps.ahw_type = GPIO_EXPANDER;
    gpio_exp_mcp23008_gps.io_instance_id = IOAL_INST_I2C4;
    gpio_exp_mcp23008_gps.slv_addr = 0x4E;

    /***Thurster sensor configuration***/

    data_acq_dvc_ads7828.ahw_id =DATA_ACQ_DVC_ADS7828;
    data_acq_dvc_ads7828.ahw_type =DATA_ACQ_DVC;
    data_acq_dvc_ads7828.io_instance_id =IOAL_INST_I2C1;
    data_acq_dvc_ads7828.slv_addr =0x02;

    /***HRM***/

    hrm_temp_sns_spe01.ahw_id=TEMP_SENSOR_MCP9843_SPE01;
    hrm_temp_sns_spe01.ahw_type=TEMP_SENSOR;
    hrm_temp_sns_spe01.io_instance_id=IOAL_INST_I2C1;
    hrm_temp_sns_spe01.slv_addr = 0x48<<1;

    hrm_temp_sns_spe02.ahw_id=TEMP_SENSOR_MCP9843_SPE02;
    hrm_temp_sns_spe02.ahw_type=TEMP_SENSOR;
    hrm_temp_sns_spe02.io_instance_id=IOAL_INST_I2C1;
    hrm_temp_sns_spe02.slv_addr = 0x49<<1;

    hrm_temp_sns_spb01.ahw_id=TEMP_SENSOR_MCP9843_SPB01;
    hrm_temp_sns_spb01.ahw_type=TEMP_SENSOR;
    hrm_temp_sns_spb01.io_instance_id=IOAL_INST_I2C1;
    hrm_temp_sns_spb01.slv_addr = 0x4C<<1;

    hrm_temp_sns_spw01.ahw_id=TEMP_SENSOR_MCP9843_SPW01;
    hrm_temp_sns_spw01.ahw_type=TEMP_SENSOR;
    hrm_temp_sns_spw01.io_instance_id=IOAL_INST_I2C1;
    hrm_temp_sns_spw01.slv_addr = 0x4A<<1;

    hrm_temp_sns_spw02.ahw_id=TEMP_SENSOR_MCP9843_SPW02;
    hrm_temp_sns_spw02.ahw_type=TEMP_SENSOR;
    hrm_temp_sns_spw02.io_instance_id=IOAL_INST_I2C1;
    hrm_temp_sns_spw02.slv_addr = 0x4B<<1;
}

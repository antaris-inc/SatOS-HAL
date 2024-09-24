/**
 * @file psm_register_map.h
 *
 *  @brief This file contains macro definition of power sense monitor INA230
 *
 *	@copyright Copyright 2024 Antaris, Inc.
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

#ifndef PSM_REGISTER_MAP_H_
#define PSM_REGISTER_MAP_H_
/*******************************Register address*****************************************/
#define INA230_REG_CONFIG        0x00  /**< Configuration Register      */ //0x00 is the address A0-testing purpose
#define INA230_REG_VSHUNT        0x01  /**< Shunt Voltage Register      */
#define INA230_REG_VBUS          0x02  /**< Bus Voltage Register        */
#define INA230_REG_PWR           0x03  /**< Power Register              */
#define INA230_REG_CURRENT       0x04  /**< Current Register            */
#define INA230_REG_CALIBRATION   0x05  /**< Calibration Register        */
#define INA230_REG_MASK_ENABLE   0x06  /**< Mask/Enable Register        */
#define INA230_REG_ALERT_LIMIT   0x07  /**< Alert Limit Register        */
#define INA230_REG_ID            0xFF  /**< Die identification register */ //0xFF is the address A2-testing purpose

/*******************  Bit definition for Configuration register  **************/
#define INA230_REG_CFG_RESET_Pos        (15U)
#define INA230_REG_CFG_RESET_Msk        (0x1U << INA230_REG_CFG_RESET_Pos)      /**< 0x8000 */
#define INA230_REG_CFG_RESET            INA230_REG_CFG_RESET_Msk                /**< Reset Bit */
#define INA230_REG_CFG_AVG_Pos          (9U)
#define INA230_REG_CFG_AVG_Msk          (0x7U << INA230_REG_CFG_AVG_Pos)        /**< 0x0E00 */
#define INA230_REG_CFG_AVG              INA230_REG_CFG_AVG_Msk                  /**< Averaging Mode */
#define INA230_REG_CFG_AVG_0            (0x1U << INA230_REG_CFG_AVG_Pos)        /**< 0x0200 */
#define INA230_REG_CFG_AVG_1            (0x2U << INA230_REG_CFG_AVG_Pos)        /**< 0x0400 */
#define INA230_REG_CFG_AVG_2            (0x3U << INA230_REG_CFG_AVG_Pos)        /**< 0x0800 */
#define INA230_REG_CFG_VBUSCT_Pos       (6U)
#define INA230_REG_CFG_VBUSCT_Msk       (0x7U << INA230_REG_CFG_VBUSCT_Pos)     /**< 0x01C0 */
#define INA230_REG_CFG_VBUSCT           INA230_REG_CFG_VBUSCT_Msk               /**< Bus Voltage Conversion Time */
#define INA230_REG_CFG_VBUSCT_0         (0x1U << INA230_REG_CFG_VBUSCT_Pos)     /**< 0x0040 */
#define INA230_REG_CFG_VBUSCT_1         (0x2U << INA230_REG_CFG_VBUSCT_Pos)     /**< 0x0080 */
#define INA230_REG_CFG_VBUSCT_2         (0x4U << INA230_REG_CFG_VBUSCT_Pos)     /**< 0x0100*/
#define INA230_REG_CFG_VSHUNTCT_Pos     (3U)
#define INA230_REG_CFG_VSHUNTCT_Msk     (0x7U << INA230_REG_CFG_VSHUNTCT_Pos)   /**< 0x0068 */
#define INA230_REG_CFG_VSHUNTCT         INA230_REG_CFG_VSHUNTCT_Msk             /**< Shunt Voltage Conversion Time */
#define INA230_REG_CFG_VSHUNTCT_0       (0x1U << INA230_REG_CFG_VBUSCT_Pos)     /**< 0x0008 */
#define INA230_REG_CFG_VSHUNTCT_1       (0x2U << INA230_REG_CFG_VBUSCT_Pos)     /**< 0x0020 */
#define INA230_REG_CFG_VSHUNTCT_2       (0x4U << INA230_REG_CFG_VBUSCT_Pos)     /**< 0x0040 */
#define INA230_REG_CFG_MODE_Pos         (0U)
#define INA230_REG_CFG_MODE_Msk         (0x7U << INA230_REG_CFG_MODE_Pos)       /**< 0x0007 */
#define INA230_REG_CFG_MODE             INA230_REG_CFG_MODE_Msk                 /**< Operating Mode */
#define INA230_REG_CFG_MODE_0           (0x1U << INA230_REG_CFG_MODE_Pos)       /**< 0x0001 */
#define INA230_REG_CFG_MODE_1           (0x2U << INA230_REG_CFG_MODE_Pos)       /**< 0x0002 */
#define INA230_REG_CFG_MODE_2           (0x4U << INA230_REG_CFG_MODE_Pos)       /**< 0x0004 */

/******************  Bit definition for Shunt Voltage register  ***************/
#define INA230_REG_VSHUNT_DATA_Pos      (0U)
#define INA230_REG_VSHUNT_DATA_Msk      (0x7FFFU << INA230_REG_VSHUNT_DATA_Pos) /**< 0x7FFF */
#define INA230_REG_VSHUNT_DATA          INA230_REG_VSHUNT_DATA_Msk              /**< Measured shunt voltage */
#define INA230_REG_VSHUNT_SIGN_Pos      (15U)
#define INA230_REG_VSHUNT_SIGN_Msk      (0x1U << INA230_REG_VSHUNT_SIGN_Pos)    /**< 0x8000 */
#define INA230_REG_VSHUNT_SIGN          INA230_REG_VSHUNT_SIGN_Msk              /**< Sign */

/*******************  Bit definition for Bus Voltage register  ****************/
#define INA230_REG_VBUS_DATA_Pos        (0U)
#define INA230_REG_VBUS_DATA_Msk        (0x7FFFU << INA230_REG_VBUS_DATA_Pos)   /**< 0x7FFF */
#define INA230_REG_VBUS_DATA            INA230_REG_VBUS_DATA_Msk                /**< Measured bus voltage */

/*********************  Bit definition for Power register  ********************/
#define INA230_REG_PWR_DATA_Pos         (0U)
#define INA230_REG_PWR_DATA_Msk         (0xFFFFU << INA230_REG_PWR_DATA_Pos)    /**< 0xFFFF */
#define INA230_REG_PWR_DATA             INA230_REG_PWR_DATA_Msk                 /**< Measured power */

/*****************  Bit definition for Current register  **********************/
#define INA230_REG_CURRENT_DATA_Pos     (0U)
#define INA230_REG_CURRENT_DATA_Msk     (0x7FFFU << INA230_REG_CURRENT_DATA_Pos) /**< 0x7FFF */
#define INA230_REG_CURRENT_DATA         INA230_REG_CURRENT_DATA_Msk              /**< Measured current */
#define INA230_REG_CURRENT_SIGN_Pos     (15U)
#define INA230_REG_CURRENT_SIGN_Msk     (0x1U << INA230_REG_CURRENT_SIGN_Pos)   /**< 0x8000 */
#define INA230_REG_CURRENT_SIGN         INA230_REG_CURRENT_SIGN_Msk             /**< Sign */

/*******************  Bit definition for Calibration register  ****************/
#define INA230_REG_CALIBRATION_DATA_Pos (0U)
#define INA230_REG_CALIBRATION_DATA_Msk (0x7FFFU << INA230_REG_CALIBRATION_DATA_Pos) /**< 0x7FFF */
#define INA230_REG_CALIBRATION_DATA     INA230_REG_CALIBRATION_DATA_Msk              /**< Measured current */

/*******************  Bit definition for Mask/Enable register  ****************/
#define INA230_REG_MASK_ENABLE_SOL_Pos  (15U)
#define INA230_REG_MASK_ENABLE_SOL_Msk  (0x1U << INA230_REG_MASK_ENABLE_SOL_Pos)  /**< 0x8000 */
#define INA230_REG_MASK_ENABLE_SOL      INA230_REG_MASK_ENABLE_SOL_Msk            /**< Shunt Voltage Over-Voltage */
#define INA230_REG_MASK_ENABLE_SUL_Pos  (14U)
#define INA230_REG_MASK_ENABLE_SUL_Msk  (0x1U << INA230_REG_MASK_ENABLE_SUL_Pos)  /**< 0x4000 */
#define INA230_REG_MASK_ENABLE_SUL      INA230_REG_MASK_ENABLE_SUL_Msk            /**< Shunt Voltage Under-Voltage */
#define INA230_REG_MASK_ENABLE_BOL_Pos  (13U)
#define INA230_REG_MASK_ENABLE_BOL_Msk  (0x1U << INA230_REG_MASK_ENABLE_BOL_Pos)  /**< 0x2000 */
#define INA230_REG_MASK_ENABLE_BOL      INA230_REG_MASK_ENABLE_BOL_Msk            /**< Bus Voltage Over-Voltage */
#define INA230_REG_MASK_ENABLE_BUL_Pos  (12U)
#define INA230_REG_MASK_ENABLE_BUL_Msk  (0x1U << INA230_REG_MASK_ENABLE_BUL_Pos)  /**< 0x1000 */
#define INA230_REG_MASK_ENABLE_BUL      INA230_REG_MASK_ENABLE_BUL_Msk            /**< Bus Voltage Under-Voltage */
#define INA230_REG_MASK_ENABLE_POL_Pos  (11U)
#define INA230_REG_MASK_ENABLE_POL_Msk  (0x1U << INA230_REG_MASK_ENABLE_POL_Pos)  /**< 0x0800 */
#define INA230_REG_MASK_ENABLE_POL      INA230_REG_MASK_ENABLE_POL_Msk            /**< Over-Limit Power */
#define INA230_REG_MASK_ENABLE_CNVR_Pos (10U)
#define INA230_REG_MASK_ENABLE_CNVR_Msk (0x1U << INA230_REG_MASK_ENABLE_CNVR_Pos) /**< 0x0400 */
#define INA230_REG_MASK_ENABLE_CNVR     INA230_REG_MASK_ENABLE_CNVR_Msk           /**< Conversion Ready */
#define INA230_REG_MASK_ENABLE_AFF_Pos  (4U)
#define INA230_REG_MASK_ENABLE_AFF_Msk  (0x1U << INA230_REG_MASK_ENABLE_AFF_Pos)  /**< 0x0001 */
#define INA230_REG_MASK_ENABLE_AFF      INA230_REG_MASK_ENABLE_AFF_Msk            /**< Alert Function Flag */
#define INA230_REG_MASK_ENABLE_CVRF_Pos (3U)
#define INA230_REG_MASK_ENABLE_CVRF_Msk (0x1U << INA230_REG_MASK_ENABLE_CVRF_Pos) /**< 0x0008 */
#define INA230_REG_MASK_ENABLE_CVRF     INA230_REG_MASK_ENABLE_CVRF_Msk           /**< Conversion Ready Flag */
#define INA230_REG_MASK_ENABLE_OVF_Pos  (2U)
#define INA230_REG_MASK_ENABLE_OVF_Msk  (0x1U << INA230_REG_MASK_ENABLE_OVF_Pos)  /**< 0x0004 */
#define INA230_REG_MASK_ENABLE_OVF      INA230_REG_MASK_ENABLE_OVF_Msk            /**< Math Overflow Flag */
#define INA230_REG_MASK_ENABLE_APOL_Pos (1U)
#define INA230_REG_MASK_ENABLE_APOL_Msk (0x1U << INA230_REG_MASK_ENABLE_APOL_Pos) /**< 0x0002 */
#define INA230_REG_MASK_ENABLE_APOL     INA230_REG_MASK_ENABLE_APOL_Msk           /**< Alert Polarity */
#define INA230_REG_MASK_ENABLE_LEN_Pos  (0U)
#define INA230_REG_MASK_ENABLE_LEN_Msk  (0x1U << INA230_REG_MASK_ENABLE_LEN_Pos)  /**< 0x0001 */
#define INA230_REG_MASK_ENABLE_LEN      INA230_REG_MASK_ENABLE_LEN_Msk            /**< Alert Latch Enable */

/*******************  Bit definition for Alert Limit register  ****************/
#define INA230_REG_ALERT_LIMIT_DATA_Pos (0U)
#define INA230_REG_ALERT_LIMIT_DATA_Msk (0xFFFFU << INA230_REG_ALERT_LIMIT_DATA_Pos) /**< 0xFFFF */
#define INA230_REG_ALERT_LIMIT_DATA     INA230_REG_ALERT_LIMIT_DATA_Msk              /**< Alert Limit */

/**
 * @brief INA230_MODE  INA230 operating mode
 */
#define INA230_MODE_POWER_DOWN       (uint16_t)0x0000U                                 /**< Turn off current into the INA230 inputs               */
#define INA230_MODE_TRIGGERED_VSHUNT INA230_REG_CFG_MODE_0                             /**< Shunt Voltage, Single shot conversion                 */
#define INA230_MODE_TRIGGERED_VBUS   INA230_REG_CFG_MODE_1                             /**< Bus voltage, Single shot conversion                   */
#define INA230_MODE_TRIGGERED_ALL    (INA230_REG_CFG_MODE_1 | INA230_REG_CFG_MODE_0)   /**< Shunt Voltage and Bus voltage, Single shot conversion */
#define INA230_MODE_CONTINOUS_VSHUNT (INA230_REG_CFG_MODE_2 | INA230_REG_CFG_MODE_0)   /**< Shunt Voltage, Continuous conversion                  */
#define INA230_MODE_CONTINOUS_VBUS   (INA230_REG_CFG_MODE_2 | INA230_REG_CFG_MODE_1)   /**< Bus voltage, Continuous conversion                    */
#define INA230_MODE_CONTINOUS_ALL    INA230_REG_CFG_MODE                               /**< Shunt Voltage and Bus voltage, Continuous conversion  */

/**
 * @brief INA230_CT INA230 ADC conversion time
 */
#define INA230_CT_140     (uint16_t)0x0000U                                       /**< ADC conversion time: 140 us  */
#define INA230_CT_204     INA230_REG_CFG_VSHUNTCT_0                               /**< ADC conversion time: 204 us  */
#define INA230_CT_332     INA230_REG_CFG_VSHUNTCT_1                               /**< ADC conversion time: 332 us  */
#define INA230_CT_588     (INA230_REG_CFG_VSHUNTCT_1 | INA230_REG_CFG_VSHUNTCT_0) /**< ADC conversion time: 588 us  */
#define INA230_CT_1100    INA230_REG_CFG_VSHUNTCT_2                               /**< ADC conversion time: 1100 us */
#define INA230_CT_2116    (INA230_REG_CFG_VSHUNTCT_2| INA230_REG_CFG_VSHUNTCT_0)  /**< ADC conversion time: 2116 us */
#define INA230_CT_4156    (INA230_REG_CFG_VSHUNTCT_2| INA230_REG_CFG_VSHUNTCT_1)  /**< ADC conversion time: 4156 us */
#define INA230_CT_8244    INA230_REG_CFG_VSHUNTCT                                 /**< ADC conversion time: 8244 us */

/**
 * @brief INA230_AVG INA230 number of averages
 */

#define INA230_AVG_1      (uint16_t)0x0000U                                       /**< Number of averages: 1    */
#define INA230_AVG_4      INA230_REG_AVG_VSHUNTCT_0                               /**< Number of averages: 4    */
#define INA230_AVG_16     INA230_REG_AVG_VSHUNTCT_1                               /**< Number of averages: 16   */
#define INA230_AVG_64     (INA230_REG_AVG_VSHUNTCT_1 | INA230_REG_AVG_VSHUNTCT_0) /**< Number of averages: 64   */
#define INA230_AVG_128    INA230_REG_AVG_VSHUNTCT_2                               /**< Number of averages: 128  */
#define INA230_AVG_256    (INA230_REG_AVG_VSHUNTCT_2| INA230_REG_AVG_VSHUNTCT_0)  /**< Number of averages: 256  */
#define INA230_AVG_512    (INA230_REG_AVG_VSHUNTCT_2| INA230_REG_AVG_VSHUNTCT_1)  /**< Number of averages: 512  */
#define INA230_AVG_1024   INA230_REG_AVG_VSHUNTCT                                 /**< Number of averages: 1024 */


/**
 * @brief  INA230 NULL PTR CHECK DEFINITIONS
 *
 */
#define INA230_OK 					(0)				/**< INA230 OK   */
#define INA230_E_NULL_PTR			(-1)			/**< INA230 NULL Ptr error   */
#define INA230_E_COM_FAIL			(-2)			/**< INA230 communication fail   */
#define INA230_DEV_NOT_FOUND		(-4)			/**< INA230 DEVICE NOT FOUND */
#define INA230_E_READ_FAIL			(-5)			/**< INA230 READ FAIL*/

/**
 * @brief INA230_FLAG INA230 flags
 */
#define INA230_AFF        INA230_REG_MASK_ENABLE_AFF         /**< Alert Function Flag   */
#define INA230_CVRF       INA230_REG_MASK_ENABLE_CVRF        /**< Conversion Ready Flag */
#define INA230_OVRF       INA230_REG_MASK_ENABLE_OVF         /**< Math Overflow Flag    */


/**
 * @brief  INA230 alert functions
 *
 */
#define INA230_ALERTFUNC_SOL       INA230_REG_MASK_ENABLE_SOL         /**< Shunt Voltage Over Limit  */
#define INA230_ALERTFUNC_SUL       INA230_REG_MASK_ENABLE_SUL         /**< Shunt Voltage Under Limit */
#define INA230_ALERTFUNC_BOL       INA230_REG_MASK_ENABLE_BOL         /**< Bus Voltage Over Limit    */
#define INA230_ALERTFUNC_BUL       INA230_REG_MASK_ENABLE_BUL         /**< Bus Voltage Under Limit   */
#define INA230_ALERTFUNC_POL       INA230_REG_MASK_ENABLE_POL         /**< Power Over Limit          */

#define REG_MASK_ENABLE_FUNCTIONS_Msk (INA230_REG_MASK_ENABLE_SOL_Msk | INA230_REG_MASK_ENABLE_SUL_Msk | INA230_REG_MASK_ENABLE_BOL_Msk | INA230_REG_MASK_ENABLE_BUL_Msk | INA230_REG_MASK_ENABLE_POL_Msk)

#define REG_MASK_ENABLE_FLAGS_Msk (INA230_REG_MASK_ENABLE_AFF_Msk  | INA230_REG_MASK_ENABLE_CVRF_Msk | INA230_REG_MASK_ENABLE_OVF_Msk)
/*
 * @brief 1 LSB step size for VBus : 1.25 mV
 * VBus = [INA230_REG_VBUS] * 1.25 mV
 * VBus = [INA230_REG_VBUS] * BUS_VOLTAGE_LSB/1000
 */
#define BUS_VOLTAGE_LSB 0.00125

#define CURR_MULTIPLIER 1.0
/* 1 LSB step size for  VShunt: 2.5 µV
 * VShunt = [INA230_REG_VSHUNT] * (1000/2.5) mV = ([INA230_REG_VSHUNT]/400) mV
 * VShunt = [INA230_REG_VSHUNT] * VSHUNT_DIV
 */
#define VSHUNT_DIV 0.0000025
/* 1 LSB step size for power : 25 mW (assuming Current LSB is 1 mA)
 * Power = [INA230_REG_PWR] * 25 mW
 * Power = [INA230_REG_PWR] * POWER_LSB
 */
#define POWER_LSB 25

#define RSHUNT 0.002
#define DIV_ROUND_CLOSEST( DIVIDEND , DIVISOR ) (((  DIVIDEND  ) + (( DIVISOR )/2)) / ( DIVISOR ))

#endif /* PSM_REGISTER_MAP_H_ */

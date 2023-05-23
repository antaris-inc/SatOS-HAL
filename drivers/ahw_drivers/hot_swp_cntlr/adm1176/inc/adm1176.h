/**
 * @file adm1176.h
 *
 *  @brief This file contains the macros,structure declaration,enumeration,
 *  function declaration of hotswap controller ADM1176
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

#ifndef ADM1176_H
#define ADM1176_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#define ADM1176_I2C_ADDR0	  0x80		///< ADM1176 I2C address 0
#define ADM1176_I2C_ADDR1	  0x82		///< ADM1176 I2C address 1
#define ADM1176_I2C_ADDR2	  0x84		///< ADM1176 I2C address 2
#define ADM1176_I2C_ADDR3	  0x86		///< ADM1176 I2C address 3
#define ADM1176_I2C_ADDR4	  0x88		///< ADM1176 I2C address 4
#define ADM1176_I2C_ADDR5	  0x8A		///< ADM1176 I2C address 5
#define ADM1176_I2C_ADDR6	  0x8C		///< ADM1176 I2C address 6
#define ADM1176_I2C_ADDR7	  0x8E		///< ADM1176 I2C address 7
#define ADM1176_I2C_ADDR8	  0x90		///< ADM1176 I2C address 8
#define ADM1176_I2C_ADDR9	  0x92		///< ADM1176 I2C address 9
#define ADM1176_I2C_ADDR10	  0x94		///< ADM1176 I2C address 10
#define ADM1176_I2C_ADDR11	  0x96		///< ADM1176 I2C address 11
#define ADM1176_I2C_ADDR12	  0x98		///< ADM1176 I2C address 12
#define ADM1176_I2C_ADDR13	  0x9A		///< ADM1176 I2C address 13
#define ADM1176_I2C_ADDR14	  0x9C		///< ADM1176 I2C address 14
#define ADM1176_I2C_ADDR15	  0x9E		///< ADM1176 I2C address 15

#define ALERT_EN            0x81		///< Alert enable
#define ALERT_TH            0x82		///<
#define CONTROL             0x83		///< ADM1176 control

#define V_FULL_SCALE     26.35			///< V full scale
#define I_FULL_SCALE     105.84			///< I full scle
#define SENSE_RESISTOR   0.002			///< ADM1176 resistor

/**
 * @brief  read API function pointer
 */
typedef int8_t (*adm1176_read_fptr_t)(void* intf_hdl, uint16_t slv_addr, uint8_t *data, uint16_t len);

/**
 * @brief  write API function pointer
 */
typedef int8_t (*adm1176_write_fptr_t)(void* intf_hdl, uint16_t slv_addr,uint8_t *data, uint16_t len);

/**
 * @brief  Delay API function pointer
 */
typedef void (*adm1176_delay_fptr_t)(uint32_t time_micro_sec);

/*!
 *  @brief Enumeration for types of error in ADM1176
 */
typedef enum
{
    ADM1176_SCS,              ///< ADM1176 success status
    ADM1176_ERR,              ///< ADM1176 error status
    NULL_PTR_ER=-2,           ///< ADM1176 null ptr error
    ADM1176_E_COM_FAIL=-3     ///< ADM1176 communication fail error
}e_adm1176_err;

/*!
 *  @brief enumeration for ADM1176 operating modes
 */
typedef enum
{
    ADM_ONESHOT = 0b1,            ///< one shot mode or continuous conversion mode
    ADM_CONTINOUS_CONV = 0b0      ///< Continuous conversion mode
}e_adm1176_mode;

/*!
 *  @brief control block structure for ADM1176 instance.
 */
typedef struct
{
    uint8_t rdbck_type:1;                   /*!< read back type 1-status read  0-voltage and current read 	*/
    e_adm1176_mode voltage_read_mode:1;     /*!< 1-onehot or 0-continous conversion  						*/
    e_adm1176_mode current_read_mode:1;     /*!< 1-onehot or 0-continous conversion  						*/
    uint8_t over_curr_sts:1;                /*!< over currrent event status          						*/
    uint8_t hot_swp_sts:1;                  /*!< hot swap status                     						*/
    uint16_t slv_addr;                      /*!< I2C interface slave address         						*/
    void* intf_hdl;                         /*!< Interface handler pointer           						*/
    adm1176_write_fptr_t write;             /*!< I2C write function pointer          						*/
    adm1176_read_fptr_t read;               /*!< I2C read function pointer           						*/
    uint8_t fault_curr_thrsld;              /*!< fault current threshold             						*/
    adm1176_delay_fptr_t delay;             /*!< Delay function pointer         							*/

}s_adm1176_drv_cb;

typedef s_adm1176_drv_cb *s_adm1176_drv_cb_ptr;

/**
 * @brief ADM1176 initialization is done in this function
 * @param[in]  adm1176_hdl - instance pointer of adm1176
 * @retval e_adm1176_err - returns the success or error code
 */
e_adm1176_err adm1176_init(s_adm1176_drv_cb_ptr adm1176_hdl);

/**
 * @brief ADM1176 deinitialization is done in this function
 * @param[in]  adm1176_hdl - instance pointer of adm1176
 * @retval e_adm1176_err - returns the success or error code
 */
e_adm1176_err adm1176_deinit(s_adm1176_drv_cb_ptr adm1176_hdl);

/**
 * @brief voltage read is done in this function
 * @param[in]  adm1176_hdl - instance pointer of adm1176
 * @param[out] voltage – voltage is updated
 * @retval e_adm1176_err - returns the success or error code
 */
e_adm1176_err  adm1176_read_voltage(s_adm1176_drv_cb_ptr adm1176_hdl, float *voltage);

/**
 * @brief current read is done in this function
 * @param[in]  adm1176_hdl - instance pointer of adm1176
 * @param[out] current – current is updated
 * @retval e_adm1176_err - returns the success or error code
 */
e_adm1176_err adm1176_read_current(s_adm1176_drv_cb_ptr adm1176_hdl, float *current);

/**
 * @brief threshold for alert is set in this function
 * @param[in]  adm1176_hdl - instance pointer of adm1176
 * @param[in]  threshold – threshold for alert
 * @retval e_adm1176_err - returns the success or error code
 */
e_adm1176_err adm1176_set_alert_threshold(s_adm1176_drv_cb_ptr adm1176_hdl, uint8_t threshold);

/**
 * @brief this function is used to manually turn on/off the hotswap operation
 * @param[in]  adm1176_hdl - instance pointer of adm1176
 * @param[in]  on_off –  on/off control command
 * @retval e_adm1176_err - returns the success or error code
 */
e_adm1176_err adm1176_hotswap_control(s_adm1176_drv_cb_ptr adm1176_hdl, uint8_t on_off);

/**
 * @brief  This function is use to get the hotswap status
 * @param[in]  adm1176_hdl - instance pointer of adm1176
 * @param[out] hotswap_sts – hotswap status is updated here
 * @retval e_adm1176_err - returns the success or error code
 */
e_adm1176_err adm1176_get_hotswap_sts(s_adm1176_drv_cb_ptr adm1176_hdl, uint8_t *hotswap_sts);

/**
 * @brief this function is used to get the under voltage status
 * @param[in]  adm1176_hdl - instance pointer of adm1176
 * @param[out] under_vlt_sts – under voltage status is updated here
 * @retval e_adm1176_err - returns the success or error code
 */
e_adm1176_err adm1176_get_overcurrent_sts(s_adm1176_drv_cb_ptr adm1176_hdl, uint8_t *under_vlt_sts);

/**
 * @brief this function is used to get the alert and hotswap status of adm1176
 * @param[in]  adm1176_hdl - instance pointer of adm1176
 * @param[out] sts – status of adm1176 is updated here
 * @retval e_adm1176_err - returns the success or error code
 */
e_adm1176_err adm1176_get_sts(s_adm1176_drv_cb_ptr adm1176_hdl, uint8_t *sts);


#endif

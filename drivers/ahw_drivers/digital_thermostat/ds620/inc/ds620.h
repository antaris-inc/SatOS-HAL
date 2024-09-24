/**
 * @file ds620.h
 *
 * @brief This file contains the macros,structure declaration,enumeration,
 *  function declaration of digital thermostat DS620
 *
 *  @copyright Copyright 2024 Antaris, Inc.
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
 *
 */

#ifndef DS620_H
#define DS620_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define MAX_COUNT 4           ///< Maximum count
#define MAX_TEMP_VAL 125      ///< Maximum temperature value
#define MIN_TEMP_VAL -55      ///< Minimum temperature value

#define TEMP_TL_LSB_REG   0xA3   ///< Low temperature threshold LSB register Address
#define TEMP_TL_MSB_REG   0xA2   ///< Low temperature threshold MSB register Address
#define TEMP_TH_LSB_REG   0xA1   ///< High temperature threshold LSB register Address
#define TEMP_TH_MSB_REG   0xA0   ///< High temperature threshold LSB register Address
#define TEMP_MSB_REG      0xAA   ///< Temperature MSB register Address
#define TEMP_LSB_REG      0xAB   ///< Temperature LSB register Address
#define CONFIG_MSB_REG    0xAC   ///< configuration MSB register Address
#define CONFIG_LSB_REG    0xAD   ///< configuration LSB register Address

#define DS620_I2C_ADDR0   0x90   ///< I2C slave address 0
#define DS620_I2C_ADDR1   0x91   ///< I2C slave address 1
#define DS620_I2C_ADDR2   0x92   ///< I2C slave address 2
#define DS620_I2C_ADDR3   0x93   ///< I2C slave address 3
#define DS620_I2C_ADDR4   0x94   ///< I2C slave address 4
#define DS620_I2C_ADDR5   0x95   ///< I2C slave address 5
#define DS620_I2C_ADDR6   0x96   ///< I2C slave address 6
#define DS620_I2C_ADDR7   0x97   ///< I2C slave address 7

#define START_CMD         0x51   ///< Start temperature conversion command
#define STOP_CMD          0x22   ///< Stop temperature conversion command
#define RECALL_CMD        0xB8   ///< Recall command
#define COPY_CMD          0x48   ///< Value of the Internal oscillator in Hz
#define SOFTWARE_POR      0x54   ///< Software power on reset command

#define MAX_NUM_DEV_SUPPORT  8   ///< Maximum number of device supported

#define DS620_DELAY 100          ///< Delay of 100

#define TIMEOUT 1000             ///< Timeout for IO interface read/write API

/**
 * @brief  read API function pointer
 */
typedef int8_t (*ds620_read_fptr_t)(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/**
 * @brief  write API function pointer
 */
typedef int8_t (*ds620_write_fptr_t)(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *read_data, uint16_t len);

typedef void (*ds620_delay_ms_fptr)(uint32_t ms);

/**
 * @brief  DS620 error status enumeration
 */
typedef enum
{
    DS620_SCS=0,               ///< DS620 success
    DS620_ERR=-1,              ///< DS620 error
    NULL_PTR_ERR=-2,           ///< NULL pointer error
    DS620_E_COM_FAIL=-3,       ///< DS620 communication fail error
    DS620_INVLD_ARG=-4,        ///< DS620 invalid argument error
    DS620_E_DEV_NOT_FOUND=-5   ///< DS620 device not found error

}e_ds620_err;

/**
 * @brief  DS620 ADC resolution enumeration
 */
typedef enum
{
    BIT_10 = 0x00,          ///< 10bit resolution
    BIT_11 = 0x04,          ///< 11bit resolution
    BIT_12 = 0x08,          ///< 12bit resolution
    BIT_13 = 0x0C           ///< 13bit resolution
}e_ds620_res;

/**
 * @brief  DS620 operating mode enumeration
 */
typedef enum
{
    ONESHOT_CONV = 0b1,           ///< Oneshot mode
    CONTINOUS_CONV = 0b0          ///< Continous conversion mode
}e_ds620_mode;

/**
 * @brief  DS620 PO pin level type enumeration
 */
typedef enum
{
    PO_HIGH = 0xC0,        ///< PO pin High level
    PO_LOW = 0x80,         ///< PO pin Low level
    FORCE_LOW = 0x00       ///< PO pin Force low
}e_ds620_po_lvl;

/**
 * @brief  DS620 auto conversion enable/disable enumeration
 */
typedef enum
{
    AUTO_CONV_ENABLE= 0x02,    ///< Enable auto conversion
    AUTO_CONV_DISABLE = 0x00   ///< Disable auto conversion
}e_ds620_auto_conv;

/**
 * @brief  DS620 instance control block structure definition
 */
typedef struct
{
    e_ds620_mode mode;              /*!< DS620 operating mode                 */
    e_ds620_res resolution;         /*!< ADC resolution                       */
    int16_t temp_high_thrshd;       /*!< High temperature threshold value     */
    int16_t temp_low_thrshd;        /*!< low temperature threshold value      */
    e_ds620_auto_conv conv_type;    /*!< Auto conversion enable/disable       */
    e_ds620_po_lvl po_level_type;   /*!< PO pin level type                    */
    uint16_t slv_addr;              /*!< Slave address                        */
    void* intf_hdl;                 /*!< IO interface handle pointer          */
    ds620_read_fptr_t read;         /*!< Read API function pointer            */
    ds620_write_fptr_t write;       /*!< Write API function pointer           */
    ds620_delay_ms_fptr delay_ms;

}s_ds620_drv_cb;

/**
 * @brief  DS620 control block memory pointer type definition
 */
typedef s_ds620_drv_cb *s_ds620_drv_cb_ptr;

/**
 * @brief DS620 memory and peripheral initalizes in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_init (s_ds620_drv_cb_ptr ds620_hdl);

/**
 * @brief DS620 memory and peripheral deinit in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_deinit (s_ds620_drv_cb_ptr ds620_hdl);

/**
 * @brief DS620 high temperature threshold is set in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[in]  high_temp_thrshd – high temperature threshold in celsius
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_set_temperature_high_thrshd (s_ds620_drv_cb_ptr ds620_hdl, double high_temp_thrshd);

/**
 * @brief DS620 low temperature threshold is set in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[out] low_temp_thrshd – low temperature threshold in celsius
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_set_temperature_low_thrshd (s_ds620_drv_cb_ptr ds620_hdl, double low_temp_thrshd);

/**
 * @brief Temperature read is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[out] temperature – temperature in celsius is updated in this variable
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_get_temperature (s_ds620_drv_cb_ptr ds620_hdl, double* temperature);

/**
 * @brief DS620 temperature set is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[in] temperature –set temperature for the DS620, this will be used for testing
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_set_temperature (s_ds620_drv_cb_ptr ds620_hdl, double temperature);

/**
 * @brief DS620 configurations is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_config (s_ds620_drv_cb_ptr ds620_hdl);

/**
 * @brief DS620 resolution set is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[in]  res – ADC resolution value
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_set_resolution (s_ds620_drv_cb_ptr ds620_hdl, e_ds620_res res);

/**
 * @brief DS620 resolution get is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[out] res – ADC resolution pointer
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_get_resolution(s_ds620_drv_cb_ptr ds620_hdl,e_ds620_res *res);

/**
 * @brief DS620 operating mode set is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[in] mode – operating mode it can be either oneshot or continous conversion
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_set_conv_mode (s_ds620_drv_cb_ptr ds620_hdl,e_ds620_mode mode);

/**
 * @brief DS620 PO pin level type set is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[in]  lvl – PO pin level type
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_set_po_lvl (s_ds620_drv_cb_ptr ds620_hdl, e_ds620_po_lvl lvl);

/**
 * @brief DS620 software power on reset is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_reset(s_ds620_drv_cb_ptr ds620_hdl);

/**
 * @brief DS620 start conversion is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_start_conversion(s_ds620_drv_cb_ptr ds620_hdl);

/**
 * @brief DS620 stop conversion is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_stop_conversion(s_ds620_drv_cb_ptr ds620_hdl);

/**
 * @brief DS620 PO pin level type get is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[out] lvl - PO pin level
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_get_po_lvl (s_ds620_drv_cb_ptr ds620_hdl, e_ds620_po_lvl* lvl);

/**
 * @brief DS620 mode type is get in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[out] mode - Mode type
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_get_mode (s_ds620_drv_cb_ptr ds620_hdl,e_ds620_mode* mode);

/**
 * @brief DS620 low temperature threshold is get in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[out] low_temp_thrshd - low temperature threshold in celsius
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_get_temperature_low_thrshd (s_ds620_drv_cb_ptr ds620_hdl, double* low_temp_thrshd);

/**
 * @brief DS620 high temperature threshold is get in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[out] high_temp_thrshd - high temperature threshold in celsius
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_get_temperature_high_thrshd (s_ds620_drv_cb_ptr ds620_hdl, double* high_temp_thrshd);

/**
 * @brief DS620 reset of alert flag is done in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_reset_alert_flag(s_ds620_drv_cb_ptr ds620_hdl);

/**
 * @brief DS620 PO pin level alert status is received in this function
 * @param[in]  ds620_hdl - instance pointer of DS620
 * @param[out] alert_sts - alert status
 * @retval e_ds620_err - returns the success or error code
 */
e_ds620_err ds620_get_po_lvl_alert_sts (s_ds620_drv_cb_ptr ds620_hdl, e_ds620_po_lvl* alert_sts);

#endif /* DS620_H */

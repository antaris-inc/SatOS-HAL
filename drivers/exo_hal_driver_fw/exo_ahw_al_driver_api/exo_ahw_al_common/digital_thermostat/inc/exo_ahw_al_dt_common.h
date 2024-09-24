/**
 * @file exo_ahw_al_dt_common.h
 *
 * @brief This file has abstracted driver functions,structures and enumerations for digital thermostat
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


#ifndef _AHW_AL_DT_COMMON_H_
#define _AHW_AL_DT_COMMON_H_

#include <stdint.h>
#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_ahw_al_common.h"

/**
 * @brief  DS620 ADC resolution enumeration
 */
typedef enum
{
    DT_BIT_10 = 0x00,          /*!< 10bit resolution */
    DT_BIT_11 = 0x01,          /*!< 11bit resolution */
    DT_BIT_12 = 0x02,          /*!< 12bit resolution */
    DT_BIT_13 = 0x03,          /*!< 13bit resolution */
    DT_RES_MAX

}digital_thermos_resolution;

/**
 * @brief  DS620 operating mode enumeration
 */
typedef enum
{
    DT_ONESHOT,             /*!< Oneshot mode */
    DT_CONTINOUS_CONV,      /*!< Continous conversion mode */
    DT_CONV_MODE_MAX

}digital_thermos_conversion_mode;

/**
 * @brief  DS620 PO pin level type enumeration
 */
typedef enum
{
    DT_HIGH,                /*!< PO pin High level */
    DT_LOW,             /*!< PO pin Low level */
    DT_MODE_MAX

}digital_thermos_mode;

/**
 * @brief Digital thermostat control block memory structure definition
 */
typedef struct _ahw_al_dt_hdle
{
    ahw_al_gen_info ahw_gen_info;       /*!< AHW general information              */
    double low_temp_thrsld;             /*!< low temperature threshold value      */
    double high_temp_thrsld;            /*!< High temperature threshold value     */
    uint8_t conversion_mode;            /*!< Auto conversion enable/disable       */
    uint8_t resolution;                 /*!< ADC resolution                       */
    uint8_t thermostat_mode;            /*!< DS620 operating mode                 */
    uint8_t thermostat_event_sts;       /*!< DS620 event status                   */

}ahw_al_dt_hdle;

/**
 * @brief This API initializes the control block memory and do the
 * basic configurations for digital thermostat and temperature sensor instance.
 * @param[in] hdt_arg - AHAL instance pointer of digital thermostat and temperature sensor.
 * @param[in] ahw_id - application hardware instance ID
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_init(ahw_al_dt_hdle* hdt_arg, ahw_inst_id_t ahw_id);

/**
 * @brief This API deinitializes the control block memory and do the basic configurations
 * for digital thermostat and temperature sensor instance.
 * @param[in] hdt_arg - AHAL instance pointer of digital thermostat and temperature sensor.
 * @param[in] ahw_id - application hardware instance ID
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_deinit(ahw_al_dt_hdle* hdt_arg, ahw_inst_id_t ahw_id);

/**
 * @brief This API set the high temperature threshold for temperature sensor
 * @param[in] hdt - AHAL instance pointer of digital thermostat and temperature sensor.
 * @param[in] high_temp_threshold – high temperature threshold in celsius
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_set_temperature_high_threshold (ahw_al_dt_hdle *hdt, double high_temp_threshold);

/**
 * @brief This API set the low temperature threshold temperature sensor
 * @param[in] hdt - AHAL instance pointer of digital thermostat and temperature sensor.
 * @param[in] low_temp_threshold – low temperature threshold in celsius
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_set_temperature_low_threshold (ahw_al_dt_hdle *hdt, double low_temp_threshold);

/**
 * @brief This API get the temperature temperature sensor
 * @param[in] hdt - AHAL instance pointer of digital thermostat and temperature sensor.
 * @param[in] temperature – temperature in celsius is updated in this variable
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_get_temperature (ahw_al_dt_hdle *hdt, double* temperature);

/**
 * @brief This API do the basic configurations for digital thermostat and temperature sensor instance.
 * @param[in] hdt - AHAL instance pointer of digital thermostat and temperature sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_config (ahw_al_dt_hdle *hdt);

/**
 * @brief This API sets the ADC resolution temperature sensor
 * @param[in] hdt - AHAL instance pointer of digital thermostat and temperature sensor.
 * @param[in] res – ADC resolution value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_set_resolution (ahw_al_dt_hdle *hdt, digital_thermos_resolution _res);

/**
 * @brief This API gets the ADC resolution temperature sensor
 * @param[in] hdt - AHAL instance pointer of digital thermostat and temperature sensor.
 * @param[out] res – ADC resolution value
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_get_resolution (ahw_al_dt_hdle *hdt, digital_thermos_resolution *res );

/**
 * @brief This API set the operating mode for temperature sensor
 * @param[in] hdt - AHAL instance pointer of digital thermostat and temperature sensor.
 * @param[in] mode – operating mode it can be either oneshot or continuous conversion.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_set_conv_mode (ahw_al_dt_hdle *hdt, uint8_t mode);

/**
 * @brief This API sets the PO pin logic level of digital thermostat
 * @param[in] hdt - AHAL instance pointer of digital thermostat and temperature sensor.
 * @param[in] lvl – PO pin level type
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_set_po_lvl (ahw_al_dt_hdle *hdt, uint8_t lvl);

/**
 * @brief This API resets the digital thermostat
 * @param[in] hdt - AHAL instance pointer of digital thermostat and temperature sensor.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_reset (ahw_al_dt_hdle *hdt);

/**
 * @brief This API set the PO pin level alert status
 * @param[in]  hdt - instance pointer of DS620
 * @param[in] lvl - PO pin level type
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_set_po_lvl_alert_sts(ahw_al_dt_hdle *hdt, uint8_t* lvl);

/**
 * @brief This API start temperature conversion
 * @param[in]  hdt - instance pointer of DS620
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_start_conversion(ahw_al_dt_hdle *hdt);

/**
 * @brief This API stop temperature conversion
 * @param[in]  hdt - instance pointer of DS620
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_stop_conversion(ahw_al_dt_hdle *hdt);

/**
 * @brief This API get the PO pin logic level
 * @param[in]  hdt - instance pointer of DS620
 * @param[out] lvl - PO pin level type
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_get_po_lvl(ahw_al_dt_hdle *hdt,uint8_t *lvl);

/**
 * @brief This API get the operating mode of temperature sensor
 * @param[in]  hdt - instance pointer of DS620
 * @param[out] mode - operating mode
 *              1 - one shot conversion
 *              0 - continuous conversion
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_get_mode(ahw_al_dt_hdle *hdt,uint8_t *mode);

/**
 * @brief This API get the low temperature threshold
 * @param[in]  hdt - instance pointer of DS620
 * @param[out] low_temp_thrshld - low temperature threshold in celsius
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_get_temperature_low_thrshd(ahw_al_dt_hdle *hdt,double *low_temp_thrshld);

/**
 * @brief This API get the high temperature threshold
 * @param[in]  hdt - instance pointer of DS620
 * @param[out] high_temp_thrshld - high temperature threshold in celsius
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_get_temperature_high_thrshd(ahw_al_dt_hdle *hdt,double *high_temp_thrshld);

/**
 * @brief This API reset the alert flag
 * @param[in]  hdt - instance pointer of DS620
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_dt_reset_alert_flag(ahw_al_dt_hdle *hdt);


#endif

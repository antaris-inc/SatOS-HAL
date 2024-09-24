/**
 * @file exo_ahw_al_temp_sensor_common.h
 *
 * @brief This file contains function prototype,structure and enumeration for temperature sensor
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

#ifndef HAL_DRIVER_FW_AHW_AL_DRIVER_API_AHW_AL_INC_AHW_AL_TEMP_H_
#define HAL_DRIVER_FW_AHW_AL_DRIVER_API_AHW_AL_INC_AHW_AL_TEMP_H_

#include <stdint.h>
#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_ahw_al_common.h"

/**
 * @brief temperature sensor mode of operation enumeration
 */
typedef enum
{
    TEMP_SENSE_CONTINUOUS_CONVERSTION=0,        /*!< temperature sensor continuous converstion */
    TEMP_SENSE_SHUTDOWN_MODE=256,           /*!< temperature sensor shutdown mode */
    TEMP_SENSE_MODE_MAX
}temp_sensor_mode_t;

/**
 * @brief temperature sensor event output mode enumeration
 */
typedef enum
{
    TEMP_SENSE_COMPARATOR_EVENT_MODE=0x08,      /*!< temperature sensor comparison event mode */
    TEMP_SENSE_INTRUPT_EVENT_MODE=0x09,     /*!< temperature sensor interrupt event mode */
    TEMP_SENSE_EVENT_NONE=0x00
}temp_sensor_event_output_mode_t;

/**
 * @brief temperature sensor resolution enumeration
 */
typedef enum
{
    RES_0_5    = 0,                             /*!< resolution 0-5 */
    RES_0_25   = 1,                             /*!< resolution 0-25 */
    RES_0_125  = 2,                             /*!< resolution 0-125 */
    RES_0_0625 = 3                              /*!< resolution 0-625 */
}temp_sensor_res_t;

/**
 * @brief temperature sensor hysteresis enumeration
 */
typedef enum
{
    HYS_0_0  = 0,                                   /*!< hysteresis 0 */
    HYS_1_5  = 512,                             /*!< hysteresis 512 */
    HYS_3_0  = 1024,                                /*!< hysteresis 1024 */
    HYS_6_0  = 1536                             /*!< hysteresis 1536 */
}temp_sensor_hyst_t;

/**
 * @brief temperature sensor event_polarity enumeration
 */
typedef enum
{
    TEMP_SENSE_ACTIVE_HIGH=2,                   /*!< temperature sensor active high */
    TEMP_SENSE_ACTIVE_LOW=0                     /*!< temperature sensor active low */
}temp_sensor_event_polarity_t;

/**
 * @brief temperature sensor win_lock_bit enumeration
 */
typedef enum
{
    WIN_UNLOCK_0=0,                             /*!< win unlock */
    WIN_LOCK_1=1 //BIT_6(64)                    /*!< win lock */
}temp_sensor_win_lock_t;

/**
 * @brief temperature sensor crit_lock_bit enumeration
 */
typedef enum
{
    CRIT_UNLOCK_0=0,                            /*!< critical unlock */
    CRIT_LOCK_1=1                               /*!< critical lock */
}temp_sensor_crit_lock_t;

/**
 * @brief temperature sensor alarm_alert enumeration
 */
typedef enum
{
    TEMP_SENSE_TEMP_BOUNDARY_LIMIT_DEFAULT=0,       /*!< temperature boundary limit default */
    TEMP_SENSE_TEMP_BOUNDARY_LIMIT_ALARM=1          /*!< temperature boundary limit alarm */
}temp_sensor_alarm_alert_t;

/**
 * @brief temperature sensor device structure.
 */
typedef struct
{
    ahw_al_gen_info ahw_gen_info;
    uint8_t interrupt_clear;            /*!< intrupt_clear                  */
    uint8_t slave_address;              /*!< slave_address                  */
    uint16_t device_id;             /*!< device_id                      */
    uint16_t manufacture_id;            /*!< manufacture_id                 */
    float high_temp_threshold;          /*!< high_temp_threshold            */
    float low_temp_threshold;           /*!< low_temp_threshold             */
    float critical_temp_threshold;          /*!< critical_temp_threshold        */
    temp_sensor_mode_t mode_of_operation;       /*!< temp_sensor mode of operation  */
    temp_sensor_event_output_mode_t event_mode; /*!< event pin mode of operation    */
    temp_sensor_event_polarity_t polarity;      /*!< event polarity                 */
    temp_sensor_win_lock_t win_lock;        /*!< window lock bit enumeration    */
    temp_sensor_crit_lock_t crit_lock;      /*!< window lock bit enumeration    */
    temp_sensor_hyst_t hysteresis;          /*!< hysteresis enumeration         */
    temp_sensor_alarm_alert_t alarm_alert;      /*!< alarm_alert enumeration        */
    temp_sensor_res_t resolution;           /*!< resolution enumeration         */
}ahw_al_temp_sensor_hdl;

/**
 * @brief ahw_al_temp_sensor pointer type definition
 */
typedef ahw_al_temp_sensor_hdl ahw_al_temp_sensor_hdl_ptr;

/**
 * @brief API to initialize the temperature sensor.
 * @param[in] ht_arg : structure handle of Ahw Al temperature sensor handle.
 * @param[in] ahw_id : application hardware instance ID
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_init(ahw_al_temp_sensor_hdl* ht_arg, ahw_inst_id_t ahw_id);

/**
 * @brief API to de-Initialize the temperature sensor and configure.
 * @param[in] ht_arg : structure handle of Ahw Al temperature sensor handle.
 * @param[in] ahw_id : application hardware instance ID
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_deinit(ahw_al_temp_sensor_hdl* ht_arg, ahw_inst_id_t ahw_id);

/**
 * @brief API to get event status of temperature sensor
 * @param[in] ahw_al_hts : structure handle of Ahw Al temperature sensor handle.
 * @param[out] evnt_sts : event status of temperature sensor
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_get_evnt_sts(ahw_al_temp_sensor_hdl *ahw_al_hts, uint8_t* evnt_sts);

/**
 * @brief API to temperature sensor device configure.
 * @param[in] ahw_al_hts : structure handle of Ahw Al temperature sensor handle.
 * @retval hal_ret_sts - returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_config (ahw_al_temp_sensor_hdl *ahw_al_hts);

/**
 * @brief API to set the mode of operation
 * @param[in] ahw_al_hts        : structure handle of Ahw Al temperature sensor handle.
 * @param[in] mode: mode of operation cont or shut_down mode.
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_set_mode(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_mode_t mode);

/**
 * @brief API to clear the interrupt bit
 * @param[in] ahw_al_hts        : structure handle of Ahw Al temperature sensor handle.
 * @param[in] interrupt_clear   : interrupt_clear value.
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_intrupt_clear(ahw_al_temp_sensor_hdl *ahw_al_hts, uint8_t interrupt_clear);

/**
 * @brief API to set the event output pin
 * @param[in] ahw_al_hts    : structure handle of Ahw Al temperature sensor handle.
 * @param[in] event_mode    : event_mode set value
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_set_event_output_mode(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_event_output_mode_t event_mode);

/**
 * @brief API to set the event polarity
 * @param[in] ahw_al_hts    : structure handle of Ahw Al temperature sensor handle.
 * @param[in] polarity      : polarity set value
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_set_event_polarity(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_event_polarity_t polarity);

/**
 * @brief API to set the win_lock_bit
 * @param[in] ahw_al_hts : structure handle of Ahw Al temperature sensor handle.
 * @param[in] win_lock  : win_lock_bit set value
 * @retval hal_ret_sts  :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_set_win_lockbit(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_win_lock_t win_lock);

/**
 * @brief API to set the crit_lock_bit
 * @param[in] ahw_al_hts    : structure handle of Ahw Al temperature sensor handle.
 * @param[in] crit_lock : crit_lock_bit set value
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_set_crit_lockbit(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_crit_lock_t crit_lock);

/**
 * @brief API to set the temperature high threshold
 * @param[in] ahw_al_hts            : structure handle of Ahw Al temperature sensor handle.
 * @param[in] high_temp_threshold   : high_temp_threshold set value
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_set_temp_high_threshold (ahw_al_temp_sensor_hdl *ahw_al_hts, float high_temp_threshold);

/**
 * @brief API to set the temperature low threshold
 * @param[in] ahw_al_hts            : structure handle of Ahw Al temperature sensor handle.
 * @param[in] low_temp_threshold    : low_temp_threshold set value
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_set_temp_low_threshold (ahw_al_temp_sensor_hdl *ahw_al_hts, float low_temp_threshold);

/**
 * @brief API to set the temperature critical threshold
 * @param[in] ahw_al_hts                : structure handle of Ahw Al temperature sensor handle.
 * @param[in] critical_temp_threshold   : critical_temp_threshold set value
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_set_temp_critical_threshold (ahw_al_temp_sensor_hdl *ahw_al_hts, float critical_temp_threshold);

/**
 * @brief API to set the temperature hysteresis.
 * @param[in] ahw_al_hts        : structure handle of Ahw Al temperature sensor handle.
 * @param[in] hysteresis    : hysteresis
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_set_hysteresis(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_hyst_t hysteresis);

/**
 * @brief API to get the temperature hysteresis.
 * @param[in] ahw_al_hts        : structure handle of Ahw Al temperature sensor handle.
 * @param[out] hysteresis   : hysteresis of temperature sensor
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_get_hysteresis(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_hyst_t *hysteresis);

/**
 * @brief API to set the temperature hysteresis.
 * @param[in] ahw_al_hts        : structure handle of Ahw Al temperature sensor handle.
 * @param[in] resolution    : resolution to be set
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_set_resolution(ahw_al_temp_sensor_hdl *ahw_al_hts, temp_sensor_res_t resolution);

/**
 * @brief API to get the temperature resolution.
 * @param[in] ahw_al_hts        : structure handle of Ahw Al temperature sensor handle.
 * @param[out] res          : resolution of the temperature sensor
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_get_resolution(ahw_al_temp_sensor_hdl *ahw_al_hts,temp_sensor_res_t *res);

/**
 * @brief API to get the current temperature in celsius
 * @param[in] ahw_al_hts        : structure handle of Ahw Al temperature sensor handle.
 * @param[out] temperature  : temperature value in celsius
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts  ahw_al_temp_sensor_gettemperature(ahw_al_temp_sensor_hdl *ahw_al_hts,float *temperature);

/**
 * @brief API to get the temperature value in fahrenheit.
 * @param[in] ahw_al_hts        : structure handle of Ahw Al temperature sensor handle.
 * @param[out] temperature  : temperature value in fahrenheit.
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_get_fahrenheit(ahw_al_temp_sensor_hdl *ahw_al_hts,float* temperature);

/**
 * @brief API to get the temperature value in celsius.
 * @param[in] ahw_al_hts        : structure handle of Ahw Al temperature sensor handle.
 * @param[out] temperature  : temperature value in celsius.
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts ahw_al_temp_sensor_get_celsius(ahw_al_temp_sensor_hdl *ahw_al_hts,float* temperature);

/**
 * @brief API to read the manufacture ID.
 * @param[in] ahw_al_hts    : structure handle of Ahw Al temperature sensor handle.
 * @param[out] temperature  : temperature value in celsius.
 * @retval hal_ret_sts      :returns the success or error code
 */
hal_ret_sts  ahw_al_temp_sensor_read_manufacture_id(ahw_al_temp_sensor_hdl *ahw_al_hts,int16_t* temperature);

#endif /* HAL_DRIVER_FW_AHW_AL_DRIVER_API_AHW_AL_INC_AHW_AL_TEMP_H_ */

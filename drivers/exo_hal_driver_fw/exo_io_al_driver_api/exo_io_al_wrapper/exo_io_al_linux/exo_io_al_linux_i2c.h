/**
 * @file exo_io_al_linux_i2c.h
 *
 * @brief This file contains linux wrapper functions declarations for IO interface
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

#ifndef _IO_AL_LINUX_I2C_H_
#define _IO_AL_LINUX_I2_CH_

#include "exo_hal_common.h"
#include "exo_io_al_i2c_common.h"


/**
 * @brief IO-HAL I2C1 initialization function for linux
 * @param[in] ioal_hi2c1 - pointer to I2C1 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_i2c1_init(ioal_i2c_hdle *ioal_hi2c1);

/**
 * @brief IO-HAL I2C2 initialization function for linux
 * @param[in] ioal_hi2c2 - pointer to I2C2 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_i2c2_init(ioal_i2c_hdle *ioal_hi2c2);

/**
 * @brief IO-HAL I2C3 initialization function for linux
 * @param[in] ioal_hi2c3 - pointer to I2C3 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_i2c3_init(ioal_i2c_hdle *ioal_hi2c3);

/**
 * @brief IO-HAL I2C4 initialization function for linux
 * @param[in] ioal_hi2c4 - pointer to I2C4 instance
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_i2c4_init(ioal_i2c_hdle *ioal_hi2c4);

/**
 * @brief IO-HAL I2C transmit function for linux
 * @param[in] ioal_hi2c - pointer to I2C instance
 * @param[in] addr - address of the data
 * @param[in] pdata - pointer to a buffer
 * @param[in] size - size of the data
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_i2c_transmit(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout);

/**
 * @brief IO-HAL I2C receive function for linux
 * @param[in] ioal_hi2c - pointer to I2C instance
 * @param[in] addr - address of the data
 * @param[out]pdata - pointer to a buffer
 * @param[in] size - size of the data
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_linux_i2c_receive(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout);

/** IO HAL common I2C fucntion mapping **/
#define io_hal_common_i2c1_init 			io_hal_linux_i2c1_init
#define io_hal_common_i2c2_init 			io_hal_linux_i2c2_init
#define io_hal_common_i2c3_init 			io_hal_linux_i2c3_init
#define io_hal_common_i2c4_init 			io_hal_linux_i2c4_init
#define io_hal_common_i2c_transmit 			io_hal_linux_i2c_transmit
#define io_hal_common_i2c_receive 			io_hal_linux_i2c_receive


#endif

/**
 * @file exo_io_al_linux_i2c.c
 *
 * @brief This file contains linux wrapper functions for IO interface
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

#include <stdio.h>
#include <unistd.h>
#include "exo_io_al_linux_i2c.h"
#include "exo_hal_io_al_common.h"


/**
 * @brief IO-HAL I2C1 initialization function for linux
 */
hal_ret_sts io_hal_linux_i2c1_init(ioal_i2c_hdle *ioal_hi2c1)
{
    ioal_hi2c1->intf_gen_info.io_id=IOAL_INST_I2C1;
    printf("\n EXO I2C1 IO Vendor driver porting layer initialise");
    printf("\n EXO I2C1 IO Vendor driver initialise");
    usleep(100000);
    printf("\n EXO I2C1 IO Vendor driver initialisation completed successfully");
    printf("\n EXO I2C1 IO Vendor driver porting layer initialisation completed successfully");
    return HAL_SCS;
}

/**
 * @brief IO-HAL I2C2 initialization function for linux
 */
hal_ret_sts io_hal_linux_i2c2_init(ioal_i2c_hdle *ioal_hi2c2)
{
    ioal_hi2c2->intf_gen_info.io_id=IOAL_INST_I2C2;
    printf("\n EXO I2C2 IO Vendor driver porting layer initialise");
    printf("\n EXO I2C2 IO Vendor driver initialise");
    usleep(100000);
    printf("\n EXO I2C2 IO Vendor driver initialisation completed successfully");
    printf("\n EXO I2C2 IO Vendor driver porting layer initialisation completed successfully");
    return HAL_SCS;
}

/**
 * @brief IO-HAL I2C4 initialization function for linux
 */
hal_ret_sts io_hal_linux_i2c4_init(ioal_i2c_hdle *ioal_hi2c4)
{
    ioal_hi2c4->intf_gen_info.io_id=IOAL_INST_I2C4;
    printf("\n EXO I2C4 IO Vendor driver porting layer initialise");
    printf("\n EXO I2C4 IO Vendor driver initialise");
    usleep(100000);
    printf("\n EXO I2C4 IO Vendor driver initialisation completed successfully");
    printf("\n EXO I2C4 IO Vendor driver porting layer initialisation completed successfully");
    return HAL_SCS;
}

/**
 * @brief IO-HAL I2C3 initialization function for linux
 */
hal_ret_sts io_hal_linux_i2c3_init(ioal_i2c_hdle *ioal_hi2c3)
{
    ioal_hi2c3->intf_gen_info.io_id=IOAL_INST_I2C3;
    printf("\n EXO I2C4 IO Vendor driver porting layer initialise");
    printf("\n EXO I2C4 IO Vendor driver initialise");
    usleep(100000);
    printf("\n EXO I2C4 IO Vendor driver initialisation completed successfully");
    printf("\n EXO I2C4 IO Vendor driver porting layer initialisation completed successfully");
    return HAL_SCS;
}

/**
 * @brief IO-HAL I2C transmit function for linux
 */
hal_ret_sts io_hal_linux_i2c_transmit(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout)
{
    return HAL_SCS;
}

/**
 * @brief IO-HAL I2C receive function for linux
 */
hal_ret_sts io_hal_linux_i2c_receive(ioal_i2c_hdle  *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout)
{
    return HAL_SCS;
}

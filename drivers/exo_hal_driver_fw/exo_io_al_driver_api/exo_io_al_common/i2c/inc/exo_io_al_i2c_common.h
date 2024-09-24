/**
 * @file exo_io_al_i2c_common.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for I2C interface
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

#ifndef _IO_HAL_I2C_COMMON_H_
#define _IO_HAL_I2C_COMMON_H_

#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_hal_io_al_intr.h"
#include "exo_ahw_al_common.h"

#define I2C_INTF_ENB

/**
 * @brief IO-HAl I2C interface control block handle structure definition
 */
typedef struct _ioal_i2c_hdle
{
    ioal_intf_gen_info intf_gen_info;                        ///< Hold general information of interface
    void (*i2c_mst_tx_cplt_cb)(struct _ioal_i2c_hdle *hi2c);    ///< Hold Fn address for I2C Master Tx Transfer completed callback ID
    void (*i2c_mst_rx_cplt_cb)(struct _ioal_i2c_hdle *hi2c);    ///< Hold Fn address for I2C Master Rx Transfer completed callback ID
    void (*i2c_abort_cplt_cb)(struct _ioal_i2c_hdle *hi2c);     ///< Hold Fn address for Abort complete event
    void (*i2c_listen_cplt_cb)(struct _ioal_i2c_hdle *hi2c);    ///< Hold Fn address for Listen complete event
    void (*i2c_error_cb)(struct _ioal_i2c_hdle *hi2c);          ///< Hold Fn address for error event
    uint16 cb_context;                   ///< App registered callbacks execution context
    i2c_cb_lst app_callbacks;            ///< App registered callbacks list 
}ioal_i2c_hdle;

/**
 * @brief  This function initializes the control block memory
 * and do the basic configurations for I2C
 *
 * @retval HAL status
 */
hal_ret_sts io_hal_i2c_init(void);
/**
 * @brief  This function initializes I2C1 callback events
 * @param[in]  hi2c1 - hi2c1 pointer to a hi2c1 structure that contains
 *          the configuration information for I2C module
 * @retval HAL status
 */
void io_hal_i2c1_cb_init(ioal_i2c_hdle *hi2c1);
/**
 * @brief  This function initializes I2C2 callback events
 * @param[in]  hi2c2 - hi2c2 pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for I2C module
 * @retval HAL status
 */
void io_hal_i2c2_cb_init(ioal_i2c_hdle *hi2c2);
/**
 * @brief  This function initializes I2C2 callback events
 * @param[in]  hi2c3 - hi2c3 pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for I2C module
 * @retval HAL status
 */
void io_hal_i2c3_cb_init(ioal_i2c_hdle *hi2c3);
/**
 * @brief  This function initializes I2C4 callback events
 * @param[in]  hi2c4 - hi2c4 pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for I2C module
 * @retval HAL status
 */
void io_hal_i2c4_cb_init(ioal_i2c_hdle *hi2c4);
/**
 * @brief  This function transmits data in master mode..
 * @param[in]  hi2c - hi2c pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for QSPI module
 * @param[in]  addr - Address of the data
 * @param[in]  pdata - Pointer to data buffer
 * @param[in]  size - size of the data to be sent
 * @param[in]  timeout - Timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_i2c_transmit(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief  This function receives data in master mode.
 * @param[in]  hi2c - hi2c pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for QSPI module
 * @param[in]  addr - Address of the data
 * @param[out] pdata - Pointer to data buffer
 * @param[in]  size - size of the data to be sent
 * @param[in]  timeout - Timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_i2c_receive(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief  This function transmit data in master mode with interrupt
 * @param[in]  hi2c - hi2c pointer to a ioal_i2c_hdle structure that contains
 *             the configuration information for QSPI module
 * @param[in]  addr - Address of the data
 * @param[in]  pdata - Pointer to data buffer
 * @param[in]  size - Amount of data to be sent
 * @param[in]  timeout - Timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_i2c_transmit_it(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size);
/**
 * @brief  This function receive data in master mode interrupt
 * @param[in]  hi2c - hi2c pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for QSPI module
 * @param[in]  addr - Address of the data
 * @param[out] pdata - Pointer to data buffer
 * @param[in]  size - Amount of data to be sent
 * @param[in]  timeout - Timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_i2c_receive_it(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size);
/**
 * @brief  This function transmit data in master mode with DMA
 * @param[in]  hi2c - hi2c pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for QSPI module
 * @param[in]  addr - Address of the data
 * @param[in]  pdata - Pointer to data buffer
 * @param[in]  size - Amount of data to be sent
 * @param[in]  timeout - Timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_i2c_transmit_dma(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size);
/**
 * @brief  This function receive data in master mode with DMA
 * @param[in]  hi2c - hi2c pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for QSPI module
 * @param[in]  addr - Address of the data
 * @param[out] pdata - Pointer to data buffer
 * @param[in]  size - Amount of data to be sent
 * @param[in]  timeout - Timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_i2c_receive_dma(ioal_i2c_hdle *hi2c, uint16 addr, uint8 *pdata, uint16 size);
/**
 * @brief  This function checks if device is ready for communication.
 * @param[in]  hi2c - hi2c pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for QSPI module
 * @param[in]  addr - Address of the data
 * @param[in]  trials - Number of trials
 * @param[in]  timeout - Timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_i2c_is_device_ready(ioal_i2c_hdle *hi2c, uint16 addr, uint32 trials, uint32 timeout);
/**
 * @brief  This function enable the address in listen mode with Interrupt.
 * @param[in]  hi2c - hi2c pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for QSPI module
 * @retval HAL status
 */
hal_ret_sts io_hal_i2c_enablelisten_it(ioal_i2c_hdle *hi2c);
/**
 * @brief  This function abort a master I2C with Interrupt.
 * @param[in]  hi2c - hi2c pointer to a ioal_i2c_hdle structure that contains
 *          the configuration information for QSPI module
 * @param[in]  addr - Address of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_i2c_abort_it(ioal_i2c_hdle *hi2c, uint16 addr);


#ifndef LINUX_TEMP_PORT

/**
 * @brief Check I2C 1 dummy
 *
 * @param[in] hi2c : pointer to i2c handle
 */
void check_i2c1_dummy(ioal_i2c_hdle *hi2c);
/**
 * @brief Check I2C 2 dummy
 *
 * @param[in] hi2c : pointer to i2c handle
 */
void check_i2c2_dummy(ioal_i2c_hdle *hi2c);
/**
 * @brief Check I2C 3 dummy
 *
 * @param[in] hi2c : pointer to i2c handle
 */
void check_i2c3_dummy(ioal_i2c_hdle *hi2c);
/**
 * @brief Check I2C 4 dummy
 *
 * @param[in] hi2c : pointer to i2c handle
 */
void check_i2c4_dummy(ioal_i2c_hdle *hi2c);

#else
/**
 * @brief This is I2C interface dummy function for linux
 *
 * @param[in] hi2c : pointer to i2c handle
 */
void linux_i2c_dummy_fn(struct _ioal_i2c_hdle *hi2c);

#endif

#endif /* _IO_HAL_I2C_COMMON_H_ */

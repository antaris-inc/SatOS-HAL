/**
 * @file exo_io_al_stm32f7xx_i2c.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for I2C interface
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

#ifndef IO_AL_STM32F7xx_I2C_H
#define IO_AL_STM32F7xx_I2C_H

#include "exo_types.h"
#include "exo_hal_common.h"
#include "exo_io_al_common.h"
#include "exo_io_al_i2c_common.h"
#include "exo_io_al_stm32f7xx_common.h"

/**
 * @brief  VDP layer I2C callback ID
 */
typedef enum
{
    IOHAL_STM32_I2C_MASTER_TX_CPLT_CB_ID      = 0x00U,    /*!< I2C Master Tx Transfer completed callback ID */
    IOHAL_STM32_I2C_MASTER_RX_CPLT_CB_ID      = 0x01U,    /*!< I2C Master Rx Transfer completed callback ID */
    IOHAL_STM32_I2C_LISTEN_CPLT_CB_ID         = 0x02U,    /*!< I2C Listen Complete callback ID */
    IOHAL_STM32_I2C_ABORT_CB_ID               = 0x03U,    /*!< I2C Abort callback ID */
    IOHAL_STM32_I2C_ERROR_CB_ID               = 0x04U,    /*!< I2C Error callback ID */

} iohal_stm32_i2c_cbid;

/**
 * @brief  This function initializes the control block memory and do the basic
 * 		configurations I2C1
 * @param[in]  ioal_hi2c1 -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C1 module.
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c1_init(ioal_i2c_hdle *ioal_hi2c1);
/**
 * @brief  This function initializes the control block memory and do the basic
 * 		configurations I2C2
 * @param[in]  ioal_hi2c2 -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C2 module.
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c2_init(ioal_i2c_hdle *ioal_hi2c2);
/**
 * @brief  This function initializes the control block memory and do the basic
 * 		configurations I2C3
 * @param[in]  ioal_hi2c3 -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C3 module.
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c3_init(ioal_i2c_hdle *ioal_hi2c3);
/**
 * @brief  This function initializes the control block memory and do the basic
 * 		configurations I2C4
 * @param[in]  ioal_hi2c4 -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C4 module.
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c4_init(ioal_i2c_hdle *ioal_hi2c4);
/**
 * @brief  This function transmits data in master mode
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @param[in]  addr - Address of the data
 * @param[in]  pdata - Pointer to data buffer
 * @param[in]  size - size of the data
 * @param[in]  timeout - Timeout duration
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_transmit(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief  This function receives data in master mode
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @param[in]  addr - Address of the data
 * @param[out] pdata - Pointer to data buffer
 * @param[in]  size - size of the data
 * @param[in]  timeout - Timeout duration
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_receive(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief  This function transmit data in master mode with Interrupt
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @param[in]  addr - Address of the data
 * @param[in]  pdata - Pointer to data buffer
 * @param[in]  size - size of the data
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_transmit_it(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size);
/**
 * @brief  This function receive data in master mode with Interrupt
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @param[in]  addr - Address of the data
 * @param[out] pdata - Pointer to data buffer
 * @param[in]  size - size of the data
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_receive_it(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size);
/**
 * @brief  This function transmit data in master mode with DMA
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @param[in]  addr - Address of the data
 * @param[in]  pdata - Pointer to data buffer
 * @param[in]  size - size of the data
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_transmit_dma(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size);
/**
 * @brief  This function receive data in master mode with DMA
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @param[in]  addr - Address of the data
 * @param[out] pdata - Pointer to data buffer
 * @param[in]  size - size of the data
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_receive_dma(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size);
/**
 * @brief  This function checks if device is ready for communication.
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @param[in]  addr - Address of the data
 * @param[in]  trials - Number of trials
 * @param[in]  timeout - Timeout duration
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_is_device_ready(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint32 trials, uint32 timeout);
/**
 * @brief  This function enable the address listen mode with Interrupt.
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_enablelisten_it(ioal_i2c_hdle *ioal_hi2c);
/**
 * @brief  This function disable the Address listen mode with Interrupt.
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_disablelisten_it(ioal_i2c_hdle *ioal_hi2c);
/**
 * @brief   This function abort a master I2C  with Interrupt.
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @param[in]  addr - Address of the data
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_abort_it(ioal_i2c_hdle *ioal_hi2c, uint16 addr);
/**
 * @brief   This function  register a I2C Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @param[in]  cbid - ID of the callback event
 * @retval HAL status.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_reg_cb(ioal_i2c_hdle *ioal_hi2c, iohal_stm32_i2c_cbid cbid);

/**
 * @brief  This function is a I2C1 initialization function
 * @param[in]  ioal_hi2c1 -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C1 module.
 * @retval HAL status.
 */
void MX_I2C1_Init(ioal_i2c_hdle *ioal_hi2c1);
/**
 * @brief  This function is a I2C2 initialization function
 * @param[in]  ioal_hi2c2 -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C2 module.
 * @retval HAL status.
 */
void MX_I2C2_Init(ioal_i2c_hdle *ioal_hi2c2);
/**
 * @brief  This function is a I2C3 initialization function
 * @param[in]  ioal_hi2c3 -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C3 module.
 * @retval HAL status.
 */
void MX_I2C3_Init(ioal_i2c_hdle *ioal_hi2c3);
/**
 * @brief  This function is a I2C4 initialization function
 * @param[in]  ioal_hi2c4 -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C4 module.
 * @retval HAL status.
 */
void MX_I2C4_Init(ioal_i2c_hdle *ioal_hi2c4);


/* API Mapping */
#define io_hal_common_i2c1_init 			io_hal_stm32f7xx_i2c1_init
#define io_hal_common_i2c2_init 			io_hal_stm32f7xx_i2c2_init
#define io_hal_common_i2c3_init 			io_hal_stm32f7xx_i2c3_init
#define io_hal_common_i2c4_init 			io_hal_stm32f7xx_i2c4_init
#define io_hal_common_i2c_transmit 			io_hal_stm32f7xx_i2c_transmit
#define io_hal_common_i2c_receive 			io_hal_stm32f7xx_i2c_receive
#define io_hal_common_i2c_transmit_it 		io_hal_stm32f7xx_i2c_transmit_it
#define io_hal_common_i2c_receive_it 		io_hal_stm32f7xx_i2c_receive_it
#define io_hal_common_i2c_transmit_dma 		io_hal_stm32f7xx_i2c_transmit_dma
#define io_hal_common_i2c_receive_dma 		io_hal_stm32f7xx_i2c_receive_dma
#define io_hal_common_i2c_is_device_ready 	io_hal_stm32f7xx_i2c_is_device_ready
#define io_hal_common_i2c_enablelisten_it 	io_hal_stm32f7xx_i2c_enablelisten_it
#define io_hal_common_i2c_disablelisten_it 	io_hal_stm32f7xx_i2c_disablelisten_it
#define io_hal_common_i2c_abort_it 			io_hal_stm32f7xx_i2c_abort_it
#define io_hal_common_i2c_reg_cb			io_hal_stm32f7xx_i2c_reg_cb

#endif

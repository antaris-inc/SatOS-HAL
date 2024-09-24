/**
 * @file exo_io_al_eth_common.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for ETHERNET interface
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

#ifndef DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_COMMON_ETHERNET_INC_EXO_IO_AL_ETH_COMMON_H_
#define DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_COMMON_ETHERNET_INC_EXO_IO_AL_ETH_COMMON_H_

#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include <stdint.h>

//#define ETH_INTF_ENB

/**
 * @brief IO-HAl Ethernet interface control block handle structure definition
 *
 */
typedef struct _ioal_eth_hdl
{
    ioal_intf_gen_info intf_gen_info; 							 /*!< Hold general information of interface */
    void    (* tx_cpltCallback) (struct _ioal_eth_hdl * heth);   /*!< ETH Tx Complete Callback   			*/
    void    (* rx_CpltCallback) (struct _ioal_eth_hdl * heth);   /*!< ETH Rx  Complete Callback   			*/
    void    (* dma_error_cb)    (struct _ioal_eth_hdl * heth);   /*!< DMA Error Callback      				*/
}ioal_eth_hdl;

/**
 * @brief  This function initializes the ethernet Callback.
 * @param[in]  ioal_heth - ioal_heth pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval HAL status
 */
void io_hal_eth_cb_init(ioal_eth_hdl *ioal_heth);
/**
 * @brief  This function initializes the ethernet MAC and DMA according to default
 *         parameters.
 * @retval HAL status
 */
hal_ret_sts io_hal_eth_init(void);
/**
 * @brief  This function de-Initializes the ETH peripheral.
 * @param[in]  ioal_heth - ioal_heth pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval HAL status
 */
hal_ret_sts io_hal_eth_deinit(ioal_eth_hdl*ioal_heth);
/**
 * @brief  This function sends an ethernet frame.
 * @param[in]  ioal_heth - ioal_heth pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @param  framelength - FrameLength Amount of data to be sent
 * @retval hal_ret_sts
 */
#ifndef LINUX_TEMP_PORT
hal_ret_sts io_hal_eth_tf(ioal_eth_hdl*ioal_heth, uint32_t framelength);
/**
 * @brief  This function reads/get the ethernet frame.
 * @param[in]  ioal_heth - ioal_heth pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_eth_get_rf(ioal_eth_hdl*ioal_heth);
/**
 * @brief  This function gets the received frame in interrupt mode.
 * @param[in]  ioal_heth - ioal_heth pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_eth_getrf_it(ioal_eth_hdl*ioal_heth);
/**
 * @brief  This function enables ethernet MAC and DMA reception/transmission
 * @param[in]  ioal_heth - ioal_heth pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_eth_start(ioal_eth_hdl*ioal_heth);
/**
 * @brief  This function stop ethernet MAC and DMA reception/transmission
 * @param[in]  ioal_heth - ioal_heth pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_eth_stop(ioal_eth_hdl*ioal_heth);


/**
 * @brief  This function reads a PHY register
 * @param[in] ioal_heth - ioal_heth pointer to a ETH_HandleTypeDef structure that contains
 *         the configuration information for ETHERNET module
 * @param[in] phy_reg - PHYReg PHY register address, is the index of one of the 32 PHY register.
 *                This parameter can be one of the following values:
 *                   PHY_BCR: Transceiver Basic Control Register,
 *                   PHY_BSR: Transceiver Basic Status Register.
 *                   More PHY register could be read depending on the used PHY
 * @param[out]reg_value - RegValue PHY register value
 * @retval HAL status
 */
hal_ret_sts io_hal_eth_read_phy_reg(ioal_eth_hdl*ioal_heth, uint16_t phy_reg, uint32_t *reg_value);
/**
 * @brief  This function writes to a PHY register.
 * @param[in]  ioal_heth - ioal_heth pointer to a ETH_HandleTypeDef structure that contains
 *             the configuration information for ETHERNET module
 * @param[in]  phy_reg - PHYReg PHY register address, is the index of one of the 32 PHY register.
 *             This parameter can be one of the following values:
 *             PHY_BCR: Transceiver Control Register.
 *             More PHY register could be written depending on the used PHY
 * @param[in]  reg_value - RegValue the value to write
 * @retval HAL status
 */
hal_ret_sts io_hal_eth_write_phy_reg(ioal_eth_hdl*ioal_heth, uint16_t phy_reg, uint32_t reg_value);
#endif

#ifndef LINUX_TEMP_PORT
/**
 * @brief Check Ethernet dummy
 *
 * @param[in] ioal_eth : pointer to ethernet handler
 */
void check_eth_dummy(ioal_eth_hdl *ioal_heth);
#else
/**
 * @brief This is ethernet interface dummy function for linux
 *
 * @param[in] ioal_eth : pointer to ethernet handler
 */
void linux_eth_dummy_fn(struct _ioal_eth_hdl *heth);
#endif

#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_COMMON_ETHERNET_INC_EXO_IO_AL_ETH_COMMON_H_ */

/**
 * @file exo_io_al_stm32f7xx_eth.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for ETHERNET interface
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

#ifndef DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_WRAPPER_EXO_IO_AL_STM32F7XX_ETHERNET_INC_EXO_IO_AL_STM32F7XX_ETH_H_
#define DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_WRAPPER_EXO_IO_AL_STM32F7XX_ETHERNET_INC_EXO_IO_AL_STM32F7XX_ETH_H_

#include "exo_types.h"
#include "exo_hal_common.h"
#include "exo_io_al_common.h"
#include "exo_io_al_eth_common.h"
#include "exo_io_al_stm32f7xx_common.h"




/**
 * @brief  HAL ETH Callback pointer definition
 */
typedef  void (*piohal_stm32_eth_cb_id)(ioal_eth_hdl * heth);

/**
 * @brief  ETH Callback ID enumeration definition
 */
typedef enum
{
    IOHAL_ETH_TX_COMPLETE_CB_ID        = 0x02U,    /*!< ETH Tx Complete Callback ID        */
    IOHAL_ETH_RX_COMPLETE_CB_ID        = 0x03U,    /*!< ETH Rx Complete Callback ID        */
    IOHAL_ETH_DMA_ERROR_CB_ID          = 0x04U,    /*!< ETH DMA Error Callback ID          */

}iohal_stm32_eth_cb_id;

/*
   ===============================================================================
##### Ethernet IO Abstraction function prototype #####
===============================================================================  */

/**
 * @brief  This function initializes the Ethernet MAC and DMA according to default
 *         parameters.
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_eth_init(ioal_eth_hdl* ioal_hether);
/**
 * @brief  This function de-Initializes the ETH peripheral.
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_eth_deinit(ioal_eth_hdl* ioal_hether);

/*
   ===============================================================================
##### Callback Register/Unregister functions #####
===============================================================================  */
/**
 * @brief  This function register a User ETH Callback
 *         To be used instead of the weak predefined callback
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @param[in] cb_id - ID of the callback to be registered
 * @retval status
 */

hal_ret_sts io_hal_stm32f7xx_eth_reg_cb(ioal_eth_hdl* ioal_hether, iohal_stm32_eth_cb_id cb_id);
/**
 * @brief  This function unregister an ETH Callback
 *         ETH callabck is redirected to the weak predefined callback
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @param[in] cb_id - ID of the callback to be unregistered
 * @retval status
 */
hal_ret_sts io_hal_stm32f7xx_eth_unreg_cb(ioal_eth_hdl* ioal_hether, iohal_stm32_eth_cb_id cb_id);

/*
   ===============================================================================
##### IO operation functions #####
===============================================================================  */
/**
 * @brief  This function sends an Ethernet frame.
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @param[in]  framelength - Amount of data to be sent
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_stm32f7xx_eth_tf(ioal_eth_hdl* ioal_hether, uint32_t framelength);
/**
 * @brief  This function checks for received frames.
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_stm32f7xx_eth_get_rf(ioal_eth_hdl* ioal_hether);


/*
   ===============================================================================
##### Communication with PHY functions#####
===============================================================================  */

/**
 * @brief  This function reads a PHY register
 * @param[in]  ioal_hether - ioal_hether pointer to a ETH_HandleTypeDef structure that contains
 *         the configuration information for ETHERNET module
 * @param[in] phy_reg - PHY register address, is the index of one of the 32 PHY register.
 * @param[out]reg_value - register value to be read
 * @retval HAL status
 */
hal_ret_sts  io_hal_stm32f7xx_eth_read_phy_reg(ioal_eth_hdl* ioal_hether, uint16_t phy_reg, uint32_t *reg_value);
/**
 * @brief  This function writes to a PHY register.
 * @param[in]  ioal_hether - ioal_hether pointer to a ETH_HandleTypeDef structure that contains
 *         the configuration information for ETHERNET module
 * @param[in]  phy_reg - PHY register address, is the index of one of the 32 PHY register.
 * @param[in]  reg_value -  value to write
 * @retval HAL status
 */
hal_ret_sts  io_hal_stm32f7xx_eth_write_phy_reg(ioal_eth_hdl* ioal_hether, uint16_t phy_reg, uint32_t reg_value);

/*
   ===============================================================================
##### Non-Blocking mode: Interrupt #####
===============================================================================  */

/**
 * @brief  This function gets the received frame in interrupt mode.
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_stm32f7xx_eth_getrf_it(ioal_eth_hdl* ioal_hether);

/*
   ===============================================================================
##### Callback in non blocking modes (Interrupt) #####
===============================================================================  */


/*
   ===============================================================================
##### Peripheral Control functions #####
===============================================================================  */

/**
 * @brief  This function enables Ethernet MAC and DMA reception/transmission
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_stm32f7xx_eth_start(ioal_eth_hdl* ioal_hether);
/**
 * @brief  This function stop Ethernet MAC and DMA reception/transmission
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_stm32f7xx_eth_stop(ioal_eth_hdl* ioal_hether);

/*
   ===============================================================================
##### Peripheral State functions #####
===============================================================================  */


/**
 * @brief This function configure the ETHERNET parameters
 * @retval No return
 */
void MX_Eth_Init(void);
/*
   ===============================================================================
##### API Mapping #####
===============================================================================  */

#define io_hal_common_eth_init					io_hal_stm32f7xx_eth_init
#define io_hal_common_eth_deinit				io_hal_stm32f7xx_eth_deinit
#define io_hal_common_eth_tf					io_hal_stm32f7xx_eth_tf
#define io_hal_common_eth_get_rf				io_hal_stm32f7xx_eth_get_rf
#define io_hal_common_eth_getrf_it				io_hal_stm32f7xx_eth_getrf_it
#define io_hal_common_eth_start				    io_hal_stm32f7xx_eth_start
#define io_hal_common_eth_stop					io_hal_stm32f7xx_eth_stop
#define io_hal_common_eth_get_state				io_hal_stm32f7xx_eth_get_state
#define io_hal_common_eth_reg_cb                io_hal_stm32f7xx_eth_reg_cb
#define io_hal_common_eth_dmatx_desclist_init	io_hal_stm32f7xx_eth_dmatx_desclist_init
#define io_hal_common_eth_dmarx_desclist_init	io_hal_stm32f7xx_eth_dmarx_desclist_init
#define io_hal_common_eth_config_mac			io_hal_stm32f7xx_eth_config_mac
#define io_hal_common_eth_config_dma			io_hal_stm32f7xx_eth_config_dma
#define	io_hal_common_eth_read_phy_reg			io_hal_stm32f7xx_eth_read_phy_reg
#define io_hal_common_eth_write_phy_reg			io_hal_stm32f7xx_eth_write_phy_reg



#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_IO_AL_DRIVER_API_EXO_IO_AL_WRAPPER_EXO_IO_AL_STM32F7XX_ETHERNET_INC_EXO_IO_AL_STM32F7XX_ETH_H_ */

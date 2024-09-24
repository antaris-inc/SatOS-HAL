/**
 * @file exo_io_al_eth_common.c
 *
 * @brief This file contains abstracted function definition for ETHERNET interface
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
#include "exo_io_al_eth_common.h"
#include "exo_hal_io_al_common.h"
#ifndef LINUX_TEMP_PORT
#include "exo_io_al_stm32f7xx_eth.h"
#else
#include "exo_io_al_linux_ethernet.h"
#endif

#ifndef LINUX_TEMP_PORT

#define ETH_TX_CPLT_CB check_eth_dummy									///< ETH TX complete callback event
#define ETH_RX_CPLT_CB check_eth_dummy									///< ETH RX complete callback event
#define ETH_ERROR_CB check_eth_dummy									///< ETH error callback event
#else
#define ETH_TX_CPLT_CB linux_eth_dummy_fn       							///< ETH TX complete callback event
#define ETH_RX_CPLT_CB linux_eth_dummy_fn									///< ETH RX complete callback event
#define ETH_ERROR_CB linux_eth_dummy_fn										///< ETH error callback event

#endif


extern void *intf_inst_hdle_ptr[MAX_IO_INST_ID];

ioal_eth_hdl ioal_heth;

/**
 * @brief  This API initializes the ethernet according to default
 *         parameters.
 */
hal_ret_sts io_hal_eth_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL Ethernet Initialize");
    usleep(100000);
#endif
    hal_ret_sts sts;
    if(HAL_SCS == io_hal_common_eth_init(&ioal_heth))
    {
        intf_inst_hdle_ptr[IOAL_INST_ETHERNET1] = &ioal_heth;

    }
    else
    {
        sts = HAL_IO_INIT_ERR;
    }
#ifdef LINUX_TEMP_PORT
    printf("\n EXO IO AL I2C InitialiZation completed successfully");
#endif
    return sts;
}

/**
 * @brief  This API initializes the ethernet callback according to default
 *         parameters.
 */
void io_hal_eth_cb_init(ioal_eth_hdl *heth)
{
    heth->tx_cpltCallback = ETH_TX_CPLT_CB;
    heth->rx_CpltCallback = ETH_RX_CPLT_CB;
    heth->dma_error_cb    = ETH_ERROR_CB;

#ifndef LINUX_TEMP_PORT
    io_hal_common_eth_reg_cb(heth, IOHAL_ETH_TX_COMPLETE_CB_ID);
    io_hal_common_eth_reg_cb(heth, IOHAL_ETH_RX_COMPLETE_CB_ID);
    io_hal_common_eth_reg_cb(heth, IOHAL_ETH_DMA_ERROR_CB_ID);
#endif
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief  This API de-Initializes the ethernet
 */
hal_ret_sts io_hal_eth_deinit(ioal_eth_hdl* ioal_heth)
{
    hal_ret_sts sts;
    if(HAL_SCS == io_hal_common_eth_deinit(ioal_heth))
    {
        sts =HAL_SCS;
    }
    else
    {
        sts = HAL_IO_INIT_ERR;
    }
    return sts;
}

/**
 * @brief This API sends an ethernet frame.
 */
hal_ret_sts io_hal_eth_tf(ioal_eth_hdl* ioal_heth, uint32_t framelength)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    ioal_heth->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_eth_tf(ioal_heth,framelength))
    {
        ret_sts = HAL_SCS;
        ioal_heth->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
        ioal_heth->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API reads/get the ethernet frame.
 */
hal_ret_sts io_hal_eth_get_rf(ioal_eth_hdl* ioal_heth)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    ioal_heth->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS == io_hal_common_eth_get_rf(ioal_heth))
    {
        ret_sts = HAL_SCS;
        ioal_heth->intf_gen_info.state = IO_FREE_STATE;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
        ioal_heth->intf_gen_info.state = IO_FREE_STATE;
    }
    return ret_sts;
}

/**
 * @brief This API get tthe received frame in interrupt mode.
 */
hal_ret_sts io_hal_eth_getrf_it(ioal_eth_hdl* ioal_heth)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    ioal_heth->intf_gen_info.state = IO_BUSY_STATE;
    if(HAL_SCS ==io_hal_common_eth_getrf_it(ioal_heth))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_RX_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API enables ethernet MAC and DMA reception/transmission.
 */
hal_ret_sts io_hal_eth_start(ioal_eth_hdl* ioal_heth)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_eth_start(ioal_heth))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API stop ethernet MAC and DMA reception/transmission.
 */
hal_ret_sts io_hal_eth_stop(ioal_eth_hdl* ioal_heth)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS == io_hal_common_eth_stop(ioal_heth))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}


/**
 * @brief This API reads a PHY register
 */
hal_ret_sts io_hal_eth_read_phy_reg(ioal_eth_hdl* ioal_heth, uint16_t phy_reg, uint32_t *reg_value)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS ==io_hal_common_eth_read_phy_reg(ioal_heth,phy_reg,reg_value))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API writes to a PHY register
 */
hal_ret_sts io_hal_eth_write_phy_reg(ioal_eth_hdl* ioal_heth, uint16_t phy_reg, uint32_t reg_value)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    if(HAL_SCS ==io_hal_common_eth_write_phy_reg(ioal_heth,phy_reg,reg_value))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_TX_ERR;
    }
    return ret_sts;
}

#endif


#ifndef LINUX_TEMP_PORT
/**
 * @brief Check Ethernet dummy
 */
void check_eth_dummy(ioal_eth_hdl *ioal_heth)
{
    return;
}

#else

/**
 * @brief This is ethernet interface dummy function for linux
 */
void linux_eth_dummy_fn(struct _ioal_eth_hdl *heth)
{
}

#endif

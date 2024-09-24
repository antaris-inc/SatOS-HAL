/**
 * @file exo_io_al_stm32f7xx_eth.c
 *
 * @brief This file contains wrapper function definition for ETHERNET interface
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

#include "exo_io_al_stm32f7xx_eth.h"

#ifndef LINUX_TEMP_PORT
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_eth.h"
#endif

extern ETH_HandleTypeDef heth; ///< Ethernet handler
extern struct netif gnetif; ///< Netif
typedef HAL_ETH_StateTypeDef ioal_eth_state; ///< IOAL Ethernet state

/**
 * @brief  This function initializes the DMA Tx descriptors in chain mode.
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @param[in]  dmatxdesctab - Pointer to the first Tx desc list
 * @param[in]  txbuff  - Pointer to the first TxBuffer list
 * @param[in]  txbuffcount - Number of the used Tx desc in the list
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_eth_dmatx_desclist_init(ioal_eth_hdl* ioal_hether, ETH_DMADescTypeDef *dmatxdesctab, uint8_t* txbuff, uint32_t txbuffcount);
/**
 * @brief  This function initializes the DMA Rx descriptors in chain mode.
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @param[out] dmarxdesctab - Pointer to the first Rx desc list
 * @param[out] rxBuff - Pointer to the first RxBuffer list
 * @param[in]  rxBuffCount - Number of the used Rx desc in the list
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_eth_dmarx_desclist_init(ioal_eth_hdl* ioal_hether, ETH_DMADescTypeDef *dmarxdesctab, uint8_t *rxbuff, uint32_t rxbuffcount);

/**
 * @brief  This function Tx transfer completed callbacks.
 * @param[in]  hether - hether pointer to a ETH_HandleTypeDef structure that contains
 *         the configuration information for ETHERNET module
 * @retval None
 */
void io_hal_stm32f7xx_eth_tx_cmplt_cb(ETH_HandleTypeDef *hether);
/**
 * @brief  This function Rx transfer completed callbacks.
 * @param[in]  hether - hether pointer to a ETH_HandleTypeDef structure that contains
 *         the configuration information for ETHERNET module
 * @retval None
 */
void io_hal_stm32f7xx_eth_rx_cmblt_cb(ETH_HandleTypeDef *hether);
/**
 * @brief  This function ethernet transfer error callbacks
 * @param[in]  hether - hether pointer to a ETH_HandleTypeDef structure that contains
 *         the configuration information for ETHERNET module
 * @retval None
 */
void io_hal_stm32f7xx_eth_error_cb(ETH_HandleTypeDef *hether);



/**
 * @brief  This function set ETH MAC Configuration.
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @param[in]  mac_cfg - pointer points to MAC Configuration structure
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_stm32f7xx_eth_config_mac(ioal_eth_hdl* ioal_hether,ETH_MACConfigTypeDef *mac_cfg);
/**
 * @brief  This function sets ETH DMA Configuration.
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @param[in]  dma_cfg - pointer points to DMA Configuration structure
 * @retval hal_ret_sts
 */
hal_ret_sts io_hal_stm32f7xx_eth_config_dma(ioal_eth_hdl* ioal_hether, ETH_DMAConfigTypeDef *dma_cfg);


/**
 * @brief  This function return the ETH HAL state
 * @param[in]  ioal_hether - ioal_hether pointer to a ioal_eth_hdl structure that contains
 *         the configuration information for ETHERNET module
 * @retval hal_ret_sts
 */
ioal_eth_state io_hal_stm32f7xx_eth_get_state(ioal_eth_hdl* ioal_hether);


/**
 * @brief  This API initializes the ethernet according to default
 *         parameters.
 */
hal_ret_sts io_hal_stm32f7xx_eth_init(ioal_eth_hdl *ioal_hether)
{
    hal_ret_sts sts = HAL_SCS;

    MX_Eth_Init();


    ioal_hether->intf_gen_info.vdp_intf_inst_hdle = (void*)&heth;
    ioal_hether->intf_gen_info.state = IO_FREE_STATE;
    return sts;
}

/**
 * @brief This API configure the ethernet parameters
 */
void MX_Eth_Init(void)
{
    MX_LWIP_Init();

}

/**
 * @brief  This API de-Initializes the ethernet
 */
hal_ret_sts io_hal_stm32f7xx_eth_deinit(ioal_eth_hdl* ioal_hether)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    ETH_HandleTypeDef *hether=ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK ==HAL_ETH_DeInit(hether))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API initializes the DMA Tx descriptors in chain mode.
 */
hal_ret_sts io_hal_stm32f7xx_eth_dmatx_desclist_init(ioal_eth_hdl* ioal_hether, ETH_DMADescTypeDef *dmatxdesctab, uint8_t* txbuff, uint32_t txbuffcount)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(0)//(HAL_OK ==HAL_ETH_DMATxDescListInit(hether,dmatxdesctab,txbuff,txbuffcount))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API initializes the DMA Rx descriptors in chain mode.
 */
hal_ret_sts io_hal_stm32f7xx_eth_dmarx_desclist_init(ioal_eth_hdl* ioal_hether, ETH_DMADescTypeDef *dmarxdesctab, uint8_t *rxbuff, uint32_t rxbuffcount)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(0)//(HAL_OK ==HAL_ETH_DMARxDescListInit(hether,dmarxdesctab,rxbuff,rxbuffcount))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}


/**
 * @brief  This API register an ethernet Callback
 */

hal_ret_sts io_hal_stm32f7xx_eth_reg_cb(ioal_eth_hdl* ioal_hether, iohal_stm32_eth_cb_id cb_id)
{
    hal_ret_sts sts = HAL_SCS;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    switch (cb_id)
    {
        case IOHAL_ETH_TX_COMPLETE_CB_ID:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
            //sts = HAL_ETH_RegisterCallback(hether,IOHAL_ETH_TX_COMPLETE_CB_ID,io_hal_stm32f7xx_eth_tx_cmplt_cb);
#pragma GCC diagnostic pop
            break;

        case IOHAL_ETH_RX_COMPLETE_CB_ID:
            //sts = HAL_ETH_RegisterCallback(hether,IOHAL_ETH_RX_COMPLETE_CB_ID,io_hal_stm32f7xx_eth_rx_cmblt_cb);
            break;

        case IOHAL_ETH_DMA_ERROR_CB_ID:
            //sts = HAL_ETH_RegisterCallback(hether,IOHAL_ETH_DMA_ERROR_CB_ID,io_hal_stm32f7xx_eth_error_cb);
            break;

        default :
            /* Return error status */
            sts =  HAL_IO_INVLD_CB_FN;
            break;
    }
    return sts;

}

/**
 * @brief This API unregister an ethernet Callback.
 */
hal_ret_sts io_hal_stm32f7xx_eth_unreg_cb(ioal_eth_hdl* ioal_hether, iohal_stm32_eth_cb_id cb_id)
{
    hal_ret_sts sts = HAL_SCS;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;

    switch (cb_id)
    {
        case IOHAL_ETH_TX_COMPLETE_CB_ID:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
            //sts = HAL_ETH_UnRegisterCallback(hether,IOHAL_ETH_TX_COMPLETE_CB_ID);
#pragma GCC diagnostic pop
            break;

        case IOHAL_ETH_RX_COMPLETE_CB_ID:
            //sts = HAL_ETH_UnRegisterCallback(hether,IOHAL_ETH_RX_COMPLETE_CB_ID);
            break;

        case IOHAL_ETH_DMA_ERROR_CB_ID:
            //sts = HAL_ETH_UnRegisterCallback(hether,IOHAL_ETH_DMA_ERROR_CB_ID);
            break;

        default :

            sts =  HAL_IO_INVLD_CB_FN;
            break;
    }
    return sts;
}


/**
 * @brief This API sends an ethernet frame.
 */
hal_ret_sts io_hal_stm32f7xx_eth_tf(ioal_eth_hdl* ioal_hether, uint32_t framelength)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(0)//(HAL_OK ==HAL_ETH_TransmitFrame(hether,framelength))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief This API reads/get the Ethernet frame.
 */
hal_ret_sts io_hal_stm32f7xx_eth_get_rf(ioal_eth_hdl* ioal_hether)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(0)//(HAL_OK ==HAL_ETH_GetReceivedFrame(hether))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API read to a PHY register.
 */
hal_ret_sts  io_hal_stm32f7xx_eth_read_phy_reg(ioal_eth_hdl* ioal_hether, uint16_t phy_reg, uint32_t *reg_value)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(0)//(HAL_OK ==HAL_ETH_ReadPHYRegister(hether,phy_reg,reg_value))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API writes to a PHY register.
 */
hal_ret_sts  io_hal_stm32f7xx_eth_write_phy_reg(ioal_eth_hdl* ioal_hether, uint16_t phy_reg, uint32_t reg_value)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(0)//(HAL_OK ==HAL_ETH_WritePHYRegister(hether,phy_reg,reg_value))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API gets the received frame in interrupt mode.
 */
hal_ret_sts io_hal_stm32f7xx_eth_getrf_it(ioal_eth_hdl* ioal_hether)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(0)//(HAL_OK ==HAL_ETH_GetReceivedFrame_IT(hether))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief Tx completed callback event function
 */
void io_hal_stm32f7xx_eth_tx_cmplt_cb(ETH_HandleTypeDef *hether)
{
    ioal_eth_hdl*ioal_hether= NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hether, (void**)&ioal_hether))
    {
        ioal_hether->tx_cpltCallback(ioal_hether);
    }
    else
    {

    }
}

/**
 * @brief  Rx completed callback event function
 */
void io_hal_stm32f7xx_eth_rx_cmblt_cb(ETH_HandleTypeDef *hether)
{
    ioal_eth_hdl*ioal_hether= NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hether, (void**)&ioal_hether))
    {
        ioal_hether->rx_CpltCallback(ioal_hether);
    }
    else
    {

    }
}

/**
 * @brief  Error complete callback event function
 */
void io_hal_stm32f7xx_eth_error_cb(ETH_HandleTypeDef *hether)
{
    ioal_eth_hdl*ioal_hether= NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(hether, (void**)&ioal_hether))
    {
        ioal_hether->dma_error_cb(ioal_hether);
    }
    else
    {

    }
}

/**
 * @brief  This API start ethernet MAC and DMA reception/transmission .
 */
hal_ret_sts io_hal_stm32f7xx_eth_start(ioal_eth_hdl* ioal_hether)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK ==HAL_ETH_Start(hether))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API stop ethernet MAC and DMA reception/transmission .
 */
hal_ret_sts io_hal_stm32f7xx_eth_stop(ioal_eth_hdl* ioal_hether)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK ==HAL_ETH_Stop(hether))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API sets ethernet MAC Configuration.
 */
hal_ret_sts io_hal_stm32f7xx_eth_config_mac(ioal_eth_hdl* ioal_hether,ETH_MACConfigTypeDef *mac_cfg)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(0)//(HAL_OK ==HAL_ETH_ConfigMAC(hether,mac_cfg))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API sets ethernet DMA Configuration.
 */
hal_ret_sts io_hal_stm32f7xx_eth_config_dma(ioal_eth_hdl* ioal_hether, ETH_DMAConfigTypeDef *dma_cfg)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    //ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(0)//(HAL_OK ==HAL_ETH_ConfigDMA(hether,dma_cfg))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/**
 * @brief  This API get the ethernet peripheral state
 */
ioal_eth_state io_hal_stm32f7xx_eth_get_state(ioal_eth_hdl* ioal_hether)
{
    HAL_ETH_StateTypeDef state=0;
    ETH_HandleTypeDef *hether = ioal_hether->intf_gen_info.vdp_intf_inst_hdle;
    if(state ==HAL_ETH_GetState(hether))
    {
        state = HAL_SCS;
    }
    else
    {
        state = HAL_IO_VDP_ERR;
    }
    return state;
}



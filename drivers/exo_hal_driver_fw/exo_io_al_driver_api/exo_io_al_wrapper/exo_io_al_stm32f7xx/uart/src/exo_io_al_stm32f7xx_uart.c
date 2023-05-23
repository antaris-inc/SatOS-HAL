/**
 * @file exo_io_al_stm32f7xx_uart.c
 *
 * @brief This file contains wrapper function definition for UART interface
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

#include "exo_io_al_stm32f7xx_uart.h"

#include "stm32f7xx_hal.h"

static void MX_USART6_Init(ioal_uart_hdle *ioal_uart6);
static void MX_USART1_Init(ioal_uart_hdle *ioal_uart1);
static void MX_USART4_Init(ioal_uart_hdle *ioal_uart4);
static void MX_USART5_Init(ioal_uart_hdle *ioal_uart5);



/**
 * @brief TX complete callback event function
 * @param[in] huart - huart pointer to a UART_HandleTypeDef structure that contains
 * @retval No return
 */
void io_hal_stm32f7xx_uart_tx_cplt_cb(UART_HandleTypeDef *huart);
/**
 * @brief RX complete callback event function
 * @param[in] huart - huart pointer to a UART_HandleTypeDef structure that contains
 * 			the configuration information for UART

 * @retval No return
 */
void io_hal_stm32f7xx_uart_rx_cplt_cb(UART_HandleTypeDef *huart);
/**
 * @brief Abort complete callback event function
 * @param[in] huart - huart pointer to a UART_HandleTypeDef structure that contains
 * 			the configuration information for UART

 * @retval No return
 */
void io_hal_stm32f7xx_uart_abort_cplt_cb(UART_HandleTypeDef *huart);
/**
 * @brief Abort TX complete callback event function
 * @param[in] huart - huart pointer to a UART_HandleTypeDef structure that contains
 * 			the configuration information for UART

 * @retval No return
 */
void io_hal_stm32f7xx_uart_abort_tx_cplt_cb(UART_HandleTypeDef *huart);
/**
 * @brief Abort RX  complete callback event function
 * @param[in] huart - huart pointer to a UART_HandleTypeDef structure that contains
 * 			the configuration information for UART

 * @retval No return
 */
void io_hal_stm32f7xx_uart_abort_rx_cplt_cb(UART_HandleTypeDef *huart);
/**
 * @brief Error callback event function
 * @param[in] huart - huart pointer to a UART_HandleTypeDef structure that contains
 * 			the configuration information for UART
 * @retval No return
 */
void io_hal_stm32f7xx_uart_error_cb(UART_HandleTypeDef *huart);




UART_HandleTypeDef huart6;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;

/**
 * @brief This API initialize the control block memory of UART6
 */     
hal_ret_sts io_hal_stm32f7xx_uart6_init(ioal_uart_hdle *ioal_huart6)
{
    MX_USART6_Init(ioal_huart6);
    return HAL_SCS;
}

/**
 * @brief This API initialize the control block memory of UART1
 */     
hal_ret_sts io_hal_stm32f7xx_uart1_init(ioal_uart_hdle *ioal_huart1)
{
    MX_USART1_Init(ioal_huart1);
    return HAL_SCS;
}
/**
 * @brief This API initialize the control block memory of UART4
 */     
hal_ret_sts io_hal_stm32f7xx_uart4_init(ioal_uart_hdle *ioal_huart4)
{
    MX_USART4_Init(ioal_huart4);
    return HAL_SCS;
}
/**
 * @brief This API initialize the control block memory of UART5
 */     
hal_ret_sts io_hal_stm32f7xx_uart5_init(ioal_uart_hdle *ioal_huart5)
{
    MX_USART5_Init(ioal_huart5);
    return HAL_SCS;
}

/**
 * @brief USART6 Initialization Function
 */
static void MX_USART6_Init(ioal_uart_hdle *ioal_huart6)
{
    huart6.Instance = USART6;
    huart6.Init.BaudRate = 115200;
    huart6.Init.WordLength = UART_WORDLENGTH_8B;
    huart6.Init.StopBits = UART_STOPBITS_1;
    huart6.Init.Parity = UART_PARITY_NONE;
    huart6.Init.Mode = UART_MODE_TX_RX;
    huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart6.Init.OverSampling = UART_OVERSAMPLING_16;
    huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart6) != HAL_OK)
    {
        ioal_error_handler();
    }

    ioal_huart6->intf_gen_info.vdp_intf_inst_hdle = (void*)&huart6;
    ioal_huart6->intf_gen_info.state = IO_FREE_STATE;
}

/**
 * @brief USART1 Initialization Function
 */     
static void MX_USART1_Init(ioal_uart_hdle *ioal_huart1)
{

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        ioal_error_handler();
    }

    ioal_huart1->intf_gen_info.vdp_intf_inst_hdle = (void*)&huart1;
    ioal_huart1->intf_gen_info.state = IO_FREE_STATE;
}

/**
 * @brief USART4 Initialization Function
 */     
static void MX_USART4_Init(ioal_uart_hdle *ioal_huart4)
{

    huart4.Instance = UART4;
    huart4.Init.BaudRate = 115200;
    huart4.Init.WordLength = UART_WORDLENGTH_8B;
    huart4.Init.StopBits = UART_STOPBITS_1;
    huart4.Init.Parity = UART_PARITY_NONE;
    huart4.Init.Mode = UART_MODE_TX_RX;
    huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart4.Init.OverSampling = UART_OVERSAMPLING_16;
    huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart4) != HAL_OK)
    {
        ioal_error_handler();
    }

    ioal_huart4->intf_gen_info.vdp_intf_inst_hdle = (void*)&huart4;
    ioal_huart4->intf_gen_info.state = IO_FREE_STATE;
}

/**
 * @brief USART5 Initialization Function
 */     
static void MX_USART5_Init(ioal_uart_hdle *ioal_huart5)
{

    huart5.Instance = UART5;
    huart5.Init.BaudRate = 115200;
    huart5.Init.WordLength = UART_WORDLENGTH_8B;
    huart5.Init.StopBits = UART_STOPBITS_1;
    huart5.Init.Parity = UART_PARITY_NONE;
    huart5.Init.Mode = UART_MODE_TX_RX;
    huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart5.Init.OverSampling = UART_OVERSAMPLING_16;
    huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart5) != HAL_OK)
    {
        ioal_error_handler();
    }

    ioal_huart5->intf_gen_info.vdp_intf_inst_hdle = (void*)&huart5;
    ioal_huart5->intf_gen_info.state = IO_FREE_STATE;
}


/**
 * @brief This API transmit the data in blocking mode
 */     
hal_ret_sts io_hal_stm32f7xx_uart_transmit(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_Transmit(huart, pdata, size, timeout))
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
 * @brief This API receive the data in blocking mode
 */     
hal_ret_sts io_hal_stm32f7xx_uart_receive(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_Receive(huart, pdata, size, timeout))
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
 * @brief This API transmit the data in interrupt mode
 */     
hal_ret_sts io_hal_stm32f7xx_uart_transmit_it(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_Transmit_IT(huart, pdata, size))
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
 * @brief This API receive the data in interrupt mode
 */     
hal_ret_sts io_hal_stm32f7xx_uart_receive_it(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_Receive_IT(huart, pdata, size))
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
 * @brief This API transmit the data in DMA mode
 */     
hal_ret_sts io_hal_stm32f7xx_uart_transmit_dma(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_Transmit_DMA(huart, pdata, size))
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
 * @brief This API receive the data in DMA mode
 */     
hal_ret_sts io_hal_stm32f7xx_uart_receive_dma(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_Receive_DMA(huart, pdata, size))
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
 * @brief This API pause the transmission of data
 */     
hal_ret_sts io_hal_stm32f7xx_uart_dma_pause(ioal_uart_hdle *ioal_huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_DMAPause(huart))
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
 * @brief This API resume the transmission of data
 */     
hal_ret_sts io_hal_stm32f7xx_uart_dma_resume(ioal_uart_hdle *ioal_huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_DMAResume(huart))
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
 * @brief This API stop the transmission of data
 */     
hal_ret_sts io_hal_stm32f7xx_uart_dma_stop(ioal_uart_hdle *ioal_huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_DMAStop(huart))
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
 * @brief This API abort the transmission of data
 */     
hal_ret_sts io_hal_stm32f7xx_uart_abort(ioal_uart_hdle *ioal_huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_Abort(huart))
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
 * @brief This API abort the ongoing transmit of data
 */     
hal_ret_sts io_hal_stm32f7xx_uart_abort_transmit(ioal_uart_hdle *ioal_huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_AbortTransmit(huart))
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
 * @brief This API abort the receive of data
 */     
hal_ret_sts io_hal_stm32f7xx_uart_abort_receive(ioal_uart_hdle *ioal_huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_AbortReceive(huart))
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
 * @brief This API abort the transmission of data in interrupt mode
 */     
hal_ret_sts io_hal_stm32f7xx_uart_abort_it(ioal_uart_hdle *ioal_huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_Abort_IT(huart))
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
 * @brief This API abort the transmit of data in interrupt mode
 */     
hal_ret_sts io_hal_stm32f7xx_uart_abort_transmit_it(ioal_uart_hdle *ioal_huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_AbortTransmit_IT(huart))
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
 * @brief This API abort the receive of data in interrupt mode
 */     
hal_ret_sts io_hal_stm32f7xx_uart_abort_receive_it(ioal_uart_hdle *ioal_huart)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(HAL_OK == HAL_UART_AbortReceive_IT(huart))
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
 * @brief This API register the callback event
 */     
hal_ret_sts io_hal_stm32f7xx_uart_reg_cb(ioal_uart_hdle *ioal_huart, iohal_stm32_uart_cbid cbid)
{
    hal_ret_sts sts = HAL_SCS;
    UART_HandleTypeDef *huart = ioal_huart->intf_gen_info.vdp_intf_inst_hdle;

    switch (cbid)
    {
        case IOHAL_STM32_UART_TX_CPLT_CB_ID :
            sts = HAL_UART_RegisterCallback(huart, HAL_UART_TX_COMPLETE_CB_ID,io_hal_stm32f7xx_uart_tx_cplt_cb);
            break;

        case IOHAL_STM32_UART_RX_CPLT_CB_ID:
            sts = HAL_UART_RegisterCallback(huart, HAL_UART_RX_COMPLETE_CB_ID,io_hal_stm32f7xx_uart_rx_cplt_cb);
            break;

        case IOHAL_STM32_UART_ABORT_CPLT_CB_ID:
            sts = HAL_UART_RegisterCallback(huart, HAL_UART_ABORT_COMPLETE_CB_ID,io_hal_stm32f7xx_uart_abort_cplt_cb);
            break;

        case IOHAL_STM32_UART_ABORT_TX_CPLT_CB_ID:
            sts = HAL_UART_RegisterCallback(huart, HAL_UART_ABORT_TRANSMIT_COMPLETE_CB_ID,io_hal_stm32f7xx_uart_abort_tx_cplt_cb);
            break;

        case IOHAL_STM32_UART_ABORT_RX_CPLT_CB_ID:
            sts = HAL_UART_RegisterCallback(huart, HAL_UART_ABORT_RECEIVE_COMPLETE_CB_ID,io_hal_stm32f7xx_uart_abort_rx_cplt_cb);
            break;

        case IOHAL_STM32_UART_ERROR_CB_ID:
            sts = HAL_UART_RegisterCallback(huart, HAL_UART_ERROR_CB_ID,io_hal_stm32f7xx_uart_error_cb);
            break;

        default :

            sts =  HAL_IO_INVLD_CB_FN;
            break;
    }
    return sts;
}

/**
 * @brief TX complete callback event function
 */     
void io_hal_stm32f7xx_uart_tx_cplt_cb(UART_HandleTypeDef *huart)
{
    ioal_uart_hdle *ioal_huart = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(huart, (void**)&ioal_huart))
    {
        ioal_huart->tx_cplt_cb(ioal_huart);
    }
    else
    {

    }
}

/**
 * @brief RX complete callback event function
 */     
void io_hal_stm32f7xx_uart_rx_cplt_cb(UART_HandleTypeDef *huart)
{
    ioal_uart_hdle *ioal_huart = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(huart, (void**)&ioal_huart))
    {
        ioal_huart->rx_cplt_cb(ioal_huart);
    }
    else
    {

    }
}

/**
 * @brief Abort complete callback event function
 */     
void io_hal_stm32f7xx_uart_abort_cplt_cb(UART_HandleTypeDef *huart)
{
    ioal_uart_hdle *ioal_huart = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(huart, (void**)&ioal_huart))
    {
        ioal_huart->abort_cplt_cb(ioal_huart);
    }
    else
    {

    }
}

/**
 * @brief Abort TX complete callback event function
 */     
void io_hal_stm32f7xx_uart_abort_tx_cplt_cb(UART_HandleTypeDef *huart)
{
    ioal_uart_hdle *ioal_huart = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(huart, (void**)&ioal_huart))
    {
        ioal_huart->abort_tx_cplt_cb(ioal_huart);
    }
    else
    {

    }
}

/**
 * @brief Abort RX complete callback event function
 */     
void io_hal_stm32f7xx_uart_abort_rx_cplt_cb(UART_HandleTypeDef *huart)
{
    ioal_uart_hdle *ioal_huart = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(huart, (void**)&ioal_huart))
    {
        ioal_huart->abort_rx_cplt_cb(ioal_huart);
    }
    else
    {

    }
}

/**
 * @brief Error callback event function
 */     
void io_hal_stm32f7xx_uart_error_cb(UART_HandleTypeDef *huart)
{
    ioal_uart_hdle *ioal_huart = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(huart, (void**)&ioal_huart))
    {
        ioal_huart->error_cb(ioal_huart);
    }
    else
    {

    }
}

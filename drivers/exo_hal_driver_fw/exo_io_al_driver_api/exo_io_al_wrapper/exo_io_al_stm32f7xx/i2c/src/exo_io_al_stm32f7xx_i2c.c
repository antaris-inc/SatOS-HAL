/**
 * @file exo_io_al_stm32f7xx_i2c.c
 *
 * @brief This file contains wrapper function definition for I2C interface
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

#include "exo_io_al_stm32f7xx_i2c.h"
#include "exo_osal.h"
#include "exo_common.h"
#ifndef LINUX_TEMP_PORT
#include "stm32f7xx_hal.h"
#endif

I2C_HandleTypeDef hi2c1;  ///< I2C1 handler
I2C_HandleTypeDef hi2c2;  ///< I2C2 handler
I2C_HandleTypeDef hi2c3;  ///< I2C3 handler
I2C_HandleTypeDef hi2c4;  ///< I2C4 handler
HAL_StatusTypeDef i2c_sts = 0;  ///< I2C status

/**
 * @brief  This API register the I2C1 callback event
 */
void io_hal_stm32f7xx_i2c1_reg_cb();
/**
 * @brief  This API register the I2C2 callback event
 */
void io_hal_stm32f7xx_i2c2_reg_cb();
/**
 * @brief  This API register the I2C3 callback event
 */
void io_hal_stm32f7xx_i2c3_reg_cb();
/**
 * @brief  This API register the I2C4 callback event
 */
void io_hal_stm32f7xx_i2c4_reg_cb();
/**
 * @brief   This function is a master transmit complete I2C1 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c1_mst_tx_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a master recieve complete I2C1 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c1_mst_rx_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief   This function is a abort complete I2C1 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c1_abort_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a Listen complete I2C1 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c1_listen_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a error complete I2C1 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c1_error_cb(I2C_HandleTypeDef *hi2c);

/**
 * @brief   This function is a master transmit complete I2C2 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c2_mst_tx_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a master recieve complete I2C2 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c2_mst_rx_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief   This function is a abort complete I2C2 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c2_abort_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a Listen complete I2C2 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c2_listen_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a error complete I2C2 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c2_error_cb(I2C_HandleTypeDef *hi2c);

/**
 * @brief   This function is a master transmit complete I2C3 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c3_mst_tx_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a master recieve complete I2C3 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c3_mst_rx_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief   This function is a abort complete I2C3 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c3_abort_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a Listen complete I2C3 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c3_listen_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a error complete I2C3 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c3_error_cb(I2C_HandleTypeDef *hi2c);

/**
 * @brief   This function is a master transmit complete I2C4 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c4_mst_tx_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a master recieve complete I2C4 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c4_mst_rx_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief   This function is a abort complete I2C4 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c4_abort_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a Listen complete I2C4 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c4_listen_cplt_cb(I2C_HandleTypeDef *hi2c);
/**
 * @brief  This function is a error complete I2C4 Callback event
 * @param[in]  ioal_hi2c -  pointer to a ioal_i2c_hdle structure that contains
 *                the configuration information for I2C module.
 * @retval HAL status.
 */
void io_hal_stm32f7xx_i2c4_error_cb(I2C_HandleTypeDef *hi2c);


/**
 * @brief  This API initializes the control block memory and do the basic
 * 		configurations I2C1
 */
hal_ret_sts io_hal_stm32f7xx_i2c1_init(ioal_i2c_hdle *ioal_hi2c1)
{
    hal_ret_sts ret_sts = HAL_IO_INVLD_ARG;
    if(ioal_hi2c1 != NULL)
    {
        MX_I2C1_Init(ioal_hi2c1);
        io_hal_stm32f7xx_i2c1_reg_cb();
        ret_sts = HAL_SCS;
    }
    return ret_sts;
}

/**
 * @brief  This API initializes the control block memory and do the basic
 * 		configurations I2C2
 */
hal_ret_sts io_hal_stm32f7xx_i2c2_init(ioal_i2c_hdle *ioal_hi2c2)
{
    hal_ret_sts ret_sts = HAL_IO_INVLD_ARG;
    if(ioal_hi2c2 != NULL)
    {
        MX_I2C2_Init(ioal_hi2c2);
        io_hal_stm32f7xx_i2c2_reg_cb();
        ret_sts = HAL_SCS;
    }
    return ret_sts;
}

/**
 * @brief  This API initializes the control block memory and do the basic
 * 		configurations I2C3
 */
hal_ret_sts io_hal_stm32f7xx_i2c3_init(ioal_i2c_hdle *ioal_hi2c3)
{
    hal_ret_sts ret_sts = HAL_IO_INVLD_ARG;
    if(ioal_hi2c3 != NULL)
    {
        MX_I2C3_Init(ioal_hi2c3);
        io_hal_stm32f7xx_i2c3_reg_cb();
        ret_sts = HAL_SCS;
    }
    return ret_sts;
}

/**
 * @brief  This API initializes the control block memory and do the basic
 * 		configurations I2C4
 */
hal_ret_sts io_hal_stm32f7xx_i2c4_init(ioal_i2c_hdle *ioal_hi2c4)
{
    hal_ret_sts ret_sts = HAL_IO_INVLD_ARG;
    if(ioal_hi2c4 != NULL)
    {
        MX_I2C4_Init(ioal_hi2c4);
        io_hal_stm32f7xx_i2c4_reg_cb();
        ret_sts = HAL_SCS;
    }
    return ret_sts;
}

/**
 * @brief  This function De initializes the I2C
 */
hal_ret_sts io_hal_stm32f7xx_i2c_deinit(ioal_i2c_hdle *ioal_hi2c)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    //Clear I2C Error Flag
    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_BERR);
    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_OVR);
    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ARLO);
    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_TIMEOUT);
    if(HAL_OK == HAL_I2C_DeInit(hi2c))
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
 * @brief This function get the i2c error code
 */
uint32 io_hal_stm32f7xx_i2c_get_err(ioal_i2c_hdle *ioal_hi2c)
{
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;

    return HAL_I2C_GetError(hi2c);
}
/**
 * @brief  I2C1 Initialization function
 */
void MX_I2C1_Init(ioal_i2c_hdle *ioal_hi2c1)
{

    hi2c1.Instance = I2C1;
    hi2c1.Init.Timing = 0x20404768;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        ioal_error_handler();
    }

    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        ioal_error_handler();
    }

    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
    {
        ioal_error_handler();
    }

    ioal_hi2c1->intf_gen_info.vdp_intf_inst_hdle = (void*)&hi2c1;
    ioal_hi2c1->intf_gen_info.state = IO_FREE_STATE;

}

/**
 * @brief I2C2 Initialization function
 */
void MX_I2C2_Init(ioal_i2c_hdle *ioal_hi2c2)
{

    hi2c2.Instance = I2C2;
    hi2c2.Init.Timing = 0x20404768;
    hi2c2.Init.OwnAddress1 = 0;
    hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c2.Init.OwnAddress2 = 0;
    hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c2) != HAL_OK)
    {
        ioal_error_handler();
    }

    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        ioal_error_handler();
    }

    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
    {
        ioal_error_handler();
    }

    ioal_hi2c2->intf_gen_info.vdp_intf_inst_hdle = (void*)&hi2c2;
    ioal_hi2c2->intf_gen_info.state = IO_FREE_STATE;

}

/**
 * @brief  I2C4 Initialization function
 */
void MX_I2C4_Init(ioal_i2c_hdle *ioal_hi2c4)
{
    hi2c4.Instance = I2C4;
    hi2c4.Init.Timing = 0x20404768;
    hi2c4.Init.OwnAddress1 = 0;
    hi2c4.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c4.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c4.Init.OwnAddress2 = 0;
    hi2c4.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c4.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c4.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c4) != HAL_OK)
    {
        ioal_error_handler();
    }
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c4, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        ioal_error_handler();
    }
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c4, 0) != HAL_OK)
    {
        ioal_error_handler();
    }
    ioal_hi2c4->intf_gen_info.vdp_intf_inst_hdle = (void*)&hi2c4;
    ioal_hi2c4->intf_gen_info.state = IO_FREE_STATE;
}

/**
 * @brief  I2C3 Initialization function
 */
void MX_I2C3_Init(ioal_i2c_hdle *ioal_hi2c3)
{
    hi2c3.Instance = I2C3;
    hi2c3.Init.Timing = 0x20404768;
    hi2c3.Init.OwnAddress1 = 0;
    hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c3.Init.OwnAddress2 = 0;
    hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c3) != HAL_OK)
    {
        ioal_error_handler();
    }
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        ioal_error_handler();
    }
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
    {
        ioal_error_handler();
    }
    ioal_hi2c3->intf_gen_info.vdp_intf_inst_hdle = (void*)&hi2c3;
    ioal_hi2c3->intf_gen_info.state = IO_FREE_STATE;
}

/**
 * @brief  This API transmits data in master mode
 */
hal_ret_sts io_hal_stm32f7xx_i2c_transmit(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    if(hi2c != NULL && pdata != NULL)
    {
        if(HAL_OK == HAL_I2C_Master_Transmit(hi2c, addr, pdata, size, timeout))
        {
            ret_sts = HAL_SCS;
        }
        else
        {
            ret_sts = HAL_IO_VDP_ERR;
        }
    }
    else
    {
        ret_sts = HAL_IO_INVLD_ARG;
    }
    return ret_sts;
}

/**
 * @brief  This API receives data in master mode
 */
hal_ret_sts io_hal_stm32f7xx_i2c_receive(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    if(hi2c != NULL && pdata != NULL)
    {
        if(HAL_OK == HAL_I2C_Master_Receive(hi2c, addr, pdata, size, timeout))
        {
            ret_sts = HAL_SCS;
        }
        else
        {
            ret_sts = HAL_IO_VDP_ERR;
        }
    }
    else
    {
        ret_sts = HAL_IO_INVLD_ARG;
    }
    return ret_sts;
}

/**
 * @brief  This API transmit data in master mode with Interrupt
 */
hal_ret_sts io_hal_stm32f7xx_i2c_transmit_it(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    if(hi2c != NULL && pdata != NULL)
    {
        if(HAL_OK == HAL_I2C_Master_Transmit_IT(hi2c, addr, pdata, size))
        {
            ret_sts = HAL_SCS;
        }
        else
        {
            ret_sts = HAL_IO_VDP_ERR;
        }
    }
    else
    {
        ret_sts = HAL_IO_INVLD_ARG;
    }
    return ret_sts;
}

/**
 * @brief  This API receive data in master mode with Interrupt
 */
hal_ret_sts io_hal_stm32f7xx_i2c_receive_it(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    if(hi2c != NULL && pdata != NULL)
    {
        if(HAL_OK == HAL_I2C_Master_Receive_IT(hi2c, addr, pdata, size))
        {
            ret_sts = HAL_SCS;
        }
        else
        {
            ret_sts = HAL_IO_VDP_ERR;
        }
    }
    else
    {
        ret_sts = HAL_IO_INVLD_ARG;
    }
    return ret_sts;
}

/**
 * @brief  This API transmit data in master mode with DMA
 */
hal_ret_sts io_hal_stm32f7xx_i2c_transmit_dma(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    if(hi2c != NULL && pdata != NULL)
    {
        if(HAL_OK == HAL_I2C_Master_Transmit_DMA(hi2c, addr, pdata, size))
        {
            ret_sts = HAL_SCS;
        }
        else
        {
            ret_sts = HAL_IO_VDP_ERR;
        }
    }
    else
    {
        ret_sts = HAL_IO_INVLD_ARG;
    }
    return ret_sts;
}

/**
 * @brief  This API receive data in master mode with DMA
 */
hal_ret_sts io_hal_stm32f7xx_i2c_receive_dma(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint8 *pdata, uint16 size)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    if(hi2c != NULL && pdata != NULL)
    {
        if(HAL_OK == HAL_I2C_Master_Receive_DMA(hi2c, addr, pdata, size))
        {
            ret_sts = HAL_SCS;
        }
        else
        {
            ret_sts = HAL_IO_VDP_ERR;
        }
    }
    else
    {
        ret_sts = HAL_IO_INVLD_ARG;
    }
    return ret_sts;
}

/**
 * @brief  This API checks if device is ready for communication.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_is_device_ready(ioal_i2c_hdle *ioal_hi2c, uint16 addr, uint32 trials, uint32 timeout)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    if(hi2c != NULL)
    {
        if(HAL_OK == HAL_I2C_IsDeviceReady(hi2c, addr, trials, timeout))
        {
            ret_sts = HAL_SCS;
        }
        else
        {
            ret_sts = HAL_IO_VDP_ERR;
        }
    }
    else
    {
        ret_sts = HAL_IO_INVLD_ARG;
    }
    return ret_sts;
}

/**
 * @brief  This API enable the Address listen mode with Interrupt.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_enable_listen_it(ioal_i2c_hdle *ioal_hi2c)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    if(hi2c != NULL)
    {
        if(HAL_OK == HAL_I2C_EnableListen_IT(hi2c))
        {
            ret_sts = HAL_SCS;
        }
        else
        {
            ret_sts = HAL_IO_VDP_ERR;
        }
    }
    else
    {
        ret_sts = HAL_IO_INVLD_ARG;
    }
    return ret_sts;
}

/**
 * @brief  This API disable the Address listen mode with Interrupt.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_disable_listen_it(ioal_i2c_hdle *ioal_hi2c)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    if(hi2c != NULL)
    {
        if(HAL_OK == HAL_I2C_DisableListen_IT(hi2c))
        {
            ret_sts = HAL_SCS;
        }
        else
        {
            ret_sts = HAL_IO_VDP_ERR;
        }
    }
    else
    {
        ret_sts = HAL_IO_INVLD_ARG;
    }
    return ret_sts;
}

/**
 * @brief  This API abort a master with Interrupt.
 */
hal_ret_sts io_hal_stm32f7xx_i2c_abort_it(ioal_i2c_hdle *ioal_hi2c, uint16 addr)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    I2C_HandleTypeDef *hi2c = ioal_hi2c->intf_gen_info.vdp_intf_inst_hdle;
    if(hi2c != NULL)
    {
        if(HAL_OK == HAL_I2C_Master_Abort_IT(hi2c, addr))
        {
            ret_sts = HAL_SCS;
        }
        else
        {
            ret_sts = HAL_IO_VDP_ERR;
        }
    }
    else
    {
        ret_sts = HAL_IO_INVLD_ARG;
    }
    return ret_sts;
}

/**
 * @brief  This API register the I2C1 callback event
 */
void io_hal_stm32f7xx_i2c1_reg_cb()
{
    HAL_I2C_RegisterCallback(&hi2c1, HAL_I2C_MASTER_TX_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c1_mst_tx_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c1, HAL_I2C_MASTER_RX_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c1_mst_rx_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c1, HAL_I2C_ABORT_CB_ID,io_hal_stm32f7xx_i2c1_abort_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c1, HAL_I2C_LISTEN_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c1_listen_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c1, HAL_I2C_ERROR_CB_ID,io_hal_stm32f7xx_i2c1_error_cb);
}

/**
 * @brief  This API register the I2C2 callback event
 */
void io_hal_stm32f7xx_i2c2_reg_cb()
{
    HAL_I2C_RegisterCallback(&hi2c2, HAL_I2C_MASTER_TX_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c2_mst_tx_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c2, HAL_I2C_MASTER_RX_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c2_mst_rx_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c2, HAL_I2C_ABORT_CB_ID,io_hal_stm32f7xx_i2c2_abort_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c2, HAL_I2C_LISTEN_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c2_listen_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c2, HAL_I2C_ERROR_CB_ID,io_hal_stm32f7xx_i2c2_error_cb);
}

/**
 * @brief  This API register the I2C3 callback event
 */
void io_hal_stm32f7xx_i2c3_reg_cb()
{
    HAL_I2C_RegisterCallback(&hi2c3, HAL_I2C_MASTER_TX_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c3_mst_tx_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c3, HAL_I2C_MASTER_RX_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c3_mst_rx_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c3, HAL_I2C_ABORT_CB_ID,io_hal_stm32f7xx_i2c3_abort_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c3, HAL_I2C_LISTEN_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c3_listen_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c3, HAL_I2C_ERROR_CB_ID,io_hal_stm32f7xx_i2c3_error_cb);
}

/**
 * @brief  This API register the I2C4 callback event
 */
void io_hal_stm32f7xx_i2c4_reg_cb()
{
    HAL_I2C_RegisterCallback(&hi2c4, HAL_I2C_MASTER_TX_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c4_mst_tx_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c4, HAL_I2C_MASTER_RX_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c4_mst_rx_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c4, HAL_I2C_ABORT_CB_ID,io_hal_stm32f7xx_i2c4_abort_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c4, HAL_I2C_LISTEN_COMPLETE_CB_ID,io_hal_stm32f7xx_i2c4_listen_cplt_cb);
    HAL_I2C_RegisterCallback(&hi2c4, HAL_I2C_ERROR_CB_ID,io_hal_stm32f7xx_i2c4_error_cb);
}

/**
 * @brief  This API is a master transmit complete I2C1 Callback event
 */
void io_hal_stm32f7xx_i2c1_mst_tx_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C1);
    if((ioal_hi2c->cb_context & I2C_MST_TX_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_mst_tx_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C1;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_MST_TX_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief  This API is a master recieve complete I2C1 Callback event
 */
void io_hal_stm32f7xx_i2c1_mst_rx_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C1);
    if((ioal_hi2c->cb_context & I2C_MST_RX_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_mst_rx_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C1;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_MST_RX_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief   This API is a abort complete I2C1 Callback event
 */
void io_hal_stm32f7xx_i2c1_abort_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C1);
    if((ioal_hi2c->cb_context & I2C_ABORT_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_abort_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C1;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_ABORT_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief This API is a Listen complete I2C1 Callback event
 */
void io_hal_stm32f7xx_i2c1_listen_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C1);
    if((ioal_hi2c->cb_context & I2C_LISTEN_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_listen_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C1;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_LISTEN_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief This API is a error complete I2C1 Callback event
 */
void io_hal_stm32f7xx_i2c1_error_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C1);
    if((ioal_hi2c->cb_context & I2C_ERROR_CB)==LISR)
    {
        ioal_hi2c->i2c_error_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C1;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_ERROR_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}


/**
 * @brief  This API is a master recieve complete I2C2 Callback event
 */
void io_hal_stm32f7xx_i2c2_mst_tx_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C2);
    if((ioal_hi2c->cb_context & I2C_MST_TX_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_mst_tx_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C2;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_MST_TX_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief  This API is a master recieve complete I2C2 Callback event
 */
void io_hal_stm32f7xx_i2c2_mst_rx_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C1);
    if((ioal_hi2c->cb_context & I2C_MST_RX_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_mst_rx_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C1;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_MST_RX_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief   This API is a abort complete I2C2 Callback event
 */
void io_hal_stm32f7xx_i2c2_abort_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C2);
    if((ioal_hi2c->cb_context & I2C_ABORT_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_abort_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C2;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_ABORT_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief This API is a Listen complete I2C2 Callback event
 */
void io_hal_stm32f7xx_i2c2_listen_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C2);
    if((ioal_hi2c->cb_context & I2C_LISTEN_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_listen_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C2;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_LISTEN_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief This API is a error complete I2C2 Callback event
 */
void io_hal_stm32f7xx_i2c2_error_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C2);
    if((ioal_hi2c->cb_context & I2C_ERROR_CB)==LISR)
    {
        ioal_hi2c->i2c_error_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C2;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_ERROR_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief  This API is a master transmit complete I2C3 Callback event
 */
void io_hal_stm32f7xx_i2c3_mst_tx_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C3);
    if((ioal_hi2c->cb_context & I2C_MST_TX_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_mst_tx_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C3;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_MST_TX_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief  This API is a master recieve complete I2C3 Callback event
 */
void io_hal_stm32f7xx_i2c3_mst_rx_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C3);
    if((ioal_hi2c->cb_context & I2C_MST_RX_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_mst_rx_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C3;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_MST_RX_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief   This API is a abort complete I2C3 Callback event
 */
void io_hal_stm32f7xx_i2c3_abort_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C3);
    if((ioal_hi2c->cb_context & I2C_ABORT_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_abort_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C3;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_ABORT_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief This API is a Listen complete I2C3 Callback event
 */
void io_hal_stm32f7xx_i2c3_listen_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C3);
    if((ioal_hi2c->cb_context & I2C_LISTEN_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_listen_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C3;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_LISTEN_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief This API is a error complete I2C3 Callback event
 */
void io_hal_stm32f7xx_i2c3_error_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C3);
    if((ioal_hi2c->cb_context & I2C_ERROR_CB)==LISR)
    {
        ioal_hi2c->i2c_error_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C3;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_ERROR_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief  This API is a master recieve complete I2C4 Callback event
 */
void io_hal_stm32f7xx_i2c4_mst_tx_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C4);
    if((ioal_hi2c->cb_context & I2C_MST_TX_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_mst_tx_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C3;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_MST_TX_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief  This API is a master recieve complete I2C4 Callback event
 */
void io_hal_stm32f7xx_i2c4_mst_rx_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C4);
    if((ioal_hi2c->cb_context & I2C_MST_RX_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_mst_rx_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C4;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_MST_RX_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief   This API is a abort complete I2C4 Callback event
 */
void io_hal_stm32f7xx_i2c4_abort_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C4);
    if((ioal_hi2c->cb_context & I2C_ABORT_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_abort_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C4;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_ABORT_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief This API is a Listen complete I2C4 Callback event
 */
void io_hal_stm32f7xx_i2c4_listen_cplt_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C4);
    if((ioal_hi2c->cb_context & I2C_LISTEN_CPLT_CB)==LISR)
    {
        ioal_hi2c->i2c_listen_cplt_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C4;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_LISTEN_CPLT_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

/**
 * @brief This API is a error complete I2C4 Callback event
 */
void io_hal_stm32f7xx_i2c4_error_cb(I2C_HandleTypeDef *hi2c)
{
    os_itc_msg_handle_t i2c_intr_hdlr_ipc;
    ioal_i2c_hdle *ioal_hi2c = get_ioal_inst_hdle(IOAL_INST_I2C4);
    if((ioal_hi2c->cb_context & I2C_ERROR_CB)==LISR)
    {
        ioal_hi2c->i2c_error_cb(ioal_hi2c);
    }
    else
    {
        i2c_intr_hdlr_ipc.pld_info=IOAL_INST_I2C4;
        i2c_intr_hdlr_ipc.pld.pld_data=I2C_ERROR_CB;
        os_itc_msg_send(&i2c_intr_hdlr_ipc,HAL_INTR_HDLR,0);
    }
}

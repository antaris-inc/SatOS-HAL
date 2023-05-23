/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file         stm32f7xx_hal_msp.c
 * @brief        This file provides code for the MSP Initialization
 *               and de-Initialization codes.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */
#include "pin_map.h"
/* USER CODE END Includes */

extern DMA_HandleTypeDef hdma_i2c1_rx;

extern DMA_HandleTypeDef hdma_i2c1_tx;

extern DMA_HandleTypeDef hdma_i2c2_rx;

extern DMA_HandleTypeDef hdma_i2c2_tx;

extern DMA_HandleTypeDef hdma_spi1_rx;

extern DMA_HandleTypeDef hdma_spi2_tx;

extern DMA_HandleTypeDef hdma_spi2_rx;

extern DMA_HandleTypeDef hdma_spi1_tx;

extern DMA_HandleTypeDef hdma_usart6_rx;

extern DMA_HandleTypeDef hdma_usart6_tx;

void HAL_MspInit(void)
{
    /* USER CODE BEGIN MspInit 0 */

    /* USER CODE END MspInit 0 */

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    /* System interrupt init*/
    /* PendSV_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);

    /* USER CODE BEGIN MspInit 1 */

    /* USER CODE END MspInit 1 */
}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef* hwwdg)
{
    if(hwwdg->Instance==WWDG)
    {
        /* USER CODE BEGIN WWDG_MspInit 0 */

        /* USER CODE END WWDG_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_WWDG_CLK_ENABLE();
        /* WWDG interrupt Init */
        HAL_NVIC_SetPriority(WWDG_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(WWDG_IRQn);
        /* USER CODE BEGIN WWDG_MspInit 1 */

        /* USER CODE END WWDG_MspInit 1 */
    }

}

#ifdef COREBOARD
static uint32_t FMC_Initialized = 0;


static void HAL_FMC_MspInit(void){

    /* USER CODE BEGIN FMC_MspInit 0 */

    /* USER CODE END FMC_MspInit 0 */
    GPIO_InitTypeDef GPIO_InitStruct ={0};
    if (FMC_Initialized) {
        return;
    }
    FMC_Initialized = 1;

    /* Peripheral clock enable */
    __HAL_RCC_FMC_CLK_ENABLE();

    /** FMC GPIO Configuration
      PE4   ------> FMC_A20
      PE3   ------> FMC_A19
      PE1   ------> FMC_NBL1
      PE0   ------> FMC_NBL0
      PE5   ------> FMC_A21
      PE6   ------> FMC_A22
      PG15   ------> FMC_SDNCAS
      PD6   ------> FMC_NWAIT
      PD0   ------> FMC_D2
      PI4   ------> FMC_NBL2
      PD5   ------> FMC_NWE
      PD1   ------> FMC_D3
      PI3   ------> FMC_D27
      PI2   ------> FMC_D26
      PF0   ------> FMC_A0
      PI5   ------> FMC_NBL3
      PI7   ------> FMC_D29
      PI10   ------> FMC_D31
      PI6   ------> FMC_D28
      PD4   ------> FMC_NOE
      PH15   ------> FMC_D23
      PI1   ------> FMC_D25
      PF1   ------> FMC_A1
      PI9   ------> FMC_D30
      PH13   ------> FMC_D21
      PH14   ------> FMC_D22
      PI0   ------> FMC_D24
      PF2   ------> FMC_A2
      PC7   ------> FMC_NE1
      PF3   ------> FMC_A3
      PG8   ------> FMC_SDCLK
      PF4   ------> FMC_A4
      PH3   ------> FMC_SDNE0
      PF5   ------> FMC_A5
      PH2   ------> FMC_SDCKE0
      PD15   ------> FMC_D1
      PD10   ------> FMC_D15
      PD14   ------> FMC_D0
      PD9   ------> FMC_D14
      PD8   ------> FMC_D13
      PC0   ------> FMC_SDNWE
      PF12   ------> FMC_A6
      PG1   ------> FMC_A11
      PF15   ------> FMC_A9
      PD12   ------> FMC_A17
      PD13   ------> FMC_A18
      PG3   ------> FMC_A13
      PG2   ------> FMC_A12
      PH12   ------> FMC_D20
      PF13   ------> FMC_A7
      PG0   ------> FMC_A10
      PE8   ------> FMC_D5
      PD11   ------> FMC_A16
      PG5   ------> FMC_A15
      PG5   ------> FMC_BA1
      PG4   ------> FMC_A14
      PG4   ------> FMC_BA0
      PH9   ------> FMC_D17
      PH11   ------> FMC_D19
      PF14   ------> FMC_A8
      PF11   ------> FMC_SDNRAS
      PE9   ------> FMC_D6
      PE11   ------> FMC_D8
      PE14   ------> FMC_D11
      PH8   ------> FMC_D16
      PH10   ------> FMC_D18
      PE7   ------> FMC_D4
      PE10   ------> FMC_D7
      PE12   ------> FMC_D9
      PE15   ------> FMC_D12
    PE13   ------> FMC_D10
        */
        GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_0
        |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9
        |GPIO_PIN_11|GPIO_PIN_14|GPIO_PIN_7|GPIO_PIN_10
        |GPIO_PIN_12|GPIO_PIN_15|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_1|GPIO_PIN_3
        |GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_1
        |GPIO_PIN_4|GPIO_PIN_15|GPIO_PIN_10|GPIO_PIN_14
        |GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_12|GPIO_PIN_13
        |GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_5
        |GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_6|GPIO_PIN_1
        |GPIO_PIN_9|GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
        |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_12|GPIO_PIN_15
        |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_3
        |GPIO_PIN_2|GPIO_PIN_12|GPIO_PIN_9|GPIO_PIN_11
        |GPIO_PIN_8|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_FMC;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USER CODE BEGIN FMC_MspInit 1 */

    /* USER CODE END FMC_MspInit 1 */
}


void HAL_NOR_MspInit(NOR_HandleTypeDef* hnor){
    /* USER CODE BEGIN NOR_MspInit 0 */

    /* USER CODE END NOR_MspInit 0 */
    HAL_FMC_MspInit();
    /* USER CODE BEGIN NOR_MspInit 1 */

    /* USER CODE END NOR_MspInit 1 */
}
void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* hsdram){
    /* USER CODE BEGIN SDRAM_MspInit 0 */

    /* USER CODE END SDRAM_MspInit 0 */
    HAL_FMC_MspInit();
    /* USER CODE BEGIN SDRAM_MspInit 1 */

    /* USER CODE END SDRAM_MspInit 1 */
}

static uint32_t FMC_DeInitialized = 0;

static void HAL_FMC_MspDeInit(void){
    /* USER CODE BEGIN FMC_MspDeInit 0 */

    /* USER CODE END FMC_MspDeInit 0 */
    if (FMC_DeInitialized) {
        return;
    }
    FMC_DeInitialized = 1;
    /* Peripheral clock enable */
    __HAL_RCC_FMC_CLK_DISABLE();

    /** FMC GPIO Configuration
      PE4   ------> FMC_A20
      PE3   ------> FMC_A19
      PE1   ------> FMC_NBL1
      PE0   ------> FMC_NBL0
      PE5   ------> FMC_A21
      PE6   ------> FMC_A22
      PG15   ------> FMC_SDNCAS
      PD6   ------> FMC_NWAIT
      PD0   ------> FMC_D2
      PI4   ------> FMC_NBL2
      PD5   ------> FMC_NWE
      PD1   ------> FMC_D3
      PI3   ------> FMC_D27
      PI2   ------> FMC_D26
      PF0   ------> FMC_A0
      PI5   ------> FMC_NBL3
      PI7   ------> FMC_D29
      PI10   ------> FMC_D31
      PI6   ------> FMC_D28
      PD4   ------> FMC_NOE
      PH15   ------> FMC_D23
      PI1   ------> FMC_D25
      PF1   ------> FMC_A1
      PI9   ------> FMC_D30
      PH13   ------> FMC_D21
      PH14   ------> FMC_D22
      PI0   ------> FMC_D24
      PF2   ------> FMC_A2
      PC7   ------> FMC_NE1
      PF3   ------> FMC_A3
      PG8   ------> FMC_SDCLK
      PF4   ------> FMC_A4
      PH3   ------> FMC_SDNE0
      PF5   ------> FMC_A5
      PH2   ------> FMC_SDCKE0
      PD15   ------> FMC_D1
      PD10   ------> FMC_D15
      PD14   ------> FMC_D0
      PD9   ------> FMC_D14
      PD8   ------> FMC_D13
      PC0   ------> FMC_SDNWE
      PF12   ------> FMC_A6
      PG1   ------> FMC_A11
      PF15   ------> FMC_A9
      PD12   ------> FMC_A17
      PD13   ------> FMC_A18
      PG3   ------> FMC_A13
      PG2   ------> FMC_A12
      PH12   ------> FMC_D20
      PF13   ------> FMC_A7
      PG0   ------> FMC_A10
      PE8   ------> FMC_D5
      PD11   ------> FMC_A16
      PG5   ------> FMC_A15
      PG5   ------> FMC_BA1
      PG4   ------> FMC_A14
      PG4   ------> FMC_BA0
      PH9   ------> FMC_D17
      PH11   ------> FMC_D19
      PF14   ------> FMC_A8
      PF11   ------> FMC_SDNRAS
      PE9   ------> FMC_D6
      PE11   ------> FMC_D8
      PE14   ------> FMC_D11
      PH8   ------> FMC_D16
      PH10   ------> FMC_D18
      PE7   ------> FMC_D4
      PE10   ------> FMC_D7
      PE12   ------> FMC_D9
      PE15   ------> FMC_D12
    PE13   ------> FMC_D10
        */
        HAL_GPIO_DeInit(GPIOE, GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_0
                |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9
                |GPIO_PIN_11|GPIO_PIN_14|GPIO_PIN_7|GPIO_PIN_10
                |GPIO_PIN_12|GPIO_PIN_15|GPIO_PIN_13);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_1|GPIO_PIN_3
            |GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_4);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_6|GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_1
            |GPIO_PIN_4|GPIO_PIN_15|GPIO_PIN_10|GPIO_PIN_14
            |GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_12|GPIO_PIN_13
            |GPIO_PIN_11);

    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_5
            |GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_6|GPIO_PIN_1
            |GPIO_PIN_9|GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
            |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_12|GPIO_PIN_15
            |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_11);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_15|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_3
            |GPIO_PIN_2|GPIO_PIN_12|GPIO_PIN_9|GPIO_PIN_11
            |GPIO_PIN_8|GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_7|GPIO_PIN_0);

    /* USER CODE BEGIN FMC_MspDeInit 1 */

    /* USER CODE END FMC_MspDeInit 1 */
}

void HAL_NOR_MspDeInit(NOR_HandleTypeDef* hnor){
    /* USER CODE BEGIN NOR_MspDeInit 0 */

    /* USER CODE END NOR_MspDeInit 0 */
    HAL_FMC_MspDeInit();
    /* USER CODE BEGIN NOR_MspDeInit 1 */

    /* USER CODE END NOR_MspDeInit 1 */
}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* hsdram){
    /* USER CODE BEGIN SDRAM_MspDeInit 0 */

    /* USER CODE END SDRAM_MspDeInit 0 */
    HAL_FMC_MspDeInit();
    /* USER CODE BEGIN SDRAM_MspDeInit 1 */

    /* USER CODE END SDRAM_MspDeInit 1 */
}


/**
 * @brief QSPI MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hqspi: QSPI handle pointer
 * @retval None
 */
void HAL_QSPI_MspInit(QSPI_HandleTypeDef* hqspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hqspi->Instance==QUADSPI)
    {
        /* USER CODE BEGIN QUADSPI_MspInit 0 */
        __HAL_RCC_QSPI_FORCE_RESET();
        __HAL_RCC_QSPI_RELEASE_RESET();

        /* USER CODE END QUADSPI_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_QSPI_CLK_ENABLE();

        __HAL_RCC_GPIOF_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**QUADSPI GPIO Configuration
          PF7     ------> QUADSPI_BK1_IO2
          PF6     ------> QUADSPI_BK1_IO3
          PF10     ------> QUADSPI_CLK
          PF9     ------> QUADSPI_BK1_IO1
          PF8     ------> QUADSPI_BK1_IO0
          PB10     ------> QUADSPI_BK1_NCS
          */
        GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* QUADSPI interrupt Init */
        HAL_NVIC_SetPriority(QUADSPI_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(QUADSPI_IRQn);
        /* USER CODE BEGIN QUADSPI_MspInit 1 */

        /* USER CODE END QUADSPI_MspInit 1 */
    }

}

/**
 * @brief QSPI MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hqspi: QSPI handle pointer
 * @retval None
 */
void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* hqspi)
{
    if(hqspi->Instance==QUADSPI)
    {
        /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

        /* USER CODE END QUADSPI_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_QSPI_CLK_DISABLE();

        /**QUADSPI GPIO Configuration
          PF7     ------> QUADSPI_BK1_IO2
          PF6     ------> QUADSPI_BK1_IO3
          PF10     ------> QUADSPI_CLK
          PF9     ------> QUADSPI_BK1_IO1
          PF8     ------> QUADSPI_BK1_IO0
          PB10     ------> QUADSPI_BK1_NCS
          */
        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_9
                |GPIO_PIN_8);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);

        /* QUADSPI interrupt DeInit */
        HAL_NVIC_DisableIRQ(QUADSPI_IRQn);
        /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

        /* USER CODE END QUADSPI_MspDeInit 1 */
    }

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
 * @brief CAN MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hcan: CAN handle pointer
 * @retval None
 */
void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hcan->Instance==CAN2)
    {
        /* USER CODE BEGIN CAN2_MspInit 0 */

        /* USER CODE END CAN2_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_CAN2_CLK_ENABLE();
        __HAL_RCC_CAN1_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**CAN2 GPIO Configuration
          PB13     ------> CAN2_TX
          PB12     ------> CAN2_RX
          */
        GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* CAN2 interrupt Init */
        HAL_NVIC_SetPriority(CAN2_TX_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN2_TX_IRQn);
        HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
        HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
        HAL_NVIC_SetPriority(CAN2_SCE_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN2_SCE_IRQn);
        /* USER CODE BEGIN CAN2_MspInit 1 */

        /* USER CODE END CAN2_MspInit 1 */
    }

}

/**
 * @brief CAN MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hcan: CAN handle pointer
 * @retval None
 */
void HAL_CAN_MspDeInit(CAN_HandleTypeDef* hcan)
{
    if(hcan->Instance==CAN2)
    {
        /* USER CODE BEGIN CAN2_MspDeInit 0 */

        /* USER CODE END CAN2_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_CAN2_CLK_DISABLE();
        __HAL_RCC_CAN1_CLK_DISABLE();

        /**CAN2 GPIO Configuration
          PB13     ------> CAN2_TX
          PB12     ------> CAN2_RX
          */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_12);

        /* CAN2 interrupt DeInit */
        HAL_NVIC_DisableIRQ(CAN2_TX_IRQn);
        HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
        HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
        HAL_NVIC_DisableIRQ(CAN2_SCE_IRQn);
        /* USER CODE BEGIN CAN2_MspDeInit 1 */

        /* USER CODE END CAN2_MspDeInit 1 */
    }

}

/**
 * @brief I2C MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if(hi2c->Instance==I2C1)
    {
        /* USER CODE BEGIN I2C1_MspInit 0 */

        /* USER CODE END I2C1_MspInit 0 */

        /** Initializes the peripherals clock
        */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
        PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**I2C1 GPIO Configuration
          PB8     ------> I2C1_SCL
          PB9     ------> I2C1_SDA
          */
        GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* Peripheral clock enable */
        __HAL_RCC_I2C1_CLK_ENABLE();
        /* I2C1 interrupt Init */
        HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
        HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
        /* USER CODE BEGIN I2C1_MspInit 1 */

        /* USER CODE END I2C1_MspInit 1 */
    }
    else if(hi2c->Instance==I2C2)
    {
        /* USER CODE BEGIN I2C2_MspInit 0 */

        /* USER CODE END I2C2_MspInit 0 */

        /** Initializes the peripherals clock
        */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C2;
        PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_RCC_GPIOH_CLK_ENABLE();
        /**I2C2 GPIO Configuration
          PH4     ------> I2C2_SCL
          PH5     ------> I2C2_SDA
          */
        GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
        HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

        /* Peripheral clock enable */
        __HAL_RCC_I2C2_CLK_ENABLE();
        /* I2C2 interrupt Init */
        HAL_NVIC_SetPriority(I2C2_EV_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);
        HAL_NVIC_SetPriority(I2C2_ER_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
        /* USER CODE BEGIN I2C2_MspInit 1 */

        /* USER CODE END I2C2_MspInit 1 */
    }
    else if(hi2c->Instance==I2C3)
    {
        /* USER CODE BEGIN I2C3_MspInit 0 */

        /* USER CODE END I2C3_MspInit 0 */

        /** Initializes the peripherals clock
        */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C3;
        PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOH_CLK_ENABLE();
        /**I2C3 GPIO Configuration
          PC9     ------> I2C3_SDA
          PH7     ------> I2C3_SCL
          */
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
        HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

        /* Peripheral clock enable */
        __HAL_RCC_I2C3_CLK_ENABLE();
        /* I2C3 interrupt Init */
        HAL_NVIC_SetPriority(I2C3_EV_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);
        HAL_NVIC_SetPriority(I2C3_ER_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);
        /* USER CODE BEGIN I2C3_MspInit 1 */

        /* USER CODE END I2C3_MspInit 1 */
    }
    else if(hi2c->Instance==I2C4)
    {
        /* USER CODE BEGIN I2C4_MspInit 0 */

        /* USER CODE END I2C4_MspInit 0 */

        /** Initializes the peripherals clock
        */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C4;
        PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**I2C4 GPIO Configuration
          PB7     ------> I2C4_SDA
          PB6     ------> I2C4_SCL
          */
        GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_I2C4;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* Peripheral clock enable */
        __HAL_RCC_I2C4_CLK_ENABLE();
        /* I2C4 interrupt Init */
        HAL_NVIC_SetPriority(I2C4_EV_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C4_EV_IRQn);
        HAL_NVIC_SetPriority(I2C4_ER_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C4_ER_IRQn);
        /* USER CODE BEGIN I2C4_MspInit 1 */

        /* USER CODE END I2C4_MspInit 1 */
    }

}

/**
 * @brief I2C MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
    if(hi2c->Instance==I2C1)
    {
        /* USER CODE BEGIN I2C1_MspDeInit 0 */

        /* USER CODE END I2C1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_I2C1_CLK_DISABLE();

        /**I2C1 GPIO Configuration
          PB8     ------> I2C1_SCL
          PB9     ------> I2C1_SDA
          */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

        /* I2C1 interrupt DeInit */
        HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
        /* USER CODE BEGIN I2C1_MspDeInit 1 */

        /* USER CODE END I2C1_MspDeInit 1 */
    }
    else if(hi2c->Instance==I2C2)
    {
        /* USER CODE BEGIN I2C2_MspDeInit 0 */

        /* USER CODE END I2C2_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_I2C2_CLK_DISABLE();

        /**I2C2 GPIO Configuration
          PH4     ------> I2C2_SCL
          PH5     ------> I2C2_SDA
          */
        HAL_GPIO_DeInit(GPIOH, GPIO_PIN_4);

        HAL_GPIO_DeInit(GPIOH, GPIO_PIN_5);

        /* I2C2 interrupt DeInit */
        HAL_NVIC_DisableIRQ(I2C2_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);
        /* USER CODE BEGIN I2C2_MspDeInit 1 */

        /* USER CODE END I2C2_MspDeInit 1 */
    }
    else if(hi2c->Instance==I2C3)
    {
        /* USER CODE BEGIN I2C3_MspDeInit 0 */

        /* USER CODE END I2C3_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_I2C3_CLK_DISABLE();

        /**I2C3 GPIO Configuration
          PC9     ------> I2C3_SDA
          PH7     ------> I2C3_SCL
          */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);

        HAL_GPIO_DeInit(GPIOH, GPIO_PIN_7);

        /* I2C3 interrupt DeInit */
        HAL_NVIC_DisableIRQ(I2C3_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C3_ER_IRQn);
        /* USER CODE BEGIN I2C3_MspDeInit 1 */

        /* USER CODE END I2C3_MspDeInit 1 */
    }
    else if(hi2c->Instance==I2C4)
    {
        /* USER CODE BEGIN I2C4_MspDeInit 0 */

        /* USER CODE END I2C4_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_I2C4_CLK_DISABLE();

        /**I2C4 GPIO Configuration
          PB7     ------> I2C4_SDA
          PB6     ------> I2C4_SCL
          */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

        /* I2C4 interrupt DeInit */
        HAL_NVIC_DisableIRQ(I2C4_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C4_ER_IRQn);
        /* USER CODE BEGIN I2C4_MspDeInit 1 */

        /* USER CODE END I2C4_MspDeInit 1 */
    }

}

/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if(huart->Instance==UART4)
    {
        /* USER CODE BEGIN UART4_MspInit 0 */

        /* USER CODE END UART4_MspInit 0 */

        /** Initializes the peripherals clock
        */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART4;
        PeriphClkInitStruct.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            Error_Handler();
        }

        /* Peripheral clock enable */
        __HAL_RCC_UART4_CLK_ENABLE();

        __HAL_RCC_GPIOC_CLK_ENABLE();
        /**UART4 GPIO Configuration
          PC11     ------> UART4_RX
          PC10     ------> UART4_TX
          */
        GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        /* UART4 interrupt Init */
        HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(UART4_IRQn);
        /* USER CODE BEGIN UART4_MspInit 1 */

        /* USER CODE END UART4_MspInit 1 */
    }
    else if(huart->Instance==UART5)
    {
        /* USER CODE BEGIN UART5_MspInit 0 */

        /* USER CODE END UART5_MspInit 0 */

        /** Initializes the peripherals clock
        */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART5;
        PeriphClkInitStruct.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            Error_Handler();
        }

        /* Peripheral clock enable */
        __HAL_RCC_UART5_CLK_ENABLE();

        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        /**UART5 GPIO Configuration
          PC12     ------> UART5_TX
          PD2     ------> UART5_RX
          */
        GPIO_InitStruct.Pin = GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        /* UART5 interrupt Init */
        HAL_NVIC_SetPriority(UART5_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(UART5_IRQn);
        /* USER CODE BEGIN UART5_MspInit 1 */

        /* USER CODE END UART5_MspInit 1 */
    }

}

/**
 * @brief UART MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
    if(huart->Instance==UART4)
    {
        /* USER CODE BEGIN UART4_MspDeInit 0 */

        /* USER CODE END UART4_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_UART4_CLK_DISABLE();

        /**UART4 GPIO Configuration
          PC11     ------> UART4_RX
          PC10     ------> UART4_TX
          */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_11|GPIO_PIN_10);

        /* UART4 interrupt DeInit */
        HAL_NVIC_DisableIRQ(UART4_IRQn);
        /* USER CODE BEGIN UART4_MspDeInit 1 */

        /* USER CODE END UART4_MspDeInit 1 */
    }
    else if(huart->Instance==UART5)
    {
        /* USER CODE BEGIN UART5_MspDeInit 0 */

        /* USER CODE END UART5_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_UART5_CLK_DISABLE();

        /**UART5 GPIO Configuration
          PC12     ------> UART5_TX
          PD2     ------> UART5_RX
          */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

        /* UART5 interrupt DeInit */
        HAL_NVIC_DisableIRQ(UART5_IRQn);
        /* USER CODE BEGIN UART5_MspDeInit 1 */

        /* USER CODE END UART5_MspDeInit 1 */
    }

}


#else
/**
 * @brief CAN MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hcan: CAN handle pointer
 * @retval None
 */
void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hcan->Instance==CAN1)
    {
        /* USER CODE BEGIN CAN1_MspInit 0 */

        /* USER CODE END CAN1_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_CAN1_CLK_ENABLE();
#ifdef STM32F765xx
        __HAL_RCC_GPIOD_CLK_ENABLE();
#else
#ifdef STM32F769xx
        __HAL_RCC_GPIOB_CLK_ENABLE();
#endif
#endif
        /**CAN1 GPIO Configuration
          PD0     ------> CAN1_RX
          PD1     ------> CAN1_TX
          */
        GPIO_InitStruct.Pin = CAN1_TX|CAN1_RX;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
        HAL_GPIO_Init(CAN1_PORT, &GPIO_InitStruct);

        /* CAN1 interrupt Init */
        HAL_NVIC_SetPriority(CAN1_TX_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
        HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
        HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
        HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
        /* USER CODE BEGIN CAN1_MspInit 1 */

        /* USER CODE END CAN1_MspInit 1 */
    }
    else if(hcan->Instance==CAN3)
    {
        __HAL_RCC_CAN3_CLK_ENABLE();
#ifdef STM32F765xx
        __HAL_RCC_GPIOB_CLK_ENABLE();
#else
#ifdef STM32F769xx
        __HAL_RCC_GPIOB_CLK_ENABLE();
#endif
#endif
        GPIO_InitStruct.Pin = CAN3_TX|CAN3_RX;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_CAN3;
        HAL_GPIO_Init(CAN3_PORT, &GPIO_InitStruct);
        HAL_NVIC_SetPriority(CAN3_TX_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN3_TX_IRQn);
        HAL_NVIC_SetPriority(CAN3_RX0_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ(CAN3_RX0_IRQn);
        HAL_NVIC_SetPriority(CAN3_RX1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN3_RX1_IRQn);
        HAL_NVIC_SetPriority(CAN3_SCE_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN3_SCE_IRQn);
    }
    else if(hcan->Instance==CAN2)
    {
        __HAL_RCC_CAN1_CLK_ENABLE();
        __HAL_RCC_CAN2_CLK_ENABLE();
#ifdef STM32F765xx
        __HAL_RCC_GPIOB_CLK_ENABLE();
#else
#ifdef STM32F769xx
        __HAL_RCC_GPIOB_CLK_ENABLE();
#endif
#endif
        GPIO_InitStruct.Pin = CAN2_TX|CAN2_RX;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_CAN2 ;
        HAL_GPIO_Init(CAN2_PORT, &GPIO_InitStruct);
        HAL_NVIC_SetPriority(CAN2_TX_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN2_TX_IRQn);
        HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
        HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
        HAL_NVIC_SetPriority(CAN2_SCE_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN2_SCE_IRQn);
    }

}

/**
 * @brief CAN MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hcan: CAN handle pointer
 * @retval None
 */
void HAL_CAN_MspDeInit(CAN_HandleTypeDef* hcan)
{
    if(hcan->Instance==CAN1)
    {
        /* USER CODE BEGIN CAN1_MspDeInit 0 */

        /* USER CODE END CAN1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_CAN1_CLK_DISABLE();

        /**CAN1 GPIO Configuration
          PA11     ------> CAN1_RX
          PA12     ------> CAN1_TX
          */
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);

        /* CAN1 interrupt DeInit */
        HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
        HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
        HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
        HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
        /* USER CODE BEGIN CAN1_MspDeInit 1 */

        /* USER CODE END CAN1_MspDeInit 1 */
    }
    else if (hcan->Instance==CAN3)
    {

        __HAL_RCC_CAN3_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_4|GPIO_PIN_3);
        HAL_NVIC_DisableIRQ(CAN3_RX0_IRQn);
        HAL_NVIC_DisableIRQ(CAN3_RX1_IRQn);
    }
}

/**
 * @brief I2C MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hi2c->Instance==I2C1)
    {
        /* USER CODE BEGIN I2C1_MspInit 0 */

        /* USER CODE END I2C1_MspInit 0 */

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**I2C1 GPIO Configuration
          PB6     ------> I2C1_SCL
          PB7     ------> I2C1_SDA
          */
        GPIO_InitStruct.Pin = I2C1_SDA|I2C1_SCK;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
        HAL_GPIO_Init(I2C1_PORT, &GPIO_InitStruct);

        /* Peripheral clock enable */
        __HAL_RCC_I2C1_CLK_ENABLE();
        /* I2C1 DMA Init */
        /* I2C1_RX Init */
        hdma_i2c1_rx.Instance = DMA1_Stream0;
        hdma_i2c1_rx.Init.Channel = DMA_CHANNEL_1;
        hdma_i2c1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_i2c1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_i2c1_rx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_i2c1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_i2c1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_i2c1_rx.Init.Mode = DMA_NORMAL;
        hdma_i2c1_rx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_i2c1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_i2c1_rx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hi2c,hdmarx,hdma_i2c1_rx);

        /* I2C1_TX Init */
        hdma_i2c1_tx.Instance = DMA1_Stream6;
        hdma_i2c1_tx.Init.Channel = DMA_CHANNEL_1;
        hdma_i2c1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_i2c1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_i2c1_tx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_i2c1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_i2c1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_i2c1_tx.Init.Mode = DMA_NORMAL;
        hdma_i2c1_tx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_i2c1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_i2c1_tx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hi2c,hdmatx,hdma_i2c1_tx);
        /* I2C1 interrupt Init */
        HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
        HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
        /* USER CODE BEGIN I2C1_MspInit 1 */

        /* USER CODE END I2C1_MspInit 1 */
    }
    else if(hi2c->Instance==I2C2)
    {
        /* USER CODE BEGIN I2C2_MspInit 0 */

        /* USER CODE END I2C2_MspInit 0 */

        __HAL_RCC_GPIOF_CLK_ENABLE();
        /**I2C2 GPIO Configuration
          PF0     ------> I2C2_SDA
          PF1     ------> I2C2_SCL
          */
        GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        /* Peripheral clock enable */
        __HAL_RCC_I2C2_CLK_ENABLE();
        /* I2C2 DMA Init */
        /* I2C2_RX Init */
        hdma_i2c2_rx.Instance = DMA1_Stream2;
        hdma_i2c2_rx.Init.Channel = DMA_CHANNEL_7;
        hdma_i2c2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_i2c2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_i2c2_rx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_i2c2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_i2c2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_i2c2_rx.Init.Mode = DMA_NORMAL;
        hdma_i2c2_rx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_i2c2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_i2c2_rx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hi2c,hdmarx,hdma_i2c2_rx);

        /* I2C2_TX Init */
        hdma_i2c2_tx.Instance = DMA1_Stream4;
        hdma_i2c2_tx.Init.Channel = DMA_CHANNEL_8;
        hdma_i2c2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_i2c2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_i2c2_tx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_i2c2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_i2c2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_i2c2_tx.Init.Mode = DMA_NORMAL;
        hdma_i2c2_tx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_i2c2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_i2c2_tx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hi2c,hdmatx,hdma_i2c2_tx);
        /* I2C2 interrupt Init */
        HAL_NVIC_SetPriority(I2C2_EV_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);
        HAL_NVIC_SetPriority(I2C2_ER_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
        /* USER CODE BEGIN I2C2_MspInit 1 */

        /* USER CODE END I2C2_MspInit 1 */
    }

}

/**
 * @brief I2C MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
    if(hi2c->Instance==I2C1)
    {
        /* USER CODE BEGIN I2C1_MspDeInit 0 */

        /* USER CODE END I2C1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_I2C1_CLK_DISABLE();

        /**I2C1 GPIO Configuration
          PB6     ------> I2C1_SCL
          PB7     ------> I2C1_SDA
          */
        HAL_GPIO_DeInit(I2C1_PORT,I2C1_SDA);
        HAL_GPIO_DeInit(I2C1_PORT,I2C1_SCK);

        /* I2C1 DMA DeInit */
        HAL_DMA_DeInit(hi2c->hdmarx);
        HAL_DMA_DeInit(hi2c->hdmatx);

        /* I2C1 interrupt DeInit */
        HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
        /* USER CODE BEGIN I2C1_MspDeInit 1 */

        /* USER CODE END I2C1_MspDeInit 1 */
    }
    else if(hi2c->Instance==I2C2)
    {
        /* USER CODE BEGIN I2C2_MspDeInit 0 */

        /* USER CODE END I2C2_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_I2C2_CLK_DISABLE();

        /**I2C2 GPIO Configuration
          PF0     ------> I2C2_SDA
          PF1     ------> I2C2_SCL
          */
        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0);

        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_1);

        /* I2C2 DMA DeInit */
        HAL_DMA_DeInit(hi2c->hdmarx);
        HAL_DMA_DeInit(hi2c->hdmatx);

        /* I2C2 interrupt DeInit */
        HAL_NVIC_DisableIRQ(I2C2_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);
        /* USER CODE BEGIN I2C2_MspDeInit 1 */

        /* USER CODE END I2C2_MspDeInit 1 */
    }

}
/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(huart->Instance==USART6)
    {
        /* USER CODE BEGIN USART6_MspInit 0 */

        /* USER CODE END USART6_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_USART6_CLK_ENABLE();

        __HAL_RCC_GPIOC_CLK_ENABLE();
        /**USART6 GPIO Configuration
          PC6     ------> USART6_TX
          PC7     ------> USART6_RX
          */
        GPIO_InitStruct.Pin = UART6_TX |UART6_RX ;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
        HAL_GPIO_Init(UART6_PORT, &GPIO_InitStruct);

        /* USART6 DMA Init */
        /* USART6_RX Init */
        hdma_usart6_rx.Instance = DMA2_Stream1;
        hdma_usart6_rx.Init.Channel = DMA_CHANNEL_5;
        hdma_usart6_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_usart6_rx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_usart6_rx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_usart6_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_usart6_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_usart6_rx.Init.Mode = DMA_NORMAL;
        hdma_usart6_rx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_usart6_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_usart6_rx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(huart,hdmarx,hdma_usart6_rx);

        /* USART6_TX Init */
        hdma_usart6_tx.Instance = DMA2_Stream6;
        hdma_usart6_tx.Init.Channel = DMA_CHANNEL_5;
        hdma_usart6_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_usart6_tx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_usart6_tx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_usart6_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_usart6_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_usart6_tx.Init.Mode = DMA_NORMAL;
        hdma_usart6_tx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_usart6_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_usart6_tx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(huart,hdmatx,hdma_usart6_tx);

        /* USART6 interrupt Init */
        HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART6_IRQn);
        /* USER CODE BEGIN USART6_MspInit 1 */

        /* USER CODE END USART6_MspInit 1 */
    }
    if(huart->Instance==USART1)
    {
        /* USER CODE BEGIN USART6_MspInit 0 */

        /* USER CODE END USART6_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();
#ifdef STM32F769xx
        __HAL_RCC_GPIOA_CLK_ENABLE();
#endif
#ifdef STM32F765xx
        __HAL_RCC_GPIOB_CLK_ENABLE();
#endif
        /**USART6 GPIO Configuration
          PC6     ------> USART6_TX
          PC7     ------> USART6_RX
          */
        GPIO_InitStruct.Pin = UART1_TX |UART1_RX ;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(UART1_PORT, &GPIO_InitStruct);

        /* USART6 interrupt Init */
        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        /* USER CODE BEGIN USART6_MspInit 1 */

        /* USER CODE END USART6_MspInit 1 */
    }
}

/**
 * @brief UART MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
    if(huart->Instance==USART6)
    {
        /* USER CODE BEGIN USART6_MspDeInit 0 */

        /* USER CODE END USART6_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_USART6_CLK_DISABLE();

        /**USART6 GPIO Configuration
          PC6     ------> USART6_TX
          PC7     ------> USART6_RX
          */
        HAL_GPIO_DeInit(UART6_PORT, UART6_TX|UART6_RX);

        /* USART6 DMA DeInit */
        HAL_DMA_DeInit(huart->hdmarx);
        HAL_DMA_DeInit(huart->hdmatx);

        /* USART6 interrupt DeInit */
        HAL_NVIC_DisableIRQ(USART6_IRQn);
        /* USER CODE BEGIN USART6_MspDeInit 1 */

        /* USER CODE END USART6_MspDeInit 1 */
    }

}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram)
{
    GPIO_InitTypeDef gpio_init_structure;
    __HAL_RCC_FMC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
    gpio_init_structure.Pull      = GPIO_PULLUP;
    gpio_init_structure.Speed     = GPIO_SPEED_FAST;
    gpio_init_structure.Alternate = GPIO_AF12_FMC;
    gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8| GPIO_PIN_9 | GPIO_PIN_10 |\
                                GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOD, &gpio_init_structure);
    gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7| GPIO_PIN_8 | GPIO_PIN_9 |\
                                GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                                GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &gpio_init_structure);
    gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 |\
                                GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                                GPIO_PIN_15;
    HAL_GPIO_Init(GPIOF, &gpio_init_structure);
    gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4|\
                                GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOG, &gpio_init_structure);
    gpio_init_structure.Pin   = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 |\
                                GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                                GPIO_PIN_15;
    HAL_GPIO_Init(GPIOH, &gpio_init_structure);
    gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |\
                                GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10;
    HAL_GPIO_Init(GPIOI, &gpio_init_structure);
}
void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef *hsdram)
{
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3| GPIO_PIN_4 | GPIO_PIN_5     |\
            GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |\
            GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3| GPIO_PIN_4 | GPIO_PIN_7     |\
            GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |\
            GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
            GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 |\
            GPIO_PIN_5 | GPIO_PIN_10);
}
#endif



/**
 * @brief SPI MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hspi: SPI handle pointer
 * @retval None
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hspi->Instance==SPI1)
    {
#ifdef STM32F765xx

        /* USER CODE BEGIN SPI1_MspInit 0 */

        /* USER CODE END SPI1_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOG_CLK_ENABLE();
        /**SPI1 GPIO Configuration
          PA6     ------> SPI1_MISO
          PA7     ------> SPI1_MOSI
          PG11     ------> SPI1_SCK
          */
        GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

        /* SPI1 DMA Init */
        /* SPI1_RX Init */
        hdma_spi1_rx.Instance = DMA2_Stream0;
        hdma_spi1_rx.Init.Channel = DMA_CHANNEL_3;
        hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_spi1_rx.Init.Mode = DMA_NORMAL;
        hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_spi1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hspi,hdmarx,hdma_spi1_rx);

        /* SPI1_TX Init */
        hdma_spi1_tx.Instance = DMA2_Stream3;
        hdma_spi1_tx.Init.Channel = DMA_CHANNEL_3;
        hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_spi1_tx.Init.Mode = DMA_NORMAL;
        hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hspi,hdmatx,hdma_spi1_tx);

        /* SPI1 interrupt Init */
        HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(SPI1_IRQn);
        /* USER CODE BEGIN SPI1_MspInit 1 */
#endif
        /* USER CODE END SPI1_MspInit 1 */
    }

    else if(hspi->Instance==SPI2)
    {
        /* USER CODE BEGIN SPI1_MspInit 0 */

        /* USER CODE END SPI1_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_SPI2_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**SPI1 GPIO Configuration
          PA6     ------> SPI1_MISO
          PA7     ------> SPI1_MOSI
          PG11     ------> SPI1_SCK
          */
        GPIO_InitStruct.Pin = SPI2_MOSI|SPI2_MISO;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(SPI2_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = SPI2_SCK;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(SPI2_SCK_PORT, &GPIO_InitStruct);

        /* SPI1 DMA Init */
        /* SPI1_RX Init */
        hdma_spi2_rx.Instance = DMA2_Stream0;
        hdma_spi2_rx.Init.Channel = DMA_CHANNEL_3;
        hdma_spi2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_spi2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_spi2_rx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_spi2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_spi2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_spi2_rx.Init.Mode = DMA_NORMAL;
        hdma_spi2_rx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_spi2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hspi,hdmarx,hdma_spi2_rx);

        /* SPI1_TX Init */
        hdma_spi2_tx.Instance = DMA2_Stream3;
        hdma_spi2_tx.Init.Channel = DMA_CHANNEL_3;
        hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_spi2_tx.Init.Mode = DMA_NORMAL;
        hdma_spi2_tx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_spi2_tx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(hspi,hdmatx,hdma_spi2_tx);

        /* SPI1 interrupt Init */
        HAL_NVIC_SetPriority(SPI2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(SPI2_IRQn);
        /* USER CODE BEGIN SPI1_MspInit 1 */

        /* USER CODE END SPI1_MspInit 1 */


    }

}

/**
 * @brief SPI MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hspi: SPI handle pointer
 * @retval None
 */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
    if(hspi->Instance==SPI1)
    {
        /* USER CODE BEGIN SPI1_MspDeInit 0 */

        /* USER CODE END SPI1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_SPI1_CLK_DISABLE();

        /**SPI1 GPIO Configuration
          PA6     ------> SPI1_MISO
          PA7     ------> SPI1_MOSI
          PG11     ------> SPI1_SCK
          */
        HAL_GPIO_DeInit(SPI2_PORT, GPIO_PIN_6|GPIO_PIN_7);

        HAL_GPIO_DeInit(SPI2_SCK_PORT, SPI2_SCK);

        /* SPI1 DMA DeInit */
        HAL_DMA_DeInit(hspi->hdmarx);
        HAL_DMA_DeInit(hspi->hdmatx);

        /* SPI1 interrupt DeInit */
        HAL_NVIC_DisableIRQ(SPI1_IRQn);
        /* USER CODE BEGIN SPI1_MspDeInit 1 */

        /* USER CODE END SPI1_MspDeInit 1 */
    }
    else if(hspi->Instance==SPI2)
    {
        /* USER CODE BEGIN SPI1_MspDeInit 0 */

        /* USER CODE END SPI1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_SPI1_CLK_DISABLE();

        /**SPI1 GPIO Configuration
          PA6     ------> SPI1_MISO
          PA7     ------> SPI1_MOSI
          PG11     ------> SPI1_SCK
          */
        HAL_GPIO_DeInit(SPI2_PORT, SPI2_MOSI|SPI2_MISO);

        HAL_GPIO_DeInit(SPI2_SCK_PORT,SPI2_SCK);

        /* SPI1 DMA DeInit */
        HAL_DMA_DeInit(hspi->hdmarx);
        HAL_DMA_DeInit(hspi->hdmatx);

        /* SPI1 interrupt DeInit */
        HAL_NVIC_DisableIRQ(SPI2_IRQn);
        /* USER CODE BEGIN SPI1_MspDeInit 1 */

        /* USER CODE END SPI1_MspDeInit 1 */

    }

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
    RCC_OscInitTypeDef        RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

    /*##-1- Configue LSE/LSI as RTC clock soucre ###############################*/
#ifdef RTC_CLOCK_SOURCE_LSE
    RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /* Configures the External Low Speed oscillator (LSE) drive capability */
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_HIGH);
#elif defined (RTC_CLOCK_SOURCE_LSI)
    RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
#else
#error Please select the RTC Clock source inside the main.h file
#endif /*RTC_CLOCK_SOURCE_LSE*/

    /*##-2- Enable RTC peripheral Clocks #######################################*/
    /* Enable RTC Clock */
    __HAL_RCC_RTC_ENABLE();

    /*##-3- Configure the NVIC for RTC Alarm ###################################*/
    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0x0F, 0);
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
}

/**
 * @brief RTC MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 * @param hrtc: RTC handle pointer
 * @retval None
 */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc)
{
    /*##-1- Reset peripherals ##################################################*/
    __HAL_RCC_RTC_DISABLE();
}


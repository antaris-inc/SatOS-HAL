/**
 * @file           : main.c
 * @brief          : Main program body
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

#include <stdio.h>
#include "main.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "cmsis_os.h"
#include "exo_osal.h"
#include "qspi.h"
#include "exo_io_al_rtc_common.h"
#include "exo_io_al_sos_timer.h"
#include "exo_ahw_al_dt_common.h"
#include "exo_ahw_al_temp_sensor_common.h"
#include "exo_debug.h"

s_exo_debug exo_dbg_cb;
extern volatile uint8_t system_error;
volatile uint8_t debug_cb_idx=0;
volatile uint8_t disable_wdt=0;

FMC_SDRAM_TimingTypeDef  SDRAM_Timing;
FMC_SDRAM_CommandTypeDef command;
SDRAM_HandleTypeDef hsdram1;
NOR_HandleTypeDef hnor1;
IWDG_HandleTypeDef hiwdg;
WWDG_HandleTypeDef hwwdg;

extern QSPI_HandleTypeDef hqspi;
extern QSPI_InfoTypeDef QspiInfo;

DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;
DMA_HandleTypeDef hdma_i2c2_rx;
DMA_HandleTypeDef hdma_i2c2_tx;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi2_rx;
DMA_HandleTypeDef hdma_spi2_tx;
DMA_HandleTypeDef hdma_usart6_rx;
DMA_HandleTypeDef hdma_usart6_tx;

ahw_al_temp_sensor_hdl ahw_ts_obc;
float temperature_value;

/**
 * @brief Global variable for flight mode
 */
volatile uint8_t flight_mode = 1;

/**
 * @brief Define the watchdog enable or disable
 */
#ifdef WDT_ENABLE
volatile uint8_t WDT_ENB =1;
#else
volatile uint8_t WDT_ENB =0;
#ifdef COREBOARD
#error "WDT Disabled"
#endif
#endif

/**
 * @brief Define the core board configuration
 */
#ifdef STM32F765xx
volatile uint8_t BOARD = 1;
#else
#warning  "#####################This is not compiled for CORE BOARD #######################"
volatile uint8_t BOARD = 0;
#endif

/**
 * @Brief Enable or disable the UART print
 */
#ifndef PRINT_UART_4
#ifndef PRINT_UART_5
volatile uint8_t PRINT_ENB=1;
#endif
#endif
#ifdef PRINT_UART_4
#ifndef PRINT_UART_5
volatile uint8_t PRINT_ENB=0;
#endif
#endif
#ifndef PRINT_UART_4
#ifdef PRINT_UART_5
volatile uint8_t PRINT_ENB=0;
#endif
#endif

/**
 * @brief Enable or disable Bootloader
 */
#ifdef BTLR_ON
volatile uint8_t BOOTLOADER =1;
#else
volatile uint8_t BOOTLOADER =0;
#endif

/**
 * @brief Configure the interface for ground station communication.
 */
#ifndef GSOBC_USB_EN
#ifdef COREBOARD
#error    "################### GS via Ethernet was enabled, so PS based validaiton cannot be performed #####################"
#endif
volatile uint8_t GS_OBC_VIA_USB_DISABLE=1;
#else
volatile uint8_t GS_OBC_VIA_USB_DISABLE =0;
#endif

/**
 * @brief Configure the interface for payload communication.
 */
#ifndef PSOBC_ETH_EN
volatile uint8_t PS_OBC_VIA_ETH_DISABLE =1;
#else
#ifdef COREBOARD
#error   "################### PS via Ethernet was enabled, #####################"
#endif
volatile uint8_t PS_OBC_VIA_ETH_DISABLE =0;
#endif

/**
 * @brief Configure the coreboard communication.
 */
#ifndef S_BAND_SIM_CB
volatile uint8_t CORE_BRD_S_BAND_SIM_DISABLE =1;
#else
#ifdef COREBOARD
#error  "################### S_BAND Simulator was enabled #####################"
#endif
volatile uint8_t CORE_BRD_S_BAND_SIM_DISABLE =0;
#endif

/**
 * @brief Configure the socket interface.
 */
#ifndef CAN_BYPASS
volatile uint8_t CAN_BYPASS_SOCK_DISABLE =1;
#else
#ifdef COREBOARD
#error  "################### CAN Bypass mode enabled #####################"
#endif
#endif

/**
 * @brief Configure EPS default state.
 */
#ifdef EPS_HRM_ON_DFLT
volatile uint8_t EPS_HRM_ON_DEFLT =1;
#else
#ifdef COREBOARD
#error  "################### HRM ON was disabled  #####################"
#endif
volatile uint8_t EPS_HRM_ON_DEFLT =0;
#endif

/**
 * @brief Configure payload server default state.
 */
#ifndef EPS_PS_ON_DFLT
volatile uint8_t EPS_PS_ON_DEFLT_DISABLE =1;
#else
#ifdef COREBOARD
#error  "################### PS ON was default enabled  #####################"
#endif
volatile uint8_t EPS_PS_ON_DEFLT_DISABLE =0;
#endif

/**
 * @brief Disable heat sink
 */
#ifdef HEAT_SINK_DISABLE
#error  "################### HEAT SINK Auto ON/OFF was disabled   #####################"
#endif

/* Buffer used for displaying Time */
uint8_t aShowTime[50] = {0};
extern ioal_rtc_hdle ioal_hrtc;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)P_DEFAULT_PRIO,
};

/**
 * @brief This function is configure the system clock.
 */
void SystemClock_Config(void);
/**
 * @brief This function for test task entry.
 */
void StartDefaultTask(void *argument);
/**
 * @brief Function to initialize DMA controller.
 */
void MX_DMA_Init(void);

/**
 * @brief This function initialize the GPIO controller.
 */
static void MX_GPIO_Init(void);
/**
 * @brief This function is initialize the FMC.
 */
static void MX_FMC_Init(void);

/**
 * @brief This function initialize the SDRAM sequence.
 */
static void BSP_SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram1, FMC_SDRAM_CommandTypeDef *Command);

/**
 * @brief This function is initialize the FMC SDRAM.
 */
int8_t fmc_sdram_init();
void nvm_test();
void sns_dummy_simu();
/**
 * @brief This function is use to print the build macros.
 */
void build_macro_print();

os_timer_handle_ptr early_wdt_catch_tmr;

uint8_t kernel_init_done=0;
uint32 i = 0;
uint32_t start_time =0;
uint32_t total_time =0;
/**
 * @brief Application entry point.
 * @retval int
 */
int main(void)
{
    if(0 == flight_mode)
    {
        disable_wdt = 1;
        CAN_BYPASS_SOCK_DISABLE = 0;
        EPS_HRM_ON_DEFLT = 0;
        EPS_PS_ON_DEFLT_DISABLE = 0;
    }

    HAL_Init();
    SystemClock_Config();
    start_time = HAL_GetTick();
    hal_init();
    MX_GPIO_Init();
    __enable_irq();
    MX_DMA_Init();
#if defined(COREBOARD) || defined(STM32F769xx)
    HAL_NOR_MspDeInit(&hnor1);
    MX_FMC_Init();
    fmc_sdram_init();
    qspi_init(&hqspi,&QspiInfo);
#endif
    osKernelInitialize();
#ifdef	MEM_DEBUG_ENB
    mem_debug_tracker_init();
#endif
    os_memcpy_fw_init(&hnor1,&hqspi);
    build_macro_print();
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
    /* Start scheduler */
    kernel_init_done = 1;
    total_time = (HAL_GetTick()-start_time);
    printf("HAL init total time taken : %lu ms\n",total_time);
    total_time=0xFFFFFFFF;
    start_time = HAL_GetTick();
    osKernelStart();
    while (1)
    {
    }
}

/**
 * @brief This function is use to print the build macros.
 */
void build_macro_print(void)
{
    printf("Flight Mode Enable stats %d",flight_mode);
    printf("WDT_ENB==%d\n",WDT_ENB);
    printf("BOARD==%d\n",BOARD);
    printf("EPS_PS_ON_DEFLT_DISABLE==%d\n",EPS_PS_ON_DEFLT_DISABLE);
    printf("EPS_HRM_ON_DEFLT==%d\n",EPS_HRM_ON_DEFLT);
    printf("CAN_BYPASS_SOCK_DISABLE==%d\n",CAN_BYPASS_SOCK_DISABLE);
    printf("GS_OBC_VIA_USB_DISABLE==%d\n",GS_OBC_VIA_USB_DISABLE);
    printf("CORE_BRD_S_BAND_SIM_DISABLE==%d\n",CORE_BRD_S_BAND_SIM_DISABLE);
    printf("PRINT_ENB==%d\n",PRINT_ENB);
    printf("BOOTLOADER==%d\n",BOOTLOADER);
    printf("PS_OBC_VIA_ETH_DISABLE==%d\n",PS_OBC_VIA_ETH_DISABLE);
}

void obc_temperature_sns_init()
{
    ahw_ts_obc.event_mode = TEMP_SENSE_EVENT_NONE;
    ahw_ts_obc.critical_temp_threshold = 75;
    ahw_ts_obc.high_temp_threshold= 70;
    ahw_ts_obc.low_temp_threshold = 0;
    ahw_ts_obc.hysteresis = HYS_0_0;
    ahw_ts_obc.win_lock = WIN_UNLOCK_0;
    ahw_ts_obc.resolution = RES_0_25;
    ahw_ts_obc.mode_of_operation = TEMP_SENSE_CONTINUOUS_CONVERSTION;
    ahw_ts_obc.polarity = TEMP_SENSE_ACTIVE_LOW;
    ahw_al_temp_sensor_init(&ahw_ts_obc,TEMP_SENSOR_MCP9843_OBC);
}

/**
 * @brief This function for test task entry.
 */
void StartDefaultTask(void *argument)
{
    obc_temperature_sns_init();
    for(;;)
    {
#ifdef STM32F769xx
        HAL_GPIO_TogglePin(GPIOJ, GPIO_PIN_13);
#endif
        osDelay(1000);
        ahw_al_temp_sensor_gettemperature(&ahw_ts_obc,&temperature_value);
        printf("OBC Temperature sensor value = %d \n",(int)temperature_value);
    }
}
/**
 * @brief This function is initialize the FMC SDRAM.
 */
int8_t fmc_sdram_init()
{
    BSP_SDRAM_Initialization_Sequence(&hsdram1, &command);
    return 0;
}
/**
 * @brief System Clock Configuration
 * @retval None
 */
#if defined(COREBOARD) || defined(STM32F765xx)
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 400;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 5;
    RCC_OscInitStruct.PLL.PLLR = 2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Activate the Over-Drive mode
    */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_4);
}

#else

/**
 * @brief This function is configure the system clock.
 */
void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 400;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    if(ret != HAL_OK)
    {
        while(1) { ; }
    }
    ret = HAL_PWREx_EnableOverDrive();
    if(ret != HAL_OK)
    {
        while(1) { ; }
    }
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
    if(ret != HAL_OK)
    {
        while(1) { ; }
    }
}
#endif

/**
 * @brief This function initialize the GPIO controller.
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOK_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();

#ifdef STM32F769xx
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_5, GPIO_PIN_RESET);
    /*Configure GPIO pin : PJ13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    //configuring interrupt pin for EPS error flag
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,5 , 5);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

#endif

#ifdef COREBOARD

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOK, GPIO_PIN_5, GPIO_PIN_SET);

    /*Configure GPIO pin : PK5 */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_12, GPIO_PIN_RESET);

    /*Configure GPIO pin : PK5 */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);
    /*Configure GPIO pin : PA8 */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    //configuring interrupt pin for EPS error flag
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 5);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOK_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOK, GPIO_PIN_6, GPIO_PIN_RESET);

    /*Configure GPIO pin : PK6 */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_10, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 5);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    HAL_NVIC_SetPriority(EXTI2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 5);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 5);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
#endif
}

/**
 * @brief Function to initialize DMA controller.
 */
void MX_DMA_Init(void)
{

    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA1_Stream0_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
    /* DMA1_Stream2_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
    /* DMA1_Stream4_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
    /* DMA1_Stream6_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
    /* DMA2_Stream0_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
    /* DMA2_Stream1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
    /* DMA2_Stream3_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
    /* DMA2_Stream6_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

}

#if defined(COREBOARD) || defined(STM32F769xx)
/**
 * @brief This function is initialize the FMC.
 */
static void MX_FMC_Init(void)
{
#ifdef COREBOARD
    FMC_NORSRAM_TimingTypeDef Timing = {0};

    hnor1.Instance = FMC_NORSRAM_DEVICE;
    hnor1.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
    /* hnor1.Init */
    hnor1.Init.NSBank = FMC_NORSRAM_BANK1;
    hnor1.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
    hnor1.Init.MemoryType = FMC_MEMORY_TYPE_NOR;
    hnor1.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
    hnor1.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
    hnor1.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
    hnor1.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
    hnor1.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
    hnor1.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
    hnor1.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
    hnor1.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_ENABLE;
    hnor1.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
    hnor1.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
    hnor1.Init.WriteFifo = FMC_WRITE_FIFO_ENABLE;
    hnor1.Init.PageSize = FMC_PAGE_SIZE_NONE;
    /* Timing */
    Timing.AddressSetupTime = 4;
    Timing.AddressHoldTime = 15;
    Timing.DataSetupTime = 20;
    Timing.BusTurnAroundDuration = 1;
    Timing.CLKDivision = 16;
    Timing.DataLatency = 17;
    Timing.AccessMode = FMC_ACCESS_MODE_A;
    /* ExtTiming */

    if (HAL_NOR_Init(&hnor1, &Timing, NULL) != HAL_OK)
    {
        Error_Handler( );
    }
#endif
    FMC_SDRAM_TimingTypeDef SdramTiming = {0};

    hsdram1.Instance = FMC_SDRAM_DEVICE;
    /* hsdram1.Init */
    hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
#ifdef COREBOARD
    hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
    hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
#else
#ifdef STM32F769xx
    hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
    hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
#endif
#endif
    hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
    hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;   //3
    hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;   //SDCLOCK_PERIOD
    hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
    hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
    /* SdramTiming */
    SdramTiming.LoadToActiveDelay = 2;
    SdramTiming.ExitSelfRefreshDelay = 6;
    SdramTiming.SelfRefreshTime = 4;
    SdramTiming.RowCycleDelay = 6;
    SdramTiming.WriteRecoveryTime = 2;
    SdramTiming.RPDelay = 2;
    SdramTiming.RCDDelay = 2;

    if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
    {
        Error_Handler( );
    }
    /* USER CODE BEGIN FMC_Init 2 */

    /* USER CODE END FMC_Init 2 */
}
#endif


/**
 * @brief This function initialize the SDRAM sequence.
 */
static void BSP_SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram1, FMC_SDRAM_CommandTypeDef *Command)
{
    __IO uint32_t tmpmrd =0;
    /* Step 3:  Configure a clock configuration enable command */
    Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command->AutoRefreshNumber = 1;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram1, Command, SDRAM_TIMEOUT);

    /* Step 4: Insert 100 us minimum delay */
    /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
    HAL_Delay(1);

    /* Step 5: Configure a PALL (precharge all) command */
    Command->CommandMode = FMC_SDRAM_CMD_PALL;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command->AutoRefreshNumber = 1;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram1, Command, SDRAM_TIMEOUT);

    /* Step 6 : Configure a Auto-Refresh command */
    Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command->AutoRefreshNumber = 8;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram1, Command, SDRAM_TIMEOUT);

    /* Step 7: Program the external memory mode register */
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
        SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
        SDRAM_MODEREG_CAS_LATENCY_2           |
        SDRAM_MODEREG_OPERATING_MODE_STANDARD |
        SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Command->AutoRefreshNumber = 1;
    Command->ModeRegisterDefinition = tmpmrd;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram1, Command, SDRAM_TIMEOUT);

    /* Step 8: Set the refresh rate counter */
    /* (15.62 us x Freq) - 20 */
    /* Set the device refresh counter */
    hsdram1->Instance->SDRTR |= ((uint32_t)((1292)<< 1));

}

/**
 * @brief Function for error handler.
 */
void exo_err_hdlr(uint8_t err_no)
{
    while(1)
    {
    }
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    while(1)
    {
    }
}
/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM1 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1) {
        HAL_IncTick();
    }
}



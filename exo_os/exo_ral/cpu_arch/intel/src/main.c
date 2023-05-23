/**
 * @file main.c
 *
 * @brief This file contains definitions for application main.
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

#include <unistd.h>
#include <stdio.h>
#include "exo_hal_common.h"
#include "exo_debug.h"
#include "exo_io_al_sos_timer.h"
#include "exo_common.h"

/**
 * @brief Test function
 */
void ral_main();

/**
 * @brief Global variables for thread and IPC operations
 */
s_exo_debug exo_dbg_cb;

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
volatile uint8_t BOARD = 0;
#endif

/**
 * @Brief Enable or disable the UART print
 */
#ifndef PRINT_UART_4                /*!< Enable print in UART_4 */
#ifndef PRINT_UART_5                /*!< Enable print in UART_5 */
volatile uint8_t PRINT_ENB=1;       /*!< Enable print */
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
#ifdef COREBOARD
#warning  "################### Bootloader was disabled#####################"
//#error   "################### Bootloader was disabled#####################"
#endif
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



void app_init(void *args)
{
    printf("app_init*************************\n");
}

/**
 * @brief Application main for linux.
 */
int main()
{
    //nvm_flash_drive_init();
    rtc_nvm_reload();

    //osal_test();
    hal_init();
    ral_main();
    //adcs_csw_main();
    //comms_csw_init();
    //xband_init();
    //eps_init();
    //tc_tm_sample_mfcc_sock_main();
    //tc_tm_mngr_main();
    //conops_sch_init();
    //obc_main_init();
    while(1)
    {
        //printf("\n EXO Idle Task routine running");
        sleep(3);
    }
    return(0);
}


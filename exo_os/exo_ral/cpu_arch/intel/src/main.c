/**
 * @file main.c
 *
 * @brief This file contains definitions for application main.
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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include "exo_hal_common.h"
#include "exo_debug.h"
#include "exo_io_al_sos_timer.h"
#include "exo_common.h"
#include "comms_uhf_main.h"
#include "csp_comms.h"

extern s_obc_sock_info obc_gs2_soc_inf;
extern s_obc_sock_info sludp_tctm_soc_inf;

void sock_info_init(void);

/**
 * @brief Test function
 */
void ral_main();

s_exo_debug exo_dbg_cb; ///< Global variables for thread and IPC operations
char *lnx_uart_com_port; ///< UART COM PORT to communicate UHF board in Linux environment
volatile uint8_t flight_mode = 1; ///< Global variable for flight mode

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
#ifndef PRINT_UART_5                /*!< Enable print in UART_5 */
volatile uint8_t PRINT_ENB=1;       /*!< Enable print */
#endif
#ifdef PRINT_UART_5
volatile uint8_t PRINT_ENB=0;
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
    sock_info_init();
    rtc_nvm_reload();

    //osal_test();
    hal_init();
    ral_main();
    CSP_Setup();
    comms_uhf_csw_init();
    while(1)
    {
        //printf("\n EXO Idle Task routine running");
        sleep(3);
    }
    return(0);
}


void sock_info_init()
{
    /** Read the JSON config file */
    FILE *fp = fopen("obc_soc_cfg.json", "r");
    if (!fp) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *data = malloc(length+1);
    if (!data) {
        perror("Unable to allocate memory");
        exit(EXIT_FAILURE);
    }

    fread(data, 1, length, fp);
    fclose(fp);

    /** Load the JSON data */
    json_error_t error;
    json_t *root = json_loads(data, 0, &error);
    free(data);

    if (!root) {
        fprintf(stderr, "Error parsing JSON data: %s\n", error.text);
        exit(EXIT_FAILURE);
    }

    /** Get all the subsystems */
    json_t *nodes_array = json_object_get(root, "subsystem");
    if (!json_is_array(nodes_array)) {
        fprintf(stderr, "Error finding 'nodes' array in JSON data\n");
        json_decref(root);
        exit(EXIT_FAILURE);
    }

    size_t index;
    json_t *node_obj;
    /** Iterate through all the subsystems */
    json_array_foreach(nodes_array, index, node_obj) 
    {
        /** - Retrieve the name from the configuration */
        json_t *name_obj = json_object_get(node_obj, "name");

        /** - Retrieve the ip address from the configuration */
        json_t *ip_obj = json_object_get(node_obj, "ip_address");

        /** - Retrieve the port from the configuration */
        json_t *port_obj = json_object_get(node_obj, "port");

        /** - Retrieve the port from the configuration */
        json_t *com_port_obj = json_object_get(node_obj, "com_port");

        /** - Convert the name object into string */
        const char *name = json_string_value(name_obj);

        /** - Convert the ip address object into string */
        const char *ip_address = json_string_value(ip_obj);

        /** - Convert the port object address object into integer */
        unsigned short port = json_integer_value(port_obj);

        /** - Convert the com port object into string */
        const char *com_port = json_string_value(com_port_obj);

        /** - Compare the configuration name */
        if(0 == strcmp(name,"OBC<->UHF"))
        {
            /**  - Copy the IP address from local variable to global config struct */
            strcpy(obc_uhf_soc_inf.ip_addr, ip_address);

            /**  - Copy the port from local variable to global config struct */
            obc_uhf_soc_inf.port= port;
        }
        /** - Compare the configuration name */
        else if(0 == strcmp(name,"LNX_UART_COM_PORT"))
        {
            lnx_uart_com_port = malloc(strlen(com_port) + 1);  // +1 for the null terminator
            /**  - Copy the COM port */
            strcpy(lnx_uart_com_port, com_port);
        }
#if 0
        else if(0 == strcmp(name,"OBC<->BK"))
        {
            /**  - Copy the IP address from local variable to global config struct */
            strcpy(obc_gs2_soc_inf.ip_addr, ip_address);

            /**  - Copy the port from local variable to global config struct */
            obc_gs2_soc_inf.port= port;

            /**  - Copy the IP address from local variable to global config struct */
            strcpy(sludp_tctm_soc_inf.ip_addr, ip_address);

            /**  - Copy the port from local variable to global config struct */
            sludp_tctm_soc_inf.port = port;
        }
#endif
        else
        {
            /** - Invalid configuration */
        }
    }
    DEBUG_CPRINT(("\n UHF SOC IP =%s Port =%d\n",obc_uhf_soc_inf.ip_addr,obc_uhf_soc_inf.port));
}

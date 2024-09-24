/**
 * @file exo_hal_common.c
 *
 * @brief This file contains structures,enumerations,function declaration for HAL
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

#define ALL_INTF_ENB

#include <stdio.h>
#include <unistd.h>
#include "exo_hal_common.h"
#include "exo_io_al_common.h"
#include "exo_ahw_al_common.h"
#include "exo_io_al_can_common.h"
#include "exo_io_al_uart_common.h"
#include "exo_io_al_spi_common.h"
#include "exo_io_al_rtc_common.h"
#include "exo_io_al_usb_common.h"
#include "exo_io_al_i2c_common.h"
#include "exo_io_al_eth_common.h"

/**
 * @brief This API initialize the HAL
 */
void hal_init(void)
{
#ifdef LINUX_TEMP_PORT
    printf("\n EXO HAL Framework Initialise");
    usleep(100000);
#endif
    ahw_io_lookup_table_updt();
    io_hal_init();
    io_ahw_hal_intr_init();
    ah_hal_init();
#ifdef LINUX_TEMP_PORT
    printf("\n EXO HAL Framework Initialisation completed successfully");
#endif
}

/**
 * @brief This API is error handler
 */
void ioal_error_handler(void)
{
    // Placeholder for interface error handling
    return;
}

/**
 * @brief This is dummy function for linux
 */
void linux_dummy_fn(void* arg)
{
}
/**
 * @brief Application callback registration function for HAL
 */

hal_ret_sts ahal_register_io_cb(ahw_al_gen_info* ahal_info, uint8 cb_id,void (*cb_fptr)(void* args),uint8 cb_context)
{
    hal_ret_sts sts=HAL_SCS;
    switch(ahal_info->io_intf_id)
    {
        case IOAL_INST_I2C1:
        case IOAL_INST_I2C2:
        case IOAL_INST_I2C3:
        case IOAL_INST_I2C4:
        {
            switch(cb_id)
            {
                case I2C_MST_TX_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.i2c_callbacks.i2c_mst_tx_cplt_cb=cb_fptr;
                    break;
                case I2C_MST_RX_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.i2c_callbacks.i2c_mst_rx_cplt_cb=cb_fptr;
                    break;
                case I2C_ABORT_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.i2c_callbacks.i2c_abort_cplt_cb=cb_fptr;
                    break;
                case I2C_LISTEN_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.i2c_callbacks.i2c_listen_cplt_cb=cb_fptr;
                    break;
                case I2C_ERROR_CB:
                    ahal_info->intr_hdl.io_cb_list.i2c_callbacks.i2c_error_cb=cb_fptr;
                    break;
                default:
                    sts=HAL_IO_INVLD_INST_ID;
                    break;
            }
            break;
        }
        case IOAL_INST_SPI1:
        case IOAL_INST_SPI2:
        {
            switch(cb_id)
            {
                case SPI_TX_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.spi_callbacks.spi_tx_cplt_cb=cb_fptr;
                    break;
                case SPI_RX_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.spi_callbacks.spi_rx_cplt_cb=cb_fptr;
                    break;
                case SPI_TX_RX_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.spi_callbacks.spi_tx_rx_cplt_cb=cb_fptr;
                    break;
                case SPI_ABORT_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.spi_callbacks.spi_abort_cplt_cb=cb_fptr;
                    break;
                case SPI_ERROR_CB:
                    ahal_info->intr_hdl.io_cb_list.spi_callbacks.spi_error_cb=cb_fptr;
                    break;
                default:
                    sts=HAL_IO_INVLD_INST_ID;
                    break;
            }
            break;
        }
        case IOAL_INST_UART1:
        case IOAL_INST_UART2:
        case IOAL_INST_UART3:
        case IOAL_INST_UART4:
        case IOAL_INST_UART5:
        case IOAL_INST_UART6:

        {
            switch(cb_id)
            {
                case UART_TX_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.uart_callbacks.uart_tx_cplt_cb=cb_fptr;
                    break;
                case UART_RX_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.uart_callbacks.uart_rx_cplt_cb=cb_fptr;
                    break;
                case UART_ABORT_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.uart_callbacks.uart_abort_cplt_cb=cb_fptr;
                    break;
                case UART_TX_ABORT_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.uart_callbacks.uart_abort_tx_cplt_cb=cb_fptr;
                    break;
                case UART_RX_ABORT_CPLT_CB:
                    ahal_info->intr_hdl.io_cb_list.uart_callbacks.uart_abort_rx_cplt_cb=cb_fptr;
                    break;
                case UART_ERROR_CB:
                    ahal_info->intr_hdl.io_cb_list.uart_callbacks.uart_error_cb=cb_fptr;
                    break;
                default:
                    sts=HAL_IO_INVLD_INST_ID;
                    break;
            }
            break;
        }
        case IOAL_INST_CAN1:
        case IOAL_INST_CAN2:
        case IOAL_INST_CAN3:
        {

            break;
        }
        default:
            sts=HAL_IO_INVLD_INST_ID;
            break;
    }

    if(cb_context==LISR)
    {
        ahal_info->intr_hdl.cb_context&= ~(cb_id);
    }
    else if(cb_context==HISR)
    {
        ahal_info->intr_hdl.cb_context|=cb_id;
    }
    else
    {

    }

    return sts;
}


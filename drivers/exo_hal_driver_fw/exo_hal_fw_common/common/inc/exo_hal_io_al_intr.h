/**
 * @file exo_hal_io_al_intr.h
 *
 * @brief This file contains structures,enumerations,function declaration for
 * IO HAL interfaces.
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

#ifndef DRIVERS_EXO_HAL_DRIVER_FW_EXO_HAL_FW_COMMON_COMMON_INC_EXO_HAL_IO_AL_INTR_H_
#define DRIVERS_EXO_HAL_DRIVER_FW_EXO_HAL_FW_COMMON_COMMON_INC_EXO_HAL_IO_AL_INTR_H_

#include <stdint.h>
#include "exo_types.h"
#include "exo_hal_common.h"
/**
 * @brief Enumeration of I2C callback identifiers.
 */
typedef enum
{
    I2C_MST_TX_CPLT_CB = 0b1,     ///< I2C master transmit complete callback
    I2C_MST_RX_CPLT_CB = 0b10,    ///< I2C master receive complete callback
    I2C_ABORT_CPLT_CB = 0b100,    ///< I2C abort complete callback
    I2C_LISTEN_CPLT_CB = 0b1000,  ///< I2C listen complete callback
    I2C_ERROR_CB = 0b10000,       ///< I2C error callback
    I2C_CB_ID_MAX = 0b10001       ///< Maximum identifier for I2C callbacks (used for boundary checks)
} i2c_cb_id;

/**
 * @brief Enumeration of SPI callback identifiers.
 */
typedef enum
{
    SPI_TX_CPLT_CB = 0b1,         ///< SPI transmit complete callback
    SPI_RX_CPLT_CB = 0b10,        ///< SPI receive complete callback
    SPI_TX_RX_CPLT_CB = 0b100,    ///< SPI transmit and receive complete callback
    SPI_ABORT_CPLT_CB = 0b1000,   ///< SPI abort complete callback
    SPI_ERROR_CB = 0b10000,       ///< SPI error callback
    SPI_CB_ID_MAX = 0b10001       ///< Maximum identifier for SPI callbacks (used for boundary checks)
} spi_cb_id;

/**
 * @brief Enumeration of UART callback identifiers.
 */
typedef enum
{
    UART_TX_CPLT_CB = 0b1,        ///< UART transmit complete callback
    UART_RX_CPLT_CB = 0b10,       ///< UART receive complete callback
    UART_ABORT_CPLT_CB = 0b100,   ///< UART abort complete callback
    UART_TX_ABORT_CPLT_CB = 0b1000, ///< UART transmit abort complete callback
    UART_RX_ABORT_CPLT_CB = 0b10000, ///< UART receive abort complete callback
    UART_ERROR_CB = 0b100000,     ///< UART error callback
    UART_CB_ID_MAX = 0b100001     ///< Maximum identifier for UART callbacks (used for boundary checks)
} uart_cb_id;

/**
 * @brief Application hardware information structure definition
 */
typedef struct _i2c_intr_cb
{
    void (*i2c_mst_tx_cplt_cb)(void* args);     /*!< Hold Fn address for I2C Master Tx Transfer completed callback ID */
    void (*i2c_mst_rx_cplt_cb)(void* args);     /*!< Hold Fn address for I2C Master Rx Transfer completed callback ID */
    void (*i2c_abort_cplt_cb)(void* args);      /*!< Hold Fn address for Abort complete event */
    void (*i2c_listen_cplt_cb)(void* args);     /*!< Hold Fn address for Listen complete event */
    void (*i2c_error_cb)(void* args);           /*!< Hold Fn address for error event */
}i2c_cb_lst;

/**
 * @brief Application hardware information structure definition
 */
typedef struct _spi_intr_cb
{
    void (*spi_tx_cplt_cb)(void* args);    /*!< Hold Fn address for Transmit complete event                 */
    void (*spi_rx_cplt_cb)(void* args);    /*!< Hold Fn address for Receive complete event                      */
    void (*spi_tx_rx_cplt_cb)(void* args); /*!< Hold Fn address for Transmit and Receive complete event     */
    void (*spi_abort_cplt_cb)(void* args); /*!< Hold Fn address for Abort complete event                        */
    void (*spi_error_cb)(void* args);      /*!< Hold Fn address for error event                             */
}spi_cb_lst;

/**
 * @brief Application hardware information structure definition
 */
typedef struct _uart_intr_cb
{
    void (*uart_tx_cplt_cb)(void* args);            /*!< Fn address of TX complete event callback           */
    void (*uart_rx_cplt_cb)(void* args);            /*!< Fn address of RX complete event callback           */
    void (*uart_abort_cplt_cb)(void* args);     /*!< Fn address of abort complete event callback        */
    void (*uart_abort_tx_cplt_cb)(void* args);  /*!< Fn address of abort TX complete event callback     */
    void (*uart_abort_rx_cplt_cb)(void* args);  /*!< Fn address of abort RX complete event callback     */
    void (*uart_error_cb)(void* args);          /*!< Fn address of error event callback                 */

}uart_cb_lst;

/**
 * @brief Application hardware information structure definition
 */
typedef struct _can_intr_cb
{
    void (*can_tx_mb0_cplt_cb)(void* args);    /*!< Hold Fn address for Tx complete for mailbox0 event                  */
    void (*can_tx_mb1_cplt_cb)(void* args);    /*!< Hold Fn address for Tx complete for mailbox1 event                  */
    void (*can_tx_mb2_cplt_cb)(void* args);    /*!< Hold Fn address for Tx complete for mailbox2 event                  */
    void (*can_mb0_abort_cb)(void* args);       /*!< Hold Fn address for mailbox0 abort event                           */
    void (*can_mb1_abort_cb)(void* args);       /*!< Hold Fn address for mailbox1 abort event                           */
    void (*can_mb2_abort_cb)(void* args);       /*!< Hold Fn address for mailbox2 abort event                           */
    void (*can_fifo0_msg_pend_cb)(void* args); /*!< Hold Fn address for message pending indication for fifo0 event      */
    void (*can_fifo0_full_cb)(void* args);     /*!< Hold Fn address for fifo0 full event                                */
    void (*can_fifo1_msg_pend_cb)(void* args); /*!< Hold Fn address for message pending indication for fifo1 event      */
    void (*can_fifo1_full_cb)(void* args);     /*!< Hold Fn address for fifo1 full event                                */
    void (*can_sleep_cb)(void* args);           /*!< Hold Fn address for sleep event                                    */
    void (*can_wakeup_cb)(void* args);          /*!< Hold Fn address for wakeup event                                   */
    void (*can_error_cb)(void* args);           /*!< Hold Fn address for error event                                    */
}can_cb_lst;

/**
 * @brief Union for holding callback lists for various I/O interfaces.
 */
typedef union _io_cb_list
{
    can_cb_lst can_callbacks;   /*!< Callback list for CAN interface */
    spi_cb_lst spi_callbacks;   /*!< Callback list for SPI interface */
    i2c_cb_lst i2c_callbacks;   /*!< Callback list for I2C interface */
    uart_cb_lst uart_callbacks; /*!< Callback list for UART interface */
} io_cb_list;

/**
 * @brief Enumeration for interrupt service routine (ISR) contexts.
 */
typedef enum
{
    LISR,                     ///< Low Interrupt Service Routine context
    HISR,                     ///< High Interrupt Service Routine context
    ISR_CONTEXT_MAX           ///< Maximum ISR context identifier (used for boundary checks)
} isr_context;

/**
 * @brief Structure for storing information about I/O interrupt handling.
 */
typedef struct
{
    io_cb_list io_cb_list;   /*!< Union for callback lists for different I/O interfaces */
    uint16 cb_context;       /*!< Context identifier for the callback */
} io_al_intr_info;

/**
 * @brief This function initializes the HAL for handling interrupts related to I/O operations.
 * @return Status of the initialization operation (e.g., success or failure)
 */
hal_ret_sts io_ahw_hal_intr_init();

/**
 * @brief This function is called to handle interrupts generated by the SPI interface.
 *
 * @param spi_inst_id : The identifier of the SPI instance generating the interrupt.
 * @param cb_id : The identifier of the callback associated with the interrupt.
 */
void spi_intr_hdl(uint8_t spi_inst_id, uint8_t cb_id);

/**
 * @brief This function is called to handle interrupts generated by the UART interface.
 *
 * @param[in] uart_inst_id : The identifier of the UART instance generating the interrupt.
 *                     This should correspond to one of the defined UART instance IDs.
 * @param[in] cb_id : The identifier of the callback associated with the interrupt.
 */
void uart_intr_hdl(uint8_t uart_inst_id, uint8_t cb_id);

/**
 * @brief This function is called to handle interrupts generated by the I2C interface.
 * @param[in] i2c_inst_id : The identifier of the I2C instance generating the interrupt.
 * @param[in] cb_id : The identifier of the callback associated with the interrupt.
 */
void i2c_intr_hdl(uint8_t i2c_inst_id, uint8_t cb_id);

/**
 * @brief This function is called to handle interrupts related to
 * external IO and AHW (Application Hardware) components.
 * @param args[in] : A pointer to arguments relevant to the interrupt handling.
 */
void exo_io_ah_intr_hdl(void* args);

#endif /* DRIVERS_EXO_HAL_DRIVER_FW_EXO_HAL_FW_COMMON_COMMON_INC_EXO_HAL_IO_AL_INTR_H_ */

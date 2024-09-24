/**
 * @file exo_io_al_uart_common.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for UART interface
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

#ifndef _IO_AL_UART_COMMON_H_
#define _IO_AL_UART_COMMON_H_

#include "exo_ahw_al_common.h"
#include "exo_io_al_common.h"
#include "exo_hal_common.h"
#include "exo_hal_io_al_intr.h"
#include "exo_ahw_al_common.h"

#define URT_INTF_ENB

/**
 * @brief IO-HAl UART interface control block handle structure definition
 */
typedef struct _ioal_uart_hdle
{
    ioal_intf_gen_info intf_gen_info;               /*!< Hold general information of interface              */
    void (*tx_cplt_cb)(struct _ioal_uart_hdle *huart);      /*!< Fn address of TX complete event callback           */
    void (*rx_cplt_cb)(struct _ioal_uart_hdle *huart);      /*!< Fn address of RX complete event callback           */
    void (*abort_cplt_cb)(struct _ioal_uart_hdle *huart);   /*!< Fn address of abort complete event callback        */
    void (*abort_tx_cplt_cb)(struct _ioal_uart_hdle *huart);/*!< Fn address of abort TX complete event callback     */
    void (*abort_rx_cplt_cb)(struct _ioal_uart_hdle *huart);/*!< Fn address of abort RX complete event callback     */
    void (*error_cb)(struct _ioal_uart_hdle *huart);        /*!< Fn address of error event callback                 */
    uint16 cb_context;                                      /*!< UART App callbacks execution context               */
    uart_cb_lst app_callbacks;                              /*!< UART App callbacks list                            */
}ioal_uart_hdle;
typedef enum
{
    IOAL_UART_STATE_RESET,     /*!< Peripheral is not initialized Value is allowed for gState and RxState */
    IOAL_UART_STATE_READY,     /*!< Peripheral Initialized and ready for use Value is allowed for gState and RxState */
    IOAL_UART_STATE_BUSY,      /*!< an internal process is ongoing Value is allowed for gState only */
    IOAL_UART_STATE_BUSY_TX,   /*!< Data Transmission process is ongoing Value is allowed for gState only */
    IOAL_UART_STATE_BUSY_RX,   /*!< Data Reception process is ongoing Value is allowed for RxState only */
    IOAL_UART_STATE_BUSY_TX_RX,/*!< Data Transmission and Reception process is ongoing
                                  Not to be used for neither gState nor RxState.Value is result
                                  of combination (Or) between gState and RxState values */
    IOAL_UART_STATE_TIMEOUT,   /*!< Timeout state Value is allowed for gState only */
    IOAL_UART_STATE_ERROR ,    /*!< Error Value is allowed for gState only */
    IOAL_UART_STATE_MAX

}ioal_uart_state;

/**
 * @brief This function initializes the control block memory and do the basic configurations for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_uart_init(void);
/**
 * @brief This function transmit the data in UART interface with blocking mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @param[in] pdata - pointer to a data
 * @param[in] size - size of the data
 * @param[in] timeout - timeout duration
 * @return HAL status
 */
hal_ret_sts io_hal_uart_transmit(ioal_uart_hdle *huart, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief This function receive the data in UART interface with blocking mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @param[out]pdata - pointer to a data
 * @param[in] size - size of the data
 * @param[in] timeout - timeout duration
 * @return Total bytes received
 */
uint32 io_hal_uart_receive(ioal_uart_hdle *huart, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief This function transmit the data with interrupt mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @param[in]  ahw_info - pointer to application hardware information handle
 * @param[in] pdata - pointer to a data
 * @param[in] size - size of the data
 * @return HAL status
 */
hal_ret_sts io_hal_uart_transmit_it(ioal_uart_hdle *huart, ahw_al_gen_info* ahw_info, uint8 *pdata, uint16 size);
/**
 * @brief This function receive the data with interrupt mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @param[in]  ahw_info - pointer to application hardware information handle
 * @param[out]pdata - pointer to a data
 * @param[in] size - size of the data
 * @return HAL status
 */
hal_ret_sts io_hal_uart_receive_it(ioal_uart_hdle *huart, ahw_al_gen_info* ahw_info, uint8 *pdata, uint16 size);
/**
 * @brief This function transmit the data in UART interface with DMA mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @param[in]  ahw_info - pointer to application hardware information handle

 * @param[in] pdata - pointer to a data
 * @param[in] size - size of the data
 * @return HAL status
 */
hal_ret_sts io_hal_uart_transmit_dma(ioal_uart_hdle *huart, ahw_al_gen_info* ahw_info, uint8 *pdata, uint16 size);
/**
 * @brief This function receive the data in UART interface with DMA mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @param[in]  ahw_info - pointer to application hardware information handle
 * @param[out]pdata - pointer to a data
 * @param[in] size - size of the data
 * @return HAL status
 */
hal_ret_sts io_hal_uart_receive_dma(ioal_uart_hdle *huart, ahw_al_gen_info* ahw_info, uint8 *pdata, uint16 size);
/**
 * @brief This function pause the transmission of data in DMA mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return HAL status
 */
hal_ret_sts io_hal_uart_dma_pause(ioal_uart_hdle *huart);
/**
 * @brief This function resume the transmission of data in DMA mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return HAL status
 */
hal_ret_sts io_hal_uart_dma_resume(ioal_uart_hdle *huart);
/**
 * @brief This function stop the transmission of data in DMA mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return HAL status
 */
hal_ret_sts io_hal_uart_dma_stop(ioal_uart_hdle *huart);
/**
 * @brief This function abort the transmission of data
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return HAL status
 */
hal_ret_sts io_hal_uart_abort(ioal_uart_hdle *huart);
/**
 * @brief This function abort the ongoing transmit of data
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return HAL status
 */
hal_ret_sts io_hal_uart_abort_transmit(ioal_uart_hdle *huart);
/**
 * @brief This function abort the receive of data
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return HAL status
 */
hal_ret_sts io_hal_uart_abort_receive(ioal_uart_hdle *huart);
/**
 * @brief This function abort transmission of data with interrupt mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return HAL status
 */
hal_ret_sts io_hal_uart_abort_it(ioal_uart_hdle *huart);
/**
 * @brief This function abort the transmission of data with interrupt mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return HAL status
 */
hal_ret_sts io_hal_uart_abort_transmit_it(ioal_uart_hdle *huart);
/**
 * @brief This function abort the receive of data with interrupt mode
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return HAL status
 */
hal_ret_sts io_hal_uart_abort_receive_it(ioal_uart_hdle *huart);
/**
 * @brief This function initialize the callback event
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return HAL status
 */
void io_hal_uart6_cb_init(ioal_uart_hdle *huart6);

/**
 * @brief UART TX complete call back api
 *
 * @param[in] huart: pointer to UART handler
 */
void io_hal_uart_tx_cmplt_cb(ioal_uart_hdle *huart);

/**
 * @brief UART RX complete call back api
 *
 * @param[in] huart: pointer to UART handler
 */
void io_hal_uart_rx_cmplt_cb(ioal_uart_hdle *huart);

/**
 * @brief UART abort complete call back api
 *
 * @param[in] huart: pointer to UART handler
 */
void io_hal_uart_abort_cmplt_cb(ioal_uart_hdle *huart);

/**
 * @brief UART abort TX complete call back api
 *
 * @param[in] huart: pointer to UART handler
 */
void io_hal_uart_abort_tx_cmplt_cb(ioal_uart_hdle *huart);

/**
 * @brief UART abort RX complete call back api
 *
 * @param[in] huart: pointer to UART handler
 */
void io_hal_uart_abort_rx_cmplt_cb(ioal_uart_hdle *huart);

/**
 * @brief UART error call back api
 *
 * @param[in] huart: pointer to UART handler
 */
void io_hal_uart_error_cb(ioal_uart_hdle *huart);

/**
 * @brief This API handle UART DMA receive data to idle
 *
 * @param[in] huart: Pointer to UART handler
 * @param[in] ahw_info: Pointer to AHW information
 * @param[out] pdata: pointer to receive data
 * @param[out] size: Received data size
 *
 * @return HAL status
 * @retval HAL_SCS is success, otherwise failure
 */
hal_ret_sts io_hal_uart_dma_receive_to_idle(ioal_uart_hdle *huart, ahw_al_gen_info* ahw_info, uint8 *pdata, uint16 size);

/**
 * @brief This function to get UART state
 * @param[in] huart - huart pointer to a ioal_uart_hdle structure that contains
 *             the configuration information for UART module
 * @return UART State
 */
ioal_uart_state io_hal_uart_get_state(ioal_uart_hdle *huart);



#ifdef LINUX_TEMP_PORT
/**
 * @brief This is UART interface dummy function for linux
 *
 * @param[in] huart: pointer to UART handle
 */
void linux_uart_dummy_fn(struct _ioal_uart_hdle *huart);
#endif


#endif /* _IO_AL_UART_COMMON_H_ */

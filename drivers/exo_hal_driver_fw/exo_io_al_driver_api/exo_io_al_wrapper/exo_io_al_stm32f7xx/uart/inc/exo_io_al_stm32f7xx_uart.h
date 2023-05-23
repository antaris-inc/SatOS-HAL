/**
 * @file exo_io_al_stm32f7xx_uart.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for UART interface
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

#ifndef _IO_AL_STM32F7XX_UART_H_
#define _IO_AL_STM32F7XX_UART_H_

#include "exo_types.h"
#include "exo_io_al_uart_common.h"
#include "exo_hal_common.h"
#include "exo_io_al_common.h"
#include "exo_io_al_stm32f7xx_common.h"

/**
 * @brief  VDP layer UART callback ID
 */
typedef enum
{
    IOHAL_STM32_UART_TX_CPLT_CB_ID,					/*!< UART Tx Transfer completed callback ID */
    IOHAL_STM32_UART_RX_CPLT_CB_ID,					/*!< UART Rx Transfer completed callback ID */
    IOHAL_STM32_UART_ABORT_CPLT_CB_ID,				/*!< UART abort completed callback ID */
    IOHAL_STM32_UART_ABORT_TX_CPLT_CB_ID,			/*!< UART abort Tx Transfer completed callback ID */
    IOHAL_STM32_UART_ABORT_RX_CPLT_CB_ID,			/*!< UART abort RX Transfer completed callback ID */
    IOHAL_STM32_UART_ERROR_CB_ID					/*!< UART error completed callback ID */
}iohal_stm32_uart_cbid;


/**
 * @brief This function initialize the control block memory and do basic configurations of UART6
 * @param[in] ioal_huart6 - ioal_huart6 pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART6
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart6_init(ioal_uart_hdle *ioal_huart6);
/**
 * @brief This function initialize the control block memory and do basic configurations of UART1
 * @param[in] ioal_huart6 - ioal_huart1 pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART1
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart1_init(ioal_uart_hdle *ioal_huart1);
/**
 * @brief This function initialize the control block memory and do basic configurations of UART4
 * @param[in] ioal_huart6 - ioal_huart4 pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART4
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart4_init(ioal_uart_hdle *ioal_huart4);
/**
 * @brief This function initialize the control block memory and do basic configurations of UART5
 * @param[in] ioal_huart6 - ioal_huart5 pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART5
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart5_init(ioal_uart_hdle *ioal_huart5);
/**
 * @brief This function transmit the data in blocking mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] pdata - pointer to a data
 * @param[in] size - size of the data
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_transmit(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief This function receive the data in blocking mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @param[out]pdata - pointer to a data
 * @param[in] size - size of the data
 * @param[in] timeout - timeout duration
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_receive(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout);
/**
 * @brief This function transmit the data in interrupt mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] pdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_transmit_it(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size);
/**
 * @brief This function receive the data in interrupt mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @param[out]pdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_receive_it(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size);
/**
 * @brief This function transmit the data in DMA mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] pdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_transmit_dma(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size);
/**
 * @brief This function receive the data in DMA mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @param[out]pdata - pointer to a data
 * @param[in] size - size of the data
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_receive_dma(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size);
/**
 * @brief This function pause the transmission of data in DMA mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_dma_pause(ioal_uart_hdle *ioal_huart);
/**
 * @brief This function resume the transmission of data in DMA mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_dma_resume(ioal_uart_hdle *ioal_huart);
/**
 * @brief This function stop the transmission of data in DMA mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_dma_stop(ioal_uart_hdle *ioal_huart);
/**
 * @brief This function abort the transmission of data
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_abort(ioal_uart_hdle *ioal_huart);
/**
 * @brief This function abort the ongoing transmit of data
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_abort_transmit(ioal_uart_hdle *ioal_huart);
/**
 * @brief This function abort the receive of data
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_abort_receive(ioal_uart_hdle *ioal_huart);
/**
 * @brief This function abort the transmission of data in interrupt mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_abort_it(ioal_uart_hdle *ioal_huart);
/**
 * @brief This function transmit the data in interrupt mode
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_abort_transmit_it(ioal_uart_hdle *ioal_huart);
/**
 * @brief This function receive the data with interrupt
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_abort_receive_it(ioal_uart_hdle *ioal_huart);
/**
 * @brief This function register the callback event
 * @param[in] ioal_huart - ioal_huart pointer to a ioal_uart_hdle structure that contains
 * 							the configuration information for UART
 * @param[in] cbid - ID of the callback event
 * @retval HAL status
 */
hal_ret_sts io_hal_stm32f7xx_uart_reg_cb(ioal_uart_hdle *ioal_huart, iohal_stm32_uart_cbid cbid);


/* API Mapping */
#define io_hal_common_uart6_init 				io_hal_stm32f7xx_uart6_init
#define io_hal_common_uart1_init 				io_hal_stm32f7xx_uart1_init
#define io_hal_common_uart4_init 				io_hal_stm32f7xx_uart4_init
#define io_hal_common_uart5_init 				io_hal_stm32f7xx_uart5_init
#define io_hal_common_uart_transmit		 		io_hal_stm32f7xx_uart_transmit
#define io_hal_common_uart_receive		 		io_hal_stm32f7xx_uart_receive
#define io_hal_common_uart_transmit_it	 		io_hal_stm32f7xx_uart_transmit_it
#define io_hal_common_uart_receive_it	 		io_hal_stm32f7xx_uart_receive_it
#define io_hal_common_uart_transmit_dma			io_hal_stm32f7xx_uart_transmit_dma
#define io_hal_common_uart_receive_dma			io_hal_stm32f7xx_uart_receive_dma
#define io_hal_common_uart_dma_pause			io_hal_stm32f7xx_uart_dma_pause
#define io_hal_common_uart_dma_resume			io_hal_stm32f7xx_uart_dma_resume
#define io_hal_common_uart_dma_stop				io_hal_stm32f7xx_uart_dma_stop
#define io_hal_common_uart_abort				io_hal_stm32f7xx_uart_abort
#define io_hal_common_uart_abort_transmit		io_hal_stm32f7xx_uart_abort_transmit
#define io_hal_common_uart_abort_receive		io_hal_stm32f7xx_uart_abort_receive
#define io_hal_common_uart_abort_it				io_hal_stm32f7xx_uart_abort_it
#define io_hal_common_uart_abort_transmit_it	io_hal_stm32f7xx_uart_abort_transmit_it
#define io_hal_common_uart_abort_receive_it		io_hal_stm32f7xx_uart_abort_receive_it
#define io_hal_common_uart_reg_cb				io_hal_stm32f7xx_uart_reg_cb

#endif /* _IO_AL_STM32F7XX_UART_H_ */

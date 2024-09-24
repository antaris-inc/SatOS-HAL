/**
 * @file csp_uart_if.c
 *
 * @brief This file contains CSP UART interface functionality
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
 *
 */
/*********************************************************************/
#include "stdlib.h"
#include "usart.h"
#include <errno.h>
#ifndef LINUX_TEMP_PORT 
#include "stm32f7xx_hal_uart.h"
#include "cmsis_os.h"
#endif
#include "exo_hal_io_al_common.h"
#include "exo_ahw_al_common.h"
#include "exo_osal.h"
#include "exo_hal_io_al_intr.h"

#include "csp.h"
#include "csp_thread.h"

#define CBUF_SIZE  400  ///< Maximum CBUF size

extern ioal_uart_hdle ioal_huart6; ///< UART6 handler declaration
extern ioal_uart_hdle ioal_huart4; ///< UART4 handler declaration

os_sem_handle_ptr csp_uart_sem; ///< Semaphore handle for UART

ahw_al_gen_info csp_uart; ///< UART hardware generic information
ioal_uart_hdle *uart_hdl; ///< comman UART handler

/**
 * @brief It defines UART context
 */
typedef struct {
    csp_usart_callback_t rx_callback;
    void * user_data;
    csp_usart_fd_t fd;
    csp_thread_handle_t rx_thread;
}usart_context_t;

uint16_t csp_g_tail = 0;
uint8_t csp_bGet[CBUF_SIZE] = {0};
uint8_t uhf_uart_rsp[CBUF_SIZE] = {0};
uint16_t uhf_uart_rsp_len = 0;
uint16_t length=0;

/**
 * @brief This is UART receive callback function
 *
 * @param [in] arg: Dummy parameter
 */
void usart_rx_cb(void * arg);

/**
 * @brief This is UART error callback function
 *
 * @param [in] arg: Dummy parameter
 */
void csp_uart_error_cb(void* args);

/**
 * @brief This is UART error callback function
 */
void csp_uart_error_cb(void* args)
{
#ifndef LINUX_TEMP_PORT
#ifdef COREBOARD
    io_hal_uart_dma_receive_to_idle(&ioal_huart4,&csp_uart,csp_bGet, CBUF_SIZE);
#else
    io_hal_uart_dma_receive_to_idle(&ioal_huart6,&csp_uart,csp_bGet, CBUF_SIZE);
#endif
#endif
}

/**
 * @brief This is UART TX complete callback function
 *
 * @param [in] arg: Dummy parameter
 */
void csp_uart_tx_cplt_cb(void* args)
{
}

/**
 * @brief This is UART RX complete callback function
 *
 * @param [in] arg: Dummy parameter
 */
void csp_uart_rx_cplt_cb(void* args)
{
}

#ifndef LINUX_TEMP_PORT
/**
 * @brief This is UART RX event callback function
 *
 * @param [in] huart: pointer to UART handle
 * @param [in] size: Received length
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if((huart->RxEventType == HAL_UART_RXEVENT_IDLE) || (huart->RxEventType == HAL_UART_RXEVENT_TC))
    {
        length = Size;
        os_sem_give(csp_uart_sem);
    }
}
#endif
#ifdef LINUX_TEMP_PORT
/**
 * @brief This is UART receive callback function
 */
void usart_rx_cb(void * arg)
{
#ifndef UHF_HW_BYPASS
    //usart_context_t * ctx =arg;
    usart_context_t * ctx = ((os_thread_handle_ptr)arg)->app_entry_args;
    uint8_t cbuf[CBUF_SIZE];

    while(1)
    {
        length = io_hal_uart_receive(&ioal_huart6, csp_bGet, CBUF_SIZE, 100);
	printf("RCV length=%d\n",length);
        os_memcpy(cbuf,csp_bGet,length);
        if (length > 0)
        {
            os_memcpy(uhf_uart_rsp,csp_bGet,length);
            uhf_uart_rsp_len = length;
            if (ctx->rx_callback)
            {
                ctx->rx_callback(ctx->user_data, csp_bGet, length, NULL);
            }

            length =0;

        }
        os_delay(10);
    }
#endif
}
#else
/**
 * @brief This is UART receive callback function
 */
void usart_rx_cb(void * arg)
{
    //usart_context_t * ctx =arg;
    usart_context_t * ctx = ((os_thread_handle_ptr)arg)->app_entry_args;
    uint8_t cbuf[CBUF_SIZE];

    while(1)
    {
        if(os_sem_take(csp_uart_sem, 5000) == ral_success)
        {
            os_memcpy(cbuf,csp_bGet,length);
#ifdef COREBOARD
            io_hal_uart_dma_receive_to_idle(&ioal_huart4,&csp_uart,csp_bGet, CBUF_SIZE);
#else
            io_hal_uart_dma_receive_to_idle(&ioal_huart6,&csp_uart,csp_bGet, CBUF_SIZE);
#endif

            if (length)
            {
                os_memcpy(uhf_uart_rsp,csp_bGet,length);
                uhf_uart_rsp_len = length;
                if (ctx->rx_callback)
                {
                    ctx->rx_callback(ctx->user_data, csp_bGet, length, NULL);
                }

                length =0;
            }
        }
        else
        {
#ifdef COREBOARD
            io_hal_uart_dma_receive_to_idle(&ioal_huart4,&csp_uart,csp_bGet, CBUF_SIZE);
#else
            io_hal_uart_dma_receive_to_idle(&ioal_huart6,&csp_uart,csp_bGet, CBUF_SIZE);
#endif
        }
    }
}
#endif

/**
   Write data on open UART.

   @param[in] fd file descriptor.
   @param[in] data data to write.
   @param[in] data_length length of \a data.
   @return number of bytes written on success, a negative value on failure.
 */
int csp_usart_open(ioal_uart_hdle *uart_hdl, csp_usart_callback_t rx_callback, void * user_data, csp_usart_fd_t * fd)
{
    *fd = 1;
#ifdef COREBOARD
    csp_uart.io_intf_id=IOAL_INST_UART4;
#else
    csp_uart.io_intf_id=IOAL_INST_UART6;
#endif
    ahal_register_io_cb(&csp_uart,UART_TX_CPLT_CB,csp_uart_tx_cplt_cb,HISR);
    ahal_register_io_cb(&csp_uart,UART_RX_CPLT_CB,csp_uart_rx_cplt_cb,HISR);
    ahal_register_io_cb(&csp_uart,UART_ERROR_CB,csp_uart_error_cb,HISR);
#ifndef LINUX_TEMP_PORT
    os_sem_create_bin(&csp_uart_sem);
    os_sem_take(csp_uart_sem, 5000);
    io_hal_uart_dma_receive_to_idle(uart_hdl,&csp_uart,csp_bGet, CBUF_SIZE);
#endif
    //   io_hal_uart_receive_it(uart_hdl,&csp_uart,csp_bGet, CBUF_SIZE);
    usart_context_t * ctx = calloc(1, sizeof(*ctx));

    if (ctx == NULL) {
        csp_log_error("%s: Error allocating context, errno: %s", __FUNCTION__, strerror(errno));
        return CSP_ERR_NOMEM;
    }

    ctx->rx_callback = rx_callback;
    ctx->user_data = user_data;
    ctx->fd = 1;
    if (rx_callback) {
        if (csp_thread_create(usart_rx_cb, "usart_cb", (128 * 4), ctx, P_UART_RX, &ctx->rx_thread) != CSP_ERR_NONE) {
            csp_log_error("%s: csp_thread_create() failed to create Rx cb for, errno: %s", __FUNCTION__, strerror(errno));
            free(ctx);
            return CSP_ERR_NOMEM;
        }

        //        if (csp_thread_create(usart_rxTask, "usart_rx", (1280 ), NULL, P_CSP_INTF_UART_RX, NULL) != CSP_ERR_NONE) {
        //            csp_log_error("%s: csp_thread_create() failed to create Rx loop for, errno: %s", __FUNCTION__, strerror(errno));
        //            return CSP_ERR_NOMEM;
        //        }
        return CSP_ERR_NONE;
    }
    return CSP_ERR_INVAL;
}

/**
   Opens UART device and add KISS interface.

   This is a convience function for opening an UART device and adding it as an interface with a given name.

   @note On read failures, exit() will be called - terminating the process.

   @param[in] conf UART configuration.
   @param[in] ifname internface name (will be copied), or use NULL for default name.
   @param[out] return_iface the added interface.
   @return #CSP_ERR_NONE on success, otherwise an error code.
 */

int csp_usart_write(ioal_uart_hdle *uart_hdl, const void * data, size_t data_length)
{
    hal_ret_sts  status;
    status =1;
    status=io_hal_uart_transmit_dma(uart_hdl,&csp_uart,(uint8_t*)data,data_length);
#ifndef LINUX_TEMP_PORT
    while (io_hal_uart_get_state(uart_hdl) != IOAL_UART_STATE_READY)
    {
        if (io_hal_uart_get_state(uart_hdl) == IOAL_UART_STATE_BUSY_RX)
            break;
        osDelay(1);
    }
#endif
    //if (status == HAL_OK)
    if (status == HAL_SCS)
        return data_length;
    return 0;

}

#if 0
uint32_t uhf_fw_usart_write(uint8_t* data, uint16_t data_len)
{
    hal_ret_sts  status;
    //ioal_uart_hdle *uart_hdl1;
    status =1;
#ifdef COREBOARD
    status=io_hal_uart_transmit_dma(&ioal_huart4,&csp_uart,(uint8_t*)data,data_len);
#else
    status=io_hal_uart_transmit_dma(&ioal_huart6,&csp_uart,(uint8_t*)data,data_len);
#endif

#ifndef LINUX_TEMP_PORT
    while (io_hal_uart_get_state(uart_hdl) != IOAL_UART_STATE_READY)
    {
        if (io_hal_uart_get_state(uart_hdl) == IOAL_UART_STATE_BUSY_RX)
            break;
        osDelay(1);
    }
#endif
    //if (status == HAL_OK)
    if (status == HAL_SCS)
    {
        //UHF_FW_UP = 1;
        return data_len;
    }
    //else UHF_FW_UP = 0;

    return 0;

}

uint8_t uhf_fw_write(int8* data, uint8_t reply, uint16_t data_len)
{
    int ret_sts = 0;
    uint8_t* fw_data = (uint8*) data;

    ret_sts = uhf_fw_usart_write(fw_data, data_len);
    if(ret_sts == data_len)
    {
        return 0; // wr succ
    }
    else
    {
        return 1; // wr fail
    }

}
#endif

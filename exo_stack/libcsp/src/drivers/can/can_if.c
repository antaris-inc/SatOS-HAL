/*
   Cubesat Space Protocol - A small network-layer protocol designed for Cubesats
   Copyright (C) 2012 GomSpace ApS (http://www.gomspace.com)
   Copyright (C) 2012 AAUSAT3 Project (http://aausat3.space.aau.dk)

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
   */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "csp.h"
#include "csp_queue.h"
#include "csp_can.h"
#include "csp_thread.h"
#include "exo_hal_io_al_common.h"
#include "cmsis_os.h"
#include "exo_osal.h"

extern ioal_can_hdle ioal_hcan1;
extern ioal_can_hdle ioal_hcan2;
extern ioal_can_hdle ioal_hcan3;

os_queue_handle_ptr adcs_queue_ptr;

typedef struct{

    iohal_can_rx_header rxheader_p;
    uint8_t rxdata_p[8];
}can_data;

// CAN interface data, state, etc.
typedef struct {
    char name[CSP_IFLIST_NAME_MAX + 1];
    csp_iface_t iface;
    csp_can_interface_data_t ifdata;
    csp_thread_handle_t rx_thread;
    ioal_can_hdle* can_hdl;
    int socket;
} can_context_t;

csp_queue_handle_t can_csp_q;


static void csp_can_free(can_context_t * ctx) {

    if (ctx)
    {
#if(0)
        if (ctx->socket >= 0) {
            close(ctx->socket);
        }
#endif
        free(ctx);
    }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    can_data data;

    uint8 src_id, dst_id = 0;
    uint8 msg_typ = 0;

#ifdef COREBOARD
    io_hal_can_get_rx_message(&ioal_hcan2, CAN_RX_FIFO0, &data.rxheader_p, data.rxdata_p);
#else
    io_hal_can_get_rx_message(&ioal_hcan3, CAN_RX_FIFO0, &data.rxheader_p, data.rxdata_p);
#endif
    /*
     *      * Extended CAN identifier : 1st 8 bits- Destination address
     *      * Extended CAN identifier : 9-16 bits- Destination address
     *      */
    src_id =  CAN_GET_SRC_ADDRESS(data.rxheader_p.ExtId) ;
    dst_id =  CAN_GET_DST_ADDRESS(data.rxheader_p.ExtId);
    msg_typ =  CAN_GET_MSG_TYPE(data.rxheader_p.ExtId);

    /*
     *      * ADCS cube computer id is 0x1 and ADCS controller SW
     *      * id is 0x2. Route the received data to either ADCS or COMMS
     *      * based on the Source and Destination identifier
     *      */
    if((0x1 == src_id) && (0xff == dst_id) && (msg_typ>0) && (msg_typ <=8))
    {
        csp_queue_enqueue(can_csp_q,&data,0);
    }
    else
    {
        csp_queue_enqueue(can_csp_q,&data,0);
    }
}

/**
 * @brief TBD: Can be removed once the Core board is integrated with ADCS.
 * This api is written as an example to route the CAN bus data based on
 * the extended CAN identifier.
 */
void check_can3_dummy(ioal_can_hdle *hcan)
{
    can_data data;
    uint8 src_id, dst_id = 0;
    io_hal_can_get_rx_message(&ioal_hcan3, CAN_RX_FIFO0, &data.rxheader_p, data.rxdata_p);
    /*
     * Extended CAN identifier : 1st 8 bits- Destination address
     * Extended CAN identifier : 9-16 bits- Destination address
     */
    src_id =  CAN_GET_SRC_ADDRESS(data.rxheader_p.ExtId) ;
    dst_id =  CAN_GET_DST_ADDRESS(data.rxheader_p.ExtId);

    /*
     * ADCS cube computer id is 0x1 and ADCS controller SW
     * id is 0x2. Route the received data to either ADCS or COMMS
     * based on the Source and Destination identifier
     */
    if((0x1 == src_id) && (0x2 == dst_id))
    {
        //ADCS node
        //adcs_get_can_queue_hdlr(&adcs_queue_ptr);
        os_queue_send(adcs_queue_ptr, &data,0);
    }
}

static void  can_rx_thread(void * arg)
{
    can_context_t * ctx = arg;
    can_data data_p;
    while (1)
    {
        csp_queue_dequeue(can_csp_q, &data_p, os_wait_forever);
        csp_can_rx(&ctx->iface,data_p.rxheader_p.ExtId,data_p.rxdata_p,data_p.rxheader_p.DLC, NULL);
    }
    /* We should never reach this point */
    csp_thread_exit();
}


static int csp_can_tx_frame(void * driver_data, uint32_t id, const uint8_t * data, uint8_t dlc)
{
    if (dlc > 8)
    {
        return CSP_ERR_INVAL;
    }
    iohal_can_tx_header txheader;
    txheader.DLC=dlc;
    txheader.ExtId=id;
    txheader.RTR=CAN_RTR_DATA;
    txheader.StdId=0;
    txheader.IDE=CAN_ID_EXT;
    uint32_t txmailbox;
    uint32_t elapsed_ms = 0;
    can_context_t * ctx = driver_data;

    while(io_hal_can_add_tx_message(ctx->can_hdl, &txheader,(uint8_t*)data, &txmailbox)!=HAL_SCS)
    {
        if ((errno != ENOBUFS) || (elapsed_ms >= 1000))
        {
            csp_log_warn("%s[%s]: write() failed, errno %d: %s", __FUNCTION__, ctx->name, errno, strerror(errno));
            return CSP_ERR_TX;
        }
        csp_sleep_ms(5);
        elapsed_ms += 5;
    }
    osDelay(1);
    return CSP_ERR_NONE;
}

int csp_can_open_and_add_interface(const char * device, const char * ifname,ioal_can_hdle* can_intf_hdl, csp_iface_t ** return_iface)
{
    if (ifname == NULL) {
        ifname = CSP_IF_CAN_DEFAULT_NAME;
    }

    csp_log_info("INIT %s: device: [%s]",
            ifname, device);

    can_context_t * ctx = calloc(1, sizeof(*ctx));
    if (ctx == NULL) {
        return CSP_ERR_NOMEM;
    }
    ctx->socket = -1;

    strncpy(ctx->name, ifname, sizeof(ctx->name) - 1);
    ctx->iface.name = ctx->name;
    ctx->iface.interface_data = &ctx->ifdata;
    ctx->iface.driver_data = ctx;
    ctx->ifdata.tx_func = csp_can_tx_frame;
    ctx->can_hdl=can_intf_hdl;

    iohal_can_state can_ste;
    can_ste=io_hal_can_get_state(ctx->can_hdl);
    if(can_ste ==IOHAL_CAN_STATE_READY )
    {
        io_hal_can_start(ctx->can_hdl);
    }
    else if(can_ste ==IOHAL_CAN_STATE_LISTENING )
    {
        //do nothing
    }
    else
    {
        return CSP_ERR_DRIVER;
    }
    io_hal_can_activate_notification(ctx->can_hdl, CAN_IT_RX_FIFO0_MSG_PENDING);
    can_csp_q = csp_queue_create(100,sizeof(can_data));

    /* Add interface to CSP */
    int res = csp_can_add_interface(&ctx->iface);
    if (res != CSP_ERR_NONE) {
        csp_log_error("%s[%s]: csp_can_add_interface() failed, error: %d", __FUNCTION__, ctx->name, res);
        csp_can_free(ctx);
        return res;
    }
    /* Create receive thread */
    if(csp_thread_create(can_rx_thread,"can_rx", 2048, ctx, P_CSP_INTF_CAN_RX,&ctx->rx_thread )!=0)
    {
        csp_log_error("%s[%s]: can_rx_thread failed, error: %s", __FUNCTION__, ctx->name, strerror(errno));
        csp_can_free(ctx); // we already added it to CSP (no way to remove it)
        return CSP_ERR_NOMEM;
    }
    if (return_iface) {
        *return_iface = &ctx->iface;
    }
    return CSP_ERR_NONE;
}

csp_iface_t * csp_can_init(const char * device,ioal_can_hdle* can_intf_hdl)
{
    csp_iface_t * return_iface;
    int res = csp_can_open_and_add_interface(device, CSP_IF_CAN_DEFAULT_NAME,can_intf_hdl, &return_iface);
    return (res == CSP_ERR_NONE) ? return_iface : NULL;
}

int csp_can_stop(csp_iface_t *iface)
{
    can_context_t * ctx = iface->driver_data;
  //unused:  os_thread_handle_ptr hdle = (os_thread_handle_ptr)ctx->rx_thread;
    os_status_t sts;
    csp_queue_remove(can_csp_q);
    sts=os_thread_delete(CSP_TASK);
    if(sts!=os_success)
    {
        return CSP_ERR_NOMEM;
    }
    else
    {
        csp_can_free(ctx);
        return CSP_ERR_NONE;
    }
}


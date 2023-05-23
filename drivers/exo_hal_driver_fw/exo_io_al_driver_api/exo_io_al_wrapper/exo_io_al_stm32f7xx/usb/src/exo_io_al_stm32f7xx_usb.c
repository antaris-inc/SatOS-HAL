/**
 * @file exo_io_al_stm32f7xx_usb.c
 *
 * @brief This file contains wrapper function definition for USB interface
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

#include "exo_io_al_stm32f7xx_usb.h"
#include "exo_io_al_stm32f7xx_common.h"


#include "stm32f7xx_hal.h"

PCD_HandleTypeDef hpcd_USB_OTG_FS;
PCD_HandleTypeDef hpcd_USB_OTG_HS;


static void MX_USB_FS_PCD_Init(void);
/**
 * @brief SOF callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @param[in] cbid - ID of the callback event
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_sof_cb(PCD_HandleTypeDef *husbdev);
/**
 * @brief Setup stage callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_setup_stage_cb(PCD_HandleTypeDef *husbdev);
/**
 * @brief Reset callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_reset_cb(PCD_HandleTypeDef *husbdev);
/**
 * @brief Suspend callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_suspend_cb(PCD_HandleTypeDef *husbdev);
/**
 * @brief Resume callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_resume_cb(PCD_HandleTypeDef *husbdev);
/**
 * @brief Connect callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_connect_cb(PCD_HandleTypeDef *husbdev);
/**
 * @brief Disconnect callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_disconnect_cb(PCD_HandleTypeDef *husbdev);
/**
 * @brief Data outstage callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @param[in[ epnum - endpoint number
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_data_out_stage_cb(PCD_HandleTypeDef *husbdev, uint8 epnum);
/**
 * @brief Data instage callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @param[in[ epnum - endpoint number
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_data_in_stage_cb(PCD_HandleTypeDef *husbdev, uint8 epnum);
/**
 * @brief ISO out incomplete callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @param[in[ epnum - endpoint number
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_iso_out_incplt_cb(PCD_HandleTypeDef *husbdev, uint8 epnum);
/**
 * @brief ISO in incomplete callback event function
 * @param[in] husbdev - husbdev pointer to a PCD_HandleTypeDef structure that contains
 * 							the configuration information for UART
 * @param[in[ epnum - endpoint number
 * @retval No return
 */
void io_hal_stm32f7xx_usbdev_iso_in_incplt_cb(PCD_HandleTypeDef *husbdev, uint8 epnum);

/*!
 *  @brief This API initialize the control block memory of usb
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_init(ioal_usb_hdle *ioal_husbdev)
{

    MX_USB_FS_PCD_Init();
    hal_ret_sts sts= HAL_OK;
#ifdef STM32F765xx
    ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle=&hpcd_USB_OTG_FS;
#else
#ifdef STM32F769xx
    ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle=&hpcd_USB_OTG_HS;
#endif
#endif
    ioal_husbdev->intf_gen_info.state = IO_FREE_STATE;
    return sts;
}

/*!
 *  @brief This API deinit the USB
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_deinit(ioal_usb_hdle *ioal_husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_DeInit(husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API start the USB device
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_start(ioal_usb_hdle *ioal_husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_Start(husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API stop the USB device
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_stop(ioal_usb_hdle *ioal_husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_Stop(husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API initialize the USB FS
 */
static void MX_USB_FS_PCD_Init(void)
{
#ifdef STM32F765xx
    hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
    hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
    hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = 0;
    hpcd_USB_OTG_FS.Init.dma_enable = 0;
    hpcd_USB_OTG_FS.Init.low_power_enable = 0;
    hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
    hpcd_USB_OTG_FS.Init.Sof_enable = 0;
    hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
    hpcd_USB_OTG_FS.Init.vbus_sensing_enable = 0;
    hpcd_USB_OTG_FS.Init.lpm_enable = 0;

    if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
    {
        ioal_error_handler();
    }
#else
#ifdef STM32F769xx

    hpcd_USB_OTG_HS.Instance = USB_OTG_HS;
    hpcd_USB_OTG_HS.Init.dev_endpoints = 4;
    hpcd_USB_OTG_HS.Init.use_dedicated_ep1 = 0;


    hpcd_USB_OTG_HS.Init.dma_enable = 0;
    hpcd_USB_OTG_HS.Init.low_power_enable = 0;
    hpcd_USB_OTG_HS.Init.lpm_enable = 0;
    hpcd_USB_OTG_HS.Init.phy_itface = PCD_PHY_ULPI;
    hpcd_USB_OTG_HS.Init.Sof_enable = 0;
    hpcd_USB_OTG_HS.Init.speed = PCD_SPEED_HIGH;
    hpcd_USB_OTG_HS.Init.vbus_sensing_enable = 1;

    if (HAL_PCD_Init(&hpcd_USB_OTG_HS) != HAL_OK)
    {
        ioal_error_handler();
    }
#endif
#endif
}

/*!
 *  @brief This API register callback event
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_reg_cb(ioal_usb_hdle *ioal_husbdev, iohal_stm32_usbdev_cbid cbid)
{
    hal_ret_sts sts = HAL_SCS;
    PCD_HandleTypeDef *husbdev = ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle;

    switch (cbid)
    {
        case IOHAL_STM32_USBDEV_SOF_CB_ID :
            sts = HAL_PCD_RegisterCallback(husbdev, HAL_PCD_SOF_CB_ID, io_hal_stm32f7xx_usbdev_sof_cb);
            break;

        case IOHAL_STM32_USBDEV_SETUP_STAGE_CB_ID :
            sts = HAL_PCD_RegisterCallback(husbdev, HAL_PCD_SETUPSTAGE_CB_ID, io_hal_stm32f7xx_usbdev_setup_stage_cb);
            break;

        case IOHAL_STM32_USBDEV_RESET_CB_ID :
            sts = HAL_PCD_RegisterCallback(husbdev, HAL_PCD_RESET_CB_ID, io_hal_stm32f7xx_usbdev_reset_cb);
            break;

        case IOHAL_STM32_USBDEV_SUSPEND_CB_ID :
            sts = HAL_PCD_RegisterCallback(husbdev, HAL_PCD_SUSPEND_CB_ID, io_hal_stm32f7xx_usbdev_suspend_cb);
            break;

        case IOHAL_STM32_USBDEV_RESUME_CB_ID :
            sts = HAL_PCD_RegisterCallback(husbdev, HAL_PCD_RESUME_CB_ID, io_hal_stm32f7xx_usbdev_resume_cb);
            break;

        case IOHAL_STM32_USBDEV_CONNECT_CB_ID :
            sts = HAL_PCD_RegisterCallback(husbdev, HAL_PCD_CONNECT_CB_ID, io_hal_stm32f7xx_usbdev_connect_cb);
            break;

        case IOHAL_STM32_USBDEV_DISCONNECT_CB_ID :
            sts = HAL_PCD_RegisterCallback(husbdev, HAL_PCD_DISCONNECT_CB_ID, io_hal_stm32f7xx_usbdev_disconnect_cb);
            break;

        case IOHAL_STM32_USBDEV_DATA_OUT_STAGE_CB_ID :
            sts = HAL_PCD_RegisterDataOutStageCallback(husbdev, io_hal_stm32f7xx_usbdev_data_out_stage_cb);
            break;

        case IOHAL_STM32_USBDEV_DATA_IN_STAGE_CB_ID :
            sts = HAL_PCD_RegisterDataInStageCallback(husbdev, io_hal_stm32f7xx_usbdev_data_in_stage_cb);
            break;

        case IOHAL_STM32_USBDEV_ISO_OUT_INCPLT_CB_ID :
            sts = HAL_PCD_RegisterIsoOutIncpltCallback(husbdev, io_hal_stm32f7xx_usbdev_iso_out_incplt_cb);
            break;

        case IOHAL_STM32_USBDEV_ISO_IN_INCPLT_CB_ID :
            sts = HAL_PCD_RegisterIsoInIncpltCallback(husbdev, io_hal_stm32f7xx_usbdev_iso_in_incplt_cb);
            break;

        default :

            sts =  HAL_IO_INVLD_CB_FN;
            break;
    }
    return sts;
}

/*!
 *  @brief SOF callback event function
 */
void io_hal_stm32f7xx_usbdev_sof_cb(PCD_HandleTypeDef *husbdev)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->sof_cb(ioal_husbdev);
    }
    else
    {

    }
}

/*!
 *  @brief Setup stage callback event function
 */
void io_hal_stm32f7xx_usbdev_setup_stage_cb(PCD_HandleTypeDef *husbdev)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->setup_stage_cb(ioal_husbdev);
    }
    else
    {

    }
}

/*!
 *  @brief Reset callback event function
 */
void io_hal_stm32f7xx_usbdev_reset_cb(PCD_HandleTypeDef *husbdev)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->reset_cb(ioal_husbdev);
    }
    else
    {

    }
}

/*!
 *  @brief Suspend callback event function
 */
void io_hal_stm32f7xx_usbdev_suspend_cb(PCD_HandleTypeDef *husbdev)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->suspend_cb(ioal_husbdev);
    }
    else
    {

    }
}

/*!
 *  @brief Resume callback event function
 */
void io_hal_stm32f7xx_usbdev_resume_cb(PCD_HandleTypeDef *husbdev)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->resume_cb(ioal_husbdev);
    }
    else
    {

    }
}

/*!
 *  @brief Connect callback event function
 */
void io_hal_stm32f7xx_usbdev_connect_cb(PCD_HandleTypeDef *husbdev)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->connect_cb(ioal_husbdev);
    }
    else
    {

    }
}

/*!
 *  @brief Disconnect callback event function
 */
void io_hal_stm32f7xx_usbdev_disconnect_cb(PCD_HandleTypeDef *husbdev)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->disconnect_cb(ioal_husbdev);
    }
    else
    {

    }
}

/*!
 *  @brief Data outstage callback event function
 */
void io_hal_stm32f7xx_usbdev_data_out_stage_cb(PCD_HandleTypeDef *husbdev, uint8 epnum)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->data_out_stage_cb(ioal_husbdev, epnum);
    }
    else
    {

    }
}

/*!
 *  @brief Data instage callback event function
 */
void io_hal_stm32f7xx_usbdev_data_in_stage_cb(PCD_HandleTypeDef *husbdev, uint8 epnum)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->data_in_stage_cb(ioal_husbdev, epnum);
    }
    else
    {

    }
}

/*!
 *  @brief ISO out incomplete callback event function
 */
void io_hal_stm32f7xx_usbdev_iso_out_incplt_cb(PCD_HandleTypeDef *husbdev, uint8 epnum)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->iso_out_incplt_cb(ioal_husbdev, epnum);
    }
    else
    {

    }
}

/*!
 *  @brief ISO in incomplete callback event function
 */
void io_hal_stm32f7xx_usbdev_iso_in_incplt_cb(PCD_HandleTypeDef *husbdev, uint8 epnum)
{
    ioal_usb_hdle *ioal_husbdev = NULL;
    if(HAL_SCS == get_ioal_inst_from_vd_inst(husbdev, (void**)&ioal_husbdev))
    {
        ioal_husbdev->iso_in_incplt_cb(ioal_husbdev, epnum);
    }
    else
    {

    }
}

/*!
 *  @brief This API connects the USB device
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_devconnect (ioal_usb_hdle *ioal_husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_DevConnect(husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API disconnects the USB device
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_devdisconnect (ioal_usb_hdle *ioal_husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_DevDisconnect (husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;

}

/*!
 *  @brief This API sets the USB Device address
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_setaddress (ioal_usb_hdle *ioal_husbdev, uint8_t address)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_SetAddress(husbdev,address))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API opens and configures an endpoint
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_open (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_EP_Open (husbdev, ep_addr,ep_mps,ep_type))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API deactivate an endpoint
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_close (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_EP_Close (husbdev,ep_addr))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API receive an amount of data from the specified endpoint address
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_receive (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr, uint8_t *pbuf,uint32_t len)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_EP_Receive (husbdev,ep_addr,pbuf,len))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API get number of receive count for the specified endpoint address
 */
uint32_t io_hal_stm32f7xx_usbdev_ep_getrxcount (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr)
{
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    return HAL_PCD_EP_GetRxCount (husbdev,ep_addr);

}

/*!
 *  @brief This API send an amount of data for the specified endpoint address
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_transmit (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t len)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_EP_Transmit (husbdev,ep_addr,pbuf,len))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API set a stall condition for the specified endpoint address
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_setstall (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_EP_SetStall (husbdev,ep_addr))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API clear a stall condition for the specified endpoint address
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_clrstall (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_EP_ClrStall (husbdev,ep_addr))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API flush the specified endpoint
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_ep_flush (ioal_usb_hdle *ioal_husbdev, uint8_t ep_addr)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_EP_Flush (husbdev, ep_addr))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API activate remote wakeup signalling
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_activate_remote_wakeup (ioal_usb_hdle *ioal_husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_ActivateRemoteWakeup (husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

/*!
 *  @brief This API de-activate remote wakeup signalling.
 */
hal_ret_sts io_hal_stm32f7xx_usbdev_deactivate_remote_wakeup (ioal_usb_hdle *ioal_husbdev)
{
    hal_ret_sts ret_sts = HAL_MAX_ERR;
    PCD_HandleTypeDef *husbdev = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
    if(HAL_OK == HAL_PCD_DeActivateRemoteWakeup (husbdev))
    {
        ret_sts = HAL_SCS;
    }
    else
    {
        ret_sts = HAL_IO_VDP_ERR;
    }
    return ret_sts;
}

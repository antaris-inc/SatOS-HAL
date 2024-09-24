
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include "exo_io_al_usb_common.h"
#include "usb_device.h"
#include "usbd_cdc_ecm_if.h"
#include "usbd_desc.h"
#include "usbd_cdc_ecm.h"
#include "usbd_core.h"

extern ioal_usb_hdle io_hal_husbdev;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
                       PCD BSP Routines
*******************************************************************************/

/**
  * @brief  Initializes the PCD MSP.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  if(hpcd->Instance == USB_OTG_FS)
  {
    /* Configure USB FS GPIOs */
	    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
	    PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
	    PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
	    PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
	    PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV4;
	    PeriphClkInitStruct.PLLSAIDivQ = 1;
	    PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
	    PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	    {
	      Error_Handler();
	    }

    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Configure DM DP Pins */
    GPIO_InitStruct.Pin = (GPIO_PIN_11 | GPIO_PIN_12);
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


    /* Configure ID pin */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Enable USB FS Clock */
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

    /* Set USBFS Interrupt priority */
    HAL_NVIC_SetPriority(OTG_FS_IRQn, 6, 0);

    /* Enable USBFS Interrupt */
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
  }
  else if(hpcd->Instance == USB_OTG_HS)
  {
	  /* USER CODE BEGIN USB_OTG_HS_MspInit 0 */

	  /* USER CODE END USB_OTG_HS_MspInit 0 */

	    __HAL_RCC_GPIOB_CLK_ENABLE();
	    __HAL_RCC_GPIOI_CLK_ENABLE();
	    __HAL_RCC_GPIOH_CLK_ENABLE();
	    __HAL_RCC_GPIOC_CLK_ENABLE();
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    /**USB_OTG_HS GPIO Configuration
	    PB5     ------> USB_OTG_HS_ULPI_D7
	    PI11     ------> USB_OTG_HS_ULPI_DIR
	    PH4     ------> USB_OTG_HS_ULPI_NXT
	    PB13     ------> USB_OTG_HS_ULPI_D6
	    PB12     ------> USB_OTG_HS_ULPI_D5
	    PC0     ------> USB_OTG_HS_ULPI_STP
	    PA5     ------> USB_OTG_HS_ULPI_CK
	    PB10     ------> USB_OTG_HS_ULPI_D3
	    PA3     ------> USB_OTG_HS_ULPI_D0
	    PB1     ------> USB_OTG_HS_ULPI_D2
	    PB0     ------> USB_OTG_HS_ULPI_D1
	    PB11     ------> USB_OTG_HS_ULPI_D4
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_10
	                          |GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_11;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_11;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_4;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_0;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_3;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	    /* Peripheral clock enable */
	    __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
	    __HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE();

	    /* Peripheral interrupt init */
	    HAL_NVIC_SetPriority(OTG_HS_IRQn, 5, 0);
	    HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
	  /* USER CODE BEGIN USB_OTG_HS_MspInit 1 */

	  /* USER CODE END USB_OTG_HS_MspInit 1 */

  }
  else
  {

  }

}

/**
  * @brief  De-Initializes the PCD MSP.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd)
{
  if(hpcd->Instance == USB_OTG_FS)
  {
    /* Disable USB FS Clock */
    __HAL_RCC_USB_OTG_FS_CLK_DISABLE();
    __HAL_RCC_SYSCFG_CLK_DISABLE();
  }
  else if(hpcd->Instance == USB_OTG_HS)
  {
	  /* USER CODE BEGIN USB_OTG_HS_MspDeInit 0 */

	  /* USER CODE END USB_OTG_HS_MspDeInit 0 */
	    /* Disable Peripheral clock */
	    __HAL_RCC_USB_OTG_HS_CLK_DISABLE();
	    __HAL_RCC_USB_OTG_HS_ULPI_CLK_DISABLE();

	    /**USB_OTG_HS GPIO Configuration
	    PB5     ------> USB_OTG_HS_ULPI_D7
	    PI11     ------> USB_OTG_HS_ULPI_DIR
	    PH4     ------> USB_OTG_HS_ULPI_NXT
	    PB13     ------> USB_OTG_HS_ULPI_D6
	    PB12     ------> USB_OTG_HS_ULPI_D5
	    PC0     ------> USB_OTG_HS_ULPI_STP
	    PA5     ------> USB_OTG_HS_ULPI_CK
	    PB10     ------> USB_OTG_HS_ULPI_D3
	    PA3     ------> USB_OTG_HS_ULPI_D0
	    PB1     ------> USB_OTG_HS_ULPI_D2
	    PB0     ------> USB_OTG_HS_ULPI_D1
	    PB11     ------> USB_OTG_HS_ULPI_D4
	    */
	    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5|GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_10
	                          |GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_11);

	    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_11);

	    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_4);

	    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0);

	    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_3);

	    /* Peripheral interrupt Deinit*/
	    HAL_NVIC_DisableIRQ(OTG_HS_IRQn);

	  /* USER CODE BEGIN USB_OTG_HS_MspDeInit 1 */

	  /* USER CODE END USB_OTG_HS_MspDeInit 1 */
  }
  else
  {
  }
}

/******************************************************************************
                       LL Driver Callbacks (PCD -> USB Device Library)
                       */

/**
  * @brief  SetupStage callback.
  * @param  hpcd: PCD handle
  * @retval None
  **/

void io_hal_pcd_setupstage_cb(ioal_usb_hdle *ioal_husbdev)
{
  PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  (void)USBD_LL_SetupStage(hpcd->pData, (uint8_t *)hpcd->Setup);
}

/**
  * @brief  DataOut Stage cb.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void io_hal_pcd_dataoutstage_cb(ioal_usb_hdle *ioal_husbdev, uint8_t epnum)
{
  PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  (void)USBD_LL_DataOutStage(hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}

/**
  * @brief  DataIn Stage cb.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void io_hal_pcd_datainstage_cb(ioal_usb_hdle *ioal_husbdev, uint8_t epnum)
{
  PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  (void)USBD_LL_DataInStage(hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}

/**
  * @brief  SOF cb.
  * @param  hpcd: PCD handle
  * @retval None
  */
void io_hal_pcd_sof_cb(ioal_usb_hdle *ioal_husbdev)
{
	PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  (void)USBD_LL_SOF(hpcd->pData);
}

/**
  * @brief  Reset cb.
  * @param  hpcd: PCD handle
  * @retval None
  */
void io_hal_pcd_reset_cb(ioal_usb_hdle *ioal_husbdev)
{
  USBD_SpeedTypeDef speed;
  PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  /* Set USB Current Speed */
  switch(hpcd->Init.speed)
  {
  case PCD_SPEED_HIGH:
    speed = USBD_SPEED_HIGH;
    break;

  case PCD_SPEED_FULL:
    speed = USBD_SPEED_FULL;
    break;

  default:
    speed = USBD_SPEED_FULL;
    break;
  }

  /* Reset Device */
  (void)USBD_LL_Reset(hpcd->pData);
  (void)USBD_LL_SetSpeed(hpcd->pData, speed);
}

/**
  * @brief  Suspend cb.
  * @param  hpcd: PCD handle
  * @retval None
  */
void io_hal_pcd_suspend_cb(ioal_usb_hdle *ioal_husbdev)
{
	PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  (void)USBD_LL_Suspend(hpcd->pData);
}

/**
  * @brief  Resume cb.
  * @param  hpcd: PCD handle
  * @retval None
  */
void io_hal_pcd_resume_cb(ioal_usb_hdle *ioal_husbdev)
{
	PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  (void)USBD_LL_Resume(hpcd->pData);
}

/**
  * @brief  ISOOUTIncomplete cb.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void io_hal_pcd_iso_out_incomplete_cb(ioal_usb_hdle *ioal_husbdev, uint8_t epnum)
{
	PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  (void)USBD_LL_IsoOUTIncomplete(hpcd->pData, epnum);
}

/**
  * @brief  ISOINIncomplete cb.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void io_hal_pcd_iso_in_incomplete_cb(ioal_usb_hdle *ioal_husbdev, uint8_t epnum)
{
	PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  (void)USBD_LL_IsoINIncomplete(hpcd->pData, epnum);
}

/**
  * @brief  Connectcb cb.
  * @param  hpcd: PCD handle
  * @retval None
  */
void io_hal_pcd_connect_cb(ioal_usb_hdle *ioal_husbdev)
{
	PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  (void)USBD_LL_DevConnected(hpcd->pData);
}

/**
  * @brief  Disconnect cb.
  * @param  hpcd: PCD handle
  * @retval None
  */
void io_hal_pcd_disconnect_cb(ioal_usb_hdle *ioal_husbdev)
{
	PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)(ioal_husbdev->intf_gen_info.vdp_intf_inst_hdle);
  (void)USBD_LL_DevDisconnected(hpcd->pData);
}


/*******************************************************************************
                       LL Driver Interface (USB Device Library --> PCD)
*******************************************************************************/

/**
  * @brief  Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Init(USBD_HandleTypeDef *pdev)
{
#if defined(STM32F765xx) || defined(COREBOARD)
    io_hal_usb_device_init();
    ((PCD_HandleTypeDef*)(io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle))->pData = pdev;
    pdev->pData= io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle;
    (void)HAL_PCDEx_SetRxFiFo(((PCD_HandleTypeDef*)(io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle)), 0x80);
    (void)HAL_PCDEx_SetTxFiFo(((PCD_HandleTypeDef*)(io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle)), 0, 0x20);
    (void)HAL_PCDEx_SetTxFiFo(((PCD_HandleTypeDef*)(io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle)), 1, 0x20);
    (void)HAL_PCDEx_SetTxFiFo(((PCD_HandleTypeDef*)(io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle)), 2, 0x20);

  /* Initialize LL Driver */

#else
#ifdef STM32F769xx
    io_hal_usb_device_init();
    ((PCD_HandleTypeDef*)(io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle))->pData = pdev;
    pdev->pData= io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle;
    (void)HAL_PCDEx_SetRxFiFo(((PCD_HandleTypeDef*)(io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle)), 0x200);
    (void)HAL_PCDEx_SetTxFiFo(((PCD_HandleTypeDef*)(io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle)), 0, 0x40);
    (void)HAL_PCDEx_SetTxFiFo(((PCD_HandleTypeDef*)(io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle)), 1, 0x100);
    (void)HAL_PCDEx_SetTxFiFo(((PCD_HandleTypeDef*)(io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle)), 2, 0x40);

#endif
#endif

  return USBD_OK;
}

/**
  * @brief  De-Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_DeInit(USBD_HandleTypeDef *pdev)
{
  io_hal_usb_device_deinit();
  return USBD_OK;
}

/**
  * @brief  Starts the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Start(USBD_HandleTypeDef *pdev)
{
  io_hal_usb_device_start(&io_hal_husbdev);
  return USBD_OK;

}

/**
  * @brief  Stops the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Stop(USBD_HandleTypeDef *pdev)
{
  io_hal_usb_device_stop(&io_hal_husbdev);
  return USBD_OK;
}

/**
  * @brief  Opens an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  ep_type: Endpoint Type
  * @param  ep_mps: Endpoint Max Packet Size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_OpenEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr,
                                  uint8_t ep_type, uint16_t ep_mps)
{
  io_hal_usb_device_ep_open(&io_hal_husbdev,ep_addr, ep_mps, ep_type);
  return USBD_OK;

}

/**
  * @brief  Closes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_CloseEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  io_hal_usb_device_ep_close(&io_hal_husbdev,ep_addr);
  return USBD_OK;
}

/**
  * @brief  Flushes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_FlushEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  io_hal_usb_device_ep_flush(&io_hal_husbdev,ep_addr);
  return USBD_OK;
}

/**
  * @brief  Sets a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_StallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  io_hal_usb_device_ep_setstall(&io_hal_husbdev,ep_addr);
  return USBD_OK;
}

/**
  * @brief  Clears a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_ClearStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  io_hal_usb_device_ep_clrstall(&io_hal_husbdev,ep_addr);
  return USBD_OK;
}

/**
  * @brief  Returns Stall condition.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval Stall (1: Yes, 0: No)
  */
uint8_t USBD_LL_IsStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*)io_hal_husbdev.intf_gen_info.vdp_intf_inst_hdle;
  if((ep_addr & 0x80U) == 0x80U)
  {
    return hpcd->IN_ep[ep_addr & 0x7FU].is_stall;
  }
  else
  {
    return hpcd->OUT_ep[ep_addr & 0x7FU].is_stall;
  }
}

/**
  * @brief  Assigns a USB address to the device.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_SetUSBAddress(USBD_HandleTypeDef *pdev, uint8_t dev_addr)
{
  io_hal_usb_device_setaddress(&io_hal_husbdev,dev_addr);
  return USBD_OK;
}

/**
  * @brief  Transmits data over an endpoint.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  pbuf: Pointer to data to be sent
  * @param  size: Data size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Transmit(USBD_HandleTypeDef *pdev,
                                    uint8_t ep_addr,
                                    uint8_t *pbuf,
                                    uint32_t size)
{
  /* Get the packet total length */
  pdev->ep_in[ep_addr & 0x7FU].total_length = size;
  io_hal_usb_device_ep_transmit(&io_hal_husbdev,ep_addr, pbuf, size);
  return USBD_OK;
}

/**
  * @brief  Prepares an endpoint for reception.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  pbuf: Pointer to data to be received
  * @param  size: Data size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_PrepareReceive(USBD_HandleTypeDef *pdev,
                                          uint8_t ep_addr,
                                          uint8_t *pbuf,
                                          uint32_t size)

{
  io_hal_usb_device_ep_receive(&io_hal_husbdev,ep_addr, pbuf, size);
  return USBD_OK;
}

/**
  * @brief  Returns the last transferred packet size.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval Received Data Size
  */
uint32_t USBD_LL_GetRxDataSize(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
    return io_hal_usb_device_ep_getrxcount(&io_hal_husbdev,ep_addr);
}

/**
  * @brief  Delays routine for the USB Device Library.
  * @param  Delay: Delay in ms
  * @retval None
  */
void USBD_LL_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}


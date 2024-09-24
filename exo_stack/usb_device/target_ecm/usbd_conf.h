/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF_H
#define __USBD_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal_ext.h"
#include "exo_io_al_usb_common.h"
#include "exo_osal.h"
#include <stdlib.h>
#include <string.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Common Config */
#define USBD_MAX_NUM_INTERFACES               1
#define USBD_MAX_NUM_CONFIGURATION            1
#define USBD_MAX_STR_DESC_SIZ                 0x100
#define USBD_SUPPORT_USER_STRING_DESC         1 
#define USBD_SELF_POWERED                     1
#define USBD_DEBUG_LEVEL                      0

#ifdef STM32F765xx
#define USE_USB_FS 1
#else
#ifdef STM32F769xx
#define USE_USB_HS 1
#endif
#endif
/* Exported macro ------------------------------------------------------------*/
/* Memory management macros */   
#define USBD_malloc               malloc
#define USBD_free                 free
#define USBD_memset               memset
#define USBD_memcpy               os_memcpy
#define USBD_Delay                os_delay

/* DEBUG macros */
#if (USBD_DEBUG_LEVEL > 0U)
#define  USBD_UsrLog(...)   do { \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBD_UsrLog(...) do {} while (0)
#endif

#if (USBD_DEBUG_LEVEL > 1U)

#define  USBD_ErrLog(...) do { \
                            printf("ERROR: ") ; \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBD_ErrLog(...) do {} while (0)
#endif

#if (USBD_DEBUG_LEVEL > 2U)
#define  USBD_DbgLog(...)   do { \
                            printf("DEBUG : ") ; \
                            printf(__VA_ARGS__); \
                            printf("\n"); \
} while (0)
#else
#define USBD_DbgLog(...) do {} while (0)
#endif

void io_hal_usbdev_sof_cb(ioal_usb_hdle *husbdev);
void io_hal_setup_stage_cb(ioal_usb_hdle *husbdev);
void io_hal_usbdev_reset_cb(ioal_usb_hdle *husbdev);
void io_hal_usbdev_suspend_cb(ioal_usb_hdle *husbdev);
void io_hal_usbdev_resume_cb(ioal_usb_hdle *husbdev);
void io_hal_usbdev_connect_cb(ioal_usb_hdle *husbdev);
void io_hal_usbdev_disconnect_cb(ioal_usb_hdle *husbdev);
void io_hal_usbdev_data_out_stage_cb(ioal_usb_hdle *husbdev, uint8_t epnum);
void io_hal_usbdev_data_in_stage_cb(ioal_usb_hdle *husbdev, uint8_t epnum);
void io_hal_usbdev_iso_out_incplt_cb(ioal_usb_hdle *husbdev, uint8_t epnum);
void io_hal_usbdev_iso_in_incplt_cb(ioal_usb_hdle *husbdev, uint8_t epnum);

/* Exported functions ------------------------------------------------------- */
#ifdef USE_USB_FS 
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
#endif
#ifdef USE_USB_HS
extern PCD_HandleTypeDef hpcd_USB_HS;
#endif
#endif /* __USBD_CONF_H */


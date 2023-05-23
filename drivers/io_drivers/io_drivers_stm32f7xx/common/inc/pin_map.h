#ifndef PIN_MAP
#define PIN_MAP

#include "stm32f769ni_disco_pinmap.h"
#include "stm32f765zi_pinmap.h"

#ifdef STM32F769xx
#define I2C1_SDA          STM32F769_I2C1_SDA
#define I2C1_SCK          STM32F769_I2C1_SCK
#define I2C1_PORT         STM32F769_I2C1_PORT

#define UART6_TX          STM32F769_UART6_TX
#define UART6_RX          STM32F769_UART6_RX
#define UART6_PORT        STM32F769_UART6_PORT

#define UART1_TX          STM32F769_UART1_TX
#define UART1_RX          STM32F769_UART1_RX
#define UART1_PORT        STM32F769_UART1_PORT

#define SPI2_MOSI  	      STM32F769_SPI2_MOSI
#define SPI2_MISO         STM32F769_SPI2_MISO
#define SPI2_SCK          STM32F769_SPI2_SCK
#define SPI2_PORT         STM32F769_SPI2_PORT
#define SPI2_SCK_PORT     STM32F769_SPI2_SCK_PORT

#define CAN1_TX           STM32F769_CAN1_TX
#define CAN1_RX           STM32F769_CAN1_RX
#define CAN1_PORT         STM32F769_CAN1_PORT

#define CAN3_TX           STM32F769_CAN3_TX
#define CAN3_RX           STM32F769_CAN3_RX
#define CAN3_PORT         STM32F769_CAN3_PORT

#define CAN2_TX           STM32F769_CAN2_TX
#define CAN2_RX           STM32F769_CAN2_RX
#define CAN2_PORT         STM32F769_CAN2_PORT

#endif

#ifdef STM32F765xx

#define I2C1_SDA          STM32F765_I2C1_SDA
#define I2C1_SCK          STM32F765_I2C1_SCK
#define I2C1_PORT         STM32F765_I2C1_PORT

#define UART6_TX          STM32F765_UART6_TX
#define UART6_RX          STM32F765_UART6_RX
#define UART6_PORT        STM32F765_UART6_PORT

#define UART1_TX          STM32F765_UART1_TX
#define UART1_RX          STM32F765_UART1_RX
#define UART1_PORT        STM32F765_UART1_PORT

#define SPI1_MOSI         STM32F765_SPI1_MOSI
#define SPI1_MISO         STM32F765_SPI1_MISO
#define SPI1_SCK          STM32F765_SPI1_SCK
#define SPI1_PORT         STM32F765_SPI1_PORT
#define SPI1_SCK_PORT     STM32F765_SPI1_SCK_PORT

#define SPI2_MOSI         STM32F765_SPI2_MOSI
#define SPI2_MISO         STM32F765_SPI2_MISO
#define SPI2_SCK          STM32F765_SPI2_SCK
#define SPI2_PORT         STM32F765_SPI2_PORT
#define SPI2_SCK_PORT     STM32F765_SPI2_SCK_PORT


#define CAN1_TX           STM32F765_CAN1_TX
#define CAN1_RX           STM32F765_CAN1_RX
#define CAN1_PORT         STM32F765_CAN1_PORT

#define CAN3_TX           STM32F765_CAN3_TX
#define CAN3_RX           STM32F765_CAN3_RX
#define CAN3_PORT         STM32F765_CAN3_PORT

#define CAN2_TX           STM32F765_CAN2_TX
#define CAN2_RX           STM32F765_CAN2_RX
#define CAN2_PORT         STM32F765_CAN2_PORT

#endif


#endif





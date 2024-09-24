/**
 * @file exo_pinmap.h
 *
 * @brief This file contains GPIO pin mapping for STM32 Discover board
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

#ifndef STM32F769_PIN_MAP
#define STM32F769_PIN_MAP

#define RTC_ASYNCH_PREDIV  0x7F ///< RTC asynchronous prescaler for LSE clock source
#define RTC_SYNCH_PREDIV   0x00FF ///< RTC synchronous prescaler for LSE clock source
#define STM32F769_I2C1_SDA      GPIO_PIN_9  ///< GPIO pin for I2C1 SDA
#define STM32F769_I2C1_SCK      GPIO_PIN_8  ///< GPIO pin for I2C1 SCK
#define STM32F769_I2C1_PORT     GPIOB       ///< I2C1 port
#define STM32F769_UART6_TX       GPIO_PIN_6  ///< GPIO pin for UART6 TX
#define STM32F769_UART6_RX       GPIO_PIN_7  ///< GPIO pin for UART6 RX
#define STM32F769_UART6_PORT     GPIOC       ///< UART6 port
#define STM32F769_UART1_TX       GPIO_PIN_9  ///< GPIO pin for UART1 TX
#define STM32F769_UART1_RX       GPIO_PIN_10 ///< GPIO pin for UART1 RX

#define STM32F769_UART1_PORT     GPIOA       ///< UART1 port
#define STM32F769_SPI2_MOSI      GPIO_PIN_15 ///< GPIO pin for SPI2 MOSI
#define STM32F769_SPI2_MISO      GPIO_PIN_14 ///< GPIO pin for SPI2 MISO
#define STM32F769_SPI2_SCK       GPIO_PIN_12 ///< GPIO pin for SPI2 SCK
#define STM32F769_SPI2_PORT      GPIOB       ///< SPI2 port
#define STM32F769_SPI2_SCK_PORT  GPIOA       ///< SPI2 SCK port
#define STM32F769_CAN1_TX         GPIO_PIN_9  ///< GPIO pin for CAN1 TX
#define STM32F769_CAN1_RX         GPIO_PIN_8  ///< GPIO pin for CAN1 RX
#define STM32F769_CAN1_PORT       GPIOB       ///< CAN1 port

#define STM32F769_CAN3_TX         GPIO_PIN_4  ///< GPIO pin for CAN3 TX

#define STM32F769_CAN3_RX         GPIO_PIN_3  ///< GPIO pin for CAN3 RX
#define STM32F769_CAN3_PORT       GPIOB       ///< CAN3 port
#define STM32F769_CAN2_TX         GPIO_PIN_13 ///< GPIO pin for CAN2 TX
#define STM32F769_CAN2_RX         GPIO_PIN_12 ///< GPIO pin for CAN2 RX
#define STM32F769_CAN2_PORT       GPIOB       ///< CAN2 port
#define I2C1_SDA          STM32F769_I2C1_SDA  ///< STM32F769 I2C1 SDA pin
#define I2C1_SCK          STM32F769_I2C1_SCK  ///< STM32F769 I2C1 SCK pin
#define I2C1_PORT         STM32F769_I2C1_PORT ///< STM32F769 I2C1 port
#define UART6_TX          STM32F769_UART6_TX ///< STM32F769 UART6 TX pin
#define UART6_RX          STM32F769_UART6_RX ///< STM32F769 UART6 RX pin
#define UART6_PORT        STM32F769_UART6_PORT ///< STM32F769 UART6 port
#define UART1_TX          STM32F769_UART1_TX ///< STM32F769 UART1 TX pin
#define UART1_RX          STM32F769_UART1_RX ///< STM32F769 UART1 RX pin
#define UART1_PORT        STM32F769_UART1_PORT ///< STM32F769 UART1 port
#define SPI2_MOSI         STM32F769_SPI2_MOSI ///< STM32F769 SPI2 MOSI pin
#define SPI2_MISO         STM32F769_SPI2_MISO ///< STM32F769 SPI2 MISO pin
#define SPI2_SCK          STM32F769_SPI2_SCK  ///< STM32F769 SPI2 SCK pin
#define SPI2_PORT         STM32F769_SPI2_PORT ///< STM32F769 SPI2 port
#define SPI2_SCK_PORT     STM32F769_SPI2_SCK_PORT ///< STM32F769 SPI2 SCK port
#define CAN1_TX           STM32F769_CAN1_TX ///< STM32F769 CAN1 TX pin
#define CAN1_RX           STM32F769_CAN1_RX ///< STM32F769 CAN1 RX pin
#define CAN1_PORT         STM32F769_CAN1_PORT ///< STM32F769 CAN1 port
#define CAN3_TX           STM32F769_CAN3_TX ///< STM32F769 CAN3 TX pin
#define CAN3_RX           STM32F769_CAN3_RX ///< STM32F769 CAN3 RX pin
#define CAN3_PORT         STM32F769_CAN3_PORT ///< STM32F769 CAN3 port
#define CAN2_TX           STM32F769_CAN2_TX ///< STM32F769 CAN2 TX pin
#define CAN2_RX           STM32F769_CAN2_RX ///< STM32F769 CAN2 RX pin
#define CAN2_PORT         STM32F769_CAN2_PORT ///< STM32F769 CAN2 port

#endif /* STM32F769_PIN_MAP */

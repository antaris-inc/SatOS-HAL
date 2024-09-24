/**
 * @file exo_pinmap.h
 *
 * @brief This file contains GPIO mapping
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

#ifndef DRIVERS_BSP_JANUS2_STM32F7XX_PIN_MAP_H_
#define DRIVERS_BSP_JANUS2_STM32F7XX_PIN_MAP_H_

/*Includes --------------------------------------------------------------*/
#include "exo_hal_io_al_common.h"
#include "exo_io_al_gpio_common.h"
#include "exo_ahw_al_gpio_exp_common.h"


#define RTC_CLOCK_SOURCE_LSE    ///< RTC clock source LSE

#define RTC_ASYNCH_PREDIV  0x7F    ///< RTC asynchronous prescaler
#define RTC_SYNCH_PREDIV   0x00FF  ///< RTC synchronous prescaler

#define I2C1_SDA        GPIO_PIN_9 ///< PB9 for I2C 1 SDA
#define I2C1_SDA_PORT   GPIOB      ///< I2C 1 SDA port
#define I2C1_SCL        GPIO_PIN_8 ///< PB8 for I2C 1 SCL
#define I2C1_SCL_PORT   GPIOB      ///< I2C 1 SCL port

#define I2C2_SDA        GPIO_PIN_5 ///< PH5 for I2C 2 SDA
#define I2C2_SDA_PORT   GPIOH      ///< I2C 2 SDA port
#define I2C2_SCL        GPIO_PIN_4 ///< PH4 I2C 2 SCL
#define I2C2_SCL_PORT   GPIOH      ///< I2C 2 SCL port

#define I2C3_SDA        GPIO_PIN_9 ///< PC9 for I2C 3 SDA
#define I2C3_SDA_PORT   GPIOC      ///< I2C 3 SDA port
#define I2C3_SCL        GPIO_PIN_7 ///< PH7 I2C 3 SCL
#define I2C3_SCL_PORT   GPIOH      ///< I2C 3 SCL port

#define I2C4_SDA        GPIO_PIN_7 ///< PB7 for I2C 4 SDA
#define I2C4_SDA_PORT   GPIOB      ///< I2C 4 SDA port
#define I2C4_SCL        GPIO_PIN_6 ///< PB6 I2C 4 SCL
#define I2C4_SCL_PORT   GPIOB      ///< I2C 4 SCL port


#define UART5_TX        GPIO_PIN_12 ///< PC12 for UART 5 TX
#define UART5_TX_PORT   GPIOC       ///< UART 5 TX port
#define UART5_RX        GPIO_PIN_2  ///< PD2 for UART 5 RX
#define UART5_RX_PORT   GPIOD       ///< UART 5 RX port

#define UART4_TX        GPIO_PIN_10 ///< PC10 for UART 4 TX
#define UART4_TX_PORT   GPIOC       ///< UART 4 TX port
#define UART4_RX        GPIO_PIN_11 ///< PC11 for UART 4 RX
#define UART4_RX_PORT   GPIOC       ///< UART 4 RX port

#define SPI1_CS        PA4      ///< PA4 for SPI1 Chip Select
#define SPI1_MOSI      PD7      ///< PD7 for SPI1 Master Out Slave In (MOSI)
#define SPI1_MISO      PA6      ///< PA6 for SPI1 Master In Slave Out (MISO)
#define SPI1_SCL       PA5      ///< PA5 for SPI1 Serial Clock (SCL)
#define SPI1_RST       PJ4      ///< PJ4 for SPI1 Reset (RST)
#define SPI1_IRQ       PJ5      ///< PJ5 for SPI1 Interrupt Request (IRQ)
#define SPI1_PORT                ///< SPI1 general port (to be defined)
#define SPI1_SCK_PORT            ///< SPI1 clock port (to be defined)

/**
 * @brief CAN2 GPIO Configuration
 */
#define CAN2_TX      PB13     ///< PB13 for CAN2 Transmit
#define CAN2_RX      PB12     ///< PB12 for CAN2 Receive
#define CAN2_PORT               ///< CAN2 general port (to be defined)

/**
 * @brief QUADSPI GPIO Configuration
 */
#define QUADSPI_BK1_IO2  PF7   ///< PF7 for QUADSPI Bank 1 IO2
#define QUADSPI_BK1_IO3  PF6   ///< PF6 for QUADSPI Bank 1 IO3
#define QUADSPI_CLK      PF10  ///< PF10 for QUADSPI Clock
#define QUADSPI_BK1_IO1  PF9   ///< PF9 for QUADSPI Bank 1 IO1
#define QUADSPI_BK1_IO0  PF8   ///< PF8 for QUADSPI Bank 1 IO0
#define QUADSPI_BK1_NCS  PB10  ///< PB10 for QUADSPI Bank 1 Chip Select (NCS)

/**
 * @brief FMC GPIO Configuration
 */
#define FMC_SDCLK    PG8      ///< PG8 for FMC SDRAM Clock
#define FMC_SDNE0    PH3      ///< PH3 for FMC SDRAM Chip Select (SDNE0)
#define FMC_SDCKE0   PH2      ///< PH2 for FMC SDRAM Clock Enable (SDCKE0)
#define FMC_SDNWE    PC0      ///< PC0 for FMC SDRAM Write Enable (SDNWE)
#define FMC_SDNCAS   PG15     ///< PG15 for FMC SDRAM Column Address Select (SDNCAS)
#define FMC_SDNRAS   PF11     ///< PF11 for FMC SDRAM Row Address Select (SDNRAS)

#define FMC_NE1      PC7      ///< PC7 for FMC Chip Select 1 (NE1)
#define FMC_NOE      PD4      ///< PD4 for FMC Output Enable (NOE)
#define FMC_NWE      PD5      ///< PD5 for FMC Write Enable (NWE)
#define FMC_NWAIT    PD6      ///< PD6 for FMC Wait (NWAIT)
#define FMC_NBL3     PI5      ///< PI5 for FMC Byte Lane 3 (NBL3)

#define FMC_BA0      PG4      ///< PG4 for FMC Bank Address 0 (BA0)
#define FMC_BA1      PG5      ///< PG5 for FMC Bank Address 1 (BA1)

#define FMC_NBL0     PE0      ///< PE0 for FMC Byte Lane 0 (NBL0)
#define FMC_NBL1     PE1      ///< PE1 for FMC Byte Lane 1 (NBL1)
#define FMC_NBL2     PI4      ///< PI4 for FMC Byte Lane 2 (NBL2)

#define FMC_A0       PF0      ///< PF0 for FMC Address Line 0 (A0)
#define FMC_A1       PF1      ///< PF1 for FMC Address Line 1 (A1)
#define FMC_A2       PF2      ///< PF2 for FMC Address Line 2 (A2)
#define FMC_A3       PF3      ///< PF3 for FMC Address Line 3 (A3)
#define FMC_A4       PF4      ///< PF4 for FMC Address Line 4 (A4)
#define FMC_A5       PF5      ///< PF5 for FMC Address Line 5 (A5)
#define FMC_A6       PF12     ///< PF12 for FMC Address Line 6 (A6)
#define FMC_A7       PF13     ///< PF13 for FMC Address Line 7 (A7)
#define FMC_A8       PF14     ///< PF14 for FMC Address Line 8 (A8)
#define FMC_A9       PF15     ///< PF15 for FMC Address Line 9 (A9)
#define FMC_A10      PG0      ///< PG0 for FMC Address Line 10 (A10)
#define FMC_A11      PG1      ///< PG1 for FMC Address Line 11 (A11)
#define FMC_A12      PG2      ///< PG2 for FMC Address Line 12 (A12)
#define FMC_A13      PG3      ///< PG3 for FMC Address Line 13 (A13)
#define FMC_A14      PG4      ///< PG4 for FMC Address Line 14 (A14)
#define FMC_A15      PG5      ///< PG5 for FMC Address Line 15 (A15)
#define FMC_A16      PD11     ///< PD11 for FMC Address Line 16 (A16)
#define FMC_A17      PD12     ///< PD12 for FMC Address Line 17 (A17)
#define FMC_A18      PD13     ///< PD13 for FMC Address Line 18 (A18)
#define FMC_A19      PE3      ///< PE3 for FMC Address Line 19 (A19)
#define FMC_A20      PE4      ///< PE4 for FMC Address Line 20 (A20)
#define FMC_A21      PE5      ///< PE5 for FMC Address Line 21 (A21)
#define FMC_A22      PE6      ///< PE6 for FMC Address Line 22 (A22)

#define FMC_D0       PD14     ///< PD14 for FMC Data Line 0 (D0)
#define FMC_D1       PD15     ///< PD15 for FMC Data Line 1 (D1)
#define FMC_D2       PD0      ///< PD0 for FMC Data Line 2 (D2)
#define FMC_D3       PD1      ///< PD1 for FMC Data Line 3 (D3)
#define FMC_D4       PE7      ///< PE7 for FMC Data Line 4 (D4)
#define FMC_D5       PE8      ///< PE8 for FMC Data Line 5 (D5)
#define FMC_D6       PE9      ///< PE9 for FMC Data Line 6 (D6)
#define FMC_D7       PE10     ///< PE10 for FMC Data Line 7 (D7)
#define FMC_D8       PE11     ///< PE11 for FMC Data Line 8 (D8)
#define FMC_D9       PE12     ///< PE12 for FMC Data Line 9 (D9)
#define FMC_D10      PE13     ///< PE13 for FMC Data Line 10 (D10)
#define FMC_D11      PE14     ///< PE14 for FMC Data Line 11 (D11)
#define FMC_D12      PE15     ///< PE15 for FMC Data Line 12 (D12)
#define FMC_D13      PD8      ///< PD8 for FMC Data Line 13 (D13)
#define FMC_D14      PD9      ///< PD9 for FMC Data Line 14 (D14)
#define FMC_D15      PD10     ///< PD10 for FMC Data Line 15 (D15)
#define FMC_D16      PH8      ///< PH8 for FMC Data Line 16 (D16)
#define FMC_D17      PH9      ///< PH9 for FMC Data Line 17 (D17)
#define FMC_D18      PH10     ///< PH10 for FMC Data Line 18 (D18)
#define FMC_D19      PH11     ///< PH11 for FMC Data Line 19 (D19)
#define FMC_D20      PH12     ///< PH12 for FMC Data Line 20 (D20)
#define FMC_D21      PH13     ///< PH13 for FMC Data Line 21 (D21)
#define FMC_D22      PH14     ///< PH14 for FMC Data Line 22 (D22)
#define FMC_D23      PH15     ///< PH15 for FMC Data Line 23 (D23)
#define FMC_D24      PI0      ///< PI0 for FMC Data Line 24 (D24)
#define FMC_D25      PI1      ///< PI1 for FMC Data Line 25 (D25)
#define FMC_D26      PI2      ///< PI2 for FMC Data Line 26 (D26)
#define FMC_D27      PI3      ///< PI3 for FMC Data Line 27 (D27)
#define FMC_D28      PI6      ///< PI6 for FMC Data Line 28 (D28)
#define FMC_D29      PI7      ///< PI7 for FMC Data Line 29 (D29)
#define FMC_D30      PI9      ///< PI9 for FMC Data Line 30 (D30)
#define FMC_D31      PI10     ///< PI10 for FMC Data Line 31 (D31)

/** MCP sensor related mapping**/
#define MCU_GPIO(x) ((x <<8)  | MCU_ID)
#define MCP23008_EDGE_1_GPIO(x) ((x <<8)  | GPIO_EXPANDER_MCP23008_EDGE_1)
#define MCP23008_EDGE_2_GPIO(x) ((x <<8)  | GPIO_EXPANDER_MCP23008_EDGE_2)
#define MCP23008_OBC_1_GPIO(x) ((x <<8)  | GPIO_EXPANDER_MCP23008_OBC_1)
#define MCP23008_OBC_2_GPIO(x) ((x <<8)  | GPIO_EXPANDER_MCP23008_OBC_2)
#define MCP23008_GPS_GPIO(x) ((x <<8)  | GPIO_EXPANDER_MCP23008_GPS)
#define PCAL6408A_PS_GPIO(x) ((x <<8)  | GPIO_EXPANDER_PCAL6408A_PS)


//#define CORE_CURRENT_SENSE_INT  MCU_GPIO(IOAL_GPIO_PIN_0)
//#define PLD_SSD_EN   MCP23008_OBC_1_GPIO(GPIO_EXP_GPIO_6)

/** PS sensor related mapping**/
#define PS_CURRENT_SENSE_INT               MCU_GPIO(IOAL_GPIO_PIN_161)
#define PS_TEMP_SENSE_INT                  MCU_GPIO(IOAL_GPIO_PIN_163)
/** Core sensor related mapping**/
#define CORE_CURRENT_SENSE_INT             MCU_GPIO(IOAL_GPIO_PIN_137)
#define CORE_TEMP_SENSE_INT                MCU_GPIO(IOAL_GPIO_PIN_104)
#define CORE_IO2_EXPD_INT                  MCU_GPIO(IOAL_GPIO_PIN_144)
#define CORE_IO1_EXPD_INT                  MCU_GPIO(IOAL_GPIO_PIN_167)
/** EDGE sensor related mapping**/
#define EDGE_IO_INT                        MCU_GPIO(IOAL_GPIO_PIN_164)

/** GPS IO expander GPIO mapping**/
#define GPS_IO_EXPD_INT                    MCU_GPIO(IOAL_GPIO_PIN_145)
/** Shutdown request gpio mapping **/
#define SHUTDOWN_REQ                       MCU_GPIO(IOAL_GPIO_PIN_17)
/** power Enable gpio mapping **/
#define POWER_EN                           MCU_GPIO(IOAL_GPIO_PIN_18)
/** SUS S3 Core gpio mapping **/
#define SUS_S3_CORE                        MCU_GPIO(IOAL_GPIO_PIN_19)

#define SPI1_NSS              MCU_GPIO(IOAL_GPIO_PIN_5) ///< SPI 1 NSS gpio mapping
#define MCO                   MCU_GPIO(IOAL_GPIO_PIN_9) ///< MCU gpio mapping
#define ETH_RESET_N           MCU_GPIO(IOAL_GPIO_PIN_166)  ///< Ethernet reset gpio mapping
#define PS_SSD_HEAT_ENABLE    MCU_GPIO(IOAL_GPIO_PIN_157) ///< PS SSD heat enable gpio mapping


#define SPI_RST               MCU_GPIO(IOAL_GPIO_PIN_149)   ///< Reset pin for SPI interface
#define SPI_UART_CONV_INTRPT  MCU_GPIO(IOAL_GPIO_PIN_150)   ///< SPI to UART converter interrupt pin

#define EPS_ALERT_INTR        MCU_GPIO(IOAL_GPIO_PIN_119)   ///< EPS alert interrupt pin

#define UART_SW_EN_1             MCP23008_OBC_1_GPIO(GPIO_EXP_GPIO_0)  ///< Enable UART switch 1
#define UART_SW_SEL_1            MCP23008_OBC_1_GPIO(GPIO_EXP_GPIO_1)  ///< Select UART switch 1
#define UART_SW_EN_2             MCP23008_OBC_1_GPIO(GPIO_EXP_GPIO_2)  ///< Enable UART switch 2
#define UART_SW_SEL_2            MCP23008_OBC_1_GPIO(GPIO_EXP_GPIO_3)  ///< Select UART switch 2
#define ETH_RESET                MCP23008_OBC_1_GPIO(GPIO_EXP_GPIO_4)  ///< Ethernet reset pin
#define GPS_CORE_PGOOD           MCP23008_OBC_1_GPIO(GPIO_EXP_GPIO_5)  ///< GPS core power good pin
#define GPS_ON_CORE              MCP23008_OBC_1_GPIO(GPIO_EXP_GPIO_6)  ///< GPS on-core pin
#define GPS_NRESET_IN            MCP23008_OBC_1_GPIO(GPIO_EXP_GPIO_7)  ///< GPS nRESET input pin

#define ETH_DCDC1_ON             MCP23008_OBC_2_GPIO(GPIO_EXP_GPIO_0)  ///< Ethernet DCDC1 enable pin
#define ETH_DCDC2_ON             MCP23008_OBC_2_GPIO(GPIO_EXP_GPIO_1)  ///< Ethernet DCDC2 enable pin
#define OBC_DVDDL_PG             MCP23008_OBC_2_GPIO(GPIO_EXP_GPIO_2)  ///< OBC DVDDL power good pin
#define OBC_DVDDIO_PG            MCP23008_OBC_2_GPIO(GPIO_EXP_GPIO_3)  ///< OBC DVDDIO power good pin
#define PAYLOAD_VCC_ENABLE       MCP23008_OBC_2_GPIO(GPIO_EXP_GPIO_4)  ///< Payload VCC enable pin
#define PAYLOAD_SB_ENABLE        MCP23008_OBC_2_GPIO(GPIO_EXP_GPIO_5)  ///< Payload SB enable pin
#define PAYLOAD_SSD_CORE_ENABLE  MCP23008_OBC_2_GPIO(GPIO_EXP_GPIO_6)  ///< Payload SSD core enable pin
#define SBAND_BB_EN              MCP23008_OBC_2_GPIO(GPIO_EXP_GPIO_7)  ///< S-Band baseband enable pin

#define PS_DVDDL_PG           PCAL6408A_PS_GPIO(GPIO_EXP_GPIO_0)   ///< Payload server DVDDL power good pin
#define PS_PCIE_EW3           PCAL6408A_PS_GPIO(GPIO_EXP_GPIO_1)   ///< Payload server PCIe EW3 pin
#define PS_SSD_EN1            PCAL6408A_PS_GPIO(GPIO_EXP_GPIO_2)   ///< Payload server SSD enable 1 pin
#define PS_SSD_EN2            PCAL6408A_PS_GPIO(GPIO_EXP_GPIO_3)   ///< Payload server SSD enable 2 pin
#define PS_DVDDIO_PG          PCAL6408A_PS_GPIO(GPIO_EXP_GPIO_4)   ///< Payload server DVDDIO power good pin
#define PS_ETH_DCDC2_ON       PCAL6408A_PS_GPIO(GPIO_EXP_GPIO_5)   ///< Payload server Ethernet DCDC2 enable pin
#define PS_ETH_RESET          PCAL6408A_PS_GPIO(GPIO_EXP_GPIO_6)   ///< Payload server Ethernet reset pin
#define PS_ETH_DCDC1_ON       PCAL6408A_PS_GPIO(GPIO_EXP_GPIO_7)   ///< Payload server Ethernet DCDC1 enable pin

#define EDGE_SSD_EN1          MCP23008_EDGE_1_GPIO(GPIO_EXP_GPIO_0) ///< EDGE SSD enable 1 pin
#define EDGE_SSD_EN2          MCP23008_EDGE_1_GPIO(GPIO_EXP_GPIO_1) ///< EDGE SSD enable 2 pin
#define EDGE_UART_SW_EN_1     MCP23008_EDGE_1_GPIO(GPIO_EXP_GPIO_2) ///< EDGE UART switch enable 1 pin
#define EDGE_UART_SW_SEL_1    MCP23008_EDGE_1_GPIO(GPIO_EXP_GPIO_3) ///< EDGE UART switch select 1 pin
#define EDGE_SSD_HEAT_ENABLE  MCP23008_EDGE_1_GPIO(GPIO_EXP_GPIO_4) ///< EDGE SSD heat enable pin
#define EDGE_TEM_SEN_INT      MCP23008_EDGE_1_GPIO(GPIO_EXP_GPIO_5) ///< EDGE temperature sensor interrupt pin
#define EDGE_UART_SW_EN_2     MCP23008_EDGE_1_GPIO(GPIO_EXP_GPIO_6) ///< EDGE UART switch enable 2 pin
#define EDGE_UART_SW_SEL_2    MCP23008_EDGE_1_GPIO(GPIO_EXP_GPIO_7) ///< EDGE UART switch select 2 pin

#define EDGE_EN_5V_EDGE       MCP23008_EDGE_2_GPIO(GPIO_EXP_GPIO_0) ///< EDGE 5V enable pin
#define EDGE_IO2_EXPD_INT     MCP23008_EDGE_2_GPIO(GPIO_EXP_GPIO_1) ///< EDGE IO2 expander interrupt pin
#define EDGE_EN_1P8V_EDGE     MCP23008_EDGE_2_GPIO(GPIO_EXP_GPIO_2) ///< EDGE 1.8V enable pin
#define EDGE_EN_3P3V_EDGE_EN  MCP23008_EDGE_2_GPIO(GPIO_EXP_GPIO_3) ///< EDGE 3.3V enable pin
#define EDGE_PGOOD_1P8V_EDGE  MCP23008_EDGE_2_GPIO(GPIO_EXP_GPIO_4) ///< EDGE 1.8V power good pin
#define EDGE_PGOOD_3P3V_EDGE  MCP23008_EDGE_2_GPIO(GPIO_EXP_GPIO_5) ///< EDGE 3.3V power good pin

#define GPS_TEM_SEN_INT       MCP23008_GPS_GPIO(GPIO_EXP_GPIO_0) ///< GPS temperature sensor interrupt pin
#define GPS_HUB_ON            MCP23008_GPS_GPIO(GPIO_EXP_GPIO_1) ///< GPS hub on pin
#define GPS_HUB_PGOOD         MCP23008_GPS_GPIO(GPIO_EXP_GPIO_2) ///< GPS hub power good pin
#define GPS_PGOOD             MCP23008_GPS_GPIO(GPIO_EXP_GPIO_3) ///< GPS power good pin
#define GPS2_IO_EXPD_INT      MCP23008_GPS_GPIO(GPIO_EXP_GPIO_4) ///< GPS IO expander 2 interrupt pin
#define GPS_TRANS_WFDOUT      MCP23008_GPS_GPIO(GPIO_EXP_GPIO_5) ///< GPS transceiver waveform data output pin
#define GPS_FDTI_RESETN       MCP23008_GPS_GPIO(GPIO_EXP_GPIO_6) ///< GPS FTDI reset pin
#define GPS_ON                MCP23008_GPS_GPIO(GPIO_EXP_GPIO_7) ///< GPS on pin


//Address for EPS interface

#define EPS_CONV_BRD_ADDR     (0x55 <<1)    ///< EPS Converter Board Address
#define EPS_OP_CH_BRD_ADDR    (0x56 <<1)    ///< EPS Operational Channel Board Address

#define GPS_EN_SLV_ADDR             0x4E     ///< GPS Board Slave Address
#define GPS_BRD_EN_GPIO_PINS        0x20     ///< GPS Board GPIO Pin mask

#define PLD_SRVR_EN_SLV_ADDR        0x42     ///< Payload Server Board slave address
#define PLD_SRVR_EN_GPIO_PINS       0xEC     ///< Payload Server Board GPIO Pin mask

#define EDGE_BRD_U14_EN_SLV_ADDR    0x46     ///< EDGE Board U14 slave address
#define EDGE_BRD_U16_EN_SLV_ADDR    0x42     ///< EDGE Board U16 slave address
#define EDGE_BRD_EN_GPIO_PIN0       0x01     ///< EDGE Board GPIO Pin 0 mask
#define EDGE_BRD_EN_GPIO_PIN1       0x04     ///< EDGE Board GPIO Pin 1 mask
#define EDGE_BRD_EN_GPIO_PIN3       0x08     ///< EDGE Board GPIO Pin 3 mask
#define EDGE_BRD_EN_GPIO_PINS       (EDGE_BRD_EN_GPIO_PIN0|EDGE_BRD_EN_GPIO_PIN1|EDGE_BRD_EN_GPIO_PIN3) ///< EDGE Board GPIO Pin mask


#endif /* DRIVERS_BSP_JANUS2_STM32F7XX_PIN_MAP_H_ */

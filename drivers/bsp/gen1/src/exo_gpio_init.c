/**
 * @file exo_gpio_init.c
 *
 * @brief This file contains declaration of API's,enumerations,structure
 *  definition and macros of GPIO expander MCP23008
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

#include "exo_io_al_gpio_common.h"
#include "exo_gpio.h"
#include "exo_osal.h"
#include "exo_common.h"

#ifndef __weak
#define __weak   __attribute__((weak))
#endif

#ifndef EXO_UNUSED
#define EXO_UNUSED(X) (void)X
#endif

/**
 * @brief This API handles the interrupt for core IO2 expander.
 */
__weak void core_io2_expd_int(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief This API handles the interrupt for EDGE GPX1 GPIO.
 */
__weak void edge_gpx1_int(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief This API handles the interrupt for EDGE GPX2 GPIO.
 */
__weak void edge_gpx2_int(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief This API handles the interrupt for core IO1 expander.
 */
__weak void core_io1_expd_int(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for GPS IO expander interrupt.
 */
__weak void gps_io_expd_int(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for SPI to UART converter interrupt.
 */
__weak void spi_uart_conv_int(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for PS DVDDL power good interrupt.
 */
__weak void ps_dvddl_pgd_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for PS DVDDIO power good interrupt.
 */
__weak void ps_dvddio_pgd_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for OBC DVDDIO power good interrupt.
 */
__weak void obc_dvddio_pgd_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for OBC DVDDL power good interrupt.
 */
__weak void obc_dvddl_pgd_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for EDGE 1.8V power good interrupt.
 */
__weak void edge_1p8v_pgd_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for EDGE 3.3V power good interrupt.
 */
__weak void edge_3p3v_pgd_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for GPS hub power good interrupt.
 */
__weak void gps_hub_pgd_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for GPS power good interrupt.
 */
__weak void gps_pgd_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for GPS core power good interrupt.
 */
__weak void gps_core_pgd_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for OBC temperature sensor interrupt.
 */
__weak void obc_temp_sns_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Callback for EPS alert.
 */
__weak void eps_alert_cb(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for PS temperature sensor interrupt.
 */
__weak void ps_temp_sns_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for EDGE temperature sensor interrupt.
 */
__weak void edge_temp_sns_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for GPS temperature sensor interrupt.
 */
__weak void gps_temp_sns_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for OBC power sensor interrupt.
 */
__weak void obc_pwr_sns_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief Interrupt service routine for PS power sensor interrupt.
 */
__weak void ps_pwr_sns_isr(void* args)
{
    EXO_UNUSED(args);
}

/**
 * @brief This API initialize the payload server gpio's
 */
void payload_server_gpio_init()
{
    ioal_gpio_config ioal_gpio_cfg;

    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = PS_SSD_EN2;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = PS_DVDDL_PG;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_RISING_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =ps_dvddl_pgd_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = PS_PCIE_EW3;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_INPUT;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = PS_DVDDIO_PG;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_RISING_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =ps_dvddio_pgd_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = PS_CURRENT_SENSE_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =ps_pwr_sns_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = PS_TEMP_SENSE_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =ps_temp_sns_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = PAYLOAD_SSD_CORE_ENABLE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = PAYLOAD_VCC_ENABLE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_INPUT;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = PAYLOAD_SB_ENABLE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_INPUT;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);
}

void obc_gpio_init()
{
    ioal_gpio_config ioal_gpio_cfg;
    ioal_gpio_cfg.pin_number = ETH_RESET_N;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    ioal_gpio_cfg.speed = IOAL_GPIO_SPEED_FREQ_LOW;
    io_hal_gpio_init(&ioal_gpio_cfg);
    io_hal_gpio_writepin(ETH_RESET_N,IOAL_GPIO_PIN_SET);

    io_hal_gpio_writepin(PS_SSD_HEAT_ENABLE,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = PS_SSD_HEAT_ENABLE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);
    io_hal_gpio_writepin(PS_SSD_HEAT_ENABLE,IOAL_GPIO_PIN_RESET);

    ioal_gpio_cfg.pin_number = SPI_UART_CONV_INTRPT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =spi_uart_conv_int;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(SPI1_NSS,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = SPI1_NSS;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(SPI_RST,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = SPI_RST;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = SHUTDOWN_REQ;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_INPUT;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = POWER_EN;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_INPUT;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = SUS_S3_CORE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_INPUT;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = CORE_IO2_EXPD_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =core_io2_expd_int;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = CORE_CURRENT_SENSE_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =obc_pwr_sns_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = CORE_TEMP_SENSE_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =obc_temp_sns_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_IO_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =edge_gpx1_int;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS_IO_EXPD_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =gps_io_expd_int;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(UART_SW_SEL_1,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = UART_SW_SEL_1;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(UART_SW_SEL_2,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = UART_SW_SEL_2;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(UART_SW_EN_1,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = UART_SW_EN_1;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(UART_SW_EN_2,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = UART_SW_EN_2;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(ETH_RESET,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = ETH_RESET;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS_CORE_PGOOD;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_RISING_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =gps_core_pgd_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(GPS_ON_CORE,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = GPS_ON_CORE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS_NRESET_IN;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);
    io_hal_gpio_writepin(GPS_NRESET_IN,IOAL_GPIO_PIN_SET);

    io_hal_gpio_writepin(ETH_DCDC1_ON,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = ETH_DCDC1_ON;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(ETH_DCDC2_ON,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = ETH_DCDC2_ON;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = OBC_DVDDL_PG;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_RISING_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =obc_dvddl_pgd_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = OBC_DVDDIO_PG;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_RISING_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =obc_dvddio_pgd_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(SBAND_BB_EN,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = SBAND_BB_EN;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(PS_ETH_DCDC2_ON,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = PS_ETH_DCDC2_ON;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(PS_ETH_RESET,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = PS_ETH_RESET;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    io_hal_gpio_writepin(PS_ETH_DCDC1_ON,IOAL_GPIO_PIN_RESET);
    ioal_gpio_cfg.pin_number = PS_ETH_DCDC1_ON;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EPS_ALERT_INTR;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_PULLUP;
    ioal_gpio_cfg.external_int.isr_handler =eps_alert_cb;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

}

/**
 * @brief This API initialize the EDGE server gpio's
 */
void edge_server_gpio_init()
{
    ioal_gpio_config ioal_gpio_cfg;

    ioal_gpio_cfg.pin_number = EDGE_SSD_EN1;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_SSD_EN2;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_UART_SW_EN_1;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_UART_SW_SEL_1;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_SSD_HEAT_ENABLE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_TEM_SEN_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =edge_temp_sns_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_UART_SW_EN_2;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_UART_SW_SEL_2;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_EN_5V_EDGE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_IO2_EXPD_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =edge_gpx2_int;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_EN_1P8V_EDGE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_EN_3P3V_EDGE_EN;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_PGOOD_1P8V_EDGE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_RISING_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =edge_1p8v_pgd_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number =EDGE_PGOOD_3P3V_EDGE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_RISING_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =edge_3p3v_pgd_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);


}

/**
 * @brief This API initialize the GPS GPIO
 */
void gps_gpio_init()
{
    ioal_gpio_config ioal_gpio_cfg;

    ioal_gpio_cfg.pin_number = GPS_TEM_SEN_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =gps_temp_sns_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS_HUB_ON;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS_HUB_PGOOD;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_RISING_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =gps_hub_pgd_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS_PGOOD;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_RISING_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =gps_pgd_isr;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS2_IO_EXPD_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS_TRANS_WFDOUT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS_FDTI_RESETN;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS_ON_CORE;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = GPS_ON;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_OUTPUT_PP;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);
}

/**
 * @brief This API De-initialize the PS interface
 */
void ps_intr_deinit()
{
    ioal_gpio_config ioal_gpio_cfg;
    ioal_gpio_cfg.pin_number = PS_CURRENT_SENSE_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_INPUT;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler = NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = PS_TEMP_SENSE_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_INPUT;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler = NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);
}

/**
 * @brief This API De-initialize the EDGE interface
 */
void edge_intr_deinit()
{
    ioal_gpio_config ioal_gpio_cfg;
    ioal_gpio_cfg.pin_number = EDGE_IO2_EXPD_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_INPUT;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

    ioal_gpio_cfg.pin_number = EDGE_TEM_SEN_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler = NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);
}

/**
 * @brief This API De-initialize the GPS interface
 */
void gps_intr_deinit()
{
    ioal_gpio_config ioal_gpio_cfg;
    ioal_gpio_cfg.pin_number = GPS_TEM_SEN_INT;
    ioal_gpio_cfg.mode = IOAL_GPIO_MODE_IT_FALLING;
    ioal_gpio_cfg.pull_sts = IOAL_GPIO_NOPULL;
    ioal_gpio_cfg.external_int.isr_handler =NULL;
    ioal_gpio_cfg.external_int.isr_args = NULL;
    io_hal_gpio_init(&ioal_gpio_cfg);

}

/**
 * @brief This API enable the OBC Ethernet for communication
 */
void obc_ethernet_enable()
{
    io_hal_gpio_writepin(ETH_RESET,IOAL_GPIO_PIN_RESET);
    os_delay(50);
    io_hal_gpio_writepin(ETH_DCDC1_ON,IOAL_GPIO_PIN_SET);
    io_hal_gpio_writepin(ETH_DCDC2_ON,IOAL_GPIO_PIN_SET);
    io_hal_gpio_writepin(SBAND_BB_EN,IOAL_GPIO_PIN_SET);

    io_hal_gpio_writepin(UART_SW_EN_2,IOAL_GPIO_PIN_RESET);
    io_hal_gpio_writepin(UART_SW_SEL_2,IOAL_GPIO_PIN_SET);
    io_hal_gpio_writepin(GPS_ON_CORE,IOAL_GPIO_PIN_SET);

    os_delay(100);
    io_hal_gpio_writepin(ETH_RESET,IOAL_GPIO_PIN_SET);
}

/**
 * @brief This API enable the payload server ethernet
 */
void ps_ethernet_enable()
{
    io_hal_gpio_writepin(PS_ETH_DCDC1_ON,IOAL_GPIO_PIN_SET);
    io_hal_gpio_writepin(PS_ETH_DCDC2_ON,IOAL_GPIO_PIN_SET);
    os_delay(300);
    io_hal_gpio_writepin(PS_ETH_RESET,IOAL_GPIO_PIN_SET);
}

/**
 * @brief This API initialize the BSP funtionality's
 */
void bsp_init()
{
    obc_gpio_init();
    obc_ethernet_enable();
    ps_ethernet_enable();
    os_delay(700);
}


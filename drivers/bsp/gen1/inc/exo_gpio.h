/**
 * @file exo_gpio.h
 *
 * @brief This file contains GPIO functionality prototypes.
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

#ifndef EXO_GPIO_H
#define EXO_GPIO_H

/*Includes --------------------------------------------------------------*/
#include "exo_pinmap.h"

/**
 * @brief This API handles the interrupt for core IO2 expander.
 *
 * @param[in] args Dummy argument (unused).
 */
void core_io2_expd_int(void* args);

/**
 * @brief This API handles the interrupt for EDGE GPX1 GPIO.
 *
 * @param[in] args Dummy argument (unused).
 */
void edge_gpx1_int(void* args);

/**
 * @brief This API handles the interrupt for EDGE GPX2 GPIO.
 *
 * @param[in] args Dummy argument (unused).
 */
void edge_gpx2_int(void* args);

/**
 * @brief This API handles the interrupt for core IO1 expander.
 *
 * @param[in] args Dummy argument (unused).
 */
void core_io1_expd_int(void* args);

/**
 * @brief This API handles the interrupt for GPS IO expander.
 *
 * @param[in] args Dummy argument (unused).
 */
void gps_io_expd_int(void* args);

/**
 * @brief This API handles the interrupt for SPI to UART conversion.
 *
 * @param[in] args Dummy argument (unused).
 */
void spi_uart_conv_int(void* args);

/**
 * @brief This API handles the PS DVDDL power good interrupt.
 *
 * @param[in] args Dummy argument (unused).
 */
void ps_dvddl_pgd_isr(void* args);

/**
 * @brief This API handles the PS DVDDIO power good interrupt.
 *
 * @param[in] args Dummy argument (unused).
 */
void ps_dvddio_pgd_isr(void* args);

/**
 * @brief This API handles the OBC DVDDIO power good interrupt.
 *
 * @param[in] args Dummy argument (unused).
 */
void obc_dvddio_pgd_isr(void* args);

/**
 * @brief This API handles the OBC DVDDL power good interrupt.
 *
 * @param[in] args Dummy argument (unused).
 */
void obc_dvddl_pgd_isr(void* args);

/**
 * @brief This API handles the EDGE 1.8V power good interrupt.
 *
 * @param[in] args Dummy argument (unused).
 */
void edge_1p8v_pgd_isr(void* args);

/**
 * @brief This API handles the EDGE 3.3V power good interrupt.
 *
 * @param[in] args Dummy argument (unused).
 */
void edge_3p3v_pgd_isr(void* args);

/**
 * @brief This API handles the GPS hub power good interrupt.
 *
 * @param[in] args Dummy argument (unused).
 */
void gps_hub_pgd_isr(void* args);

/**
 * @brief This API handles the GPS power good interrupt.
 *
 * @param[in] args Dummy argument (unused).
 */
void gps_pgd_isr(void* args);

/**
 * @brief This API handles the GPS core power good interrupt.
 *
 * @param[in] args Dummy argument (unused).
 */
void gps_core_pgd_isr(void* args);

/**
 * @brief This API handles the interrupt for the OBC temperature sensor.
 *
 * @param[in] args Dummy argument (unused).
 */
void obc_temp_sns_isr(void* args);

/**
 * @brief This API handles the interrupt for the PS temperature sensor.
 *
 * @param[in] args Dummy argument (unused).
 */
void ps_temp_sns_isr(void* args);

/**
 * @brief This API handles the interrupt for the EDGE temperature sensor.
 *
 * @param[in] args Dummy argument (unused).
 */
void edge_temp_sns_isr(void* args);

/**
 * @brief This API handles the interrupt for the GPS temperature sensor.
 *
 * @param[in] args Dummy argument (unused).
 */
void gps_temp_sns_isr(void* args);

/**
 * @brief This API handles the interrupt for the OBC power sensor.
 *
 * @param[in] args Dummy argument (unused).
 */
void obc_pwr_sns_isr(void* args);

/**
 * @brief This API handles the interrupt for the PS power sensor.
 *
 * @param[in] args Dummy argument (unused).
 */
void ps_pwr_sns_isr(void* args);

/**
 * @brief This API handles the EPS alert callback.
 *
 * @param[in] args Dummy argument (unused).
 */
void eps_alert_cb(void* args);

/**
 * @brief This API initializes the core IO expander and other peripherals.
 */
void bsp_init();

/**
 * @brief This API initializes the GPIO pins for OBC.
 */
void obc_gpio_init();

/**
 * @brief This API initializes the GPIO pins for the payload server.
 */
void payload_server_gpio_init();

/**
 * @brief This API initializes the GPIO pins for the EDGE server.
 */
void edge_server_gpio_init();

/**
 * @brief This API initializes the GPIO pins for GPS.
 */
void gps_gpio_init();

/**
 * @brief This API disables and deinitializes the PS interrupt handlers.
 */
void ps_intr_deinit();

/**
 * @brief This API disables and deinitializes the EDGE interrupt handlers.
 */
void edge_intr_deinit();

/**
 * @brief This API disables and deinitializes the GPS interrupt handlers.
 */
void gps_intr_deinit();

#endif

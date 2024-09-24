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

#include "exo_pinmap.h"


/**
 * @brief Initializes the EXO GPIO pins.
 *
 * This API configures and initializes all the required GPIO pins for the EXO system.
 */
void exo_gpio_init();

/**
 * @brief Initializes the Board Support Package (BSP).
 *
 * This API sets up and initializes the core peripherals and devices required for the system operation.
 */
void bsp_init();

/**
 * @brief Interrupt service routine for core current sensing.
 *
 * This API handles the interrupt related to core current sensing.
 *
 * @param[in] args Dummy argument (unused).
 */
void core_current_sense_int(void* args);

/**
 * @brief Interrupt service routine for core IO2 expander.
 *
 * This API handles the interrupt for core IO2 expander.
 *
 * @param[in] args Dummy argument (unused).
 */
void core_io2_expd_int(void* args);

/**
 * @brief Interrupt service routine for EDGE IO.
 *
 * This API handles the interrupt for EDGE IO.
 *
 * @param[in] args Dummy argument (unused).
 */
void edge_io_int(void* args);

/**
 * @brief Interrupt service routine for core IO1 expander.
 *
 * This API handles the interrupt for core IO1 expander.
 *
 * @param[in] args Dummy argument (unused).
 */
void core_io1_expd_int(void* args);

/**
 * @brief Interrupt service routine for core temperature sensor.
 *
 * This API handles the interrupt for the core temperature sensor.
 *
 * @param[in] args Dummy argument (unused).
 */
void core_tem_sen_int(void* args);

/**
 * @brief Interrupt service routine for GPS IO expander.
 *
 * This API handles the interrupt for GPS IO expander.
 *
 * @param[in] args Dummy argument (unused).
 */
void gps_io_expd_int(void* args);

/**
 * @brief Interrupt service routine for SPI to UART converter.
 *
 * This API handles the interrupt for SPI to UART conversion.
 *
 * @param[in] args Dummy argument (unused).
 */
void spi_uart_conv_int(void* args);

/**
 * @brief Initializes the GPIO pins for OBC (On-Board Computer).
 *
 * This API configures and initializes the GPIO pins required for the OBC.
 */
void obc_gpio_init();

/**
 * @brief Initializes the GPIO pins for the payload server.
 *
 * This API configures and initializes the GPIO pins required for the payload server.
 */
void payload_server_gpio_init();

/**
 * @brief Initializes the GPIO pins for the EDGE server.
 *
 * This API configures and initializes the GPIO pins required for the EDGE server.
 */
void edge_server_gpio_init();

/**
 * @brief Initializes the GPIO pins for GPS.
 *
 * This API configures and initializes the GPIO pins required for GPS functionality.
 */
void gps_gpio_init();

#endif /* EXO_GPIO_H */

/**
 * @file exo_io_al_wrapper.h
 *
 * @brief This file contains IO header mapping for different MCU.
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


#ifndef _IO_AL_WRAPPER_H_
#define _IO_AL_WRAPPER_H_

#ifdef STM32F765xx
#include "exo_io_al_stm32f7xx_i2c.h"
#include "exo_io_al_stm32f7xx_can.h"
#include "exo_io_al_stm32f7xx_spi.h"
#include "exo_io_al_stm32f7xx_uart.h"
#include "exo_io_al_stm32f7xx_usb.h"
#else
#ifdef  STM32F769xx
#include "exo_io_al_stm32f7xx_i2c.h"
#include "exo_io_al_stm32f7xx_can.h"
#include "exo_io_al_stm32f7xx_spi.h"
#include "exo_io_al_stm32f7xx_uart.h"
#include "exo_io_al_stm32f7xx_usb.h"

#endif
#endif

#ifdef LINUX_TEMP_PORT
#include "exo_io_al_linux.h"
#endif

#endif /* _IO_AL_WRAPPER_H_ */

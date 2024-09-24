/**
 * @file exo_io_al_stm32f7xx_common.h
 *
 * @brief This file contains function declaration to get the IO-AL instance
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

#ifndef _IO_AL_STM32F7XX_COMMON_H_
#define _IO_AL_STM32F7XX_COMMON_H_

#include "exo_hal_common.h"
#include "exo_io_al_common.h"

/**
 * @brief This function get the IO-AL instance from VDP instance
 * @param[in] vdp_io_inst_hdle - pointer to VDP instance
 * @param[in] io_hal_inst_hdle - pointer to IO-AL instance
 * @retval HAL status
 */
hal_ret_sts get_ioal_inst_from_vd_inst(void *vdp_io_inst_hdle, void** io_hal_inst_hdle);

#endif /* _IO_AL_STM32F7XX_COMMON_H_ */

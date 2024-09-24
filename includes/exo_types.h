/**
 * @file exo_types.h
 *
 * @brief This file contains datatype defintions and macros for storage memory.
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
 *
 */
#ifndef _EXO_TYPES_H_
#define _EXO_TYPES_H_

#ifdef LINUX_TEMP_PORT
#include <stdint.h>
#endif

#if defined(COREBOARD) || defined(STM32F769xx)

#define PLACE_IN_SDRAM_NVM     __attribute__((aligned(4))) __attribute__ ((section (".e_sdram_nvm_temp")))

#define PLACE_IN_SDRAM_MEM     __attribute__((aligned(4))) __attribute__ ((section (".e_sdram_mem")))

#define PLACE_IN_SDRAM_FTP     __attribute__((aligned(4))) __attribute__ ((section (".e_sdram_ftp_temp_mem")))

#define PLACE_IN_SDRAM_LOG     __attribute__((aligned(4))) __attribute__ ((section (".e_sdram_logger_mem")))

#define PLACE_IN_SDRAM_TC_STRG __attribute__((aligned(4))) __attribute__ ((section (".e_sdram_tc_strg_mem")))

#define PLACE_IN_FIXED_DATA __attribute__((aligned(4))) __attribute__ ((section (".fixed_data")))


#else

#define PLACE_IN_SDRAM_NVM  

#define PLACE_IN_SDRAM_MEM	

#define PLACE_IN_SDRAM_FTP	

#define PLACE_IN_SDRAM_LOG

#define PLACE_IN_SDRAM_TC_STRG

#define PLACE_IN_FIXED_DATA

#endif
typedef unsigned int uint32;
//typedef unsigned int uint32_t; 
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef int int32;
typedef short int16;
typedef char int8;

#endif

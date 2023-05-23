/**
 * @file exo_osal_mem_cpy.h
 *
 * @brief This file contains enumeration, stucture and function prototypes
 *        for different memory.
 *
 *  @copyright Copyright 2023 Antaris, Inc.
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

#ifndef OSAL_MEM_CPY_H_
#define OSAL_MEM_CPY_H_

/* enable it when it is compiled in exo_sat_bus_btlr software
 * it should be disabled in exo_sat_bus_ctrl software
 */
#define BOOTLOADER_STD_SFT

/**
 * @brief Memory copy status code enumeration
 */
typedef enum
{
    CPY_OK,       /*!<Copy sucess*/
    CPY_ERR,      /*!<Copy error*/
    VALID_ADDR,   /*!<Correct address*/
    INVLD_ADDR    /*!<Incorrect address*/
}cpy_sts;

/**
 * @brief Memory type enumeration
 */
typedef enum
{
    I_RAM,         /*!<Internal ram memory*/
    E_RAM,         /*!<External ram memory*/
    E_QSPI_FLASH,  /*!<External QSPI flash memory*/
    E_FMC_FLASH,   /*!<External FMC flash memory*/
    MAX_MEM        /*!<Maximum memory*/
}memory_types;

//Read function pointer
typedef uint8_t (*read_api)(uint8_t* src,uint8_t* dst,int len);
//Write function pointer
typedef uint8_t (*write_api)(uint8_t*src,uint8_t* dst,int len,uint8_t erase_flag);
//Memory copy complete function pointer
typedef void (*mem_cpy_cmptl_cb)(uint8_t sts);

/**
 * @brief Memory information structure
 */
typedef struct
{
    uint8_t* src_addr;              /*!<Source address*/
    uint8_t* dst_addr;              /*!<Destination address*/
    uint32_t len;                   /*!<Length memory*/
    uint8_t src_mem_type;           /*!<Source memory type*/
    uint8_t dst_mem_type;           /*!<Destination memory type*/
    uint8_t erase_flag;             /*!< 1- perform sector erase, 0- No sector erase*/
    uint8_t rsvd;                   /*!<check reserved or unreserved memory*/
    mem_cpy_cmptl_cb call_back_fun; /*!<Memory callback*/
}obc_memcpy_info;

/**
 * @brief Onboard memory copy layout in structure
 */
typedef struct
{
    uint8_t* start_addr;     /*!<start address*/
    uint32_t len_bytes;      /*!<length in bytes*/
    uint8_t* end_addr;       /*!<End address*/
    read_api read_fun;       /*!<Read function pointer*/
    write_api write_fun;     /*!<Write function pointer*/
}__attribute__ ((packed))obc_memcpy_memory_layout;

/**
 * @brief Memory copy thread entry function.
 *
 * @param[in]  args : pointer to argument
 */
void memcpy_event_thread(void* args);

/**
 * @brief This API write data to External NOR flash memory.
 *
 * @param[in]  write_addr : pointer to write address
 * @param[in]  data : pointer to data
 * @param[in]  len : Length of data in bytes
 * @param[in]  erase_flag : Erase flag
 *
 * @return status of write
 */
uint8_t write_to_e_norfmc(uint8_t* write_addr,uint8_t* data,int len, uint8_t erase_flag);

/**
 * @brief This API write data to External QSPI memory
 *
 * @param[in]  write_addr : pointer to write address
 * @param[in]  data : pointer to data
 * @param[in]  len : Length of data in bytes
 * @param[in]  erase_flag : Erase flag
 *
 * @return status of write
 */
uint8_t write_to_e_qspi(uint8_t* write_addr,uint8_t* data,int len, uint8_t erase_flag);

/**
 * @brief This API write data to internal flash memory
 *
 * @param[in]  write_addr : pointer to write address
 * @param[in]  data : pointer to data
 * @param[in]  len : Length of data in bytes
 * @param[in]  erase_flag : Erase flag
 *
 * @return status of write
 */
uint8_t write_to_iflash(uint8_t* write_addr,uint8_t* data,int len, uint8_t erase_flag);

/**
 * @brief This API write data to RAM.
 *
 * @param[in]  write_addr : pointer to write address
 * @param[in]  data : pointer to data
 * @param[in]  len : Length of data in bytes
 * @param[in]  erase_flag : Erase flag
 *
 * @return status of write
 * @retval CPY_OK->success
 */
uint8_t write_to_ram(uint8_t* write_addr,uint8_t* data,int len, uint8_t erase_flag);

/**
 * @brief This API read data from RAM.
 *
 * @param[in]  read_addr : pointer to read address
 * @param[in]  data : pointer to data
 * @param[in]  len : Length of data in bytes
 *
 * @return status of read
 * @retval CPY_OK->success
 */
uint8_t read_from_ram(uint8_t* read_addr,uint8_t* data,int len);

/**
 * @brief This API read data from internal flash.
 *
 * @param[in]  read_addr : pointer to read address
 * @param[in]  data : pointer to data
 * @param[in]  len : Length of data in bytes
 *
 * @return status of read
 * @retval CPY_OK->success
 */
uint8_t read_from_iflash(uint8_t* read_addr,uint8_t* data,int len);

/**
 * @brief This API read data from external NOR flash
 *
 * @param[in]  read_addr : pointer to read address
 * @param[in]  data : pointer to data
 * @param[in]  len : Length of data in bytes
 *
 * @return status of read
 */
uint8_t read_from_e_norfmc(uint8_t* read_addr,uint8_t* data,int len);

/**
 * @brief This API read data from external QSPI.
 *
 * @param[in]  read_addr : pointer to read address
 * @param[in]  data : pointer to data
 * @param[in]  len : Length of data in bytes
 *
 * @return status of read
 */
uint8_t read_from_e_qspi(uint8_t* read_addr,uint8_t* data,int len);

/**
 * @brief wrapper API to copy the block of memory.
 *
 *  Length cannot be greater than 1 MB
 *
 * @param[in]  dst_addr : Destination address
 * @param[in]  src_addr : source address
 * @param[in]  len : Length of data in bytes
 * @param[in]  cf_fun : callback function
 * @param[in]  imemdiate_flag : Immediate flag
 * @param[in]  erase_flag : Memory erase flag
 *
 * @return status of memory copy
 *
 * @retval CPY_OK->successfully copied, CPY_ERR->error
 */
cpy_sts obc_memcpy_wrapper(uint8_t* dst_addr,uint8_t* src_addr,uint32_t len,
        mem_cpy_cmptl_cb cb_fun,uint8_t imemdiate_flag,uint8_t erase_flag);

/**
 * @brief This API compare both source and destination address and update
 *        the memory type info.
 *
 * @param[in]  obc_cpy_info : pointer to memcpy handle.
 *
 * @return status of memory copy
 *
 * @retval cpy_ok->successfully copied
 */
uint8_t mem_cpy_fun_def(obc_memcpy_info *obc_cpy_info);

/**
 * @brief This API initialize the memory copy framework.
 *
 * @param[in]  nor_hdl : pointer to NOR flash handle
 * @param[in]  qspi_hdl : pointer to QSPI handle
 */
void os_memcpy_fw_init(void *nor_hdl,void* qspi_hdl);

/**
 * @brief This API erase the flash sector for given length.
 *
 * @param[in] write_addr : pointer to write address
 * @param[in] len : length of the write address
 * @param[in] flash_type : Type of flash memory
 */
void flash_sector_erase_by_add_n_len(uint8_t* write_addr,int len,int8_t flash_type);

/**
 * @brief This API test the external memory.
 *
 * @param[in]  mem_type : External memory type
 *
 * @return status of memory test
 */
uint8_t extrnl_memory_test(uint8_t mem_type);

#endif /*OSAL_MEM_CPY_H_*/

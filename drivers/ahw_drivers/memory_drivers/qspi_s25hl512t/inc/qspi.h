/**
 * @file qspi.h
 *
 *  @brief This file contains the macros,structure declaration,enumeration,
 *  function declaration for memory management through QSPI
 *
 *	@copyright Copyright 2024 Antaris, Inc.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __QSPI_MEM_DRIVER_H
#define __QSPI_MEM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

    /* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal_ext.h"
#include "s25fl512s.h"

    /* QSPI Error codes */
#define QSPI_OK            ((uint8_t)0x00)          ///< QSPI success
#define QSPI_ERROR         ((uint8_t)0x01)			///< QSPI error
#define QSPI_BUSY          ((uint8_t)0x02)			///< QSPI busy
#define QSPI_NOT_SUPPORTED ((uint8_t)0x04)			///< QSPI not supported
#define QSPI_SUSPENDED     ((uint8_t)0x08)			///< QSPI suspended
#define QSPI_PROTECTED     ((uint8_t)0x10)			///< QSPI protected

#define QSPI_S25HL512T     ((uint8_t)0x2A)			///< QSPI S25HL512T
#define QSPI_N25Q512A      ((uint8_t)0x40)			///< QSPI N25Q512A

    /* Definition for QSPI clock resources */
#define QSPI_CLK_ENABLE()             __HAL_RCC_QSPI_CLK_ENABLE()        ///< QSPI clock enable
#define QSPI_CLK_DISABLE()            __HAL_RCC_QSPI_CLK_DISABLE()		 ///< QSPI clock disable
#define QSPI_CS_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()		 ///< QSPI cs gpio clock enable
#define QSPI_CS_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOB_CLK_DISABLE()		 ///< QSPI cs gpio clock disable
#define QSPI_DX_CLK_GPIO_CLK_ENABLE() __HAL_RCC_GPIOF_CLK_ENABLE()		 ///< QSPI dx clock gpio clock enable
#define QSPI_DX_CLK_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOF_CLK_DISABLE()	 ///< QSPI dx clock gpio clock disable

#define QSPI_FORCE_RESET()            __HAL_RCC_QSPI_FORCE_RESET()		 	///< QSPI force reset
#define QSPI_RELEASE_RESET()          __HAL_RCC_QSPI_RELEASE_RESET()		///< QSPI release reset

    /**
     * @brief QSPI Info
     */
    typedef struct {
        uint32_t FlashSize;          /*!< Size of the flash                         */
        uint32_t EraseSectorSize;    /*!< Size of sectors for the erase operation   */
        uint32_t EraseSectorsNumber; /*!< Number of sectors for the erase operation */
        uint32_t ProgPageSize;       /*!< Size of pages for the program operation   */
        uint32_t ProgPagesNumber;    /*!< Number of pages for the program operation */
        uint32_t DummyCyclesRead;    /*!< Number of dummy read cycles               */
        uint8_t  ManufID;            /*!< Manufacture value                        */
        uint32_t SectorEraseMaxTime; /*!< Sector Erase max value                    */
        uint32_t BulkEraseMaxTime;   /*!< Bulk Erase Max Time                       */
    } QSPI_InfoTypeDef;

    /**
     * @brief QSPI latency cycle enumeration
     */
    typedef enum
    {
        QSPI_LATENCY_CYCLE_0,			///< QSPI latency cycle 0
        QSPI_LATENCY_CYCLE_1,			///< QSPI latency cycle 1
        QSPI_LATENCY_CYCLE_2,			///< QSPI latency cycle 2
        QSPI_LATENCY_CYCLE_3,			///< QSPI latency cycle 3
        QSPI_LATENCY_CYCLE_4,			///< QSPI latency cycle 4
        QSPI_LATENCY_CYCLE_5,			///< QSPI latency cycle 5
        QSPI_LATENCY_CYCLE_6,			///< QSPI latency cycle 6
        QSPI_LATENCY_CYCLE_7,			///< QSPI latency cycle 7
        QSPI_LATENCY_CYCLE_8,			///< QSPI latency cycle 8
        QSPI_LATENCY_CYCLE_9,			///< QSPI latency cycle 9
        QSPI_LATENCY_CYCLE_10,			///< QSPI latency cycle 10
        QSPI_LATENCY_CYCLE_11,			///< QSPI latency cycle 11
        QSPI_LATENCY_CYCLE_12,			///< QSPI latency cycle 12
        QSPI_LATENCY_CYCLE_13,			///< QSPI latency cycle 13
        QSPI_LATENCY_CYCLE_14,			///< QSPI latency cycle 14
        QSPI_LATENCY_CYCLE_15,			///< QSPI latency cycle 15
        QPSI_LATENCY_CYCLE_MAX

    }e_qspi_latency_cycle;

    /**
     * @brief QSPI transfer protocol type enumeration
     */
    typedef enum
    {
        SIO,
        DIO,
        QOR,
        QIO,
        QPI
    }e_qspi_protocol_type;

    /**
     * @brief QSPI Initialization done in this function
     * @param[in] qspi_hdl - instance pointer of qspi
     * @param[in] qspi_info -  pointer to qspi information structure
     * @retval error status
     */
    uint8_t qspi_init(QSPI_HandleTypeDef *qspi_hdl,QSPI_InfoTypeDef *qspi_info);

    /**
     * @brief This function read the data from memory through qspi
     * @param[in] qspi_hdl - instance pointer of qspi
     * @param[out]pData -  pointer to a buffer
     * @param[in] ReadAddr - address of the data
     * @param[in] Size -  size of the data in bytes
     * @retval error status
     */
    uint8_t qspi_read(QSPI_HandleTypeDef *qspi_hdl,uint8_t* pData, uint32_t ReadAddr, uint32_t Size);

    /**
     * @brief This function write the data in memory through qspi
     * @param[in] qspi_hdl - instance pointer of qspi
     * @param[in] pData -  pointer to a buffer
     * @param[in] ReadAddr - address of the data
     * @param[in] Size -  size of the data in bytes
     * @retval error status
     */
    uint8_t qspi_write(QSPI_HandleTypeDef *qspi_hdl,uint8_t* pData, uint32_t WriteAddr, uint32_t Size);

    /**
     * @brief This function erases the specified block of memory through qspi .
     * @param[in] qspi_hdl - instance pointer of qspi
     * @param[in] BlockAddress - block of address to be erased
     * @retval error status
     */
    uint8_t qspi_erase_block(QSPI_HandleTypeDef *qspi_hdl,uint32_t BlockAddress);

    /**
     * @brief This function erase the entire memory through qspi
     * @param[in] qspi_hdl - instance pointer of qspi
     * @retval error status
     */
    uint8_t qspi_erase_chip(QSPI_HandleTypeDef *qspi_hdl);

    /**
     * @brief This function get the status of memory
     * @param[in] qspi_hdl - instance pointer of qspi
     * @retval error status
     */
    uint8_t qspi_get_status(QSPI_HandleTypeDef *qspi_hdl);

    /**
     * @brief This function configure the qspi to memory-mapped mode
     * @param[in] qspi_hdl - instance pointer of qspi
     * @retval error status
     */
    uint8_t qspi_enable_memorymapped_mode(QSPI_HandleTypeDef *qspi_hdl);

    /**
     * @brief This function reset the memory
     * @param[in] qspi_hdl - instance pointer of qspi
     * @retval error status
     */
    uint8_t qspi_reset_memory(QSPI_HandleTypeDef *qspi_hdl);

    /**
     * @brief This function set the qspi in 4-byte address mode
     * @param[in] qspi_hdl - instance pointer of qspi
     * @retval error status
     */
    uint8_t qspi_enter_fourbytes_address(QSPI_HandleTypeDef *qspi_hdl);

    /**
     * @brief This function send a Write enable command to memory
     * @param[in] qspi_hdl - instance pointer of qspi
     * @retval error status
     */
    uint8_t qspi_write_enable(QSPI_HandleTypeDef *qspi_hdl);

    /**
     * @brief This function configure the QSPI Automatic Polling Mode in blocking mode.
     * @param[in] qspi_hdl - instance pointer of qspi
     * @param[in] timeout - timeout duration
     * @retval error status
     */
    uint8_t qspi_auto_polling_mem_ready(QSPI_HandleTypeDef *hqspi, uint32_t Timeout);

    /**
     * @brief This function read the memory id
     * @param[in] qspi_hdl - instance pointer of qspi
     * @param[out]pqspi_info - Pointer to a QSPI_InfoTypeDef
     * @retval error status
     */
    uint8_t qspi_read_id(QSPI_HandleTypeDef *qspi_hdl,QSPI_InfoTypeDef *pqspi_info);

    /**
     * @brief This function set the qspi transfer protocol type
     * @param[in] qspi_hdl - instance pointer of qspi
     * @param[in] prtcl_type - protocol type
     * @retval error status
     */
    uint8_t qspi_set_protocol_type(QSPI_HandleTypeDef *qspi_hdl, uint8_t prtcl_type);

    /**
     * @brief This function configure the dummy cycles of qspi
     * @param[in] qspi_hdl - instance pointer of qspi
     * @param[in] dummy_cycle - dummy cycle
     * @retval error status
     */
    uint8_t qspi_dummy_cycles_cfg(QSPI_HandleTypeDef *qspi_hdl, e_qspi_latency_cycle dummy_cycle);

#ifdef __cplusplus
}
#endif

#endif

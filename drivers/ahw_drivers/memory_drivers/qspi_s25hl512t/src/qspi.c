/**
 * @file qspi.c
 *
 *  @brief This file contains function definitions of QSPI
 *
 *	@copyright Copyright 2023 Antaris, Inc.
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


#define QSPI_INTF_ENB

#include "qspi.h"

#define JEDEC_MANUF_ID_CYPRESS ((uint8_t) 0x34)

QSPI_HandleTypeDef hqspi;
QSPI_InfoTypeDef QspiInfo;

uint8_t qspi_protocol_type = QPI;

/**
 * @brief QSPI initialization function
 */
uint8_t qspi_init(QSPI_HandleTypeDef *qspi_hdl,QSPI_InfoTypeDef *qspi_info)
{
    (*qspi_hdl).Instance = QUADSPI;
    if (HAL_QSPI_DeInit(qspi_hdl) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    (*qspi_hdl).Init.ClockPrescaler     = 32;
    (*qspi_hdl).Init.FifoThreshold      = 1;
    (*qspi_hdl).Init.SampleShifting     = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
    (*qspi_hdl).Init.FlashSize          = POSITION_VAL(S25HL512T_FLASH_SIZE) - 1;
    (*qspi_hdl).Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_5_CYCLE;
    (*qspi_hdl).Init.ClockMode          = QSPI_CLOCK_MODE_0;
    (*qspi_hdl).Init.FlashID            = QSPI_FLASH_ID_1;
    (*qspi_hdl).Init.DualFlash          = QSPI_DUALFLASH_DISABLE;
    if (HAL_QSPI_Init(qspi_hdl) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (qspi_read_id(qspi_hdl,qspi_info) != QSPI_OK)
    {
        return QSPI_NOT_SUPPORTED;
    }
    if (qspi_set_protocol_type(qspi_hdl, QPI) != QSPI_OK)
    {
        return QSPI_NOT_SUPPORTED;
    }
    return QSPI_OK;
}

/**
 * @brief This API read the data from memory through qspi
 */
uint8_t qspi_read(QSPI_HandleTypeDef *qspi_hdl,uint8_t* pData, uint32_t ReadAddr, uint32_t Size)
{
    QSPI_CommandTypeDef s_command;
    if(qspi_protocol_type==QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
        s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
        s_command.DataMode          = QSPI_DATA_4_LINES;
        s_command.Instruction       =  S25HL512T_QUAD_INOUT_FAST_READ_CMD ;
        s_command.AlternateByteMode  = QSPI_ALTERNATE_BYTES_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
        s_command.DataMode          = QSPI_DATA_1_LINE;
        s_command.Instruction       = S25HL512T_READ_CMD;
        s_command.AlternateByteMode  = QSPI_ALTERNATE_BYTES_1_LINE;
    }
    s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
    s_command.Address           = ReadAddr;
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    s_command.AlternateBytes     = 0x00;

    s_command.DummyCycles       = QspiInfo.DummyCyclesRead;
    s_command.NbData            = Size;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    MODIFY_REG((*qspi_hdl).Instance->DCR, QUADSPI_DCR_CSHT, QSPI_CS_HIGH_TIME_2_CYCLE);
    if (HAL_QSPI_Receive(qspi_hdl, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    MODIFY_REG((*qspi_hdl).Instance->DCR, QUADSPI_DCR_CSHT, QSPI_CS_HIGH_TIME_5_CYCLE);
    return QSPI_OK;
}

/**
 * @brief This API write the data in memory through qspi
 */
uint8_t qspi_write(QSPI_HandleTypeDef *qspi_hdl,uint8_t* pData, uint32_t WriteAddr, uint32_t Size)
{
    QSPI_CommandTypeDef s_command;
    uint32_t end_addr, current_size, current_addr;
    current_size = QspiInfo.ProgPageSize - (WriteAddr % (QspiInfo.ProgPageSize));
    if (current_size > Size)
    {
        current_size = Size;
    }
    current_addr = WriteAddr;
    end_addr = WriteAddr + Size;
    if(qspi_protocol_type==QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
        s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
        s_command.DataMode          = QSPI_DATA_4_LINES;
        s_command.Instruction       = S25HL512T_QUAD_PROG_CMD ;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
        s_command.DataMode          = QSPI_DATA_1_LINE;
        s_command.Instruction       =  S25HL512T_PAGE_PROG_CMD ;
    }
    s_command.AlternateBytes     = 0x00;
    s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTES_16_BITS;
    do
    {
        s_command.Address = current_addr;
        s_command.NbData  = current_size;
        if (qspi_write_enable(qspi_hdl) != QSPI_OK)
        {
            return QSPI_ERROR;
        }
        if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
        if (HAL_QSPI_Transmit(qspi_hdl, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
        if (qspi_auto_polling_mem_ready(qspi_hdl, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
        {
            return QSPI_ERROR;
        }
        current_addr += current_size;
        pData += current_size;
        current_size = ((current_addr + QspiInfo.ProgPageSize) > end_addr) ? (end_addr - current_addr) : QspiInfo.ProgPageSize;
    } while (current_addr < end_addr);
    return QSPI_OK;
}

/**
 * @brief This API erases the specified block of memory through QSPI .
 */
uint8_t qspi_erase_block(QSPI_HandleTypeDef *qspi_hdl,uint32_t BlockAddress)
{
    QSPI_CommandTypeDef s_command;
    if(qspi_protocol_type==QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
        s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
    }
    s_command.Instruction       = S25HL512T_SECTOR_ERASE_CMD; /* same value on both memory types */
    s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
    s_command.Address           = BlockAddress;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    if (qspi_write_enable(qspi_hdl) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (qspi_auto_polling_mem_ready(qspi_hdl, QspiInfo.SectorEraseMaxTime) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

/**
 * @brief This API erases the entire memory chip
 */
uint8_t qspi_erase_chip(QSPI_HandleTypeDef *qspi_hdl)
{
    QSPI_CommandTypeDef s_command;
    if(qspi_protocol_type==QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    }
    s_command.Instruction       = S25HL512T_BULK_ERASE_ALTERNATE_CMD; /* same value on both memory types */
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    if (qspi_write_enable(qspi_hdl) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (qspi_auto_polling_mem_ready(qspi_hdl, QspiInfo.BulkEraseMaxTime) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

/**
 * @brief This API reads current status of memory
 */
uint8_t qspi_get_status(QSPI_HandleTypeDef *qspi_hdl)
{
    QSPI_CommandTypeDef s_command;
    uint8_t reg1, reg2 ,reg3;
    if(qspi_protocol_type==QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
        s_command.DataMode          = QSPI_DATA_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        s_command.DataMode          = QSPI_DATA_1_LINE;
    }
    s_command.Instruction       = S25HL512T_READ_STATUS_REG1_CMD;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (HAL_QSPI_Receive(qspi_hdl, &reg1, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    s_command.Instruction  = S25HL512T_READ_STATUS_REG2_CMD;
    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (HAL_QSPI_Receive(qspi_hdl, &reg2, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    s_command.Instruction       = S25HL512T_READ_CONFIGURATION_REG1_CMD;
    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (HAL_QSPI_Receive(qspi_hdl, &reg3, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if ((reg1 & (S25HL512T_SR1_ERERR | S25HL512T_SR1_PGERR | S25HL512T_SR1_SRWD )) != 0)
    {
        return QSPI_ERROR;
    }
    if ((reg1 & (S25HL512T_SR1_BP0 | S25HL512T_SR1_BP1 | S25HL512T_SR1_BP2)) != 0)
    {
        return QSPI_PROTECTED;
    }
    if ((reg2 & (S25HL512T_SR2_PS | S25HL512T_SR2_ES)) != 0)
    {
        return QSPI_SUSPENDED;
    }
    if ((reg1 & (S25HL512T_SR1_WIP | S25HL512T_SR1_WREN)) == 0)
    {
        return QSPI_OK;
    }
    else
    {
        return QSPI_BUSY;
    }
}

/**
 * @brief This API configure the QSPI to memory-mapped mode
 */
uint8_t qspi_enable_memorymapped_mode(QSPI_HandleTypeDef *qspi_hdl)
{
    QSPI_CommandTypeDef s_command;
    QSPI_MemoryMappedTypeDef s_mem_mapped_cfg;
    if(qspi_protocol_type == QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
        s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
        s_command.DataMode          = QSPI_DATA_4_LINES;
        s_command.Instruction       =  S25HL512T_QUAD_INOUT_FAST_READ_CMD ;
        s_command.AlternateByteMode  = QSPI_ALTERNATE_BYTES_NONE;//QSPI_ALTERNATE_BYTES_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
        s_command.DataMode          = QSPI_DATA_1_LINE;
        s_command.Instruction       = S25HL512T_READ_CMD;
        s_command.AlternateByteMode  = QSPI_ALTERNATE_BYTES_1_LINE;
    }
    s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    s_command.AlternateBytes     = 0xA0;
    s_command.AddressSize = QSPI_ADDRESS_32_BITS;
    s_command.DummyCycles = QspiInfo.DummyCyclesRead;
    s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
    if (HAL_QSPI_MemoryMapped(qspi_hdl, &s_command, &s_mem_mapped_cfg) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

/*
 * @brief This API reset the memory .
 */
uint8_t qspi_reset_memory(QSPI_HandleTypeDef *qspi_hdl)
{
    QSPI_CommandTypeDef s_command;
    uint32_t instruction1;
    instruction1 = S25HL512T_SOFTWARE_RESET_CMD;
    if(qspi_protocol_type==QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    }
    s_command.Instruction       = instruction1;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (qspi_auto_polling_mem_ready(qspi_hdl, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

/**
 * @brief This API set the QSPI in 4-byte address mode
 */
uint8_t qspi_enter_fourbytes_address(QSPI_HandleTypeDef *qspi_hdl)
{
    QSPI_CommandTypeDef s_command;
    uint8_t reg_val;
    {
        if(qspi_protocol_type==QPI)
        {
            s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
            s_command.DataMode          = QSPI_DATA_4_LINES;
            s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
        }
        else if(qspi_protocol_type==SIO)
        {
            s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
            s_command.DataMode          = QSPI_DATA_1_LINE;
            s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
        }
        s_command.Instruction       = S25HL512T_READ_ANY_REG_CMD;
        s_command.Address           = S25HL512T_CONF2_REG_NV_ADDR;
        s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
        s_command.DummyCycles       = 0;
        s_command.NbData            = 1;
        s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
        s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
        s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
        if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
        if (HAL_QSPI_Receive(qspi_hdl, &reg_val, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
        if (qspi_write_enable(qspi_hdl) != QSPI_OK)
        {
            return QSPI_ERROR;
        }
        s_command.Instruction       = S25HL512T_WRITE_ANY_REG_CMD;
        s_command.NbData            = 1;
        reg_val = (reg_val & 0x7F) | 0x01;
        if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
        if (HAL_QSPI_Transmit(qspi_hdl, &reg_val, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
    }
    return QSPI_OK;
}

/**
 * @brief This API configure the dummy cycles of memory
 */
uint8_t qspi_dummy_cycles_cfg(QSPI_HandleTypeDef *qspi_hdl, e_qspi_latency_cycle dummy_cycle)
{
    QSPI_CommandTypeDef s_command;
    uint8_t reg_val;
    {
        if(qspi_protocol_type==QPI)
        {
            s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
            s_command.DataMode          = QSPI_DATA_4_LINES;
            s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
        }
        else if(qspi_protocol_type==SIO)
        {
            s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
            s_command.DataMode          = QSPI_DATA_1_LINE;
            s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
        }
        s_command.Instruction       = S25HL512T_READ_ANY_REG_CMD;
        s_command.Address           = S25HL512T_CONF2_REG_NV_ADDR;
        s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
        s_command.DummyCycles       = 0;
        s_command.NbData            = 1;
        s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
        s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
        s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
        if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
        if (HAL_QSPI_Receive(qspi_hdl, &reg_val, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
        if (qspi_write_enable(qspi_hdl) != QSPI_OK)
        {
            return QSPI_ERROR;
        }
        s_command.Instruction       = S25HL512T_WRITE_ANY_REG_CMD;
        s_command.NbData            = 1;
        reg_val= (reg_val & 0xF0) | (uint8_t)(dummy_cycle);
        if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
        if (HAL_QSPI_Transmit(qspi_hdl, &reg_val, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
    }
    return QSPI_OK;
}

/**
 * @brief This API send a Write enable command to memory
 */
uint8_t qspi_write_enable(QSPI_HandleTypeDef *qspi_hdl)
{
    QSPI_CommandTypeDef     s_command;
    QSPI_AutoPollingTypeDef sConfig;
    if(qspi_protocol_type==QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    }
    s_command.Instruction       = S25HL512T_WRITE_ENABLE_CMD; /* equal on both memory types */
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    sConfig.Match           = S25HL512T_SR1_WREN;
    sConfig.Mask            = S25HL512T_SR1_WREN;
    sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
    sConfig.StatusBytesSize = 1;
    sConfig.Interval        = 0x10;
    sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;
    if(qspi_protocol_type==QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
        s_command.DataMode       = QSPI_DATA_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        s_command.DataMode       = QSPI_DATA_1_LINE;
    }
    s_command.Instruction    = S25HL512T_READ_STATUS_REG1_CMD;

    if (HAL_QSPI_AutoPolling(qspi_hdl, &s_command, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

/**
 * @brief This API configure the QSPI Automatic Polling Mode in blocking mode.
 */
uint8_t qspi_auto_polling_mem_ready(QSPI_HandleTypeDef *qspi_hdl, uint32_t Timeout)
{
    QSPI_CommandTypeDef     s_command;
    QSPI_AutoPollingTypeDef sConfig;
    if(qspi_protocol_type==QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
        s_command.DataMode          = QSPI_DATA_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        s_command.DataMode          = QSPI_DATA_1_LINE;
    }
    s_command.Instruction       = S25HL512T_READ_STATUS_REG1_CMD;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    sConfig.Match           = 0;
    sConfig.Mask            = S25HL512T_SR1_WIP;
    sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
    sConfig.StatusBytesSize = 1;
    sConfig.Interval        = 0x10;
    sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;
    if (HAL_QSPI_AutoPolling(qspi_hdl, &s_command, &sConfig, Timeout) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

/**
 * @brief This API reads the ID of the Memory id
 */
uint8_t qspi_read_id(QSPI_HandleTypeDef *qspi_hdl,QSPI_InfoTypeDef *pqspi_info)
{
    QSPI_CommandTypeDef     s_command;
    uint8_t reg[6];
    if(qspi_protocol_type == QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
        s_command.DataMode          = QSPI_DATA_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        s_command.DataMode          = QSPI_DATA_1_LINE;
    }
    s_command.Instruction       = S25HL512T_READ_ID_CMD;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.NbData            = 6;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (HAL_QSPI_Receive(qspi_hdl, reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (reg[0] == JEDEC_MANUF_ID_CYPRESS)
    {
        pqspi_info->ManufID = QSPI_S25HL512T;
        pqspi_info->FlashSize = (reg[2]<<21) & 0xFFFFFFFF;
        pqspi_info->EraseSectorSize = S25HL512T_SECTOR_SIZE;
        pqspi_info->EraseSectorsNumber = (S25HL512T_FLASH_SIZE/S25HL512T_SECTOR_SIZE);
        pqspi_info->ProgPageSize = S25HL512T_PAGE_SIZE;
        pqspi_info->ProgPagesNumber = (S25HL512T_FLASH_SIZE/S25HL512T_PAGE_SIZE);
        pqspi_info->DummyCyclesRead = 8;
        pqspi_info->SectorEraseMaxTime = S25HL512T_SECTOR_ERASE_MAX_TIME;
        pqspi_info->BulkEraseMaxTime = S25HL512T_BULK_ERASE_MAX_TIME;
    }
    else
        return QSPI_ERROR;

    return QSPI_OK;
}

/**
 * @brief  This API set the transfer protocol type
 */
uint8_t qspi_set_protocol_type(QSPI_HandleTypeDef *qspi_hdl, uint8_t prtcl_type)
{
    QSPI_CommandTypeDef s_command;
    uint8_t reg[4]={0,0,0,0};
    if(qspi_protocol_type==QPI)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
        s_command.DataMode          = QSPI_DATA_4_LINES;
    }
    else if(qspi_protocol_type==SIO)
    {
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        s_command.DataMode          = QSPI_DATA_1_LINE;
    }
    s_command.Instruction       = 0x35;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (HAL_QSPI_Receive(qspi_hdl, &reg[1], HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (qspi_write_enable(qspi_hdl) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    s_command.Instruction = 0x01;
    s_command.NbData  	  = 4;
    if(prtcl_type==QPI)
    {
        MODIFY_REG(reg[1], S25FL512T_CR1_QUAD, S25FL512T_CR1_QUAD);
        reg[2]=0xC8;
        reg[3]=0x10;
    }
    else if(prtcl_type==SIO)
    {
        reg[1]=reg[1]&0xFD;
        reg[2]=0x08;
    }

    if (HAL_QSPI_Command(qspi_hdl, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (HAL_QSPI_Transmit(qspi_hdl, &reg[0], HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (qspi_auto_polling_mem_ready(qspi_hdl, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    qspi_protocol_type=prtcl_type;
    return QSPI_OK;

}

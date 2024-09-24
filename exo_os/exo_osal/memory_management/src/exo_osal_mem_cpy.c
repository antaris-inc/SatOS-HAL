/**
 * @file exo_osal_mem_cpy.c
 *
 * @brief This file contains function definitions for different memory.
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

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "exo_osal.h"
#include "exo_osal_common.h"
#include "exo_common.h"
#include "exo_osal_mem_cpy.h"
#ifndef LINUX_TEMP_PORT
#include "qspi.h"
#include "exo_io_al_fmc_nor_flash.h"
#endif
#include "exo_types.h"

void* hnor_hdl;
void* hqspi_hdl;

extern volatile uint8_t nvm_write_flag;
volatile uint8_t init_flag = 0;

/* Added Fixed Memery address for external memory validation*/
#define SDRAM_ADDR		((uint32_t)0xC0500000)       ///< starting address for SDRAM
#define FMC_NOR_ADDR	((uint32_t)0x60200000)       ///< starting address for FMC NOR
#define FMC_QSPI_ADDR	((uint32_t)0x00000000)       ///< starting address for FMC QSPI
#define LEN				(100)                        ///< Maximum length for all memory

#define FLASH_TYPEPROGRAM_BYTE        ((uint32_t)0x00U)  ///< Program byte (8-bit) at a specified address
#define FLASH_TYPEPROGRAM_HALFWORD    ((uint32_t)0x01U)  ///< Program a half-word (16-bit) at a specified address
#define FLASH_TYPEPROGRAM_WORD        ((uint32_t)0x02U)  ///< Program a word (32-bit) at a specified address
#define FLASH_TYPEPROGRAM_DOUBLEWORD  ((uint32_t)0x03U)  ///< Program a double word (64-bit) at a specified address
#define LOCAL_BUFF_LEN	(1*1024*1024)                    ///< Local buffer length
#define SECTOR_SIZE_NOR (64*1024)                        ///< NOR sector size
#define SECTOR_SIZE_QSPI (4*1024)                        ///< QSPI sector size
#define FLASH_SIZE (1*1024)                              ///< Flash size
obc_memcpy_memory_layout look_up_table[MAX_MEM];         ///< Maximum memcpy size
uint8_t local_buff_sram[FLASH_SIZE] ={0};                ///< SRAM local buffer size
uint8_t PLACE_IN_SDRAM_MEM local_buff[LOCAL_BUFF_LEN];   ///< Buffer to place in SDRAM

#ifndef LINUX_TEMP_PORT
/**
 * @brief This API erase the flash sector for given length.
 */
void flash_sector_erase_by_add_n_len(uint8_t* write_addr,int len,int8_t flash_type)
{
    switch(flash_type)
    {
        case E_QSPI_FLASH:
            {
                for(int erase_len=0; erase_len<len; erase_len+=(SECTOR_SIZE_QSPI))
                {
                    qspi_erase_block(hqspi_hdl,(uint32_t)write_addr);
                    os_delay(10);
                }
            }
            break;
        case E_FMC_FLASH:
            {
                for(int erase_len=0; erase_len<len; erase_len+=(SECTOR_SIZE_NOR*2))
                {
                    io_hal_fmc_nor_flash_erase_block(hnor_hdl,(uint32_t)write_addr);
                    io_hal_fmc_nor_flash_erase_block(hnor_hdl,(uint32_t)(write_addr+SECTOR_SIZE_NOR));
                    os_delay(10);
                }
            }
            break;
        default:
            {
                printf("Invalid flash type %d ", flash_type);
            }
    }

}

/**
 * @brief This API write data to External NOR flash memory.
 */
uint8_t write_to_e_norfmc(uint8_t* write_addr,uint8_t* data,int len, uint8_t erase_flag)
{
    uint8_t sts=0;
    uint32_t flsh_write_addr = (uint32_t)write_addr;
    while(len>0)
    {
        if(len>SECTOR_SIZE_NOR)
        {
            if(erase_flag)
            {
                sts = io_hal_fmc_nor_flash_erase_block(hnor_hdl,flsh_write_addr);
                sts = io_hal_fmc_nor_flash_erase_block(hnor_hdl,flsh_write_addr+SECTOR_SIZE_NOR);
                os_delay(10);
            }
            sts = io_hal_fmc_nor_flash_write(hnor_hdl,flsh_write_addr,data,(SECTOR_SIZE_NOR));
            os_delay(10);
            sts = io_hal_fmc_nor_flash_write(hnor_hdl,flsh_write_addr+SECTOR_SIZE_NOR,data+SECTOR_SIZE_NOR,(SECTOR_SIZE_NOR));
            os_delay(10);
            flsh_write_addr = flsh_write_addr + SECTOR_SIZE_NOR*2;
            len = len-(SECTOR_SIZE_NOR*2);
            data = data + (SECTOR_SIZE_NOR)*2;
        }
        else
        {
            if(erase_flag)
            {
                sts = io_hal_fmc_nor_flash_erase_block(hnor_hdl,flsh_write_addr);
                sts = io_hal_fmc_nor_flash_erase_block(hnor_hdl,flsh_write_addr+SECTOR_SIZE_NOR);
                os_delay(10);
            }
            sts = io_hal_fmc_nor_flash_write(hnor_hdl,flsh_write_addr,data,len);
            len = len-(SECTOR_SIZE_NOR*2);
        }
    }

    return sts;
}

/**
 * @brief This API write data to External QSPI memory
 */
uint8_t write_to_e_qspi(uint8_t* write_addr,uint8_t* data,int len, uint8_t erase_flag)
{
    uint8_t sts=0;
    uint32_t flsh_write_addr = (uint32_t)write_addr;
    while(len>0)
    {
        if(len>SECTOR_SIZE_QSPI)
        {
            if(erase_flag)
            {
                sts = qspi_erase_block(hqspi_hdl,flsh_write_addr);
                os_delay(10);
            }
            sts = qspi_write(hqspi_hdl,data, flsh_write_addr,len);
            flsh_write_addr = flsh_write_addr + SECTOR_SIZE_QSPI;
            len = len-SECTOR_SIZE_QSPI;
            data = data + SECTOR_SIZE_QSPI;
        }
        else
        {
            if(erase_flag)
            {
                sts = qspi_erase_block(hqspi_hdl,flsh_write_addr);
                os_delay(10);
            }
            sts = qspi_write(hqspi_hdl,data, flsh_write_addr,len);
            len = len-SECTOR_SIZE_QSPI;
        }
    }
    return sts;
}

#endif

/**
 * @brief This API write data to RAM.
 */
uint8_t write_to_ram(uint8_t* write_addr,uint8_t* data,int len, uint8_t erase_flag)
{
    uint8_t sts = CPY_OK;
    int size_inc;
    for(size_inc =0; size_inc < len ;size_inc++)
    {
        write_addr[size_inc] = data[size_inc];
    }
    return sts;
}

/**
 * @brief This API read data from RAM.
 */
uint8_t read_from_ram(uint8_t* read_addr,uint8_t* data,int len)
{
    uint8_t sts = CPY_OK;
    int size_inc;
    for(size_inc =0; size_inc < len ;size_inc++)
    {
        data[size_inc] = read_addr[size_inc];
    }
    return sts;
}

/**
 * @brief This API read data from internal flash.
 */
uint8_t read_from_iflash(uint8_t* read_addr,uint8_t* data,int len)
{
    uint8_t sts = CPY_OK;
    int size_inc;
    for(size_inc =0; size_inc < len ;size_inc++)
    {
        data[size_inc] = read_addr[size_inc];
    }
    return sts;
}
#ifndef LINUX_TEMP_PORT

/**
 * @brief This API read data from external NOR flash.
 */
uint8_t read_from_e_norfmc(uint8_t* read_addr,uint8_t* data,int len)
{
    uint8_t sts;
    /*DRIVER only supports 2 byte read or write*/
    sts = io_hal_fmc_nor_flash_read(hnor_hdl,(uint32_t)read_addr,data,len/2);
    return sts;
}

/**
 * @brief This API read data from external QSPI.
 */
uint8_t read_from_e_qspi(uint8_t* read_addr,uint8_t* data,int len)
{
    uint8_t sts;
    /*uint32_t src_add = ((uint32_t)src/(uint32_t)look_up_table[E_QSPI_FLASH].start_addr);*/
    sts = qspi_read(hqspi_hdl,data,(uint32_t)read_addr,len);
    return sts;
}
#endif

/**
 * @brief This API initialize the memcpy framework.
 */
void os_memcpy_fw_init(void *nor_hdl,void* qspi_hdl)
{
    look_up_table[I_RAM].start_addr = (uint8_t*)0x20000000;
    look_up_table[I_RAM].len_bytes = (0.5*1024*1024);
    look_up_table[I_RAM].end_addr = look_up_table[I_RAM].start_addr+look_up_table[I_RAM].len_bytes;
    look_up_table[I_RAM].read_fun = read_from_ram;
    look_up_table[I_RAM].write_fun = write_to_ram;

#ifndef LINUX_TEMP_PORT 

#if defined(STM32F769xx) || defined(COREBOARD)
    look_up_table[E_RAM].start_addr =(uint8_t*)0xC0000000;
    look_up_table[E_RAM].len_bytes = (32*1024*1024);
    look_up_table[E_RAM].end_addr = look_up_table[E_RAM].start_addr+look_up_table[E_RAM].len_bytes;
    look_up_table[E_RAM].read_fun = read_from_ram;
    look_up_table[E_RAM].write_fun = write_to_ram;

    hqspi_hdl = qspi_hdl;
    look_up_table[E_QSPI_FLASH].start_addr = (uint8_t*)0x90000000;
    look_up_table[E_QSPI_FLASH].len_bytes = (64*1024*1024);
    look_up_table[E_QSPI_FLASH].end_addr = look_up_table[E_QSPI_FLASH].start_addr+look_up_table[E_QSPI_FLASH].len_bytes;
    look_up_table[E_QSPI_FLASH].read_fun = read_from_e_qspi;
    look_up_table[E_QSPI_FLASH].write_fun = write_to_e_qspi;
#endif
#if defined(COREBOARD)
    hnor_hdl = nor_hdl;
    look_up_table[E_FMC_FLASH].start_addr = (uint8_t*)0x60000000;
    look_up_table[E_FMC_FLASH].len_bytes = (16*1024*1024);
    look_up_table[E_FMC_FLASH].end_addr = look_up_table[E_FMC_FLASH].start_addr+look_up_table[E_FMC_FLASH].len_bytes;
    look_up_table[E_FMC_FLASH].read_fun = read_from_e_norfmc;
    look_up_table[E_FMC_FLASH].write_fun = write_to_e_norfmc;

#endif
#endif
    os_thread_create(OBC_MEMCPY_THREAD,T_OSAL_MEM_STACK_SIZE,P_OBC_MEMCPY_THREAD,"MEMCPY THREAD",memcpy_event_thread,NULL,NULL,NULL);
    init_flag = 1;
}

/**
 * @brief This API compare both source and destination address and update
 *        the memory type info.
 */
uint8_t mem_cpy_fun_def(obc_memcpy_info *obc_cpy_info)
{
    uint8_t sts = CPY_OK;
#ifndef LINUX_TEMP_PORT
#ifdef SD_RAM_FIX
    switch(obc_cpy_info->src_mem_type)
    {
        case I_RAM:
        case E_RAM:
            if(obc_cpy_info->dst_mem_type < I_FLASH)
            {
                sts = look_up_table[obc_cpy_info->src_mem_type].read_fun(obc_cpy_info->src_addr,obc_cpy_info->dst_addr,obc_cpy_info->len);
            }
            break;
        case I_FLASH:
        case E_QSPI_FLASH:
        case E_FMC_FLASH:
            if(obc_cpy_info->dst_mem_type < I_FLASH)
            {
                sts = look_up_table[obc_cpy_info->src_mem_type].read_fun(obc_cpy_info->src_addr,obc_cpy_info->dst_addr,obc_cpy_info->len);
            }
            else
            {
                sts = look_up_table[obc_cpy_info->src_mem_type].read_fun(obc_cpy_info->src_addr,local_buff,obc_cpy_info->len);
            }
            break;
    }
    if(sts == CPY_OK)
    {
        switch(obc_cpy_info->dst_mem_type)
        {
            case I_RAM:
            case E_RAM:
                break;
            case I_FLASH:
            case E_QSPI_FLASH:
            case E_FMC_FLASH:
                if(obc_cpy_info->src_mem_type < I_FLASH)
                {
                    sts = look_up_table[obc_cpy_info->dst_mem_type]\
                          .write_fun(obc_cpy_info->dst_addr,obc_cpy_info->src_addr,obc_cpy_info->len,obc_cpy_info->erase_flag);
                }
                else
                {
                    sts = look_up_table[obc_cpy_info->dst_mem_type]\
                          .write_fun(obc_cpy_info->dst_addr,local_buff,obc_cpy_info->len,obc_cpy_info->erase_flag);
                }
                break;
        }
    }

#else
    uint8_t* src_addr = obc_cpy_info->src_addr;
    uint8_t* dst_addr = obc_cpy_info->dst_addr;
    int len = obc_cpy_info->len;
    int erase_flag  = obc_cpy_info->erase_flag;
    if((obc_cpy_info->dst_mem_type == E_FMC_FLASH))
    {
        sts = look_up_table[obc_cpy_info->dst_mem_type].write_fun(dst_addr,src_addr,len,erase_flag);
    }
    else
    {
        while(len > 0)
        {
            if(len > FLASH_SIZE)
            {
                sts = look_up_table[obc_cpy_info->src_mem_type].read_fun(src_addr,local_buff_sram,FLASH_SIZE);
                os_delay(10);
                sts = look_up_table[obc_cpy_info->dst_mem_type].write_fun(dst_addr,local_buff_sram,FLASH_SIZE,erase_flag);
            }
            else
            {
                sts = look_up_table[obc_cpy_info->src_mem_type].read_fun(src_addr,local_buff_sram,len);
                os_delay(10);
                sts = look_up_table[obc_cpy_info->dst_mem_type].write_fun(dst_addr,local_buff_sram,len,erase_flag);
            }
            src_addr += FLASH_SIZE;
            dst_addr += FLASH_SIZE;
            len = len - FLASH_SIZE;
        }
    }
#endif
#else
    os_memcpy(obc_cpy_info->dst_addr,obc_cpy_info->src_addr,obc_cpy_info->len);
#endif
    if(obc_cpy_info->call_back_fun)
    {
        obc_cpy_info->call_back_fun(sts);
    }
    return sts;
}

/**
 * @brief This API compare both source and destination address and update
 *        the memory type info.
 *
 * Length cannot be greater than 1 MB
 */
cpy_sts obc_memcpy_wrapper(uint8_t* dst_addr,uint8_t* src_addr,uint32_t len,mem_cpy_cmptl_cb cb_fun,uint8_t imemdiate_flag,uint8_t erase_flag)
{
    cpy_sts sts = CPY_ERR;
    obc_memcpy_info *obc_memcpy_hdlr_info = os_malloc(sizeof(obc_memcpy_info));
    obc_memcpy_hdlr_info->src_addr = src_addr;
    obc_memcpy_hdlr_info->dst_addr = dst_addr;
    obc_memcpy_hdlr_info->len = len;
    obc_memcpy_hdlr_info->erase_flag  = erase_flag;
#ifndef LINUX_TEMP_PORT
    if(init_flag == 1)
    {
        uint8_t i;
        uint8_t src_sts,dst_sts;
        for(i =0;i<MAX_MEM;i++)
        {
            if((obc_memcpy_hdlr_info->src_addr >= look_up_table[i].start_addr) && ((obc_memcpy_hdlr_info->src_addr+obc_memcpy_hdlr_info->len) <= look_up_table[i].end_addr))
            {
                obc_memcpy_hdlr_info->src_mem_type = i;
                src_sts = VALID_ADDR;
            }
            if((obc_memcpy_hdlr_info->dst_addr >= look_up_table[i].start_addr) && ((obc_memcpy_hdlr_info->dst_addr+obc_memcpy_hdlr_info->len) <= look_up_table[i].end_addr))
            {
                obc_memcpy_hdlr_info->dst_mem_type = i;
                dst_sts = VALID_ADDR;
            }
        }
        if(src_sts == VALID_ADDR && dst_sts == VALID_ADDR)
        {
            if(imemdiate_flag == 0)
            {
                obc_memcpy_hdlr_info->call_back_fun = cb_fun;
                os_itc_msg_handle_t send;
                send.src_entity = 1;
                send.pld_info = 0;
                send.Msg_id = 0;
                send.Msg_len = sizeof(obc_memcpy_info);
                send.pld.pld_ptr = obc_memcpy_hdlr_info;
                sts = os_itc_msg_send(&send,OBC_MEMCPY_THREAD,os_wait_forever);
            }
            else
            {
                obc_memcpy_hdlr_info->call_back_fun = NULL;
                sts = mem_cpy_fun_def(obc_memcpy_hdlr_info);
            }
        }
        else
        {
            if(src_sts != VALID_ADDR)
            {
                sts = src_sts;
            }
            else
            {
                sts = dst_sts;
            }
        }
    }
#else
    if(imemdiate_flag == 0)
    {
        obc_memcpy_hdlr_info->call_back_fun = cb_fun;
        os_itc_msg_handle_t send;
        send.src_entity = 1;
        send.pld_info = 0;
        send.Msg_id = 0;
        send.Msg_len = sizeof(obc_memcpy_info);
        send.pld.pld_ptr = obc_memcpy_hdlr_info;
        sts = os_itc_msg_send(&send,OBC_MEMCPY_THREAD,os_wait_forever);
    }
    else
    {
        sts = CPY_OK;
        os_memcpy(obc_memcpy_hdlr_info->dst_addr,obc_memcpy_hdlr_info->src_addr,obc_memcpy_hdlr_info->len);
    }
#endif
    return sts;
}

/**
 * @brief Memory copy thread entry function.
 */
void memcpy_event_thread(void* args)
{
    while(1)
    {
        os_itc_msg_handle_t recv_info;
        if(os_itc_msg_rcv(OBC_MEMCPY_THREAD,&recv_info,os_wait_forever) == 1)
        {
            obc_memcpy_info *obc_cpy_info_rec = ((obc_memcpy_info*)recv_info.pld.pld_ptr);
            mem_cpy_fun_def(obc_cpy_info_rec);

            if(recv_info.pld.pld_ptr)
            {
                os_free(recv_info.pld.pld_ptr);
                recv_info.pld.pld_ptr = NULL;
            }
        }
    }
}

/**
 * @brief This API to load buffer with given offset.
 */
void Fill_test_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset)
{
    uint32_t tmpIndex = 0;
    /* Put in global buffer different values */
    for (tmpIndex = 0; tmpIndex < uwBufferLenght; tmpIndex++ )
    {
        pBuffer[tmpIndex] = tmpIndex;// + uwOffset;
    }
}

/**
 * @brief This API test the external memory.
 */
uint8_t extrnl_memory_test(uint8_t mem_type)
{
    uint8_t sts=0,intg_sts=0,rd_sts=0,wr_sts=0,ers_sts=0;
    uint32_t uwWriteReadStatus = 0;
    uint32_t uwIndex = 0;
    uint32_t* write_buffer= os_malloc(sizeof(uint32_t)*LEN);
    uint32_t* read_buffer= os_malloc(sizeof(uint32_t)*LEN);
    uint32_t* mem_addr;
    /* Fill the buffer to write */
    Fill_test_Buffer(write_buffer, LEN, 0xA244250F);
    switch(mem_type)
    {
        case E_RAM:
            mem_addr = (uint32_t*)SDRAM_ADDR;
            os_memcpy(mem_addr,write_buffer,LEN);
            os_memcpy(read_buffer,mem_addr,LEN);
            break;
        case E_QSPI_FLASH:
            mem_addr = (uint32_t*)FMC_QSPI_ADDR;
#ifndef LINUX_TEMP_PORT
            ers_sts = qspi_erase_block(hqspi_hdl,(uint32_t)mem_addr);
            wr_sts = qspi_write(hqspi_hdl,(uint8_t*)write_buffer,(uint32_t)mem_addr,LEN);
            rd_sts = qspi_read(hqspi_hdl,(uint8_t*)read_buffer,(uint32_t)mem_addr,LEN);
#endif
            break;
        case E_FMC_FLASH:
            mem_addr = (uint32_t*)FMC_NOR_ADDR;
#ifndef LINUX_TEMP_PORT
            ers_sts = io_hal_fmc_nor_flash_erase_block(hnor_hdl,(uint32_t)mem_addr);
            wr_sts = io_hal_fmc_nor_flash_write(hnor_hdl,(uint32_t)mem_addr,(uint8_t*)write_buffer,LEN);
            rd_sts = io_hal_fmc_nor_flash_read(hnor_hdl,(uint32_t)mem_addr,(uint8_t*)read_buffer,LEN/2);
#endif
            break;
    }
    /*##-3- Checking data integrity ############################################*/
    for (uwIndex = 0; (uwIndex < (LEN/4)) && (uwWriteReadStatus == 0); uwIndex++)
    {
        if (write_buffer[uwIndex] != read_buffer[uwIndex])
        {
            uwWriteReadStatus++;
        }
    }
    intg_sts = (uwWriteReadStatus != 0)?1:0;
    os_free(read_buffer);
    read_buffer = NULL;
    os_free(write_buffer);
    write_buffer = NULL;
    sts = ((intg_sts)&0x01) | (((ers_sts)&0x01)<<1) | (((wr_sts)&0x01)<<2) | (((rd_sts)&0x01)<<3);
    return sts;
}

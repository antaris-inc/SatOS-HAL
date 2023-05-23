/**
 * @file s25fl512t.h
 *
 *  @brief This file contains the macro definitions for S25FL512T QSPI memory
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __S25HL512T_H
#define __S25HL512T_H

#ifdef __cplusplus
extern "C" {
#endif 

#define S25FL512T_CR1_QUAD                              ((uint8_t)0x02)      /*!< Quad mode enable */
    /**
     * @brief  S25HL512T Configuration
     */
#define S25HL512T_FLASH_SIZE                            0x4000000 		///< 512 MBits => 64MBytes
#define S25HL512T_SECTOR_SIZE                           0x40000   		///< 256 sectors of 256KBytes
#define S25HL512T_PAGE_SIZE                             0x200     		///< 131072 pages of 512 bytes

#define S25HL512T_BULK_ERASE_MAX_TIME                   460000			///< Maximum time of bulk erase
#define S25HL512T_SECTOR_ERASE_MAX_TIME                 2600			///< Maximum time of sector erase


#define  S25HL512T_STS1_REG_NV_ADDR                 0x00000000     		///< Non volatile status1 register address
#define  S25HL512T_CONF1_REG_NV_ADDR                0x00000002			///< Non volatile conf1 register address
#define  S25HL512T_CONF2_REG_NV_ADDR                0x00000003			///< Non volatile conf2 register address
#define  S25HL512T_CONF3_REG_NV_ADDR                0x00000004			///< Non volatile conf3 register address
#define  S25HL512T_CONF4_REG_NV_ADDR                0x00000005			///< Non volatile conf4 register address

#define  S25HL512T_STS1_REG_V_ADDR                  0x00800000			///< volatile status1 register address
#define  S25HL512T_STS2_REG_V_ADDR                  0x00800001			///< volatile status2 register address
#define  S25HL512T_CONF1_REG_V_ADDR                 0x00800002			///< volatile conf1  register address
#define  S25HL512T_CONF2_REG_V_ADDR                 0x00800003			///< volatile conf2 register address
#define  S25HL512T_CONF3_REG_V_ADDR                 0x00800004			///< volatile conf3 register address
#define  S25HL512T_CONF4_REG_V_ADDR                 0x00800005			///< volatile conf4 register address


    /**
     * @brief  S25HL512T Commands
     */
    /* Reset Operations */
#define S25HL512T_SOFTWARE_RESET_CMD                    0xF0			///< software reset command

#define S25HL512T_READ_ID_CMD                           0x9F			///< read ID command
#define S25HL512T_READ_ELECTRONIC_SIGNATURE             0x4C			///< read electronic signature
#define S25HL512T_READ_SERIAL_FLASH_DISCO_PARAM_CMD     0x5A			///< read serial flash discovery command

#define S25HL512T_READ_STATUS_REG1_CMD                  0x05			///< read status register 1 command
#define S25HL512T_READ_STATUS_REG2_CMD                  0x07			///< read status register 2 command
#define S25HL512T_READ_CONFIGURATION_REG1_CMD           0x35			///< read configuration register 1 command

#define S25HL512T_READ_ANY_REG_CMD                      0x65			///< read anu register command
#define S25HL512T_WRITE_ANY_REG_CMD                     0x71			///< write any register command

#define S25HL512T_WRITE_STATUS_CONF_REG_CMD             0x01			///< write status conf register command
#define S25HL512T_WRITE_DISABLE_CMD                     0x04			///< write disable command
#define S25HL512T_WRITE_ENABLE_CMD                      0x06			///< write enablecommand

#define S25HL512T_CLEAR_STATUS_REG1_CMD                 0x30			///< clear status register command
#define S25HL512T_READ_AUTOBOOT_REG_CMD                 0x14			///< read autoboot register command
#define S25HL512T_WRITE_AUTOBOOT_REG_CMD                0x15			///< write autoboot register command

#define S25HL512T_READ_DATA_LEARNING_PATTERN_CMD        0x41			///< read data learning pattern command
#define S25HL512T_PGM_NV_DATA_LEARNING_REG_CMD          0x43			///< pgm non volatile data learning register command
#define S25HL512T_WRITE_VOL_DATA_LEARNING_REG_CMD       0x4A			///< write volatile data learning register command

    /* Read Operations */
#define S25HL512T_READ_CMD                              0x03			///< read command
#define S25HL512T_READ_4_BYTE_ADDR_CMD                  0x13			///< read 4 byte address command

#define S25HL512T_FAST_READ_CMD                         0x0B			///< fast read command
#define S25HL512T_FAST_READ_4_BYTE_ADDR_CMD             0x0C			///< fast read 4 byte address command

#define S25HL512T_FAST_READ_DDR_CMD                     0x0D			///< fast read ddr command
#define S25HL512T_FAST_READ_DDR_4_BYTE_ADDR_CMD         0x0E			///< fast read ddr 4 byte address command

#define S25HL512T_QUAD_OUT_FAST_READ_CMD                0x6B			///< quad out fast read command
#define S25HL512T_QUAD_OUT_FAST_READ_4_BYTE_ADDR_CMD    0x6C			///< quad out fast read 4 byte address command

#define S25HL512T_DUAL_INOUT_FAST_READ_CMD              0xBB			///< dual inout fast read command
#define S25HL512T_DUAL_INOUT_FAST_READ_4_BYTE_ADDR_CMD  0xBC			///< dual inout fast read 4 byte address command

#define S25HL512T_QUAD_INOUT_FAST_READ_CMD              0xEB			///< quad timeout fast read command
#define S25HL512T_QUAD_INOUT_FAST_READ_4_BYTE_ADDR_CMD  0xEC			///< quad timeout fast read 4 byte address command

#define S25HL512T_QUAD_INOUT_FAST_READ_DDR_CMD          0xED			///< quad inout fast read ddr command
#define S25HL512T_QUAD_INOUT_READ_DDR_4_BYTE_ADDR_CMD   0xEE			///< quad inout read ddr 4 byte address command

    /* Program Operations */
#define S25HL512T_PAGE_PROG_CMD                         0x02			///< page program command
#define S25HL512T_PAGE_PROG_4_BYTE_ADDR_CMD             0x12			///< page program 4 byte address command

#define S25HL512T_QUAD_PROG_CMD                         0x12    		///< quad program command

#define S25HL512T_PROGRAM_SUSPEND_CMD                   0x85    		///< program suspend command
#define S25HL512T_PROGRAM_RESUME_CMD                    0x8A    		///< program resume command

    /* Erase Operations */
#define S25HL512T_SECTOR_ERASE_CMD                      0x21			///< sector erase command
#define S25HL512T_SECTOR_ERASE_4_BYTE_ADDR_CMD          0xDC            ///< sector erase 4 byte address command

#define S25HL512T_BULK_ERASE_CMD                        0x60    		///< Erase Chip
#define S25HL512T_BULK_ERASE_ALTERNATE_CMD              0xC7    		///< Erase Chip

#define S25HL512T_PROG_ERASE_SUSPEND_CMD                0x75    		///< Suspend Erase / Program / Data Integrity Check
#define S25HL512T_PROG_ERASE_RESUME_CMD                 0x7A    		///< Resume Erase / Program / Data Integrity Check

    /* One-Time Programmable Operations */
#define S25HL512T_PROG_SSR_CMD                          0x42    		///< Program Secure Silicon Region
#define S25HL512T_READ_SSR_CMD                          0x4B    		///< Read Secure Silicon Region

    /* Advanced Sector Protection Operations */
#define S25HL512T_READ_DYB_CMD                          0xE0   		///< Read Dynamic Protection Bit
#define S25HL512T_WRITE_DYB_CMD                         0xE1   		///< Write Dynamic Protection Bit

#define S25HL512T_READ_PPB_CMD                          0xE2   		///< Read Persistent Protection Bit
#define S25HL512T_PROGRAM_PPB_CMD                       0xE3   		///< Program Persistent Protection Bit
#define S25HL512T_ERASE_PPB_CMD                         0xE4  			///< Erase Persistent Protection Bit

#define S25HL512T_PROGRAM_ASP_CMD                       0x2F    		///< ASP- Advanced sector protection

#define S25HL512T_READ_PPB_LOCKBIT_CMD                  0xA7			///< read ppb lockbit command
#define S25HL512T_WRITE_PPB_LOCKBIT_CMD                 0xA6			///< write ppb lockbit command

#define S25HL512T_PROGRAM_PASSWORD_CMD                  0xE8			///< program password command
#define S25HL512T_UNLOCK_PASSWORD_CMD                   0xE9			///< unlock password command


    /**
     * @brief  S25HL512T Registers
     */
    /* Status Register-1 */
#define S25HL512T_SR1_WIP                               ((uint8_t)0x01)      ///< Write in progress, device busy
#define S25HL512T_SR1_WREN                              ((uint8_t)0x02)      ///< Write Registers, program or commands are accepted
#define S25HL512T_SR1_BP0                               ((uint8_t)0x04)      ///< Sector0 protected from Program or Erase
#define S25HL512T_SR1_BP1                               ((uint8_t)0x08)      ///< Sector1 protected from Program or Erase
#define S25HL512T_SR1_BP2                               ((uint8_t)0x10)      ///< Sector2 protected from Program or Erase
#define S25HL512T_SR1_ERERR                             ((uint8_t)0x20)      ///< Erase error
#define S25HL512T_SR1_PGERR                             ((uint8_t)0x40)      ///< Program error
#define S25HL512T_SR1_SRWD                              ((uint8_t)0x80)      ///< Status Register Write Disable

    /* Status Register-2 */
#define S25HL512T_SR2_PS                                ((uint8_t)0x01)      ///< Program in Suspend mode
#define S25HL512T_SR2_ES                                ((uint8_t)0x02)      ///< Erase Suspend Mode

    /* Configuration Register CR1 */
#define S25HL512T_CR1_FREEZE                            ((uint8_t)0x01)      ///< Block protection and OTP locked
#define S25HL512T_CR1_QUAD                              ((uint8_t)0x02)      ///< Quad mode enable
#define S25HL512T_CR1_BPNV                              ((uint8_t)0x08)      ///< BP2-0 bits of Status Reg are volatile
#define S25HL512T_CR1_TBPROT                            ((uint8_t)0x20)      ///< BPstarts at bottom
#define S25HL512T_CR1_LC_MASK                           ((uint8_t)0xC0)      ///< Latency Code mask
#define S25HL512T_CR1_LC0                               ((uint8_t)0x00)      ///< Latency Code = 0
#define S25HL512T_CR1_LC1                               ((uint8_t)0x40)      ///< Latency Code = 1
#define S25HL512T_CR1_LC2                               ((uint8_t)0x80)      ///< Latency Code = 2
#define S25HL512T_CR1_LC3                               ((uint8_t)0xC0)      ///< Latency Code = 3

    /* AutoBoot Register */
#define S25HL512T_AB_EN                                 ((uint32_t)0x00000001)	///< AutoBoot Enabled
#define S25HL512T_AB_SD_MASK                            ((uint32_t)0x000001FE)	///< AutoBoot Start Delay mask
#define S25HL512T_AB_SA_MASK                            ((uint32_t)0xFFFFFE00)	///< AutoBoot Start Address mask

    /* Bank Address Register */
#define S25HL512T_BA_BA24                               ((uint8_t)0x01)      ///< A24 for 512 Mb device
#define S25HL512T_BA_BA25                               ((uint8_t)0x02)      ///< A25 for 512 Mb device
#define S25HL512T_BA_EXTADD                             ((uint8_t)0x80)      ///< 4 bytes addressing required from command
#define S25HL512T_QUAD_DATA                             ((uint8_t)0x40)      ///< 4 bit mode

    /* ASP Register */
#define S25HL512T_ASP_PSTMLB                            ((uint16_t)0x0002)   ///< Persistent protection mode not permanently enabled
#define S25HL512T_ASP_PWSMLB                            ((uint16_t)0x0003)   ///< Password protection mode not permanently enabled

    /* PPB Lock Register */
#define S25HL512T_PPBLOCK                               ((uint8_t)0x01)      ///< PPB array may be programmed or erased


#ifdef __cplusplus
}
#endif

#endif

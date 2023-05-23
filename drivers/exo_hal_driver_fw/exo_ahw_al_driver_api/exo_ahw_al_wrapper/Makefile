#
#   @copyright Copyright 2022 Antaris, Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

TOP_DIR=../../../../
include $(TOP_DIR)Makefile.def

##############################################################################
# All variables here intensionally set to empty, User should not modify here

SRC =
SRC_DIR =
SUBDIR =

##############################################################################
# List of include file directories required for compilation
INCLUDES =                      \
	   -I$(TOP_DIR)includes/\
	   -I$(TOP_DIR)drivers/ut/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/imu/bmx160/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/hot_swp_cntlr/adm1176/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/power_sense_monitor/ina230/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/digital_thermostat/ds620/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/temp_sensor/mcp9843/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/gpio_expander/pcal6408a/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/gpio_expander/mcp23008/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/voltage_sequencer/ucd9081/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/data_logger/ads7828/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/memory_drivers/qspi_s25hl512t/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/memory_drivers/sdram_is42s32800b/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/common/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/rcc/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/rtc/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/exti/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/gpio/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/dma/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/cortex/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/can/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/flash/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/wdg/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/i2c/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/pwr/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/spi/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/qspi/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/tmr/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/uart/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/usb/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/ethernet/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/fmc/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/sdram/inc/\
	   -I$(TOP_DIR)drivers/io_drivers/io_drivers_stm32f7xx/nor_flash/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_hal_fw_common/exo_ah_iob_csn/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_hal_fw_common/exo_ahdlsd/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_hal_fw_common/common/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/common/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/imu/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/psm/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/hot_swp_cntlr/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/digital_thermostat/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/temp_sensor/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/gpio_expander/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/voltage_sequencer/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/data_acq_dvc/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_wrapper/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_wrapper/imu_bmx160/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_wrapper/psm_ina230/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_wrapper/temp_sensor_mcp9843/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_wrapper/gpio_pcal6408a/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_wrapper/gpio_mcp23008/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_wrapper/dt_ds620/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_wrapper/hsc_adm1176/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_wrapper/vsm_ucd9081/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_wrapper/data_acq_dvc_ads7828/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/common/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/i2c/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/uart/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/rtc/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/spi/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/usb/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/ethernet/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/can/inc/\
	   -I$(TOP_DIR)drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/fmc_nor_flash/inc/\
	   -I$(TOP_DIR)exo_os/exo_ral/cpu_arch/stm32f7xx/inc/\
	   -I$(TOP_DIR)exo_os/rtos/free_rtos/CMSIS_RTOS_V2/\
	   -I$(TOP_DIR)exo_os/rtos/free_rtos/include/\
	   -I$(TOP_DIR)exo_os/rtos/free_rtos/portable/GCC/ARM_CM7/r0p1/\
	   -I$(TOP_DIR)exo_os/exo_ral/exo_ral_common/inc/\
	   -I$(TOP_DIR)exo_os/exo_osal/exo_osal_common/inc/\
	   -I$(TOP_DIR)exo_os/exo_osal/ipc_mbmr/inc/\
	   -I$(TOP_DIR)exo_os/exo_osal/memory_management/inc/\
	   -I$(TOP_DIR)exo_os/exo_osal/task_management/inc/\

##############################################################################
#Current Folder target name, usually current folder name
#TARGET_LIB = target_name

# List of source files required for compilation using SRC
# mention the directory path where all C files to be compiled usig SRC_DIR
# Mention Sub director makefile compilation using SUBDIR
#SRC += src/file_name.c
#SRC_DIR += src
#SUBDIR += dir_name

SRC_DIR += src

SUBDIR += imu_bmx160
SUBDIR += psm_ina230
SUBDIR += temp_sensor_mcp9843
SUBDIR += gpio_pcal6408a
SUBDIR += gpio_mcp23008
SUBDIR += dt_ds620
SUBDIR += hsc_adm1176
SUBDIR += vsm_ucd9081
SUBDIR += data_acq_dvc_ads7828

##############################################################################

ifeq ($(TARGET_LIB),)
TARGET_LIB := $(shell basename `pwd`)
endif

ifneq ($(SRC_DIR),)
    SOURCES = $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.c))
endif

SOURCES += $(SRC)

OBJS = $(foreach dir,$(patsubst %.c, %.o, $(SOURCES)), $(OBJ_DIR)/$(dir))

ifneq ($(SUBDIR),)
SUB_DIR_LIBS = $(foreach dir,$(SUBDIR), $(dir)/$(OBJ_DIR)/$(shell basename $(dir)).a)
endif

#$(info selective source files List : $(SRC))
#$(info source file directory       : $(SRC_DIR))
#$(info All source file list        : $(SOURCES))
#$(info All target object files     : $(OBJS))
#$(info All target lib files        : $(SUB_DIR_LIBS))

DEPS = $(OBJS:.o=.d)

# Command to invoke compilation in sub-directories
subdir_clean:
	$(HIDE)for i in $(SUBDIR); do \
	    $(MAKE) clean -C $$i;\
	    done
# Command to invoke compilation in sub-directories
subdir_all:
	$(HIDE)for i in $(SUBDIR); do \
	    $(MAKE) all -C $$i;\
	    done
lib: subdir_all
	$(HIDE)$(MKDIR) $(OBJ_DIR)
	$(HIDE)$(AR) $(OBJ_DIR)/$(TARGET_LIB).a $(SUB_DIR_LIBS)

# Command to compile source files to intermediate object files
all:$(OBJS)
	$(HIDE)$(MKDIR) $(OBJ_DIR)
ifneq ($(SUBDIR),)
	$(HIDE)$(MAKE) subdir_all
endif
#	$(HIDE)$(AR) $(OBJ_DIR)/$(TARGET_LIB).a $^ $(SUB_DIR_LIBS)

# Command to delete intermediate object files
clean:
ifneq ($(SUBDIR),)
	$(HIDE)$(MAKE) subdir_clean
endif
	$(HIDE)$(RM) $(OBJ_DIR)

-include $(DEPS)

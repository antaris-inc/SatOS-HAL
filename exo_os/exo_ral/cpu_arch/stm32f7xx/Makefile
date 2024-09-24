#
#   @copyright Copyright 2024 Antaris, Inc.
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
#

TOP_DIR=../../../../
include $(TOP_DIR)Makefile.def

##############################################################################
# All variables here intensionally set to empty, User should not modify here

SRC =
SRC_DIR =
SUBDIR =

##############################################################################
# List of include file directories required for compilation
INCLUDES = -Iinc/\
	   -I$(TOP_DIR)/drivers/ahw_drivers/eps/inc/\
	   -I$(TOP_DIR)/exo_services/eps_ctrlr/inc/\
	   -I$(TOP_DIR)/exo_stack/lwip/app/\
	   -I$(TOP_DIR)/exo_stack/lwip/src/include\
	   -I$(TOP_DIR)/exo_lib/adcs_intf/inc/\
	   -I$(TOP_DIR)/exo_stack/lwip/src/apps\
	   -I$(TOP_DIR)/exo_stack/lwip/system/arch\
	   -I$(TOP_DIR)/exo_stack/lwip/target/\
	   -I$(TOP_DIR)/exo_stack/usb_device/app_ecm/\
	   -I$(TOP_DIR)/exo_stack/usb_device/stm32_usb_device_library/core_ecm/Inc/\
	   -I$(TOP_DIR)/exo_stack/usb_device/app_ecm/\
	   -I$(TOP_DIR)/exo_stack/usb_device/target_ecm/\
	   -I$(TOP_DIR)/exo_stack/usb_device/stm32_usb_device_library/class/cdc/Inc/\
	   -I$(TOP_DIR)/exo_stack/usb_device/stm32_usb_device_library/class/cdc_ecm/Inc/\
	   -I$(TOP_DIR)/includes/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/common/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/rcc/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/rtc/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/timer/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/gpio/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/dma/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/cortex/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/i2c/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/pwr/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/uart/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/flash/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/exti/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/can/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/spi/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/qspi/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/tmr/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/usb/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/ethernet/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/fmc/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/nor_flash/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/sdram/inc/\
	   -I$(TOP_DIR)/drivers/io_drivers/io_drivers_stm32f7xx/wdg/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_hal_fw_common/common/inc/\
	   -I$(TOP_DIR)/drivers/ut/inc/\
	   -I$(TOP_DIR)/exo_os/rtos/free_rtos/CMSIS_RTOS_V2/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/common/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/uart/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/i2c/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/spi/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/usb/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/can/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/rtc/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/ethernet/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/fmc_nor_flash/inc/\
	   -I$(TOP_DIR)/exo_os/rtos/free_rtos/include/\
	   -I$(TOP_DIR)/exo_os/rtos/free_rtos/portable/GCC/ARM_CM7/r0p1/\
	   -I$(TOP_DIR)/exo_os/exo_ral/exo_ral_common/inc/\
	   -I$(TOP_DIR)/exo_os/ut/inc/\
	   -I$(TOP_DIR)/exo_os/exo_osal/exo_osal_common/inc/\
	   -I$(TOP_DIR)/exo_os/exo_osal/ipc_mbmr/inc/\
	   -I$(TOP_DIR)/exo_os/exo_osal/memory_management/inc/\
	   -I$(TOP_DIR)/exo_os/exo_osal/task_management/inc/\
	   -I$(TOP_DIR)exo_stack/lwip/src/include/compat/posix/\
	   -I$(TOP_DIR)drivers/sensor_intf/common/inc/\
	   -I$(TOP_DIR)drivers/sensor_intf/digital_thermostat/inc/\
	   -I$(TOP_DIR)drivers/sensor_intf/hot_swp_cntlr/inc/\
	   -I$(TOP_DIR)drivers/sensor_intf/temp_sensor/inc/\
	   -I$(TOP_DIR)drivers/sensor_intf/Voltage_sequencer/inc/\
	   -I$(TOP_DIR)drivers/sensor_intf/Power_sensor_monitor/inc/\
	   -I$(TOP_DIR)exo_stack/libcsp/include/csp/\
	   -I$(TOP_DIR)exo_stack/libcsp/include/\
	   -I$(TOP_DIR)exo_stack/libcsp/include/csp/interfaces/\
	   -I$(TOP_DIR)exo_stack/libcsp/include/csp/drivers/\
	   -I$(TOP_DIR)exo_stack/libcsp/include/csp/crypto/\
	   -I$(TOP_DIR)exo_stack/libcsp/include/csp/arch/\
	   -I$(TOP_DIR)exo_stack/libcsp/src/\
	   -I$(TOP_DIR)exo_stack/libcsp/src/transport/\
	   -I$(TOP_DIR)exo_stack/libcsp/src/rtable/\
	   -I$(TOP_DIR)exo_stack/libcsp/src/interfaces/\
	   -I$(TOP_DIR)exo_stack/libcsp/src/arch/\
	   -I$(TOP_DIR)exo_stack/libcsp/src/arch/wrap\
	   -I$(TOP_DIR)/drivers/ahw_drivers/data_logger/ads7828/inc/\
	   -I$(TOP_DIR)/drivers/ahw_drivers/digital_thermostat/ds620/inc/\
	   -I$(TOP_DIR)/drivers/ahw_drivers/gpio_expander/mcp23008/inc/\
	   -I$(TOP_DIR)/drivers/ahw_drivers/gpio_expander/pcal6408a/inc/\
	   -I$(TOP_DIR)/drivers/ahw_drivers/imu/bmx160/inc/\
	   -I$(TOP_DIR)/drivers/ahw_drivers/power_sense_monitor/ina230/inc/\
	   -I$(TOP_DIR)/drivers/ahw_drivers/temp_sensor/mcp9843/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/imu/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/data_acq_dvc/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/digital_thermostat/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/gpio_expander/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/psm/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/temp_sensor/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/voltage_sequencer/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/hot_swp_cntlr/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_ahw_al_driver_api/exo_ahw_al_common/common/inc/\
	   -I$(TOP_DIR)drivers/ahw_drivers/memory_drivers/qspi_s25hl512t/inc/\
	   -I$(TOP_DIR)/exo_lib/security/mbedtls/include\
	   -I$(TOP_DIR)/exo_lib/file_transfer/inc\
           -I$(TOP_DIR)/exo_lib/security/hmac/src/\
           -I$(TOP_DIR)/exo_lib/security/libcrc-2.0/include\
	   -I$(TOP_DIR)/exo_services/comms_ctrlr/uhf/inc/\
	   -I$(TOP_DIR)/drivers/exo_hal_driver_fw/exo_io_al_driver_api/exo_io_al_common/gpio/inc/\
	   
ifneq ($(BOARD),)
    ifeq ($(BOARD),GEN1)
        INCLUDES += \
            -I$(TOP_DIR)drivers/bsp/gen1/inc/
    else ifeq ($(BOARD),STM32_DISCO_F769NI)
        INCLUDES += \
            -I$(TOP_DIR)drivers/bsp/stm32_disco_f769ni/inc/
    endif
endif
	   

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

ifeq ($(BOARD),GEN1)
    SRC += src/startup_stm32f765nihx.s
else ifeq ($(BOARD),STM32_DISCO_F769NI)
    SRC += src/startup_stm32f769nihx.s
endif

##############################################################################

ifeq ($(TARGET_LIB),)
TARGET_LIB := $(shell basename `pwd`)
endif

ifneq ($(SRC_DIR),)
    SOURCES = $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.c))
endif

SOURCES += $(SRC)

OBJS1 = $(foreach dir,$(patsubst %.c, %.o, $(SOURCES)), $(OBJ_DIR)/$(dir))

OBJS = $(foreach dir,$(patsubst %.s, %.o, $(OBJS1)), $(dir))

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

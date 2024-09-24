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
TOP_DIR=../../
include $(TOP_DIR)Makefile.def

##############################################################################
# All variables here intensionally set to empty, User should not modify here

SRC =
SRC_DIR =
SUBDIR =

##############################################################################
# List of include file directories required for compilation
INCLUDES =

##############################################################################
#Current Folder target name, usually current folder name
#TARGET_LIB = target_name

# List of source files required for compilation using SRC
# mention the directory path where all C files to be compiled usig SRC_DIR
# Mention Sub director makefile compilation using SUBDIR

SUBDIR += uhf

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

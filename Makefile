# Template taken from:
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

#------------------------------------------------------------------------------
# Project parameters.

TARGET_LIB ?= libexparser

LIB_DIR ?= ./lib
BUILD_DIR ?= ./build

SRC_INCL ?= ./include

SRC_DIRS ?= ./src

LDFLAGS += -lm
ARFLAGS = rcs

#------------------------------------------------------------------------------
# Search for project files.

SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_DIRS += $(SRC_INCL)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=iso9899:1999

#------------------------------------------------------------------------------
# Library extensions.

ifeq ($(OS), Windows_NT)
	STLEXT := lib
else
	STLEXT := a
endif

#------------------------------------------------------------------------------
# Main targets.

all: \
  $(BUILD_DIR)/$(LIB_DIR)/$(TARGET_LIB).$(STLEXT)

$(BUILD_DIR)/$(LIB_DIR)/$(TARGET_LIB).$(STLEXT): $(OBJS)
	$(MKDIR_P) $(dir $@)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#------------------------------------------------------------------------------
# Implicit rules.

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC_INCL_FLAGS) -c $< -o $@

#------------------------------------------------------------------------------
# Cleaning rules.

.PHONY: all clean

clean:
	$(RM) -r $(BUILD_DIR)

#------------------------------------------------------------------------------
# Misc.

-include $(DEPS)
MKDIR_P ?= mkdir -p

# Template taken from:
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

#------------------------------------------------------------------------------
# Project parameters.

TARGET_LIB ?= libexparser

BUILD_DIR ?= ./build
LIB_DIR ?= ./lib

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
	SHLEXT := dll
else
	STLEXT := a
	SHLEXT := so
endif

#------------------------------------------------------------------------------
# Main targets.

all: \
  $(BUILD_DIR)/$(LIB_DIR)/$(TARGET_LIB).$(STLEXT) \
  $(BUILD_DIR)/$(LIB_DIR)/$(TARGET_LIB).$(SHLEXT)

$(BUILD_DIR)/$(LIB_DIR)/$(TARGET_LIB).$(STLEXT): $(OBJS)
	$(MKDIR_P) $(dir $@)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(BUILD_DIR)/$(LIB_DIR)/$(TARGET_LIB).$(SHLEXT): $(OBJS)
	$(MKDIR_P) $(dir $@)
	$(CC) -shared -o $@ $(OBJS) $(LDFLAGS)

#------------------------------------------------------------------------------
# Implicit rules.

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC_INCL_FLAGS) -c $< -o $@ -fPIC

#------------------------------------------------------------------------------
# Cleaning rules.

.PHONY: all clean

clean:
	$(RM) -r $(BUILD_DIR)

#------------------------------------------------------------------------------
# Misc.

-include $(DEPS)
MKDIR_P ?= mkdir -p

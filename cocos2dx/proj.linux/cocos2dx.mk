################################################################################
#
# LINUX MAKEFILE
#
# Available options are:
# - CLANG=1  : Compiles with clang instead of gcc. Clang must be in your PATH.
# - V=1      : Enables the verbose mode.
# - DEBUG=1  : Enables the debug mode, disable compiler optimizations.
# - OPENAL=1 : Uses OpenAL instead of FMOD as sound engine.
#
################################################################################

all:

# Remove -Wall, because it enables -Wunused-function, and this warning exists in webp.h
# when enable c++11. I don't know why.
# GCC 4.6 is primary platform for cocos2d v.3, because it's default compiler for Android, 
# Blackberry, some Linux distributions.It supports all important features of c++11, but have 
# no flag "-std=c++11" (which was turned on in version 4.7).
CCFLAGS  += -MMD -Wno-deprecated-declarations -fPIC
CXXFLAGS += -MMD -Wno-deprecated-declarations -fPIC -std=gnu++0x

ifeq ($(CLANG), 1)
CC := clang
CXX := clang++
DEFINES += -D__STRICT_ANSI__ # Allows clang 3.3 to use __float128
else
CC = gcc
CXX = g++
CCFLAGS  += -Werror
CXXFLAGS += -Werror
endif

ARFLAGS = cr

DEFINES += -DLINUX -DCC_KEYBOARD_SUPPORT

ifdef USE_BOX2D
DEFINES += -DCC_ENABLE_BOX2D_INTEGRATION=1
else
DEFINES += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
endif

THIS_MAKEFILE := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
ifndef COCOS_ROOT
COCOS_ROOT := $(realpath $(dir $(THIS_MAKEFILE))/../..)
endif
COCOS_SRC = $(COCOS_ROOT)/cocos2dx
OBJ_DIR ?= obj

LIB_DIR = $(COCOS_ROOT)/lib/linux
BIN_DIR = bin

INCLUDES +=  \
    -I$(COCOS_SRC) \
    -I$(COCOS_SRC)/cocoa \
    -I$(COCOS_SRC)/include \
    -I$(COCOS_SRC)/kazmath/include \
    -I$(COCOS_SRC)/platform/linux \
    -I$(COCOS_SRC)/platform/third_party/linux/libjpeg \
    -I$(COCOS_SRC)/platform/third_party/linux/libtiff \
    -I$(COCOS_SRC)/platform/third_party/linux/libwebp

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
INCLUDES += -I$(COCOS_SRC)/platform/third_party/linux/include64
else
INCLUDES += -I$(COCOS_SRC)/platform/third_party/linux
endif

ifeq ($(DEBUG), 1)
CCFLAGS += -g3 -O0
CXXFLAGS += -g3 -O0
DEFINES += -D_DEBUG -DCOCOS2D_DEBUG=1
OBJ_DIR := $(OBJ_DIR)/debug
LIB_DIR := $(LIB_DIR)/debug
BIN_DIR := $(BIN_DIR)/debug
else
CCFLAGS += -O3
CXXFLAGS += -O3
DEFINES += -DNDEBUG
OBJ_DIR := $(OBJ_DIR)/release
LIB_DIR := $(LIB_DIR)/release
BIN_DIR := $(BIN_DIR)/release
endif

ifndef V
LOG_CC = @echo " CC $@";
LOG_CXX = @echo " CXX $@";
LOG_AR = @echo " AR $@";
LOG_LINK = @echo " LINK $@";
endif

OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)
OBJECTS := $(subst ../,,$(OBJECTS))
OBJECTS := $(subst $(COCOS_ROOT)/,,$(OBJECTS))
OBJECTS := $(addprefix $(OBJ_DIR)/, $(OBJECTS))
DEPS = $(OBJECTS:.o=.d)
CORE_MAKEFILE_LIST := $(MAKEFILE_LIST)
-include $(DEPS)

ifeq ($(LBITS),64)
STATICLIBS_DIR = $(COCOS_SRC)/platform/third_party/linux/libraries/lib64
else
STATICLIBS_DIR = $(COCOS_SRC)/platform/third_party/linux/libraries
endif
STATICLIBS = $(STATICLIBS_DIR)/libfreetype.a \
    $(STATICLIBS_DIR)/libjpeg.a \
    $(STATICLIBS_DIR)/libtiff.a \
    $(STATICLIBS_DIR)/libwebp.a

ifneq ($(OPENAL),1)
ifeq ($(LBITS),64)
FMOD_LIBDIR = $(COCOS_ROOT)/CocosDenshion/third_party/fmod/lib64/api/lib
SHAREDLIBS += -lfmodex64
else
FMOD_LIBDIR = $(COCOS_ROOT)/CocosDenshion/third_party/fmod/api/lib
SHAREDLIBS += -lfmodex
endif
endif

SHAREDLIBS += -lGLEW -lfontconfig -lpthread -lGL -lpng `pkg-config --libs glfw3`
SHAREDLIBS += -L$(FMOD_LIBDIR) -Wl,-rpath,$(abspath $(FMOD_LIBDIR))
SHAREDLIBS += -L$(LIB_DIR) -Wl,-rpath,$(abspath $(LIB_DIR))

LIBS = -lrt -lz -lX11

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET) core

.PHONY: all clean

# If the parent Makefile defines $(EXECUTABLE) then define this as the target
# and create a 'make run' rule to run the app.
ifdef EXECUTABLE
TARGET := $(BIN_DIR)/$(EXECUTABLE)

all: $(TARGET)

run: $(TARGET)
	cd $(dir $^) && ./$(notdir $^)

.PHONY: run
endif

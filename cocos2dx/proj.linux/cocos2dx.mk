all:

CC = gcc
CXX = g++
CCFLAGS += -MMD -Wall -Werror -fPIC
CXXFLAGS += -MMD -Wall -Werror -fPIC
ARFLAGS = cr

DEFINES += -DLINUX

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
    -I$(COCOS_SRC)/platform/third_party/linux/libpng \
    -I$(COCOS_SRC)/platform/third_party/linux/libjpeg \
    -I$(COCOS_SRC)/platform/third_party/linux/libtiff/include \
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
    $(STATICLIBS_DIR)/libpng.a \
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

SHAREDLIBS += -lglfw -lGLEW -lfontconfig -lpthread -lGL
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

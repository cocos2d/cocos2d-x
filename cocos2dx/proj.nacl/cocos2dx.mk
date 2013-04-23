# This makefile is included by each of the cocos2d-x libraries and examples
# when building for Native Client.  It defines a set of variables that all
# cocos2dx projects have in common.

all:

NACL_LIBC = newlib
NACL_ARCH ?= x86_64
NACL_AR ?= $(NACL_ARCH)-nacl-ar
NACL_CC ?= $(NACL_ARCH)-nacl-gcc
NACL_CXX ?= $(NACL_ARCH)-nacl-g++
CCFLAGS += -Wall -Werror
CXXFLAGS += -Wall -Werror
ARFLAGS = cr

THIS_MAKEFILE := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))

# The top level of the cocos2dx-x source tree.  The parent Makefile will
# often define this, but in case is doesn't we can find it relative to
# THIS_MAKEFILE
ifndef COCOS_ROOT
COCOS_ROOT := $(realpath $(dir $(THIS_MAKEFILE))/../..)
endif
COCOS_SRC := $(COCOS_ROOT)/cocos2dx

ifeq ($(NACL_ARCH), i686)
ARCH_DIR := $(NACL_LIBC)_x86_32
else
ARCH_DIR := $(NACL_LIBC)_$(NACL_ARCH)
endif

NACLPORTS_ROOT ?= $(NACL_SDK_ROOT)/ports
NACLPORTS_INCLUDE ?= $(NACLPORTS_ROOT)/include
OUT_DIR ?= obj
OBJ_DIR ?= $(OUT_DIR)/$(NACL_ARCH)
LIB_DIR ?= $(COCOS_ROOT)/lib/nacl/$(ARCH_DIR)

ifdef USE_BOX2D
DEFINES += -DCC_ENABLE_BOX2D_INTEGRATION=1
else
DEFINES += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
endif

INCLUDES += -I$(COCOS_SRC) \
	-I$(COCOS_SRC)/cocoa \
	-I$(COCOS_SRC)/include \
	-I$(COCOS_SRC)/kazmath/include \
	-I$(COCOS_SRC)/platform \
	-I$(COCOS_SRC)/platform/nacl \
	-I$(NACL_SDK_ROOT)/include \
	-isystem $(NACLPORTS_INCLUDE) \
	-isystem $(NACLPORTS_INCLUDE)/libxml2

ifeq ($(DEBUG), 1)
BIN_DIR = bin/debug
CCFLAGS += -g3 -O0
CXXFLAGS += -g3 -O0
LIB_DIR := $(LIB_DIR)/Debug
OBJ_DIR := $(OBJ_DIR)/Debug
MULTILIB_SUFFIX := $(ARCH_DIR)/Debug
DEFINES += -D_DEBUG -DCOCOS2D_DEBUG=1
else
BIN_DIR = bin/release
CCFLAGS += -O3
CXXFLAGS += -O3
LIB_DIR := $(LIB_DIR)/Release
OBJ_DIR := $(OBJ_DIR)/Release
MULTILIB_SUFFIX := $(ARCH_DIR)/Release
DEFINES += -DNDEBUG
endif

ifndef V
LOG_CC = @echo " CC $@";
LOG_CXX = @echo " CXX $@";
LOG_AR = @echo " AR $@";
LOG_LINK = @echo " LINK $@";
endif

# The default library search path consists of the cocos2dx library path, the
# main nacl sdk library path and the naclports library path.
LDFLAGS += -L$(LIB_DIR)
LDFLAGS += -L$(NACL_SDK_ROOT)/lib/$(MULTILIB_SUFFIX)
LDFLAGS += -L$(NACLPORTS_ROOT)/lib/$(MULTILIB_SUFFIX)

# Some cococs sources use #pragma mark
CCFLAGS += -Wno-unknown-pragmas
CXXFLAGS += -Wno-unknown-pragmas

ifeq ($(NACL_ARCH),arm)
# Don't warn about mangling of 'va_list' on arm builds
CCFLAGS += -Wno-psabi
CXXFLAGS += -Wno-psabi
endif

ifdef NACL_MOUNTS
DEFINES += -DOLD_NACL_MOUNTS
STATICLIBS += -lnacl-mounts
else
STATICLIBS += -lnacl_io
endif

SOUNDLIBS := -lalut -lopenal -lvorbisfile -lvorbis -logg
STATICLIBS += $(SOUNDLIBS) -lfreetype -lxml2 -lwebp -lpng -ljpeg -ltiff -llua
STATICLIBS += -lppapi_gles2 -lppapi -lppapi_cpp -lnosys
SHAREDLIBS += -lpthread -lcocosdenshion -lcocos2d -lz

OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)
OBJECTS := $(subst ../,,$(OBJECTS))
OBJECTS := $(subst $(COCOS_ROOT)/,,$(OBJECTS))
OBJECTS := $(addprefix $(OBJ_DIR)/, $(OBJECTS))
DEPS = $(OBJECTS:.o=.d)
CORE_MAKEFILE_LIST := $(MAKEFILE_LIST)
-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET) core

.PHONY: all clean

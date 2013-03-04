NACL_ARCH ?= x86_64
NACL_LIBC = newlib
NACL_AR ?= $(NACL_ARCH)-nacl-ar
NACL_CC ?= $(NACL_ARCH)-nacl-gcc
NACL_CXX ?= $(NACL_ARCH)-nacl-g++
CCFLAGS = -Wall
CXXFLAGS = -Wall
VISIBILITY =
ARFLAGS = cr

LIBS =

INCLUDES = -I.. -I../lua

NACLPORTS_INCLUDE ?= $(NACL_SDK_ROOT)/toolchain/linux_x86_$(NACL_LIBC)/$(NACL_ARCH)-nacl/usr/include
INCLUDES += -I$(NACL_SDK_ROOT)/include
INCLUDES += -I$(NACLPORTS_INCLUDE)


SOURCES = ../lua/lapi.c \
          ../lua/lauxlib.c \
          ../lua/lbaselib.c \
          ../lua/lcode.c \
          ../lua/ldblib.c \
          ../lua/ldebug.c \
          ../lua/ldo.c \
          ../lua/ldump.c \
          ../lua/lfunc.c \
          ../lua/lgc.c \
          ../lua/linit.c \
          ../lua/liolib.c \
          ../lua/llex.c \
          ../lua/lmathlib.c \
          ../lua/lmem.c \
          ../lua/loadlib.c \
          ../lua/lobject.c \
          ../lua/lopcodes.c \
          ../lua/loslib.c \
          ../lua/lparser.c \
          ../lua/lstate.c \
          ../lua/lstring.c \
          ../lua/lstrlib.c \
          ../lua/ltable.c \
          ../lua/ltablib.c \
          ../lua/ltm.c \
          ../lua/lua.c \
          ../lua/lundump.c \
          ../lua/lvm.c \
          ../lua/lzio.c \
          ../lua/print.c \
          ../tolua/tolua_event.c \
          ../tolua/tolua_is.c \
          ../tolua/tolua_map.c \
          ../tolua/tolua_push.c \
          ../tolua/tolua_to.c

COCOS_ROOT = ../../..

include $(COCOS_ROOT)/cocos2dx/proj.nacl/cocos2dx.mk

TARGET	= $(LIB_DIR)/liblua.a

####### Build rules
$(TARGET): $(OBJECTS)
	$(NACL_AR) $(ARFLAGS) $(TARGET) $(OBJECTS)

####### Compile
$(OBJ_DIR)/%.o: ../%.c
	@mkdir -p $(@D)
	$(NACL_CC) -MMD $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET) core

-include $(DEPS)

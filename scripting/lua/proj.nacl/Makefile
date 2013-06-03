INCLUDES = -I.. -I../lua -I../../../extensions -I../../../external/chipmunk/include/chipmunk

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
          ../lua/lundump.c \
          ../lua/lvm.c \
          ../lua/lzio.c \
          ../lua/print.c \
          ../tolua/tolua_event.c \
          ../tolua/tolua_is.c \
          ../tolua/tolua_map.c \
          ../tolua/tolua_push.c \
          ../tolua/tolua_to.c \
          ../cocos2dx_support/tolua_fix.c \
          ../cocos2dx_support/CCLuaBridge.cpp \
          ../cocos2dx_support/CCLuaEngine.cpp \
          ../cocos2dx_support/CCLuaStack.cpp \
          ../cocos2dx_support/CCLuaValue.cpp \
          ../cocos2dx_support/Cocos2dxLuaLoader.cpp \
          ../cocos2dx_support/LuaCocos2d.cpp \
          ../cocos2dx_support/CCBProxy.cpp \
          ../cocos2dx_support/Lua_extensions_CCB.cpp \

COCOS_ROOT = ../../..

include $(COCOS_ROOT)/cocos2dx/proj.nacl/cocos2dx.mk

CCFLAGS = -Wno-uninitialized

TARGET = $(LIB_DIR)/liblua.a
all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	$(LOG_AR)$(NACL_AR) $(ARFLAGS) $(TARGET) $(OBJECTS)

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(NACL_CC) -MMD $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

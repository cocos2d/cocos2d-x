TARGET = liblua.so

INCLUDES += -I.. -I../lua -I../tolua -I../cocos2dx_support -I../../auto-generated/lua-bindings \
        -I../Classes -I../../../CocosDenshion/include -I../../../extensions -I../../../external/chipmunk/include/chipmunk

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
          ../../auto-generated/lua-bindings/lua_cocos2dx_auto.cpp \
          ../../auto-generated/lua-bindings/lua_cocos2dx_extension_auto.cpp \
          ../cocos2dx_support/CCLuaBridge.cpp \
          ../cocos2dx_support/CCLuaEngine.cpp \
          ../cocos2dx_support/CCLuaStack.cpp \
          ../cocos2dx_support/CCLuaValue.cpp \
          ../cocos2dx_support/Cocos2dxLuaLoader.cpp \
          ../cocos2dx_support/CCBProxy.cpp \
          ../cocos2dx_support/LuaOpengl.cpp \
          ../cocos2dx_support/LuaScriptHandlerMgr.cpp \
          ../cocos2dx_support/LuaBasicConversions.cpp \
          ../cocos2dx_support/lua_cocos2dx_manual.cpp \
          ../cocos2dx_support/lua_cocos2dx_extension_manual.cpp \
          ../cocos2dx_support/lua_cocos2dx_deprecated.cpp


include ../../../cocos2dx/proj.linux/cocos2dx.mk

TARGET := $(LIB_DIR)/$(TARGET)
SHAREDLIBS += -lextension

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -shared -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: ../../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

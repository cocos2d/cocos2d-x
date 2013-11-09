TARGET = liblua.so

INCLUDES += -I../../../../external/lua/tolua \
-I../../../../external/lua/lua \
-I../../auto-generated/lua-bindings \
-I../../../../extensions \
-I../../../editor-support \
-I. \
-I../../../editor-support/cocosbuilder \
-I../../../editor-support/cocostudio \
-I../../../../external \
-I../../../

SOURCES = ../../../../external/lua/lua/lapi.c \
          ../../../../external/lua/lua/lauxlib.c \
          ../../../../external/lua/lua/lbaselib.c \
          ../../../../external/lua/lua/lcode.c \
          ../../../../external/lua/lua/ldblib.c \
          ../../../../external/lua/lua/ldebug.c \
          ../../../../external/lua/lua/ldo.c \
          ../../../../external/lua/lua/ldump.c \
          ../../../../external/lua/lua/lfunc.c \
          ../../../../external/lua/lua/lgc.c \
          ../../../../external/lua/lua/linit.c \
          ../../../../external/lua/lua/liolib.c \
          ../../../../external/lua/lua/llex.c \
          ../../../../external/lua/lua/lmathlib.c \
          ../../../../external/lua/lua/lmem.c \
          ../../../../external/lua/lua/loadlib.c \
          ../../../../external/lua/lua/lobject.c \
          ../../../../external/lua/lua/lopcodes.c \
          ../../../../external/lua/lua/loslib.c \
          ../../../../external/lua/lua/lparser.c \
          ../../../../external/lua/lua/lstate.c \
          ../../../../external/lua/lua/lstring.c \
          ../../../../external/lua/lua/lstrlib.c \
          ../../../../external/lua/lua/ltable.c \
          ../../../../external/lua/lua/ltablib.c \
          ../../../../external/lua/lua/ltm.c \
          ../../../../external/lua/lua/lundump.c \
          ../../../../external/lua/lua/lvm.c \
          ../../../../external/lua/lua/lzio.c \
          ../../../../external/lua/lua/print.c \
          ../../../../external/lua/tolua/tolua_event.c \
          ../../../../external/lua/tolua/tolua_is.c \
          ../../../../external/lua/tolua/tolua_map.c \
          ../../../../external/lua/tolua/tolua_push.c \
          ../../../../external/lua/tolua/tolua_to.c \
          tolua_fix.c \
          ../../auto-generated/lua-bindings/lua_cocos2dx_auto.cpp \
          ../../auto-generated/lua-bindings/lua_cocos2dx_extension_auto.cpp \
          ../../auto-generated/lua-bindings/lua_cocos2dx_studio_auto.cpp \
          CCLuaBridge.cpp \
          CCLuaEngine.cpp \
          CCLuaStack.cpp \
          CCLuaValue.cpp \
          Cocos2dxLuaLoader.cpp \
          CCBProxy.cpp \
          LuaOpengl.cpp \
          LuaScriptHandlerMgr.cpp \
          LuaBasicConversions.cpp \
          lua_cocos2dx_manual.cpp \
          lua_cocos2dx_extension_manual.cpp \
          lua_cocos2dx_deprecated.cpp \
          lua_xml_http_request.cpp


include ../../../2d/cocos2dx.mk

TARGET := $(LIB_DIR)/$(TARGET)
SHAREDLIBS += -lextension -lcocostudio -lcocosbuilder
STATICLIBS += $(LIB_DIR)/libbox2d.a

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -shared -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../../../../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

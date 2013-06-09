COCOS_ROOT = ../../../../
COCOS2DX_PATH = $(COCOS_ROOT)/cocos2dx

INCLUDES =  -I.. \
	-I../Classes \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I$(COCOS_ROOT)/scripting/lua/lua \
	-I$(COCOS_ROOT)/scripting/lua/tolua \
	-I$(COCOS_ROOT)/scripting/lua/cocos2dx_support \
	-I$(NACL_SDK_ROOT)/include \
	-I$(COCOS_ROOT)/external \
	-I$(COCOS_ROOT)/external/chipmunk/include/chipmunk \
	-I$(COCOS_ROOT)/extensions \
	-I$(COCOS_ROOT)/extensions/Components

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        $(COCOS_ROOT)/scripting/lua/cocos2dx_support/CCLuaEngine.cpp \
        $(COCOS_ROOT)/scripting/lua/cocos2dx_support/CCLuaStack.cpp \
        $(COCOS_ROOT)/scripting/lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \
        $(COCOS_ROOT)/scripting/lua/cocos2dx_support/LuaCocos2d.cpp \
        $(COCOS_ROOT)/scripting/lua/cocos2dx_support/tolua_fix.c \
        $(COCOS_ROOT)/scripting/lua/cocos2dx_support/CCBProxy.cpp \
        $(COCOS_ROOT)/scripting/lua/cocos2dx_support/Lua_extensions_CCB.cpp

include $(COCOS2DX_PATH)/../extensions/proj.nacl/Makefile
SOURCES += $(addprefix $(COCOS_ROOT)/extensions/, $(EXTENSIONS_SOURCES))

include $(COCOS_ROOT)/cocos2dx/proj.nacl/cocos2dx.mk

CXXFLAGS   += -Wno-multichar
STATICLIBS += -llua -lnosys
SHAREDLIBS += -lbox2d

APP_NAME = TestLua
TARGET = $(BIN_DIR)/$(APP_NAME)_$(NACL_ARCH).nexe
NMF = $(BIN_DIR)/$(APP_NAME).nmf

all: $(NMF)

$(TARGET): $(OBJECTS) $(LIB_DIR)/libcocos2d.a
	@mkdir -p $(@D)
	$(LOG_LINK)$(NACL_CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(LOG_CXX)$(NACL_CXX) -MMD $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp
	@mkdir -p $(@D)
	$(LOG_CXX)$(NACL_CXX) -MMD $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: $(COCOS_ROOT)/%.cpp
	@mkdir -p $(@D)
	$(LOG_CXX)$(NACL_CXX) -MMD $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: $(COCOS_ROOT)/%.c
	@mkdir -p $(@D)
	$(LOG_CC)$(NACL_CC) -MMD $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(NMF): $(TARGET)
	$(NACL_SDK_ROOT)/tools/create_nmf.py -o $@ $(BIN_DIR)/*.nexe --objdump=i686-nacl-objdump -L$(NACL_SDK_ROOT)/toolchain/linux_x86_newlib/x86_64-nacl/lib/ -s $(BIN_DIR)

run: all
	/bin/cp -ar ../Resources/ .
	$(NACL_SDK_ROOT)/tools/httpd.py --no_dir_check

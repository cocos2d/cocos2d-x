LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_lua_static

LOCAL_MODULE_FILENAME := liblua

LOCAL_SRC_FILES :=../../lua/lapi.c \
                  ../../lua/lauxlib.c \
          ../../lua/lbaselib.c \
          ../../lua/lcode.c \
          ../../lua/ldblib.c \
          ../../lua/ldebug.c \
          ../../lua/ldo.c \
          ../../lua/ldump.c \
          ../../lua/lfunc.c \
          ../../lua/lgc.c \
          ../../lua/linit.c \
          ../../lua/liolib.c \
          ../../lua/llex.c \
          ../../lua/lmathlib.c \
          ../../lua/lmem.c \
          ../../lua/loadlib.c \
          ../../lua/lobject.c \
          ../../lua/lopcodes.c \
          ../../lua/loslib.c \
          ../../lua/lparser.c \
          ../../lua/lstate.c \
          ../../lua/lstring.c \
          ../../lua/lstrlib.c \
          ../../lua/ltable.c \
          ../../lua/ltablib.c \
          ../../lua/ltm.c \
          ../../lua/lua.c \
          ../../lua/lundump.c \
          ../../lua/lvm.c \
          ../../lua/lzio.c \
          ../../lua/print.c \
          ../../tolua/tolua_event.c \
          ../../tolua/tolua_is.c \
          ../../tolua/tolua_map.c \
          ../../tolua/tolua_push.c \
          ../../tolua/tolua_to.c \
          ../../cocos2dx_support/CCLuaBridge.cpp \
          ../../cocos2dx_support/CCLuaEngine.cpp \
          ../../cocos2dx_support/CCLuaStack.cpp \
          ../../cocos2dx_support/CCLuaValue.cpp \
          ../../cocos2dx_support/Cocos2dxLuaLoader.cpp \
          ../../cocos2dx_support/LuaCocos2d.cpp \
          ../../cocos2dx_support/tolua_fix.c
          
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../lua \
                           $(LOCAL_PATH)/../../tolua \
                           $(LOCAL_PATH)/../../cocos2dx_support 
          
          
LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/../../lua \
                    $(LOCAL_PATH)/../../tolua \
                    $(LOCAL_PATH)/../../../../cocos2dx \
                    $(LOCAL_PATH)/../../../../cocos2dx/include \
                    $(LOCAL_PATH)/../../../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../../../cocos2dx/platform/android \
                    $(LOCAL_PATH)/../../../../cocos2dx/kazmath/include \
                    $(LOCAL_PATH)/../../../../CocosDenshion/include
                    
LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

include $(BUILD_STATIC_LIBRARY)
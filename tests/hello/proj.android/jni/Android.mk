LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
    ../../sources/AppDelegate.cpp \
    ../../sources/SimulatorConfig.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../sources

COCOS2DX_ROOT := $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/cocos
LOCAL_C_INCLUDES += $(COCOS2DX_ROOT) \
                    $(COCOS2DX_ROOT)/platform/android \
                    $(COCOS2DX_ROOT)/../external/tinyxml2 \
                    $(COCOS2DX_ROOT)/../external/unzip \
                    $(COCOS2DX_ROOT)/../external/chipmunk/include/chipmunk \
                    $(COCOS2DX_ROOT)/../external/edtaa3func \
                    $(COCOS2DX_ROOT)/../external/xxhash \
                    $(COCOS2DX_ROOT)/../external/ConvertUTF \
                    $(COCOS2DX_ROOT)/base \
                    $(COCOS2DX_ROOT)/audio/include

LUA_STATIC_ROOT := $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/cocos/scripting/lua-bindings
LOCAL_C_INCLUDES += $(LUA_STATIC_ROOT)/../../../external/lua/tolua \
                    $(LUA_STATIC_ROOT)/../../../external/lua/luajit/include \
                    $(LUA_STATIC_ROOT)/../../../external/lua \
                    $(LUA_STATIC_ROOT)/../../../extensions \
                    $(LUA_STATIC_ROOT)/../../editor-support/spine \
                    $(LUA_STATIC_ROOT)/../../editor-support/cocosbuilder \
                    $(LUA_STATIC_ROOT)/../../editor-support/cocostudio \
                    $(LUA_STATIC_ROOT)/../../ui \
                    $(LUA_STATIC_ROOT)/auto \
                    $(LUA_STATIC_ROOT)/manual \
                    $(LUA_STATIC_ROOT)/manual/platform/android \
                    $(LUA_STATIC_ROOT)/manual/platform/android/jni \
                    $(LUA_STATIC_ROOT)/../../../external/xxtea

#LOCAL_CFLAGS += -std=c++11 -Wno-psabi -DCC_LUA_ENGINE_ENABLED=1 $(ANDROID_COCOS2D_BUILD_FLAGS)

LOCAL_LDLIBS := -lGLESv2 \
                -llog \
                -lz \
                -landroid

LOCAL_EXPORT_LDLIBS := -lGLESv1_CM \
                       -lGLESv2 \
                       -lEGL \
                       -llog \
                       -lz \
                       -landroid

LOCAL_SHARED_LIBRARIES := quickx_shared

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

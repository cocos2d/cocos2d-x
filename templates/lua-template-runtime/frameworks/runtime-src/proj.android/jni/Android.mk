LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dlua_shared

LOCAL_MODULE_FILENAME := libcocos2dlua

LOCAL_SRC_FILES := lua/main.cpp \
                   lua/Runtime_android.cpp \
                   ../../Classes/runtime/Landscape_png.cpp \
                   ../../Classes/runtime/PlayDisable_png.cpp \
                   ../../Classes/runtime/PlayEnable_png.cpp \
                   ../../Classes/runtime/Portrait_png.cpp \
                   ../../Classes/runtime/Shine_png.cpp \
                   ../../Classes/runtime/Runtime.cpp \
                   ../../Classes/VisibleRect.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/ConfigParser.cpp
                   


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/runtime \

LOCAL_STATIC_LIBRARIES := curl_static_prebuilt

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_lua_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings)
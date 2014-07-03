LOCAL_PATH := $(call my-dir)
$(call import-add-path,$(LOCAL_PATH)/../)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
    hellocpp/AnySDKListener.cpp \
    hellocpp/lua_anysdk_auto.cpp \
    hellocpp/lua_anysdk_manual.cpp \
    ../../sources/AppDelegate.cpp \
    ../../sources/SimulatorConfig.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../sources \
                    $(COCOS2DX_ROOT)/external/json


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

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_lua_static
LOCAL_WHOLE_STATIC_LIBRARIES += PluginProtocolStatic

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx/lua-bindings)

$(call import-module,protocols/android)


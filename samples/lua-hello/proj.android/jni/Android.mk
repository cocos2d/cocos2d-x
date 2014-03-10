LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellolua_shared

LOCAL_MODULE_FILENAME := libhellolua

LOCAL_SRC_FILES := hellolua/main.cpp \
                   ../../Classes/AppDelegate.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../../../../external/lua/tolua \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_lua_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua/bindings)

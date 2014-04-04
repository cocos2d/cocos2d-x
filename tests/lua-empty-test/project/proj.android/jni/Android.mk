LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := lua_empty_test_shared

LOCAL_MODULE_FILENAME := liblua_empty_test

LOCAL_SRC_FILES := main.cpp \
                   ../../Classes/AppDelegate.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../../../../external/lua/tolua \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_lua_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings)

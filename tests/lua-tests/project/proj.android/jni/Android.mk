LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := lua_tests_shared

LOCAL_MODULE_FILENAME := liblua_tests

LOCAL_SRC_FILES += main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/lua_assetsmanager_test_sample.cpp


LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := curl_static_prebuilt

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_lua_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings)

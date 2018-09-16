LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := lua_tests_shared

LOCAL_MODULE_FILENAME := liblua_tests

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES += main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/lua_assetsmanager_test_sample.cpp \
                   ../../../Classes/lua_test_bindings.cpp


LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes

LOCAL_STATIC_LIBRARIES := cclua_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos/scripting/lua-bindings/proj.android)

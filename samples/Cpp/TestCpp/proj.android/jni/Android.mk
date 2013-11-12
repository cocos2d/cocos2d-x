LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := testcpp_shared

LOCAL_MODULE_FILENAME := libtestcpp

LOCAL_SRC_FILES := testcpp/main.cpp

LOCAL_C_INCLUDES := ../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_testcpp_common

include $(BUILD_SHARED_LIBRARY)

$(call import-module,samples/Cpp/TestCpp)

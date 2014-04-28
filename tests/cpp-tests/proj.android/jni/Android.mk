LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../..)
$(call import-add-path,$(LOCAL_PATH)/../../../../cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../../external)

LOCAL_MODULE := cpp_tests_shared

LOCAL_MODULE_FILENAME := libcpp_tests

LOCAL_SRC_FILES := main.cpp

LOCAL_C_INCLUDES := ../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_cpp_tests_common

include $(BUILD_SHARED_LIBRARY)

$(call import-module,tests/cpp-tests)

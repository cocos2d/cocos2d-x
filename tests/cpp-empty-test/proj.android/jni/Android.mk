LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
path := $(LOCAL_PATH)

LOCAL_MODULE := cpp_empty_test_shared

LOCAL_MODULE_FILENAME := libcpp_empty_test

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../../../extensions \
                    $(LOCAL_PATH)/../../../.. \
                    $(LOCAL_PATH)/../../../../cocos/editor-support

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += creator_reader

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

$(call import-add-path, $(path)/../../Classes/)
$(call import-module, reader)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_loop_static

#LOCAL_MODULE_FILENAME := libloop

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := LoopRunable.cpp \
ThreadLoop.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../external/uv/include

LOCAL_STATIC_LIBRARIES += uv_static

include $(BUILD_STATIC_LIBRARY)

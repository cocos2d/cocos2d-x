LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos2d_simulator_static

LOCAL_MODULE_FILENAME := libsimulator

LOCAL_SRC_FILES := \
../lib/runtime/ConfigParser.cpp \
../lib/ProjectConfig/ProjectConfig.cpp \
../lib/ProjectConfig/SimulatorConfig.cpp \


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../lib


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../lib

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static

include $(BUILD_STATIC_LIBRARY)

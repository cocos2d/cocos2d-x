LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := helloworld_shared

LOCAL_MODULE_FILENAME := helloworld

LOCAL_SRC_FILES := main.cpp
                
LOCAL_SHARED_LIBRARIES := cocos2dx_shared game_logic
            
include $(BUILD_SHARED_LIBRARY)
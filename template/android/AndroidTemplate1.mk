LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := main.cpp

LOCAL_SHARED_LIBRARIES := cocos2dx_shared game_logic_shared
            
include $(BUILD_SHARED_LIBRARY)

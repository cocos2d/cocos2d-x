LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := main.cpp

LOCAL_SHARED_LIBRARIES := cocos2dx_shared game_shared
            
include $(BUILD_SHARED_LIBRARY)

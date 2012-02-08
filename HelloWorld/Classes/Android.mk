LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_logic_shared

LOCAL_MODULE_FILENAME := libgame_logic

LOCAL_SRC_FILES := AppDelegate.cpp \
                   HelloWorldScene.cpp
                   
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
                
LOCAL_SHARED_LIBRARIES := cocos2dx_shared cocosdenshion_shared
            
include $(BUILD_SHARED_LIBRARY)
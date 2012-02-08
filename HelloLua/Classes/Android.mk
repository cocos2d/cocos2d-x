LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_logic_shared

LOCAL_MODULE_FILENAME := libgame_logic

LOCAL_SRC_FILES := \
AppDelegate.cpp \
../../lua/cocos2dx_support/LuaEngineImpl.cpp \
../../lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \
../../lua/cocos2dx_support/LuaCocos2d.cpp \
../../lua/cocos2dx_support/LuaEngine.cpp \
../../lua/CocosDenshion_support/LuaSimpleAudioEngine.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_SHARED_LIBRARIES := cocos2dx_shared cocosdenshion_shared lua_shared
            
include $(BUILD_SHARED_LIBRARY)

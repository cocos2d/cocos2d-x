LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game_logic

LOCAL_SRC_FILES := \
AppDelegate.cpp \
../../lua/cocos2dx_support/LuaEngineImpl.cpp \
../../lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \
../../lua/cocos2dx_support/LuaCocos2d.cpp \
../../lua/cocos2dx_support/LuaEngine.cpp \
../../lua/CocosDenshion_support/LuaSimpleAudioEngine.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../cocos2dx \
                    $(LOCAL_PATH)/../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../cocos2dx/include \
                    $(LOCAL_PATH)/../../cocos2dx/lua_support \
                    $(LOCAL_PATH)/../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../lua/lua \
                    $(LOCAL_PATH)/../../lua/tolua \
                    $(LOCAL_PATH)/../../lua/cocos2dx_support \
                    $(LOCAL_PATH)/../../lua/CocosDenshion_support
 
LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../Android/libs/$(TARGET_ARCH_ABI)) \
		-L$(call host-path, $(LOCAL_PATH)/../../cocos2dx/platform/third_party/android/libraries/$(TARGET_ARCH_ABI)) -lcurl \
		-lcocos2d \
		-lcocosdenshion \
		-llua
            
include $(BUILD_SHARED_LIBRARY)
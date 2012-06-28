LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game

LOCAL_SRC_FILES := main.cpp \
../../../Classes/AppDelegate.cpp \
../../../../lua/cocos2dx_support/LuaEngineImpl.cpp \
../../../../lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \
../../../../lua/cocos2dx_support/LuaCocos2d.cpp \
../../../../lua/cocos2dx_support/LuaEngine.cpp \
../../../../lua/CocosDenshion_support/LuaSimpleAudioEngine.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos2dx \
                    $(LOCAL_PATH)/../../../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../../../cocos2dx/include \
                    $(LOCAL_PATH)/../../../../cocos2dx/lua_support \
                    $(LOCAL_PATH)/../../../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../../Classes \
                    $(LOCAL_PATH)/../../../../lua/lua \
                    $(LOCAL_PATH)/../../../../lua/tolua \
                    $(LOCAL_PATH)/../../../../lua/cocos2dx_support \
                    $(LOCAL_PATH)/../../../../lua/CocosDenshion_support
# it is used for ndk-r5  
# if you build with ndk-r4, comment it  
# because the new Windows toolchain doesn't support Cygwin's drive
# mapping (i.e /cygdrive/c/ instead of C:/)  
LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/armeabi) \
        -L$(call host-path, $(LOCAL_PATH)/../../../../cocos2dx/platform/third_party/android/libraries) -lcurl \
        -lcocos2d \
        -lcocosdenshion \
        -llua
            
include $(BUILD_SHARED_LIBRARY)
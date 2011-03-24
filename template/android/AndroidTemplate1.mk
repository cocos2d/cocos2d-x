LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := helloworld

LOCAL_SRC_FILES := main.cpp \
../../../Classes/AppDelegate.cpp \
../../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos2dx \
                    $(LOCAL_PATH)/../../../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../../../cocos2dx/include \
                    $(LOCAL_PATH)/../../../Classes 
                   
LOCAL_LDLIBS := -L$(LOCAL_PATH)/../../libs/armeabi -lcocos2d -llog -lcocosdenshion

# it is used for ndk-r5    
# because the new Windows toolchain doesn't support Cygwin's drive
# mapping (i.e /cygdrive/c/ instead of C:/)  
# LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/armeabi) \
#                -lcocos2d -llog -lcocosdenshion
            
include $(BUILD_SHARED_LIBRARY)
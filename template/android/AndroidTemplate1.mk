LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game

LOCAL_SRC_FILES := main.cpp \
../../../Classes/AppDelegate.cpp \
../../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos2dx \
                    $(LOCAL_PATH)/../../../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../../../cocos2dx/include \
                    $(LOCAL_PATH)/../../../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../../Classes 

# it is used for ndk-r4
# if you build with nkd-r4, uncomment it                    
# LOCAL_LDLIBS := -llog -lGLESv1_CM -lz \
#                -L$(LOCAL_PATH)/../../../../cocos2dx/platform/third_party/android/libraries -lcurl \
#                -lpng \
#                -lxml2 \
#                -ljpeg 

# it is used for ndk-r5  
# if you build with ndk-r4, comment it  
# because the new Windows toolchain doesn't support Cygwin's drive
# mapping (i.e /cygdrive/c/ instead of C:/)  
LOCAL_LDLIBS := -llog -lGLESv1_CM -lz \
                -L$(call host-path, $(LOCAL_PATH)/../../../../cocos2dx/platform/third_party/android/libraries) -lcurl \
                -lpng \
                -lxml2 \
                -ljpeg
                
LOCAL_STATIC_LIBRARIES := libcocos2d libcocosdenshion
            
include $(BUILD_SHARED_LIBRARY)
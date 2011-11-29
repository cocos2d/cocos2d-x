LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := tests

LOCAL_SRC_FILES := main.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos2dx \
                    $(LOCAL_PATH)/../../../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../../../cocos2dx/include \
                    $(LOCAL_PATH)/../../.. 
                
  
LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/$(TARGET_ARCH_ABI)) \
                -lGLESv1_CM \
                -lcocos2d -llog -lgame_logic
            
include $(BUILD_SHARED_LIBRARY)
                   

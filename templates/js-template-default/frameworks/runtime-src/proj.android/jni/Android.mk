LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../vrsdks)
LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

LOCAL_SRC_FILES := hellojavascript/main.cpp \
                   ../../Classes/AppDelegate.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../vrsdks

# _COCOS_VR_HEADER_ANDROID_BEGIN
# _COCOS_VR_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2d_js_static

# _COCOS_VR_LIB_ANDROID_BEGIN
# _COCOS_VR_LIB_ANDROID_END

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)


$(call import-module, scripting/js-bindings/proj.android)

# _COCOS_VR_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_VR_LIB_IMPORT_ANDROID_END

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dxandroid_static

LOCAL_MODULE_FILENAME := libcocos2dandroid

LOCAL_SRC_FILES := \
CCApplication.cpp \
CCCommon.cpp \
CCDevice.cpp \
CCGLView.cpp \
CCFileUtilsAndroid.cpp \
javaactivity.cpp \
jni/DPIJni.cpp \
jni/IMEJni.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxAccelerometer.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp \
jni/JniHelper.cpp \
jni/TouchesJni.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/../.. \

LOCAL_LDLIBS := -lGLESv1_CM \
                -lGLESv2 \
                -lEGL \
                -llog \
                -lz \
                -landroid

LOCAL_EXPORT_LDLIBS := -lGLESv1_CM \
                       -lGLESv2 \
                       -lEGL \
                       -llog \
                       -lz \
                       -landroid

LOCAL_WHOLE_STATIC_LIBRARIES	:= cocos_png_static cocos_jpeg_static cocos_tiff_static cocos_webp_static


include $(BUILD_STATIC_LIBRARY)

$(call import-module,jpeg/prebuilt/android)
$(call import-module,png/prebuilt/android)
$(call import-module,tiff/prebuilt/android)
$(call import-module,webp/prebuilt/android)

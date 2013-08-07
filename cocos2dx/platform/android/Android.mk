LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dxandroid_static

LOCAL_MODULE_FILENAME := libcocos2dandroid

LOCAL_SRC_FILES := \
CCDevice.cpp \
CCEGLView.cpp \
CCAccelerometer.cpp \
CCApplication.cpp \
CCCommon.cpp \
CCFileUtilsAndroid.cpp \
CCImage.cpp \
nativeactivity.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp \
jni/Java_org_cocos2dx_lib_Cocos2dxAccelerometer.cpp \
jni/JniHelper.cpp \
jni/IMEJni.cpp \
jni/TouchesJni.cpp \
jni/DPIJni.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../.. \
                    $(LOCAL_PATH)/../../include \
                    $(LOCAL_PATH)/../../kazmath/include \
                    $(LOCAL_PATH)/../../platform/third_party/common/etc

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

LOCAL_WHOLE_STATIC_LIBRARIES	:= android_native_app_glue cocos_libpng_static cocos_jpeg_static cocos_libxml2_static cocos_libtiff_static cocos_libwebp_static


include $(BUILD_STATIC_LIBRARY)

$(call import-module,libjpeg)
$(call import-module,libpng)
$(call import-module,libtiff)
$(call import-module,libwebp)
$(call import-module,android/native_app_glue)

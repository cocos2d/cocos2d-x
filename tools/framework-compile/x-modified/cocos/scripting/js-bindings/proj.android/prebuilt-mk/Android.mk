LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2d_js_android_static

LOCAL_MODULE_FILENAME := libjscocos2dandroid

LOCAL_SRC_FILES := __LIBS_DIR__/android/$(TARGET_ARCH_ABI)/libjscocos2dandroid.a

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../.. \
                    $(LOCAL_PATH)/../manual \
                    $(LOCAL_PATH)/../manual/platform/android \
                    $(LOCAL_PATH)/../../../base \
                    $(LOCAL_PATH)/../../../../external/chipmunk/include/chipmunk

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -landroid

LOCAL_STATIC_LIBRARIES := spidermonkey_static

include $(PREBUILT_STATIC_LIBRARY)

#==============================================================

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2d_js_static

LOCAL_MODULE_FILENAME := libjscocos2d

LOCAL_SRC_FILES := __LIBS_DIR__/prebuilt/android/$(TARGET_ARCH_ABI)/libjscocos2d.a
                   

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../manual \
                    $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../../../2d \
                    $(LOCAL_PATH)/../../../base \
                    $(LOCAL_PATH)/../../../ui \
                    $(LOCAL_PATH)/../../../audio/include \
                    $(LOCAL_PATH)/../../../storage \
                    $(LOCAL_PATH)/../../../../extensions \
                    $(LOCAL_PATH)/../../../editor-support/spine \
                    $(LOCAL_PATH)/../../../editor-support/cocosbuilder \
                    $(LOCAL_PATH)/../../../editor-support/cocostudio


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../manual \
                           $(LOCAL_PATH)/../../auto \
                           $(LOCAL_PATH)/../../../../audio/include 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2d_js_android_static

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_localstorage_static

include $(PREBUILT_STATIC_LIBRARY)

$(call import-module,./prebuilt-mk)
$(call import-module,external/spidermonkey/prebuilt/android)
$(call import-module,storage/local-storage/prebuilt-mk)

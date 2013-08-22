LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES :=%s

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/kazmath/include \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/platform/third_party/common/etc \
                    $(LOCAL_PATH)/platform/third_party/common/s3tc \
                    $(LOCAL_PATH)/platform/third_party/common/atitc

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/kazmath/include \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/platform/third_party/common/etc \
                    $(LOCAL_PATH)/platform/third_party/common/s3tc \
                    $(LOCAL_PATH)/platform/third_party/common/atitc


LOCAL_LDLIBS := -lGLESv2 \
                -llog \
                -lz \
                -landroid

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz \
                       -landroid

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_libpng_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_jpeg_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libxml2_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libtiff_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libwebp_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_freetype2_static

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   := -Wno-psabi -DUSE_FILE32API
LOCAL_EXPORT_CFLAGS   := -Wno-psabi -DUSE_FILE32API

include $(BUILD_STATIC_LIBRARY)

$(call import-module,libjpeg)
$(call import-module,libpng)
$(call import-module,libtiff)
$(call import-module,libwebp)
$(call import-module,libfreetype2)
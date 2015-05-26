LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_internal_static

LOCAL_MODULE_FILENAME := libcocos2dxinternal

LOCAL_SRC_FILES := __LIBS_DIR__/android/$(TARGET_ARCH_ABI)/libcocos2dxinternal.a


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../. \
$(LOCAL_PATH)/../platform \
$(LOCAL_PATH)/../base \
$(LOCAL_PATH)/../../external \
$(LOCAL_PATH)/../../external/tinyxml2 \
$(LOCAL_PATH)/../../external/unzip \
$(LOCAL_PATH)/../../external/chipmunk/include/chipmunk \
$(LOCAL_PATH)/../../external/xxhash \
$(LOCAL_PATH)/../../external/nslog


LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -landroid

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_freetype2_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_png_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_jpeg_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_tiff_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_webp_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_zlib_static

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dxandroid_static

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat
LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat

include $(PREBUILT_STATIC_LIBRARY)

#==============================================================

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static
LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES := __LIBS_DIR__/android/$(TARGET_ARCH_ABI)/libcocos2d.a

LOCAL_WHOLE_STATIC_LIBRARIES := cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += audioengine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos3d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static

include $(PREBUILT_STATIC_LIBRARY)

#==============================================================
$(call import-module,freetype2/prebuilt/android)
$(call import-module, platform/android/prebuilt-mk)
$(call import-module,png/prebuilt/android)
$(call import-module,jpeg/prebuilt/android)
$(call import-module,tiff/prebuilt/android)
$(call import-module,webp/prebuilt/android)
$(call import-module,chipmunk/prebuilt/android)
$(call import-module, 3d/prebuilt-mk)
$(call import-module, audio/android/prebuilt-mk)
$(call import-module, editor-support/cocosbuilder/prebuilt-mk)
$(call import-module, editor-support/cocostudio/prebuilt-mk)
$(call import-module, editor-support/spine/prebuilt-mk)
$(call import-module, network/prebuilt-mk)
$(call import-module, ui/prebuilt-mk)
$(call import-module, extensions/prebuilt-mk)
$(call import-module, Box2D/prebuilt-mk)
$(call import-module,curl/prebuilt/android)
$(call import-module,websockets/prebuilt/android)
$(call import-module, flatbuffers/prebuilt-mk)
$(call import-module, zlib/prebuilt/android)



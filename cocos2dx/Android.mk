LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

# need to accureate control of directories, so not use 'find' to list all
cpp_dirs := $(LOCAL_PATH) \
            $(LOCAL_PATH)/base_nodes \
            $(LOCAL_PATH)/actions \
            $(LOCAL_PATH)/cocoa \
            $(LOCAL_PATH)/draw_nodes \
            $(LOCAL_PATH)/effects \
            $(LOCAL_PATH)/keyboard_dispatcher \
            $(LOCAL_PATH)/keypad_dispatcher \
            $(LOCAL_PATH)/label_nodes \
            $(LOCAL_PATH)/layers_scenes_transitions_nodes \
            $(LOCAL_PATH)/menu_nodes \
            $(LOCAL_PATH)/misc_nodes \
            $(LOCAL_PATH)/particle_nodes \
            $(LOCAL_PATH)/platform \
            $(LOCAL_PATH)/platform/third_party/common/etc \
            $(LOCAL_PATH)/platform/android \
            $(LOCAL_PATH)/platform/android/jni \
            $(LOCAL_PATH)/script_support \
            $(LOCAL_PATH)/shaders \
            $(LOCAL_PATH)/sprite_nodes \
            $(LOCAL_PATH)/support \
            $(LOCAL_PATH)/support/component \
            $(LOCAL_PATH)/support/data_support \
            $(LOCAL_PATH)/support/image_support \
            $(LOCAL_PATH)/support/tinyxml2 \
            $(LOCAL_PATH)/support/user_default \
            $(LOCAL_PATH)/support/zip_support \
            $(LOCAL_PATH)/text_input_node \
            $(LOCAL_PATH)/textures \
            $(LOCAL_PATH)/tilemap_parallax_nodes \
            $(LOCAL_PATH)/touch_dispatcher

c_dirs := $(LOCAL_PATH)\
          $(LOCAL_PATH)/kazmath/src \
          $(LOCAL_PATH)/kazmath/src/GL

find_cpp_files = $(subst $(LOCAL_PATH)/,,$(wildcard $(dir)/*.cpp)) 
find_c_files = $(subst $(LOCAL_PATH)/,,$(wildcard $(dir)/*.c)) 
LOCAL_SRC_FILES := $(foreach dir, $(cpp_dirs), $(find_cpp_files))
LOCAL_SRC_FILES += $(foreach dir, $(c_dirs), $(find_c_files))

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/kazmath/include \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/platform/third_party/common/etc

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/kazmath/include \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/platform/third_party/common/etc


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

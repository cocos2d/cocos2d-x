LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dlua_shared

LOCAL_MODULE_FILENAME := libcocos2dlua

LOCAL_SRC_FILES := hellolua/main.cpp \
hellolua/Runtime_android.cpp \
../../Classes/protobuf-lite/google/protobuf/io/coded_stream.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/common.cc \
../../Classes/protobuf-lite/google/protobuf/extension_set.cc \
../../Classes/protobuf-lite/google/protobuf/generated_message_util.cc \
../../Classes/protobuf-lite/google/protobuf/message_lite.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/once.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/atomicops_internals_x86_gcc.cc \
../../Classes/protobuf-lite/google/protobuf/repeated_field.cc \
../../Classes/protobuf-lite/google/protobuf/wire_format_lite.cc \
../../Classes/protobuf-lite/google/protobuf/io/zero_copy_stream.cc \
../../Classes/protobuf-lite/google/protobuf/io/zero_copy_stream_impl_lite.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/stringprintf.cc \
../../Classes/runtime/Landscape_png.cpp \
../../Classes/runtime/PlayDisable_png.cpp \
../../Classes/runtime/PlayEnable_png.cpp \
../../Classes/runtime/Portrait_png.cpp \
../../Classes/runtime/Shine_png.cpp \
../../Classes/runtime/Runtime.cpp \
../../Classes/runtime/Protos.pb.cc \
../../Classes/runtime/lua_debugger.c \
../../Classes/VisibleRect.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/ConfigParser.cpp

#anysdk
LOCAL_SRC_FILES += \
../../Classes/anysdkbindings.cpp \
../../Classes/anysdk_manual_bindings.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../Classes/protobuf-lite \
$(LOCAL_PATH)/../../Classes/runtime \
$(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../../cocos2d-x/external \
$(LOCAL_PATH)/../../Classes/quick-src \
$(LOCAL_PATH)/../../Classes/quick-src/extra

#anysdk
LOCAL_C_INCLUDES +=	\
$(LOCAL_PATH)/../protocols/android \
$(LOCAL_PATH)/../protocols/include

#anysdk
LOCAL_WHOLE_STATIC_LIBRARIES += PluginProtocolStatic

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += lua_extensions_static
LOCAL_STATIC_LIBRARIES += extra_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings/proj.android)

$(call import-module, quick-src/lua_extensions)
$(call import-module, quick-src/extra)

#anysdk
$(call import-module,protocols/android)


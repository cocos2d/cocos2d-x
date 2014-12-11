LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dlua_shared

LOCAL_MODULE_FILENAME := libcocos2dlua

LOCAL_SRC_FILES := \
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
../../Classes/runtime/ConnectWaitLayer.cpp \
../../Classes/runtime/ConsoleCommand.cpp \
../../Classes/runtime/FileServer.cpp \
../../Classes/runtime/Landscape_png.cpp \
../../Classes/runtime/lua_debugger.c \
../../Classes/runtime/PlayDisable_png.cpp \
../../Classes/runtime/PlayEnable_png.cpp \
../../Classes/runtime/Portrait_png.cpp \
../../Classes/runtime/Protos.pb.cc \
../../Classes/runtime/Runtime.cpp \
../../Classes/runtime/Shine_png.cpp \
../../Classes/VisibleRect.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/ConfigParser.cpp \
hellolua/Runtime_android.cpp \
hellolua/main.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../Classes/protobuf-lite \
$(LOCAL_PATH)/../../Classes/runtime \
$(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../../cocos2d-x/external

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings/proj.android)

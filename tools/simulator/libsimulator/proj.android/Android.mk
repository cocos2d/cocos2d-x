LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos2d_simulator_static

LOCAL_MODULE_FILENAME := libsimulator

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
../lib/protobuf-lite/google/protobuf/io/coded_stream.cc \
../lib/protobuf-lite/google/protobuf/stubs/common.cc \
../lib/protobuf-lite/google/protobuf/extension_set.cc \
../lib/protobuf-lite/google/protobuf/generated_message_util.cc \
../lib/protobuf-lite/google/protobuf/message_lite.cc \
../lib/protobuf-lite/google/protobuf/stubs/once.cc \
../lib/protobuf-lite/google/protobuf/stubs/atomicops_internals_x86_gcc.cc \
../lib/protobuf-lite/google/protobuf/repeated_field.cc \
../lib/protobuf-lite/google/protobuf/wire_format_lite.cc \
../lib/protobuf-lite/google/protobuf/io/zero_copy_stream.cc \
../lib/protobuf-lite/google/protobuf/io/zero_copy_stream_impl_lite.cc \
../lib/protobuf-lite/google/protobuf/stubs/stringprintf.cc \
../lib/runtime/ConnectWaitLayer.cpp \
../lib/runtime/ConsoleCommand.cpp \
../lib/runtime/FileServer.cpp \
../lib/runtime/Landscape_png.cpp \
../lib/runtime/PlayDisable_png.cpp \
../lib/runtime/PlayEnable_png.cpp \
../lib/runtime/Portrait_png.cpp \
../lib/runtime/Protos.pb.cc \
../lib/runtime/Runtime.cpp \
../lib/runtime/RuntimeProtocol.cpp \
../lib/runtime/RuntimeCCSImpl.cpp \
../lib/runtime/Shine_png.cpp \
../lib/runtime/ConfigParser.cpp \
../lib/runtime/VisibleRect.cpp \
../lib/ProjectConfig/ProjectConfig.cpp \
../lib/ProjectConfig/SimulatorConfig.cpp \
hellolua/Runtime_android.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../lib/protobuf-lite


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../lib/protobuf-lite

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_STATIC_LIBRARY)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocostudio_static

LOCAL_MODULE_FILENAME := libcocostudio

LOCAL_SRC_FILES := CCActionFrame.cpp \
CCActionFrameEasing.cpp \
CCActionManagerEx.cpp \
CCActionNode.cpp \
CCActionObject.cpp \
CCArmature.cpp \
CCBone.cpp \
CCArmatureAnimation.cpp \
CCProcessBase.cpp \
CCTween.cpp \
CCDatas.cpp \
CCBatchNode.cpp \
CCDecorativeDisplay.cpp \
CCDisplayFactory.cpp \
CCDisplayManager.cpp \
CCSkin.cpp \
CCColliderDetector.cpp \
CCArmatureDataManager.cpp \
CCArmatureDefine.cpp \
CCDataReaderHelper.cpp \
CCSpriteFrameCacheHelper.cpp \
CCTransformHelp.cpp \
CCUtilMath.cpp \
CCComAttribute.cpp \
CCComAudio.cpp \
CCComController.cpp \
CCComRender.cpp \
CCInputDelegate.cpp \
DictionaryHelper.cpp \
CCSGUIReader.cpp \
CCSSceneReader.cpp \
TriggerBase.cpp \
TriggerMng.cpp \
TriggerObj.cpp \
CocoLoader.cpp \
WidgetReader/WidgetReader.cpp \
WidgetReader/ButtonReader/ButtonReader.cpp \
WidgetReader/CheckBoxReader/CheckBoxReader.cpp \
WidgetReader/ImageViewReader/ImageViewReader.cpp \
WidgetReader/LayoutReader/LayoutReader.cpp \
WidgetReader/ListViewReader/ListViewReader.cpp \
WidgetReader/LoadingBarReader/LoadingBarReader.cpp \
WidgetReader/PageViewReader/PageViewReader.cpp \
WidgetReader/ScrollViewReader/ScrollViewReader.cpp \
WidgetReader/SliderReader/SliderReader.cpp \
WidgetReader/TextAtlasReader/TextAtlasReader.cpp \
WidgetReader/TextBMFontReader/TextBMFontReader.cpp \
WidgetReader/TextFieldReader/TextFieldReader.cpp \
WidgetReader/TextReader/TextReader.cpp \
ActionTimeline/CCNodeReader.cpp \
ActionTimeline/CCActionTimelineCache.cpp \
ActionTimeline/CCFrame.cpp \
ActionTimeline/CCTimeLine.cpp \
ActionTimeline/CCActionTimeline.cpp \
CSParseBinary.pb.cc \
../../../external/protocolBuf/src/google/protobuf/descriptor.cc \
../../../external/protocolBuf/src/google/protobuf/descriptor.pb.cc \
../../../external/protocolBuf/src/google/protobuf/descriptor_database.cc \
../../../external/protocolBuf/src/google/protobuf/dynamic_message.cc \
../../../external/protocolBuf/src/google/protobuf/extension_set.cc \
../../../external/protocolBuf/src/google/protobuf/extension_set_heavy.cc \
../../../external/protocolBuf/src/google/protobuf/generated_message_reflection.cc \
../../../external/protocolBuf/src/google/protobuf/generated_message_util.cc \
../../../external/protocolBuf/src/google/protobuf/message.cc \
../../../external/protocolBuf/src/google/protobuf/message_lite.cc \
../../../external/protocolBuf/src/google/protobuf/reflection_ops.cc \
../../../external/protocolBuf/src/google/protobuf/repeated_field.cc \
../../../external/protocolBuf/src/google/protobuf/service.cc \
../../../external/protocolBuf/src/google/protobuf/text_format.cc \
../../../external/protocolBuf/src/google/protobuf/unknown_field_set.cc \
../../../external/protocolBuf/src/google/protobuf/wire_format.cc \
../../../external/protocolBuf/src/google/protobuf/wire_format_lite.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_enum.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_enum_field.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_extension.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_field.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_file.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_generator.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_helpers.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_message.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_message_field.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_primitive_field.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_service.cc \
../../../external/protocolBuf/src/google/protobuf/compiler/cpp/cpp_string_field.cc \
../../../external/protocolBuf/src/google/protobuf/io/coded_stream.cc \
../../../external/protocolBuf/src/google/protobuf/io/gzip_stream.cc \
../../../external/protocolBuf/src/google/protobuf/io/printer.cc \
../../../external/protocolBuf/src/google/protobuf/io/tokenizer.cc \
../../../external/protocolBuf/src/google/protobuf/io/zero_copy_stream.cc \
../../../external/protocolBuf/src/google/protobuf/io/zero_copy_stream_impl.cc \
../../../external/protocolBuf/src/google/protobuf/io/zero_copy_stream_impl_lite.cc \
../../../external/protocolBuf/src/google/protobuf/stubs/common.cc \
../../../external/protocolBuf/src/google/protobuf/stubs/once.cc \
../../../external/protocolBuf/src/google/protobuf/stubs/stringprintf.cc \
../../../external/protocolBuf/src/google/protobuf/stubs/structurally_valid.cc \
../../../external/protocolBuf/src/google/protobuf/stubs/strutil.cc \
../../../external/protocolBuf/src/google/protobuf/stubs/substitute.cc \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../../../external

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../.. \
$(LOCAL_PATH)/../../../external \
$(LOCAL_PATH)/../../../external/protocolBuf/src/google/protobuf \
$(LOCAL_PATH)/../../../external/protocolBuf/src \
$(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../..

LOCAL_CFLAGS += -fexceptions


LOCAL_WHOLE_STATIC_LIBRARIES := cocos_ui_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,ui)
$(call import-module,audio/android)

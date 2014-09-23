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
ActionTimeline/CSLoader.cpp \
CSParseBinary.pb.cc \
../../../external/protocolBuf/src/google/protobuf/extension_set.cc \
../../../external/protocolBuf/src/google/protobuf/generated_message_util.cc \
../../../external/protocolBuf/src/google/protobuf/message_lite.cc \
../../../external/protocolBuf/src/google/protobuf/repeated_field.cc \
../../../external/protocolBuf/src/google/protobuf/wire_format_lite.cc \
../../../external/protocolBuf/src/google/protobuf/io/coded_stream.cc \
../../../external/protocolBuf/src/google/protobuf/io/zero_copy_stream.cc \
../../../external/protocolBuf/src/google/protobuf/io/zero_copy_stream_impl.cc \
../../../external/protocolBuf/src/google/protobuf/io/zero_copy_stream_impl_lite.cc \
../../../external/protocolBuf/src/google/protobuf/stubs/common.cc \
../../../external/protocolBuf/src/google/protobuf/stubs/once.cc \
../../../external/protocolBuf/src/google/protobuf/stubs/stringprintf.cc \

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

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocostudio_static

LOCAL_MODULE_FILENAME := libcocostudio

LOCAL_SRC_FILES := action/CCActionFrame.cpp \
action/CCActionFrameEasing.cpp \
action/CCActionManagerEx.cpp \
action/CCActionNode.cpp \
action/CCActionObject.cpp \
armature/CCArmature.cpp \
armature/CCBone.cpp \
armature/animation/CCArmatureAnimation.cpp \
armature/animation/CCProcessBase.cpp \
armature/animation/CCTween.cpp \
armature/datas/CCDatas.cpp \
armature/display/CCBatchNode.cpp \
armature/display/CCDecorativeDisplay.cpp \
armature/display/CCDisplayFactory.cpp \
armature/display/CCDisplayManager.cpp \
armature/display/CCSkin.cpp \
armature/physics/CCColliderDetector.cpp \
armature/utils/CCArmatureDataManager.cpp \
armature/utils/CCArmatureDefine.cpp \
armature/utils/CCDataReaderHelper.cpp \
armature/utils/CCSpriteFrameCacheHelper.cpp \
armature/utils/CCTransformHelp.cpp \
armature/utils/CCTweenFunction.cpp \
armature/utils/CCUtilMath.cpp \
components/CCComAttribute.cpp \
components/CCComAudio.cpp \
components/CCComController.cpp \
components/CCComRender.cpp \
components/CCInputDelegate.cpp \
json/CSContentJsonDictionary.cpp \
json/DictionaryHelper.cpp \
reader/CCSGUIReader.cpp \
reader/CCSSceneReader.cpp \
../../../external/json/json_reader.cpp \
../../../external/json/json_value.cpp \
../../../external/json/json_writer.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/../../../external/json

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../2d \
$(LOCAL_PATH)/../../../external/json \
$(LOCAL_PATH) \
$(LOCAL_PATH)/../../gui \
$(LOCAL_PATH)/../../../external

LOCAL_CFLAGS += -Wno-psabi -fexceptions
LOCAL_EXPORT_CFLAGS += -Wno-psabi

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)


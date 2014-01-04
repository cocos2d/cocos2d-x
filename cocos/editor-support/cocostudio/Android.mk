LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocostudio_static

LOCAL_MODULE_FILENAME := libcocostudio

LOCAL_SRC_FILES := CCActionFrame.cpp \
CCActionEaseEx.cpp \
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
CCTweenFunction.cpp \
CCUtilMath.cpp \
CCComAttribute.cpp \
CCComAudio.cpp \
CCComController.cpp \
CCComRender.cpp \
CCInputDelegate.cpp \
DictionaryHelper.cpp \
CCSGUIReader.cpp \
CCSSceneReader.cpp \
ObjectFactory.cpp \
TriggerBase.cpp \
TriggerMng.cpp \
TriggerObj.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../../../external

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../2d \
$(LOCAL_PATH)/../../../external \
$(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../..

LOCAL_CFLAGS += -Wno-psabi -fexceptions
LOCAL_EXPORT_CFLAGS += -Wno-psabi

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_gui_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,gui)


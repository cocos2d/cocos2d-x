LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := spine_static

LOCAL_MODULE_FILENAME := libspine

LOCAL_SRC_FILES := Animation.cpp \
AnimationState.cpp \
AnimationStateData.cpp \
Atlas.cpp \
AtlasAttachmentLoader.cpp \
Attachment.cpp \
AttachmentLoader.cpp \
Bone.cpp \
BoneData.cpp \
CCSkeleton.cpp \
CCSkeletonAnimation.cpp \
Json.cpp \
RegionAttachment.cpp \
Skeleton.cpp \
SkeletonData.cpp \
SkeletonJson.cpp \
Skin.cpp \
Slot.cpp \
SlotData.cpp \
BoundingBoxAttachment.cpp \
Event.cpp \
EventData.cpp \
SkeletonBounds.cpp \
extension.cpp \
spine-cocos2dx.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../2d \
$(LOCAL_PATH)/..

LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,2d)

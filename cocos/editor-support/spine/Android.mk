LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := spine_static

LOCAL_MODULE_FILENAME := libspine

LOCAL_SRC_FILES := Animation.c \
AnimationState.c \
AnimationStateData.c \
Atlas.c \
AtlasAttachmentLoader.c \
Attachment.c \
AttachmentLoader.c \
Bone.c \
BoneData.c \
BoundingBoxAttachment.c \
Event.c \
EventData.c \
extension.c \
IkConstraint.c \
IkConstraintData.c \
Json.c \
MeshAttachment.c \
PolygonBatch.cpp \
RegionAttachment.c \
Skeleton.c \
SkeletonAnimation.cpp \
SkeletonBounds.c \
SkeletonData.c \
SkeletonJson.c \
SkeletonRenderer.cpp \
Skin.c \
SkinnedMeshAttachment.c \
Slot.c \
SlotData.c \
spine-cocos2dx.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static

include $(BUILD_STATIC_LIBRARY)

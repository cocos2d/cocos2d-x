LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := chipmunk_static

LOCAL_MODULE_FILENAME := libchipmunk

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/src/chipmunk.c \
$(LOCAL_PATH)/src/cpArbiter.c \
$(LOCAL_PATH)/src/cpArray.c \
$(LOCAL_PATH)/src/cpBB.c \
$(LOCAL_PATH)/src/cpBBTree.c \
$(LOCAL_PATH)/src/cpBody.c \
$(LOCAL_PATH)/src/cpCollision.c \
$(LOCAL_PATH)/src/cpHashSet.c \
$(LOCAL_PATH)/src/cpPolyShape.c \
$(LOCAL_PATH)/src/cpShape.c \
$(LOCAL_PATH)/src/cpSpace.c \
$(LOCAL_PATH)/src/cpSpaceComponent.c \
$(LOCAL_PATH)/src/cpSpaceHash.c \
$(LOCAL_PATH)/src/cpSpaceQuery.c \
$(LOCAL_PATH)/src/cpSpaceStep.c \
$(LOCAL_PATH)/src/cpSpatialIndex.c \
$(LOCAL_PATH)/src/cpSweep1D.c \
$(LOCAL_PATH)/src/cpVect.c \
$(LOCAL_PATH)/src/constraints/cpConstraint.c \
$(LOCAL_PATH)/src/constraints/cpDampedRotarySpring.c \
$(LOCAL_PATH)/src/constraints/cpDampedSpring.c \
$(LOCAL_PATH)/src/constraints/cpGearJoint.c \
$(LOCAL_PATH)/src/constraints/cpGrooveJoint.c \
$(LOCAL_PATH)/src/constraints/cpPinJoint.c \
$(LOCAL_PATH)/src/constraints/cpPivotJoint.c \
$(LOCAL_PATH)/src/constraints/cpRatchetJoint.c \
$(LOCAL_PATH)/src/constraints/cpRotaryLimitJoint.c \
$(LOCAL_PATH)/src/constraints/cpSimpleMotor.c \
$(LOCAL_PATH)/src/constraints/cpSlideJoint.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include/chipmunk

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/chipmunk
LOCAL_CFLAGS := -std=c99
                                 
include $(BUILD_STATIC_LIBRARY)

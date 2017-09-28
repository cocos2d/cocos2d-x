LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
path := $(LOCAL_PATH)

LOCAL_MODULE := creator_reader

LOCAL_MODULE_FILENAME := libcreatorreader

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
animation/AnimateClip.cpp \
animation/AnimationClip.cpp \
animation/AnimationManager.cpp \
collider/Collider.cpp \
collider/ColliderManager.cpp \
collider/Contract.cpp \
collider/Intersection.cpp \
CreatorReader.cpp \
ui/PageView.cpp \
ui/RichtextStringVisitor.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.
LOCAL_C_INCLUDES := $(LOCAL_PATH)/.

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += dragonbones_static

include $(BUILD_STATIC_LIBRARY)

$(call import-add-path, $(path))
$(call import-module, dragonbones)

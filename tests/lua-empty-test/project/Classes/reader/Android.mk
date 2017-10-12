LOCAL_PATH := $(call my-dir)

cpp_src := \
animation/AnimateClip.cpp \
animation/AnimationClip.cpp \
animation/AnimationManager.cpp \
animation/Easing.cpp \
animation/Bezier.cpp \
collider/Collider.cpp \
collider/ColliderManager.cpp \
collider/Contract.cpp \
collider/Intersection.cpp \
CreatorReader.cpp \
ui/PageView.cpp \
ui/RichtextStringVisitor.cpp

# for cpp
include $(CLEAR_VARS)
path := $(LOCAL_PATH)

LOCAL_MODULE := creator_reader
LOCAL_MODULE_FILENAME := libcreatorreader
LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES := $(cpp_src)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.
LOCAL_C_INCLUDES := $(LOCAL_PATH)/.
LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += dragonbones_static

include $(BUILD_STATIC_LIBRARY)

# for lua
include $(CLEAR_VARS)
LOCAL_MODULE := creator_reader_lua
LOCAL_MODULE_FILENAME := libcreatorreaderlua
LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES := $(cpp_src) \
lua-bindings/creator_reader_bindings.cpp \
lua-bindings/reader/lua_creator_reader_auto.cpp \
lua-bindings/reader/lua_creator_reader_manual.cpp \
lua-bindings/dragonbones/lua_dragonbones_manual.cpp \
lua-bindings/dragonbones/lua_dragonbones_auto.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.
LOCAL_C_INCLUDES := $(LOCAL_PATH)/. \
                    $(LOCAL_PATH)/collider \
                    $(LOCAL_PATH)/animation \
                    $(LOCAL_PATH)/dragonbones/cocos2dx \
                    $(LOCAL_PATH)/dragonbones/armature \
                    $(LOCAL_PATH)/dragonbones/animation \
                    $(LOCAL_PATH)/dragonbones/events \
                    $(LOCAL_PATH)/dragonbones/factories \
                    $(LOCAL_PATH)/dragonbones/core \
                    $(LOCAL_PATH)/dragonbones/geom
LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += dragonbones_static
include $(BUILD_STATIC_LIBRARY)

$(call import-add-path, $(path))
$(call import-module, dragonbones)

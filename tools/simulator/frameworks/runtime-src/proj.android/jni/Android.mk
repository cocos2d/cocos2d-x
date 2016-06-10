LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := core_shared

LOCAL_MODULE_FILENAME := libcore

LOCAL_SRC_FILES := \
                   ../../../../../../cocos2d-tooflya-sdk/actions/Shake.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/audio/Music.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/audio/Sound.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/backgrounds/Background.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/backgrounds/BackgroundColor.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/backgrounds/BackgroundScroll.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/backgrounds/BackgroundPages.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/entities/Entity.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/entities/TiledEntity.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/entities/Entity3D.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/entities/AnimatedEntity.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/entities/BatchEntity.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/entities/Button.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/entities/Motion.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/entities/Text.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/entities/Spine.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/entities/ParallaxEntity.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/missions/Missions.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/parallax/ParallaxPool.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/pools/Pool.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/screens/Screen.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/translate/Translate.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/support/Events.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/support/TEvents.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/support/Config.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/analytics/Analytics.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/batch/Batch.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/heyzap/Heyzap.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/internal/Internal.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/include/internal/Internal.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/media/Media.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/modal/Modal.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/purchase/Purchase.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/screenshot/Screenshot.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/services/Services.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/include/services/Services.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/social/Social.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/include/vote/Vote.cpp \
                   ../../../../../../cocos2d-tooflya-sdk/platform/android/vote/Vote.cpp \
                   ../../../../../../cocos2d-android-library/native/vote/Vote.cpp \
                   ../../../../../../cocos2d-android-library/native/heyzap/Heyzap.cpp \
                   ../../../../../../cocos2d-android-library/native/purchase/Purchase.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../../../cocos2d/cocos/audio/include \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/actions \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/audio \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/backgrounds \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/entities \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/parallax \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/pools \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/screens \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/internal \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/support \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/translate \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/analytics \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/batch \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/heyzap \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/internal \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/media \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/modal \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/purchase \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/screenshot \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/services \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/social \
                    $(LOCAL_PATH)/../../../../../../cocos2d-tooflya-sdk/platform/include/vote \

FILE_LIST := hellolua/main.cpp
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../frameworks/runtime-src/Classes/*.cpp)

LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES += \
$(LOCAL_PATH)/../../../frameworks/runtime-src/Classes/protobuf-lite \
$(LOCAL_PATH)/../../../frameworks/runtime-src/Classes/runtime \
$(LOCAL_PATH)/../../../frameworks/runtime-src/Classes \
$(LOCAL_PATH)/../../../../../../cocos2d/external \
$(LOCAL_PATH)/../../../../../../cocos2d/tools/simulator/libsimulator/lib \
$(LOCAL_PATH)/../../../../../../cocos2d/tools/simulator/libsimulator/lib/protobuf-lite

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos)

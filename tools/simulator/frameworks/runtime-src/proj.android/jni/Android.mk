LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := core_shared

LOCAL_MODULE_FILENAME := libcore

<<<<<<< HEAD
LOCAL_SRC_FILES := application.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/AppDelegate.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/actions/Shake.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/audio/Music.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/audio/Sound.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/backgrounds/Background.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/backgrounds/BackgroundColor.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/backgrounds/BackgroundScroll.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/backgrounds/BackgroundPages.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/entities/Entity.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/entities/TiledEntity.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/entities/Entity3D.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/entities/AnimatedEntity.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/entities/BatchEntity.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/entities/Button.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/entities/Motion.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/entities/Text.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/entities/Spine.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/entities/ParallaxEntity.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/missions/Missions.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/parallax/ParallaxPool.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/pools/Pool.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/screens/Screen.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/translate/Translate.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/ui/Content.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/support/Events.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/support/Parameters.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/analytics/Analytics.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/batch/Batch.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/heyzap/Heyzap.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/internal/Internal.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/include/internal/Internal.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/media/Media.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/purchase/Purchase.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/screenshot/Screenshot.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/services/Services.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/include/services/Services.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/social/Social.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/support/Support.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/include/ui/UI.cpp \
                   ../../../../../../../cocos2d-tooflya-sdk/platform/android/ui/UI.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../../../../cocos2d/cocos/audio/include \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/actions \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/audio \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/backgrounds \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/entities \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/parallax \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/pools \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/screens \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/internal \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/support \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/translate \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/ui \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/analytics \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/batch \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/heyzap \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/internal \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/media \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/purchase \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/screenshot \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/services \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/social \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/support \
                    $(LOCAL_PATH)/../../../../../../../cocos2d-tooflya-sdk/platform/include/ui \
=======
LOCAL_ARM_MODE := arm

FILE_LIST := hellolua/main.cpp
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
>>>>>>> cocos2d/v3

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos)

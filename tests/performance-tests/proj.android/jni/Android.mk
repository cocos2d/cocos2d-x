LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Profile.cpp \
                   ../../Classes/tests/BaseTest.cpp \
                   ../../Classes/tests/PerformanceParticle3DTest.cpp \
                   ../../Classes/tests/PerformanceAllocTest.cpp \
                   ../../Classes/tests/PerformanceParticleTest.cpp \
                   ../../Classes/tests/PerformanceCallbackTest.cpp \
                   ../../Classes/tests/PerformanceScenarioTest.cpp \
                   ../../Classes/tests/PerformanceContainerTest.cpp \
                   ../../Classes/tests/PerformanceSpriteTest.cpp \
                   ../../Classes/tests/PerformanceEventDispatcherTest.cpp \
                   ../../Classes/tests/PerformanceTextureTest.cpp \
                   ../../Classes/tests/PerformanceLabelTest.cpp \
                   ../../Classes/tests/VisibleRect.cpp \
                   ../../Classes/tests/PerformanceMathTest.cpp \
                   ../../Classes/tests/controller.cpp \
                   ../../Classes/tests/PerformanceNodeChildrenTest.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/tests

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES := cocos3d_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

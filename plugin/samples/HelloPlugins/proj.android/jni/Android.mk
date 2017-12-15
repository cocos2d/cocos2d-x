LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../../..)
$(call import-add-path,$(LOCAL_PATH)/../../../../../external)
$(call import-add-path,$(LOCAL_PATH)/../../../../../cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../../publish)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/TestAds/TestAdsScene.cpp \
                   ../../Classes/TestAnalytics/TestAnalyticsScene.cpp \
                   ../../Classes/TestIAP/TestIAPScene.cpp \
                   ../../Classes/TestIAP/MyPurchase.cpp \
                   ../../Classes/TestShare/TestShareScene.cpp \
                   ../../Classes/TestShare/MyShareManager.cpp \
                   ../../Classes/TestUser/TestUserScene.cpp \
                   ../../Classes/TestUser/MyUserManager.cpp \
                   ../../Classes/TestIAPOnline/TestIAPOnlineScene.cpp \
                   ../../Classes/TestIAPOnline/MyIAPOLManager.cpp \
                   ../../Classes/TestSocial/TestSocialScene.cpp \
                   ../../Classes/TestSocial/MySocialManager.cpp \
                   ../../Classes/TestFacebookUser/TestFacebookUserScene.cpp \
                   ../../Classes/TestFacebookShare/TestFacebookShare.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
    $(LOCAL_PATH)/../../Classes/TestAds \
    $(LOCAL_PATH)/../../Classes/TestAnalytics \
    $(LOCAL_PATH)/../../Classes/TestIAP \
    $(LOCAL_PATH)/../../Classes/TestShare \
    $(LOCAL_PATH)/../../Classes/TestUser \
    $(LOCAL_PATH)/../../Classes/TestIAPOnline \
    $(LOCAL_PATH)/../../Classes/TestSocial \
    $(LOCAL_PATH)/../../Classes/TestFacebookUser \
    $(LOCAL_PATH)/../../Classes/TestFacebookShare



LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static \
PluginProtocolStatic

include $(BUILD_SHARED_LIBRARY)

$(call import-module,plugin/protocols/proj.android/jni)
$(call import-module,cocos)

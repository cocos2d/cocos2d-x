LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

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
				   ../../Classes/TestUser/MyUserManager.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes $(LOCAL_PATH)/../../Classes/TestAds $(LOCAL_PATH)/../../Classes/TestAnalytics \
	$(LOCAL_PATH)/../../Classes/TestIAP $(LOCAL_PATH)/../../Classes/TestShare $(LOCAL_PATH)/../../Classes/TestUser

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static \
PluginProtocolStatic

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,protocols/android)

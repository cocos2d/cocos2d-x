LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := tests_shared

LOCAL_MODULE_FILENAME := libtests

LOCAL_SRC_FILES := main.cpp
                
LOCAL_SHARED_LIBRARIES := cocosdenshion_shared box2d_shared chipmunk_shared

LOCAL_STATIC_LIBRARIES := png_static_prebuilt
LOCAL_STATIC_LIBRARIES += xml2_static_prebuilt
LOCAL_STATIC_LIBRARIES += jpeg_static_prebuilt
LOCAL_STATIC_LIBRARIES += curl_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES := game_logic_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static

            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx/platform/third_party/android/modules/libcurl)
$(call import-module,cocos2dx/platform/third_party/android/modules/libpng)
$(call import-module,cocos2dx/platform/third_party/android/modules/libxml2)
$(call import-module,cocos2dx/platform/third_party/android/modules/libjpeg)

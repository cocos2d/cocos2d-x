LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_logic_static

LOCAL_MODULE_FILENAME := libgame_logic

LOCAL_SRC_FILES := \
AppDelegate.cpp \
../../lua/cocos2dx_support/CCLuaEngine.cpp \
../../lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \
../../lua/cocos2dx_support/LuaCocos2d.cpp \
../../lua/cocos2dx_support/tolua_fix.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_STATIC_LIBRARIES += xml2_static_prebuilt
LOCAL_STATIC_LIBRARIES += jpeg_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static

LOCAL_SHARED_LIBRARIES := cocosdenshion_shared lua_shared
            
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx/platform/third_party/android/modules/libpng)
$(call import-module,cocos2dx/platform/third_party/android/modules/libxml2)
$(call import-module,cocos2dx/platform/third_party/android/modules/libjpeg)


LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := extra_static
LOCAL_MODULE_FILENAME := libextra

LOCAL_SRC_FILES := \
    $(LOCAL_PATH)/luabinding/cocos2dx_extra_luabinding.cpp \
    $(LOCAL_PATH)/luabinding/HelperFunc_luabinding.cpp \
    $(LOCAL_PATH)/apptools/HelperFunc.cpp \
    $(LOCAL_PATH)/crypto/CCCrypto.cpp \
    $(LOCAL_PATH)/crypto/base64/libbase64.c \
    $(LOCAL_PATH)/network/CCHTTPRequest.cpp \
    $(LOCAL_PATH)/network/CCNetwork.cpp \
    $(LOCAL_PATH)/platform/android/CCCryptoAndroid.cpp \
    $(LOCAL_PATH)/platform/android/CCNativeAndroid.cpp \
    $(LOCAL_PATH)/platform/android/CCNetworkAndroid.cpp 


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/luabinding/ \
                           $(QUICK_V3_LIB)/lua_bindings/manual

LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES) \
                    $(COCOS2DX_CORE) \
                    $(COCOS2DX_CORE)/platform \
                    $(COCOS2DX_CORE)/platform/android \
                    $(COCOS2DX_ROOT)/external \
                    $(COCOS2DX_ROOT)/external/unzip \
                    $(COCOS2DX_ROOT)/external/xxtea \
                    $(COCOS2DX_ROOT)/external/curl/include/android \
                    $(QUICK_V3_LIB) \
                    $(QUICK_V3_LIB)/lua_bindings/luajit/include \
                    $(QUICK_V3_LIB)/lua_bindings/tolua


LOCAL_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 $(ANDROID_COCOS2D_BUILD_FLAGS) -std=c++11
LOCAL_EXPORT_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1

#LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocos_chipmunk_static

include $(BUILD_STATIC_LIBRARY)

#$(call import-module,cocos2dx)
#$(call import-module,scripting/lua/proj.android)
#$(call import-module,external/chipmunk)

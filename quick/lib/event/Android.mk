
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := event_static
LOCAL_MODULE_FILENAME := libevent

LOCAL_SRC_FILES := \
    $(LOCAL_PATH)/CCScriptEventDispatcher.cpp \
    $(LOCAL_PATH)/CCTouchTargetNode.cpp \
    $(LOCAL_PATH)/ScriptEventCenter.cpp \


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \


LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES) \
                    $(COCOS2DX_CORE) \
                    $(COCOS2DX_CORE)/platform \
                    $(COCOS2DX_CORE)/platform/android \
                    $(QUICK_V3_LIB)/lua_bindings/luajit/include \
                    $(QUICK_V3_LIB)/lua_bindings/tolua \
                    $(COCOS2DX_ROOT)/external \
                    $(COCOS2DX_ROOT)/external/unzip \
                    $(COCOS2DX_ROOT)/external/xxtea \
                    $(COCOS2DX_ROOT)/external/curl/include/android \
                    $(QUICK_V3_LIB)


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

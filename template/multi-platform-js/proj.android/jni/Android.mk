LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

LOCAL_SRC_FILES := hellojavascript/main.cpp \
                   ../../Classes/AppDelegate.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_jsb_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsb_localstorage_static

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)


$(call import-module,scripting/javascript/bindings)
$(call import-module,scripting/javascript/bindings/extension)
$(call import-module,scripting/javascript/bindings/chipmunk)
$(call import-module,scripting/javascript/bindings/localstorage)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2d_js_android_static

LOCAL_MODULE_FILENAME := libjscocos2dandroid

ifeq ($(COCOS_SIMULATOR_BUILD),1)
LOCAL_ARM_MODE := arm
endif

LOCAL_SRC_FILES := ../manual/platform/android/CCJavascriptJavaBridge.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../.. \
                    $(LOCAL_PATH)/../manual \
                    $(LOCAL_PATH)/../manual/platform/android \
                    $(LOCAL_PATH)/../../../base \

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -landroid

LOCAL_STATIC_LIBRARIES := spidermonkey_static

include $(BUILD_STATIC_LIBRARY)

#==============================================================

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2d_js_static

LOCAL_MODULE_FILENAME := libjscocos2d

LOCAL_SRC_FILES := ../auto/jsb_cocos2dx_auto.cpp \
                   ../auto/jsb_cocos2dx_extension_auto.cpp \
                   ../auto/jsb_cocos2dx_ui_auto.cpp \
                   ../manual/ScriptingCore.cpp \
                   ../manual/cocos2d_specifics.cpp \
                   ../manual/js_manual_conversions.cpp \
                   ../manual/js_bindings_core.cpp \
                   ../manual/js_bindings_opengl.cpp \
                   ../manual/jsb_opengl_functions.cpp \
                   ../manual/jsb_opengl_manual.cpp \
                   ../manual/jsb_opengl_registration.cpp \
                   ../manual/jsb_event_dispatcher_manual.cpp \
                   ../manual/chipmunk/js_bindings_chipmunk_auto_classes.cpp \
                   ../manual/chipmunk/js_bindings_chipmunk_functions.cpp \
                   ../manual/chipmunk/js_bindings_chipmunk_manual.cpp \
                   ../manual/chipmunk/js_bindings_chipmunk_registration.cpp \
                   ../manual/extension/jsb_cocos2dx_extension_manual.cpp \
                   ../manual/localstorage/js_bindings_system_functions.cpp \
                   ../manual/localstorage/js_bindings_system_registration.cpp \
                   ../manual/network/jsb_socketio.cpp \
                   ../manual/network/jsb_websocket.cpp \
                   ../manual/network/XMLHTTPRequest.cpp \
                   ../manual/ui/jsb_cocos2dx_ui_manual.cpp \
                   

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../manual \
                    $(LOCAL_PATH)/../manual/cocostudio \
                    $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../../../2d \
                    $(LOCAL_PATH)/../../../base \
                    $(LOCAL_PATH)/../../../ui \
                    $(LOCAL_PATH)/../../../audio/include \
                    $(LOCAL_PATH)/../../../storage \
                    $(LOCAL_PATH)/../../../../extensions \


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../manual \
                           $(LOCAL_PATH)/../auto \
                           $(LOCAL_PATH)/../../../audio/include \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2d_js_android_static

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocos_localstorage_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,.)
$(call import-module,storage/local-storage)

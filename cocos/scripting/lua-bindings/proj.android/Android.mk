LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2d_lua_android_static

LOCAL_MODULE_FILENAME := libluacocos2dandroid

LOCAL_SRC_FILES := ../manual/platform/android/CCLuaJavaBridge.cpp \
                   ../manual/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../.. \
                    $(LOCAL_PATH)/../manual \
                    $(LOCAL_PATH)/../manual/tolua \
                    $(LOCAL_PATH)/../manual/platform/android \
                    $(LOCAL_PATH)/../manual/platform/android/jni \

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -landroid

# don't use JIT on mips since it is not supported
ifneq ($(TARGET_ARCH_ABI),mips)
LOCAL_STATIC_LIBRARIES := cocos_luajit_static
else
LOCAL_STATIC_LIBRARIES := cocos_lua_static
endif

include $(BUILD_STATIC_LIBRARY)

#==============================================================

include $(CLEAR_VARS)

LOCAL_MODULE    := cocos2d_lua_static

LOCAL_MODULE_FILENAME := libluacocos2d

LOCAL_SRC_FILES := ../manual/CCLuaBridge.cpp \
          ../manual/CCLuaEngine.cpp \
          ../manual/CCLuaStack.cpp \
          ../manual/CCLuaValue.cpp \
          ../manual/Cocos2dxLuaLoader.cpp \
          ../manual/LuaBasicConversions.cpp \
          ../auto/lua_cocos2dx_auto.cpp \
          ../auto/lua_cocos2dx_physics_auto.cpp \
          ../auto/lua_cocos2dx_experimental_auto.cpp \
          ../manual/cocos2d/lua_cocos2dx_deprecated.cpp \
          ../manual/cocos2d/lua_cocos2dx_experimental_manual.cpp \
          ../manual/cocos2d/lua_cocos2dx_manual.cpp \
          ../manual/cocos2d/lua_cocos2dx_physics_manual.cpp \
          ../manual/cocos2d/LuaOpengl.cpp \
          ../manual/cocos2d/LuaScriptHandlerMgr.cpp \
          ../manual/tolua/tolua_fix.cpp \
          ../manual/tolua/tolua_event.c \
          ../manual/tolua/tolua_is.c \
          ../manual/tolua/tolua_map.c \
          ../manual/tolua/tolua_push.c \
          ../manual/tolua/tolua_to.c \
          ../auto/lua_cocos2dx_audioengine_auto.cpp \
          ../manual/audioengine/lua_cocos2dx_audioengine_manual.cpp

#3d
LOCAL_SRC_FILES += ../manual/3d/lua_cocos2dx_3d_manual.cpp \
                   ../auto/lua_cocos2dx_3d_auto.cpp

#cocosdenshion
LOCAL_SRC_FILES += ../manual/cocosdenshion/lua_cocos2dx_cocosdenshion_manual.cpp \
                   ../auto/lua_cocos2dx_cocosdenshion_auto.cpp

#network
LOCAL_SRC_FILES += ../manual/network/lua_cocos2dx_network_manual.cpp \
                   ../manual/network/lua_extensions.c \
                   ../manual/network/Lua_web_socket.cpp \
                   ../manual/network/lua_xml_http_request.cpp \

#ui
LOCAL_SRC_FILES += ../manual/ui/lua_cocos2dx_experimental_video_manual.cpp \
                   ../manual/ui/lua_cocos2dx_ui_manual.cpp \
                   ../auto/lua_cocos2dx_experimental_video_auto.cpp \
                   ../auto/lua_cocos2dx_ui_auto.cpp

#extension
LOCAL_SRC_FILES += ../manual/extension/lua_cocos2dx_extension_manual.cpp \
                   ../auto/lua_cocos2dx_extension_auto.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../external/android/$(TARGET_ARCH_ABI)/include \
                    $(LOCAL_PATH)/../../../2d \
                    $(LOCAL_PATH)/../../../3d \
                    $(LOCAL_PATH)/../../../network \
                    $(LOCAL_PATH)/../../../ui \
                    $(LOCAL_PATH)/../../../../extensions \
                    $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../manual \
                    $(LOCAL_PATH)/../manual/tolua \
                    $(LOCAL_PATH)/../manual/cocos2d \
                    $(LOCAL_PATH)/../manual/3d \
                    $(LOCAL_PATH)/../manual/cocosdenshion \
                    $(LOCAL_PATH)/../manual/audioengine \
                    $(LOCAL_PATH)/../manual/network \
                    $(LOCAL_PATH)/../manual/extension \
                    $(LOCAL_PATH)/../manual/ui \
                    $(LOCAL_PATH)/../../../.. \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../../external/android/$(TARGET_ARCH_ABI)/include \
                           $(LOCAL_PATH)/../auto \
                           $(LOCAL_PATH)/../manual \
                           $(LOCAL_PATH)/../manual/tolua \
                           $(LOCAL_PATH)/../manual/cocos2d \
                           $(LOCAL_PATH)/../manual/3d \
                           $(LOCAL_PATH)/../manual/cocosdenshion \
                           $(LOCAL_PATH)/../manual/audioengine \
                           $(LOCAL_PATH)/../manual/network \
                           $(LOCAL_PATH)/../manual/extension \
                           $(LOCAL_PATH)/../manual/ui \
                           $(LOCAL_PATH)/../../../..

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2d_lua_android_static

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocos_luasocket_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,.)

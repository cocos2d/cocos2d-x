LOCAL_PATH := $(call my-dir)
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
          ../manual/platform/android/CCLuaJavaBridge.cpp \
          ../manual/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp \
          ../manual/tolua_fix.cpp \
          ../../../../external/lua/tolua/tolua_event.c \
          ../../../../external/lua/tolua/tolua_is.c \
          ../../../../external/lua/tolua/tolua_map.c \
          ../../../../external/lua/tolua/tolua_push.c \
          ../../../../external/lua/tolua/tolua_to.c \
          ../../../../external/xxtea/xxtea.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../external/lua/tolua \
                    $(LOCAL_PATH)/../../../../external/lua/luajit/include \
                    $(LOCAL_PATH)/../../../2d \
                    $(LOCAL_PATH)/../../../3d \
                    $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../manual \
                    $(LOCAL_PATH)/../manual/extension \
                    $(LOCAL_PATH)/../manual/cocostudio \
                    $(LOCAL_PATH)/../manual/ui \
                    $(LOCAL_PATH)/../manual/cocos2d \
                    $(LOCAL_PATH)/../manual/platform/android \
                    $(LOCAL_PATH)/../manual/platform/android/jni \
                    $(LOCAL_PATH)/../../../../external/xxtea \
                    $(LOCAL_PATH)/../../../.. \
                    $(LOCAL_PATH)/../../../../extensions 


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../../external/lua/tolua \
                           $(LOCAL_PATH)/../../../../external/lua/luajit/include \
                           $(LOCAL_PATH)/../auto \
                           $(LOCAL_PATH)/../manual \
                           $(LOCAL_PATH)/../manual/cocos2d 


LOCAL_STATIC_LIBRARIES := luajit_static
LOCAL_STATIC_LIBRARIES += cocos2dx_static

include $(BUILD_STATIC_LIBRARY)

#libluacocos3d
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos3d_lua_static

LOCAL_MODULE_FILENAME := libluacocos3d

LOCAL_SRC_FILES := ../manual/3d/lua_cocos2dx_3d_manual.cpp \
                   ../auto/lua_cocos2dx_3d_auto.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../manual/3d \
                    $(LOCAL_PATH)/../../../3d \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../manual/3d 

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += cocos3d_static

include $(BUILD_STATIC_LIBRARY)

#libluacocosdenshion
include $(CLEAR_VARS)

LOCAL_MODULE    := cocosdenshion_lua_static

LOCAL_MODULE_FILENAME := libluacocosdenshion

LOCAL_SRC_FILES := ../manual/cocosdenshion/lua_cocos2dx_cocosdenshion_manual.cpp \
                   ../auto/lua_cocos2dx_cocosdenshion_auto.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../manual/cocosdenshion \
                    $(LOCAL_PATH)/../../../audio/include \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../manual/cocosdenshion 

LOCAL_STATIC_LIBRARIES := cocosdenshion_static
LOCAL_STATIC_LIBRARIES += cocos2d_lua_static

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := network_lua_static

LOCAL_MODULE_FILENAME := libluanetwork

LOCAL_SRC_FILES := ../manual/network/lua_cocos2dx_network_manual.cpp \
                   ../manual/network/lua_extensions.c \
                   ../manual/network/Lua_web_socket.cpp \
                   ../manual/network/lua_xml_http_request.cpp \
                   ../../../../external/lua/luasocket/auxiliar.c \
                   ../../../../external/lua/luasocket/buffer.c \
                   ../../../../external/lua/luasocket/except.c \
                   ../../../../external/lua/luasocket/inet.c \
                   ../../../../external/lua/luasocket/io.c \
                   ../../../../external/lua/luasocket/luasocket.c \
                   ../../../../external/lua/luasocket/mime.c \
                   ../../../../external/lua/luasocket/options.c \
                   ../../../../external/lua/luasocket/select.c \
                   ../../../../external/lua/luasocket/serial.c \
                   ../../../../external/lua/luasocket/tcp.c \
                   ../../../../external/lua/luasocket/timeout.c \
                   ../../../../external/lua/luasocket/udp.c \
                   ../../../../external/lua/luasocket/unix.c \
                   ../../../../external/lua/luasocket/usocket.c \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../manual/network \
                    $(LOCAL_PATH)/../../../../external/lua \
                    $(LOCAL_PATH)/../../../network

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../manual/network

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += cocos_network_static

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := cocosbuilder_lua_static

LOCAL_MODULE_FILENAME := libluacocosbuilder

LOCAL_SRC_FILES := ../manual/cocosbuilder/lua_cocos2dx_cocosbuilder_manual.cpp \
                   ../manual/cocosbuilder/CCBProxy.cpp \
                   ../auto/lua_cocos2dx_cocosbuilder_auto.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../manual/cocosbuilder \
                    $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../../../editor-support/cocosbuilder

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../manual/cocosbuilder

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += cocosbuilder_static

include $(BUILD_STATIC_LIBRARY)


#
include $(CLEAR_VARS)

LOCAL_MODULE    := cocostudio_lua_static

LOCAL_MODULE_FILENAME := libluacocostudio

LOCAL_SRC_FILES := ../manual/cocostudio/lua_cocos2dx_coco_studio_manual.cpp \
                   ../auto/lua_cocos2dx_studio_auto.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../manual/cocostudio \
                    $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../../../editor-support/cocostudio

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../manual/cocostudio

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += cocostudio_static

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := spine_lua_static

LOCAL_MODULE_FILENAME := libluaspine

LOCAL_SRC_FILES := ../manual/spine/lua_cocos2dx_spine_manual.cpp \
                   ../manual/spine/LuaSkeletonAnimation.cpp \
                   ../auto/lua_cocos2dx_spine_auto.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../manual/spine \
                    $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../../../editor-support/spine

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../manual/spine

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += spine_static

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := extension_lua_static

LOCAL_MODULE_FILENAME := libluaextension

LOCAL_SRC_FILES := ../manual/extension/lua_cocos2dx_extension_manual.cpp \
                   ../auto/lua_cocos2dx_extension_auto.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../manual/extension \
                    $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../../../../extensions


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../manual/extension

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := ui_lua_static

LOCAL_MODULE_FILENAME := libluaui

LOCAL_SRC_FILES := ../manual/ui/lua_cocos2dx_experimental_video_manual.cpp \
                   ../manual/ui/lua_cocos2dx_ui_manual.cpp \
                   ../auto/lua_cocos2dx_experimental_video_auto.cpp \
                   ../auto/lua_cocos2dx_ui_auto.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../manual/ui \
                    $(LOCAL_PATH)/../auto \
                    $(LOCAL_PATH)/../../../ui
                    

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../manual/ui

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += cocos_ui_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,lua/luajit/prebuilt/android)
$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,network)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/cocostudio)
$(call import-module,editor-support/spine)
$(call import-module,ui)
$(call import-module,extensions)
$(call import-module,3d)



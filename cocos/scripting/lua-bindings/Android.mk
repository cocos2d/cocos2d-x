LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_lua_static

LOCAL_MODULE_FILENAME := liblua

LOCAL_SRC_FILES := manual/CCLuaBridge.cpp \
          manual/CCLuaEngine.cpp \
          manual/CCLuaStack.cpp \
          manual/lua_debugger.c \
          manual/CCLuaValue.cpp \
          manual/Cocos2dxLuaLoader.cpp \
          manual/CCBProxy.cpp \
          manual/Lua_web_socket.cpp \
          manual/LuaOpengl.cpp \
          manual/LuaScriptHandlerMgr.cpp \
          manual/LuaBasicConversions.cpp \
          manual/LuaSkeletonAnimation.cpp \
          manual/lua_cocos2dx_manual.cpp \
          manual/lua_cocos2dx_extension_manual.cpp \
          manual/lua_cocos2dx_coco_studio_manual.cpp \
          manual/lua_cocos2dx_gui_manual.cpp \
          manual/lua_cocos2dx_spine_manual.cpp \
          manual/lua_cocos2dx_physics_manual.cpp \
          manual/lua_cocos2dx_deprecated.cpp \
          manual/lua_xml_http_request.cpp \
          manual/platform/android/CCLuaJavaBridge.cpp \
          manual/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp \
          manual/tolua_fix.cpp \
          manual/lua_extensions.c \
          auto/lua_cocos2dx_auto.cpp \
          auto/lua_cocos2dx_extension_auto.cpp \
          auto/lua_cocos2dx_studio_auto.cpp \
          auto/lua_cocos2dx_gui_auto.cpp \
          auto/lua_cocos2dx_spine_auto.cpp \
          auto/lua_cocos2dx_physics_auto.cpp \
          ../external/tolua/tolua_event.c \
          ../external/tolua/tolua_is.c \
          ../external/tolua/tolua_map.c \
          ../external/tolua/tolua_push.c \
          ../external/tolua/tolua_to.c \
          ../external/luasocket/auxiliar.c \
          ../external/luasocket/luasocket_buffer.c \
          ../external/luasocket/except.c \
          ../external/luasocket/inet.c \
          ../external/luasocket/luasocket_io.c \
          ../external/luasocket/luasocket.c \
          ../external/luasocket/mime.c \
          ../external/luasocket/options.c \
          ../external/luasocket/select.c \
          ../external/luasocket/serial.c \
          ../external/luasocket/socket_scripts.c \
          ../external/luasocket/tcp.c \
          ../external/luasocket/timeout.c \
          ../external/luasocket/udp.c \
          ../external/luasocket/unix.c \
          ../external/luasocket/usocket.c


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../external/tolua \
                    $(LOCAL_PATH)/../external/luajit/include \
                    $(LOCAL_PATH)/../external \
                    $(LOCAL_PATH)/../cocos2d-x/extensions \
                    $(LOCAL_PATH)/../cocos2d-x/cocos/editor-support/spine \
                    $(LOCAL_PATH)/../cocos2d-x/cocos/editor-support/cocosbuilder \
                    $(LOCAL_PATH)/../cocos2d-x/cocos/editor-support/cocostudio \
                    $(LOCAL_PATH)/../cocos2d-x/cocos/gui \
                    $(LOCAL_PATH)/auto \
                    $(LOCAL_PATH)/manual \
                    $(LOCAL_PATH)/manual/platform/android \
                    $(LOCAL_PATH)/manual/platform/android/jni


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../external/tolua \
                           $(LOCAL_PATH)/../external/luajit/include \
                           $(LOCAL_PATH)/../external \
                           $(LOCAL_PATH)/auto \
                           $(LOCAL_PATH)/manual


LOCAL_WHOLE_STATIC_LIBRARIES := luajit_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += websockets_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static

LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

include $(BUILD_STATIC_LIBRARY)

$(call import-module,luajit/prebuilt/android)
$(call import-module,extensions)
$(call import-module,2d)
$(call import-module,websockets/prebuilt/android)
$(call import-module,network)
$(call import-module,editor-support/cocostudio)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)

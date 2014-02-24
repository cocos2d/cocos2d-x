LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_lua_static

LOCAL_MODULE_FILENAME := liblua

LOCAL_SRC_FILES := CCLuaBridge.cpp \
          CCLuaEngine.cpp \
          CCLuaStack.cpp \
          CCLuaValue.cpp \
          Cocos2dxLuaLoader.cpp \
          CCBProxy.cpp \
          Lua_web_socket.cpp \
          LuaOpengl.cpp \
          LuaScriptHandlerMgr.cpp \
          LuaBasicConversions.cpp \
          LuaSkeletonAnimation.cpp \
          ../../auto-generated/lua-bindings/lua_cocos2dx_auto.cpp \
          ../../auto-generated/lua-bindings/lua_cocos2dx_extension_auto.cpp \
          ../../auto-generated/lua-bindings/lua_cocos2dx_studio_auto.cpp \
          ../../auto-generated/lua-bindings/lua_cocos2dx_gui_auto.cpp \
          ../../auto-generated/lua-bindings/lua_cocos2dx_spine_auto.cpp \
          ../../auto-generated/lua-bindings/lua_cocos2dx_physics_auto.cpp \
          lua_cocos2dx_manual.cpp \
          lua_cocos2dx_extension_manual.cpp \
          lua_cocos2dx_coco_studio_manual.cpp \
          lua_cocos2dx_gui_manual.cpp \
          lua_cocos2dx_spine_manual.cpp \
          lua_cocos2dx_physics_manual.cpp \
          lua_cocos2dx_deprecated.cpp \
          lua_xml_http_request.cpp \
          platform/android/CCLuaJavaBridge.cpp \
          platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp \
          ../../../../external/lua/tolua/tolua_event.c \
          ../../../../external/lua/tolua/tolua_is.c \
          ../../../../external/lua/tolua/tolua_map.c \
          ../../../../external/lua/tolua/tolua_push.c \
          ../../../../external/lua/tolua/tolua_to.c \
          tolua_fix.c \
          socket/auxiliar.c \
          socket/luasocket_buffer.c \
          socket/except.c \
          socket/inet.c \
          socket/luasocket_io.c \
          socket/luasocket.c \
          socket/mime.c \
          socket/options.c \
          socket/select.c \
          socket/serial.c \
          socket/socket_scripts.c \
          socket/tcp.c \
          socket/timeout.c \
          socket/udp.c \
          socket/unix.c \
          socket/usocket.c \
          lua_extensions.c


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../external/lua/tolua \
                    $(LOCAL_PATH)/../../auto-generated/lua-bindings \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/platform/android/jni \
                    $(LOCAL_PATH)/../../../../extensions \
                    $(LOCAL_PATH)/../../../editor-support/cocosbuilder \
                    $(LOCAL_PATH)/../../../editor-support/cocostudio \
                    $(LOCAL_PATH)/../../../editor-support/spine \
                    $(LOCAL_PATH)/../../../gui


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)


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

$(call import-module,lua/luajit/prebuilt/android)
$(call import-module,extensions)
$(call import-module,2d)
$(call import-module,websockets/prebuilt/android)
$(call import-module,network)
$(call import-module,editor-support/cocostudio)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)

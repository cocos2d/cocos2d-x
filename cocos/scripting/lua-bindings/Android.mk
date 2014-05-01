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
          manual/lua_cocos2dx_ui_manual.cpp \
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
          auto/lua_cocos2dx_ui_auto.cpp \
          auto/lua_cocos2dx_spine_auto.cpp \
          auto/lua_cocos2dx_physics_auto.cpp \
          ../../../external/lua/tolua/tolua_event.c \
          ../../../external/lua/tolua/tolua_is.c \
          ../../../external/lua/tolua/tolua_map.c \
          ../../../external/lua/tolua/tolua_push.c \
          ../../../external/lua/tolua/tolua_to.c \
          ../../../external/lua/luasocket/auxiliar.c \
          ../../../external/lua/luasocket/buffer.c \
          ../../../external/lua/luasocket/except.c \
          ../../../external/lua/luasocket/inet.c \
          ../../../external/lua/luasocket/io.c \
          ../../../external/lua/luasocket/luasocket.c \
          ../../../external/lua/luasocket/mime.c \
          ../../../external/lua/luasocket/options.c \
          ../../../external/lua/luasocket/select.c \
          ../../../external/lua/luasocket/serial.c \
          ../../../external/lua/luasocket/tcp.c \
          ../../../external/lua/luasocket/timeout.c \
          ../../../external/lua/luasocket/udp.c \
          ../../../external/lua/luasocket/unix.c \
          ../../../external/lua/luasocket/usocket.c


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../external/lua/tolua \
                    $(LOCAL_PATH)/../../../external/lua/luajit/include \
                    $(LOCAL_PATH)/../../../external/lua \
                    $(LOCAL_PATH)/../../../extensions \
                    $(LOCAL_PATH)/../../editor-support/spine \
                    $(LOCAL_PATH)/../../editor-support/cocosbuilder \
                    $(LOCAL_PATH)/../../editor-support/cocostudio \
                    $(LOCAL_PATH)/../../ui \
                    $(LOCAL_PATH)/auto \
                    $(LOCAL_PATH)/manual \
                    $(LOCAL_PATH)/manual/platform/android \
                    $(LOCAL_PATH)/manual/platform/android/jni


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../external/lua/tolua \
                           $(LOCAL_PATH)/../../../external/lua/luajit/include \
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

$(call import-module,lua/luajit/prebuilt/android)
$(call import-module,extensions)
$(call import-module,.)
$(call import-module,websockets/prebuilt/android)
$(call import-module,network)
$(call import-module,editor-support/cocostudio)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)

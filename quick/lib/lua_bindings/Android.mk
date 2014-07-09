LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_lua_static

LOCAL_MODULE_FILENAME := liblua

LOCAL_SRC_FILES := $(LOCAL_PATH)/manual/CCLuaBridge.cpp \
          $(LOCAL_PATH)/manual/CCLuaEngine.cpp \
          $(LOCAL_PATH)/manual/CCLuaStack.cpp \
          $(LOCAL_PATH)/manual/CCLuaValue.cpp \
          $(LOCAL_PATH)/manual/Cocos2dxLuaLoader.cpp \
          $(LOCAL_PATH)/manual/LuaScriptHandlerMgr.cpp \
          $(LOCAL_PATH)/manual/LuaBasicConversions.cpp \
          $(LOCAL_PATH)/manual/lua_cocos2dx_manual.cpp \
          $(LOCAL_PATH)/manual/lua_cocos2dx_extension_manual.cpp \
          $(LOCAL_PATH)/manual/lua_cocos2dx_external_extra_manual.cpp \
          $(LOCAL_PATH)/manual/lua_cocos2dx_physics_manual.cpp \
          $(LOCAL_PATH)/manual/lua_cocos2dx_deprecated.cpp \
          $(LOCAL_PATH)/manual/platform/android/CCLuaJavaBridge.cpp \
          $(LOCAL_PATH)/manual/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp \
          $(LOCAL_PATH)/manual/tolua_fix.cpp \
          $(LOCAL_PATH)/auto/lua_cocos2dx_auto.cpp \
          $(LOCAL_PATH)/auto/lua_cocos2dx_extension_auto.cpp \
          $(LOCAL_PATH)/auto/lua_cocos2dx_extra_auto.cpp \
          $(LOCAL_PATH)/auto/lua_cocos2dx_physics_auto.cpp \
          $(LOCAL_PATH)/tolua/tolua_event.c \
          $(LOCAL_PATH)/tolua/tolua_is.c \
          $(LOCAL_PATH)/tolua/tolua_map.c \
          $(LOCAL_PATH)/tolua/tolua_push.c \
          $(LOCAL_PATH)/tolua/tolua_to.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/auxiliar.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/except.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/inet.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/luasocket.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/luasocket_buffer.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/luasocket_io.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/mime.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/options.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/select.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/serial.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/socket_scripts.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/tcp.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/timeout.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/udp.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/unix.c \
          $(QUICK_V3_LIB)/lua_extensions/socket/usocket.c \
          $(COCOS2DX_ROOT)/external/xxtea/xxtea.cpp


LOCAL_C_INCLUDES := $(COCOS2DX_ROOT)/external/lua/tolua \
                    $(COCOS2DX_ROOT)/external/lua/luajit/include \
                    $(COCOS2DX_ROOT)/external/lua \
                    $(COCOS2DX_ROOT)/extensions \
                    $(COCOS2DX_CORE)/editor-support/spine \
                    $(COCOS2DX_CORE)/editor-support/cocosbuilder \
                    $(COCOS2DX_CORE)/editor-support/cocostudio \
                    $(COCOS2DX_CORE)/ui \
                    $(LOCAL_PATH)/auto \
                    $(LOCAL_PATH)/manual \
                    $(LOCAL_PATH)/manual/platform/android \
                    $(LOCAL_PATH)/manual/platform/android/jni \
                    $(QUICK_V3_LIB)/lua_extensions \
                    $(QUICK_V3_LIB) \
                    $(QUICK_V3_LIB)/extra \
                    $(QUICK_V3_LIB)/extra/native \
                    $(QUICK_V3_LIB)/extra/crypto \
                    $(QUICK_V3_LIB)/extra/network \
                    $(QUICK_V3_LIB)/external \
                    $(QUICK_V3_LIB)/lua_bindings/tolua \
                    $(COCOS2DX_ROOT)/external/xxtea


LOCAL_EXPORT_C_INCLUDES := $(COCOS2DX_ROOT)/external/lua/tolua \
                           $(COCOS2DX_ROOT)/external/lua/luajit/include \
                           $(QUICK_V3_LIB) \
                           $(QUICK_V3_LIB)/lua_extensions \
                           $(LOCAL_PATH)/auto \
                           $(LOCAL_PATH)/manual


LOCAL_WHOLE_STATIC_LIBRARIES := luajit_static
LOCAL_WHOLE_STATIC_LIBRARIES += lua_extensions_static
LOCAL_WHOLE_STATIC_LIBRARIES += extra_static
LOCAL_WHOLE_STATIC_LIBRARIES += event_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += websockets_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
#LOCAL_WHOLE_STATIC_LIBRARIES += spine_static

LOCAL_CFLAGS += -Wno-psabi -DCC_LUA_ENGINE_ENABLED=1
LOCAL_EXPORT_CFLAGS += -Wno-psabi

include $(BUILD_STATIC_LIBRARY)

$(call import-module,lua_bindings/luajit)
$(call import-module,lua_extensions)
$(call import-module,extra)
$(call import-module,event)
$(call import-module,extensions)
$(call import-module,.)
$(call import-module,websockets/prebuilt/android)
#$(call import-module,editor-support/cocostudio)
#$(call import-module,editor-support/cocosbuilder)
#$(call import-module,editor-support/spine)

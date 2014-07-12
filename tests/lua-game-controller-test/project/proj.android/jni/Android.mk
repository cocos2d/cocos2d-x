LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := lua_game_controller_test_shared

LOCAL_MODULE_FILENAME := liblua_game_controller

LOCAL_SRC_FILES := main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../../../../cocos/scripting/lua-bindings/auto/lua_cocos2dx_controller_auto.cpp \
                   ../../../../../cocos/scripting/lua-bindings/manual/lua_cocos2dx_controller_manual.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../../../../external/lua/tolua \
                    $(LOCAL_PATH)/../../../../../cocos/scripting/lua-bindings/auto \
                    $(LOCAL_PATH)/../../../../../cocos/scripting/lua-bindings/manual \
                    $(LOCAL_PATH)/../../../../../cocos/base

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_lua_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings)

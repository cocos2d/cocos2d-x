LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dlua_shared

LOCAL_MODULE_FILENAME := libcocos2dlua

ifeq ($(COCOS_SIMULATOR_BUILD),1)
LOCAL_ARM_MODE := arm
endif

FILE_LIST := hellolua/main.cpp
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ide-support/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ide-support/*.c)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../Classes/protobuf-lite \
$(LOCAL_PATH)/../../Classes/runtime \
$(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../../../../../external \
$(LOCAL_PATH)/../../../../../../tools/simulator/libsimulator/lib \
$(LOCAL_PATH)/../../../../../../tools/simulator/libsimulator/lib/protobuf-lite

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static 
LOCAL_STATIC_LIBRARIES += cocos2d_simulator_static
LOCAL_STATIC_LIBRARIES += cocos2d_js_static

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings/proj.android)
$(call import-module,scripting/js-bindings/proj.android)
$(call import-module,tools/simulator/libsimulator/proj.android)

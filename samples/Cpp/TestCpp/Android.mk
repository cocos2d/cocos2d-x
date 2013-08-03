LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_testcpp_common

LOCAL_MODULE_FILENAME := libtestcppcommon

dirs := $(shell find $(LOCAL_PATH)/Classes -type d -print)
find_files = $(subst $(LOCAL_PATH)/,,$(wildcard $(dir)/*.cpp)) 

LOCAL_SRC_FILES := $(foreach dir, $(dirs), $(find_files))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
            
include $(BUILD_STATIC_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,cocos2dx)
$(call import-module,extensions)

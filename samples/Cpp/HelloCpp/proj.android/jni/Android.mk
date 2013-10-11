LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

MY_FILES_PATH  :=  $(LOCAL_PATH) \
                   $(LOCAL_PATH)/../../Classes

MY_FILES_SUFFIX := %.cpp %.c
					   
# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
	
# Retrieve all source files in each dir recursively.
MY_ALL_FILES := $(foreach src_path,$(MY_FILES_PATH), $(call rwildcard,$(src_path),*.*) ) 
MY_ALL_FILES := $(MY_ALL_FILES:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)
MY_SRC_LIST  := $(filter $(MY_FILES_SUFFIX),$(MY_ALL_FILES)) 
MY_SRC_LIST  := $(MY_SRC_LIST:$(LOCAL_PATH)/%=%)

# helper function for remove duplicated words in string
define uniq =
  $(eval seen :=)
  $(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
  ${seen}
endef
	
# Retrieve all directory recursively.
MY_ALL_DIRS := $(dir $(foreach src_path,$(MY_FILES_PATH), $(call rwildcard,$(src_path),*/) ) )
MY_ALL_DIRS := $(call uniq,$(MY_ALL_DIRS))

# All done, just tell NDK build system.
LOCAL_SRC_FILES  := $(MY_SRC_LIST)
LOCAL_C_INCLUDES := $(MY_ALL_DIRS)

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocos2dxandroid_static cocosdenshion_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,audio/android)
$(call import-module,cocos2dx/platform/android)

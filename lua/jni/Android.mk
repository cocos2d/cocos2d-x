LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := lua
LOCAL_SRC_FILES :=../src/lapi.c \
                  ../src/lauxlib.c \
		  ../src/lbaselib.c \
		  ../src/lcode.c \
		  ../src/ldblib.c \
		  ../src/ldebug.c \
		  ../src/ldo.c \
		  ../src/ldump.c \
		  ../src/lfunc.c \
		  ../src/lgc.c \
		  ../src/linit.c \
		  ../src/liolib.c \
		  ../src/llex.c \
		  ../src/lmathlib.c \
		  ../src/lmem.c \
		  ../src/loadlib.c \
		  ../src/lobject.c \
		  ../src/lopcodes.c \
		  ../src/loslib.c \
		  ../src/lparser.c \
		  ../src/lstate.c \
		  ../src/lstring.c \
		  ../src/lstrlib.c \
		  ../src/ltable.c \
		  ../src/ltablib.c \
		  ../src/ltm.c \
		  ../src/lua.c \
		  ../src/luac.c \
		  ../src/lundump.c \
		  ../src/lvm.c \
		  ../src/lzio.c \
		  ../src/print.c \
		  ../tolua/tolua_event.c \
		  ../tolua/tolua_is.c \
		  ../tolua/tolua_map.c \
		  ../tolua/tolua_push.c \
		  ../tolua/tolua_to.c
		  
		  
LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/../src 
                    

include $(BUILD_STATIC_LIBRARY)

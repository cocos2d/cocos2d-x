
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := lua515_static
LOCAL_MODULE_FILENAME := liblua515

LOCAL_SRC_FILES := \
    lapi.c \
    lauxlib.c \
    lbaselib.c \
    lcode.c \
    ldblib.c \
    ldebug.c \
    ldo.c \
    ldump.c \
    lfunc.c \
    lgc.c \
    linit.c \
    liolib.c \
    llex.c \
    lmathlib.c \
    lmem.c \
    loadlib.c \
    lobject.c \
    lopcodes.c \
    loslib.c \
    lparser.c \
    lstate.c \
    lstring.c \
    lstrlib.c \
    ltable.c \
    ltablib.c \
    ltm.c \
    lundump.c \
    lvm.c \
    lzio.c \
    print.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_CFLAGS += $(ANDROID_COCOS2D_BUILD_FLAGS)

include $(BUILD_STATIC_LIBRARY)
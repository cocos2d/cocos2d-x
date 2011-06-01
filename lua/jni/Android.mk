# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
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
                    $(LOCAL_PATH)/../src \
                    $(LOCAL_PATH)/../tolua
#LOCAL_PRELINK_MODULE := false

include $(BUILD_STATIC_LIBRARY)

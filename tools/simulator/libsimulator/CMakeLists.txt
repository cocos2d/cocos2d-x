#/****************************************************************************
# Copyright (c) 2014-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

set(SIMULATOR_LIB_PATH ${COCOS2DX_ROOT_PATH}/tools/simulator/libsimulator/lib)

if(WINDOWS)
    set(PLATFORM_HEADER
        ${SIMULATOR_LIB_PATH}/../proj.win32/stdafx.h
        ${SIMULATOR_LIB_PATH}/../proj.win32/targetver.h
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerMessageBoxServiceWin.h
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerMenuServiceWin.h
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerWin.h
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerEditBoxServiceWin.h
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerFileDialogServiceWin.h
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerTaskServiceWin.h
        )
    set(PLATFORM_SOURCE
        ${SIMULATOR_LIB_PATH}/../proj.win32/Runtime_win32.cpp
        ${SIMULATOR_LIB_PATH}/../proj.win32/stdafx.cpp
        ${SIMULATOR_LIB_PATH}/platform/win32/DeviceEx-win32.cpp
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerEditBoxServiceWin.cpp
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerFileDialogServiceWin.cpp
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerMenuServiceWin.cpp
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerMessageBoxServiceWin.cpp
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerTaskServiceWin.cpp
        ${SIMULATOR_LIB_PATH}/platform/win32/PlayerWin.cpp
        )
elseif(MACOSX)
    set(PLATFORM_HEADER
        ${SIMULATOR_LIB_PATH}/platform/mac/openudid/OpenUDIDMac.h
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerMessageBoxServiceMac.h
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerEditBoxServiceMac.h
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerMac.h
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerMenuServiceMac.h
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerTaskServiceMac.h
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerFileDialogServiceMac.h
        )
    set(PLATFORM_SOURCE
        ${SIMULATOR_LIB_PATH}/platform/mac/DeviceEx-mac.mm
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerEditBoxServiceMac.mm
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerFileDialogServiceMac.mm
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerMac.mm
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerMenuServiceMac.mm
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerMessageBoxServiceMac.mm
        ${SIMULATOR_LIB_PATH}/platform/mac/PlayerTaskServiceMac.mm
        ${SIMULATOR_LIB_PATH}/platform/mac/Runtime_ios-mac.mm
        ${SIMULATOR_LIB_PATH}/platform/mac/openudid/OpenUDIDMac.m
        )
endif()

set(PROTOBUF_HEADER
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/stl_util.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/atomicops_internals_arm_gcc.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/template_util.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/atomicops_internals_macosx.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/stringprintf.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/atomicops.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/atomicops_internals_x86_gcc.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/atomicops_internals_x86_msvc.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/atomicops_internals_generic_gcc.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/common.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/platform_macros.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/once.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/type_traits.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/atomicops_internals_atomicword_compat.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/map-util.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/hash.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/repeated_field.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/io/zero_copy_stream_impl.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/io/coded_stream_inl.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/io/zero_copy_stream_impl_lite.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/io/zero_copy_stream.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/io/coded_stream.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/wire_format_lite_inl.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/extension_set.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/message_lite.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/generated_message_util.h
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/wire_format_lite.h
    )

set(PROTOBUF_SOURCE
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/extension_set.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/generated_message_util.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/io/coded_stream.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/io/zero_copy_stream.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/io/zero_copy_stream_impl_lite.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/message_lite.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/repeated_field.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/atomicops_internals_x86_msvc.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/common.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/once.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/stubs/stringprintf.cc
    ${SIMULATOR_LIB_PATH}/protobuf-lite/google/protobuf/wire_format_lite.cc
    )

set(SIMULATOR_HEADER
    ${SIMULATOR_LIB_PATH}/cocos2dx_extra.h
    ${SIMULATOR_LIB_PATH}/AppLang.h
    ${SIMULATOR_LIB_PATH}/PlayerMenuServiceProtocol.h
    ${SIMULATOR_LIB_PATH}/DeviceEx.h
    ${SIMULATOR_LIB_PATH}/SimulatorExport.h
    ${SIMULATOR_LIB_PATH}/network/CCHTTPRequestDelegate.h
    ${SIMULATOR_LIB_PATH}/network/CCHTTPRequest.h
    ${SIMULATOR_LIB_PATH}/runtime/Widget_mac.h
    ${SIMULATOR_LIB_PATH}/runtime/FileServer.h
    ${SIMULATOR_LIB_PATH}/runtime/ConfigParser.h
    ${SIMULATOR_LIB_PATH}/runtime/ConsoleCommand.h
    ${SIMULATOR_LIB_PATH}/runtime/RuntimeCCSImpl.h
    ${SIMULATOR_LIB_PATH}/runtime/Runtime.h
    ${SIMULATOR_LIB_PATH}/runtime/ResData.h
    ${SIMULATOR_LIB_PATH}/runtime/ConnectWaitLayer.h
    ${SIMULATOR_LIB_PATH}/runtime/RuntimeProtocol.h
    ${SIMULATOR_LIB_PATH}/runtime/Protos.pb.h
    ${SIMULATOR_LIB_PATH}/runtime/VisibleRect.h
    ${SIMULATOR_LIB_PATH}/PlayerSettings.h
    ${SIMULATOR_LIB_PATH}/PlayerEditBoxServiceProtocol.h
    ${SIMULATOR_LIB_PATH}/PlayerMessageBoxServiceProtocol.h
    ${SIMULATOR_LIB_PATH}/AppEvent.h
    ${SIMULATOR_LIB_PATH}/PlayerProtocol.h
    ${SIMULATOR_LIB_PATH}/PlayerMacros.h
    ${SIMULATOR_LIB_PATH}/PlayerFileDialogServiceProtocol.h
    ${SIMULATOR_LIB_PATH}/ProjectConfig/SimulatorConfig.h
    ${SIMULATOR_LIB_PATH}/ProjectConfig/ProjectConfig.h
    ${SIMULATOR_LIB_PATH}/PlayerServiceProtocol.h
    ${SIMULATOR_LIB_PATH}/PlayerUtils.h
    ${SIMULATOR_LIB_PATH}/PlayerTaskServiceProtocol.h
    ${PROTOBUF_HEADER}
    ${PLATFORM_HEADER}
    )

set(SIMULATOR_SOURCE
    ${SIMULATOR_LIB_PATH}/network/CCHTTPRequest.cpp
    ${SIMULATOR_LIB_PATH}/ProjectConfig/ProjectConfig.cpp
    ${SIMULATOR_LIB_PATH}/ProjectConfig/SimulatorConfig.cpp
    ${SIMULATOR_LIB_PATH}/AppEvent.cpp
    ${SIMULATOR_LIB_PATH}/AppLang.cpp
    ${SIMULATOR_LIB_PATH}/PlayerMenuServiceProtocol.cpp
    ${SIMULATOR_LIB_PATH}/PlayerProtocol.cpp
    ${SIMULATOR_LIB_PATH}/PlayerServiceProtocol.cpp
    ${SIMULATOR_LIB_PATH}/PlayerSettings.cpp
    ${SIMULATOR_LIB_PATH}/PlayerTaskServiceProtocol.cpp
    ${SIMULATOR_LIB_PATH}/PlayerUtils.cpp
    ${SIMULATOR_LIB_PATH}/runtime/ConfigParser.cpp
    ${SIMULATOR_LIB_PATH}/runtime/ConnectWaitLayer.cpp
    ${SIMULATOR_LIB_PATH}/runtime/ConsoleCommand.cpp
    ${SIMULATOR_LIB_PATH}/runtime/FileServer.cpp
    ${SIMULATOR_LIB_PATH}/runtime/Landscape_png.cpp
    ${SIMULATOR_LIB_PATH}/runtime/PlayDisable_png.cpp
    ${SIMULATOR_LIB_PATH}/runtime/PlayEnable_png.cpp
    ${SIMULATOR_LIB_PATH}/runtime/Portrait_png.cpp
    ${SIMULATOR_LIB_PATH}/runtime/Protos.pb.cc
    ${SIMULATOR_LIB_PATH}/runtime/Runtime.cpp
    ${SIMULATOR_LIB_PATH}/runtime/RuntimeCCSImpl.cpp
    ${SIMULATOR_LIB_PATH}/runtime/RuntimeProtocol.cpp
    ${SIMULATOR_LIB_PATH}/runtime/Shine_png.cpp
    ${SIMULATOR_LIB_PATH}/runtime/VisibleRect.cpp
    ${PROTOBUF_SOURCE}
    ${PLATFORM_SOURCE}
    )


set(LIB_SOURCE ${SIMULATOR_SOURCE} ${SIMULATOR_HEADER})

add_library(simulatorlib STATIC ${LIB_SOURCE})
target_link_libraries(simulatorlib cocos2d)

if(WINDOWS)
    target_compile_definitions(simulatorlib
        PUBLIC _USRLIBSIMSTATIC
        PRIVATE _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
    )
    target_include_directories(simulatorlib
        PRIVATE ${SIMULATOR_LIB_PATH}/../proj.win32
    )
endif()

target_include_directories(simulatorlib
        PRIVATE ${SIMULATOR_LIB_PATH}
        PRIVATE ${SIMULATOR_LIB_PATH}/platform/${PLATFORM_FOLDER}
        PRIVATE ${SIMULATOR_LIB_PATH}/protobuf-lite
        PRIVATE ${SIMULATOR_LIB_PATH}/runtime
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/editor-support
)

set_target_properties(simulatorlib
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      FOLDER "Internal"
                      )

if(XCODE OR VS)
    cocos_mark_code_files("simulatorlib")
endif()

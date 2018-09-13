#/****************************************************************************
# Copyright (c) 2015-2017 Chukong Technologies Inc.
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

if(WINDOWS)
    set(COCOS_PLATFORM_SPECIFIC_HEADER
        platform/win32/compat/stdint.h
        platform/win32/CCApplication-win32.h
        platform/win32/inet_pton_mingw.h
        platform/win32/CCGL-win32.h
        platform/win32/CCFileUtils-win32.h
        platform/win32/CCStdC-win32.h
        platform/win32/CCPlatformDefine-win32.h
        platform/win32/CCUtils-win32.h
        platform/desktop/CCGLViewImpl-desktop.h
        )
    set(COCOS_PLATFORM_SPECIFIC_SRC
        platform/win32/CCStdC-win32.cpp
        platform/win32/CCUtils-win32.cpp
        platform/win32/CCFileUtils-win32.cpp
        platform/win32/CCCommon-win32.cpp
        platform/win32/CCApplication-win32.cpp
        platform/win32/CCDevice-win32.cpp
        platform/win32/inet_pton_mingw.cpp
        platform/desktop/CCGLViewImpl-desktop.cpp
        )

elseif(APPLE)
    set(COCOS_PLATFORM_SPECIFIC_HEADER
        platform/apple/CCFileUtils-apple.h
        platform/apple/CCLock-apple.h
        platform/apple/CCDevice-apple.h
        )
    set(COCOS_PLATFORM_SPECIFIC_SRC
        platform/apple/CCLock-apple.cpp
        platform/apple/CCFileUtils-apple.mm
        platform/apple/CCThread-apple.mm
        platform/apple/CCDevice-apple.mm
        )
    if(MACOSX)
        set(COCOS_PLATFORM_SPECIFIC_HEADER
            ${COCOS_PLATFORM_SPECIFIC_HEADER}
            platform/mac/CCStdC-mac.h
            platform/mac/CCPlatformDefine-mac.h
            platform/mac/CCApplication-mac.h
            platform/mac/CCGL-mac.h
            platform/desktop/CCGLViewImpl-desktop.h
            )
        set(COCOS_PLATFORM_SPECIFIC_SRC
            ${COCOS_PLATFORM_SPECIFIC_SRC}
            platform/mac/CCApplication-mac.mm
            platform/mac/CCCommon-mac.mm
            platform/mac/CCDevice-mac.mm
            platform/desktop/CCGLViewImpl-desktop.cpp
            )
    elseif(IOS)
        set(COCOS_PLATFORM_SPECIFIC_HEADER
            ${COCOS_PLATFORM_SPECIFIC_HEADER}
            platform/ios/CCGL-ios.h
            platform/ios/CCApplication-ios.h
            platform/ios/CCDirectorCaller-ios.h
            platform/ios/CCESRenderer-ios.h
            platform/ios/OpenGL_Internal-ios.h
            platform/ios/CCPlatformDefine-ios.h
            platform/ios/CCStdC-ios.h
            platform/ios/CCEAGLView-ios.h
            platform/ios/CCGLViewImpl-ios.h
            platform/ios/CCES2Renderer-ios.h
            )
        set(COCOS_PLATFORM_SPECIFIC_SRC
            ${COCOS_PLATFORM_SPECIFIC_SRC}
            platform/ios/CCApplication-ios.mm
            platform/ios/CCCommon-ios.mm
            platform/ios/CCDevice-ios.mm
            platform/ios/CCDirectorCaller-ios.mm
            platform/ios/CCEAGLView-ios.mm
            platform/ios/CCES2Renderer-ios.m
            platform/ios/CCGLViewImpl-ios.mm
            platform/ios/CCImage-ios.mm
            )
    endif()

elseif(LINUX)

    if(NOT CMAKE_CROSSCOMPILING)
        include_directories(
                /usr/include
                /usr/include/GLFW
                /usr/local/include/GLFW
        )
    endif(NOT CMAKE_CROSSCOMPILING)

    set(COCOS_PLATFORM_SPECIFIC_HEADER
        platform/linux/CCApplication-linux.h
        platform/linux/CCGL-linux.h
        platform/linux/CCStdC-linux.h
        platform/linux/CCFileUtils-linux.h
        platform/linux/CCPlatformDefine-linux.h
        platform/desktop/CCGLViewImpl-desktop.h
        )
    set(COCOS_PLATFORM_SPECIFIC_SRC
        platform/linux/CCStdC-linux.cpp
        platform/linux/CCFileUtils-linux.cpp
        platform/linux/CCCommon-linux.cpp
        platform/linux/CCApplication-linux.cpp
        platform/linux/CCDevice-linux.cpp
        platform/desktop/CCGLViewImpl-desktop.cpp
        )

elseif(ANDROID)

    set(COCOS_PLATFORM_SPECIFIC_HEADER
        platform/android/CCApplication-android.h
        platform/android/CCStdC-android.h
        platform/android/CCFileUtils-android.h
        platform/android/CCEnhanceAPI-android.h
        platform/android/CCPlatformDefine-android.h
        platform/android/CCGLViewImpl-android.h
        platform/android/jni/ProcessCpuTracker.h
        platform/android/jni/JniHelper.h
        platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.h
        platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h
        platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxEngineDataManager.h
        platform/android/CCGL-android.h
        )
    # need move to COCOS2DX_ANDROID_SRC?
    # need refactor
    set(COCOS_PLATFORM_SPECIFIC_SRC
        platform/android/CCApplication-android.cpp
        platform/android/CCCommon-android.cpp
        platform/android/CCGLViewImpl-android.cpp
        platform/android/CCFileUtils-android.cpp
        platform/android/CCEnhanceAPI-android.cpp
        platform/android/jni/JniHelper.cpp
        )

    set(COCOS2DX_ANDROID_SRC
        platform/android/CCDevice-android.cpp
        platform/android/javaactivity-android.cpp
        platform/android/jni/TouchesJni.cpp
        platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxAccelerometer.cpp
        platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.cpp
        platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp
        platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp
        platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxEngineDataManager.cpp

        )

    add_library(cocos2d_android STATIC ${COCOS2DX_ANDROID_SRC})
    set_property(TARGET cocos2d_android PROPERTY POSITION_INDEPENDENT_CODE TRUE)
    set_target_properties(cocos2d_android
                          PROPERTIES
                          ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                          LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                          VERSION "${COCOS2D_X_VERSION}"
                          )

endif()

#leave andatory external stuff here also

include_directories(
        ../external
        ../external/ConvertUTF
        ../external/edtaa3func
        ../external/poly2tri
        ../external/poly2tri/common
        ../external/poly2tri/sweep
)

set(COCOS_PLATFORM_HEADER
    ${COCOS_PLATFORM_SPECIFIC_HEADER}
    platform/CCApplication.h
    platform/CCApplicationProtocol.h
    platform/CCCommon.h
    platform/CCDevice.h
    platform/CCFileUtils.h
    platform/CCGL.h
    platform/CCGLView.h
    platform/CCImage.h
    platform/CCPlatformConfig.h
    platform/CCPlatformDefine.h
    platform/CCPlatformMacros.h
    platform/CCSAXParser.h
    platform/CCStdC.h
    platform/CCThread.h
    )

set(COCOS_PLATFORM_SRC
    ${COCOS_PLATFORM_SPECIFIC_SRC}
    platform/CCSAXParser.cpp
    platform/CCThread.cpp
    platform/CCGLView.cpp
    platform/CCFileUtils.cpp
    platform/CCImage.cpp
    ../external/edtaa3func/edtaa3func.cpp
    ../external/ConvertUTF/ConvertUTFWrapper.cpp
    ../external/ConvertUTF/ConvertUTF.c
    ../external/md5/md5.c
    ../external/poly2tri/common/shapes.cc
    ../external/poly2tri/sweep/advancing_front.cc
    ../external/poly2tri/sweep/cdt.cc
    ../external/poly2tri/sweep/sweep_context.cc
    ../external/poly2tri/sweep/sweep.cc
    )

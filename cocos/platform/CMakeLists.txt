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

elseif(MACOSX OR APPLE)

set(COCOS_PLATFORM_SPECIFIC_SRC
  platform/mac/CCApplication-mac.mm
  platform/mac/CCCommon-mac.mm
  platform/mac/CCDevice-mac.mm
  platform/apple/CCLock-apple.cpp
  platform/apple/CCFileUtils-apple.mm
  platform/apple/CCThread-apple.mm
  platform/apple/CCDevice-apple.mm
  platform/desktop/CCGLViewImpl-desktop.cpp
)

elseif(LINUX)

  include_directories(
    /usr/include
    /usr/include/GLFW
    /usr/local/include/GLFW
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

set(COCOS_PLATFORM_SPECIFIC_SRC
  platform/android/CCApplication-android.cpp
  platform/android/CCCommon-android.cpp
  platform/android/CCGLViewImpl-android.cpp
  platform/android/CCFileUtils-android.cpp
  platform/android/CCEnhanceAPI-android.cpp
  platform/android/jni/JniHelper.cpp
)

set(COCOS2DX_ANDROID_STATIC
  platform/android/CCDevice-android.cpp
  platform/android/javaactivity-android.cpp
  platform/android/jni/TouchesJni.cpp
  platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxAccelerometer.cpp
  platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.cpp
  platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp
  platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp

)

add_library(cocos2dxandroid_static STATIC ${COCOS2DX_ANDROID_STATIC})
set_property(TARGET cocos2dxandroid_static PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(cocos2dxandroid_static
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

set(COCOS_PLATFORM_SRC

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
  ${COCOS_PLATFORM_SPECIFIC_SRC}

)

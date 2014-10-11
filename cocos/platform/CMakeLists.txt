
if(WINDOWS)

set(COCOS_PLATFORM_SPECIFIC_SRC
  platform/win32/CCStdC-win32.cpp
  platform/win32/CCFileUtils-win32.cpp
  platform/win32/CCCommon-win32.cpp
  platform/win32/CCApplication-win32.cpp
  platform/win32/CCDevice-win32.cpp
  platform/desktop/CCGLViewImpl-desktop.cpp
)

elseif(MACOSX)

set(COCOS_PLATFORM_SPECIFIC_SRC
  platform/mac/CCApplication-mac.mm
  platform/mac/CCCommon-mac.mm
  platform/mac/CCDevice-mac.mm
  platform/apple/CCLock-apple.cpp
  platform/apple/CCFileUtils-apple.mm
  platform/apple/CCThread-apple.mm
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
  platform/android/CCDevice-android.cpp
  platform/android/CCGLViewImpl-android.cpp
  platform/android/CCFileUtils-android.cpp
  platform/android/javaactivity-android.cpp
  platform/android/jni/DPIJni.cpp
  platform/android/jni/IMEJni.cpp
  platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxAccelerometer.cpp
  platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.cpp
  platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp
  platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp
  platform/android/jni/JniHelper.cpp
  platform/android/jni/TouchesJni.cpp
)

endif()

#leave andatory external stuff here also

include_directories(
  platform/desktop
  platform
  ../external/ConvertUTF
  ../external/edtaa3func
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
  ${COCOS_PLATFORM_SPECIFIC_SRC}

)

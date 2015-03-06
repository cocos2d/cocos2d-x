#===============================================================================
# Add include directories.
if(COCOS_TARGET_SYSTEM_MACOSX OR
        COCOS_TARGET_SYSTEM_WINDOWS OR
        COCOS_TARGET_SYSTEM_LINUX)
    target_include_directories(${COCOS2D_TARGET} PRIVATE "platform/desktop")
endif()

#===============================================================================
# Common sources.
set(platform_src
    ${CMAKE_CURRENT_LIST_FILE}
    "platform/CCSAXParser.cpp"
    "platform/CCThread.cpp"
    "platform/CCGLView.cpp"
    "platform/CCFileUtils.cpp"
    "platform/CCImage.cpp"
    )

#===============================================================================
# System specific sources.
if(COCOS_TARGET_SYSTEM_MACOSX)
    set(platform_specific_src
        "platform/mac/CCApplication-mac.mm"
        "platform/mac/CCCommon-mac.mm"
        "platform/mac/CCDevice-mac.mm"
        "platform/apple/CCLock-apple.cpp"
        "platform/apple/CCFileUtils-apple.mm"
        "platform/apple/CCThread-apple.mm"
        "platform/desktop/CCGLViewImpl-desktop.cpp"
    )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    set(platform_specific_src
        "platform/win32/CCStdC-win32.cpp"
        "platform/win32/CCFileUtils-win32.cpp"
        "platform/win32/CCCommon-win32.cpp"
        "platform/win32/CCApplication-win32.cpp"
        "platform/win32/CCDevice-win32.cpp"
        "platform/desktop/CCGLViewImpl-desktop.cpp"
    )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    set(platform_specific_src
        "platform/linux/CCStdC-linux.cpp"
        "platform/linux/CCFileUtils-linux.cpp"
        "platform/linux/CCCommon-linux.cpp"
        "platform/linux/CCApplication-linux.cpp"
        "platform/linux/CCDevice-linux.cpp"
        "platform/desktop/CCGLViewImpl-desktop.cpp"
    )
elseif(COCOS_TARGET_SYSTEM_IOS)
    set(platform_specific_src
        "platform/ios/CCApplication-ios.h"
        "platform/ios/CCApplication-ios.mm"
        "platform/ios/CCCommon-ios.mm"
        "platform/ios/CCDevice-ios.mm"
        "platform/ios/CCDirectorCaller-ios.h"
        "platform/ios/CCDirectorCaller-ios.mm"
        "platform/ios/CCEAGLView-ios.h"
        "platform/ios/CCEAGLView-ios.mm"
        "platform/ios/CCES2Renderer-ios.h"
        "platform/ios/CCES2Renderer-ios.m"
        "platform/ios/CCESRenderer-ios.h"
        "platform/ios/CCGL-ios.h"
        "platform/ios/CCGLViewImpl-ios.h"
        "platform/ios/CCGLViewImpl-ios.mm"
        "platform/ios/CCImage-ios.mm"
        "platform/ios/CCPlatformDefine-ios.h"
        "platform/ios/CCStdC-ios.h"
        "platform/ios/OpenGL_Internal-ios.h"
        "platform/apple/CCLock-apple.cpp"
        "platform/apple/CCFileUtils-apple.mm"
        "platform/apple/CCThread-apple.mm"
    )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    set(platform_specific_src
        "platform/android/CCApplication-android.cpp"
        "platform/android/CCCommon-android.cpp"
        "platform/android/CCDevice-android.cpp"
        "platform/android/CCGLViewImpl-android.cpp"
        "platform/android/CCFileUtils-android.cpp"
        "platform/android/javaactivity-android.cpp"
        "platform/android/jni/CocosPlayClient.cpp"
        "platform/android/jni/DPIJni.cpp"
        "platform/android/jni/IMEJni.cpp"
        "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxAccelerometer.cpp"
        "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.cpp"
        "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp"
        "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp"
        "platform/android/jni/JniHelper.cpp"
        "platform/android/jni/TouchesJni.cpp"
    )
endif()

cocos_target_sources(${COCOS2D_TARGET} GROUP "platform" FILES
    ${platform_src}
    ${platform_specific_src}
    )

# CCGLViewImpl-ios.mm depends on CCSet.h yet, need remove sometime.
if(COCOS_TARGET_SYSTEM_IOS)
    target_include_directories(${COCOS2D_TARGET} PRIVATE
        "${COCOS2D_SOURCE_DIR}/deprecated"
        )
endif()

# DPIJni.cpp include "jni/JniHelper.h" yet, need change path sometime.
if(COCOS_TARGET_SYSTEM_ANDROID)
    target_include_directories(${COCOS2D_TARGET} PRIVATE
        "platform/android"
        )
endif()


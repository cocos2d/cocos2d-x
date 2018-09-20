cmake_minimum_required(VERSION 3.6)

set(target_name cpp_android_spec)

project(${target_name})

set(${target_name}_src
  CCApplication-android.cpp
  CCCommon-android.cpp
  CCDevice-android.cpp
  CCGLViewImpl-android.cpp
  CCFileUtils-android.cpp
  javaactivity-android.cpp
  CCEnhanceAPI-android.cpp
  jni/Java_org_cocos2dx_lib_Cocos2dxAccelerometer.cpp
  jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.cpp
  jni/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp
  jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp
  jni/Java_org_cocos2dx_lib_Cocos2dxEngineDataManager.cpp
  jni/JniHelper.cpp
  jni/TouchesJni.cpp
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)

target_include_directories(${target_name}
  PRIVATE ..
  PRIVATE ../..
)
# whole-archive JNI relatived codes
set_property(TARGET ${target_name} PROPERTY INTERFACE_LINK_LIBRARIES
  -Wl,--whole-archive,$<TARGET_FILE:${target_name}>,--no-whole-archive)     


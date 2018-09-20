cmake_minimum_required(VERSION 3.6)

set(target_name cpp_android_spec)

project(${target_name})

set(${target_name}_src
  CCDevice-android.cpp
  javaactivity-android.cpp
  jni/JniHelper.cpp
  jni/TouchesJni.cpp
  jni/Java_org_cocos2dx_lib_Cocos2dxAccelerometer.cpp
  jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.cpp
  jni/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp
  jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp
  jni/Java_org_cocos2dx_lib_Cocos2dxEngineDataManager.cpp
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)

target_include_directories(${target_name}
  PRIVATE ..
  PRIVATE ../..
)
# whole-archive JNI relatived codes
set_target_properties(${target_name} PROPERTIES INTERFACE_LINK_LIBRARIES
  -Wl,--whole-archive,$<TARGET_FILE:${target_name}>,-Wl,--no-whole-archive)     


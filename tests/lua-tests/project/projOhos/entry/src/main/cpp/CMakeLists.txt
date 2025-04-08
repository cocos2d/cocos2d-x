cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../..)
set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)

set(platform_name "ohos")
add_definitions(-DOHOS)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} SHARED main.cpp
                                   napi_init.cpp)

find_library( # Sets the name of the path variable.
              hilog-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              hilog_ndk.z )

add_subdirectory(${COCOS2DX_ROOT_PATH} cocos2dx)
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d lua-tests ${hilog-lib})
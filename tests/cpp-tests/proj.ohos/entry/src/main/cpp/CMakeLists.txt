cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../..)
set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)


set(OHOS true)
add_definitions(-DOHOS)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules)
include(CocosBuildHelpers)
set(CMAKE_CXX_STANDARD 14)
find_library( # Sets the name of the path variable.
              EGL-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              EGL )

find_library( # Sets the name of the path variable.
              GLES-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              GLESv3 )

find_library( # Sets the name of the path variable.
              hilog-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              hilog_ndk.z )

find_library( # Sets the name of the path variable.
              libace-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              ace_ndk.z )

find_library( # Sets the name of the path variable.
              libnapi-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              ace_napi.z )

find_library( # Sets the name of the path variable.
              libuv-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              uv )
find_library( # Sets the name of the path variable.
              rawfile-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              rawfile.z )
#add_subdirectory(../../../../cocos2d-x/cocos2dx cocos.bin)
#target_link_libraries(nativerender PUBLIC ${EGL-lib} ${GLES-lib} ${hilog-lib} ${libace-lib} ${libnapi-lib} ${libuv-lib} ${rawfile-lib} cocos_helo libc++.a)
#add_subdirectory(../../../../../cocos2d-x/samples/Cpp/HelloCpp/proj.ohos cocosOut.bin)

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../Resources/*")
    file(COPY ${ALL_RESOURCES_FILES}
        DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
endif()

include_directories(
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos
)

add_library(${PROJECT_NAME} SHARED main.cpp napi_init.cpp)

set(COCOS2DX_HEADER_PUBLIC
        ${CLASSES_PATH}
        ${COCOS2DX_ROOT_PATH}/cocos
        # ${COCOS2DX_ROOT_PATH}/cocos/include
        ${COCOS2DX_ROOT_PATH}/cocos/math
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/modules
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/common
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/render
        )


target_include_directories(${PROJECT_NAME} PUBLIC ${COCOS2DX_HEADER_PUBLIC})
target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSES_PATH})

target_link_libraries(${PROJECT_NAME} cocos2d cpp-tests ${libnapi-lib} ${hilog-lib})
add_subdirectory(${COCOS2DX_ROOT_PATH} Cocos2d-X)

cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../..)

set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)

set(platform_name "ohos")
set(OHOS true)
add_definitions(-DOHOS)
add_definitions(-DCOCOS2D_DEBUG=1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fexceptions -fsigned-char")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

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

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../Resources/*")
    file(COPY ${ALL_RESOURCES_FILES}
        DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
endif()

add_library(${PROJECT_NAME} SHARED  main.cpp
                                    napi_init.cpp
                                    )

target_include_directories(${PROJECT_NAME}  PUBLIC  ${CLASSES_PATH}
                                            PUBLIC  ${CLASSES_PATH}/../..
                                                    )
target_include_directories(${PROJECT_NAME}  PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/common
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/modules
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/editor-support
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/base
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos
                                                    )

#TBD need fixed
target_include_directories(${PROJECT_NAME} PUBLIC ${COCOS2DX_ROOT_PATH}/external/chipmunk/include
    )

add_subdirectory(${COCOS2DX_ROOT_PATH} Cocos-2dX)
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d cpp-tests ${libnapi-lib} ${GLES-lib})
# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

#add_library(entry SHARED hello.cpp)
#target_link_libraries(entry PUBLIC libace_napi.z.so)

project(nativerender)

set(CMAKE_VERBOSE_MAKEFILEON ON)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../..)

set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)

set(platform_name "ohos")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(OHOS true)
add_definitions(-DOHOS)
add_definitions(-DOpenHarmony)
add_definitions(-DNO_JS_ASSERT)
add_definitions(-DCOCOS2D_DEBUG=1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fexceptions -fsigned-char")

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

message("***************  GLES-lib: ${GLES-lib} ****************")

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

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../resjs/*")
    file(COPY ${ALL_RESOURCES_FILES}
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile/res)

    file(GLOB ALL_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../src/*")
    file(COPY ${ALL_SRC_FILES}
            DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile/src)

    file(GLOB ALL_SCRIPT_FILES "${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/script/*")
    file(COPY ${ALL_SCRIPT_FILES}
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile/script)

    file(GLOB ALL_MAIN_JS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../main.js")
    file(COPY ${ALL_MAIN_JS_FILES}
         DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile)

    file(GLOB ALL_PROJECT_JS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../project.json")
    file(COPY ${ALL_PROJECT_JS_FILES}
         DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile)

    file(GLOB CCS_RESOURCES_FILES "${COCOS2DX_ROOT_PATH}/tests/cpp-tests/Resources/*")
    file(COPY ${CCS_RESOURCES_FILES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile)

    file(GLOB JSB_PLUGANX_FILES "${COCOS2DX_ROOT_PATH}/plugin/jsbindings/script/*")
    file(COPY ${JSB_PLUGANX_FILES}
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile)
endif()

add_library(${PROJECT_NAME} SHARED  main.cpp
                                    napi_init.cpp
                                    ${CLASSES_PATH}/AppDelegate.cpp
                                    ${CLASSES_PATH}/js_DrawNode3D_bindings.cpp
                                    ${CLASSES_PATH}/js_Effect3D_bindings.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSES_PATH})
target_include_directories(${PROJECT_NAME} PUBLIC ${COCOS2DX_ROOT_PATH}/cocos)

include_directories(
        ${COCOS2DX_ROOT_PATH}
        ${COCOS2DX_ROOT_PATH}/cocos
        ${COCOS2DX_ROOT_PATH}/cocos/base
        ${COCOS2DX_ROOT_PATH}/cocos/2d
        ${COCOS2DX_ROOT_PATH}/cocos/ui
        ${COCOS2DX_ROOT_PATH}/cocos/audio/include
        ${COCOS2DX_ROOT_PATH}/cocos/storage
        ${COCOS2DX_ROOT_PATH}/cocos/network
        ${COCOS2DX_ROOT_PATH}/cocos/platform
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi
        ${COCOS2DX_ROOT_PATH}/cocos/editor-support
        ${COCOS2DX_ROOT_PATH}/cocos/editor-support/spine
        ${COCOS2DX_ROOT_PATH}/cocos/editor-support/cocosbuilder
        ${COCOS2DX_ROOT_PATH}/cocos/editor-support/cocostudio
        ${COCOS2DX_ROOT_PATH}/deprecated
        ${COCOS2DX_ROOT_PATH}/cocos/platform
        ${COCOS2DX_ROOT_PATH}/extensions
        ${COCOS2DX_ROOT_PATH}/external
        ${COCOS2DX_ROOT_PATH}/external/chipmunk/include/chipmunk
        ${COCOS2DX_ROOT_PATH}/external/chipmunk/include
        ${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/auto
        ${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/manual
        ${COCOS2DX_ROOT_PATH}/external/spidermonkey/include/ohos
        ${COCOS2DX_ROOT_PATH}/external/bullet/include
        ${COCOS2DX_ROOT_PATH}/external/bullet/include/bullet
        ${COCOS2DX_ROOT_PATH}/external/sqlite3/include
)
# jsbindings library
set(Cocos2d_JS_Samples_VERSION_MAJOR 3)
set(Cocos2d_JS_Samples_VERSION_MINOR 2)

link_directories(
        /usr/local/lib
        ${COCOS2DX_ROOT_PATH}/external/spidermonkey/prebuilt/ohos
)
add_subdirectory(${COCOS2DX_ROOT_PATH} Cocos2d-X)
target_link_libraries(${PROJECT_NAME} jscocos2d cocos2d ${libnapi-lib} ${hilog-lib})


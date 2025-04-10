cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../..)

set(CLASSES_PATH ${COCOS2DX_ROOT_PATH}/samples/Lua/TestLua/Classes)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_definitions(-DOHOS)
add_definitions("-DCOCOS2D_DEBUG=3")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DHarmonyOS_Next)

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

#[[if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../tests/lua-empty-tests/Resources/*")
    file(COPY ${ALL_RESOURCES_FILES}
        DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
endif()]]


    set(res_raw_folders "${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile")
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    file(GLOB resFiles "${CMAKE_CURRENT_LIST_DIR}/../../../../../Resources/*")
    file(COPY ${resFiles} DESTINATION  ${res_raw_folders})
    file(GLOB cppTestresFiles "${COCOS2DX_ROOT_PATH}/samples/Cpp/TestCpp/Resources/*")
    file(COPY ${cppTestresFiles} DESTINATION  ${res_raw_folders})

    file(GLOB cocosFiles "${COCOS2DX_ROOT_PATH}/scripting/lua/script/*")
    file(COPY ${cocosFiles} DESTINATION  ${res_raw_folders})

add_library(${PROJECT_NAME} SHARED  main.cpp
                                    napi_init.cpp
                                    ${CLASSES_PATH}/AppDelegate.cpp)


include_directories(${PROJECT_NAME}  PUBLIC  ${CLASSES_PATH}
                                            PUBLIC  ${CLASSES_PATH}/../..
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos2dx
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos2dx/platform/ohos/napi/common
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos2dx/platform/ohos/napi/modules
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos2dx/platform/ohos/napi/render
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos2dx/platform/ohos/napi
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/extensions
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/CocosDenshion/include
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/scripting/lua
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/scripting/lua/cocos2dx_support
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/scripting/lua/lua
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/scripting/lua/tolua
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/scripting/lua/xxtea
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos2dx/kazmath/include
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos2dx/platform/ohos
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/external/openssl/include/ohos
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/external/sqlit3/include
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos2dx/include
)

add_subdirectory(${COCOS2DX_ROOT_PATH}/external/openssl openssl.bin)
add_subdirectory(${COCOS2DX_ROOT_PATH}/external/curl curl.bin)
add_subdirectory(${COCOS2DX_ROOT_PATH}/scripting/lua/cocos2dx_support luasupport.bin)
add_subdirectory(${COCOS2DX_ROOT_PATH}/scripting/lua/lua lua.bin)
add_subdirectory(${COCOS2DX_ROOT_PATH}/scripting/lua/tolua tolua.bin)
add_subdirectory(${COCOS2DX_ROOT_PATH}/scripting/lua/xxtea xxtea.bin)
add_subdirectory(${COCOS2DX_ROOT_PATH}/CocosDenshion/ohos cocosDenshionOut.bin)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos2dx cocos2dx)
add_subdirectory(${COCOS2DX_ROOT_PATH}/extensions extensions.bin)
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2dx_static cocosdenshion luabinding xxtea ext_ssl ext_crypto ext_curl extensions ${libnapi-lib} ${GLES-lib} ${libace-lib} ${EGL-lib} ${hilog-lib} ${rawfile-lib} ${libnapi-lib} ${libuv-lib} ${rawfile-lib})


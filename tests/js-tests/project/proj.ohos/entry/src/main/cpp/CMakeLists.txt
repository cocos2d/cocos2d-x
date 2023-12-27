cmake_minimum_required(VERSION 3.6)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../..)
set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fexceptions -fsigned-char")
set(CMAKE_CXX_STANDARD 14)

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CLASSES_PATH}/../../resjs")
    file(COPY ${ALL_RESOURCES_FILES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile/res)

    file(GLOB ALL_SRC_FILES "${CLASSES_PATH}/../../src" "${CLASSES_PATH}/../../main.js" "${CLASSES_PATH}/../../project.json")
    file(COPY ${ALL_SRC_FILES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile)

    file(GLOB ALL_SCRIPT_FILES "${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/script")
    file(COPY ${ALL_SCRIPT_FILES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile)

    file(GLOB CCS_RESOURCES_FILES "${COCOS2DX_ROOT_PATH}/tests/cpp-tests/Resources/*")
    file(COPY ${CCS_RESOURCES_FILES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../resources/rawfile)
endif()

add_library(${PROJECT_NAME} SHARED main.cpp
                                   napi_init.cpp)

include_directories(${COCOS2DX_ROOT_PATH}/external/opengles/api)
target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSES_PATH}
                                           PUBLIC ${COCOS2DX_ROOT_PATH}/cocos
                                           PUBLIC ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos)

add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/js-tests/project js_test)
find_library(hilog-lib hilog_ndk.z)
find_library(libuv-lib uv)
target_link_libraries(${PROJECT_NAME} js-tests ${hilog-lib} ${libuv-lib})
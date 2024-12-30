cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../..)
set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)

set(OHOS true)
add_definitions(-DOHOS)

set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules)
include(CocosBuildHelpers)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../Resources/*")
    file(COPY ${ALL_RESOURCES_FILES}
        DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
endif()


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

add_subdirectory(${COCOS2DX_ROOT_PATH} Cocos-2dX)
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d cpp-tests ${libnapi-lib} ${GLES-lib})
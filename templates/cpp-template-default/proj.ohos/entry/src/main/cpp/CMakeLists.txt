cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../cocos2d)
set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)

set(platform_name "ohos")
add_definitions(-DOHOS)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../Resources/*")
    file(COPY ${ALL_RESOURCES_FILES} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
endif()

add_library(${PROJECT_NAME} SHARED  main.cpp napi_init.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSES_PATH})

add_subdirectory(${COCOS2DX_ROOT_PATH}/../ ${ENGINE_BINARY_PATH}/tests/)
find_library(hilog-lib hilog_ndk.z)
find_library(libuv-lib uv)
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d cpp-tests ${hilog-lib} ${libuv-lib})
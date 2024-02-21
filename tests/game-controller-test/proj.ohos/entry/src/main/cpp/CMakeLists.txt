cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../..)
set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)

set(OHOS true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fexceptions -fsigned-char")
set(game-controllertest "game-controller-test")
if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../Resources/*")
    file(COPY ${ALL_RESOURCES_FILES} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
endif()

include_directories(${COCOS2DX_ROOT_PATH}/external/opengles/api)

add_library(${PROJECT_NAME} SHARED  main.cpp
                                    napi_init.cpp
                                    )

target_include_directories(${PROJECT_NAME}  PUBLIC ${CLASSES_PATH}
                                            PUBLIC ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos
                                                    )

add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/${game-controllertest} GameControllerTest)

find_library(hilog-lib hilog_ndk.z)
find_library(libuv-lib uv)
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d GameControllerTest  ${hilog-lib} ${libuv-lib})
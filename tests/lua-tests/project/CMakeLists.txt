cmake_minimum_required(VERSION 3.1)

set(APP_NAME lua_tests)

project(${APP_NAME})

# default build, not build when build engine and all tests
if(NOT DEFINED BUILD_ENGINE_DONE)
    # define some variables
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)
    set(ENGINE_BINARY_PATH ${PROJECT_BINARY_DIR}/engine)

    message(STATUS "COCOS2DX_ROOT_PATH:" ${COCOS2DX_ROOT_PATH})
    message(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})
    
    # works before libcocos2d
    include(CocosBuildSet)
    CocosBuildSet()

    # add engine directory, get cocos library
    set(BUILD_LUA_LIBS ON)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH})

endif(NOT DEFINED BUILD_ENGINE_DONE)

set(SAMPLE_SRC
    Classes/AppDelegate.cpp
    Classes/lua_assetsmanager_test_sample.cpp
    Classes/lua_test_bindings.cpp
)

if(LINUX)
    set(SAMPLE_SRC ${SAMPLE_SRC} proj.linux/main.cpp)
    set(RES_PREFIX "/Resources")
elseif(WINDOWS)
    list(APPEND SAMPLE_SRC proj.win32/main.cpp)
    set(RES_PREFIX "")
elseif(MACOSX)
    set(SAMPLE_SRC ${SAMPLE_SRC} proj.ios_mac/mac/main.cpp)

    file(GLOB_RECURSE APP_RESOURCES ../res/*)
    cocos_mark_resources(FILES ${APP_RESOURCES} BASEDIR ../res RESOURCEBASE Resources/res)
    file(GLOB_RECURSE APP_SCRIPTS ../src/*)
    cocos_mark_resources(FILES ${APP_SCRIPTS} BASEDIR ../src RESOURCEBASE Resources/src)
    file(GLOB_RECURSE COCOS_SCRIPTS ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/*)
    cocos_mark_resources(FILES ${COCOS_SCRIPTS} BASEDIR ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script RESOURCEBASE Resources/src/cocos)
    file(GLOB_RECURSE TEST_RESOURCES ${CMAKE_SOURCE_DIR}/tests/cpp-tests/Resources/*)
    cocos_mark_resources(FILES ${TEST_RESOURCES} BASEDIR ${CMAKE_SOURCE_DIR}/tests/cpp-tests/Resources RESOURCEBASE Resources/res)

    list(APPEND SAMPLE_SRC ${APP_RESOURCES} ${APP_SCRIPTS} ${COCOS_SCRIPTS} ${TEST_RESOURCES})
elseif(ANDROID)
    list(APPEND SAMPLE_SRC proj.android/app/jni/main.cpp)
    set(RES_PREFIX "/Resources")
endif()

include_directories(
  Classes
  ../../../cocos/scripting/lua-bindings/manual
  ../../../cocos/scripting/lua-bindings/auto
  ../../../external/lua/tolua
)

include_directories(${LUAJIT_INCLUDE_DIRS})

if(ANDROID)
    add_library(${APP_NAME} SHARED ${SAMPLE_SRC})
    IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF()
else()
    # add the executable
    add_executable(${APP_NAME} ${SAMPLE_SRC})
endif()

target_link_libraries(${APP_NAME} luacocos2d)

if(MACOSX OR APPLE)
  set_target_properties(${APP_NAME} PROPERTIES
      MACOSX_BUNDLE 1
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )

else()

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

    set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")

    pre_build(${APP_NAME}
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}${RES_PREFIX}/res
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}${RES_PREFIX}/src
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/ ${APP_BIN_DIR}/Resources/src/cocos
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/tests/cpp-tests/Resources ${APP_BIN_DIR}${RES_PREFIX}/res
      )

endif()


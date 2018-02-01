cmake_minimum_required(VERSION 3.1)

set(APP_NAME lua_tests)

project(${APP_NAME})

# default build, not build when build engine and all tests
if(NOT DEFINED BUILD_ENGINE_DONE)
    # define some variables
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)
    
    # works before libcocos2d
    include(CocosBuildSet)
    CocosBuildSet()
    # add engine directory, get cocos library
    set(BUILD_LUA_LIBS ON)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

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

    file(GLOB_RECURSE RES_ICON proj.ios_mac/mac/Icon.icns)
    cocos_mark_resources(FILES ${RES_ICON} BASEDIR proj.ios_mac/mac)
    file(GLOB_RECURSE APP_RESOURCES ../res/*)
    cocos_mark_resources(FILES ${APP_RESOURCES} BASEDIR ../res RESOURCEBASE Resources/res)
    file(GLOB_RECURSE APP_SCRIPTS ../src/*)
    cocos_mark_resources(FILES ${APP_SCRIPTS} BASEDIR ../src RESOURCEBASE Resources/src)
    file(GLOB_RECURSE COCOS_SCRIPTS ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/*)
    cocos_mark_resources(FILES ${COCOS_SCRIPTS} BASEDIR ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script RESOURCEBASE Resources/src/cocos)
    file(GLOB_RECURSE TEST_RESOURCES ${COCOS2DX_ROOT_PATH}/tests/cpp-tests/Resources/*)
    cocos_mark_resources(FILES ${TEST_RESOURCES} BASEDIR ${COCOS2DX_ROOT_PATH}/tests/cpp-tests/Resources RESOURCEBASE Resources/res)

    list(APPEND SAMPLE_SRC ${RES_ICON} ${APP_RESOURCES} ${APP_SCRIPTS} ${COCOS_SCRIPTS} ${TEST_RESOURCES})
elseif(ANDROID)
    list(APPEND SAMPLE_SRC proj.android/app/jni/main.cpp)
    set(RES_PREFIX "/Resources")
elseif(IOS)
    set(PLATFORM_SRC
        proj.ios_mac/main.m
        proj.ios_mac/AppController.mm
        proj.ios_mac/RootViewController.mm
        )
    include_directories(proj.ios_mac)
endif()

include_directories(
    Classes
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/manual
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/auto
    ${COCOS2DX_ROOT_PATH}/external/lua/tolua
    )

include_directories(${LUAJIT_INCLUDE_DIRS})

if(ANDROID)
    add_library(${APP_NAME} SHARED ${SAMPLE_SRC})
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    endif()
else()
    # add the executable
    add_executable(${APP_NAME} ${SAMPLE_SRC})
endif()

target_link_libraries(${APP_NAME} luacocos2d)
add_dependencies(${APP_NAME} luacocos2d)

# need research, it should be added to all macos project?
if(MACOSX OR APPLE)
  # fix js-tests compile error, for temp
  set_property(TARGET ${APP_NAME} APPEND_STRING PROPERTY COMPILE_FLAGS "-fobjc-arc")
endif()

if(MACOSX OR APPLE)
  set_target_properties(${APP_NAME} PROPERTIES
        MACOSX_BUNDLE 1
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
    cocos_pak_xcode(${APP_NAME})
else()

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

    set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")

    pre_build(${APP_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}${RES_PREFIX}/res
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}${RES_PREFIX}/src
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/ ${APP_BIN_DIR}/Resources/src/cocos
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/tests/cpp-tests/Resources ${APP_BIN_DIR}${RES_PREFIX}/res
        )

endif()

if(XCODE OR VS)
    cocos_mark_code_files(${APP_NAME})
endif()
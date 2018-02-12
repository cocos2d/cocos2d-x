cmake_minimum_required(VERSION 3.1)

set(APP_NAME lua_empty_test)

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

set(SAMPLE_SRC Classes/AppDelegate.cpp)

if(APPLE OR VS)
    set(res_res_folders 
        "${CMAKE_CURRENT_SOURCE_DIR}/../res" 
    )
    set(res_src_folders
        "${CMAKE_CURRENT_SOURCE_DIR}/../src"
    )
    set(res_script_folders
        "${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script"
    )
    cocos_mark_multi_resources(res_res RES_TO "Resources/res" FOLDERS ${res_res_folders})
    cocos_mark_multi_resources(res_src RES_TO "Resources/src" FOLDERS ${res_src_folders})
    cocos_mark_multi_resources(res_script RES_TO "Resources/src/cocos" FOLDERS ${res_script_folders})
    set(cc_common_res ${res_res} ${res_src} ${res_script})
endif()

if(LINUX)
    set(SAMPLE_SRC ${SAMPLE_SRC} proj.linux/main.cpp)
    set(RES_PREFIX "/Resources")
elseif(WINDOWS)
    add_definitions(-D_USRLUASTATIC)
    list(APPEND SAMPLE_SRC proj.win32/main.cpp ${cc_common_res})
elseif(APPLE)

    if(IOS)
        set(ios_code_files
            proj.ios/main.m
            proj.ios/AppController.mm
            proj.ios/RootViewController.mm
        )
        set(ios_res_files
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios/LaunchScreen.storyboard
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios/LaunchScreenBackground.png
        )
        cocos_mark_multi_resources(ios_res_files RES_TO "Resources" FILES ${ios_res_files})
        set(apple_src_files ${ios_code_files} ${ios_res_files})
    elseif(MACOSX)
        set(mac_code_files proj.mac/main.cpp)
        set(mac_res_files
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/Icon.icns
        )
        cocos_mark_multi_resources(mac_res_files RES_TO "Resources" FILES ${mac_res_files})
        set(apple_src_files ${mac_res_files} ${mac_code_files})
    endif()

    list(APPEND SAMPLE_SRC ${cc_common_res} ${apple_src_files})
elseif(ANDROID)
    list(APPEND SAMPLE_SRC proj.android/app/jni/main.cpp)
    set(RES_PREFIX "/Resources")
endif()

include_directories(
    Classes
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/auto
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/manual
    ${COCOS2DX_ROOT_PATH}/external/lua/luajit/include
    ${COCOS2DX_ROOT_PATH}/external/lua/tolua
    )

include_directories(${LUAJIT_INCLUDE_DIRS})

if(ANDROID)
    add_library(${APP_NAME} SHARED ${SAMPLE_SRC})
    if(CMAKE_BUILD_TYPE MATCHES Release)
        add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    endif()
    target_link_libraries(${APP_NAME} -Wl,-whole-archive cocos2d_android -Wl,-no-whole-archive)
    add_dependencies(${APP_NAME} cocos2d_android)
else()
    # add the executable
    add_executable(${APP_NAME} ${SAMPLE_SRC})
endif()

target_link_libraries(${APP_NAME} luacocos2d)
add_dependencies(${APP_NAME} luacocos2d)

if(APPLE)
  set_target_properties(${APP_NAME} PROPERTIES
      MACOSX_BUNDLE 1
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )
    if(MACOSX)
        cocos_pak_xcode(${APP_NAME})
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
    endif()
elseif(MSVC)
    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}/$<CONFIG>")
    #Visual Studio Defaults to wrong type
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_BIN_DIR})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR}/res FOLDERS ${res_res_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR}/src FOLDERS ${res_src_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR}/src/cocos FOLDERS ${res_script_folders})
else()

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

    set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")

    pre_build(${APP_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}${RES_PREFIX}/res
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}${RES_PREFIX}/src
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/ ${APP_BIN_DIR}${RES_PREFIX}/src/cocos
        )

endif()

if(XCODE OR VS)
    cocos_mark_code_files(${APP_NAME})
endif()
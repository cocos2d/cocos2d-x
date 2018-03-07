cmake_minimum_required(VERSION 3.1)

set(APP_NAME lua_tests)

project(${APP_NAME})

if(NOT DEFINED BUILD_ENGINE_DONE)
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)
    
    include(CocosBuildSet)
    CocosBuildSet()
    if(NOT USE_COCOS_PREBUILT)
        set(BUILD_LUA_LIBS ON)
        add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
    endif()
endif()

set(SAMPLE_SRC
    Classes/AppDelegate.cpp
    Classes/lua_assetsmanager_test_sample.cpp
    Classes/lua_test_bindings.cpp
)

set(res_res_folders 
    "${CMAKE_CURRENT_SOURCE_DIR}/../res" 
    "${COCOS2DX_ROOT_PATH}/tests/cpp-tests/Resources"
)
set(res_src_folders
    "${CMAKE_CURRENT_SOURCE_DIR}/../src"
)
set(res_script_folders
    "${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script"
)
if(APPLE OR VS)
    cocos_mark_multi_resources(res_res RES_TO "Resources/res" FOLDERS ${res_res_folders})
    cocos_mark_multi_resources(res_src RES_TO "Resources/src" FOLDERS ${res_src_folders})
    cocos_mark_multi_resources(res_script RES_TO "Resources/src/cocos" FOLDERS ${res_script_folders})
    set(cc_common_res ${res_res} ${res_src} ${res_script})
endif()

if(ANDROID)
    list(APPEND SAMPLE_SRC proj.android/app/jni/main.cpp)
elseif(LINUX)
    set(SAMPLE_SRC ${SAMPLE_SRC} proj.linux/main.cpp)
elseif(WINDOWS)
    add_definitions(-D_USRLUASTATIC)
    list(APPEND SAMPLE_SRC proj.win32/main.cpp ${cc_common_res})
elseif(APPLE)
    if(IOS)
        set(ios_code_files
            proj.ios_mac/ios/main.m
            proj.ios_mac/ios/LuaObjectCBridgeTest.mm
            proj.ios_mac/ios/AppController.mm
            proj.ios_mac/ios/RootViewController.mm
            )
        set(ios_res_files
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/LaunchScreen.storyboard
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/LaunchScreenBackground.png
        )
        cocos_mark_multi_resources(ios_res_files RES_TO "Resources" FILES ${ios_res_files})
        set(apple_src_files ${ios_code_files} ${ios_res_files})
    elseif(MACOSX)
        set(mac_code_files proj.ios_mac/mac/main.cpp)
        set(mac_res_files
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Icon.icns
        )
        cocos_mark_multi_resources(mac_res_files RES_TO "Resources" FILES ${mac_res_files})
        set(apple_src_files ${mac_res_files} ${mac_code_files})
    endif()
    list(APPEND SAMPLE_SRC ${apple_src_files} ${cc_common_res})
endif()

include_directories(
    Classes
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/manual
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/auto
    ${COCOS2DX_ROOT_PATH}/external/lua/tolua
)

include_directories(${LUAJIT_INCLUDE_DIRS})

# mark app complie info and libs info
cocos_build_app(${APP_NAME} 
    APP_SRC "${SAMPLE_SRC}"
    DEPEND_COMMON_LIBS "luacocos2d" "cocos2d"
    DEPEND_ANDROID_LIBS "cocos2d_android"
)

# mark app resources
if(APPLE)
    if(MACOSX)
        cocos_pak_xcode(${APP_NAME} BUNDLE_NAME "LuaTestsApp")
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_BIN_DIR})
endif()

if(LINUX OR WINDOWS)
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR}/res FOLDERS ${res_res_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR}/src FOLDERS ${res_src_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR}/src/cocos FOLDERS ${res_script_folders})
endif()

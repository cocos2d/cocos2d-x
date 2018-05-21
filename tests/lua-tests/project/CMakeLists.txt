cmake_minimum_required(VERSION 3.1)

set(APP_NAME lua-tests)

project(${APP_NAME})

if(NOT DEFINED BUILD_ENGINE_DONE)
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    if(NOT USE_COCOS_PREBUILT)
        set(BUILD_LUA_LIBS ON)
        add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
    endif()
endif()

set(GAME_HEADER
    Classes/AppDelegate.h
    Classes/lua_test_bindings.h
    Classes/lua_assetsmanager_test_sample.h
    )
set(GAME_SOURCE
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
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME lua_tests)
    list(APPEND GAME_SOURCE proj.android/app/jni/main.cpp)
elseif(LINUX)
    list(APPEND GAME_SOURCE proj.linux/main.cpp)
elseif(WINDOWS)
    add_definitions(-D_USRLUASTATIC)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE proj.win32/main.cpp ${cc_common_res})
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/LuaObjectCBridgeTest.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/LuaObjectCBridgeTest.mm
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        list(APPEND GAME_HEADER
             proj.ios_mac/mac/LuaObjectCBridgeTest.h
             )
        set(APP_UI_RES
            proj.ios_mac/mac/en.lproj/MainMenu.xib
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/LuaObjectCBridgeTest.mm
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${cc_common_res})
endif()

include_directories(
        Classes
        ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/manual
        ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/auto
        ${COCOS2DX_ROOT_PATH}/external/lua/tolua
)

include_directories(${LUAJIT_INCLUDE_DIRS})

set(APP_SRC ${GAME_HEADER} ${GAME_SOURCE})
# mark app complie info and libs info
cocos_build_app(${APP_NAME}
                APP_SRC "${APP_SRC}"
                DEPEND_COMMON_LIBS "luacocos2d" "cocos2d"
                DEPEND_ANDROID_LIBS "cocos2d_android"
                )

# mark app resources
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon-${APP_NAME}")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_RES_DIR})
endif()

if(LINUX OR WINDOWS)
    cocos_copy_res(COPY_TO ${APP_RES_DIR}/res FOLDERS ${res_res_folders})
    cocos_copy_res(COPY_TO ${APP_RES_DIR}/src FOLDERS ${res_src_folders})
    cocos_copy_res(COPY_TO ${APP_RES_DIR}/src/cocos FOLDERS ${res_script_folders})
endif()

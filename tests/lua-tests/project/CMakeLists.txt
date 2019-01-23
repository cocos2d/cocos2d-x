cmake_minimum_required(VERSION 3.6)

set(APP_NAME lua-tests)

project(${APP_NAME})

if(NOT DEFINED BUILD_ENGINE_DONE)
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    set(BUILD_LUA_LIBS ON)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
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

set(APP_SRC ${GAME_HEADER} ${GAME_SOURCE})

if(NOT ANDROID)
    add_executable(${APP_NAME} ${APP_SRC})
else()
    add_library(${APP_NAME} SHARED ${APP_SRC})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/cpp-android)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/proj.android ${ENGINE_BINARY_PATH}/cocos/lua-android)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive lua_android_spec -Wl,--no-whole-archive)
endif()
target_link_libraries(${APP_NAME} luacocos2d)
target_include_directories(${APP_NAME} PRIVATE Classes)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon-${APP_NAME}")
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "")
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    set(APP_RES_DIR "$<TARGET_FILE_DIR:${APP_NAME}>/Resources")
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR}/res FOLDERS ${res_res_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR}/src FOLDERS ${res_src_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR}/src/cocos FOLDERS ${res_script_folders})
endif()

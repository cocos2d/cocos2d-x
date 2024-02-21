cmake_minimum_required(VERSION 3.6)

set(APP_NAME GameControllerTest)

project(${APP_NAME})
if(NOT DEFINED BUILD_ENGINE_DONE)
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR VS)
    cocos_mark_multi_resources(cc_common_res RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME GameControllerTest)
    list(APPEND GAME_HEADER
         Classes/JNITest/JNITest.h
         )
    list(APPEND GAME_SOURCE
         Classes/JNITest/JNITest.cpp
         proj.android/app/jni/main.cpp
         )
elseif(OHOS)
    set(APP_NAME GameControllerTest)
    list(APPEND GAME_SOURCE
        proj.ohos/entry/src/main/cpp/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         ${cc_common_res}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios/Classes/testsAppDelegate.h
             proj.ios/Classes/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios/LaunchScreen.storyboard
            proj.ios/LaunchScreenBackground.png
            proj.ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios/main.m
             proj.ios/Classes/testsAppDelegate.mm
             proj.ios/Classes/RootViewController.mm
             proj.ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.mac/Icon.icns
            proj.mac/Info.plist
            proj.mac/Prefix.pch
            proj.mac/en.lproj/MainMenu.xib
            proj.mac/en.lproj/InfoPlist.strings
            )
        list(APPEND GAME_SOURCE
             proj.mac/main.cpp
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${cc_common_res})
endif()

list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     Classes/AppMacros.h
     Classes/GameControllerTest.h
     )

list(APPEND GAME_SOURCE
    Classes/AppDelegate.cpp
    Classes/GameControllerTest.cpp
     )

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )

set(game-controllertest "game-controller-test")

if (ANDROID)
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
elseif (OHOS)
    add_library(${APP_NAME} STATIC ${all_code_files})
else()
    add_executable(${APP_NAME} ${all_code_files})
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon-${APP_NAME}")
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "")
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
    endif()
elseif(WINDOWS)
    # "too large PDB" error often occurs in cpp-tests when using default "/Zi"
    target_compile_options(${APP_NAME} PRIVATE /Z7)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    set(APP_RES_DIR "$<TARGET_FILE_DIR:${APP_NAME}>/Resources")
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()

if(WINDOWS)
    # precompiled header. Compilation time speedup ~4x.
    target_sources(${APP_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Classes/precheader.cpp")
    set_target_properties(${APP_NAME} PROPERTIES COMPILE_FLAGS "/Yuprecheader.h /FIprecheader.h")
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/Classes/precheader.cpp" PROPERTIES COMPILE_FLAGS "/Ycprecheader.h")
endif()
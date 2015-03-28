project(GAME_CONTROLLER_TEST)

#===============================================================================
# Define game-controller-test target.
set(app_name game-controller-test)

if(COCOS_TARGET_SYSTEM_ANDROID)
    add_library(${app_name} SHARED ${CMAKE_CURRENT_LIST_FILE})
else()
    add_executable(${app_name} ${CMAKE_CURRENT_LIST_FILE})
endif()
set_target_properties(${app_name} PROPERTIES FOLDER "tests")

#===============================================================================
# Add include directories.
target_include_directories(${app_name} PRIVATE "Classes")

#===============================================================================
# Add sources.
cocos_target_sources(${app_name} GROUP "Classes" FILES
    "Classes/AppDelegate.cpp"
    "Classes/GameControllerTest.cpp"
    )

if(COCOS_TARGET_SYSTEM_IOS)
    set(platform_src
        "proj.ios/AppController.h"
        "proj.ios/AppController.mm"
        "proj.ios/main.m"
        "proj.ios/RootViewController.h"
        "proj.ios/RootViewController.mm"
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    set(platform_src
        "proj.android/jni/main.cpp"
        )
else()
    message(FATAL_ERROR "${CMAKE_CURRENT_LIST_FILE} build on unsupport system.")
endif()

cocos_target_sources(${app_name} GROUP "proj" FILES ${platform_src})

#===============================================================================
# Project resource files list.
file(GLOB_RECURSE app_res "Resources/*")

#===============================================================================
# Link dependent libraries.
target_link_libraries(${app_name} ${COCOS2D_TARGET})

if(COCOS_TARGET_SYSTEM_IOS)
    target_link_libraries(${app_name}
        "-framework GameController"
        )
endif()

#===============================================================================
# Specific settings.
if(COCOS_TARGET_SYSTEM_IOS)
    cocos_target_resource(${app_name} GROUP "Resources"
        LOCATION "."
        BASEDIR "Resources"
        FILES ${app_res}
        )
    set(ios_res
        "proj.ios/Default-568h@2x.png"
        "proj.ios/Default-667h@2x.png"
        "proj.ios/Default-736h@3x.png"
        "proj.ios/Default.png"
        "proj.ios/Default@2x.png"
        "proj.ios/Icon-100.png"
        "proj.ios/Icon-114.png"
        "proj.ios/Icon-120.png"
        "proj.ios/Icon-144.png"
        "proj.ios/Icon-152.png"
        "proj.ios/Icon-40.png"
        "proj.ios/Icon-57.png"
        "proj.ios/Icon-58.png"
        "proj.ios/Icon-72.png"
        "proj.ios/Icon-76.png"
        "proj.ios/Icon-80.png"
        )
    cocos_target_resource(${app_name} GROUP "proj"
        LOCATION "."
        FLAT_TO_LOCATION TRUE
        FILES ${ios_res}
        )

    set_target_properties(${app_name} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "${app_name}"
        MACOSX_BUNDLE_BUNDLE_VERSION "${COCOS2D_X_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.cocos.$(PRODUCT_NAME)"
        MACOSX_BUNDLE_ICON_FILE "Icon-57.png"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/proj.ios/InfoCMake.plist"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${COCOS2D_X_VERSION}"
        )
endif()


project(LUA_GAME_CONTROLLER_TEST)

#===============================================================================
# Define executable target 'lua-game-controller-test'.
set(app_name lua-game-controller-test)

if(COCOS_TARGET_SYSTEM_ANDROID)
    add_library(${app_name} SHARED ${CMAKE_CURRENT_LIST_FILE})
else()
    add_executable(${app_name} ${CMAKE_CURRENT_LIST_FILE})
endif()
set_target_properties(${app_name} PROPERTIES
    FOLDER "tests"
    )

#===============================================================================
# Set include directories.
target_include_directories(${app_name} PRIVATE
    "Classes"
    )

#===============================================================================
# Add sources.
cocos_target_sources(${app_name} GROUP "Classes" FILES
    "Classes/AppDelegate.cpp"
    "Classes/AppDelegate.h"
    )

if(COCOS_TARGET_SYSTEM_IOS)
    set(app_src
        "proj.ios/AppController.h"
        "proj.ios/AppController.mm"
        "proj.ios/main.m"
        "proj.ios/RootViewController.h"
        "proj.ios/RootViewController.mm"
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    set(app_src
        "proj.android/jni/main.cpp"
        )
else()
    message(FATAL_ERROR "${CMAKE_CURRENT_LIST_FILE} build for unsupport OS.")
endif()
cocos_target_sources(${app_name} GROUP "proj" FILES ${app_src})

#===============================================================================
# Link dependent libraries.
target_link_libraries(${app_name} ${LUACOCOS2D_TARGET})

if(COCOS_TARGET_SYSTEM_IOS)
    target_link_libraries(${app_name}
        "-framework GameController"
        )
endif()

#===============================================================================
# Get game-controller-test resources list.
file(GLOB_RECURSE cpp_res "${GAME_CONTROLLER_TEST_SOURCE_DIR}/Resources/*")

#===============================================================================
# Specific settings.
if(COCOS_TARGET_SYSTEM_IOS)
    # Add resources to xcodeproj.

    # res dir has no file yet
    #file(GLOB_RECURSE app_resources "../res/*")
    #cocos_target_resource(${app_name} GROUP "Resources\\res"
    #    LOCATION "res"
    #    FILES ${app_resources}
    #    BASEDIR "../res"
    #    )

    file(GLOB_RECURSE app_scripts "../src/*")
    cocos_target_resource(${app_name} GROUP "Resources\\src"
        LOCATION "src"
        FILES ${app_scripts}
        BASEDIR "../src"
        )

    file(GLOB_RECURSE cocos_scripts "${COCOS2D_SOURCE_DIR}/scripting/lua-bindings/script/*")
    cocos_target_resource(${app_name} GROUP "Resources\\src\\cocos"
        LOCATION "src/cocos"
        FILES ${cocos_scripts}
        BASEDIR "${COCOS2D_SOURCE_DIR}/scripting/lua-bindings/script"
        )
    # Add cpp-tests resources.
    cocos_target_resource(${app_name} GROUP "Resources\\res"
        LOCATION "."
        FILES ${cpp_res}
        BASEDIR "${GAME_CONTROLLER_TEST_SOURCE_DIR}/Resources"
        )
    set(ios_res
        "proj.ios/Default-568h@2x.png"
        "proj.ios/Default-667h@2x.png"
        "proj.ios/Default-736h@3x.png"
        "proj.ios/Default.png"
        "proj.ios/Default@2x.png"
        "proj.ios/Icon-114.png"
        "proj.ios/Icon-120.png"
        "proj.ios/Icon-144.png"
        "proj.ios/Icon-152.png"
        "proj.ios/Icon-57.png"
        "proj.ios/Icon-72.png"
        "proj.ios/Icon-76.png"
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


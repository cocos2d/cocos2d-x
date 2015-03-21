project(CPP_EMPTY_TEST)

#===============================================================================
# Define cpp-empty-test target.
set(app_name cpp-empty-test)

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
    "Classes/HelloWorldScene.cpp"
    )

if(COCOS_TARGET_SYSTEM_MACOSX)
    set(platform_src
        "proj.mac/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    set(platform_src
        "proj.win32/main.cpp"
        "proj.win32/main.h"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    set(platform_src
        "proj.linux/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_IOS)
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
set(app_res
    "Resources/fonts/arial.ttf"
    "Resources/fonts/Marker Felt.ttf"
    "Resources/ipad/CloseNormal.png"
    "Resources/ipad/CloseSelected.png"
    "Resources/ipad/HelloWorld.png"
    "Resources/ipadhd/CloseNormal.png"
    "Resources/ipadhd/CloseSelected.png"
    "Resources/ipadhd/HelloWorld.png"
    "Resources/iphone/CloseNormal.png"
    "Resources/iphone/CloseSelected.png"
    "Resources/iphone/HelloWorld.png"
    "Resources/bang.png"
    )

#===============================================================================
# Link dependent libraries.
target_link_libraries(${app_name} ${COCOS2D_TARGET})

#===============================================================================
# Specific settings.
if(COCOS_TARGET_SYSTEM_MACOSX)
    cocos_target_resource(${app_name} GROUP "Resources"
        LOCATION "Resources"
        BASEDIR "Resources"
        FILES ${app_res}
        )
    set_target_properties(${app_name} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "${app_name}"
        MACOSX_BUNDLE_BUNDLE_VERSION "${COCOS2D_X_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.cocos.$(PRODUCT_NAME)"
        MACOSX_BUNDLE_ICON_FILE "${CMAKE_CURRENT_LIST_DIR}/proj.mac/Icon.icns"
        )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    set_target_properties(${app_name} PROPERTIES 
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    #cocos_use_package(${app_name} GLFW3 REQUIRED)
elseif(COCOS_TARGET_SYSTEM_IOS)
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

#===============================================================================
# Copy resources.
if(XCODE_VERSION)
    # Nothing to do.
elseif(MSVC_IDE)
    cocos_add_copy_depends_dll_command(${app_name})

    # Copy resource folder "Resources" to WorkingDir(is $(ProjectDir) in VS).
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_LIST_DIR}/Resources" res_dir)
    add_custom_command(TARGET ${app_name} POST_BUILD
        COMMAND xcopy /Y /Q /E
        "\"${res_dir}\""
        "\"$(ProjectDir)\""
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    # TODO
else()
    add_custom_command(TARGET ${app_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:${app_name}>/Resources"
        )
endif()


project(LUA_EMPTY_TEST)

#===============================================================================
# Define executable target 'lua-empty-test'.
set(app_name lua-empty-test)

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
    "Classes/lua_module_register.h"
    )

if(COCOS_TARGET_SYSTEM_MACOSX)
    set(app_src
        "proj.mac/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    set(app_src
        "proj.win32/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    set(app_src
        "proj.linux/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_IOS)
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

#===============================================================================
# Specific settings.
if(COCOS_TARGET_SYSTEM_MACOSX)
    # Add resources to xcodeproj.
    file(GLOB_RECURSE app_resources "../res/*")
    cocos_target_resource(${app_name} GROUP "Resources\\res"
        LOCATION "Resources/res"
        FILES ${app_resources}
        BASEDIR "../res"
        )
    
    file(GLOB_RECURSE app_scripts "../src/*")
    cocos_target_resource(${app_name} GROUP "Resources\\src"
        LOCATION "Resources/src"
        FILES ${app_scripts}
        BASEDIR "../src"
        )

    file(GLOB_RECURSE cocos_scripts "${COCOS2D_SOURCE_DIR}/scripting/lua-bindings/script/*")
    cocos_target_resource(${app_name} GROUP "Resources\\src\\cocos"
        LOCATION "Resources/src/cocos"
        FILES ${cocos_scripts}
        BASEDIR "${COCOS2D_SOURCE_DIR}/scripting/lua-bindings/script"
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
elseif(COCOS_TARGET_SYSTEM_IOS)
    # Add resources to xcodeproj.
    file(GLOB_RECURSE app_resources "../res/*")
    cocos_target_resource(${app_name} GROUP "Resources\\res"
        LOCATION "res"
        FILES ${app_resources}
        BASEDIR "../res"
        )
    
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

#===============================================================================
# Copy resources.
if(XCODE_VERSION)
    # Nothing to do.
elseif(MSVC_IDE AND COCOS_TARGET_SYSTEM_WINDOWS)
    cocos_add_copy_depends_dll_command(${app_name})

    # Copy resource folders to WorkingDir(is $(ProjectDir) in VS).
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_LIST_DIR}/../res" res_dir)
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_LIST_DIR}/../src" src_dir)
    file(TO_NATIVE_PATH
        "${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script" 
        cocos_src_dir
        )

    add_custom_command(TARGET ${app_name} POST_BUILD
        COMMAND xcopy /Y /Q /E
        "\"${res_dir}\""
        "\"$(ProjectDir)res\\\""
        COMMAND xcopy /Y /Q /E
        "\"${src_dir}\""
        "\"$(ProjectDir)src\\\""
        COMMAND xcopy /Y /Q /E
        "\"${cocos_src_dir}\""
        "\"$(ProjectDir)src\\cocos\\\""
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    # TODO
else()
    # Copy resource to executable directory.
    add_custom_command(TARGET ${app_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_CURRENT_SOURCE_DIR}/../res"
        "$<TARGET_FILE_DIR:${app_name}>/Resources/res"
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_CURRENT_SOURCE_DIR}/../src"
        "$<TARGET_FILE_DIR:${app_name}>/Resources/src"
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script"
        "$<TARGET_FILE_DIR:${app_name}>/Resources/src/cocos"
        )
endif()


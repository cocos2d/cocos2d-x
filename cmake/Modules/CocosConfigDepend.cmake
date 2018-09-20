macro(cocos2dx_depend)
    # confim the libs, prepare to link
    set(PLATFORM_SPECIFIC_LIBS)

    if(WINDOWS)
        list(APPEND PLATFORM_SPECIFIC_LIBS ws2_32 userenv psapi winmm Version Iphlpapi)
    elseif(LINUX)
        # need review those libs: X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m
        list(APPEND PLATFORM_SPECIFIC_LIBS dl X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m)
    elseif(ANDROID)
        list(APPEND PLATFORM_SPECIFIC_LIBS GLESv2 EGL log android OpenSLES)
    elseif(APPLE)

        include_directories(/System/Library/Frameworks)
        find_library(ICONV_LIBRARY iconv)
        find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
        find_library(FOUNDATION_LIBRARY Foundation)
        find_library(OPENAL_LIBRARY OpenAL)
        find_library(QUARTZCORE_LIBRARY QuartzCore)
        find_library(GAMECONTROLLER_LIBRARY GameController)
        set(COCOS_APPLE_LIBS
            ${OPENAL_LIBRARY}
            ${AUDIOTOOLBOX_LIBRARY}
            ${QUARTZCORE_LIBRARY}
            ${FOUNDATION_LIBRARY}
            ${ICONV_LIBRARY}
            ${GAMECONTROLLER_LIBRARY}
            )

        if(BUILD_JS_LIBS)
            find_library(SQLITE3_LIBRARY SQLite3)
            list(APPEND COCOS_APPLE_LIBS ${SQLITE3_LIBRARY})
        endif()
            
        if(MACOSX)
            list(APPEND PREBUILT_SPECIFIC_LIBS GLFW3)

            find_library(COCOA_LIBRARY Cocoa)
            find_library(OPENGL_LIBRARY OpenGL)
            find_library(APPLICATIONSERVICES_LIBRARY ApplicationServices)
            find_library(IOKIT_LIBRARY IOKit)
            find_library(APPKIT_LIBRARY AppKit)
            list(APPEND PLATFORM_SPECIFIC_LIBS
                 ${COCOA_LIBRARY}
                 ${OPENGL_LIBRARY}
                 ${APPLICATIONSERVICES_LIBRARY}
                 ${IOKIT_LIBRARY}
                 ${COCOS_APPLE_LIBS}
                 ${APPKIT_LIBRARY}
                 )
        elseif(IOS)
            # Locate system libraries on iOS
            find_library(UIKIT_LIBRARY UIKit)
            find_library(OPENGLES_LIBRARY OpenGLES)
            find_library(CORE_MOTION_LIBRARY CoreMotion)
            find_library(MEDIA_PLAYER_LIBRARY MediaPlayer)
            find_library(CORE_TEXT_LIBRARY CoreText)
            find_library(SECURITY_LIBRARY Security)
            find_library(CORE_GRAPHICS_LIBRARY CoreGraphics)
            find_library(AV_FOUNDATION_LIBRARY AVFoundation)
            find_library(Z_LIBRARY z)
            list(APPEND PLATFORM_SPECIFIC_LIBS
                 ${UIKIT_LIBRARY}
                 ${OPENGLES_LIBRARY}
                 ${CORE_MOTION_LIBRARY}
                 ${MEDIA_PLAYER_LIBRARY}
                 ${CORE_TEXT_LIBRARY}
                 ${SECURITY_LIBRARY}
                 ${CORE_GRAPHICS_LIBRARY}
                 ${AV_FOUNDATION_LIBRARY}
                 ${Z_LIBRARY}
                 ${COCOS_APPLE_LIBS}
                 )
        endif()
    endif()
endmacro()

macro(cocos2dx_define)
    
    if(USE_JPEG)
        add_definitions(-DCC_USE_JPEG=1)
    else()
        add_definitions(-DCC_USE_JPEG=0)
    endif()

    if(USE_WEBP)
        add_definitions(-DCC_USE_WEBP=1)
    else()
        add_definitions(-DCC_USE_WEBP=0)
    endif()

    if(USE_TIFF)
        add_definitions(-DCC_USE_TIFF=1)
    else()
        add_definitions(-DCC_USE_TIFF=0)
    endif()

    if(USE_PNG)
        add_definitions(-DCC_USE_PNG=1)
    else()
        add_definitions(-DCC_USE_PNG=0)
    endif()

    if(USE_CHIPMUNK)
        add_definitions(-DCC_USE_PHYSICS=1)
        add_definitions(-DCC_ENABLE_CHIPMUNK_INTEGRATION=1)
    else()
        add_definitions(-DCC_USE_PHYSICS=0)
        add_definitions(-DCC_ENABLE_CHIPMUNK_INTEGRATION=0)
    endif()

    if(USE_BOX2D)
        add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=1)
    else()
        add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=0)
    endif(USE_BOX2D)

    if(USE_BULLET)
        add_definitions(-DCC_USE_3D_PHYSICS=1)
        add_definitions(-DCC_ENABLE_BULLET_INTEGRATION=1)
    else(USE_BULLET)
        add_definitions(-DCC_USE_3D_PHYSICS=0)
        add_definitions(-DCC_ENABLE_BULLET_INTEGRATION=0)
    endif(USE_BULLET)

    # tocheck, libuv option
    add_definitions(-DLWS_WITH_LIBUV)
endmacro()


macro(target_use_cocos2dx_depend target)
    cocos2dx_depend()
    cocos2dx_define()
    message(STATUS "${target} prepare to use depend: ${PLATFORM_SPECIFIC_LIBS}")
    foreach(platform_lib ${PLATFORM_SPECIFIC_LIBS})
        target_link_libraries(${target} ${platform_lib})
    endforeach()
endmacro()


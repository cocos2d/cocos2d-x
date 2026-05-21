macro(cocos2dx_depend)
    # confim the libs, prepare to link
    set(PLATFORM_SPECIFIC_LIBS)

    if(WINDOWS)
        list(APPEND PLATFORM_SPECIFIC_LIBS ws2_32 userenv psapi winmm Version Iphlpapi opengl32)
    elseif(LINUX)
        # need review those libs: X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m
        list(APPEND PLATFORM_SPECIFIC_LIBS dl X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m)
        # use older cmake style on below linux libs
        cocos_find_package(Fontconfig FONTCONFIG REQUIRED)	
        cocos_find_package(GTK3 GTK3 REQUIRED)
        cocos_find_package(ZLIB ZLIB REQUIRED)
        cocos_find_package(PNG PNG REQUIRED)
        cocos_find_package(GLEW GLEW REQUIRED)
        cocos_find_package(OpenGL OPENGL REQUIRED)
        cocos_find_package(CURL CURL REQUIRED)
        cocos_find_package(SQLite3 SQLITE3 REQUIRED)
        set(CMAKE_THREAD_PREFER_PTHREAD TRUE)	
        find_package(Threads REQUIRED)	
        set(THREADS_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
    elseif(ANDROID)
        list(APPEND PLATFORM_SPECIFIC_LIBS GLESv2 EGL log android OpenSLES)
    elseif(APPLE)

        include_directories(/System/Library/Frameworks)
        find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
        find_library(FOUNDATION_LIBRARY Foundation)
        find_library(OPENAL_LIBRARY OpenAL)
        find_library(QUARTZCORE_LIBRARY QuartzCore)
        find_library(GAMECONTROLLER_LIBRARY GameController)
        find_library(METAL_LIBRARY Metal)
        set(COCOS_APPLE_LIBS
            ${OPENAL_LIBRARY}
            ${AUDIOTOOLBOX_LIBRARY}
            ${QUARTZCORE_LIBRARY}
            ${FOUNDATION_LIBRARY}
            ${GAMECONTROLLER_LIBRARY}
            ${METAL_LIBRARY}
            )
            
        if(MACOSX)
            list(APPEND PREBUILT_SPECIFIC_LIBS GLFW3)

            find_library(COCOA_LIBRARY Cocoa)
            find_library(OPENGL_LIBRARY OpenGL)
            find_library(APPLICATIONSERVICES_LIBRARY ApplicationServices)
            find_library(IOKIT_LIBRARY IOKit)
            find_library(APPKIT_LIBRARY AppKit)
            find_library(ICONV_LIBRARY iconv)
            list(APPEND PLATFORM_SPECIFIC_LIBS
                 ${COCOA_LIBRARY}
                 ${OPENGL_LIBRARY}
                 ${APPLICATIONSERVICES_LIBRARY}
                 ${IOKIT_LIBRARY}
                 ${COCOS_APPLE_LIBS}
                 ${APPKIT_LIBRARY}
                 ${ICONV_LIBRARY}
                 )
        elseif(IOS)
            # Locate system libraries on iOS
            find_library(UIKIT_LIBRARY UIKit)
            find_library(OPENGLES_LIBRARY OpenGLES)
            find_library(CORE_MOTION_LIBRARY CoreMotion)
            find_library(AVKIT_LIBRARY AVKit)
            find_library(CORE_MEDIA_LIBRARY CoreMedia)
            find_library(CORE_TEXT_LIBRARY CoreText)
            find_library(SECURITY_LIBRARY Security)
            find_library(CORE_GRAPHICS_LIBRARY CoreGraphics)
            find_library(AV_FOUNDATION_LIBRARY AVFoundation)
            find_library(WEBKIT_LIBRARY WebKit)
            find_library(ZLIB_LIBRARY z)
            find_library(ICONV_LIBRARY iconv)
            list(APPEND PLATFORM_SPECIFIC_LIBS
                 ${UIKIT_LIBRARY}
                 ${OPENGLES_LIBRARY}
                 ${CORE_MOTION_LIBRARY}
                 ${AVKIT_LIBRARY}
                 ${CORE_MEDIA_LIBRARY}
                 ${CORE_TEXT_LIBRARY}
                 ${SECURITY_LIBRARY}
                 ${CORE_GRAPHICS_LIBRARY}
                 ${AV_FOUNDATION_LIBRARY}
                 ${WEBKIT_LIBRARY}
                 ${COCOS_APPLE_LIBS}
                 ${ZLIB_LIBRARY}
                 ${ICONV_LIBRARY}
                 )
        endif()
    endif()
endmacro()

macro(use_cocos2dx_libs_depend target)
    cocos2dx_depend()
    foreach(platform_lib ${PLATFORM_SPECIFIC_LIBS})
        target_link_libraries(${target} ${platform_lib})
    endforeach()

    if(LINUX)
        cocos_use_pkg(${target} FONTCONFIG)
        cocos_use_pkg(${target} GTK3)
        cocos_use_pkg(${target} ZLIB)
        cocos_use_pkg(${target} PNG)
        cocos_use_pkg(${target} GLEW)
        cocos_use_pkg(${target} OPENGL)
        cocos_use_pkg(${target} CURL)
        cocos_use_pkg(${target} THREADS)
        cocos_use_pkg(${target} SQLITE3)
    endif()
endmacro()


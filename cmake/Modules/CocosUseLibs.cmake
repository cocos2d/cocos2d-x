macro(cocos2d_depend_libs)
    # confim the libs, prepare to link
    set(PLATFORM_SPECIFIC_LIBS)
    # confim the prebuilt libs, prepare to use
    set(PREBUILT_SPECIFIC_LIBS)

    if(WINDOWS)
        foreach(_pkg OPENGL GLEW GLFW3 VORBIS MPG123 OPENAL SQLITE3)
            list(APPEND PREBUILT_SPECIFIC_LIBS ${_pkg})
        endforeach()
        list(APPEND PLATFORM_SPECIFIC_LIBS ws2_32 winmm Version Iphlpapi)
        if(MINGW)
            list(APPEND PLATFORM_SPECIFIC_LIBS shlwapi version)
        endif()
    elseif(LINUX)
        # need review those libs: X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m
        list(APPEND PLATFORM_SPECIFIC_LIBS dl X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m)
        foreach(_pkg OPENGL GLEW GLFW3 FMOD FONTCONFIG THREADS GTK3 SQLITE3)
            list(APPEND PREBUILT_SPECIFIC_LIBS ${_pkg})
        endforeach()
    elseif(ANDROID)
        list(APPEND PLATFORM_SPECIFIC_LIBS GLESv2 EGL log android OpenSLES)
        list(APPEND PREBUILT_SPECIFIC_LIBS TREMOLO PVMP3DEC CPUFEATURES)
    elseif(APPLE)

        include_directories(/System/Library/Frameworks)
        find_library(ICONV_LIBRARY iconv)
        find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
        find_library(FOUNDATION_LIBRARY Foundation)
        find_library(OPENAL_LIBRARY OpenAL)
        find_library(QUARTZCORE_LIBRARY QuartzCore)
        set(COCOS_APPLE_LIBS
            ${OPENAL_LIBRARY}
            ${AUDIOTOOLBOX_LIBRARY}
            ${QUARTZCORE_LIBRARY}
            ${FOUNDATION_LIBRARY}
            ${ICONV_LIBRARY}
            )

        if(MACOSX)
            list(APPEND PREBUILT_SPECIFIC_LIBS GLFW3)

            find_library(COCOA_LIBRARY Cocoa)
            find_library(OPENGL_LIBRARY OpenGL)
            find_library(APPLICATIONSERVICES_LIBRARY ApplicationServices)
            find_library(IOKIT_LIBRARY IOKit)
            list(APPEND PLATFORM_SPECIFIC_LIBS
                 ${COCOA_LIBRARY}
                 ${OPENGL_LIBRARY}
                 ${APPLICATIONSERVICES_LIBRARY}
                 ${IOKIT_LIBRARY}
                 ${COCOS_APPLE_LIBS}
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

    foreach(_pkg ZLIB MINIZIP TinyXML2 FREETYPE WEBSOCKETS CURL FLATBUFFERS XXHASH)
        list(APPEND PREBUILT_SPECIFIC_LIBS ${_pkg})
    endforeach()

    if(NOT EMSCRIPTEN)
        list(APPEND PREBUILT_SPECIFIC_LIBS OPENSSL)
    endif()

    if(USE_JPEG)
        add_definitions(-DCC_USE_JPEG=1)
        list(APPEND PREBUILT_SPECIFIC_LIBS JPEG)
    else()
        add_definitions(-DCC_USE_JPEG=0)
    endif()

    if(USE_WEBP)
        cocos_find_package(WebP WEBP REQUIRED)
        add_definitions(-DCC_USE_WEBP=1)
        list(APPEND PREBUILT_SPECIFIC_LIBS WEBP)
    else()
        add_definitions(-DCC_USE_WEBP=0)
    endif()

    if(USE_TIFF)
        add_definitions(-DCC_USE_TIFF=1)
        list(APPEND PREBUILT_SPECIFIC_LIBS TIFF)
    else()
        add_definitions(-DCC_USE_TIFF=0)
    endif()

    if(USE_PNG)
        add_definitions(-DCC_USE_PNG=1)
        list(APPEND PREBUILT_SPECIFIC_LIBS PNG)
    else()
        add_definitions(-DCC_USE_PNG=0)
    endif()

    if(USE_CHIPMUNK)
        cocos_find_package(Chipmunk CHIPMUNK REQUIRED)
        add_definitions(-DCC_USE_PHYSICS=1)
        add_definitions(-DCC_ENABLE_CHIPMUNK_INTEGRATION=1)
        list(APPEND PREBUILT_SPECIFIC_LIBS CHIPMUNK)
    else()
        add_definitions(-DCC_USE_PHYSICS=0)
        add_definitions(-DCC_ENABLE_CHIPMUNK_INTEGRATION=0)
    endif()

    if(USE_BOX2D)
        cocos_find_package(box2d Box2D REQUIRED)
        add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=1)
        list(APPEND PREBUILT_SPECIFIC_LIBS Box2D)
    else()
        add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=0)
    endif(USE_BOX2D)

    if(USE_BULLET)
        cocos_find_package(bullet BULLET REQUIRED)
        add_definitions(-DCC_USE_3D_PHYSICS=1)
        add_definitions(-DCC_ENABLE_BULLET_INTEGRATION=1)
        list(APPEND PREBUILT_SPECIFIC_LIBS BULLET)
    else(USE_BULLET)
        add_definitions(-DCC_USE_3D_PHYSICS=0)
        add_definitions(-DCC_ENABLE_BULLET_INTEGRATION=0)
    endif(USE_BULLET)

    if(USE_RECAST)
        list(APPEND PREBUILT_SPECIFIC_LIBS RECAST)
    endif()
endmacro()

macro(target_use_cocos2d_depend_libs target)
    cocos2d_depend_libs()
    message(STATUS "${target} prepare to use cpp needed libs: ${PREBUILT_SPECIFIC_LIBS}")
    foreach(prebuilt_lib ${PREBUILT_SPECIFIC_LIBS})
        cocos_use_pkg(${target} ${prebuilt_lib})
    endforeach()
    foreach(platform_lib ${PLATFORM_SPECIFIC_LIBS})
        target_link_libraries(${target} ${platform_lib})
    endforeach()
endmacro()

macro(jscocos2d_depend_libs)
    set(PLATFORM_SPECIFIC_LIBS)
    set(PREBUILT_SPECIFIC_LIBS)

    list(APPEND PREBUILT_SPECIFIC_LIBS SPIDERMONKEY)
    if(APPLE)
        find_library(GAME_CONTROLLER GameController)
        list(APPEND PLATFORM_SPECIFIC_LIBS ${GAME_CONTROLLER})
        list(APPEND PREBUILT_SPECIFIC_LIBS SQLITE3)
    endif()
endmacro()

macro(target_use_jscocos2d_depend_libs target)
    jscocos2d_depend_libs()
    message(STATUS "${target} prepare to use js needed libs: ${PREBUILT_SPECIFIC_LIBS}")
    foreach(prebuilt_lib ${PREBUILT_SPECIFIC_LIBS})
        cocos_use_pkg(${target} ${prebuilt_lib})
    endforeach()
    foreach(platform_lib ${PLATFORM_SPECIFIC_LIBS})
        target_link_libraries(${target} ${platform_lib})
    endforeach()
endmacro()

macro(luacocos2d_depend_libs)
    set(PLATFORM_SPECIFIC_LIBS)
    set(PREBUILT_SPECIFIC_LIBS)
    list(APPEND PREBUILT_SPECIFIC_LIBS LUAJIT)
endmacro()

macro(target_use_luacocos2d_depend_libs target)
    luacocos2d_depend_libs()
    message(STATUS "${target} prepare to use lua needed libs: ${PREBUILT_SPECIFIC_LIBS}")
    foreach(prebuilt_lib ${PREBUILT_SPECIFIC_LIBS})
        cocos_use_pkg(${target} ${prebuilt_lib})
    endforeach()
    foreach(platform_lib ${PLATFORM_SPECIFIC_LIBS})
        target_link_libraries(${target} ${platform_lib})
    endforeach()
endmacro()

macro(simulator_depend_libs)
    set(PLATFORM_SPECIFIC_LIBS)
    set(PREBUILT_SPECIFIC_LIBS)
    if(MACOSX)
        include_directories(/System/Library/Frameworks)
        find_library(APPKIT_LIBRARY AppKit)
        list(APPEND PLATFORM_SPECIFIC_LIBS ${APPKIT_LIBRARY})
    elseif(WINDOWS)
        list(APPEND PREBUILT_SPECIFIC_LIBS TinyXML2 CURL)
    endif()

endmacro()

macro(target_use_simulator_depend_libs target)
    simulator_depend_libs()
    if(WINDOWS)
        message(STATUS "${target} prepare to use simulator needed libs: ${PREBUILT_SPECIFIC_LIBS}")
    endif()
    foreach(prebuilt_lib ${PREBUILT_SPECIFIC_LIBS})
        cocos_use_pkg(${target} ${prebuilt_lib})
    endforeach()
    foreach(platform_lib ${PLATFORM_SPECIFIC_LIBS})
        target_link_libraries(${target} ${platform_lib})
    endforeach()
endmacro()
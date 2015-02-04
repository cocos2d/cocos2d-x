# CocosUsePrebuiltLibs - sets external libs variables to link with

# if(_COCOS_USE_PREBUILT_LIBS_CMAKE)
#     return()
# endif()
# set(_COCOS_USE_PREBUILT_LIBS_CMAKE TRUE)

# This file use some macros defined in Cocosbuildhelpers.cmake.
#if(NOT _COCOS_BUILD_HELPERS_CMAKE)
#    message(AUTHOR_WARNING "Include CocosBuildHelpers first.")
#endif()

# This file define all prebuilt libraries as target.
# Each prebuilt library has:
# TARGET: target name of this library, upper case.
# <TARGET>_INCLUDE_DIR
# <TARGET>_LIBRARY
# <TARGET>_RUNTIME:  If is a dll library, has this variable.

#===============================================================================
# Define some useful macro for simplify the code.

# Helper variable, indicated the <cocos>/external directory.
get_filename_component(external_dir 
    "${CMAKE_CURRENT_LIST_DIR}/../../external" ABSOLUTE
    )

# Output some message if some prebuilt lib found.
macro(COCOS_FOUND_PREBUILT)
    set(${_target}_USE_PREBUILT TRUE)
    set(${_target}_FOUND TRUE)
    message(STATUS "Found prebuilt '${_target}::${_target}': "
        "${${_target}_RUNTIME} ${${_target}_LIBRARY} ${${_target}_INCLUDE_DIR}"
        )
endmacro()

# Output some message if there is no prebuilt lib found.
macro(COCOS_NOT_FOUND_PREBUILT)
    message(AUTHOR_WARNING "There is no prebuilt '${_target}' for target system "
        "'${CMAKE_SYSTEM_NAME}' in directory '${_path}'."
        )
endmacro()

# 'B'efore 'C'heck the 'P'rebuilt library exists or not, define some local variables.
# _target: the target name
# _path: the location which prebuilt library in external folder.
# _header: the include header file in source file. 
macro(_BCP _name _path _header_file)
    string(TOUPPER ${_name} _target)
    if(TARGET ${_target} OR ${_target}_FOUND})
        return()
    endif()
    set(_path "${external_dir}/${_path}")
    set(_header ${_header_file})
endmacro()

# 'C'heck the 'P'ribuilt 'L'ibrary exists or not for given include path and lib path by
# need predefined vars:
# _target
# _path
# _header
macro(_CPL _inc_path_surffix _lib_name _lib_path_surffix)
    set(_old_mode_include ${CMAKE_FIND_ROOT_PATH_MODE_INCLUDE})
    set(_old_mode_library ${CMAKE_FIND_ROOT_PATH_MODE_LIBRARY})
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
    find_path(${_target}_INCLUDE_DIR ${_header}
        HINTS ${_path}
        PATH_SUFFIXES ${_inc_path_surffix}
        NO_DEFAULT_PATH
        )
    #message("_path:${_path}/${_inc_path_surffix}/${_header}")
    find_library(${_target}_LIBRARY ${_lib_name}
        HINTS ${_path}
        PATH_SUFFIXES ${_lib_path_surffix}
        NO_DEFAULT_PATH
        )
    if(NOT ${_target}_INCLUDE_DIR OR NOT ${_target}_LIBRARY)
        COCOS_NOT_FOUND_PREBUILT()
        set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ${_old_mode_library})
        set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ${_old_mode_include})
        return()
    endif()
    # Add target.
    add_library(${_target}::${_target} UNKNOWN IMPORTED)
    set_target_properties(${_target}::${_target} PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${${_target}_INCLUDE_DIR}
        IMPORTED_LOCATION ${${_target}_LIBRARY}
    )
    COCOS_FOUND_PREBUILT()
    mark_as_advanced(${_target}_INCLUDE_DIR ${_target}_LIBRARY)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ${_old_mode_library})
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ${_old_mode_include})
endmacro()

# Check the prebuilt library with dll.
macro(_CPLD _inc_path_surffix _lib_name _lib_path_surffix _dll_path)
    #message("_path:${_path}")
    #message("_header:${_header}")
    find_path(${_target}_INCLUDE_DIR ${_header}
        HINTS ${_path}
        PATH_SUFFIXES ${_inc_path_surffix}
        NO_DEFAULT_PATH
        )
    find_library(${_target}_LIBRARY ${_lib_name}
        HINTS ${_path}
        PATH_SUFFIXES ${_lib_path_surffix}
        NO_DEFAULT_PATH
        )
    find_file(${_target}_RUNTIME ${_dll_path}
        HINTS ${_path}
        NO_DEFAULT_PATH
        )
    if(NOT ${_target}_INCLUDE_DIR OR
            NOT ${_target}_LIBRARY OR
            NOT ${_target}_RUNTIME)
        COCOS_NOT_FOUND_PREBUILT()
        return()
    endif()
    # Add target.
    add_library(${_target}::${_target} SHARED IMPORTED)
    set_target_properties(${_target}::${_target} PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${${_target}_INCLUDE_DIR}
        IMPORTED_LOCATION ${${_target}_RUNTIME}
        IMPORTED_IMPLIB ${${_target}_LIBRARY}
    )
    COCOS_FOUND_PREBUILT()
    mark_as_advanced(${_target}_INCLUDE_DIR ${_target}_LIBRARY)
    mark_as_advanced(${_target}_RUNTIME)
endmacro()

#===============================================================================
# chipmunk
function(load_prebuilt_chipmunk)
    _BCP(chipmunk "chipmunk" "chipmunk.h")

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/chipmunk" "chipmunk" "prebuilt/mac")
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPL("include/chipmunk" "libchipmunk" "prebuilt/win32/release-lib")
        find_library(CHIPMUNK_LIBRARY_DEBUG "libchipmunk"
            HINTS ${_path}
            PATH_SUFFIXES "prebuilt/win32/debug-lib"
            NO_DEFAULT_PATH
            )
        set_target_properties(${_target}::${_target} PROPERTIES
            IMPORTED_LOCATION_RELEASE ${CHIPMUNK_LIBRARY}
            IMPORTED_LOCATION_DEBUG ${CHIPMUNK_LIBRARY_DEBUG}
            )
        mark_as_advanced(CHIPMUNK_LIBRARY_DEBUG)
    elseif(COCOS_TARGET_SYSTEM_LINUX)
        _CPL("include/chipmunk" "chipmunk" "prebuilt/linux/${COCOS_ARCH_FOLDER_SUFFIX}")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include/chipmunk" "chipmunk" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include/chipmunk" "chipmunk" "prebuilt/android/${ANDROID_ABI}")
    endif()
endfunction()
load_prebuilt_chipmunk()

#===============================================================================
# curl
function(load_prebuilt_curl)
    _BCP(curl "curl" "curl/curl.h") 

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/mac" "curl" "prebuilt/mac")
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include/win32" "libcurl_imp" "prebuilt/win32" "prebuilt/win32/libcurl.dll")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include/ios" "curl" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include/android" "curl" "prebuilt/android/${ANDROID_ABI}")
    else()
        return()
    endif()
    # Load crypto and ssl.
    _BCP(crypto "curl" "curl/easy.h")

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/mac" "crypto" "prebuilt/mac")
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include/win32" "libcurl_imp" "prebuilt/win32" "prebuilt/win32/libeay32.dll")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include/ios" "crypto" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include/android" "crypto" "prebuilt/android/${ANDROID_ABI}")
    endif()

    _BCP(OpenSSL "curl" "curl/easy.h")
    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/mac" "ssl" "prebuilt/mac")
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include/win32" "libcurl_imp" "prebuilt/win32" "prebuilt/win32/ssleay32.dll")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include/ios" "ssl" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include/android" "ssl" "prebuilt/android/${ANDROID_ABI}")
    endif()
    message(STATUS "Target 'CURL' depends: CRYPTO, OPENSSL.")
endfunction()
load_prebuilt_curl()

#===============================================================================
# fmodex
function(load_prebuilt_fmodex)
    _BCP(fmodex "linux-specific/fmod" "fmod.h") 

    if(COCOS_TARGET_SYSTEM_LINUX)
        set(_path "${external_dir}/linux-specific/fmod")
        if(BUILD_TARGET_ARCHITECTURE MATCHES "x86_64")
            _CPL("include/${COCOS_ARCH_FOLDER_SUFFIX}" "fmodex64" "prebuilt/${COCOS_ARCH_FOLDER_SUFFIX}")
        else()
            _CPL("include/${COCOS_ARCH_FOLDER_SUFFIX}" "fmodex" "prebuilt/${COCOS_ARCH_FOLDER_SUFFIX}")
        endif()
    endif()
endfunction()
load_prebuilt_fmodex()

#===============================================================================
# freetype2
function(load_prebuilt_freetype)
    _BCP(freetype "freetype2" "ft2build.h")

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/mac" "freetype" "prebuilt/mac")
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPL("include/win32" "freetype250" "prebuilt/win32")
    elseif(COCOS_TARGET_SYSTEM_LINUX)
        _CPL("include/linux" "freetype" "prebuilt/linux/${COCOS_ARCH_FOLDER_SUFFIX}")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include/ios" "freetype" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include/android" "freetype" "prebuilt/android/${ANDROID_ABI}")
        get_target_property(_inc_dir ${_target}::${_target} INTERFACE_INCLUDE_DIRECTORIES)
        set_target_properties(${_target}::${_target} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${_inc_dir};${${_target}_INCLUDE_DIR}/freetype2"
            )
    endif()
endfunction()
load_prebuilt_freetype()

#===============================================================================
# glew
function(load_prebuilt_glew)
    _BCP(glew "win32-specific/gles" "GL/glew.h")

    if(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include/OGLES" "glew32" "prebuilt" "prebuilt/glew32.dll")
    endif()
endfunction()
load_prebuilt_glew()

#===============================================================================
# glfw3
function(load_prebuilt_glfw3)
    _BCP(glfw3 "glfw3" "glfw3.h")

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/mac" "glfw3" "prebuilt/mac")
        set_target_properties(${_target}::${_target} PROPERTIES
            INTERFACE_LINK_LIBRARIES "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo"
            )
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPL("include/win32" "glfw3" "prebuilt/win32")
        find_package(OpenGL REQUIRED)
        set_target_properties(${_target}::${_target} PROPERTIES
            INTERFACE_LINK_LIBRARIES "${OPENGL_gl_LIBRARY}"
            )
    endif()
endfunction()
load_prebuilt_glfw3()

#===============================================================================
# jpeg
function(load_prebuilt_jpeg)
    _BCP(jpeg "jpeg" "jpeglib.h")

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/mac" "jpeg" "prebuilt/mac")
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPL("include/win32" "libjpeg" "prebuilt/win32")
    elseif(COCOS_TARGET_SYSTEM_LINUX)
        _CPL("include/linux" "jpeg" "prebuilt/linux/${COCOS_ARCH_FOLDER_SUFFIX}")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include/ios" "jpeg" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include/android" "jpeg" "prebuilt/android/${ANDROID_ABI}")
    endif()
endfunction()
load_prebuilt_jpeg()

#===============================================================================
#luajit
function(load_prebuilt_luajit)
    _BCP(luajit "lua/luajit" "lua.h")

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include" "luajit" "prebuilt/mac")
        # luajit works on apple need special link options.
        set_target_properties(${_target}::${_target} PROPERTIES
            IMPORTED_LINK_INTERFACE_LIBRARIES "-pagezero_size 10000 -image_base 100000000"
            )
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include" "lua51" "prebuilt/win32" "prebuilt/win32/lua51.dll")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include" "luajit" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include" "luajit" "prebuilt/android/${ANDROID_ABI}")
    endif()
endfunction()
load_prebuilt_luajit()

#===============================================================================
# mpg123
function(load_prebuilt_mpg123)
    _BCP(mpg123 "win32-specific/MP3Decoder" "mpg123.h")

    if(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include" "libmpg123" "prebuilt" "prebuilt/libmpg123.dll")
    endif()
endfunction()
load_prebuilt_mpg123()

#===============================================================================
# ogg
function(load_prebuilt_ogg)
    if(COCOS_TARGET_SYSTEM_WINDOWS)
        _BCP(ogg "win32-specific/OggDecoder" "ogg/ogg.h")
        _CPLD("include" "libogg" "prebuilt" "prebuilt/libogg.dll")
        _BCP(vorbis "win32-specific/OggDecoder" "vorbis/codec.h")
        _CPLD("include" "libvorbis" "prebuilt" "prebuilt/libvorbis.dll")
        _BCP(vorbisfile "win32-specific/OggDecoder" "vorbis/vorbisfile.h")
        _CPLD("include" "libvorbisfile" "prebuilt" "prebuilt/libvorbisfile.dll")
        message(STATUS "Target '${_target}' depends: VORBIS, VORBISFILE.")
    endif()
endfunction()
load_prebuilt_ogg()

#===============================================================================
# OpenAL
function(load_prebuilt_openal)
    _BCP(OpenAL "win32-specific/OpenalSoft" "AL/al.h")

    if(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include" "OpenAL32" "prebuilt" "prebuilt/OpenAL32.dll")
    endif()
endfunction()
load_prebuilt_openal()

#===============================================================================
# png
function(load_prebuilt_png)
    _BCP(png "png" "png.h")

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/mac" "png" "prebuilt/mac")
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPL("include/win32" "libpng" "prebuilt/win32")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include/ios" "png" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include/android" "png" "prebuilt/android/${ANDROID_ABI}")
    else()
        return()
    endif()
    message(STATUS "Target '${_target}' depends: ZLIB.")
endfunction()
load_prebuilt_png()

#===============================================================================
# sqlite3
function(load_prebuilt_sqlite3)
    _BCP(sqlite3 "sqlite3" "sqlite3.h")

    if(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include" "sqlite3" "libraries/win32" "libraries/win32/sqlite3.dll")
    endif()
endfunction()
load_prebuilt_sqlite3()

#===============================================================================
# tiff
function(load_prebuilt_tiff)
    _BCP(tiff "tiff" "tiff.h")

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/mac" "tiff" "prebuilt/mac")
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include/win32" "libtiff" "prebuilt/win32" "prebuilt/win32/libtiff.dll")
    elseif(COCOS_TARGET_SYSTEM_LINUX)
        _CPL("include/linux" "tiff" "prebuilt/linux/${COCOS_ARCH_FOLDER_SUFFIX}")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include/ios" "tiff" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include/android" "tiff" "prebuilt/android/${ANDROID_ABI}")
    endif()
endfunction()
load_prebuilt_tiff()

#===============================================================================
# webp
function(load_prebuilt_webp)
    _BCP(webp "webp" "decode.h")

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/mac" "webp" "prebuilt/mac")
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPL("include/win32" "libwebp" "prebuilt/win32")
    elseif(COCOS_TARGET_SYSTEM_LINUX)
        _CPL("include/linux" "webp" "prebuilt/linux/${COCOS_ARCH_FOLDER_SUFFIX}")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include/ios" "webp" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include/android" "webp" "prebuilt/android/${ANDROID_ABI}")
        message(STATUS "Target '${_target}' depends: cpufeatures.")
    endif()
endfunction()
load_prebuilt_webp()

#===============================================================================
# websockets
function(load_prebuilt_websockets)
    _BCP(websockets "websockets" "libwebsockets.h")

    if(COCOS_TARGET_SYSTEM_MACOSX)
        _CPL("include/mac" "websockets" "prebuilt/mac")
    elseif(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include/win32" "websockets" "prebuilt/win32" "prebuilt/win32/websockets.dll")
    elseif(COCOS_TARGET_SYSTEM_LINUX)
        _CPL("include/linux" "websockets" "prebuilt/linux/${COCOS_ARCH_FOLDER_SUFFIX}")
    elseif(COCOS_TARGET_SYSTEM_IOS)
        _CPL("include/ios" "websockets" "prebuilt/ios")
    elseif(COCOS_TARGET_SYSTEM_ANDROID)
        _CPL("include/android" "websockets" "prebuilt/android/${ANDROID_ABI}")
    endif()
endfunction()
load_prebuilt_websockets()

#===============================================================================
# zlib
function(load_prebuilt_zlib)
    _BCP(zlib "win32-specific/zlib" "zlib.h")
    
    if(COCOS_TARGET_SYSTEM_WINDOWS)
        _CPLD("include" "libzlib" "prebuilt" "prebuilt/zlib1.dll")
    endif()
endfunction()
load_prebuilt_zlib()

#===============================================================================

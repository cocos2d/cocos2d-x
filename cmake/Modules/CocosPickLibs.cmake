# CocosPickLibs - sets external libs variables to link with

# START CONFIG

# record all the prebuilt libs which found for specific platform
set(COCOS_EXTERNAL_LIBS)

# Debug build use debug folder libs, Release build use release folder libs
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE_FOLDER)

# RelWithDebInfo is one of Visual Studio 2017 default build type
if(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    # RelWithDebInfo build use release folder libs
    set(BUILD_TYPE_FOLDER "release")  
endif()

set(_chipmunk_inc chipmunk/chipmunk.h)
set(_chipmunk_inc_paths include)
if(WINDOWS)
    if(MSVC)
        set(_chipmunk_libs chipmunk libchipmunk libchipmunk-2015)
    else()
        set(_chipmunk_libs chipmunk libchipmunk)
    endif()
else()
    set(_chipmunk_libs chipmunk libchipmunk)
endif(WINDOWS)

set(_bullet_inc bullet/Bullet-C-Api.h BulletCollision/btBulletCollisionCommon.h)
set(_bullet_inc_paths bullet)
# sequence is important
set(_bullet_libs BulletDynamics libBulletDynamics BulletCollision libBulletCollision BulletMultiThreaded libBulletMultiThreaded LinearMath libLinearMath MiniCL libMiniCL)
if(MSVC)
    set(_bullet_libs bullet libbullet)
endif()

set(_Box2D_inc Box2D/Box2D.h)
set(_Box2D_inc_paths include)
set(_Box2D_libs box2d libbox2d)
set(_Box2D_prefix Box2D)

set(_glfw3_inc glfw3.h glfw3native.h)
set(_glfw3_libs glfw3 libglfw3)

set(_curl_inc curl/curl.h)
# order: curl, ssl, crypto
set(_curl_libs curl libcurl_imp libcurl ssl libeay32 ssleay32 crypto)

set(_freetype2_prefix FREETYPE)
set(_freetype2_inc ft2build.h freetype/freetype.h)
set(_freetype2_inc_paths freetype2)
set(_freetype2_libs freetype freetype250)

set(_jpeg_inc jpeglib.h)
if(WINDOWS)
    if(MSVC)
        set(_jpeg_libs jpeg libjpeg libjpeg-2015)
    else()
        set(_jpeg_libs jpeg libjpeg)
    endif()
else()
    set(_jpeg_libs jpeg libjpeg)
endif(WINDOWS)

set(_png_inc png.h)
if(WINDOWS)
    if(MSVC)
        set(_png_libs png libpng libpng-2015)
    else()
        set(_png_libs png libpng)
    endif()
else()
    set(_png_libs png libpng)
endif(WINDOWS)

set(_tiff_inc tiff.h)
if(WINDOWS)
    if(MSVC)
        set(_tiff_libs tiff libtiff libtiff-2015)
    else()
        set(_tiff_libs tiff libtiff)
    endif()
else()
    set(_tiff_libs tiff libtiff)
endif(WINDOWS)

set(_webp_inc decode.h)
set(_webp_libs webp libwebp)

set(_websockets_inc libwebsockets.h)
set(_websockets_libs websockets libwebsockets)

set(_openssl_inc openssl/ssl.h)
set(_openssl_libs ssl crypto)
if(MSVC)
    set(_openssl_libs ssl crypto libssl libcrypto)
endif()

set(_sqlite3_inc sqlite3.h)
set(_sqlite3_libs sqlite3)

set(_gles_prefix GLEW)
set(_gles_inc GL/glew.h)
set(_gles_inc_paths OGLES)
set(_gles_libs glew32)

set(_icon_prefix ICONV)
set(_icon_inc iconv.h)
set(_icon_libs libiconv)

set(_MP3Decoder_prefix MPG123)
set(_MP3Decoder_inc mpg123.h)
set(_MP3Decoder_libs libmpg123)

set(_OggDecoder_prefix VORBIS)
set(_OggDecoder_inc ogg/ogg.h)
set(_OggDecoder_libs libogg libvorbis libvorbisfile)

set(_OpenalSoft_prefix OPENAL)
set(_OpenalSoft_inc al.h)
set(_OpenalSoft_inc_paths AL)
set(_OpenalSoft_libs OpenAL32)

set(_zlib_inc zlib.h)
set(_zlib_libs z libzlib libz)
if(MSVC)
    set(_zlib_libs libzlib)
    # zlib's dll is so special, lib name and dll name is different
    # single special
    set(_zlib_dll zlib1)
endif()

set(_fmod_prefix FMOD)
set(_fmod_inc fmod.hpp)
set(_fmod_libs fmod fmod64 fmod fmod64)

set(_luajit_prefix LUAJIT)
set(_luajit_inc lua.hpp)
set(_luajit_libs luajit)
if(MSVC)
    set(_luajit_libs lua51)
endif()

set(_spidermonkey_prefix SPIDERMONKEY)
set(_spidermonkey_inc jsapi.h)
set(_spidermonkey_libs js_static)
if(MSVC)
    set(_spidermonkey_libs mozjs-33)
endif()

set(all_prebuilt_libs
    chipmunk
    curl
    freetype2
    jpeg
    png
    tiff
    webp
    websockets
    openssl
    bullet
    Box2D
    luajit
    spidermonkey
    )


if(MACOSX)
    list(APPEND all_prebuilt_libs glfw3 zlib)
endif()

# We use MSVC instead of WINDOWS because it can be mingw that can't use our prebuilt libs
if(MSVC)
    list(APPEND all_prebuilt_libs glfw3 sqlite3 gles icon MP3Decoder OggDecoder OpenalSoft zlib)
endif()

if(LINUX)
    list(APPEND all_prebuilt_libs fmod glfw3)
endif()

if(ANDROID)
    list(APPEND all_prebuilt_libs zlib)
endif()

# END CONFIG

foreach(_lib ${all_prebuilt_libs})
    if(_${_lib}_prefix)
        set(_prefix ${_${_lib}_prefix})
    else()
        # auto-prefix is uppercased name
        string(TOUPPER ${_lib} _prefix)
        set(_${_lib}_prefix ${_prefix})
    endif()

    set(roots
        ${COCOS_EXTERNAL_DIR}/${_lib}
        ${COCOS_EXTERNAL_DIR}/${PLATFORM_FOLDER}-specific/${_lib}
        #lua/luajit
        ${COCOS_EXTERNAL_DIR}/lua/${_lib}
        )
    foreach(_root ${roots})
        if(EXISTS ${_root})
            set(include_dir_candidates
                ${_root}/include
                ${_root}/include/${ARCH_DIR}
                ${_root}/include/${PLATFORM_FOLDER}
                ${_root}/include/${PLATFORM_FOLDER}/${ARCH_DIR}
                )
            set(include_dirs)
            foreach(_dir ${include_dir_candidates})
                if(EXISTS ${_dir})
                    # find all include paths
                    if(_${_lib}_inc_paths)
                        set(_suffixes ${_${_lib}_inc_paths})
                    else()
                        set(_suffixes include)
                    endif()
                    foreach(_inc_name ${_${_lib}_inc})
                        unset(_inc_tmp CACHE)
                        find_path(_inc_tmp ${_inc_name} PATH_SUFFIXES ${_suffixes} PATHS ${_dir} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
                        if(_inc_tmp)
                            list(APPEND include_dirs ${_inc_tmp})
                        endif()
                    endforeach()
                endif(EXISTS ${_dir})
            endforeach()
            if(include_dirs)
                list(REMOVE_DUPLICATES include_dirs)
                set(${_prefix}_INCLUDE_DIRS ${include_dirs} CACHE PATH "Path to includes for ${_prefix}" FORCE)
                message(STATUS "${_lib} ${_prefix}_INCLUDE_DIRS: ${${_prefix}_INCLUDE_DIRS}")
                # don't find lib, if not find include in once ${_root} search
                set(lib_dir_candidates
                    ${_root}/prebuilt/${PLATFORM_FOLDER}
                    ${_root}/prebuilt/${PLATFORM_FOLDER}/${BUILD_TYPE_FOLDER}
                    ${_root}/prebuilt/${PLATFORM_FOLDER}/${BUILD_TYPE_FOLDER}-lib
                    ${_root}/libraries/${PLATFORM_FOLDER}
                    ${_root}/prebuilt
                    )
                if(ANDROID_ABI)
                    list(APPEND lib_dir_candidates ${_root}/prebuilt/${PLATFORM_FOLDER}/${ANDROID_ABI})
                endif()
                if(ARCH_DIR)
                    list(APPEND lib_dir_candidates ${_root}/prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR})
                    list(APPEND lib_dir_candidates ${_root}/prebuilt/${ARCH_DIR})
                endif()
                set(libs)
                set(dlls)
                foreach(_dir ${lib_dir_candidates})
                    if(EXISTS ${_dir})
                        # find all libs
                        foreach(_lib_name ${_${_lib}_libs})
                            find_library(_lib_tmp ${_lib_name} PATHS ${_dir} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
                            if(_lib_tmp)
                                list(APPEND libs ${_lib_tmp})
                                #find dlls for _lib_tmp
                                if(MSVC)
                                    cocos_find_dlls_for_lib(_dll_tmp LIB_ABS_PATH ${_lib_tmp})
                                endif()
                                list(APPEND dlls ${_dll_tmp})
                                unset(_dll_tmp CACHE)
                            endif()
                            unset(_lib_tmp CACHE)
                        endforeach()
                    endif(EXISTS ${_dir})
                endforeach()

                if(libs)
                    set(${_prefix}_LIBRARIES ${libs} CACHE STRING "Libraries to link for ${_prefix}" FORCE)
                    message(STATUS "${_lib} ${_prefix}_LIBRARIES: ${${_prefix}_LIBRARIES}")
                endif()

                if(MSVC)
                    if(dlls)
                        # remove repeat items
                        list(REMOVE_DUPLICATES dlls)
                        # set dlls into var ${_prefix}_DLLS
                        set(${_prefix}_DLLS ${dlls} CACHE STRING "dlls to link for ${_prefix}" FORCE)
                        message(STATUS "${_lib} ${_prefix}_DLLS: ${${_prefix}_DLLS}")
                    endif(dlls)
                endif()

                if(${_prefix}_LIBRARIES AND ${_prefix}_INCLUDE_DIRS)
                    set(${_prefix}_FOUND YES)
                    list(APPEND COCOS_EXTERNAL_LIBS ${${_prefix}_LIBRARIES})
                endif()
            endif()
        endif(EXISTS ${_root})
    endforeach()
endforeach()

# use engine prebuilt libs, try to pick all engine libs
if(USE_COCOS_PREBUILT)
    # cocos2d/jscocos2d/luacocos2d
    set(_cocos2d_prefix COCOS2D)
    cocos_find_prebuilt_lib_by_name(cocos2d COCOS2D_LIBRARIES)

    set(_jscocos2d_prefix JSCOCOS2D)
    cocos_find_prebuilt_lib_by_name(jscocos2d JSCOCOS2D_LIBRARIES)

    set(_luacocos2d_prefix LUACOCOS2D)
    cocos_find_prebuilt_lib_by_name(luacocos2d LUACOCOS2D_LIBRARIES)

    set(_simulator_prefix SIMULATOR)
    cocos_find_prebuilt_lib_by_name(simulator SIMULATOR_LIBRARIES)

    if(ANDROID)
        set(_cocos2d_android_prefix ANDROID_COCOS2D)
        cocos_find_prebuilt_lib_by_name(cocos2d_android ANDROID_COCOS2D_LIBRARIES)
    endif()
endif(USE_COCOS_PREBUILT)





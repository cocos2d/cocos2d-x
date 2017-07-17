# CocosUsePrebuiltLibs - sets external libs variables to link with

# START CONFIG

set(_chipmunk_inc chipmunk/chipmunk.h)
set(_chipmunk_inc_paths include)
if(WINDOWS)
    if (${MSVC_VERSION} EQUAL 1900 OR ${MSVC_VERSION} GREATER 1900)
        set(_chipmunk_libs chipmunk libchipmunk-2015)
    else()
        set(_chipmunk_libs chipmunk libchipmunk)
    endif(${MSVC_VERSION})
else()
    set(_chipmunk_libs chipmunk libchipmunk)
endif(WINDOWS)

set(_bullet_inc bullet/Bullet-C-Api.h BulletCollision/btBulletCollisionCommon.h)
set(_bullet_inc_paths  bullet)
# sequence is important
set(_bullet_libs BulletDynamics libBulletDynamics BulletCollision libBulletCollision BulletMultiThreaded libBulletMultiThreaded LinearMath libLinearMath MiniCL libMiniCL)

set(_curl_inc curl/curl.h)
# order: curl, ssl, crypto
set(_curl_libs curl libcurl_imp libcurl ssl libeay32 ssleay32 crypto)

set(_freetype2_prefix FREETYPE)
set(_freetype2_inc ft2build.h freetype/freetype.h)
set(_freetype2_inc_paths freetype2)
set(_freetype2_libs freetype freetype250)

set(_jpeg_inc jpeglib.h)
if(WINDOWS)
    if (${MSVC_VERSION} EQUAL 1900 OR ${MSVC_VERSION} GREATER 1900)
        set(_jpeg_libs jpeg libjpeg-2015)
    else()
        set(_jpeg_libs jpeg libjpeg)
    endif(${MSVC_VERSION})
else()
    set(_jpeg_libs jpeg libjpeg)
endif(WINDOWS)

set(_png_inc png.h)
if(WINDOWS)
    if (${MSVC_VERSION} EQUAL 1900 OR ${MSVC_VERSION} GREATER 1900)
        set(_png_libs png libpng-2015)
    else()
        set(_png_libs png libpng)
    endif(${MSVC_VERSION})
else()
    set(_png_libs png libpng)
endif(WINDOWS)

set(_tiff_inc tiff.h)
if(WINDOWS)
    if (${MSVC_VERSION} EQUAL 1900 OR ${MSVC_VERSION} GREATER 1900)
        set(_tiff_libs tiff libtiff-2015)
    else()
        set(_tiff_libs tiff libtiff)
    endif(${MSVC_VERSION})
else()
    set(_tiff_libs tiff libtiff)
endif(WINDOWS)

set(_webp_inc decode.h)
set(_webp_libs webp libwebp)

set(_websockets_inc libwebsockets.h)
set(_websockets_libs websockets libwebsockets)

set(_openssl_inc openssl/ssl.h)
set(_openssl_libs ssl crypto)

set(_glfw3_inc glfw3.h)
if(WINDOWS)
    if (${MSVC_VERSION} EQUAL 1900 OR ${MSVC_VERSION} GREATER 1900)
        set(_glfw3_libs glfw3-2015 libglfw3)
    else()
        set(_glfw3_libs glfw3 libglfw3)
    endif(${MSVC_VERSION})
else()
    set(_glfw3_libs glfw3 libglfw3)
endif(WINDOWS)

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

set(_fmod_prefix FMOD)
set(_fmod_inc fmod.hpp)
set(_fmod_libs fmod fmod64 fmod fmod64)

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
)


if(MACOSX)
  list(APPEND all_prebuilt_libs glfw3 zlib)
endif()

# We use MSVC instead of WINDOWS because it can be mingw that can't use our prebuilt libs
if(MSVC)
  list(APPEND all_prebuilt_libs glfw3 sqlite3 gles icon MP3Decoder OggDecoder OpenalSoft zlib)
endif()

if(LINUX)
  list(APPEND all_prebuilt_libs fmod)
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
  endif()

  set(roots
    ${COCOS_EXTERNAL_DIR}/${_lib}
    ${COCOS_EXTERNAL_DIR}/${PLATFORM_FOLDER}-specific/${_lib}
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
            find_path(_inc_tmp ${_inc_name} PATH_SUFFIXES ${_suffixes} PATHS ${_dir} NO_DEFAULT_PATH)
            if(_inc_tmp)
              list(APPEND include_dirs ${_inc_tmp})
            endif()
          endforeach()
        endif(EXISTS ${_dir})
      endforeach()
      if(include_dirs)
        set(${_prefix}_INCLUDE_DIRS ${include_dirs} CACHE PATH "Path to includes for ${_prefix}" FORCE)
      endif()
      #message(STATUS "${_lib} ${_prefix}_INCLUDE_DIRS: ${${_prefix}_INCLUDE_DIRS}")

      set(lib_dir_candidates
        ${_root}/prebuilt/${PLATFORM_FOLDER}/${ANDROID_ABI}
        ${_root}/prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
        ${_root}/prebuilt/${PLATFORM_FOLDER}
        ${_root}/prebuilt/${PLATFORM_FOLDER}/release-lib
        ${_root}/prebuilt/${ARCH_DIR}
        ${_root}/libraries/${PLATFORM_FOLDER}
        ${_root}/prebuilt
        )
      set(libs)
      foreach(_dir ${lib_dir_candidates})
        if(EXISTS ${_dir})
          # find all libs
          foreach(_lib_name ${_${_lib}_libs})
            unset(_lib_tmp CACHE)
            find_library(_lib_tmp ${_lib_name} PATHS ${_dir} NO_DEFAULT_PATH)
            if(_lib_tmp)
              list(APPEND libs ${_lib_tmp})
            endif()
          endforeach()
        endif(EXISTS ${_dir})
      endforeach()
      if(libs)
        set(${_prefix}_LIBRARIES ${libs} CACHE STRING "Libraries to link for ${_prefix}" FORCE)
      endif()
      message(STATUS "${_lib} ${_prefix}_LIBRARIES: ${${_prefix}_LIBRARIES}")

      if(${_prefix}_LIBRARIES AND ${_prefix}_INCLUDE_DIRS)
        set(${_prefix}_FOUND YES)
      endif()
      
    endif(EXISTS ${_root})
  endforeach()
endforeach()

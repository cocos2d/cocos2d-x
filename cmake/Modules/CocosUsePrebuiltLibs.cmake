# CocosUsePrebuiltLibs - sets external libs variables to link with

# START CONFIG
set(_box2d_inc Box2D.h)
set(_box2d_inc_paths box2d)
set(_box2d_libs box2d libbox2d)

set(_tinyxml2_inc tinyxml2.h)
set(_tinyxml2_inc_paths tinyxml2)
set(_tinyxml2_libs tinyxml2 libtinyxml2)

set(_minizip_inc unzip.h)
set(_minizip_inc_paths minizip)
set(_minizip_libs minizip libminizip)

set(_edtaa3func_inc edtaa3func.h)
set(_edtaa3func_inc_paths edtaa3func)
set(_edtaa3func_libs edtaa3func libedtaa3func)

set(_convertutf_inc ConvertUTF.h)
set(_convertutf_inc_paths convertutf)
set(_convertutf_libs convertutf libconvertutf)

set(_xxhash_inc xxhash.h)
set(_xxhash_inc_paths xxhash)
set(_xxhash_libs xxhash libxxhash)

set(_xxtea_inc xxtea.h)
set(_xxtea_inc_paths xxtea)
set(_xxtea_libs xxtea libxxtea)

set(_flatbuffers_inc flatbuffers.h)
set(_flatbuffers_inc_paths flatbuffers)
set(_flatbuffers_libs flatbuffer libflatbuffer)

set(_chipmunk_inc chipmunk.h)
set(_chipmunk_inc_paths chipmunk)
set(_chipmunk_libs chipmunk libchipmunk)

set(_zlib_inc zlib.h)
set(_zlib_inc_paths zlib)
set(_zlib_libs z libz)

set(_curl_inc curl/curl.h)
set(_curl_inc_paths curl)
set(_curl_libs crypto ssl libeay32 ssleay32 curl libcurl_imp libcurl)

set(_freetype2_prefix FREETYPE)
set(_freetype2_inc ft2build.h freetype.h)
set(_freetype2_inc_paths freetype)
set(_freetype2_libs freetype freetype250)

set(_jpeg_inc jpeglib.h)
set(_jpeg_inc_paths jpeg)
set(_jpeg_libs jpeg libjpeg)

set(_png_inc png.h)
set(_png_inc_paths png)
set(_png_libs png libpng)

set(_tiff_inc tiff.h)
set(_tiff_inc_paths tiff)
set(_tiff_libs tiff libtiff)

set(_webp_inc decode.h)
set(_webp_inc_paths webp)
set(_webp_libs webp libwebp)

set(_websockets_inc libwebsockets.h)
set(_websockets_inc_paths websockets)
set(_websockets_libs websockets libwebsockets)

set(_glfw3_inc glfw3.h)
set(_glfw3_inc_paths glfw)
set(_glfw3_libs glfw libglfw)

set(_sqlite3_inc sqlite3.h)
set(_sqlite3_inc_paths sqlite3)
set(_sqlite3_libs sqlite3)

set(_gles_prefix GLEW)
set(_gles_inc GL/glew.h)
set(_gles_libs glew32)

set(_icon_prefix ICONV)
set(_icon_inc iconv.h)
set(_icon_inc_paths iconv)
set(_icon_libs libiconv)

set(_MP3Decoder_prefix MPG123)
set(_MP3Decoder_inc mpg123.h)
set(_MP3Decoder_inc_paths Mp3Decoder)
set(_MP3Decoder_libs libmpg123)

set(_OggDecoder_prefix VORBIS)
set(_OggDecoder_inc ogg/ogg.h)
set(_OggDecoder_libs libogg libvorbis libvorbisfile)

set(_OpenalSoft_prefix OPENAL)
set(_OpenalSoft_inc al.h)
set(_OpenalSoft_inc_paths AL)
set(_OpenalSoft_libs OpenAL32)

set(_fmod_prefix FMODEX)
set(_fmod_inc fmod.h)
set(_fmod_inc_paths fmod)
set(_fmod_libs fmodex fmodex64 fmodexL fmodexL64)

#for lua
set(_cjson_inc lua_cjson.h)
set(_cjson_inc_paths cjson)
set(_cjson_libs cjson libcjson)

set(_luajit_inc lua.h)
set(_luajit_inc_paths luajit)
set(_luajit_libs luajit libluajit)

set(_luasocket_inc luasocket.h)
set(_luasocket_inc_paths luasocket)
set(_luasocket_libs luasocket libluasocket)

set(all_prebuilt_libs
  chipmunk
  curl
  freetype2
  jpeg
  png
  tiff
  webp
  websockets
  box2d
  tinyxml2
  minizip
  xxhash
  xxtea
  flatbuffers
  convertutf
  edtaa3func
  cjson
  luasocket
  luajit
  zlib
)


if(MACOSX)
  list(APPEND all_prebuilt_libs glfw3)
endif()

# We use MSVC instead of WINDOWS because it can be mingw that can't use our prebuilt libs
if(MSVC)
  list(APPEND all_prebuilt_libs glfw3 sqlite3 gles icon MP3Decoder OggDecoder OpenalSoft zlib)
endif()

if(LINUX)
  list(APPEND all_prebuilt_libs fmod glfw3)
endif()

# END CONFIG

foreach(_lib ${all_prebuilt_libs})
  if(_${_lib}_prefix)
    set(_prefix ${_${_lib}_prefix})
  else()
    # auto-prefix is uppercased name
    string(TOUPPER ${_lib} _prefix)
  endif()

  set(roots ${COCOS_EXTERNAL_DIR}/${PLATFORM_FOLDER})
  set(include_dir_candidates
    ${roots}/include  #for ios & mac only
    ${roots}/${ARCH_DIR}/include)

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
    # message(STATUS "${_lib} include path found")
  endif()
  # message(STATUS "${_lib} ${_prefix}_INCLUDE_DIRS: ${${_prefix}_INCLUDE_DIRS}")

  set(lib_dir_candidates
    ${roots}/${ARCH_DIR}/libs
    ${roots}/${ARCH_DIR}/libs/Debug
    ${roots}/${ARCH_DIR}/libs/Release
    ${roots}/libs #for ios&mac only
    )
  set(libs)
  foreach(_dir ${lib_dir_candidates})
    if(EXISTS ${_dir})
      # find all libs
      foreach(_lib_name ${_${_lib}_libs})
        unset(_lib_tmp CACHE)
        # message(STATUS "Found ${_lib_name} ${_dir}")
        find_library(_lib_tmp ${_lib_name} PATH ${_dir} NO_DEFAULT_PATH)
        if(_lib_tmp)
          list(APPEND libs ${_lib_tmp})
        endif()
      endforeach()
    endif(EXISTS ${_dir})
  endforeach()
  if(libs)
    set(${_prefix}_LIBRARIES ${libs} CACHE STRING "Libraries to link for ${_prefix}" FORCE)
    # message(STATUS "${_lib} library path found")
  endif()
  # message(STATUS "${_lib} ${_prefix}_LIBRARIES: ${${_prefix}_LIBRARIES}")

  if(${_prefix}_LIBRARIES AND ${_prefix}_INCLUDE_DIRS)
    # message(STATUS "${_prefix} found")
    set(${_prefix}_FOUND YES)
  endif()
      
endforeach()

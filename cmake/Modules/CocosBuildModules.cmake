 # header files third libiary needed, such as tinyxml2.h
 include_directories(
         ${COCOS2DX_ROOT_PATH}
         ${COCOS2DX_ROOT_PATH}/cocos
         ${COCOS2DX_ROOT_PATH}/deprecated
         ${COCOS2DX_ROOT_PATH}/cocos/platform
         ${COCOS2DX_ROOT_PATH}/extensions
         ${COCOS2DX_ROOT_PATH}/external
 )

 # desktop platforms
 if(LINUX OR MACOSX OR WINDOWS)
     cocos_find_package(OpenGL OPENGL REQUIRED)
     cocos_find_package(SQLite3 SQLITE3 REQUIRED)

     if(LINUX OR WINDOWS)
         cocos_find_package(GLEW GLEW REQUIRED)
         include_directories(${GLEW_INCLUDE_DIRS})
     endif()

     cocos_find_package(GLFW3 GLFW3 REQUIRED)
     include_directories(${GLFW3_INCLUDE_DIRS})

     if(LINUX)
         set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
         find_package(Threads REQUIRED)
         set(THREADS_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

         cocos_find_package(FMOD FMOD REQUIRED)
         cocos_find_package(Fontconfig FONTCONFIG REQUIRED)
         cocos_find_package(GTK3 GTK3 REQUIRED)
     endif()

     if(WINDOWS)
         cocos_find_package(Vorbis VORBIS REQUIRED)
         cocos_find_package(MPG123 MPG123 REQUIRED)
         cocos_find_package(OpenAL OPENAL REQUIRED)
         # because FindOpenAL.cmake set include dir for '#include <al.h>' for portability (not for '#include <AL/al.h>'
         set(OPENAL_DEFINITIONS "-DOPENAL_PLAIN_INCLUDES")
     endif()
 endif(LINUX OR MACOSX OR WINDOWS)

 # Freetype required on all platforms
 cocos_find_package(Freetype FREETYPE REQUIRED)

 # Recast (not prebuilded, exists as source)
 if(USE_RECAST)
     if(USE_EXTERNAL_PREBUILT)
         set(_recast_prefix RECAST)
         set(RECAST_INCLUDE_DIRS ${COCOS2DX_ROOT_PATH}/external/recast)
         if(USE_COCOS_PREBUILT)
             cocos_find_prebuilt_lib_by_name(recast RECAST_LIBRARIES)
         else()
             add_subdirectory(${COCOS2DX_ROOT_PATH}/external/recast ${ENGINE_BINARY_PATH}/external/recast)
             set(RECAST_LIBRARIES recast)
         endif()
     else()
         cocos_find_package(recast RECAST REQUIRED)
         set(RECAST_LIBRARIES recast)
     endif()
     message(STATUS "Recast include dirs: ${RECAST_INCLUDE_DIRS}")
     add_definitions(-DCC_USE_NAVMESH=1)
 else(USE_RECAST)
     add_definitions(-DCC_USE_NAVMESH=0)
 endif(USE_RECAST)

 # Tinyxml2 (not prebuilded, exists as source)
 if(USE_EXTERNAL_PREBUILT)
     set(_tinyxml2_prefix TinyXML2)
     set(TinyXML2_INCLUDE_DIRS ${COCOS2DX_ROOT_PATH}/external/tinyxml2)
     if(USE_COCOS_PREBUILT)
         cocos_find_prebuilt_lib_by_name(tinyxml2 TinyXML2_LIBRARIES)
     else()
         add_subdirectory(${COCOS2DX_ROOT_PATH}/external/tinyxml2 ${ENGINE_BINARY_PATH}/external/tinyxml2)
         set(TinyXML2_LIBRARIES tinyxml2)
     endif()
 else()
     cocos_find_package(TinyXML2 TinyXML2 REQUIRED)
 endif()
 message(STATUS "TinyXML2 include dirs: ${TinyXML2_INCLUDE_DIRS}")

 if(NOT IOS)
     cocos_find_package(ZLIB ZLIB REQUIRED)
 endif()
 if(IOS)
     cocos_find_package(SQLite3 SQLITE3 REQUIRED)
 endif(IOS)

 if(ANDROID)
     set(_pvmp3dec_prefix PVMP3DEC)
     set(PVMP3DEC_INCLUDE_DIRS ${COCOS2DX_ROOT_PATH}/external/android-specific/pvmp3dec/include ${COCOS2DX_ROOT_PATH}/external/android-specific/pvmp3dec/src)
     if(USE_COCOS_PREBUILT)
         cocos_find_prebuilt_lib_by_name(pvmp3dec PVMP3DEC_LIBRARIES)
     else()
         add_subdirectory(${COCOS2DX_ROOT_PATH}/external/android-specific/pvmp3dec ${ENGINE_BINARY_PATH}/external/android-specific/pvmp3dec)
         set(PVMP3DEC_LIBRARIES pvmp3dec)
     endif()
     message(STATUS "pvmp3dec include dirs: ${PVMP3DEC_INCLUDE_DIRS}")

     set(_tremolo_prefix TREMOLO)
     set(TREMOLO_INCLUDE_DIRS ${COCOS2DX_ROOT_PATH}/external/android-specific/tremolo)
     if(USE_COCOS_PREBUILT)
         cocos_find_prebuilt_lib_by_name(tremolo TREMOLO_LIBRARIES)
     else()
         add_subdirectory(${COCOS2DX_ROOT_PATH}/external/android-specific/tremolo ${ENGINE_BINARY_PATH}/external/android-specific/tremolo)
         set(TREMOLO_LIBRARIES tremolo)
     endif()
     message(STATUS "Tremolo include dirs: ${TREMOLO_INCLUDE_DIRS}")

     set(_cpufeatures_prefix CPUFEATURES)
     if(USE_COCOS_PREBUILT)
         cocos_find_prebuilt_lib_by_name(cpufeatures CPUFEATURES_LIBRARIES)
     else()
         include(AndroidNdkModules)
         android_ndk_import_module_cpufeatures()
         set(CPUFEATURES_LIBRARIES cpufeatures)
     endif()
 endif()

 # minizip (we try to migrate to minizip from https://github.com/nmoinvaz/minizip)
 # only msys2 currently provides package for this variant, all other
 # dists have packages from zlib, thats very old for us.
 # moreover our embedded version modified to quick provide
 # functionality needed by cocos.
 if(USE_EXTERNAL_PREBUILT)
     set(_unzip_prefix MINIZIP)
     include_directories(${ZLIB_INCLUDE_DIRS})
     set(MINIZIP_INCLUDE_DIRS ${COCOS2DX_ROOT_PATH}/external/unzip ${ZLIB_INCLUDE_DIRS})
     if(USE_COCOS_PREBUILT)
         cocos_find_prebuilt_lib_by_name(unzip MINIZIP_LIBRARIES)
     else()
         add_subdirectory(${COCOS2DX_ROOT_PATH}/external/unzip ${ENGINE_BINARY_PATH}/external/unzip)
         # set(MINIZIP_LIBRARIES unzip ${ZLIB_LIBRARIES})
         set(MINIZIP_LIBRARIES unzip)
     endif()
     message(STATUS "MINIZIP include dirs: ${MINIZIP_INCLUDE_DIRS}")
 else()
     cocos_find_package(MINIZIP MINIZIP REQUIRED)
     # double check that we have needed functions
     include(CheckLibraryExists)
     add_definitions(-DMINIZIP_FROM_SYSTEM)
 endif()

 # Jpeg
 if(USE_JPEG)
     cocos_find_package(JPEG JPEG REQUIRED)
     add_definitions(-DCC_USE_JPEG=1)
 else(USE_JPEG)
     add_definitions(-DCC_USE_JPEG=0)
 endif(USE_JPEG)

 # Tiff
 if(USE_TIFF)
     cocos_find_package(TIFF TIFF REQUIRED)
     add_definitions(-DCC_USE_TIFF=1)
 else(USE_TIFF)
     add_definitions(-DCC_USE_TIFF=0)
 endif(USE_TIFF)

 # Png
 if(USE_PNG)
     cocos_find_package(PNG PNG REQUIRED)
     add_definitions(-DCC_USE_PNG=1)
 else(USE_PNG)
     add_definitions(-DCC_USE_PNG=0)
 endif(USE_PNG)

 cocos_find_package(WEBSOCKETS WEBSOCKETS REQUIRED)
 cocos_find_package(CURL CURL REQUIRED)
 if(NOT USE_EXTERNAL_PREBUILT)
     cocos_find_package(OpenSSL OPENSSL REQUIRED)
 endif()

 # flatbuffers
 if(USE_EXTERNAL_PREBUILT)
     set(_flatbuffers_prefix FLATBUFFERS)
     set(FLATBUFFERS_INCLUDE_DIRS ${COCOS2DX_ROOT_PATH}/external)
     if(USE_COCOS_PREBUILT)
         cocos_find_prebuilt_lib_by_name(flatbuffers FLATBUFFERS_LIBRARIES)
     else()
         add_subdirectory(${COCOS2DX_ROOT_PATH}/external/flatbuffers ${ENGINE_BINARY_PATH}/external/flatbuffers)
         set(FLATBUFFERS_LIBRARIES flatbuffers)
     endif()
     message(STATUS "Flatbuffers include dirs: ${FLATBUFFERS_INCLUDE_DIRS}")
 else()
     cocos_find_package(flatbuffers FLATBUFFERS REQUIRED)
 endif()

 # xxhash
 if(USE_EXTERNAL_PREBUILT)
     set(_xxhash_prefix XXHASH)
     set(XXHASH_INCLUDE_DIRS ${COCOS2DX_ROOT_PATH}/external/xxhash)
     if(USE_COCOS_PREBUILT)
         cocos_find_prebuilt_lib_by_name(xxhash XXHASH_LIBRARIES)
     else()
         add_subdirectory(${COCOS2DX_ROOT_PATH}/external/xxhash ${ENGINE_BINARY_PATH}/external/xxhash)
         set(XXHASH_LIBRARIES xxhash)
     endif()
     message(STATUS "xxhash include dirs: ${XXHASH_INCLUDE_DIRS}")
 else()
     cocos_find_package(xxhash xxhash REQUIRED)
 endif()

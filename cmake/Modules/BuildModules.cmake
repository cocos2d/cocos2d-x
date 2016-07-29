macro (BuildModules)
	# desktop platforms
	if(LINUX OR MACOSX OR WINDOWS)
	  cocos_find_package(OpenGL OPENGL REQUIRED)

	  if(LINUX OR WINDOWS)
	    cocos_find_package(GLEW GLEW REQUIRED)
	    #TODO: implement correct schema for pass cocos2d specific requirements to projects
	    include_directories(${GLEW_INCLUDE_DIRS})
	  endif()

	  cocos_find_package(GLFW3 GLFW3 REQUIRED)
	  include_directories(${GLFW3_INCLUDE_DIRS})

	  if(LINUX)
	    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
	    find_package(Threads REQUIRED)
	    set(THREADS_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

	    cocos_find_package(SQLite3 SQLITE3 REQUIRED)
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

	# WebP required if used
	if(USE_WEBP)
	  cocos_find_package(WebP WEBP REQUIRED)
	endif(USE_WEBP)

	# Chipmunk
	if(USE_CHIPMUNK)
	  if(USE_PREBUILT_LIBS)
	    cocos_find_package(Chipmunk CHIPMUNK REQUIRED)
	  endif()
	endif(USE_CHIPMUNK)

	# Box2d (not prebuilded, exists as source)
	if(USE_BOX2D)
	  if(USE_PREBUILT_LIBS OR USE_SOURCES_EXTERNAL)
	    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/Box2D)
	    set(Box2D_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/box2d/include)
	    set(Box2D_LIBRARIES box2d)
	  else()
	    find_package(Box2D REQUIRED CONFIG)
	    # actually Box2D in next line is not a library, it is target exported from Box2DConfig.cmake
	    set(Box2D_LIBRARIES Box2D)
	  endif()
	  message(STATUS "Box2D include dirs: ${Box2D_INCLUDE_DIRS}")
	elseif(BUILD_BOX2D)
	  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/Box2D)
	endif(USE_BOX2D)

	# Bullet (not prebuilded, exists as source)
	if(USE_BULLET)
	  if(USE_PREBUILT_LIBS OR USE_SOURCES_EXTERNAL)
	    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/bullet)
	    set(BULLET_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/bullet)
	    set(BULLET_LIBRARIES bullet)
	  else()
	    cocos_find_package(bullet BULLET REQUIRED)
	    set(BULLET_LIBRARIES bullet)
	  endif()
	  message(STATUS "Bullet include dirs: ${BULLET_INCLUDE_DIRS}")
	endif(USE_BULLET)

	# Recast (not prebuilded, exists as source)
	if(USE_RECAST)
	  if(USE_PREBUILT_LIBS OR USE_SOURCES_EXTERNAL)
	    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/recast)
	    set(RECAST_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/recast)
	    set(RECAST_LIBRARIES recast)
	  else()
	    cocos_find_package(recast RECAST REQUIRED)
	    set(RECAST_LIBRARIES recast)
	  endif()
	  message(STATUS "Recast include dirs: ${RECAST_INCLUDE_DIRS}")
	endif(USE_RECAST)

	# Tinyxml2 (not prebuilded, exists as source)
	if(USE_PREBUILT_LIBS OR USE_SOURCES_EXTERNAL)
	  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/tinyxml2)
	  set(TinyXML2_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/tinyxml2)
	  set(TinyXML2_LIBRARIES tinyxml2)
	else()
	  cocos_find_package(TinyXML2 TinyXML2 REQUIRED)
	endif()
	message(STATUS "TinyXML2 include dirs: ${TinyXML2_INCLUDE_DIRS}")

	# libjpeg
	cocos_find_package(JPEG JPEG REQUIRED)
	cocos_find_package(ZLIB ZLIB REQUIRED)

	# minizip (we try to migrate to minizip from https://github.com/nmoinvaz/minizip)
	# only msys2 currently provides package for this variant, all other
	# dists have packages from zlib, thats very old for us.
	# moreover our embedded version modified to quick provide
	# functionality needed by cocos.
	if(USE_PREBUILT_LIBS OR NOT MINGW)
	  #TODO: hack! should be in external/unzip/CMakeLists.txt
	  include_directories(${ZLIB_INCLUDE_DIRS})
	  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/unzip)
	  set(MINIZIP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/unzip ${ZLIB_INCLUDE_DIRS})
	  set(MINIZIP_LIBRARIES unzip ${ZLIB_LIBRARIES})
	  message(STATUS "MINIZIP include dirs: ${MINIZIP_INCLUDE_DIRS}")
	else()
	  cocos_find_package(MINIZIP MINIZIP REQUIRED)
	  # double check that we have needed functions
	  include(CheckLibraryExists)
	  check_library_exists(${MINIZIP_LIBRARIES} "unzGoToFirstFile2" "" MINIZIP_HAS_GOTOFIRSTFILE2)
	  if(NOT MINIZIP_HAS_GOTOFIRSTFILE2)
	    message(FATAL_ERROR "Minizip library on you system very old. Please use recent version from https://github.com/nmoinvaz/minizip or enable USE_PREBUILT_LIBS")
	    return()
	  endif()
	endif()

	cocos_find_package(PNG PNG REQUIRED)
	cocos_find_package(TIFF TIFF REQUIRED)
	cocos_find_package(WEBSOCKETS WEBSOCKETS REQUIRED)
	cocos_find_package(CURL CURL REQUIRED)

	# flatbuffers
	if(USE_PREBUILT_LIBS OR USE_SOURCES_EXTERNAL)
	  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/flatbuffers)
	  set(FLATBUFFERS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external)
	  message(STATUS "Flatbuffers include dirs: ${FLATBUFFERS_INCLUDE_DIRS}")
	else()
	  cocos_find_package(flatbuffers flatbuffers REQUIRED)
	endif()

	# xxhash
	if(USE_PREBUILT_LIBS OR USE_SOURCES_EXTERNAL)
	  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/xxhash)
	  set(XXHASH_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/xxhash)
	  set(XXHASH_LIBRARIES xxhash)
	else()
	  cocos_find_package(xxhash xxhash REQUIRED)
	endif()

	# libcocos2d.a
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cocos)
endmacro(BuildModules)

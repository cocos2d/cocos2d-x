macro (SetCompilerOptions)

	#cmake has some strange defaults, this should help us a lot
	#Please use them everywhere
	#WINDOWS 	= 	Windows Desktop
	#WINRT 		= 	Windows RT
	#WP8 	  	= 	Windows Phone 8
	#ANDROID    =	Android
	#IOS		=	iOS
	#MACOSX		=	MacOS X
	#LINUX      =   Linux
	if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
		if(WINRT)
			set(SYSTEM_STRING "Windows RT")
		elseif(WP8)
			set(SYSTEM_STRING "Windows Phone 8")
		else()
			set(WINDOWS TRUE)
			set(SYSTEM_STRING "Windows Desktop")
		endif()
	elseif (${CMAKE_SYSTEM_NAME} MATCHES "Android")
		set(SYSTEM_STRING "Android")
	elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		if(ANDROID)
			set(SYSTEM_STRING "Android")
		else()
			set(LINUX TRUE)
			set(SYSTEM_STRING "Linux")
		endif()
	elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		if(IOS)
			set(APPLE TRUE)
			set(SYSTEM_STRING "IOS")
		else()
			set(APPLE TRUE)
			set(MACOSX TRUE)
			set(SYSTEM_STRING "Mac OSX")
		endif()
	endif()

	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(COMPILER_STRING ${CMAKE_CXX_COMPILER_ID})
		set(CLANG TRUE)
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		if(MINGW)
			set(COMPILER_STRING "Mingw GCC")
		else()
			set(COMPILER_STRING "GCC")
		endif()
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
		set(COMPILER_STRING "${CMAKE_CXX_COMPILER_ID} C++")
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
		set(COMPILER_STRING "Visual Studio C++")
	endif()

	if(CMAKE_CROSSCOMPILING)
		set(BUILDING_STRING "It appears you are cross compiling for ${SYSTEM_STRING} with ${COMPILER_STRING}")
	else()
		set(BUILDING_STRING "It appears you are building natively for ${SYSTEM_STRING} with ${COMPILER_STRING}")
	endif()

	message(STATUS ${BUILDING_STRING})

	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCOCOS2D_DEBUG=1")
	set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

    # definitions for chipmunk
	if (USE_CHIPMUNK)
		add_definitions(-DCC_ENABLE_CHIPMUNK_INTEGRATION=1)
		if (IOS OR MACOSX)
			# without this chipmunk will try to use apple defined geometry types, that conflicts with cocos
            add_definitions(-DCP_USE_CGPOINTS=0)
		endif()
	else()
		add_definitions(-DCC_USE_PHYSICS=0)
	endif()

    # definitions for box2d
	if (USE_BOX2D)
		add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=1)
	else()
		add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=0)
	endif()

    # definitions for bullet
	if (USE_BULLET)
		add_definitions(-DCC_ENABLE_BULLET_INTEGRATION=1)
        add_definitions(-DCC_USE_3D_PHYSICS=1)
	else()
		add_definitions(-DCC_ENABLE_BULLET_INTEGRATION=0)
        add_definitions(-DCC_USE_3D_PHYSICS=0)
	endif()

    # definitions for recast
	if (USE_RECAST)
		add_definitions(-DCC_USE_NAVMESH=1)
	else()
		add_definitions(-DCC_USE_NAVMESH=0)
	endif()

	# Compiler options
	if(MSVC)
		if(CMAKE_BUILD_TYPE STREQUAL "Debug")
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt /NODEFAULTLIB:libcmt")
		else()
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt")
		endif()
	  add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
	                  -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
	                  -wd4514 -wd4056 -wd4996 -wd4099)

	  # Use inline debug info (/Z7) format. Or internal error may occur.
	  # Errors looks like: "xmemory0(592): error C3130: Internal Compiler Error: failed to write injected code block to PDB"
	  foreach(lang C CXX)
	    string(REGEX REPLACE "/Z[iI7]" "" CMAKE_${lang}_FLAGS_DEBUG "${CMAKE_${lang}_FLAGS_DEBUG}")
	    set(CMAKE_${lang}_FLAGS_DEBUG "${CMAKE_${lang}_FLAGS_DEBUG} /Z7")
	  endforeach()

	else()
		if(CMAKE_BUILD_TYPE STREQUAL "Debug")
			ADD_DEFINITIONS(-DCOCOS2D_DEBUG=1)
		endif()
	  set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
	  set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
	  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -fPIC")
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder -Wno-invalid-offsetof -fPIC")
	  if(CLANG AND NOT ANDROID)
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
		endif()
		if(CLANG AND ANDROID AND ANDROID_ARM_MODE STREQUAL thumb AND ANDROID_ABI STREQUAL armeabi)
			string(REPLACE "-mthumb" "-marm" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
			string(REPLACE "-mthumb" "-marm" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  	endif()
	endif(MSVC)

	# Some macro definitions
	if(WINDOWS)

	  if(BUILD_SHARED_LIBS)
	    add_definitions(-D_USRDLL -D_EXPORT_DLL_ -D_USEGUIDLL -D_USREXDLL -D_USRSTUDIODLL)
	  else()
	    add_definitions(-DCC_STATIC)
	  endif()

	  add_definitions(-DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32 -D_WIN32)
	  set(PLATFORM_FOLDER win32)
	elseif(APPLE)
		add_definitions(-DUSE_FILE32API)
		if(MACOSX)
			add_definitions(-DTARGET_OS_MAC)
			set(PLATFORM_FOLDER mac)
		elseif(IOS)
			# TARGET_OS_IOS
			# add_definitions(-DTARGET_OS_IPHONE)
			add_definitions(-DTARGET_OS_IOS)
			set(PLATFORM_FOLDER ios)
		endif(MACOSX)

	elseif(LINUX)
	  add_definitions(-DLINUX)
	  set(PLATFORM_FOLDER linux)
	elseif(ANDROID)
	  add_definitions(-DUSE_FILE32API)
	  set(PLATFORM_FOLDER android)
	  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions")
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char -fexceptions")
	  set(CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY} -latomic")
	  
	  if(CLANG AND ANDROID_ARM_MODE STREQUAL thumb AND ANDROID_ABI STREQUAL armeabi)
            string(REPLACE "-mthumb" "-marm" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
            string(REPLACE "-mthumb" "-marm" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	  endif()

	else()
	  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
	  return()
	endif()

	if(MINGW)
	  add_definitions(-DGLEW_STATIC)
	  add_definitions(-DCURL_STATICLIB)
	  add_definitions(-DAL_LIBTYPE_STATIC)
	  add_definitions(-D__SSIZE_T)

	  if(CLANG)
	    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
	  endif()
	endif()

endmacro (SetCompilerOptions)

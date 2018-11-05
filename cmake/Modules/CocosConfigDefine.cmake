 #Please use them everywhere
 #WINDOWS   =   Windows Desktop
 #ANDROID    =  Android
 #IOS    =  iOS
 #MACOSX    =  MacOS X
 #LINUX      =   Linux
 if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
     set(WINDOWS TRUE)
     set(SYSTEM_STRING "Windows Desktop")
     set(PLATFORM_FOLDER win32)
 elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
     set(SYSTEM_STRING "Android")
     set(PLATFORM_FOLDER android)
 elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
     if(ANDROID)
         set(SYSTEM_STRING "Android")
         set(PLATFORM_FOLDER android)
     else()
         set(LINUX TRUE)
         set(SYSTEM_STRING "Linux")
         set(PLATFORM_FOLDER linux)
     endif()
 elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
     if(IOS)
         set(APPLE TRUE)
         set(SYSTEM_STRING "IOS")
         set(PLATFORM_FOLDER ios)
     else()
         set(APPLE TRUE)
         set(MACOSX TRUE)
         set(SYSTEM_STRING "Mac OSX")
         set(PLATFORM_FOLDER mac)
     endif()
else()
     message(FATAL_ERROR "Unsupported platform, CMake will exit")
     return()
 endif()

 # build mode, Debug is default value
 if(NOT CMAKE_BUILD_TYPE)
     if(DEBUG_MODE)
         set(CMAKE_BUILD_TYPE Debug)
     else()
         set(CMAKE_BUILD_TYPE Release)
     endif()
 endif()

 if(CMAKE_GENERATOR)
    # generators that are capable of organizing into a hierarchy of folders
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    # simplify generator condition judgement
    if(CMAKE_GENERATOR STREQUAL Xcode)
        set(XCODE TRUE)
    elseif(CMAKE_GENERATOR MATCHES Visual)
        set(VS TRUE)
        # make configurations type keep same to cmake build type.
        set(CMAKE_CONFIGURATION_TYPES "${CMAKE_BUILD_TYPE}" CACHE STRING "Reset the configurations to what we need" FORCE)
    endif()
 endif()
 message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")


# custom target property for dll collect
define_property(TARGET
    PROPERTY CC_DEPEND_DLLS
    BRIEF_DOCS "depend dlls of a target"
    FULL_DOCS "use to save depend dlls of a target"
)
# custom target property for lua/js link
define_property(TARGET
    PROPERTY CC_JS_DEPEND
    BRIEF_DOCS "cocos2d js depend libs"
    FULL_DOCS "use to save depend libs of cocos2d js project"
) 
define_property(TARGET
    PROPERTY CC_LUA_DEPEND
    BRIEF_DOCS "cocos2d lua depend libs"
    FULL_DOCS "use to save depend libs of cocos2d lua project"
) 

 # check and print compiler infos
 if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
     set(COMPILER_STRING ${CMAKE_CXX_COMPILER_ID})
     set(CLANG TRUE)
 elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
     if(MINGW)
         set(COMPILER_STRING "Mingw GCC")
     else()
         set(COMPILER_STRING "GCC")
     endif()
 elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
     set(COMPILER_STRING "${CMAKE_CXX_COMPILER_ID} C++")
 elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
     set(COMPILER_STRING "Visual Studio C++")
 else()
     set(COMPILER_STRING "${CMAKE_CXX_COMPILER_ID}")
 endif()
 if(CMAKE_CROSSCOMPILING)
     set(BUILDING_STRING "It appears you are cross compiling for ${SYSTEM_STRING} with ${COMPILER_STRING}")
 else()
     set(BUILDING_STRING "It appears you are building natively for ${SYSTEM_STRING} with ${COMPILER_STRING}")
 endif()
 message(STATUS ${BUILDING_STRING})

# check visual studio version
 if(WINDOWS)
    # not support other compile tools except MSVC for now
    if(MSVC)
        # Visual Studio 2015, MSVC_VERSION 1900      (v140 toolset)
        # Visual Studio 2017, MSVC_VERSION 1910-1919 (v141 toolset)
        if(${MSVC_VERSION} EQUAL 1900 OR ${MSVC_VERSION} GREATER 1900)
            message(STATUS "using Windows MSVC generate cocos2d-x project, MSVC_VERSION:${MSVC_VERSION}")
        else()
            message(FATAL_ERROR "using Windows MSVC generate cocos2d-x project, MSVC_VERSION:${MSVC_VERSION} lower than needed")
        endif()
    else()
        message(FATAL_ERROR "please using Windows MSVC compile cocos2d-x project, support other compile tools not yet")
    endif()
endif()

 # Set macro definitions for special platforms
 function(target_use_cocos2dx_define target)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${target} PUBLIC COCOS2D_DEBUG=1)
    endif()
    if(APPLE)
        target_compile_definitions(${target} PUBLIC __APPLE__)
        target_compile_definitions(${target} PUBLIC USE_FILE32API)
    elseif(LINUX)
        target_compile_definitions(${target} PUBLIC LINUX)
    elseif(ANDROID)
        target_compile_definitions(${target} PUBLIC ANDROID)
        target_compile_definitions(${target} PUBLIC USE_FILE32API)
    elseif(WINDOWS)
        target_compile_definitions(${target} 
            PUBLIC WIN32
            PUBLIC _WIN32
            PUBLIC _WINDOWS
            PUBLIC UNICODE
            PUBLIC _UNICODE
            PUBLIC _CRT_SECURE_NO_WARNINGS
            PUBLIC _SCL_SECURE_NO_WARNINGS
        )
        if(BUILD_SHARED_LIBS)
            target_compile_definitions(${target} 
                PUBLIC _USRDLL
                PUBLIC _EXPORT_DLL_
                PUBLIC _USEGUIDLL
                PUBLIC _USREXDLL
                PUBLIC _USRSTUDIODLL
            )
        else()
            target_compile_definitions(${target} PUBLIC CC_STATIC)
        endif()
    endif()
endfunction()

 # Set compiler options
 if(MSVC)
     set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
     set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
     set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /NODEFAULTLIB:msvcrt /NODEFAULTLIB:libcmt")
     set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:libcmt")

     # multi thread compile option
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
 else()
     set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall")
     set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_C_FLAGS_DEBUG}")
     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -fPIC")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder -Wno-invalid-offsetof -fPIC")
     if(CLANG AND NOT ANDROID)
         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
     endif()
     if(LINUX)
         add_definitions(-D_GNU_SOURCE)
         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lrt")
         set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -lrt")
     endif()
     # specail options for android
     if(ANDROID)
         set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions")
         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char -fexceptions")
         set(CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY} -latomic")
         if(CLANG AND ANDROID_ARM_MODE STREQUAL thumb AND ANDROID_ABI STREQUAL armeabi)
             string(REPLACE "-mthumb" "-marm" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
             string(REPLACE "-mthumb" "-marm" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
         endif()
     endif()
 endif(MSVC)

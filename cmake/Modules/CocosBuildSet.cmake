# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
        FATAL: In-source builds are not allowed.
            You should create a separate directory for build files.
        ")
endif()

if(DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
endif()

macro(CocosBuildSet)

    # It ensures that when Find*.cmake files included from cmake's Modules dir
    # include another *.cmake file with relative path, that file will be included
    # also from cmake's Modules dir, to not clash with per-project files.
    cmake_policy(SET CMP0017 NEW)

    # Use new behaviour with cmake >= 3.1:
    # Only interpret if() arguments as variables or keywords when unquoted.
    cmake_policy(SET CMP0054 NEW)
    
    # Use new behaviour with cmake >= 3.1:
    # Only interpret if() arguments as variables or keywords when unquoted.
    if(CMAKE_VERSION VERSION_GREATER 3.1)
        cmake_policy(SET CMP0054 NEW)
    endif()

    # some useful variables for every one cocos project
    set(COCOS_EXTERNAL_DIR ${COCOS2DX_ROOT_PATH}/external)
    set(ENGINE_BINARY_PATH ${PROJECT_BINARY_DIR}/engine)

    message(STATUS "COCOS2DX_ROOT_PATH:" ${COCOS2DX_ROOT_PATH})
    message(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})
    message(STATUS "COCOS_EXTERNAL_DIR:" ${COCOS_EXTERNAL_DIR})
    message(STATUS "ENGINE_BINARY_PATH:" ${ENGINE_BINARY_PATH})
    
    # architecture
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCH_DIR "64-bit")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(ARCH_DIR "32-bit")
    else()
        message(WARN "CMAKE_SIZEOF_VOID_P: ${CMAKE_SIZEOF_VOID_P}")
    endif()
    # CMAKE_BUILD_TYPE has precedence over DEBUG_MODE
    # Still supporting DEBUG_MODE for backwards compatibility
    if(NOT CMAKE_BUILD_TYPE)
        if(DEBUG_MODE)
            set(CMAKE_BUILD_TYPE Debug)
        else(DEBUG_MODE)
            set(CMAKE_BUILD_TYPE Release)
        endif(DEBUG_MODE)
    endif(NOT CMAKE_BUILD_TYPE)

    # Define other useful variables not defined by CMake
    if(CMAKE_GENERATOR STREQUAL Xcode)
        set (XCODE TRUE)
    elseif(CMAKE_GENERATOR MATCHES Visual)
        set (VS TRUE)
    endif()

    # make configurations type keep same to cmake build type. prevent use generate debug project but switch release mode in IDE
    if(CMAKE_GENERATOR)
        set(CMAKE_CONFIGURATION_TYPES "${CMAKE_BUILD_TYPE}" CACHE STRING "Reset the configurations to what we need" FORCE)
    endif()

    include(CocosBuildHelpers)

    # SelectModule() is a macro to select building modules
    include(SelectModule)
    SelectModule()

    # set compiler options
    include(SetCompilerOptions)
    SetCompilerOptions()

    if(CMAKE_FIND_ROOT_PATH AND USE_EXTERNAL_PREBUILT)
        # Adds cocos2d-x external folder to the list of valid include/library paths when cross-compiling and using prebuilds
        set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH} ${COCOS_EXTERNAL_DIR})
    endif()

    if(WINDOWS)
        # folder much targets
        set_property(GLOBAL PROPERTY USE_FOLDERS ON)
        # not support other compile tools except MSVC for now
        if(MSVC)
            if (${MSVC_VERSION} EQUAL 1900 OR ${MSVC_VERSION} GREATER 1900)
                message(STATUS "using Windows MSVC generate cocos2d-x project, MSVC_VERSION:${MSVC_VERSION} check pass")
            else()
                message(FATAL_ERROR "using Windows MSVC generate cocos2d-x project, MSVC_VERSION:${MSVC_VERSION} too low" )
            endif()
        else()
            message(FATAL_ERROR "please using Windows MSVC compile cocos2d-x project, support other compile tools not yet" )
        endif()
    endif()

    # check use prebuilt config
    if(GEN_COCOS_PREBUILT AND USE_COCOS_PREBUILT)
        message(FATAL_ERROR "can't generate prebuilt libs and use prebuilt libs at the same time" )
    endif()

    if(GEN_COCOS_PREBUILT OR USE_COCOS_PREBUILT)
        message(STATUS "pre-defined COCOS_PREBUILT_ROOT: ${COCOS_PREBUILT_ROOT}")
        if(DEFINED COCOS_PREBUILT_ROOT)
            if(NOT IS_DIRECTORY ${COCOS_PREBUILT_ROOT})
                message(STATUS "prebuilt root directory defined but not existed, create: ${COCOS_PREBUILT_ROOT}")
                file(MAKE_DIRECTORY ${COCOS_PREBUILT_ROOT})
            endif()
        else()
            # the default prebuilt path is cocos2d-x/prebuilt
            set(COCOS_PREBUILT_ROOT $ENV{COCOS_TEMPLATES_ROOT}/../prebuilt)
        endif()
        if(IS_DIRECTORY ${COCOS_PREBUILT_ROOT})
            # prebuilt libs path
            set(COCOS_PREBUILT_PATH ${COCOS_PREBUILT_ROOT}/${PLATFORM_FOLDER}/${CMAKE_BUILD_TYPE})
            if(XCODE OR VS)
                set(COCOS_PREBUILT_PATH ${COCOS_PREBUILT_ROOT}/${PLATFORM_FOLDER})
            endif()
            if(ANDROID)
                set(COCOS_PREBUILT_PATH ${COCOS_PREBUILT_ROOT}/${PLATFORM_FOLDER}/${ANDROID_ABI})
            endif()
            message(STATUS "COCOS_PREBUILT_PATH:" ${COCOS_PREBUILT_PATH})
        else()
            if(ANDROID)
                message(WARNING "using cmake in Android Studio, can't get value of environment variable" )
            endif()
            message(FATAL_ERROR "can't find prebuilt libs location, please check cocos environment variable" )
        endif()
    endif()

    if(USE_EXTERNAL_PREBUILT)
        include(CocosPickLibs)
    endif()

    include(BuildModules)
    BuildModules()
endmacro(CocosBuildSet)

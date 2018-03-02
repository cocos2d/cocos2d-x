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


    include(CocosBuildHelpers)

    # SelectModule() is a macro to select building modules
    include(SelectModule)
    SelectModule()

    # set compiler options
    include(SetCompilerOptions)
    SetCompilerOptions()

    # collect prebuilt libraries
    if(USE_EXTERNAL_PREBUILT OR USE_COCOS_PREBUILT)
        include(CocosPickLibs)
    endif()

    # compile source libraries, find prebuilt package
    include(BuildModules)
    BuildModules()
endmacro(CocosBuildSet)

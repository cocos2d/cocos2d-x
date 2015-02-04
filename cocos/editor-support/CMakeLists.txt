# This file include by cocos/CMakeLists.txt.

option(BUILD_SUPPORT_COCOSBUILDER "Build editor support for cocosbuilder" ON)
option(BUILD_SUPPORT_COCOSTUDIO "Build editor support for cocostudio" ON)
option(BUILD_SUPPORT_SPINE "Build editor support for spine" ON)

if(BUILD_SUPPORT_COCOSBUILDER)
    include("editor-support/cocosbuilder/CMakeLists.txt")
endif()

if(BUILD_SUPPORT_COCOSTUDIO)
    include("editor-support/cocostudio/CMakeLists.txt")
endif()

if(BUILD_SUPPORT_SPINE)
    add_subdirectory("editor-support/spine")
endif()

if(BUILD_SUPPORT_COCOSBUILDER OR BUILD_SUPPORT_COCOSTUDIO OR BUILD_SUPPORT_SPINE)
    target_include_directories(${COCOS2D_TARGET} PUBLIC editor-support)
endif()



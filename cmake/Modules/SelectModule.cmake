# the default behavior of build module
macro(selectmodule)

    set(USE_WEBP_DEFAULT ON)
    set(USE_EXTERNAL_PREBUILT_DEFAULT ON)

    set(GEN_COCOS_PREBUILT_DEFAULT OFF)
    set(USE_COCOS_PREBUILT_DEFAULT OFF)

    set(BUILD_LUA_LIBS_DEFAULT OFF)
    set(BUILD_JS_LIBS_DEFAULT OFF)

    option(USE_CHIPMUNK "Use chipmunk for physics library" ON)
    option(USE_BOX2D "Use box2d for physics library" OFF)
    option(USE_BULLET "Use bullet for physics3d library" ON)
    option(USE_RECAST "Use Recast for navigation mesh" ON)
    option(USE_WEBP "Use WebP codec" ${USE_WEBP_DEFAULT})
    option(USE_PNG "Use PNG codec" ON)
    option(USE_TIFF "Use TIFF codec" ON)
    option(USE_JPEG "Use JPEG codec" ON)
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
    option(DEBUG_MODE "Debug or Release?" ON)
    option(BUILD_EXTENSIONS "Build extension library" ON)
    option(BUILD_EDITOR_SPINE "Build editor support for spine" ON)
    option(BUILD_EDITOR_COCOSTUDIO "Build editor support for cocostudio" ON)
    option(BUILD_EDITOR_COCOSBUILDER "Build editor support for cocosbuilder" ON)
    option(BUILD_LUA_LIBS "Build lua libraries" ${BUILD_LUA_LIBS_DEFAULT})
    option(BUILD_JS_LIBS "Build js libraries" ${BUILD_JS_LIBS_DEFAULT})
    option(USE_EXTERNAL_PREBUILT "Use prebuilt libraries in external directory" ${USE_EXTERNAL_PREBUILT_DEFAULT})
    option(GEN_COCOS_PREBUILT "generate cocos static libraries, put libraries into prebuilt folder in cocos root" ${GEN_COCOS_PREBUILT_DEFAULT})
    option(USE_COCOS_PREBUILT "use cocos static libraries, return warning if not find" ${USE_COCOS_PREBUILT_DEFAULT})

endmacro(selectmodule)
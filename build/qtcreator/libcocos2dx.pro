
TEMPLATE = lib
CONFIG += dll

include(common.prf)

LIBS += $$CC_EXTERNAL_LIBS

# Function cc_files(wildcardPath) returns all files matching given wildcard,
# without recursive folders search.
defineReplace(cc_files) {
    return($$files(../../$$1))
}

TARGET = $$cc_get_target_path($${CC_LIB_LOCATION}/cocos2dx)

OBJECTS_DIR = obj/cocos2dx/$${BUILD_TYPE}
MOC_DIR = obj/cocos2dx/$${BUILD_TYPE}

SOURCES += \
    $$cc_files(cocos/2d/*.cpp) \
    $$cc_files(cocos/2d/*.c) \
    $$cc_files(cocos/base/*.cpp) \
    $$cc_files(cocos/network/*.cpp) \
    $$cc_files(cocos/physics/*.cpp) \
    $$cc_files(cocos/math/kazmath/src/*.c) \
    $$cc_files(cocos/math/kazmath/src/GL/*.c) \
    $$cc_files(cocos/gui/*.cpp) \
    $$cc_files(cocos/editor-support/cocosbuilder/*.cpp) \
    $$cc_files(cocos/editor-support/spine/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/action/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/components/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/json/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/reader/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/armature/animation/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/armature/datas/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/armature/display/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/armature/physics/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/armature/utils/*.cpp) \
    $$cc_files(cocos/editor-support/cocostudio/armature/*.cpp) \
    ../../external/tinyxml2/tinyxml2.cpp \
    $$cc_files(external/unzip/*.cpp) \
    $$cc_files(external/json/*.cpp) \
    $$cc_files(extensions/proj.win32/*.cpp) \
    $$cc_files(extensions/assets-manager/*.cpp) \
    $$cc_files(extensions/physics-nodes/*.cpp) \
    $$cc_files(extensions/GUI/CCControlExtension/*.cpp) \
    $$cc_files(extensions/GUI/CCEditBox/*.cpp) \
    $$cc_files(extensions/GUI/CCScrollView/*.cpp) \
    $$cc_files(external/Box2D/Collision/*.cpp) \
    $$cc_files(external/Box2D/Collision/Shapes/*.cpp) \
    $$cc_files(external/Box2D/Common/*.cpp) \
    $$cc_files(external/Box2D/Dynamics/*.cpp) \
    $$cc_files(external/Box2D/Dynamics/Contacts/*.cpp) \
    $$cc_files(external/Box2D/Dynamics/Joints/*.cpp) \
    $$cc_files(external/Box2D/Rope/*.cpp) \
    $$cc_files(external/chipmunk/src/*.c) \
    $$cc_files(external/chipmunk/src/constraints/*.c)

win32 {
    SOURCES += $$cc_files(cocos/audio/win32/*.cpp)
    HEADERS += $$cc_files(cocos/audio/win32/*.h)
} else {
    SOURCES += $$cc_files(cocos/audio/openal/*.cpp)
}

# FIXME: websocket library does not work on Linux.
*linux-* {
    SOURCES -= ../../cocos/network/WebSocket.cpp
    SOURCES -= ../../cocos/network/SocketIO.cpp
}

HEADERS += \
    $$cc_files(cocos/2d/*.h) \
    $$cc_files(cocos/base/*.h) \
    $$cc_files(cocos/network/*.h) \
    $$cc_files(cocos/physics/*.h) \
    $$cc_files(cocos/audio/include/*.h) \
    $$cc_files(cocos/audio/openal/*.h) \
    $$cc_files(cocos/math/kazmath/include/kazmath/*.h) \
    $$cc_files(cocos/math/kazmath/include/kazmath/GL/*.h) \
    $$cc_files(cocos/gui/*.h) \
    $$cc_files(cocos/editor-support/cocosbuilder/*.h) \
    $$cc_files(cocos/editor-support/spine/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/action/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/components/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/json/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/reader/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/armature/animation/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/armature/datas/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/armature/display/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/armature/physics/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/armature/utils/*.h) \
    $$cc_files(cocos/editor-support/cocostudio/armature/*.h) \
    ../../external/tinyxml2/tinyxml2.h \
    $$cc_files(external/unzip/*.h) \
    $$cc_files(external/json/*.h) \
    $$cc_files(extensions/assets-manager/*.h) \
    $$cc_files(extensions/physics-nodes/*.h) \
    $$cc_files(extensions/GUI/CCControlExtension/*.h) \
    $$cc_files(extensions/GUI/CCEditBox/*.h) \
    $$cc_files(extensions/GUI/CCScrollView/*.h) \
    $$cc_files(extensions/*.h) \
    $$cc_files(extensions/proj.win32/*.h)

cocos2d_qt_api {
    SOURCES += $$cc_files(cocos/2d/platform/qt5/*.cpp)
    HEADERS += $$cc_files(cocos/2d/platform/qt5/*.h)
}

cocos2d_native_api {
    SOURCES += $$cc_files(cocos/2d/platform/*.cpp)
    HEADERS += $$cc_files(cocos/2d/platform/*.h)
    *linux-* {
        SOURCES += $$cc_files(cocos/2d/platform/linux/*.cpp)
        HEADERS += $$cc_files(cocos/2d/platform/linux/*.h)
    }
    *macx-*:
        OBJECTIVE_SOURCES += \
            $$cc_files(cocos/2d/platform/mac/*.mm) \
            $$cc_files(cocos/2d/platform/mac/*.m) \
            $$cc_files(cocos/2d/platform/apple/*.mm) \
            $$cc_files(cocos/2d/platform/apple/*.cpp)
        OBJECTIVE_HEADERS += \
            $$cc_files(cocos/2d/platform/mac/*.h) \
            $$cc_files(cocos/2d/platform/apple/*.h)
    *win32-* {
        SOURCES += $$cc_files(cocos/2d/platform/win32/*.cpp)
        HEADERS += $$cc_files(cocos/2d/platform/win32/*.h)
    }
}

cocos2d_chipmunk {
    HEADERS += $$cc_files(cocos/physics/chipmunk/*.h)
    SOURCES += $$cc_files(cocos/physics/chipmunk/*.cpp)
}

cocos2d_box2d {
    HEADERS += $$cc_files(cocos/physics/box2d/*.h)
    SOURCES += $$cc_files(cocos/physics/box2d/*.cpp)
}


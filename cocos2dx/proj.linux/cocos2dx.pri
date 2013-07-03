
################################################################################
#
# If you want enable extra modules, set COCOS2D_MODULES variable before include
# this file, example:
#   COCOS2D_MODULES += CocosDenshion
#   COCOS2D_MODULES += extensions
#   COCOS2D_MODULES += box2d
# or
#   COCOS2D_MODULES += chipmunk
# note: you cannot include both box2d and chipmunk.
#
# By default, QtCreator project will use OpenAL audio backend (because FMOD is
# free only for non-commercial use). If you are legal FMOD user, set variable
# COCOS2D_USE_FMOD to use FMOD audio backend:
#   COCOS2D_USE_FMOD = 1
#
################################################################################

INCLUDEPATH += $$PWD/../
INCLUDEPATH += $$PWD/../cocoa/
INCLUDEPATH += $$PWD/../include/
INCLUDEPATH += $$PWD/../platform/
INCLUDEPATH += $$PWD/../kazmath/include

*-msvc* {
    # Use equivalents of -Wno-overloaded-virtual -Wno-unused-parameter.
    QMAKE_CXXFLAGS_WARN_ON += /wd4263 /wd4100
} else {
    QMAKE_CXXFLAGS_WARN_ON += -Wno-ignored-qualifiers -Wno-overloaded-virtual -Wno-unused-parameter -Wno-unused-function
    QMAKE_CXXFLAGS += -std=c++0x
}

include($$PWD/cocos2dx.prf)

linux {
    DEFINES += LINUX
    INCLUDEPATH += $$PWD/../platform/linux
    LIBS += -lpthread
}

contains(COCOS2D_MODULES,CocosDenshion) {
    INCLUDEPATH += $$PWD/../../CocosDenshion/include
    include($$PWD/../../CocosDenshion/proj.linux/CocosDenshion.prf)
}

contains(COCOS2D_MODULES,extensions) {
    INCLUDEPATH += $$PWD/../../extensions
    LIBS += -lcurl
    include($$PWD/../../extensions/proj.linux/extensions.prf)
}

contains(COCOS2D_MODULES,box2d) {
    INCLUDEPATH += $$PWD/../../external
    include($$PWD/../../external/Box2D/proj.linux/box2d.prf)
}

contains(COCOS2D_MODULES,chipmunk) {
    contains(COCOS2D_MODULES,box2d):error("COCOS2D_MODULES cannot contain both box2d and chipmunk: choose one and remove another.")

    INCLUDEPATH += $$PWD/../../external/chipmunk/include/chipmunk
    include($$PWD/../../external/chipmunk/proj.linux/chipmunk.prf)
}

CONFIG(debug, debug|release) {
    DEFINES += COCOS2D_DEBUG=1
}
else {
    DEFINES += COCOS2D_DEBUG=0
}

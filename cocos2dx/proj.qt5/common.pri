
include(user_configuration.pri)

DEFINES += CC_TARGET_QT5

CONFIG += silent

*macx-* {
    QMAKE_CXXFLAGS += -stdlib=libc++
}

# Disable some warnings to make compiler output easier to read during development
DISABLED_WARNINGS = -Wno-ignored-qualifiers -Wno-unused-parameter -Wno-sign-compare -Wno-unused-variable
*-g++* {
    DISABLED_WARNINGS += -Wno-psabi
}

QMAKE_CXXFLAGS_WARN_ON += $${DISABLED_WARNINGS} -Wno-reorder
QMAKE_CFLAGS_WARN_ON += $${DISABLED_WARNINGS}

# C++11 support (Pick the first one if you have an old GCC version)
#QMAKE_CXXFLAGS += -Doverride= -std=c++0x
CONFIG += c++11

OS_TYPE = linux

CONFIG(debug, debug|release) {
    DEFINES += COCOS2D_DEBUG=1
    BUILD_TYPE = debug
} else {
    DEFINES += COCOS2D_DEBUG=0
    BUILD_TYPE = release
}

OBJECTS_DIR = obj/$${BUILD_TYPE}
MOC_DIR = obj/$${BUILD_TYPE}
LIB_OUTPUT_DIR = $${PWD}/../../lib/$${OS_TYPE}/$${BUILD_TYPE}

# Installation location of binaries
LIB_INSTALL_DIR = /usr/lib
BIN_INSTALL_DIR = /usr/bin
DESKTOP_INSTALL_DIR = /usr/share/applications

INCLUDEPATH += $${PWD}/..
INCLUDEPATH += $${PWD}/../include
INCLUDEPATH += $${PWD}/../platform
INCLUDEPATH += $${PWD}/../platform/qt5
INCLUDEPATH += $${PWD}/../kazmath/include

COCOS2DX_SYSTEM_LIBS += -lz
COCOS2DX_SYSTEM_LIBS += -ljpeg -ltiff -lpng
COCOS2DX_SYSTEM_LIBS += -lfontconfig -lfreetype

# Sensors module needed for CCAccelerometer
QT += sensors

LINK_AGAINST_COCOS2DX = -L$${LIB_OUTPUT_DIR} -lcocos2d $${COCOS2DX_SYSTEM_LIBS}

# CocosDenshion (audio library)
QT += multimedia
INCLUDEPATH += $${PWD}/../../CocosDenshion/include
LINK_AGAINST_COCOSDENSHION = -lcocosdenshion

# Extensions library
INCLUDEPATH += $${PWD}/../../extensions
LINK_AGAINST_COCOSEXTENSION = -lextension -lchipmunk -lbox2d -lcurl

# Physics engines (pick one)
DEFINES += CC_ENABLE_CHIPMUNK_INTEGRATION
#DEFINES += CC_ENABLE_BOX2D_INTEGRATION
INCLUDEPATH += $${PWD}/../../external/chipmunk/include/chipmunk
INCLUDEPATH += $${PWD}/../../external


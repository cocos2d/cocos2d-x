
DEFINES += CC_TARGET_QT5

CONFIG += silent

QMAKE_CXXFLAGS += -Wno-ignored-qualifiers -Wno-unused-parameter -Wno-psabi
QMAKE_CFLAGS += -Wno-ignored-qualifiers -Wno-unused-parameter -Wno-psabi

OS_TYPE = linux

CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
} else {
    BUILD_TYPE = release
}

OBJECTS_DIR = obj/$${BUILD_TYPE}
LIB_OUTPUT_DIR = $${PWD}/../../lib/$${OS_TYPE}/$${BUILD_TYPE}

INCLUDEPATH += $${PWD}/..
INCLUDEPATH += $${PWD}/../include
INCLUDEPATH += $${PWD}/../platform
INCLUDEPATH += $${PWD}/../platform/qt5
INCLUDEPATH += $${PWD}/../kazmath/include

COCOS2DX_SYSTEM_LIBS += -lz
COCOS2DX_SYSTEM_LIBS += -ljpeg -ltiff -lpng
COCOS2DX_SYSTEM_LIBS += -lfontconfig -lfreetype

LINK_AGAINST_COCOS2DX = -L$${LIB_OUTPUT_DIR} -lcocos2d $${COCOS2DX_SYSTEM_LIBS}

# CocosDenshion (audio library)
QT += multimedia
INCLUDEPATH += $${PWD}/../../CocosDenshion/include
LINK_AGAINST_COCOSDENSHION = -L$${LIB_OUTPUT_DIR} -lcocosdenshion

# Physics engines (pick one)
DEFINES += CC_ENABLE_CHIPMUNK_INTEGRATION
#DEFINES += CC_ENABLE_BOX2D_INTEGRATION
INCLUDEPATH += $${PWD}/../../external/chipmunk/include/chipmunk
INCLUDEPATH += $${PWD}/../../external


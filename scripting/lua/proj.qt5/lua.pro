
include(../../../cocos2dx/proj.qt5/common.pri)

TEMPLATE = lib
CONFIG += static
CONFIG += c++11

SOURCES += $$files(../lua/*.c)
SOURCES += $$files(../tolua/*.c)
SOURCES += $$files(../cocos2dx_support/*.c)
SOURCES += $$files(../cocos2dx_support/*.cpp)

DEFINES += CC_TARGET_OS_MAC

INCLUDEPATH += ..
INCLUDEPATH += ../lua
INCLUDEPATH += ../tolua
INCLUDEPATH += ../Classes
INCLUDEPATH += ../../../CocosDenshion/include
INCLUDEPATH += ../../../extensions
INCLUDEPATH += ../../../external/chipmunk/include/chipmunk
INCLUDEPATH += ../../../cocos2dx/include
INCLUDEPATH += ../../../cocos2dx
INCLUDEPATH += ../../../cocos2dx/platform/qt5
INCLUDEPATH += ../../../cocos2dx/kazmath/include

# XXX SHAREDLIBS += -lextension

TARGET = $${LIB_OUTPUT_DIR}/lua


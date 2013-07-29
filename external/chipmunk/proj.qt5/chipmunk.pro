
include(../../../cocos2dx/proj.qt5/common.pri)

TEMPLATE = lib
CONFIG += static

SOURCES += $$files(../src/*.c)
SOURCES += $$files(../src/constraints/*.c)

QMAKE_CFLAGS += -std=gnu99

INCLUDEPATH += ../include/chipmunk

TARGET = $${LIB_OUTPUT_DIR}/chipmunk


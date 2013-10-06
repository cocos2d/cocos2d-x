
include(../../cocos2dx/proj.qt5/common.pri)

TEMPLATE = lib

SOURCES += $$files(../qt5/*.cpp)

HEADERS += $$files(../qt5/*.h) \
    $$files(../include/*.h)

INCLUDEPATH += ..
INCLUDEPATH += ../include

TARGET = $${LIB_OUTPUT_DIR}/cocosdenshion

INSTALLS += target
target.path = $${LIB_INSTALL_DIR}


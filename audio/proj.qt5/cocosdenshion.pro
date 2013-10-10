
include(../../cocos2dx/proj.qt5/common.pri)

TEMPLATE = lib

SOURCES += $$files(../qt5/*.cpp)

INCLUDEPATH += ..
INCLUDEPATH += ../include

TARGET = $${LIB_OUTPUT_DIR}/cocosdenshion

INSTALLS += target
target.path = $${LIB_INSTALL_DIR}


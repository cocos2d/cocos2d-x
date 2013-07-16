
include(../../../cocos2dx/proj.qt5/common.pri)

TEMPLATE = lib
CONFIG += static

SOURCES += $$files(../Collision/Shapes/*.cpp)
SOURCES += $$files(../Collision/*.cpp)
SOURCES += $$files(../Common/*.cpp)
SOURCES += $$files(../Dynamics/Contacts/*.cpp)
SOURCES += $$files(../Dynamics/Joints/*.cpp)
SOURCES += $$files(../Dynamics/*.cpp)
SOURCES += $$files(../Rope/*.cpp)

INCLUDEPATH += ../..

TARGET = $${LIB_OUTPUT_DIR}/box2d



include(../../../../cocos2dx/proj.qt5/common.pri)

TARGET = HelloCpp

INCLUDEPATH += ..
INCLUDEPATH += ../Classes

SOURCES += main.cpp
SOURCES += ../Classes/AppDelegate.cpp
SOURCES += ../Classes/HelloWorldScene.cpp

LIBS += $${LINK_AGAINST_COCOS2DX}



include(../../../../cocos2dx/proj.qt5/common.pri)

TARGET = SimpleGame

INCLUDEPATH += ..
INCLUDEPATH += ../Classes

SOURCES += main.cpp
SOURCES += ../Classes/AppDelegate.cpp
SOURCES += ../Classes/HelloWorldScene.cpp
SOURCES += ../Classes/GameOverScene.cpp

LIBS += $${LINK_AGAINST_COCOS2DX}
LIBS += $${LINK_AGAINST_COCOSDENSHION}


TARGET = MyCocos2dGame

# Try get path from project settings.
isEmpty(COCOS2D_ROOT):COCOS2D_ROOT=$$(COCOS2D_ROOT)
# Try get path from environment variable.
isEmpty(COCOS2D_ROOT):COCOS2D_ROOT=$$system(echo $COCOS2D_ROOT)
# Finally default to predefined path.
isEmpty(COCOS2D_ROOT):COCOS2D_ROOT=$$PWD/../../..

INCLUDEPATH += ..
INCLUDEPATH += ../Classes

# Go to "Projects" mode and add argument "COCOS2D_LINUX_NATIVE=1" to qmake build
# step if you want to use Linux Native backend instead of Qt5.
isEmpty(COCOS2D_LINUX_NATIVE) {
    include(cocos2d-qt5.pri)
} else {
    include(../proj.linux/cocos2d-linux.pri)
}

HEADERS += \
    ../Classes/AppDelegate.h \
    ../Classes/HelloWorldScene.h

SOURCES += \
    ../Classes/AppDelegate.cpp \
    ../Classes/HelloWorldScene.cpp

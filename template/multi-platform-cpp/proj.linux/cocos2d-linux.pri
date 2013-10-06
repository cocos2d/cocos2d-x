################################################################################
#                                                                              #
# Project part for QtCreator IDE. Actual project file located in "../proj.qt5" #
#                                                                              #
################################################################################

COCOS2D_MODULES += chipmunk CocosDenshion extensions
include($$COCOS2D_ROOT/cocos2dx/proj.linux/cocos2dx.pri)

SOURCES += $$PWD/main.cpp

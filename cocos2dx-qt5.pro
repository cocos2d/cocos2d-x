
TEMPLATE = subdirs

CONFIG += ordered

# Cocos2D-X Core Library
SUBDIRS += external/chipmunk/proj.qt5/chipmunk.pro
SUBDIRS += external/Box2D/proj.qt5/box2d.pro
SUBDIRS += cocos2dx/proj.qt5/cocos2dx.pro

# Cocos2D-X Additional Libraries
SUBDIRS += CocosDenshion/proj.qt5/cocosdenshion.pro
SUBDIRS += extensions/proj.qt5/extensions.pro

# Examples
SUBDIRS += samples/Cpp/HelloCpp/proj.qt5/HelloCpp.pro
SUBDIRS += samples/Cpp/SimpleGame/proj.qt5/SimpleGame.pro
SUBDIRS += samples/Cpp/TestCpp/proj.qt5/TestCpp.pro


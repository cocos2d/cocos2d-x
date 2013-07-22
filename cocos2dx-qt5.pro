
TEMPLATE = subdirs

CONFIG += ordered

# Cocos2D-X Core Library
SUBDIRS += external/chipmunk/proj.qt5/chipmunk.pro
SUBDIRS += external/Box2D/proj.qt5/box2d.pro
SUBDIRS += cocos2dx/proj.qt5/cocos2dx.pro

# Examples
SUBDIRS += samples/Cpp/HelloCpp/proj.qt5/HelloCpp.pro


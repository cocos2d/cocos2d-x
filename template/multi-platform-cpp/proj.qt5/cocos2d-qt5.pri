include($$COCOS2D_ROOT/cocos2dx/proj.qt5/common.pri)

SOURCES += $$PWD/main.cpp

LIBS += $${LINK_AGAINST_COCOS2DX}
LIBS += $${LINK_AGAINST_COCOSDENSHION}
LIBS += $${LINK_AGAINST_COCOSEXTENSION}

INSTALLS += target
target.path = /opt/$${TARGET}

INSTALLS += desktop
desktop.files = $$PWD/$${TARGET}.desktop
desktop.path = $${DESKTOP_INSTALL_DIR}

INSTALLS += resources
resources.files = $$PWD/icon.png $$PWD/../Resources
resources.path = /opt/$${TARGET}

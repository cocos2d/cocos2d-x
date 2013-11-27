
# Include this file to your game project file, example:
#   include(PATH_TO_COCOS2D/build/game.pri)

TEMPLATE = app

include(common.prf)

LIBS += $${LINK_AGAINST_COCOS2DX}

# Function cc_copy_directory copies directory.
# WARNING: works only for latin paths without spaces!
# Param 1 (required) Source path.
# Param 2 (optional) Destination path suffix, relative to build folder.
defineTest(cc_copy_directory) {
    CC_SRC = $$1
    CC_DEST_SUFFIX = $$2
    CC_DEST = $$shadowed($${PWD}/$${CC_DEST_SUFFIX})
    isEmpty(CC_DEST_SUFFIX):CC_DEST = $$shadowed($${PWD})
    win32:CC_DEST ~= s,/,\\,g
    win32:CC_SRC ~= s,/,\\,g

    *linux-*|*macx-* {
        CC_COMMAND = cp -r $$quote($$CC_SRC) $$quote($$CC_DEST) $$escape_expand(\\n\\t)
        QMAKE_POST_LINK += $$CC_COMMAND
    }

    export(QMAKE_POST_LINK)
}


DEFINES += CC_TARGET_QT5

CONFIG += silent

QMAKE_CXXFLAGS += -Wno-ignored-qualifiers -Wno-unused-parameter -Wno-psabi
QMAKE_CFLAGS += -Wno-ignored-qualifiers -Wno-unused-parameter -Wno-psabi

OS_TYPE = linux

CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
} else {
    BUILD_TYPE = release
}

OBJECTS_DIR = obj/$${BUILD_TYPE}
LIB_OUTPUT_DIR = $${PWD}/../../lib/$${OS_TYPE}/$${BUILD_TYPE}


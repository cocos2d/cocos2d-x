TARGET = libcocosdenshion.so

INCLUDES += -I.. -I../include

SOURCES = ../emscripten/SimpleAudioEngine.cpp

COCOS_ROOT = ../..
include $(COCOS_ROOT)/cocos2dx/proj.emscripten/cocos2dx.mk

TARGET := $(LIB_DIR)/$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -shared -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

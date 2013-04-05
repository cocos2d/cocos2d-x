EXECUTABLE = HelloCpp

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/HelloWorldScene.cpp

RESOURCE_PATH = ../Resources/iphone

RESOURCE_FLAGS = --preload CloseNormal.png \
                 --preload CloseSelected.png \
                 --preload HelloWorld.png

COCOS_ROOT = ../../../..
include $(COCOS_ROOT)/cocos2dx/proj.emscripten/cocos2dx.mk

SHAREDLIBS += -lcocos2d
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so

$(TARGET).js: $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

# TODO: Make this rule not an egregious hack.
$(TARGET).data:
	@mkdir -p $(@D)
	(cd $(RESOURCE_PATH); python $(PACKAGER) $(EXECUTABLE).data $(RESOURCE_FLAGS) --pre-run) > $(RESOURCE_PATH)/$(EXECUTABLE).data.js
	mv $(RESOURCE_PATH)/$(EXECUTABLE).data $@
	mv $(RESOURCE_PATH)/$(EXECUTABLE).data.js $@.js

$(BIN_DIR)/index.html: index.html
	@mkdir -p $(@D)
	cp index.html $(@D)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

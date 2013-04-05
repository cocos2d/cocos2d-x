EXECUTABLE = HelloCpp

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/HelloWorldScene.cpp

RESOURCE_PATH = ../Resources/iphone

RESOURCES = CloseNormal.png \
            CloseSelected.png \
            HelloWorld.png

FONT_PATH = ../Resources/fonts

COCOS_ROOT = ../../../..
include $(COCOS_ROOT)/cocos2dx/proj.emscripten/cocos2dx.mk

SHAREDLIBS += -lcocos2d
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so

$(TARGET).js: $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(TARGET).data:
	@mkdir -p $(@D)
	$(eval RESTMP := $(shell mktemp -d /tmp/cocos-emscripten.XXXXXX))
	# Always need a font path, so ensure that it is created first.
	mkdir -p $(RESTMP)/fonts
	(cd $(RESOURCE_PATH) && cp -a $(RESOURCES) $(RESTMP))
	(cd $(FONT_PATH) && cp -a * $(RESTMP)/fonts)
	# NOTE: we copy the system arial.ttf so that there is always a fallback.
	cp /Library/Fonts/Arial.ttf $(RESTMP)/fonts/arial.ttf
	(cd $(RESTMP); python $(PACKAGER) $(EXECUTABLE).data $(patsubst %,--preload %,$(RESOURCES)) --preload fonts --pre-run > $(EXECUTABLE).data.js)
	mv $(RESTMP)/$(EXECUTABLE).data $@
	mv $(RESTMP)/$(EXECUTABLE).data.js $@.js
	rm -rf $(RESTMP)

$(BIN_DIR)/index.html: index.html
	@mkdir -p $(@D)
	cp index.html $(@D)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

EXECUTABLE = SimpleGame

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/HelloWorldScene.cpp \
        ../Classes/GameOverScene.cpp

RESOURCE_PATH = ../Resources

RESOURCES = app.config.txt \
            app.icf \
            background-music-aac.wav \
            development.icf \
            pew-pew-lei.wav

SD_RESOURCE_PATH = ../Resources/sd

SD_RESOURCES = app.icf \
               CloseNormal.png \
               CloseSelected.png \
               Player.png \
               Projectile.png \
               Target.png

ALL_ASSETS := $(SD_RESOURCES) $(RESOURCES)

COCOS_ROOT = ../../../..
include $(COCOS_ROOT)/cocos2dx/proj.emscripten/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so
INCLUDES += -I$(COCOS_ROOT)/CocosDenshion/include

$(TARGET).js: $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(TARGET).data:
	@mkdir -p $(@D)
	$(eval RESTMP := $(shell mktemp -d /tmp/cocos-emscripten.XXXXXX))
	# Always need a font path, so ensure that it is created first.
	mkdir -p $(RESTMP)/fonts
	(cd $(RESOURCE_PATH) && tar cf - $(RESOURCES)) | (cd $(RESTMP) && tar xvf -)
	(cd $(SD_RESOURCE_PATH) && tar cf - $(SD_RESOURCES)) | (cd $(RESTMP) && tar xvf -)
	# NOTE: we copy the system arial.ttf so that there is always a fallback.
	cp /Library/Fonts/Arial.ttf $(RESTMP)/fonts/arial.ttf
	(cd $(RESTMP); python $(PACKAGER) $(EXECUTABLE).data $(patsubst %,--preload %,$(ALL_ASSETS)) --preload fonts --pre-run > $(EXECUTABLE).data.js)
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

CC      = gcc
CXX     = g++
TARGET	= libcocos2d.so
CCFLAGS = -Wall -g -O2 -fPIC
CXXFLAGS = -Wall -g -O2 -fPIC
VISIBILITY = 

INCLUDES = -I.. \
					-I../platform/third_party/linux/libfreetype2 \
					-I../include \
					-I../platform \
					-I../platform/third_party/linux/libpng \
					-I../platform/third_party/linux/libxml2 \
					-I../platform/third_party/linux/libjpeg 

DEFINES = -DLINUX

OBJECTS = ../actions/CCAction.o \
					../actions/CCActionCamera.o \
					../actions/CCActionEase.o \
					../actions/CCActionGrid.o \
					../actions/CCActionGrid3D.o \
					../actions/CCActionInstant.o \
					../actions/CCActionInterval.o \
					../actions/CCActionManager.o \
					../actions/CCActionPageTurn3D.o \
					../actions/CCActionProgressTimer.o \
					../actions/CCActionTiledGrid.o \
					../base_nodes/CCAtlasNode.o \
					../base_nodes/CCNode.o \
					../cocoa/CCAffineTransform.o \
					../cocoa/CCAutoreleasePool.o \
					../cocoa/CCData.o \
					../cocoa/CCGeometry.o \
					../cocoa/CCNS.o \
					../cocoa/CCObject.o \
					../cocoa/CCSet.o \
					../cocoa/CCZone.o \
					../effects/CCGrabber.o \
					../effects/CCGrid.o \
					../extensions/CCNotificationCenter.o \
					../keypad_dispatcher/CCKeypadDelegate.o \
					../keypad_dispatcher/CCKeypadDispatcher.o \
					../label_nodes/CCLabelAtlas.o \
					../label_nodes/CCLabelBMFont.o \
					../label_nodes/CCLabelTTF.o \
					../layers_scenes_transitions_nodes/CCLayer.o \
					../layers_scenes_transitions_nodes/CCScene.o \
					../layers_scenes_transitions_nodes/CCTransition.o \
					../layers_scenes_transitions_nodes/CCTransitionPageTurn.o \
					../layers_scenes_transitions_nodes/CCTransitionRadial.o \
					../menu_nodes/CCMenu.o \
					../menu_nodes/CCMenuItem.o \
					../misc_nodes/CCMotionStreak.o \
					../misc_nodes/CCProgressTimer.o \
					../misc_nodes/CCRenderTexture.o \
					../misc_nodes/CCRibbon.o \
					../particle_nodes/CCParticleExamples.o \
					../particle_nodes/CCParticleSystem.o \
					../particle_nodes/CCParticleSystemQuad.o \
					../platform/CCCommon.o \
					../platform/CCFileUtils.o \
					../platform/CCGL.o \
					../platform/CCImage.o \
					../platform/CCSAXParser.o \
					../platform/CCStdC.o \
					../platform/CCThread.o \
					../platform/platform.o \
					../platform/Linux/CCAplication_linux.o \
					../platform/Linux/CCEGLView_linux.o \
					../script_support/CCScriptSupport.o \
					../sprite_nodes/CCAnimation.o \
					../sprite_nodes/CCAnimationCache.o \
					../sprite_nodes/CCSprite.o \
					../sprite_nodes/CCSpriteBatchNode.o \
					../sprite_nodes/CCSpriteFrame.o \
					../sprite_nodes/CCSpriteFrameCache.o \
					../support/CCArray.o \
					../support/CCPointExtension.o \
					../support/CCProfiling.o \
					../support/CCUserDefault.o \
					../support/TransformUtils.o \
					../support/base64.o \
					../support/ccUtils.o \
					../support/image_support/TGAlib.o \
					../support/zip_support/ZipUtils.o \
					../support/zip_support/ioapi.o \
					../support/zip_support/unzip.o \
					../text_input_node/CCIMEDispatcher.o \
					../text_input_node/CCTextFieldTTF.o \
					../textures/CCTexture2D.o \
					../textures/CCTextureAtlas.o \
					../textures/CCTextureCache.o \
					../textures/CCTexturePVR.o \
					../tileMap_parallax_nodes/CCParallaxNode.o \
					../tileMap_parallax_nodes/CCTMXLayer.o \
					../tileMap_parallax_nodes/CCTMXObjectGroup.o \
					../tileMap_parallax_nodes/CCTMXTiledMap.o \
					../tileMap_parallax_nodes/CCTMXXMLParser.o \
					../tileMap_parallax_nodes/CCTileMapAtlas.o \
					../touch_dispatcher/CCTouchDispatcher.o \
					../touch_dispatcher/CCTouchHandler.o \
					../CCCamera.o \
					../CCConfiguration.o \
					../CCDirector.o \
					../CCDrawingPrimitives.o \
					../CCScheduler.o \
					../cocos2d.o 

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
STATICLIBS_DIR = ../platform/third_party/linux/libraries/lib64
else
STATICLIBS_DIR = ../platform/third_party/linux/libraries
endif
STATICLIBS = $(STATICLIBS_DIR)/libfreetype.a \
						$(STATICLIBS_DIR)/libcurl.a \
						$(STATICLIBS_DIR)/libxml2.a \
						$(STATICLIBS_DIR)/libpng.a \
						$(STATICLIBS_DIR)/libjpeg.a

SHAREDLIBS = -lglfw -lGL

####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -shared -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)
	
####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
		
clean: 
	rm -f $(OBJECTS) $(TARGET) core

CC      = gcc
CXX     = g++
TARGET	= libcocos2d.so
CCFLAGS = -Wall -g -fPIC #-O2 
CXXFLAGS = -Wall -g -fPIC #-O2 
VISIBILITY = 

LIBS = 

INCLUDES = -I.. \
			-I../platform/third_party/linux/libfreetype2 \
			-I../cocoa \
			-I../include \
			-I../kazmath/include \
			-I../platform \
			-I../../extensions \
			-I../../extensions/CCBReader \
			-I../../extensions/GUI/CCControlExtension \
			-I../../extensions/GUI/CCControlExtension \
			-I../platform/linux/ \
			-I../platform/third_party/linux/glew-1.7.0/glew-1.7.0/include/ \
			-I../platform/third_party/linux/libxml2 \
			-I../platform/third_party/linux/libpng \
			-I../platform/third_party/linux/libjpeg \
			-I../platform/third_party/linux/libtiff/include \

#			-I../platform/third_party/linux/libpng \

DEFINES = -DLINUX
DEFINES += -D__CC_PLATFORM_FILEUTILS_CPP__
DEFINES += -D__CC_PLATFORM_IMAGE_CPP__

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
					../actions/CCActionCatmullRom.o \
					../actions/CCActionTween.o \
					../base_nodes/CCAtlasNode.o \
					../base_nodes/CCNode.o \
					../cocoa/CCAffineTransform.o \
					../cocoa/CCAutoreleasePool.o \
					../cocoa/CCGeometry.o \
					../cocoa/CCNS.o \
					../cocoa/CCObject.o \
					../cocoa/CCSet.o \
					../cocoa/CCZone.o \
					../cocoa/CCArray.o \
					../cocoa/CCDictionary.o \
					../cocoa/CCString.o \
					../effects/CCGrabber.o \
					../effects/CCGrid.o \
					../keypad_dispatcher/CCKeypadDelegate.o \
					../keypad_dispatcher/CCKeypadDispatcher.o \
					../label_nodes/CCLabelAtlas.o \
					../label_nodes/CCLabelBMFont.o \
					../label_nodes/CCLabelTTF.o \
					../layers_scenes_transitions_nodes/CCLayer.o \
					../layers_scenes_transitions_nodes/CCScene.o \
					../layers_scenes_transitions_nodes/CCTransition.o \
					../layers_scenes_transitions_nodes/CCTransitionPageTurn.o \
					../layers_scenes_transitions_nodes/CCTransitionProgress.o \
					../menu_nodes/CCMenu.o \
					../menu_nodes/CCMenuItem.o \
					../misc_nodes/CCMotionStreak.o \
					../misc_nodes/CCProgressTimer.o \
					../misc_nodes/CCRenderTexture.o \
					../particle_nodes/CCParticleExamples.o \
					../particle_nodes/CCParticleSystem.o \
					../particle_nodes/CCParticleSystemQuad.o \
					../particle_nodes/CCParticleBatchNode.o \
					../platform/CCSAXParser.o \
					../platform/CCThread.o \
					../platform/platform.o \
					../platform/CCEGLViewProtocol.o \
					../platform/linux/CCStdC.o \
					../platform/linux/CCFileUtils.o \
					../platform/linux/CCCommon.o \
					../platform/linux/CCApplication.o \
					../platform/linux/CCEGLView.o \
					../platform/linux/CCImage.o \
					../script_support/CCScriptSupport.o \
					../sprite_nodes/CCAnimation.o \
					../sprite_nodes/CCAnimationCache.o \
					../sprite_nodes/CCSprite.o \
					../sprite_nodes/CCSpriteBatchNode.o \
					../sprite_nodes/CCSpriteFrame.o \
					../sprite_nodes/CCSpriteFrameCache.o \
					../support/CCPointExtension.o \
					../support/CCProfiling.o \
					../support/CCUserDefault.o \
					../support/TransformUtils.o \
					../support/base64.o \
					../support/ccUtils.o \
					../support/CCVertex.o \
					../support/CCNotificationCenter.o \
					../support/image_support/TGAlib.o \
					../support/zip_support/ZipUtils.o \
					../support/zip_support/ioapi.o \
					../support/zip_support/unzip.o \
					../support/data_support/ccCArray.o \
					../text_input_node/CCIMEDispatcher.o \
					../text_input_node/CCTextFieldTTF.o \
					../textures/CCTexture2D.o \
					../textures/CCTextureAtlas.o \
					../textures/CCTextureCache.o \
					../textures/CCTexturePVR.o \
					../tilemap_parallax_nodes/CCParallaxNode.o \
					../tilemap_parallax_nodes/CCTMXLayer.o \
					../tilemap_parallax_nodes/CCTMXObjectGroup.o \
					../tilemap_parallax_nodes/CCTMXTiledMap.o \
					../tilemap_parallax_nodes/CCTMXXMLParser.o \
					../tilemap_parallax_nodes/CCTileMapAtlas.o \
					../touch_dispatcher/CCTouchDispatcher.o \
					../touch_dispatcher/CCTouchHandler.o \
					../touch_dispatcher/CCTouch.o \
					../shaders/CCGLProgram.o \
					../shaders/ccGLStateCache.o \
					../shaders/CCShaderCache.o \
					../shaders/ccShaders.o \
					../../extensions/CCBReader/CCBFileLoader.o \
					../../extensions/CCBReader/CCMenuItemImageLoader.o \
					../../extensions/CCBReader/CCBReader.o \
					../../extensions/CCBReader/CCMenuItemLoader.o \
					../../extensions/CCBReader/CCControlButtonLoader.o \
					../../extensions/CCBReader/CCNodeLoader.o \
					../../extensions/CCBReader/CCControlLoader.o \
					../../extensions/CCBReader/CCNodeLoaderLibrary.o \
					../../extensions/CCBReader/CCLabelBMFontLoader.o \
					../../extensions/CCBReader/CCParticleSystemQuadLoader.o \
					../../extensions/CCBReader/CCLabelTTFLoader.o \
					../../extensions/CCBReader/CCScale9SpriteLoader.o \
					../../extensions/CCBReader/CCLayerColorLoader.o \
					../../extensions/CCBReader/CCScrollViewLoader.o \
					../../extensions/CCBReader/CCLayerGradientLoader.o \
					../../extensions/CCBReader/CCSpriteLoader.o \
					../../extensions/CCBReader/CCLayerLoader.o \
					../../extensions/GUI/CCScrollView/CCScrollView.o \
					../../extensions/GUI/CCControlExtension/CCControlButton.o \
					../../extensions/GUI/CCControlExtension/CCControlColourPicker.o \
					../../extensions/GUI/CCControlExtension/CCControl.o \
					../../extensions/GUI/CCControlExtension/CCControlHuePicker.o \
					../../extensions/GUI/CCControlExtension/CCControlSaturationBrightnessPicker.o \
					../../extensions/GUI/CCControlExtension/CCControlSlider.o \
					../../extensions/GUI/CCControlExtension/CCControlSwitch.o \
					../../extensions/GUI/CCControlExtension/CCControlUtils.o \
					../../extensions/GUI/CCControlExtension/CCInvocation.o \
					../../extensions/GUI/CCControlExtension/CCMenuPassive.o \
					../../extensions/GUI/CCControlExtension/CCScale9Sprite.o \
					../../extensions/GUI/CCControlExtension/CCSpacer.o \
					../kazmath/src/aabb.o \
					../kazmath/src/plane.o \
					../kazmath/src/vec2.o \
					../kazmath/src/mat3.o \
					../kazmath/src/quaternion.o \
					../kazmath/src/vec3.o \
					../kazmath/src/mat4.o \
					../kazmath/src/ray2.o \
					../kazmath/src/vec4.o \
					../kazmath/src/neon_matrix_impl.o \
					../kazmath/src/utility.o \
					../kazmath/src/GL/mat4stack.o \
					../kazmath/src/GL/matrix.o \
					../CCCamera.o \
					../CCConfiguration.o \
					../CCDirector.o \
					../CCDrawingPrimitives.o \
					../CCScheduler.o \
					../cocos2d.o 
#					../../extensions/CCListView/CCListViewCell.o \
#					../../extensions/CCListView/CCListView.o \
#					../../extensions/GUI/CCTextureWatcher/CCTextureWatcher.o \

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
STATICLIBS_DIR = ../platform/third_party/linux/libraries/lib64
else
STATICLIBS_DIR = ../platform/third_party/linux/libraries
endif
STATICLIBS = 
STATICLIBS = $(STATICLIBS_DIR)/libfreetype.a \
				$(STATICLIBS_DIR)/libcurl.a \
				$(STATICLIBS_DIR)/libxml2.a \
				$(STATICLIBS_DIR)/libpng.a \
				$(STATICLIBS_DIR)/libjpeg.a \
				$(STATICLIBS_DIR)/libtiff.a \

SHAREDLIBS = 
SHAREDLIBS += -lglfw -lGL
SHAREDLIBS += -Wl,-rpath,../../cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib
SHAREDLIBS += -L../../cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib -lGLEW


####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -shared -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS) $(LIBS)
	
####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
		
clean: 
	rm -f $(OBJECTS) $(TARGET) core

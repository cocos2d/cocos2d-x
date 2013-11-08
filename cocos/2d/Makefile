TARGET = libcocos2d.so

INCLUDES = 

SOURCES = \
CCAction.cpp \
CCActionCamera.cpp \
CCActionEase.cpp \
CCActionGrid.cpp \
CCActionGrid3D.cpp \
CCActionInstant.cpp \
CCActionInterval.cpp \
CCActionManager.cpp \
CCActionPageTurn3D.cpp \
CCActionProgressTimer.cpp \
CCActionTiledGrid.cpp \
CCActionCatmullRom.cpp \
CCActionTween.cpp \
CCAtlasNode.cpp \
CCNode.cpp \
../base/CCAffineTransform.cpp \
../base/CCAutoreleasePool.cpp \
../base/CCGeometry.cpp \
../base/CCNS.cpp \
../base/CCObject.cpp \
../base/CCSet.cpp \
../base/CCArray.cpp \
../base/CCDictionary.cpp \
../base/CCString.cpp \
../base/CCDataVisitor.cpp \
../base/CCData.cpp \
CCEventAcceleration.cpp \
CCEventListenerAcceleration.cpp \
CCEvent.cpp \
CCEventDispatcher.cpp \
CCEventListener.cpp \
CCEventKeyboard.cpp \
CCEventListenerKeyboard.cpp \
CCEventMouse.cpp \
CCEventListenerMouse.cpp \
CCTouch.cpp \
CCEventTouch.cpp \
CCEventListenerTouch.cpp \
CCEventCustom.cpp \
CCEventListenerCustom.cpp \
CCDrawingPrimitives.cpp \
CCDrawNode.cpp \
CCGrabber.cpp \
CCGrid.cpp \
CCFont.cpp \
CCFontAtlas.cpp \
CCFontAtlasCache.cpp \
CCFontAtlasFactory.cpp \
CCFontDefinition.cpp \
CCFontFNT.cpp \
CCFontFreeType.cpp \
CCLabel.cpp \
CCLabelAtlas.cpp \
CCLabelBMFont.cpp \
CCLabelTTF.cpp \
CCLabelTextFormatter.cpp \
CCTextImage.cpp \
CCLayer.cpp \
CCScene.cpp \
CCTransition.cpp \
CCTransitionPageTurn.cpp \
CCTransitionProgress.cpp \
CCMenu.cpp \
CCMenuItem.cpp \
CCMotionStreak.cpp \
CCProgressTimer.cpp \
CCClippingNode.cpp \
CCRenderTexture.cpp \
CCParticleExamples.cpp \
CCParticleSystem.cpp \
CCParticleSystemQuad.cpp \
CCParticleBatchNode.cpp \
../physics/box2d/CCPhysicsContactInfo_box2d.cpp \
../physics/box2d/CCPhysicsJointInfo_box2d.cpp \
../physics/box2d/CCPhysicsShapeInfo_box2d.cpp \
../physics/box2d/CCPhysicsBodyInfo_box2d.cpp \
../physics/box2d/CCPhysicsWorldInfo_box2d.cpp \
../physics/chipmunk/CCPhysicsContactInfo_chipmunk.cpp \
../physics/chipmunk/CCPhysicsJointInfo_chipmunk.cpp \
../physics/chipmunk/CCPhysicsShapeInfo_chipmunk.cpp \
../physics/chipmunk/CCPhysicsBodyInfo_chipmunk.cpp \
../physics/chipmunk/CCPhysicsWorldInfo_chipmunk.cpp \
../physics/CCPhysicsBody.cpp \
../physics/CCPhysicsContact.cpp \
../physics/CCPhysicsShape.cpp \
../physics/CCPhysicsJoint.cpp \
../physics/CCPhysicsWorld.cpp \
../platform/CCSAXParser.cpp \
../platform/CCThread.cpp \
../platform/CCEGLViewProtocol.cpp \
../platform/CCFileUtils.cpp \
../platform/linux/CCStdC.cpp \
../platform/linux/CCFileUtilsLinux.cpp \
../platform/linux/CCCommon.cpp \
../platform/linux/CCApplication.cpp \
../platform/linux/CCEGLView.cpp \
../platform/linux/CCImage.cpp \
../platform/linux/CCDevice.cpp \
../base/etc1.cpp \
../base/s3tc.cpp \
../base/atitc.cpp \
CCScriptSupport.cpp \
CCAnimation.cpp \
CCAnimationCache.cpp \
CCSprite.cpp \
CCSpriteBatchNode.cpp \
CCSpriteFrame.cpp \
CCSpriteFrameCache.cpp \
ccUTF8.cpp \
CCProfiling.cpp \
CCUserDefault.cpp \
TransformUtils.cpp \
base64.cpp \
ccUtils.cpp \
CCVertex.cpp \
CCNotificationCenter.cpp \
TGAlib.cpp \
../../external/tinyxml2/tinyxml2.cpp \
ZipUtils.cpp \
../../external/unzip/ioapi.cpp \
../../external/unzip/unzip.cpp \
ccCArray.cpp \
CCComponent.cpp \
CCComponentContainer.cpp \
CCIMEDispatcher.cpp \
CCTextFieldTTF.cpp \
CCTexture2D.cpp \
CCTextureAtlas.cpp \
CCTextureCache.cpp \
CCParallaxNode.cpp \
CCTMXLayer.cpp \
CCTMXObjectGroup.cpp \
CCTMXTiledMap.cpp \
CCTMXXMLParser.cpp \
CCTileMapAtlas.cpp \
CCGLProgram.cpp \
ccGLStateCache.cpp \
CCShaderCache.cpp \
ccShaders.cpp \
../math/kazmath/src/aabb.c \
../math/kazmath/src/plane.c \
../math/kazmath/src/vec2.c \
../math/kazmath/src/mat3.c \
../math/kazmath/src/quaternion.c \
../math/kazmath/src/vec3.c \
../math/kazmath/src/mat4.c \
../math/kazmath/src/ray2.c \
../math/kazmath/src/vec4.c \
../math/kazmath/src/neon_matrix_impl.c \
../math/kazmath/src/utility.c \
../math/kazmath/src/GL/mat4stack.c \
../math/kazmath/src/GL/matrix.c \
CCCamera.cpp \
CCConfiguration.cpp \
CCDirector.cpp \
CCScheduler.cpp \
ccFPSImages.c \
ccTypes.cpp \
cocos2d.cpp \
CCDeprecated.cpp

COCOS_ROOT = ../..

include cocos2dx.mk

CXXFLAGS += -Wno-sequence-point
CCFLAGS += -Wno-sequence-point

STATICLIBS += $(LIB_DIR)/libchipmunk.a

TARGET := $(LIB_DIR)/$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -shared -o $@ $(SHAREDLIBS) $(STATICLIBS) $(LIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@



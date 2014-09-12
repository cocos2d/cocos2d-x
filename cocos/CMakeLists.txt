#/****************************************************************************
# Copyright (c) 2013 cocos2d-x.org
# Copyright (c) 2014 martell malone
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

# this CMakeLists is to generate libcocos2d.a

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/platform/desktop
  ${CMAKE_CURRENT_SOURCE_DIR}/platform
  ${CMAKE_CURRENT_SOURCE_DIR}/audio/include
  ${CMAKE_CURRENT_SOURCE_DIR}/editor-support
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/tinyxml2
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/unzip
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/edtaa3func
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/chipmunk/include/chipmunk
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/jpeg/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/png/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/tiff/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/webp/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw3/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/freetype2/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/websockets/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/xxhash
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/ConvertUTF
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/${PLATFORM_FOLDER}-specific/fmod/include/${ARCH_DIR}
)


#
# cocos2d source files and header files
#
# From CMake page:
# We do not recommend using GLOB to collect a list of source files from your source tree. 
# If no CMakeLists.txt file changes when a source is added or removed then the generated
# build system cannot know when to ask CMake to regenerate.)

set(COCOS2D_BASE_SRC

    cocos2d.cpp

    base/ccFPSImages.c
    base/CCAutoreleasePool.cpp
    base/CCCamera.cpp
    base/CCConfiguration.cpp
    base/CCConsole.cpp
    base/CCController-android.cpp
    base/CCController.cpp
    base/CCData.cpp
    base/CCDataVisitor.cpp
    base/CCDirector.cpp
    base/CCEvent.cpp
    base/CCEventAcceleration.cpp
    base/CCEventController.cpp
    base/CCEventCustom.cpp
    base/CCEventDispatcher.cpp
    base/CCEventFocus.cpp
    base/CCEventKeyboard.cpp
    base/CCEventListener.cpp
    base/CCEventListenerAcceleration.cpp
    base/CCEventListenerController.cpp
    base/CCEventListenerCustom.cpp
    base/CCEventListenerFocus.cpp
    base/CCEventListenerKeyboard.cpp
    base/CCEventListenerMouse.cpp
    base/CCEventListenerTouch.cpp
    base/CCEventMouse.cpp
    base/CCEventTouch.cpp
    base/CCIMEDispatcher.cpp
    base/CCNS.cpp
    base/CCProfiling.cpp
    base/CCRef.cpp
    base/CCScheduler.cpp
    base/CCScriptSupport.cpp
    base/CCTouch.cpp
    base/CCUserDefault.cpp
    base/CCUserDefault-android.cpp
    base/CCValue.cpp
    base/ObjectFactory.cpp
    base/TGAlib.cpp
    base/ZipUtils.cpp
    base/atitc.cpp
    base/base64.cpp
    base/ccCArray.cpp
    base/ccRandom.cpp
    base/ccTypes.cpp
    base/ccUTF8.cpp
    base/ccUtils.cpp
    base/etc1.cpp
    base/pvr.cpp
    base/s3tc.cpp

    2d/CCAction.cpp
    2d/CCActionCamera.cpp
    2d/CCActionCatmullRom.cpp
    2d/CCActionEase.cpp
    2d/CCActionGrid.cpp
    2d/CCActionGrid3D.cpp
    2d/CCActionInstant.cpp
    2d/CCActionInterval.cpp
    2d/CCActionManager.cpp
    2d/CCActionPageTurn3D.cpp
    2d/CCActionProgressTimer.cpp
    2d/CCActionTiledGrid.cpp
    2d/CCActionTween.cpp
    2d/CCAnimation.cpp
    2d/CCAnimationCache.cpp
    2d/CCAtlasNode.cpp
    2d/CCClippingNode.cpp
    2d/CCComponent.cpp
    2d/CCComponentContainer.cpp
    2d/CCDrawNode.cpp
    2d/CCDrawingPrimitives.cpp
    2d/CCFastTMXLayer.cpp
    2d/CCFastTMXTiledMap.cpp
    2d/CCFont.cpp
    2d/CCFontAtlas.cpp
    2d/CCFontAtlasCache.cpp
    2d/CCFontCharMap.cpp
    2d/CCFontFNT.cpp
    2d/CCFontFreeType.cpp
    2d/CCGLBufferedNode.cpp
    2d/CCGrabber.cpp
    2d/CCGrid.cpp
    2d/CCLabel.cpp
    2d/CCLabelAtlas.cpp
    2d/CCLabelBMFont.cpp
    2d/CCLabelTTF.cpp
    2d/CCLabelTextFormatter.cpp
    2d/CCLayer.cpp
    2d/CCMenu.cpp
    2d/CCMenuItem.cpp
    2d/CCMotionStreak.cpp
    2d/CCNode.cpp
    2d/CCNodeGrid.cpp
    2d/CCParallaxNode.cpp
    2d/CCParticleBatchNode.cpp
    2d/CCParticleExamples.cpp
    2d/CCParticleSystem.cpp
    2d/CCParticleSystemQuad.cpp
    2d/CCProgressTimer.cpp
    2d/CCProtectedNode.cpp
    2d/CCRenderTexture.cpp
    2d/CCScene.cpp
    2d/CCSprite.cpp
    2d/CCSpriteBatchNode.cpp
    2d/CCSpriteFrame.cpp
    2d/CCSpriteFrameCache.cpp
    2d/CCTMXLayer.cpp
    2d/CCTMXObjectGroup.cpp
    2d/CCTMXTiledMap.cpp
    2d/CCTMXXMLParser.cpp
    2d/CCTextFieldTTF.cpp
    2d/CCTileMapAtlas.cpp
    2d/CCTransition.cpp
    2d/CCTransitionPageTurn.cpp
    2d/CCTransitionProgress.cpp
    2d/CCTweenFunction.cpp

    3d/CCAABB.cpp
    3d/CCAnimate3D.cpp
    3d/CCAnimation3D.cpp
    3d/CCAttachNode.cpp
    3d/CCBundle3D.cpp
    3d/CCBundleReader.cpp
    3d/CCMesh.cpp
    3d/CCMeshSkin.cpp
    3d/CCMeshVertexIndexData.cpp
    3d/CCOBB.cpp
    3d/CCObjLoader.cpp
    3d/CCRay.cpp
    3d/CCSkeleton3D.cpp
    3d/CCSprite3D.cpp
    3d/CCSprite3DMaterial.cpp
    3d/CCBillBoard.cpp

    network/HttpClient.cpp
    network/SocketIO.cpp
    network/WebSocket.cpp

    ui/CocosGUI.cpp
    ui/UIButton.cpp
    ui/UICheckBox.cpp
    ui/UIDeprecated.cpp
    ui/UIHBox.cpp
    ui/UIHelper.cpp
    ui/UIImageView.cpp
    ui/UILayout.cpp
    ui/UILayoutManager.cpp
    ui/UILayoutParameter.cpp
    ui/UIListView.cpp
    ui/UILoadingBar.cpp
    ui/UIPageView.cpp
    ui/UIRelativeBox.cpp
    ui/UIRichText.cpp
    ui/UIScale9Sprite.cpp
    ui/UIScrollView.cpp
    ui/UISlider.cpp
    ui/UIText.cpp
    ui/UITextAtlas.cpp
    ui/UITextBMFont.cpp
    ui/UITextField.cpp
    ui/UIVBox.cpp
    ui/UIVideoPlayer-android.cpp
    ui/UIWebView.cpp
    ui/UIWebViewImpl-android.cpp
    ui/UIWidget.cpp
    ui/UIEditBox/UIEditBox.cpp
    ui/UIEditBox/UIEditBoxImpl-android.cpp
    ui/UIEditBox/UIEditBoxImpl-stub.cpp
    ui/UIEditBox/UIEditBoxImpl-win32.cpp
    ui/UIEditBox/UIEditBoxImpl-wp8.cpp

    math/CCAffineTransform.cpp
    math/CCGeometry.cpp
    math/CCVertex.cpp
    math/Mat4.cpp
    math/MathUtil.cpp
    math/Quaternion.cpp
    math/TransformUtils.cpp
    math/Vec2.cpp
    math/Vec3.cpp
    math/Vec4.cpp

    renderer/CCBatchCommand.cpp
    renderer/CCCustomCommand.cpp
    renderer/CCGLProgram.cpp
    renderer/CCGLProgramCache.cpp
    renderer/CCGLProgramState.cpp
    renderer/CCGLProgramStateCache.cpp
    renderer/CCGroupCommand.cpp
    renderer/CCMeshCommand.cpp
    renderer/CCPrimitive.cpp
    renderer/CCPrimitiveCommand.cpp
    renderer/CCQuadCommand.cpp
    renderer/CCRenderCommand.cpp
    renderer/CCRenderer.cpp
    renderer/CCTexture2D.cpp
    renderer/CCTextureAtlas.cpp
    renderer/CCTextureCache.cpp
    renderer/CCTrianglesCommand.cpp
    renderer/CCVertexIndexBuffer.cpp
    renderer/CCVertexIndexData.cpp
    renderer/ccGLStateCache.cpp
    renderer/ccShaders.cpp

    deprecated/CCArray.cpp
    deprecated/CCDeprecated.cpp
    deprecated/CCDictionary.cpp
    deprecated/CCNotificationCenter.cpp
    deprecated/CCSet.cpp
    deprecated/CCString.cpp

    physics/CCPhysicsBody.cpp
    physics/CCPhysicsContact.cpp
    physics/CCPhysicsJoint.cpp
    physics/CCPhysicsShape.cpp
    physics/CCPhysicsWorld.cpp
    physics/chipmunk/CCPhysicsBodyInfo_chipmunk.cpp
    physics/chipmunk/CCPhysicsContactInfo_chipmunk.cpp
    physics/chipmunk/CCPhysicsJointInfo_chipmunk.cpp
    physics/chipmunk/CCPhysicsShapeInfo_chipmunk.cpp
    physics/chipmunk/CCPhysicsWorldInfo_chipmunk.cpp

    platform/CCFileUtils.cpp
    platform/CCGLView.cpp
    platform/CCImage.cpp
    platform/CCSAXParser.cpp
    platform/CCThread.cpp

    storage/local-storage/LocalStorage.cpp
    storage/local-storage/LocalStorage-android.cpp
    )

if(MACOSX)
  set(COCOS2D_BASE_SRC
    ${COCOS2D_BASE_SRC}
    ui/UIEditBox/UIEditBoxImpl-ios.mm
    ui/UIEditBox/UIEditBoxImpl-mac.mm
    base/CCUserDefault-apple.mm
  )
endif()

set(COCOS2D_EDITOR_SUPPORT_SRC
    editor-support/cocosbuilder/CCBAnimationManager.cpp
    editor-support/cocosbuilder/CCBFileLoader.cpp
    editor-support/cocosbuilder/CCBKeyframe.cpp
    editor-support/cocosbuilder/CCBReader.cpp
    editor-support/cocosbuilder/CCBSequence.cpp
    editor-support/cocosbuilder/CCBSequenceProperty.cpp
    editor-support/cocosbuilder/CCControlButtonLoader.cpp
    editor-support/cocosbuilder/CCControlLoader.cpp
    editor-support/cocosbuilder/CCLabelBMFontLoader.cpp
    editor-support/cocosbuilder/CCLabelTTFLoader.cpp
    editor-support/cocosbuilder/CCLayerColorLoader.cpp
    editor-support/cocosbuilder/CCLayerGradientLoader.cpp
    editor-support/cocosbuilder/CCLayerLoader.cpp
    editor-support/cocosbuilder/CCMenuItemImageLoader.cpp
    editor-support/cocosbuilder/CCMenuItemLoader.cpp
    editor-support/cocosbuilder/CCNode+CCBRelativePositioning.cpp
    editor-support/cocosbuilder/CCNodeLoader.cpp
    editor-support/cocosbuilder/CCNodeLoaderLibrary.cpp
    editor-support/cocosbuilder/CCParticleSystemQuadLoader.cpp
    editor-support/cocosbuilder/CCScale9SpriteLoader.cpp
    editor-support/cocosbuilder/CCScrollViewLoader.cpp
    editor-support/cocosbuilder/CCSpriteLoader.cpp

    editor-support/spine/Animation.cpp
    editor-support/spine/AnimationState.cpp
    editor-support/spine/AnimationStateData.cpp
    editor-support/spine/Atlas.cpp
    editor-support/spine/AtlasAttachmentLoader.cpp
    editor-support/spine/Attachment.cpp
    editor-support/spine/AttachmentLoader.cpp
    editor-support/spine/Bone.cpp
    editor-support/spine/BoneData.cpp
    editor-support/spine/BoundingBoxAttachment.cpp
    editor-support/spine/CCSkeleton.cpp
    editor-support/spine/CCSkeletonAnimation.cpp
    editor-support/spine/Event.cpp
    editor-support/spine/EventData.cpp
    editor-support/spine/Json.cpp
    editor-support/spine/RegionAttachment.cpp
    editor-support/spine/Skeleton.cpp
    editor-support/spine/SkeletonBounds.cpp
    editor-support/spine/SkeletonData.cpp
    editor-support/spine/SkeletonJson.cpp
    editor-support/spine/Skin.cpp
    editor-support/spine/Slot.cpp
    editor-support/spine/SlotData.cpp
    editor-support/spine/extension.cpp
    editor-support/spine/spine-cocos2dx.cpp

    editor-support/cocostudio/CCActionFrame.cpp
    editor-support/cocostudio/CCActionFrameEasing.cpp
    editor-support/cocostudio/CCActionManagerEx.cpp
    editor-support/cocostudio/CCActionNode.cpp
    editor-support/cocostudio/CCActionObject.cpp
    editor-support/cocostudio/CCArmature.cpp
    editor-support/cocostudio/CCArmatureAnimation.cpp
    editor-support/cocostudio/CCArmatureDataManager.cpp
    editor-support/cocostudio/CCArmatureDefine.cpp
    editor-support/cocostudio/CCBatchNode.cpp
    editor-support/cocostudio/CCBone.cpp
    editor-support/cocostudio/CCColliderDetector.cpp
    editor-support/cocostudio/CCComAttribute.cpp
    editor-support/cocostudio/CCComAudio.cpp
    editor-support/cocostudio/CCComController.cpp
    editor-support/cocostudio/CCComRender.cpp
    editor-support/cocostudio/CCDataReaderHelper.cpp
    editor-support/cocostudio/CCDatas.cpp
    editor-support/cocostudio/CCDecorativeDisplay.cpp
    editor-support/cocostudio/CCDisplayFactory.cpp
    editor-support/cocostudio/CCDisplayManager.cpp
    editor-support/cocostudio/CCInputDelegate.cpp
    editor-support/cocostudio/CCProcessBase.cpp
    editor-support/cocostudio/CCSGUIReader.cpp
    editor-support/cocostudio/CCSSceneReader.cpp
    editor-support/cocostudio/CCSkin.cpp
    editor-support/cocostudio/CCSpriteFrameCacheHelper.cpp
    editor-support/cocostudio/CCTransformHelp.cpp
    editor-support/cocostudio/CCTween.cpp
    editor-support/cocostudio/CCUtilMath.cpp
    editor-support/cocostudio/CocoLoader.cpp
    editor-support/cocostudio/DictionaryHelper.cpp
    editor-support/cocostudio/TriggerBase.cpp
    editor-support/cocostudio/TriggerMng.cpp
    editor-support/cocostudio/TriggerObj.cpp
    editor-support/cocostudio/WidgetReader/WidgetReader.cpp
    editor-support/cocostudio/WidgetReader/LoadingBarReader/LoadingBarReader.cpp
    editor-support/cocostudio/WidgetReader/ListViewReader/ListViewReader.cpp
    editor-support/cocostudio/WidgetReader/TextFieldReader/TextFieldReader.cpp
    editor-support/cocostudio/WidgetReader/WidgetReader.cpp
    editor-support/cocostudio/WidgetReader/CheckBoxReader/CheckBoxReader.cpp
    editor-support/cocostudio/WidgetReader/SliderReader/SliderReader.cpp
    editor-support/cocostudio/WidgetReader/PageViewReader/PageViewReader.cpp
    editor-support/cocostudio/WidgetReader/TextReader/TextReader.cpp
    editor-support/cocostudio/WidgetReader/TextAtlasReader/TextAtlasReader.cpp
    editor-support/cocostudio/WidgetReader/LayoutReader/LayoutReader.cpp
    editor-support/cocostudio/WidgetReader/TextBMFontReader/TextBMFontReader.cpp
    editor-support/cocostudio/WidgetReader/ImageViewReader/ImageViewReader.cpp
    editor-support/cocostudio/WidgetReader/ButtonReader/ButtonReader.cpp
    editor-support/cocostudio/WidgetReader/ScrollViewReader/ScrollViewReader.cpp
    editor-support/cocostudio/ActionTimeline/CCActionTimelineCache.cpp
    editor-support/cocostudio/ActionTimeline/CCActionTimeline.cpp
    editor-support/cocostudio/ActionTimeline/CCFrame.cpp
    editor-support/cocostudio/ActionTimeline/CCNodeReader.cpp
    editor-support/cocostudio/ActionTimeline/CCTimeLine.cpp
    )

if(LINUX)
    set(COCOS2D_AUDIO_SRC
        audio/linux/FmodAudioPlayer.cpp
        audio/linux/SimpleAudioEngineFMOD.cpp
        )
elseif(MACOSX)
    # split it in _C and non C
    # because C files needs to be compiled with C compiler and not C++
    # compiler
    set(COCOS2D_AUDIO_SRC_C
        audio/mac/CDAudioManager.m
        audio/mac/CDOpenALSupport.m
        audio/mac/CocosDenshion.m
        audio/mac/SimpleAudioEngine_objc.m
       )
    set(COCOS2D_AUDIO_SRC
        ${COCOS2D_AUDIO_SRC_C}
        audio/mac/SimpleAudioEngine.mm
        audio/mac/CDXMacOSXSupport.mm
       )
    SET_SOURCE_FILES_PROPERTIES(
        ${COCOS2D_AUDIO_SRC_C}
        PROPERTIES LANGUAGE C
    )
else()
    message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

# For external projects, leave one empty line
# between projects
set(COCOS2D_EXTERNAL_SRC
    ../external/tinyxml2/tinyxml2.cpp

    ../external/xxhash/xxhash.c

    ../external/unzip/ioapi.cpp
    ../external/unzip/unzip.cpp

    ../external/edtaa3func/edtaa3func.cpp

    ../external/ConvertUTF/ConvertUTF.c
    ../external/ConvertUTF/ConvertUTFWrapper.cpp
    )

set(COCOS2D_DESKTOP_SRC
    platform/desktop/CCGLViewImpl-desktop.cpp
    )

if(LINUX)
    set(COCOS2D_PLATFORM_SRC
        ${COCOS2D_DESKTOP_SRC}
        platform/linux/CCApplication-linux.cpp
        platform/linux/CCCommon-linux.cpp
        platform/linux/CCDevice-linux.cpp
        platform/linux/CCFileUtils-linux.cpp
        platform/linux/CCStdC-linux.cpp
    )
elseif(MACOSX)
    set(COCOS2D_PLATFORM_SRC
        ${COCOS2D_DESKTOP_SRC}
        platform/mac/CCApplication-mac.mm
        platform/mac/CCCommon-mac.mm
        platform/mac/CCDevice-mac.mm
        platform/apple/CCLock-apple.cpp
        platform/apple/CCFileUtils-apple.mm
        platform/apple/CCThread-apple.mm
        )
else()
    message( FATAL_ERROR "Unsupported architecture, CMake will exit" )
endif()

set(COCOS2D_SRC
    ${COCOS2D_BASE_SRC}
    ${COCOS2D_PLATFORM_SRC}
    ${COCOS2D_EXTERNAL_SRC}
    ${COCOS2D_AUDIO_SRC}
    ${COCOS2D_EDITOR_SUPPORT_SRC}
    )

set(COCOS2D_EXTENSIONS_SRC
    ../extensions/ExtensionDeprecated.cpp
    ../extensions/GUI/CCControlExtension/CCControlButton.cpp
    ../extensions/GUI/CCControlExtension/CCControlColourPicker.cpp
    ../extensions/GUI/CCControlExtension/CCControl.cpp
    ../extensions/GUI/CCControlExtension/CCControlHuePicker.cpp
    ../extensions/GUI/CCControlExtension/CCControlPotentiometer.cpp
    ../extensions/GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp
    ../extensions/GUI/CCControlExtension/CCControlSlider.cpp
    ../extensions/GUI/CCControlExtension/CCControlStepper.cpp
    ../extensions/GUI/CCControlExtension/CCControlSwitch.cpp
    ../extensions/GUI/CCControlExtension/CCControlUtils.cpp
    ../extensions/GUI/CCControlExtension/CCInvocation.cpp
    ../extensions/GUI/CCScrollView/CCScrollView.cpp
    ../extensions/GUI/CCScrollView/CCTableViewCell.cpp
    ../extensions/GUI/CCScrollView/CCTableView.cpp
    ../extensions/assets-manager/AssetsManager.cpp
    ../extensions/physics-nodes/CCPhysicsDebugNode.cpp
    ../extensions/physics-nodes/CCPhysicsSprite.cpp
    )


set(BOX2D_SRC
    ../external/Box2D/Collision/b2BroadPhase.cpp
    ../external/Box2D/Collision/b2CollideCircle.cpp
    ../external/Box2D/Collision/b2CollideEdge.cpp
    ../external/Box2D/Collision/b2CollidePolygon.cpp
    ../external/Box2D/Collision/b2Collision.cpp
    ../external/Box2D/Collision/b2Distance.cpp
    ../external/Box2D/Collision/b2DynamicTree.cpp
    ../external/Box2D/Collision/b2TimeOfImpact.cpp
    ../external/Box2D/Collision/Shapes/b2ChainShape.cpp
    ../external/Box2D/Collision/Shapes/b2CircleShape.cpp
    ../external/Box2D/Collision/Shapes/b2EdgeShape.cpp
    ../external/Box2D/Collision/Shapes/b2PolygonShape.cpp
    ../external/Box2D/Common/b2BlockAllocator.cpp
    ../external/Box2D/Common/b2Draw.cpp
    ../external/Box2D/Common/b2Math.cpp
    ../external/Box2D/Common/b2Settings.cpp
    ../external/Box2D/Common/b2StackAllocator.cpp
    ../external/Box2D/Common/b2Timer.cpp
    ../external/Box2D/Dynamics/b2Body.cpp
    ../external/Box2D/Dynamics/b2ContactManager.cpp
    ../external/Box2D/Dynamics/b2Fixture.cpp
    ../external/Box2D/Dynamics/b2Island.cpp
    ../external/Box2D/Dynamics/b2World.cpp
    ../external/Box2D/Dynamics/b2WorldCallbacks.cpp
    ../external/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
    ../external/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
    ../external/Box2D/Dynamics/Joints/b2GearJoint.cpp
    ../external/Box2D/Dynamics/Joints/b2Joint.cpp
    ../external/Box2D/Dynamics/Joints/b2MotorJoint.cpp
    ../external/Box2D/Dynamics/Joints/b2MouseJoint.cpp
    ../external/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
    ../external/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
    ../external/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
    ../external/Box2D/Dynamics/Joints/b2RopeJoint.cpp
    ../external/Box2D/Dynamics/Joints/b2WeldJoint.cpp
    ../external/Box2D/Dynamics/Joints/b2WheelJoint.cpp
    ../external/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
    ../external/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
    ../external/Box2D/Dynamics/Contacts/b2CircleContact.cpp
    ../external/Box2D/Dynamics/Contacts/b2Contact.cpp
    ../external/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
    ../external/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
    ../external/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
    ../external/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
    ../external/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
    ../external/Box2D/Rope/b2Rope.cpp
    )

add_library(cocos2d STATIC ${COCOS2D_SRC} ${COCOS2D_EXTENSIONS_SRC} ${BOX2D_SRC})

if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set(FMOD_LIB "fmodex64")
elseif ( CMAKE_SIZEOF_VOID_P EQUAL 4 )
    set(FMOD_LIB "fmodex")
else()
    message( FATAL_ERROR "Unsupported architecture, CMake will exit" )
endif()

if(LINUX)
    set(PLATFORM_SPECIFIC_LIBS
        pthread
        fontconfig
        GLEW
        X11
        rt
        glfw
        GL
        ${FMOD_LIB}
        )
elseif(MACOSX)
   INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(OPENGL_LIBRARY OpenGL )
   FIND_LIBRARY(AUDIOTOOLBOX_LIBRARY AudioToolbox)
   FIND_LIBRARY(OPENAL_LIBRARY OpenAL )
   FIND_LIBRARY(QUARTZCORE_LIBRARY QuartzCore )
   FIND_LIBRARY(APPLICATIONSERVICES_LIBRARY ApplicationServices)
   FIND_LIBRARY(IOKIT_LIBRARY IOKit)
   FIND_LIBRARY(FOUNDATION_LIBRARY Foundation)
   set(PLATFORM_SPECIFIC_LIBS
        glfw3
        websockets
        ${COCOA_LIBRARY}
        ${OPENGL_LIBRARY}
        ${OPENAL_LIBRARY}
        ${AUDIOTOOLBOX_LIBRARY}
        ${QUARTZCORE_LIBRARY}
        ${APPLICATIONSERVICES_LIBRARY}
        ${IOKIT_LIBRARY}
        ${FOUNDATION_LIBRARY}
        )
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

target_link_libraries(cocos2d jpeg webp tiff freetype chipmunk png z curl ${PLATFORM_SPECIFIC_LIBS})

set_target_properties(cocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    VERSION ${COCOS2D_X_VERSION}
)


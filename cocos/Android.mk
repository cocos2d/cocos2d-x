LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SHORT_COMMANDS := true

LOCAL_SRC_FILES := \
cocos2d.cpp \
2d/CCAction.cpp \
2d/CCActionCamera.cpp \
2d/CCActionCatmullRom.cpp \
2d/CCActionEase.cpp \
2d/CCActionGrid.cpp \
2d/CCActionGrid3D.cpp \
2d/CCActionInstant.cpp \
2d/CCActionInterval.cpp \
2d/CCActionManager.cpp \
2d/CCActionPageTurn3D.cpp \
2d/CCActionProgressTimer.cpp \
2d/CCActionTiledGrid.cpp \
2d/CCActionTween.cpp \
2d/CCAnimation.cpp \
2d/CCAnimationCache.cpp \
2d/CCAtlasNode.cpp \
2d/CCClippingNode.cpp \
2d/CCComponent.cpp \
2d/CCComponentContainer.cpp \
2d/CCDrawNode.cpp \
2d/CCDrawingPrimitives.cpp \
2d/CCFont.cpp \
2d/CCFontAtlas.cpp \
2d/CCFontAtlasCache.cpp \
2d/CCFontCharMap.cpp \
2d/CCFontFNT.cpp \
2d/CCFontFreeType.cpp \
2d/CCGLBufferedNode.cpp \
2d/CCGrabber.cpp \
2d/CCGrid.cpp \
2d/CCLabel.cpp \
2d/CCLabelAtlas.cpp \
2d/CCLabelBMFont.cpp \
2d/CCLabelTTF.cpp \
2d/CCLabelTextFormatter.cpp \
2d/CCLayer.cpp \
2d/CCMenu.cpp \
2d/CCMenuItem.cpp \
2d/CCMotionStreak.cpp \
2d/CCNode.cpp \
2d/CCNodeGrid.cpp \
2d/CCParallaxNode.cpp \
2d/CCParticleBatchNode.cpp \
2d/CCParticleExamples.cpp \
2d/CCParticleSystem.cpp \
2d/CCParticleSystemQuad.cpp \
2d/CCProgressTimer.cpp \
2d/CCProtectedNode.cpp \
2d/CCRenderTexture.cpp \
2d/CCScene.cpp \
2d/CCSprite.cpp \
2d/CCSpriteBatchNode.cpp \
2d/CCSpriteFrame.cpp \
2d/CCSpriteFrameCache.cpp \
2d/CCTMXLayer.cpp \
2d/CCFastTMXLayer.cpp \
2d/CCTMXObjectGroup.cpp \
2d/CCTMXTiledMap.cpp \
2d/CCFastTMXTiledMap.cpp \
2d/CCTMXXMLParser.cpp \
2d/CCTextFieldTTF.cpp \
2d/CCTileMapAtlas.cpp \
2d/CCTransition.cpp \
2d/CCTransitionPageTurn.cpp \
2d/CCTransitionProgress.cpp \
2d/CCTweenFunction.cpp \
platform/CCGLView.cpp \
platform/CCFileUtils.cpp \
platform/CCSAXParser.cpp \
platform/CCThread.cpp \
platform/CCImage.cpp \
math/CCAffineTransform.cpp \
math/CCGeometry.cpp \
math/CCVertex.cpp \
math/Mat4.cpp \
math/MathUtil.cpp \
math/Quaternion.cpp \
math/TransformUtils.cpp \
math/Vec2.cpp \
math/Vec3.cpp \
math/Vec4.cpp \
base/CCAutoreleasePool.cpp \
base/CCCamera.cpp \
base/CCConfiguration.cpp \
base/CCConsole.cpp \
base/CCData.cpp \
base/CCDataVisitor.cpp \
base/CCDirector.cpp \
base/CCEvent.cpp \
base/CCEventAcceleration.cpp \
base/CCEventCustom.cpp \
base/CCEventDispatcher.cpp \
base/CCEventFocus.cpp \
base/CCEventKeyboard.cpp \
base/CCEventController.cpp \
base/CCEventListener.cpp \
base/CCEventListenerController.cpp \
base/CCEventListenerAcceleration.cpp \
base/CCEventListenerCustom.cpp \
base/CCEventListenerFocus.cpp \
base/CCEventListenerKeyboard.cpp \
base/CCEventListenerMouse.cpp \
base/CCEventListenerTouch.cpp \
base/CCEventMouse.cpp \
base/CCEventTouch.cpp \
base/CCIMEDispatcher.cpp \
base/CCNS.cpp \
base/CCProfiling.cpp \
base/ccRandom.cpp \
base/CCRef.cpp \
base/CCScheduler.cpp \
base/CCScriptSupport.cpp \
base/CCTouch.cpp \
base/CCUserDefault.cpp \
base/CCUserDefaultAndroid.cpp \
base/CCValue.cpp \
base/TGAlib.cpp \
base/ZipUtils.cpp \
base/atitc.cpp \
base/base64.cpp \
base/ccCArray.cpp \
base/ccFPSImages.c \
base/ccTypes.cpp \
base/ccUTF8.cpp \
base/ccUtils.cpp \
base/etc1.cpp \
base/pvr.cpp \
base/s3tc.cpp \
base/CCController.cpp \
base/CCController-android.cpp \
base/ObjectFactory.cpp \
renderer/CCBatchCommand.cpp \
renderer/CCCustomCommand.cpp \
renderer/CCGLProgram.cpp \
renderer/CCGLProgramCache.cpp \
renderer/CCGLProgramState.cpp \
renderer/CCGLProgramStateCache.cpp \
renderer/CCGroupCommand.cpp \
renderer/CCQuadCommand.cpp \
renderer/CCMeshCommand.cpp \
renderer/CCRenderCommand.cpp \
renderer/CCRenderer.cpp \
renderer/CCTexture2D.cpp \
renderer/CCTextureAtlas.cpp \
renderer/CCTextureCache.cpp \
renderer/ccGLStateCache.cpp \
renderer/ccShaders.cpp \
renderer/CCVertexIndexBuffer.cpp \
renderer/CCVertexIndexData.cpp \
renderer/CCPrimitive.cpp \
renderer/CCPrimitiveCommand.cpp \
deprecated/CCArray.cpp \
deprecated/CCSet.cpp \
deprecated/CCString.cpp \
deprecated/CCDictionary.cpp \
deprecated/CCDeprecated.cpp \
deprecated/CCNotificationCenter.cpp \
physics/CCPhysicsBody.cpp \
physics/CCPhysicsContact.cpp \
physics/CCPhysicsJoint.cpp \
physics/CCPhysicsShape.cpp \
physics/CCPhysicsWorld.cpp \
physics/chipmunk/CCPhysicsBodyInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsContactInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsJointInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsShapeInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsWorldInfo_chipmunk.cpp \
../external/ConvertUTF/ConvertUTFWrapper.cpp \
../external/ConvertUTF/ConvertUTF.c \
../external/tinyxml2/tinyxml2.cpp \
../external/unzip/ioapi.cpp \
../external/unzip/unzip.cpp \
../external/edtaa3func/edtaa3func.cpp \
../external/xxhash/xxhash.c


#3d
LOCAL_SRC_FILES += 3d/CCRay.cpp \
                   3d/CCAABB.cpp \
                   3d/CCOBB.cpp \
                   3d/CCAnimate3D.cpp \
                   3d/CCAnimation3D.cpp \
                   3d/CCAttachNode.cpp \
                   3d/CCBundle3D.cpp \
                   3d/CCBundleReader.cpp \
                   3d/CCMesh.cpp \
                   3d/CCMeshSkin.cpp \
                   3d/CCMeshVertexIndexData.cpp \
                   3d/CCObjLoader.cpp \
                   3d/CCSkeleton3D.cpp \
                   3d/CCSprite3D.cpp \
                   3d/CCSprite3DMaterial.cpp 


#audio
LOCAL_SRC_FILES += audio/android/cddSimpleAudioEngine.cpp \
                   audio/android/ccdandroidUtils.cpp \
                   audio/android/jni/cddandroidAndroidJavaEngine.cpp

#network
LOCAL_SRC_FILES += network/HttpClient.cpp \
                   network/SocketIO.cpp \
                   network/WebSocket.cpp

#cocosbuilder
LOCAL_SRC_FILES += editor-support/cocosbuilder/CCBAnimationManager.cpp \
                   editor-support/cocosbuilder/CCBFileLoader.cpp \
                   editor-support/cocosbuilder/CCBKeyframe.cpp \
                   editor-support/cocosbuilder/CCBReader.cpp \
                   editor-support/cocosbuilder/CCBSequence.cpp \
                   editor-support/cocosbuilder/CCBSequenceProperty.cpp \
                   editor-support/cocosbuilder/CCControlButtonLoader.cpp \
                   editor-support/cocosbuilder/CCControlLoader.cpp \
                   editor-support/cocosbuilder/CCLabelBMFontLoader.cpp \
                   editor-support/cocosbuilder/CCLabelTTFLoader.cpp \
                   editor-support/cocosbuilder/CCLayerColorLoader.cpp \
                   editor-support/cocosbuilder/CCLayerGradientLoader.cpp \
                   editor-support/cocosbuilder/CCLayerLoader.cpp \
                   editor-support/cocosbuilder/CCMenuItemImageLoader.cpp \
                   editor-support/cocosbuilder/CCMenuItemLoader.cpp \
                   editor-support/cocosbuilder/CCNode+CCBRelativePositioning.cpp \
                   editor-support/cocosbuilder/CCNodeLoader.cpp \
                   editor-support/cocosbuilder/CCNodeLoaderLibrary.cpp \
                   editor-support/cocosbuilder/CCParticleSystemQuadLoader.cpp \
                   editor-support/cocosbuilder/CCScale9SpriteLoader.cpp \
                   editor-support/cocosbuilder/CCScrollViewLoader.cpp \
                   editor-support/cocosbuilder/CCSpriteLoader.cpp

#cocostudio
LOCAL_SRC_FILES += editor-support/cocostudio/CCActionFrame.cpp \
               editor-support/cocostudio/CCActionFrameEasing.cpp \
               editor-support/cocostudio/CCActionManagerEx.cpp \
               editor-support/cocostudio/CCActionNode.cpp \
               editor-support/cocostudio/CCActionObject.cpp \
               editor-support/cocostudio/CCArmature.cpp \
               editor-support/cocostudio/CCBone.cpp \
               editor-support/cocostudio/CCArmatureAnimation.cpp \
               editor-support/cocostudio/CCProcessBase.cpp \
               editor-support/cocostudio/CCTween.cpp \
               editor-support/cocostudio/CCDatas.cpp \
               editor-support/cocostudio/CCBatchNode.cpp \
               editor-support/cocostudio/CCDecorativeDisplay.cpp \
               editor-support/cocostudio/CCDisplayFactory.cpp \
               editor-support/cocostudio/CCDisplayManager.cpp \
               editor-support/cocostudio/CCSkin.cpp \
               editor-support/cocostudio/CCColliderDetector.cpp \
               editor-support/cocostudio/CCArmatureDataManager.cpp \
               editor-support/cocostudio/CCArmatureDefine.cpp \
               editor-support/cocostudio/CCDataReaderHelper.cpp \
               editor-support/cocostudio/CCSpriteFrameCacheHelper.cpp \
               editor-support/cocostudio/CCTransformHelp.cpp \
               editor-support/cocostudio/CCUtilMath.cpp \
               editor-support/cocostudio/CCComAttribute.cpp \
               editor-support/cocostudio/CCComAudio.cpp \
               editor-support/cocostudio/CCComController.cpp \
               editor-support/cocostudio/CCComRender.cpp \
               editor-support/cocostudio/CCInputDelegate.cpp \
               editor-support/cocostudio/DictionaryHelper.cpp \
               editor-support/cocostudio/CCSGUIReader.cpp \
               editor-support/cocostudio/CCSSceneReader.cpp \
               editor-support/cocostudio/TriggerBase.cpp \
               editor-support/cocostudio/TriggerMng.cpp \
               editor-support/cocostudio/TriggerObj.cpp \
               editor-support/cocostudio/CocoLoader.cpp \
               editor-support/cocostudio/WidgetReader/WidgetReader.cpp \
               editor-support/cocostudio/WidgetReader/ButtonReader/ButtonReader.cpp \
               editor-support/cocostudio/WidgetReader/CheckBoxReader/CheckBoxReader.cpp \
               editor-support/cocostudio/WidgetReader/ImageViewReader/ImageViewReader.cpp \
               editor-support/cocostudio/WidgetReader/LayoutReader/LayoutReader.cpp \
               editor-support/cocostudio/WidgetReader/ListViewReader/ListViewReader.cpp \
               editor-support/cocostudio/WidgetReader/LoadingBarReader/LoadingBarReader.cpp \
               editor-support/cocostudio/WidgetReader/PageViewReader/PageViewReader.cpp \
               editor-support/cocostudio/WidgetReader/ScrollViewReader/ScrollViewReader.cpp \
               editor-support/cocostudio/WidgetReader/SliderReader/SliderReader.cpp \
               editor-support/cocostudio/WidgetReader/TextAtlasReader/TextAtlasReader.cpp \
               editor-support/cocostudio/WidgetReader/TextBMFontReader/TextBMFontReader.cpp \
               editor-support/cocostudio/WidgetReader/TextFieldReader/TextFieldReader.cpp \
               editor-support/cocostudio/WidgetReader/TextReader/TextReader.cpp \
               editor-support/cocostudio/ActionTimeline/CCNodeReader.cpp \
               editor-support/cocostudio/ActionTimeline/CCActionTimelineCache.cpp \
               editor-support/cocostudio/ActionTimeline/CCFrame.cpp \
               editor-support/cocostudio/ActionTimeline/CCTimeLine.cpp \
               editor-support/cocostudio/ActionTimeline/CCActionTimeline.cpp

#spine
LOCAL_SRC_FILES += editor-support/spine/Animation.cpp \
                   editor-support/spine/AnimationState.cpp \
                   editor-support/spine/AnimationStateData.cpp \
                   editor-support/spine/Atlas.cpp \
                   editor-support/spine/AtlasAttachmentLoader.cpp \
                   editor-support/spine/Attachment.cpp \
                   editor-support/spine/AttachmentLoader.cpp \
                   editor-support/spine/Bone.cpp \
                   editor-support/spine/BoneData.cpp \
                   editor-support/spine/CCSkeleton.cpp \
                   editor-support/spine/CCSkeletonAnimation.cpp \
                   editor-support/spine/Json.cpp \
                   editor-support/spine/RegionAttachment.cpp \
                   editor-support/spine/Skeleton.cpp \
                   editor-support/spine/SkeletonData.cpp \
                   editor-support/spine/SkeletonJson.cpp \
                   editor-support/spine/Skin.cpp \
                   editor-support/spine/Slot.cpp \
                   editor-support/spine/SlotData.cpp \
                   editor-support/spine/BoundingBoxAttachment.cpp \
                   editor-support/spine/Event.cpp \
                   editor-support/spine/EventData.cpp \
                   editor-support/spine/SkeletonBounds.cpp \
                   editor-support/spine/extension.cpp \
                   editor-support/spine/spine-cocos2dx.cpp

#local-storage
LOCAL_SRC_FILES += storage/local-storage/LocalStorage.cpp \
                   storage/local-storage/LocalStorageAndroid.cpp

#ui
LOCAL_SRC_FILES += ui/UIWidget.cpp \
                   ui/UILayout.cpp \
                   ui/UILayoutParameter.cpp \
                   ui/UILayoutManager.cpp \
                   ui/CocosGUI.cpp \
                   ui/UIHelper.cpp \
                   ui/UIListView.cpp \
                   ui/UIPageView.cpp \
                   ui/UIScrollView.cpp \
                   ui/UIButton.cpp \
                   ui/UICheckBox.cpp \
                   ui/UIImageView.cpp \
                   ui/UIText.cpp \
                   ui/UITextAtlas.cpp \
                   ui/UITextBMFont.cpp \
                   ui/UILoadingBar.cpp \
                   ui/UISlider.cpp \
                   ui/UITextField.cpp \
                   ui/UIRichText.cpp \
                   ui/UIHBox.cpp \
                   ui/UIVBox.cpp \
                   ui/UIRelativeBox.cpp \
                   ui/UIVideoPlayerAndroid.cpp \
                   ui/UIDeprecated.cpp \
		   ui/UIScale9Sprite.cpp \
		   ui/WebView.cpp \
		   ui/WebViewImpl_android.cpp \

#extension
LOCAL_SRC_FILES += ../extensions/assets-manager/AssetsManager.cpp \
                   ../extensions/GUI/CCControlExtension/CCControl.cpp \
                   ../extensions/GUI/CCControlExtension/CCControlButton.cpp \
                   ../extensions/GUI/CCControlExtension/CCControlColourPicker.cpp \
                   ../extensions/GUI/CCControlExtension/CCControlHuePicker.cpp \
                   ../extensions/GUI/CCControlExtension/CCControlPotentiometer.cpp \
                   ../extensions/GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
                   ../extensions/GUI/CCControlExtension/CCControlSlider.cpp \
                   ../extensions/GUI/CCControlExtension/CCControlStepper.cpp \
                   ../extensions/GUI/CCControlExtension/CCControlSwitch.cpp \
                   ../extensions/GUI/CCControlExtension/CCControlUtils.cpp \
                   ../extensions/GUI/CCControlExtension/CCInvocation.cpp \
                   ../extensions/GUI/CCControlExtension/CCScale9Sprite.cpp \
                   ../extensions/GUI/CCEditBox/CCEditBox.cpp \
                   ../extensions/GUI/CCEditBox/CCEditBoxImplAndroid.cpp \
                   ../extensions/GUI/CCEditBox/CCEditBoxImplNone.cpp \
                   ../extensions/GUI/CCEditBox/CCEditBoxImplWin.cpp \
                   ../extensions/GUI/CCScrollView/CCScrollView.cpp \
                   ../extensions/GUI/CCScrollView/CCTableView.cpp \
                   ../extensions/GUI/CCScrollView/CCTableViewCell.cpp \
                   ../extensions/physics-nodes/CCPhysicsDebugNode.cpp \
                   ../extensions/physics-nodes/CCPhysicsSprite.cpp

#box2d
LOCAL_SRC_FILES += ../external/Box2d/Collision/b2BroadPhase.cpp \
                   ../external/Box2d/Collision/b2CollideCircle.cpp \
                   ../external/Box2d/Collision/b2CollideEdge.cpp \
                   ../external/Box2d/Collision/b2CollidePolygon.cpp \
                   ../external/Box2d/Collision/b2Collision.cpp \
                   ../external/Box2d/Collision/b2Distance.cpp \
                   ../external/Box2d/Collision/b2DynamicTree.cpp \
                   ../external/Box2d/Collision/b2TimeOfImpact.cpp \
                   ../external/Box2d/Collision/Shapes/b2ChainShape.cpp \
                   ../external/Box2d/Collision/Shapes/b2CircleShape.cpp \
                   ../external/Box2d/Collision/Shapes/b2EdgeShape.cpp \
                   ../external/Box2d/Collision/Shapes/b2PolygonShape.cpp \
                   ../external/Box2d/Common/b2BlockAllocator.cpp \
                   ../external/Box2d/Common/b2Draw.cpp \
                   ../external/Box2d/Common/b2Math.cpp \
                   ../external/Box2d/Common/b2Settings.cpp \
                   ../external/Box2d/Common/b2StackAllocator.cpp \
                   ../external/Box2d/Common/b2Timer.cpp \
                   ../external/Box2d/Dynamics/b2Body.cpp \
                   ../external/Box2d/Dynamics/b2ContactManager.cpp \
                   ../external/Box2d/Dynamics/b2Fixture.cpp \
                   ../external/Box2d/Dynamics/b2Island.cpp \
                   ../external/Box2d/Dynamics/b2World.cpp \
                   ../external/Box2d/Dynamics/b2WorldCallbacks.cpp \
                   ../external/Box2d/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
                   ../external/Box2d/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
                   ../external/Box2d/Dynamics/Contacts/b2CircleContact.cpp \
                   ../external/Box2d/Dynamics/Contacts/b2Contact.cpp \
                   ../external/Box2d/Dynamics/Contacts/b2ContactSolver.cpp \
                   ../external/Box2d/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
                   ../external/Box2d/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
                   ../external/Box2d/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
                   ../external/Box2d/Dynamics/Contacts/b2PolygonContact.cpp \
                   ../external/Box2d/Dynamics/Joints/b2DistanceJoint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2FrictionJoint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2GearJoint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2Joint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2MotorJoint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2MouseJoint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2PrismaticJoint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2PulleyJoint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2RevoluteJoint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2RopeJoint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2WeldJoint.cpp \
                   ../external/Box2d/Dynamics/Joints/b2WheelJoint.cpp \
                   ../external/Box2d/Rope/b2Rope.cpp

#chipmunk
LOCAL_SRC_FILES += ../external/chipmunk/src/chipmunk.c \
                   ../external/chipmunk/src/cpArbiter.c \
                   ../external/chipmunk/src/cpArray.c \
                   ../external/chipmunk/src/cpBB.c \
                   ../external/chipmunk/src/cpBBTree.c \
                   ../external/chipmunk/src/cpBody.c \
                   ../external/chipmunk/src/cpCollision.c \
                   ../external/chipmunk/src/cpHashSet.c \
                   ../external/chipmunk/src/cpPolyShape.c \
                   ../external/chipmunk/src/cpShape.c \
                   ../external/chipmunk/src/cpSpace.c \
                   ../external/chipmunk/src/cpSpaceComponent.c \
                   ../external/chipmunk/src/cpSpaceHash.c \
                   ../external/chipmunk/src/cpSpaceQuery.c \
                   ../external/chipmunk/src/cpSpaceStep.c \
                   ../external/chipmunk/src/cpSpatialIndex.c \
                   ../external/chipmunk/src/cpSweep1D.c \
                   ../external/chipmunk/src/cpVect.c \
                   ../external/chipmunk/src/constraints/cpConstraint.c \
                   ../external/chipmunk/src/constraints/cpDampedRotarySpring.c \
                   ../external/chipmunk/src/constraints/cpDampedSpring.c \
                   ../external/chipmunk/src/constraints/cpGearJoint.c \
                   ../external/chipmunk/src/constraints/cpGrooveJoint.c \
                   ../external/chipmunk/src/constraints/cpPinJoint.c \
                   ../external/chipmunk/src/constraints/cpPivotJoint.c \
                   ../external/chipmunk/src/constraints/cpRatchetJoint.c \
                   ../external/chipmunk/src/constraints/cpRotaryLimitJoint.c \
                   ../external/chipmunk/src/constraints/cpSimpleMotor.c \
                   ../external/chipmunk/src/constraints/cpSlideJoint.c


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/base \
                    $(LOCAL_PATH)/../external \
                    $(LOCAL_PATH)/../external/tinyxml2 \
                    $(LOCAL_PATH)/../external/unzip \
                    $(LOCAL_PATH)/../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../external/xxhash \
                    $(LOCAL_PATH)/../external/nslog \
                    $(LOCAL_PATH)/audio/include \
                    $(LOCAL_PATH)/editor-support \
                    $(LOCAL_PATH)/storage \
                    $(LOCAL_PATH)/../extensions/GUI/CCControlExtension \
                    $(LOCAL_PATH)/../extensions/GUI/CCScrollView \
                    $(LOCAL_PATH)/../external/chipmunk/include/chipmunk

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/../external \
                    $(LOCAL_PATH)/../external/tinyxml2 \
                    $(LOCAL_PATH)/../external/unzip \
                    $(LOCAL_PATH)/../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../external/edtaa3func \
                    $(LOCAL_PATH)/../external/xxhash \
                    $(LOCAL_PATH)/../external/ConvertUTF \
                    $(LOCAL_PATH)/../external/nslog \
                    $(LOCAL_PATH)/audio/include \
                    $(LOCAL_PATH)/audio/android \
                    $(LOCAL_PATH)/editor-support \
                    $(LOCAL_PATH)/editor-support/cocosbuilder

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz \
                       -landroid

LOCAL_STATIC_LIBRARIES := cocos_freetype2_static
LOCAL_STATIC_LIBRARIES += cocos_curl_static
LOCAL_STATIC_LIBRARIES += libwebsockets_static
LOCAL_STATIC_LIBRARIES += cocos_png_static
LOCAL_STATIC_LIBRARIES += cocos_jpeg_static
LOCAL_STATIC_LIBRARIES += cocos_tiff_static
LOCAL_STATIC_LIBRARIES += cocos_webp_static

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dxandroid_static

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CFLAGS   +=  -std=c99
LOCAL_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat
LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat

include $(BUILD_STATIC_LIBRARY)

$(call import-module,freetype2/prebuilt/android)
$(call import-module,platform/android)
$(call import-module,png/prebuilt/android)
$(call import-module,jpeg/prebuilt/android)
$(call import-module,tiff/prebuilt/android)
$(call import-module,webp/prebuilt/android)
$(call import-module,curl/prebuilt/android)
$(call import-module,websockets/prebuilt/android)

/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __COCOS2D_H__
#define __COCOS2D_H__

// 0x00 HI ME LO
// 00   03 01 00
#define COCOS2D_VERSION 0x00030100

//
// all cocos2d include files
//
#include "2d/ccConfig.h"

// actions
#include "2d/CCAction.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionCamera.h"
#include "2d/CCActionManager.h"
#include "2d/CCActionEase.h"
#include "2d/CCActionPageTurn3D.h"
#include "2d/CCActionGrid.h"
#include "2d/CCActionProgressTimer.h"
#include "2d/CCActionGrid3D.h"
#include "2d/CCActionTiledGrid.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionTween.h"
#include "2d/CCActionCatmullRom.h"
#include "2d/CCTweenFunction.h"

// base_nodes
#include "2d/CCNode.h"
#include "2d/CCAtlasNode.h"

// cocoa
#include "base/CCAffineTransform.h"
#include "base/CCRef.h"
#include "base/CCRefPtr.h"
#include "base/CCVector.h"
#include "base/CCMap.h"
#include "base/CCGeometry.h"
#include "base/CCAutoreleasePool.h"
#include "base/CCNS.h"
#include "base/CCData.h"
#include "base/CCValue.h"

// draw nodes
#include "2d/CCDrawingPrimitives.h"
#include "2d/CCDrawNode.h"

// effects
#include "2d/CCGrabber.h"
#include "2d/CCGrid.h"

// include
#include "2d/CCEventType.h"
#include "2d/CCProtocols.h"
#include "2d/ccConfig.h"
#include "2d/ccMacros.h"
#include "2d/ccTypes.h"

// label_nodes
#include "2d/CCLabelAtlas.h"
#include "2d/CCLabelTTF.h"
#include "2d/CCLabelBMFont.h"
#include "2d/CCLabel.h"
#include "2d/CCFontFNT.h"

// layers_scenes_transitions_nodes
#include "2d/CCLayer.h"
#include "2d/CCScene.h"
#include "2d/CCTransition.h"
#include "2d/CCTransitionPageTurn.h"
#include "2d/CCTransitionProgress.h"

// menu_nodes
#include "2d/CCMenu.h"
#include "2d/CCMenuItem.h"

// misc_nodes
#include "2d/CCClippingNode.h"
#include "2d/CCMotionStreak.h"
#include "2d/CCProgressTimer.h"
#include "2d/CCRenderTexture.h"
#include "2d/CCNodeGrid.h"

// particle_nodes
#include "2d/CCParticleBatchNode.h"
#include "2d/CCParticleSystem.h"
#include "2d/CCParticleExamples.h"
#include "2d/CCParticleSystemQuad.h"

// new renderer
#include "2d/renderer/CCCustomCommand.h"
#include "2d/renderer/CCGroupCommand.h"
#include "2d/renderer/CCMaterialManager.h"
#include "2d/renderer/CCQuadCommand.h"
#include "2d/renderer/CCRenderCommand.h"
#include "2d/renderer/CCRenderCommandPool.h"
#include "2d/renderer/CCRenderMaterial.h"
#include "2d/renderer/CCRenderer.h"

// physics
#include "physics/CCPhysicsBody.h"
#include "physics/CCPhysicsContact.h"
#include "physics/CCPhysicsShape.h"
#include "physics/CCPhysicsJoint.h"
#include "physics/CCPhysicsWorld.h"

// platform
#include "2d/platform/CCDevice.h"
#include "2d/platform/CCCommon.h"
#include "2d/platform/CCFileUtils.h"
#include "2d/platform/CCImage.h"
#include "2d/platform/CCSAXParser.h"
#include "2d/platform/CCThread.h"
#include "base/CCPlatformConfig.h"
#include "base/CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "2d/platform/ios/CCApplication.h"
    #include "2d/platform/ios/CCGLView.h"
    #include "2d/platform/ios/CCGL.h"
    #include "2d/platform/ios/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "2d/platform/android/CCApplication.h"
    #include "2d/platform/android/CCGLView.h"
    #include "2d/platform/android/CCGL.h"
    #include "2d/platform/android/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    #include "2d/platform/blackberry/CCApplication.h"
    #include "2d/platform/blackberry/CCGLView.h"
    #include "2d/platform/blackberry/CCGL.h"
    #include "2d/platform/blackberry/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    #include "2d/platform/win32/CCApplication.h"
    #include "2d/platform/desktop/CCGLView.h"
    #include "2d/platform/win32/CCGL.h"
    #include "2d/platform/win32/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    #include "2d/platform/mac/CCApplication.h"
    #include "2d/platform/desktop/CCGLView.h"
    #include "2d/platform/mac/CCGL.h"
    #include "2d/platform/mac/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    #include "2d/platform/linux/CCApplication.h"
    #include "2d/platform/desktop/CCGLView.h"
    #include "2d/platform/linux/CCGL.h"
    #include "2d/platform/linux/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	#include "2d/platform/winrt/CCApplication.h"
	#include "2d/platform/winrt/CCGLView.h"
	#include "2d/platform/winrt/CCGL.h"
	#include "2d/platform/winrt/CCStdC.h"
	#include "2d/platform/winrt/CCPrecompiledShaders.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WINRT

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	#include "2d/platform/winrt/CCApplication.h"
	#include "2d/platform/wp8/CCGLView.h"
	#include "2d/platform/winrt/CCGL.h"
	#include "2d/platform/winrt/CCStdC.h"
	#include "2d/platform/winrt/CCPrecompiledShaders.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WP8

// script_support
#include "2d/CCScriptSupport.h"

// shaders
#include "2d/CCGLProgram.h"
#include "2d/ccGLStateCache.h"
#include "2d/CCShaderCache.h"
#include "2d/ccShaders.h"

// sprite_nodes
#include "2d/CCAnimation.h"
#include "2d/CCAnimationCache.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteBatchNode.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCSpriteFrameCache.h"

// support
#include "2d/ccUTF8.h"
#include "2d/CCProfiling.h"
#include "base/CCConsole.h"
#include "2d/CCUserDefault.h"
#include "2d/CCVertex.h"

// text_input_node
#include "2d/CCIMEDelegate.h"
#include "2d/CCIMEDispatcher.h"
#include "2d/CCTextFieldTTF.h"

// textures
#include "2d/CCTexture2D.h"
#include "2d/CCTextureAtlas.h"
#include "2d/CCTextureCache.h"

// tilemap_parallax_nodes
#include "2d/CCParallaxNode.h"
#include "2d/CCTMXLayer.h"
#include "2d/CCTMXObjectGroup.h"
#include "2d/CCTMXTiledMap.h"
#include "2d/CCTMXXMLParser.h"
#include "2d/CCTileMapAtlas.h"

// EventDispatcher
#include "2d/CCEventDispatcher.h"
#include "2d/CCEventListenerTouch.h"
#include "2d/CCEventTouch.h"
#include "2d/CCEventListenerKeyboard.h"
#include "2d/CCEventKeyboard.h"
#include "2d/CCEventListenerMouse.h"
#include "2d/CCEventMouse.h"
#include "2d/CCEventAcceleration.h"
#include "2d/CCEventListenerAcceleration.h"
#include "2d/CCEventCustom.h"
#include "2d/CCEventListenerCustom.h"

// root
#include "2d/CCConfiguration.h"
#include "2d/CCDirector.h"
#include "2d/CCScheduler.h"

// component
#include "2d/CCComponent.h"
#include "2d/CCComponentContainer.h"

// Extras
#include "2d/base64.h"
#include "2d/ZipUtils.h"

// Audio
#include "audio/include/SimpleAudioEngine.h"

// Deprecated include
#include "deprecated/CCDictionary.h"
#include "deprecated/CCArray.h"
#include "deprecated/CCSet.h"
#include "deprecated/CCInteger.h"
#include "deprecated/CCFloat.h"
#include "deprecated/CCDouble.h"
#include "deprecated/CCBool.h"
#include "deprecated/CCString.h"
#include "deprecated/CCNotificationCenter.h"
// CCDeprecated.h must be included at the end
#include "deprecated/CCDeprecated.h"


NS_CC_BEGIN

CC_DLL const char* cocos2dVersion();

NS_CC_END

#endif // __COCOS2D_H__

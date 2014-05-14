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
#include "base/ccConfig.h"

// base
#include "base/CCRef.h"
#include "base/CCRefPtr.h"
#include "base/CCVector.h"
#include "base/CCMap.h"
#include "base/CCAutoreleasePool.h"
#include "base/CCNS.h"
#include "base/CCData.h"
#include "base/CCValue.h"
#include "base/ccConfig.h"
#include "base/ccMacros.h"
#include "base/ccTypes.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/base64.h"
#include "base/ZipUtils.h"
#include "base/CCProfiling.h"
#include "base/CCConsole.h"

// EventDispatcher
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventTouch.h"
#include "base/CCEventListenerKeyboard.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventListenerMouse.h"
#include "base/CCEventMouse.h"
#include "base/CCEventAcceleration.h"
#include "base/CCEventListenerAcceleration.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventFocus.h"
#include "base/CCEventListenerFocus.h"

// math
#include "math/CCAffineTransform.h"
#include "math/CCGeometry.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"
#include "math/MathUtil.h"

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

// 2d nodes
#include "2d/CCNode.h"
#include "2d/CCAtlasNode.h"
#include "2d/CCDrawingPrimitives.h"
#include "2d/CCDrawNode.h"
#include "2d/CCLabelAtlas.h"
#include "2d/CCLabelTTF.h"
#include "2d/CCLabelBMFont.h"
#include "2d/CCLabel.h"
#include "2d/CCFontFNT.h"
#include "2d/CCLayer.h"
#include "2d/CCScene.h"
#include "2d/CCTransition.h"
#include "2d/CCTransitionPageTurn.h"
#include "2d/CCTransitionProgress.h"
#include "2d/CCMenu.h"
#include "2d/CCMenuItem.h"
#include "2d/CCClippingNode.h"
#include "2d/CCMotionStreak.h"
#include "2d/CCProgressTimer.h"
#include "2d/CCRenderTexture.h"
#include "2d/CCNodeGrid.h"
#include "2d/CCParticleBatchNode.h"
#include "2d/CCParticleSystem.h"
#include "2d/CCParticleExamples.h"
#include "2d/CCParticleSystemQuad.h"

// 2d utils
#include "2d/CCGrabber.h"
#include "2d/CCGrid.h"

// include
#include "base/CCEventType.h"
#include "2d/CCProtocols.h"

// new renderer
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCRenderCommand.h"
#include "renderer/CCRenderCommandPool.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/ccShaders.h"

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

// sprite_nodes
#include "2d/CCAnimation.h"
#include "2d/CCAnimationCache.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteBatchNode.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCSpriteFrameCache.h"

// support
#include "2d/ccUTF8.h"
#include "2d/CCUserDefault.h"
#include "2d/CCVertex.h"
#include "2d/ccUtils.h"

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

// component
#include "2d/CCComponent.h"
#include "2d/CCComponentContainer.h"

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

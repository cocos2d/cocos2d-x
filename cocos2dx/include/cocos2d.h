/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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
// 00   02 00 00
#define COCOS2D_VERSION 0x00020000

//
// all cocos2d include files
//

#include "ccConfig.h"

// actions
#include "actions/CCAction.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionCamera.h"
#include "actions/CCActionManager.h"
#include "actions/CCActionEase.h"
#include "actions/CCActionPageTurn3D.h"
#include "actions/CCActionGrid.h"
#include "actions/CCActionProgressTimer.h"
#include "actions/CCActionGrid3D.h"
#include "actions/CCActionTiledGrid.h"
#include "actions/CCActionInstant.h"
#include "actions/CCActionTween.h"
#include "actions/CCActionCatmullRom.h"

// base_nodes
#include "base_nodes/CCNode.h"
#include "base_nodes/CCAtlasNode.h"

// cocoa
#include "cocoa/CCAffineTransform.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCGeometry.h"
#include "cocoa/CCSet.h"
#include "cocoa/CCAutoreleasePool.h"
#include "cocoa/CCInteger.h"
#include "cocoa/CCString.h"
#include "cocoa/CCNS.h"
#include "cocoa/CCZone.h"

// effects
#include "effects/CCGrabber.h"
#include "effects/CCGrid.h"

// include
#include "CCEventType.h"
#include "CCProtocols.h"
#include "ccConfig.h"
#include "ccMacros.h"
#include "ccTypes.h"

// kazmath
#include "kazmath/include/kazmath/kazmath.h"
#include "kazmath/include/kazmath/GL/matrix.h"

// keypad_dispatcher
#include "keypad_dispatcher/CCKeypadDelegate.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"

// label_nodes
#include "label_nodes/CCLabelAtlas.h"
#include "label_nodes/CCLabelTTF.h"
#include "label_nodes/CCLabelBMFont.h"

// layers_scenes_transitions_nodes
#include "layers_scenes_transitions_nodes/CCLayer.h"
#include "layers_scenes_transitions_nodes/CCScene.h"
#include "layers_scenes_transitions_nodes/CCTransition.h"
#include "layers_scenes_transitions_nodes/CCTransitionPageTurn.h"
#include "layers_scenes_transitions_nodes/CCTransitionProgress.h"

// menu_nodes
#include "menu_nodes/CCMenu.h"
#include "menu_nodes/CCMenuItem.h"

// misc_nodes
#include "misc_nodes/CCMotionStreak.h"
#include "misc_nodes/CCProgressTimer.h"
#include "misc_nodes/CCRenderTexture.h"

// particle_nodes
#include "particle_nodes/CCParticleBatchNode.h"
#include "particle_nodes/CCParticleSystem.h"
#include "particle_nodes/CCParticleExamples.h"
#include "particle_nodes/CCParticleSystemQuad.h"

// platform

#include "platform/CCCommon.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
#include "platform/CCSAXParser.h"
#include "platform/CCThread.h"
#include "platform/platform.h"
#include "platform/CCPlatformConfig.h"
#include "platform/CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "platform/ios/CCAccelerometer.h"
    #include "platform/ios/CCApplication.h"
    #include "platform/ios/CCEGLView.h"
    #include "platform/ios/CCGL.h"
    #include "platform/ios/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/CCAccelerometer.h"
    #include "platform/android/CCApplication.h"
    #include "platform/android/CCEGLView.h"
    #include "platform/android/CCGL.h"
    #include "platform/android/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#include "platform/win32/CCAccelerometer.h"
	#include "platform/win32/CCApplication.h"
	#include "platform/win32/CCEGLView.h"
	#include "platform/win32/CCGL.h"
	#include "platform/win32/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	#include "platform/mac/CCAccelerometer.h"
	#include "platform/mac/CCApplication.h"
	#include "platform/mac/CCEGLView.h"
	#include "platform/mac/CCGL.h"
	#include "platform/mac/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	#include "platform/linux/CCAccelerometer.h"
	#include "platform/linux/CCApplication.h"
	#include "platform/linux/CCEGLView.h"
	#include "platform/linux/CCGL.h"
	#include "platform/linux/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX


// script_support
#include "script_support/CCScriptSupport.h"

// shaders
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCShaderCache.h"
#include "shaders/ccShaders.h"

// sprite_nodes
#include "sprite_nodes/CCAnimation.h"
#include "sprite_nodes/CCAnimationCache.h"
#include "sprite_nodes/CCSprite.h"
#include "sprite_nodes/CCSpriteBatchNode.h"
#include "sprite_nodes/CCSpriteFrame.h"
#include "sprite_nodes/CCSpriteFrameCache.h"

// support
#include "support/CCNotificationCenter.h"
#include "support/CCPointExtension.h"
#include "support/CCProfiling.h"
#include "support/CCUserDefault.h"
#include "support/CCVertex.h"

// text_input_node
#include "text_input_node/CCIMEDelegate.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "text_input_node/CCTextFieldTTF.h"

// textures
#include "textures/CCTexture2D.h"
#include "textures/CCTextureAtlas.h"
#include "textures/CCTextureCache.h"
#include "textures/CCTexturePVR.h"

// tilemap_parallax_nodes
#include "tilemap_parallax_nodes/CCParallaxNode.h"
#include "tilemap_parallax_nodes/CCTMXLayer.h"
#include "tilemap_parallax_nodes/CCTMXObjectGroup.h"
#include "tilemap_parallax_nodes/CCTMXTiledMap.h"
#include "tilemap_parallax_nodes/CCTMXXMLParser.h"
#include "tilemap_parallax_nodes/CCTileMapAtlas.h"

// touch_dispatcher
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouchHandler.h"

// root
#include "CCCamera.h"
#include "CCConfiguration.h"
#include "CCDirector.h"
#include "CCDrawingPrimitives.h"
#include "CCScheduler.h"

NS_CC_BEGIN

const char* cocos2dVersion();

NS_CC_END

#endif // __COCOS2D_H__

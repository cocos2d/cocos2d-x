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
// 00   03 00 00
#define COCOS2D_VERSION 0x00030000

//
// all cocos2d include files
//
#include "ccConfig.h"

// actions
#include "CCAction.h"
#include "CCActionInterval.h"
#include "CCActionCamera.h"
#include "CCActionManager.h"
#include "CCActionEase.h"
#include "CCActionPageTurn3D.h"
#include "CCActionGrid.h"
#include "CCActionProgressTimer.h"
#include "CCActionGrid3D.h"
#include "CCActionTiledGrid.h"
#include "CCActionInstant.h"
#include "CCActionTween.h"
#include "CCActionCatmullRom.h"

// base_nodes
#include "CCNode.h"
#include "CCAtlasNode.h"

// cocoa
#include "CCAffineTransform.h"
#include "CCDictionary.h"
#include "CCObject.h"
#include "CCArray.h"
#include "CCVector.h"
#include "CCMap.h"
#include "CCGeometry.h"
#include "CCSet.h"
#include "CCAutoreleasePool.h"
#include "CCInteger.h"
#include "CCFloat.h"
#include "CCDouble.h"
#include "CCBool.h"
#include "CCString.h"
#include "CCNS.h"
#include "CCData.h"
#include "CCValue.h"

// draw nodes
#include "CCDrawingPrimitives.h"
#include "CCDrawNode.h"

// effects
#include "CCGrabber.h"
#include "CCGrid.h"

// include
#include "CCEventType.h"
#include "CCProtocols.h"
#include "ccConfig.h"
#include "ccMacros.h"
#include "ccTypes.h"

// label_nodes
#include "CCLabelAtlas.h"
#include "CCLabelTTF.h"
#include "CCLabelBMFont.h"
#include "CCLabel.h"

// layers_scenes_transitions_nodes
#include "CCLayer.h"
#include "CCScene.h"
#include "CCTransition.h"
#include "CCTransitionPageTurn.h"
#include "CCTransitionProgress.h"

// menu_nodes
#include "CCMenu.h"
#include "CCMenuItem.h"

// misc_nodes
#include "CCClippingNode.h"
#include "CCMotionStreak.h"
#include "CCProgressTimer.h"
#include "CCRenderTexture.h"
#include "CCNodeGrid.h"

// particle_nodes
#include "CCParticleBatchNode.h"
#include "CCParticleSystem.h"
#include "CCParticleExamples.h"
#include "CCParticleSystemQuad.h"

// new renderer
#include "renderer/CCCustomCommand.h"
#include "renderer/CCFrustum.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCMaterialManager.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCRenderCommand.h"
#include "renderer/CCRenderCommandPool.h"
#include "renderer/CCRenderMaterial.h"
#include "renderer/CCRenderer.h"

// physics
#include "CCPhysicsBody.h"
#include "CCPhysicsContact.h"
#include "CCPhysicsShape.h"
#include "CCPhysicsJoint.h"
#include "CCPhysicsWorld.h"

// kazmath
#include "kazmath/kazmath.h"
#include "kazmath/GL/matrix.h"

// platform
#include "platform/CCDevice.h"
#include "platform/CCCommon.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
#include "platform/CCSAXParser.h"
#include "platform/CCThread.h"
#include "CCPlatformConfig.h"
#include "CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "platform/ios/CCApplication.h"
    #include "platform/ios/CCGLView.h"
    #include "platform/ios/CCGL.h"
    #include "platform/ios/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/CCApplication.h"
    #include "platform/android/CCGLView.h"
    #include "platform/android/CCGL.h"
    #include "platform/android/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    #include "platform/blackberry/CCApplication.h"
    #include "platform/blackberry/CCGLView.h"
    #include "platform/blackberry/CCGL.h"
    #include "platform/blackberry/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    #include "platform/win32/CCApplication.h"
    #include "platform/desktop/CCGLView.h"
    #include "platform/win32/CCGL.h"
    #include "platform/win32/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    #include "platform/mac/CCApplication.h"
    #include "platform/desktop/CCGLView.h"
    #include "platform/mac/CCGL.h"
    #include "platform/mac/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    #include "platform/linux/CCApplication.h"
    #include "platform/desktop/CCGLView.h"
    #include "platform/linux/CCGL.h"
    #include "platform/linux/CCStdC.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

// script_support
#include "CCScriptSupport.h"

// shaders
#include "CCGLProgram.h"
#include "ccGLStateCache.h"
#include "CCShaderCache.h"
#include "ccShaders.h"

// sprite_nodes
#include "CCAnimation.h"
#include "CCAnimationCache.h"
#include "CCSprite.h"
#include "CCSpriteBatchNode.h"
#include "CCSpriteFrame.h"
#include "CCSpriteFrameCache.h"

// support
#include "ccUTF8.h"
#include "CCNotificationCenter.h"
#include "CCProfiling.h"
#include "CCConsole.h"
#include "CCUserDefault.h"
#include "CCVertex.h"

// text_input_node
#include "CCIMEDelegate.h"
#include "CCIMEDispatcher.h"
#include "CCTextFieldTTF.h"

// textures
#include "CCTexture2D.h"
#include "CCTextureAtlas.h"
#include "CCTextureCache.h"

// tilemap_parallax_nodes
#include "CCParallaxNode.h"
#include "CCTMXLayer.h"
#include "CCTMXObjectGroup.h"
#include "CCTMXTiledMap.h"
#include "CCTMXXMLParser.h"
#include "CCTileMapAtlas.h"

// EventDispatcher
#include "CCEventDispatcher.h"
#include "CCEventListenerTouch.h"
#include "CCEventTouch.h"
#include "CCEventListenerKeyboard.h"
#include "CCEventKeyboard.h"
#include "CCEventListenerMouse.h"
#include "CCEventMouse.h"
#include "CCEventAcceleration.h"
#include "CCEventListenerAcceleration.h"
#include "CCEventCustom.h"
#include "CCEventListenerCustom.h"

// root
#include "CCConfiguration.h"
#include "CCDirector.h"
#include "CCScheduler.h"

// component
#include "CCComponent.h"
#include "CCComponentContainer.h"

// Deprecated include
#include "CCDeprecated.h"

NS_CC_BEGIN

CC_DLL const char* cocos2dVersion();

NS_CC_END

#endif // __COCOS2D_H__

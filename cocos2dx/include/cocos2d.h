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

// base_nodes
#include "CCNode.h"
#include "CCAtlasNode.h"

// cocoa
#include "CCAffineTransform.h"
#include "CCDictionary.h"
#include "CCObject.h"
#include "CCArray.h"
#include "CCGeometry.h"
#include "CCSet.h"
#include "CCAutoreleasePool.h"
#include "CCInteger.h"
#include "CCString.h"
#include "CCData.h"
#include "CCNS.h"
#include "CCZone.h"

// effects
#include "CCGrabber.h"
#include "CCGrid.h"

// include
#include "CCEventType.h"
#include "CCProtocols.h"
#include "ccConfig.h"
#include "ccMacros.h"
#include "ccTypes.h"
#include "cocos2dExt.h"

// kazmath
#include "kazmath/kazmath.h"
#include "kazmath/GL/matrix.h"

// keypad_dispatcher
#include "CCKeypadDelegate.h"
#include "CCKeypadDispatcher.h"

// label_nodes
#include "CCLabelAtlas.h"
#include "CCLabelTTF.h"
#include "CCLabelBMFont.h"

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
#include "CCMotionStreak.h"
#include "CCProgressTimer.h"
#include "CCRenderTexture.h"

// particle_nodes
#include "CCParticleBatchNode.h"
#include "CCParticleSystem.h"
#include "CCParticleExamples.h"
#include "CCParticleSystemQuad.h"

// platform
#include "CCAccelerometer.h"
#include "CCApplication.h"
#include "CCEGLView.h"
#include "CCGL.h"
#include "CCCommon.h"
#include "CCFileUtils.h"
#include "CCImage.h"
#include "CCSAXParser.h"
#include "CCStdC.h"
#include "CCThread.h"
#include "platform.h"

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
#include "CCPointExtension.h"
#include "CCProfiling.h"
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
#include "CCTexturePVR.h"

// tileMap_parallax_nodes
#include "CCParallaxNode.h"
#include "CCTMXLayer.h"
#include "CCTMXObjectGroup.h"
#include "CCTMXTiledMap.h"
#include "CCTMXXMLParser.h"
#include "CCTileMapAtlas.h"

// touch_dispatcher
#include "CCTouch.h"
#include "CCTouchDelegateProtocol.h"
#include "CCTouchDispatcher.h"
#include "CCTouchHandler.h"

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

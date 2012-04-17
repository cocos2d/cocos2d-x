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
// 00   01 00 01
#define COCOS2D_VERSION 0x00010001

//
// all cocos2d include files
//

#include "ccConfig.h"	// should be included first
#include "CCAction.h"
#include "CCAnimation.h"
#include "CCAnimationCache.h"
#include "CCActionManager.h"
#include "CCCamera.h"
#include "CCActionCamera.h"
#include "CCProtocols.h"
#include "CCNode.h"
#include "CCDirector.h"
#include "CCUserDefault.h"
#include "CCActionInstant.h"
#include "CCActionInterval.h"
#include "CCActionEase.h"
#include "CCLabelTTF.h"
#include "CCLayer.h"
#include "CCMenu.h"
#include "CCMenuItem.h"
#include "CCParticleSystem.h"
#include "CCParticleSystemPoint.h"
#include "CCParticleSystemQuad.h"
#include "CCParticleExamples.h"
#include "CCScene.h"
#include "CCSprite.h"
#include "CCSpriteFrameCache.h"
#include "CCTextureCache.h"
#include "CCTransition.h"
#include "CCTextureAtlas.h"
#include "CCLabelAtlas.h"
#include "CCAtlasNode.h"
#include "CCActionTiledGrid.h"
#include "CCActionGrid3D.h"
#include "CCActionGrid.h"
#include "CCLabelBMFont.h"
#include "CCParallaxNode.h"
#include "CCTileMapAtlas.h"
#include "CCTMXTiledMap.h"
#include "CCTMXLayer.h"
#include "CCTMXObjectGroup.h"
#include "CCTMXXMLParser.h"
#include "CCRenderTexture.h"
#include "CCMotionStreak.h"
#include "CCActionPageTurn3D.h"
#include "CCTransitionPageTurn.h"
#include "CCTexture2D.h"
#include "CCTexturePVR.h"
#include "CCTransitionRadial.h"
#include "CCActionProgressTimer.h"
#include "CCTouchHandler.h"
#include "CCTouchDispatcher.h"
#include "CCDrawingPrimitives.h"
#include "CCScheduler.h"

// havn't implement on wophone
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WOPHONE)
#include "CCTextFieldTTF.h"
#endif

//
// cocoa includes
//
#include "CCSet.h"
#include "CCMutableArray.h"
#include "CCMutableDictionary.h"
#include "CCObject.h"
#include "CCZone.h"
#include "CCGeometry.h"
#include "CCAffineTransform.h"
#include "CCTouch.h"
#include "CCPointExtension.h"

//
// platform specific
//
#include "CCApplication.h"
#include "CCEGLView.h"
#include "CCImage.h"
#include "CCFileUtils.h"
#include "CCAccelerometer.h"

// extensions
#include "extensions/CCNotificationCenter.h"

//
// cocos2d macros
//
#include "ccTypes.h"
#include "ccMacros.h"

namespace   cocos2d {

const char* cocos2dVersion();

}//namespace   cocos2d 

#endif // __COCOS2D_H__

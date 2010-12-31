/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "ccConfig.h"	// should be included first
#include "CCAction.h"
#include "CCActionManager.h"
#include "CCCamera.h"
#include "CCActionCamera.h"
#include "CCProtocols.h"
#include "CCNode.h"
#include "CCDirector.h"
// #include "CCTouchDispatcher.h"
// #include "CCTouchDelegateProtocol.h"
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
#include "CCPVRTexture.h"
#include "CCTransitionRadial.h"
#include "CCActionProgressTimer.h"
#include "CCTouchDispatcher.h"
#include "CCDrawingPrimitives.h"
#include "CCScheduler.h"

//
// cocoa includes
//
#include "NSSet.h"
#include "NSMutableArray.h"
#include "NSMutableDictionary.h"
#include "NSObject.h"
#include "NSZone.h"
#include "CGGeometry.h"
#include "CGAffineTransform.h"
#include "selector_protocol.h"
#include "CCTouch.h"
#include "CGPointExtension.h"

//
// platform specific
//
#include "CCXApplication.h"
#include "CCXEGLView.h"
#include "CCXUIImage.h"
#include "CCXFileUtils.h"
#include "CCXUIAccelerometer.h"
 
//
// cocos2d macros
//
#include "ccTypes.h"
#include "ccMacros.h"

namespace   cocos2d {

const char* cocos2dVersion();
}//namespace   cocos2d 

#endif // __COCOS2D_H__

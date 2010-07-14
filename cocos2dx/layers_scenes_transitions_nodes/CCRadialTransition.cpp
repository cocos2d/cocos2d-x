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

#include "CCRadialTransition.h"

using namespace std;


//#import "CCDirector.h"
//#import "CCRadialTransition.h"
//#import "CCRenderTexture.h"
//#import "CCLayer.h"
//#import "CCInstantAction.h"
//#import "Support/CGPointExtension.h"

enum {
	kSceneRadial = 0xc001,
};

CCRadialCCWTransition::CCRadialCCWTransition()
{
	/// @todo
}
CCRadialCCWTransition::~CCRadialCCWTransition()
{
	/// @todo
}

void CCRadialCCWTransition::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

/** @todo no declare in .h
-(CCProgressTimerType) radialType
{
	return kCCProgressTimerTypeRadialCCW;
}*/

void CCRadialCCWTransition::onEnter()
{
	/** @todo
	[super onEnter];
	// create a transparent color layer
	// in which we are going to add our rendertextures
	CGSize size = [[CCDirector sharedDirector] winSize];

	// create the second render texture for outScene
	CCRenderTexture *outTexture = [CCRenderTexture renderTextureWithWidth:size.width height:size.height];
	outTexture.sprite.anchorPoint= ccp(0.5f,0.5f);
	outTexture.position = ccp(size.width/2, size.height/2);
	outTexture.anchorPoint = ccp(0.5f,0.5f);

	// render outScene to its texturebuffer
	[outTexture clear:0 g:0 b:0 a:1];
	[outTexture begin];
	[outScene visit];
	[outTexture end];

	//	Since we've passed the outScene to the texture we don't need it.
	[self hideOutShowIn];

	//	We need the texture in RenderTexture.
	CCProgressTimer *outNode = [CCProgressTimer progressWithTexture:outTexture.sprite.texture];
	// but it's flipped upside down so we flip the sprite
	outNode.sprite.flipY = YES;
	//	Return the radial type that we want to use
	outNode.type = [self radialType];
	outNode.percentage = 100.f;
	outNode.position = ccp(size.width/2, size.height/2);
	outNode.anchorPoint = ccp(0.5f,0.5f);

	// create the blend action
	CCIntervalAction * layerAction = [CCSequence actions:
	[CCProgressFromTo actionWithDuration:duration from:100.f to:0.f],
		[CCCallFunc actionWithTarget:self selector:@selector(finish)],
		nil ];	
	// run the blend action
	[outNode runAction: layerAction];

	// add the layer (which contains our two rendertextures) to the scene
	[self addChild: outNode z:2 tag:kSceneRadial];*/
}


// clean up on exit
void CCRadialCCWTransition::onExit()
{
	// remove our layer and release all containing objects 
	this->removeChildByTag(kSceneRadial, false);
	__super::onExit();
}

/** @todo no declare in .h
-(CCProgressTimerType) radialType
{
	return kCCProgressTimerTypeRadialCW;
}*/



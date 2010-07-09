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

#ifndef __CCTRANSITION_H__
#define __CCTRANSITION_H__

#include "CCScene.h"
class CCIntervalAction;
class CCNode;

/** CCTransitionEaseScene can ease the actions of the scene protocol.
@since v0.8.2
*/
class CCTransitionEaseScene : public NSObject
{
	/** returns the Ease action that will be performed on a linear action.
	@since v0.8.2
	*/
public:
	virtual CCIntervalAction * easeActionWithAction(CCIntervalAction * action);
};

/** Orientation Type used by some transitions
*/
typedef enum {
	/// An horizontal orientation where the Left is nearer
	kOrientationLeftOver = 0,
	/// An horizontal orientation where the Right is nearer
	kOrientationRightOver = 1,
	/// A vertical orientation where the Up is nearer
	kOrientationUpOver = 0,
	/// A vertical orientation where the Bottom is nearer
	kOrientationDownOver = 1,
} tOrientation;

/** Base class for CCTransition scenes
*/
class CCTransitionScene : public CCScene
{

protected:
	CCScene	* m_tInScene;
	CCScene	* m_tOutScene;
	ccTime	m_fDuration;
	BOOL	m_bIsInSceneOnTop;
	BOOL	m_bIsSendCleanupToScene;

public:
	/** creates a base transition with duration and incoming scene */
	static void* transitionWithDurationAndScene(ccTime t, CCScene *scene);

	/** initializes a transition with duration and incoming scene */
	virtual void* initWithDurationAndScene(ccTime t,CCScene* scene);

	/** called after the transition finishes */
	void finish(void);

	/** used by some transitions to hide the outter scene */
	void hideOutShowIn(void);
};

/** A CCTransition that supports orientation like.
* Possible orientation: LeftOver, RightOver, UpOver, DownOver
*/
class CCOrientedTransitionScene : public CCTransitionScene
{
protected:
	tOrientation m_tOrientation;

public:
	/** creates a base transition with duration and incoming scene */
	virtual void* transitionWithDurationAndScene(ccTime t,CCScene* scene, tOrientation orientation);
	/** initializes a transition with duration and incoming scene */
	virtual void* initWithDurationAndScene(ccTime t,CCScene* scene,tOrientation orientation);
};

/** CCRotoZoomTransition:
Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming 
*/
class CCRotoZoomTransition : public CCTransitionScene
{

};

/** CCJumpZoomTransition:
Zoom out and jump the outgoing scene, and then jump and zoom in the incoming 
*/
class CCJumpZoomTransition : public CCTransitionScene
{

};

/** CCMoveInLTransition:
Move in from to the left the incoming scene.
*/
class CCMoveInLTransition : public CCTransitionScene, public CCTransitionEaseScene
{
public:
	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed */
	virtual CCIntervalAction* action(void);
};

/** CCMoveInRTransition:
Move in from to the right the incoming scene.
*/
class CCMoveInRTransition : public CCMoveInLTransition
{

};

/** CCMoveInTTransition:
Move in from to the top the incoming scene.
*/
class CCMoveInTTransition : public CCMoveInLTransition 
{

};

/** CCMoveInBTransition:
Move in from to the bottom the incoming scene.
*/
class CCMoveInBTransition : public CCMoveInLTransition
{

};

/** CCSlideInLTransition:
Slide in the incoming scene from the left border.
*/
class CCSlideInLTransition : public CCTransitionScene, public CCTransitionEaseScene
{
public:
	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed by the incomming and outgoing scene */
	virtual CCIntervalAction* action(void);
};

/** CCSlideInRTransition:
Slide in the incoming scene from the right border.
*/
class CCSlideInRTransition : public CCSlideInLTransition 
{

};

/** CCSlideInBTransition:
Slide in the incoming scene from the bottom border.
*/
class CCSlideInBTransition : public CCSlideInLTransition
{

};

/** CCSlideInTTransition:
Slide in the incoming scene from the top border.
*/
class CCSlideInTTransition : public CCSlideInLTransition
{

};

/**
Shrink the outgoing scene while grow the incoming scene
*/
class CCShrinkGrowTransition : public CCTransitionScene , public CCTransitionEaseScene
{

};

/** CCFlipXTransition:
Flips the screen horizontally.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCFlipXTransition : public CCOrientedTransitionScene
{

};

/** CCFlipYTransition:
Flips the screen vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCFlipYTransition : public CCOrientedTransitionScene
{

};

/** CCFlipAngularTransition:
Flips the screen half horizontally and half vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCFlipAngularTransition : public CCOrientedTransitionScene
{

};

/** CCZoomFlipXTransition:
Flips the screen horizontally doing a zoom out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCZoomFlipXTransition : public CCOrientedTransitionScene
{

};

/** CCZoomFlipYTransition:
Flips the screen vertically doing a little zooming out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCZoomFlipYTransition : public CCOrientedTransitionScene
{

};

/** CCZoomFlipAngularTransition:
Flips the screen half horizontally and half vertically doing a little zooming out/in.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCZoomFlipAngularTransition : public CCOrientedTransitionScene
{

};

/** CCFadeTransition:
Fade out the outgoing scene and then fade in the incoming scene.'''
*/
class CCFadeTransition : public CCTransitionScene
{
protected:
	ccColor4B	color;

public:
	/** creates the transition with a duration and with an RGB color
	* Example: [FadeTransition transitionWithDuration:2 scene:s withColor:ccc3(255,0,0)]; // red color
	*/
	static void* transitionWithDurationAndColor(ccTime duration,CCScene* scene, ccColor3B color);
	/** initializes the transition with a duration and with an RGB color */
	void* initWithDurationAndColor(ccTime duration, CCScene*scene ,ccColor3B color);
};

/**
CCCrossFadeTransition:
Cross fades two scenes using the CCRenderTexture object.
*/
class CCRenderTexture;
class CCCrossFadeTransition : public CCTransitionScene
{

};

/** CCTurnOffTilesTransition:
Turn off the tiles of the outgoing scene in random order
*/
class CCTurnOffTilesTransition : public CCTransitionScene ,public CCTransitionEaseScene
{

};

/** CCSplitColsTransition:
The odd columns goes upwards while the even columns goes downwards.
*/
class CCSplitColsTransition : public CCTransitionScene , public CCTransitionEaseScene
{
public:
	virtual CCIntervalAction* action(void);
};

/** CCSplitRowsTransition:
The odd rows goes to the left while the even rows goes to the right.
*/
class CCSplitRowsTransition : public CCSplitColsTransition
{

};

/** CCFadeTRTransition:
Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner.
*/
class CCFadeTRTransition : public CCTransitionScene , public CCTransitionEaseScene
{
public:
	virtual CCIntervalAction* actionWithSize(ccGridSize size);
};

/** CCFadeBLTransition:
Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner.
*/
class CCFadeBLTransition : public CCFadeTRTransition
{

};

/** CCFadeUpTransition:
* Fade the tiles of the outgoing scene from the bottom to the top.
*/
class CCFadeUpTransition : public CCFadeTRTransition
{

};

/** CCFadeDownTransition:
* Fade the tiles of the outgoing scene from the top to the bottom.
*/
class CCFadeDownTransition : public CCFadeTRTransition
{

};

#endif // __CCTRANSITION_H__
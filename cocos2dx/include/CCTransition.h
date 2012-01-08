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

#ifndef __CCTRANSITION_H__
#define __CCTRANSITION_H__

#include "CCScene.h"
namespace   cocos2d {

//static creation function macro
//c/c++ don't support object creation of using class name
//so, all classes need creation method.
#define DECLEAR_TRANSITIONWITHDURATION(_Type)\
    static _Type* transitionWithDuration(ccTime t, CCScene* scene);

class CCActionInterval;
class CCNode;

/** @brief CCTransitionEaseScene can ease the actions of the scene protocol.
@since v0.8.2
*/
class CC_DLL CCTransitionEaseScene// : public CCObject
{
public:
	/** returns the Ease action that will be performed on a linear action.
	@since v0.8.2
	*/
	virtual CCActionInterval * easeActionWithAction(CCActionInterval * action) = 0;
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

/** @brief Base class for CCTransition scenes
*/
class CC_DLL CCTransitionScene : public CCScene
{

protected:
	CCScene	* m_pInScene;
	CCScene	* m_pOutScene;
	ccTime	m_fDuration;
	bool	m_bIsInSceneOnTop;
	bool	m_bIsSendCleanupToScene;

public:

	CCTransitionScene();
	virtual ~CCTransitionScene();
	virtual void draw();
	virtual void onEnter();
	virtual void onExit();
	virtual void cleanup();

	/** creates a base transition with duration and incoming scene */
	static CCTransitionScene * transitionWithDuration(ccTime t, CCScene *scene);

	/** initializes a transition with duration and incoming scene */
	virtual bool initWithDuration(ccTime t,CCScene* scene);

	/** called after the transition finishes */
	void finish(void);

	/** used by some transitions to hide the outter scene */
	void hideOutShowIn(void);

protected:
	virtual void sceneOrder();
private:
	void setNewScene(ccTime dt);

};

/** @brief A CCTransition that supports orientation like.
* Possible orientation: LeftOver, RightOver, UpOver, DownOver
*/
class CC_DLL CCTransitionSceneOriented : public CCTransitionScene
{
protected:
	tOrientation m_eOrientation;

public:
	CCTransitionSceneOriented();
	virtual ~CCTransitionSceneOriented();

	/** creates a base transition with duration and incoming scene */
	static CCTransitionSceneOriented * transitionWithDuration(ccTime t,CCScene* scene, tOrientation orientation);
	/** initializes a transition with duration and incoming scene */
	virtual bool initWithDuration(ccTime t,CCScene* scene,tOrientation orientation);
};

/** @brief CCTransitionRotoZoom:
Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming 
*/
class CC_DLL CCTransitionRotoZoom : public CCTransitionScene
{
public:
	CCTransitionRotoZoom();
	virtual ~CCTransitionRotoZoom();
	virtual void onEnter();

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionRotoZoom);
};

/** @brief CCTransitionJumpZoom:
Zoom out and jump the outgoing scene, and then jump and zoom in the incoming 
*/
class CC_DLL CCTransitionJumpZoom : public CCTransitionScene
{
public:
	CCTransitionJumpZoom();
	virtual ~CCTransitionJumpZoom();
	virtual void onEnter();

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionJumpZoom);
};

/** @brief CCTransitionMoveInL:
Move in from to the left the incoming scene.
*/
class CC_DLL CCTransitionMoveInL : public CCTransitionScene, public CCTransitionEaseScene
{
public:
	CCTransitionMoveInL();
	virtual ~CCTransitionMoveInL();
	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed */
	virtual CCActionInterval* action(void);

	virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

	virtual void onEnter();

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionMoveInL);
};

/** @brief CCTransitionMoveInR:
Move in from to the right the incoming scene.
*/
class CC_DLL CCTransitionMoveInR : public CCTransitionMoveInL
{
public:
	CCTransitionMoveInR();
	virtual ~CCTransitionMoveInR();
	virtual void initScenes();

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionMoveInR);
};

/** @brief CCTransitionMoveInT:
Move in from to the top the incoming scene.
*/
class CC_DLL CCTransitionMoveInT : public CCTransitionMoveInL 
{
public:
	CCTransitionMoveInT();
	virtual ~CCTransitionMoveInT();
	virtual void initScenes();

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionMoveInT);
};

/** @brief CCTransitionMoveInB:
Move in from to the bottom the incoming scene.
*/
class CC_DLL CCTransitionMoveInB : public CCTransitionMoveInL
{
public:
	CCTransitionMoveInB();
	virtual ~CCTransitionMoveInB();
	virtual void initScenes();

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionMoveInB);
};

/** @brief CCTransitionSlideInL:
Slide in the incoming scene from the left border.
*/
class CC_DLL CCTransitionSlideInL : public CCTransitionScene, public CCTransitionEaseScene
{
public:
	CCTransitionSlideInL();
	virtual ~CCTransitionSlideInL();

	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed by the incomming and outgoing scene */
	virtual CCActionInterval* action(void);

	virtual void onEnter();
	
	virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionSlideInL);
protected:
	virtual void sceneOrder();
};

/** @brief CCTransitionSlideInR:
Slide in the incoming scene from the right border.
*/
class CC_DLL CCTransitionSlideInR : public CCTransitionSlideInL 
{
public:
	CCTransitionSlideInR();
	virtual ~CCTransitionSlideInR();

	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed by the incomming and outgoing scene */
	virtual CCActionInterval* action(void);

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionSlideInR);
protected:
	virtual void sceneOrder();
};

/** @brief CCTransitionSlideInB:
Slide in the incoming scene from the bottom border.
*/
class CC_DLL CCTransitionSlideInB : public CCTransitionSlideInL
{
public:
	CCTransitionSlideInB();
	virtual ~CCTransitionSlideInB();

	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed by the incomming and outgoing scene */
	virtual CCActionInterval* action(void);

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionSlideInB);
protected: 
	virtual void sceneOrder();
};

/** @brief CCTransitionSlideInT:
Slide in the incoming scene from the top border.
*/
class CC_DLL CCTransitionSlideInT : public CCTransitionSlideInL
{
public:
	CCTransitionSlideInT();
	virtual ~CCTransitionSlideInT();

	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed by the incomming and outgoing scene */
	virtual CCActionInterval* action(void);

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionSlideInT);
protected:
	virtual void sceneOrder();
};

/**
@brief Shrink the outgoing scene while grow the incoming scene
*/
class CC_DLL CCTransitionShrinkGrow : public CCTransitionScene , public CCTransitionEaseScene
{
public:
	CCTransitionShrinkGrow();
	virtual ~CCTransitionShrinkGrow();

	virtual void onEnter();
	virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    DECLEAR_TRANSITIONWITHDURATION(CCTransitionShrinkGrow);
};

/** @brief CCTransitionFlipX:
Flips the screen horizontally.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionFlipX : public CCTransitionSceneOriented
{
public:
	CCTransitionFlipX();
	virtual ~CCTransitionFlipX();

	virtual void onEnter();

    static CCTransitionFlipX* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationRightOver);
};

/** @brief CCTransitionFlipY:
Flips the screen vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionFlipY : public CCTransitionSceneOriented
{
public:
	CCTransitionFlipY();
	virtual ~CCTransitionFlipY();

	virtual void onEnter();

    static CCTransitionFlipY* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationUpOver);
};

/** @brief CCTransitionFlipAngular:
Flips the screen half horizontally and half vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionFlipAngular : public CCTransitionSceneOriented
{
public:
	CCTransitionFlipAngular();
	virtual ~CCTransitionFlipAngular();

	virtual void onEnter();

    static CCTransitionFlipAngular* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationRightOver);
};

/** @brief CCTransitionZoomFlipX:
Flips the screen horizontally doing a zoom out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionZoomFlipX : public CCTransitionSceneOriented
{
public:
	CCTransitionZoomFlipX();
	virtual ~CCTransitionZoomFlipX();

	virtual void onEnter();

    static CCTransitionZoomFlipX* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationRightOver);
};

/** @brief CCTransitionZoomFlipY:
Flips the screen vertically doing a little zooming out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionZoomFlipY : public CCTransitionSceneOriented
{
public:
	CCTransitionZoomFlipY();
	virtual ~CCTransitionZoomFlipY();

	virtual void onEnter();

    static CCTransitionZoomFlipY* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationUpOver);
};

/** @brief CCTransitionZoomFlipAngular:
Flips the screen half horizontally and half vertically doing a little zooming out/in.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionZoomFlipAngular : public CCTransitionSceneOriented
{
public:
	CCTransitionZoomFlipAngular();
	virtual ~CCTransitionZoomFlipAngular();

	virtual void onEnter();

    static CCTransitionZoomFlipAngular* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationRightOver);
};

/** @brief CCTransitionFade:
Fade out the outgoing scene and then fade in the incoming scene.'''
*/
class CC_DLL CCTransitionFade : public CCTransitionScene
{
protected:
	ccColor4B	m_tColor;

public:

	CCTransitionFade();
	virtual ~CCTransitionFade();

	/** creates the transition with a duration and with an RGB color
	* Example: FadeTransition::transitionWithDuration(2, scene, ccc3(255,0,0); // red color
	*/
	static CCTransitionFade* transitionWithDuration(ccTime duration,CCScene* scene, const ccColor3B& color = ccBLACK);
	/** initializes the transition with a duration and with an RGB color */
	virtual bool initWithDuration(ccTime t, CCScene*scene ,const ccColor3B& color);

	virtual bool initWithDuration(ccTime t,CCScene* scene); 
	virtual void onEnter();
	virtual void onExit();
};

class CCRenderTexture;
/**
@brief CCTransitionCrossFade:
Cross fades two scenes using the CCRenderTexture object.
*/
class CC_DLL CCTransitionCrossFade : public CCTransitionScene
{
public :
	CCTransitionCrossFade();
	virtual ~CCTransitionCrossFade();

	virtual void draw();
	virtual void onEnter();
	virtual void onExit();

public:
    DECLEAR_TRANSITIONWITHDURATION(CCTransitionCrossFade);
};

/** @brief CCTransitionTurnOffTiles:
Turn off the tiles of the outgoing scene in random order
*/
class CC_DLL CCTransitionTurnOffTiles : public CCTransitionScene ,public CCTransitionEaseScene
{
public :
	CCTransitionTurnOffTiles();
	virtual ~CCTransitionTurnOffTiles();

	virtual void onEnter();
	virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCTransitionTurnOffTiles);
protected:
	virtual void sceneOrder();
};

/** @brief CCTransitionSplitCols:
The odd columns goes upwards while the even columns goes downwards.
*/
class CC_DLL CCTransitionSplitCols : public CCTransitionScene , public CCTransitionEaseScene
{
public:
	CCTransitionSplitCols();
	virtual ~CCTransitionSplitCols();

	virtual CCActionInterval* action(void);
	virtual void onEnter();
	virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCTransitionSplitCols);
};

/** @brief CCTransitionSplitRows:
The odd rows goes to the left while the even rows goes to the right.
*/
class CC_DLL CCTransitionSplitRows : public CCTransitionSplitCols
{
public:
	CCTransitionSplitRows();
	virtual ~CCTransitionSplitRows();

	virtual CCActionInterval* action(void);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCTransitionSplitRows)
};

/** @brief CCTransitionFadeTR:
Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner.
*/
class CC_DLL CCTransitionFadeTR : public CCTransitionScene , public CCTransitionEaseScene
{
public:
	CCTransitionFadeTR();
	virtual ~CCTransitionFadeTR();
	virtual CCActionInterval* actionWithSize(const ccGridSize& size);
	virtual void onEnter();
	virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCTransitionFadeTR)
protected:
	virtual void sceneOrder();
	
};

/** @brief CCTransitionFadeBL:
Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner.
*/
class CC_DLL CCTransitionFadeBL : public CCTransitionFadeTR
{
public:
	CCTransitionFadeBL();
	virtual ~CCTransitionFadeBL();
	virtual CCActionInterval* actionWithSize(const ccGridSize& size);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCTransitionFadeBL)
};

/** @brief CCTransitionFadeUp:
* Fade the tiles of the outgoing scene from the bottom to the top.
*/
class CC_DLL CCTransitionFadeUp : public CCTransitionFadeTR
{
public:
	CCTransitionFadeUp();
	virtual ~CCTransitionFadeUp();
	virtual CCActionInterval* actionWithSize(const ccGridSize& size);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCTransitionFadeUp)
};

/** @brief CCTransitionFadeDown:
* Fade the tiles of the outgoing scene from the top to the bottom.
*/
class CC_DLL CCTransitionFadeDown : public CCTransitionFadeTR
{
public:
	CCTransitionFadeDown();
	virtual ~CCTransitionFadeDown();
	virtual CCActionInterval* actionWithSize(const ccGridSize& size);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCTransitionFadeDown)
};
}//namespace   cocos2d 

#endif // __CCTRANSITION_H__


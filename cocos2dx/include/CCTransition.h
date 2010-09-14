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
namespace   cocos2d {

//static creation function macro
//c/c++ don't support object creation of using class name
//so, all classes need creation method.
#define DECLEAR_TRANSITIONWITHDURATION(_Type)\
    static _Type* transitionWithDuration(ccTime t, CCScene* scene);

class CCIntervalAction;
class CCNode;

/** CCTransitionEaseScene can ease the actions of the scene protocol.
@since v0.8.2
*/
class CCX_DLL CCTransitionEaseScene// : public NSObject
{
	/** returns the Ease action that will be performed on a linear action.
	@since v0.8.2
	*/
public:
	virtual CCIntervalAction * easeActionWithAction(CCIntervalAction * action) = 0;
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
class CCX_DLL CCTransitionScene : public CCScene
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

/** A CCTransition that supports orientation like.
* Possible orientation: LeftOver, RightOver, UpOver, DownOver
*/
class CCX_DLL CCOrientedTransitionScene : public CCTransitionScene
{
protected:
	tOrientation m_eOrientation;

public:
	CCOrientedTransitionScene();
	virtual ~CCOrientedTransitionScene();

	/** creates a base transition with duration and incoming scene */
	static CCOrientedTransitionScene * transitionWithDuration(ccTime t,CCScene* scene, tOrientation orientation);
	/** initializes a transition with duration and incoming scene */
	virtual bool initWithDuration(ccTime t,CCScene* scene,tOrientation orientation);
};

/** CCRotoZoomTransition:
Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming 
*/
class CCX_DLL CCRotoZoomTransition : public CCTransitionScene
{
public:
	CCRotoZoomTransition();
	virtual ~CCRotoZoomTransition();
	virtual void onEnter();

    DECLEAR_TRANSITIONWITHDURATION(CCRotoZoomTransition);
};

/** CCJumpZoomTransition:
Zoom out and jump the outgoing scene, and then jump and zoom in the incoming 
*/
class CCX_DLL CCJumpZoomTransition : public CCTransitionScene
{
public:
	CCJumpZoomTransition();
	virtual ~CCJumpZoomTransition();
	virtual void onEnter();

    DECLEAR_TRANSITIONWITHDURATION(CCJumpZoomTransition);
};

/** CCMoveInLTransition:
Move in from to the left the incoming scene.
*/
class CCX_DLL CCMoveInLTransition : public CCTransitionScene, public CCTransitionEaseScene
{
public:
	CCMoveInLTransition();
	virtual ~CCMoveInLTransition();
	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed */
	virtual CCIntervalAction* action(void);

	virtual CCIntervalAction* easeActionWithAction(CCIntervalAction * action);

	virtual void onEnter();

    DECLEAR_TRANSITIONWITHDURATION(CCMoveInLTransition);
};

/** CCMoveInRTransition:
Move in from to the right the incoming scene.
*/
class CCX_DLL CCMoveInRTransition : public CCMoveInLTransition
{
public:
	CCMoveInRTransition();
	virtual ~CCMoveInRTransition();
	virtual void initScenes();

    DECLEAR_TRANSITIONWITHDURATION(CCMoveInRTransition);
};

/** CCMoveInTTransition:
Move in from to the top the incoming scene.
*/
class CCX_DLL CCMoveInTTransition : public CCMoveInLTransition 
{
public:
	CCMoveInTTransition();
	virtual ~CCMoveInTTransition();
	virtual void initScenes();

    DECLEAR_TRANSITIONWITHDURATION(CCMoveInTTransition);
};

/** CCMoveInBTransition:
Move in from to the bottom the incoming scene.
*/
class CCX_DLL CCMoveInBTransition : public CCMoveInLTransition
{
public:
	CCMoveInBTransition();
	virtual ~CCMoveInBTransition();
	virtual void initScenes();

    DECLEAR_TRANSITIONWITHDURATION(CCMoveInBTransition);
};

/** CCSlideInLTransition:
Slide in the incoming scene from the left border.
*/
class CCX_DLL CCSlideInLTransition : public CCTransitionScene, public CCTransitionEaseScene
{
public:
	CCSlideInLTransition();
	virtual ~CCSlideInLTransition();

	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed by the incomming and outgoing scene */
	virtual CCIntervalAction* action(void);

	virtual void onEnter();
	
	virtual CCIntervalAction* easeActionWithAction(CCIntervalAction * action);

    DECLEAR_TRANSITIONWITHDURATION(CCSlideInLTransition);
protected:
	virtual void sceneOrder();
};

/** CCSlideInRTransition:
Slide in the incoming scene from the right border.
*/
class CCX_DLL CCSlideInRTransition : public CCSlideInLTransition 
{
public:
	CCSlideInRTransition();
	virtual ~CCSlideInRTransition();

	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed by the incomming and outgoing scene */
	virtual CCIntervalAction* action(void);

    DECLEAR_TRANSITIONWITHDURATION(CCSlideInRTransition);
protected:
	virtual void sceneOrder();
};

/** CCSlideInBTransition:
Slide in the incoming scene from the bottom border.
*/
class CCX_DLL CCSlideInBTransition : public CCSlideInLTransition
{
public:
	CCSlideInBTransition();
	virtual ~CCSlideInBTransition();

	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed by the incomming and outgoing scene */
	virtual CCIntervalAction* action(void);

    DECLEAR_TRANSITIONWITHDURATION(CCSlideInBTransition);
protected: 
	virtual void sceneOrder();
};

/** CCSlideInTTransition:
Slide in the incoming scene from the top border.
*/
class CCX_DLL CCSlideInTTransition : public CCSlideInLTransition
{
public:
	CCSlideInTTransition();
	virtual ~CCSlideInTTransition();

	/** initializes the scenes */
	virtual void initScenes(void);
	/** returns the action that will be performed by the incomming and outgoing scene */
	virtual CCIntervalAction* action(void);

    DECLEAR_TRANSITIONWITHDURATION(CCSlideInTTransition);
protected:
	virtual void sceneOrder();
};

/**
Shrink the outgoing scene while grow the incoming scene
*/
class CCX_DLL CCShrinkGrowTransition : public CCTransitionScene , public CCTransitionEaseScene
{
public:
	CCShrinkGrowTransition();
	virtual ~CCShrinkGrowTransition();

	virtual void onEnter();
	virtual CCIntervalAction* easeActionWithAction(CCIntervalAction * action);

    DECLEAR_TRANSITIONWITHDURATION(CCShrinkGrowTransition);
};

/** CCFlipXTransition:
Flips the screen horizontally.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCX_DLL CCFlipXTransition : public CCOrientedTransitionScene
{
public:
	CCFlipXTransition();
	virtual ~CCFlipXTransition();

	virtual void onEnter();

    static CCFlipXTransition* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationRightOver);
};

/** CCFlipYTransition:
Flips the screen vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCX_DLL CCFlipYTransition : public CCOrientedTransitionScene
{
public:
	CCFlipYTransition();
	virtual ~CCFlipYTransition();

	virtual void onEnter();

    static CCFlipYTransition* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationUpOver);
};

/** CCFlipAngularTransition:
Flips the screen half horizontally and half vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCX_DLL CCFlipAngularTransition : public CCOrientedTransitionScene
{
public:
	CCFlipAngularTransition();
	virtual ~CCFlipAngularTransition();

	virtual void onEnter();

    static CCFlipAngularTransition* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationRightOver);
};

/** CCZoomFlipXTransition:
Flips the screen horizontally doing a zoom out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCX_DLL CCZoomFlipXTransition : public CCOrientedTransitionScene
{
public:
	CCZoomFlipXTransition();
	virtual ~CCZoomFlipXTransition();

	virtual void onEnter();

    static CCZoomFlipXTransition* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationRightOver);
};

/** CCZoomFlipYTransition:
Flips the screen vertically doing a little zooming out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCX_DLL CCZoomFlipYTransition : public CCOrientedTransitionScene
{
public:
	CCZoomFlipYTransition();
	virtual ~CCZoomFlipYTransition();

	virtual void onEnter();

    static CCZoomFlipYTransition* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationUpOver);
};

/** CCZoomFlipAngularTransition:
Flips the screen half horizontally and half vertically doing a little zooming out/in.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CCX_DLL CCZoomFlipAngularTransition : public CCOrientedTransitionScene
{
public:
	CCZoomFlipAngularTransition();
	virtual ~CCZoomFlipAngularTransition();

	virtual void onEnter();

    static CCZoomFlipAngularTransition* transitionWithDuration(ccTime t, CCScene* s, tOrientation o = kOrientationRightOver);
};

/** CCFadeTransition:
Fade out the outgoing scene and then fade in the incoming scene.'''
*/
class CCX_DLL CCFadeTransition : public CCTransitionScene
{
protected:
	ccColor4B	m_tColor;

public:

	CCFadeTransition();
	virtual ~CCFadeTransition();

	/** creates the transition with a duration and with an RGB color
	* Example: [FadeTransition transitionWithDuration:2 scene:s withColor:ccc3(255,0,0)]; // red color
	*/
	static CCFadeTransition* transitionWithDuration(ccTime duration,CCScene* scene, ccColor3B color = ccBLACK);
	/** initializes the transition with a duration and with an RGB color */
	virtual bool initWithDuration(ccTime t, CCScene*scene ,ccColor3B color);

	virtual bool initWithDuration(ccTime t,CCScene* scene); 
	virtual void onEnter();
	virtual void onExit();
};

/**
CCCrossFadeTransition:
Cross fades two scenes using the CCRenderTexture object.
*/
class CCRenderTexture;
class CCX_DLL CCCrossFadeTransition : public CCTransitionScene
{
public :
	CCCrossFadeTransition();
	virtual ~CCCrossFadeTransition();

	virtual void draw();
	virtual void onEnter();
	virtual void onExit();

public:
    DECLEAR_TRANSITIONWITHDURATION(CCCrossFadeTransition);
};

/** CCTurnOffTilesTransition:
Turn off the tiles of the outgoing scene in random order
*/
class CCX_DLL CCTurnOffTilesTransition : public CCTransitionScene ,public CCTransitionEaseScene
{
public :
	CCTurnOffTilesTransition();
	virtual ~CCTurnOffTilesTransition();

	virtual void onEnter();
	virtual CCIntervalAction * easeActionWithAction(CCIntervalAction * action);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCTurnOffTilesTransition);
protected:
	virtual void sceneOrder();
};

/** CCSplitColsTransition:
The odd columns goes upwards while the even columns goes downwards.
*/
class CCX_DLL CCSplitColsTransition : public CCTransitionScene , public CCTransitionEaseScene
{
public:
	CCSplitColsTransition();
	virtual ~CCSplitColsTransition();

	virtual CCIntervalAction* action(void);
	virtual void onEnter();
	virtual CCIntervalAction * easeActionWithAction(CCIntervalAction * action);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCSplitColsTransition);
};

/** CCSplitRowsTransition:
The odd rows goes to the left while the even rows goes to the right.
*/
class CCX_DLL CCSplitRowsTransition : public CCSplitColsTransition
{
public:
	CCSplitRowsTransition();
	virtual ~CCSplitRowsTransition();

	virtual CCIntervalAction* action(void);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCSplitRowsTransition)
};

/** CCFadeTRTransition:
Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner.
*/
class CCX_DLL CCFadeTRTransition : public CCTransitionScene , public CCTransitionEaseScene
{
public:
	CCFadeTRTransition();
	virtual ~CCFadeTRTransition();
	virtual CCIntervalAction* actionWithSize(ccGridSize size);
	virtual void onEnter();
	virtual CCIntervalAction* easeActionWithAction(CCIntervalAction * action);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCFadeTRTransition)
protected:
	virtual void sceneOrder();
	
};

/** CCFadeBLTransition:
Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner.
*/
class CCX_DLL CCFadeBLTransition : public CCFadeTRTransition
{
public:
	CCFadeBLTransition();
	virtual ~CCFadeBLTransition();
	virtual CCIntervalAction* actionWithSize(ccGridSize size);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCFadeBLTransition)
};

/** CCFadeUpTransition:
* Fade the tiles of the outgoing scene from the bottom to the top.
*/
class CCX_DLL CCFadeUpTransition : public CCFadeTRTransition
{
public:
	CCFadeUpTransition();
	virtual ~CCFadeUpTransition();
	virtual CCIntervalAction* actionWithSize(ccGridSize size);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCFadeUpTransition)
};

/** CCFadeDownTransition:
* Fade the tiles of the outgoing scene from the top to the bottom.
*/
class CCX_DLL CCFadeDownTransition : public CCFadeTRTransition
{
public:
	CCFadeDownTransition();
	virtual ~CCFadeDownTransition();
	virtual CCIntervalAction* actionWithSize(ccGridSize size);

public:
    DECLEAR_TRANSITIONWITHDURATION(CCFadeDownTransition)
};
}//namespace   cocos2d 

#endif // __CCTRANSITION_H__


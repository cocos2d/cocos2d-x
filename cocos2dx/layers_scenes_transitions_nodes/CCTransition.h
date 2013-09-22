/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup transition
 * @{
 */

//static creation function macro
//c/c++ don't support object creation of using class name
//so, all classes need creation method.

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
	kCCTransitionOrientationLeftOver = 0,
	/// An horizontal orientation where the Right is nearer
	kCCTransitionOrientationRightOver = 1,
	/// A vertical orientation where the Up is nearer
	kCCTransitionOrientationUpOver = 0,
	/// A vertical orientation where the Bottom is nearer
	kCCTransitionOrientationDownOver = 1,
    
	// Deprecated
    //	kOrientationLeftOver = kCCTransitionOrientationLeftOver,
    //	kOrientationRightOver = kCCTransitionOrientationRightOver,
    //	kOrientationUpOver = kCCTransitionOrientationUpOver,
    //	kOrientationDownOver = kCCTransitionOrientationDownOver,
} tOrientation;

/** @brief Base class for CCTransition scenes
*/
class CC_DLL CCTransitionScene : public CCScene
{

protected:
    CCScene    * m_pInScene;
    CCScene    * m_pOutScene;
    float    m_fDuration;
    bool    m_bIsInSceneOnTop;
    bool    m_bIsSendCleanupToScene;

public:
    /**
     *  @js ctor
     */
    CCTransitionScene();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionScene();
    virtual void draw();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onExit();
    virtual void cleanup();

    /** creates a base transition with duration and incoming scene */
    static CCTransitionScene * create(float t, CCScene *scene);

    /** initializes a transition with duration and incoming scene */
    virtual bool initWithDuration(float t,CCScene* scene);

    /** called after the transition finishes */
    void finish(void);

    /** used by some transitions to hide the outer scene */
    void hideOutShowIn(void);

protected:
    virtual void sceneOrder();
private:
    void setNewScene(float dt);

};

/** @brief A CCTransition that supports orientation like.
* Possible orientation: LeftOver, RightOver, UpOver, DownOver
*/
class CC_DLL CCTransitionSceneOriented : public CCTransitionScene
{
protected:
    tOrientation m_eOrientation;

public:
    /**
     *  @js ctor
     */
    CCTransitionSceneOriented();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionSceneOriented();

    /** creates a base transition with duration and incoming scene */
    static CCTransitionSceneOriented * create(float t,CCScene* scene, tOrientation orientation);

    /** initializes a transition with duration and incoming scene */
    virtual bool initWithDuration(float t,CCScene* scene,tOrientation orientation);
};

/** @brief CCTransitionRotoZoom:
Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming 
*/
class CC_DLL CCTransitionRotoZoom : public CCTransitionScene
{
public:
    /**
     *  @js ctor
     */
    CCTransitionRotoZoom();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionRotoZoom();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCTransitionRotoZoom* create(float t, CCScene* scene);
};

/** @brief CCTransitionJumpZoom:
Zoom out and jump the outgoing scene, and then jump and zoom in the incoming 
*/
class CC_DLL CCTransitionJumpZoom : public CCTransitionScene
{
public:
    /**
     *  @js ctor
     */
    CCTransitionJumpZoom();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionJumpZoom();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCTransitionJumpZoom* create(float t, CCScene* scene);
};

/** @brief CCTransitionMoveInL:
Move in from to the left the incoming scene.
*/
class CC_DLL CCTransitionMoveInL : public CCTransitionScene, public CCTransitionEaseScene
{
public:
    /**
     *  @js ctor
     */
    CCTransitionMoveInL();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionMoveInL();
    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed */
    virtual CCActionInterval* action(void);

    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCTransitionMoveInL* create(float t, CCScene* scene);
};

/** @brief CCTransitionMoveInR:
Move in from to the right the incoming scene.
*/
class CC_DLL CCTransitionMoveInR : public CCTransitionMoveInL
{
public:
    /**
     *  @js ctor
     */
    CCTransitionMoveInR();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionMoveInR();
    virtual void initScenes();

    static CCTransitionMoveInR* create(float t, CCScene* scene);
};

/** @brief CCTransitionMoveInT:
Move in from to the top the incoming scene.
*/
class CC_DLL CCTransitionMoveInT : public CCTransitionMoveInL 
{
public:
    /**
     *  @js ctor
     */
    CCTransitionMoveInT();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionMoveInT();
    virtual void initScenes();

    static CCTransitionMoveInT* create(float t, CCScene* scene);
};

/** @brief CCTransitionMoveInB:
Move in from to the bottom the incoming scene.
*/
class CC_DLL CCTransitionMoveInB : public CCTransitionMoveInL
{
public:
    /**
     *  @js ctor
     */
    CCTransitionMoveInB();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionMoveInB();
    virtual void initScenes();

    static CCTransitionMoveInB* create(float t, CCScene* scene);
};

/** @brief CCTransitionSlideInL:
Slide in the incoming scene from the left border.
*/
class CC_DLL CCTransitionSlideInL : public CCTransitionScene, public CCTransitionEaseScene
{
public:
    /**
     *  @js ctor
     */
    CCTransitionSlideInL();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionSlideInL();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    static CCTransitionSlideInL* create(float t, CCScene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionSlideInR:
Slide in the incoming scene from the right border.
*/
class CC_DLL CCTransitionSlideInR : public CCTransitionSlideInL 
{
public:
    /**
     *  @js ctor
     */
    CCTransitionSlideInR();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionSlideInR();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);

    static CCTransitionSlideInR* create(float t, CCScene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionSlideInB:
Slide in the incoming scene from the bottom border.
*/
class CC_DLL CCTransitionSlideInB : public CCTransitionSlideInL
{
public:
    /**
     *  @js ctor
     */
    CCTransitionSlideInB();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionSlideInB();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);

    static CCTransitionSlideInB* create(float t, CCScene* scene);
protected: 
    virtual void sceneOrder();
};

/** @brief CCTransitionSlideInT:
Slide in the incoming scene from the top border.
*/
class CC_DLL CCTransitionSlideInT : public CCTransitionSlideInL
{
public:
    /**
     *  @js ctor
     */
    CCTransitionSlideInT();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionSlideInT();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);

    static CCTransitionSlideInT* create(float t, CCScene* scene);
protected:
    virtual void sceneOrder();
};

/**
@brief Shrink the outgoing scene while grow the incoming scene
*/
class CC_DLL CCTransitionShrinkGrow : public CCTransitionScene , public CCTransitionEaseScene
{
public:
    /**
     *  @js ctor
     */
    CCTransitionShrinkGrow();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionShrinkGrow();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    static CCTransitionShrinkGrow* create(float t, CCScene* scene);
};

/** @brief CCTransitionFlipX:
Flips the screen horizontally.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionFlipX : public CCTransitionSceneOriented
{
public:
    /**
     *  @js ctor
     */
    CCTransitionFlipX();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionFlipX();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCTransitionFlipX* create(float t, CCScene* s, tOrientation o);
    static CCTransitionFlipX* create(float t, CCScene* s);
};

/** @brief CCTransitionFlipY:
Flips the screen vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionFlipY : public CCTransitionSceneOriented
{
public:
    /**
     *  @js ctor
     */
    CCTransitionFlipY();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionFlipY();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCTransitionFlipY* create(float t, CCScene* s, tOrientation o);
    static CCTransitionFlipY* create(float t, CCScene* s);
};

/** @brief CCTransitionFlipAngular:
Flips the screen half horizontally and half vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionFlipAngular : public CCTransitionSceneOriented
{
public:
    /**
     *  @js ctor
     */
    CCTransitionFlipAngular();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionFlipAngular();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    
    static CCTransitionFlipAngular* create(float t, CCScene* s, tOrientation o);
    static CCTransitionFlipAngular* create(float t, CCScene* s);
};

/** @brief CCTransitionZoomFlipX:
Flips the screen horizontally doing a zoom out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionZoomFlipX : public CCTransitionSceneOriented
{
public:
    /**
     *  @js ctor
     */
    CCTransitionZoomFlipX();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionZoomFlipX();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCTransitionZoomFlipX* create(float t, CCScene* s, tOrientation o);
    static CCTransitionZoomFlipX* create(float t, CCScene* s);
};

/** @brief CCTransitionZoomFlipY:
Flips the screen vertically doing a little zooming out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionZoomFlipY : public CCTransitionSceneOriented
{
public:
    /**
     *  @js ctor
     */
    CCTransitionZoomFlipY();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionZoomFlipY();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCTransitionZoomFlipY* create(float t, CCScene* s, tOrientation o);
    static CCTransitionZoomFlipY* create(float t, CCScene* s);
};

/** @brief CCTransitionZoomFlipAngular:
Flips the screen half horizontally and half vertically doing a little zooming out/in.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL CCTransitionZoomFlipAngular : public CCTransitionSceneOriented
{
public:
    /**
     *  @js ctor
     */
    CCTransitionZoomFlipAngular();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionZoomFlipAngular();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();

    static CCTransitionZoomFlipAngular* create(float t, CCScene* s, tOrientation o);
    static CCTransitionZoomFlipAngular* create(float t, CCScene* s);
};

/** @brief CCTransitionFade:
Fade out the outgoing scene and then fade in the incoming scene.'''
*/
class CC_DLL CCTransitionFade : public CCTransitionScene
{
protected:
    ccColor4B    m_tColor;

public:
    /**
     *  @js ctor
     */
    CCTransitionFade();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionFade();
    
    /** creates the transition with a duration and with an RGB color
    * Example: FadeTransition::create(2, scene, ccc3(255,0,0); // red color
    */
    static CCTransitionFade* create(float duration,CCScene* scene, const ccColor3B& color);
    static CCTransitionFade* create(float duration,CCScene* scene);

    /** initializes the transition with a duration and with an RGB color */
    virtual bool initWithDuration(float t, CCScene*scene ,const ccColor3B& color);

    virtual bool initWithDuration(float t,CCScene* scene);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    /**
     *  @js NA
     *  @lua NA
     */
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
    /**
     *  @js ctor
     */
    CCTransitionCrossFade();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionCrossFade();

    virtual void draw();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onExit();

public:
    static CCTransitionCrossFade* create(float t, CCScene* scene);
};

/** @brief CCTransitionTurnOffTiles:
Turn off the tiles of the outgoing scene in random order
*/
class CC_DLL CCTransitionTurnOffTiles : public CCTransitionScene ,public CCTransitionEaseScene
{
public :
    /**
     *  @js ctor
     */
    CCTransitionTurnOffTiles();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionTurnOffTiles();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:
    static CCTransitionTurnOffTiles* create(float t, CCScene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionSplitCols:
The odd columns goes upwards while the even columns goes downwards.
*/
class CC_DLL CCTransitionSplitCols : public CCTransitionScene , public CCTransitionEaseScene
{
public:
    /**
     *  @js ctor
     */
    CCTransitionSplitCols();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionSplitCols();

    virtual CCActionInterval* action(void);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:

    static CCTransitionSplitCols* create(float t, CCScene* scene);
};

/** @brief CCTransitionSplitRows:
The odd rows goes to the left while the even rows goes to the right.
*/
class CC_DLL CCTransitionSplitRows : public CCTransitionSplitCols
{
public:
    /**
     *  @js ctor
     */
    CCTransitionSplitRows();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionSplitRows();

    virtual CCActionInterval* action(void);

public:

    static CCTransitionSplitRows* create(float t, CCScene* scene);
};

/** @brief CCTransitionFadeTR:
Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner.
*/
class CC_DLL CCTransitionFadeTR : public CCTransitionScene , public CCTransitionEaseScene
{
public:
    /**
     *  @js ctor
     */
    CCTransitionFadeTR();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionFadeTR();
    virtual CCActionInterval* actionWithSize(const CCSize& size);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void onEnter();
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

public:

    static CCTransitionFadeTR* create(float t, CCScene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief CCTransitionFadeBL:
Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner.
*/
class CC_DLL CCTransitionFadeBL : public CCTransitionFadeTR
{
public:
    /**
     *  @js ctor
     */
    CCTransitionFadeBL();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionFadeBL();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static CCTransitionFadeBL* create(float t, CCScene* scene);
};

/** @brief CCTransitionFadeUp:
* Fade the tiles of the outgoing scene from the bottom to the top.
*/
class CC_DLL CCTransitionFadeUp : public CCTransitionFadeTR
{
public:
    /**
     *  @js ctor
     */
    CCTransitionFadeUp();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionFadeUp();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static CCTransitionFadeUp* create(float t, CCScene* scene);
};

/** @brief CCTransitionFadeDown:
* Fade the tiles of the outgoing scene from the top to the bottom.
*/
class CC_DLL CCTransitionFadeDown : public CCTransitionFadeTR
{
public:
    /**
     *  @js ctor
     */
    CCTransitionFadeDown();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCTransitionFadeDown();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static CCTransitionFadeDown* create(float t, CCScene* scene);
};

// end of transition group
/// @}

NS_CC_END

#endif // __CCTRANSITION_H__


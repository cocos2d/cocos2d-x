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

    CCTransitionScene();
    virtual ~CCTransitionScene();
    virtual void draw();
    virtual void onEnter();
    virtual void onExit();
    virtual void cleanup();

    /** creates a base transition with duration and incoming scene
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCTransitionScene * transitionWithDuration(float t, CCScene *scene);

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
    CCTransitionSceneOriented();
    virtual ~CCTransitionSceneOriented();

    /** creates a base transition with duration and incoming scene 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCTransitionSceneOriented * transitionWithDuration(float t,CCScene* scene, tOrientation orientation);

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
    CCTransitionRotoZoom();
    virtual ~CCTransitionRotoZoom();
    virtual void onEnter();

    CC_DEPRECATED_ATTRIBUTE static CCTransitionRotoZoom* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionRotoZoom* create(float t, CCScene* scene);
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

    CC_DEPRECATED_ATTRIBUTE static CCTransitionJumpZoom* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionJumpZoom* create(float t, CCScene* scene);
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

    CC_DEPRECATED_ATTRIBUTE static CCTransitionMoveInL* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionMoveInL* create(float t, CCScene* scene);
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

    CC_DEPRECATED_ATTRIBUTE static CCTransitionMoveInR* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionMoveInR* create(float t, CCScene* scene);
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

    CC_DEPRECATED_ATTRIBUTE static CCTransitionMoveInT* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionMoveInT* create(float t, CCScene* scene);
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

    CC_DEPRECATED_ATTRIBUTE static CCTransitionMoveInB* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionMoveInB* create(float t, CCScene* scene);
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
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);

    virtual void onEnter();
    
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    CC_DEPRECATED_ATTRIBUTE static CCTransitionSlideInL* transitionWithDuration(float t, CCScene* scene);
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
    CCTransitionSlideInR();
    virtual ~CCTransitionSlideInR();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);

    CC_DEPRECATED_ATTRIBUTE static CCTransitionSlideInR* transitionWithDuration(float t, CCScene* scene);
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
    CCTransitionSlideInB();
    virtual ~CCTransitionSlideInB();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);

    CC_DEPRECATED_ATTRIBUTE static CCTransitionSlideInB* transitionWithDuration(float t, CCScene* scene);
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
    CCTransitionSlideInT();
    virtual ~CCTransitionSlideInT();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual CCActionInterval* action(void);

    CC_DEPRECATED_ATTRIBUTE static CCTransitionSlideInT* transitionWithDuration(float t, CCScene* scene);
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
    CCTransitionShrinkGrow();
    virtual ~CCTransitionShrinkGrow();

    virtual void onEnter();
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    CC_DEPRECATED_ATTRIBUTE static CCTransitionShrinkGrow* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionShrinkGrow* create(float t, CCScene* scene);
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

    // @deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCTransitionFlipX* transitionWithDuration(float t, CCScene* s, tOrientation o = kCCTransitionOrientationRightOver);
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
    CCTransitionFlipY();
    virtual ~CCTransitionFlipY();

    virtual void onEnter();

    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCTransitionFlipY* transitionWithDuration(float t, CCScene* s, tOrientation o = kCCTransitionOrientationUpOver);
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
    CCTransitionFlipAngular();
    virtual ~CCTransitionFlipAngular();

    virtual void onEnter();

    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCTransitionFlipAngular* transitionWithDuration(float t, CCScene* s, tOrientation o = kCCTransitionOrientationRightOver);
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
    CCTransitionZoomFlipX();
    virtual ~CCTransitionZoomFlipX();

    virtual void onEnter();

    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCTransitionZoomFlipX* transitionWithDuration(float t, CCScene* s, tOrientation o = kCCTransitionOrientationRightOver);
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
    CCTransitionZoomFlipY();
    virtual ~CCTransitionZoomFlipY();

    virtual void onEnter();

    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCTransitionZoomFlipY* transitionWithDuration(float t, CCScene* s, tOrientation o = kCCTransitionOrientationUpOver);
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
    CCTransitionZoomFlipAngular();
    virtual ~CCTransitionZoomFlipAngular();

    virtual void onEnter();

    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCTransitionZoomFlipAngular* transitionWithDuration(float t, CCScene* s, tOrientation o = kCCTransitionOrientationRightOver);
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

    CCTransitionFade();
    virtual ~CCTransitionFade();

    /** creates the transition with a duration and with an RGB color
    * Example: FadeTransition::transitionWithDuration(2, scene, ccc3(255,0,0); // red color
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCTransitionFade* transitionWithDuration(float duration,CCScene* scene, const ccColor3B& color = ccBLACK);
    
        /** creates the transition with a duration and with an RGB color
    * Example: FadeTransition::create(2, scene, ccc3(255,0,0); // red color
    */
    static CCTransitionFade* create(float duration,CCScene* scene, const ccColor3B& color);
    static CCTransitionFade* create(float duration,CCScene* scene);

    /** initializes the transition with a duration and with an RGB color */
    virtual bool initWithDuration(float t, CCScene*scene ,const ccColor3B& color);

    virtual bool initWithDuration(float t,CCScene* scene); 
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
    CC_DEPRECATED_ATTRIBUTE static CCTransitionCrossFade* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionCrossFade* create(float t, CCScene* scene);
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
    CC_DEPRECATED_ATTRIBUTE static CCTransitionTurnOffTiles* transitionWithDuration(float t, CCScene* scene);
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
    CCTransitionSplitCols();
    virtual ~CCTransitionSplitCols();

    virtual CCActionInterval* action(void);
    virtual void onEnter();
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:
    CC_DEPRECATED_ATTRIBUTE static CCTransitionSplitCols* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionSplitCols* create(float t, CCScene* scene);
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
    CC_DEPRECATED_ATTRIBUTE static CCTransitionSplitRows* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionSplitRows* create(float t, CCScene* scene);
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
    CC_DEPRECATED_ATTRIBUTE static CCTransitionFadeTR* transitionWithDuration(float t, CCScene* scene);
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
    CCTransitionFadeBL();
    virtual ~CCTransitionFadeBL();
    virtual CCActionInterval* actionWithSize(const ccGridSize& size);

public:
    CC_DEPRECATED_ATTRIBUTE static CCTransitionFadeBL* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionFadeBL* create(float t, CCScene* scene);
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
    CC_DEPRECATED_ATTRIBUTE static CCTransitionFadeUp* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionFadeUp* create(float t, CCScene* scene);
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
    CC_DEPRECATED_ATTRIBUTE static CCTransitionFadeDown* transitionWithDuration(float t, CCScene* scene);
    static CCTransitionFadeDown* create(float t, CCScene* scene);
};

// end of transition group
/// @}

NS_CC_END

#endif // __CCTRANSITION_H__


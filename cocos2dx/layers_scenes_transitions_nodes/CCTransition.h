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

class ActionInterval;
class Node;

/** @brief TransitionEaseScene can ease the actions of the scene protocol.
@since v0.8.2
*/
class CC_DLL TransitionEaseScene// : public Object
{
public:
    /** returns the Ease action that will be performed on a linear action.
    @since v0.8.2
    */
    virtual ActionInterval * easeActionWithAction(ActionInterval * action) = 0;
};

/** Orientation Type used by some transitions
*/
typedef enum {
    /// An horizontal orientation where the Left is nearer
	kTransitionOrientationLeftOver = 0,
	/// An horizontal orientation where the Right is nearer
	kTransitionOrientationRightOver = 1,
	/// A vertical orientation where the Up is nearer
	kTransitionOrientationUpOver = 0,
	/// A vertical orientation where the Bottom is nearer
	kTransitionOrientationDownOver = 1,
    
	// Deprecated
    //	kOrientationLeftOver = kTransitionOrientationLeftOver,
    //	kOrientationRightOver = kTransitionOrientationRightOver,
    //	kOrientationUpOver = kTransitionOrientationUpOver,
    //	kOrientationDownOver = kTransitionOrientationDownOver,
} tOrientation;

/** @brief Base class for Transition scenes
*/
class CC_DLL TransitionScene : public Scene
{

protected:
    Scene    * _inScene;
    Scene    * _outScene;
    float    _duration;
    bool    _isInSceneOnTop;
    bool    _isSendCleanupToScene;

public:

    TransitionScene();
    virtual ~TransitionScene();
    virtual void draw();
    virtual void onEnter();
    virtual void onExit();
    virtual void cleanup();

    /** creates a base transition with duration and incoming scene */
    static TransitionScene * create(float t, Scene *scene);

    /** initializes a transition with duration and incoming scene */
    virtual bool initWithDuration(float t,Scene* scene);

    /** called after the transition finishes */
    void finish(void);

    /** used by some transitions to hide the outer scene */
    void hideOutShowIn(void);

protected:
    virtual void sceneOrder();
private:
    void setNewScene(float dt);

};

/** @brief A Transition that supports orientation like.
* Possible orientation: LeftOver, RightOver, UpOver, DownOver
*/
class CC_DLL TransitionSceneOriented : public TransitionScene
{
protected:
    tOrientation _orientation;

public:
    TransitionSceneOriented();
    virtual ~TransitionSceneOriented();

    /** creates a base transition with duration and incoming scene */
    static TransitionSceneOriented * create(float t,Scene* scene, tOrientation orientation);

    /** initializes a transition with duration and incoming scene */
    virtual bool initWithDuration(float t,Scene* scene,tOrientation orientation);
};

/** @brief TransitionRotoZoom:
Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming 
*/
class CC_DLL TransitionRotoZoom : public TransitionScene
{
public:
    TransitionRotoZoom();
    virtual ~TransitionRotoZoom();
    virtual void onEnter();

    static TransitionRotoZoom* create(float t, Scene* scene);
};

/** @brief TransitionJumpZoom:
Zoom out and jump the outgoing scene, and then jump and zoom in the incoming 
*/
class CC_DLL TransitionJumpZoom : public TransitionScene
{
public:
    TransitionJumpZoom();
    virtual ~TransitionJumpZoom();
    virtual void onEnter();

    static TransitionJumpZoom* create(float t, Scene* scene);
};

/** @brief TransitionMoveInL:
Move in from to the left the incoming scene.
*/
class CC_DLL TransitionMoveInL : public TransitionScene, public TransitionEaseScene
{
public:
    TransitionMoveInL();
    virtual ~TransitionMoveInL();
    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed */
    virtual ActionInterval* action(void);

    virtual ActionInterval* easeActionWithAction(ActionInterval * action);

    virtual void onEnter();

    static TransitionMoveInL* create(float t, Scene* scene);
};

/** @brief TransitionMoveInR:
Move in from to the right the incoming scene.
*/
class CC_DLL TransitionMoveInR : public TransitionMoveInL
{
public:
    TransitionMoveInR();
    virtual ~TransitionMoveInR();
    virtual void initScenes();

    static TransitionMoveInR* create(float t, Scene* scene);
};

/** @brief TransitionMoveInT:
Move in from to the top the incoming scene.
*/
class CC_DLL TransitionMoveInT : public TransitionMoveInL 
{
public:
    TransitionMoveInT();
    virtual ~TransitionMoveInT();
    virtual void initScenes();

    static TransitionMoveInT* create(float t, Scene* scene);
};

/** @brief TransitionMoveInB:
Move in from to the bottom the incoming scene.
*/
class CC_DLL TransitionMoveInB : public TransitionMoveInL
{
public:
    TransitionMoveInB();
    virtual ~TransitionMoveInB();
    virtual void initScenes();

    static TransitionMoveInB* create(float t, Scene* scene);
};

/** @brief TransitionSlideInL:
Slide in the incoming scene from the left border.
*/
class CC_DLL TransitionSlideInL : public TransitionScene, public TransitionEaseScene
{
public:
    TransitionSlideInL();
    virtual ~TransitionSlideInL();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual ActionInterval* action(void);

    virtual void onEnter();
    
    virtual ActionInterval* easeActionWithAction(ActionInterval * action);

    static TransitionSlideInL* create(float t, Scene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief TransitionSlideInR:
Slide in the incoming scene from the right border.
*/
class CC_DLL TransitionSlideInR : public TransitionSlideInL 
{
public:
    TransitionSlideInR();
    virtual ~TransitionSlideInR();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual ActionInterval* action(void);

    static TransitionSlideInR* create(float t, Scene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief TransitionSlideInB:
Slide in the incoming scene from the bottom border.
*/
class CC_DLL TransitionSlideInB : public TransitionSlideInL
{
public:
    TransitionSlideInB();
    virtual ~TransitionSlideInB();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual ActionInterval* action(void);

    static TransitionSlideInB* create(float t, Scene* scene);
protected: 
    virtual void sceneOrder();
};

/** @brief TransitionSlideInT:
Slide in the incoming scene from the top border.
*/
class CC_DLL TransitionSlideInT : public TransitionSlideInL
{
public:
    TransitionSlideInT();
    virtual ~TransitionSlideInT();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual ActionInterval* action(void);

    static TransitionSlideInT* create(float t, Scene* scene);
protected:
    virtual void sceneOrder();
};

/**
@brief Shrink the outgoing scene while grow the incoming scene
*/
class CC_DLL TransitionShrinkGrow : public TransitionScene , public TransitionEaseScene
{
public:
    TransitionShrinkGrow();
    virtual ~TransitionShrinkGrow();

    virtual void onEnter();
    virtual ActionInterval* easeActionWithAction(ActionInterval * action);

    static TransitionShrinkGrow* create(float t, Scene* scene);
};

/** @brief TransitionFlipX:
Flips the screen horizontally.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionFlipX : public TransitionSceneOriented
{
public:
    TransitionFlipX();
    virtual ~TransitionFlipX();

    virtual void onEnter();

    static TransitionFlipX* create(float t, Scene* s, tOrientation o);
    static TransitionFlipX* create(float t, Scene* s);
};

/** @brief TransitionFlipY:
Flips the screen vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionFlipY : public TransitionSceneOriented
{
public:
    TransitionFlipY();
    virtual ~TransitionFlipY();

    virtual void onEnter();

    static TransitionFlipY* create(float t, Scene* s, tOrientation o);
    static TransitionFlipY* create(float t, Scene* s);
};

/** @brief TransitionFlipAngular:
Flips the screen half horizontally and half vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionFlipAngular : public TransitionSceneOriented
{
public:
    TransitionFlipAngular();
    virtual ~TransitionFlipAngular();

    virtual void onEnter();
    
    static TransitionFlipAngular* create(float t, Scene* s, tOrientation o);
    static TransitionFlipAngular* create(float t, Scene* s);
};

/** @brief TransitionZoomFlipX:
Flips the screen horizontally doing a zoom out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionZoomFlipX : public TransitionSceneOriented
{
public:
    TransitionZoomFlipX();
    virtual ~TransitionZoomFlipX();

    virtual void onEnter();

    static TransitionZoomFlipX* create(float t, Scene* s, tOrientation o);
    static TransitionZoomFlipX* create(float t, Scene* s);
};

/** @brief TransitionZoomFlipY:
Flips the screen vertically doing a little zooming out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionZoomFlipY : public TransitionSceneOriented
{
public:
    TransitionZoomFlipY();
    virtual ~TransitionZoomFlipY();

    virtual void onEnter();

    static TransitionZoomFlipY* create(float t, Scene* s, tOrientation o);
    static TransitionZoomFlipY* create(float t, Scene* s);
};

/** @brief TransitionZoomFlipAngular:
Flips the screen half horizontally and half vertically doing a little zooming out/in.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionZoomFlipAngular : public TransitionSceneOriented
{
public:
    TransitionZoomFlipAngular();
    virtual ~TransitionZoomFlipAngular();

    virtual void onEnter();

    static TransitionZoomFlipAngular* create(float t, Scene* s, tOrientation o);
    static TransitionZoomFlipAngular* create(float t, Scene* s);
};

/** @brief TransitionFade:
Fade out the outgoing scene and then fade in the incoming scene.'''
*/
class CC_DLL TransitionFade : public TransitionScene
{
protected:
    ccColor4B    _color;

public:

    TransitionFade();
    virtual ~TransitionFade();
    
    /** creates the transition with a duration and with an RGB color
    * Example: FadeTransition::create(2, scene, ccc3(255,0,0); // red color
    */
    static TransitionFade* create(float duration,Scene* scene, const ccColor3B& color);
    static TransitionFade* create(float duration,Scene* scene);

    /** initializes the transition with a duration and with an RGB color */
    virtual bool initWithDuration(float t, Scene*scene ,const ccColor3B& color);

    virtual bool initWithDuration(float t,Scene* scene); 
    virtual void onEnter();
    virtual void onExit();
};

class RenderTexture;
/**
@brief TransitionCrossFade:
Cross fades two scenes using the RenderTexture object.
*/
class CC_DLL TransitionCrossFade : public TransitionScene
{
public :
    TransitionCrossFade();
    virtual ~TransitionCrossFade();

    virtual void draw();
    virtual void onEnter();
    virtual void onExit();

public:
    static TransitionCrossFade* create(float t, Scene* scene);
};

/** @brief TransitionTurnOffTiles:
Turn off the tiles of the outgoing scene in random order
*/
class CC_DLL TransitionTurnOffTiles : public TransitionScene ,public TransitionEaseScene
{
public :
    TransitionTurnOffTiles();
    virtual ~TransitionTurnOffTiles();

    virtual void onEnter();
    virtual ActionInterval * easeActionWithAction(ActionInterval * action);

public:
    static TransitionTurnOffTiles* create(float t, Scene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief TransitionSplitCols:
The odd columns goes upwards while the even columns goes downwards.
*/
class CC_DLL TransitionSplitCols : public TransitionScene , public TransitionEaseScene
{
public:
    TransitionSplitCols();
    virtual ~TransitionSplitCols();

    virtual ActionInterval* action(void);
    virtual void onEnter();
    virtual ActionInterval * easeActionWithAction(ActionInterval * action);

public:

    static TransitionSplitCols* create(float t, Scene* scene);
};

/** @brief TransitionSplitRows:
The odd rows goes to the left while the even rows goes to the right.
*/
class CC_DLL TransitionSplitRows : public TransitionSplitCols
{
public:
    TransitionSplitRows();
    virtual ~TransitionSplitRows();

    virtual ActionInterval* action(void);

public:

    static TransitionSplitRows* create(float t, Scene* scene);
};

/** @brief TransitionFadeTR:
Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner.
*/
class CC_DLL TransitionFadeTR : public TransitionScene , public TransitionEaseScene
{
public:
    TransitionFadeTR();
    virtual ~TransitionFadeTR();
    virtual ActionInterval* actionWithSize(const Size& size);
    virtual void onEnter();
    virtual ActionInterval* easeActionWithAction(ActionInterval * action);

public:

    static TransitionFadeTR* create(float t, Scene* scene);
protected:
    virtual void sceneOrder();
};

/** @brief TransitionFadeBL:
Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner.
*/
class CC_DLL TransitionFadeBL : public TransitionFadeTR
{
public:
    TransitionFadeBL();
    virtual ~TransitionFadeBL();
    virtual ActionInterval* actionWithSize(const Size& size);

public:

    static TransitionFadeBL* create(float t, Scene* scene);
};

/** @brief TransitionFadeUp:
* Fade the tiles of the outgoing scene from the bottom to the top.
*/
class CC_DLL TransitionFadeUp : public TransitionFadeTR
{
public:
    TransitionFadeUp();
    virtual ~TransitionFadeUp();
    virtual ActionInterval* actionWithSize(const Size& size);

public:

    static TransitionFadeUp* create(float t, Scene* scene);
};

/** @brief TransitionFadeDown:
* Fade the tiles of the outgoing scene from the top to the bottom.
*/
class CC_DLL TransitionFadeDown : public TransitionFadeTR
{
public:
    TransitionFadeDown();
    virtual ~TransitionFadeDown();
    virtual ActionInterval* actionWithSize(const Size& size);

public:

    static TransitionFadeDown* create(float t, Scene* scene);
};

// end of transition group
/// @}

NS_CC_END

#endif // __CCTRANSITION_H__


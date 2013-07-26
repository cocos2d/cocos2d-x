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

/** @brief Base class for Transition scenes
*/
class CC_DLL TransitionScene : public Scene
{
public:
    /** Orientation Type used by some transitions
     */
    enum class Orientation
    {
        /// An horizontal orientation where the Left is nearer
        LEFT_OVER = 0,
        /// An horizontal orientation where the Right is nearer
        RIGHT_OVER = 1,
        /// A vertical orientation where the Up is nearer
        UP_OVER = 0,
        /// A vertical orientation where the Bottom is nearer
        DOWN_OVER = 1,
    };
    
    /** creates a base transition with duration and incoming scene */
    static TransitionScene * create(float t, Scene *scene);

    TransitionScene();
    virtual ~TransitionScene();

    /** initializes a transition with duration and incoming scene */
    bool initWithDuration(float t,Scene* scene);

    /** called after the transition finishes */
    void finish(void);

    /** used by some transitions to hide the outer scene */
    void hideOutShowIn(void);

    //
    // Overrides
    //
    virtual void draw() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void cleanup() override;

protected:
    virtual void sceneOrder();

private:
    void setNewScene(float dt);

protected:
    Scene    * _inScene;
    Scene    * _outScene;
    float    _duration;
    bool    _isInSceneOnTop;
    bool    _isSendCleanupToScene;
};

/** @brief A Transition that supports orientation like.
* Possible orientation: LeftOver, RightOver, UpOver, DownOver
*/
class CC_DLL TransitionSceneOriented : public TransitionScene
{
public:
    /** creates a base transition with duration and incoming scene */
    static TransitionSceneOriented * create(float t,Scene* scene, Orientation orientation);

    TransitionSceneOriented();
    virtual ~TransitionSceneOriented();

    /** initializes a transition with duration and incoming scene */
    bool initWithDuration(float t,Scene* scene,Orientation orientation);

protected:
    Orientation _orientation;
};

/** @brief TransitionRotoZoom:
Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming 
*/
class CC_DLL TransitionRotoZoom : public TransitionScene
{
public:
    static TransitionRotoZoom* create(float t, Scene* scene);

    TransitionRotoZoom();
    virtual ~TransitionRotoZoom();

    //
    // Overrides
    //
    virtual void onEnter() override;
};

/** @brief TransitionJumpZoom:
Zoom out and jump the outgoing scene, and then jump and zoom in the incoming 
*/
class CC_DLL TransitionJumpZoom : public TransitionScene
{
public:
    static TransitionJumpZoom* create(float t, Scene* scene);

    TransitionJumpZoom();
    virtual ~TransitionJumpZoom();

    //
    // Overrides
    //
    virtual void onEnter() override;
};

/** @brief TransitionMoveInL:
Move in from to the left the incoming scene.
*/
class CC_DLL TransitionMoveInL : public TransitionScene, public TransitionEaseScene
{
public:
    static TransitionMoveInL* create(float t, Scene* scene);

    TransitionMoveInL();
    virtual ~TransitionMoveInL();
    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed */
    virtual ActionInterval* action(void);

    virtual ActionInterval* easeActionWithAction(ActionInterval * action);

    //
    // Overrides
    //
    virtual void onEnter() override;
};

/** @brief TransitionMoveInR:
Move in from to the right the incoming scene.
*/
class CC_DLL TransitionMoveInR : public TransitionMoveInL
{
public:
    static TransitionMoveInR* create(float t, Scene* scene);

    TransitionMoveInR();
    virtual ~TransitionMoveInR();
    virtual void initScenes();
};

/** @brief TransitionMoveInT:
Move in from to the top the incoming scene.
*/
class CC_DLL TransitionMoveInT : public TransitionMoveInL 
{
public:
    static TransitionMoveInT* create(float t, Scene* scene);

    TransitionMoveInT();
    virtual ~TransitionMoveInT();
    virtual void initScenes();
};

/** @brief TransitionMoveInB:
Move in from to the bottom the incoming scene.
*/
class CC_DLL TransitionMoveInB : public TransitionMoveInL
{
public:
    static TransitionMoveInB* create(float t, Scene* scene);

    TransitionMoveInB();
    virtual ~TransitionMoveInB();
    virtual void initScenes();
};

/** @brief TransitionSlideInL:
Slide in the incoming scene from the left border.
*/
class CC_DLL TransitionSlideInL : public TransitionScene, public TransitionEaseScene
{
public:
    static TransitionSlideInL* create(float t, Scene* scene);

    TransitionSlideInL();
    virtual ~TransitionSlideInL();

    virtual ActionInterval* easeActionWithAction(ActionInterval * action);

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual ActionInterval* action(void);

    //
    // Overrides
    //
    virtual void onEnter() override;
    
protected:
    virtual void sceneOrder() override;
};

/** @brief TransitionSlideInR:
Slide in the incoming scene from the right border.
*/
class CC_DLL TransitionSlideInR : public TransitionSlideInL 
{
public:
    static TransitionSlideInR* create(float t, Scene* scene);

    TransitionSlideInR();
    virtual ~TransitionSlideInR();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual ActionInterval* action(void);

protected:
    virtual void sceneOrder() override;
};

/** @brief TransitionSlideInB:
Slide in the incoming scene from the bottom border.
*/
class CC_DLL TransitionSlideInB : public TransitionSlideInL
{
public:
    static TransitionSlideInB* create(float t, Scene* scene);

    TransitionSlideInB();
    virtual ~TransitionSlideInB();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual ActionInterval* action(void);

protected:
    virtual void sceneOrder() override;
};

/** @brief TransitionSlideInT:
Slide in the incoming scene from the top border.
*/
class CC_DLL TransitionSlideInT : public TransitionSlideInL
{
public:
    static TransitionSlideInT* create(float t, Scene* scene);

    TransitionSlideInT();
    virtual ~TransitionSlideInT();

    /** initializes the scenes */
    virtual void initScenes(void);
    /** returns the action that will be performed by the incoming and outgoing scene */
    virtual ActionInterval* action(void);

protected:
    virtual void sceneOrder() override;
};

/**
@brief Shrink the outgoing scene while grow the incoming scene
*/
class CC_DLL TransitionShrinkGrow : public TransitionScene , public TransitionEaseScene
{
public:
    static TransitionShrinkGrow* create(float t, Scene* scene);

    TransitionShrinkGrow();
    virtual ~TransitionShrinkGrow();

    //
    // Overrides
    //
    virtual void onEnter() override;
    virtual ActionInterval* easeActionWithAction(ActionInterval * action) override;
};

/** @brief TransitionFlipX:
Flips the screen horizontally.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionFlipX : public TransitionSceneOriented
{
public:
    static TransitionFlipX* create(float t, Scene* s, Orientation o);
    static TransitionFlipX* create(float t, Scene* s);

    TransitionFlipX();
    virtual ~TransitionFlipX();

    //
    // Overrides
    //
    virtual void onEnter() override;
};

/** @brief TransitionFlipY:
Flips the screen vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionFlipY : public TransitionSceneOriented
{
public:
    static TransitionFlipY* create(float t, Scene* s, Orientation o);
    static TransitionFlipY* create(float t, Scene* s);

    TransitionFlipY();
    virtual ~TransitionFlipY();

    //
    // Overrides
    //
    virtual void onEnter() override;
};

/** @brief TransitionFlipAngular:
Flips the screen half horizontally and half vertically.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionFlipAngular : public TransitionSceneOriented
{
public:
    static TransitionFlipAngular* create(float t, Scene* s, Orientation o);
    static TransitionFlipAngular* create(float t, Scene* s);

    TransitionFlipAngular();
    virtual ~TransitionFlipAngular();

    //
    // Overrides
    //
    virtual void onEnter() override;
};

/** @brief TransitionZoomFlipX:
Flips the screen horizontally doing a zoom out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionZoomFlipX : public TransitionSceneOriented
{
public:
    static TransitionZoomFlipX* create(float t, Scene* s, Orientation o);
    static TransitionZoomFlipX* create(float t, Scene* s);

    TransitionZoomFlipX();
    virtual ~TransitionZoomFlipX();

    //
    // Overrides
    //
    virtual void onEnter() override;
};

/** @brief TransitionZoomFlipY:
Flips the screen vertically doing a little zooming out/in
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionZoomFlipY : public TransitionSceneOriented
{
public:
    static TransitionZoomFlipY* create(float t, Scene* s, Orientation o);
    static TransitionZoomFlipY* create(float t, Scene* s);

    TransitionZoomFlipY();
    virtual ~TransitionZoomFlipY();

    //
    // Overrides
    //
    virtual void onEnter() override;
};

/** @brief TransitionZoomFlipAngular:
Flips the screen half horizontally and half vertically doing a little zooming out/in.
The front face is the outgoing scene and the back face is the incoming scene.
*/
class CC_DLL TransitionZoomFlipAngular : public TransitionSceneOriented
{
public:
    static TransitionZoomFlipAngular* create(float t, Scene* s, Orientation o);
    static TransitionZoomFlipAngular* create(float t, Scene* s);

    TransitionZoomFlipAngular();
    virtual ~TransitionZoomFlipAngular();

    //
    // Overrides
    //
    virtual void onEnter() override;
};

/** @brief TransitionFade:
Fade out the outgoing scene and then fade in the incoming scene.'''
*/
class CC_DLL TransitionFade : public TransitionScene
{
public:
    /** creates the transition with a duration and with an RGB color
    * Example: FadeTransition::create(2, scene, Color3B(255,0,0); // red color
    */
    static TransitionFade* create(float duration,Scene* scene, const Color3B& color);
    static TransitionFade* create(float duration,Scene* scene);

    TransitionFade();
    virtual ~TransitionFade();

    /** initializes the transition with a duration and with an RGB color */
    bool initWithDuration(float t, Scene*scene ,const Color3B& color);

    //
    // Overrides
    //
    bool initWithDuration(float t,Scene* scene);
    virtual void onEnter();
    virtual void onExit();

protected:
    Color4B    _color;
};

class RenderTexture;
/**
@brief TransitionCrossFade:
Cross fades two scenes using the RenderTexture object.
*/
class CC_DLL TransitionCrossFade : public TransitionScene
{
public :
    static TransitionCrossFade* create(float t, Scene* scene);

    TransitionCrossFade();
    virtual ~TransitionCrossFade();

    //
    // Overrides
    //
    virtual void draw() override;
    virtual void onEnter() override;
    virtual void onExit() override;

};

/** @brief TransitionTurnOffTiles:
Turn off the tiles of the outgoing scene in random order
*/
class CC_DLL TransitionTurnOffTiles : public TransitionScene ,public TransitionEaseScene
{
public :
    static TransitionTurnOffTiles* create(float t, Scene* scene);

    TransitionTurnOffTiles();
    virtual ~TransitionTurnOffTiles();

    //
    // Overrides
    //
    virtual void onEnter() override;
    virtual ActionInterval * easeActionWithAction(ActionInterval * action) override;

protected:
    virtual void sceneOrder() override;
};

/** @brief TransitionSplitCols:
The odd columns goes upwards while the even columns goes downwards.
*/
class CC_DLL TransitionSplitCols : public TransitionScene , public TransitionEaseScene
{
public:
    static TransitionSplitCols* create(float t, Scene* scene);

    TransitionSplitCols();
    virtual ~TransitionSplitCols();

    virtual ActionInterval* action(void);

    //
    // Overrides
    //
    virtual void onEnter() override;
    virtual ActionInterval * easeActionWithAction(ActionInterval * action) override;
};

/** @brief TransitionSplitRows:
The odd rows goes to the left while the even rows goes to the right.
*/
class CC_DLL TransitionSplitRows : public TransitionSplitCols
{
public:
    static TransitionSplitRows* create(float t, Scene* scene);

    TransitionSplitRows();
    virtual ~TransitionSplitRows();

    //
    // Overrides
    //
    virtual ActionInterval* action(void) override;
};

/** @brief TransitionFadeTR:
Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner.
*/
class CC_DLL TransitionFadeTR : public TransitionScene , public TransitionEaseScene
{
public:
    static TransitionFadeTR* create(float t, Scene* scene);

    TransitionFadeTR();
    virtual ~TransitionFadeTR();
    virtual ActionInterval* actionWithSize(const Size& size);

    //
    // Overrides
    //
    virtual void onEnter() override;
    virtual ActionInterval* easeActionWithAction(ActionInterval * action) override;

protected:
    virtual void sceneOrder();
};

/** @brief TransitionFadeBL:
Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner.
*/
class CC_DLL TransitionFadeBL : public TransitionFadeTR
{
public:
    static TransitionFadeBL* create(float t, Scene* scene);

    TransitionFadeBL();
    virtual ~TransitionFadeBL();

    //
    // Overrides
    //
    virtual ActionInterval* actionWithSize(const Size& size) override;

};

/** @brief TransitionFadeUp:
* Fade the tiles of the outgoing scene from the bottom to the top.
*/
class CC_DLL TransitionFadeUp : public TransitionFadeTR
{
public:
    static TransitionFadeUp* create(float t, Scene* scene);

    TransitionFadeUp();
    virtual ~TransitionFadeUp();

    //
    // Overrides
    //
    virtual ActionInterval* actionWithSize(const Size& size) override;
};

/** @brief TransitionFadeDown:
* Fade the tiles of the outgoing scene from the top to the bottom.
*/
class CC_DLL TransitionFadeDown : public TransitionFadeTR
{
public:
    static TransitionFadeDown* create(float t, Scene* scene);

    TransitionFadeDown();
    virtual ~TransitionFadeDown();

    //
    // Overrides
    //
    virtual ActionInterval* actionWithSize(const Size& size) override;
};

// end of transition group
/// @}

NS_CC_END

#endif // __CCTRANSITION_H__


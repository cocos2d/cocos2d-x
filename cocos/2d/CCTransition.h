/****************************************************************************
Copyright (c) 2009-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sel
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

#include "2d/CCScene.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

//static creation function macro
//c/c++ don't support object creation of using class name
//so, all classes need creation method.

class ActionInterval;
class Node;
class NodeGrid;

/** 
 * @brief @~english TransitionEaseScene can ease the actions of the scene protocol.
 * @~chinese TransitionEaseScene类可以使场景运行ease动作。
 * @since v0.8.2
 * @js NA
*/
class CC_DLL TransitionEaseScene// : public Ref
{
public:
    /** @~english Constructor.
     * @~chinese 构造函数。
     */
    virtual ~TransitionEaseScene() {}

    /** @~english Returns the Ease action that will be performed on a linear action.
     * @~chinese 返回一个线性的缓动动作。
     * @since v0.8.2
     *
     * @param action @~english A given interval action.
     * @~chinese 在一个指定的持续性动作。
     * @return @~english The Ease action that will be performed on a linear action.
     * @~chinese 返回一个线性的缓动动作。
     */
    virtual ActionInterval * easeActionWithAction(ActionInterval * action) = 0;
};

/** 
 * @brief @~english Base class for Transition scenes.
 * @~chinese 场景转换的基类。
 */
class CC_DLL TransitionScene : public Scene
{
public:
    /** @~english Orientation Type used by some transitions.
     * @~chinese 一些用于转换的方向类型。
     */
    enum class Orientation
    {
        ///@~english  An horizontal orientation where the Left is nearer @~chinese 一个水平朝向，它离左边更近
        LEFT_OVER = 0,
        /// @~english An horizontal orientation where the Right is nearer @~chinese 一个水平朝向，它离右边更近
        RIGHT_OVER = 1,
        ///@~english  A vertical orientation where the Up is nearer @~chinese 一个垂直朝向，它离上面更近
        UP_OVER = 0,
        ///@~english  A vertical orientation where the Bottom is nearer @~chinese 一个垂直朝向，它离底部更近
        DOWN_OVER = 1,
    };
    
    /** @~english Creates a base transition with duration and incoming scene.
     *
     * @~chinese 基于给定的持续时间和待进入场景创建一个转换过渡场景(transition)。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionScene object.
     * @~chinese autoreleased TransitionScene对象。
     */
    static TransitionScene * create(float t, Scene *scene);

    /** @~english Called after the transition finishes.
     * @~chinese 转换结束调用此方法。
     */
    void finish(void);

    /** @~english Used by some transitions to hide the outer scene.
     * @~chinese 用于一些转换去隐藏淡出的场景。
     */
    void hideOutShowIn(void);

    Scene* getInScene() const{ return _inScene; }
    float getDuration() const { return _duration; }
    //
    // Overrides
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void cleanup() override;
    
CC_CONSTRUCTOR_ACCESS:
    TransitionScene();
    virtual ~TransitionScene();

    /** @~english initializes a transition with duration and incoming scene
     * @~chinese 初始化一个具有持续时间和进入的场景转换
     */
    bool initWithDuration(float t,Scene* scene);
    
protected:
    virtual void sceneOrder();
    void setNewScene(float dt);

    Scene *_inScene;
    Scene *_outScene;
    float _duration;
    bool _isInSceneOnTop;
    bool _isSendCleanupToScene;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionScene);
};

/** 
 * @brief @~english A Transition that supports orientation like.
 * Possible orientation: LeftOver, RightOver, UpOver, DownOver
 * @~chinese 支持方向的转换。
 * 可能的方向：LeftOver，RightOver，UpOver，DownOver
 */
class CC_DLL TransitionSceneOriented : public TransitionScene
{
public:
    /** @~english Creates a transition with duration, incoming scene and orientation.
     * 
     * @~chinese 基于给定的持续时间和待进入场景创建一个转换过渡场景(transition)。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @param orientation @~english A given orientation: LeftOver, RightOver, UpOver, DownOver.
     * @~chinese 一个给定的方向:LeftOver, RightOver, UpOver, DownOver。
     * @return @~english A autoreleased TransitionSceneOriented object.
     * @~chinese autoreleased TransitionSceneOriented对象。
     */
    static TransitionSceneOriented * create(float t,Scene* scene, Orientation orientation);
    
CC_CONSTRUCTOR_ACCESS:
    TransitionSceneOriented();
    virtual ~TransitionSceneOriented();

    /**
    * @~english initializes a transition with duration and incoming scene
    * @~chinese 初始化一个具有持续时间和进入的场景转换
    */
    bool initWithDuration(float t,Scene* scene,Orientation orientation);

protected:
    Orientation _orientation;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSceneOriented);
};

/** 
 * @brief @~english TransitionRotoZoom:
 * Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming 
 * @~chinese TransitionRotoZoom:
 * 旋转和缩放离开前一个场景，同时旋转缩放进入下一个场景
*/
class CC_DLL TransitionRotoZoom : public TransitionScene
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个旋转和缩放场景过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionRotoZoom object.
     * @~chinese autoreleased TransitionRotoZoom对象。
     */
    static TransitionRotoZoom* create(float t, Scene* scene);

    //
    // Overrides
    //
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionRotoZoom();
    virtual ~TransitionRotoZoom();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionRotoZoom);

};

/** 
 * @brief @~english TransitionJumpZoom:
 * Zoom out and jump the outgoing scene, and then jump and zoom in the incoming 
 * @~chinese TransitionJumpZoom:
 * 缩小跳着切出场景, 同时跳着放大传人场景
*/
class CC_DLL TransitionJumpZoom : public TransitionScene
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个缩小跳着切出场景, 同时跳着放大传入过渡场景。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionJumpZoom object.
     * @~chinese autoreleased TransitionJumpZoom对象。
     */
    static TransitionJumpZoom* create(float t, Scene* scene);

    //
    // Overrides
    //
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionJumpZoom();
    virtual ~TransitionJumpZoom();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionJumpZoom);
};

/** 
 * @brief @~english TransitionMoveInL:
 * Move in from to the left the incoming scene.
 * @~chinese TransitionMoveInL:
 * 从左侧传入场景。
*/
class CC_DLL TransitionMoveInL : public TransitionScene, public TransitionEaseScene
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 基于给定的持续时间和待进入场景创建一个转换过渡场景(transition)。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionMoveInL object.
     * @~chinese autoreleased TransitionMoveInL对象。
     */
    static TransitionMoveInL* create(float t, Scene* scene);

    /** @~english Returns the action that will be performed. 
     * 
     * @~chinese 返回将要执行的动作。
     * 
     * @return @~english The action that will be performed.
     * @~chinese 返回将要执行的动作。
     */
    virtual ActionInterval* action(void);

    virtual ActionInterval* easeActionWithAction(ActionInterval * action) override;

    //
    // Overrides
    //
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionMoveInL();
    virtual ~TransitionMoveInL();

protected:
    /** @~english initializes the scenes  @~chinese 初始化的场景*/
    virtual void initScenes();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionMoveInL);
};

/** 
 * @brief @~english TransitionMoveInR:
 * Move in from to the right the incoming scene.
 * @~chinese TransitionMoveInR:
 * 从右侧传人场景。
*/
class CC_DLL TransitionMoveInR : public TransitionMoveInL
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 基于给定的持续时间和待进入场景创建一个转换过渡场景(transition)。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionMoveInR object.
     * @~chinese autoreleased TransitionMoveInR对象。
     */
    static TransitionMoveInR* create(float t, Scene* scene);

CC_CONSTRUCTOR_ACCESS:
    TransitionMoveInR();
    virtual ~TransitionMoveInR();

protected:
    virtual void initScenes();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionMoveInR);
};

/** 
 * @brief @~english TransitionMoveInT:
 * Move in from to the top the incoming scene.
 * @~chinese TransitionMoveInT:
 * 从顶部传入场景。
*/
class CC_DLL TransitionMoveInT : public TransitionMoveInL 
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个从顶部传入的场景过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionMoveInT object.
     * @~chinese autoreleased TransitionMoveInT对象。
     */
    static TransitionMoveInT* create(float t, Scene* scene);

CC_CONSTRUCTOR_ACCESS:
    TransitionMoveInT();
    virtual ~TransitionMoveInT();

protected:
    virtual void initScenes();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionMoveInT);
};

/** 
 * @brief @~english TransitionMoveInB:
 * Move in from to the bottom the incoming scene.
 * @~chinese TransitionMoveInB:
 * 从底部传入。
*/
class CC_DLL TransitionMoveInB : public TransitionMoveInL
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个从底部传入的场景过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionMoveInB object.
     * @~chinese autoreleased TransitionMoveInB对象。
     */
    static TransitionMoveInB* create(float t, Scene* scene);

CC_CONSTRUCTOR_ACCESS:
    TransitionMoveInB();
    virtual ~TransitionMoveInB();

protected:
    virtual void initScenes();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionMoveInB);
};

/** 
 * @brief @~english TransitionSlideInL:
 * Slide in the incoming scene from the left border.
 * @~chinese TransitionSlideInL:
 * 从左边滑入传人场景。
*/
class CC_DLL TransitionSlideInL : public TransitionScene, public TransitionEaseScene
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建从左边滑入传人场景的过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionSlideInL object.
     * @~chinese autoreleased TransitionSlideInL对象。
     */
    static TransitionSlideInL* create(float t, Scene* scene);

    virtual ActionInterval* easeActionWithAction(ActionInterval * action) override;

    /** @~english Returns the action that will be performed by the incoming and outgoing scene.
     *
     * @~chinese 返回传入/传出场景要执行的动作。
     * 
     * @return @~english The action that will be performed by the incoming and outgoing scene.
     * @~chinese 返回传入/传出场景要执行的动作。
     */
    virtual ActionInterval* action(void);

    //
    // Overrides
    //
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionSlideInL();
    virtual ~TransitionSlideInL();

protected:
    /** @~english initializes the scenes  @~chinese Initializes the scenes*/
    virtual void initScenes(void);

    virtual void sceneOrder() override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideInL);
};

/** 
 * @brief @~english TransitionSlideInR:
 * Slide in the incoming scene from the right border.
 * @~chinese TransitionSlideInR:
 * 从右边滑入传入场景。
*/
class CC_DLL TransitionSlideInR : public TransitionSlideInL 
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个从右边滑入的场景过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionSlideInR object.
     * @~chinese autoreleased TransitionSlideInR对象。
     */
    static TransitionSlideInR* create(float t, Scene* scene);

    /** @~english Returns the action that will be performed by the incoming and outgoing scene.  @~chinese 返回传入/传出 scene 要执行的动作。*/
    virtual ActionInterval* action(void) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionSlideInR();
    virtual ~TransitionSlideInR();

protected:
    /** @~english initializes the scenes  @~chinese 初始化的场景*/
    virtual void initScenes(void) override;

    virtual void sceneOrder() override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideInR);
};

/** 
 * @brief @~english TransitionSlideInB:
 * Slide in the incoming scene from the bottom border.
 * @~chinese TransitionSlideInB:
 * 从底部滑入场景。
 */
class CC_DLL TransitionSlideInB : public TransitionSlideInL
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个从底部滑入的场景过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionSlideInB object.
     * @~chinese autoreleased TransitionSlideInB对象。
     */
    static TransitionSlideInB* create(float t, Scene* scene);

    /** @~english returns the action that will be performed by the incoming and outgoing scene  @~chinese 返回传入/传出场景要执行的动作*/
    virtual ActionInterval* action(void) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionSlideInB();
    virtual ~TransitionSlideInB();

protected:
    /** @~english initializes the scenes  @~chinese 初始化的场景*/
    virtual void initScenes() override;

    virtual void sceneOrder() override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideInB);
};

/** 
 * @brief @~english TransitionSlideInT:
 * Slide in the incoming scene from the top border.
 * @~chinese TransitionSlideInT:
 * 从顶部滑入场景。
*/
class CC_DLL TransitionSlideInT : public TransitionSlideInL
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个从顶部滑入场景的过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionSlideInT object.
     * @~chinese autoreleased TransitionSlideInT对象。
     */
    static TransitionSlideInT* create(float t, Scene* scene);

    /** @~english returns the action that will be performed by the incoming and outgoing scene  @~chinese 返回传入/传出场景要执行的动作*/
    virtual ActionInterval* action(void) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionSlideInT();
    virtual ~TransitionSlideInT();

protected:
    /** @~english initializes the scenes  @~chinese 初始化的场景*/
    virtual void initScenes(void) override;

    virtual void sceneOrder() override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideInT);
};

/** 
 * @brief @~english Shrink the outgoing scene while grow the incoming scene
 * @~chinese 收缩切出场景，同时放大切入场景
 */
class CC_DLL TransitionShrinkGrow : public TransitionScene , public TransitionEaseScene
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个收缩切出场景，同时放大切入场景的过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionShrinkGrow object.
     * @~chinese autoreleased TransitionShrinkGrow对象。
     */
    static TransitionShrinkGrow* create(float t, Scene* scene);

    //
    // Overrides
    //
    /**
     * @lua NA
     */
    virtual void onEnter() override;
    virtual ActionInterval* easeActionWithAction(ActionInterval * action) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionShrinkGrow();
    virtual ~TransitionShrinkGrow();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionShrinkGrow);
};

/** 
 * @brief @~english TransitionFlipX:
 * Flips the screen horizontally.
 * The front face is the outgoing scene and the back face is the incoming scene.
 * @~chinese TransitionFlipX:
 * 水平翻转屏幕。
 * 正面是传出的场景，背面是传入的场景。
*/
class CC_DLL TransitionFlipX : public TransitionSceneOriented
{
public:
    /** @~english Creates a transition with duration, incoming scene and orientation.
     *
     * @~chinese 创建一个水平翻转过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @param o @~english A given orientation.
     * @~chinese 一个给定的方向。
     * @return @~english A autoreleased TransitionFlipX object.
     * @~chinese autoreleased TransitionFlipX对象。
     */
    static TransitionFlipX* create(float t, Scene* s, Orientation o);

    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个水平翻转过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionFlipX object.
     * @~chinese autoreleased TransitionFlipX对象。
     */
    static TransitionFlipX* create(float t, Scene* s);

    //
    // Overrides
    //
    /**
     * @lua NA
     */
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionFlipX();
    virtual ~TransitionFlipX();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFlipX);
};

/** 
 * @brief @~english TransitionFlipY:
 * Flips the screen vertically.
 * The front face is the outgoing scene and the back face is the incoming scene.
 * @~chinese TransitionFlipY:
 * 垂直翻转屏幕。
 * 正面是传出的场景，背面是传入的场景。
*/
class CC_DLL TransitionFlipY : public TransitionSceneOriented
{
public:
    /** @~english Creates a transition with duration, incoming scene and orientation.
     *
     * @~chinese 创建一个垂直翻转屏幕过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @param o @~english A given orientation.
     * @~chinese 一个给定的方向。
     * @return @~english A autoreleased TransitionFlipY object.
     * @~chinese autoreleased TransitionFlipY对象。
     */
    static TransitionFlipY* create(float t, Scene* s, Orientation o);

    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个垂直翻转屏幕过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionFlipY object.
     * @~chinese autoreleased TransitionFlipY对象。
     */
    static TransitionFlipY* create(float t, Scene* s);

    //
    // Overrides
    //
    /**
     * @lua NA
     */
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionFlipY();
    virtual ~TransitionFlipY();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFlipY);
};

/** 
 * @brief @~english TransitionFlipAngular:
 * Flips the screen half horizontally and half vertically.
 * The front face is the outgoing scene and the back face is the incoming scene.
 * @~chinese TransitionFlipAngular:
 * 水平垂直翻转屏幕.（类似一种镜面）。
 * 正面是传出的场景，背面是传入的场景。
*/
class CC_DLL TransitionFlipAngular : public TransitionSceneOriented
{
public:
    /** @~english Creates a transition with duration, incoming scene and orientation.
     *
     * @~chinese 创建一个水平垂直翻转过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @param o @~english A given orientation.
     * @~chinese 一个给定的方向。
     * @return @~english A autoreleased TransitionFlipAngular object.
     * @~chinese autoreleased TransitionFlipAngular对象。
     */
    static TransitionFlipAngular* create(float t, Scene* s, Orientation o);

    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个水平垂直翻转过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionFlipAngular object.
     * @~chinese autoreleased TransitionFlipAngular对象。
     */
    static TransitionFlipAngular* create(float t, Scene* s);

    //
    // Overrides
    //
    /**
     * @lua NA
     */
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionFlipAngular();
    virtual ~TransitionFlipAngular();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFlipAngular);
};

/** 
 * @brief @~english TransitionZoomFlipX:
 * Flips the screen horizontally doing a zoom out/in
 * The front face is the outgoing scene and the back face is the incoming scene.
 * @~chinese TransitionZoomFlipX:
 * 水平翻转同时缩放屏幕
 * 正面是传出的场景，背面是传入的场景。
*/
class CC_DLL TransitionZoomFlipX : public TransitionSceneOriented
{
public:
    /** @~english Creates a transition with duration, incoming scene and orientation.
     *
     * @~chinese 创建一个水平翻转同时缩放屏幕。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @param o @~english A given orientation.
     * @~chinese 一个给定的方向。
     * @return @~english A autoreleased TransitionZoomFlipX object.
     * @~chinese autoreleased TransitionZoomFlipX对象。
     */
    static TransitionZoomFlipX* create(float t, Scene* s, Orientation o);

    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个水平翻转同时缩放屏幕。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 在全国,后者。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionZoomFlipX object.
     * @~chinese autoreleased TransitionZoomFlipX对象。
     */
    static TransitionZoomFlipX* create(float t, Scene* s);

    //
    // Overrides
    //
    /**
     * @lua NA
     */
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionZoomFlipX();
    virtual ~TransitionZoomFlipX();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionZoomFlipX);
};

/** 
 * @brief @~english TransitionZoomFlipY:
 * Flips the screen vertically doing a little zooming out/in
 * The front face is the outgoing scene and the back face is the incoming scene.
 * @~chinese TransitionZoomFlipY:
 * 垂直翻转同时缩放屏幕。
 * 正面是传出的场景，背面是传入的场景。
*/
class CC_DLL TransitionZoomFlipY : public TransitionSceneOriented
{
public:
    /** @~english Creates a transition with duration, incoming scene and orientation.
     *
     * @~chinese 创建一个垂直翻转同时缩放屏幕过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @param o @~english A given orientation.
     * @~chinese 一个给定的方向。
     * @return @~english A autoreleased TransitionZoomFlipY object.
     * @~chinese autoreleased TransitionZoomFlipY对象。
     */
    static TransitionZoomFlipY* create(float t, Scene* s, Orientation o);

    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个垂直翻转同时缩放屏幕过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionZoomFlipY object.
     * @~chinese autoreleased TransitionZoomFlipY对象。
     */
    static TransitionZoomFlipY* create(float t, Scene* s);

    //
    // Overrides
    //
    /**
     * @lua NA
     */
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionZoomFlipY();
    virtual ~TransitionZoomFlipY();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionZoomFlipY);
};

/** 
 * @brief @~english TransitionZoomFlipAngular:
 * Flips the screen half horizontally and half vertically doing a little zooming out/in.
 * The front face is the outgoing scene and the back face is the incoming scene.
 * @~chinese TransitionZoomFlipAngular:
 * 对角翻转同时缩放屏幕
 * 正面是传出的场景，背面是传入的场景。
*/
class CC_DLL TransitionZoomFlipAngular : public TransitionSceneOriented
{
public:
    /** @~english Creates a transition with duration, incoming scene and orientation.
     *
     * @~chinese 创建一个对角翻转同时缩放屏幕过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @param o @~english A given orientation.
     * @~chinese 一个给定的方向。
     * @return @~english A autoreleased TransitionZoomFlipAngular object.
     * @~chinese autoreleased TransitionZoomFlipAngular对象。
     */
    static TransitionZoomFlipAngular* create(float t, Scene* s, Orientation o);

    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个对角翻转同时缩放屏幕过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionZoomFlipAngular object.
     * @~chinese autoreleased TransitionZoomFlipAngular对象。
     */
    static TransitionZoomFlipAngular* create(float t, Scene* s);

    //
    // Overrides
    //
    /**
     * @lua NA
     */
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionZoomFlipAngular();
    virtual ~TransitionZoomFlipAngular();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionZoomFlipAngular);
};

/** 
 * @brief @~english TransitionFade:
 * Fade out the outgoing scene and then fade in the incoming scene.'''
 * @~chinese TransitionFade:
 * 淡入淡出
*/
class CC_DLL TransitionFade : public TransitionScene
{
public:
    /** @~english Creates the transition with a duration and with an RGB color
     * Example: FadeTransition::create(2, scene, Color3B(255,0,0); // red color
     *
     * @~chinese 创建一个淡入淡出场景过渡
     * 例如: FadeTransition::create(2, scene, Color3B(255,0,0); //红色
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @param color @~english A given transition color.
     * @~chinese 一个给定的过渡色。
     * @return @~english A autoreleased TransitionFade object.
     * @~chinese autoreleased TransitionFade对象。
     */
    static TransitionFade* create(float duration, Scene* scene, const Color3B& color);

    /** @~english Creates the transition with a duration.
     *
     * @~chinese 创建一个淡入淡出场景过渡。
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionFade object.
     * @~chinese autoreleased TransitionFade对象。
     */
    static TransitionFade* create(float duration, Scene* scene);

    /**
     * @lua NA
     */
    virtual void onEnter() override;
    /**
     * @lua NA
     */
    virtual void onExit() override;
    
CC_CONSTRUCTOR_ACCESS:
    TransitionFade();
    virtual ~TransitionFade();

    /** @~english initializes the transition with a duration and with an RGB color  @~chinese 使用 duration、RGB color 初始化一个 transition（过渡）*/
    bool initWithDuration(float t, Scene*scene, const Color3B& color);
    bool initWithDuration(float t, Scene* scene);

protected:
    Color4B _color;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFade);

};

class RenderTexture;

/** 
 * @brief @~english TransitionCrossFade:
 * Cross fades two scenes using the RenderTexture object.
 * @~chinese TransitionCrossFade:
 * 交叉淡入淡出
 */
class CC_DLL TransitionCrossFade : public TransitionScene
{
public :
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个交叉淡入淡出过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionCrossFade object.
     * @~chinese autoreleased TransitionCrossFade对象。
     */
    static TransitionCrossFade* create(float t, Scene* scene);

    //
    // Overrides
    //
    /**
     * @lua NA
     */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    /**
     * @lua NA
     */
    virtual void onEnter() override;
    /**
     * @lua NA
     */
    virtual void onExit() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionCrossFade();
    virtual ~TransitionCrossFade();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionCrossFade);
};

/** 
 * @brief @~english TransitionTurnOffTiles:
 * Turn off the tiles of the outgoing scene in random order
 * @~chinese TransitionTurnOffTiles:
 * 随机瓦片
*/
class CC_DLL TransitionTurnOffTiles : public TransitionScene ,public TransitionEaseScene
{
public :
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个随机瓦片过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionTurnOffTiles object.
     * @~chinese autoreleased TransitionTurnOffTiles对象。
     */
    static TransitionTurnOffTiles* create(float t, Scene* scene);

    //
    // Overrides
    //
    /**
     * @lua NA
     */
    virtual void onEnter() override;
    /**
     * @js NA
     */
    virtual void onExit() override;
	virtual ActionInterval * easeActionWithAction(ActionInterval * action) override;
	/**
	* @js NA
	*/
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionTurnOffTiles();
    virtual ~TransitionTurnOffTiles();

protected:
    virtual void sceneOrder() override;
    NodeGrid* _outSceneProxy;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionTurnOffTiles);
};

/** 
 * @brief @~english TransitionSplitCols:
 * The odd columns goes upwards while the even columns goes downwards.
 * @~chinese TransitionSplitCols:
 * 奇数列向上推移而偶数列向下推移。
*/
class CC_DLL TransitionSplitCols : public TransitionScene , public TransitionEaseScene
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个奇数列向上推移而偶数列向下推移过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionSplitCols object.
     * @~chinese autoreleased TransitionSplitCols对象。
     */
    static TransitionSplitCols* create(float t, Scene* scene);

    /** @~english Returns the action that will be performed.
     *
     * @~chinese 返回将要被执行的动作。
     * 
     * @return @~english The action that will be performed.
     * @~chinese 将要被执行的动作。
     */
    virtual ActionInterval* action();

    //
    // Overrides
    //
    /**
     * @lua NA
     */
    virtual void onEnter() override;
    virtual ActionInterval * easeActionWithAction(ActionInterval * action) override;
    virtual void onExit() override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionSplitCols();
    virtual ~TransitionSplitCols();

protected:
    void switchTargetToInscene();
    NodeGrid* _gridProxy;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSplitCols);
};

/** 
 * @brief @~english TransitionSplitRows:
 * The odd rows goes to the left while the even rows goes to the right.
 * @~chinese TransitionSplitRows:
 * 奇数行从左侧推移，偶数行从右侧推移。
 */
class CC_DLL TransitionSplitRows : public TransitionSplitCols
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个奇数行从左侧推移，偶数行从右侧推移过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionSplitRows object.
     * @~chinese autoreleased TransitionSplitRows对象。
     */
    static TransitionSplitRows* create(float t, Scene* scene);

    //
    // Overrides
    //
    virtual ActionInterval* action(void) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionSplitRows();
    virtual ~TransitionSplitRows();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSplitRows);
};

/** 
 * @brief @~english TransitionFadeTR:
 * Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner.
 * @~chinese TransitionFadeTR:
 * 从从左下角到右上角淡出瓦片。
*/
class CC_DLL TransitionFadeTR : public TransitionScene , public TransitionEaseScene
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个从从左下角到右上角淡出瓦片过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionFadeTR object.
     * @~chinese autoreleased TransitionFadeTR对象。
     */
    static TransitionFadeTR* create(float t, Scene* scene);

    /** @~english Returns the action that will be performed with size.
     *
     * @~chinese 返回将要被执行的动作。
     * 
     * @param size @~english A given size.
     * @~chinese 一个给定的大小。
     * @return @~english The action that will be performed.
     * @~chinese 将要被执行的动作
     */
    virtual ActionInterval* actionWithSize(const Size& size);

    //
    // Overrides
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;
    virtual ActionInterval* easeActionWithAction(ActionInterval * action) override;
    virtual void onExit() override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionFadeTR();
    virtual ~TransitionFadeTR();

protected:
    virtual void sceneOrder() override;

    NodeGrid* _outSceneProxy;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFadeTR);
};

/** 
 * @brief @~english TransitionFadeBL:
 * Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner.
 * @~chinese TransitionFadeBL:
 * 从右上角到左下角淡出瓦片。
*/
class CC_DLL TransitionFadeBL : public TransitionFadeTR
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个从右上角到左下角淡出瓦片过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese seconds in,time duration。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionFadeBL object.
     * @~chinese autoreleased TransitionFadeBL对象。
     */
    static TransitionFadeBL* create(float t, Scene* scene);

    //
    // Overrides
    //
    virtual ActionInterval* actionWithSize(const Size& size) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionFadeBL();
    virtual ~TransitionFadeBL();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFadeBL);
};

/** 
 * @brief @~english TransitionFadeUp:
 * Fade the tiles of the outgoing scene from the bottom to the top.
 * @~chinese TransitionFadeUp:
 * 从下向上淡出瓦片。
 */
class CC_DLL TransitionFadeUp : public TransitionFadeTR
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个从下向上淡出瓦片过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionFadeUp object.
     * @~chinese autoreleased TransitionFadeUp对象。
     */
    static TransitionFadeUp* create(float t, Scene* scene);

    //
    // Overrides
    //
    virtual ActionInterval* actionWithSize(const Size& size) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionFadeUp();
    virtual ~TransitionFadeUp();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFadeUp);
};

/** 
 * @brief @~english TransitionFadeDown:
 * Fade the tiles of the outgoing scene from the top to the bottom.
 * @~chinese TransitionFadeDown:
 * 从上向下淡出瓦片。
 */
class CC_DLL TransitionFadeDown : public TransitionFadeTR
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 创建一个从上向下淡出瓦片过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english A autoreleased TransitionFadeDown object.
     * @~chinese autoreleased TransitionFadeDown对象。
     */
    static TransitionFadeDown* create(float t, Scene* scene);

    //
    // Overrides
    //
    virtual ActionInterval* actionWithSize(const Size& size) override;

CC_CONSTRUCTOR_ACCESS:
    TransitionFadeDown();
    virtual ~TransitionFadeDown();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFadeDown);

};

// end of _2d group
/// @}

NS_CC_END

#endif // __CCTRANSITION_H__


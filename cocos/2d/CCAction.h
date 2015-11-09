/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef __ACTIONS_CCACTION_H__
#define __ACTIONS_CCACTION_H__

#include "base/CCRef.h"
#include "math/CCGeometry.h"
#include "base/CCScriptSupport.h"

NS_CC_BEGIN

class Node;

enum {
    kActionUpdate
};

/**
 * @addtogroup actions
 * @{
 */


/** 
 * @brief @~english Base class for Action objects. @~chinese Action类是所有动作对象的基类.
 */
class CC_DLL Action : public Ref, public Clonable
{
public:
    
    /** 
     @property INVALID_TAG
     @~english Default tag used for all the actions. 
     @~chinese 所有Action对象的缺省tag值
     */
    static const int INVALID_TAG = -1;

    /**
     * @js NA
     * @lua NA
     */
    virtual std::string description() const;

    /** @~english Returns a clone of action.
     *
     * @~chinese 返回一个克隆的动作。
     * 
     * @return @~english A clone action.
     * @~chinese 一个克隆的动作
     */
    virtual Action* clone() const
    {
        CC_ASSERT(0);
        return nullptr;
    }

    /** @~english Returns a new action that performs the exactly the reverse action. 
     *
     * @~chinese 返回一个新的动作，执行与原动作完全相反的动作。
     * 
     * @return @~english A new action that performs the exactly the reverse action.
     * @~chinese 一个与原动作相反的动作。
     * @js NA
     */
    virtual Action* reverse() const
    {
        CC_ASSERT(0);
        return nullptr;
    }

    /** @~english Return true if the action has finished. 
     * 
     * @~chinese 如果动作已经完成就返回true。
     * 
     * @return @~english Is true if the action has finished.
     * @~chinese 如果动作已经完成就返回true。
     */
    virtual bool isDone() const;

    /** @~english Called before the action start. It will also set the target. 
     *
     * @~chinese 在动作开始之前调用，它还将设置target属性为目标节点。
     * 
     * @param target @~english A certain target.
     * @~chinese 一个特定的目标节点。
     */
    virtual void startWithTarget(Node *target);

    /** @~english
     * Called after the action that has finished. It will set the 'target' to nil.
     * IMPORTANT: You should never call "Action::stop()" manually. Instead, use: "target->stopAction(action);".
     * @~chinese 
     * 操作完成后会调用，它会将target设置为空。
     * **注意**: 你不应该叫手动调用这个API，请使用"target->stopAction(action);"。
     */
    virtual void stop();

    /** @~english Called every frame with its delta time, dt in seconds. DON'T override unless you know what you are doing. 
     *
     * @~chinese 动作开始后每一帧都会被调用，并传递与上一帧的间隔时间dt为参数，dt以秒为单位。不要重载这个函数，除非你知道你在做什么。
     * 
     * @param dt @~english In seconds.
     * @~chinese 以秒为单位的时间间隔。
     */
    virtual void step(float dt);

    /** @~english
     * Called once per frame. time is a value between 0 and 1.

     * For example:
     * - 0 Means that the action just started.
     * - 0.5 Means that the action is in the middle.
     * - 1 Means that the action is over.
     *
     * @~chinese 
     * 动作开始后每帧都会被调用。time是一个值在0和1之间的进度。
     * 
     * 例如:
     * - 0意味着动作刚刚开始。
     * - 0.5意味着动作是在中间。
     * - 1意味着动作已经结束。
     * 
     * @param time @~english A value between 0 and 1.
     * @~chinese 一个在0和1之间的值。
     */
    virtual void update(float time);

    /** @~english Return the current target.
     *
     * @~chinese 返回当前目标节点。
     * 
     * @return @~english the current target.
     * @~chinese 当前目标节点。
     */
    inline Node* getTarget() const { return _target; }

    /** @~english The setter function for the target property. 
     *
     * @~chinese 修改目标节点属性的设置函数。
     * 
     * @param target @~english A certain target.
     * @~chinese 一个特定的目标节点。
     */
    inline void setTarget(Node *target) { _target = target; }

    /** @~english Return the original Target. 
     *
     * @~chinese 返回原始目标节点。
     * 
     * @return @~english The original Target.
     * @~chinese 原始的目标节点。
     */
    inline Node* getOriginalTarget() const { return _originalTarget; }

    /** @~english
     * Set the original target, since target can be nil.
     * The original target is the target that were used to run the action. Unless you are doing something complex, like ActionManager, you should NOT call this method.
     * The target is 'assigned', it is not 'retained'.
     * @~chinese 
     * 用于设置原始目标节点，因为原始目标节点可能为空。
     * 原始目标节点是曾经被用来运行这个动作的节点。除非你需要做一些复杂操作，像ActionManager，否则你不应该调用这个方法。
     * 原始目标节点被设置后，不会自动调用`retain`函数增加其引用。
     * @since v0.8.2
     *
     * @param originalTarget @~english Is 'assigned', it is not 'retained'.
     * @~chinese 原始目标节点，它将被赋值给属性，但不会增加引用计数。
     */
    inline void setOriginalTarget(Node *originalTarget) { _originalTarget = originalTarget; }
    
    /** @~english Returns a tag that is used to identify the action easily. 
     *
     * @~chinese 返回一个用于识别动作的标签。
     * 
     * @return @~english A tag.
     * @~chinese 一个标签。
     */
    inline int getTag() const { return _tag; }

    /** @~english Changes the tag that is used to identify the action easily. 
     *
     * @~chinese 更改标签，用于识别动作。
     * 
     * @param tag @~english Used to identify the action easily.
     * @~chinese 用于识别动作的标签。
     */
    inline void setTag(int tag) { _tag = tag; }
    /** Returns a flag field that is used to group the actions easily.
     *
     * @return A tag.
     */
    inline unsigned int getFlags() const { return _flags; }
    /** Changes the flag field that is used to group the actions easily.
     *
     * @param tag Used to identify the action easily.
     */
    inline void setFlags(unsigned int flags) { _flags = flags; }

CC_CONSTRUCTOR_ACCESS:
    Action();
    virtual ~Action();

protected:
    Node    *_originalTarget;

    /** @~english
     * The "target".
     * The target will be set with the 'startWithTarget' method.
     * When the 'stop' method is called, target will be set to nil.
     * The target is 'assigned', it is not 'retained'.
     * @~chinese 
     * 目标节点。
     * 目标节点将在`startWithTarget`方法中被调用。
     * `stop`方法被调用时，目标节点将被设置为空。
     * 目标节点不会增加节点的引用计数。
     */
    Node    *_target;

    /** @~english The action tag. An identifier of the action.  @~chinese 用于标识动作的标签。*/
    int     _tag;
    /** The action flag field. To categorize action into certain groups.*/
    unsigned int _flags;

#if CC_ENABLE_SCRIPT_BINDING
    ccScriptType _scriptType;         ///< type of script binding, lua or javascript
#endif
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Action);
};

/** @class FiniteTimeAction
 * @brief @~english 
 * Base class actions that do have a finite time duration.
 * Possible actions:
 * - An action with a duration of 0 seconds.
 * - An action with a duration of 35.5 seconds.
 * Infinite time actions are valid.
 * @~chinese 
 * 所有有限时间动作的基类。
 * 可能的动作:
 * - 一个持续时间为0秒的动作。
 * - 一个持续时间为35.5秒的动作。
 * 无限时间的动作是有效的。
 */
class CC_DLL FiniteTimeAction : public Action
{
public:

    /** @~english Get duration in seconds of the action. 
     *
     * @~chinese 得到动作以秒为单位的持续时间。
     * 
     * @return @~english The duration in seconds of the action.
     * @~chinese 以秒为单位的持续时间。
     */
    inline float getDuration() const { return _duration; }

    /** @~english Set duration in seconds of the action. 
     *
     * @~chinese 设置动作以秒为单位的持续时间。
     * 
     * @param duration @~english In seconds of the action.
     * @~chinese 以秒为单位的持续时间。
     */
    inline void setDuration(float duration) { _duration = duration; }

    //
    // Overrides
    //
    virtual FiniteTimeAction* reverse() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
    virtual FiniteTimeAction* clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

CC_CONSTRUCTOR_ACCESS:
    FiniteTimeAction()
    : _duration(0)
    {}
    virtual ~FiniteTimeAction(){}

protected:
    //! Duration in seconds.
    float _duration;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FiniteTimeAction);
};

class ActionInterval;
class RepeatForever;

/** @class Speed
 * @brief @~english Changes the speed of an action, making it take longer (speed>1)
 * or less (speed<1) time.
 * Useful to simulate 'slow motion' or 'fast forward' effect.
 * @~chinese 改变一个动作的速度，使它的执行使用更长的时间（speed>1）或更少（speed<1）
 * 可以有效得模拟“慢动作”或“快进”的效果。
 * @warning @~english This action can't be Sequenceable because it is not an IntervalAction.
 * @~chinese 这个动作不能被添加到`Sequence`中，因为它不是一个`IntervalAction`。
 */
class CC_DLL Speed : public Action
{
public:
    /** @~english Create the action and set the speed.
     *
     * @~chinese 创建速度动作并设置其速度。
     * 
     * @param action @~english An action.
     * @~chinese 一个动作。
     * @param speed @~english The action speed.
     * @~chinese 动作速度。
     */
    static Speed* create(ActionInterval* action, float speed);

    /** @~english Return the speed.
     *
     * @~chinese 返回目标动作执行的速度。
     * 
     * @return @~english The action speed.
     * @~chinese 动作速度。
     */
    inline float getSpeed(void) const { return _speed; }

    /** @~english Alter the speed of the inner action in runtime. 
     *
     * @~chinese 改变目标动作执行的速度。
     * 
     * @param speed @~english Alter the speed of the inner action in runtime.
     * @~chinese 改变目标动作在执行时的速度。
     */
    inline void setSpeed(float speed) { _speed = speed; }

    /** @~english Replace the interior action.
     *
     * @~chinese 重设目标动作。
     * 
     * @param action @~english The new action, it will replace the running action.
     * @~chinese 新的动作，它将取代当前的目标动作。
     */
    void setInnerAction(ActionInterval *action);

    /** @~english Return the interior action.
     *
     * @~chinese 返回当前的目标动作。
     * 
     * @return @~english The interior action.
     * @~chinese 当前的目标动作。
     */
    inline ActionInterval* getInnerAction() const { return _innerAction; }

    //
    // Override
    //
    virtual Speed* clone() const override;
    virtual Speed* reverse() const override;
    virtual void startWithTarget(Node* target) override;
    virtual void stop() override;
    virtual void step(float dt) override;

    /** @~english Return true if the action has finished.
     *
     * @~chinese 如果动作已经完成则返回true，否则返回false。
     * 
     * @return @~english Is true if the action has finished.
     * @~chinese 如果动作已经完成则返回true，否则返回false。
     */
    virtual bool isDone() const  override;
    
CC_CONSTRUCTOR_ACCESS:
    Speed();
    virtual ~Speed(void);

    /** @~english Initializes the action.  @~chinese 初始化动作。*/
    bool initWithAction(ActionInterval *action, float speed);

protected:
    float _speed;
    ActionInterval *_innerAction;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Speed);
};

/** @class Follow
 * @brief @~english Follow is an action that "follows" a node.
 * Instead of using Camera as a "follower", use this action instead.
 * Eg:
 * @~chinese Follow是一个追踪某个节点的动作。 
 * 与其使用相机去追踪一个动作，你可以使用这个动作达到同样的效果。
 * 例如:
 * @code
 * layer->runAction(Follow::actionWithTarget(hero));
 * @endcode
 * @since v0.99.2
 */
class CC_DLL Follow : public Action
{
public:

    /**@~english
     * Creates the action with a set boundary or with no boundary.
     *
     * @~chinese 
     * 创建追踪动作，并可以选择设置一组边界。
     * 
     * @param followedNode  @~english The node to be followed.
     * @~chinese 被追踪的目标节点。
     * @param rect  @~english The boundary. If rect is equal to Rect::ZERO, it'll work
     *              with no boundary.
     * @~chinese 追踪的边界。如果矩形等于`Rect::ZERO`，等同于没有边界。
     */
    static Follow* create(Node *followedNode, const Rect& rect = Rect::ZERO);
    
    /** @~english Return whether the boundarySet is opened.
     *
     * @~chinese 返回是否开启追踪边界.
     * 
     * @return @~english Return boundary activated or not.
     * @~chinese 是否开启追踪边界。
     */
    inline bool isBoundarySet() const { return _boundarySet; }

    /** @~english Ater behavior - turn on/off the boundary. 
     *
     * @~chinese 用来开启或关闭追踪边界
     * 
     * @param value @~english Turn on/off the boundary.
     * @~chinese 开启或关闭追踪边界
     */
    inline void setBoundarySet(bool value) { _boundarySet = value; }
    
    /** @deprecated 
     * @~english Ater behavior - turn on/off the boundary. 
     *
     * @~chinese 用来开启或关闭追踪边界
     * 
     * @param value @~english Turn on/off the boundary.
     * @~chinese 开启或关闭追踪边界
     */
    CC_DEPRECATED_ATTRIBUTE inline void setBoudarySet(bool value) { setBoundarySet(value); }

    //
    // Override
    //
    virtual Follow* clone() const override;
    virtual Follow* reverse() const override;
    virtual void step(float dt) override;
    virtual bool isDone() const override;
    virtual void stop() override;

CC_CONSTRUCTOR_ACCESS:

    /**
     * @js ctor
     */
    Follow()
    : _followedNode(nullptr)
    , _boundarySet(false)
    , _boundaryFullyCovered(false)
    , _leftBoundary(0.0)
    , _rightBoundary(0.0)
    , _topBoundary(0.0)
    , _bottomBoundary(0.0)
    , _worldRect(Rect::ZERO)
    {}

    /**
     * @js NA
     * @lua NA
     */
    virtual ~Follow();
    
    /**@~english
     * Initializes the action with a set boundary or with no boundary.
     *
     * @~chinese 
     * 初始化追踪动作，可以选择设置一组追踪边界。
     * 
     * @param followedNode  @~english The node to be followed.
     * @~chinese 被追踪的节点。
     * @param rect  @~english The boundary. If rect is equal to Rect::ZERO, it'll work
     *              with no boundary.
     * @~chinese 追踪的边界。如果矩形等于`Rect::ZERO`，等同于没有边界。
     */
    bool initWithTarget(Node *followedNode, const Rect& rect = Rect::ZERO);

protected:

    /** @~english Node to follow.  @~chinese 被追踪的节点*/
    Node *_followedNode;

    /** @~english Whether camera should be limited to certain area.  @~chinese 相机是否应该被限制在特定的区域。*/
    bool _boundarySet;

    /** @~english If screen size is bigger than the boundary - update will not be needed.  @~chinese 如果屏幕尺寸比边界更大，则不需要更新。*/
    bool _boundaryFullyCovered;

    /** @~english Fast access to the screen dimensions.  @~chinese 快速访问屏幕尺寸。*/
    Vec2 _halfScreenSize;
    Vec2 _fullScreenSize;

    /** @~english World boundaries.  @~chinese 世界的边界。*/
    float _leftBoundary;
    float _rightBoundary;
    float _topBoundary;
    float _bottomBoundary;
    Rect _worldRect;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Follow);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTIONS_CCACTION_H__

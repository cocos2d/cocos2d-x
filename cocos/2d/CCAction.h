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

NS_CC_BEGIN

class Node;
/**
 * @addtogroup actions
 * @{
 */

/** 
@brief Action类是所有动作对象的基类.
 */
class CC_DLL Action : public Ref, public Clonable
{
public:
    /// 所有Action对象的缺省tag值
    static const int INVALID_TAG = -1;
    /**
     * @js NA
     * @lua NA
     */
    virtual std::string description() const;

	/** 返回action的克隆对象 */
	virtual Action* clone() const = 0;

    /** 返回执行与本Action对象相反操作的新Action对象 */
	virtual Action* reverse() const = 0;

    //! 当action完成时返回true
    virtual bool isDone() const;

    //! 方法在action开始前调用, 操作会设置执行Action的目标对象为target.
    virtual void startWithTarget(Node *target);

    /** 
    方法在action完成之后调用，它将执行Action的target对象设置为nil.
    IMPORTANT: 你不应该直接去调用 "action->stop()" 方法, 而应该调用 "target->stopAction(action);"
    */
    virtual void stop();

    //! 这个方法每一帧都会被调用, 参数dt为两帧之间的时间间隔(单位秒). 除非你知道正在做什么否则不要重载这个方法.
    virtual void step(float dt);

    /** 
    每一帧都会调用这个方法，参数time是一个在0和1之间的值

    time的含义举例: 
    - 0 表示action刚刚开始
    - 0.5 表示action执行到正中间
    - 1 表示action已经执行完毕
    */
    virtual void update(float time);
    
    inline Node* getTarget() const { return _target; }
    /** 这个方法更改action的target属性. */
    inline void setTarget(Node *target) { _target = target; }
    
    inline Node* getOriginalTarget() const { return _originalTarget; }
    /** 设置action的原始目标对象target, 当target为nil时setOriginalTarget设置的对象会运行这个action
    除非你要像ActionManager类那样做一些很复杂的操作，否则不要调用这个方法
    本方法只是对originalTarget的弱引用（assigned），没有进行retain操作。
    @since v0.8.2
    */
    inline void setOriginalTarget(Node *originalTarget) { _originalTarget = originalTarget; }

    inline int getTag() const { return _tag; }
    inline void setTag(int tag) { _tag = tag; }

protected:
    Action();
    virtual ~Action();

    Node    *_originalTarget;
    /** action动作的执行目标target.
    在 'startWithTarget' 方法中会对target进行设置.
    当 'stop' 方法被调用时, target会被设置为nil.
    target 是弱引用（assigned），没有进行retain操作.
    */
    Node    *_target;
    /** action的tag属性. 是action的一个标识 */
    int     _tag;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Action);
};

/** 
@brief 
 FiniteTimeAction类是所有在限时间能够完成的动作（action）的基类
 可以是下列动作:
   - 持续时间为0秒的action
   - 持续时间为35.5秒的action

 持续无限时间的action是有效地
 */
class CC_DLL FiniteTimeAction : public Action
{
public:
    //! 返回action的持续时间（单位：秒）
    inline float getDuration() const { return _duration; }
    //! 设置action的持续时间（单位：秒）
    inline void setDuration(float duration) { _duration = duration; }

    //
    // Overrides
    //
    virtual FiniteTimeAction* reverse() const override = 0;
	virtual FiniteTimeAction* clone() const override = 0;

protected:
    FiniteTimeAction()
	: _duration(0)
    {}
    virtual ~FiniteTimeAction(){}

    //! 以秒单位的持续时间
    float _duration;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FiniteTimeAction);
};

class ActionInterval;
class RepeatForever;

/** 
 @brief Speed类改变一个action的运行速度, 使他持续更长时间 (speed>1)或者更短的时间(speed<1).
 可以用来模拟慢速动作（'slow motion'）或者快进动作（'fast forward')的效果.

 @warning Speed对象不能作为一个动作序列的一部分, 因为它不是一个IntervalAction对象
 */
class CC_DLL Speed : public Action
{
public:
    /** 创建action对象 */
    static Speed* create(ActionInterval* action, float speed);

    inline float getSpeed(void) const { return _speed; }
    /** 在运行时改变内部action的速度 */
    inline void setSpeed(float speed) { _speed = speed; }


    void setInnerAction(ActionInterval *action);

    inline ActionInterval* getInnerAction() const { return _innerAction; }

    //
    // Override
    //
	virtual Speed* clone() const override;
    virtual Speed* reverse() const override;
    virtual void startWithTarget(Node* target) override;
    virtual void stop() override;
    virtual void step(float dt) override;
    virtual bool isDone() const  override;
    
CC_CONSTRUCTOR_ACCESS:
    Speed();
    virtual ~Speed(void);
    /** 初始化action */
    bool initWithAction(ActionInterval *action, float speed);

protected:
    float _speed;
    ActionInterval *_innerAction;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Speed);
};

/** 
@brief Follow是一种“跟随”某一个节点的动作.

示例代码:
@code
layer->runAction(Follow::actionWithTarget(hero));
@endcode

不要使用Camera作为一个跟随者，使用这个类
@since v0.99.2
*/
class CC_DLL Follow : public Action
{
public:
    /**
     * 创建action 可以有边界，也可以没有.
     *
     * @param followedNode  要跟随的Node.
     * @param rect  边界. 当 \p rect 为 Rect::ZERO时 表示没有边界.
     */
    static Follow* create(Node *followedNode, const Rect& rect = Rect::ZERO);

    inline bool isBoundarySet() const { return _boundarySet; }
    /** 调用这个方法打开或关闭边界 */
    inline void setBoudarySet(bool value) { _boundarySet = value; }

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
    
    /**
     * 初始化action 可以提供边界，也可以比提供
     *
     * @param followedNode  The node to be followed.
     * @param rect  The boundary. If \p rect is equal to Rect::ZERO, it'll work
     *              with no boundary.
     */
    bool initWithTarget(Node *followedNode, const Rect& rect = Rect::ZERO);

protected:
    // 要跟随的node
    Node *_followedNode;

    // 是否相机要被限制在中心
    bool _boundarySet;

    // 当屏幕尺寸比边界大时 不需要进行更新
    bool _boundaryFullyCovered;

    // 保存屏幕尺寸用来快速访问
    Vec2 _halfScreenSize;
    Vec2 _fullScreenSize;

    // 世界坐标的边界范围
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

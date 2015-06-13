/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __ACTION_CCINTERVAL_ACTION_H__
#define __ACTION_CCINTERVAL_ACTION_H__

#include <vector>

#include "2d/CCAction.h"
#include "2d/CCAnimation.h"
#include "base/CCProtocols.h"
#include "base/CCVector.h"

NS_CC_BEGIN

class Node;
class SpriteFrame;
class EventCustom;

/**
 * @addtogroup actions
 * @{
 */

/** @class ActionInterval
 * @brief @~english An interval action is an action that takes place within a certain period of time.
 * It has an start time, and a finish time. The finish time is the parameter duration plus the start time.
 * 
 * These ActionInterval actions have some interesting properties, like:
 * - They can run normally (default)
 * - They can run reversed with the reverse method
 * - They can run with the time altered with the Accelerate, AccelDeccel and Speed actions.
 * 
 * For example, you can simulate a Ping Pong effect running the action normally and
 * then running it again in Reverse mode.
 * 
 * Example:
 * 
 * @~chinese 时间间隔动作（ActionInterval）是一个在一段时间内执行的动作。
 * 它有一个开始时间和完成时间。完成时间等于起始时间加上持续时间
 * 
 * 这些ActionInterval动作有一些有趣的特性,如:
 * - 他们可以正常运行(默认)
 * - 他们可以通过逆转方法逆转运行效果
 * - 他们在运行时可以通过加速度（Accelerate），加速减速（AccelDeccel）和速度（Speed）等动作来修改它的运行时间轴。
 * 
 * 例如，你想要模拟乒乓球效果，可以执行一个动作再反向执行一次同样的动作
 * 
 * 例子:
 * 
 * @code
 * Action *pingPongAction = Sequence::actions(action, action->reverse(), nullptr);
 * @endcode
 */
class CC_DLL ActionInterval : public FiniteTimeAction
{
public:
    /** @~english How many seconds had elapsed since the actions started to run.
     *
     * @~chinese 获取从动作开始运行已经过去了多长时间。
     * 
     * @return @~english The seconds had elapsed since the ations started to run.
     * @~chinese 从动作开始运行已经过去了多长时间。
     */
    inline float getElapsed(void) { return _elapsed; }

    /** @~english Sets the amplitude rate, extension in GridAction
     *
     * @~chinese 设置振幅衰减率，用于GridAction的扩展
     * 
     * @param amp   @~english The ampliture rate.
     * @~chinese 振幅衰减率。
     */
    void setAmplitudeRate(float amp);
    
    /** @~english Gets the ampliture rate, extension in GridAction
     *
     * @~chinese 获取振幅衰减率，用于GridAction的扩展
     * 
     * @return @~english  The ampliture rate.
     * @~chinese 振幅衰减率。
     */
    float getAmplitudeRate(void);

    //
    // Overrides
    //
    virtual bool isDone(void) const override;
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    virtual ActionInterval* reverse() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

    virtual ActionInterval *clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

CC_CONSTRUCTOR_ACCESS:
    /** @~english initializes the action with the duration.
     * @~chinese 使用持续时间初始化动作 
     * @param d @~english The duration @~chinese 持续时间
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese 如果初始化成功则返回true，否则返回false
     */
    bool initWithDuration(float d);

protected:
    float _elapsed;
    bool _firstTick;
};

/** @class Sequence
 * @brief @~english Runs actions sequentially, one after another.
 * @~chinese 顺序动作（Sequnce）可以顺序得一个接着一个运行内部动作序列。
 */
class CC_DLL Sequence : public ActionInterval
{
public:
    /// @{ Constructor functions
    /// @brief @~english @~chinese 构造函数

    /**
     * @~english Helper constructor to create an array of sequenceable actions.
     *
     * @~chinese 用于创建一个可以按序列执行动作的Sequence动作对象的一系列辅助构造函数
     * 
     * @return @~english An autoreleased Sequence object.
     * @~chinese 一个自释放的Sequence动作对象，如果创建失败则返回空指针。
     */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported
    typedef FiniteTimeAction* M;
    static Sequence* create(M m1, std::nullptr_t listEnd) { return variadicCreate(m1, NULL); }
    static Sequence* create(M m1, M m2, std::nullptr_t listEnd) { return variadicCreate(m1, m2, NULL); }
    static Sequence* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for variable argument lists longer than 10 items, use the other create functions or variadicCreate with NULL as the last argument
    static Sequence* variadicCreate(FiniteTimeAction* item, ...);
#else
    static Sequence* create(FiniteTimeAction *action1, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

    /** @~english Helper constructor to create an array of sequenceable actions given an array.
     * @~chinese 使用指定动作数组来创建可以按序列执行的Sequence动作对象。
     * @code
     * When this funtion bound to the js or lua,the input params changed
     * in js  :var   create(var   object1,var   object2, ...)
     * in lua :local create(local object1,local object2, ...)
     * @endcode
     *
     * @param arrayOfActions @~english An array of sequenceable actions.
     * @~chinese 动作数组。
     * @return @~english An autoreleased Sequence object.
     * @~chinese 一个自释放Sequence对象，如果创建失败则返回空指针。
     */
    static Sequence* create(const Vector<FiniteTimeAction*>& arrayOfActions);
    /** @~english Helper constructor to create an array of sequence-able actions.
     *
     * @~chinese 用动作列表创建可以按序列执行的Sequence动作对象。
     * 
     * @param action1 @~english The first sequenceable action.
     * @~chinese 动作序列中的第一个动作。
     * @param args @~english The variable list variable.
     * @~chinese 动作列表变量。
     * @return @~english An autoreleased Sequence object.
     * @~chinese 一个自释放的Sequence对象，如果创建失败则返回空指针。
     * @js NA
     */
    static Sequence* createWithVariableList(FiniteTimeAction *action1, va_list args);
    /** @~english Creates the action with two actions.
     * @~chinese 用两个动作创建Sequence动作。
     * @param actionOne @~english The first sequenceable action.
     * @~chinese 第一个动作。
     * @param actionTwo @~english The second sequenceable action.
     * @~chinese 第二个动作。
     * @return @~english An autoreleased Sequence object.
     * @~chinese 一个自释放Sequence动作对象，如果创建失败则返回空指针。
     * @js NA
     */
    static Sequence* createWithTwoActions(FiniteTimeAction *actionOne, FiniteTimeAction *actionTwo);

    /// @} Constructor functions

    //
    // Overrides
    //
    virtual Sequence* clone() const override;
    virtual Sequence* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float t) override;
    
CC_CONSTRUCTOR_ACCESS:
    Sequence() {}
    virtual ~Sequence(void);

    /** @~english initializes the action  @~chinese 用两个动作初始化动作 */
    bool initWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo);

protected:
    FiniteTimeAction *_actions[2];
    float _split;
    int _last;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Sequence);
};

/** @class Repeat
 * @brief @~english Repeats an action a number of times.
 * To repeat an action forever use the RepeatForever action.
 * @~chinese 重复动作（Repeat）可以按一定次数重复一个动作。
 * 使用RepeatForever动作来永远重复一个动作。
 */
class CC_DLL Repeat : public ActionInterval
{
public:
    /** @~english Creates a Repeat action. Parameter `times` is an unsigned integer between 1 and pow(2,30).
     *
     * @~chinese 创建一个重复动作，`times`参数是一个取值在1和`pow(2, 30)`之间的整数。
     * 
     * @param action @~english The action needs to repeat.
     * @~chinese 需要重复的目标动作。
     * @param times @~english The repeat times.
     * @~chinese 重复次数。
     * @return @~english An autoreleased Repeat object.
     * @~chinese 一个自释放的Repeat对象，如果创建失败则返回空指针。
     */
    static Repeat* create(FiniteTimeAction *action, unsigned int times);

    /** @~english Sets the inner action.
     *
     * @~chinese 设置内部动作。
     * 
     * @param action @~english The inner action.
     * @~chinese 内部动作。
     */
    inline void setInnerAction(FiniteTimeAction *action)
    {
        if (_innerAction != action)
        {
            CC_SAFE_RETAIN(action);
            CC_SAFE_RELEASE(_innerAction);
            _innerAction = action;
        }
    }

    /** @~english Gets the inner action.
     *
     * @~chinese 获取内部动作。
     * 
     * @return @~english The inner action.
     * @~chinese 内部动作。
     */
    inline FiniteTimeAction* getInnerAction()
    {
        return _innerAction;
    }

    //
    // Overrides
    //
    virtual Repeat* clone() const override;
    virtual Repeat* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float dt) override;
    virtual bool isDone(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    Repeat() {}
    virtual ~Repeat();

    /** @~english initializes a Repeat action. Times is an unsigned integer between 1 and pow(2,30)  
     * @~chinese 初始化Repeat动作。`times`参数是一个取值在1和`pow(2, 30)`之间的整数。
     * @param pAction @~english The action needs to repeat.
     * @~chinese 需要重复的目标动作。
     * @param times @~english The repeat times.
     * @~chinese 重复次数。
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese 如果初始化成功则返回true，否则返回false
     */
    bool initWithAction(FiniteTimeAction *pAction, unsigned int times);

protected:
    unsigned int _times;
    unsigned int _total;
    float _nextDt;
    bool _actionInstant;
    /** @~english Inner action  @~chinese 内部动作 */
    FiniteTimeAction *_innerAction;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Repeat);
};

/** @class RepeatForever
 * @brief @~english Repeats an action forever.
 * To repeat the an action for a limited number of times use the Repeat action.
 * @~chinese 永远地重复一个动作。
 * 有限次数内重复一个动作请使用Repeat动作。
 * @warning @~english This action can't be Sequenceable because it is not an finite time action.
 * @~chinese 这个动作不能用来组成序列动作，因为它不是一个有限时间动作。
 */
class CC_DLL RepeatForever : public ActionInterval
{
public:
    /** @~english Creates the action with an inner action.
     *
     * @~chinese 用内部动作创建一个RepeatForever动作。
     * 
     * @param action @~english The action need to repeat forever.
     * @~chinese 内部动作，这个动作会永远重复。
     * @return @~english An autoreleased RepeatForever object.
     * @~chinese 一个自释放的RepeatForever动作，如果创建失败则返回空指针。
     */
    static RepeatForever* create(ActionInterval *action);

    /** @~english Sets the inner action.
     *
     * @~chinese 设置内部动作。
     * 
     * @param action @~english The inner action.
     * @~chinese 内部动作。
     */
    inline void setInnerAction(ActionInterval *action)
    {
        if (_innerAction != action)
        {
            CC_SAFE_RELEASE(_innerAction);
            _innerAction = action;
            CC_SAFE_RETAIN(_innerAction);
        }
    }

    /** @~english Gets the inner action.
     *
     * @~chinese 获取内部动作。
     * 
     * @return @~english The inner action.
     * @~chinese 内部动作。
     */
    inline ActionInterval* getInnerAction()
    {
        return _innerAction;
    }

    //
    // Overrides
    //
    virtual RepeatForever* clone() const override;
    virtual RepeatForever* reverse(void) const override;
    virtual void startWithTarget(Node* target) override;
    virtual void step(float dt) override;
    virtual bool isDone(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    RepeatForever()
    : _innerAction(nullptr)
    {}
    virtual ~RepeatForever();

    /** @~english initializes the action  @~chinese 用内部动作初始化动作 */
    bool initWithAction(ActionInterval *action);

protected:
    /** @~english Inner action  @~chinese 内部动作 */
    ActionInterval *_innerAction;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RepeatForever);
};

/** @class Spawn
 * @brief @~english Spawn a group of actions
 * @~chinese 同步动作（Spawn）用于同步执行一组动作
 */
class CC_DLL Spawn : public ActionInterval
{
public:
    /// @{ Constructor functions
    /// @brief @~english @~chinese 构造函数

    /** @~english Helper constructor to create an array of spawned actions.
     * When this funtion bound to the js or lua, the input params changed.
     * @~chinese 创建包含一组同步动作的Spawn动作的辅助构造函数。
     * 当这个函数绑定到js和lua中，参数会发生变化
     *
     * @code
     * in lua :local create(local object1,local object2, ...)
     * @endcode
     *
     * @return @~english An autoreleased Spawn object.
     * @~chinese 一个自释放Spawn对象，如果创建失败则返回空指针。
     */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported.
    typedef FiniteTimeAction* M;
    static Spawn* create(M m1, std::nullptr_t listEnd) { return variadicCreate(m1, NULL); }
    static Spawn* create(M m1, M m2, std::nullptr_t listEnd) { return variadicCreate(m1, m2, NULL); }
    static Spawn* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for variable argument lists longer than 10 items, use the other create functions or createSpawn with NULL as the last argument.
    static Spawn* variadicCreate(FiniteTimeAction* item, ...);
#else
    static Spawn* create(FiniteTimeAction *action1, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

    /** @~english Helper constructor to create an array of spawned actions. 
     *
     * @~chinese 用一个动作列表创建Spawn动作。
     * 
     * @param action1   @~english The first inner action.
     * @~chinese 第一个同步的内部动作。
     * @param args  @~english The va_list variable.
     * @~chinese 动作列表变量.
     * @return @~english  An autoreleased Spawn object.
     * @~chinese 一个自释放的Spawn对象，如果创建失败则返回空指针。
     * @js NA
     */
    static Spawn* createWithVariableList(FiniteTimeAction *action1, va_list args);

    /** @~english Helper constructor to create an array of spawned actions given an array.
     *
     * @~chinese 用一个给定数组创建一个Spawn动作。
     * 
     * @param arrayOfActions    @~english An array of spawned actions.
     * @~chinese 一个同步动作数组。
     * @return @~english  An autoreleased Spawn object.
     * @~chinese 一个自释放的Spawn对象，如果创建失败则返回空指针。
     */
    static Spawn* create(const Vector<FiniteTimeAction*>& arrayOfActions);

    /** @~english Creates the Spawn action with two spawned actions.
     *
     * @~chinese 用两个同步动作创建Spawn动作。
     * 
     * @param action1   @~english The first spawned action.
     * @~chinese 第一个同步动作。
     * @param action2   @~english THe second spawned action.
     * @~chinese 第二个同步动作。
     * @return @~english An autoreleased Spawn object.
     * @~chinese 一个自释放的Spawn对象，如果创建失败则返回空指针。
     * @js NA
     */
    static Spawn* createWithTwoActions(FiniteTimeAction *action1, FiniteTimeAction *action2);
    /// @}

    //
    // Overrides
    //
    virtual Spawn* clone() const override;
    virtual Spawn* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Spawn() {}
    virtual ~Spawn();

    /** @~english initializes the Spawn action with the 2 actions to spawn  
     * @~chinese 用两个同步动作初始化Spawn动作
     * @param action1   @~english The first spawned action.
     * @~chinese 第一个同步动作。
     * @param action2   @~english THe second spawned action.
     * @~chinese 第二个同步动作。
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese 如果初始化成功则返回true，否则返回false
     */
    bool initWithTwoActions(FiniteTimeAction *action1, FiniteTimeAction *action2);

protected:
    FiniteTimeAction *_one;
    FiniteTimeAction *_two;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Spawn);
};

/** @class RotateTo
 * @brief @~english Rotates a Node object to a certain angle by modifying it's rotation attribute.
 * The direction will be decided by the shortest angle.
 * @~chinese RotateTo动作用来旋转一个节点对象到一定角度，通过逐帧修改它的`rotation`属性。
 * 旋转方向将由最短的角度决定。
 */ 
class CC_DLL RotateTo : public ActionInterval
{
public:
    /** @~english
     * Creates the action with duration and separate rotation angles.
     *
     * @~chinese 
     * 用持续时间与X,Y轴独立的旋转角度来创建RotateTo动作。
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param dstAngleX @~english Destination angle x in degrees.
     * @~chinese X轴的目标角度，以角度值计。
     * @param dstAngleY @~english Destination angle y in degrees.
     * @~chinese Y轴的目标角度，以角度值计
     * @return @~english An autoreleased RotateTo object.
     * @~chinese 一个自释放的RotateTo对象，如果创建失败则返回空指针。
     */
    static RotateTo* create(float duration, float dstAngleX, float dstAngleY);

    /** @~english
     * Creates the action with duration and destination angle.
     *
     * @~chinese 
     * 用持续时间和目标角度创建RotateTo动作。
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param dstAngle @~english Destination angle in degrees.
     * @~chinese 目标角度，以角度值计。
     * @return @~english An autoreleased RotateTo object.
     * @~chinese 一个自释放的RotateTo对象，如果创建失败则返回空指针。
     */
    static RotateTo* create(float duration, float dstAngle);

    /** @~english
     * Creates the action with 3D rotation angles.
     * @~chinese 
     * 创建一个旋转到三维旋转角度的RotateTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param dstAngle3D @~english A Vec3 angle.
     * @~chinese 三维旋转角度。
     * @return @~english An autoreleased RotateTo object.
     * @~chinese 一个自释放的RotateTo对象，如果创建失败则返回空指针。
     */
    static RotateTo* create(float duration, const Vec3& dstAngle3D);

    //
    // Overrides
    //
    virtual RotateTo* clone() const override;
    virtual RotateTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    RotateTo();
    virtual ~RotateTo() {}

    /** @~english
     * initializes the action
     * @~chinese 
     * 初始化动作
     * @param duration @~english Duration in seconds
     * @~chinese 持续时间，以秒为单位
     * @param dstAngleX @~english Destination angle x in degrees.
     * @~chinese X轴的目标角度，以角度值计。
     * @param dstAngleY @~english Destination angle y in degrees.
     * @~chinese Y轴的目标角度，以角度值计。
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese 如果初始化成功则返回true，否则返回false
     */
    bool initWithDuration(float duration, float dstAngleX, float dstAngleY);
    /**@~english
     * initializes the action
     * @~chinese 
     * 初始化动作
     * @param duration @~english Duration in seconds
     * @~chinese 持续时间，以秒为单位
     * @param dstAngle3D @~english A Vec3 angle.
     * @~chinese 三维旋转角度。
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese 如果初始化成功则返回true，否则返回false
     */
    bool initWithDuration(float duration, const Vec3& dstAngle3D);

    /** @~english
     * Calculates the start and diff angles
     * @~chinese 
     * 计算开始和旋转角度差值。
     * @param startAngle @~english Start angle in degrees
     * @~chinese 起始角度，以角度值计，用于保存计算结果
     * @param diffAngle @~english Angle difference between start angle and destination angle in degrees
     * @~chinese 起始角度和目标角度之间的差值，以角度值计，用于保存计算结果
     * @param dstAngle @~english Destination angle in degrees
     * @~chinese 目标角度，以角度值计
     */
    void calculateAngles(float &startAngle, float &diffAngle, float dstAngle);
    
protected:
    bool _is3D;
    Vec3 _dstAngle;
    Vec3 _startAngle;
    Vec3 _diffAngle;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RotateTo);
};

/** @class RotateBy
 * @brief @~english Rotates a Node object clockwise a number of degrees by modifying it's rotation attribute.
 * @~chinese RotateBy动作可以顺时针旋转一个节点对象，通过修改它的旋转属性。
*/
class CC_DLL RotateBy : public ActionInterval
{
public:
    /** @~english
     * Creates the action with duration and delta angle to rotate.
     *
     * @~chinese 
     * 用持续时间和旋转角度创建RotateBy动作。
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param deltaAngle @~english Delta angle in degrees.
     * @~chinese 旋转角度。
     * @return @~english An autoreleased RotateBy object.
     * @~chinese 一个自释放的RotateBy对象，如果创建失败则返回空指针。
     */
    static RotateBy* create(float duration, float deltaAngle);
    /**@~english
     * Creates the action with separate rotation angles.
     *
     * @~chinese 
     * 用X，Y轴独立的旋转角度创建RotateBy动作。
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param deltaAngleZ_X @~english Delta angle x in degrees.
     * @~chinese X轴旋转角度，以角度值计。
     * @param deltaAngleZ_Y @~english Delta angle y n degreesCW.
     * @~chinese Y轴旋转角度，以角度值计。
     * @return @~english An autoreleased RotateBy object.
     * @~chinese 一个自释放的RotateBy对象，如果创建失败则返回空指针。
     * @warning @~english The physics body contained in Node doesn't support rotate with different x and y angle.
     * @~chinese 包含的物理身体的节点不支持用x和y轴分离的旋转角度。
     */
    static RotateBy* create(float duration, float deltaAngleZ_X, float deltaAngleZ_Y);
    /** @~english Creates the action with 3D rotation angles.
     *
     * @~chinese 用持续时间和三维旋转角度创建RotateBy动作。
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param deltaAngle3D @~english A Vec3 angle.
     * @~chinese 三维旋转角度。
     * @return @~english An autoreleased RotateBy object.
     * @~chinese 一个自释放的RotateBy对象，如果创建失败则返回空指针。
     */
    static RotateBy* create(float duration, const Vec3& deltaAngle3D);

    //
    // Override
    //
    virtual RotateBy* clone() const override;
    virtual RotateBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    RotateBy();
    virtual ~RotateBy() {}

    /** @~english initializes the action  @~chinese 用持续时间和旋转角度初始化动作 
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param deltaAngle @~english Delta angle in degrees.
     * @~chinese 旋转角度。
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese 如果初始化成功则返回true，否则返回false
     */
    bool initWithDuration(float duration, float deltaAngle);
    /** 
     * @warning @~english The physics body contained in Node doesn't support rotate with different x and y angle.
     * @~chinese 包含的物理身体的节点不支持用x和y轴分离的旋转角度。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param deltaAngleZ_X @~english Delta angle x in degrees.
     * @~chinese X轴旋转角度，以角度值计。
     * @param deltaAngleZ_Y @~english Delta angle y n degreesCW.
     * @~chinese Y轴旋转角度，以角度值计。
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese 如果初始化成功则返回true，否则返回false
     */
    bool initWithDuration(float duration, float deltaAngleZ_X, float deltaAngleZ_Y);
    /**
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param deltaAngle3D @~english A Vec3 angle.
     * @~chinese 三维旋转角度。
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese 如果初始化成功则返回true，否则返回false
     */
    bool initWithDuration(float duration, const Vec3& deltaAngle3D);
    
protected:
    bool _is3D;
    Vec3 _deltaAngle;
    Vec3 _startAngle;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RotateBy);
};

/** @class MoveBy
 * @brief @~english Moves a Node object by x,y pixels by modifying it's position attribute.
 x and y are relative to the position of the object.
 Several MoveBy actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 * @~chinese MoveBy动作通过修改一个目标节点的位置属性将它移动x，y像素。
 * X轴和Y轴位移是相对于节点位置的，
 * 几个MoveBy操作可以并行，由此产生的位移将是所有个体位移的总和。
 @since v2.1beta2-custom
 */
class CC_DLL MoveBy : public ActionInterval
{
public:
    /** @~english
     * Creates the action with duration and delta position.
     *
     * @~chinese 
     * 用持续时间和位移创建MoveBy动作。
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param deltaPosition @~english The delta distance in 2d, it's a Vec2 type.
     * @~chinese 位移，Vec2类型。
     * @return @~english An autoreleased MoveBy object.
     * @~chinese 一个自释放的MoveBy对象。
     */
    static MoveBy* create(float duration, const Vec2& deltaPosition);
    /**@~english
     * Creates the action with duration and 3d delta position.
     *
     * @~chinese 
     * 用持续时间和三维位移创建MoveBy动作。
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param deltaPosition @~english The delta distance in 3d, it's a Vec3 type.
     * @~chinese 三维位移，Vec3类型。
     * @return @~english An autoreleased MoveBy object.
     * @~chinese 一个自释放的MoveBy对象。
     */
    static MoveBy* create(float duration, const Vec3& deltaPosition);

    //
    // Overrides
    //
    virtual MoveBy* clone() const override;
    virtual MoveBy* reverse(void) const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    MoveBy():_is3D(false) {}
    virtual ~MoveBy() {}

    bool initWithDuration(float duration, const Vec2& deltaPosition);
    bool initWithDuration(float duration, const Vec3& deltaPosition);

protected:
    bool _is3D;
    Vec3 _positionDelta;
    Vec3 _startPosition;
    Vec3 _previousPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MoveBy);
};

/** @class MoveTo
 * @brief @~english Moves a Node object to the position x,y. x and y are absolute coordinates by modifying it's position attribute.
 Several MoveTo actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 * @~chinese MoveTo动作通过修改一个目标节点的位置属性将它移动到特定位置。
 * 几个MoveTo操作可以并行，由此产生的运动将是所有个体运动的总和。
 @since v2.1beta2-custom
 */
class CC_DLL MoveTo : public MoveBy
{
public:
    /** @~english
     * Creates the action with duration and 2d position.
     * @~chinese 
     * 用持续时间和二维世界目标位置创建MoveTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param position @~english The destination position in 2d.
     * @~chinese 二维世界的目标位置。
     * @return @~english An autoreleased MoveTo object.
     * @~chinese 一个自释放的MoveTo对象。
     */
    static MoveTo* create(float duration, const Vec2& position);
    /**@~english
     * Creates the action with duration and 3d position.
     * @~chinese 
     * 用持续时间和三维世界目标位置创建MoveTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param position @~english The destination position in 3d.
     * @~chinese 三维世界目标位置。
     * @return @~english An autoreleased MoveTo object.
     * @~chinese 一个自释放MoveTo对象。
     */
    static MoveTo* create(float duration, const Vec3& position);

    //
    // Overrides
    //
    virtual MoveTo* clone() const override;
    virtual MoveTo* reverse() const  override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    MoveTo() {}
    virtual ~MoveTo() {}

    bool initWithDuration(float duration, const Vec2& position);
    bool initWithDuration(float duration, const Vec3& position);

protected:
    Vec3 _endPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MoveTo);
};

/** @class SkewTo
 * @brief @~english Skews a Node object to given angles by modifying it's skewX and skewY attributes
 * @~chinese SkewTo动作通过修改skewX和skewY属性倾斜一个节点对象到特定的倾斜角度
@since v1.0
*/
class CC_DLL SkewTo : public ActionInterval
{
public:
    /** @~english
     * Creates the SkewTo action with the duration, x and y axis target skew parameters.
     * @~chinese 
     * 用持续时间，X和Y轴目标倾斜角来创建SkewTo动作。
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param sx @~english Skew x angle.
     * @~chinese X轴目标倾斜角度。
     * @param sy @~english Skew y angle.
     * @~chinese Y轴目标倾斜角度。
     * @return @~english An autoreleased SkewTo object.
     * @~chinese 一个自释放的SkewTo对象。
     */
    static SkewTo* create(float t, float sx, float sy);

    //
    // Overrides
    //
    virtual SkewTo* clone() const override;
    virtual SkewTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    SkewTo();
    virtual ~SkewTo() {}
    bool initWithDuration(float t, float sx, float sy);

protected:
    float _skewX;
    float _skewY;
    float _startSkewX;
    float _startSkewY;
    float _endSkewX;
    float _endSkewY;
    float _deltaX;
    float _deltaY;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SkewTo);
};

/** @class SkewBy
* @brief @~english Skews a Node object by skewX and skewY degrees.
 * @~chinese SkewBy动作可以以一定角度倾斜一个节点。
@since v1.0
*/
class CC_DLL SkewBy : public SkewTo
{
public:
    /** @~english
     * Creates the SkewBy action with the duration, x and y axis delta skew parameters.
     * @~chinese 
     * 用持续时间，X和Y轴倾斜角创建动作。
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param deltaSkewX @~english Skew x delta angle.
     * @~chinese X轴倾斜角。
     * @param deltaSkewY @~english Skew y delta angle.
     * @~chinese Y轴倾斜角。
     * @return @~english An autoreleased SkewBy object.
     * @~chinese 一个自释放的SkewBy对象。
     */
    static SkewBy* create(float t, float deltaSkewX, float deltaSkewY);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual SkewBy* clone() const  override;
    virtual SkewBy* reverse(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    SkewBy() {}
    virtual ~SkewBy() {}
    bool initWithDuration(float t, float sx, float sy);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SkewBy);
};

/** @class JumpBy
 * @brief @~english Moves a Node object simulating a parabolic jump movement by modifying it's position attribute.
 * @~chinese JumpBy动作可以模拟抛物线跳运动移动一个节点对象。
*/
class CC_DLL JumpBy : public ActionInterval
{
public:
    /** @~english
     * Creates the JumpBy action with duration, jumping distance, jumping height and number of jumps.
     * @~chinese 
     * 用持续时间，跳跃距离，跳跃高度和次数创建JumpBy动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param position @~english The jumping distance.
     * @~chinese 跳跃的距离。
     * @param height @~english The jumping height.
     * @~chinese 跳跃的高度。
     * @param jumps @~english The jumping times.
     * @~chinese 跳跃次数。
     * @return @~english An autoreleased JumpBy object.
     * @~chinese 一个自释放的JumpBy对象。
     */
    static JumpBy* create(float duration, const Vec2& position, float height, int jumps);

    //
    // Overrides
    //
    virtual JumpBy* clone() const override;
    virtual JumpBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    JumpBy() {}
    virtual ~JumpBy() {}

    bool initWithDuration(float duration, const Vec2& position, float height, int jumps);

protected:
    Vec2           _startPosition;
    Vec2           _delta;
    float           _height;
    int             _jumps;
    Vec2           _previousPos;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpBy);
};

/** @class JumpTo
 * @brief @~english Moves a Node object to a parabolic position simulating a jump movement by modifying it's position attribute.
 * @~chinese JumpTo动作可以模拟抛物线跳运动移动一个节点对象到特定的位置。
*/ 
class CC_DLL JumpTo : public JumpBy
{
public:
    /** @~english
     * Creates the JumpTo action with duration, destination position, jumping height and number of jumps.
     * @~chinese 
     * 用持续时间，目的地位置，跳跃高度和次数创建JumpTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param position @~english The jumping destination position.
     * @~chinese 跳跃的目的地的位置。
     * @param height @~english The jumping height.
     * @~chinese 跳跃的高度。
     * @param jumps @~english The jumping times.
     * @~chinese 跳跃的次数。
     * @return @~english An autoreleased JumpTo object.
     * @~chinese 一个自释放的JumpTo对象。
     */
    static JumpTo* create(float duration, const Vec2& position, float height, int jumps);

    //
    // Override
    //
    virtual void startWithTarget(Node *target) override;
    virtual JumpTo* clone() const override;
    virtual JumpTo* reverse(void) const override;

CC_CONSTRUCTOR_ACCESS:
    JumpTo() {}
    virtual ~JumpTo() {}

    bool initWithDuration(float duration, const Vec2& position, float height, int jumps);

protected:
    Vec2 _endPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpTo);
};

/** @struct ccBezierConfig @~english Bezier configuration structure
 * @~chinese Bezier曲线配置结构体
 */
typedef struct _ccBezierConfig {
    //! end position of the bezier
    Vec2 endPosition;
    //! Bezier control point 1
    Vec2 controlPoint_1;
    //! Bezier control point 2
    Vec2 controlPoint_2;
} ccBezierConfig;

/** @class BezierBy
 * @brief @~english An action that moves the target with a cubic Bezier curve by a certain distance.
 * @~chinese BezierBy动作可以将一个节点沿三次贝塞尔曲线移动一定距离。
 */
class CC_DLL BezierBy : public ActionInterval
{
public:
    /** @~english Creates the action with a duration and a bezier configuration.
     * @~chinese 用持续时间和贝塞尔曲线配置创建BezierBy动作。
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param c @~english Bezier config.
     * @~chinese 贝塞尔曲线配置。
     * @return @~english An autoreleased BezierBy object.
     * @~chinese 一个自释放的BezierBy对象。
     * @code
     * When this function bound to js or lua,the input params are changed.
     * in js: var create(var t,var table)
     * in lua: lcaol create(local t, local table)
     * @endcode
     */
    static BezierBy* create(float t, const ccBezierConfig& c);

    //
    // Overrides
    //
    virtual BezierBy* clone() const override;
    virtual BezierBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    BezierBy() {}
    virtual ~BezierBy() {}

    /** @~english
     * initializes the action with a duration and a bezier configuration
     * @~chinese 
     * 用持续时间和贝塞尔曲线配置初始化BezierBy动作。
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param c @~english Bezier config.
     * @~chinese 贝塞尔曲线配置。
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese 如果初始化成功返回true，否则返回false。
     */
    bool initWithDuration(float t, const ccBezierConfig& c);

protected:
    ccBezierConfig _config;
    Vec2 _startPosition;
    Vec2 _previousPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(BezierBy);
};

/** @class BezierTo
 * @brief @~english An action that moves the target with a cubic Bezier curve to a destination point.
 * @~chinese BezierTo动作可以将一个节点沿三次贝塞尔曲线移动到特定位置。
 @since v0.8.2
 */
class CC_DLL BezierTo : public BezierBy
{
public:
    /** @~english Creates the action with a duration and a bezier configuration.
     * @~chinese 用持续时间和贝塞尔曲线配置创建BezierTo动作。
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param c @~english Bezier config.
     * @~chinese 贝塞尔曲线配置。
     * @return @~english An autoreleased BezierTo object.
     * @~chinese 一个自释放的BezierTo对象。
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js: var create(var t,var table)
     * in lua: lcaol create(local t, local table)
     * @endcode
     */
    static BezierTo* create(float t, const ccBezierConfig& c);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual BezierTo* clone() const override;
    virtual BezierTo* reverse(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    BezierTo() {}
    virtual ~BezierTo() {}
    
    /** @~english
     * initializes the action with a duration and a bezier configuration
     * @~chinese 
     * 用持续时间和贝塞尔曲线配置初始化BezierTo动作。
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param c @~english Bezier config.
     * @~chinese 贝塞尔曲线配置。
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese 如果初始化成功返回true，否则返回false。
     */
    bool initWithDuration(float t, const ccBezierConfig &c);

protected:
    ccBezierConfig _toConfig;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(BezierTo);
};

/** @class ScaleTo
 @brief @~english Scales a Node object to a zoom factor by modifying it's scale attribute.
 * @~chinese ScaleTo动作通过修改scale属性让一个节点对象的缩放到特定大小。
 @warning @~english This action doesn't support "reverse".
 * @~chinese 这个动作不支持“逆转”（reverse）。
 @warning @~english The physics body contained in Node doesn't support this action.
 * @~chinese 包含的物理身体的节点不支持这一动作。
 */
class CC_DLL ScaleTo : public ActionInterval
{
public:
    /** @~english
     * Creates the action with the same scale factor for X and Y.
     * @~chinese 
     * 用持续时间和X和Y轴相同的缩放比例创建ScaleTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param s @~english Scale factor of x and y.
     * @~chinese X和Y轴的缩放比例。
     * @return @~english An autoreleased ScaleTo object.
     * @~chinese 一个自释放的ScaleTo对象。
     */
    static ScaleTo* create(float duration, float s);

    /** @~english
     * Creates the action with and X factor and a Y factor.
     * @~chinese 
     * 用持续时间和X和Y轴分别的缩放比例创建ScaleTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param sx @~english Scale factor of x.
     * @~chinese X轴缩放比例。
     * @param sy @~english Scale factor of y.
     * @~chinese Y轴的缩放比例。
     * @return @~english An autoreleased ScaleTo object.
     * @~chinese 一个自释放的ScaleTo对象。
     */
    static ScaleTo* create(float duration, float sx, float sy);

    /** @~english
     * Creates the action with X Y Z factor.
     * @~chinese 
     * 用持续时间和X，Y，Z轴分别的缩放比例创建ScaleTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param sx @~english Scale factor of x.
     * @~chinese X轴缩放比例。
     * @param sy @~english Scale factor of y.
     * @~chinese Y轴缩放比例。
     * @param sz @~english Scale factor of z.
     * @~chinese Z轴缩放比例。
     * @return @~english An autoreleased ScaleTo object.
     * @~chinese 一个自释放的ScaleTo对象。
     */
    static ScaleTo* create(float duration, float sx, float sy, float sz);

    //
    // Overrides
    //
    virtual ScaleTo* clone() const override;
    virtual ScaleTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ScaleTo() {}
    virtual ~ScaleTo() {}

    /** @~english
     * Initialize the action with the same scale factor for X and Y.
     * @~chinese 
     * 用持续时间和X和Y轴相同的缩放比例初始化ScaleTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param s @~english Scale factor of x and y.
     * @~chinese X和Y轴的缩放比例。
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese 如果初始化成功返回true，否则返回false。
     */
    bool initWithDuration(float duration, float s);
    /** @~english
     * Initialize the action with and X factor and a Y factor.
     * @~chinese 
     * 用持续时间和X和Y轴分别的缩放比例初始化ScaleTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param sx @~english Scale factor of x.
     * @~chinese X轴缩放比例。
     * @param sy @~english Scale factor of y.
     * @~chinese Y轴的缩放比例。
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese 如果初始化成功返回true，否则返回false。
     */
    bool initWithDuration(float duration, float sx, float sy);
    /** @~english
     * Initializes the action with X Y Z factor 
     * @~chinese 
     * 用持续时间和X，Y，Z轴分别的缩放比例初始化ScaleTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param sx @~english Scale factor of x.
     * @~chinese X轴缩放比例。
     * @param sy @~english Scale factor of y.
     * @~chinese Y轴缩放比例。
     * @param sz @~english Scale factor of z.
     * @~chinese Z轴缩放比例。
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese 如果初始化成功返回true，否则返回false。
     */
    bool initWithDuration(float duration, float sx, float sy, float sz);

protected:
    float _scaleX;
    float _scaleY;
    float _scaleZ;
    float _startScaleX;
    float _startScaleY;
    float _startScaleZ;
    float _endScaleX;
    float _endScaleY;
    float _endScaleZ;
    float _deltaX;
    float _deltaY;
    float _deltaZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ScaleTo);
};

/** @class ScaleBy
 * @brief @~english Scales a Node object a zoom factor by modifying it's scale attribute.
 * @~chinese ScaleTo动作通过修改scale属性让一个节点对象的缩放到特定比例，相对于当前大小。
 @warning @~english The physics body contained in Node doesn't support this action.
 * @~chinese 包含的物理身体的节点不支持这一动作。
*/
class CC_DLL ScaleBy : public ScaleTo
{
public:
    /** @~english
     * Creates the action with the same scale factor for X and Y.
     * @~chinese 
     * 用持续时间和X和Y轴相同的缩放比例创建ScaleBy动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param s @~english Scale factor of x and y.
     * @~chinese X和Y轴的缩放比例。
     * @return @~english An autoreleased ScaleBy object.
     * @~chinese 一个自释放的ScaleBy对象。
     */
    static ScaleBy* create(float duration, float s);

    /** @~english
     * Creates the action with and X factor and a Y factor.
     * @~chinese 
     * 用持续时间和X和Y轴分别的缩放比例创建ScaleBy动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param sx @~english Scale factor of x.
     * @~chinese X轴缩放比例。
     * @param sy @~english Scale factor of y.
     * @~chinese Y轴的缩放比例。
     * @return @~english An autoreleased ScaleBy object.
     * @~chinese 一个自释放的ScaleBy对象。
     */
    static ScaleBy* create(float duration, float sx, float sy);

    /** @~english
     * Creates the action with X Y Z factor.
     * @~chinese 
     * 用持续时间和X，Y，Z轴分别的缩放比例创建ScaleBy动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param sx @~english Scale factor of x.
     * @~chinese X轴缩放比例。
     * @param sy @~english Scale factor of y.
     * @~chinese Y轴缩放比例。
     * @param sz @~english Scale factor of z.
     * @~chinese Z轴缩放比例。
     * @return @~english An autoreleased ScaleBy object.
     * @~chinese 一个自释放的ScaleBy对象。
     */
    static ScaleBy* create(float duration, float sx, float sy, float sz);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual ScaleBy* clone() const override;
    virtual ScaleBy* reverse(void) const override;

CC_CONSTRUCTOR_ACCESS:
    ScaleBy() {}
    virtual ~ScaleBy() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ScaleBy);
};

/** @class Blink
 * @brief @~english Blinks a Node object by modifying it's visible attribute.
 * @~chinese Blink可以通过修改节点的visible属性让节点对象有不断闪现的效果。
*/
class CC_DLL Blink : public ActionInterval
{
public:
    /** @~english
     * Creates the action with duration and number of blinks.
     * @~chinese 
     * 用持续时间和闪现次数创建Blink动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param blinks @~english Blink times.
     * @~chinese 闪现次数。
     * @return @~english An autoreleased Blink object.
     * @~chinese 一个自释放的Blink动作。
     */
    static Blink* create(float duration, int blinks);

    //
    // Overrides
    //
    virtual Blink* clone() const override;
    virtual Blink* reverse() const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop() override;
    
CC_CONSTRUCTOR_ACCESS:
    Blink() {}
    virtual ~Blink() {}

    /** @~english
     * initializes the action with duration and number of blinks.
     * @~chinese 
     * 用持续时间和闪现次数初始化Blink动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param blinks @~english Blink times.
     * @~chinese 闪现次数。
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese 如果初始化成功返回true，否则返回false。
     */
    bool initWithDuration(float duration, int blinks);
    
protected:
    int _times;
    bool _originalState;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Blink);
};


/** @class FadeTo
 * @brief @~english Fades an object that implements the RGBAProtocol protocol. It modifies the opacity from the current value to a custom one.
 * @~chinese FadeTo（渐变）可以将一个实现了RGBAProtocol协议的对象从当前透明度渐变到指定透明度。
 @warning @~english This action doesn't support "reverse"
 * @~chinese 这个动作不支持“逆转”（reverse）
 */
class CC_DLL FadeTo : public ActionInterval
{
public:
    /** @~english
     * Creates an action with duration and opacity.
     * @~chinese 
     * 使用持续时间和目标透明度创建FadeTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param opacity @~english A certain opacity, the range is from 0 to 255.
     * @~chinese 目标透明度，范围从0到255。
     * @return @~english An autoreleased FadeTo object.
     * @~chinese 一个自释放的FadeTo对象。
     */
    static FadeTo* create(float duration, GLubyte opacity);

    //
    // Overrides
    //
    virtual FadeTo* clone() const override;
    virtual FadeTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    FadeTo() {}
    virtual ~FadeTo() {}

    /** @~english
     * initializes the action with duration and opacity 
     * @~chinese 
     * 使用持续时间和目标透明度初始化FadeTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param opacity @~english A certain opacity, the range is from 0 to 255.
     * @~chinese 目标透明度，范围从0到255。
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese 如果初始化成功返回true，否则返回false。
     */
    bool initWithDuration(float duration, GLubyte opacity);

protected:
    GLubyte _toOpacity;
    GLubyte _fromOpacity;
    friend class FadeOut;
    friend class FadeIn;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeTo);
};

/** @class FadeIn
 * @brief @~english Fades In an object that implements the RGBAProtocol protocol. It modifies the opacity from 0 to 255.
 The "reverse" of this action is FadeOut
 * @~chinese FadeIn（淡入）动作可以让一个实现RGBAProtocol协议的对象淡入，它使节点的当前透明度渐变到255。
 * 这一动作的“反向”是FadeOut（淡出）动作
 */
class CC_DLL FadeIn : public FadeTo
{
public:
    /** @~english
     * Creates the action with duration.
     * @~chinese 
     * 用持续时间创建FadeIn动作。
     * @param d @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @return @~english An autoreleased FadeIn object.
     * @~chinese 一个自释放FadeIn对象。
     */
    static FadeIn* create(float d);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeIn* clone() const override;
    virtual FadeTo* reverse(void) const override;

    /**
     * @~english Set the reverse action.
     * @~chinese 设置逆转动作。
     * @param ac @~english The reverse action @~chinese 逆转动作
     * @js NA
     */
    void setReverseAction(FadeTo* ac);

CC_CONSTRUCTOR_ACCESS:
    FadeIn():_reverseAction(nullptr) {}
    virtual ~FadeIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeIn);
    FadeTo* _reverseAction;
};

/** @class FadeOut
 * @brief @~english Fades Out an object that implements the RGBAProtocol protocol. It modifies the opacity from 255 to 0.
 The "reverse" of this action is FadeIn
 * @~chinese FadeOut（淡出）动作可以让一个实现RGBAProtocol协议的对象淡出，它使节点的当前透明度渐变到0。
 * 这一动作的“反向”是FadeIn（淡入）动作
*/
class CC_DLL FadeOut : public FadeTo
{
public:
    /** @~english
     * Creates the action with duration.
     * @~chinese 
     * 用持续时间创建FadeOut动作。
     * @param d @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @return @~english An autoreleased FadeOut object.
     * @~chinese 一个自释放FadeOut对象。
     */
    static FadeOut* create(float d);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeOut* clone() const  override;
    virtual FadeTo* reverse(void) const override;

    /**
     * @~english Set the reverse action.
     * @~chinese 设置逆转动作。
     * @param ac @~english The reverse action @~chinese 逆转动作
     * @js NA
     */
    void setReverseAction(FadeTo* ac);

CC_CONSTRUCTOR_ACCESS:
    FadeOut():_reverseAction(nullptr) {}
    virtual ~FadeOut() {}
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOut);
    FadeTo* _reverseAction;
};

/** @class TintTo
 * @brief @~english Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 * @~chinese TintTo动作可以让一个实现NodeRGB协议的对象变色到特定颜色。
 @warning @~english This action doesn't support "reverse"
 * @~chinese 这个动作不支持“逆转”（reverse）
 @since v0.7.2
*/
class CC_DLL TintTo : public ActionInterval
{
public:
    /** @~english
     * Creates an action with duration and color.
     * @~chinese 
     * 用持续时间和目标颜色创建TintTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param red @~english Red Color, from 0 to 255.
     * @~chinese 颜色的红色通道值，从0到255。
     * @param green @~english Green Color, from 0 to 255.
     * @~chinese 颜色的绿色通道值，从0到255。
     * @param blue @~english Blue Color, from 0 to 255.
     * @~chinese 颜色的蓝色通道值，从0到255。
     * @return @~english An autoreleased TintTo object.
     * @~chinese 一个自释放的TintTo对象。
     */
    static TintTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue);
    /**@~english
     * Creates an action with duration and color.
     * @~chinese 
     * 用持续时间和目标颜色创建TintTo动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param color @~english It's a Color3B type color.
     * @~chinese 一个Color3B类型颜色。
     * @return @~english An autoreleased TintTo object.
     * @~chinese 一个自释放的TintTo对象。
     */
    static TintTo* create(float duration, const Color3B& color);

    //
    // Overrides
    //
    virtual TintTo* clone() const override;
    virtual TintTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TintTo() {}
    virtual ~TintTo() {}

    bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue);

protected:
    Color3B _to;
    Color3B _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TintTo);
};

/** @class TintBy
 @brief @~english Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 * @~chinese TintBy动作可以让一个实现NodeRGB协议的对象按一定差值改变其颜色。
 @since v0.7.2
 */
class CC_DLL TintBy : public ActionInterval
{
public:
    /** @~english
     * Creates an action with duration and color.
     * @~chinese 
     * 用持续时间和目标颜色创建TintBy动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param deltaRed @~english Delta red color.
     * @~chinese 颜色差值的红色通道值，从0到255。
     * @param deltaGreen @~english Delta green color.
     * @~chinese 颜色差值的绿色通道值，从0到255。
     * @param deltaBlue @~english Delta blue color.
     * @~chinese 颜色差值的蓝色通道值，从0到255。
     * @return @~english An autoreleased TintBy object.
     * @~chinese 一个自释放的TintBy对象。
     */
    static TintBy* create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

    //
    // Overrides
    //
    virtual TintBy* clone() const override;
    virtual TintBy* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TintBy() {}
    virtual ~TintBy() {}

    bool initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

protected:
    GLshort _deltaR;
    GLshort _deltaG;
    GLshort _deltaB;

    GLshort _fromR;
    GLshort _fromG;
    GLshort _fromB;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TintBy);
};

/** @class DelayTime
 * @brief @~english Delays the action a certain amount of seconds.
 * @~chinese DelayTime是延迟动作，可以让Sequence中的动作执行延迟一段时间。
*/
class CC_DLL DelayTime : public ActionInterval
{
public:
    /** @~english
     * Creates the action with delayed duration.
     * @~chinese 
     * 用延迟时间创建DelayTime动作。
     * @param d @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @return @~english An autoreleased DelayTime object.
     * @~chinese 一个自释放的DelayTime对象。
     */
    static DelayTime* create(float d);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual DelayTime* reverse() const override;
    virtual DelayTime* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    DelayTime() {}
    virtual ~DelayTime() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(DelayTime);
};

/** @class ReverseTime
 * @brief @~english Executes an action in reverse order, from time=duration to time=0
 
 * @~chinese ReverseTime动作会用逆转的时间轴执行一个目标动作，逆转后的时间轴从time=duration到time=0
 * 
 @warning @~english Use this action carefully. This action is not
 sequenceable. Use it as the default "reversed" method
 of your own actions, but using it outside the "reversed"
 scope is not recommended.
 * @~chinese 要小心使用这个操作。这种动作不可以被包含在Sequence动作中。
 * 可以把它作为默认的“逆转”的方法，但在“逆转”范围外使用是不推荐的。
 */
class CC_DLL ReverseTime : public ActionInterval
{
public:
    /** @~english Creates the action with the inner action.
     *
     * @~chinese 使用内部动作创建ReverseTime动作。
     * 
     * @param action @~english a certain action.
     * @~chinese 内部动作。
     * @return @~english An autoreleased ReverseTime object.
     * @~chinese 一个自释放的ReverseTime对象。
     */
    static ReverseTime* create(FiniteTimeAction *action);

    //
    // Overrides
    //
    virtual ReverseTime* reverse() const override;
    virtual ReverseTime* clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ReverseTime();
    virtual ~ReverseTime(void);

    bool initWithAction(FiniteTimeAction *action);

protected:
    FiniteTimeAction *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ReverseTime);
};

class Texture2D;
/** @class Animate
 * @brief @~english Animates a sprite given the Animation.
 * @~chinese Animate动作可以使用Animation（动画）对象播放一个精灵动画。
 */
class CC_DLL Animate : public ActionInterval
{
public:
    /** @~english Creates the action with an Animation and will restore the original frame when the animation is over.
     *
     * @~chinese 使用Animation（动画）对象创建一个Animate对象，目标精灵的初始帧将在动画结束后被恢复。
     * 
     * @param animation @~english A certain animation.
     * @~chinese Animation（动画）对象。
     * @return @~english An autoreleased Animate object.
     * @~chinese 一个自释放Animate对象。
     */
    static Animate* create(Animation *animation);

    /** @~english Sets the Animation object to be animated 
     * 
     * @~chinese 设置动画对象
     * 
     * @param animation @~english certain animation.
     * @~chinese Animation（动画）对象。
     */
    void setAnimation( Animation* animation );
    /** @~english returns the Animation object that is being animated 
     *
     * @~chinese 获取动画对象
     * 
     * @return @~english Gets the animation object that is being animated.
     * @~chinese 动画对象
     */
    Animation* getAnimation() { return _animation; }
    const Animation* getAnimation() const { return _animation; }

    //
    // Overrides
    //
    virtual Animate* clone() const override;
    virtual Animate* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float t) override;
    
CC_CONSTRUCTOR_ACCESS:
    Animate();
    virtual ~Animate();

    bool initWithAnimation(Animation *animation);

protected:
    std::vector<float>* _splitTimes;
    int             _nextFrame;
    SpriteFrame*    _origFrame;
    unsigned int    _executedLoops;
    Animation*      _animation;

    EventCustom*    _frameDisplayedEvent;
    AnimationFrame::DisplayedEventInfo _frameDisplayedEventInfo;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Animate);
};

/** @class TargetedAction
 * @brief @~english Overrides the target of an action so that it always runs on the target
 * specified at action creation rather than the one specified by runAction.
 * @~chinese TargetedAction可以让内部动作强制在目标节点上执行，而不是调用`runAction`函数时指定的节点。
 */
class CC_DLL TargetedAction : public ActionInterval
{
public:
    /** @~english Create an action with the specified action and forced target.
     * 
     * @~chinese 使用固定目标和内部动作创建TargetedAction动作。
     * 
     * @param target @~english The target.
     * @~chinese 该动作的固定目标节点.
     * @param action @~english The action.
     * @~chinese 内部动作。
     * @return @~english An autoreleased TargetedAction object.
     * @~chinese 一个自释放的TargetedAction对象。
     */
    static TargetedAction* create(Node* target, FiniteTimeAction* action);

    /** @~english Sets the target that the action will be forced to run with.
     *
     * @~chinese 设置固定目标节点，内部动作将强制在这个目标节点上执行。
     * 
     * @param forcedTarget @~english The target that the action will be forced to run with.
     * @~chinese 固定目标节点。
     */
    void setForcedTarget(Node* forcedTarget);
    /** @~english returns the target that the action is forced to run with. 
     *
     * @~chinese 获取固定目标节点，内部动作将强制在这个目标节点上执行。
     * 
     * @return @~english The target that the action is forced to run with.
     * @~chinese 固定目标节点。
     */
    Node* getForcedTarget() { return _forcedTarget; }
    const Node* getForcedTarget() const { return _forcedTarget; }

    //
    // Overrides
    //
    virtual TargetedAction* clone() const override;
    virtual TargetedAction* reverse() const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TargetedAction();
    virtual ~TargetedAction();

    bool initWithTarget(Node* target, FiniteTimeAction* action);

protected:
    FiniteTimeAction* _action;
    Node* _forcedTarget;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TargetedAction);
};

/**
 * @class ActionFloat
 * @brief @~english Action used to animate any value in range [from,to] over specified time interval
 * @~chinese ActionFloat可以将任何值在一定时间间隔内从指定的起始值改变为指定的最终值
 */
class CC_DLL ActionFloat : public ActionInterval
{
public:
    /**@~english
     *  Callback function used to report back result
     * @~chinese 
     * 用于报告结果的回调函数
     */
    typedef std::function<void(float value)> ActionFloatCallback;

    /**@~english
     * Creates FloatAction with specified duration, from value, to value and callback to report back results
     * @~chinese 
     * 用持续时间、起始值、最终值和回调函数来创建ActionFloat动作
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间，以秒为单位。
     * @param from @~english value to start from
     * @~chinese 起始值
     * @param to @~english value to be at the end of the action
     * @~chinese 最终值
     * @param callback @~english Callback to report back result
     * @~chinese 报告结果的回调函数
     * @return @~english An autoreleased ActionFloat object
     * @~chinese 一个自释放的ActionFloat对象
     */
    static ActionFloat* create(float duration, float from, float to, ActionFloatCallback callback);

    void startWithTarget(Node* target) override;
    void update(float delta) override;
    ActionFloat* reverse() const override;
    ActionFloat* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    ActionFloat() {};
    virtual ~ActionFloat() {};

    bool initWithDuration(float duration, float from, float to, ActionFloatCallback callback);

protected:
    float _from;
    float _to;
    float _delta;

    ActionFloatCallback _callback;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ActionFloat);
};

// end of actions group
/// @}

NS_CC_END

#endif //__ACTION_CCINTERVAL_ACTION_H__

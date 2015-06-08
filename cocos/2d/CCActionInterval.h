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
     * @~chinese 用于创建一个可以按序列执行动作的Sequence动作对象的辅助构造函数系列
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
 * @~chinese 永远得重复一个动作。
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
 * @~chinese 倾斜一个节点对象给定角度通过修改skewX和skewY属性
@since v1.0
*/
class CC_DLL SkewTo : public ActionInterval
{
public:
    /** @~english
     * Creates the action.
     * @~chinese 
     * 创建动作。
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param sx @~english Skew x angle.
     * @~chinese x倾斜角度。
     * @param sy @~english Skew y angle.
     * @~chinese 倾斜角度。
     * @return @~english An autoreleased SkewTo object.
     * @~chinese 一个自释放 SkewTo对象。
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
    /**
     * @param t @~english In seconds.
     * @~chinese 在几秒钟内。
     */
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
 * @~chinese 倾斜一个节点对象skewX和skewY度。
@since v1.0
*/
class CC_DLL SkewBy : public SkewTo
{
public:
    /** @~english
     * Creates the action.
     * @~chinese 
     * 创建动作。
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param deltaSkewX @~english Skew x delta angle.
     * @~chinese 斜x三角洲角度。
     * @param deltaSkewY @~english Skew y delta angle.
     * @~chinese 斜y三角洲角度。
     * @return @~english An autoreleased SkewBy object.
     * @~chinese 一个自释放 SkewBy对象。
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
    /**
     * @param t @~english In seconds.
     * @~chinese 在几秒钟内。
     */
    bool initWithDuration(float t, float sx, float sy);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SkewBy);
};

/** @class JumpBy
 * @brief @~english Moves a Node object simulating a parabolic jump movement by modifying it's position attribute.
 * @~chinese 移动一个节点对象模拟抛物线跳运动通过修改它的位置属性。
*/
class CC_DLL JumpBy : public ActionInterval
{
public:
    /** @~english
     * Creates the action.
     * @~chinese 
     * 创建动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param position @~english The jumping distance.
     * @~chinese 跳跃的距离。
     * @param height @~english The jumping height.
     * @~chinese 跳的高度。
     * @param jumps @~english The jumping times.
     * @~chinese 跳跃。
     * @return @~english An autoreleased JumpBy object.
     * @~chinese 一个自释放 JumpBy对象。
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

    /** @~english
     * initializes the action
     * @~chinese 
     * 初始化动作
     * @param duration @~english in seconds
     * @~chinese 以秒为单位
     */
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
 * @~chinese 移动节点对象到一个抛物线位置模拟跳运动通过修改它的位置属性。
*/ 
class CC_DLL JumpTo : public JumpBy
{
public:
    /** @~english
     * Creates the action.
     * @~chinese 
     * 创建动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param position @~english The jumping destination position.
     * @~chinese 跳的目的地的位置。
     * @param height @~english The jumping height.
     * @~chinese 跳的高度。
     * @param jumps @~english The jumping times.
     * @~chinese 跳跃。
     * @return @~english An autoreleased JumpTo object.
     * @~chinese 一个自释放 JumpTo对象。
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

    /** @~english
     * initializes the action
     * @~chinese 
     * 初始化动作
     * @param duration @~english In seconds.
     * @~chinese 在几秒钟内。
     */
    bool initWithDuration(float duration, const Vec2& position, float height, int jumps);

protected:
    Vec2 _endPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpTo);
};

/** @struct @~english Bezier configuration structure
 * @~chinese Bezier配置结构
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
 * @~chinese 动作,动作目标一定距离的立方曲线。
 */
class CC_DLL BezierBy : public ActionInterval
{
public:
    /** @~english Creates the action with a duration and a bezier configuration.
     * @~chinese 创建动作持续时间和贝塞尔曲线配置。
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param c @~english Bezier config.
     * @~chinese config Bezier。
     * @return @~english An autoreleased BezierBy object.
     * @~chinese 一个自释放 BezierBy对象。
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
     * 初始化动作持续时间和贝塞尔曲线配置
     * @param t @~english in seconds
     * @~chinese 以秒为单位
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
 * @~chinese 动作,动作目标立方曲线到目的地。
 @since v0.8.2
 */
class CC_DLL BezierTo : public BezierBy
{
public:
    /** @~english Creates the action with a duration and a bezier configuration.
     * @~chinese 创建动作持续时间和贝塞尔曲线配置。
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param c @~english Bezier config.
     * @~chinese config Bezier。
     * @return @~english An autoreleased BezierTo object.
     * @~chinese 一个自释放 BezierTo对象。
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
    /**
     * @param t @~english In seconds.
     * @~chinese 在几秒钟内。
     */
    bool initWithDuration(float t, const ccBezierConfig &c);

protected:
    ccBezierConfig _toConfig;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(BezierTo);
};

/** @class ScaleTo
 @brief @~english Scales a Node object to a zoom factor by modifying it's scale attribute.
 * @~chinese 天平一个节点对象的缩放因子修改它的规模属性。
 @warning @~english This action doesn't support "reverse".
 * @~chinese 这个动作不支持“逆转”。
 @warning @~english The physics body contained in Node doesn't support this action.
 * @~chinese 中包含的物理身体节点不支持这一动作。
 */
class CC_DLL ScaleTo : public ActionInterval
{
public:
    /** @~english
     * Creates the action with the same scale factor for X and Y.
     * @~chinese 
     * 创建动作具有相同比例因子X和Y。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english Scale factor of x and y.
     * @~chinese x和y的比例因子。
     * @return @~english An autoreleased ScaleTo object.
     * @~chinese 一个自释放 ScaleTo对象。
     */
    static ScaleTo* create(float duration, float s);

    /** @~english
     * Creates the action with and X factor and a Y factor.
     * @~chinese 
     * 创建动作和X因素和因素。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param sx @~english Scale factor of x.
     * @~chinese 比例因子的x。
     * @param sy @~english Scale factor of y.
     * @~chinese y的比例因子。
     * @return @~english An autoreleased ScaleTo object.
     * @~chinese 一个自释放 ScaleTo对象。
     */
    static ScaleTo* create(float duration, float sx, float sy);

    /** @~english
     * Creates the action with X Y Z factor.
     * @~chinese 
     * 创建动作与X Y Z因子。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param sx @~english Scale factor of x.
     * @~chinese 比例因子的x。
     * @param sy @~english Scale factor of y.
     * @~chinese y的比例因子。
     * @param sz @~english Scale factor of z.
     * @~chinese 比例因子z。
     * @return @~english An autoreleased ScaleTo object.
     * @~chinese 一个自释放 ScaleTo对象。
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
     * initializes the action with the same scale factor for X and Y
     * @~chinese 
     * Initializes the action with the same scale factor for X and Y
     * @param duration @~english in seconds
     * @~chinese 以秒为单位
     */
    bool initWithDuration(float duration, float s);
    /** @~english
     * initializes the action with and X factor and a Y factor 
     * @~chinese 
     * 初始化动作和X因素和因素
     * @param duration @~english in seconds
     * @~chinese 以秒为单位
     */
    bool initWithDuration(float duration, float sx, float sy);
    /** @~english
     * initializes the action with X Y Z factor 
     * @~chinese 
     * 初始化动作与X Y Z因子
     * @param duration @~english in seconds
     * @~chinese 以秒为单位
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
 * @~chinese Scales, a Node object a zoom factor by modifying it 's scale attribute.
 @warning @~english The physics body contained in Node doesn't support this action.
 * @~chinese 中包含的物理身体节点不支持这一动作。
*/
class CC_DLL ScaleBy : public ScaleTo
{
public:
    /** @~english
     * Creates the action with the same scale factor for X and Y.
     * @~chinese 
     * 创建动作具有相同比例因子X和Y。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param s @~english Scale factor of x and y.
     * @~chinese x和y的比例因子。
     * @return @~english An autoreleased ScaleBy object.
     * @~chinese 一个自释放 ScaleBy对象。
     */
    static ScaleBy* create(float duration, float s);

    /** @~english
     * Creates the action with and X factor and a Y factor.
     * @~chinese 
     * 创建动作和X因素和因素。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param sx @~english Scale factor of x.
     * @~chinese 比例因子的x。
     * @param sy @~english Scale factor of y.
     * @~chinese y的比例因子。
     * @return @~english An autoreleased ScaleBy object.
     * @~chinese 一个自释放 ScaleBy对象。
     */
    static ScaleBy* create(float duration, float sx, float sy);

    /** @~english
     * Creates the action with X Y Z factor.
     * @~chinese 
     * 创建动作与X Y Z因子。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param sx @~english Scale factor of x.
     * @~chinese 比例因子的x。
     * @param sy @~english Scale factor of y.
     * @~chinese y的比例因子。
     * @param sz @~english Scale factor of z.
     * @~chinese 比例因子z。
     * @return @~english An autoreleased ScaleBy object.
     * @~chinese 一个自释放 ScaleBy对象。
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
 * @~chinese 眨眼一个节点对象通过修改它的可见属性。
*/
class CC_DLL Blink : public ActionInterval
{
public:
    /** @~english
     * Creates the action.
     * @~chinese 
     * 创建动作。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 在全国,后者。
     * @param blinks @~english Blink times.
     * @~chinese 眨眼时间。
     * @return @~english An autoreleased Blink object.
     * @~chinese 一个自释放眨眼对象。
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
     * initializes the action 
     * @~chinese 
     * 初始化动作
     * @param duration @~english in seconds
     * @~chinese 以秒为单位
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
 * @~chinese 褪色的对象实现了RGBAProtocol协议。从当前值修改透明度自定义。
 @warning @~english This action doesn't support "reverse"
 * @~chinese 这个动作不支持“反向”
 */
class CC_DLL FadeTo : public ActionInterval
{
public:
    /** @~english
     * Creates an action with duration and opacity.
     * @~chinese 
     * 创建一个动作持续时间和不透明度。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param opacity @~english A certain opacity, the range is from 0 to 255.
     * @~chinese 一定的透明度,范围从0到255。
     * @return @~english An autoreleased FadeTo object.
     * @~chinese 一个自释放 FadeTo对象。
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
     * 初始化动作持续时间和不透明度
     * @param duration @~english in seconds
     * @~chinese 以秒为单位
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
 * @~chinese 消失在一个对象实现RGBAProtocol协议。它修改透明度从0到255。
 * 这一动作的“反向”渐隐
 */
class CC_DLL FadeIn : public FadeTo
{
public:
    /** @~english
     * Creates the action.
     * @~chinese 
     * 创建动作。
     * @param d @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @return @~english An autoreleased FadeIn object.
     * @~chinese 一个自释放渐显对象。
     */
    static FadeIn* create(float d);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeIn* clone() const override;
    virtual FadeTo* reverse(void) const override;

    /**
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
 * @~chinese 逐渐消失的对象实现了RGBAProtocol协议。从255年修改透明度为0。
 * 这一动作的“反向”渐显
*/
class CC_DLL FadeOut : public FadeTo
{
public:
    /** @~english
     * Creates the action.
     * @~chinese 
     * 创建动作。
     * @param d @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     */
    static FadeOut* create(float d);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeOut* clone() const  override;
    virtual FadeTo* reverse(void) const override;

    /**
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
 * @~chinese 颜色一个节点实现NodeRGB从当前颜色自定义一个协议。
 @warning @~english This action doesn't support "reverse"
 * @~chinese This action doesn 't support "reverse"
 @since v0.7.2
*/
class CC_DLL TintTo : public ActionInterval
{
public:
    /** @~english
     * Creates an action with duration and color.
     * @~chinese 
     * 创建一个动作持续时间和颜色。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param red @~english Red Color, from 0 to 255.
     * @~chinese 红颜色,从0到255。
     * @param green @~english Green Color, from 0 to 255.
     * @~chinese 绿色的颜色,从0到255。
     * @param blue @~english Blue Color, from 0 to 255.
     * @~chinese 蓝色的颜色,从0到255。
     * @return @~english An autoreleased TintTo object.
     * @~chinese 一个自释放 TintTo对象。
     */
    static TintTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue);
    /**@~english
     * Creates an action with duration and color.
     * @~chinese 
     * 创建一个动作持续时间和颜色。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param color @~english It's a Color3B type.
     * @~chinese 这是一个Color3B类型。
     * @return @~english An autoreleased TintTo object.
     * @~chinese 一个自释放 TintTo对象。
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

    /** @~english initializes the action with duration and color  @~chinese 初始化动作与时间和颜色*/
    bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue);

protected:
    Color3B _to;
    Color3B _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TintTo);
};

/** @class TintBy
 @brief @~english Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 * @~chinese 颜色一个节点实现NodeRGB从当前颜色自定义一个协议。
 @since v0.7.2
 */
class CC_DLL TintBy : public ActionInterval
{
public:
    /** @~english
     * Creates an action with duration and color.
     * @~chinese 
     * 创建一个动作持续时间和颜色。
     * @param duration @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param deltaRed @~english Delta red color.
     * @~chinese 三角洲红色。
     * @param deltaGreen @~english Delta green color.
     * @~chinese 三角洲绿色。
     * @param deltaBlue @~english Delta blue color.
     * @~chinese 三角洲蓝色。
     * @return @~english An autoreleased TintBy object.
     * @~chinese 一个自释放 TintBy对象。
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

    /** @~english initializes the action with duration and color  @~chinese 初始化动作与时间和颜色*/
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
 * @~chinese 延迟动作一定数量的秒。
*/
class CC_DLL DelayTime : public ActionInterval
{
public:
    /** @~english
     * Creates the action.
     * @~chinese 
     * 创建动作。
     * @param d @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @return @~english An autoreleased DelayTime object.
     * @~chinese 一个自释放时延对象。
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
 
 * @~chinese 在相反的顺序执行一个动作,从时间=时间= 0
 * 
 @warning @~english Use this action carefully. This action is not
 sequenceable. Use it as the default "reversed" method
 of your own actions, but using it outside the "reversed"
 scope is not recommended.
 * @~chinese 使用这个操作要小心。这种做法不
 * sequenceable。把它作为默认的“逆转”的方法
 * 你自己的行为,但使用它在“逆转”
 * 不推荐范围。
*/
class CC_DLL ReverseTime : public ActionInterval
{
public:
    /** @~english Creates the action.
     *
     * @~chinese 创建动作。
     * 
     * @param action @~english a certain action.
     * @~chinese 某种动作。
     * @return @~english An autoreleased ReverseTime object.
     * @~chinese 一个自释放 ReverseTime对象。
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

    /** @~english initializes the action  @~chinese 初始化动作*/
    bool initWithAction(FiniteTimeAction *action);

protected:
    FiniteTimeAction *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ReverseTime);
};

class Texture2D;
/** @class Animate
 * @brief @~english Animates a sprite given the name of an Animation.
 * @~chinese 一个雪碧给动画的名字。
 */
class CC_DLL Animate : public ActionInterval
{
public:
    /** @~english Creates the action with an Animation and will restore the original frame when the animation is over.
     *
     * @~chinese Creates the action with an Animation and will restore the original frame when the animation is over.
     * 
     * @param animation @~english A certain animation.
     * @~chinese 在一些热闹。
     * @return @~english An autoreleased Animate object.
     * @~chinese 一个自释放激活对象。
     */
    static Animate* create(Animation *animation);

    /** @~english Sets the Animation object to be animated 
     * 
     * @~chinese 设置动画对象的动画
     * 
     * @param animation @~english certain animation.
     * @~chinese 一些热闹。
     */
    void setAnimation( Animation* animation );
    /** @~english returns the Animation object that is being animated 
     *
     * @~chinese 返回被动画的动画对象
     * 
     * @return @~english Gets the animation object that is being animated.
     * @~chinese Gets the animation object that is being animated.
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
    /**
     * @param t @~english In seconds.
     * @~chinese 在几秒钟内。
     */
    virtual void update(float t) override;
    
CC_CONSTRUCTOR_ACCESS:
    Animate();
    virtual ~Animate();

    /** @~english initializes the action with an Animation and will restore the original frame when the animation is over  @~chinese 初始化动作与一个动画和动画结束时恢复原来的框架*/
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
 * @~chinese 覆盖一个动作的目标,它总是在目标系统上运行
 * 指定在创建动作而不是runAction所指定的一个。
 */
class CC_DLL TargetedAction : public ActionInterval
{
public:
    /** @~english Create an action with the specified action and forced target.
     * 
     * @~chinese 创建一个动作与指定的动作,迫使目标。
     * 
     * @param target @~english The target needs to override.
     * @~chinese The target needs to override.
     * @param action @~english The action needs to override.
     * @~chinese 动作需要覆盖。
     * @return @~english An autoreleased TargetedAction object.
     * @~chinese 一个自释放 TargetedAction对象。
     */
    static TargetedAction* create(Node* target, FiniteTimeAction* action);

    /** @~english Sets the target that the action will be forced to run with.
     *
     * @~chinese 通过提供目标,动作范围将强迫赛跑。
     * 
     * @param forcedTarget @~english The target that the action will be forced to run with.
     * @~chinese 目标,动作将被迫与运行。
     */
    void setForcedTarget(Node* forcedTarget);
    /** @~english returns the target that the action is forced to run with. 
     *
     * @~chinese 英国the目标,动作强迫赛跑。
     * 
     * @return @~english The target that the action is forced to run with.
     * @~chinese 动作的目标是被迫与运行。
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

    /** @~english Init an action with the specified action and forced target  @~chinese 初始化操作指定的动作,迫使目标*/
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
 * @~chinese 动作用于激活任何值范围(,)在指定的时间间隔
 */
class CC_DLL ActionFloat : public ActionInterval
{
public:
    /**@~english
     *  Callback function used to report back result
     * @~chinese 
     * 回调函数用于报告结果
     */
    typedef std::function<void(float value)> ActionFloatCallback;

    /**@~english
     * Creates FloatAction with specified duration, from value, to value and callback to report back
     * results
     * @~chinese 
     * 创建FloatAction指定持续时间、价值、价值和回调报告回来
     * 结果
     * @param duration @~english of the action
     * @~chinese 的动作
     * @param from @~english value to start from
     * @~chinese 价值从
     * @param to @~english value to be at the end of the action
     * @~chinese 价值的动作
     * @param callback @~english to report back result
     *
     * @~chinese 报告结果
     * 
     * @return @~english An autoreleased ActionFloat object
     * @~chinese 一个自释放 ActionFloat对象
     */
    static ActionFloat* create(float duration, float from, float to, ActionFloatCallback callback);

    /**@~english
     * Overrided ActionInterval methods
     * @~chinese 
     * 覆盖ActionInterval方法
     */
    void startWithTarget(Node* target) override;
    void update(float delta) override;
    ActionFloat* reverse() const override;
    ActionFloat* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    ActionFloat() {};
    virtual ~ActionFloat() {};

    bool initWithDuration(float duration, float from, float to, ActionFloatCallback callback);

protected:
    /* @~english From value  @~chinese 从价值*/
    float _from;
    /* @~english To value  @~chinese 价值*/
    float _to;
    /* @~english delta time  @~chinese 三角洲的时间*/
    float _delta;

    /* @~english Callback to report back results  @~chinese The Callback to report back the results*/
    ActionFloatCallback _callback;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ActionFloat);
};

// end of actions group
/// @}

NS_CC_END

#endif //__ACTION_CCINTERVAL_ACTION_H__

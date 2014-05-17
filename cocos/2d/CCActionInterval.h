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

#include "2d/CCNode.h"
#include "2d/CCAction.h"
#include "2d/CCProtocols.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCAnimation.h"
#include "base/CCVector.h"
#include <vector>

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** 
@brief An interval action is an action that takes place within a certain period of time.
It has an start time, and a finish time. The finish time is the parameter
duration plus the start time.

These ActionInterval actions have some interesting properties, like:
- They can run normally (default)
- They can run reversed with the reverse method
- They can run with the time altered with the Accelerate, AccelDeccel and Speed actions.

For example, you can simulate a Ping Pong effect running the action normally and
then running it again in Reverse mode.

Example:

Action *pingPongAction = Sequence::actions(action, action->reverse(), nullptr);
*/
class CC_DLL ActionInterval : public FiniteTimeAction
{
public:
    /** 从动作开始执行过去了多少秒 。*/
    inline float getElapsed(void) { return _elapsed; }

    //网格动作上的延伸
    void setAmplitudeRate(float amp);
    float getAmplitudeRate(void);

    //
    // 重载
    //
    virtual bool isDone(void) const override;
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    virtual ActionInterval* reverse() const override = 0;
	virtual ActionInterval *clone() const override = 0;

protected:
    /**初始化动作 */
    bool initWithDuration(float d);

    float _elapsed;
    bool   _firstTick;
};

/** @brief Runs actions sequentially, one after another
 */
class CC_DLL Sequence : public ActionInterval
{
public:
    /** 创建一组顺序性动作的协助构造函数*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
   
    /*WP8在VS2012中，不支持在变量参数列表中使用nullptr，也不支持可变参数模板*/
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

    //在WP8平台上，对于变量参数列表多余10项的情况，使用其他的创建函数或者是使用以NULL作为最后一个参数的可变参数的创建函数
    static Sequence* variadicCreate(FiniteTimeAction* item, ...);
#else
    static Sequence* create(FiniteTimeAction *action1, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

    /**用一组给定的动作创建一组顺序性动作的协助构造函数
     * @code
     * When this funtion bound to the js or lua,the input params changed
     * in js  :var   create(var   object1,var   object2, ...)
     * in lua :local create(local object1,local object2, ...)
     * @endcode
     */
    static Sequence* create(const Vector<FiniteTimeAction*>& arrayOfActions);
    /** 创建一组顺序性动作的协助构造函数 */
    static Sequence* createWithVariableList(FiniteTimeAction *action1, va_list args);
    /** 创建动作 */
    static Sequence* createWithTwoActions(FiniteTimeAction *actionOne, FiniteTimeAction *actionTwo);

    //
    // 重载
    //
    virtual Sequence* clone() const override;
	virtual Sequence* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float t) override;
    
CC_CONSTRUCTOR_ACCESS:
    Sequence() {}
    virtual ~Sequence(void);

    /** 初始化动作 */
    bool initWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo);

protected:
    FiniteTimeAction *_actions[2];
    float _split;
    int _last;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Sequence);
};

/** @brief Repeats an action a number of times.
 * To repeat an action forever use the RepeatForever action.
 */
class CC_DLL Repeat : public ActionInterval
{
public:
    /** 创建一个重复性动作。第二个参数表示次数，是一个取值在1到2的30次方之间的无符号整数 */
    static Repeat* create(FiniteTimeAction *action, unsigned int times);

    inline void setInnerAction(FiniteTimeAction *action)
    {
        if (_innerAction != action)
        {
            CC_SAFE_RETAIN(action);
            CC_SAFE_RELEASE(_innerAction);
            _innerAction = action;
        }
    }

    inline FiniteTimeAction* getInnerAction()
    {
        return _innerAction;
    }

    //
    // 重载
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

    /** 初始化一个重复性动作。第二个参数表示次数，是一个取值在1到2的30次方之间的无符号整数*/
    bool initWithAction(FiniteTimeAction *pAction, unsigned int times);

protected:
    unsigned int _times;
    unsigned int _total;
    float _nextDt;
    bool _actionInstant;
    /** 内部动作成员变量 */
    FiniteTimeAction *_innerAction;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Repeat);
};

/** @brief Repeats an action for ever.
To repeat the an action for a limited number of times use the Repeat action.
@warning This action can't be Sequenceable because it is not an IntervalAction
*/
class CC_DLL RepeatForever : public ActionInterval
{
public:
    /** 创建动作 */
    static RepeatForever* create(ActionInterval *action);

    inline void setInnerAction(ActionInterval *action)
    {
        if (_innerAction != action)
        {
            CC_SAFE_RELEASE(_innerAction);
            _innerAction = action;
            CC_SAFE_RETAIN(_innerAction);
        }
    }

    inline ActionInterval* getInnerAction()
    {
        return _innerAction;
    }

    //
    // 重载
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

    /** 初始化动作 */
    bool initWithAction(ActionInterval *action);

protected:
    /** 内部动作成员变量 */
    ActionInterval *_innerAction;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RepeatForever);
};

/** @brief Spawn a new action immediately
 */
class CC_DLL Spawn : public ActionInterval
{
public:
    /** helper constructor to create an array of spawned actions 
     * @code
     * When this funtion bound to the js or lua,the input params changed
     * in js  :var   create(var   object1,var   object2, ...)
     * in lua :local create(local object1,local object2, ...)
     * @endcode
     */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // WP8在VS2012中，不支持在变量参数列表中使用nullptr，也不支持可变参数模板
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

    // 在WP8平台上，对于变量参数列表多余10项的情况，使用其他的创建函数或者是使用以NULL作为最后一个参数的可变参数的创建函数
    static Spawn* variadicCreate(FiniteTimeAction* item, ...);
#else
    static Spawn* create(FiniteTimeAction *action1, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

    /** 创建一组同时发生的动作的协助构造函数 */
    static Spawn* createWithVariableList(FiniteTimeAction *action1, va_list args);

   
    /**通过一组给定的动作创建一组同时发生的动作的协助构造函数*/
    static Spawn* create(const Vector<FiniteTimeAction*>& arrayOfActions);

    /** 创建同时发生的动作 */
    static Spawn* createWithTwoActions(FiniteTimeAction *action1, FiniteTimeAction *action2);

    //
    // 重载
    //
    virtual Spawn* clone() const override;
	virtual Spawn* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Spawn() {}
    virtual ~Spawn();

    /** 用两个动作为参数初始化同时发生的动作 */
    bool initWithTwoActions(FiniteTimeAction *action1, FiniteTimeAction *action2);

protected:
    FiniteTimeAction *_one;
    FiniteTimeAction *_two;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Spawn);
};

/** @brief Rotates a Node object to a certain angle by modifying it's
 rotation attribute.
 The direction will be decided by the shortest angle.
*/ 
class CC_DLL RotateTo : public ActionInterval
{
public:
    /** 用单独的旋转角度创建动作 */
    static RotateTo* create(float duration, float deltaAngleX, float deltaAngleY);

    /** 创建动作 */
    static RotateTo* create(float duration, float deltaAngle);

    //
    // 重载
    //
    virtual RotateTo* clone() const override;
    virtual RotateTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    RotateTo() {}
    virtual ~RotateTo() {}

    /** 初始化动作 */
    bool initWithDuration(float duration, float deltaAngle);
    bool initWithDuration(float duration, float deltaAngleX, float deltaAngleY);
    
protected:
    float _dstAngleX;
    float _startAngleX;
    float _diffAngleX;
    
    float _dstAngleY;
    float _startAngleY;
    float _diffAngleY;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RotateTo);
};

/** @brief Rotates a Node object clockwise a number of degrees by modifying it's rotation attribute.
*/
class CC_DLL RotateBy : public ActionInterval
{
public:
    /** 创建动作*/
    static RotateBy* create(float duration, float deltaAngle);
    static RotateBy* create(float duration, float deltaAngleZ_X, float deltaAngleZ_Y);
    static RotateBy* create(float duration, const Vec3& deltaAngle3D);

    //
    // 重载
    //
    virtual RotateBy* clone() const override;
	virtual RotateBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    RotateBy();
    virtual ~RotateBy() {}

    /** 初始化动作 */
    bool initWithDuration(float duration, float deltaAngle);
    bool initWithDuration(float duration, float deltaAngleZ_X, float deltaAngleZ_Y);
    bool initWithDuration(float duration, const Vec3& deltaAngle3D);
    
protected:
    float _angleZ_X;
    float _startAngleZ_X;
    float _angleZ_Y;
    float _startAngleZ_Y;

    bool _is3D;
    Vec3 _angle3D;
    Vec3 _startAngle3D;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RotateBy);
};

/** 通过修改节点对象的位置属性来改变节点对象的x,y像素。
 * x,y的坐标是相对于这个对象的位置来说的。
 几个MoveBy动作可以同时被调用，最终的运动是这几个单独运动的综合
 @since v2.1beta2-custom
 */
class CC_DLL MoveBy : public ActionInterval
{
public:
    /** 创建动作*/
    static MoveBy* create(float duration, const Vec2& deltaPosition);

    //
    // 重载
    //
    virtual MoveBy* clone() const override;
	virtual MoveBy* reverse(void) const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    MoveBy() {}
    virtual ~MoveBy() {}

    /**初始化动作 */
    bool initWithDuration(float duration, const Vec2& deltaPosition);

protected:
    Vec2 _positionDelta;
    Vec2 _startPosition;
    Vec2 _previousPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MoveBy);
};

/** 移动节点对象到位置x,y。x,y是绝对坐标，通过修改它的位置属性来改变它们的值。
 几个MoveTo动作可以被同时调用，并且最终的运动是几个单独运动的综合。
 @since v2.1beta2-custom
 */
class CC_DLL MoveTo : public MoveBy
{
public:
    /** 创建动作 */
    static MoveTo* create(float duration, const Vec2& position);

    //
    // 重载
    //
    virtual MoveTo* clone() const override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    MoveTo() {}
    virtual ~MoveTo() {}

    /** 初始化动作 */
    bool initWithDuration(float duration, const Vec2& position);

protected:
    Vec2 _endPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MoveTo);
};

/** 
 * 通过修改节点对象的skewX和skewY属性来使节点对象倾斜到一个给定的角度。
@since v1.0
*/
class CC_DLL SkewTo : public ActionInterval
{
public:
    /** 创建动作 */
    static SkewTo* create(float t, float sx, float sy);

    //
    // 重载
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

/** 通过skewX和skewY的度数来事节点对象倾斜
@since v1.0
*/
class CC_DLL SkewBy : public SkewTo
{
public:
    /** 创建动作*/
    static SkewBy* create(float t, float deltaSkewX, float deltaSkewY);

    //
    // 重载
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

/** @brief Moves a Node object simulating a parabolic jump movement by modifying it's position attribute.
*/
class CC_DLL JumpBy : public ActionInterval
{
public:
    /** 创建动作n */
    static JumpBy* create(float duration, const Vec2& position, float height, int jumps);

    //
    // 重载
    //
    virtual JumpBy* clone() const override;
	virtual JumpBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    JumpBy() {}
    virtual ~JumpBy() {}

    /** 初始化动作 */
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

/** @brief Moves a Node object to a parabolic position simulating a jump movement by modifying it's position attribute.
*/ 
class CC_DLL JumpTo : public JumpBy
{
public:
    /**创建动作 */
    static JumpTo* create(float duration, const Vec2& position, float height, int jumps);

    //
    // 重载
    //
    virtual void startWithTarget(Node *target) override;
    virtual JumpTo* clone() const override;
	virtual JumpTo* reverse(void) const override;

private:
    JumpTo() {}
    virtual ~JumpTo() {}
    CC_DISALLOW_COPY_AND_ASSIGN(JumpTo);
};

/** 贝塞尔曲线的配置结构体
 */
typedef struct _ccBezierConfig {
    //! 贝塞尔曲线的终点
    Vec2 endPosition;
    //! 贝塞尔曲线的第一个控制点
    Vec2 controlPoint_1;
    //! 贝塞尔曲线的第二个控制点
    Vec2 controlPoint_2;
} ccBezierConfig;

/** @brief An action that moves the target with a cubic Bezier curve by a certain distance.
 */
class CC_DLL BezierBy : public ActionInterval
{
public:
    /** 
     * 以持续时间和贝塞尔曲线的配置结构体为参数创建动作
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js: var create(var t,var table)
     * in lua: lcaol create(local t, local table)
     * @endcode
     */
    static BezierBy* create(float t, const ccBezierConfig& c);

    //
    // 重载
    //
    virtual BezierBy* clone() const override;
	virtual BezierBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    BezierBy() {}
    virtual ~BezierBy() {}

    /** 以持续时间和贝塞尔曲线的配置结构体为参数初始化动作 */
    bool initWithDuration(float t, const ccBezierConfig& c);

protected:
    ccBezierConfig _config;
    Vec2 _startPosition;
    Vec2 _previousPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(BezierBy);
};

/** @brief An action that moves the target with a cubic Bezier curve to a destination point.
 @since v0.8.2
 */
class CC_DLL BezierTo : public BezierBy
{
public:
    /** 以持续时间和贝塞尔曲线的配置结构体为参数创建动作
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js: var create(var t,var table)
     * in lua: lcaol create(local t, local table)
     * @endcode
     */
    static BezierTo* create(float t, const ccBezierConfig& c);

    //
    // 重载
    //
    virtual void startWithTarget(Node *target) override;
    virtual BezierTo* clone() const override;
	virtual BezierTo* reverse(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    BezierTo() {}
    virtual ~BezierTo() {}

    bool initWithDuration(float t, const ccBezierConfig &c);

protected:
    ccBezierConfig _toConfig;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(BezierTo);
};

/** @brief Scales a Node object to a zoom factor by modifying it's scale attribute.
 @warning This action doesn't support "reverse"
 */
class CC_DLL ScaleTo : public ActionInterval
{
public:
    /** 创建一个X和Y有相同的缩放因子的动作 */
    static ScaleTo* create(float duration, float s);

    /** 用X和Y的缩放因子去创建动作(X和Y的缩放因子可以不同) */
    static ScaleTo* create(float duration, float sx, float sy);

    /** 用X、Y、Z的缩放因子创建动作 */
    static ScaleTo* create(float duration, float sx, float sy, float sz);

    //
    // 重载
    //
    virtual ScaleTo* clone() const override;
	virtual ScaleTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ScaleTo() {}
    virtual ~ScaleTo() {}

    /** 初始化一个X和Y有相同的缩放因子的动作 */
    bool initWithDuration(float duration, float s);
    /** 用X和Y的缩放因子初始化动作 */
    bool initWithDuration(float duration, float sx, float sy);
    /** 用X、Y、Z的缩放因子初始化动作 */
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

/** @brief Scales a Node object a zoom factor by modifying it's scale attribute.
*/
class CC_DLL ScaleBy : public ScaleTo
{
public:
    /** 创建一个X和Y有相同的缩放因子的动作 */
    static ScaleBy* create(float duration, float s);

    /** 用X和Y的缩放因子去创建动作(X和Y的缩放因子可以不同) */
    static ScaleBy* create(float duration, float sx, float sy);

    /** 用X、Y、Z的缩放因子创建动作 */
    static ScaleBy* create(float duration, float sx, float sy, float sz);

    //
    // 重载
    //
    virtual void startWithTarget(Node *target) override;
    virtual ScaleBy* clone() const override;
	virtual ScaleBy* reverse(void) const override;

protected:
    ScaleBy() {}
    virtual ~ScaleBy() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ScaleBy);
};

/** @brief Blinks a Node object by modifying it's visible attribute
*/
class CC_DLL Blink : public ActionInterval
{
public:
    /** 创建动作 */
    static Blink* create(float duration, int blinks);

    //
    // 重载
    //
    virtual Blink* clone() const override;
	virtual Blink* reverse(void) const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop() override;
    
CC_CONSTRUCTOR_ACCESS:
    Blink() {}
    virtual ~Blink() {}

    /** 初始化动作 */
    bool initWithDuration(float duration, int blinks);
    
protected:
    int _times;
    bool _originalState;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Blink);
};


/** @brief Fades an object that implements the RGBAProtocol protocol. It modifies the opacity from the current value to a custom one.
 @warning This action doesn't support "reverse"
 */
class CC_DLL FadeTo : public ActionInterval
{
public:
    /** 用持续时间和不透明度创建动作 */
    static FadeTo* create(float duration, GLubyte opacity);

    //
    // 重载
    //
    virtual FadeTo* clone() const override;
	virtual FadeTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    FadeTo() {}
    virtual ~FadeTo() {}

    /** 用持续时间和不透明度初始化动作 */
    bool initWithDuration(float duration, GLubyte opacity);

protected:
    GLubyte _toOpacity;
    GLubyte _fromOpacity;
    friend class FadeOut;
    friend class FadeIn;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeTo);
};

/** @brief Fades In an object that implements the RGBAProtocol protocol. It modifies the opacity from 0 to 255.
 The "reverse" of this action is FadeOut
 */
class CC_DLL FadeIn : public FadeTo
{
public:
    /** 创建动作*/
    static FadeIn* create(float d);

    //
    //重载
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeIn* clone() const override;
	virtual FadeTo* reverse(void) const override;
    
    void setReverseAction(FadeTo* ac);

protected:
    FadeIn():_reverseAction(nullptr) {}
    virtual ~FadeIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeIn);
    FadeTo* _reverseAction;
};

/** @brief Fades Out an object that implements the RGBAProtocol protocol. It modifies the opacity from 255 to 0.
 The "reverse" of this action is FadeIn
*/
class CC_DLL FadeOut : public FadeTo
{
public:
    /** 创建动作 */
    static FadeOut* create(float d);

    //
    // 重载
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeOut* clone() const  override;
	virtual FadeTo* reverse(void) const override;
    
    void setReverseAction(FadeTo* ac);

protected:
    FadeOut():_reverseAction(nullptr) {}
    virtual ~FadeOut() {}
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOut);
    FadeTo* _reverseAction;
};
/** @brief Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 @warning This action doesn't support "reverse"
 @since v0.7.2
*/
class CC_DLL TintTo : public ActionInterval
{
public:
    /** 用持续时间和颜色创建动作 */
    static TintTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue);

    //
    // 重载
    //
    virtual TintTo* clone() const override;
	virtual TintTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TintTo() {}
    virtual ~TintTo() {}

    /** 用持续时间和颜色初始化动作*/
    bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue);

protected:
    Color3B _to;
    Color3B _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TintTo);
};

/** @brief Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 @since v0.7.2
 */
class CC_DLL TintBy : public ActionInterval
{
public:
    /** 用持续时间和颜色创建动作 */
    static TintBy* create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

    //
    // 重载
    //
    virtual TintBy* clone() const override;
	virtual TintBy* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TintBy() {}
    virtual ~TintBy() {}

    /** 用持续时间和颜色初始化动作 */
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

/** @brief Delays the action a certain amount of seconds
*/
class CC_DLL DelayTime : public ActionInterval
{
public:
    /** 创建动作 */
    static DelayTime* create(float d);

    //
    // 重载
    //
    virtual void update(float time) override;
    virtual DelayTime* reverse() const override;
    virtual DelayTime* clone() const override;

protected:
    DelayTime() {}
    virtual ~DelayTime() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(DelayTime);
};

/** @brief Executes an action in reverse order, from time=duration to time=0
 
 @warning Use this action carefully. This action is not
 sequenceable. Use it as the default "reversed" method
 of your own actions, but using it outside the "reversed"
 scope is not recommended.
*/
class CC_DLL ReverseTime : public ActionInterval
{
public:
    /** 创建动作 */
    static ReverseTime* create(FiniteTimeAction *action);

    //
    // 重载
    //
	virtual ReverseTime* reverse() const override;
    virtual ReverseTime* clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ReverseTime();
    virtual ~ReverseTime(void);

    /** 初始化动作 */
    bool initWithAction(FiniteTimeAction *action);

protected:
    FiniteTimeAction *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ReverseTime);
};

class Texture2D;
/** @brief Animates a sprite given the name of an Animation */
class CC_DLL Animate : public ActionInterval
{
public:
    /*用一个动画创建动作，当这个动画结束的时候恢复原来的帧*/
    static Animate* create(Animation *animation);

    /** 设置动画对象 */
    void setAnimation( Animation* animation );
    /** 返回正在运行的动画对象 */
    Animation* getAnimation() { return _animation; }
    const Animation* getAnimation() const { return _animation; }

    //
    // 重载
    //
    virtual Animate* clone() const override;
    virtual Animate* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float t) override;
    
CC_CONSTRUCTOR_ACCESS:
    Animate();
    virtual ~Animate();

    /** 用一个动画初始化动作，当这个动画结束的时候恢复原来的帧 */
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

/**改写一个动作的目标，让这个动作可以在动作创建的时候运行在一个指定的目标上，而不是运行在通过runAction指定的目标
 */
class CC_DLL TargetedAction : public ActionInterval
{
public:
    /** 用具体的动作和强制的目标创建动作 */
    static TargetedAction* create(Node* target, FiniteTimeAction* action);

    /** 设置讲强制运行这个动作的目标*/
    void setForcedTarget(Node* forcedTarget);
    /** 返回强制运行这个动作的目标 */
    Node* getForcedTarget() { return _forcedTarget; }
    const Node* getForcedTarget() const { return _forcedTarget; }

    //
    // 重载
    //
    virtual TargetedAction* clone() const override;
    virtual TargetedAction* reverse() const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TargetedAction();
    virtual ~TargetedAction();

    /** 用具体的动作和强制的目标初始化动作 */
    bool initWithTarget(Node* target, FiniteTimeAction* action);

protected:
    FiniteTimeAction* _action;
    Node* _forcedTarget;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TargetedAction);
};

// 结束
/// @}

NS_CC_END

#endif //__ACTION_CCINTERVAL_ACTION_H__

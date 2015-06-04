/****************************************************************************
Copyright (c) 2008-2009 Jason Booth
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

#ifndef __ACTION_CCEASE_ACTION_H__
#define __ACTION_CCEASE_ACTION_H__

#include "2d/CCActionInterval.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** 
 @class ActionEase
 @brief @~english Base class for Easing actions.
 * @~chinese 缓动动作的基类。
 @details @~english Ease actions are created from other interval actions.
         The ease action will change the timeline of the inner action.
 * @~chinese 缓动动作是基于其他持续时间动作创建出来的。
 * 缓动动作会改变内部动作的时间轴，赋予缓动特效。
 @ingroup Actions
 */
class CC_DLL ActionEase : public ActionInterval
{
public:

    /**
    @brief @~english Get the pointer of the inner action.
     * @~chinese 内行动的指针。
    @return @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
    */
    virtual ActionInterval* getInnerAction();

    //
    // Overrides
    //
    virtual ActionEase* clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
    
    virtual ActionEase* reverse() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

    virtual void startWithTarget(Node *target) override;
    virtual void stop() override;
    virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
    ActionEase() {}
    virtual ~ActionEase();
    /** 
     @brief @~english Initializes the action.
     * @~chinese 初始化动作。
     @return @~english Return true when the initialization success, otherwise return false.
     * @~chinese 返回true时,初始化成功,否则返回假。
    */
    bool initWithAction(ActionInterval *action);

protected:
    /** @~english The inner action  @~chinese 内部的行动*/
    ActionInterval *_inner;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ActionEase);
};

/** 
 @class EaseRateAction
 @brief @~english Base class for Easing actions with rate parameters.
 * @~chinese 基类与速度参数对宽松政策的行为。
 @details @~english Ease the inner action with specified rate.
 * @~chinese 缓解内心的动作与指定利率。
 @ingroup Actions
 */
class CC_DLL EaseRateAction : public ActionEase
{
public:
    /**
     @brief @~english Creates the action with the inner action and the rate parameter.
     * @~chinese 创建行动的内在行动和速度参数。
     @param action @~english A given ActionInterval
     * @~chinese 一个给定ActionInterval
     @param rate @~english A given rate
     * @~chinese 一个给定的速度
     @return @~english An autoreleased EaseRateAction object.
     * @~chinese 一个autoreleased EaseRateAction对象。
    **/
    static EaseRateAction* create(ActionInterval* action, float rate);
    
    /**
     @brief @~english Set the rate value for the ease rate action.
     * @~chinese 设定的速度值缓解率的行动。
     @param rate @~english The value will be set.
     * @~chinese 值将被设置。
     */
    inline void setRate(float rate) { _rate = rate; }
    /**
     @brief @~english Get the rate value of the ease rate action.
     * @~chinese 缓解率行动的速度值。
     @return @~english Return the rate value of the ease rate action.
     * @~chinese 返回的值的缓解率的行动。
     */
    inline float getRate() const { return _rate; }

    //
    // Overrides
    //
    virtual EaseRateAction* clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
    virtual EaseRateAction* reverse() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

CC_CONSTRUCTOR_ACCESS:
    EaseRateAction() {}
    virtual ~EaseRateAction();
    /** 
     @brief @~english Initializes the action with the inner action and the rate parameter.
     * @~chinese 初始化动作与内在的行动和速度参数。
     @param pAction @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @param fRate @~english The value of the rate parameter.
     * @~chinese 速度参数的值。
     @return @~english Return true when the initialization success, otherwise return false.
     * @~chinese 返回true时,初始化成功,否则返回假。
     */
    bool initWithAction(ActionInterval *pAction, float fRate);

protected:
    float _rate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseRateAction);
};

/** 
 @class EaseIn
 @brief @~english EaseIn action with a rate.
 * @~chinese EaseIn行动速度。
 @details @~english The timeline of inner action will be changed by:
         \f${ time }^{ rate }\f$.
 * @~chinese 内心的行动将改变的时间表:
 * \ f ^ } { { time雷亚尔} \ f脾美元。
 @ingroup Actions
 */
class CC_DLL EaseIn : public EaseRateAction
{
public:
    /** 
     @brief @~english Create the action with the inner action and the rate parameter.
     * @~chinese 创建行动的内在行动和速度参数。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @param rate @~english The value of the rate parameter.
     * @~chinese 速度参数的值。
     @return @~english A pointer of EaseIn action. If creation failed, return nil.
     * @~chinese EaseIn行动的指针。如果创建失败,返回零。
    */
    static EaseIn* create(ActionInterval* action, float rate);

    // Overrides
    virtual void update(float time) override;
    virtual EaseIn* clone() const override;
    virtual EaseIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseIn() {}
    virtual ~EaseIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseIn);
};

/** 
 @class EaseOut
 @brief @~english EaseOut action with a rate.
 * @~chinese EaseOut行动速度。
 @details @~english The timeline of inner action will be changed by:
         \f${ time }^ { (1/rate) }\f$.
 * @~chinese 内心的行动将改变的时间表:
 * \ f ^ } { { time雷亚尔(1
 @ingroup Actions
 */
class CC_DLL EaseOut : public EaseRateAction
{
public:
    /** 
     @brief @~english Create the action with the inner action and the rate parameter.
     * @~chinese Create the action with the inner action and the rate parameter.
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @param rate @~english The value of the rate parameter.
     * @~chinese 速度参数的值。
     @return @~english A pointer of EaseOut action. If creation failed, return nil.
     * @~chinese EaseOut行动的指针。如果创建失败,返回零。
    */
    static EaseOut* create(ActionInterval* action, float rate);

    // Overrides
    virtual void update(float time) override;
    virtual EaseOut* clone() const  override;
    virtual EaseOut* reverse() const  override;

CC_CONSTRUCTOR_ACCESS:
    EaseOut() {}
    virtual ~EaseOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseOut);
};

/** 
 @class EaseInOut
 @brief @~english EaseInOut action with a rate
 * @~chinese EaseInOut行动速度
 @details @~english If time * 2 < 1, the timeline of inner action will be changed by:
         \f$0.5*{ time }^{ rate }\f$.
         Else, the timeline of inner action will be changed by:
         \f$1.0-0.5*{ 2-time }^{ rate }\f$.
 * @~chinese 如果时间* 2 < 1,内在的行动将改变的时间表:
 * $ 0.5 f \
 * 别的,内在的行动将改变的时间表:
 * \ f 1.0美元1.0
 @ingroup Actions
 */
class CC_DLL EaseInOut : public EaseRateAction
{
public:
    /** 
     @brief @~english Create the action with the inner action and the rate parameter.
     * @~chinese 创建行动的内在行动和速度参数。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @param rate @~english The value of the rate parameter.
     * @~chinese 速度参数的值。
     @return @~english A pointer of EaseInOut action. If creation failed, return nil.
     * @~chinese EaseInOut行动的指针。如果创建失败,返回零。
    */
    static EaseInOut* create(ActionInterval* action, float rate);

    // Overrides
    virtual void update(float time) override;
    virtual EaseInOut* clone() const  override;
    virtual EaseInOut* reverse() const  override;

CC_CONSTRUCTOR_ACCESS:
    EaseInOut() {}
    virtual ~EaseInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseInOut);
};

/** 
 @class EaseExponentialIn
 @brief @~english Ease Exponential In action.
 * @~chinese 缓解指数。
 @details @~english The timeline of inner action will be changed by:
         \f${ 2 }^{ 10*(time-1) }-1*0.001\f$.
 * @~chinese 内心的行动将改变的时间表:
 * \ f $ { 2 } { 10 ^
 @ingroup Actions
 */
class CC_DLL EaseExponentialIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseExponentialIn action. If creation failed, return nil.
     * @~chinese EaseExponentialIn行动的指针。如果创建失败,返回零。
    */
    static EaseExponentialIn* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseExponentialIn* clone() const override;
    virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseExponentialIn() {}
    virtual ~EaseExponentialIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseExponentialIn);
};

/** 
 @class EaseExponentialOut
 @brief @~english Ease Exponential Out
 * @~chinese 缓解指数从
 @details @~english The timeline of inner action will be changed by:
         \f$1-{ 2 }^{ -10*(time-1) }\f$.
 * @~chinese 内心的行动将改变的时间表:
 * \ f 1 - { 2 } ^ { -10美元
 @ingroup Actions
 */
class CC_DLL EaseExponentialOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseExponentialOut action. If creation failed, return nil.
     * @~chinese EaseExponentialOut行动的指针。如果创建失败,返回零。
    */
    static EaseExponentialOut* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseExponentialOut* clone() const override;
    virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseExponentialOut() {}
    virtual ~EaseExponentialOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseExponentialOut);
};

/** 
 @class EaseExponentialInOut
 @brief @~english Ease Exponential InOut
 * @~chinese 缓解指数InOut
 @details @~english If time * 2 < 1, the timeline of inner action will be changed by:
         \f$0.5*{ 2 }^{ 10*(time-1) }\f$.
         else, the timeline of inner action will be changed by:
         \f$0.5*(2-{ 2 }^{ -10*(time-1) })\f$.
 * @~chinese 如果时间* 2 < 1,内在的行动将改变的时间表:
 * \ f 0.5美元
 * 别的,内在的行动将改变的时间表:
 * \ f 0.5美元
 @ingroup Actions
 */
class CC_DLL EaseExponentialInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseExponentialInOut action. If creation failed, return nil.
     * @~chinese EaseExponentialInOut行动的指针。如果创建失败,返回零。
    */
    static EaseExponentialInOut* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseExponentialInOut* clone() const override;
    virtual EaseExponentialInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseExponentialInOut() {}
    virtual ~EaseExponentialInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseExponentialInOut);
};

/** 
 @class EaseSineIn
 @brief @~english Ease Sine In
 * @~chinese 缓解的正弦
 @details @~english The timeline of inner action will be changed by:
         \f$1-cos(time*\frac { \pi  }{ 2 } )\f$.
 * @~chinese 内心的行动将改变的时间表:
 * \ f $ 1-cos(时间
 @ingroup Actions
 */
class CC_DLL EaseSineIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseSineIn action. If creation failed, return nil.
     * @~chinese EaseSineIn行动的指针。如果创建失败,返回零。
    */
    static EaseSineIn* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseSineIn* clone() const override;
    virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseSineIn() {}
    virtual ~EaseSineIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseSineIn);
};

/** 
 @class EaseSineOut
 @brief @~english Ease Sine Out
 * @~chinese 缓解正弦出来
 @details @~english The timeline of inner action will be changed by:
         \f$sin(time*\frac { \pi  }{ 2 } )\f$.
 * @~chinese 内心的行动将改变的时间表:
 * \ f(time sin美元
 @ingroup Actions
 */
class CC_DLL EaseSineOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseSineOut action. If creation failed, return nil.
     * @~chinese EaseSineOut of A对准行动。如果就业机会、尼罗河破产。
    */
    static EaseSineOut* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseSineOut* clone() const override;
    virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseSineOut() {}
    virtual ~EaseSineOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseSineOut);
};

/** 
 @class EaseSineInOut
 @brief @~english Ease Sine InOut
 * @~chinese 缓解正弦InOut
 @details @~english The timeline of inner action will be changed by:
         \f$-0.5*(cos(\pi *time)-1)\f$.
 * @~chinese 内心的行动将改变的时间表:
 * \ f - 0.5美元
 @ingroup Actions
 */
class CC_DLL EaseSineInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseSineInOut action. If creation failed, return nil.
     * @~chinese EaseSineInOut行动的指针。如果创建失败,返回零。
    */
    static EaseSineInOut* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseSineInOut* clone() const override;
    virtual EaseSineInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseSineInOut() {}
    virtual ~EaseSineInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseSineInOut);
};

/** 
 @class EaseElastic
 @brief @~english Ease Elastic abstract class
 * @~chinese 缓解弹性抽象类
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElastic : public ActionEase
{
public:

    /** 
     @brief @~english Get period of the wave in radians. Default value is 0.3.
     * @~chinese 周期波的弧度。默认值是0.3。
     @return @~english Return the period of the wave in radians.
     * @~chinese 回报周期波的弧度。
    */
    inline float getPeriod() const { return _period; }
    /**
     @brief @~english Set period of the wave in radians.
     * @~chinese 设置周期波的弧度。
     @param fPeriod @~english The value will be set.
     * @~chinese 值将被设置。
    */
    inline void setPeriod(float fPeriod) { _period = fPeriod; }

    //
    // Overrides
    //
    virtual EaseElastic* clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
    
    virtual EaseElastic* reverse() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

CC_CONSTRUCTOR_ACCESS:
    EaseElastic() {}
    virtual ~EaseElastic() {}
    /** 
     @brief @~english Initializes the action with the inner action and the period in radians.
     * @~chinese 初始化动作与内在的行动和弧度的时期。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @param period @~english Period of the wave in radians. Default is 0.3.
     * @~chinese 波的弧度。默认是0.3。
     @return @~english Return true when the initialization success, otherwise return false.
     * @~chinese 返回true时,初始化成功,否则返回假。
    */
    bool initWithAction(ActionInterval *action, float period = 0.3f);

protected:
    float _period;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElastic);

};

/** 
 @class EaseElasticIn
 @brief @~english Ease Elastic In action.
 * @~chinese 缓解弹性。
 @details @~english If time == 0 or time == 1, the timeline of inner action will not be changed.
         Else, the timeline of inner action will be changed by:
         \f$-{ 2 }^{ 10*(time-1) }*sin((time-1-\frac { period }{ 4 } )*\pi *2/period)\f$.

 * @~chinese 如果时间= = = = 1,0或时间内行动的时间表将不会改变。
 * 别的,内在的行动将改变的时间表:
 * \ f $ { 2 } { ^ - 10
 * 
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用一个双射函数。
 * 等操作序列可能会使用这个动作时一个意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticIn : public EaseElastic
{
public:
    /** 
     @brief @~english Create the EaseElasticIn action with the inner action and the period in radians.
     * @~chinese 创建EaseElasticIn行动的内在行动和弧度的时期。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @param period @~english Period of the wave in radians.
     * @~chinese 波的弧度。
     @return @~english A pointer of EaseElasticIn action. If creation failed, return nil.
     * @~chinese EaseElasticIn行动的指针。如果创建失败,返回零。
    */
    static EaseElasticIn* create(ActionInterval *action, float period);

    /** 
     @brief @~english Create the EaseElasticIn action with the inner action and period value is 0.3.
     * @~chinese 创建EaseElasticIn行动的内在行动和时间值是0.3。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseElasticIn action. If creation failed, return nil.
     * @~chinese EaseElasticIn行动的指针。如果创建失败,返回零。
    */
    static EaseElasticIn* create(ActionInterval *action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseElasticIn* clone() const override;
    virtual EaseElastic* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseElasticIn() {}
    virtual ~EaseElasticIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElasticIn);
};

/** 
 @class EaseElasticOut
 @brief @~english Ease Elastic Out action.
 * @~chinese 缓解弹性行为。
 @details @~english If time == 0 or time == 1, the timeline of inner action will not be changed.
         Else, the timeline of inner action will be changed by:
         \f${ 2 }^{ -10*time }*sin((time-\frac { period }{ 4 } )*\pi *2/period)+1\f$.
 * @~chinese 如果时间= = = = 1,0或时间内行动的时间表将不会改变。
 * 别的,内在的行动将改变的时间表:
 * \ f $ { 2 } {约^
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用一个双射函数。
 * 等操作序列可能会使用这个动作时一个意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticOut : public EaseElastic
{
public:
    /** 
     @brief @~english Create the EaseElasticOut action with the inner action and the period in radians.
     * @~chinese 创建EaseElasticOut行动的内在行动和弧度的时期。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @param period @~english Period of the wave in radians.
     * @~chinese 波的弧度。
     @return @~english A pointer of EaseElasticOut action. If creation failed, return nil.
     * @~chinese EaseElasticOut行动的指针。如果创建失败,返回零。
    */
    static EaseElasticOut* create(ActionInterval *action, float period);

    /** 
     @brief @~english Create the EaseElasticOut action with the inner action and period value is 0.3.
     * @~chinese 创建EaseElasticOut行动的内在行动和时间值是0.3。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseElasticOut action. If creation failed, return nil.
     * @~chinese EaseElasticOut行动的指针。如果创建失败,返回零。
    */
    static EaseElasticOut* create(ActionInterval *action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseElasticOut* clone() const override;
    virtual EaseElastic* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseElasticOut() {}
    virtual ~EaseElasticOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElasticOut);
};

/** 
 @class EaseElasticInOut
 @brief @~english Ease Elastic InOut action.
 * @~chinese 缓解弹性InOut行动。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用一个双射函数。
 * 等操作序列可能会使用这个动作时一个意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticInOut : public EaseElastic
{
public:
    /** 
     @brief @~english Create the EaseElasticInOut action with the inner action and the period in radians.
     * @~chinese 创建EaseElasticInOut行动的内在行动和弧度的时期。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @param period @~english Period of the wave in radians.
     * @~chinese 波的弧度。
     @return @~english A pointer of EaseElasticInOut action. If creation failed, return nil.
     * @~chinese EaseElasticInOut行动的指针。如果创建失败,返回零。
    */
    static EaseElasticInOut* create(ActionInterval *action, float period);

    /** 
     @brief @~english Create the EaseElasticInOut action with the inner action and period value is 0.3.
     * @~chinese 创建EaseElasticInOut行动的内在行动和时间值是0.3。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseElasticInOut action. If creation failed, return nil.
     * @~chinese EaseElasticInOut行动的指针。如果创建失败,返回零。
    */
    static EaseElasticInOut* create(ActionInterval *action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseElasticInOut* clone() const override;
    virtual EaseElasticInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseElasticInOut() {}
    virtual ~EaseElasticInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElasticInOut);
};

/** 
 @class EaseBounce
 @brief @~english EaseBounce abstract class.
 * @~chinese EaseBounce抽象类。
 @since v0.8.2
 @ingroup Actions
*/
class CC_DLL EaseBounce : public ActionEase
{
public:

    // Overrides
    virtual EaseBounce* clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

    virtual EaseBounce* reverse() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

CC_CONSTRUCTOR_ACCESS:
    EaseBounce() {}
    virtual ~EaseBounce() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBounce);
};

/** 
 @class EaseBounceIn
 @brief @~english EaseBounceIn action.
 * @~chinese EaseBounceIn行动。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用一个双射函数。
 * 等操作序列可能会使用这个动作时一个意想不到的结果。
 @since v0.8.2
 @ingroup Actions
*/
class CC_DLL EaseBounceIn : public EaseBounce
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseBounceIn action. If creation failed, return nil.
     * @~chinese EaseBounceIn行动的指针。如果创建失败,返回零。
    */
    static EaseBounceIn* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseBounceIn* clone() const override;
    virtual EaseBounce* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBounceIn() {}
    virtual ~EaseBounceIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBounceIn);
};

/** 
 @class EaseBounceOut
 @brief @~english EaseBounceOut action.
 * @~chinese EaseBounceOut行动。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese This action doesn 't use a bijective function.
 * 有可能像行动顺序发生an action因此当used with this。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBounceOut : public EaseBounce
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseBounceOut action. If creation failed, return nil.
     * @~chinese EaseBounceOut行动的指针。如果创建失败,返回零。
    */
    static EaseBounceOut* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseBounceOut* clone() const override;
    virtual EaseBounce* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBounceOut() {}
    virtual ~EaseBounceOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBounceOut);
};

/** 
 @class EaseBounceInOut
 @brief @~english EaseBounceInOut action.
 * @~chinese EaseBounceInOut行动。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用一个双射函数。
 * 等操作序列可能会使用这个动作时一个意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBounceInOut : public EaseBounce
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseBounceInOut action. If creation failed, return nil.
     * @~chinese EaseBounceInOut行动的指针。如果创建失败,返回零。
    */
    static EaseBounceInOut* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseBounceInOut* clone() const override;
    virtual EaseBounceInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBounceInOut() {}
    virtual ~EaseBounceInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBounceInOut);
};

/** 
 @class EaseBackIn
 @brief @~english EaseBackIn action.
 * @~chinese EaseBackIn行动。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用一个双射函数。
 * 等操作序列可能会使用这个动作时一个意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseBackIn action. If creation failed, return nil.
     * @~chinese EaseBackIn行动的指针。如果创建失败,返回零。
    */
    static EaseBackIn* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseBackIn* clone() const override;
    virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBackIn() {}
    virtual ~EaseBackIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBackIn);
};

/** 
 @class EaseBackOut
 @brief @~english EaseBackOut action.
 * @~chinese EaseBackOut行动。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用一个双射函数。
 * 等操作序列可能会使用这个动作时一个意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseBackOut action. If creation failed, return nil.
     * @~chinese EaseBackOut行动的指针。如果创建失败,返回零。
    */
    static EaseBackOut* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseBackOut* clone() const override;
    virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBackOut() {}
    virtual ~EaseBackOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBackOut);
};

/** 
 @class EaseBackInOut
 @brief @~english EaseBackInOut action.
 * @~chinese EaseBackInOut行动。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用一个双射函数。
 * Actions like Sequence took have an unexpected result when 2 with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseBackInOut action. If creation failed, return nil.
     * @~chinese A pointer of EaseBackInOut action. If creation failed, return nil.
    */
    static EaseBackInOut* create(ActionInterval* action);

    // Overrides
    virtual void update(float time) override;
    virtual EaseBackInOut* clone() const override;
    virtual EaseBackInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBackInOut() {}
    virtual ~EaseBackInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBackInOut);
};


/** 
@class EaseBezierAction
@brief @~english Ease Bezier
 * @~chinese 缓解贝塞尔曲线
@ingroup Actions
*/
class CC_DLL EaseBezierAction : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseBezierAction action. If creation failed, return nil.
     * @~chinese EaseBezierAction行动的指针。如果创建失败,返回零。
    */
    static EaseBezierAction* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseBezierAction* clone() const override;
    virtual EaseBezierAction* reverse() const override;

    /**
    @brief @~english Set the bezier parameters.
     * @~chinese 贝塞尔曲线的参数设置。
    */
    virtual void setBezierParamer( float p0, float p1, float p2, float p3);

CC_CONSTRUCTOR_ACCESS:
    EaseBezierAction() {}
    virtual ~EaseBezierAction() {}

protected:
    float _p0;
    float _p1;
    float _p2;
    float _p3;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBezierAction);
};

/** 
@class EaseQuadraticActionIn
@brief @~english Ease Quadratic In
 * @~chinese 减轻二次的
@ingroup Actions
*/
class CC_DLL EaseQuadraticActionIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseQuadraticActionIn action. If creation failed, return nil.
     * @~chinese EaseQuadraticActionIn行动的指针。如果创建失败,返回零。
    */
    static EaseQuadraticActionIn* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseQuadraticActionIn* clone() const override;
    virtual EaseQuadraticActionIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseQuadraticActionIn() {}
    virtual ~EaseQuadraticActionIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseQuadraticActionIn);

};

/** 
@class EaseQuadraticActionOut
@brief @~english Ease Quadratic Out
 * @~chinese 减轻二次了
@ingroup Actions
*/
class CC_DLL EaseQuadraticActionOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseQuadraticActionOut action. If creation failed, return nil.
     * @~chinese EaseQuadraticActionOut行动的指针。如果创建失败,返回零。
    */
    static EaseQuadraticActionOut* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseQuadraticActionOut* clone() const override;
    virtual EaseQuadraticActionOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseQuadraticActionOut() {}
    virtual ~EaseQuadraticActionOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseQuadraticActionOut);

};

/** 
@class EaseQuadraticActionInOut
@brief @~english Ease Quadratic InOut
 * @~chinese 减轻二次InOut
@ingroup Actions
*/
class CC_DLL EaseQuadraticActionInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseQuadraticActionInOut action. If creation failed, return nil.
     * @~chinese EaseQuadraticActionInOut行动的指针。如果创建失败,返回零。
    */
    static EaseQuadraticActionInOut* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseQuadraticActionInOut* clone() const override;
    virtual EaseQuadraticActionInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseQuadraticActionInOut() {}
    virtual ~EaseQuadraticActionInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseQuadraticActionInOut);
};

/** 
@class EaseQuarticActionIn
@brief @~english Ease Quartic In
 * @~chinese 缓解四次在
@ingroup Actions
*/
class CC_DLL EaseQuarticActionIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseQuarticActionIn action. If creation failed, return nil.
     * @~chinese EaseQuarticActionIn行动的指针。如果创建失败,返回零。
    */
    static EaseQuarticActionIn* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseQuarticActionIn* clone() const override;
    virtual EaseQuarticActionIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseQuarticActionIn() {}
    virtual ~EaseQuarticActionIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseQuarticActionIn);
};

/** 
@class EaseQuarticActionOut
@brief @~english Ease Quartic Out
 * @~chinese 缓解四次了
@ingroup Actions
*/
class CC_DLL EaseQuarticActionOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseQuarticActionOut action. If creation failed, return nil.
     * @~chinese EaseQuarticActionOut行动的指针。如果创建失败,返回零。
    */
    static EaseQuarticActionOut* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseQuarticActionOut* clone() const override;
    virtual EaseQuarticActionOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseQuarticActionOut() {}
    virtual ~EaseQuarticActionOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseQuarticActionOut);
};

/** 
@class EaseQuarticActionInOut
@brief @~english Ease Quartic InOut
 * @~chinese 缓解四次InOut
@ingroup Actions
*/
class CC_DLL EaseQuarticActionInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseQuarticActionInOut action. If creation failed, return nil.
     * @~chinese EaseQuarticActionInOut行动的指针。如果创建失败,返回零。
    */
    static EaseQuarticActionInOut* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseQuarticActionInOut* clone() const override;
    virtual EaseQuarticActionInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseQuarticActionInOut() {}
    virtual ~EaseQuarticActionInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseQuarticActionInOut);
};


/** 
@class EaseQuinticActionIn
@brief @~english Ease Quintic In
 * @~chinese 缓解五次在
@ingroup Actions
*/
class CC_DLL EaseQuinticActionIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseQuinticActionIn action. If creation failed, return nil.
     * @~chinese EaseQuinticActionIn行动的指针。如果创建失败,返回零。
    */
    static EaseQuinticActionIn* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseQuinticActionIn* clone() const override;
    virtual EaseQuinticActionIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseQuinticActionIn() {}
    virtual ~EaseQuinticActionIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseQuinticActionIn);
};

/** 
@class EaseQuinticActionOut
@brief @~english Ease Quintic Out
 * @~chinese 缓解五次了
@ingroup Actions
*/
class CC_DLL EaseQuinticActionOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseQuinticActionOut action. If creation failed, return nil.
     * @~chinese EaseQuinticActionOut行动的指针。如果创建失败,返回零。
    */
    static EaseQuinticActionOut* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseQuinticActionOut* clone() const override;
    virtual EaseQuinticActionOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseQuinticActionOut() {}
    virtual ~EaseQuinticActionOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseQuinticActionOut);
};

/** 
@class EaseQuinticActionInOut
@brief @~english Ease Quintic InOut
 * @~chinese 缓解五次InOut
@ingroup Actions
*/
class CC_DLL EaseQuinticActionInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseQuinticActionInOut action. If creation failed, return nil.
     * @~chinese EaseQuinticActionInOut行动的指针。如果创建失败,返回零。
    */
    static EaseQuinticActionInOut* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseQuinticActionInOut* clone() const override;
    virtual EaseQuinticActionInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseQuinticActionInOut() {}
    virtual ~EaseQuinticActionInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseQuinticActionInOut);
};

/** 
@class EaseCircleActionIn
@brief @~english Ease Circle In
 * @~chinese 缓解循环
@ingroup Actions
*/
class CC_DLL EaseCircleActionIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseCircleActionIn action. If creation failed, return nil.
     * @~chinese EaseCircleActionIn行动的指针。如果创建失败,返回零。
    */
    static EaseCircleActionIn* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseCircleActionIn* clone() const override;
    virtual EaseCircleActionIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseCircleActionIn() {}
    virtual ~EaseCircleActionIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseCircleActionIn);
};

/** 
@class EaseCircleActionOut
@brief @~english Ease Circle Out
 * @~chinese 缓解圈出来
@ingroup Actions
*/
class CC_DLL EaseCircleActionOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseCircleActionOut action. If creation failed, return nil.
     * @~chinese EaseCircleActionOut行动的指针。如果创建失败,返回零。
    */
    static EaseCircleActionOut* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseCircleActionOut* clone() const override;
    virtual EaseCircleActionOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseCircleActionOut() {}
    virtual ~EaseCircleActionOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseCircleActionOut);
};

/** 
@class EaseCircleActionInOut
@brief @~english Ease Circle InOut
 * @~chinese 缓解圈InOut
@ingroup Actions
*/
class CC_DLL EaseCircleActionInOut:public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseCircleActionInOut action. If creation failed, return nil.
     * @~chinese EaseCircleActionInOut行动的指针。如果创建失败,返回零。
    */
    static EaseCircleActionInOut* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseCircleActionInOut* clone() const override;
    virtual EaseCircleActionInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseCircleActionInOut() {}
    virtual ~EaseCircleActionInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseCircleActionInOut);
};

/** 
@class EaseCubicActionIn
@brief @~english Ease Cubic In
 * @~chinese 缓解立方的
@ingroup Actions
*/
class CC_DLL EaseCubicActionIn:public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseCubicActionIn action. If creation failed, return nil.
     * @~chinese EaseCubicActionIn行动的指针。如果创建失败,返回零。
    */
    static EaseCubicActionIn* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseCubicActionIn* clone() const override;
    virtual EaseCubicActionIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseCubicActionIn() {}
    virtual ~EaseCubicActionIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseCubicActionIn);
};

/** 
@class EaseCubicActionOut
@brief @~english Ease Cubic Out
 * @~chinese 缓解立方了
@ingroup Actions
*/
class CC_DLL EaseCubicActionOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseCubicActionOut action. If creation failed, return nil.
     * @~chinese EaseCubicActionOut行动的指针。如果创建失败,返回零。
    */
    static EaseCubicActionOut* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseCubicActionOut* clone() const override;
    virtual EaseCubicActionOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseCubicActionOut() {}
    virtual ~EaseCubicActionOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseCubicActionOut);
};

/** 
@class EaseCubicActionInOut
@brief @~english Ease Cubic InOut
 * @~chinese 缓解立方InOut
@ingroup Actions
*/
class CC_DLL EaseCubicActionInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 创建行动与内心的行动。
     @param action @~english The pointer of the inner action.
     * @~chinese 内行动的指针。
     @return @~english A pointer of EaseCubicActionInOut action. If creation failed, return nil.
     * @~chinese EaseCubicActionInOut行动的指针。如果创建失败,返回零。
    */
    static EaseCubicActionInOut* create(ActionInterval* action);
    
    virtual void update(float time) override;
    virtual EaseCubicActionInOut* clone() const override;
    virtual EaseCubicActionInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseCubicActionInOut() {}
    virtual ~EaseCubicActionInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseCubicActionInOut);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCEASE_ACTION_H__

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
     * @~chinese 获得内部动作。
    @return @~english The pointer of the inner action.
     * @~chinese 内部动作。
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
     @brief @~english Initializes the action with the inner action.
     * @~chinese 用内部动作初始化动作。
     * @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english Return true when the initialization success, otherwise return false.
     * @~chinese 返回true时，初始化成功，否则返回false。
    */
    bool initWithAction(ActionInterval *action);

protected:
    /** @~english The inner action  @~chinese 内部动作*/
    ActionInterval *_inner;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ActionEase);
};

/** 
 @class EaseRateAction
 @brief @~english Base class for Easing actions with rate parameters.
 * @~chinese 基于速率曲线的缓动动作基类。
 @details @~english Ease the inner action with specified rate.
 * @~chinese 用一定速率曲线来执行内部动作。
 @ingroup Actions
 */
class CC_DLL EaseRateAction : public ActionEase
{
public:
    /**
     @brief @~english Creates the action with the inner action and the rate parameter.
     * @~chinese 用内部动作和速率参数来创建一个动作。
     @param action @~english A given ActionInterval
     * @~chinese 一个给定的内部动作
     @param rate @~english A given rate
     * @~chinese 一个给定的速率
     @return @~english An autoreleased EaseRateAction object.
     * @~chinese 一个自动释放的缓动动作
    **/
    static EaseRateAction* create(ActionInterval* action, float rate);
    
    /**
     @brief @~english Set the rate value for the ease rate action.
     * @~chinese 设定速率。
     @param rate @~english The rate value.
     * @~chinese 速率。
     */
    inline void setRate(float rate) { _rate = rate; }
    /**
     @brief @~english Get the rate value of the ease rate action.
     * @~chinese 获取速率。
     @return @~english Return the rate value of the ease rate action.
     * @~chinese 速率。
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
     * @~chinese 用内部动作和速率参数来初始化一个动作。
     @param pAction @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @param fRate @~english The value of the rate parameter.
     * @~chinese 速率。
     @return @~english Return true when the initialization success, otherwise return false.
     * @~chinese 返回true时，初始化成功，否则返回false。
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
 * @~chinese 设定速率的EaseIn动作。
 @details @~english The timeline of inner action will be changed by:
 * @~chinese 内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f${ time }^{ rate }\f$
 @ingroup Actions
 */
class CC_DLL EaseIn : public EaseRateAction
{
public:
    /** 
     @brief @~english Create the action with the inner action and the rate parameter.
     * @~chinese 用内部动作和速率参数来创建一个EaseIn动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @param rate @~english The value of the rate parameter.
     * @~chinese 速率。
     @return @~english A pointer of EaseIn action. If creation failed, return nil.
     * @~chinese 如果创建成功，返回一个EaseIn动作。如果创建失败，返回空指针。
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
 * @~chinese 设定速率的EaseOut动作。
 @details @~english The timeline of inner action will be changed by:
 * @~chinese 内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f${ time }^ { (1/rate) }\f$.
 @ingroup Actions
 */
class CC_DLL EaseOut : public EaseRateAction
{
public:
    /** 
     @brief @~english Create the action with the inner action and the rate parameter.
     * @~chinese 用内部动作和速率参数来创建一个动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @param rate @~english The value of the rate parameter.
     * @~chinese 速率。
     @return @~english A pointer of EaseOut action. If creation failed, return nil.
     * @~chinese EaseOut动作的指针。如果创建失败，返回空指针。
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
 * @~chinese 设定速率的EaseInOut动作
 @details @~english If time * 2 < 1, the timeline of inner action will be changed by:
         \f$0.5*{ time }^{ rate }\f$.
         Else, the timeline of inner action will be changed by:
         \f$1.0-0.5*{ 2-time }^{ rate }\f$.
 * @~chinese 如果time * 2 < 1，内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f$0.5*{ time }^{ rate }\f$.
 * 否则，内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f$1.0-0.5*{ 2-time }^{ rate }\f$.
 @ingroup Actions
 */
class CC_DLL EaseInOut : public EaseRateAction
{
public:
    /** 
     @brief @~english Create the action with the inner action and the rate parameter.
     * @~chinese 创建动作的内在动作和速度参数。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @param rate @~english The value of the rate parameter.
     * @~chinese 速率。
     @return @~english A pointer of EaseInOut action. If creation failed, return nil.
     * @~chinese EaseInOut动作的指针。如果创建失败，返回空指针。
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
 @brief @~english EaseExponentialIn action.
 * @~chinese EaseExponentialIn是按指数函数缓动进入的动作。
 @details @~english The timeline of inner action will be changed by:
         \f${ 2 }^{ 10*(time-1) }-1*0.001\f$.
 * @~chinese 内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f${ 2 }^{ 10*(time-1) }-1*0.001\f$.
 @ingroup Actions
 */
class CC_DLL EaseExponentialIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseExponentialIn action. If creation failed, return nil.
     * @~chinese EaseExponentialIn动作的指针。如果创建失败，返回空指针。
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
 @brief @~english EaseExponentialOut action
 * @~chinese EaseExponentialOut是按指数函数缓动退出的动作。
 @details @~english The timeline of inner action will be changed by:
 * @~chinese 内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f$1-{ 2 }^{ -10*(time-1) }\f$
 @ingroup Actions
 */
class CC_DLL EaseExponentialOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseExponentialOut action. If creation failed, return nil.
     * @~chinese EaseExponentialOut动作的指针。如果创建失败，返回空指针。
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
 @brief @~english EaseExponentialInOut action
 * @~chinese EaseExponentialInOut是按指数函数缓动进入并退出的动作
 @details @~english If time * 2 < 1, the timeline of inner action will be changed by:
         \f$0.5*{ 2 }^{ 10*(time-1) }\f$.
         else, the timeline of inner action will be changed by:
         \f$0.5*(2-{ 2 }^{ -10*(time-1) })\f$.
 * @~chinese 如果time * 2 < 1，内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f$0.5*{ 2 }^{ 10*(time-1) }\f$.
 * 否则，内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f$0.5*(2-{ 2 }^{ -10*(time-1) })\f$.
 @ingroup Actions
 */
class CC_DLL EaseExponentialInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseExponentialInOut action. If creation failed, return nil.
     * @~chinese EaseExponentialInOut动作的指针。如果创建失败，返回空指针。
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
 @brief @~english EaseSineIn action
 * @~chinese EaseSineIn是按正弦函数缓动进入的动作
 @details @~english The timeline of inner action will be changed by:
 * @~chinese 内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f$1-cos(time*\frac { \pi  }{ 2 } )\f$.
 @ingroup Actions
 */
class CC_DLL EaseSineIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseSineIn action. If creation failed, return nil.
     * @~chinese EaseSineIn动作的指针。如果创建失败，返回空指针。
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
 @brief @~english EaseSineOut action
 * @~chinese EaseSineIn是按正弦函数缓动退出的动作
 @details @~english The timeline of inner action will be changed by:   
 * @~chinese 内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f$sin(time*\frac { \pi  }{ 2 } )\f$.
 @ingroup Actions
 */
class CC_DLL EaseSineOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseSineOut action. If creation failed, return nil.
     * @~chinese EaseSineOut of A对准动作。如果就业机会、尼罗河破产。
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
 @brief @~english EaseSineInOut action
 * @~chinese EaseSineIn是按正弦函数缓动进入并退出的动作
 @details @~english The timeline of inner action will be changed by:
 * @~chinese 内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f$-0.5*(cos(\pi *time)-1)\f$.
 @ingroup Actions
 */
class CC_DLL EaseSineInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseSineInOut action. If creation failed, return nil.
     * @~chinese EaseSineInOut动作的指针。如果创建失败，返回空指针。
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
 @brief @~english EaseElastic base action
 * @~chinese EaseElastic是按弹性缓动的动作基类
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElastic : public ActionEase
{
public:

    /** 
     @brief @~english Get period of the curve in radians. Default value is 0.3.
     * @~chinese 获取缓动曲线的周期，单位是弧度值，默认值是0.3。
     @return @~english Return the period of the wave in radians.
     * @~chinese 返回缓动曲线的周期。
    */
    inline float getPeriod() const { return _period; }
    /**
     @brief @~english Set period of the wave in radians.
     * @~chinese 设置缓动曲线的周期。
     @param fPeriod @~english Period of the curve in radians.
     * @~chinese 缓动曲线的周期，单位是弧度值。
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
     * @~chinese 使用内部动作和周期的弧度值来初始化动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @param period @~english Period of the curve in radians. Default is 0.3.
     * @~chinese 缓动曲线的周期，默认是0.3。
     @return @~english Return true when the initialization success, otherwise return false.
     * @~chinese 返回true时，初始化成功，否则返回false。
    */
    bool initWithAction(ActionInterval *action, float period = 0.3f);

protected:
    float _period;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElastic);

};

/** 
 @class EaseElasticIn
 @brief @~english EaseElasticIn action.
 * @~chinese EaseElasticIn是按弹性曲线缓动进入的动作。
 @details @~english If time == 0 or time == 1, the timeline of inner action will not be changed.
         Else, the timeline of inner action will be changed by:
 * @~chinese 如果time == 0或者time == 1，内部动作的时间轴将不会被改变。
 * 除此之外，内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f$-{ 2 }^{ 10*(time-1) }*sin((time-1-\frac { period }{ 4 } )*\pi *2/period)\f$.
 * 
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用双射函数。
 * 和序列动作等结合使用这个动作时可能会得到意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticIn : public EaseElastic
{
public:
    /** 
     @brief @~english Create the EaseElasticIn action with the inner action and the period in radians.
     * @~chinese 用内部动作和缓动曲线周期（弧度值）创建EaseElasticIn动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @param period @~english Period of the wave in radians.
     * @~chinese 曲线的弧度。
     @return @~english A pointer of EaseElasticIn action. If creation failed, return nil.
     * @~chinese EaseElasticIn动作的指针。如果创建失败，返回空指针。
    */
    static EaseElasticIn* create(ActionInterval *action, float period);

    /** 
     @brief @~english Create the EaseElasticIn action with the inner action and period value is 0.3.
     * @~chinese 用内部动作创建EaseElasticIn动作，缓动曲线周期（弧度值）是0.3。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseElasticIn action. If creation failed, return nil.
     * @~chinese EaseElasticIn动作的指针。如果创建失败，返回空指针。
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
 @brief @~english EaseElasticOut action.
 * @~chinese EaseElasticOut是按弹性曲线缓动退出的动作。
 @details @~english If time == 0 or time == 1, the timeline of inner action will not be changed.
         Else, the timeline of inner action will be changed by:
 * @~chinese 如果time == 0或者time == 1，内部动作的时间轴将不会被改变。
 * 除此之外，内部动作的时间轴将会按照下面的公式代表的曲线被修改:
 * \f${ 2 }^{ -10*time }*sin((time-\frac { period }{ 4 } )*\pi *2/period)+1\f$.
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用双射函数。
 * 和序列动作等结合使用这个动作时可能会得到意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticOut : public EaseElastic
{
public:
    /** 
     @brief @~english Create the EaseElasticOut action with the inner action and the period in radians.
     * @~chinese 用内部动作和缓动曲线周期（弧度值）创建EaseElasticOut动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @param period @~english Period of the wave in radians.
     * @~chinese 曲线的弧度。
     @return @~english A pointer of EaseElasticOut action. If creation failed, return nil.
     * @~chinese EaseElasticOut动作的指针。如果创建失败，返回空指针。
    */
    static EaseElasticOut* create(ActionInterval *action, float period);

    /** 
     @brief @~english Create the EaseElasticOut action with the inner action and period value is 0.3.
     * @~chinese 用内部动作创建EaseElasticOut动作，缓动曲线周期（弧度值）是0.3。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseElasticOut action. If creation failed, return nil.
     * @~chinese EaseElasticOut动作的指针。如果创建失败，返回空指针。
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
 @brief @~english EaseElasticInOut action.
 * @~chinese EaseElasticInOut是按弹性曲线缓动进入并退出的动作。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用双射函数。
 * 和序列动作等结合使用这个动作时可能会得到意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticInOut : public EaseElastic
{
public:
    /** 
     @brief @~english Create the EaseElasticInOut action with the inner action and the period in radians.
     * @~chinese 用内部动作和缓动曲线周期（弧度值）创建EaseElasticInOut动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @param period @~english Period of the wave in radians.
     * @~chinese 波的弧度。
     @return @~english A pointer of EaseElasticInOut action. If creation failed, return nil.
     * @~chinese EaseElasticInOut动作的指针。如果创建失败，返回空指针。
    */
    static EaseElasticInOut* create(ActionInterval *action, float period);

    /** 
     @brief @~english Create the EaseElasticInOut action with the inner action and period value is 0.3.
     * @~chinese 用内部动作创建EaseElasticInOut动作，缓动曲线周期（弧度值）是0.3。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseElasticInOut action. If creation failed, return nil.
     * @~chinese EaseElasticInOut动作的指针。如果创建失败，返回空指针。
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
 @brief @~english EaseBounce base action.
 * @~chinese EaseBounce是按弹跳动作缓动的动作基类。
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
 * @~chinese EaseBounceIn是按弹跳动作缓动进入的动作。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用双射函数。
 * 和序列动作等结合使用这个动作时可能会得到意想不到的结果。
 @since v0.8.2
 @ingroup Actions
*/
class CC_DLL EaseBounceIn : public EaseBounce
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseBounceIn action. If creation failed, return nil.
     * @~chinese EaseBounceIn动作的指针。如果创建失败，返回空指针。
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
 * @~chinese EaseBounceOut是按弹跳动作缓动退出的动作。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用双射函数。
 * 和序列动作等结合使用这个动作时可能会得到意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBounceOut : public EaseBounce
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseBounceOut action. If creation failed, return nil.
     * @~chinese EaseBounceOut动作的指针。如果创建失败，返回空指针。
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
 * @~chinese EaseBounceInOut是按弹跳动作缓动进入并退出的动作。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用双射函数。
 * 和序列动作等结合使用这个动作时可能会得到意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBounceInOut : public EaseBounce
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseBounceInOut action. If creation failed, return nil.
     * @~chinese EaseBounceInOut动作的指针。如果创建失败，返回空指针。
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
 * @~chinese EaseBackIn缓动动作。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用双射函数。
 * 和序列动作等结合使用这个动作时可能会得到意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseBackIn action. If creation failed, return nil.
     * @~chinese EaseBackIn动作的指针。如果创建失败，返回空指针。
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
 * @~chinese EaseBackOut缓动动作。
 @warning @~english This action doesn't use a bijective function.
          Actions like Sequence might have an unexpected result when used with this action.
 * @~chinese 这个动作不使用双射函数。
 * 和序列动作等结合使用这个动作时可能会得到意想不到的结果。
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseBackOut action. If creation failed, return nil.
     * @~chinese EaseBackOut动作的指针。如果创建失败，返回空指针。
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
 * @~chinese EaseBackInOut缓动动作。
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
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
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
@brief @~english EaseBezierAction
@~chinese EaseBezierAction是按贝塞尔曲线缓动的动作
@ingroup Actions
*/
class CC_DLL EaseBezierAction : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseBezierAction action. If creation failed, return nil.
     * @~chinese EaseBezierAction动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseQuadraticIn
 * @~chinese EaseQuadraticIn是按二次函数缓动进入的动作
@ingroup Actions
*/
class CC_DLL EaseQuadraticActionIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseQuadraticActionIn action. If creation failed, return nil.
     * @~chinese EaseQuadraticActionIn动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseQuadraticOut action
 * @~chinese EaseQuadraticOut是按二次函数缓动退出的动作
@ingroup Actions
*/
class CC_DLL EaseQuadraticActionOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseQuadraticActionOut action. If creation failed, return nil.
     * @~chinese EaseQuadraticActionOut动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseQuadraticInOut action
 * @~chinese EaseQuadraticInOut是按二次函数缓动进入并退出的动作
@ingroup Actions
*/
class CC_DLL EaseQuadraticActionInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseQuadraticActionInOut action. If creation failed, return nil.
     * @~chinese EaseQuadraticActionInOut动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseQuarticIn action
 * @~chinese EaseQuarticIn是按四次函数缓动进入的动作
@ingroup Actions
*/
class CC_DLL EaseQuarticActionIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseQuarticActionIn action. If creation failed, return nil.
     * @~chinese EaseQuarticActionIn动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseQuarticOut action
 * @~chinese EaseQuarticOut是按四次函数缓动退出的动作
@ingroup Actions
*/
class CC_DLL EaseQuarticActionOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseQuarticActionOut action. If creation failed, return nil.
     * @~chinese EaseQuarticActionOut动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseQuarticInOut action
 * @~chinese EaseQuarticInOut是按四次函数缓动进入并退出的动作
@ingroup Actions
*/
class CC_DLL EaseQuarticActionInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseQuarticActionInOut action. If creation failed, return nil.
     * @~chinese EaseQuarticActionInOut动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseQuinticIn action
 * @~chinese EaseQuinticIn是按五次函数缓动进的动作
@ingroup Actions
*/
class CC_DLL EaseQuinticActionIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseQuinticActionIn action. If creation failed, return nil.
     * @~chinese EaseQuinticActionIn动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseQuinticOut action
 * @~chinese EaseQuinticOut是按五次函数缓动退出的动作
@ingroup Actions
*/
class CC_DLL EaseQuinticActionOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseQuinticActionOut action. If creation failed, return nil.
     * @~chinese EaseQuinticActionOut动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseQuinticInOut action
 * @~chinese EaseQuinticInOut是按五次函数缓动进入并退出的动作
@ingroup Actions
*/
class CC_DLL EaseQuinticActionInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseQuinticActionInOut action. If creation failed, return nil.
     * @~chinese EaseQuinticActionInOut动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseCircleIn action
 * @~chinese EaseCircleIn是按圆形曲线缓动进入的动作
@ingroup Actions
*/
class CC_DLL EaseCircleActionIn : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseCircleActionIn action. If creation failed, return nil.
     * @~chinese EaseCircleActionIn动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseCircleOut action
 * @~chinese EaseCircleOut是按圆形曲线缓动退出的动作
@ingroup Actions
*/
class CC_DLL EaseCircleActionOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseCircleActionOut action. If creation failed, return nil.
     * @~chinese EaseCircleActionOut动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseCircleInOut action
 * @~chinese EaseCircleInOut是按圆形曲线缓动进入并退出的动作
@ingroup Actions
*/
class CC_DLL EaseCircleActionInOut:public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseCircleActionInOut action. If creation failed, return nil.
     * @~chinese EaseCircleActionInOut动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseCubicIn action
 * @~chinese EaseCubicIn是按三次函数缓动进入的动作
@ingroup Actions
*/
class CC_DLL EaseCubicActionIn:public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseCubicActionIn action. If creation failed, return nil.
     * @~chinese EaseCubicActionIn动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseCubicOut action
 * @~chinese EaseCubicOut是按三次函数缓动退出的动作
@ingroup Actions
*/
class CC_DLL EaseCubicActionOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseCubicActionOut action. If creation failed, return nil.
     * @~chinese EaseCubicActionOut动作的指针。如果创建失败，返回空指针。
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
@brief @~english EaseCubicInOut action
 * @~chinese EaseCubicInOut是按三次函数缓动进入并退出的动作
@ingroup Actions
*/
class CC_DLL EaseCubicActionInOut : public ActionEase
{
public:
    /** 
     @brief @~english Create the action with the inner action.
     * @~chinese 使用内部动作创建动作。
     @param action @~english The pointer of the inner action.
     * @~chinese 内部动作。
     @return @~english A pointer of EaseCubicActionInOut action. If creation failed, return nil.
     * @~chinese EaseCubicActionInOut动作的指针。如果创建失败，返回空指针。
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

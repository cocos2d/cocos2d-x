/****************************************************************************
Copyright (c) 2008-2009 Jason Booth
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "2d/CCTweenFunction.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/**
 @class ActionEase
 @brief Base class for Easing actions.
 @details Ease actions are created from other interval actions.
 The ease action will change the timeline of the inner action.
 @ingroup Actions
 */
class CC_DLL ActionEase : public ActionInterval
{
public:
    /**
     @brief Get the pointer of the inner action.
     @return The pointer of the inner action.
    */
    virtual ActionInterval* getInnerAction();

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual void stop() override;
    virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
    ActionEase()
    : _inner(nullptr)
    {}
    
    virtual ~ActionEase();
    /**
     @brief Initializes the action.
     @return Return true when the initialization success, otherwise return false.
    */
    bool initWithAction(ActionInterval *action);

protected:
    /** The inner action */
    ActionInterval *_inner;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ActionEase);
};

/**
 @class EaseRateAction
 @brief Base class for Easing actions with rate parameters
 @details Ease the inner action with specified rate.
 @ingroup Actions
 */
class CC_DLL EaseRateAction : public ActionEase
{
public:
    static EaseRateAction* create(ActionInterval* action, float rate);
    /**
    @brief Set the rate value for the ease rate action.
    @param rate The value will be set.
    */
    void setRate(float rate) { _rate = rate; }
    /**
    @brief Get the rate value of the ease rate action.
    @return Return the rate value of the ease rate action.
    */
    float getRate() const { return _rate; }

CC_CONSTRUCTOR_ACCESS:
    EaseRateAction() {}
    virtual ~EaseRateAction() {}
    /**
     @brief Initializes the action with the inner action and the rate parameter.
     @param pAction The pointer of the inner action.
     @param fRate The value of the rate parameter.
     @return Return true when the initialization success, otherwise return false.
    */
    bool initWithAction(ActionInterval *pAction, float fRate);

protected:
    float _rate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseRateAction);
};

//
// NOTE: Converting these macros into Templates is desirable, but please see
// issue #16159 [https://github.com/cocos2d/cocos2d-x/pull/16159] for further info
//
#define EASE_TEMPLATE_DECL_CLASS(CLASSNAME) \
class CC_DLL CLASSNAME : public ActionEase \
{ \
CC_CONSTRUCTOR_ACCESS: \
    virtual ~CLASSNAME() { } \
    CLASSNAME() { } \
public: \
    static CLASSNAME* create(ActionInterval* action); \
    virtual CLASSNAME* clone() const override; \
    virtual void update(float time) override; \
    virtual ActionEase* reverse() const override; \
private: \
    CC_DISALLOW_COPY_AND_ASSIGN(CLASSNAME); \
};

/**
 @class EaseExponentialIn
 @brief Ease Exponential In action.
 @details The timeline of inner action will be changed by:
 \f${ 2 }^{ 10*(time-1) }-1*0.001\f$.
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseExponentialIn);

/**
 @class EaseExponentialOut
 @brief Ease Exponential Out
 @details The timeline of inner action will be changed by:
 \f$1-{ 2 }^{ -10*(time-1) }\f$.
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseExponentialOut);

/**
 @class EaseExponentialInOut
 @brief Ease Exponential InOut
 @details If time * 2 < 1, the timeline of inner action will be changed by:
 \f$0.5*{ 2 }^{ 10*(time-1) }\f$.
 else, the timeline of inner action will be changed by:
 \f$0.5*(2-{ 2 }^{ -10*(time-1) })\f$.
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseExponentialInOut);

/**
 @class EaseSineIn
 @brief Ease Sine In
 @details The timeline of inner action will be changed by:
 \f$1-cos(time*\frac { \pi  }{ 2 } )\f$.
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseSineIn);

/**
 @class EaseSineOut
 @brief Ease Sine Out
 @details The timeline of inner action will be changed by:
 \f$sin(time*\frac { \pi  }{ 2 } )\f$.
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseSineOut);

/**
 @class EaseSineInOut
 @brief Ease Sine InOut
 @details The timeline of inner action will be changed by:
 \f$-0.5*(cos(\pi *time)-1)\f$.
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseSineInOut);

/**
 @class EaseBounce
 @brief EaseBounce abstract class.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBounce : public ActionEase {};

/**
 @class EaseBounceIn
 @brief EaseBounceIn action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseBounceIn);

/**
 @class EaseBounceOut
 @brief EaseBounceOut action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseBounceOut);

/**
 @class EaseBounceInOut
 @brief EaseBounceInOut action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseBounceInOut);

/**
 @class EaseBackIn
 @brief EaseBackIn action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseBackIn);

/**
 @class EaseBackOut
 @brief EaseBackOut action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseBackOut);

/**
 @class EaseBackInOut
 @brief EaseBackInOut action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseBackInOut);

/**
 @class EaseQuadraticActionIn
 @brief Ease Quadratic In
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseQuadraticActionIn);

/**
 @class EaseQuadraticActionOut
 @brief Ease Quadratic Out
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseQuadraticActionOut);

/**
 @class EaseQuadraticActionInOut
 @brief Ease Quadratic InOut
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseQuadraticActionInOut);

/**
 @class EaseQuarticActionIn
 @brief Ease Quartic In
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseQuarticActionIn);

/**
 @class EaseQuarticActionOut
 @brief Ease Quartic Out
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseQuarticActionOut);

/**
 @class EaseQuarticActionInOut
 @brief Ease Quartic InOut
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseQuarticActionInOut);

/**
 @class EaseQuinticActionIn
 @brief Ease Quintic In
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseQuinticActionIn);

/**
 @class EaseQuinticActionOut
 @brief Ease Quintic Out
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseQuinticActionOut);

/**
 @class EaseQuinticActionInOut
 @brief Ease Quintic InOut
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseQuinticActionInOut);

/**
 @class EaseCircleActionIn
 @brief Ease Circle In
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseCircleActionIn);

/**
 @class EaseCircleActionOut
 @brief Ease Circle Out
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseCircleActionOut);

/**
 @class EaseCircleActionInOut
 @brief Ease Circle InOut
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseCircleActionInOut);

/**
 @class EaseCubicActionIn
 @brief Ease Cubic In
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseCubicActionIn);

/**
 @class EaseCubicActionOut
 @brief Ease Cubic Out
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseCubicActionOut);

/**
 @class EaseCubicActionInOut
 @brief Ease Cubic InOut
 @ingroup Actions
 */
EASE_TEMPLATE_DECL_CLASS(EaseCubicActionInOut);

//
// NOTE: Converting these macros into Templates is desirable, but please see
// issue #16159 [https://github.com/cocos2d/cocos2d-x/pull/16159] for further info
//

#define EASERATE_TEMPLATE_DECL_CLASS(CLASSNAME) \
class CC_DLL CLASSNAME : public EaseRateAction \
{ \
CC_CONSTRUCTOR_ACCESS: \
    virtual ~CLASSNAME() { } \
    CLASSNAME() { } \
public: \
    static CLASSNAME* create(ActionInterval* action, float rate); \
    virtual CLASSNAME* clone() const override; \
    virtual void update(float time) override; \
    virtual EaseRateAction* reverse() const override; \
private: \
    CC_DISALLOW_COPY_AND_ASSIGN(CLASSNAME); \
};

/**
 @class EaseIn
 @brief EaseIn action with a rate.
 @details The timeline of inner action will be changed by:
 \f${ time }^{ rate }\f$.
 @ingroup Actions
 */
EASERATE_TEMPLATE_DECL_CLASS(EaseIn);

/**
 @class EaseOut
 @brief EaseOut action with a rate.
 @details The timeline of inner action will be changed by:
 \f${ time }^ { (1/rate) }\f$.
 @ingroup Actions
 */
EASERATE_TEMPLATE_DECL_CLASS(EaseOut);

/**
 @class EaseInOut
 @brief EaseInOut action with a rate
 @details If time * 2 < 1, the timeline of inner action will be changed by:
 \f$0.5*{ time }^{ rate }\f$.
 Else, the timeline of inner action will be changed by:
 \f$1.0-0.5*{ 2-time }^{ rate }\f$.
 @ingroup Actions
 */
EASERATE_TEMPLATE_DECL_CLASS(EaseInOut);

/**
 @class EaseElastic
 @brief Ease Elastic abstract class
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElastic : public ActionEase
{
public:

    /**
     @brief Get period of the wave in radians. Default value is 0.3.
     @return Return the period of the wave in radians.
    */
    float getPeriod() const { return _period; }
    /**
     @brief Set period of the wave in radians.
     @param fPeriod The value will be set.
    */
    void setPeriod(float fPeriod) { _period = fPeriod; }

CC_CONSTRUCTOR_ACCESS:
    EaseElastic() {}
    virtual ~EaseElastic() {}
    /**
     @brief Initializes the action with the inner action and the period in radians.
     @param action The pointer of the inner action.
     @param period Period of the wave in radians. Default is 0.3.
     @return Return true when the initialization success, otherwise return false.
    */
    bool initWithAction(ActionInterval *action, float period = 0.3f);

protected:
    float _period;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElastic);
};

//
// NOTE: Converting these macros into Templates is desirable, but please see
// issue #16159 [https://github.com/cocos2d/cocos2d-x/pull/16159] for further info
//
#define EASEELASTIC_TEMPLATE_DECL_CLASS(CLASSNAME) \
class CC_DLL CLASSNAME : public EaseElastic \
{ \
CC_CONSTRUCTOR_ACCESS: \
    virtual ~CLASSNAME() { } \
    CLASSNAME() { } \
public: \
    static CLASSNAME* create(ActionInterval* action, float rate = 0.3f); \
    virtual CLASSNAME* clone() const override; \
    virtual void update(float time) override; \
    virtual EaseElastic* reverse() const override; \
private: \
    CC_DISALLOW_COPY_AND_ASSIGN(CLASSNAME); \
};

/**
 @class EaseElasticIn
 @brief Ease Elastic In action.
 @details If time == 0 or time == 1, the timeline of inner action will not be changed.
 Else, the timeline of inner action will be changed by:
 \f$-{ 2 }^{ 10*(time-1) }*sin((time-1-\frac { period }{ 4 } )*\pi *2/period)\f$.

 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
EASEELASTIC_TEMPLATE_DECL_CLASS(EaseElasticIn);

/**
 @class EaseElasticOut
 @brief Ease Elastic Out action.
 @details If time == 0 or time == 1, the timeline of inner action will not be changed.
 Else, the timeline of inner action will be changed by:
 \f${ 2 }^{ -10*time }*sin((time-\frac { period }{ 4 } )*\pi *2/period)+1\f$.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
EASEELASTIC_TEMPLATE_DECL_CLASS(EaseElasticOut);

/**
 @class EaseElasticInOut
 @brief Ease Elastic InOut action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
EASEELASTIC_TEMPLATE_DECL_CLASS(EaseElasticInOut);


/**
 @class EaseBezierAction
 @brief Ease Bezier
 @ingroup Actions
 */
class CC_DLL EaseBezierAction : public cocos2d::ActionEase
{
public:
    /**
     @brief Create the action with the inner action.
     @param action The pointer of the inner action.
     @return A pointer of EaseBezierAction action. If creation failed, return nil.
    */
    static EaseBezierAction* create(cocos2d::ActionInterval* action);

    virtual void update(float time) override;
    virtual EaseBezierAction* clone() const override;
    virtual EaseBezierAction* reverse() const override;

    /**
     @brief Set the bezier parameters.
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

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCEASE_ACTION_H__

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
#include "CCTweenFunction.h"

#define EASE_MACRO_COMMA ,

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
    virtual ActionEase* clone() const override = 0;
    virtual ActionEase* reverse() const override = 0;
    virtual void startWithTarget(Node *target) override;
    virtual void stop() override;
    virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
    ActionEase() {}
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
    /**
    @brief Set the rate value for the ease rate action.
    @param rate The value will be set.
    */
    inline void setRate(float rate) { _rate = rate; }
    /**
    @brief Get the rate value of the ease rate action.
    @return Return the rate value of the ease rate action.
    */
    inline float getRate() const { return _rate; }

    //
    // Overrides
    //
    virtual EaseRateAction* clone() const override = 0;
    virtual EaseRateAction* reverse() const override = 0;

CC_CONSTRUCTOR_ACCESS:
    EaseRateAction() {}
    virtual ~EaseRateAction();
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

template<float (*F)(float), float (*I)(float) = F>
class CC_DLL EaseTemplate : public ActionEase
{
CC_CONSTRUCTOR_ACCESS:
    virtual ~EaseTemplate() { }
    EaseTemplate<F>() { }

public:
    static EaseTemplate<F,I>* create(ActionInterval* action);

    void update(float time) override { _inner->update(F(time)); }
    ActionEase* reverse() const override { return EaseTemplate<I,F>::create(_inner->reverse()); }
    ActionEase* clone() const override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseTemplate<F EASE_MACRO_COMMA I>);
};

/**
 @class EaseBounce
 @brief EaseBounce type alias.
 @since v0.8.2
 @ingroup Actions
 */
using EaseBounce = ActionEase;

template class EaseTemplate<tweenfunc::expoEaseIn, tweenfunc::expoEaseOut>;
template class EaseTemplate<tweenfunc::expoEaseOut, tweenfunc::expoEaseIn>;
template class EaseTemplate<tweenfunc::expoEaseInOut>;

template class EaseTemplate<tweenfunc::sineEaseIn, tweenfunc::sineEaseOut>;
template class EaseTemplate<tweenfunc::sineEaseOut, tweenfunc::sineEaseIn>;
template class EaseTemplate<tweenfunc::sineEaseInOut>;

template class EaseTemplate<tweenfunc::bounceEaseIn, tweenfunc::bounceEaseOut>;
template class EaseTemplate<tweenfunc::bounceEaseOut, tweenfunc::bounceEaseIn>;
template class EaseTemplate<tweenfunc::bounceEaseInOut>;

template class EaseTemplate<tweenfunc::backEaseIn, tweenfunc::backEaseOut>;
template class EaseTemplate<tweenfunc::backEaseOut, tweenfunc::backEaseIn>;
template class EaseTemplate<tweenfunc::backEaseInOut>;

template class EaseTemplate<tweenfunc::quadraticIn>;
template class EaseTemplate<tweenfunc::quadraticOut>;
template class EaseTemplate<tweenfunc::quadraticInOut>;

template class EaseTemplate<tweenfunc::quartEaseIn>;
template class EaseTemplate<tweenfunc::quartEaseOut>;
template class EaseTemplate<tweenfunc::quartEaseInOut>;

template class EaseTemplate<tweenfunc::quintEaseIn>;
template class EaseTemplate<tweenfunc::quintEaseOut>;
template class EaseTemplate<tweenfunc::quintEaseInOut>;

template class EaseTemplate<tweenfunc::circEaseIn>;
template class EaseTemplate<tweenfunc::circEaseOut>;
template class EaseTemplate<tweenfunc::circEaseInOut>;

template class EaseTemplate<tweenfunc::cubicEaseIn>;
template class EaseTemplate<tweenfunc::cubicEaseOut>;
template class EaseTemplate<tweenfunc::cubicEaseInOut>;

/**
 @class EaseExponentialIn
 @brief Ease Exponential In action.
 @details The timeline of inner action will be changed by:
 \f${ 2 }^{ 10*(time-1) }-1*0.001\f$.
 @ingroup Actions
 */
using EaseExponentialIn = EaseTemplate<tweenfunc::expoEaseIn, tweenfunc::expoEaseOut>;
/**
 @class EaseExponentialOut
 @brief Ease Exponential Out
 @details The timeline of inner action will be changed by:
 \f$1-{ 2 }^{ -10*(time-1) }\f$.
 @ingroup Actions
 */
using EaseExponentialOut = EaseTemplate<tweenfunc::expoEaseOut, tweenfunc::expoEaseIn>;
/**
 @class EaseExponentialInOut
 @brief Ease Exponential InOut
 @details If time * 2 < 1, the timeline of inner action will be changed by:
 \f$0.5*{ 2 }^{ 10*(time-1) }\f$.
 else, the timeline of inner action will be changed by:
 \f$0.5*(2-{ 2 }^{ -10*(time-1) })\f$.
 @ingroup Actions
 */
using EaseExponentialInOut = EaseTemplate<tweenfunc::expoEaseInOut>;

/**
 @class EaseSineIn
 @brief Ease Sine In
 @details The timeline of inner action will be changed by:
 \f$1-cos(time*\frac { \pi  }{ 2 } )\f$.
 @ingroup Actions
 */
using EaseSineIn = EaseTemplate<tweenfunc::sineEaseIn, tweenfunc::sineEaseOut>;

/**
 @class EaseSineOut
 @brief Ease Sine Out
 @details The timeline of inner action will be changed by:
 \f$sin(time*\frac { \pi  }{ 2 } )\f$.
 @ingroup Actions
 */
using EaseSineOut = EaseTemplate<tweenfunc::sineEaseOut, tweenfunc::sineEaseIn>;
/**
 @class EaseSineInOut
 @brief Ease Sine InOut
 @details The timeline of inner action will be changed by:
 \f$-0.5*(cos(\pi *time)-1)\f$.
 @ingroup Actions
 */
using EaseSineInOut = EaseTemplate<tweenfunc::sineEaseInOut>;

/**
 @class EaseBounceIn
 @brief EaseBounceIn action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
using EaseBounceIn = EaseTemplate<tweenfunc::bounceEaseIn, tweenfunc::bounceEaseOut>;
/**
 @class EaseBounceOut
 @brief EaseBounceOut action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
using EaseBounceOut = EaseTemplate<tweenfunc::bounceEaseOut, tweenfunc::bounceEaseIn>;
/**
 @class EaseBounceInOut
 @brief EaseBounceInOut action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
using EaseBounceInOut = EaseTemplate<tweenfunc::bounceEaseInOut>;

/**
 @class EaseBackIn
 @brief EaseBackIn action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
using EaseBackIn = EaseTemplate<tweenfunc::backEaseIn, tweenfunc::backEaseOut>;
/**
 @class EaseBackOut
 @brief EaseBackOut action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
using EaseBackOut = EaseTemplate<tweenfunc::backEaseOut, tweenfunc::backEaseIn>;
/**
 @class EaseBackInOut
 @brief EaseBackInOut action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
using EaseBackInOut = EaseTemplate<tweenfunc::backEaseInOut>;

/**
 @class EaseQuadraticActionIn
 @brief Ease Quadratic In
 @ingroup Actions
 */
using EaseQuadraticActionIn = EaseTemplate<tweenfunc::quadraticIn>;
/**
 @class EaseQuadraticActionOut
 @brief Ease Quadratic Out
 @ingroup Actions
 */
using EaseQuadraticActionOut = EaseTemplate<tweenfunc::quadraticOut>;
/**
 @class EaseQuadraticActionInOut
 @brief Ease Quadratic InOut
 @ingroup Actions
 */
using EaseQuadraticActionInOut = EaseTemplate<tweenfunc::quadraticInOut>;

/**
 @class EaseQuarticActionIn
 @brief Ease Quartic In
 @ingroup Actions
 */
using EaseQuarticActionIn = EaseTemplate<tweenfunc::quartEaseIn>;
/**
 @class EaseQuarticActionOut
 @brief Ease Quartic Out
 @ingroup Actions
 */
using EaseQuarticActionOut = EaseTemplate<tweenfunc::quartEaseOut>;
/**
 @class EaseQuarticActionInOut
 @brief Ease Quartic InOut
 @ingroup Actions
 */
using EaseQuarticActionInOut = EaseTemplate<tweenfunc::quartEaseInOut>;

/**
 @class EaseQuinticActionIn
 @brief Ease Quintic In
 @ingroup Actions
 */
using EaseQuinticActionIn = EaseTemplate<tweenfunc::quintEaseIn>;
/**
 @class EaseQuinticActionOut
 @brief Ease Quintic Out
 @ingroup Actions
 */
using EaseQuinticActionOut = EaseTemplate<tweenfunc::quintEaseOut>;
/**
 @class EaseQuinticActionInOut
 @brief Ease Quintic InOut
 @ingroup Actions
 */
using EaseQuinticActionInOut = EaseTemplate<tweenfunc::quintEaseInOut>;

/**
 @class EaseCircleActionIn
 @brief Ease Circle In
 @ingroup Actions
 */
using EaseCircleActionIn = EaseTemplate<tweenfunc::circEaseIn>;
/**
 @class EaseCircleActionOut
 @brief Ease Circle Out
 @ingroup Actions
 */
using EaseCircleActionOut = EaseTemplate<tweenfunc::circEaseOut>;
/**
 @class EaseCircleActionInOut
 @brief Ease Circle InOut
 @ingroup Actions
 */
using EaseCircleActionInOut = EaseTemplate<tweenfunc::circEaseInOut>;

/**
 @class EaseCubicActionIn
 @brief Ease Cubic In
 @ingroup Actions
 */
using EaseCubicActionIn = EaseTemplate<tweenfunc::cubicEaseIn>;
/**
 @class EaseCubicActionOut
 @brief Ease Cubic Out
 @ingroup Actions
 */
using EaseCubicActionOut = EaseTemplate<tweenfunc::cubicEaseOut>;
/**
 @class EaseCubicActionInOut
 @brief Ease Cubic InOut
 @ingroup Actions
 */
using EaseCubicActionInOut = EaseTemplate<tweenfunc::cubicEaseInOut>;

template<float (*F)(float,float), float(*I)(float,float) = F>
class CC_DLL EaseRateTemplate : public EaseRateAction
{
CC_CONSTRUCTOR_ACCESS:
    virtual ~EaseRateTemplate() { }
    EaseRateTemplate<F,I>() { }

public:
    /**
     @brief Creates the action with the inner action and the rate parameter.
     @param action A given ActionInterval
     @param rate A given rate
     @return An autoreleased EaseRateAction object.
    **/
    static EaseRateTemplate<F,I>* create(ActionInterval* action, float rate);

    void update(float time) override { _inner->update(F(time, _rate)); }
    EaseRateAction* reverse() const override { return EaseRateTemplate<I,F>::create(_inner->reverse(), 1 / _rate); }
    EaseRateAction* clone() const override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseRateTemplate<F EASE_MACRO_COMMA I>);
};

template class EaseRateTemplate<tweenfunc::easeIn>;
template class EaseRateTemplate<tweenfunc::easeOut>;
template class EaseRateTemplate<tweenfunc::easeInOut>;

/**
 @class EaseIn
 @brief EaseIn action with a rate.
 @details The timeline of inner action will be changed by:
 \f${ time }^{ rate }\f$.
 @ingroup Actions
 */
using EaseIn = EaseRateTemplate<tweenfunc::easeIn>;
/**
 @class EaseOut
 @brief EaseOut action with a rate.
 @details The timeline of inner action will be changed by:
 \f${ time }^ { (1/rate) }\f$.
 @ingroup Actions
 */
using EaseOut = EaseRateTemplate<tweenfunc::easeOut>;
/**
 @class EaseInOut
 @brief EaseInOut action with a rate
 @details If time * 2 < 1, the timeline of inner action will be changed by:
 \f$0.5*{ time }^{ rate }\f$.
 Else, the timeline of inner action will be changed by:
 \f$1.0-0.5*{ 2-time }^{ rate }\f$.
 @ingroup Actions
 */
using EaseInOut = EaseRateTemplate<tweenfunc::easeInOut>;


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
    inline float getPeriod() const { return _period; }
    /**
     @brief Set period of the wave in radians.
     @param fPeriod The value will be set.
    */
    inline void setPeriod(float fPeriod) { _period = fPeriod; }

    //
    // Overrides
    //
	  virtual EaseElastic* clone() const override = 0;
	  virtual EaseElastic* reverse() const override = 0;

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

template<float (*F)(float,float), float(*I)(float,float) = F>
class CC_DLL EaseElasticTemplate : public EaseElastic
{

CC_CONSTRUCTOR_ACCESS:
    virtual ~EaseElasticTemplate() { }
    EaseElasticTemplate<F,I>() { }

public:
    static EaseElasticTemplate<F,I>* create(ActionInterval* action, float rate = 0.3f);

    void update(float time) override { _inner->update(F(time, _period)); }
    EaseElastic* reverse() const override { return EaseElasticTemplate<I,F>::create(_inner->reverse(), _period); }
    EaseElastic* clone() const override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElasticTemplate<F EASE_MACRO_COMMA I>);
};

template class EaseElasticTemplate<tweenfunc::elasticEaseIn>;
template class EaseElasticTemplate<tweenfunc::elasticEaseOut>;
template class EaseElasticTemplate<tweenfunc::elasticEaseInOut>;

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
using EaseElasticIn = EaseElasticTemplate<tweenfunc::elasticEaseIn>;
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
using EaseElasticOut = EaseElasticTemplate<tweenfunc::elasticEaseOut>;
/**
 @class EaseElasticInOut
 @brief Ease Elastic InOut action.
 @warning This action doesn't use a bijective function.
 Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
using EaseElasticInOut = EaseElasticTemplate<tweenfunc::elasticEaseInOut>;


/**
 @class EaseBezierAction
 @brief Ease Bezier
 @ingroup Actions
 */
class EaseBezierAction : public cocos2d::ActionEase
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

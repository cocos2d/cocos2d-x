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
 @brief Base class for Easing actions
 @ingroup Actions
 */
class CC_DLL ActionEase : public ActionInterval
{
public:

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
    /** initializes the action */
    bool initWithAction(ActionInterval *action);

protected:
    /** The inner action */
    ActionInterval *_inner;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ActionEase);
};

/** 
 @brief Base class for Easing actions with rate parameters
 @ingroup Actions
 */
class CC_DLL EaseRateAction : public ActionEase
{
public:
    /** set rate value for the actions */
    inline void setRate(float rate) { _rate = rate; }
    /** get rate value for the actions */
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
    /** Initializes the action with the inner action and the rate parameter */
    bool initWithAction(ActionInterval *pAction, float fRate);

protected:
    float _rate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseRateAction);
};

/** 
 @brief EaseIn action with a rate
 @ingroup Actions
 */
class CC_DLL EaseIn : public EaseRateAction
{
public:
    /** Creates the action with the inner action and the rate parameter */
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
 @brief EaseOut action with a rate
 @ingroup Actions
 */
class CC_DLL EaseOut : public EaseRateAction
{
public:
    /** Creates the action with the inner action and the rate parameter */
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
 @brief EaseInOut action with a rate
 @ingroup Actions
 */
class CC_DLL EaseInOut : public EaseRateAction
{
public:
    /** Creates the action with the inner action and the rate parameter */
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
 @brief Ease Exponential In
 @ingroup Actions
 */
class CC_DLL EaseExponentialIn : public ActionEase
{
public:
    /** creates the action */
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
 @brief Ease Exponential Out
 @ingroup Actions
 */
class CC_DLL EaseExponentialOut : public ActionEase
{
public:
    /** creates the action */
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
 @brief Ease Exponential InOut
 @ingroup Actions
 */
class CC_DLL EaseExponentialInOut : public ActionEase
{
public:
    /** creates the action */
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
 @brief Ease Sine In
 @ingroup Actions
 */
class CC_DLL EaseSineIn : public ActionEase
{
public:
    /** creates the action */
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
 @brief Ease Sine Out
 @ingroup Actions
 */
class CC_DLL EaseSineOut : public ActionEase
{
public:
    /** creates the action */
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
 @brief Ease Sine InOut
 @ingroup Actions
 */
class CC_DLL EaseSineInOut : public ActionEase
{
public:
    /** creates the action */
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
 @brief Ease Elastic abstract class
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElastic : public ActionEase
{
public:

    /** get period of the wave in radians. default is 0.3 */
    inline float getPeriod() const { return _period; }
    /** set period of the wave in radians. */
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
    /** Initializes the action with the inner action and the period in radians (default is 0.3) */
    bool initWithAction(ActionInterval *action, float period = 0.3f);

protected:
    float _period;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElastic);

};

/** 
 @brief Ease Elastic In action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticIn : public EaseElastic
{
public:
    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    static EaseElasticIn* create(ActionInterval *action, float period);
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
 @brief Ease Elastic Out action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticOut : public EaseElastic
{
public:
    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    static EaseElasticOut* create(ActionInterval *action, float period);
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
 @brief Ease Elastic InOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticInOut : public EaseElastic
{
public:
    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    static EaseElasticInOut* create(ActionInterval *action, float period);
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
 @brief EaseBounce abstract class.
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
 @brief EaseBounceIn action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
*/
class CC_DLL EaseBounceIn : public EaseBounce
{
public:
    /** creates the action */
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
 @brief EaseBounceOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBounceOut : public EaseBounce
{
public:
    /** creates the action */
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
 @brief EaseBounceInOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBounceInOut : public EaseBounce
{
public:
    /** creates the action */
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
 @brief EaseBackIn action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackIn : public ActionEase
{
public:
    /** creates the action */
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
 @brief EaseBackOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackOut : public ActionEase
{
public:
    /** creates the action */
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
 @brief EaseBackInOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackInOut : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Bezier
@ingroup Actions
*/
class CC_DLL EaseBezierAction : public ActionEase
{
public:
    /** creates the action */
    static EaseBezierAction* create(ActionInterval* action);

    virtual void update(float time) override;
    virtual EaseBezierAction* clone() const override;
    virtual EaseBezierAction* reverse() const override;

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
@brief Ease Quadratic In
@ingroup Actions
*/
class CC_DLL EaseQuadraticActionIn : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Quadratic Out
@ingroup Actions
*/
class CC_DLL EaseQuadraticActionOut : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Quadratic InOut
@ingroup Actions
*/
class CC_DLL EaseQuadraticActionInOut : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Quartic In
@ingroup Actions
*/
class CC_DLL EaseQuarticActionIn : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Quartic Out
@ingroup Actions
*/
class CC_DLL EaseQuarticActionOut : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Quartic InOut
@ingroup Actions
*/
class CC_DLL EaseQuarticActionInOut : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Quintic In
@ingroup Actions
*/
class CC_DLL EaseQuinticActionIn : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Quintic Out
@ingroup Actions
*/
class CC_DLL EaseQuinticActionOut : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Quintic InOut
@ingroup Actions
*/
class CC_DLL EaseQuinticActionInOut : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Circle In
@ingroup Actions
*/
class CC_DLL EaseCircleActionIn : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Circle Out
@ingroup Actions
*/
class CC_DLL EaseCircleActionOut : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Circle InOut
@ingroup Actions
*/
class CC_DLL EaseCircleActionInOut:public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Cubic In
@ingroup Actions
*/
class CC_DLL EaseCubicActionIn:public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Cubic Out
@ingroup Actions
*/
class CC_DLL EaseCubicActionOut : public ActionEase
{
public:
    /** creates the action */
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
@brief Ease Cubic InOut
@ingroup Actions
*/
class CC_DLL EaseCubicActionInOut : public ActionEase
{
public:
    /** creates the action */
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

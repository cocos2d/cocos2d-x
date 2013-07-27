/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2009 Jason Booth

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

#include "CCActionInterval.h"

NS_CC_BEGIN

class Object;

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
    virtual ~ActionEase(void);

    /** initializes the action */
    bool initWithAction(ActionInterval *pAction);

    virtual ActionInterval* getInnerAction();

    //
    // Overrides
    //
	virtual ActionEase* clone() const override = 0;
    virtual ActionEase* reverse() const override = 0;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;

protected:
    /** The inner action */
    ActionInterval *_inner;
};

/** 
 @brief Base class for Easing actions with rate parameters
 @ingroup Actions
 */
class CC_DLL EaseRateAction : public ActionEase
{
public:
    virtual ~EaseRateAction(void);

    /** Initializes the action with the inner action and the rate parameter */
    bool initWithAction(ActionInterval *pAction, float fRate);

    /** set rate value for the actions */
    inline void setRate(float rate) { _rate = rate; }
    /** get rate value for the actions */
    inline float getRate(void) const { return _rate; }

    //
    // Overrides
    //
	virtual EaseRateAction* clone() const override = 0;
    virtual EaseRateAction* reverse() const override = 0;

protected:
    float _rate;
};

/** 
 @brief EaseIn action with a rate
 @ingroup Actions
 */
class CC_DLL EaseIn : public EaseRateAction
{
public:
    /** Creates the action with the inner action and the rate parameter */
    static EaseIn* create(ActionInterval* pAction, float fRate);

    // Overrides
    virtual void update(float time) override;
	virtual EaseIn* clone() const override;
	virtual EaseIn* reverse() const override;
};

/** 
 @brief EaseOut action with a rate
 @ingroup Actions
 */
class CC_DLL EaseOut : public EaseRateAction
{
public:
    /** Creates the action with the inner action and the rate parameter */
    static EaseOut* create(ActionInterval* pAction, float fRate);

    // Overrides
    virtual void update(float time) override;
	virtual EaseOut* clone() const  override;
	virtual EaseOut* reverse() const  override;
};

/** 
 @brief EaseInOut action with a rate
 @ingroup Actions
 */
class CC_DLL EaseInOut : public EaseRateAction
{
public:
    /** Creates the action with the inner action and the rate parameter */
    static EaseInOut* create(ActionInterval* pAction, float fRate);

    // Overrides
    virtual void update(float time) override;
	virtual EaseInOut* clone() const  override;
	virtual EaseInOut* reverse() const  override;
};

/** 
 @brief Ease Exponential In
 @ingroup Actions
 */
class CC_DLL EaseExponentialIn : public ActionEase
{
public:
    /** creates the action */
    static EaseExponentialIn* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseExponentialIn* clone() const override;
	virtual ActionEase* reverse() const override;
};

/** 
 @brief Ease Exponential Out
 @ingroup Actions
 */
class CC_DLL EaseExponentialOut : public ActionEase
{
public:
    /** creates the action */
    static EaseExponentialOut* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseExponentialOut* clone() const override;
	virtual ActionEase* reverse() const override;
};

/** 
 @brief Ease Exponential InOut
 @ingroup Actions
 */
class CC_DLL EaseExponentialInOut : public ActionEase
{
public:
    /** creates the action */
    static EaseExponentialInOut* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseExponentialInOut* clone() const override;
	virtual EaseExponentialInOut* reverse() const override;
};

/** 
 @brief Ease Sine In
 @ingroup Actions
 */
class CC_DLL EaseSineIn : public ActionEase
{
public:
    /** creates the action */
    static EaseSineIn* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseSineIn* clone() const override;
	virtual ActionEase* reverse() const override;
};

/** 
 @brief Ease Sine Out
 @ingroup Actions
 */
class CC_DLL EaseSineOut : public ActionEase
{
public:
    /** creates the action */
    static EaseSineOut* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseSineOut* clone() const override;
	virtual ActionEase* reverse() const override;
};

/** 
 @brief Ease Sine InOut
 @ingroup Actions
 */
class CC_DLL EaseSineInOut : public ActionEase
{
public:
    /** creates the action */
    static EaseSineInOut* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseSineInOut* clone() const override;
	virtual EaseSineInOut* reverse() const override;
};

/** 
 @brief Ease Elastic abstract class
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElastic : public ActionEase
{
public:
    /** Initializes the action with the inner action and the period in radians (default is 0.3) */
    bool initWithAction(ActionInterval *pAction, float fPeriod = 0.3f);

    /** get period of the wave in radians. default is 0.3 */
    inline float getPeriod(void) const { return _period; }
    /** set period of the wave in radians. */
    inline void setPeriod(float fPeriod) { _period = fPeriod; }

    //
    // Overrides
    //
	virtual EaseElastic* clone() const override = 0;
	virtual EaseElastic* reverse() const override = 0;

protected:
    float _period;
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
    static EaseElasticIn* create(ActionInterval *pAction, float fPeriod);
    static EaseElasticIn* create(ActionInterval *pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseElasticIn* clone() const override;
	virtual EaseElastic* reverse() const override;
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
    static EaseElasticOut* create(ActionInterval *pAction, float fPeriod);
    static EaseElasticOut* create(ActionInterval *pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseElasticOut* clone() const override;
	virtual EaseElastic* reverse() const override;
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
    static EaseElasticInOut* create(ActionInterval *pAction, float fPeriod);
    static EaseElasticInOut* create(ActionInterval *pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseElasticInOut* clone() const override;
	virtual EaseElasticInOut* reverse() const override;
};

/** 
 @brief EaseBounce abstract class.
 @since v0.8.2
 @ingroup Actions
*/
class CC_DLL EaseBounce : public ActionEase
{
public:
    float bounceTime(float time);

    // Overrides
	virtual EaseBounce* clone() const override = 0;
	virtual EaseBounce* reverse() const override = 0;
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
    static EaseBounceIn* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseBounceIn* clone() const override;
	virtual EaseBounce* reverse() const override;
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
    static EaseBounceOut* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseBounceOut* clone() const override;
	virtual EaseBounce* reverse() const override;
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
    static EaseBounceInOut* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseBounceInOut* clone() const override;
	virtual EaseBounceInOut* reverse() const override;
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
    static EaseBackIn* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseBackIn* clone() const override;
	virtual ActionEase* reverse() const override;
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
    static EaseBackOut* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseBackOut* clone() const override;
	virtual ActionEase* reverse() const override;
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
    static EaseBackInOut* create(ActionInterval* pAction);

    // Overrides
    virtual void update(float time) override;
	virtual EaseBackInOut* clone() const override;
	virtual EaseBackInOut* reverse() const override;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCEASE_ACTION_H__

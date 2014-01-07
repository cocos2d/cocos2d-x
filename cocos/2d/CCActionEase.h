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

    virtual ActionInterval* getInnerAction();

    //
    // Overrides
    //
	virtual ActionEase* clone() const override = 0;
    virtual ActionEase* reverse() const override = 0;
    virtual void startWithTarget(Node *target) override;
    virtual void stop() override;
    virtual void update(float time) override;

protected:
    ActionEase() {}
    virtual ~ActionEase();
    /** initializes the action */
    bool initWithAction(ActionInterval *action);

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
	virtual EaseRateAction* clone() const override = 0;
    virtual EaseRateAction* reverse() const override = 0;

protected:
    EaseRateAction() {}
    virtual ~EaseRateAction();
    /** Initializes the action with the inner action and the rate parameter */
    bool initWithAction(ActionInterval *pAction, float fRate);

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

protected:
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

protected:
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

protected:
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

protected:
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

protected:
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

protected:
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

protected:
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

protected:
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

protected:
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
	virtual EaseElastic* clone() const override = 0;
	virtual EaseElastic* reverse() const override = 0;

protected:
    EaseElastic() {}
    virtual ~EaseElastic() {}
    /** Initializes the action with the inner action and the period in radians (default is 0.3) */
    bool initWithAction(ActionInterval *action, float period = 0.3f);

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

protected:
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

protected:
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

protected:
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
    float bounceTime(float time);

    // Overrides
	virtual EaseBounce* clone() const override = 0;
	virtual EaseBounce* reverse() const override = 0;

protected:
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

protected:
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

protected:
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

protected:
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

protected:
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

protected:
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

protected:
    EaseBackInOut() {}
    virtual ~EaseBackInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBackInOut);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCEASE_ACTION_H__

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
class Zone;

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

	virtual ActionEase* clone() const = 0;
    virtual ActionEase* reverse() const = 0;

    virtual void startWithTarget(Node *pTarget);
    virtual void stop(void);
    virtual void update(float time);
    virtual ActionInterval* getInnerAction();

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

    /** set rate value for the actions */
    inline void setRate(float rate) { _rate = rate; }
    /** get rate value for the actions */
    inline float getRate(void) { return _rate; }

    /** Initializes the action with the inner action and the rate parameter */
    bool initWithAction(ActionInterval *pAction, float fRate);

	virtual EaseRateAction* clone() const = 0;
    virtual EaseRateAction* reverse() const = 0;

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
    virtual void update(float time);

	/** returns a new clone of the action */
	virtual EaseIn* clone() const;
	/** returns a new reversed action */
	virtual EaseIn* reverse() const;

    virtual Object* copyWithZone(Zone* pZone);
public:

    /** Creates the action with the inner action and the rate parameter */
    static EaseIn* create(ActionInterval* pAction, float fRate);
};

/** 
 @brief EaseOut action with a rate
 @ingroup Actions
 */
class CC_DLL EaseOut : public EaseRateAction
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseOut* clone() const;
	/** returns a new reversed action */
	virtual EaseOut* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** Creates the action with the inner action and the rate parameter */
    static EaseOut* create(ActionInterval* pAction, float fRate);
};

/** 
 @brief EaseInOut action with a rate
 @ingroup Actions
 */
class CC_DLL EaseInOut : public EaseRateAction
{
public:
    virtual void update(float time);
    virtual Object* copyWithZone(Zone* pZone);
	/** returns a new clone of the action */
	virtual EaseInOut* clone() const;
	/** returns a new reversed action */
	virtual EaseInOut* reverse() const;

public:

    /** Creates the action with the inner action and the rate parameter */
    static EaseInOut* create(ActionInterval* pAction, float fRate);
};

/** 
 @brief Ease Exponential In
 @ingroup Actions
 */
class CC_DLL EaseExponentialIn : public ActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseExponentialIn* clone() const;
	/** returns a new reversed action */
	virtual ActionEase* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:
    /** creates the action */
    static EaseExponentialIn* create(ActionInterval* pAction);
};

/** 
 @brief Ease Exponential Out
 @ingroup Actions
 */
class CC_DLL EaseExponentialOut : public ActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseExponentialOut* clone() const;
	/** returns a new reversed action */
	virtual ActionEase* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:
    /** creates the action */
    static EaseExponentialOut* create(ActionInterval* pAction);
};

/** 
 @brief Ease Exponential InOut
 @ingroup Actions
 */
class CC_DLL EaseExponentialInOut : public ActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseExponentialInOut* clone() const;
	/** returns a new reversed action */
	virtual EaseExponentialInOut* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action */
    static EaseExponentialInOut* create(ActionInterval* pAction);
};

/** 
 @brief Ease Sine In
 @ingroup Actions
 */
class CC_DLL EaseSineIn : public ActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseSineIn* clone() const;
	/** returns a new reversed action */
	virtual ActionEase* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:
    /** creates the action */
    static EaseSineIn* create(ActionInterval* pAction);
};

/** 
 @brief Ease Sine Out
 @ingroup Actions
 */
class CC_DLL EaseSineOut : public ActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseSineOut* clone() const;
	/** returns a new reversed action */
	virtual ActionEase* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action */
    static EaseSineOut* create(ActionInterval* pAction);
};

/** 
 @brief Ease Sine InOut
 @ingroup Actions
 */
class CC_DLL EaseSineInOut : public ActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseSineInOut* clone() const;
	/** returns a new reversed action */
	virtual EaseSineInOut* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action */
    static EaseSineInOut* create(ActionInterval* pAction);
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
    inline float getPeriod(void) { return _period; }
    /** set period of the wave in radians. */
    inline void setPeriod(float fPeriod) { _period = fPeriod; }

    /** Initializes the action with the inner action and the period in radians (default is 0.3) */
    bool initWithAction(ActionInterval *pAction, float fPeriod = 0.3f);

	/** returns a new clone of the action */
	virtual EaseElastic* clone() const = 0;
	/** returns a new reversed action */
	virtual EaseElastic* reverse() const = 0;

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
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseElasticIn* clone() const;
	/** returns a new reversed action */
	virtual EaseElastic* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    static EaseElasticIn* create(ActionInterval *pAction, float fPeriod);
    static EaseElasticIn* create(ActionInterval *pAction);
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
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseElasticOut* clone() const;
	/** returns a new reversed action */
	virtual EaseElastic* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    static EaseElasticOut* create(ActionInterval *pAction, float fPeriod);
    static EaseElasticOut* create(ActionInterval *pAction);
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
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseElasticInOut* clone() const;
	/** returns a new reversed action */
	virtual EaseElasticInOut* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    static EaseElasticInOut* create(ActionInterval *pAction, float fPeriod);
    static EaseElasticInOut* create(ActionInterval *pAction);
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
	/** returns a new clone of the action */
	virtual EaseBounce* clone() const = 0;
	/** returns a new reversed action */
	virtual EaseBounce* reverse() const = 0;

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
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseBounceIn* clone() const;
	/** returns a new reversed action */
	virtual EaseBounce* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action */
    static EaseBounceIn* create(ActionInterval* pAction);
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
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseBounceOut* clone() const;
	/** returns a new reversed action */
	virtual EaseBounce* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action */
    static EaseBounceOut* create(ActionInterval* pAction);
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
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseBounceInOut* clone() const;
	/** returns a new reversed action */
	virtual EaseBounceInOut* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action */
    static EaseBounceInOut* create(ActionInterval* pAction);
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
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseBackIn* clone() const;
	/** returns a new reversed action */
	virtual ActionEase* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action */
    static EaseBackIn* create(ActionInterval* pAction);
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
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseBackOut* clone() const;
	/** returns a new reversed action */
	virtual ActionEase* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action */
    static EaseBackOut* create(ActionInterval* pAction);
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
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual EaseBackInOut* clone() const;
	/** returns a new reversed action */
	virtual EaseBackInOut* reverse() const;
    virtual Object* copyWithZone(Zone* pZone);

public:

    /** creates the action */
    static EaseBackInOut* create(ActionInterval* pAction);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCEASE_ACTION_H__

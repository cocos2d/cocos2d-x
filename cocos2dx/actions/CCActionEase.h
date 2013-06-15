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

class CCObject;
class CCZone;

/**
 * @addtogroup actions
 * @{
 */

/** 
 @brief Base class for Easing actions
 @ingroup Actions
 */
class CC_DLL CCActionEase : public CCActionInterval
{
public:
    virtual ~CCActionEase(void);

    /** initializes the action */
    bool initWithAction(CCActionInterval *pAction);

	virtual CCActionEase* clone() const = 0;
    virtual CCActionEase* reverse() const = 0;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void update(float time);
    virtual CCActionInterval* getInnerAction();

protected:
    /** The inner action */
    CCActionInterval *m_pInner;
};

/** 
 @brief Base class for Easing actions with rate parameters
 @ingroup Actions
 */
class CC_DLL CCEaseRateAction : public CCActionEase
{
public:
    virtual ~CCEaseRateAction(void);

    /** set rate value for the actions */
    inline void setRate(float rate) { m_fRate = rate; }
    /** get rate value for the actions */
    inline float getRate(void) { return m_fRate; }

    /** Initializes the action with the inner action and the rate parameter */
    bool initWithAction(CCActionInterval *pAction, float fRate);

	virtual CCEaseRateAction* clone() const = 0;
    virtual CCEaseRateAction* reverse() const = 0;

protected:
    float m_fRate;
};

/** 
 @brief CCEaseIn action with a rate
 @ingroup Actions
 */
class CC_DLL CCEaseIn : public CCEaseRateAction
{
public:
    virtual void update(float time);

	/** returns a new clone of the action */
	virtual CCEaseIn* clone() const;
	/** returns a new reversed action */
	virtual CCEaseIn* reverse() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
public:

    /** Creates the action with the inner action and the rate parameter */
    static CCEaseIn* create(CCActionInterval* pAction, float fRate);
};

/** 
 @brief CCEaseOut action with a rate
 @ingroup Actions
 */
class CC_DLL CCEaseOut : public CCEaseRateAction
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseOut* clone() const;
	/** returns a new reversed action */
	virtual CCEaseOut* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** Creates the action with the inner action and the rate parameter */
    static CCEaseOut* create(CCActionInterval* pAction, float fRate);
};

/** 
 @brief CCEaseInOut action with a rate
 @ingroup Actions
 */
class CC_DLL CCEaseInOut : public CCEaseRateAction
{
public:
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone* pZone);
	/** returns a new clone of the action */
	virtual CCEaseInOut* clone() const;
	/** returns a new reversed action */
	virtual CCEaseInOut* reverse() const;

public:

    /** Creates the action with the inner action and the rate parameter */
    static CCEaseInOut* create(CCActionInterval* pAction, float fRate);
};

/** 
 @brief CCEase Exponential In
 @ingroup Actions
 */
class CC_DLL CCEaseExponentialIn : public CCActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseExponentialIn* clone() const;
	/** returns a new reversed action */
	virtual CCActionEase* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action */
    static CCEaseExponentialIn* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Exponential Out
 @ingroup Actions
 */
class CC_DLL CCEaseExponentialOut : public CCActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseExponentialOut* clone() const;
	/** returns a new reversed action */
	virtual CCActionEase* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action */
    static CCEaseExponentialOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Exponential InOut
 @ingroup Actions
 */
class CC_DLL CCEaseExponentialInOut : public CCActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseExponentialInOut* clone() const;
	/** returns a new reversed action */
	virtual CCEaseExponentialInOut* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static CCEaseExponentialInOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Sine In
 @ingroup Actions
 */
class CC_DLL CCEaseSineIn : public CCActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseSineIn* clone() const;
	/** returns a new reversed action */
	virtual CCActionEase* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action */
    static CCEaseSineIn* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Sine Out
 @ingroup Actions
 */
class CC_DLL CCEaseSineOut : public CCActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseSineOut* clone() const;
	/** returns a new reversed action */
	virtual CCActionEase* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static CCEaseSineOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Sine InOut
 @ingroup Actions
 */
class CC_DLL CCEaseSineInOut : public CCActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseSineInOut* clone() const;
	/** returns a new reversed action */
	virtual CCEaseSineInOut* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static CCEaseSineInOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Elastic abstract class
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL CCEaseElastic : public CCActionEase
{
public:
    /** get period of the wave in radians. default is 0.3 */
    inline float getPeriod(void) { return m_fPeriod; }
    /** set period of the wave in radians. */
    inline void setPeriod(float fPeriod) { m_fPeriod = fPeriod; }

    /** Initializes the action with the inner action and the period in radians (default is 0.3) */
    bool initWithAction(CCActionInterval *pAction, float fPeriod = 0.3f);

	/** returns a new clone of the action */
	virtual CCEaseElastic* clone() const = 0;
	/** returns a new reversed action */
	virtual CCEaseElastic* reverse() const = 0;

protected:
    float m_fPeriod;
};

/** 
 @brief Ease Elastic In action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL CCEaseElasticIn : public CCEaseElastic
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseElasticIn* clone() const;
	/** returns a new reversed action */
	virtual CCEaseElastic* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    static CCEaseElasticIn* create(CCActionInterval *pAction, float fPeriod);
    static CCEaseElasticIn* create(CCActionInterval *pAction);
};

/** 
 @brief Ease Elastic Out action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL CCEaseElasticOut : public CCEaseElastic
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseElasticOut* clone() const;
	/** returns a new reversed action */
	virtual CCEaseElastic* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    static CCEaseElasticOut* create(CCActionInterval *pAction, float fPeriod);
    static CCEaseElasticOut* create(CCActionInterval *pAction);
};

/** 
 @brief Ease Elastic InOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL CCEaseElasticInOut : public CCEaseElastic
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseElasticInOut* clone() const;
	/** returns a new reversed action */
	virtual CCEaseElasticInOut* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** Creates the action with the inner action and the period in radians (default is 0.3) */
    static CCEaseElasticInOut* create(CCActionInterval *pAction, float fPeriod);
    static CCEaseElasticInOut* create(CCActionInterval *pAction);
};

/** 
 @brief CCEaseBounce abstract class.
 @since v0.8.2
 @ingroup Actions
*/
class CC_DLL CCEaseBounce : public CCActionEase
{
public:
    float bounceTime(float time);
	/** returns a new clone of the action */
	virtual CCEaseBounce* clone() const = 0;
	/** returns a new reversed action */
	virtual CCEaseBounce* reverse() const = 0;

};

/** 
 @brief CCEaseBounceIn action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
*/
class CC_DLL CCEaseBounceIn : public CCEaseBounce
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseBounceIn* clone() const;
	/** returns a new reversed action */
	virtual CCEaseBounce* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static CCEaseBounceIn* create(CCActionInterval* pAction);
};

/** 
 @brief EaseBounceOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL CCEaseBounceOut : public CCEaseBounce
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseBounceOut* clone() const;
	/** returns a new reversed action */
	virtual CCEaseBounce* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static CCEaseBounceOut* create(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBounceInOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL CCEaseBounceInOut : public CCEaseBounce
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseBounceInOut* clone() const;
	/** returns a new reversed action */
	virtual CCEaseBounceInOut* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static CCEaseBounceInOut* create(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBackIn action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL CCEaseBackIn : public CCActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseBackIn* clone() const;
	/** returns a new reversed action */
	virtual CCActionEase* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static CCEaseBackIn* create(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBackOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL CCEaseBackOut : public CCActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseBackOut* clone() const;
	/** returns a new reversed action */
	virtual CCActionEase* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static CCEaseBackOut* create(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBackInOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL CCEaseBackInOut : public CCActionEase
{
public:
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCEaseBackInOut* clone() const;
	/** returns a new reversed action */
	virtual CCEaseBackInOut* reverse() const;
    virtual CCObject* copyWithZone(CCZone* pZone);

public:

    /** creates the action */
    static CCEaseBackInOut* create(CCActionInterval* pAction);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCEASE_ACTION_H__

/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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

namespace cocos2d {

class CCObject;
class CCZone;

/** 
 @brief Base class for Easing actions
 */
class CC_DLL CCActionEase : public CCActionInterval
{
public:
	virtual ~CCActionEase(void);

	/** initializes the action */
    bool initWithAction(CCActionInterval *pAction);

	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void stop(void);
	virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);

public:
	/** creates the action */
	static CCActionEase* actionWithAction(CCActionInterval *pAction);

protected:
	CCActionInterval *m_pOther;
};

/** 
 @brief Base class for Easing actions with rate parameters
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

	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual CCActionInterval* reverse(void);

public:
	/** Creates the action with the inner action and the rate parameter */
	static CCEaseRateAction* actionWithAction(CCActionInterval* pAction, float fRate);

protected:
	float m_fRate;
};

/** 
 @brief CCEaseIn action with a rate
 */
class CC_DLL CCEaseIn : public CCEaseRateAction
{
public:
	virtual void update(ccTime time);
	virtual CCObject* copyWithZone(CCZone* pZone);
public:
	/** Creates the action with the inner action and the rate parameter */
	static CCEaseIn* actionWithAction(CCActionInterval* pAction, float fRate);
};

/** 
 @brief CCEaseOut action with a rate
 */
class CC_DLL CCEaseOut : public CCEaseRateAction
{
public:
	virtual void update(ccTime time);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** Creates the action with the inner action and the rate parameter */
    static CCEaseOut* actionWithAction(CCActionInterval* pAction, float fRate);
};

/** 
 @brief CCEaseInOut action with a rate
 */
class CC_DLL CCEaseInOut : public CCEaseRateAction
{
public:
	virtual void update(ccTime time);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual CCActionInterval* reverse(void);

public:
	/** Creates the action with the inner action and the rate parameter */
	static CCEaseInOut* actionWithAction(CCActionInterval* pAction, float fRate);
};

/** 
 @brief CCEase Exponential In
 */
class CC_DLL CCEaseExponentialIn : public CCActionEase
{
public:
	virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseExponentialIn* actionWithAction(CCActionInterval* pAction);
};

/** 
 @brief Ease Exponential Out
 */
class CC_DLL CCEaseExponentialOut : public CCActionEase
{
public:
    virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseExponentialOut* actionWithAction(CCActionInterval* pAction);

};

/** 
 @brief Ease Exponential InOut
 */
class CC_DLL CCEaseExponentialInOut : public CCActionEase
{
public:
	virtual void update(ccTime time);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseExponentialInOut* actionWithAction(CCActionInterval* pAction);

};

/** 
 @brief Ease Sine In
 */
class CC_DLL CCEaseSineIn : public CCActionEase
{
public:
	virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseSineIn* actionWithAction(CCActionInterval* pAction);
};

/** 
 @brief Ease Sine Out
 */
class CC_DLL CCEaseSineOut : public CCActionEase
{
public:
	virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseSineOut* actionWithAction(CCActionInterval* pAction);
};

/** 
 @brief Ease Sine InOut
 */
class CC_DLL CCEaseSineInOut : public CCActionEase
{
public:
	virtual void update(ccTime time);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseSineInOut* actionWithAction(CCActionInterval* pAction);
};

/** 
 @brief Ease Elastic abstract class
 @since v0.8.2
 */
class CC_DLL CCEaseElastic : public CCActionEase
{
public:
	/** get period of the wave in radians. default is 0.3 */
	inline float getPeriod(void) { return m_fPeriod; }
	/** set period of the wave in radians. */
	inline void setPeriod(float fPeriod) { m_fPeriod = fPeriod; }

	/** Initializes the action with the inner action and the period in radians (default is 0.3) */
	bool initWithAction(CCActionInterval *pAction, float fPeriod);
	/** initializes the action */
	bool initWithAction(CCActionInterval *pAction);

	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseElastic* actionWithAction(CCActionInterval *pAction);
	/** Creates the action with the inner action and the period in radians (default is 0.3) */
	static CCEaseElastic* actionWithAction(CCActionInterval *pAction, float fPeriod);

protected:
	float m_fPeriod;
};

/** 
 @brief Ease Elastic In action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CC_DLL CCEaseElasticIn : public CCEaseElastic
{
public:
	virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseElasticIn* actionWithAction(CCActionInterval *pAction);
	/** Creates the action with the inner action and the period in radians (default is 0.3) */
	static CCEaseElasticIn* actionWithAction(CCActionInterval *pAction, float fPeriod);
};

/** 
 @brief Ease Elastic Out action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CC_DLL CCEaseElasticOut : public CCEaseElastic
{
public:
	virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseElasticOut* actionWithAction(CCActionInterval *pAction);
	/** Creates the action with the inner action and the period in radians (default is 0.3) */
	static CCEaseElasticOut* actionWithAction(CCActionInterval *pAction, float fPeriod);
};

/** 
 @brief Ease Elastic InOut action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CC_DLL CCEaseElasticInOut : public CCEaseElastic
{
public:
	virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseElasticInOut* actionWithAction(CCActionInterval *pAction);
	/** Creates the action with the inner action and the period in radians (default is 0.3) */
	static CCEaseElasticInOut* actionWithAction(CCActionInterval *pAction, float fPeriod);
};

/** 
 @brief CCEaseBounce abstract class.
 @since v0.8.2
*/
class CC_DLL CCEaseBounce : public CCActionEase
{
public:
	ccTime bounceTime(ccTime time);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseBounce* actionWithAction(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBounceIn action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
*/
class CC_DLL CCEaseBounceIn : public CCEaseBounce
{
public:
    virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseBounceIn* actionWithAction(CCActionInterval* pAction);
};

/** 
 @brief EaseBounceOut action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CC_DLL CCEaseBounceOut : public CCEaseBounce
{
public:
	virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseBounceOut* actionWithAction(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBounceInOut action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CC_DLL CCEaseBounceInOut : public CCEaseBounce
{
public:
	virtual void update(ccTime time);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseBounceInOut* actionWithAction(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBackIn action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CC_DLL CCEaseBackIn : public CCActionEase
{
public:
	virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseBackIn* actionWithAction(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBackOut action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CC_DLL CCEaseBackOut : public CCActionEase
{
public:
	virtual void update(ccTime time);
	virtual CCActionInterval* reverse(void);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseBackOut* actionWithAction(CCActionInterval* pAction);
};

/** 
 @brief CCEaseBackInOut action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CC_DLL CCEaseBackInOut : public CCActionEase
{
public:
	virtual void update(ccTime time);
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseBackInOut* actionWithAction(CCActionInterval* pAction);
};

}

#endif // __ACTION_CCEASE_ACTION_H__

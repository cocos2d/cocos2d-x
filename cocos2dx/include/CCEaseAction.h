/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCIntervalAction.h"
#include "ccxCommon.h"

namespace cocos2d {

class NSObject;
class NSZone;

/** Base class for Easing actions
 */
class CCX_DLL CCEaseAction : public CCIntervalAction
{
public:
	virtual ~CCEaseAction(void);

	/** initializes the action */
    bool initWithAction(CCIntervalAction *pAction);

	virtual NSObject* copyWithZone(NSZone* pZone);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void stop(void);
	virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);

public:
	/** creates the action */
	static CCEaseAction* actionWithAction(CCIntervalAction *pAction);

protected:
	CCIntervalAction *m_pOther;
};

/** Base class for Easing actions with rate parameters
 */
class CCX_DLL CCEaseRateAction : public CCEaseAction
{
public:
	virtual ~CCEaseRateAction(void);

	/** set rate value for the actions */
	inline void setRate(float rate) { m_fRate = rate; }
	/** get rate value for the actions */
	inline float getRate(void) { return m_fRate; }

	/** Initializes the action with the inner action and the rate parameter */
	bool initWithAction(CCIntervalAction *pAction, float fRate);

	virtual NSObject* copyWithZone(NSZone* pZone);
	virtual CCIntervalAction* reverse(void);

public:
	/** Creates the action with the inner action and the rate parameter */
	static CCEaseRateAction* actionWithAction(CCIntervalAction* pAction, float fRate);

protected:
	float m_fRate;
};

/** CCEaseIn action with a rate
 */
class CCX_DLL CCEaseIn : public CCEaseRateAction
{
public:
	virtual void update(ccTime time);
	virtual NSObject* copyWithZone(NSZone* pZone);
public:
	/** Creates the action with the inner action and the rate parameter */
	static CCEaseIn* actionWithAction(CCIntervalAction* pAction, float fRate);
};

/** CCEaseOut action with a rate
 */
class CCX_DLL CCEaseOut : public CCEaseRateAction
{
public:
	virtual void update(ccTime time);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** Creates the action with the inner action and the rate parameter */
    static CCEaseOut* actionWithAction(CCIntervalAction* pAction, float fRate);
};

/** CCEaseInOut action with a rate
 */
class CCX_DLL CCEaseInOut : public CCEaseRateAction
{
public:
	virtual void update(ccTime time);
	virtual NSObject* copyWithZone(NSZone* pZone);
	virtual CCIntervalAction* reverse(void);

public:
	/** Creates the action with the inner action and the rate parameter */
	static CCEaseInOut* actionWithAction(CCIntervalAction* pAction, float fRate);
};

/** CCEase Exponential In
 */
class CCX_DLL CCEaseExponentialIn : public CCEaseAction
{
public:
	virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseExponentialIn* actionWithAction(CCIntervalAction* pAction);
};

/** Ease Exponential Out
 */
class CCX_DLL CCEaseExponentialOut : public CCEaseAction
{
public:
    virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseExponentialOut* actionWithAction(CCIntervalAction* pAction);

};

/** Ease Exponential InOut
 */
class CCX_DLL CCEaseExponentialInOut : public CCEaseAction
{
public:
	virtual void update(ccTime time);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseExponentialInOut* actionWithAction(CCIntervalAction* pAction);

};

/** Ease Sine In
 */
class CCX_DLL CCEaseSineIn : public CCEaseAction
{
public:
	virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseSineIn* actionWithAction(CCIntervalAction* pAction);
};

/** Ease Sine Out
 */
class CCX_DLL CCEaseSineOut : public CCEaseAction
{
public:
	virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseSineOut* actionWithAction(CCIntervalAction* pAction);
};

/** Ease Sine InOut
 */
class CCX_DLL CCEaseSineInOut : public CCEaseAction
{
public:
	virtual void update(ccTime time);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseSineInOut* actionWithAction(CCIntervalAction* pAction);
};

/** Ease Elastic abstract class
 @since v0.8.2
 */
class CCX_DLL CCEaseElastic : public CCEaseAction
{
public:
	/** get period of the wave in radians. default is 0.3 */
	inline float getPeriod(void) { return m_fPeriod; }
	/** set period of the wave in radians. */
	inline void setPeriod(float fPeriod) { m_fPeriod = fPeriod; }

	/** Initializes the action with the inner action and the period in radians (default is 0.3) */
	bool initWithAction(CCIntervalAction *pAction, float fPeriod);
	/** initializes the action */
	bool initWithAction(CCIntervalAction *pAction);

	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseElastic* actionWithAction(CCIntervalAction *pAction);
	/** Creates the action with the inner action and the period in radians (default is 0.3) */
	static CCEaseElastic* actionWithAction(CCIntervalAction *pAction, float fPeriod);

protected:
	float m_fPeriod;
};

/** Ease Elastic In action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CCX_DLL CCEaseElasticIn : public CCEaseElastic
{
public:
	virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseElasticIn* actionWithAction(CCIntervalAction *pAction);
	/** Creates the action with the inner action and the period in radians (default is 0.3) */
	static CCEaseElasticIn* actionWithAction(CCIntervalAction *pAction, float fPeriod);
};

/** Ease Elastic Out action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CCX_DLL CCEaseElasticOut : public CCEaseElastic
{
public:
	virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseElasticOut* actionWithAction(CCIntervalAction *pAction);
	/** Creates the action with the inner action and the period in radians (default is 0.3) */
	static CCEaseElasticOut* actionWithAction(CCIntervalAction *pAction, float fPeriod);
};

/** Ease Elastic InOut action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CCX_DLL CCEaseElasticInOut : public CCEaseElastic
{
public:
	virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseElasticInOut* actionWithAction(CCIntervalAction *pAction);
	/** Creates the action with the inner action and the period in radians (default is 0.3) */
	static CCEaseElasticInOut* actionWithAction(CCIntervalAction *pAction, float fPeriod);
};

/** CCEaseBounce abstract class.
 @since v0.8.2
*/
class CCX_DLL CCEaseBounce : public CCEaseAction
{
public:
	ccTime bounceTime(ccTime time);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseBounce* actionWithAction(CCIntervalAction* pAction);
};

/** CCEaseBounceIn action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
*/
class CCX_DLL CCEaseBounceIn : public CCEaseBounce
{
public:
    virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseBounceIn* actionWithAction(CCIntervalAction* pAction);
};

/** EaseBounceOut action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CCX_DLL CCEaseBounceOut : public CCEaseBounce
{
public:
	virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseBounceOut* actionWithAction(CCIntervalAction* pAction);
};

/** CCEaseBounceInOut action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CCX_DLL CCEaseBounceInOut : public CCEaseBounce
{
public:
	virtual void update(ccTime time);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseBounceInOut* actionWithAction(CCIntervalAction* pAction);
};

/** CCEaseBackIn action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CCX_DLL CCEaseBackIn : public CCEaseAction
{
public:
	virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseBackIn* actionWithAction(CCIntervalAction* pAction);
};

/** CCEaseBackOut action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CCX_DLL CCEaseBackOut : public CCEaseAction
{
public:
	virtual void update(ccTime time);
	virtual CCIntervalAction* reverse(void);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseBackOut* actionWithAction(CCIntervalAction* pAction);
};

/** CCEaseBackInOut action.
 @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 */
class CCX_DLL CCEaseBackInOut : public CCEaseAction
{
public:
	virtual void update(ccTime time);
	virtual NSObject* copyWithZone(NSZone* pZone);

public:
	/** creates the action */
	static CCEaseBackInOut* actionWithAction(CCIntervalAction* pAction);
};

#endif // __ACTION_CCEASE_ACTION_H__

}

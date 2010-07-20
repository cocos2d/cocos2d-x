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

#ifndef __ACTIONS_CCACTION_H__
#define __ACTIONS_CCACTION_H__

#include "ccTypes.h"
#include "cocoa/NSObject.h"
#include "cocoa/NSZone.h"
#include "platform/platform.h"

enum {
	//! Default tag
	kCCActionTagInvalid = -1,
};

/** Base class for CCAction objects.
 */
class CCAction : public NSObject 
{
public:
    CCAction(void);
	virtual ~CCAction(void);

	//! Initializes the action
	CCAction* init(void);

	virtual NSObject* copyWithZone(NSZone *pZone);

	//! return true if the action has finished
	virtual bool isDone(void);

	//! called before the action start. It will also set the target.
	virtual void startWithTarget(NSObject *pTarget);

	//! called after the action has finished. It will set the 'target' to nil.
    //! IMPORTANT: You should never call "[action stop]" manually. Instead, use: "[target stopAction:action];"
    void stop(void);

	//! called every frame with it's delta time. DON'T override unless you know what you are doing.
	virtual void step(ccTime dt);

	//! called once per frame. time a value between 0 and 1
	//! For example: 
	//! * 0 means that the action just started
	//! * 0.5 means that the action is in the middle
	//! * 1 means that the action is over
	virtual void update(ccTime time);

	/** The "target". The action will modify the target properties.
	 The target will be set with the 'startWithTarget' method.
	 When the 'stop' method is called, target will be set to nil.
	 The target is 'assigned', it is not 'retained'.
	 */
	NSObject* getTarget(void);

	/** The original target, since target can be nil.
	 Is the target that were used to run the action. Unless you are doing something complex, like ActionManager, you should NOT call this method.
	 @since v0.8.2
	*/
     NSObject* getOriginalTarget(void);

	 // The action tag. An identifier of the action
	 INT32 getTag(void);
	 void setTag(INT32 nTag);

public:
	// Allocates and initializes the action
	static CCAction* action();

protected:
	NSObject	*m_pOriginalTarget;
	NSObject	*m_pTarget;
	INT32		m_nTag;
};

/** Base class actions that do have a finite time duration.
 Possible actions:
   - An action with a duration of 0 seconds
   - An action with a duration of 35.5 seconds
 Infitite time actions are valid
 */
class CCFiniteTimeAction : public CCAction
{
public:
    //! duration in seconds of the action
	ccTime getDuration(void);
	void setDuration(ccTime duration);

	// returns a reversed action
	virtual CCFiniteTimeAction* reverse(void);
protected:
	//! duration in seconds
	ccTime m_fDuration;
};

class CCIntervalAction;
/** Repeats an action for ever.
 To repeat the an action for a limited number of times use the Repeat action.
 @warning This action can't be Sequenceable because it is not an IntervalAction
 */
class CCRepeatForever : public CCAction
{
public:
    ~CCRepeatForever();

	CCRepeatForever* initWithAction(CCIntervalAction *pAction);
	virtual NSObject* copyWithZone(NSZone *pZone);
	virtual void startWithTarget(NSObject* pTarget);
	virtual void step(ccTime dt);
	virtual bool isDone(void);
	virtual CCIntervalAction* reverse(void);

public:
	static CCRepeatForever* actionWithAction(CCIntervalAction *pAction);

protected:
	CCIntervalAction *m_pOther;
};

/** Changes the speed of an action, making it take longer (speed>1)
 or less (speed<1) time.
 Useful to simulate 'slow motion' or 'fast forward' effect.
 @warning This action can't be Sequenceable because it is not an IntervalAction
 */
class CCSpeed : public CCAction
{
public:
	~CCSpeed(void);

	// alter the speed of the inner function in runtime
	float getSpeed(void);
	void setSpeed(float fSpeed);

	// initializes the action
	CCSpeed* initWithAction(CCInternalAction *pAction, float fRate);

	virtual NSObject* copyWithZone(NSZone *pZone);
	virtual void startWithTarget(NSObject* pTarget);
	virtual void step(ccTime dt);
	virtual bool isDone(void);
	virtual CCIntervalAction* reverse(void);

public:
	// creates the action
	static CCSpeed* actionWithAction(CCIntervalAction *pAction, float fRate);
    
protected:
	float m_fSpeed;
	CCIntervalAction *m_pOther;
};

/** CCFollow is an action that "follows" a node.
 
 Eg:
	[layer runAction: [CCFollow actionWithTarget:hero]];
 
 Instead of using CCCamera as a "follower", use this action instead.
 @since v0.99.2
 */
class CCNode;
class CGPoint;
class CGRect;

class CCFollow : public CCAction
{
public:
	~CCFollow(void);

	// alter behavior - turn on/off boundary
	bool isBoundarySet(void);
	void setBoudarySet(bool bValue);

	// initializes the action
	CCFollow* initWithTarget(CCNode *pFollowedNode);

	// initializes the action with a set boundary
	CCFollow* initWithTarget(CCNode *pFollowedNode, CGRect rect);

	virtual NSObject* copyWithZone(NSZone *pZone);
	virtual void startWithTarget(NSObject* pTarget);
	virtual void step(ccTime dt);
	virtual bool isDone(void);

public:
	// creates the action with no boundary set
	static CCFollow* actionWithTarget(CCNode *pFollowedNode);

	// creates the action with a set boundary
	static CCFollow* actionWithTarget(CCNode *pFollowedNode, CGRect rect);

protected:
	// node to follow
	CCNode *m_pobFollowedNode;

	// whether camera should be limited to certain area
	bool m_bBoundarySet;

	// if screensize is bigger than the boundary - update not needed
	bool m_bBoundaryFullyCovered;

	// fast access to the screen dimensions
	CGPoint m_obHalfScreenSize;
	CGPoint m_obFullScreenSize;

	// world boundaries
	float m_fLeftBoundary;
	float m_fRightBoundary;
	float m_fTopBoundary;
	float m_fBottomBoundary;
};

#endif // __ACTIONS_CCACTION_H__

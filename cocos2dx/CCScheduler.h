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

#ifndef __CCSCHEDULER_H__
#define __CCSCHEDULER_H__

#include "platform/platform.h"
#include "cocoa/NSObject.h"
#include "cocoa/selector_protocol.h"

//
// CCTimer
//
/** Light weight timer */
class CCTimer : public NSObject
{
public:
	// interval in seconds
    ccTime getInterval(void);
	void setInterval(ccTime fInterval);

    // Initializes a timer with a target and a selector.
	CCTimer* initWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector);

	// Initializes a timer with a target, a selector and an interval in seconds.
    CCTimer* initWithTargetInterval(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector, ccTime fSeconds);

	// triggers the timer
	void update(ccTime dt);

public:
	// Allocates a timer with a target and a selector.
	static CCTimer* timerWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector);

	// Allocates a timer with a target, a selector and an interval in seconds.
	static CCTimer* timerWithTargetInterval(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector, ccTime fSeconds);

public:
	SEL_SCHEDULE m_pfnSelector;

protected:
	SelectorProtocol *m_pTarget;	
	ccTime m_fInterval;
	ccTime m_fElapsed;
};

//
// CCScheduler
//
/** Scheduler is responsible of triggering the scheduled callbacks.
 You should not use NSTimer. Instead use this class.
 
 There are 2 different types of callbacks (selectors):

	- update selector: the 'update' selector will be called every frame. You can customize the priority.
	- custom selector: A custom selector will be called every frame, or with a custom interval of time
 
 The 'custom selectors' should be avoided when possible. It is faster, and consumes less memory to use the 'update selector'.

*/

struct _listEntry;
struct _hashSelectorEntry;
struct _hashUpdateEntry;

class CCScheduler : public NSObject
{
public:
	/** Modifies the time of all scheduled callbacks.
	 You can use this property to create a 'slow motion' or 'fast fordward' effect.
	 Default is 1.0. To create a 'slow motion' effect, use values below 1.0.
	 To create a 'fast fordward' effect, use values higher than 1.0.
	 @since v0.8
	 @warning It will affect EVERY scheduled selector / action.
	 */
	ccTime getTimeScale(void);
	void setTimeScale(ccTime fTimeScale);

	/** 'tick' the scheduler.
	 You should NEVER call this method, unless you know what you are doing.
	 */
	void tick(ccTime dt);

	/** The scheduled method will be called every 'interval' seconds.
	 If paused is YES, then it won't be called until it is resumed.
	 If 'interval' is 0, it will be called every frame, but if so, it recommened to use 'scheduleUpdateForTarget:' instead.

	 @since v0.99.3
	 */
	void scheduleUpdateForTarget(SelectorProtocol *pTarget, INT32 priority, bool bPaused);

	/** Unshedules a selector for a given target.
	 If you want to unschedule the "update", use unscheudleUpdateForTarget.
	 @since v0.99.3
	 */
	void unscheduleSelector(SEL_SCHEDULE pfnSelector, SelectorProtocol *pTarget);

	/** Unschedules the update selector for a given target
	 @since v0.99.3
	 */
	void unscheduleUpdateForTarget(SelectorProtocol *pTarget);

	/** Unschedules all selectors for a given target.
	 This also includes the "update" selector.
	 @since v0.99.3
	 */
	void unscheduleAllSelectorsForTarget(SelectorProtocol *pTarget);

	/** Unschedules all selectors from all targets.
	 You should NEVER call this method, unless you know what you are doing.

	 @since v0.99.3
	 */
	void unscheduleAllSelectors(void);

	/** Pauses the target.
	 All scheduled selectors/update for a given target won't be 'ticked' until the target is resumed.
	 If the target is not present, nothing happens.
	 @since v0.99.3
	 */
	void pauseTarget(SelectorProtocol *pTarget);

	/** Resumes the target.
	 The 'target' will be unpaused, so all schedule selectors/update will be 'ticked' again.
	 If the target is not present, nothing happens.
	 @since v0.99.3
	 */
	void resumeTarget(SelectorProtocol *pTarget);

	/** schedules a Timer.
	 It will be fired in every frame.
	 
	 @deprecated Use scheduleSelector:forTarget:interval:paused instead. Will be removed in 1.0
	 */
	void scheduleTimer(CCTimer *pTimer);

	/** unschedules an already scheduled Timer
 
	 @deprecated Use unscheduleSelector:forTarget. Will be removed in v1.0
	 */
	void unscheduleTimer(CCTimer *pTimer);

	/** unschedule all timers.
	 You should NEVER call this method, unless you know what you are doing.
	 
	 @deprecated Use scheduleAllSelectors instead. Will be removed in 1.0
	 @since v0.8
	 */
	void unscheduleAllTimers(void);

public:
    // returns a shared instance of the Scheduler
	static CCScheduler* getSharedScheduler(void);

	/** purges the shared scheduler. It releases the retained instance.
	 @since v0.99.0
	 */
	static void purgeSharedScheduler(void);

protected:
	ccTime m_fTimeScale;

	//
	// "updates with priority" stuff
	//
	struct _listEntry *m_pUpdatesNegList;		// list of priority < 0
	struct _listEntry *m_pUpdates0List;			// list priority == 0
	struct _listEntry *m_pUpdatesPosList;		// list priority > 0
	struct _hashUpdateEntry *m_pHashForUpdates; // hash used to fetch quickly the list entries for pause,delete,etc

	// Used for "selectors with interval"
	struct _hashSelectorEntry *m_pHashForSelectors;
	struct _hashSelectorEntry *m_pCurrentTarget;
	bool m_bCurrentTargetSalvaged;

	// Optimization
    SEL_SCHEDULE m_pfnUpdateSelector;
};

#endif // __CCSCHEDULER_H__

/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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

#include "CCObject.h"
#include "selector_protocol.h"
#include "support/data_support/uthash.h"
namespace   cocos2d {

//
// CCTimer
//
/** @brief Light weight timer */
class CC_DLL CCTimer : public CCObject
{
public:
	CCTimer(void) {}

	/** get interval in seconds */
	inline ccTime getInterval(void) { return m_fInterval; }
	/** set interval in seconds */
	inline void setInterval(ccTime fInterval){ m_fInterval = fInterval; }

    /** Initializes a timer with a target and a selector. */
	bool initWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector);

	/** Initializes a timer with a target, a selector and an interval in seconds. */
    bool initWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector, ccTime fSeconds);

	/** triggers the timer */
	void update(ccTime dt);

public:
	/** Allocates a timer with a target and a selector. */
	static CCTimer* timerWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector);

	/** Allocates a timer with a target, a selector and an interval in seconds. */
	static CCTimer* timerWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector, ccTime fSeconds);
	
#ifdef  ENABLE_LUA
	//CCTimer init from Script
	static CCTimer* timerWithScript(SelectorProtocol* pTarget, const char* szFuncName, ccTime fSeconds);
	bool initWithScript(SelectorProtocol* pTarget,  const char* szFuncName, ccTime fSeconds);
	bool isScriptFuncExist( const char* szFuncName);
	std::string m_scriptFunc;
#endif

public:
	SEL_SCHEDULE m_pfnSelector;
	ccTime m_fInterval;

protected:
	SelectorProtocol *m_pTarget;	
	ccTime m_fElapsed;
};

//
// CCScheduler
//
struct _listEntry;
struct _hashSelectorEntry;
struct _hashUpdateEntry;

/** @brief Scheduler is responsible of triggering the scheduled callbacks.
You should not use NSTimer. Instead use this class.

There are 2 different types of callbacks (selectors):

- update selector: the 'update' selector will be called every frame. You can customize the priority.
- custom selector: A custom selector will be called every frame, or with a custom interval of time

The 'custom selectors' should be avoided when possible. It is faster, and consumes less memory to use the 'update selector'.

*/
class CC_DLL CCScheduler : public CCObject
{
public:
    ~CCScheduler(void);
	
	inline ccTime getTimeScale(void) { return m_fTimeScale; }
	/** Modifies the time of all scheduled callbacks.
	You can use this property to create a 'slow motion' or 'fast forward' effect.
	Default is 1.0. To create a 'slow motion' effect, use values below 1.0.
	To create a 'fast forward' effect, use values higher than 1.0.
	@since v0.8
	@warning It will affect EVERY scheduled selector / action.
	*/
	inline void setTimeScale(ccTime fTimeScale) { m_fTimeScale = fTimeScale; }

	/** 'tick' the scheduler.
	 You should NEVER call this method, unless you know what you are doing.
	 */
	void tick(ccTime dt);

	/** The scheduled method will be called every 'interval' seconds.
	 If paused is YES, then it won't be called until it is resumed.
	 If 'interval' is 0, it will be called every frame, but if so, it recommened to use 'scheduleUpdateForTarget:' instead.
	 If the selector is already scheduled, then only the interval parameter will be updated without re-scheduling it again.

	 @since v0.99.3
	 */
#ifdef  ENABLE_LUA 
	void scheduleSelector(SEL_SCHEDULE pfnSelector, SelectorProtocol *pTarget, ccTime fInterval, bool bPaused, const char* szScriptFunc = NULL);
#else
	void scheduleSelector(SEL_SCHEDULE pfnSelector, SelectorProtocol *pTarget, ccTime fInterval, bool bPaused);
#endif
	/** Schedules the 'update' selector for a given target with a given priority.
	 The 'update' selector will be called every frame.
	 The lower the priority, the earlier it is called.
	 @since v0.99.3
	 */
	void scheduleUpdateForTarget(SelectorProtocol *pTarget, int nPriority, bool bPaused);

	/** Unschedule a selector for a given target.
	 If you want to unschedule the "update", use unscheudleUpdateForTarget.
	 @since v0.99.3
	 */
#ifdef  ENABLE_LUA
	void unscheduleSelector(SEL_SCHEDULE pfnSelector, SelectorProtocol *pTarget, const char* szScriptFunc = NULL);
#else
	void unscheduleSelector(SEL_SCHEDULE pfnSelector, SelectorProtocol *pTarget);
#endif

	/** Unschedules the update selector for a given target
	 @since v0.99.3
	 */
	void unscheduleUpdateForTarget(const SelectorProtocol *pTarget);

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
    /** returns a shared instance of the Scheduler */
	static CCScheduler* sharedScheduler(void);

	/** purges the shared scheduler. It releases the retained instance.
	 @since v0.99.0
	 */
	static void purgeSharedScheduler(void);

private:
	void removeHashElement(struct _hashSelectorEntry *pElement);
	CCScheduler();
	bool init(void);

	// update specific

	void priorityIn(struct _listEntry **ppList, SelectorProtocol *pTarget, int nPriority, bool bPaused);
	void appendIn(struct _listEntry **ppList, SelectorProtocol *pTarget, bool bPaused);

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
};
}//namespace   cocos2d 

#endif // __CCSCHEDULER_H__

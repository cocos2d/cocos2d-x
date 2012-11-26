/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "cocoa/CCObject.h"
#include "support/data_support/uthash.h"

NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */

// Priority level reserved for system services.
#define kCCPrioritySystem INT_MIN

// Minimum priority level for user scheduling.
#define kCCPriorityNonSystemMin (kCCPrioritySystem+1)

class CCSet;
//
// CCTimer
//
/** @brief Light-weight timer */
//
class CC_DLL CCTimer : public CCObject
{
public:
    CCTimer(void);
    
    /** get interval in seconds */
    float getInterval(void) const;
    /** set interval in seconds */
    void setInterval(float fInterval);
    
    SEL_SCHEDULE getSelector() const;
    
    /** Initializes a timer with a target and a selector. */
    bool initWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector);
    
    /** Initializes a timer with a target, a selector and an interval in seconds, repeat in number of times to repeat, delay in seconds. */
    bool initWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector, float fSeconds, unsigned int nRepeat, float fDelay);
    
    /** Initializes a timer with a script callback function and an interval in seconds. */
    bool initWithScriptHandler(int nHandler, float fSeconds);
    
    /** triggers the timer */
    void update(float dt);
    
public:
    /** Allocates a timer with a target and a selector. */
    static CCTimer* timerWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector);
    
    /** Allocates a timer with a target, a selector and an interval in seconds. */
    static CCTimer* timerWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector, float fSeconds);
    
    /** Allocates a timer with a script callback function and an interval in seconds. */
    static CCTimer* timerWithScriptHandler(int nHandler, float fSeconds);
    
    inline int getScriptHandler() { return m_nScriptHandler; };

protected:
    CCObject *m_pTarget;
    float m_fElapsed;
    bool m_bRunForever;
    bool m_bUseDelay;
    unsigned int m_uTimesExecuted;
    unsigned int m_uRepeat; //0 = once, 1 is 2 x executed
    float m_fDelay;
    float m_fInterval;
    SEL_SCHEDULE m_pfnSelector;
    
    int m_nScriptHandler;
};

//
// CCScheduler
//
struct _listEntry;
struct _hashSelectorEntry;
struct _hashUpdateEntry;

class CCArray;

/** @brief Scheduler is responsible for triggering the scheduled callbacks.
You should not use NSTimer. Instead use this class.

There are 2 different types of callbacks (selectors):

- update selector: the 'update' selector will be called every frame. You can customize the priority.
- custom selector: A custom selector will be called every frame, or with a custom interval of time

The 'custom selectors' should be avoided when possible. It is faster, and consumes less memory to use the 'update selector'.

*/
class CC_DLL CCScheduler : public CCObject
{
public:
    CCScheduler();
    ~CCScheduler(void);

    inline float getTimeScale(void) { return m_fTimeScale; }
    /** Modifies the time of all scheduled callbacks.
    You can use this property to create a 'slow motion' or 'fast forward' effect.
    Default is 1.0. To create a 'slow motion' effect, use values below 1.0.
    To create a 'fast forward' effect, use values higher than 1.0.
    @since v0.8
    @warning It will affect EVERY scheduled selector / action.
    */
    inline void setTimeScale(float fTimeScale) { m_fTimeScale = fTimeScale; }

    /** 'update' the scheduler.
     You should NEVER call this method, unless you know what you are doing.
     */
    void update(float dt);

    /** The scheduled method will be called every 'interval' seconds.
     If paused is YES, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame, but if so, it's recommended to use 'scheduleUpdateForTarget:' instead.
     If the selector is already scheduled, then only the interval parameter will be updated without re-scheduling it again.
     repeat let the action be repeated repeat + 1 times, use kCCRepeatForever to let the action run continuously
     delay is the amount of time the action will wait before it'll start

     @since v0.99.3, repeat and delay added in v1.1
     */
    void scheduleSelector(SEL_SCHEDULE pfnSelector, CCObject *pTarget, float fInterval, unsigned int repeat, float delay, bool bPaused);

    /** calls scheduleSelector with kCCRepeatForever and a 0 delay */
    void scheduleSelector(SEL_SCHEDULE pfnSelector, CCObject *pTarget, float fInterval, bool bPaused);
    /** Schedules the 'update' selector for a given target with a given priority.
     The 'update' selector will be called every frame.
     The lower the priority, the earlier it is called.
     @since v0.99.3
     */
    void scheduleUpdateForTarget(CCObject *pTarget, int nPriority, bool bPaused);

    /** Unschedule a selector for a given target.
     If you want to unschedule the "update", use unscheudleUpdateForTarget.
     @since v0.99.3
     */
    void unscheduleSelector(SEL_SCHEDULE pfnSelector, CCObject *pTarget);

    /** Unschedules the update selector for a given target
     @since v0.99.3
     */
    void unscheduleUpdateForTarget(const CCObject *pTarget);

    /** Unschedules all selectors for a given target.
     This also includes the "update" selector.
     @since v0.99.3
     */
    void unscheduleAllForTarget(CCObject *pTarget);

    /** Unschedules all selectors from all targets.
     You should NEVER call this method, unless you know what you are doing.

     @since v0.99.3
     */
    void unscheduleAll(void);
    
    /** Unschedules all selectors from all targets with a minimum priority.
      You should only call this with kCCPriorityNonSystemMin or higher.
      @since v2.0.0
      */
    void unscheduleAllWithMinPriority(int nMinPriority);

    /** The scheduled script callback will be called every 'interval' seconds.
     If paused is YES, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame.
     return schedule script entry ID, used for unscheduleScriptFunc().
     */
    unsigned int scheduleScriptFunc(unsigned int nHandler, float fInterval, bool bPaused);
    
    /** Unschedule a script entry. */
    void unscheduleScriptEntry(unsigned int uScheduleScriptEntryID);

    /** Pauses the target.
     All scheduled selectors/update for a given target won't be 'ticked' until the target is resumed.
     If the target is not present, nothing happens.
     @since v0.99.3
     */
    void pauseTarget(CCObject *pTarget);

    /** Resumes the target.
     The 'target' will be unpaused, so all schedule selectors/update will be 'ticked' again.
     If the target is not present, nothing happens.
     @since v0.99.3
     */
    void resumeTarget(CCObject *pTarget);

    /** Returns whether or not the target is paused
    @since v1.0.0
    */
    bool isTargetPaused(CCObject *pTarget);

    /** Pause all selectors from all targets.
      You should NEVER call this method, unless you know what you are doing.
     @since v2.0.0
      */
    CCSet* pauseAllTargets();

    /** Pause all selectors from all targets with a minimum priority.
      You should only call this with kCCPriorityNonSystemMin or higher.
      @since v2.0.0
      */
    CCSet* pauseAllTargetsWithMinPriority(int nMinPriority);

    /** Resume selectors on a set of targets.
     This can be useful for undoing a call to pauseAllSelectors.
     @since v2.0.0
      */
    void resumeTargets(CCSet* targetsToResume);

private:
    void removeHashElement(struct _hashSelectorEntry *pElement);
    void removeUpdateFromHash(struct _listEntry *entry);

    // update specific

    void priorityIn(struct _listEntry **ppList, CCObject *pTarget, int nPriority, bool bPaused);
    void appendIn(struct _listEntry **ppList, CCObject *pTarget, bool bPaused);

protected:
    float m_fTimeScale;

    //
    // "updates with priority" stuff
    //
    struct _listEntry *m_pUpdatesNegList;        // list of priority < 0
    struct _listEntry *m_pUpdates0List;            // list priority == 0
    struct _listEntry *m_pUpdatesPosList;        // list priority > 0
    struct _hashUpdateEntry *m_pHashForUpdates; // hash used to fetch quickly the list entries for pause,delete,etc

    // Used for "selectors with interval"
    struct _hashSelectorEntry *m_pHashForTimers;
    struct _hashSelectorEntry *m_pCurrentTarget;
    bool m_bCurrentTargetSalvaged;
    // If true unschedule will not remove anything from a hash. Elements will only be marked for deletion.
    bool m_bUpdateHashLocked;
    CCArray* m_pScriptHandlerEntries;
};

// end of global group
/// @}

NS_CC_END

#endif // __CCSCHEDULER_H__

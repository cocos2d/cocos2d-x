/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCSCHEDULER_H__
#define __CCSCHEDULER_H__

#include "CCObject.h"
#include "CCVector.h"
#include "uthash.h"

#include <functional>
#include <mutex>

NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */

//
// Timer
//
/** @brief Light-weight timer */
//
class CC_DLL Timer : public Object
{
public:
    /** Allocates a timer with a target and a selector. */
    static Timer* create(Object *target, SEL_SCHEDULE selector);
    /** Allocates a timer with a target, a selector and an interval in seconds. */
    static Timer* create(Object *target, SEL_SCHEDULE selector, float seconds);
    /** Allocates a timer with a script callback function and an interval in seconds. 
     * @js NA
     * @lua NA
     */
    static Timer* createWithScriptHandler(int handler, float seconds);

    CC_DEPRECATED_ATTRIBUTE static Timer* timerWithTarget(Object *target, SEL_SCHEDULE selector) { return Timer::create(target, selector); }
    CC_DEPRECATED_ATTRIBUTE static Timer* timerWithTarget(Object *target, SEL_SCHEDULE selector, float seconds) { return Timer::create(target, selector, seconds); }
    CC_DEPRECATED_ATTRIBUTE static Timer* timerWithScriptHandler(int handler, float seconds) { return Timer::createWithScriptHandler(handler, seconds); }

    Timer(void);

    /** Initializes a timer with a target and a selector. */
    bool initWithTarget(Object *target, SEL_SCHEDULE selector);
    /** Initializes a timer with a target, a selector and an interval in seconds, repeat in number of times to repeat, delay in seconds. */
    bool initWithTarget(Object *target, SEL_SCHEDULE selector, float seconds, unsigned int repeat, float delay);
    /** Initializes a timer with a script callback function and an interval in seconds. */
    bool initWithScriptHandler(int handler, float seconds);

    /** get interval in seconds */
    float getInterval() const;
    /** set interval in seconds */
    void setInterval(float interval);
    /**
     * @js NA
     * @lua NA
     */
    SEL_SCHEDULE getSelector() const;

    /** triggers the timer */
    void update(float dt);
    
    inline int getScriptHandler() const { return _scriptHandler; };

protected:
    Object *_target;
    float _elapsed;
    bool _runForever;
    bool _useDelay;
    unsigned int _timesExecuted;
    unsigned int _repeat; //0 = once, 1 is 2 x executed
    float _delay;
    float _interval;
    SEL_SCHEDULE _selector;
    
    int _scriptHandler;
};

//
// Scheduler
//
struct _listEntry;
struct _hashSelectorEntry;
struct _hashUpdateEntry;
class SchedulerScriptHandlerEntry;

/** @brief Scheduler is responsible for triggering the scheduled callbacks.
You should not use NSTimer. Instead use this class.

There are 2 different types of callbacks (selectors):

- update selector: the 'update' selector will be called every frame. You can customize the priority.
- custom selector: A custom selector will be called every frame, or with a custom interval of time

The 'custom selectors' should be avoided when possible. It is faster, and consumes less memory to use the 'update selector'.

*/
class CC_DLL Scheduler : public Object
{
public:
    // Priority level reserved for system services.
    static const int PRIORITY_SYSTEM;
    
    // Minimum priority level for user scheduling.
    static const int PRIORITY_NON_SYSTEM_MIN;
    /**
     * @js ctor
     */
    Scheduler();
    /**
     * @js NA
     * @lua NA
     */
    ~Scheduler(void);

    inline float getTimeScale() { return _timeScale; }
    /** Modifies the time of all scheduled callbacks.
    You can use this property to create a 'slow motion' or 'fast forward' effect.
    Default is 1.0. To create a 'slow motion' effect, use values below 1.0.
    To create a 'fast forward' effect, use values higher than 1.0.
    @since v0.8
    @warning It will affect EVERY scheduled selector / action.
    */
    inline void setTimeScale(float timeScale) { _timeScale = timeScale; }

    /** 'update' the scheduler.
     You should NEVER call this method, unless you know what you are doing.
     * @js NA
     * @lua NA
     */
    void update(float dt);

    /** The scheduled method will be called every 'interval' seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame, but if so, it's recommended to use 'scheduleUpdateForTarget:' instead.
     If the selector is already scheduled, then only the interval parameter will be updated without re-scheduling it again.
     repeat let the action be repeated repeat + 1 times, use kRepeatForever to let the action run continuously
     delay is the amount of time the action will wait before it'll start

     @since v0.99.3, repeat and delay added in v1.1
     */
    void scheduleSelector(SEL_SCHEDULE selector, Object *target, float interval, unsigned int repeat, float delay, bool paused);

    /** calls scheduleSelector with kRepeatForever and a 0 delay */
    void scheduleSelector(SEL_SCHEDULE selector, Object *target, float interval, bool paused);
    /** Schedules the 'update' selector for a given target with a given priority.
     The 'update' selector will be called every frame.
     The lower the priority, the earlier it is called.
     @since v0.99.3
     */
    void scheduleUpdateForTarget(Object *target, int priority, bool paused);
    
    /** Checks whether a selector for a given taget is scheduled.
     @since v3.0.0
     */
    bool isScheduledForTarget(SEL_SCHEDULE selector, Object *target);

    /** Unschedule a selector for a given target.
     If you want to unschedule the "update", use unscheudleUpdateForTarget.
     @since v0.99.3
     */
    void unscheduleSelector(SEL_SCHEDULE selector, Object *target);

    /** Unschedules the update selector for a given target
     @since v0.99.3
     */
    void unscheduleUpdateForTarget(const Object *target);

    /** Unschedules all selectors for a given target.
     This also includes the "update" selector.
     @since v0.99.3
     */
    void unscheduleAllForTarget(Object *target);

    /** Unschedules all selectors from all targets.
     You should NEVER call this method, unless you know what you are doing.

     @since v0.99.3
     */
    void unscheduleAll(void);
    
    /** Unschedules all selectors from all targets with a minimum priority.
      You should only call this with kPriorityNonSystemMin or higher.
      @since v2.0.0
      */
    void unscheduleAllWithMinPriority(int minPriority);

    /** The scheduled script callback will be called every 'interval' seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame.
     return schedule script entry ID, used for unscheduleScriptFunc().
     */
    unsigned int scheduleScriptFunc(unsigned int handler, float interval, bool paused);
    
    /** Unschedule a script entry. */
    void unscheduleScriptEntry(unsigned int scheduleScriptEntryID);

    /** Pauses the target.
     All scheduled selectors/update for a given target won't be 'ticked' until the target is resumed.
     If the target is not present, nothing happens.
     @since v0.99.3
     */
    void pauseTarget(Object *target);

    /** Resumes the target.
     The 'target' will be unpaused, so all schedule selectors/update will be 'ticked' again.
     If the target is not present, nothing happens.
     @since v0.99.3
     */
    void resumeTarget(Object *target);

    /** Returns whether or not the target is paused
    @since v1.0.0
    * In js: var isTargetPaused(var jsObject)
    * @lua NA 
    */
    bool isTargetPaused(Object *target);

    /** Pause all selectors from all targets.
      You should NEVER call this method, unless you know what you are doing.
     @since v2.0.0
      */
    Vector<Object*> pauseAllTargets();

    /** Pause all selectors from all targets with a minimum priority.
      You should only call this with kPriorityNonSystemMin or higher.
      @since v2.0.0
      */
    Vector<Object*> pauseAllTargetsWithMinPriority(int minPriority);

    /** Resume selectors on a set of targets.
     This can be useful for undoing a call to pauseAllSelectors.
     @since v2.0.0
      */
    void resumeTargets(const Vector<Object*>& targetsToResume);

    /** calls a function on the cocos2d thread. Useful when you need to call a cocos2d function from another thread.
     This function is thread safe.
     @since v3.0
     */
    void performFunctionInCocosThread( const std::function<void()> &function);

protected:
    void removeHashElement(struct _hashSelectorEntry *element);
    void removeUpdateFromHash(struct _listEntry *entry);

    // update specific

    void priorityIn(struct _listEntry **list, Object *target, int priority, bool paused);
    void appendIn(struct _listEntry **list, Object *target, bool paused);


    float _timeScale;

    //
    // "updates with priority" stuff
    //
    struct _listEntry *_updatesNegList;        // list of priority < 0
    struct _listEntry *_updates0List;            // list priority == 0
    struct _listEntry *_updatesPosList;        // list priority > 0
    struct _hashUpdateEntry *_hashForUpdates; // hash used to fetch quickly the list entries for pause,delete,etc

    // Used for "selectors with interval"
    struct _hashSelectorEntry *_hashForTimers;
    struct _hashSelectorEntry *_currentTarget;
    bool _currentTargetSalvaged;
    // If true unschedule will not remove anything from a hash. Elements will only be marked for deletion.
    bool _updateHashLocked;
    Vector<SchedulerScriptHandlerEntry*> _scriptHandlerEntries;

    // Used for "perform Function"
    std::vector<std::function<void()>> _functionsToPerform;
    std::mutex _performMutex;
};

// end of global group
/// @}

NS_CC_END

#endif // __CCSCHEDULER_H__

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

#include <functional>
#include <mutex>
#include <set>

#include "base/CCRef.h"
#include "base/CCVector.h"
#include "base/uthash.h"

NS_CC_BEGIN

class Scheduler;

typedef std::function<void(float)> ccSchedulerFunc;

/**
 * @cond
 */
class CC_DLL Timer : public Ref
{
protected:
    Timer();
public:
    /** @~english get interval in seconds  @~chinese 获取时间间隔，单位为秒*/
    inline float getInterval() const { return _interval; };
    /** @~english set interval in seconds  @~chinese 设置时间间隔，单位为秒*/
    inline void setInterval(float interval) { _interval = interval; };
    
    void setupTimerWithInterval(float seconds, unsigned int repeat, float delay);
    
    virtual void trigger() = 0;
    virtual void cancel() = 0;
    
    /** @~english triggers the timer  @~chinese 触发计时器*/
    void update(float dt);
    
protected:
    
    Scheduler* _scheduler; // weak ref
    float _elapsed;
    bool _runForever;
    bool _useDelay;
    unsigned int _timesExecuted;
    unsigned int _repeat; //0 = once, 1 is 2 x executed
    float _delay;
    float _interval;
};


class CC_DLL TimerTargetSelector : public Timer
{
public:
    TimerTargetSelector();

    /** @~english Initializes a timer with a target, a selector and an interval in seconds, repeat in number of times to repeat, delay in seconds.
     *  @~chinese 使用指定的目标对象，回调函数，时间间隔，重复次数和延迟时间初始化一个定时器。
     */
    bool initWithSelector(Scheduler* scheduler, SEL_SCHEDULE selector, Ref* target, float seconds, unsigned int repeat, float delay);
    
    inline SEL_SCHEDULE getSelector() const { return _selector; };
    
    virtual void trigger() override;
    virtual void cancel() override;
    
protected:
    Ref* _target;
    SEL_SCHEDULE _selector;
};


class CC_DLL TimerTargetCallback : public Timer
{
public:
    TimerTargetCallback();
    
    // Initializes a timer with a target, a lambda and an interval in seconds, repeat in number of times to repeat, delay in seconds.
    bool initWithCallback(Scheduler* scheduler, const ccSchedulerFunc& callback, void *target, const std::string& key, float seconds, unsigned int repeat, float delay);
    
    inline const ccSchedulerFunc& getCallback() const { return _callback; };
    inline const std::string& getKey() const { return _key; };
    
    virtual void trigger() override;
    virtual void cancel() override;
    
protected:
    void* _target;
    ccSchedulerFunc _callback;
    std::string _key;
};

#if CC_ENABLE_SCRIPT_BINDING

class CC_DLL TimerScriptHandler : public Timer
{
public:
    bool initWithScriptHandler(int handler, float seconds);
    inline int getScriptHandler() const { return _scriptHandler; };
    
    virtual void trigger() override;
    virtual void cancel() override;
    
private:
    int _scriptHandler;
};

#endif

/**
 * @endcond
 */

/**
 * @addtogroup base
 * @{
 */

struct _listEntry;
struct _hashSelectorEntry;
struct _hashUpdateEntry;

#if CC_ENABLE_SCRIPT_BINDING
class SchedulerScriptHandlerEntry;
#endif

/** @brief @~english Scheduler is responsible for triggering the scheduled callbacks.
You should not use system timer for your game logic. Instead, use this class.

There are 2 different types of callbacks (selectors):

- update selector: the 'update' selector will be called every frame. You can customize the priority.
- custom selector: A custom selector will be called every frame, or with a custom interval of time

The 'custom selectors' should be avoided when possible. It is faster, and consumes less memory to use the 'update selector'.

 * @~chinese
 * Scheduler 是负责触发回调函数的类。
 * 不建议在游戏代码中直接使用系统的定时器，推荐使用这个类来实现定时器功能。
 * 
 * 有两种不同类型的定时器:
 * - update 定时器：每一帧都会触发。您可以自定义优先级。
 * - 自定义定时器：自定义定时器可以每一帧或者自定义的时间间隔触发。
 * 
 * 应该尽量避免使用自定义定时器。使用 update 定时器更快，而且消耗更少的内存。
 * 
*/
class CC_DLL Scheduler : public Ref
{
public:
    /** @~english Priority level reserved for system services. 
     * @~chinese 系统服务的优先级。
     * @lua NA
     * @js NA
     */
    static const int PRIORITY_SYSTEM;
    
    /** @~english Minimum priority level for user scheduling. 
     * Priority level of user scheduling should bigger then this value.
     *
     * @~chinese 用户调度的最低优先级。
     * 用户调度的优先级应该比这个值大。
     * 
     * @lua NA
     * @js NA
     */
    static const int PRIORITY_NON_SYSTEM_MIN;
    
    /**@~english
     * Constructor
     *
     * @~chinese 
     * 构造函数
     * 
     * @js ctor
     */
    Scheduler();
    
    /**@~english
     * Destructor
     *
     * @~chinese 
     * 析构函数
     * 
     * @js NA
     * @lua NA
     */
    virtual ~Scheduler();

    /**@~english
     * Gets the time scale of schedule callbacks.
     * @~chinese 
     * 获取时间间隔的缩放比例。
     * @see Scheduler::setTimeScale()
     */
    inline float getTimeScale() { return _timeScale; }
    /** @~english Modifies the time of all scheduled callbacks.
     * You can use this property to create a 'slow motion' or 'fast forward' effect.
     * Default is 1.0. To create a 'slow motion' effect, use values below 1.0.
     * To create a 'fast forward' effect, use values higher than 1.0.
     * @~chinese 设置时间间隔的缩放比例。
     * 您可以使用这个方法来创建一个“慢动作”或“快进”的效果。
     * 默认是1.0。要创建一个“慢动作”效果,使用值低于1.0。
     * 要使用“快进”效果，使用值大于 1.0。
     * @since v0.8
     * @warning @~english It will affect EVERY scheduled selector / action.
     * @~chinese 它会影响所有的定时器。
     */
    inline void setTimeScale(float timeScale) { _timeScale = timeScale; }

    /** @~english 'update' the scheduler.
     * You should NEVER call this method, unless you know what you are doing.
     * @~chinese update 调度器。
     * 不应该直接调用这个方法，除非完全了解这么做的结果。
     * @lua NA
     */
    void update(float dt);

    /////////////////////////////////////
    
    // schedule
    
    /** @~english The scheduled method will be called every 'interval' seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame, but if so, it's recommended to use 'scheduleUpdate' instead.
     If the 'callback' is already scheduled, then only the interval parameter will be updated without re-scheduling it again.
     repeat let the action be repeated repeat + 1 times, use CC_REPEAT_FOREVER to let the action run continuously
     delay is the amount of time the action will wait before it'll start.
     * @~chinese 当时间间隔达到指定值时，设置的回调函数将会被调用。
     * 如果 paused 值为 true，那么直到 resume 被调用才开始计时。
     * 如果 interval 值为0，那么回调函数每一帧都会被调用。但如果是这样，建议使用 `scheduleUpdate` 代替。
     * 如果回调函数已经被定时器使用，那么只会更新之前定时器的时间间隔参数，不会设置新的定时器。
     * repeat 值可以让定时器触发 repeat + 1 次，使用 `CC_REPEAT_FOREVER` 可以让定时器一直循环触发。
     * delay 值指定延迟时间。定时器会在延迟指定的时间之后开始计时。
     @param callback @~english The callback function.
     * @~chinese 回调函数。
     @param target @~english The target of the callback function.
     * @~chinese 回调函数的对象。
     @param interval @~english The interval to schedule the callback. If the value is 0, then the callback will be scheduled every frame.
     * @~chinese 设置的时间间隔。如果该值为0,则每一帧都会触发回调函数。
     @param repeat @~english repeat+1 times to schedule the callback.
     * @~chinese 回调函数被触发 repeat + 1 次。
     @param delay @~english Schedule call back after `delay` seconds. If the value is not 0, the first schedule will happen after `delay` seconds.
            But it will only affect first schedule. After first schedule, the delay time is determined by `interval`.
     * @~chinese 第一次触发回调的延迟时间。如果该值不是0，第一次回调函数的触发时间将被推迟指定的秒数。
     * 这只会影响第一次定时器的触发。之后每次定时器的触发时间间隔由 interval 值决定。
     @param paused @~english Whether or not to pause the schedule.
     * @~chinese 是否要暂停。
     @param key @~english The key to identify the callback function, because there is not way to identify a std::function<>.
     * @~chinese 区别于其他回调函数的关键字，因为没有办法区分 std::function<> 是否相同。
     @since v3.0
     */
    void schedule(const ccSchedulerFunc& callback, void *target, float interval, unsigned int repeat, float delay, bool paused, const std::string& key);

    /** @~english The scheduled method will be called every 'interval' seconds for ever.
     * @~chinese 这个定时器会按照指定的时间间隔不断的触发。
     @param callback @~english The callback function.
     * @~chinese 回调函数。
     @param target @~english The target of the callback function.
     * @~chinese 回调函数的对象。
     @param interval @~english The interval to schedule the callback. If the value is 0, then the callback will be scheduled every frame.
     * @~chinese 设置的时间间隔。如果该值为0,则每一帧都会触发回调函数。
     @param paused @~english Whether or not to pause the schedule.
     * @~chinese 是否要暂停。
     @param key @~english The key to identify the callback function, because there is not way to identify a std::function<>.
     * @~chinese 区别于其他回调函数的关键字，因为没有办法区分 std::function<> 是否相同。
     @since v3.0
     */
    void schedule(const ccSchedulerFunc& callback, void *target, float interval, bool paused, const std::string& key);
    
    
    /** @~english The scheduled method will be called every `interval` seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame, but if so, it's recommended to use 'scheduleUpdate' instead.
     If the selector is already scheduled, then only the interval parameter will be updated without re-scheduling it again.
     repeat let the action be repeated repeat + 1 times, use CC_REPEAT_FOREVER to let the action run continuously
     delay is the amount of time the action will wait before it'll start
     
     * @~chinese 当时间间隔达到指定值时，设置的回调函数将会被调用。
     * 如果 paused 值为 true，那么直到 resume 被调用才开始计时。
     * 如果 interval 值为0，那么回调函数每一帧都会被调用。但如果是这样，建议使用 `scheduleUpdate` 代替。
     * 如果回调函数已经被定时器使用，那么只会更新之前定时器的时间间隔参数，不会设置新的定时器。
     * repeat 值可以让定时器触发 repeat + 1 次，使用 `CC_REPEAT_FOREVER` 可以让定时器一直循环触发。
     * delay 值指定延迟时间。定时器会在延迟指定的时间之后开始计时。
     @param selector @~english The callback function.
     * @~chinese 回调函数。
     @param target @~english The target of the callback function.
     * @~chinese 回调函数的对象。
     @param interval @~english The interval to schedule the callback. If the value is 0, then the callback will be scheduled every frame.
     * @~chinese 设置的时间间隔。如果该值为0,则每一帧都会触发回调函数。
     @param repeat @~english repeat+1 times to schedule the callback.
     * @~chinese 回调函数被触发 repeat + 1 次。
     @param delay @~english Schedule call back after `delay` seconds. If the value is not 0, the first schedule will happen after `delay` seconds.
     But it will only affect first schedule. After first schedule, the delay time is determined by `interval`.
     * @~chinese 第一次触发回调的延迟时间。如果该值不是0，第一次回调函数的触发时间将被推迟指定的秒数。
     * 这只会影响第一次定时器的触发。之后每次定时器的触发时间间隔由 interval 值决定。
     @param paused @~english Whether or not to pause the schedule.
     * @~chinese 是否要暂停。
     @since v3.0
     */
    void schedule(SEL_SCHEDULE selector, Ref *target, float interval, unsigned int repeat, float delay, bool paused);
    
    /** @~english The scheduled method will be called every `interval` seconds for ever.
     * @~chinese 这个定时器会按照指定的时间间隔不断的触发。
     @param selector @~english The callback function.
     * @~chinese 回调函数。
     @param target @~english The target of the callback function.
     * @~chinese 回调函数的对象。
     @param interval @~english The interval to schedule the callback. If the value is 0, then the callback will be scheduled every frame.
     * @~chinese 设置的时间间隔。如果该值为0,则每一帧都会触发回调函数。
     @param paused @~english Whether or not to pause the schedule.
     * @~chinese 是否要暂停。
     */
    void schedule(SEL_SCHEDULE selector, Ref *target, float interval, bool paused);
    
    /** @~english Schedules the 'update' selector for a given target with a given priority.
     The 'update' selector will be called every frame.
     The lower the priority, the earlier it is called.
     * @~chinese 使用指定的优先级为指定的对象设置 update 定时器。
     * update 定时器每一帧都会被触发。
     * 优先级的值越低，定时器被触发的越早。
     @since v3.0
     @lua NA
     */
    template <class T>
    void scheduleUpdate(T *target, int priority, bool paused)
    {
        this->schedulePerFrame([target](float dt){
            target->update(dt);
        }, target, priority, paused);
    }

#if CC_ENABLE_SCRIPT_BINDING
    // Schedule for script bindings.
    /** @~english The scheduled script callback will be called every 'interval' seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame.
     return schedule script entry ID, used for unscheduleScriptFunc().
     
     * @~chinese 为脚本层定制的定时器，回调函数在指定的时间间隔被触发。
     * 如果 paused 值为 true，那么直到定时器 resume 才会开始计时。
     * 如果 interval 值为0，则每一帧都会触发回调函数。
     * 返回一个 ID，用于 unscheduleScriptFunc()。
     * 
     @warn @~english Don't invoke this function unless you know what you are doing.
     * @~chinese 不要直接调用这个函数，除非你知道你在做什么。
     @js NA
     @lua NA
     */
    unsigned int scheduleScriptFunc(unsigned int handler, float interval, bool paused);
#endif
    /////////////////////////////////////
    
    // unschedule

    /** @~english Unschedules a callback for a key and a given target.
     If you want to unschedule the 'callbackPerFrame', use unscheduleUpdate.
     * @~chinese 根据指定的 key 和 target 取消相应的定时器。
     * 如果需要取消 `callbackPerFrame` 定时器，请使用 `unscheduleUpdate`。
     @param key @~english The key to identify the callback function, because there is not way to identify a std::function<>.
     * @~chinese 识别回调函数的关键字，因为没有办法区分 std::function<> 是否相同。
     @param target @~english The target to be unscheduled.
     * @~chinese 需要取消定时器的对象。
     @since v3.0
     */
    void unschedule(const std::string& key, void *target);

    /** @~english Unschedules a selector for a given target.
     If you want to unschedule the "update", use `unscheudleUpdate()`.
     * @~chinese 根据指定的回调函数和 target 对象取消相应的定时器。
     * 如果需要取消 `update` 定时器，请使用 `unscheudleUpdate()`。
     @param selector @~english The selector that is unscheduled.
     * @~chinese 需要取消的回调函数。
     @param target @~english The target of the unscheduled selector.
     * @~chinese 需要取消定时器的对象。
     @since v3.0
     */
    void unschedule(SEL_SCHEDULE selector, Ref *target);
    
    /** @~english Unschedules the update selector for a given target
     * @~chinese 取消 update 定时器。
     @param target @~english The target to be unscheduled.
     * @~chinese 需要取消定时器的对象。
     @since v0.99.3
     */
    void unscheduleUpdate(void *target);
    
    /** @~english Unschedules all selectors for a given target.
     This also includes the "update" selector.
     * @~chinese 取消指定对象的所有定时器。
     * 包括 update 定时器
     @param target @~english The target to be unscheduled.
     * @~chinese 需要取消定时器的对象。
     @since v0.99.3
     @lua NA
     */
    void unscheduleAllForTarget(void *target);
    
    /** @~english Unschedules all selectors from all targets.
     You should NEVER call this method, unless you know what you are doing.
     * @~chinese 取消所有对象的所有定时器。
     * 不用调用此函数，除非你指定你在做什么。
     @since v0.99.3
     */
    void unscheduleAll();
    
    /** @~english Unschedules all selectors from all targets with a minimum priority.
     You should only call this with `PRIORITY_NON_SYSTEM_MIN` or higher.
     * @~chinese 取消所有优先级的值大于 minPriority 的定时器。
     * 你应该只取消优先级的值大于 `PRIORITY_NON_SYSTEM_MIN` 的定时器。
     @param minPriority @~english The minimum priority of selector to be unscheduled. Which means, all selectors which
            priority is higher than minPriority will be unscheduled.
     * @~chinese 指定的优先级最低值。这意味着，所有优先级的值高于 minPriority 的定时器都会被取消。
     @since v2.0.0
     */
    void unscheduleAllWithMinPriority(int minPriority);
    
#if CC_ENABLE_SCRIPT_BINDING
    /** @~english Unschedule a script entry. 
     * @~chinese 取消脚本层的指定定时器。
     * @warning @~english Don't invoke this function unless you know what you are doing.
     * @~chinese 不要调用这个函数,除非你知道你在做什么。
     * @js NA
     * @lua NA
     */
    void unscheduleScriptEntry(unsigned int scheduleScriptEntryID);
#endif
    
    /////////////////////////////////////
    
    // isScheduled
    
    /** @~english Checks whether a callback associated with 'key' and 'target' is scheduled.
     * @~chinese 检查指定的关键字与对象是否设置了定时器。
     @param key @~english The key to identify the callback function, because there is not way to identify a std::function<>.
     * @~chinese 识别回调函数的关键字，因为没有办法区分 std::function<> 是否相同。
     @param target @~english The target of the callback.
     * @~chinese 回调函数的对象。
     @return @~english True if the specified callback is invoked, false if not.
     * @~chinese 如果设置了定时器，返回 true；否则返回 false。
     @since v3.0.0
     */
    bool isScheduled(const std::string& key, void *target);
    
    /** @~english Checks whether a selector for a given taget is scheduled.
     * @~chinese 检查指定的回调函数和对象是否设置了定时器。
     @param selector @~english The selector to be checked.
     * @~chinese 需要检查的回调函数。
     @param target @~english The target of the callback.
     * @~chinese 回调函数的对象。
     @return @~english True if the specified selector is invoked, false if not.
     * @~chinese 如果设置了定时器，返回 true；否则返回 false。
     @since v3.0
     */
    bool isScheduled(SEL_SCHEDULE selector, Ref *target);
    
    /////////////////////////////////////
    
    /** @~english Pauses the target.
     All scheduled selectors/update for a given target won't be 'ticked' until the target is resumed.
     If the target is not present, nothing happens.
     * @~chinese 暂停指定对象的定时器。
     * 指定对象的所有定时器都会被暂停。
     * 如果指定的对象没有定时器，什么也不会发生。
     @param target @~english The target to be paused.
     * @~chinese 需要暂停的对象。
     @since v0.99.3
     */
    void pauseTarget(void *target);

    /** @~english Resumes the target.
     The 'target' will be unpaused, so all schedule selectors/update will be 'ticked' again.
     If the target is not present, nothing happens.
     * @~chinese 恢复指定对象的所有定时器。
     * 指定的对象的所有定时器将继续工作。
     * 如果指定的对象没有定时器，什么也不会发生。
     @param target @~english The target to be resumed.
     * @~chinese 需要恢复定时器的对象。
     @since v0.99.3
     */
    void resumeTarget(void *target);

    /** @~english Returns whether or not the target is paused.
     * @~chinese 返回指定的对象的定时器是否暂停了。
     * @param target @~english The target to be checked.
     * @~chinese 需要检查的对象。
     * @return @~english True if the target is paused, false if not.
     * @~chinese 如果是暂停状态，返回 true；否则返回 false。
     * @since v1.0.0
     * @lua NA
     */
    bool isTargetPaused(void *target);

    /** @~english Pause all selectors from all targets.
      You should NEVER call this method, unless you know what you are doing.
     * @~chinese 暂停所有对象的所有定时器。
     * 不要调用这个方法,除非你知道你正在做什么。
     @since v2.0.0
      */
    std::set<void*> pauseAllTargets();

    /** @~english Pause all selectors from all targets with a minimum priority.
      You should only call this with PRIORITY_NON_SYSTEM_MIN or higher.
     * @~chinese 暂停所有优先级的值大于 minPriority 的定时器。
     * 你应该只暂停优先级的值大于 `PRIORITY_NON_SYSTEM_MIN` 的定时器。
      @param minPriority @~english The minimum priority of selector to be paused. Which means, all selectors which
            priority is higher than minPriority will be paused.
     * @~chinese 指定的优先级最低值。这意味着，所有优先级的值高于 minPriority 的定时器都会被暂停。
      @since v2.0.0
      */
    std::set<void*> pauseAllTargetsWithMinPriority(int minPriority);

    /** @~english Resume selectors on a set of targets.
     This can be useful for undoing a call to pauseAllSelectors.
     * @~chinese 恢复指定的数组中所有对象的定时器。
     * 这个函数可以用来取消 `pauseAllSelectors` 的效果。
     @param targetsToResume @~english The set of targets to be resumed.
     * @~chinese 需要恢复的对象数组。
     @since v2.0.0
      */
    void resumeTargets(const std::set<void*>& targetsToResume);

    /** @~english Calls a function on the cocos2d thread. Useful when you need to call a cocos2d function from another thread.
     This function is thread safe.
     * @~chinese 在 cocos2d 线程上调用一个函数。当你需要从另一个线程调用 cocos2d 函数时可以使用这个方法。
     * 这个函数是线程安全的。
     @param function @~english The function to be run in cocos2d thread.
     * @~chinese cocos2d 线程中要运行的函数。
     @since v3.0
     @js NA
     */
    void performFunctionInCocosThread( const std::function<void()> &function);
    
    /////////////////////////////////////
    
    // Deprecated methods:
    
    /** @~english The scheduled method will be called every 'interval' seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame, but if so, it's recommended to use 'scheduleUpdateForTarget:' instead.
     If the selector is already scheduled, then only the interval parameter will be updated without re-scheduling it again.
     repeat let the action be repeated repeat + 1 times, use CC_REPEAT_FOREVER to let the action run continuously
     delay is the amount of time the action will wait before it'll start
     * @~chinese 当时间间隔达到指定值时，设置的回调函数将会被调用。
     * 如果 paused 值为 true，那么直到 resume 被调用才开始计时。
     * 如果 interval 值为0，那么回调函数每一帧都会被调用。但如果是这样，建议使用 `scheduleUpdate` 代替。
     * 如果回调函数已经被定时器使用，那么只会更新之前定时器的时间间隔参数，不会设置新的定时器。
     * repeat 值可以让定时器触发 repeat + 1 次，使用 `CC_REPEAT_FOREVER` 可以让定时器一直循环触发。
     * delay 值指定延迟时间。定时器会在延迟指定的时间之后开始计时。
     @deprecated Please use `Scheduler::schedule` instead.
     @since v0.99.3, repeat and delay added in v1.1
     @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void scheduleSelector(SEL_SCHEDULE selector, Ref *target, float interval, unsigned int repeat, float delay, bool paused)
    {
        schedule(selector, target, interval, repeat, delay, paused);
    };
    
    /** @~english Calls scheduleSelector with CC_REPEAT_FOREVER and a 0 delay.
     * @~chinese 以 repeat 值为 `CC_REPEAT_FOREVER` 和 delay 值为 0 调用 `scheduleSelector(SEL_SCHEDULE selector, Ref *target, float interval, unsigned int repeat, float delay, bool paused)`.
     *  @deprecated Please use `Scheduler::schedule` instead.
     *  @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void scheduleSelector(SEL_SCHEDULE selector, Ref *target, float interval, bool paused)
    {
        schedule(selector, target, interval, paused);
    };
    
    /** @~english Schedules the 'update' selector for a given target with a given priority.
     The 'update' selector will be called every frame.
     The lower the priority, the earlier it is called.
     * @~chinese 为指定的对象设置 update 定时器。update 定时器每一帧都会被调用。
     * 优先级的值越低，越早被调用。
     @deprecated Please use 'Scheduler::scheduleUpdate' instead.
     @since v0.99.3
     */
    template <class T>
    CC_DEPRECATED_ATTRIBUTE void scheduleUpdateForTarget(T* target, int priority, bool paused) { scheduleUpdate(target, priority, paused); };
    
    /** @~english Unschedule a selector for a given target.
     If you want to unschedule the "update", use unscheudleUpdateForTarget.
     * @~chinese 根据指定的回调函数和 target 对象取消相应的定时器。
     * 如果需要取消 `update` 定时器，请使用 `unscheudleUpdate()`。
     @deprecated Please use 'Scheduler::unschedule' instead.
     @since v0.99.3
     @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void unscheduleSelector(SEL_SCHEDULE selector, Ref *target) { unschedule(selector, target); };
    
    /** @~english Checks whether a selector for a given taget is scheduled.
     * @~chinese 判断指定的对象和回调函数是否设置了定时器。
     @deprecated Please use 'Scheduler::isScheduled' instead.
     @since v0.99.3
     @js NA
     */
    CC_DEPRECATED_ATTRIBUTE bool isScheduledForTarget(Ref *target, SEL_SCHEDULE selector) { return isScheduled(selector, target); };
    
    /** @~english Unschedules the update selector for a given target
     * @~chinese 取消指定对象的所有定时器。
     @deprecated Please use 'Scheduler::unscheduleUpdate' instead.
     @since v0.99.3
     */
    CC_DEPRECATED_ATTRIBUTE void unscheduleUpdateForTarget(Ref *target) { return unscheduleUpdate(target); };
    
protected:
    void schedulePerFrame(const ccSchedulerFunc& callback, void *target, int priority, bool paused);
    
    void removeHashElement(struct _hashSelectorEntry *element);
    void removeUpdateFromHash(struct _listEntry *entry);

    // update specific

    void priorityIn(struct _listEntry **list, const ccSchedulerFunc& callback, void *target, int priority, bool paused);
    void appendIn(struct _listEntry **list, const ccSchedulerFunc& callback, void *target, bool paused);


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
    
#if CC_ENABLE_SCRIPT_BINDING
    Vector<SchedulerScriptHandlerEntry*> _scriptHandlerEntries;
#endif
    
    // Used for "perform Function"
    std::vector<std::function<void()>> _functionsToPerform;
    std::mutex _performMutex;
};

// end of base group
/** @~english @}  @~chinese @ }*/

NS_CC_END

#endif // __CCSCHEDULER_H__

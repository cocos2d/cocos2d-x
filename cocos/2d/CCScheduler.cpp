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

#include "CCScheduler.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "utlist.h"
#include "ccCArray.h"
#include "CCArray.h"
#include "CCScriptSupport.h"

using namespace std;

NS_CC_BEGIN

long schedule_selector_to_key(SEL_SCHEDULE selector)
{
    static union{
        SEL_SCHEDULE func;
        long key;
    };
    func = selector;
    return key;
}

// data structures

// A list double-linked list used for "updates with priority"
typedef struct _listEntry
{
    struct _listEntry   *prev, *next;
    void                *target;
    ccSchedulerFunc     callback;
    int                 priority;
    bool                paused;
    bool                markedForDeletion; // selector will no longer be called and entry will be removed at end of the next tick
} tListEntry;

typedef struct _hashUpdateEntry
{
    tListEntry          **list;        // Which list does it belong to ?
    tListEntry          *entry;        // entry in the list
    void                *target;
    ccSchedulerFunc     callback;
    UT_hash_handle      hh;
} tHashUpdateEntry;

// Hash Element used for "selectors with interval"
typedef struct _hashSelectorEntry
{
    ccArray             *timers;
    void                *target;
    int                 timerIndex;
    Timer               *currentTimer;
    bool                currentTimerSalvaged;
    bool                paused;
    UT_hash_handle      hh;
} tHashTimerEntry;

// implementation Timer

Timer::Timer()
: _target(nullptr)
, _elapsed(-1)
, _runForever(false)
, _useDelay(false)
, _timesExecuted(0)
, _repeat(0)
, _delay(0.0f)
, _interval(0.0f)
, _callback(nullptr)
, _key(0)
#if CC_ENABLE_SCRIPT_BINDING
, _scriptHandler(0)
#endif
{
}

Timer* Timer::create(const ccSchedulerFunc& callback, void *target, long key, float seconds/* = 0 */)
{
    Timer *timer = new Timer();

    timer->initWithTarget(callback, target, key, seconds, kRepeatForever, 0.0f);
    timer->autorelease();

    return timer;
}

#if CC_ENABLE_SCRIPT_BINDING
Timer* Timer::createWithScriptHandler(int handler, float seconds)
{
    Timer *timer = new Timer();

    timer->initWithScriptHandler(handler, seconds);
    timer->autorelease();

    return timer;
}

bool Timer::initWithScriptHandler(int handler, float seconds)
{
    _scriptHandler = handler;
    _elapsed = -1;
    _interval = seconds;

    return true;
}
#endif

bool Timer::initWithTarget(const ccSchedulerFunc& callback, void *target, long key, float seconds, unsigned int repeat, float delay)
{
    _target = target;
    _callback = callback;
    _key = key;
    _elapsed = -1;
    _interval = seconds;
    _delay = delay;
    _useDelay = (delay > 0.0f) ? true : false;
    _repeat = repeat;
    _runForever = (repeat == kRepeatForever) ? true : false;
    return true;
}

void Timer::update(float dt)
{
    if (_elapsed == -1)
    {
        _elapsed = 0;
        _timesExecuted = 0;
    }
    else
    {
        if (_runForever && !_useDelay)
        {//standard timer usage
            _elapsed += dt;
            if (_elapsed >= _interval)
            {
                if (_target && _key != 0 && _callback)
                {
                    _callback(_elapsed);
                }
#if CC_ENABLE_SCRIPT_BINDING
                if (0 != _scriptHandler)
                {
                    SchedulerScriptData data(_scriptHandler,_elapsed);
                    ScriptEvent event(kScheduleEvent,&data);
                    ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
                }
#endif
                _elapsed = 0;
            }
        }    
        else
        {//advanced usage
            _elapsed += dt;
            if (_useDelay)
            {
                if( _elapsed >= _delay )
                {
                    if (_target && _key != 0 && _callback)
                    {
                        _callback(_elapsed);
                    }

#if CC_ENABLE_SCRIPT_BINDING
                    if (0 != _scriptHandler)
                    {
                        SchedulerScriptData data(_scriptHandler,_elapsed);
                        ScriptEvent event(kScheduleEvent,&data);
                        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
                    }
#endif
                    _elapsed = _elapsed - _delay;
                    _timesExecuted += 1;
                    _useDelay = false;
                }
            }
            else
            {
                if (_elapsed >= _interval)
                {
                    if (_target && _key != 0 && _callback)
                    {
                        _callback(_elapsed);
                    }

#if CC_ENABLE_SCRIPT_BINDING
                    if (0 != _scriptHandler)
                    {
                        SchedulerScriptData data(_scriptHandler,_elapsed);
                        ScriptEvent event(kScheduleEvent,&data);
                        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
                    }
#endif
                    
                    _elapsed = 0;
                    _timesExecuted += 1;

                }
            }

            if (!_runForever && _timesExecuted > _repeat)
            {    //unschedule timer
                Director::getInstance()->getScheduler()->unschedule(_target, _key);
            }
        }
    }
}

// implementation of Scheduler

// Priority level reserved for system services.
const int Scheduler::PRIORITY_SYSTEM = INT_MIN;

// Minimum priority level for user scheduling.
const int Scheduler::PRIORITY_NON_SYSTEM_MIN = PRIORITY_SYSTEM + 1;

Scheduler::Scheduler(void)
: _timeScale(1.0f)
, _updatesNegList(nullptr)
, _updates0List(nullptr)
, _updatesPosList(nullptr)
, _hashForUpdates(nullptr)
, _hashForTimers(nullptr)
, _currentTarget(nullptr)
, _currentTargetSalvaged(false)
, _updateHashLocked(false)
#if CC_ENABLE_SCRIPT_BINDING
, _scriptHandlerEntries(20)
#endif
{
    // I don't expect to have more than 30 functions to all per frame
    _functionsToPerform.reserve(30);
}

Scheduler::~Scheduler(void)
{
    unscheduleAll();
}

void Scheduler::removeHashElement(_hashSelectorEntry *element)
{
    ccArrayFree(element->timers);
    HASH_DEL(_hashForTimers, element);
    free(element);
}

void Scheduler::schedule(const ccSchedulerFunc& callback, void *target, long key, float interval, bool paused)
{
    this->schedule(callback, target, key, interval, kRepeatForever, 0.0f, paused);
}

void Scheduler::schedule(const ccSchedulerFunc& callback, void *target, long key, float interval, unsigned int repeat, float delay, bool paused)
{
    CCASSERT(target, "Argument target must be non-nullptr");
    CCASSERT(key != 0, "key should not be empty!");

    tHashTimerEntry *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);

    if (! element)
    {
        element = (tHashTimerEntry *)calloc(sizeof(*element), 1);
        element->target = target;

        HASH_ADD_PTR(_hashForTimers, target, element);

        // Is this the 1st element ? Then set the pause level to all the selectors of this target
        element->paused = paused;
    }
    else
    {
        CCASSERT(element->paused == paused, "");
    }

    if (element->timers == nullptr)
    {
        element->timers = ccArrayNew(10);
    }
    else 
    {
        for (int i = 0; i < element->timers->num; ++i)
        {
            Timer *timer = (Timer*)element->timers->arr[i];

            if (key == timer->getKey())
            {
                CCLOG("CCScheduler#scheduleSelector. Selector already scheduled. Updating interval from: %.4f to %.4f", timer->getInterval(), interval);
                timer->setInterval(interval);
                return;
            }        
        }
        ccArrayEnsureExtraCapacity(element->timers, 1);
    }

    Timer *timer = new Timer();
    timer->initWithTarget(callback, target, key, interval, repeat, delay);
    ccArrayAppendObject(element->timers, timer);
    timer->release();
}

void Scheduler::unschedule(void *target, long key)
{
    // explicity handle nil arguments when removing an object
    if (target == nullptr || key == 0)
    {
        return;
    }

    //CCASSERT(target);
    //CCASSERT(selector);

    tHashTimerEntry *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);

    if (element)
    {
        for (int i = 0; i < element->timers->num; ++i)
        {
            Timer *timer = static_cast<Timer*>(element->timers->arr[i]);

            if (key == timer->getKey())
            {
                if (timer == element->currentTimer && (! element->currentTimerSalvaged))
                {
                    element->currentTimer->retain();
                    element->currentTimerSalvaged = true;
                }

                ccArrayRemoveObjectAtIndex(element->timers, i, true);

                // update timerIndex in case we are in tick:, looping over the actions
                if (element->timerIndex >= i)
                {
                    element->timerIndex--;
                }

                if (element->timers->num == 0)
                {
                    if (_currentTarget == element)
                    {
                        _currentTargetSalvaged = true;
                    }
                    else
                    {
                        removeHashElement(element);
                    }
                }

                return;
            }
        }
    }
}

void Scheduler::priorityIn(tListEntry **list, const ccSchedulerFunc& callback, void *target, int priority, bool paused)
{
    tListEntry *listElement = new tListEntry();

    listElement->callback = callback;
    listElement->target = target;
    listElement->priority = priority;
    listElement->paused = paused;
    listElement->next = listElement->prev = nullptr;
    listElement->markedForDeletion = false;

    // empty list ?
    if (! *list)
    {
        DL_APPEND(*list, listElement);
    }
    else
    {
        bool added = false;

        for (tListEntry *element = *list; element; element = element->next)
        {
            if (priority < element->priority)
            {
                if (element == *list)
                {
                    DL_PREPEND(*list, listElement);
                }
                else
                {
                    listElement->next = element;
                    listElement->prev = element->prev;

                    element->prev->next = listElement;
                    element->prev = listElement;
                }

                added = true;
                break;
            }
        }

        // Not added? priority has the higher value. Append it.
        if (! added)
        {
            DL_APPEND(*list, listElement);
        }
    }

    // update hash entry for quick access
    tHashUpdateEntry *hashElement = (tHashUpdateEntry *)calloc(sizeof(*hashElement), 1);
    hashElement->target = target;
    hashElement->list = list;
    hashElement->entry = listElement;
    HASH_ADD_PTR(_hashForUpdates, target, hashElement);
}

void Scheduler::appendIn(_listEntry **list, const ccSchedulerFunc& callback, void *target, bool paused)
{
    tListEntry *listElement = new tListEntry();

    listElement->callback = callback;
    listElement->target = target;
    listElement->paused = paused;
    listElement->markedForDeletion = false;

    DL_APPEND(*list, listElement);

    // update hash entry for quicker access
    tHashUpdateEntry *hashElement = (tHashUpdateEntry *)calloc(sizeof(*hashElement), 1);
    hashElement->target = target;
    hashElement->list = list;
    hashElement->entry = listElement;
    HASH_ADD_PTR(_hashForUpdates, target, hashElement);
}

void Scheduler::scheduleUpdate(const ccSchedulerFunc& callback, void *target, int priority, bool paused)
{
    tHashUpdateEntry *hashElement = nullptr;
    HASH_FIND_PTR(_hashForUpdates, &target, hashElement);
    if (hashElement)
    {
#if COCOS2D_DEBUG >= 1
        CCASSERT(hashElement->entry->markedForDeletion,"");
#endif
        // TODO: check if priority has changed!

        hashElement->entry->markedForDeletion = false;
        return;
    }

    // most of the updates are going to be 0, that's way there
    // is an special list for updates with priority 0
    if (priority == 0)
    {
        appendIn(&_updates0List, callback, target, paused);
    }
    else if (priority < 0)
    {
        priorityIn(&_updatesNegList, callback, target, priority, paused);
    }
    else
    {
        // priority > 0
        priorityIn(&_updatesPosList, callback, target, priority, paused);
    }
}

bool Scheduler::isScheduled(void *target, long key)
{
    CCASSERT(key != 0, "Argument key must be empty");
    CCASSERT(target, "Argument target must be non-nullptr");
    
    tHashTimerEntry *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);
    
    if (!element)
    {
        return false;
    }
    
    if (element->timers == nullptr)
    {
        return false;
    }else
    {
        for (int i = 0; i < element->timers->num; ++i)
        {
            Timer *timer = (Timer*)element->timers->arr[i];
            
            if (key == timer->getKey())
            {
                return true;
            }
        }
        
        return false;
    }
    
    return false;  // should never get here
}

void Scheduler::removeUpdateFromHash(struct _listEntry *entry)
{
    tHashUpdateEntry *element = nullptr;

    HASH_FIND_PTR(_hashForUpdates, &entry->target, element);
    if (element)
    {
        // list entry
        DL_DELETE(*element->list, element->entry);
        CC_SAFE_DELETE(element->entry);

        // hash entry
        HASH_DEL(_hashForUpdates, element);
        free(element);
    }
}

void Scheduler::unscheduleUpdate(void* target)
{
    if (target == nullptr)
    {
        return;
    }

    tHashUpdateEntry *element = nullptr;
    HASH_FIND_PTR(_hashForUpdates, &target, element);
    if (element)
    {
        if (_updateHashLocked)
        {
            element->entry->markedForDeletion = true;
        }
        else
        {
            this->removeUpdateFromHash(element->entry);
        }
    }
}

void Scheduler::unscheduleAll(void)
{
    unscheduleAllWithMinPriority(PRIORITY_SYSTEM);
}

void Scheduler::unscheduleAllWithMinPriority(int minPriority)
{
    // Custom Selectors
    tHashTimerEntry *element = nullptr;
    tHashTimerEntry *nextElement = nullptr;
    for (element = _hashForTimers; element != nullptr;)
    {
        // element may be removed in unscheduleAllSelectorsForTarget
        nextElement = (tHashTimerEntry *)element->hh.next;
        unscheduleAllForTarget(element->target);

        element = nextElement;
    }

    // Updates selectors
    tListEntry *entry, *tmp;
    if(minPriority < 0)
    {
        DL_FOREACH_SAFE(_updatesNegList, entry, tmp)
        {
            if(entry->priority >= minPriority)
            {
                unscheduleUpdate(entry->target);
            }
        }
    }

    if(minPriority <= 0)
    {
        DL_FOREACH_SAFE(_updates0List, entry, tmp)
        {
            unscheduleUpdate(entry->target);
        }
    }

    DL_FOREACH_SAFE(_updatesPosList, entry, tmp)
    {
        if(entry->priority >= minPriority)
        {
            unscheduleUpdate(entry->target);
        }
    }
#if CC_ENABLE_SCRIPT_BINDING
    _scriptHandlerEntries.clear();
#endif
}

void Scheduler::unscheduleAllForTarget(void *target)
{
    // explicit nullptr handling
    if (target == nullptr)
    {
        return;
    }

    // Custom Selectors
    tHashTimerEntry *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);

    if (element)
    {
        if (ccArrayContainsObject(element->timers, element->currentTimer)
            && (! element->currentTimerSalvaged))
        {
            element->currentTimer->retain();
            element->currentTimerSalvaged = true;
        }
        ccArrayRemoveAllObjects(element->timers);

        if (_currentTarget == element)
        {
            _currentTargetSalvaged = true;
        }
        else
        {
            removeHashElement(element);
        }
    }

    // update selector
    unscheduleUpdate(target);
}

#if CC_ENABLE_SCRIPT_BINDING
unsigned int Scheduler::scheduleScriptFunc(unsigned int handler, float interval, bool paused)
{
    SchedulerScriptHandlerEntry* entry = SchedulerScriptHandlerEntry::create(handler, interval, paused);
    _scriptHandlerEntries.pushBack(entry);
    return entry->getEntryId();
}

void Scheduler::unscheduleScriptEntry(unsigned int scheduleScriptEntryID)
{
    for (ssize_t i = _scriptHandlerEntries.size() - 1; i >= 0; i--)
    {
        SchedulerScriptHandlerEntry* entry = _scriptHandlerEntries.at(i);
        if (entry->getEntryId() == (int)scheduleScriptEntryID)
        {
            entry->markedForDeletion();
            break;
        }
    }
}

#endif

void Scheduler::resumeTarget(void *target)
{
    CCASSERT(target != nullptr, "");

    // custom selectors
    tHashTimerEntry *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);
    if (element)
    {
        element->paused = false;
    }

    // update selector
    tHashUpdateEntry *elementUpdate = nullptr;
    HASH_FIND_PTR(_hashForUpdates, &target, elementUpdate);
    if (elementUpdate)
    {
        CCASSERT(elementUpdate->entry != nullptr, "");
        elementUpdate->entry->paused = false;
    }
}

void Scheduler::pauseTarget(void *target)
{
    CCASSERT(target != nullptr, "");

    // custom selectors
    tHashTimerEntry *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);
    if (element)
    {
        element->paused = true;
    }

    // update selector
    tHashUpdateEntry *elementUpdate = nullptr;
    HASH_FIND_PTR(_hashForUpdates, &target, elementUpdate);
    if (elementUpdate)
    {
        CCASSERT(elementUpdate->entry != nullptr, "");
        elementUpdate->entry->paused = true;
    }
}

bool Scheduler::isTargetPaused(void *target)
{
    CCASSERT( target != nullptr, "target must be non nil" );

    // Custom selectors
    tHashTimerEntry *element = nullptr;
    HASH_FIND_PTR(_hashForTimers, &target, element);
    if( element )
    {
        return element->paused;
    }
    
    // We should check update selectors if target does not have custom selectors
	tHashUpdateEntry *elementUpdate = nullptr;
	HASH_FIND_PTR(_hashForUpdates, &target, elementUpdate);
	if ( elementUpdate )
    {
		return elementUpdate->entry->paused;
    }
    
    return false;  // should never get here
}

std::set<void*> Scheduler::pauseAllTargets()
{
    return pauseAllTargetsWithMinPriority(PRIORITY_SYSTEM);
}

std::set<void*> Scheduler::pauseAllTargetsWithMinPriority(int minPriority)
{
    std::set<void*> idsWithSelectors;

    // Custom Selectors
    for(tHashTimerEntry *element = _hashForTimers; element != nullptr;
        element = (tHashTimerEntry*)element->hh.next)
    {
        element->paused = true;
        idsWithSelectors.insert(element->target);
    }

    // Updates selectors
    tListEntry *entry, *tmp;
    if(minPriority < 0)
    {
        DL_FOREACH_SAFE( _updatesNegList, entry, tmp ) 
        {
            if(entry->priority >= minPriority)
            {
                entry->paused = true;
                idsWithSelectors.insert(entry->target);
            }
        }
    }

    if(minPriority <= 0)
    {
        DL_FOREACH_SAFE( _updates0List, entry, tmp )
        {
            entry->paused = true;
            idsWithSelectors.insert(entry->target);
        }
    }

    DL_FOREACH_SAFE( _updatesPosList, entry, tmp ) 
    {
        if(entry->priority >= minPriority) 
        {
            entry->paused = true;
            idsWithSelectors.insert(entry->target);
        }
    }

    return idsWithSelectors;
}

void Scheduler::resumeTargets(const std::set<void*>& targetsToResume)
{
    for(const auto &obj : targetsToResume) {
        this->resumeTarget(obj);
    }
}

void Scheduler::performFunctionInCocosThread(const std::function<void ()> &function)
{
    _performMutex.lock();

    _functionsToPerform.push_back(function);

    _performMutex.unlock();
}

// main loop
void Scheduler::update(float dt)
{
    _updateHashLocked = true;

    if (_timeScale != 1.0f)
    {
        dt *= _timeScale;
    }

    //
    // Selector callbacks
    //

    // Iterate over all the Updates' selectors
    tListEntry *entry, *tmp;

    // updates with priority < 0
    DL_FOREACH_SAFE(_updatesNegList, entry, tmp)
    {
        if ((! entry->paused) && (! entry->markedForDeletion))
        {
            entry->callback(dt);
        }
    }

    // updates with priority == 0
    DL_FOREACH_SAFE(_updates0List, entry, tmp)
    {
        if ((! entry->paused) && (! entry->markedForDeletion))
        {
            entry->callback(dt);
        }
    }

    // updates with priority > 0
    DL_FOREACH_SAFE(_updatesPosList, entry, tmp)
    {
        if ((! entry->paused) && (! entry->markedForDeletion))
        {
            entry->callback(dt);
        }
    }

    // Iterate over all the custom selectors
    for (tHashTimerEntry *elt = _hashForTimers; elt != nullptr; )
    {
        _currentTarget = elt;
        _currentTargetSalvaged = false;

        if (! _currentTarget->paused)
        {
            // The 'timers' array may change while inside this loop
            for (elt->timerIndex = 0; elt->timerIndex < elt->timers->num; ++(elt->timerIndex))
            {
                elt->currentTimer = (Timer*)(elt->timers->arr[elt->timerIndex]);
                elt->currentTimerSalvaged = false;

                elt->currentTimer->update(dt);

                if (elt->currentTimerSalvaged)
                {
                    // The currentTimer told the remove itself. To prevent the timer from
                    // accidentally deallocating itself before finishing its step, we retained
                    // it. Now that step is done, it's safe to release it.
                    elt->currentTimer->release();
                }

                elt->currentTimer = nullptr;
            }
        }

        // elt, at this moment, is still valid
        // so it is safe to ask this here (issue #490)
        elt = (tHashTimerEntry *)elt->hh.next;

        // only delete currentTarget if no actions were scheduled during the cycle (issue #481)
        if (_currentTargetSalvaged && _currentTarget->timers->num == 0)
        {
            removeHashElement(_currentTarget);
        }
    }

    // delete all updates that are marked for deletion
    // updates with priority < 0
    DL_FOREACH_SAFE(_updatesNegList, entry, tmp)
    {
        if (entry->markedForDeletion)
        {
            this->removeUpdateFromHash(entry);
        }
    }

    // updates with priority == 0
    DL_FOREACH_SAFE(_updates0List, entry, tmp)
    {
        if (entry->markedForDeletion)
        {
            this->removeUpdateFromHash(entry);
        }
    }

    // updates with priority > 0
    DL_FOREACH_SAFE(_updatesPosList, entry, tmp)
    {
        if (entry->markedForDeletion)
        {
            this->removeUpdateFromHash(entry);
        }
    }

    _updateHashLocked = false;
    _currentTarget = nullptr;

#if CC_ENABLE_SCRIPT_BINDING
    //
    // Script callbacks
    //

    // Iterate over all the script callbacks
    if (!_scriptHandlerEntries.empty())
    {
        for (auto i = _scriptHandlerEntries.size() - 1; i >= 0; i--)
        {
            SchedulerScriptHandlerEntry* eachEntry = _scriptHandlerEntries.at(i);
            if (eachEntry->isMarkedForDeletion())
            {
                _scriptHandlerEntries.erase(i);
            }
            else if (!eachEntry->isPaused())
            {
                eachEntry->getTimer()->update(dt);
            }
        }
    }
#endif
    //
    // Functions allocated from another thread
    //

    // Testing size is faster than locking / unlocking.
    // And almost never there will be functions scheduled to be called.
    if( !_functionsToPerform.empty() ) {
        _performMutex.lock();
        for( const auto &function : _functionsToPerform ) {
            function();
        }
        _functionsToPerform.clear();
        _performMutex.unlock();
    }
}

//OLD METHODS:
void Scheduler::scheduleSelector(SEL_SCHEDULE selector, Ref *target, float interval, unsigned int repeat, float delay, bool paused)
{
    target->retain();
    this->schedule([=](float dt){
        (target->*selector)(dt);
    }, target, schedule_selector_to_key(selector), interval , repeat, delay, paused);
}

void Scheduler::scheduleSelector(SEL_SCHEDULE selector, Ref *target, float interval, bool paused)
{
    target->retain();
    this->schedule([=](float dt){
        (target->*selector)(dt);
    }, target, schedule_selector_to_key(selector), interval, paused);
}

bool Scheduler::isScheduledForTarget(SEL_SCHEDULE selector, Ref *target)
{
    return this->isScheduled(target, schedule_selector_to_key(selector));
}

void Scheduler::unscheduleSelector(SEL_SCHEDULE selector, Ref *target)
{
    this->unschedule(target, schedule_selector_to_key(selector));
    target->release();
}

void Scheduler::unscheduleUpdateForTarget(Ref *target)
{
    this->unscheduleUpdate(target);
    target->release();
};

NS_CC_END

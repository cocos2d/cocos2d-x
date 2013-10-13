/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

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
#include "CCEventDispatcher.h"
#include "CCEvent.h"
#include "CCEventTouch.h"
#include "CCEventListenerTouch.h"
#include "base_nodes/CCNode.h"
#include "CCDirector.h"

#include <algorithm>


#define DUMP_LISTENER_ITEM_PRIORITY_INFO 0

namespace
{

class DispatchGuard
{
public:
    DispatchGuard(int& count):
            _count(count)
    {
        ++_count;
    }

    ~DispatchGuard()
    {
        --_count;
    }

private:
    int& _count;
};

}

NS_CC_BEGIN

static EventDispatcher* g_instance = nullptr;

EventDispatcher::EventListenerItem::~EventListenerItem()
{
    CC_SAFE_RELEASE(this->node);
}

EventDispatcher::EventDispatcher()
: _inDispatch(0)
, _isEnabled(true)
{
    _toAddedListeners.reserve(50);
}

EventDispatcher::~EventDispatcher()
{
    removeAllListeners();
}

EventDispatcher* EventDispatcher::getInstance()
{
    if (g_instance == nullptr)
    {
        g_instance = new EventDispatcher();
    }
    
    return g_instance;
}

void EventDispatcher::destroyInstance()
{
    CC_SAFE_DELETE(g_instance);
}

void EventDispatcher::addEventListenerWithItem(EventListenerItem* item)
{
    if (_inDispatch == 0)
    {
        std::vector<EventListenerItem*>* listenerList = nullptr;
        
        auto iter = _listeners.find(item->listener->_type);
        if (iter == _listeners.end())
        {
            listenerList = new std::vector<EventListenerItem*>();
            listenerList->reserve(100);
            _listeners.insert(std::make_pair(item->listener->_type, listenerList));
        }
        else
        {
            listenerList = iter->second;
        }

        listenerList->insert(listenerList->begin(), item);

        setDirtyForEventType(item->listener->_type, true);
    }
    else
    {
        _toAddedListeners.push_back(item);
    }
}

void EventDispatcher::addEventListenerWithSceneGraphPriority(EventListener* listener, Node* node)
{
    CCASSERT(listener && node, "Invalid parameters.");
    CCASSERT(!listener->_isRegistered, "The listener has been registered.");
    
    if (!listener->checkAvaiable())
        return;
    
    auto item = new EventListenerItem();
    item->node          = node;
    item->node->retain();
    item->fixedPriority = 0;
    item->listener      = listener;
    item->listener->retain();
    item->listener->_isRegistered = true;

    addEventListenerWithItem(item);

    node->associateEventListener(listener);
}

void EventDispatcher::addEventListenerWithFixedPriority(EventListener* listener, int fixedPriority)
{
    CCASSERT(listener, "Invalid parameters.");
    CCASSERT(!listener->_isRegistered, "The listener has been registered.");
    CCASSERT(fixedPriority != 0, "0 priority is forbidden for fixed priority since it's used for scene graph based priority.");
    
    if (!listener->checkAvaiable())
        return;
    
    auto item = new EventListenerItem();
    item->node          = nullptr;
    item->fixedPriority = fixedPriority;
    item->listener      = listener;
    item->listener->retain();
    item->listener->_isRegistered = true;

    addEventListenerWithItem(item);
}

void EventDispatcher::removeEventListener(EventListener* listener)
{
    if (listener == nullptr)
        return;

    bool isFound = false;

    for (auto iter = _listeners.begin(); iter != _listeners.end();)
    {
        for (auto itemIter = iter->second->begin(); itemIter != iter->second->end(); ++itemIter)
        {
            if ((*itemIter)->listener == listener)
            {
                CC_SAFE_RETAIN(listener);
                (*itemIter)->listener->_isRegistered = false;
                if ((*itemIter)->node != nullptr)
                {
                    (*itemIter)->node->dissociateEventListener(listener);
                }
                
                (*itemIter)->listener->release();
                if (_inDispatch == 0)
                {
                    delete (*itemIter);
                    iter->second->erase(itemIter);
                }
                else
                {
                    (*itemIter)->listener = nullptr;
                }

                isFound = true;
                break;
            }
        }

        if (iter->second->empty())
        {
            _priorityDirtyFlagMap.erase(listener->_type);
            auto list = iter->second;
            iter = _listeners.erase(iter);
            CC_SAFE_DELETE(list);
        }
        else
        {
            ++iter;
        }
        
        if (isFound)
            break;
    }

    if (isFound)
    {
        CC_SAFE_RELEASE(listener);
    }
}

void EventDispatcher::setPriority(EventListener* listener, int fixedPriority)
{
    if (listener == nullptr)
        return;
    
    for (auto iter = _listeners.begin(); iter != _listeners.end(); ++iter)
    {
        for (auto itemIter = iter->second->begin(); itemIter != iter->second->end(); ++itemIter)
        {
            auto item = *itemIter;
            if (item->listener == listener)
            {
                CCASSERT(item->node, "Can't set fixed priority with scene graph based listener.");
                
                if (item->fixedPriority != fixedPriority)
                {
                    item->fixedPriority = fixedPriority;
                    setDirtyForEventType(listener->_type, true);
                }
                return;
            }
        }
    }
}

void EventDispatcher::dispatchEvent(Event* event, bool forceSortListeners)
{
    if (!_isEnabled)
        return;
    
    bool isDirty = false;
    auto dirtyIter = _priorityDirtyFlagMap.find(event->_type);
    if (dirtyIter != _priorityDirtyFlagMap.end())
    {
        isDirty = dirtyIter->second;
    }
    
    if (forceSortListeners || isDirty)
    {
        sortAllEventListenerItemsForType(event->_type);
        // Sets the dirty flag to false
        if (isDirty)
        {
            dirtyIter->second = false;
        }
    }

    DispatchGuard guard(_inDispatch);

    if (event->_type == EventTouch::EVENT_TYPE)
    {
        dispatchTouchEvent(static_cast<EventTouch*>(event));
        return;
    }
    
    auto iter = _listeners.find(event->getType());
    if (iter != _listeners.end())
    {
        auto listenerList = iter->second;
        for (auto& item : *listenerList)
        {
            CCASSERT(item, "listener item is invalid.");

            event->setCurrentTarget(item->node);
            item->listener->_onEvent(event);

            if (event->isStopped())
                break;
        }
    }
    
    updateListenerItems();
}

void EventDispatcher::dispatchTouchEvent(EventTouch* event)
{
    auto touchListeners = getListenerItemsForType(EventTouch::EVENT_TYPE);
    if (touchListeners == nullptr)
        return;
    
    std::vector<EventDispatcher::EventListenerItem*> oneByOnelisteners;
    oneByOnelisteners.reserve(touchListeners->size());
    
    std::vector<EventDispatcher::EventListenerItem*> allInOnelisteners;
    allInOnelisteners.reserve(touchListeners->size());
    
    EventListenerTouch* touchEventListener = nullptr;
    
    std::for_each(touchListeners->begin(), touchListeners->end(), [&](EventListenerItem*& item){

        touchEventListener = static_cast<EventListenerTouch*>(item->listener);
        
        if (touchEventListener->_dispatchMode == Touch::DispatchMode::ONE_BY_ONE)
        {
            oneByOnelisteners.push_back(item);
        }
        else if (touchEventListener->_dispatchMode == Touch::DispatchMode::ALL_AT_ONCE)
        {
            allInOnelisteners.push_back(item);
        }
        else
        {
            CCASSERT(false, "Not supported touch listener type.");
        }
    });
    
    bool isNeedsMutableSet = (oneByOnelisteners.size() > 0 && allInOnelisteners.size() > 0);
    
    std::vector<Touch*> orignalTouches = event->getTouches();
    std::vector<Touch*> mutableTouches(orignalTouches.size());
    std::copy(orignalTouches.begin(), orignalTouches.end(), mutableTouches.begin());
    
    //
    // process the target handlers 1st
    //
    if (oneByOnelisteners.size() > 0)
    {
        auto mutableTouchesIter = mutableTouches.begin();
        auto touchesIter = orignalTouches.begin();
        
        for (; touchesIter != orignalTouches.end(); ++touchesIter)
        {
            bool isSwallowed = false;

            for (auto& item : oneByOnelisteners)
            {
                // Skip if the listener was removed.
                if (item->listener == nullptr)
                    continue;
             
                event->setCurrentTarget(item->node);
                
                bool isClaimed = false;
                std::vector<Touch*>::iterator removedIter;
                
                auto touchEventListener = static_cast<EventListenerTouch*>(item->listener);
                EventTouch::EventCode eventCode = event->getEventCode();
                
                if (eventCode == EventTouch::EventCode::BEGAN)
                {
                    if (touchEventListener->onTouchBegan)
                    {
                        isClaimed = touchEventListener->onTouchBegan(*touchesIter, event);
                        if (isClaimed && item->listener)
                        {
                            touchEventListener->_claimedTouches.push_back(*touchesIter);
                        }
                    }
                }
                else if (touchEventListener->_claimedTouches.size() > 0
                         && ((removedIter = std::find(touchEventListener->_claimedTouches.begin(), touchEventListener->_claimedTouches.end(), *touchesIter)) != touchEventListener->_claimedTouches.end()))
                {
                    isClaimed = true;
                    
                    switch (eventCode)
                    {
                        case EventTouch::EventCode::MOVED:
                            if (touchEventListener->onTouchMoved)
                            {
                                touchEventListener->onTouchMoved(*touchesIter, event);
                            }
                            break;
                        case EventTouch::EventCode::ENDED:
                            if (touchEventListener->onTouchEnded)
                            {
                                touchEventListener->onTouchEnded(*touchesIter, event);
                            }
                            if (item->listener)
                            {
                                touchEventListener->_claimedTouches.erase(removedIter);
                            }
                            break;
                        case EventTouch::EventCode::CANCELLED:
                            if (touchEventListener->onTouchCancelled)
                            {
                                touchEventListener->onTouchCancelled(*touchesIter, event);
                            }
                            if (item->listener)
                            {
                                touchEventListener->_claimedTouches.erase(removedIter);
                            }
                            break;
                        default:
                            CCASSERT(false, "The eventcode is invalid.");
                            break;
                    }
                }
                
                // If the event was stopped, return directly.
                if (event->isStopped())
                {
                    updateListenerItems();
                    return;
                }
                
                CCASSERT((*touchesIter)->getID() == (*mutableTouchesIter)->getID(), "");
                
                if (isClaimed && item->listener && touchEventListener->_needSwallow)
                {
                    if (isNeedsMutableSet)
                    {
                        mutableTouchesIter = mutableTouches.erase(mutableTouchesIter);
                        isSwallowed = true;
                    }
                    break;
                }
            }
            
            if (!isSwallowed)
                ++mutableTouchesIter;
        }
    }
    
    //
    // process standard handlers 2nd
    //
    if (allInOnelisteners.size() > 0 && mutableTouches.size() > 0)
    {
        for (auto& item : allInOnelisteners)
        {
            // Skip if the listener was removed.
            if (item->listener == nullptr)
                continue;
            
            event->setCurrentTarget(item->node);
            
            auto touchEventListener = static_cast<EventListenerTouch*>(item->listener);
            
            switch (event->getEventCode())
            {
                case EventTouch::EventCode::BEGAN:
                    if (touchEventListener->onTouchesBegan)
                    {
                        touchEventListener->onTouchesBegan(mutableTouches, event);
                    }
                    break;
                case EventTouch::EventCode::MOVED:
                    if (touchEventListener->onTouchesMoved)
                    {
                        touchEventListener->onTouchesMoved(mutableTouches, event);
                    }
                    break;
                case EventTouch::EventCode::ENDED:
                    if (touchEventListener->onTouchesEnded)
                    {
                        touchEventListener->onTouchesEnded(mutableTouches, event);
                    }
                    break;
                case EventTouch::EventCode::CANCELLED:
                    if (touchEventListener->onTouchesCancelled)
                    {
                        touchEventListener->onTouchesCancelled(mutableTouches, event);
                    }
                    break;
                default:
                    CCASSERT(false, "The eventcode is invalid.");
                    break;
            }
            
            // If the event was stopped, return directly.
            if (event->isStopped())
            {
                updateListenerItems();
                return;
            }
        }
    }
    
    updateListenerItems();
}

void EventDispatcher::updateListenerItems()
{
    auto listenerItemIter = _listeners.begin();
    while (listenerItemIter != _listeners.end())
    {
        for (auto iter = listenerItemIter->second->begin(); iter != listenerItemIter->second->end();)
        {
            if ((*iter)->listener == nullptr)
            {
                delete (*iter);
                iter = listenerItemIter->second->erase(iter);
            }
            else
            {
                ++iter;
            }
        }
        
        if (listenerItemIter->second->empty())
        {
            _priorityDirtyFlagMap.erase(listenerItemIter->first);
            delete listenerItemIter->second;
            listenerItemIter =  _listeners.erase(listenerItemIter);
        }
        else
        {
            ++listenerItemIter;
        }
    }
    
    if (!_toAddedListeners.empty())
    {
        std::vector<EventListenerItem*>* listenerList = nullptr;
        
        for (auto& item : _toAddedListeners)
        {
            auto itr = _listeners.find(item->listener->_type);
            if (itr == _listeners.end())
            {
                listenerList = new std::vector<EventListenerItem*>();
                listenerList->reserve(100);
                _listeners.insert(std::make_pair(item->listener->_type, listenerList));
            }
            else
            {
                listenerList = itr->second;
            }
            
            listenerList->push_back(item);
            
            setDirtyForEventType(item->listener->_type, true);
        }
        _toAddedListeners.clear();
    }
}

void EventDispatcher::sortAllEventListenerItemsForType(const std::string &eventType)
{
    if (eventType.empty())
        return;
    
    auto listenerList = getListenerItemsForType(eventType);

    if (listenerList == nullptr)
        return;
    
    // After sort: priority < 0, = 0, scene graph, > 0
    std::sort(listenerList->begin(), listenerList->end(), [](const EventListenerItem* item1, const EventListenerItem* item2) {
        
        // item1 and item2 are both using fixed priority.
        if (nullptr == item1->node && nullptr == item2->node)
        {
            return item1->fixedPriority < item2->fixedPriority;
        }
        // item1 and item2 are both using scene graph based priority.
        else if (nullptr != item1->node && nullptr != item2->node)
        {
            return item1->node->getEventPriority() > item2->node->getEventPriority();
        }
        else if (nullptr != item1->node && nullptr == item2->node)
        {
            return 0 < item2->fixedPriority;
        }
        else if (nullptr == item1->node && nullptr != item2->node)
        {
            return item1->fixedPriority <= 0;
        }
        else
        {
            CCASSERT(false, "sort event node error...");
            return false;
        }
    });
    
#if DUMP_LISTENER_ITEM_PRIORITY_INFO
    log("-----------------------------------");
    for (auto& item : *listenerList)
    {
        log("listener item priority: node (%p), fixed (%d)", item->node, item->fixedPriority);
    }    
#endif
    
}

std::vector<EventDispatcher::EventListenerItem*>* EventDispatcher::getListenerItemsForType(const std::string &eventType)
{
    auto iter = _listeners.find(eventType);
    if (iter != _listeners.end())
    {
        return iter->second;
    }
    
    return nullptr;
}

void EventDispatcher::removeListenersForEventType(const std::string& eventType)
{
    if (eventType.empty())
        return;
    
    auto listenerItemIter = _listeners.find(eventType);
    if (listenerItemIter != _listeners.end())
    {
        for (auto iter = listenerItemIter->second->begin(); iter != listenerItemIter->second->end(); ++iter)
        {
            (*iter)->listener->_isRegistered = false;
            if ((*iter)->node != nullptr)
            {
                (*iter)->node->dissociateEventListener((*iter)->listener);
            }
            
            (*iter)->listener->release();
            if (_inDispatch)
            {
                (*iter)->listener = nullptr;
            }
            else
            {
                delete (*iter);
            }
        }
        
        if (!_inDispatch)
        {
            listenerItemIter->second->clear();
            delete listenerItemIter->second;
            _listeners.erase(listenerItemIter);
            _priorityDirtyFlagMap.erase(eventType);
        }
    }
}

void EventDispatcher::removeAllListeners()
{
    for (auto listenerItemIter = _listeners.begin(); listenerItemIter != _listeners.end(); ++listenerItemIter)
    {
        for (auto iter = listenerItemIter->second->begin(); iter != listenerItemIter->second->end(); ++iter)
        {
            (*iter)->listener->_isRegistered = false;
            if ((*iter)->node != nullptr)
            {
                (*iter)->node->dissociateEventListener((*iter)->listener);
            }
            
            (*iter)->listener->release();
            if (_inDispatch)
            {
                (*iter)->listener = nullptr;
            }
            else
            {
                delete (*iter);
            }
        }
        
        if (!_inDispatch)
        {
            listenerItemIter->second->clear();        
            delete listenerItemIter->second;
            
            _priorityDirtyFlagMap.clear();
        }
    }

    if (!_inDispatch)
    {
        _listeners.clear();
    }
}

void EventDispatcher::setEnabled(bool isEnabled)
{
    _isEnabled = isEnabled;
}


bool EventDispatcher::isEnabled() const
{
    return _isEnabled;
}

void EventDispatcher::setDirtyForEventType(const std::string& eventType, bool isDirty)
{
    CCASSERT(!eventType.empty(), "Invalid event type.");
    
    auto iter = _priorityDirtyFlagMap.find(eventType);
    if (iter == _priorityDirtyFlagMap.end())
    {
        _priorityDirtyFlagMap.insert(std::make_pair(eventType, isDirty));
    }
    else
    {
        iter->second = isDirty;
    }
}

bool EventDispatcher::isDirtyForEventType(const std::string& eventType)
{
    bool isDirty = false;
    auto iter = _priorityDirtyFlagMap.find(eventType);
    if (iter != _priorityDirtyFlagMap.end())
    {
        isDirty = iter->second;
    }

    return isDirty;
}

NS_CC_END

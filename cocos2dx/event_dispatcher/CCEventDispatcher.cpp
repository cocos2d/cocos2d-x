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
#include "CCTouchEvent.h"
#include "CCTouchEventListener.h"
#include "base_nodes/CCNode.h"
#include "CCDirector.h"

#include <algorithm>

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


EventDispatcher::EventDispatcher()
: _inDispatch(0)
, _listeners(nullptr)
, _isEnabled(true)
{
}

EventDispatcher::~EventDispatcher()
{
}

EventDispatcher* EventDispatcher::getInstance()
{
    static EventDispatcher _instance;
    return &_instance;
}

void EventDispatcher::addEventListenerWithItem(EventListenerItem* item)
{
    if (!_listeners)
    {
        _listeners = new std::map<std::string, std::vector<EventListenerItem*>*>();
    }

    auto itr = _listeners->find(item->listener->type);
    if (itr == _listeners->end())
    {
        _listeners->insert(std::make_pair(item->listener->type, new std::vector<EventListenerItem*>()));
        itr = _listeners->find(item->listener->type);
    }

    auto listenerList = itr->second;

    listenerList->insert(listenerList->begin(), item);
}

void EventDispatcher::addEventListenerWithSceneGraphPriority(EventListener* listener, Node* node)
{
    CCASSERT(!listener->_isRegistered, "The listener has been registered.");
    
    if (!listener->checkAvaiable())
        return;
    
    EventListenerItem* item = new EventListenerItem();
    item->node          = node;
    item->fixedPriority = 0;
    item->listener      = listener;
    item->listener->retain();
    item->listener->_isRegistered = true;

    addEventListenerWithItem(item);

    _eventNodes.push_back(node);
    node->associateEventListener(listener);
}

void EventDispatcher::addEventListenerWithFixedPriority(EventListener* listener, int fixedPriority)
{
    CCASSERT(!listener->_isRegistered, "The listener has been registered.");
    
    if (!listener->checkAvaiable())
        return;
    
    EventListenerItem* item = new EventListenerItem();
    item->node          = nullptr;
    item->fixedPriority = fixedPriority;
    item->listener      = listener;
    item->listener->retain();
    item->listener->_isRegistered = true;

    addEventListenerWithItem(item);
}

void EventDispatcher::removeEventListener(EventListener* listener)
{
    if (_listeners == nullptr || listener == nullptr)
        return;

    for (auto iter = _listeners->begin(); iter != _listeners->end();)
    {
        for (auto itemIter = iter->second->begin(); itemIter != iter->second->end(); ++itemIter)
        {
            if ((*itemIter)->listener == listener)
            {
                if (_inDispatch == 0)
                {
                    (*itemIter)->listener->release();
                    delete (*itemIter);
                    iter->second->erase(itemIter);
                }
                else
                {
                    (*itemIter)->listener = nullptr;
                }

                break;
            }
        }

        if (iter->second->empty())
        {
            auto list = iter->second;
            iter = _listeners->erase(iter);
            CC_SAFE_DELETE(list);
        }
        else
        {
            ++iter;
        }
    }

    if (_listeners->empty())
    {
        CC_SAFE_DELETE(_listeners);
    }
}

void EventDispatcher::setPriorityWithSceneGraph(EventListener* listener, Node* node)
{
    if (_listeners == nullptr || listener == nullptr || node == nullptr)
        return;

    for (auto iter = _listeners->begin(); iter != _listeners->end(); ++iter)
    {
        for (auto itemIter = iter->second->begin(); itemIter != iter->second->end(); ++itemIter)
        {
            auto item = *itemIter;
            if (item->listener == listener)
            {
                item->fixedPriority = 0;
                item->node = node;
                return;
            }
        }
    }
}

void EventDispatcher::setPriorityWithFixedValue(EventListener* listener, int fixedPriority)
{
    if (_listeners == nullptr || listener == nullptr)
        return;

    for (auto iter = _listeners->begin(); iter != _listeners->end(); ++iter)
    {
        for (auto itemIter = iter->second->begin(); itemIter != iter->second->end(); ++itemIter)
        {
            auto item = *itemIter;
            if (item->listener == listener)
            {
                item->fixedPriority = fixedPriority;
                if (item->node != nullptr)
                {
                    item->node->dissociateEventListener(listener);
                    item->node = nullptr;
                }
                return;
            }
        }
    }
}

void EventDispatcher::dispatchEvent(Event* event, bool toSortListeners)
{
    if (_listeners == nullptr || !_isEnabled)
        return;

    if (toSortListeners)
        sortAllEventListenerItemsForType(event->_type);

    DispatchGuard guard(_inDispatch);

    if (event->_type == TouchEvent::EVENT_TYPE)
    {
        dispatchTouchEvent(static_cast<TouchEvent*>(event));
        return;
    }
    
    if (_listeners)
    {
        auto iter = _listeners->find(event->getType());
        if (iter != _listeners->end())
        {
            auto listenerList = iter->second;
            for (auto listenerIter = listenerList->begin(); listenerIter != listenerList->end(); ++listenerIter)
            {
                CCASSERT(*listenerIter, "listener is invalid.");

                (*listenerIter)->listener->onEvent(event);

                if (event->isStopped())
                    break;
            }
        }
    }
    
    removeUnregisteredListeners();
}

void EventDispatcher::dispatchTouchEvent(TouchEvent* event)
{
    auto touchListeners = getListenerItemsForType(TouchEvent::EVENT_TYPE);
    if (touchListeners == nullptr)
        return;
    
    std::vector<EventDispatcher::EventListenerItem*> oneByOnelisteners;
    oneByOnelisteners.reserve(touchListeners->size());
    
    std::vector<EventDispatcher::EventListenerItem*> allInOnelisteners;
    allInOnelisteners.reserve(touchListeners->size());
    
    for (auto iter = touchListeners->begin(); iter != touchListeners->end(); ++iter)
    {
        auto touchEventListener = static_cast<TouchEventListener*>((*iter)->listener);
        
        if (touchEventListener->_dispatchMode == Touch::DispatchMode::ONE_BY_ONE)
        {
            oneByOnelisteners.push_back(*iter);
        }
        else if (touchEventListener->_dispatchMode == Touch::DispatchMode::ALL_AT_ONCE)
        {
            allInOnelisteners.push_back(*iter);
        }
        else
        {
            CCASSERT(false, "Not supported touch listener type.");
        }
    }
    
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
            auto oneByOneIter = oneByOnelisteners.begin();
            for (; oneByOneIter != oneByOnelisteners.end(); ++oneByOneIter)
            {
                // Skip if the listener was removed.
                if ((*oneByOneIter)->listener == nullptr)
                    continue;
             
                event->setCurrentTarget((*oneByOneIter)->node);
                
                bool isClaimed = false;
                std::vector<Touch*>::iterator removedIter;
                
                auto touchEventListener = static_cast<TouchEventListener*>((*oneByOneIter)->listener);
                TouchEvent::EventCode eventCode = event->getEventCode();
                
                if (eventCode == TouchEvent::EventCode::BEGAN)
                {
                    if (touchEventListener->onTouchBegan)
                    {
                        isClaimed = touchEventListener->onTouchBegan(*touchesIter, event);
                        if (isClaimed)
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
                        case TouchEvent::EventCode::MOVED:
                            if (touchEventListener->onTouchMoved)
                            {
                                touchEventListener->onTouchMoved(*touchesIter, event);
                            }
                            break;
                        case TouchEvent::EventCode::ENDED:
                            if (touchEventListener->onTouchEnded)
                            {
                                touchEventListener->onTouchEnded(*touchesIter, event);
                            }
                            touchEventListener->_claimedTouches.erase(removedIter);
                            break;
                        case TouchEvent::EventCode::CANCELLED:
                            if (touchEventListener->onTouchCancelled)
                            {
                                touchEventListener->onTouchCancelled(*touchesIter, event);
                            }
                            touchEventListener->_claimedTouches.erase(removedIter);
                            break;
                        default:
                            CCASSERT(false, "The eventcode is invalid.");
                            break;
                    }
                }
                
                // If the event was stopped, return directly.
                if (event->isStopped())
                {
                    removeUnregisteredListeners();
                    return;
                }
                
                CCASSERT((*touchesIter)->getID() == (*mutableTouchesIter)->getID(), "");
                
                if (isClaimed && touchEventListener->_needSwallow)
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
        for (auto allInOneIter = allInOnelisteners.begin(); allInOneIter != allInOnelisteners.end(); ++allInOneIter)
        {
            // Skip if the listener was removed.
            if ((*allInOneIter)->listener == nullptr)
                continue;
            
            event->setCurrentTarget((*allInOneIter)->node);
            
            auto touchEventListener = static_cast<TouchEventListener*>((*allInOneIter)->listener);
            
            switch (event->getEventCode())
            {
                case TouchEvent::EventCode::BEGAN:
                    if (touchEventListener->onTouchesBegan)
                    {
                        touchEventListener->onTouchesBegan(mutableTouches, event);
                    }
                    break;
                case TouchEvent::EventCode::MOVED:
                    if (touchEventListener->onTouchesMoved)
                    {
                        touchEventListener->onTouchesMoved(mutableTouches, event);
                    }
                    break;
                case TouchEvent::EventCode::ENDED:
                    if (touchEventListener->onTouchesEnded)
                    {
                        touchEventListener->onTouchesEnded(mutableTouches, event);
                    }
                    break;
                case TouchEvent::EventCode::CANCELLED:
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
                removeUnregisteredListeners();
                return;
            }
        }
    }
    
    removeUnregisteredListeners();
}

void EventDispatcher::removeUnregisteredListeners()
{
    if (!_listeners)
        return;
    
    auto listenerItemIter = _listeners->begin();
    while (listenerItemIter != _listeners->end())
    {
        auto removeIterBegin = std::remove_if(listenerItemIter->second->begin(), listenerItemIter->second->end(), [](const EventListenerItem* item){
            return item->listener == nullptr;
        });
        
        for (auto iter = removeIterBegin; iter != listenerItemIter->second->end(); ++iter)
        {
            delete (*iter);
        }
        
        listenerItemIter->second->erase(removeIterBegin, listenerItemIter->second->end());
        
        if (listenerItemIter->second->empty())
        {
            delete listenerItemIter->second;
            listenerItemIter =  _listeners->erase(listenerItemIter);
        }
        else
        {
            ++listenerItemIter;
        }
    }
    
    if (_listeners->empty())
    {
        delete _listeners;
        _listeners = nullptr;
    }
}

void EventDispatcher::sortAllEventListenerItemsForType(const std::string &eventType)
{
    if (_listeners == nullptr)
        return;
    
    auto listenerList = getListenerItemsForType(eventType);

    // After sort: priority < 0, = 0, scene graph, > 0
    std::sort(listenerList->begin(), listenerList->end(), [](const EventListenerItem* item1, const EventListenerItem* item2) {
        // item1 and item2 are both using fixed priority.
        if (nullptr == item1->node && nullptr == item2->node)
        {
            return item1->fixedPriority > item2->fixedPriority;
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
            return item1->fixedPriority < 0;
        }
        else
        {
            CCASSERT(false, "sort event node error...");
            return false;
        }
    });
}

std::vector<EventDispatcher::EventListenerItem*>* EventDispatcher::getListenerItemsForType(const std::string &eventType)
{
    if (_listeners != nullptr)
    {
        auto iter = _listeners->find(eventType);
        if (iter != _listeners->end())
        {
            return iter->second;
        }
    }
    
    return nullptr;
}

void EventDispatcher::removeListenersForEventType(const std::string& eventType)
{
    if (_listeners == nullptr)
        return;
    
    auto listenerItemIter = _listeners->find(eventType);
    if (listenerItemIter != _listeners->end())
    {
        for (auto iter = listenerItemIter->second->begin(); iter != listenerItemIter->second->end(); ++iter)
        {
            (*iter)->listener->release();
            delete (*iter);
        }
        
        listenerItemIter->second->clear();
        
        delete listenerItemIter->second;
        
        _listeners->erase(listenerItemIter);
    }
}

void EventDispatcher::removeAllListeners()
{
    if (_listeners == nullptr)
        return;
    
    for (auto listenerItemIter = _listeners->begin(); listenerItemIter != _listeners->end(); ++listenerItemIter)
    {
        for (auto iter = listenerItemIter->second->begin(); iter != listenerItemIter->second->end(); ++iter)
        {
            (*iter)->listener->release();
            delete (*iter);
        }
        
        listenerItemIter->second->clear();
    
        delete listenerItemIter->second;
    }

    delete _listeners;
    _listeners = nullptr;
}

void EventDispatcher::setEnabled(bool isEnabled)
{
    _isEnabled = isEnabled;
}


bool EventDispatcher::isEnabled() const
{
    return _isEnabled;
}

NS_CC_END

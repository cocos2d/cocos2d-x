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

int _eventId = 0;

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

void EventDispatcher::registerEventListenerWithItem(EventListenerItem* item)
{
    if (!_listeners)
    {
        _listeners = new std::map<std::string, std::list<EventListenerItem*>*>();
    }

    auto itr = _listeners->find(item->listener->type);
    if (itr == _listeners->end())
    {
        _listeners->insert(std::make_pair(item->listener->type, new std::list<EventListenerItem*>()));
        itr = _listeners->find(item->listener->type);
    }

    auto listenerList = itr->second;

    listenerList->push_front(item);
}

int EventDispatcher::registerEventListenerWithSceneGraphPriority(std::shared_ptr<EventListener> listener, Node* node)
{
    if (!listener->checkAvaiable())
        return 0;

    EventListenerItem* item = new EventListenerItem();
    item->id            = ++_eventId;
    item->node          = node;
    item->fixedPriority = 0;
    item->listener      = listener;

    registerEventListenerWithItem(item);

    _eventNodes.push_back(node);
    node->addEventId(item->id);

    return item->id;
}

int EventDispatcher::registerEventListenerWithFixedPriority(std::shared_ptr<EventListener> listener, int fixedPriority)
{
    if (!listener->checkAvaiable())
        return 0;

    EventListenerItem* item = new EventListenerItem();
    item->id            = ++_eventId;
    item->node          = nullptr;
    item->fixedPriority = fixedPriority;
    item->listener      = listener;

    registerEventListenerWithItem(item);

    return item->id;
}

void EventDispatcher::unregisterEventListener(int listenerId)
{
    if (_listeners == nullptr || listenerId <= 0)
        return;

    for (auto iter = _listeners->begin(); iter != _listeners->end();)
    {
        for (auto itemIter = iter->second->begin(); itemIter != iter->second->end(); ++itemIter)
        {
            if ((*itemIter)->id == listenerId)
            {
                (*itemIter)->id = 0;

                if (_inDispatch == 0)
                {
                    delete (*itemIter);
                    iter->second->remove(*itemIter);
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

void EventDispatcher::setPriorityWithSceneGraph(int listenerId, Node* node)
{
    if (_listeners == nullptr || listenerId <= 0)
        return;

    for (auto iter = _listeners->begin(); iter != _listeners->end(); ++iter)
    {
        for (auto itemIter = iter->second->begin(); itemIter != iter->second->end(); ++itemIter)
        {
            auto item = *itemIter;
            if (item->id == listenerId)
            {
                // FIXME: fixed priority --> scene graph's priority.
                item->fixedPriority = 0;
                item->node = node;
                return;
            }
        }
    }
}

void EventDispatcher::setPriorityWithFixedValue(int listenerId, int fixedPriority)
{
    if (_listeners == nullptr || listenerId <= 0)
        return;

    for (auto iter = _listeners->begin(); iter != _listeners->end(); ++iter)
    {
        for (auto itemIter = iter->second->begin(); itemIter != iter->second->end(); ++itemIter)
        {
            auto item = *itemIter;
            if (item->id == listenerId)
            {
                // FIXME: scene graph's priority --> fixed priority.
                item->fixedPriority = fixedPriority;
                item->node = nullptr;
                return;
            }
        }
    }
}

void EventDispatcher::dispatchEvent(Event* event)
{
    if (_listeners == nullptr || !_isEnabled)
        return;

    sortAllEventListenerItems();

    DispatchGuard guard(_inDispatch);

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

                if ((*listenerIter)->id == 0)
                {
                    delete (*listenerIter);
                    listenerList->remove(*listenerIter);
                }

                if (event->isStopped())
                    break;
            }

            if (listenerList->empty())
            {
                _listeners->erase(iter);
                CC_SAFE_DELETE(listenerList);
            }
        }

        if (_listeners->empty())
        {
            CC_SAFE_DELETE(_listeners);
        }
    }

}

void EventDispatcher::sortAllEventListenerItems()
{
    for (auto listenerItemIter = _listeners->begin(); listenerItemIter != _listeners->end(); ++listenerItemIter)
    {
        // After sort: priority < 0, = 0, scene graph, > 0
        listenerItemIter->second->sort([](const EventListenerItem* item1, const EventListenerItem* item2) {
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
}

std::list<EventDispatcher::EventListenerItem*>* EventDispatcher::getListeners(const std::string& eventType)
{
    auto iter = _listeners->find(eventType);
    if (iter != _listeners->end())
    {
        return iter->second;
    }

    return nullptr;
}

NS_CC_END

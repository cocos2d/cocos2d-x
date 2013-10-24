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
#include "CCNode.h"
#include "CCDirector.h"

#include <algorithm>


#define DUMP_LISTENER_ITEM_PRIORITY_INFO 1

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
static int s_eventPriorityIndex = 0;

EventDispatcher::EventListenerVector::EventListenerVector()
: _sceneGraphListeners(nullptr)
, _fixedListeners(nullptr)
, _gt0Index(0)
{
}

EventDispatcher::EventListenerVector::~EventListenerVector()
{
    CC_SAFE_DELETE(_sceneGraphListeners);
    CC_SAFE_DELETE(_fixedListeners);
}

size_t EventDispatcher::EventListenerVector::size() const
{
    size_t ret = 0;
    if (_sceneGraphListeners)
        ret += _sceneGraphListeners->size();
    if (_fixedListeners)
        ret += _fixedListeners->size();
    
    return ret;
}

bool EventDispatcher::EventListenerVector::empty() const
{
    return (_sceneGraphListeners == nullptr || _sceneGraphListeners->empty())
        && (_fixedListeners == nullptr || _fixedListeners->empty());
}

void EventDispatcher::EventListenerVector::push_back(EventListener* listener)
{
    if (listener->_fixedPriority == 0)
    {
        if (_sceneGraphListeners == nullptr)
        {
            _sceneGraphListeners = new std::vector<EventListener*>();
            _sceneGraphListeners->reserve(100);
        }
        
        _sceneGraphListeners->push_back(listener);
    }
    else
    {
        if (_fixedListeners == nullptr)
        {
            _fixedListeners = new std::vector<EventListener*>();
            _fixedListeners->reserve(100);
        }
        
        _fixedListeners->push_back(listener);
    }
}

void EventDispatcher::EventListenerVector::clearSceneGraphListeners()
{
    if (_sceneGraphListeners)
    {
        _sceneGraphListeners->clear();
        delete _sceneGraphListeners;
        _sceneGraphListeners = nullptr;
    }
}

void EventDispatcher::EventListenerVector::clearFixedListeners()
{
    if (_fixedListeners)
    {
        _fixedListeners->clear();
        delete _fixedListeners;
        _fixedListeners = nullptr;
    }
}

void EventDispatcher::EventListenerVector::clear()
{
    clearSceneGraphListeners();
    clearFixedListeners();
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

void EventDispatcher::visitTarget(Node* node)
{    
    int i = 0;
    Array* children = node->getChildren();
    int childrenCount = children ? children->count() : 0;
    
    if(childrenCount > 0)
    {
        
        Node* child = nullptr;
        // visit children zOrder < 0
        for( ; i < childrenCount; i++ )
        {
            child = static_cast<Node*>( children->getObjectAtIndex(i) );
            
            if ( child && child->getZOrder() < 0 )
                visitTarget(child);
            else
                break;
        }
        
        _nodePriorityMap.insert(std::make_pair(node, ++s_eventPriorityIndex));
        
        for( ; i < childrenCount; i++ )
        {
            child = static_cast<Node*>( children->getObjectAtIndex(i) );
            if (child)
                visitTarget(child);
        }
    }
    else
    {
        _nodePriorityMap.insert(std::make_pair(node, ++s_eventPriorityIndex));
    }
}

void EventDispatcher::pauseTarget(Node* node)
{
    auto listenerIter = _nodeListenersMap.find(node);
    if (listenerIter != _nodeListenersMap.end())
    {
        auto listeners = listenerIter->second;
        for (auto& l : *listeners)
        {
            l->_paused = true;
        }
    }
}

void EventDispatcher::resumeTarget(Node* node)
{
    auto listenerIter = _nodeListenersMap.find(node);
    if (listenerIter != _nodeListenersMap.end())
    {
        auto listeners = listenerIter->second;
        for (auto& l : *listeners)
        {
            l->_paused = false;
        }
    }
}

void EventDispatcher::cleanTarget(Node* node)
{
    auto listenerIter = _nodeListenersMap.find(node);
    if (listenerIter != _nodeListenersMap.end())
    {
        auto listeners = listenerIter->second;
        auto listenersCopy = *listeners;
        for (auto& l : listenersCopy)
        {
            removeEventListener(l);
        }
    }
}

void EventDispatcher::associateNodeAndEventListener(Node* node, EventListener* listener)
{
    std::vector<EventListener*>* listeners = nullptr;
    auto found = _nodeListenersMap.find(node);
    if (found != _nodeListenersMap.end())
    {
        listeners = found->second;
    }
    else
    {
        listeners = new std::vector<EventListener*>();
    }
    
    listeners->push_back(listener);
    
    _nodeListenersMap.insert(std::make_pair(node, listeners));
}

void EventDispatcher::dissociateNodeAndEventListener(Node* node, EventListener* listener)
{
    std::vector<EventListener*>* listeners = nullptr;
    auto found = _nodeListenersMap.find(node);
    if (found != _nodeListenersMap.end())
    {
        listeners = found->second;
        auto iter = std::find(listeners->begin(), listeners->end(), listener);
        if (iter != listeners->end())
        {
            listeners->erase(iter);
        }
        
        if (listeners->empty())
        {
            _nodeListenersMap.erase(found);
            delete listeners;
        }
    }
}

void EventDispatcher::addEventListener(EventListener* listener)
{
    if (_inDispatch == 0)
    {
        EventListenerVector* listenerList = nullptr;
        
        auto iter = _listeners.find(listener->_type);
        if (iter == _listeners.end())
        {
            listenerList = new EventListenerVector();
            _listeners.insert(std::make_pair(listener->_type, listenerList));
        }
        else
        {
            listenerList = iter->second;
        }

        listenerList->push_back(listener);
        
        if (listener->_fixedPriority == 0)
        {
            setDirtyForEventType(listener->_type, DirtyFlag::SCENE_GRAPH_PRIORITY);
        }
        else
        {
            setDirtyForEventType(listener->_type, DirtyFlag::FIXED_PRITORY);
        }
    }
    else
    {
        _toAddedListeners.push_back(listener);
    }
}

void EventDispatcher::addEventListenerWithSceneGraphPriority(EventListener* listener, Node* node)
{
    CCASSERT(listener && node, "Invalid parameters.");
    CCASSERT(!listener->_isRegistered, "The listener has been registered.");
    
    if (!listener->checkAvailable())
        return;
    
    listener->_node = node;
    listener->_fixedPriority = 0;

    listener->retain();
    listener->_isRegistered = true;

    addEventListener(listener);

    associateNodeAndEventListener(node, listener);
    
    if (node->isRunning())
    {
        resumeTarget(node);
    }
}

void EventDispatcher::addEventListenerWithFixedPriority(EventListener* listener, int fixedPriority)
{
    CCASSERT(listener, "Invalid parameters.");
    CCASSERT(!listener->_isRegistered, "The listener has been registered.");
    CCASSERT(fixedPriority != 0, "0 priority is forbidden for fixed priority since it's used for scene graph based priority.");
    
    if (!listener->checkAvailable())
        return;
    
    listener->_node          = nullptr;
    listener->_fixedPriority = fixedPriority;
    listener->retain();
    listener->_isRegistered = true;
    listener->_paused = false;

    addEventListener(listener);
}

void EventDispatcher::removeEventListener(EventListener* listener)
{
    if (listener == nullptr)
        return;

    bool isFound = false;

    auto removeListenerInVector = [&](std::vector<EventListener*>* listeners){
        if (listeners == nullptr)
            return;
        
        for (auto iter = listeners->begin(); iter != listeners->end(); ++iter)
        {
            auto l = *iter;
            if (l == listener)
            {
                CC_SAFE_RETAIN(l);
                l->_isRegistered = false;
                if (l->_node != nullptr)
                {
                    dissociateNodeAndEventListener(l->_node, l);
                }
                
                if (_inDispatch == 0)
                {
                    listeners->erase(iter);
                    CC_SAFE_RELEASE(l);
                }
                
                isFound = true;
                break;
            }
        }
    };
    
    for (auto iter = _listeners.begin(); iter != _listeners.end();)
    {
        auto listeners = iter->second;
        auto fixedPriorityListeners = listeners->getFixedPriorityListeners();
        auto sceneGraphPriorityListeners = listeners->getSceneGraphPriorityListeners();

        removeListenerInVector(sceneGraphPriorityListeners);
        if (!isFound)
        {
            removeListenerInVector(fixedPriorityListeners);
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
        auto fixedPriorityListeners = iter->second->getFixedPriorityListeners();
        if (fixedPriorityListeners)
        {
            auto found = std::find(fixedPriorityListeners->begin(), fixedPriorityListeners->end(), listener);
            if (found != fixedPriorityListeners->end())
            {
                CCASSERT(listener->_node == nullptr, "Can't set fixed priority with scene graph based listener.");
                
                if (listener->_fixedPriority != fixedPriority)
                {
                    listener->_fixedPriority = fixedPriority;
                    setDirtyForEventType(listener->_type, DirtyFlag::FIXED_PRITORY);
                }
                return;
            }
        }
    }
}

void EventDispatcher::dispatchEventToListeners(EventListenerVector* listeners, std::function<bool(EventListener*)> onEvent)
{
    bool shouldStopPropagation = false;
    auto fixedPriorityListeners = listeners->getFixedPriorityListeners();
    auto sceneGraphPriorityListeners = listeners->getSceneGraphPriorityListeners();
    
    int i = 0;
    // priority < 0
    if (fixedPriorityListeners)
    {
        for (; !fixedPriorityListeners->empty() && i < listeners->getGt0Index(); ++i)
        {
            auto l = fixedPriorityListeners->at(i);
            if (!l->isPaused() && l->isRegistered() && onEvent(l))
            {
                shouldStopPropagation = true;
                break;
            }
        }
    }
    
    if (sceneGraphPriorityListeners)
    {
        if (!shouldStopPropagation)
        {
            // priority == 0, scene graph priority
            for (auto& l : *sceneGraphPriorityListeners)
            {
                if (!l->isPaused() && l->isRegistered() && onEvent(l))
                {
                    shouldStopPropagation = true;
                    break;
                }
            }
        }
    }

    if (fixedPriorityListeners)
    {
        if (!shouldStopPropagation)
        {
            // priority > 0
            for (; i < fixedPriorityListeners->size(); ++i)
            {
                auto l = fixedPriorityListeners->at(i);
                
                if (!l->isPaused() && l->isRegistered() && onEvent(fixedPriorityListeners->at(i)))
                {
                    shouldStopPropagation = true;
                    break;
                }
            }
        }
    }
}

void EventDispatcher::dispatchEvent(Event* event)
{
    if (!_isEnabled)
        return;
    
    updateDirtyFlagForSceneGraph();
    
    DirtyFlag dirtyFlag = DirtyFlag::NONE;
    
    auto dirtyIter = _priorityDirtyFlagMap.find(event->_type);
    if (dirtyIter != _priorityDirtyFlagMap.end())
    {
        dirtyFlag = dirtyIter->second;
    }
    
    if (dirtyFlag != DirtyFlag::NONE)
    {
        if ((int)dirtyFlag & (int)DirtyFlag::FIXED_PRITORY)
        {
            sortEventListenersOfFixedPriority(event->_type);
        }
        
        if ((int)dirtyFlag & (int)DirtyFlag::SCENE_GRAPH_PRIORITY)
        {
            sortEventListenersOfSceneGraphPriority(event->_type);
        }
        
        dirtyIter->second = DirtyFlag::NONE;
    }
    
    DispatchGuard guard(_inDispatch);
    
    auto iter = _listeners.find(event->getType());
    if (iter != _listeners.end())
    {
        auto listeners = iter->second;
        
        auto onEvent = [&event](EventListener* listener) -> bool{
            event->setCurrentTarget(listener->_node);
            listener->_onEvent(event);
            return event->isStopped();
        };
        
        dispatchEventToListeners(listeners, onEvent);
    }
    
    updateListeners();
}

void EventDispatcher::dispatchTouchEvent(EventTouch* event)
{
    if (!_isEnabled)
        return;
    
    updateDirtyFlagForSceneGraph();
    
    auto sortTouchListeners = [this](const std::string& type){
        
        DirtyFlag dirtyFlag = DirtyFlag::NONE;
        auto dirtyIter = _priorityDirtyFlagMap.find(type);
        if (dirtyIter != _priorityDirtyFlagMap.end())
        {
            dirtyFlag = dirtyIter->second;
        }
        
        if (dirtyFlag != DirtyFlag::NONE)
        {
            if ((int)dirtyFlag & (int)DirtyFlag::FIXED_PRITORY)
            {
                sortEventListenersOfFixedPriority(type);
            }
            
            if ((int)dirtyFlag & (int)DirtyFlag::SCENE_GRAPH_PRIORITY)
            {
                sortEventListenersOfSceneGraphPriority(type);
            }
            
            dirtyIter->second = DirtyFlag::NONE;
        }

    };

    sortTouchListeners(EventTouch::MODE_ONE_BY_ONE);
    sortTouchListeners(EventTouch::MODE_ALL_AT_ONCE);
    
    DispatchGuard guard(_inDispatch);
    
    auto oneByOnelisteners = getListeners(EventTouch::MODE_ONE_BY_ONE);
    auto allAtOncelisteners = getListeners(EventTouch::MODE_ALL_AT_ONCE);
    
    // If there aren't any touch listeners, return directly.
    if (nullptr == oneByOnelisteners && nullptr == allAtOncelisteners)
        return;
    
    bool isNeedsMutableSet = (oneByOnelisteners && allAtOncelisteners);
    
    std::vector<Touch*> orignalTouches = event->getTouches();
    std::vector<Touch*> mutableTouches(orignalTouches.size());
    std::copy(orignalTouches.begin(), orignalTouches.end(), mutableTouches.begin());

    //
    // process the target handlers 1st
    //
    if (oneByOnelisteners)
    {
        auto mutableTouchesIter = mutableTouches.begin();
        auto touchesIter = orignalTouches.begin();
        
        for (; touchesIter != orignalTouches.end(); ++touchesIter)
        {
            bool isSwallowed = false;

            auto onTouchEvent = [&](EventListener* l) -> bool { // Return true to break
                EventListenerTouchOneByOne* listener = static_cast<EventListenerTouchOneByOne*>(l);
                
                // Skip if the listener was removed.
                if (!listener->_isRegistered)
                    return false;
             
                event->setCurrentTarget(listener->_node);
                
                bool isClaimed = false;
                std::vector<Touch*>::iterator removedIter;
                
                EventTouch::EventCode eventCode = event->getEventCode();
                
                if (eventCode == EventTouch::EventCode::BEGAN)
                {
                    if (listener->onTouchBegan)
                    {
                        isClaimed = listener->onTouchBegan(*touchesIter, event);
                        if (isClaimed && listener->_isRegistered)
                        {
                            listener->_claimedTouches.push_back(*touchesIter);
                        }
                    }
                }
                else if (listener->_claimedTouches.size() > 0
                         && ((removedIter = std::find(listener->_claimedTouches.begin(), listener->_claimedTouches.end(), *touchesIter)) != listener->_claimedTouches.end()))
                {
                    isClaimed = true;
                    
                    switch (eventCode)
                    {
                        case EventTouch::EventCode::MOVED:
                            if (listener->onTouchMoved)
                            {
                                listener->onTouchMoved(*touchesIter, event);
                            }
                            break;
                        case EventTouch::EventCode::ENDED:
                            if (listener->onTouchEnded)
                            {
                                listener->onTouchEnded(*touchesIter, event);
                            }
                            if (listener->_isRegistered)
                            {
                                listener->_claimedTouches.erase(removedIter);
                            }
                            break;
                        case EventTouch::EventCode::CANCELLED:
                            if (listener->onTouchCancelled)
                            {
                                listener->onTouchCancelled(*touchesIter, event);
                            }
                            if (listener->_isRegistered)
                            {
                                listener->_claimedTouches.erase(removedIter);
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
                    updateListeners();
                    return true;
                }
                
                CCASSERT((*touchesIter)->getID() == (*mutableTouchesIter)->getID(), "");
                
                if (isClaimed && listener->_isRegistered && listener->_needSwallow)
                {
                    if (isNeedsMutableSet)
                    {
                        mutableTouchesIter = mutableTouches.erase(mutableTouchesIter);
                        isSwallowed = true;
                    }
                    return true;
                }
                
                return false;
            };
            
            //
            dispatchEventToListeners(oneByOnelisteners, onTouchEvent);
            if (event->isStopped())
            {
                return;
            }
            
            if (!isSwallowed)
                ++mutableTouchesIter;
        }
    }
    
    //
    // process standard handlers 2nd
    //
    if (allAtOncelisteners && mutableTouches.size() > 0)
    {
        
        auto onTouchesEvent = [&](EventListener* l) -> bool{
            EventListenerTouchAllAtOnce* listener = static_cast<EventListenerTouchAllAtOnce*>(l);
            // Skip if the listener was removed.
            if (!listener->_isRegistered)
                return false;
            
            event->setCurrentTarget(listener->_node);
            
            switch (event->getEventCode())
            {
                case EventTouch::EventCode::BEGAN:
                    if (listener->onTouchesBegan)
                    {
                        listener->onTouchesBegan(mutableTouches, event);
                    }
                    break;
                case EventTouch::EventCode::MOVED:
                    if (listener->onTouchesMoved)
                    {
                        listener->onTouchesMoved(mutableTouches, event);
                    }
                    break;
                case EventTouch::EventCode::ENDED:
                    if (listener->onTouchesEnded)
                    {
                        listener->onTouchesEnded(mutableTouches, event);
                    }
                    break;
                case EventTouch::EventCode::CANCELLED:
                    if (listener->onTouchesCancelled)
                    {
                        listener->onTouchesCancelled(mutableTouches, event);
                    }
                    break;
                default:
                    CCASSERT(false, "The eventcode is invalid.");
                    break;
            }
            
            // If the event was stopped, return directly.
            if (event->isStopped())
            {
                updateListeners();
                return false;
            }
            
            return false;
        };
        
        dispatchEventToListeners(allAtOncelisteners, onTouchesEvent);
        if (event->isStopped())
        {
            return;
        }
    }
    
    updateListeners();
}

void EventDispatcher::updateListeners()
{
    auto listenersIter = _listeners.begin();
    while (listenersIter != _listeners.end())
    {
        auto listeners = listenersIter->second;
        auto fixedPriorityListeners = listeners->getFixedPriorityListeners();
        auto sceneGraphPriorityListeners = listeners->getSceneGraphPriorityListeners();
        
        if (sceneGraphPriorityListeners)
        {
            for (auto iter = sceneGraphPriorityListeners->begin(); iter != sceneGraphPriorityListeners->end();)
            {
                auto l = *iter;
                if (!l->_isRegistered)
                {
                    iter = sceneGraphPriorityListeners->erase(iter);
                    l->release();
                }
                else
                {
                    ++iter;
                }
            }
        }
        
        if (fixedPriorityListeners)
        {
            for (auto iter = fixedPriorityListeners->begin(); iter != fixedPriorityListeners->end();)
            {
                auto l = *iter;
                if (!l->_isRegistered)
                {
                    iter = fixedPriorityListeners->erase(iter);
                    l->release();
                }
                else
                {
                    ++iter;
                }
            }
        }
        
        if (sceneGraphPriorityListeners && sceneGraphPriorityListeners->empty())
        {
            listeners->clearSceneGraphListeners();
        }

        if (fixedPriorityListeners && fixedPriorityListeners->empty())
        {
            listeners->clearFixedListeners();
        }

        if (listenersIter->second->empty())
        {
            _priorityDirtyFlagMap.erase(listenersIter->first);
            delete listenersIter->second;
            listenersIter =  _listeners.erase(listenersIter);
        }
        else
        {
            ++listenersIter;
        }
    }
    
    if (!_toAddedListeners.empty())
    {
        EventListenerVector* listeners = nullptr;
        
        for (auto& listener : _toAddedListeners)
        {
            auto itr = _listeners.find(listener->_type);
            if (itr == _listeners.end())
            {
                
                listeners = new EventListenerVector();
                _listeners.insert(std::make_pair(listener->_type, listeners));
            }
            else
            {
                listeners = itr->second;
            }
            
            listeners->push_back(listener);
            
            if (listener->_fixedPriority == 0)
            {
                setDirtyForEventType(listener->_type, DirtyFlag::SCENE_GRAPH_PRIORITY);
            }
            else
            {
                setDirtyForEventType(listener->_type, DirtyFlag::FIXED_PRITORY);
            }
        }
        _toAddedListeners.clear();
    }
}

void EventDispatcher::updateDirtyFlagForSceneGraph()
{
    if (!_dirtyNodes.empty())
    {
        for (auto& node : _dirtyNodes)
        {
            auto iter = _nodeListenersMap.find(node);
            if (iter != _nodeListenersMap.end())
            {
                for (auto& l : *iter->second)
                {
                    setDirtyForEventType(l->_type, DirtyFlag::SCENE_GRAPH_PRIORITY);
                }
            }
        }
        
        _dirtyNodes.clear();
    }
}

void EventDispatcher::sortEventListenersOfSceneGraphPriority(const std::string& eventType)
{
    if (eventType.empty())
        return;
    
    auto listeners = getListeners(eventType);
    
    if (listeners == nullptr)
        return;
    
    Node* rootNode = (Node*)Director::getInstance()->getRunningScene();
    // Reset priority index
    s_eventPriorityIndex = 0;
    _nodePriorityMap.clear();

    visitTarget(rootNode);
    
    // After sort: priority < 0, > 0
    auto sceneGraphlisteners = listeners->getSceneGraphPriorityListeners();
    std::sort(sceneGraphlisteners->begin(), sceneGraphlisteners->end(), [this](const EventListener* l1, const EventListener* l2) {
        return _nodePriorityMap[l1->_node] > _nodePriorityMap[l2->_node];
    });
    
#if DUMP_LISTENER_ITEM_PRIORITY_INFO
    log("-----------------------------------");
    for (auto& l : *sceneGraphlisteners)
    {
        log("listener priority: node ([%s]%p), priority (%d)", typeid(*l->_node).name(), l->_node, _nodePriorityMap[l->_node]);
    }
#endif
}

void EventDispatcher::sortEventListenersOfFixedPriority(const std::string &eventType)
{
    if (eventType.empty())
        return;
    
    auto listeners = getListeners(eventType);

    if (listeners == nullptr)
        return;
    
    // After sort: priority < 0, > 0
    auto fixedlisteners = listeners->getFixedPriorityListeners();
    std::sort(fixedlisteners->begin(), fixedlisteners->end(), [](const EventListener* l1, const EventListener* l2) {
        return l1->_fixedPriority < l2->_fixedPriority;
    });
    
    // FIXME: Should use binary search
    int index = 0;
    for (auto& listener : *fixedlisteners)
    {
        if (listener->_fixedPriority >= 0)
            break;
        ++index;
    }
    
    listeners->setGt0Index(index);
    
#if DUMP_LISTENER_ITEM_PRIORITY_INFO
    log("-----------------------------------");
    for (auto& l : *fixedlisteners)
    {
        log("listener priority: node (%p), fixed (%d)", l->_node, l->_fixedPriority);
    }    
#endif
    
}

EventDispatcher::EventListenerVector* EventDispatcher::getListeners(const std::string &eventType)
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
        auto listeners = listenerItemIter->second;
        auto fixedPriorityListeners = listeners->getFixedPriorityListeners();
        auto sceneGraphPriorityListeners = listeners->getSceneGraphPriorityListeners();
        
        auto removeAllListenersInVector = [&](std::vector<EventListener*>* listenerVector){
            if (listenerVector == nullptr)
                return;
            
            for (auto iter = listenerVector->begin(); iter != listenerVector->end();)
            {
                auto l = *iter;
                l->_isRegistered = false;
                if (l->_node != nullptr)
                {
                    dissociateNodeAndEventListener(l->_node, l);
                }
                
                l->release();
                if (_inDispatch == 0)
                {
                    iter = listenerVector->erase(iter);
                }
                else
                {
                    ++iter;
                }
            }
        };
        
        removeAllListenersInVector(sceneGraphPriorityListeners);
        removeAllListenersInVector(fixedPriorityListeners);
        
        if (!_inDispatch)
        {
            listeners->clear();
            delete listeners;
            _listeners.erase(listenerItemIter);
            _priorityDirtyFlagMap.erase(eventType);
        }
    }
}

void EventDispatcher::removeAllListeners()
{
    std::vector<std::string> types(_listeners.size());

    for (auto iter = _listeners.begin(); iter != _listeners.end(); ++iter)
    {
        types.push_back(iter->first);
    }

    for (auto& type : types)
    {
        removeListenersForEventType(type);
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

void EventDispatcher::setDirtyForNode(Node* node)
{
    // Mark the node dirty only when there was an eventlistener associates with it. 
    if (_nodeListenersMap.find(node) != _nodeListenersMap.end())
    {
        _dirtyNodes.insert(node);
    }
}

void EventDispatcher::setDirtyForEventType(const std::string& eventType, DirtyFlag flag)
{
    CCASSERT(!eventType.empty(), "Invalid event type.");
    
    auto iter = _priorityDirtyFlagMap.find(eventType);
    if (iter == _priorityDirtyFlagMap.end())
    {
        _priorityDirtyFlagMap.insert(std::make_pair(eventType, flag));
    }
    else
    {
        int ret = (int)flag | (int)iter->second;
        iter->second = (DirtyFlag) ret;
    }
}

EventDispatcher::DirtyFlag EventDispatcher::isDirtyForEventType(const std::string& eventType)
{
    DirtyFlag flag = DirtyFlag::NONE;
    auto iter = _priorityDirtyFlagMap.find(eventType);
    if (iter != _priorityDirtyFlagMap.end())
    {
        flag = iter->second;
    }

    return flag;
}

NS_CC_END

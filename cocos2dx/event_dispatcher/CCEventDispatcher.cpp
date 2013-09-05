//
//  CCEventDispatcher.cpp
//  cocos2d_libs
//
//  Created by James Chen on 8/30/13.
//
//

#include "CCEventDispatcher.h"
#include "CCTouchEvent.h"
#include "CCDirector.h"

NS_CC_BEGIN

namespace {

EventDispatcher _instance;

class TouchEventListener
{
public:
    TouchEventListener()
    {
        EventDispatcher::getInstance()->registerEventCallback(TouchEvent::EVENT_TYPE, [](Event* evt) -> bool {
            TouchEvent* touchEvent = static_cast<TouchEvent*>(evt);
            
            // Hit test by iterating current node tree.
            
            auto rootNode = Director::getInstance()->getRunningScene();
            
            processTouchEvent((Node*)rootNode, touchEvent);
            return true;
        });
    }
    
    static bool hitTest(Node* node, TouchEvent* touchEvent)
    {
        Point pt = node->convertToNodeSpace(touchEvent->getTouches()[0]->getLocation());
        Rect rect = Rect(0, 0, node->getContentSize().width, node->getContentSize().height);
        
        if (rect.containsPoint(pt))
        {
            return true;
        }
        return false;
    }
    
    /**
     *  @return true To stop propagation.
     */
    static bool processTouchEvent(Node* node, TouchEvent* touchEvent)
    {
        Array* children = node->getChildren();

        Object* obj;
        CCARRAY_FOREACH_REVERSE(children, obj)
        {
            Node* child = static_cast<Node*>(obj);
            
            if (processTouchEvent(child, touchEvent))
            {
                return true;
            }
        }
        
        if (node->isTouchable() && node->isVisible() && hitTest(node, touchEvent))
        {
            // If the event is cancelled, the return value of dispatchEvent will be true;
            if (node->dispatchEvent(touchEvent))
                return true;
        }
        
        return false;
    }
};

TouchEventListener _touchEventListener;

}

EventDispatcher::EventDispatcher()
: _eventDispatcherUnit(nullptr)
{
}

EventDispatcher::~EventDispatcher()
{
    CC_SAFE_DELETE(_eventDispatcherUnit);
}

EventDispatcher* EventDispatcher::getInstance()
{
    return &_instance;
}

CallbackId EventDispatcher::registerEventCallback(const std::string& type, std::function<bool(Event*)> callback)
{
    if (_eventDispatcherUnit == nullptr)
    {
        _eventDispatcherUnit = new EventDispatcherUnit();
    }
    
    return _eventDispatcherUnit->registerEventCallback(type, callback, false);
}

void EventDispatcher::unregisterEventCallback(CallbackId callbackId)
{
    if (_eventDispatcherUnit != nullptr)
    {
        _eventDispatcherUnit->unregisterEventCallback(callbackId);
    }
}

void EventDispatcher::dispatchEvent(Event* event)
{
    if (_eventDispatcherUnit != nullptr)
    {
        _eventDispatcherUnit->dispatchEvent(event);
    }
}

NS_CC_END


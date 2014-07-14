/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2011 Yannick Loriot.
 * http://yannickloriot.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *
 * converted to c++ / cocos2d-x by Angus C
 */

#include "CCControl.h"
#include "base/CCDirector.h"
#include "2d/CCMenu.h"
#include "base/CCTouch.h"
#include "CCInvocation.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerTouch.h"

NS_CC_EXT_BEGIN

__Control::__Control()
: _enabled(false)
, _selected(false)
, _highlighted(false)
, _hasVisibleParents(false)
, _isOpacityModifyRGB(false)
, _state(State::NORMAL)
{

}

__Control* __Control::create()
{
    __Control* pRet = new __Control();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool __Control::init()
{
    if (Layer::init())
    {
        // Initialise instance variables
        _state=__Control::State::NORMAL;
        setEnabled(true);
        setSelected(false);
        setHighlighted(false);

        auto dispatcher = Director::getInstance()->getEventDispatcher();
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(__Control::onTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(__Control::onTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(__Control::onTouchEnded, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(__Control::onTouchCancelled, this);
        
        dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        return true;
    }
    else
    {
        return false;
    }
}

__Control::~__Control()
{
    for (auto iter = _dispatchTable.begin(); iter != _dispatchTable.end(); ++iter)
    {
        delete iter->second;
    }
    
    _dispatchTable.clear();
}

void __Control::sendActionsForControlEvents(EventType controlEvents)
{
	retain();
    // For each control events
    for (int i = 0; i < kControlEventTotalNumber; i++)
    {
        // If the given controlEvents bitmask contains the curent event
        if (((int)controlEvents & (1 << i)))
        {
            // Call invocations
            const auto& invocationList = this->dispatchListforControlEvent((__Control::EventType)(1<<i));

            for(const auto &invocation : invocationList) {
                invocation->invoke(this);
            }

#if CC_ENABLE_SCRIPT_BINDING
            //Call ScriptFunc
            if (kScriptTypeLua == _scriptType)
            {
                cocos2d::BasicScriptData data(this,(void*)&controlEvents);
                cocos2d::ScriptEvent event(cocos2d::kControlEvent,(void*)&data);
                cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
            }
#endif
        }
    }
	release();
}
void __Control::addTargetWithActionForControlEvents(Ref* target, Handler action, EventType controlEvents)
{
    // For each control events
    for (int i = 0; i < kControlEventTotalNumber; i++)
    {
        // If the given controlEvents bitmask contains the curent event
        if (((int)controlEvents & (1 << i)))
        {
            this->addTargetWithActionForControlEvent(target, action, (EventType)(1<<i));
        }
    }
}



/**
 * Adds a target and action for a particular event to an internal dispatch 
 * table.
 * The action message may optionnaly include the sender and the event as 
 * parameters, in that order.
 * When you call this method, target is not retained.
 *
 * @param target The target object that is, the object to which the action 
 * message is sent. It cannot be nil. The target is not retained.
 * @param action A selector identifying an action message. It cannot be nullptr.
 * @param controlEvent A control event for which the action message is sent.
 * See "CCControlEvent" for constants.
 */
void __Control::addTargetWithActionForControlEvent(Ref* target, Handler action, EventType controlEvent)
{    
    // Create the invocation object
    __Invocation *invocation = __Invocation::create(target, action, controlEvent);

    // Add the invocation into the dispatch list for the given control event
    auto& eventInvocationList = this->dispatchListforControlEvent(controlEvent);
    eventInvocationList.pushBack(invocation);
}

void __Control::removeTargetWithActionForControlEvents(Ref* target, Handler action, EventType controlEvents)
{
     // For each control events
    for (int i = 0; i < kControlEventTotalNumber; i++)
    {
        // If the given controlEvents bitmask contains the curent event
        if (((int)controlEvents & (1 << i)))
        {
            this->removeTargetWithActionForControlEvent(target, action, (EventType)(1 << i));
        }
    }
}

void __Control::removeTargetWithActionForControlEvent(Ref* target, Handler action, EventType controlEvent)
{
    // Retrieve all invocations for the given control event
    //<Invocation*>
    auto& eventInvocationList = this->dispatchListforControlEvent(controlEvent);
    
    //remove all invocations if the target and action are null
    //TODO: should the invocations be deleted, or just removed from the array? Won't that cause issues if you add a single invocation for multiple events?

    if (!target && !action)
    {
        //remove objects
        eventInvocationList.clear();
    } 
    else
    {
        std::vector<__Invocation*> tobeRemovedInvocations;
        
        //normally we would use a predicate, but this won't work here. Have to do it manually
        for(const auto &invocation : eventInvocationList) {
            bool shouldBeRemoved=true;
            if (target)
            {
                shouldBeRemoved=(target==invocation->getTarget());
            }
            if (action)
            {
                shouldBeRemoved=(shouldBeRemoved && (action==invocation->getAction()));
            }
            // Remove the corresponding invocation object
            if (shouldBeRemoved)
            {
                tobeRemovedInvocations.push_back(invocation);
            }
        }

        for(const auto &invocation : tobeRemovedInvocations) {
            eventInvocationList.eraseObject(invocation);
        }
    }
}


//CRGBA protocol
void __Control::setOpacityModifyRGB(bool bOpacityModifyRGB)
{
    _isOpacityModifyRGB=bOpacityModifyRGB;
    
    for(auto child : _children){
        child->setOpacityModifyRGB(bOpacityModifyRGB);
    }
}

bool __Control::isOpacityModifyRGB() const
{
    return _isOpacityModifyRGB;
}


Vec2 __Control::getTouchLocation(Touch* touch)
{
    Vec2 touchLocation = touch->getLocation();            // Get the touch position
    touchLocation = this->convertToNodeSpace(touchLocation);  // Convert to the node space of this class
    
    return touchLocation;
}

bool __Control::isTouchInside(Touch* touch)
{
    Vec2 touchLocation = touch->getLocation(); // Get the touch position
    touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
    Rect bBox = getBoundingBox();
    return bBox.containsPoint(touchLocation);
}

Vector<__Invocation*>& __Control::dispatchListforControlEvent(EventType controlEvent)
{
    Vector<__Invocation*>* invocationList = nullptr;
    auto iter = _dispatchTable.find((int)controlEvent);
    
    // If the invocation list does not exist for the  dispatch table, we create it
    if (iter == _dispatchTable.end())
    {
        invocationList = new Vector<__Invocation*>();
        _dispatchTable[(int)controlEvent] = invocationList;
    }
    else
    {
        invocationList = iter->second;
    }
    return *invocationList;
}

void __Control::needsLayout()
{
}

void __Control::setEnabled(bool bEnabled)
{
    _enabled = bEnabled;
    if(_enabled) {
        _state = __Control::State::NORMAL;
    } else {
        _state = __Control::State::DISABLED;
    }

    this->needsLayout();
}

bool __Control::isEnabled() const
{
    return _enabled;
}

void __Control::setSelected(bool bSelected)
{
    _selected = bSelected;
    this->needsLayout();
}

bool __Control::isSelected() const
{
    return _selected;
}

void __Control::setHighlighted(bool bHighlighted)
{
    _highlighted = bHighlighted;
    this->needsLayout();
}

bool __Control::isHighlighted() const
{
    return _highlighted;
}

bool __Control::hasVisibleParents() const
{
    auto parent = this->getParent();
    for( auto c = parent; c != nullptr; c = c->getParent() )
    {
        if( !c->isVisible() )
        {
            return false;
        }
    }
    return true;
}

__Control::EventType operator|(__Control::EventType a, __Control::EventType b) {
    return static_cast<__Control::EventType>(static_cast<int>(a) | static_cast<int>(b));
}

NS_CC_EXT_END

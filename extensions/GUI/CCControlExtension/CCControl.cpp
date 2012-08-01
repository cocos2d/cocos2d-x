/*
 * CCControl.m
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
#include "CCDirector.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "menu_nodes/CCMenu.h"
#include "touch_dispatcher/CCTouch.h"

NS_CC_EXT_BEGIN

CCControl::CCControl()
{

}

bool CCControl::init()
{
    if (CCLayer::init())
    {
        //this->setTouchEnabled(true);
        //m_bIsTouchEnabled=true;
        // Initialise instance variables
        m_nState=CCControlStateNormal;
        m_bEnabled=true;
        m_bSelected=false;
        m_bHighlighted=false;

        // Set the touch dispatcher priority by default to 1
        m_nDefaultTouchPriority = 1;
        this->setDefaultTouchPriority(m_nDefaultTouchPriority);
        // Initialise the tables
        dispatchTable=new CCDictionary();    
        //dispatchTable->autorelease();
        //   dispatchTable_ = [[NSMutableDictionary alloc] initWithCapacity:1];
        return true;
    }
    else
        return false;
}

CCControl::~CCControl()
{
    CC_SAFE_RELEASE(dispatchTable);
}

    //Menu - Events
void CCControl::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void CCControl::onEnter()
{
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, m_nDefaultTouchPriority, true);
    CCLayer::onEnter();
}

void CCControl::onExit()
{
    //CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void CCControl::sendActionsForControlEvents(CCControlEvent controlEvents)
{
    // For each control events
    for (int i = 0; i < CONTROL_EVENT_TOTAL_NUMBER; i++)
    {
        // If the given controlEvents bitmask contains the curent event
        if ((controlEvents & (1 << i)))
        {
            // Call invocations
            // <CCInvocation*>
            CCArray* invocationList=CCControl::dispatchListforControlEvent(1<<i);
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(invocationList, pObj)
            {
                CCInvocation* invocation = (CCInvocation*)pObj;
                invocation->invoke(this);
            }                 
        }
    }
}
void CCControl::addTargetWithActionForControlEvents(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvents)
{
    // For each control events
    for (int i = 0; i < CONTROL_EVENT_TOTAL_NUMBER; i++)
    {
        // If the given controlEvents bitmask contains the curent event
        if ((controlEvents & (1 << i)))
        {
            CCControl::addTargetWithActionForControlEvent(target, action, 1<<i);            
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
 * @param target The target object—that is, the object to which the action 
 * message is sent. It cannot be nil. The target is not retained.
 * @param action A selector identifying an action message. It cannot be NULL.
 * @param controlEvent A control event for which the action message is sent.
 * See "CCControlEvent" for constants.
 */
void CCControl::addTargetWithActionForControlEvent(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvent)
{    
    // Create the invocation object
    CCInvocation *invocation=new CCInvocation(target, action, controlEvent);
    invocation->autorelease();
    // Add the invocation into the dispatch list for the given control event
    CCArray* eventInvocationList = dispatchListforControlEvent(controlEvent);
    eventInvocationList->addObject(invocation);    
}

void CCControl::removeTargetWithActionForControlEvents(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvents)
{
     // For each control events
    for (int i = 0; i < CONTROL_EVENT_TOTAL_NUMBER; i++)
    {
        // If the given controlEvents bitmask contains the curent event
        if ((controlEvents & (1 << i)))
        {
            removeTargetWithActionForControlEvent(target, action, 1 << i);
        }
    }
}

/**
 * Removes a target and action for a particular event from an internal dispatch
 * table.
 *
 * @param target The target object—that is, the object to which the action 
 * message is sent. Pass nil to remove all targets paired with action and the
 * specified control events.
 * @param action A selector identifying an action message. Pass NULL to remove
 * all action messages paired with target.
 * @param controlEvent A control event for which the action message is sent.
 * See "CCControlEvent" for constants.
 */
void CCControl::removeTargetWithActionForControlEvent(CCObject* target, SEL_CCControlHandler action, CCControlEvent controlEvent)
{
    // Retrieve all invocations for the given control event
    //<CCInvocation*>
    CCArray *eventInvocationList=dispatchListforControlEvent(controlEvent);
    
    //remove all invocations if the target and action are null
    //TODO: should the invocations be deleted, or just removed from the array? Won't that cause issues if you add a single invocation for multiple events?
    bool bDeleteObjects=true;
    if (!target && !action)
    {
        //remove objects
        eventInvocationList->removeAllObjects();
    } 
    else
    {
            //normally we would use a predicate, but this won't work here. Have to do it manually
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(eventInvocationList, pObj)
            {
                CCInvocation *invocation = (CCInvocation*)pObj;
                bool shouldBeRemoved=true;
                if (target)                
                    shouldBeRemoved=(target==invocation->getTarget());                
                if (action)
                    shouldBeRemoved=(shouldBeRemoved && (action==invocation->getAction()));
                // Remove the corresponding invocation object
                if (shouldBeRemoved)
                    eventInvocationList->removeObject(invocation, bDeleteObjects);
            }
    }
}


//CRGBA protocol
void CCControl::setColor(const ccColor3B& color)
{
    m_tColor=color;
    CCObject* child;
    CCArray* children=getChildren();
    CCARRAY_FOREACH(children, child)
    {
        CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
        if (pNode)
        {
            pNode->setColor(m_tColor);
        }
    }
}

const ccColor3B& CCControl::getColor(void)
{
    return m_tColor;
}


void CCControl::setOpacity(GLubyte opacity)
{
    m_cOpacity = opacity;
    
    CCObject* child;
    CCArray* children=getChildren();
    CCARRAY_FOREACH(children, child)
    {
        CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
        if (pNode)
        {
            pNode->setOpacity(opacity);
        }
    }

}

GLubyte CCControl::getOpacity()
{
    return m_cOpacity;
}


void CCControl::setOpacityModifyRGB(bool opacityModifyRGB)
{
    m_bIsOpacityModifyRGB=opacityModifyRGB;
        CCObject* child;
    CCArray* children=getChildren();
    CCARRAY_FOREACH(children, child)
    {
        CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
        if (pNode)
        {
            pNode->setOpacityModifyRGB(opacityModifyRGB);
        }
    }
}

bool CCControl::isOpacityModifyRGB()
{
    return m_bIsOpacityModifyRGB;
}


CCPoint CCControl::getTouchLocation(CCTouch* touch)
{
    CCPoint touchLocation = touch->getLocation();;                      // Get the touch position
    touchLocation = this->getParent()->convertToNodeSpace(touchLocation);  // Convert to the node space of this class
    
    return touchLocation;
}

bool CCControl::isTouchInside(CCTouch* touch)
{
    CCPoint touchLocation=getTouchLocation(touch);
    CCRect bBox=boundingBox();
    return bBox.containsPoint(touchLocation);
}

CCArray* CCControl::dispatchListforControlEvent(CCControlEvent controlEvent)
{
    CCArray* invocationList = (CCArray*)dispatchTable->objectForKey(controlEvent);

    // If the invocation list does not exist for the  dispatch table, we create it
    if (invocationList == NULL)
    {
        invocationList = CCArray::createWithCapacity(1);
        dispatchTable->setObject(invocationList, controlEvent);
    }    
    return invocationList;
}

void CCControl::setEnabled(bool bEnabled)
{
    m_bEnabled = bEnabled;
}

bool CCControl::isEnabled()
{
    return m_bEnabled;
}

void CCControl::setSelected(bool bSelected)
{
    m_bSelected = bSelected;
}

bool CCControl::isSelected()
{
    return m_bSelected;
}

void CCControl::setHighlighted(bool bHighlighted)
{
    m_bHighlighted = bHighlighted;
}

bool CCControl::isHighlighted()
{
    return m_bHighlighted;
}

NS_CC_EXT_END

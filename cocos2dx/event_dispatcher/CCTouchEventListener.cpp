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

#include "CCTouchEventListener.h"
#include "CCEventDispatcher.h"
#include "CCTouchEvent.h"

NS_CC_BEGIN

TouchEventListener::TouchEventListener(Touch::DispatchMode mode)
: EventListener(TouchEvent::EVENT_TYPE, nullptr)
, onTouchBegan(nullptr)
, onTouchMoved(nullptr)
, onTouchEnded(nullptr)
, onTouchCancelled(nullptr)
, onTouchesBegan(nullptr)
, onTouchesMoved(nullptr)
, onTouchesEnded(nullptr)
, onTouchesCancelled(nullptr)
, _needSwallow(false)
, _dispatchMode(mode)
{
    onEvent = [](Event* event){
        
        if (event->isValid())
        {
            event->setValid(false);
        }
        else
        {
            return;
        }
        
        TouchEvent* touchEvent = static_cast<TouchEvent*>(event);
        
        auto touchListeners = EventDispatcher::getInstance()->getListeners(TouchEvent::EVENT_TYPE);
        
        //CCLOG("listener count = %d", touchListeners->size());
        
        std::vector<EventDispatcher::EventListenerItem*> oneByOnelisteners;
        oneByOnelisteners.reserve(touchListeners->size());
        
        std::vector<EventDispatcher::EventListenerItem*> allInOnelisteners;
        allInOnelisteners.reserve(touchListeners->size());
        
        for (auto iter = touchListeners->begin(); iter != touchListeners->end(); ++iter)
        {
            auto touchEventListener = std::static_pointer_cast<TouchEventListener>((*iter)->listener);
            
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
        
        std::vector<Touch*> orignalTouches = touchEvent->getTouches();
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
                    if ((*oneByOneIter)->id == 0)
                        continue;
                    
                    bool isClaimed = false;
                    std::vector<Touch*>::iterator removedIter;
                    
                    auto touchEventListener = std::static_pointer_cast<TouchEventListener>((*oneByOneIter)->listener);
                    TouchEvent::EventCode eventCode = touchEvent->getEventCode();
                    
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
                                    touchEventListener->_claimedTouches.erase(removedIter);
                                }
                                break;
                            case TouchEvent::EventCode::CANCELLED:
                                if (touchEventListener->onTouchCancelled)
                                {
                                    touchEventListener->onTouchCancelled(*touchesIter, event);
                                    touchEventListener->_claimedTouches.erase(removedIter);
                                }
                                break;
                            default:
                                CCASSERT(false, "The eventcode is invalid.");
                                break;
                        }
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
                if ((*allInOneIter)->id == 0)
                    continue;
                
                auto touchEventListener = std::static_pointer_cast<TouchEventListener>((*allInOneIter)->listener);
                
                switch (touchEvent->getEventCode())
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
            }
        }
    };
}

void TouchEventListener::setSwallowTouches(bool needSwallow)
{
    CCASSERT(_dispatchMode == Touch::DispatchMode::ONE_BY_ONE, "Swallow touches only available in OneByOne mode.");
    _needSwallow = needSwallow;
}

std::shared_ptr<TouchEventListener> TouchEventListener::create(Touch::DispatchMode mode)
{
    std::shared_ptr<TouchEventListener> ret(new TouchEventListener(mode));
    return ret;
}

bool TouchEventListener::checkAvaiable()
{
    if (_dispatchMode == Touch::DispatchMode::ALL_AT_ONCE)
    {
        if (onTouchesBegan == nullptr && onTouchesMoved == nullptr
            && onTouchesEnded == nullptr && onTouchesCancelled == nullptr)
        {
            CCASSERT(false, "Invalid TouchEventListener.");
            return false;
        }
    }
    else if (_dispatchMode == Touch::DispatchMode::ONE_BY_ONE)
    {
        if (onTouchBegan == nullptr && onTouchMoved == nullptr
            && onTouchEnded == nullptr && onTouchCancelled == nullptr)
        {
            CCASSERT(false, "Invalid TouchEventListener.");
            return false;
        }
    }
    else
    {
        CCASSERT(false, "");
    }
    
    return true;
}

NS_CC_END
/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      Valentin Milea

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

#include "CCTouchHandler.h"
#include "ccMacros.h"

NS_CC_BEGIN

TouchDelegate* TouchHandler::getDelegate(void)
{
    return _delegate;
}

void TouchHandler::setDelegate(TouchDelegate *pDelegate)
{
    if (pDelegate)
    {
        dynamic_cast<Object*>(pDelegate)->retain();
    }

    if (_delegate)
    {
        dynamic_cast<Object*>(_delegate)->release();
    }

    _delegate = pDelegate;
}

int TouchHandler::getPriority(void)
{
    return _priority;
}

void TouchHandler::setPriority(int nPriority)
{
    _priority = nPriority;
}

int TouchHandler::getEnabledSelectors(void)
{
    return _enabledSelectors;
}

void TouchHandler::setEnalbedSelectors(int nValue)
{
    _enabledSelectors = nValue;
}

TouchHandler* TouchHandler::handlerWithDelegate(TouchDelegate *pDelegate, int nPriority)
{
    TouchHandler *pHandler = new TouchHandler();

    if (pHandler)
    {
        if (pHandler->initWithDelegate(pDelegate, nPriority))
        {
            pHandler->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pHandler);
        }
    }
    
    return pHandler;
}

bool TouchHandler::initWithDelegate(TouchDelegate *pDelegate, int nPriority)
{
    CCASSERT(pDelegate != NULL, "touch delegate should not be null");

    _delegate = pDelegate; 

    dynamic_cast<Object*>(pDelegate)->retain();

    _priority = nPriority;
    _enabledSelectors = 0;

    return true;
}

TouchHandler::~TouchHandler(void)
{
    if (_delegate)
    {
        dynamic_cast<Object*>(_delegate)->release();
    }   
}

// implementation of StandardTouchHandler
bool StandardTouchHandler::initWithDelegate(TouchDelegate *pDelegate, int nPriority)
{
    if (TouchHandler::initWithDelegate(pDelegate, nPriority))
    {
        return true;
    }

    return false;
}

StandardTouchHandler* StandardTouchHandler::handlerWithDelegate(TouchDelegate *pDelegate, int nPriority)
{
    StandardTouchHandler* pHandler = new StandardTouchHandler();

    if (pHandler)
    {
        if (pHandler->initWithDelegate(pDelegate, nPriority))
        {
            pHandler->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pHandler);
        }
    }

    return pHandler;
}

// implementation of TargetedTouchHandler

bool TargetedTouchHandler::isSwallowsTouches(void)
{
    return _swallowsTouches;
}

void TargetedTouchHandler::setSwallowsTouches(bool bSwallowsTouches)
{
    _swallowsTouches = bSwallowsTouches;
}

Set* TargetedTouchHandler::getClaimedTouches(void)
{
    return _claimedTouches;
}

TargetedTouchHandler* TargetedTouchHandler::handlerWithDelegate(TouchDelegate *pDelegate, int nPriority, bool bSwallow)
{
    TargetedTouchHandler *pHandler = new TargetedTouchHandler();
    if (pHandler)
    {
        if (pHandler->initWithDelegate(pDelegate, nPriority, bSwallow))
        {
            pHandler->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pHandler);
        }
    }

    return pHandler;
}

bool TargetedTouchHandler::initWithDelegate(TouchDelegate *pDelegate, int nPriority, bool bSwallow)
{
    if (TouchHandler::initWithDelegate(pDelegate, nPriority))
    {
        _claimedTouches = new Set();
        _swallowsTouches = bSwallow;

        return true;
    }

    return false;
}

TargetedTouchHandler::~TargetedTouchHandler(void)
{
    CC_SAFE_RELEASE(_claimedTouches);
}

NS_CC_END

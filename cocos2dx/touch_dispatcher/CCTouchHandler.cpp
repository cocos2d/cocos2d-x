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

CCTouchDelegate* CCTouchHandler::getDelegate(void)
{
    return _delegate;
}

void CCTouchHandler::setDelegate(CCTouchDelegate *pDelegate)
{
    if (pDelegate)
    {
        dynamic_cast<CCObject*>(pDelegate)->retain();
    }

    if (_delegate)
    {
        dynamic_cast<CCObject*>(_delegate)->release();
    }

    _delegate = pDelegate;
}

int CCTouchHandler::getPriority(void)
{
    return _priority;
}

void CCTouchHandler::setPriority(int nPriority)
{
    _priority = nPriority;
}

int CCTouchHandler::getEnabledSelectors(void)
{
    return _enabledSelectors;
}

void CCTouchHandler::setEnalbedSelectors(int nValue)
{
    _enabledSelectors = nValue;
}

CCTouchHandler* CCTouchHandler::handlerWithDelegate(CCTouchDelegate *pDelegate, int nPriority)
{
    CCTouchHandler *pHandler = new CCTouchHandler();

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

bool CCTouchHandler::initWithDelegate(CCTouchDelegate *pDelegate, int nPriority)
{
    CCAssert(pDelegate != NULL, "touch delegate should not be null");

    _delegate = pDelegate; 

    dynamic_cast<CCObject*>(pDelegate)->retain();

    _priority = nPriority;
    _enabledSelectors = 0;

    return true;
}

CCTouchHandler::~CCTouchHandler(void)
{
    if (_delegate)
    {
        dynamic_cast<CCObject*>(_delegate)->release();
    }   
}

// implementation of CCStandardTouchHandler
bool CCStandardTouchHandler::initWithDelegate(CCTouchDelegate *pDelegate, int nPriority)
{
    if (CCTouchHandler::initWithDelegate(pDelegate, nPriority))
    {
        return true;
    }

    return false;
}

CCStandardTouchHandler* CCStandardTouchHandler::handlerWithDelegate(CCTouchDelegate *pDelegate, int nPriority)
{
    CCStandardTouchHandler* pHandler = new CCStandardTouchHandler();

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

// implementation of CCTargetedTouchHandler

bool CCTargetedTouchHandler::isSwallowsTouches(void)
{
    return _swallowsTouches;
}

void CCTargetedTouchHandler::setSwallowsTouches(bool bSwallowsTouches)
{
    _swallowsTouches = bSwallowsTouches;
}

CCSet* CCTargetedTouchHandler::getClaimedTouches(void)
{
    return _claimedTouches;
}

CCTargetedTouchHandler* CCTargetedTouchHandler::handlerWithDelegate(CCTouchDelegate *pDelegate, int nPriority, bool bSwallow)
{
    CCTargetedTouchHandler *pHandler = new CCTargetedTouchHandler();
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

bool CCTargetedTouchHandler::initWithDelegate(CCTouchDelegate *pDelegate, int nPriority, bool bSwallow)
{
    if (CCTouchHandler::initWithDelegate(pDelegate, nPriority))
    {
        _claimedTouches = new CCSet();
        _swallowsTouches = bSwallow;

        return true;
    }

    return false;
}

CCTargetedTouchHandler::~CCTargetedTouchHandler(void)
{
    CC_SAFE_RELEASE(_claimedTouches);
}

NS_CC_END

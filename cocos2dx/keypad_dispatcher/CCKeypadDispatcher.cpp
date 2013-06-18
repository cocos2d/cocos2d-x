/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCKeypadDispatcher.h"
#include "support/data_support/ccCArray.h"

NS_CC_BEGIN

//------------------------------------------------------------------
//
// CCKeypadDispatcher
//
//------------------------------------------------------------------
CCKeypadDispatcher::CCKeypadDispatcher()
: _locked(false)
, _toAdd(false)
, _toRemove(false)
{
    _delegates = CCArray::create();
    _delegates->retain();

    _handlersToAdd    = ccCArrayNew(8);
    _handlersToRemove = ccCArrayNew(8);
}

CCKeypadDispatcher::~CCKeypadDispatcher()
{
    CC_SAFE_RELEASE(_delegates);
    if (_handlersToAdd)
    {
        ccCArrayFree(_handlersToAdd);
    }
    
    if (_handlersToRemove)
    {
        ccCArrayFree(_handlersToRemove);
    }    
}

void CCKeypadDispatcher::removeDelegate(CCKeypadDelegate* pDelegate)
{
    if (!pDelegate)
    {
        return;
    }
    if (! _locked)
    {
        forceRemoveDelegate(pDelegate);
    }
    else
    {
        ccCArrayAppendValue(_handlersToRemove, pDelegate);
        _toRemove = true;
    }
}

void CCKeypadDispatcher::addDelegate(CCKeypadDelegate* pDelegate)
{
    if (!pDelegate)
    {
        return;
    }

    if (! _locked)
    {
        forceAddDelegate(pDelegate);
    }
    else
    {
        ccCArrayAppendValue(_handlersToAdd, pDelegate);
        _toAdd = true;
    }
}

void CCKeypadDispatcher::forceAddDelegate(CCKeypadDelegate* pDelegate)
{
    CCKeypadHandler* pHandler = CCKeypadHandler::handlerWithDelegate(pDelegate);

    if (pHandler)
    {
        _delegates->addObject(pHandler);
    }
}

void CCKeypadDispatcher::forceRemoveDelegate(CCKeypadDelegate* pDelegate)
{
    CCKeypadHandler* pHandler = NULL;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(_delegates, pObj)
    {
        pHandler = (CCKeypadHandler*)pObj;
        if (pHandler && pHandler->getDelegate() == pDelegate)
        {
            _delegates->removeObject(pHandler);
            break;
        }
    }
}

bool CCKeypadDispatcher::dispatchKeypadMSG(ccKeypadMSGType nMsgType)
{
    CCKeypadHandler*  pHandler = NULL;
    CCKeypadDelegate* pDelegate = NULL;

    _locked = true;

    if (_delegates->count() > 0)
    {
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(_delegates, pObj)
        {
            CC_BREAK_IF(!pObj);

            pHandler = (CCKeypadHandler*)pObj;
            pDelegate = pHandler->getDelegate();

            switch (nMsgType)
            {
            case kTypeBackClicked:
                pDelegate->keyBackClicked();
                break;
            case kTypeMenuClicked:
                pDelegate->keyMenuClicked();
                break;
            default:
                break;
            }
        }
    }

    _locked = false;
    if (_toRemove)
    {
        _toRemove = false;
        for (unsigned int i = 0; i < _handlersToRemove->num; ++i)
        {
            forceRemoveDelegate((CCKeypadDelegate*)_handlersToRemove->arr[i]);
        }
        ccCArrayRemoveAllValues(_handlersToRemove);
    }

    if (_toAdd)
    {
        _toAdd = false;
        for (unsigned int i = 0; i < _handlersToAdd->num; ++i)
        {
            forceAddDelegate((CCKeypadDelegate*)_handlersToAdd->arr[i]);
        }
        ccCArrayRemoveAllValues(_handlersToAdd);
    }

    return true;
}

NS_CC_END

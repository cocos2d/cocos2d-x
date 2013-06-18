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


#include "CCObject.h"
#include "CCAutoreleasePool.h"
#include "ccMacros.h"
#include "script_support/CCScriptSupport.h"

NS_CC_BEGIN

CCObject* CCCopying::copyWithZone(CCZone *pZone)
{
    CC_UNUSED_PARAM(pZone);
    CCAssert(0, "not implement");
    return 0;
}

CCObject::CCObject(void)
: _luaID(0)
, _reference(1) // when the object is created, the reference count of it is 1
, _autoReleaseCount(0)
{
    static unsigned int uObjectCount = 0;

    _ID = ++uObjectCount;
}

CCObject::~CCObject(void)
{
    // if the object is managed, we should remove it
    // from pool manager
    if (_autoReleaseCount > 0)
    {
        CCPoolManager::sharedPoolManager()->removeObject(this);
    }

    // if the object is referenced by Lua engine, remove it
    if (_luaID)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptObjectByCCObject(this);
    }
    else
    {
        CCScriptEngineProtocol* pEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
        if (pEngine != NULL && pEngine->getScriptType() == kScriptTypeJavascript)
        {
            pEngine->removeScriptObjectByCCObject(this);
        }
    }
}

CCObject* CCObject::copy()
{
    return copyWithZone(0);
}

void CCObject::release(void)
{
    CCAssert(_reference > 0, "reference count should greater than 0");
    --_reference;

    if (_reference == 0)
    {
        delete this;
    }
}

void CCObject::retain(void)
{
    CCAssert(_reference > 0, "reference count should greater than 0");

    ++_reference;
}

CCObject* CCObject::autorelease(void)
{
    CCPoolManager::sharedPoolManager()->addObject(this);
    return this;
}

bool CCObject::isSingleReference(void) const
{
    return _reference == 1;
}

unsigned int CCObject::retainCount(void) const
{
    return _reference;
}

bool CCObject::isEqual(const CCObject *pObject)
{
    return this == pObject;
}

void CCObject::acceptVisitor(CCDataVisitor &visitor)
{
    visitor.visitObject(this);
}

NS_CC_END

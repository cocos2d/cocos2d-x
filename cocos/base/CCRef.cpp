/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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

#include "base/CCRef.h"
#include "base/CCAutoreleasePool.h"
#include "base/ccMacros.h"
#include "2d/CCScriptSupport.h"

NS_CC_BEGIN

#ifdef CC_USE_MEM_LEAK_DETECTION
void trackRef(Ref* ref);
void untrackRef(Ref* ref);
#endif

Ref::Ref()
: _referenceCount(1) // when the Ref is created, the reference count of it is 1
{
#if CC_ENABLE_SCRIPT_BINDING
    static unsigned int uObjectCount = 0;
    _luaID = 0;
    _ID = ++uObjectCount;
#endif
    trackRef(this);
}

Ref::~Ref()
{
#if CC_ENABLE_SCRIPT_BINDING
    // if the object is referenced by Lua engine, remove it
    if (_luaID)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptObjectByObject(this);
    }
    else
    {
        ScriptEngineProtocol* pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
        if (pEngine != NULL && pEngine->getScriptType() == kScriptTypeJavascript)
        {
            pEngine->removeScriptObjectByObject(this);
        }
    }
#endif
    

#ifdef CC_USE_MEM_LEAK_DETECTION
    if (_referenceCount != 0)
        untrackRef(this);
#endif
    
    //CCASSERT(0 == _referenceCount, "Ref class has to be deleted by Ref::release(), don't use 'delete pointer' directly.");
}

void Ref::retain()
{
    CCASSERT(_referenceCount > 0, "reference count should greater than 0");
    ++_referenceCount;
}

void Ref::release()
{
    CCASSERT(_referenceCount > 0, "reference count should greater than 0");
    --_referenceCount;
    
    if (_referenceCount == 0)
    {
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
        auto poolManager = PoolManager::getInstance();
        if (!poolManager->getCurrentPool()->isClearing() && poolManager->isObjectInPools(this))
        {
            // Trigger an assert if the reference count is 0 but the Ref is still in autorelease pool.
            // This happens when 'autorelease/release' were not used in pairs with 'new/retain'.
            //
            // Wrong usage (1):
            //
            // auto obj = Node::create();   // Ref = 1, but it's an autorelease Ref which means it was in the autorelease pool.
            // obj->autorelease();   // Wrong: If you wish to invoke autorelease several times, you should retain `obj` first.
            //
            // Wrong usage (2):
            //
            // auto obj = Node::create();
            // obj->release();   // Wrong: obj is an autorelease Ref, it will be released when clearing current pool.
            //
            // Correct usage (1):
            //
            // auto obj = Node::create();
            //                     |-   new Node();     // `new` is the pair of the `autorelease` of next line
            //                     |-   autorelease();  // The pair of `new Node`.
            //
            // obj->retain();
            // obj->autorelease();  // This `autorelease` is the pair of `retain` of previous line.
            //
            // Correct usage (2):
            //
            // auto obj = Node::create();
            // obj->retain();
            // obj->release();   // This `release` is the pair of `retain` of previous line.
            CCASSERT(false, "The reference shouldn't be 0 because it is still in autorelease pool.");
        }
#endif
        
#ifdef CC_USE_MEM_LEAK_DETECTION
        untrackRef(this);
#endif
        delete this;
    }
}

Ref* Ref::autorelease()
{
    PoolManager::getInstance()->getCurrentPool()->addObject(this);
    return this;
}

unsigned int Ref::getReferenceCount() const
{
    return _referenceCount;
}

#ifdef CC_USE_MEM_LEAK_DETECTION

static std::list<Ref*> __refAllocationList;

void Ref::printLeaks()
{
    // Dump Ref object memory leaks
    if (__refAllocationList.empty())
    {
        log("[memory] All Ref objects successfully cleaned up (no leaks detected).\n");
    }
    else
    {
        log("[memory] WARNING: %d Ref objects still active in memory.\n", (int)__refAllocationList.size());
        
        for (const auto& ref : __refAllocationList)
        {
            CC_ASSERT(ref);
            const char* type = typeid(*ref).name();
            log("[memory] LEAK: Ref object '%s' still active with reference count %d.\n", (type ? type : ""), ref->getReferenceCount());
        }
    }
}

void trackRef(Ref* ref)
{
    CC_ASSERT(ref);
    
    // Create memory allocation record.
    __refAllocationList.push_back(ref);
}

void untrackRef(Ref* ref)
{
    auto iter = std::find(__refAllocationList.begin(), __refAllocationList.end(), ref);
    if (iter == __refAllocationList.end())
    {
        log("[memory] CORRUPTION: Attempting to free (%s) with invalid ref tracking record.\n", typeid(*ref).name());
        return;
    }
    
    __refAllocationList.erase(iter);
}

#endif


NS_CC_END

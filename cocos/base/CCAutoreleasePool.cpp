/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "base/CCAutoreleasePool.h"
#include "base/ccMacros.h"

#include <algorithm>
#include <memory>

NS_CC_BEGIN

AutoreleasePool::AutoreleasePool()
: _name("")
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
, _isClearing(false)
#endif
{
    _managedObjectArray.reserve(150);
    PoolManager::getInstance()->push(this);
}

AutoreleasePool::AutoreleasePool(const std::string &name)
: _name(name)
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
, _isClearing(false)
#endif
{
    _managedObjectArray.reserve(150);
    PoolManager::getInstance()->push(this);
}

AutoreleasePool::~AutoreleasePool()
{
    CCLOGINFO("deallocing AutoreleasePool: %p", this);
    clear();
    
    PoolManager::getInstance()->pop();
}

void AutoreleasePool::addObject(Ref* object)
{
    _managedObjectArray.push_back(object);
}

void AutoreleasePool::clear()
{
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    _isClearing = true;
#endif
    for (const auto &obj : _managedObjectArray)
    {
        obj->release();
    }
    _managedObjectArray.clear();
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    _isClearing = false;
#endif
}

bool AutoreleasePool::contains(Ref* object) const
{
    for (const auto& obj : _managedObjectArray)
    {
        if (obj == object)
            return true;
    }
    return false;
}

void AutoreleasePool::dump()
{
    CCLOG("autorelease pool: %s, number of managed object %d\n", _name.c_str(), static_cast<int>(_managedObjectArray.size()));
    CCLOG("%20s%20s%20s", "Object pointer", "Object id", "reference count");
    for (const auto &obj : _managedObjectArray)
    {
        CC_UNUSED_PARAM(obj);
        CCLOG("%20p%20u\n", obj, obj->getReferenceCount());
    }
}


//--------------------------------------------------------------------
//
// PoolManager
//
//--------------------------------------------------------------------

PoolManager* PoolManager::s_singleInstance = nullptr;

PoolManager* PoolManager::getInstance()
{
    if (s_singleInstance == nullptr)
    {
        s_singleInstance = new PoolManager();

        // Create top level autorelease pool.
        //
        // AutoreleasePool's constructor will push itself to PoolManager::getInstance().
        auto topPool = new AutoreleasePool("cocos2d autorelease pool");
        CC_ASSERT(s_singleInstance->_releasePoolStack.size() == 1);
        CC_ASSERT(topPool == s_singleInstance->getCurrentPool());
        (void)topPool;
    }
    return s_singleInstance;
}

void PoolManager::destroyInstance()
{
    delete s_singleInstance;
    s_singleInstance = nullptr;
}

PoolManager::PoolManager()
{
    _releasePoolStack.reserve(16);
}

PoolManager::~PoolManager()
{
    CCLOGINFO("deallocing PoolManager: %p", this);

    std::for_each(_releasePoolStack.begin(), _releasePoolStack.end(), std::default_delete<AutoreleasePool>());
}


AutoreleasePool* PoolManager::getCurrentPool() const
{
    CC_ASSERT(!_releasePoolStack.empty());
    return _releasePoolStack.back();
}

bool PoolManager::isObjectInPools(Ref* obj) const
{
    auto end = _releasePoolStack.end();
    return end != std::find_if(_releasePoolStack.begin(), end, [obj] (AutoreleasePool *pool) { return pool->contains(obj); });
}

void PoolManager::push(AutoreleasePool *pool)
{
    _releasePoolStack.push_back(pool);
}

void PoolManager::pop()
{
    // Can not pop the pool that created by engine
    CC_ASSERT(_releasePoolStack.size() > 1);

    _releasePoolStack.pop_back();
}

NS_CC_END

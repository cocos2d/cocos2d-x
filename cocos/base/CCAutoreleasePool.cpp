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
#include "CCAutoreleasePool.h"
#include "ccMacros.h"

NS_CC_BEGIN

AutoreleasePool::AutoreleasePool()
{
    _managedObjectArray.reserve(150);
    
    PoolManager::getInstance()->push(this);
}

AutoreleasePool::~AutoreleasePool()
{
    CCLOGINFO("deallocing AutoreleasePool: %p", this);
    _managedObjectArray.clear();
    
    PoolManager::getInstance()->pop();
}

void AutoreleasePool::addObject(Object* object)
{
    _managedObjectArray.pushBack(object);

    CCASSERT(object->_reference > 1, "reference count should be greater than 1");
}

void AutoreleasePool::clear()
{
    if (!_managedObjectArray.empty())
    {
        _managedObjectArray.clear();
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
        // Add the first auto release pool
        s_singleInstance->_curReleasePool = new AutoreleasePool();
        s_singleInstance->_releasePoolStack.push(s_singleInstance->_curReleasePool);
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
}

PoolManager::~PoolManager()
{
    CCLOGINFO("deallocing PoolManager: %p", this);
    
    while (!_releasePoolStack.empty())
    {
        AutoreleasePool* pool = _releasePoolStack.top();
        _releasePoolStack.pop();
        
        delete pool;
    }
}


AutoreleasePool* PoolManager::getCurrentPool() const
{
    return _curReleasePool;
}

void PoolManager::push(AutoreleasePool *pool)
{
    _releasePoolStack.push(pool);
    _curReleasePool = pool;
}

void PoolManager::pop()
{
    // Can not pop the pool that created by engine
    CC_ASSERT(_releasePoolStack.size() >= 1);
    
    _releasePoolStack.pop();
    
    // Should update _curReleasePool if a temple pool is released
    if (_releasePoolStack.size() > 1)
    {
        _curReleasePool = _releasePoolStack.top();
    }
}

NS_CC_END

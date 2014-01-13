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

static PoolManager* s_pPoolManager = NULL;

AutoreleasePool::AutoreleasePool()
{
    _managedObjectArray.reserve(150);
}

AutoreleasePool::~AutoreleasePool()
{
    CCLOGINFO("deallocing AutoreleasePool: %p", this);
}

void AutoreleasePool::addObject(Object* object)
{
    _managedObjectArray.pushBack(object);

    CCASSERT(object->_reference > 1, "reference count should be greater than 1");
    ++(object->_autoReleaseCount);
    object->release(); // no ref count, in this case autorelease pool added.
}

void AutoreleasePool::removeObject(Object* object)
{
    for (unsigned int i = 0; i < object->_autoReleaseCount; ++i)
    {
       _managedObjectArray.eraseObject(object, false);
    }
}

void AutoreleasePool::clear()
{
    if (!_managedObjectArray.empty())
    {
        //CCAutoreleasePool* pReleasePool;
#ifdef _DEBUG
        int nIndex = _managedObjectArray.size() - 1;
#endif

        for(const auto &obj : _managedObjectArray) {
            --(obj->_autoReleaseCount);
            //(*it)->release();
            //delete (*it);
#ifdef _DEBUG
            nIndex--;
#endif
        }

        _managedObjectArray.clear();
    }
}


//--------------------------------------------------------------------
//
// PoolManager
//
//--------------------------------------------------------------------

PoolManager* PoolManager::sharedPoolManager()
{
    if (s_pPoolManager == NULL)
    {
        s_pPoolManager = new PoolManager();
    }
    return s_pPoolManager;
}

void PoolManager::purgePoolManager()
{
    CC_SAFE_DELETE(s_pPoolManager);
}

PoolManager::PoolManager()
{
    _releasePoolStack.reserve(150);
    _curReleasePool = 0;
}

PoolManager::~PoolManager()
{
    CCLOGINFO("deallocing PoolManager: %p", this);
    finalize();
 
     // we only release the last autorelease pool here 
    _curReleasePool = 0;
    _releasePoolStack.erase(0);
}

void PoolManager::finalize()
{
    if (!_releasePoolStack.empty())
    {
        for(const auto &pool : _releasePoolStack) {
            pool->clear();
        }
    }
}

void PoolManager::push()
{
    AutoreleasePool* pool = new AutoreleasePool();       //ref = 1
    _curReleasePool = pool;

    _releasePoolStack.pushBack(pool);                   //ref = 2

    pool->release();                                       //ref = 1
}

void PoolManager::pop()
{
    if (! _curReleasePool)
    {
        return;
    }

    ssize_t count = _releasePoolStack.size();

    _curReleasePool->clear();
 
    if (count > 1)
    {
        _releasePoolStack.erase(count-1);

//         if(nCount > 1)
//         {
//             _curReleasePool = _releasePoolStack.at(count - 2);
//             return;
//         }
        _curReleasePool = _releasePoolStack.at(count - 2);
    }

    /*_curReleasePool = NULL;*/
}

void PoolManager::removeObject(Object* object)
{
    CCASSERT(_curReleasePool, "current auto release pool should not be null");

    _curReleasePool->removeObject(object);
}

void PoolManager::addObject(Object* object)
{
    getCurReleasePool()->addObject(object);
}


AutoreleasePool* PoolManager::getCurReleasePool()
{
    if(!_curReleasePool)
    {
        push();
    }

    CCASSERT(_curReleasePool, "current auto release pool should not be null");

    return _curReleasePool;
}

NS_CC_END

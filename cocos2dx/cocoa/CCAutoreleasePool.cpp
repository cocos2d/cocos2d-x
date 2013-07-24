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
#include "CCAutoreleasePool.h"
#include "ccMacros.h"

NS_CC_BEGIN

static PoolManager* s_pPoolManager = NULL;

AutoreleasePool::AutoreleasePool(void)
{
    _managedObjectArray = new Array();
    _managedObjectArray->init();
}

AutoreleasePool::~AutoreleasePool(void)
{
    CC_SAFE_DELETE(_managedObjectArray);
}

void AutoreleasePool::addObject(Object* pObject)
{
    _managedObjectArray->addObject(pObject);

    CCASSERT(pObject->_reference > 1, "reference count should be greater than 1");
    ++(pObject->_autoReleaseCount);
    pObject->release(); // no ref count, in this case autorelease pool added.
}

void AutoreleasePool::removeObject(Object* pObject)
{
    for (unsigned int i = 0; i < pObject->_autoReleaseCount; ++i)
    {
        _managedObjectArray->removeObject(pObject, false);
    }
}

void AutoreleasePool::clear()
{
    if(_managedObjectArray->count() > 0)
    {
        //CCAutoreleasePool* pReleasePool;
#ifdef _DEBUG
        int nIndex = _managedObjectArray->count() - 1;
#endif

        Object* pObj = NULL;
        CCARRAY_FOREACH_REVERSE(_managedObjectArray, pObj)
        {
            if(!pObj)
                break;

            --(pObj->_autoReleaseCount);
            //(*it)->release();
            //delete (*it);
#ifdef _DEBUG
            nIndex--;
#endif
        }

        _managedObjectArray->removeAllObjects();
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
    _releasePoolStack = new Array();    
    _releasePoolStack->init();
    _curReleasePool = 0;
}

PoolManager::~PoolManager()
{
    
     finalize();
 
     // we only release the last autorelease pool here 
    _curReleasePool = 0;
     _releasePoolStack->removeObjectAtIndex(0);
 
     CC_SAFE_DELETE(_releasePoolStack);
}

void PoolManager::finalize()
{
    if(_releasePoolStack->count() > 0)
    {
        //CCAutoreleasePool* pReleasePool;
        Object* pObj = NULL;
        CCARRAY_FOREACH(_releasePoolStack, pObj)
        {
            if(!pObj)
                break;
            AutoreleasePool* pPool = static_cast<AutoreleasePool*>(pObj);
            pPool->clear();
        }
    }
}

void PoolManager::push()
{
    AutoreleasePool* pPool = new AutoreleasePool();       //ref = 1
    _curReleasePool = pPool;

    _releasePoolStack->addObject(pPool);                   //ref = 2

    pPool->release();                                       //ref = 1
}

void PoolManager::pop()
{
    if (! _curReleasePool)
    {
        return;
    }

     int nCount = _releasePoolStack->count();

    _curReleasePool->clear();
 
      if(nCount > 1)
      {
        _releasePoolStack->removeObjectAtIndex(nCount-1);

//         if(nCount > 1)
//         {
//             _curReleasePool = _releasePoolStack->objectAtIndex(nCount - 2);
//             return;
//         }
        _curReleasePool = (AutoreleasePool*)_releasePoolStack->objectAtIndex(nCount - 2);
    }

    /*_curReleasePool = NULL;*/
}

void PoolManager::removeObject(Object* pObject)
{
    CCASSERT(_curReleasePool, "current auto release pool should not be null");

    _curReleasePool->removeObject(pObject);
}

void PoolManager::addObject(Object* pObject)
{
    getCurReleasePool()->addObject(pObject);
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

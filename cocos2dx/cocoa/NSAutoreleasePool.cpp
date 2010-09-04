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
#include "NSAutoreleasePool.h"

namespace cocos2d 
{

NSPoolManager	g_PoolManager;

NSAutoreleasePool::NSAutoreleasePool(void)
{
	m_pManagedObjectArray = new NSMutableArray<NSObject*>();
}

NSAutoreleasePool::~NSAutoreleasePool(void)
{
	delete m_pManagedObjectArray;
}

void NSAutoreleasePool::addObject(NSObject* pObject)
{
	m_pManagedObjectArray->addObject(pObject);

	assert(pObject->m_uRefrence > 1);

	pObject->release(); // no ref count, in this case autorelease pool added.
}

void NSAutoreleasePool::removeObject(NSObject* pObject)
{
	m_pManagedObjectArray->removeObject(pObject, false);
}

void NSAutoreleasePool::clear()
{
	if(m_pManagedObjectArray->count() > 0)
	{
		//NSAutoreleasePool* pReleasePool;
#ifdef _DEBUG
		int nIndex = m_pManagedObjectArray->count() - 1;
#endif
		NSMutableArray<NSObject*>::NSMutableArrayRevIterator it;
		for(it = m_pManagedObjectArray->rbegin(); it != m_pManagedObjectArray->rend(); it++)
		{
			if(!*it)
				break;

			(*it)->m_bManaged = false;
			//(*it)->release();
			//delete (*it);
#ifdef _DEBUG
			nIndex--;
#endif
		}

		m_pManagedObjectArray->removeAllObjects();
	}
}


//--------------------------------------------------------------------
//
// NSPoolManager
//
//--------------------------------------------------------------------

NSPoolManager* NSPoolManager::getInstance()
{
	return &g_PoolManager;
}

NSPoolManager::NSPoolManager()
{
	m_pReleasePoolStack = new NSMutableArray<NSAutoreleasePool*>();	
	m_pCurReleasePool = NULL;
}

NSPoolManager::~NSPoolManager()
{
	
	finalize();

	// we only release the last autorelease pool here 
	m_pCurReleasePool = NULL;
	m_pReleasePoolStack->removeObjectAtIndex(0);

	delete m_pReleasePoolStack;
}

void NSPoolManager::finalize()
{
	if(m_pReleasePoolStack->count() > 0)
	{
		//NSAutoreleasePool* pReleasePool;
		NSMutableArray<NSAutoreleasePool*>::NSMutableArrayIterator it;
		for(it = m_pReleasePoolStack->begin(); it != m_pReleasePoolStack->end(); it++)
		{
			if(!*it)
				break;

			(*it)->clear();

			delete (*it);
		}
	}
}

void NSPoolManager::push()
{
	NSAutoreleasePool* pPool = new NSAutoreleasePool();	   //ref = 1
	m_pCurReleasePool = pPool;

	m_pReleasePoolStack->addObject(pPool);				   //ref = 2

	pPool->release();									   //ref = 1
}

void NSPoolManager::pop()
{
 	int nCount = m_pReleasePoolStack->count();

	assert(m_pCurReleasePool);

	m_pCurReleasePool->clear();
 
  	if(nCount > 1)
  	{
		m_pReleasePoolStack->removeObjectAtIndex(nCount-1);

// 		if(nCount > 1)
// 		{
// 			m_pCurReleasePool = m_pReleasePoolStack->getObjectAtIndex(nCount - 2);
// 			return;
// 		}
		m_pCurReleasePool = m_pReleasePoolStack->getObjectAtIndex(nCount - 2);
	}

	/*m_pCurReleasePool = NULL;*/
}

void NSPoolManager::removeObject(NSObject* pObject)
{
	assert(m_pCurReleasePool);

	m_pCurReleasePool->removeObject(pObject);
}

void NSPoolManager::addObject(NSObject* pObject)
{
	getCurReleasePool()->addObject(pObject);
}


NSAutoreleasePool* NSPoolManager::getCurReleasePool()
{
	if(!m_pCurReleasePool)
		push();

	assert(m_pCurReleasePool);

	return m_pCurReleasePool;
}

}

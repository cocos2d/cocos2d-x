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

#include "NSAutoReleasePool.h"
#include <assert.h>
#include <stack>
#include <vector>

using namespace std;
namespace   cocos2d {

NSAutoreleasePool::NSAutoreleasePool(void)
{
	m_pManagedObjectArray = new NSMutableArray<NSObject*>();
}

NSAutoreleasePool::~NSAutoreleasePool(void)
{
	clear();
	delete m_pManagedObjectArray;
}

void NSAutoreleasePool::addObject(NSObject *pObject)
{
	m_pManagedObjectArray->addObject(pObject);
}

void NSAutoreleasePool::removeObject(NSObject *pObject)
{
	m_pManagedObjectArray->removeObject(pObject);
}

void NSAutoreleasePool::clear(void)
{
	if (m_pManagedObjectArray->count())
	{
		NSMutableArray<NSObject*>::NSMutableArrayIterator iter;
		for (iter = m_pManagedObjectArray->begin(); iter != m_pManagedObjectArray->end(); ++iter)
		{
			if (*iter)
			{
				(*iter)->m_bManaged = false;
			}
		}

//		m_pManagedObjectArray->removeAllObjects();
	}
}


// implementiation of NSPoolManager
NSPoolManager* NSPoolManager::m_pPoolManager = NULL;

NSPoolManager* NSPoolManager::getInstance(void)
{
	static bool bInit = false;

	if (bInit == false)
	{
		bInit = true;
		m_pPoolManager = new NSPoolManager();
	}

	return m_pPoolManager;
}

NSPoolManager::NSPoolManager(void)
{
	m_pReleasePoolStack = new stack<NSAutoreleasePool *>();
}

NSPoolManager::~NSPoolManager(void)
{
	finalize();

	delete m_pReleasePoolStack;
}

void NSPoolManager::finalize(void)
{
	if (m_pReleasePoolStack->size() > 0)
	{
		NSAutoreleasePool *pTop;
		while (pTop = m_pReleasePoolStack->top())
		{
			m_pReleasePoolStack->pop();
		}
	}
}

void NSPoolManager::push(void)
{
	NSAutoreleasePool *pPool = new NSAutoreleasePool();

	m_pReleasePoolStack->push(pPool);
}

void NSPoolManager::pop(void)
{
	if (m_pReleasePoolStack->top())
	{
		delete m_pReleasePoolStack->top();
	    m_pReleasePoolStack->pop();
	}

}

void NSPoolManager::addObject(NSObject *pObject)
{
	getCurReleasePool()->addObject(pObject);
}

void NSPoolManager::removeObject(NSObject *pObject)
{
	assert(m_pReleasePoolStack->top());

	m_pReleasePoolStack->top()->removeObject(pObject);
}

NSAutoreleasePool* NSPoolManager::getCurReleasePool(void)
{
	if (m_pReleasePoolStack->empty())
	{
		push();
	}

	return m_pReleasePoolStack->top();
}
}//namespace   cocos2d

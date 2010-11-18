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


#include "NSObject.h"
#include "NSAutoreleasePool.h"
#include <assert.h>
namespace   cocos2d {

NSObject* CCCopying::copyWithZone(NSZone *pZone)
{
	assert(0);
	return NULL;
}


NSObject::NSObject(void)
{
	static unsigned int uObjectCount = 0;

	m_uID = ++uObjectCount;

	// when the object is created, the refrence count of it is 1
	m_uRefrence = 1;
	m_bManaged = false;
}

NSObject::~NSObject(void)
{
	// if the object is managed, we should remove it
	// from pool manager
	if (m_bManaged)
	{
		NSPoolManager::getInstance()->removeObject(this);
	}
}

NSObject* NSObject::copy()
{
	return copyWithZone(NULL);
}

void NSObject::release(void)
{
	assert(m_uRefrence > 0);
	--m_uRefrence;

	if (m_uRefrence == 0)
	{
		delete this;
	}
}

void NSObject::retain(void)
{
	assert(m_uRefrence > 0);

	++m_uRefrence;
}

NSObject* NSObject::autorelease(void)
{
	NSPoolManager::getInstance()->addObject(this);

	m_bManaged = true;
	return this;
}

bool NSObject::isSingleRefrence(void)
{
	return m_uRefrence == 1;
}

unsigned int NSObject::retainCount(void)
{
	return m_uRefrence;
}

bool NSObject::isEqual(const NSObject *pObject)
{
	return this == pObject;
}
}//namespace   cocos2d 

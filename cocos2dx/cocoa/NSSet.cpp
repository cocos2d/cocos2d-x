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

#include "NSSet.h"

using namespace std;

NSSet::NSSet(void)
{
}

NSSet::NSSet(const NSSet &rSetObject) : m_set(rSetObject.m_set)
{
}

NSSet::~NSSet(void)
{
}

NSSet* NSSet::copy(void)
{
	NSSet *pSet = new NSSet(*this);

	return pSet;
}

NSSet* NSSet::mutableCopy(void)
{
	return copy();
}

int NSSet::count(void)
{
	return (int)m_set.size();
}

void NSSet::addObject(NSObject *pObject)
{
	m_set.insert(pObject);
}

void NSSet::removeObject(NSObject *pObject)
{
	m_set.erase(pObject);
}

bool NSSet::containsObject(NSObject *pObject)
{
	return m_set.find(pObject) != m_set.end();
}

NSSetIterator NSSet::begin(void)
{
	return m_set.begin();
}

NSSetIterator NSSet::end(void)
{
	return m_set.end();
}

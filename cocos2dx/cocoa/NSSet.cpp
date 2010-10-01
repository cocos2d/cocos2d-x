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

namespace   cocos2d {

NSSet::NSSet(void)
{
    m_pSet = new set<NSObject *>;
}

NSSet::NSSet(const NSSet &rSetObject)
{
    m_pSet = new set<NSObject *>(*rSetObject.m_pSet);
}

NSSet::~NSSet(void)
{
    if (m_pSet)
    {
        delete m_pSet;
        m_pSet = NULL;
    }
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
	return (int)m_pSet->size();
}

void NSSet::addObject(NSObject *pObject)
{
	m_pSet->insert(pObject);
}

void NSSet::removeObject(NSObject *pObject)
{
	m_pSet->erase(pObject);
}

bool NSSet::containsObject(NSObject *pObject)
{
	return m_pSet->find(pObject) != m_pSet->end();
}

NSSetIterator NSSet::begin(void)
{
	return m_pSet->begin();
}

NSSetIterator NSSet::end(void)
{
	return m_pSet->end();
}

NSObject* NSSet::anyObject()
{
    if (!m_pSet || m_pSet->empty())
    {
        return NULL;
    }
    
    NSSetIterator it;

    for( it = m_pSet->begin(); it != m_pSet->end(); it++)
    {
        if (*it)
        {
            return (*it);
        }
    }

    return NULL;
}

}//namespace   cocos2d 

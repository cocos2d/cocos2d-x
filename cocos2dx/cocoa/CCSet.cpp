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

#include "CCSet.h"

using namespace std;

NS_CC_BEGIN

CCSet::CCSet(void)
{
    m_pSet = new set<CCObject *>;
}

CCSet::CCSet(const CCSet &rSetObject)
{
    m_pSet = new set<CCObject *>(*rSetObject.m_pSet);

    // call retain of members
    CCSetIterator iter;
    for (iter = m_pSet->begin(); iter != m_pSet->end(); ++iter)
    {
        if (! (*iter))
        {
            break;
        }

        (*iter)->retain();
    }
}

CCSet::~CCSet(void)
{
    removeAllObjects();
    CC_SAFE_DELETE(m_pSet);
}

CCSet* CCSet::copy(void)
{
    CCSet *pSet = new CCSet(*this);

    return pSet;
}

CCSet* CCSet::mutableCopy(void)
{
    return copy();
}

int CCSet::count(void)
{
    return (int)m_pSet->size();
}

void CCSet::addObject(CCObject *pObject)
{
    CC_SAFE_RETAIN(pObject);
    m_pSet->insert(pObject);
}

void CCSet::removeObject(CCObject *pObject)
{
    m_pSet->erase(pObject);
    CC_SAFE_RELEASE(pObject);
}

void CCSet::removeAllObjects()
{
    CCSetIterator it;
    for (it = m_pSet->begin(); it != m_pSet->end(); ++it)
    {
        if (! (*it))
        {
            break;
        }

        (*it)->release();
    }
}

bool CCSet::containsObject(CCObject *pObject)
{
    return m_pSet->find(pObject) != m_pSet->end();
}

CCSetIterator CCSet::begin(void)
{
    return m_pSet->begin();
}

CCSetIterator CCSet::end(void)
{
    return m_pSet->end();
}

CCObject* CCSet::anyObject()
{
    if (!m_pSet || m_pSet->empty())
    {
        return 0;
    }
    
    CCSetIterator it;

    for( it = m_pSet->begin(); it != m_pSet->end(); ++it)
    {
        if (*it)
        {
            return (*it);
        }
    }

    return 0;
}

NS_CC_END

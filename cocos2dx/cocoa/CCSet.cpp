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
    _set = new set<CCObject *>;
}

CCSet::CCSet(const CCSet &rSetObject)
{
    _set = new set<CCObject *>(*rSetObject._set);

    // call retain of members
    CCSetIterator iter;
    for (iter = _set->begin(); iter != _set->end(); ++iter)
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
    CC_SAFE_DELETE(_set);
}

void CCSet::acceptVisitor(CCDataVisitor &visitor)
{
    visitor.visit(this);
}

CCSet * CCSet::create()
{
    CCSet * pRet = new CCSet();
    
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    
    return pRet;
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
    return (int)_set->size();
}

void CCSet::addObject(CCObject *pObject)
{
    CC_SAFE_RETAIN(pObject);
    _set->insert(pObject);
}

void CCSet::removeObject(CCObject *pObject)
{
    _set->erase(pObject);
    CC_SAFE_RELEASE(pObject);
}

void CCSet::removeAllObjects()
{
    CCSetIterator it;
    for (it = _set->begin(); it != _set->end(); ++it)
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
    return _set->find(pObject) != _set->end();
}

CCSetIterator CCSet::begin(void)
{
    return _set->begin();
}

CCSetIterator CCSet::end(void)
{
    return _set->end();
}

CCObject* CCSet::anyObject()
{
    if (!_set || _set->empty())
    {
        return 0;
    }
    
    CCSetIterator it;

    for( it = _set->begin(); it != _set->end(); ++it)
    {
        if (*it)
        {
            return (*it);
        }
    }

    return 0;
}

NS_CC_END

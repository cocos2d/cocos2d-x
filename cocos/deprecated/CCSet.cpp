/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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

__Set::__Set(void)
{
    _set = new set<Ref *>;
}

__Set::__Set(const __Set &other)
{
    _set = new set<Ref *>(*other._set);

    // call retain of members
    __SetIterator iter;
    for (iter = _set->begin(); iter != _set->end(); ++iter)
    {
        if (! (*iter))
        {
            break;
        }

        (*iter)->retain();
    }
}

__Set::~__Set(void)
{
    removeAllObjects();
    CC_SAFE_DELETE(_set);
}

void __Set::acceptVisitor(DataVisitor &visitor)
{
    visitor.visit(this);
}

__Set * __Set::create()
{
    __Set * pRet = new __Set();
    
    if (pRet != nullptr)
    {
        pRet->autorelease();
    }
    
    return pRet;
}

__Set* __Set::copy(void)
{
    __Set *p__Set = new __Set(*this);

    return p__Set;
}

__Set* __Set::mutableCopy(void)
{
    return copy();
}

int __Set::count(void)
{
    return (int)_set->size();
}

void __Set::addObject(Ref *pObject)
{
    if (_set->count(pObject) == 0)
    {
        CC_SAFE_RETAIN(pObject);
        _set->insert(pObject);
    }
}

void __Set::removeObject(Ref *pObject)
{
    if (_set->erase(pObject) > 0)
    {
        CC_SAFE_RELEASE(pObject);
    }
}

void __Set::removeAllObjects()
{
    __SetIterator it = _set->begin();
    __SetIterator tmp;

    while (it != _set->end())
    {
        if (!(*it))
        {
            break;
        }
        
        tmp = it;
        ++tmp;
        Ref * obj = *it;
        _set->erase(it);
        CC_SAFE_RELEASE(obj);
        it = tmp;
    }
}

bool __Set::containsObject(Ref *pObject)
{
    return _set->find(pObject) != _set->end();
}

__SetIterator __Set::begin(void)
{
    return _set->begin();
}

__SetIterator __Set::end(void)
{
    return _set->end();
}

Ref* __Set::anyObject()
{
    if (!_set || _set->empty())
    {
        return 0;
    }
    
    __SetIterator it;

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

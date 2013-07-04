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

Set::Set(void)
{
    _set = new set<Object *>;
}

Set::Set(const Set &rSetObject)
{
    _set = new set<Object *>(*rSetObject._set);

    // call retain of members
    SetIterator iter;
    for (iter = _set->begin(); iter != _set->end(); ++iter)
    {
        if (! (*iter))
        {
            break;
        }

        (*iter)->retain();
    }
}

Set::~Set(void)
{
    removeAllObjects();
    CC_SAFE_DELETE(_set);
}

void Set::acceptVisitor(DataVisitor &visitor)
{
    visitor.visit(this);
}

Set * Set::create()
{
    Set * pRet = new Set();
    
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    
    return pRet;
}

Set* Set::copy(void)
{
    Set *pSet = new Set(*this);

    return pSet;
}

Set* Set::mutableCopy(void)
{
    return copy();
}

int Set::count(void)
{
    return (int)_set->size();
}

void Set::addObject(Object *pObject)
{
    if (_set->count(pObject) == 0)
    {
        CC_SAFE_RETAIN(pObject);
        _set->insert(pObject);
    }
}

void Set::removeObject(Object *pObject)
{
    if (_set->erase(pObject) > 0)
    {
        CC_SAFE_RELEASE(pObject);
    }
}

void Set::removeAllObjects()
{
    SetIterator it = _set->begin();
    SetIterator tmp;

    while (it != _set->end())
    {
        if (!(*it))
        {
            break;
        }
        
        tmp = it;
        ++tmp;
        _set->erase(it);
        it = tmp;
    }
}

bool Set::containsObject(Object *pObject)
{
    return _set->find(pObject) != _set->end();
}

SetIterator Set::begin(void)
{
    return _set->begin();
}

SetIterator Set::end(void)
{
    return _set->end();
}

Object* Set::anyObject()
{
    if (!_set || _set->empty())
    {
        return 0;
    }
    
    SetIterator it;

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

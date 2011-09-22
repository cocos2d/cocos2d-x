/****************************************************************************
Copyright (c) 2010 ForzeField Studios S.L. http://forzefield.com
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

#include "CCArray.h"

namespace cocos2d
{

CCArray* CCArray::array()
{
    CCArray* pArray = new CCArray();

    if (pArray && pArray->init())
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }
    
    return pArray;
}

CCArray* CCArray::arrayWithCapacity(unsigned int capacity)
{
    CCArray* pArray = new CCArray();

    if (pArray && pArray->initWithCapacity(capacity))
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }

    return pArray;
}

CCArray* CCArray::arrayWithArray(CCArray* otherArray)
{
    CCArray* pArray = new CCArray();

    if (pArray && pArray->initWithArray(otherArray))
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }

    return pArray;
}

bool CCArray::init()
{
    return initWithCapacity(1);
}

bool CCArray::initWithCapacity(unsigned int capacity)
{
    data = ccArrayNew(capacity);
    return true;
}

bool CCArray::initWithArray(CCArray* otherArray)
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! initWithCapacity(otherArray->data->num));

        addObjectsFromArray(otherArray);
        bRet = true;
    } while (0);
    
    return bRet;
}

unsigned int CCArray::count()
{
    return data->num;
}

unsigned int CCArray::capacity()
{
    return data->max;
}

unsigned int CCArray::indexOfObject(CCObject* object)
{
    return ccArrayGetIndexOfObject(data, object);
}

CCObject* CCArray::objectAtIndex(unsigned int index)
{
    CCAssert(index < data->num, "index out of range in objectAtIndex()");

    return data->arr[index];
}

CCObject* CCArray::lastObject()
{
    if( data->num > 0 )
        return data->arr[data->num-1];

    return NULL;
}

CCObject* CCArray::randomObject()
{
    if(data->num==0) return NULL;

    return data->arr[(int)(data->num*CCRANDOM_0_1())];
}

bool CCArray::containsObject(CCObject* object)
{
    return ccArrayContainsObject(data, object);
}

void CCArray::addObject(CCObject* object)
{
    ccArrayAppendObjectWithResize(data, object);
}

void CCArray::addObjectsFromArray(CCArray* otherArray)
{
    ccArrayAppendArrayWithResize(data, otherArray->data);
}

void CCArray::insertObject(CCObject* object, unsigned int index)
{
    ccArrayInsertObjectAtIndex(data, object, index);
}

void CCArray::removeLastObject()
{
    CCAssert(data->num, "no objects added");
    ccArrayRemoveObjectAtIndex(data, data->num-1);
}

void CCArray::removeObject(CCObject* object)
{
    ccArrayRemoveObject(data, object);
}

void CCArray::removeObjectAtIndex(unsigned int index)
{
    ccArrayRemoveObjectAtIndex(data, index);
}

void CCArray::removeObjectsInArray(CCArray* otherArray)
{
    ccArrayRemoveArray(data, otherArray->data);
}

void CCArray::removeAllObjects()
{
    ccArrayRemoveAllObjects(data);
}

void CCArray::fastRemoveObjectAtIndex(unsigned int index)
{
    ccArrayFastRemoveObjectAtIndex(data, index);
}

void CCArray::fastRemoveObject(CCObject* object)
{
    ccArrayFastRemoveObject(data, object);
}

void CCArray::exchangeObject(CCObject* object1, CCObject* object2)
{
    unsigned int index1 = ccArrayGetIndexOfObject(data, object1);
    if(index1 == UINT_MAX)
    {
        return;
    }

    unsigned int index2 = ccArrayGetIndexOfObject(data, object2);
    if(index2 == UINT_MAX)
    {
        return;
    }

    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void CCArray::exchangeObjectAtIndex(unsigned int index1, unsigned int index2)
{
    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void CCArray::reverseObjects()
{
    if (data->num > 1)
    {
        //floor it since in case of a oneven number the number of swaps stays the same
        int count = (int) floorf(data->num/2.f); 
        unsigned int maxIndex = data->num - 1;

        for (int i = 0; i < count ; i++)
        {
            ccArraySwapObjectsAtIndexes(data, i, maxIndex);
            maxIndex--;
        }
    }
}

void CCArray::reduceMemoryFootprint()
{
    ccArrayShrink(data);
}

CCArray::~CCArray()
{
    ccArrayFree(data);
}

}

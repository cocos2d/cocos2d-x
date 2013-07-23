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
#include "CCString.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN


Array::Array()
: data(NULL)
{
    init();
}

Array::Array(unsigned int capacity)
: data(NULL)
{
    initWithCapacity(capacity);
}

Array* Array::create()
{
    Array* pArray = new Array();

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

Array* Array::createWithObject(Object* pObject)
{
    Array* pArray = new Array();

    if (pArray && pArray->initWithObject(pObject))
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }

    return pArray;
}

Array* Array::create(Object* pObject, ...)
{
    va_list args;
    va_start(args,pObject);

    Array* pArray = create();
    if (pArray && pObject)
    {
        pArray->addObject(pObject);
        Object *i = va_arg(args, Object*);
        while(i) 
        {
            pArray->addObject(i);
            i = va_arg(args, Object*);
        }
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }

    va_end(args);

    return pArray;
}

Array* Array::createWithArray(Array* otherArray)
{
    return otherArray->clone();
}

Array* Array::createWithCapacity(unsigned int capacity)
{
    Array* pArray = new Array();
    
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

Array* Array::createWithContentsOfFile(const char* pFileName)
{
    Array* pRet = Array::createWithContentsOfFileThreadSafe(pFileName);
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

Array* Array::createWithContentsOfFileThreadSafe(const char* pFileName)
{
    return FileUtils::getInstance()->createArrayWithContentsOfFile(pFileName);
}

bool Array::init()
{
    return initWithCapacity(1);
}

bool Array::initWithObject(Object* pObject)
{
    ccArrayFree(data);
    bool bRet = initWithCapacity(1);
    if (bRet)
    {
        addObject(pObject);
    }
    return bRet;
}

/** Initializes an array with some objects */
bool Array::initWithObjects(Object* pObject, ...)
{
    ccArrayFree(data);
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(pObject == NULL);

        va_list args;
        va_start(args, pObject);

        if (pObject)
        {
            this->addObject(pObject);
            Object* i = va_arg(args, Object*);
            while(i) 
            {
                this->addObject(i);
                i = va_arg(args, Object*);
            }
            bRet = true;
        }
        va_end(args);

    } while (false);

    return bRet;
}

bool Array::initWithCapacity(unsigned int capacity)
{
    ccArrayFree(data);
    data = ccArrayNew(capacity);
    return true;
}

bool Array::initWithArray(Array* otherArray)
{
    ccArrayFree(data);
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! initWithCapacity(otherArray->data->num));

        addObjectsFromArray(otherArray);
        bRet = true;
    } while (0);
    
    return bRet;
}

unsigned int Array::count() const
{
    return data->num;
}

unsigned int Array::capacity() const
{
    return data->max;
}

unsigned int Array::indexOfObject(Object* object) const
{
    return ccArrayGetIndexOfObject(data, object);
}

Object* Array::objectAtIndex(unsigned int index)
{
    CCASSERT(index < data->num, "index out of range in objectAtIndex()");

    return data->arr[index];
}

Object* Array::lastObject()
{
    if( data->num > 0 )
        return data->arr[data->num-1];

    return NULL;
}

Object* Array::randomObject()
{
    if (data->num==0)
    {
        return NULL;
    }

    float r = CCRANDOM_0_1();
    
    if (r == 1) // to prevent from accessing data-arr[data->num], out of range.
    {
        r = 0;
    }
    
    return data->arr[(int)(data->num * r)];
}

bool Array::containsObject(Object* object) const
{
    return ccArrayContainsObject(data, object);
}

bool Array::isEqualToArray(Array* otherArray)
{
    for (unsigned int i = 0; i< this->count(); i++)
    {
        if (!this->objectAtIndex(i)->isEqual(otherArray->objectAtIndex(i)))
        {
            return false;
        }
    }
    return true;
}

void Array::addObject(Object* object)
{
    ccArrayAppendObjectWithResize(data, object);
}

void Array::addObjectsFromArray(Array* otherArray)
{
    ccArrayAppendArrayWithResize(data, otherArray->data);
}

void Array::insertObject(Object* object, unsigned int index)
{
    ccArrayInsertObjectAtIndex(data, object, index);
}

void Array::removeLastObject(bool bReleaseObj)
{
    CCASSERT(data->num, "no objects added");
    ccArrayRemoveObjectAtIndex(data, data->num-1, bReleaseObj);
}

void Array::removeObject(Object* object, bool bReleaseObj/* = true*/)
{
    ccArrayRemoveObject(data, object, bReleaseObj);
}

void Array::removeObjectAtIndex(unsigned int index, bool bReleaseObj)
{
    ccArrayRemoveObjectAtIndex(data, index, bReleaseObj);
}

void Array::removeObjectsInArray(Array* otherArray)
{
    ccArrayRemoveArray(data, otherArray->data);
}

void Array::removeAllObjects()
{
    ccArrayRemoveAllObjects(data);
}

void Array::fastRemoveObjectAtIndex(unsigned int index)
{
    ccArrayFastRemoveObjectAtIndex(data, index);
}

void Array::fastRemoveObject(Object* object)
{
    ccArrayFastRemoveObject(data, object);
}

void Array::exchangeObject(Object* object1, Object* object2)
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

void Array::exchangeObjectAtIndex(unsigned int index1, unsigned int index2)
{
    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void Array::replaceObjectAtIndex(unsigned int index, Object* pObject, bool bReleaseObject/* = true*/)
{
    ccArrayInsertObjectAtIndex(data, pObject, index);
    ccArrayRemoveObjectAtIndex(data, index+1);
}

void Array::reverseObjects()
{
    if (data->num > 1)
    {
        // floorf(), since in the case of an even number, the number of swaps stays the same
        int count = (int) floorf(data->num/2.f); 
        unsigned int maxIndex = data->num - 1;

        for (int i = 0; i < count ; i++)
        {
            ccArraySwapObjectsAtIndexes(data, i, maxIndex);
            maxIndex--;
        }
    }
}

void Array::reduceMemoryFootprint()
{
    ccArrayShrink(data);
}

Array::~Array()
{
    ccArrayFree(data);
}

Array* Array::clone() const
{
    Array* ret = new Array();
    ret->autorelease();
    ret->initWithCapacity(this->data->num > 0 ? this->data->num : 1);

    Object* obj = NULL;
    Object* tmpObj = NULL;
    Clonable* clonable = NULL;
    CCARRAY_FOREACH(this, obj)
    {
        clonable = dynamic_cast<Clonable*>(obj);
        if (clonable)
        {
            tmpObj = dynamic_cast<Object*>(clonable->clone());
            if (tmpObj)
            {
                ret->addObject(tmpObj);
            }
        }
        else
        {
            CCLOGWARN("%s isn't clonable.", typeid(*obj).name());
        }
    }
    return ret;
}

void Array::acceptVisitor(DataVisitor &visitor)
{
    visitor.visit(this);
}

NS_CC_END

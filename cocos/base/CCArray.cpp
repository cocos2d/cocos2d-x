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


#if CC_USE_ARRAY_VECTOR

//  ----------------------------------------------------------------------------------
// std::vector implementation
//  ----------------------------------------------------------------------------------

Array::Array()
: data(NULL)
{
    init();
}

Array* Array::create()
{
    Array* array = new Array();

    if (array && array->initWithCapacity(7))
    {
        array->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(array);
    }
    
    return array;
}

Array* Array::createWithObject(Object* object)
{
    Array* array = new Array();

    if (array && array->initWithObject(object))
    {
        array->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(array);
    }

    return array;
}

Array* Array::create(Object* object, ...)
{
    va_list args;
    va_start(args,object);

    Array* array = create();
    if (array && object)
    {
        array->addObject(object);
        Object *i = va_arg(args, Object*);
        while (i) 
        {
            array->addObject(i);
            i = va_arg(args, Object*);
        }
    }
    else
    {
        CC_SAFE_DELETE(array);
    }

    va_end(args);

    return array;
}

Array* Array::createWithArray(Array* otherArray)
{
    return otherArray->clone();
}

Array* Array::createWithCapacity(int capacity)
{
    CCASSERT(capacity>=0, "Invalid capacity");

    Array* array = new Array();
    
    if (array && array->initWithCapacity(capacity))
    {
        array->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(array);
    }
    
    return array;
}

Array* Array::createWithContentsOfFile(const char* fileName)
{
    Array* ret = Array::createWithContentsOfFileThreadSafe(fileName);
    if (ret != nullptr)
    {
        ret->autorelease();
    }
    return ret;
}

Array* Array::createWithContentsOfFileThreadSafe(const char* fileName)
{
    return FileUtils::getInstance()->createArrayWithContentsOfFile(fileName);
}

bool Array::init()
{
    return initWithCapacity(7);
}

bool Array::initWithObject(Object* object)
{
    bool ret = initWithCapacity(7);
    if (ret)
    {
        addObject(object);
    }
    return ret;
}

/** Initializes an array with some objects */
bool Array::initWithObjects(Object* object, ...)
{
    bool ret = false;
    do 
    {
        CC_BREAK_IF(object == nullptr);

        va_list args;
        va_start(args, object);

        if (object)
        {
            this->addObject(object);
            Object* i = va_arg(args, Object*);
            while (i) 
            {
                this->addObject(i);
                i = va_arg(args, Object*);
            }
            ret = true;
        }
        va_end(args);

    } while (false);

    return ret;
}

bool Array::initWithCapacity(int capacity)
{
    CCASSERT(capacity>=0, "Invalid capacity");

    data.reserve(capacity);
    return true;
}

bool Array::initWithArray(Array* otherArray)
{
    data = otherArray->data;
    return true;
}

int Array::getIndexOfObject(Object* object) const
{
    auto it = data.begin();

    for (int i = 0; it != data.end(); ++it, ++i)
    {
        if (it->get() == object)
        {
            return i;
        }
    }
    
    return -1;
}

Object* Array::getRandomObject()
{
    if (data.size()==0)
    {
        return nullptr;
    }

    float r = CCRANDOM_0_1();
    
    if (r == 1) // to prevent from accessing data-arr[data->num], out of range.
    {
        r = 0;
    }

    r *= data.size();
    
    return data[r].get();
}

bool Array::containsObject(Object* object) const
{
    int i = this->getIndexOfObject(object);
    return (i >=0);
}

bool Array::isEqualToArray(Array* otherArray)
{
    for (int i = 0; i< this->count(); i++)
    {
        if (!this->getObjectAtIndex(i)->isEqual(otherArray->getObjectAtIndex(i)))
        {
            return false;
        }
    }
    return true;
}

void Array::addObject(Object* object)
{
    data.push_back( RCPtr<Object>(object) );
}

void Array::addObjectsFromArray(Array* otherArray)
{
    data.insert(data.end(), otherArray->data.begin(), otherArray->data.end());
}

void Array::insertObject(Object* object, int index)
{
    data.insert( std::begin(data) + index, RCPtr<Object>(object) );
}

void Array::setObject(Object* object, int index)
{
    data[index] = RCPtr<Object>(object);
}

void Array::removeLastObject(bool releaseObj)
{
    CCASSERT(data.size(), "no objects added");
    data.pop_back();
}

void Array::removeObject(Object* object, bool releaseObj /* ignored */)
{
    data.erase( std::remove( data.begin(), data.end(), object ) );
}

void Array::removeObjectAtIndex(int index, bool releaseObj /* ignored */)
{
    auto obj = data[index];
    data.erase( data.begin() + index );
}

void Array::removeObjectsInArray(Array* otherArray)
{
    CCASSERT(false, "not implemented");
}

void Array::removeAllObjects()
{
    data.erase(std::begin(data), std::end(data));
}

void Array::fastRemoveObjectAtIndex(int index)
{
    removeObjectAtIndex(index);
}

void Array::fastRemoveObject(Object* object)
{
    removeObject(object);
}

void Array::exchangeObject(Object* object1, Object* object2)
{
    int idx1 = getIndexOfObject(object1);
    int idx2 = getIndexOfObject(object2);

    CCASSERT(idx1>=0 && idx2>=2, "invalid object index");

    std::swap( data[idx1], data[idx2] );
}

void Array::exchangeObjectAtIndex(int index1, int index2)
{
    std::swap( data[index1], data[index2] );
}

void Array::replaceObjectAtIndex(int index, Object* object, bool releaseObject /* ignored */)
{
    data[index] = object;
}

void Array::reverseObjects()
{
    std::reverse( std::begin(data), std::end(data) );
}

void Array::reduceMemoryFootprint()
{
    // N/A
}

Array::~Array()
{
    CCLOGINFO("deallocing Array: %p - len: %d", this, count() );
}

Array* Array::clone() const
{
    Array* ret = new Array();
    ret->autorelease();
    ret->initWithCapacity(this->data.size() > 0 ? this->data.size() : 1);

    Object* obj = nullptr;
    Object* tmpObj = nullptr;
    Clonable* clonable = nullptr;
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

// ----------------------------------------------------------------------------------
// ccArray implementation
// ----------------------------------------------------------------------------------

#else

Array::Array()
: data(nullptr)
{
//    init();
}

Array* Array::create()
{
    Array* array = new Array();

    if (array && array->initWithCapacity(7))
    {
        array->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(array);
    }

    return array;
}

Array* Array::createWithObject(Object* object)
{
    Array* array = new Array();

    if (array && array->initWithObject(object))
    {
        array->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(array);
    }

    return array;
}

Array* Array::create(Object* object, ...)
{
    va_list args;
    va_start(args,object);

    Array* array = create();
    if (array && object)
    {
        array->addObject(object);
        Object *i = va_arg(args, Object*);
        while (i)
        {
            array->addObject(i);
            i = va_arg(args, Object*);
        }
    }
    else
    {
        CC_SAFE_DELETE(array);
    }

    va_end(args);

    return array;
}

Array* Array::createWithArray(Array* otherArray)
{
    return otherArray->clone();
}

Array* Array::createWithCapacity(int capacity)
{
    CCASSERT(capacity>=0, "Invalid capacity");

    Array* array = new Array();

    if (array && array->initWithCapacity(capacity))
    {
        array->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(array);
    }

    return array;
}

Array* Array::createWithContentsOfFile(const char* fileName)
{
    Array* ret = Array::createWithContentsOfFileThreadSafe(fileName);
    if (ret != nullptr)
    {
        ret->autorelease();
    }
    return ret;
}

Array* Array::createWithContentsOfFileThreadSafe(const char* fileName)
{
    return FileUtils::getInstance()->createArrayWithContentsOfFile(fileName);
}

bool Array::init()
{
    CCASSERT(!data, "Array cannot be re-initialized");

    return initWithCapacity(7);
}

bool Array::initWithObject(Object* object)
{
    CCASSERT(!data, "Array cannot be re-initialized");

    bool ret = initWithCapacity(7);
    if (ret)
    {
        addObject(object);
    }
    return ret;
}

/** Initializes an array with some objects */
bool Array::initWithObjects(Object* object, ...)
{
    CCASSERT(!data, "Array cannot be re-initialized");

    bool ret = false;
    do
    {
        CC_BREAK_IF(object == nullptr);

        va_list args;
        va_start(args, object);

        if (object)
        {
            this->addObject(object);
            Object* i = va_arg(args, Object*);
            while (i)
            {
                this->addObject(i);
                i = va_arg(args, Object*);
            }
            ret = true;
        }
        va_end(args);

    } while (false);

    return ret;
}

bool Array::initWithCapacity(int capacity)
{
    CCASSERT(capacity>=0 && !data, "Array cannot be re-initialized");

    data = ccArrayNew(capacity);
    return true;
}

bool Array::initWithArray(Array* otherArray)
{
    CCASSERT(!data, "Array cannot be re-initialized");

    bool ret = false;
    do
    {
        CC_BREAK_IF(! initWithCapacity(otherArray->data->num));

        addObjectsFromArray(otherArray);
        ret = true;
    } while (0);

    return ret;
}

int Array::getIndexOfObject(Object* object) const
{
    return ccArrayGetIndexOfObject(data, object);
}

Object* Array::getRandomObject()
{
    if (data->num == 0)
    {
        return nullptr;
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
    for (int i = 0; i< this->count(); i++)
    {
        if (!this->getObjectAtIndex(i)->isEqual(otherArray->getObjectAtIndex(i)))
        {
            return false;
        }
    }
    return true;
}

void Array::addObject(Object* object) 
{
    CCASSERT(data, "Array not initialized");
    ccArrayAppendObjectWithResize(data, object);
}

void Array::addObjectsFromArray(Array* otherArray)
{
    CCASSERT(data, "Array not initialized");
    ccArrayAppendArrayWithResize(data, otherArray->data);
}

void Array::insertObject(Object* object, int index)
{
    CCASSERT(data, "Array not initialized");
    ccArrayInsertObjectAtIndex(data, object, index);
}

void Array::setObject(Object* object, int index)
{
    CCASSERT(index>=0 && index < count(), "Invalid index");
    
    if (object != data->arr[index])
    {
        data->arr[index]->release();
        data->arr[index] = object;
        object->retain();
    }
}

void Array::removeLastObject(bool releaseObj)
{
    CCASSERT(data->num, "no objects added");
    ccArrayRemoveObjectAtIndex(data, data->num-1, releaseObj);
}

void Array::removeObject(Object* object, bool releaseObj/* = true*/)
{
    ccArrayRemoveObject(data, object, releaseObj);
}

void Array::removeObjectAtIndex(int index, bool releaseObj)
{
    ccArrayRemoveObjectAtIndex(data, index, releaseObj);
}

void Array::removeObjectsInArray(Array* otherArray)
{
    ccArrayRemoveArray(data, otherArray->data);
}

void Array::removeAllObjects()
{
    ccArrayRemoveAllObjects(data);
}

void Array::fastRemoveObjectAtIndex(int index)
{
    ccArrayFastRemoveObjectAtIndex(data, index);
}

void Array::fastRemoveObject(Object* object)
{
    ccArrayFastRemoveObject(data, object);
}

void Array::exchangeObject(Object* object1, Object* object2)
{
    int index1 = ccArrayGetIndexOfObject(data, object1);
    if (index1 == UINT_MAX)
    {
        return;
    }

    int index2 = ccArrayGetIndexOfObject(data, object2);
    if (index2 == UINT_MAX)
    {
        return;
    }

    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void Array::exchangeObjectAtIndex(int index1, int index2)
{
    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void Array::replaceObjectAtIndex(int index, Object* object, bool releaseObject/* = true*/)
{
    ccArrayInsertObjectAtIndex(data, object, index);
    ccArrayRemoveObjectAtIndex(data, index+1);
}

void Array::reverseObjects()
{
    if (data->num > 1)
    {
        // floorf(), since in the case of an even number, the number of swaps stays the same
        int count = (int) floorf(data->num/2.f);
        int maxIndex = data->num - 1;

        for (int i = 0; i < count ; i++)
        {
            ccArraySwapObjectsAtIndexes(data, i, maxIndex);
            --maxIndex;
        }
    }
}

void Array::reduceMemoryFootprint()
{
    ccArrayShrink(data);
}

Array::~Array()
{
    CCLOGINFO("deallocing Array: %p - len: %d", this, count() );

    ccArrayFree(data);
}

Array* Array::clone() const
{
    Array* ret = new Array();
    ret->autorelease();
    ret->initWithCapacity(this->data->num > 0 ? this->data->num : 1);

    Object* obj = nullptr;
    Object* tmpObj = nullptr;
    Clonable* clonable = nullptr;
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

#endif // uses ccArray

NS_CC_END

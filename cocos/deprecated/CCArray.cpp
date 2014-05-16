/****************************************************************************
Copyright (c) 2010      ForzeField Studios S.L. http://forzefield.com
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "deprecated/CCString.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

#if CC_USE_ARRAY_VECTOR

//  ----------------------------------------------------------------------------------
// std::vector implementation
//  ----------------------------------------------------------------------------------

__Array::__Array()
: data(nullptr)
{
    init();
}

__Array* __Array::create()
{
    __Array* array = new __Array();

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

__Array* __Array::createWithObject(Ref* object)
{
    __Array* array = new __Array();

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

__Array* __Array::create(Ref* object, ...)
{
    va_list args;
    va_start(args,object);

    __Array* array = create();
    if (array && object)
    {
        array->addObject(object);
        Ref* i = va_arg(args, Ref*);
        while (i) 
        {
            array->addObject(i);
            i = va_arg(args, Ref*);
        }
    }
    else
    {
        CC_SAFE_DELETE(array);
    }

    va_end(args);

    return array;
}

__Array* __Array::createWithArray(__Array* otherArray)
{
    return otherArray->clone();
}

__Array* __Array::createWithCapacity(int capacity)
{
    CCASSERT(capacity>=0, "Invalid capacity");

    __Array* array = new __Array();
    
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

__Array* __Array::createWithContentsOfFile(const std::string& fileName)
{
    __Array* ret = __Array::createWithContentsOfFileThreadSafe(fileName);
    if (ret != nullptr)
    {
        ret->autorelease();
    }
    return ret;
}

__Array* __Array::createWithContentsOfFileThreadSafe(const std::string& fileName)
{
    return FileUtils::getInstance()->createArrayWithContentsOfFile(fileName);
}

bool __Array::init()
{
    return initWithCapacity(7);
}

bool __Array::initWithObject(Ref* object)
{
    bool ret = initWithCapacity(7);
    if (ret)
    {
        addObject(object);
    }
    return ret;
}

/** Initializes an array with some objects */
bool __Array::initWithObjects(Ref* object, ...)
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
            Ref* i = va_arg(args, Ref*);
            while (i) 
            {
                this->addObject(i);
                i = va_arg(args, Ref*);
            }
            ret = true;
        }
        va_end(args);

    } while (false);

    return ret;
}

bool __Array::initWithCapacity(int capacity)
{
    CCASSERT(capacity>=0, "Invalid capacity");

    data.reserve(capacity);
    return true;
}

bool __Array::initWithArray(__Array* otherArray)
{
    data = otherArray->data;
    return true;
}

ssize_t __Array::getIndexOfObject(Ref* object) const
{
    auto it = data.begin();

    for (ssize_t i = 0; it != data.end(); ++it, ++i)
    {
        if (it->get() == object)
        {
            return i;
        }
    }
    
    return -1;
}

Ref*  __Array::getRandomObject()
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

bool __Array::containsObject(Ref* object) const
{
    ssize_t i = this->getIndexOfObject(object);
    return (i >= 0);
}

bool __Array::isEqualToArray(__Array* otherArray)
{
    for (ssize_t i = 0; i < this->count(); ++i)
    {
        if (!this->getObjectAtIndex(i)->isEqual(otherArray->getObjectAtIndex(i)))
        {
            return false;
        }
    }
    return true;
}

void __Array::addObject(Ref* object)
{
    data.push_back(RCPtr<Object>(object));
}

void __Array::addObjectsFromArray(__Array* otherArray)
{
    data.insert(data.end(), otherArray->data.begin(), otherArray->data.end());
}

void __Array::insertObject(Ref* object, int index)
{
    data.insert(std::begin(data) + index, RCPtr<Object>(object));
}

void __Array::setObject(Ref* object, int index)
{
    data[index] = RCPtr<Object>(object);
}

void __Array::removeLastObject(bool releaseObj)
{
    CCASSERT(data.size(), "no objects added");
    data.pop_back();
}

void __Array::removeObject(Ref* object, bool releaseObj /* ignored */)
{
    data.erase(std::remove(data.begin(), data.end(), object));
}

void __Array::removeObjectAtIndex(ssize_t index, bool releaseObj /* ignored */)
{
    auto obj = data[index];
    data.erase(data.begin() + index);
}

void __Array::removeObjectsInArray(__Array* otherArray)
{
    CCASSERT(false, "not implemented");
}

void __Array::removeAllObjects()
{
    data.erase(std::begin(data), std::end(data));
}

void __Array::fastRemoveObjectAtIndex(int index)
{
    removeObjectAtIndex(index);
}

void __Array::fastRemoveObject(Ref* object)
{
    removeObject(object);
}

void __Array::exchangeObject(Ref* object1, Ref* object2)
{
    ssize_t idx1 = getIndexOfObject(object1);
    ssize_t idx2 = getIndexOfObject(object2);

    CCASSERT(idx1 >= 0 && idx2 >= 2, "invalid object index");

    std::swap(data[idx1], data[idx2]);
}

void __Array::exchangeObjectAtIndex(ssize_t index1, ssize_t index2)
{
    std::swap(data[index1], data[index2]);
}

void __Array::replaceObjectAtIndex(int index, Ref* object, bool releaseObject /* ignored */)
{
    data[index] = object;
}

void __Array::reverseObjects()
{
    std::reverse(std::begin(data), std::end(data));
}

void __Array::reduceMemoryFootprint()
{
    // N/A
}

__Array::~Array()
{
    CCLOGINFO("deallocing Array: %p - len: %d", this, count() );
}

__Array* __Array::clone() const
{
    __Array* ret = new __Array();
    ret->autorelease();
    ret->initWithCapacity(this->data.size() > 0 ? this->data.size() : 1);

    Ref* obj = nullptr;
    Ref* tmpObj = nullptr;
    Clonable* clonable = nullptr;
    CCARRAY_FOREACH(this, obj)
    {
        clonable = dynamic_cast<Clonable*>(obj);
        if (clonable)
        {
            tmpObj = dynamic_cast<Ref*>(clonable->clone());
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

void __Array::acceptVisitor(DataVisitor &visitor)
{
    visitor.visit(this);
}

// ----------------------------------------------------------------------------------
// ccArray implementation
// ----------------------------------------------------------------------------------

#else

__Array::__Array()
: data(nullptr)
{
//    init();
}

__Array* __Array::create()
{
    __Array* array = new __Array();

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

__Array* __Array::createWithObject(Ref* object)
{
    __Array* array = new __Array();

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

__Array* __Array::create(Ref* object, ...)
{
    va_list args;
    va_start(args,object);

    __Array* array = create();
    if (array && object)
    {
        array->addObject(object);
        Ref *i = va_arg(args, Ref*);
        while (i)
        {
            array->addObject(i);
            i = va_arg(args, Ref*);
        }
    }
    else
    {
        CC_SAFE_DELETE(array);
    }

    va_end(args);

    return array;
}

__Array* __Array::createWithArray(__Array* otherArray)
{
    return otherArray->clone();
}

__Array* __Array::createWithCapacity(ssize_t capacity)
{
    CCASSERT(capacity>=0, "Invalid capacity");

    __Array* array = new __Array();

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

__Array* __Array::createWithContentsOfFile(const std::string& fileName)
{
    __Array* ret = __Array::createWithContentsOfFileThreadSafe(fileName);
    if (ret != nullptr)
    {
        ret->autorelease();
    }
    return ret;
}

__Array* __Array::createWithContentsOfFileThreadSafe(const std::string& fileName)
{
    ValueVector arr = FileUtils::getInstance()->getValueVectorFromFile(fileName);
    
    __Array* ret = __Array::createWithCapacity(static_cast<int>(arr.size()));

    for(const auto &value : arr) {
        ret->addObject(__String::create(value.asString()));
    }
    
    return ret;
}

bool __Array::init()
{
    CCASSERT(!data, "Array cannot be re-initialized");

    return initWithCapacity(7);
}

bool __Array::initWithObject(Ref* object)
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
bool __Array::initWithObjects(Ref* object, ...)
{
    CCASSERT(!data, "Array cannot be re-initialized");

    bool ret = false;
    do
    {
        CC_BREAK_IF(object == nullptr);
        CC_BREAK_IF(!initWithCapacity(1));
        
        va_list args;
        va_start(args, object);

        if (object)
        {
            this->addObject(object);
            Ref* i = va_arg(args, Ref*);
            while (i)
            {
                this->addObject(i);
                i = va_arg(args, Ref*);
            }
            ret = true;
        }
        va_end(args);

    } while (false);

    return ret;
}

bool __Array::initWithCapacity(ssize_t capacity)
{
    CCASSERT(capacity>=0 && !data, "Array cannot be re-initialized");

    data = ccArrayNew(capacity);
    return true;
}

bool __Array::initWithArray(__Array* otherArray)
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

ssize_t __Array::getIndexOfObject(Ref* object) const
{
    return ccArrayGetIndexOfObject(data, object);
}

Ref* __Array::getRandomObject()
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

    return data->arr[static_cast<int>(data->num * r)];
}

bool __Array::containsObject(Ref* object) const
{
    return ccArrayContainsObject(data, object);
}

bool __Array::isEqualToArray(__Array* otherArray)
{
    for (int i = 0; i < this->count(); ++i)
    {
//FIXME:james
        if (this->getObjectAtIndex(i) != otherArray->getObjectAtIndex(i))
        {
            return false;
        }
    }
    return true;
}

void __Array::addObject(Ref* object) 
{
    CCASSERT(data, "Array not initialized");
    ccArrayAppendObjectWithResize(data, object);
}

void __Array::addObjectsFromArray(__Array* otherArray)
{
    CCASSERT(data, "Array not initialized");
    ccArrayAppendArrayWithResize(data, otherArray->data);
}

void __Array::insertObject(Ref* object, ssize_t index)
{
    CCASSERT(data, "Array not initialized");
    ccArrayInsertObjectAtIndex(data, object, index);
}

void __Array::setObject(Ref* object, ssize_t index)
{
    CCASSERT(index >= 0 && index < count(), "Invalid index");
    
    if (object != data->arr[index])
    {
        data->arr[index]->release();
        data->arr[index] = object;
        object->retain();
    }
}

void __Array::removeLastObject(bool releaseObj)
{
    CCASSERT(data->num, "no objects added");
    ccArrayRemoveObjectAtIndex(data, data->num - 1, releaseObj);
}

void __Array::removeObject(Ref* object, bool releaseObj/* = true*/)
{
    ccArrayRemoveObject(data, object, releaseObj);
}

void __Array::removeObjectAtIndex(ssize_t index, bool releaseObj)
{
    ccArrayRemoveObjectAtIndex(data, index, releaseObj);
}

void __Array::removeObjectsInArray(__Array* otherArray)
{
    ccArrayRemoveArray(data, otherArray->data);
}

void __Array::removeAllObjects()
{
    ccArrayRemoveAllObjects(data);
}

void __Array::fastRemoveObjectAtIndex(ssize_t index)
{
    ccArrayFastRemoveObjectAtIndex(data, index);
}

void __Array::fastRemoveObject(Ref* object)
{
    ccArrayFastRemoveObject(data, object);
}

void __Array::exchangeObject(Ref* object1, Ref* object2)
{
    auto index1 = ccArrayGetIndexOfObject(data, object1);
    if (index1 == CC_INVALID_INDEX)
    {
        return;
    }

    auto index2 = ccArrayGetIndexOfObject(data, object2);
    if (index2 == CC_INVALID_INDEX)
    {
        return;
    }

    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void __Array::exchangeObjectAtIndex(ssize_t index1, ssize_t index2)
{
    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void __Array::replaceObjectAtIndex(ssize_t index, Ref* object, bool releaseObject/* = true*/)
{
    ccArrayInsertObjectAtIndex(data, object, index);
    ccArrayRemoveObjectAtIndex(data, index + 1);
}

void __Array::reverseObjects()
{
    if (data->num > 1)
    {
        // floorf(), since in the case of an even number, the number of swaps stays the same
        auto count = static_cast<ssize_t>(floorf(data->num/2.f));
        ssize_t maxIndex = data->num - 1;

        for (ssize_t i = 0; i < count ; ++i)
        {
            ccArraySwapObjectsAtIndexes(data, i, maxIndex);
            --maxIndex;
        }
    }
}

void __Array::reduceMemoryFootprint()
{
    ccArrayShrink(data);
}

__Array::~__Array()
{
    CCLOGINFO("deallocing Array: %p - len: %d", this, count() );

    ccArrayFree(data);
}

__Array* __Array::clone() const
{
    __Array* ret = new __Array();
    ret->autorelease();
    ret->initWithCapacity(this->data->num > 0 ? this->data->num : 1);

    Ref* obj = nullptr;
    Ref* tmpObj = nullptr;
    Clonable* clonable = nullptr;
    CCARRAY_FOREACH(this, obj)
    {
        clonable = dynamic_cast<Clonable*>(obj);
        if (clonable)
        {
            tmpObj = dynamic_cast<Ref*>(clonable->clone());
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

void __Array::acceptVisitor(DataVisitor &visitor)
{
    visitor.visit(this);
}

#endif // uses ccArray

NS_CC_END

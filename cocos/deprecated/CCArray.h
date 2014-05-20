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
#ifndef __CCARRAY_H__
#define __CCARRAY_H__

#define CC_USE_ARRAY_VECTOR 0

#if CC_USE_ARRAY_VECTOR
#include <vector>
#include <algorithm>
#include "base/CCRef.h"
#include "base/ccMacros.h"
#else
#include "2d/ccCArray.h"
#endif

#include "base/CCDataVisitor.h"

#if CC_USE_ARRAY_VECTOR
/**
 * 由RCBasep衍生出的指针引用计数类，用法类似C语言指针。
 * 代码原型: http://www.codeproject.com/Articles/64111/Building-a-Quick-and-Handy-Reference-Counting-Clas
 * 许可证: http://www.codeproject.com/info/cpol10.aspx
 */
template < class T >
class RCPtr
{
public:
	//Construct using a C pointer
	//e.g. RCPtr< T > x = new T();
	RCPtr(T* ptr = nullptr)
    : _ptr(ptr)
	{
        if(ptr != nullptr) {ptr->retain();}
	}

	//Copy constructor
	RCPtr(const RCPtr &ptr)
    : _ptr(ptr._ptr)
	{
//        printf("Array: copy constructor: %p\n", this);
		if(_ptr != NULL) {_ptr->retain();}
	}

    //Move constructor
	RCPtr(RCPtr &&ptr)
    : _ptr(ptr._ptr)
	{
//        printf("Array: Move Constructor: %p\n", this);
        ptr._ptr = nullptr;
	}

	~RCPtr()
	{
//        printf("Array: Destructor: %p\n", this);
        if(_ptr != nullptr) {_ptr->release();}
	}

	//Assign a pointer
	//e.g. x = new T();
	RCPtr &operator=(T* ptr)
	{
//        printf("Array: operator= T*: %p\n", this);

        //The following grab and release operations have to be performed
        //in that order to handle the case where ptr == _ptr
        //(See comment below by David Garlisch)
        if(ptr != nullptr) {ptr->retain();}
        if(_ptr != nullptr) {_ptr->release();}
        _ptr = ptr;
        return (*this);
	}

	//Assign another RCPtr
	RCPtr &operator=(const RCPtr &ptr)
	{
//        printf("Array: operator= const&: %p\n", this);
        return (*this) = ptr._ptr;
	}

	//Retrieve actual pointer
	T* get() const
	{
        return _ptr;
	}

    //Some overloaded operators to facilitate dealing with an RCPtr
    //as a conventional C pointer.
    //Without these operators, one can still use the less transparent
    //get() method to access the pointer.
    T* operator->() const {return _ptr;}		//x->member
    T &operator*() const {return *_ptr;}		//*x, (*x).member
    explicit operator T*() const {return _ptr;}		//T* y = x;
    explicit operator bool() const {return _ptr != nullptr;}	//if(x) {/*x is not NULL*/}
    bool operator==(const RCPtr &ptr) {return _ptr == ptr._ptr;}
    bool operator==(const T *ptr) {return _ptr == ptr;}

private:
    T *_ptr;	//Actual pointer
};
#endif // CC_USE_ARRAY_VECTOR


/**
 * @addtogroup data_structures
 * @{
 */

/** @def CCARRAY_FOREACH
方便遍历数组（Array）的宏。比"快速枚举（fast enumeration）"速度快。
@since v0.99.4
*/

/*
在cocos2d-iphone 1.0.0中，此宏被更新为以下形式：

#define CCARRAY_FOREACH(__array__, __object__)                                                \
if (__array__ && __array__->data->num > 0)                                                    \
for(id *__arr__ = __array__->data->arr, *end = __array__->data->arr + __array__->data->num-1;    \
__arr__ <= end && ((__object__ = *__arr__) != nil || true);                                        \
__arr__++)

我们发现这个方法在c++中不适用。所以把他保留为1.0.0-rc3版本中的形式。 --By Bin
*/

#if CC_USE_ARRAY_VECTOR
#define CCARRAY_FOREACH(__array__, __object__)                  \
    if (__array__) \
    for( auto __it__ = (__array__)->data.begin();              \
        __it__ != (__array__)->data.end() && ((__object__) = __it__->get()) != nullptr;                     \
        ++__it__)


#define CCARRAY_FOREACH_REVERSE(__array__, __object__)          \
    if (__array__) \
    for( auto __it__ = (__array__)->data.rbegin();             \
    __it__ != (__array__)->data.rend() && ((__object__) = __it__->get()) != nullptr;                        \
    ++__it__ )


#define CCARRAY_VERIFY_TYPE(__array__, __type__) void(0)

#else // ! CC_USE_ARRAY_VECTOR --------------------------

#define CCARRAY_FOREACH(__array__, __object__)                                                                         \
    if ((__array__) && (__array__)->data->num > 0)                                                                     \
    for(Ref** __arr__ = (__array__)->data->arr, **__end__ = (__array__)->data->arr + (__array__)->data->num-1;    \
    __arr__ <= __end__ && (((__object__) = *__arr__) != NULL/* || true*/);                                             \
    __arr__++)

#define CCARRAY_FOREACH_REVERSE(__array__, __object__)                                                                  \
    if ((__array__) && (__array__)->data->num > 0)                                                                      \
    for(Ref** __arr__ = (__array__)->data->arr + (__array__)->data->num-1, **__end__ = (__array__)->data->arr;     \
    __arr__ >= __end__ && (((__object__) = *__arr__) != NULL/* || true*/);                                              \
    __arr__--)

#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
#define CCARRAY_VERIFY_TYPE(__array__, __type__)                                                                 \
    do {                                                                                                         \
        if ((__array__) && (__array__)->data->num > 0)                                                           \
            for(Ref** __arr__ = (__array__)->data->arr,                                                     \
                **__end__ = (__array__)->data->arr + (__array__)->data->num-1; __arr__ <= __end__; __arr__++)    \
                CCASSERT(dynamic_cast<__type__>(*__arr__), "element type is wrong!");                            \
    } while(false)
#else
#define CCARRAY_VERIFY_TYPE(__array__, __type__) void(0)
#endif

#endif // ! CC_USE_ARRAY_VECTOR


// Common defines -----------------------------------------------------------------------------------------------

#define arrayMakeObjectsPerformSelector(pArray, func, elementType)    \
do {                                                                  \
    if(pArray && pArray->count() > 0)                                 \
    {                                                                 \
        Ref* child;                                                \
        CCARRAY_FOREACH(pArray, child)                                \
        {                                                             \
            elementType pNode = static_cast<elementType>(child);      \
            if(pNode)                                                 \
            {                                                         \
                pNode->func();                                        \
            }                                                         \
        }                                                             \
    }                                                                 \
}                                                                     \
while(false)

#define arrayMakeObjectsPerformSelectorWithObject(pArray, func, object, elementType)   \
do {                                                                  \
    if(pArray && pArray->count() > 0)                                 \
    {                                                                 \
        Ref* child;                                                \
        CCARRAY_FOREACH(pArray, child)                                \
        {                                                             \
            elementType pNode = static_cast<elementType>(child);      \
            if(pNode)                                                 \
            {                                                         \
                pNode->func(object);                                 \
            }                                                         \
        }                                                             \
    }                                                                 \
}                                                                     \
while(false)


NS_CC_BEGIN

class CC_DLL __Array : public Ref, public Clonable
{
public:

    /** 创建一个空数组。默认容量是 10.
     * @js NA
     * @lua NA
     */
    static __Array* create();
    /** 通过多个object创建一个数组。
     * @js NA
     */
    static __Array* create(Ref* object, ...) CC_REQUIRES_NULL_TERMINATION;
    /** 通过单个object创建一个数组。
     * @js NA
     */
    static __Array* createWithObject(Ref* object);
    /** 通过默认容量创建一个数组。
     * @js NA
     */
    static __Array* createWithCapacity(ssize_t capacity);
    /** 通过已有数组创建一个新数组。
     * @js NA
     */
    static __Array* createWithArray(__Array* otherArray);
    /**
     @brief   通过文件内容创建一个数组。
     @param   pFileName  文件名，比如：*.plist
     @return  数组
     * @js NA
     */
    static __Array* createWithContentsOfFile(const std::string& pFileName);

    /*
     @brief 和接口 arrayWithContentsOfFile() 类似, 但是不使用自动释放（autorelease）, 所以需要手动调用release().
     * @js NA
     * @lua NA
     */
    static __Array* createWithContentsOfFileThreadSafe(const std::string& pFileName);
    /**
     * @js NA
     * @lua NA
     */
    ~__Array();

    /** 初始化一个数组
     * @js NA
     * @lua NA
     */
    bool init();
    /** 使用一个object初始化数组。
     * @js NA
     * @lua NA
     */
    bool initWithObject(Ref* object);
    /** 使用多个object初始化数组。
     * @js NA
     * @lua NA
     */
    bool initWithObjects(Ref* object, ...) CC_REQUIRES_NULL_TERMINATION;
    /** 根据容量（capacity）初始化一个数组。
     * @js NA
     * @lua NA
     */
    bool initWithCapacity(ssize_t capacity);
    /** 通过已有的数组初始化一个新的数组。
     * @js NA
     * @lua NA
     */
    bool initWithArray(__Array* otherArray);

    // Querying an Array

    /** 返回数组中数据总数。
     * @js NA
     */
    ssize_t count() const
    {
#if CC_USE_ARRAY_VECTOR
        return data.size();
#else
        return data->num;
#endif
    }
    /** 返回数组的容量。
     * @js NA
     */
    ssize_t capacity() const
    {
#if CC_USE_ARRAY_VECTOR
        return data.capacity();
#else
        return data->max;
#endif
    }
    /** 返回index指定的object；如果未指定index，返回UINT_MAX。
     * @js NA
     * @lua NA
     */
    ssize_t getIndexOfObject(Ref* object) const;
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE ssize_t indexOfObject(Ref* object) const { return getIndexOfObject(object); }

    /** 返回用index指定的元素（element）。
     * @js NA
     * @lua NA
     */
    Ref* getObjectAtIndex(ssize_t index)
    {
        CCASSERT(index>=0 && index < count(), "index out of range in getObjectAtIndex()");
#if CC_USE_ARRAY_VECTOR
        return data[index].get();
#else
        return data->arr[index];
#endif
    }
    CC_DEPRECATED_ATTRIBUTE Ref* objectAtIndex(ssize_t index) { return getObjectAtIndex(index); }
    /** 返回数组最后一个元素（element）。
     * @js NA
     */
    Ref* getLastObject()
    {
#if CC_USE_ARRAY_VECTOR
        return data.back().get();
#else
        if(data->num > 0)
            return data->arr[data->num-1];

        return nullptr;
#endif
    }
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE Ref* lastObject() { return getLastObject(); }
    /** 返回一个随机元素（element）。
     * @js NA
     * @lua NA
     */
    Ref* getRandomObject();
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE Ref* randomObject() { return getRandomObject(); }
    /** 返回一个表示object是否出现在数组中的布偶值（Boolean value）。
     * @js NA
     */
    bool containsObject(Ref* object) const;
    /** @since 1.1
     * @js NA
     */
    bool isEqualToArray(__Array* otherArray);
    // 添加object。

    /** 添加指定的对象（object）。
     * @js NA
     */
    void addObject(Ref* object);
    /**
     * @js NA
     */
    /** 添加已存在的数组中的所有元素（elements）。
     * @js NA
     */
    void addObjectsFromArray(__Array* otherArray);
    /** 在index指定的位置插入指定的对象（object）。
     * @js NA
     */
    void insertObject(Ref* object, ssize_t index);
    /** 通过index设置一个指定的对象（object）。
     * @js NA
     * @lua NA
     */
    void setObject(Ref* object, ssize_t index);
    /** 通过index设置一个指定的对象（object）并且不使用自动引用计数。请谨慎使用此功能。
     * @js NA
     * @lua NA
     */
    void fastSetObject(Ref* object, ssize_t index)
    {
#if CC_USE_ARRAY_VECTOR
        setObject(object, index);
#else
        // 不使用引用计数
        data->arr[index] = object;
#endif
    }
    /**
     * @js NA
     * @lua NA
     */
    void swap( ssize_t indexOne, ssize_t indexTwo )
    {
        CCASSERT(indexOne >=0 && indexOne < count() && indexTwo >= 0 && indexTwo < count(), "Invalid indices");
#if CC_USE_ARRAY_VECTOR
        std::swap(data[indexOne], data[indexTwo]);
#else
        std::swap(data->arr[indexOne], data->arr[indexTwo]);
#endif
    }

    // Removing Objects

    /** 移除最后一个对象（object）。
     * @js NA
     */
    void removeLastObject(bool releaseObj = true);
    /** 移除一个指定对象（object）。
     * @js NA
     */
    void removeObject(Ref* object, bool releaseObj = true);
    /** 通过index指定并移除一个元素（element）。
     * @js NA
     */
    void removeObjectAtIndex(ssize_t index, bool releaseObj = true);
    /** 移除所有元素（element）。
     * @js NA
     */
    void removeObjectsInArray(__Array* otherArray);
    /** 移除所有对象（object）。
     * @js NA
     */
    void removeAllObjects();
    /** 快速移除一个指定对象（object）。
     * @js NA
     */
    void fastRemoveObject(Ref* object);
    /** 通过index指定一个元素，并将它快速移除
     * @js NA
     */
    void fastRemoveObjectAtIndex(ssize_t index);

    // Rearranging Content

    /** 交换两个元素（element）。
     * @js NA
     */
    void exchangeObject(Ref* object1, Ref* object2);
    /** 通过index指定并交换两个元素（element）。
     * @js NA
     */
    void exchangeObjectAtIndex(ssize_t index1, ssize_t index2);

    /** 通过index指定并覆盖一个旧的元素。
     * @js NA
     */
    void replaceObjectAtIndex(ssize_t index, Ref* object, bool releaseObject = true);

    /** 倒序一个数组。
     * @js NA
     */
    void reverseObjects();
    /* Shrinks the array so the memory footprint corresponds with the number of items
     * @js NA
     */
    void reduceMemoryFootprint();

    /* 重写方法
     * @js NA
     */
    virtual void acceptVisitor(DataVisitor &visitor);
    /**
     * @js NA
     * @lua NA
     */
    virtual __Array* clone() const;

    // ------------------------------------------
    // Iterators
    // ------------------------------------------
#if CC_USE_ARRAY_VECTOR
    typedef std::vector<RCPtr<Object>>::iterator iterator;
    typedef std::vector<RCPtr<Object>>::const_iterator const_iterator;
    /**
     * @js NA
     * @lua NA
     */
    iterator begin() { return data.begin(); }
    /**
     * @js NA
     * @lua NA
     */
    iterator end() { return data.end(); }
    const_iterator cbegin() { return data.cbegin(); }
    /**
     * @js NA
     * @lua NA
     */
    const_iterator cend() { return data.cend(); }

    std::vector<RCPtr<Object>> data;

#else
    /**
     * @js NA
     * @lua NA
     */
    Ref** begin() { return &data->arr[0]; }
    /**
     * @js NA
     * @lua NA
     */
    Ref** end() { return &data->arr[data->num]; }

    ccArray* data;

#endif

//protected:
    /**
     * @js NA
     * @lua NA
     */
    __Array();
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCARRAY_H__

/****************************************************************************
Copyright (c) 2010      ForzeField Studios S.L. http://forzefield.com
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.

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
/// @cond DO_NOT_SHOW

#define CC_USE_ARRAY_VECTOR 0

#if CC_USE_ARRAY_VECTOR
#include <vector>
#include <algorithm>
#include "base/CCRef.h"
#include "base/ccMacros.h"
#else
#include "base/ccCArray.h"
#endif

#include "base/CCDataVisitor.h"

#if CC_USE_ARRAY_VECTOR
/**
 * A reference counting-managed pointer for classes derived from RCBase which can
 * be used as C pointer
 * Original code: http://www.codeproject.com/Articles/64111/Building-a-Quick-and-Handy-Reference-Counting-Clas
 * License: http://www.codeproject.com/info/cpol10.aspx
 */
template < class T >
class RCPtr
{
public:
	//Construct using a C pointer
	//e.g. RCPtr< T > x = new (std::nothrow) T();
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
	//e.g. x = new (std::nothrow) T();
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
A convenience macro to iterate over a Array using. It is faster than the "fast enumeration" interface.
@since v0.99.4
*/

/*
In cocos2d-iphone 1.0.0, This macro have been update to like this:

#define CCARRAY_FOREACH(__array__, __object__)                                                \
if (__array__ && __array__->data->num > 0)                                                    \
for(id *__arr__ = __array__->data->arr, *end = __array__->data->arr + __array__->data->num-1;    \
__arr__ <= end && ((__object__ = *__arr__) != nil || true);                                        \
__arr__++)

I found that it's not work in C++. So it keep what it's look like in version 1.0.0-rc3. ---By Bin
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

    /** Creates an empty array. Default capacity is 10 
     * @js NA
     * @lua NA
     */
    static __Array* create();
    /** Create an array with objects 
     * @js NA
     */
    static __Array* create(Ref* object, ...) CC_REQUIRES_NULL_TERMINATION;
    /** Create an array with one object 
     * @js NA
     */
    static __Array* createWithObject(Ref* object);
    /** Create an array with a default capacity 
     * @js NA
     */
    static __Array* createWithCapacity(ssize_t capacity);
    /** Create an array with from an existing array 
     * @js NA
     */
    static __Array* createWithArray(__Array* otherArray);
    /**
     @brief   Generate a Array pointer by file
     @param   pFileName  The file name of *.plist file
     @return  The Array pointer generated from the file
     * @js NA
     */
    static __Array* createWithContentsOfFile(const std::string& pFileName);
    
    /*
     @brief The same meaning as arrayWithContentsOfFile(), but it doesn't call autorelease, so the
     invoker should call release().
     * @js NA
     * @lua NA
     */
    static __Array* createWithContentsOfFileThreadSafe(const std::string& pFileName);
    /**
     * @js NA
     * @lua NA
     */
    ~__Array();

    /** Initializes an array 
     * @js NA
     * @lua NA
     */
    bool init();
    /** Initializes an array with one object 
     * @js NA
     * @lua NA
     */
    bool initWithObject(Ref* object);
    /** Initializes an array with some objects 
     * @js NA
     * @lua NA
     */
    bool initWithObjects(Ref* object, ...) CC_REQUIRES_NULL_TERMINATION;
    /** Initializes an array with capacity 
     * @js NA
     * @lua NA
     */
    bool initWithCapacity(ssize_t capacity);
    /** Initializes an array with an existing array 
     * @js NA
     * @lua NA
     */
    bool initWithArray(__Array* otherArray);

    // Querying an Array

    /** Returns element count of the array 
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
    /** Returns capacity of the array 
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
    /** Returns index of a certain object, return UINT_MAX if doesn't contain the object 
     * @js NA
     * @lua NA
     */
    ssize_t getIndexOfObject(Ref* object) const;
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE ssize_t indexOfObject(Ref* object) const { return getIndexOfObject(object); }

    /** Returns an element with a certain index 
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
    /** Returns the last element of the array 
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
    /** Returns a random element 
     * @js NA
     * @lua NA
     */
    Ref* getRandomObject();
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE Ref* randomObject() { return getRandomObject(); }
    /** Returns a Boolean value that indicates whether object is present in array. 
     * @js NA
     */
    bool containsObject(Ref* object) const;
    /** @since 1.1 
     * @js NA
     */
    bool isEqualToArray(__Array* otherArray);
    // Adding Objects

    /** Add a certain object 
     * @js NA
     */
    void addObject(Ref* object);
    /**
     * @js NA
     */
    /** Add all elements of an existing array 
     * @js NA
     */
    void addObjectsFromArray(__Array* otherArray);
    /** Insert a certain object at a certain index 
     * @js NA
     */
    void insertObject(Ref* object, ssize_t index);
    /** sets a certain object at a certain index 
     * @js NA
     * @lua NA
     */
    void setObject(Ref* object, ssize_t index);
    /** sets a certain object at a certain index without retaining. Use it with caution 
     * @js NA
     * @lua NA
     */
    void fastSetObject(Ref* object, ssize_t index)
    {
#if CC_USE_ARRAY_VECTOR
        setObject(object, index);
#else
        // no retain
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

    /** Remove last object 
     * @js NA
     */
    void removeLastObject(bool releaseObj = true);
    /** Remove a certain object 
     * @js NA
     */
    void removeObject(Ref* object, bool releaseObj = true);
    /** Remove an element with a certain index 
     * @js NA
     */
    void removeObjectAtIndex(ssize_t index, bool releaseObj = true);
    /** Remove all elements 
     * @js NA
     */
    void removeObjectsInArray(__Array* otherArray);
    /** Remove all objects 
     * @js NA
     */
    void removeAllObjects();
    /** Fast way to remove a certain object 
     * @js NA
     */
    void fastRemoveObject(Ref* object);
    /** Fast way to remove an element with a certain index 
     * @js NA
     */
    void fastRemoveObjectAtIndex(ssize_t index);

    // Rearranging Content

    /** Swap two elements 
     * @js NA
     */
    void exchangeObject(Ref* object1, Ref* object2);
    /** Swap two elements with certain indexes 
     * @js NA
     */
    void exchangeObjectAtIndex(ssize_t index1, ssize_t index2);

    /** Replace object at index with another object. 
     * @js NA
     */
    void replaceObjectAtIndex(ssize_t index, Ref* object, bool releaseObject = true);

    /** Revers the array 
     * @js NA
     */
    void reverseObjects();
    /* Shrinks the array so the memory footprint corresponds with the number of items 
     * @js NA
     */
    void reduceMemoryFootprint();
  
    /* override functions 
     * @js NA
     */
    virtual void acceptVisitor(DataVisitor &visitor);
    /**
     * @js NA
     * @lua NA
     */
    virtual __Array* clone() const override;

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

/// @endcond
#endif // __CCARRAY_H__

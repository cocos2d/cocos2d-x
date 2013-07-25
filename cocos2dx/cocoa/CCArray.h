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
#ifndef __CCARRAY_H__
#define __CCARRAY_H__

#include "support/data_support/ccCArray.h"

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
#define CCARRAY_FOREACH(__array__, __object__)                                                                         \
    if ((__array__) && (__array__)->data->num > 0)                                                                     \
    for(Object** __arr__ = (__array__)->data->arr, **__end__ = (__array__)->data->arr + (__array__)->data->num-1;    \
    __arr__ <= __end__ && (((__object__) = *__arr__) != NULL/* || true*/);                                             \
    __arr__++)

#define CCARRAY_FOREACH_REVERSE(__array__, __object__)                                                                  \
    if ((__array__) && (__array__)->data->num > 0)                                                                      \
    for(Object** __arr__ = (__array__)->data->arr + (__array__)->data->num-1, **__end__ = (__array__)->data->arr;     \
    __arr__ >= __end__ && (((__object__) = *__arr__) != NULL/* || true*/);                                              \
    __arr__--)

#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
#define CCARRAY_VERIFY_TYPE(__array__, __type__)                                                                 \
    do {                                                                                                         \
        if ((__array__) && (__array__)->data->num > 0)                                                           \
            for(Object** __arr__ = (__array__)->data->arr,                                                     \
                **__end__ = (__array__)->data->arr + (__array__)->data->num-1; __arr__ <= __end__; __arr__++)    \
                CCASSERT(dynamic_cast<__type__>(*__arr__), "element type is wrong!");                            \
    } while(false)
#else
#define CCARRAY_VERIFY_TYPE(__array__, __type__) void(0)
#endif

#define arrayMakeObjectsPerformSelector(pArray, func, elementType)    \
do {                                                                  \
    if(pArray && pArray->count() > 0)                                 \
    {                                                                 \
        Object* child;                                                \
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

#define arrayMakeObjectsPerformSelectorWithObject(pArray, func, pObject, elementType)   \
do {                                                                  \
    if(pArray && pArray->count() > 0)                                 \
    {                                                                 \
        Object* child;                                                \
        CCARRAY_FOREACH(pArray, child)                                \
        {                                                             \
            elementType pNode = static_cast<elementType>(child);      \
            if(pNode)                                                 \
            {                                                         \
                pNode->func(pObject);                                 \
            }                                                         \
        }                                                             \
    }                                                                 \
}                                                                     \
while(false)


NS_CC_BEGIN

class CC_DLL Array : public Object, public Clonable
{
public:
    ~Array();

    /** Create an array */
    static Array* create();
    /** Create an array with some objects */
    static Array* create(Object* pObject, ...) CC_REQUIRES_NULL_TERMINATION;
    /** Create an array with one object */
    static Array* createWithObject(Object* pObject);
    /** Create an array with capacity */
    static Array* createWithCapacity(unsigned int capacity);
    /** Create an array with an existing array */
    static Array* createWithArray(Array* otherArray);
    /**
     @brief   Generate a Array pointer by file
     @param   pFileName  The file name of *.plist file
     @return  The Array pointer generated from the file
     */
    static Array* createWithContentsOfFile(const char* pFileName);
    
    /*
     @brief The same meaning as arrayWithContentsOfFile(), but it doesn't call autorelease, so the
     invoker should call release().
     */
    static Array* createWithContentsOfFileThreadSafe(const char* pFileName);

    /** Initializes an array */
    bool init();
    /** Initializes an array with one object */
    bool initWithObject(Object* pObject);
    /** Initializes an array with some objects */
    bool initWithObjects(Object* pObject, ...) CC_REQUIRES_NULL_TERMINATION;
    /** Initializes an array with capacity */
    bool initWithCapacity(unsigned int capacity);
    /** Initializes an array with an existing array */
    bool initWithArray(Array* otherArray);

    // Querying an Array

    /** Returns element count of the array */
    unsigned int count() const;
    /** Returns capacity of the array */
    unsigned int capacity() const;
    /** Returns index of a certain object, return UINT_MAX if doesn't contain the object */
    unsigned int indexOfObject(Object* object) const;
    /** Returns an element with a certain index */
    Object* objectAtIndex(unsigned int index);
    /** Returns last element */
    Object* lastObject();
    /** Returns a random element */
    Object* randomObject();
    /** Returns a Boolean value that indicates whether object is present in array. */
    bool containsObject(Object* object) const;
    /** @since 1.1 */
    bool isEqualToArray(Array* pOtherArray);
    // Adding Objects

    /** Add a certain object */
    void addObject(Object* object);
    /** Add all elements of an existing array */
    void addObjectsFromArray(Array* otherArray);
    /** Insert a certain object at a certain index */
    void insertObject(Object* object, unsigned int index);

    // Removing Objects

    /** Remove last object */
    void removeLastObject(bool bReleaseObj = true);
    /** Remove a certain object */
    void removeObject(Object* object, bool bReleaseObj = true);
    /** Remove an element with a certain index */
    void removeObjectAtIndex(unsigned int index, bool bReleaseObj = true);
    /** Remove all elements */
    void removeObjectsInArray(Array* otherArray);
    /** Remove all objects */
    void removeAllObjects();
    /** Fast way to remove a certain object */
    void fastRemoveObject(Object* object);
    /** Fast way to remove an element with a certain index */
    void fastRemoveObjectAtIndex(unsigned int index);

    // Rearranging Content

    /** Swap two elements */
    void exchangeObject(Object* object1, Object* object2);
    /** Swap two elements with certain indexes */
    void exchangeObjectAtIndex(unsigned int index1, unsigned int index2);

    /** Replace object at index with another object. */
    void replaceObjectAtIndex(unsigned int uIndex, Object* pObject, bool bReleaseObject = true);

    /** Revers the array */
    void reverseObjects();
    /* Shrinks the array so the memory footprint corresponds with the number of items */
    void reduceMemoryFootprint();
  
    /* override functions */
    virtual void acceptVisitor(DataVisitor &visitor);
    virtual Array* clone() const;
    
public:
    ccArray* data;
    Array();
    Array(unsigned int capacity);
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCARRAY_H__

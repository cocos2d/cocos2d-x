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

/** @def CCARRAY_FOREACH
A convience macro to iterate over a CCArray using. It is faster than the "fast enumeration" interface.
@since v0.99.4
*/

/*
In cocos2d-iphone 1.0.0, This macro have been update to like this:

#define CCARRAY_FOREACH(__array__, __object__)												\
if (__array__ && __array__->data->num > 0)													\
for(id *__arr__ = __array__->data->arr, *end = __array__->data->arr + __array__->data->num-1;	\
__arr__ <= end && ((__object__ = *__arr__) != nil || true);										\
__arr__++)

I found that it's not work in C++. So it keep what it's look like in version 1.0.0-rc3. ---By Bin
*/
#define CCARRAY_FOREACH(__array__, __object__)												\
    if (__array__ && __array__->data->num > 0)													\
    for(CCObject** arr = __array__->data->arr, **end = __array__->data->arr + __array__->data->num-1;	\
    arr <= end && ((__object__ = *arr) != NULL/* || true*/);										\
    arr++)

namespace cocos2d
{

class CC_DLL CCArray : public CCObject
{
public:
    ~CCArray();
	/** Create an array */
    static CCArray* array();
	/** Create an array with capacity */
    static CCArray* arrayWithCapacity(unsigned int capacity);
	/** Create an array with an existing array */
    static CCArray* arrayWithArray(CCArray* otherArray);

	/** Initializes an array */
    bool init();
	/** Initializes an array with capacity */
    bool initWithCapacity(unsigned int capacity);
	/** Initializes an array with an existing array */
    bool initWithArray(CCArray* otherArray);

    // Querying an Array

	/** Returns element count of the array */
    unsigned int count();
	/** Returns capacity of the array */
    unsigned int capacity();
	/** Returns index of a certain object, return UINT_MAX if doesn't contain the object */
    unsigned int indexOfObject(CCObject* object);
	/** Returns an element with a certain index */
    CCObject* objectAtIndex(unsigned int index);
	/** Returns last element */
    CCObject* lastObject();
	/** Returns a random element */
    CCObject* randomObject();
	/** Returns a Boolean value that indicates whether object is present in array. */
    bool containsObject(CCObject* object);

    // Adding Objects

	/** Add a certain object */
    void addObject(CCObject* object);
	/** Add all elements of an existing array */
    void addObjectsFromArray(CCArray* otherArray);
	/** Insert a certain object at a certain index */
    void insertObject(CCObject* object, unsigned int index);

    // Removing Objects

	/** Remove last object */
    void removeLastObject();
	/** Remove a certain object */
    void removeObject(CCObject* object);
	/** Remove an element with a certain index */
    void removeObjectAtIndex(unsigned int index);
	/** Remove all elements */
    void removeObjectsInArray(CCArray* otherArray);
	/** Remove all objects */
    void removeAllObjects();
	/** Fast way to remove a certain object */
    void fastRemoveObject(CCObject* object);
	/** Fast way to remove an element with a certain index */
    void fastRemoveObjectAtIndex(unsigned int index);

    // Rearranging Content

	/** Swap two elements */
    void exchangeObject(CCObject* object1, CCObject* object2);
	/** Swap two elements with certain indexes */
    void exchangeObjectAtIndex(unsigned int index1, unsigned int index2);
	/** Revers the array */
    void reverseObjects();
	/* Shrinks the array so the memory footprint corresponds with the number of items */
    void reduceMemoryFootprint();

public:
    ccArray* data;

private:
	CCArray() : data(NULL) {};
};

}

#endif // __CCARRAY_H__

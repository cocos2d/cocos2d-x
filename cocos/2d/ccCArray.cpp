/****************************************************************************
Copyright (c) 2007      Scott Lembcke
Copyright (c) 2010-2012 cocos2d-x.org
CopyRight (c) 2013-2014 Chukong Technologies Inc.

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

#include "ccCArray.h"
#include "CCObject.h"

NS_CC_BEGIN

const ssize_t CC_INVALID_INDEX = -1;

/** Allocates and initializes a new array with specified capacity */
ccArray* ccArrayNew(ssize_t capacity)
{
	if (capacity == 0)
		capacity = 7;
	
	ccArray *arr = (ccArray*)malloc( sizeof(ccArray) );
	arr->num = 0;
	arr->arr =  (Object**)calloc(capacity, sizeof(Object*));
	arr->max = capacity;
	
	return arr;
}

/** Frees array after removing all remaining objects. Silently ignores nullptr arr. */
void ccArrayFree(ccArray*& arr)
{
    if( arr == nullptr ) 
    {
        return;
    }
	ccArrayRemoveAllObjects(arr);
	
	free(arr->arr);
	free(arr);

    arr = nullptr;
}

void ccArrayDoubleCapacity(ccArray *arr)
{
	arr->max *= 2;
	Object** newArr = (Object**)realloc( arr->arr, arr->max * sizeof(Object*) );
	// will fail when there's not enough memory
    CCASSERT(newArr != 0, "ccArrayDoubleCapacity failed. Not enough memory");
	arr->arr = newArr;
}

void ccArrayEnsureExtraCapacity(ccArray *arr, ssize_t extra)
{
	while (arr->max < arr->num + extra)
    {
        CCLOGINFO("cocos2d: ccCArray: resizing ccArray capacity from [%d] to [%d].",
              static_cast<int>(arr->max),
              static_cast<int>(arr->max*2));

		ccArrayDoubleCapacity(arr);
    }
}

void ccArrayShrink(ccArray *arr)
{
    ssize_t newSize = 0;
	
	//only resize when necessary
	if (arr->max > arr->num && !(arr->num==0 && arr->max==1))
	{
		if (arr->num!=0)
		{
			newSize=arr->num;
			arr->max=arr->num;
		}
		else
		{//minimum capacity of 1, with 0 elements the array would be free'd by realloc
			newSize=1;
			arr->max=1;
		}
		
		arr->arr = (Object**)realloc(arr->arr,newSize * sizeof(Object*) );
		CCASSERT(arr->arr!=nullptr,"could not reallocate the memory");
	}
}

/** Returns index of first occurrence of object, CC_INVALID_INDEX if object not found. */
ssize_t ccArrayGetIndexOfObject(ccArray *arr, Object* object)
{
    const auto arrNum = arr->num;
    Object** ptr = arr->arr;
	for (ssize_t i = 0; i < arrNum; ++i, ++ptr)
    {
		if (*ptr == object)
            return i;
    }
    
	return CC_INVALID_INDEX;
}

/** Returns a Boolean value that indicates whether object is present in array. */
bool ccArrayContainsObject(ccArray *arr, Object* object)
{
	return ccArrayGetIndexOfObject(arr, object) != CC_INVALID_INDEX;
}

/** Appends an object. Behavior undefined if array doesn't have enough capacity. */
void ccArrayAppendObject(ccArray *arr, Object* object)
{
    CCASSERT(object != nullptr, "Invalid parameter!");
    object->retain();
	arr->arr[arr->num] = object;
	arr->num++;
}

/** Appends an object. Capacity of arr is increased if needed. */
void ccArrayAppendObjectWithResize(ccArray *arr, Object* object)
{
	ccArrayEnsureExtraCapacity(arr, 1);
	ccArrayAppendObject(arr, object);
}

/** Appends objects from plusArr to arr. Behavior undefined if arr doesn't have
 enough capacity. */
void ccArrayAppendArray(ccArray *arr, ccArray *plusArr)
{
	for (ssize_t i = 0; i < plusArr->num; i++)
    {
		ccArrayAppendObject(arr, plusArr->arr[i]);
    }
}

/** Appends objects from plusArr to arr. Capacity of arr is increased if needed. */
void ccArrayAppendArrayWithResize(ccArray *arr, ccArray *plusArr)
{
	ccArrayEnsureExtraCapacity(arr, plusArr->num);
	ccArrayAppendArray(arr, plusArr);
}

/** Inserts an object at index */
void ccArrayInsertObjectAtIndex(ccArray *arr, Object* object, ssize_t index)
{
	CCASSERT(index<=arr->num, "Invalid index. Out of bounds");
	CCASSERT(object != nullptr, "Invalid parameter!");

	ccArrayEnsureExtraCapacity(arr, 1);
	
	ssize_t remaining = arr->num - index;
	if (remaining > 0)
    {
		memmove((void *)&arr->arr[index+1], (void *)&arr->arr[index], sizeof(Object*) * remaining );
    }

    object->retain();
	arr->arr[index] = object;
	arr->num++;
}

/** Swaps two objects */
void ccArraySwapObjectsAtIndexes(ccArray *arr, ssize_t index1, ssize_t index2)
{
	CCASSERT(index1>=0 && index1 < arr->num, "(1) Invalid index. Out of bounds");
	CCASSERT(index2>=0 && index2 < arr->num, "(2) Invalid index. Out of bounds");
	
	Object* object1 = arr->arr[index1];
	
	arr->arr[index1] = arr->arr[index2];
	arr->arr[index2] = object1;
}

/** Removes all objects from arr */
void ccArrayRemoveAllObjects(ccArray *arr)
{
	while (arr->num > 0)
    {
		(arr->arr[--arr->num])->release();
    }
}

/** Removes object at specified index and pushes back all subsequent objects.
 Behavior undefined if index outside [0, num-1]. */
void ccArrayRemoveObjectAtIndex(ccArray *arr, ssize_t index, bool releaseObj/* = true*/)
{
    CCASSERT(arr && arr->num > 0 && index>=0 && index < arr->num, "Invalid index. Out of bounds");
    if (releaseObj)
    {
        CC_SAFE_RELEASE(arr->arr[index]);
    }
    
	arr->num--;
	
	ssize_t remaining = arr->num - index;
	if(remaining>0)
    {
		memmove((void *)&arr->arr[index], (void *)&arr->arr[index+1], remaining * sizeof(Object*));
    }
}

/** Removes object at specified index and fills the gap with the last object,
 thereby avoiding the need to push back subsequent objects.
 Behavior undefined if index outside [0, num-1]. */
void ccArrayFastRemoveObjectAtIndex(ccArray *arr, ssize_t index)
{
	CC_SAFE_RELEASE(arr->arr[index]);
	auto last = --arr->num;
	arr->arr[index] = arr->arr[last];
}

void ccArrayFastRemoveObject(ccArray *arr, Object* object)
{
	auto index = ccArrayGetIndexOfObject(arr, object);
	if (index != CC_INVALID_INDEX)
    {
		ccArrayFastRemoveObjectAtIndex(arr, index);
    }
}

/** Searches for the first occurrence of object and removes it. If object is not
 found the function has no effect. */
void ccArrayRemoveObject(ccArray *arr, Object* object, bool releaseObj/* = true*/)
{
	auto index = ccArrayGetIndexOfObject(arr, object);
	if (index != CC_INVALID_INDEX)
    {
		ccArrayRemoveObjectAtIndex(arr, index, releaseObj);
    }
}

/** Removes from arr all objects in minusArr. For each object in minusArr, the
 first matching instance in arr will be removed. */
void ccArrayRemoveArray(ccArray *arr, ccArray *minusArr)
{
	for (ssize_t i = 0; i < minusArr->num; i++)
    {
		ccArrayRemoveObject(arr, minusArr->arr[i]);
    }
}

/** Removes from arr all objects in minusArr. For each object in minusArr, all
 matching instances in arr will be removed. */
void ccArrayFullRemoveArray(ccArray *arr, ccArray *minusArr)
{
	ssize_t back = 0;
	
	for (ssize_t i = 0; i < arr->num; i++)
    {
		if (ccArrayContainsObject(minusArr, arr->arr[i]))
        {
			CC_SAFE_RELEASE(arr->arr[i]);
			back++;
		} 
        else
        {
			arr->arr[i - back] = arr->arr[i];
        }
	}
	
	arr->num -= back;
}

// #pragma mark -
// #pragma mark ccCArray for Values (c structures)

/** Allocates and initializes a new C array with specified capacity */
ccCArray* ccCArrayNew(ssize_t capacity)
{
	if (capacity == 0)
    {
		capacity = 7;
    }

	ccCArray *arr = (ccCArray*)malloc(sizeof(ccCArray));
	arr->num = 0;
	arr->arr = (void**)malloc(capacity * sizeof(void*));
	arr->max = capacity;
	
	return arr;
}

/** Frees C array after removing all remaining values. Silently ignores nullptr arr. */
void ccCArrayFree(ccCArray *arr)
{
    if (arr == nullptr)
    {
        return;
    }
	ccCArrayRemoveAllValues(arr);
	
	free(arr->arr);
	free(arr);
}

/** Doubles C array capacity */
void ccCArrayDoubleCapacity(ccCArray *arr)
{
    ccArrayDoubleCapacity((ccArray*)arr);
}

/** Increases array capacity such that max >= num + extra. */
void ccCArrayEnsureExtraCapacity(ccCArray *arr, ssize_t extra)
{
    ccArrayEnsureExtraCapacity((ccArray*)arr,extra);
}

/** Returns index of first occurrence of value, CC_INVALID_INDEX if value not found. */
ssize_t ccCArrayGetIndexOfValue(ccCArray *arr, void* value)
{
	for(ssize_t i = 0; i < arr->num; i++)
    {
		if( arr->arr[i] == value )
            return i;
    }
	return CC_INVALID_INDEX;
}

/** Returns a Boolean value that indicates whether value is present in the C array. */
bool ccCArrayContainsValue(ccCArray *arr, void* value)
{
	return ccCArrayGetIndexOfValue(arr, value) != CC_INVALID_INDEX;
}

/** Inserts a value at a certain position. Behavior undefined if array doesn't have enough capacity */
void ccCArrayInsertValueAtIndex( ccCArray *arr, void* value, ssize_t index)
{
	CCASSERT( index < arr->max, "ccCArrayInsertValueAtIndex: invalid index");
	
	auto remaining = arr->num - index;
    // make sure it has enough capacity
    if (arr->num + 1 == arr->max)
    {
        ccCArrayDoubleCapacity(arr);
    }
	// last Value doesn't need to be moved
	if( remaining > 0) {
		// tex coordinates
		memmove((void *)&arr->arr[index+1], (void *)&arr->arr[index], sizeof(void*) * remaining );
	}
	
	arr->num++;
	arr->arr[index] = value;
}

/** Appends an value. Behavior undefined if array doesn't have enough capacity. */
void ccCArrayAppendValue(ccCArray *arr, void* value)
{
	arr->arr[arr->num] = value;
	arr->num++;
    // double the capacity for the next append action
    // if the num >= max
    if (arr->num >= arr->max)
    {
        ccCArrayDoubleCapacity(arr);
    }
}

/** Appends an value. Capacity of arr is increased if needed. */
void ccCArrayAppendValueWithResize(ccCArray *arr, void* value)
{
	ccCArrayEnsureExtraCapacity(arr, 1);
	ccCArrayAppendValue(arr, value);
}


/** Appends values from plusArr to arr. Behavior undefined if arr doesn't have
 enough capacity. */
void ccCArrayAppendArray(ccCArray *arr, ccCArray *plusArr)
{
	for( ssize_t i = 0; i < plusArr->num; i++)
    {
		ccCArrayAppendValue(arr, plusArr->arr[i]);
    }
}

/** Appends values from plusArr to arr. Capacity of arr is increased if needed. */
void ccCArrayAppendArrayWithResize(ccCArray *arr, ccCArray *plusArr)
{
	ccCArrayEnsureExtraCapacity(arr, plusArr->num);
	ccCArrayAppendArray(arr, plusArr);
}

/** Removes all values from arr */
void ccCArrayRemoveAllValues(ccCArray *arr)
{
	arr->num = 0;
}

/** Removes value at specified index and pushes back all subsequent values.
 Behavior undefined if index outside [0, num-1].
 @since v0.99.4
 */
void ccCArrayRemoveValueAtIndex(ccCArray *arr, ssize_t index)
{
	for( ssize_t last = --arr->num; index < last; index++)
    {
		arr->arr[index] = arr->arr[index + 1];
    }
}

/** Removes value at specified index and fills the gap with the last value,
 thereby avoiding the need to push back subsequent values.
 Behavior undefined if index outside [0, num-1].
 @since v0.99.4
 */
void ccCArrayFastRemoveValueAtIndex(ccCArray *arr, ssize_t index)
{
	ssize_t last = --arr->num;
	arr->arr[index] = arr->arr[last];
}

/** Searches for the first occurrence of value and removes it. If value is not found the function has no effect.
 @since v0.99.4
 */
void ccCArrayRemoveValue(ccCArray *arr, void* value)
{
	auto index = ccCArrayGetIndexOfValue(arr, value);
	if (index != CC_INVALID_INDEX)
    {
		ccCArrayRemoveValueAtIndex(arr, index);
    }
}

/** Removes from arr all values in minusArr. For each Value in minusArr, the first matching instance in arr will be removed.
 @since v0.99.4
 */
void ccCArrayRemoveArray(ccCArray *arr, ccCArray *minusArr)
{
	for(ssize_t i = 0; i < minusArr->num; i++)
    {
		ccCArrayRemoveValue(arr, minusArr->arr[i]);
    }
}

/** Removes from arr all values in minusArr. For each value in minusArr, all matching instances in arr will be removed.
 @since v0.99.4
 */
void ccCArrayFullRemoveArray(ccCArray *arr, ccCArray *minusArr)
{
	ssize_t back = 0;
	
	for(ssize_t i = 0; i < arr->num; i++)
    {
		if( ccCArrayContainsValue(minusArr, arr->arr[i]) ) 
        {
			back++;
		} 
        else
        {
			arr->arr[i - back] = arr->arr[i];
        }
	}
	
	arr->num -= back;
}

NS_CC_END

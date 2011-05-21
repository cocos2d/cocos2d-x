/* Copyright (c) 2007 Scott Lembcke
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
#include <stdlib.h>
#include <string.h>

#include "chipmunk_private.h"


//#define CP_ARRAY_INCREMENT 10

// NOTE: cpArray is rarely used and will probably go away.

cpArray*
cpArrayAlloc(void)
{
	return (cpArray *)cpcalloc(1, sizeof(cpArray));
}

cpArray*
cpArrayInit(cpArray *arr, int size)
{
	arr->num = 0;
	
	size = (size ? size : 4);
	arr->max = size;
	arr->arr = (void **)cpmalloc(size*sizeof(void**));
	
	return arr;
}

cpArray*
cpArrayNew(int size)
{
	return cpArrayInit(cpArrayAlloc(), size);
}

void
cpArrayDestroy(cpArray *arr)
{
	cpfree(arr->arr);
	arr->arr = NULL;
}

void
cpArrayFree(cpArray *arr)
{
	if(arr){
		cpArrayDestroy(arr);
		cpfree(arr);
	}
}

void
cpArrayPush(cpArray *arr, void *object)
{
	if(arr->num == arr->max){
		arr->max *= 2;
		arr->arr = (void **)cprealloc(arr->arr, arr->max*sizeof(void**));
	}
	
	arr->arr[arr->num] = object;
	arr->num++;
}

void *
cpArrayPop(cpArray *arr)
{
	arr->num--;
	
	void *value = arr->arr[arr->num];
	arr->arr[arr->num] = NULL;
	
	return value;
}

void
cpArrayDeleteIndex(cpArray *arr, int idx)
{
	arr->num--;
	
	arr->arr[idx] = arr->arr[arr->num];
	arr->arr[arr->num] = NULL;
}

void
cpArrayDeleteObj(cpArray *arr, void *obj)
{
	for(int i=0; i<arr->num; i++){
		if(arr->arr[i] == obj){
			cpArrayDeleteIndex(arr, i);
			return;
		}
	}
}

void
cpArrayAppend(cpArray *arr, cpArray *other)
{
	void *tail = &arr->arr[arr->num];
	
	arr->num += other->num;
	if(arr->num >= arr->max){
		arr->max = arr->num;
		arr->arr = (void **)cprealloc(arr->arr, arr->max*sizeof(void**));
	}
	
	memcpy(tail, other->arr, other->num*sizeof(void**));
}

void
cpArrayEach(cpArray *arr, cpArrayIter iterFunc, void *data)
{
	for(int i=0; i<arr->num; i++)
		iterFunc(arr->arr[i], data);
}

cpBool
cpArrayContains(cpArray *arr, void *ptr)
{
	for(int i=0; i<arr->num; i++)
		if(arr->arr[i] == ptr) return cpTrue;
	
	return cpFalse;
}

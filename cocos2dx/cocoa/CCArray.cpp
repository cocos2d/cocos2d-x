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

NS_CC_BEGIN


CCArray::CCArray()
: data(NULL)
{
    init();
}

CCArray::CCArray(unsigned int capacity)
: data(NULL)
{
    initWithCapacity(capacity);
}

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

CCArray* CCArray::arrayWithObject(CCObject* pObject)
{
    CCArray* pArray = new CCArray();

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

CCArray* CCArray::arrayWithObjects(CCObject* pObject, ...)
{
    va_list args;
    va_start(args,pObject);
    
    CCArray* pArray = array();
    if (pArray && pObject)
    {
        pArray->addObject(pObject);
        CCObject *i = va_arg(args, CCObject*);
        while(i) 
        {
            pArray->addObject(i);
            i = va_arg(args, CCObject*);
        }
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }

    va_end(args);
    
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
    CCArray* pRet = (CCArray*)otherArray->copy();
    pRet->autorelease();
    return pRet;
}

CCArray* CCArray::arrayWithContentsOfFile(const char* pFileName)
{
    CCArray* pRet = arrayWithContentsOfFileThreadSafe(pFileName);
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

extern CCArray* ccFileUtils_arrayWithContentsOfFileThreadSafe(const char* pFileName);

CCArray* CCArray::arrayWithContentsOfFileThreadSafe(const char* pFileName)
{
    return ccFileUtils_arrayWithContentsOfFileThreadSafe(pFileName);
}

bool CCArray::init()
{
    return initWithCapacity(1);
}

bool CCArray::initWithObject(CCObject* pObject)
{
    ccArrayFree(&data);
    bool bRet = initWithCapacity(1);
    if (bRet)
    {
        addObject(pObject);
    }
    return bRet;
}

/** Initializes an array with some objects */
bool CCArray::initWithObjects(CCObject* pObject, ...)
{
    ccArrayFree(&data);
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(pObject != NULL);

        va_list args;
        va_start(args, pObject);

        CCArray* pArray = new CCArray();
        if (pArray && pObject)
        {
            pArray->addObject(pObject);
            CCObject* i = va_arg(args, CCObject*);
            while(i) 
            {
                pArray->addObject(i);
                i = va_arg(args, CCObject*);
            }
            bRet = true;
        }
        else
        {
            CC_SAFE_DELETE(pArray);
        }
        va_end(args);

    } while (false);

    return bRet;
}

bool CCArray::initWithCapacity(unsigned int capacity)
{
    ccArrayFree(&data);
    data = ccArrayNew(capacity);
    return true;
}

bool CCArray::initWithArray(CCArray* otherArray)
{
    ccArrayFree(&data);
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

bool CCArray::isEqualToArray(CCArray* otherArray)
{
    for (int i = 0; i< this->count(); i++)
    {
        if (!this->objectAtIndex(i)->isEqual(otherArray->objectAtIndex(i)))
        {
            return false;
        }
    }
    return true;
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

void CCArray::removeLastObject(bool bReleaseObj)
{
    CCAssert(data->num, "no objects added");
    ccArrayRemoveObjectAtIndex(data, data->num-1, bReleaseObj);
}

void CCArray::removeObject(CCObject* object, bool bReleaseObj/* = true*/)
{
    ccArrayRemoveObject(data, object, bReleaseObj);
}

void CCArray::removeObjectAtIndex(unsigned int index, bool bReleaseObj)
{
    ccArrayRemoveObjectAtIndex(data, index, bReleaseObj);
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

void CCArray::replaceObjectAtIndex(unsigned int index, CCObject* pObject, bool bReleaseObject/* = true*/)
{
    ccArrayInsertObjectAtIndex(data, pObject, index);
    ccArrayRemoveObjectAtIndex(data, index+1);
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
    ccArrayFree(&data);
}



CCObject* CCArray::copyWithZone(CCZone* pZone)
{
    CCAssert(pZone == NULL, "CCArray should not be inherited.");
    CCArray* pArray = new CCArray();
    pArray->initWithCapacity(this->data->num > 0 ? this->data->num : 1);

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(this, pObj)
    {
        pArray->addObject(pObj->copy()->autorelease());
    }
    return pArray;
}

//#pragma mark CCArray - sorting 

/** @since 1.1 */ 
//#pragma mark -
//#pragma mark CCArray insertionSortUsingCFuncComparator

void CCArray::insertionSortUsingCFuncComparator(cc_comparator comparator)
{
    cc_insertionSort(data, comparator);
}

//#pragma mark CCArray qsortUsingCFuncComparator

void CCArray::qsortUsingCFuncComparator(cc_comparator comparator)
{
    // stable c qsort is used - cost of sorting:  best n*log(n), average n*log(n)
    //  qsort(void *, size_t, size_t, int (*)(const void *arg1, const void *arg2));

    qsort(data->arr, data->num, sizeof (CCObject*), comparator);  
}

//#pragma mark CCArray mergesortLUsingCFuncComparator

void CCArray::mergesortLUsingCFuncComparator(cc_comparator comparator)
{
    cc_mergesortL(data, sizeof (CCObject*), comparator); 
}

//#pragma mark CCArray insertionSort with (SEL)selector

void CCArray::insertionSort(SEL_Compare selector) // It sorts source array in ascending order
{
    int i,j,length = data->num;

    CCObject* * x = data->arr;
    CCObject* temp;	

    // insertion sort
    for(i=1; i<length; i++)
    {
        j = i;
        // continue moving element downwards while order is descending 
        while( j>0 &&  (x[j-1]->*selector)(x[j]) == CCOrderedDescending )
        {
            temp = x[j];
            x[j] = x[j-1];
            x[j-1] = temp;
            j--;
        }
    }
}

static inline int selectorCompare(CCObject* object1,CCObject* object2,SEL_Compare selector)
{
    return (int) (object1->*selector)(object2);
}

void CCArray::sortUsingSelector(SEL_Compare selector)
{
    this->sortUsingFunction(selectorCompare, selector);
}

//#pragma mark CCArray sortUsingFunction

// using a comparison function
void CCArray::sortUsingFunction(int (*compare)(CCObject*, CCObject*, SEL_Compare) , SEL_Compare context)
{
    int h, i, j, k, l, m, n = this->count();
    CCObject*  A, **B = (CCObject**)malloc( (n/2 + 1) * sizeof(CCObject*));

    // to prevent retain counts from temporarily hitting zero.  
    for( i=0;i<n;i++)
    {
        // [[self objectAtIndex:i] retain]; // prevents compiler warning
        data->arr[i]->retain();
    }

    for (h = 1; h < n; h += h)
    {
        for (m = n - 1 - h; m >= 0; m -= h + h)
        {
            l = m - h + 1;
            if (l < 0)
            {
                l = 0;
            }

            for (i = 0, j = l; j <= m; i++, j++)
            {
                B[i] = this->objectAtIndex(j);
            }

            for (i = 0, k = l; k < j && j <= m + h; k++)
            {
                A = this->objectAtIndex(j);
                if (compare(A, B[i], context) == CCOrderedDescending)
                {
                    this->replaceObjectAtIndex(k, B[i++]);
                }
                else
                {
                    this->replaceObjectAtIndex(k, A);
                    j++;
                }
            }

            while (k < j)
            {
                this->replaceObjectAtIndex(k++, B[i++]);
            }
        }
    }

    for(i=0;i<n;i++)
    {
        // [[self objectAtIndex:i] release]; // prevents compiler warning
        data->arr[i]->release();
    }

    free(B);
}

void CCArray::makeObjectsPerformSelector(SEL_CallFunc aSelector)
{
    ccArrayMakeObjectsPerformSelector(data, aSelector);
}

void CCArray::makeObjectsPerformSelectorWithObject(SEL_CallFuncO aSelector, CCObject* object)
{
    ccArrayMakeObjectsPerformSelectorWithObject(data, aSelector, object);
}

void CCArray::makeObjectPerformSelectorWithArrayObjects(CCObject* object, SEL_CallFuncO aSelector)
{		
    ccArrayMakeObjectPerformSelectorWithArrayObjects(data, aSelector, object);
}

NS_CC_END

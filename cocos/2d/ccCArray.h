/****************************************************************************
Copyright (c) 2007      Scott Lembcke
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

/**
 @file
 基于Chipmunk的cpArray。
 ccArray是一个更快的NSMutableArray。
 它和NSMutableArray几乎一样 (适当的存储、保持和释放NSObjects)。
 它比NSMutableArray快是因为:
 - 它用原生C接口所以它没有Objective-c的消息机制开销
 - 它假定你知道你在做什么，所以它没有在安全检查上花时间
   （数组越界, 需要的容量等）
 - 对象比较时用指针比较代替了isEqual函数

 它有两种用法：
 - ccArray函数操纵objective-c对象(进行保留和释放操作)
 - ccCArray函数像标准的C结构体一样操纵值(不进行保留和释放操作)
 */

#ifndef CC_ARRAY_H
#define CC_ARRAY_H

#include "base/ccMacros.h"
#include "base/CCRef.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

NS_CC_BEGIN

// Easy integration
#define CCARRAYDATA_FOREACH(__array__, __object__)															\
__object__=__array__->arr[0]; for(ssize_t i=0, num=__array__->num; i<num; i++, __object__=__array__->arr[i])	\


typedef struct _ccArray {
	ssize_t num, max;
	Ref** arr;
} ccArray;

/** 根据指定的容量（capacity）分配和初始化一个新的数组 */
ccArray* ccArrayNew(ssize_t capacity);

/** 在移除所有执有对象后释放数组。忽略空的数组。 */
void ccArrayFree(ccArray*& arr);

/** 数组容量翻倍 */
void ccArrayDoubleCapacity(ccArray *arr);

/** 如果数组当前元素数量（num）加额外空间（extra）大于数组容量（max），增加数组容量
 译者注：增加方式为让数组容量翻倍 */
void ccArrayEnsureExtraCapacity(ccArray *arr, ssize_t extra);

/** 把数组的容量收缩为数组内容的数量，让内存符合数组包含的内容 */
void ccArrayShrink(ccArray *arr);

/** 返回第一个匹配对象（Object）的索引（index），如果没有找到返回NSNotFound */
ssize_t ccArrayGetIndexOfObject(ccArray *arr, Ref* object);

/** 返回布尔（Boolean）值代表此对象（object）是否在当前数组中 */
bool ccArrayContainsObject(ccArray *arr, Ref* object);

/** 追加一个对象（object）。如果数组没有足够容量，则执行的结果是不可预料的（Undefined behavior）。 */
void ccArrayAppendObject(ccArray *arr, Ref* object);

/** 追加一个对象（object）。如果容量不足，增加数组的容量。 */
void ccArrayAppendObjectWithResize(ccArray *arr, Ref* object);

/** 从plusArr追加对象（objects）到arr。
 如果数组没有足够容量，则执行的结果是不可预料的（Undefined behavior） */
void ccArrayAppendArray(ccArray *arr, ccArray *plusArr);

/** 从plusArr追加对象（objects）到arr。如果容量不足，增加数组的容量。 */
void ccArrayAppendArrayWithResize(ccArray *arr, ccArray *plusArr);

/** 在索引（index）位置插入对象（object） */
void ccArrayInsertObjectAtIndex(ccArray *arr, Ref* object, ssize_t index);

/** 交换两个对象（object） */
void ccArraySwapObjectsAtIndexes(ccArray *arr, ssize_t index1, ssize_t index2);

/** 删除数组的所有对象（objects） */
void ccArrayRemoveAllObjects(ccArray *arr);

/** 删除指定索引（index）的对象（object）然后把索引（index）后面的对象（object）向前移动。
 如果索引（index）在[0, num-1]以外，即索引位置没有对象（object），则执行的结果是不可预料的（Undefined behavior）。 */
void ccArrayRemoveObjectAtIndex(ccArray *arr, ssize_t index, bool releaseObj = true);

/** 删除指定索引（index）的对象（object）然后把最后一个对象填充到指定索引（index）位置，
 从而避免移动后面的对象（objects）。
 如果索引（index）在[0, num-1]以外，即索引位置没有对象（object），则执行的结果是不可预料的（Undefined behavior）。 */
void ccArrayFastRemoveObjectAtIndex(ccArray *arr, ssize_t index);

void ccArrayFastRemoveObject(ccArray *arr, Ref* object);

/** 搜索第一个匹配的对象（object）并删除它。如果没有找到对象（object），函数不造成任何影响。 */
void ccArrayRemoveObject(ccArray *arr, Ref* object, bool releaseObj = true);

/** 根据minusArr数组中的对象（object），删除arr数组中的相同对象（object）。
 匹配时，根据minusArr数组中的对象（object），arr数组中的第一个匹配对象（object）将被删除。 */
void ccArrayRemoveArray(ccArray *arr, ccArray *minusArr);

/** 根据minusArr数组中的对象（object），删除arr数组中的所有相同对象（object）。
 匹配时，根据minusArr数组中的对象（object），arr数组中的所有匹配对象（object）将被删除。 */
void ccArrayFullRemoveArray(ccArray *arr, ccArray *minusArr);

// 
// // ccCArray for Values (c structures)

typedef struct _ccCArray {
    ssize_t num, max;
    void** arr;
} ccCArray;

/** 根据指定的容量（capacity）分配和初始化一个新的C数组 */
ccCArray* ccCArrayNew(ssize_t capacity);

/** 在移除所有执有对象后释放C数组。忽略空的数组。 */
void ccCArrayFree(ccCArray *arr);

/** C数组容量翻倍 */
void ccCArrayDoubleCapacity(ccCArray *arr);

/** 如果数组当前元素数量（num）加额外空间（extra）大于数组容量（max），增加数组容量  译者注：增加方式为让数组容量翻倍 */
void ccCArrayEnsureExtraCapacity(ccCArray *arr, ssize_t extra);

/** 返回第一个匹配值（value）的索引（index），如果没有找到返回NSNotFound */
ssize_t ccCArrayGetIndexOfValue(ccCArray *arr, void* value);

/** 返回布尔（Boolean）值代表此值（value）是否在当前C数组中 */
bool ccCArrayContainsValue(ccCArray *arr, void* value);

/** 在索引（index）位置插入值（value）。如果数组没有足够容量，则执行的结果是不可预料的（Undefined behavior）。 */
void ccCArrayInsertValueAtIndex( ccCArray *arr, void* value, ssize_t index);

/** 追加一个值（value）。如果数组没有足够容量，则执行的结果是不可预料的（Undefined behavior）。 */
void ccCArrayAppendValue(ccCArray *arr, void* value);

/** 追加一个值（value）。如果容量不足，增加数组的容量。 */
void ccCArrayAppendValueWithResize(ccCArray *arr, void* value);

/** 从plusArr追加值（values）到arr。
 如果数组没有足够容量，则执行的结果是不可预料的（Undefined behavior） */
void ccCArrayAppendArray(ccCArray *arr, ccCArray *plusArr);

/** 从plusArr追加值（values）到arr。如果容量不足，增加数组的容量。 */
void ccCArrayAppendArrayWithResize(ccCArray *arr, ccCArray *plusArr);

/** 删除数组的所有值（values） */
void ccCArrayRemoveAllValues(ccCArray *arr);

/** 删除指定索引（index）的值（value）然后把索引后面的值（values）向前移动。
 如果索引（index）在[0, num-1]以外，即索引位置没有值（value），则执行的结果是不可预料的（Undefined behavior）。
 @since v0.99.4
 */
void ccCArrayRemoveValueAtIndex(ccCArray *arr, ssize_t index);

/** 删除指定索引（index）的值（value）然后把最后一个值（value）填充到指定索引（index）位置，
 从而避免移动后面的值（values）。
 如果索引（index）在[0, num-1]以外，即索引位置没有值（value），则执行的结果是不可预料的（Undefined behavior）。
 @since v0.99.4
 */
void ccCArrayFastRemoveValueAtIndex(ccCArray *arr, ssize_t index);

/** 搜索第一个匹配的值（value）并删除它。如果没有找到值，函数不造成任何影响。
 @since v0.99.4
 */
void ccCArrayRemoveValue(ccCArray *arr, void* value);

/** 根据minusArr数组中的值（value），删除arr数组中的相同值（value）。
 匹配时，根据minusArr数组中的值（value），arr数组中的第一个匹配值（value）将被删除。
 @since v0.99.4
 */
void ccCArrayRemoveArray(ccCArray *arr, ccCArray *minusArr);

/** 根据minusArr数组中的值（value），删除arr数组中的所有相同值（value）。
 匹配时，根据minusArr数组中的值（value），arr数组中的所有匹配值（value）将被删除。
 @since v0.99.4
 */
void ccCArrayFullRemoveArray(ccCArray *arr, ccCArray *minusArr);

NS_CC_END
	
#endif // CC_ARRAY_H

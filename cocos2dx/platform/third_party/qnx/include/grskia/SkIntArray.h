/* libs/graphics/animator/SkIntArray.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkIntArray_DEFINED
#define SkIntArray_DEFINED

#include "SkColor.h"
#include "SkDisplayType.h"
#include "SkMath.h"
#include "SkTDArray_Experimental.h"

class SkActive;
class SkAnimateBase;
class SkDataInput;
class SkDisplayable;
class SkDisplayEvent;
class SkDrawable;
class SkDrawColor;
class SkMatrixPart;
struct SkMemberInfo;
class SkPathPart;
class SkPaintPart;
class SkTypedArray;
class SkString;
union SkOperand;

typedef SkIntArray(int) SkTDIntArray;
typedef SkIntArray(SkColor) SkTDColorArray;
typedef SkIntArray(SkDisplayTypes) SkTDDisplayTypesArray;
typedef SkIntArray(SkMSec) SkTDMSecArray;
typedef SkIntArray(SkScalar) SkTDScalarArray;

typedef SkLongArray(SkActive*) SkTDActiveArray; 
typedef SkLongArray(SkAnimateBase*) SkTDAnimateArray; 
typedef SkLongArray(SkDataInput*) SkTDDataArray; 
typedef SkLongArray(SkDisplayable*) SkTDDisplayableArray; 
typedef SkLongArray(SkDisplayEvent*) SkTDDisplayEventArray; 
typedef SkLongArray(SkDrawable*) SkTDDrawableArray; 
typedef SkLongArray(SkDrawColor*) SkTDDrawColorArray; 
typedef SkLongArray(SkMatrixPart*) SkTDMatrixPartArray; 
typedef SkLongArray(const SkMemberInfo*) SkTDMemberInfoArray;
typedef SkLongArray(SkPaintPart*) SkTDPaintPartArray; 
typedef SkLongArray(SkPathPart*) SkTDPathPartArray; 
typedef SkLongArray(SkTypedArray*) SkTDTypedArrayArray; 
typedef SkLongArray(SkString*) SkTDStringArray; 
typedef SkLongArray(SkOperand) SkTDOperandArray; 
typedef SkLongArray(SkOperand*) SkTDOperandPtrArray; 

#endif // SkIntArray_DEFINED




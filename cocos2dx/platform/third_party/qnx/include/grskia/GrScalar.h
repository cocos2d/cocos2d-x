/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


#ifndef GrScalar_DEFINED
#define GrScalar_DEFINED

#include "GrTypes.h"
#include "SkScalar.h"

#define GR_Int32Min         SK_NaN32
#define GR_Int32Max         SK_MaxS32

#define GR_Fixed1           SK_Fixed1
#define GR_FixedHalf        SK_FixedHalf
#define GrIntToFixed(a)     SkIntToFixed(a)
#define GrFixedToFloat(a)   SkFixedToFloat(a)
#define GrFixedFloorToInt(a)    SkFixedFloor(a)

#define GrScalar            SkScalar
#define GR_Scalar1          SK_Scalar1
#define GR_ScalarHalf       SK_ScalarHalf
#define GR_ScalarMin        SK_ScalarMin
#define GR_ScalarMax        SK_ScalarMax

#define GrIntToScalar(a)    SkIntToScalar(a)
#define GrScalarHalf(a)     SkScalarHalf(a)
#define GrScalarAve(a,b)    SkScalarAve(a,b)
#define GrMul(a,b)          SkScalarMul(a,b)
#define GrScalarDiv(a,b)    SkScalarDiv(a, b)
#define GrScalarToFloat(a)  SkScalarToFloat(a)
#define GrFloatToScalar(a)  SkScalarToFloat(a)
#define GrIntToScalar(a)    SkIntToScalar(a)
#define GrScalarAbs(a)      SkScalarAbs(a)
#define GrScalarIsInt(a)    SkScalarIsInt(a)
#define GrScalarMax(a,b)    SkScalarMax(a,b)
#define GrScalarFloorToInt(a)   SkScalarFloor(a)
#define GrScalarCeilToInt(a)    SkScalarCeil(a)
#define GrFixedToScalar(a)  SkFixedToScalar(a)

#endif


/* libs/graphics/sgl/SkFP.h
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

#ifndef SkFP_DEFINED
#define SkFP_DEFINED

#include "SkMath.h"

#ifdef SK_SCALAR_IS_FLOAT

    typedef float SkFP;

    #define SkScalarToFP(n)         (n)
    #define SkFPToScalar(n)         (n)
    #define SkIntToFP(n)            SkIntToScalar(n)
    #define SkFPRound(x)            SkScalarRound(n)
    #define SkFPCeil(x)             SkScalarCeil(n)
    #define SkFPFloor(x)            SkScalarFloor(n)

    #define SkFPNeg(x)              (-(x))
    #define SkFPAbs(x)              SkScalarAbs(x)
    #define SkFPAdd(a, b)           ((a) + (b))
    #define SkFPSub(a, b)           ((a) - (b))
    #define SkFPMul(a, b)           ((a) * (b))
    #define SkFPMulInt(a, n)        ((a) * (n))
    #define SkFPDiv(a, b)           ((a) / (b))
    #define SkFPDivInt(a, n)        ((a) / (n))
    #define SkFPInvert(x)           SkScalarInvert(x)
    #define SkFPSqrt(x)             SkScalarSqrt(x)
    #define SkFPCubeRoot(x)         sk_float_pow(x, 0.3333333f)

    #define SkFPLT(a, b)            ((a) < (b))
    #define SkFPLE(a, b)            ((a) <= (b))
    #define SkFPGT(a, b)            ((a) > (b))
    #define SkFPGE(a, b)            ((a) >= (b))

#else   // scalar is fixed

    #include "SkFloat.h"

    typedef int32_t SkFP;

    #define SkScalarToFP(n)         SkFloat::SetShift(n, -16)
    #define SkFPToScalar(n)         SkFloat::GetShift(n, -16)
    #define SkIntToFP(n)            SkFloat::SetShift(n, 0)
    #define SkFPRound(x)            SkFloat::Round(x);
    #define SkFPCeil(x)             SkFloat::Ceil();
    #define SkFPFloor(x)            SkFloat::Floor();

    #define SkFPNeg(x)              SkFloat::Neg(x)
    #define SkFPAbs(x)              SkFloat::Abs(x)
    #define SkFPAdd(a, b)           SkFloat::Add(a, b)
    #define SkFPSub(a, b)           SkFloat::Add(a, SkFloat::Neg(b))
    #define SkFPMul(a, b)           SkFloat::Mul(a, b)
    #define SkFPMulInt(a, n)        SkFloat::MulInt(a, n)
    #define SkFPDiv(a, b)           SkFloat::Div(a, b)
    #define SkFPDivInt(a, n)        SkFloat::DivInt(a, n)
    #define SkFPInvert(x)           SkFloat::Invert(x)
    #define SkFPSqrt(x)             SkFloat::Sqrt(x)
    #define SkFPCubeRoot(x)         SkFloat::CubeRoot(x)

    #define SkFPLT(a, b)            (SkFloat::Cmp(a, b) < 0)
    #define SkFPLE(a, b)            (SkFloat::Cmp(a, b) <= 0)
    #define SkFPGT(a, b)            (SkFloat::Cmp(a, b) > 0)
    #define SkFPGE(a, b)            (SkFloat::Cmp(a, b) >= 0)

#endif

#ifdef SK_DEBUG
    void SkFP_UnitTest();
#endif

#endif

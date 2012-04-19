/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkScalar_DEFINED
#define SkScalar_DEFINED

#include "SkFixed.h"
#include "SkFloatingPoint.h"

/** \file SkScalar.h

    Types and macros for the data type SkScalar. This is the fractional numeric type
    that, depending on the compile-time flag SK_SCALAR_IS_FLOAT, may be implemented
    either as an IEEE float, or as a 16.16 SkFixed. The macros in this file are written
    to allow the calling code to manipulate SkScalar values without knowing which representation
    is in effect.
*/

#ifdef SK_SCALAR_IS_FLOAT

    /** SkScalar is our type for fractional values and coordinates. Depending on
        compile configurations, it is either represented as an IEEE float, or
        as a 16.16 fixed point integer.
    */
    typedef float   SkScalar;
    extern const uint32_t gIEEENotANumber;
    extern const uint32_t gIEEEInfinity;

    /** SK_Scalar1 is defined to be 1.0 represented as an SkScalar
    */
    #define SK_Scalar1              (1.0f)
    /** SK_Scalar1 is defined to be 1/2 represented as an SkScalar
    */
    #define SK_ScalarHalf           (0.5f)
    /** SK_ScalarInfinity is defined to be infinity as an SkScalar
    */
    #define SK_ScalarInfinity           (*(const float*)&gIEEEInfinity)
    /** SK_ScalarMax is defined to be the largest value representable as an SkScalar
    */
    #define SK_ScalarMax            (3.402823466e+38f)
    /** SK_ScalarMin is defined to be the smallest value representable as an SkScalar
    */
    #define SK_ScalarMin            (-SK_ScalarMax)
    /** SK_ScalarNaN is defined to be 'Not a Number' as an SkScalar
    */
    #define SK_ScalarNaN      (*(const float*)(const void*)&gIEEENotANumber)
    /** SkScalarIsNaN(n) returns true if argument is not a number
    */
    static inline bool SkScalarIsNaN(float x) { return x != x; }
    /** Returns true if x is not NaN and not infinite */
    static inline bool SkScalarIsFinite(float x) {
        uint32_t bits = SkFloat2Bits(x);    // need unsigned for our shifts
        int exponent = bits << 1 >> 24;
        return exponent != 0xFF;
    }
#ifdef SK_DEBUG
    /** SkIntToScalar(n) returns its integer argument as an SkScalar
     *
     * If we're compiling in DEBUG mode, and can thus afford some extra runtime
     * cycles, check to make sure that the parameter passed in has not already
     * been converted to SkScalar.  (A double conversion like this is harmless
     * for SK_SCALAR_IS_FLOAT, but for SK_SCALAR_IS_FIXED this causes trouble.)
     *
     * Note that we need all of these method signatures to properly handle the
     * various types that we pass into SkIntToScalar() to date:
     * int, size_t, U8CPU, etc., even though what we really mean is "anything
     * but a float".
     */
    static inline float SkIntToScalar(signed int param) {
        return (float)param;
    }
    static inline float SkIntToScalar(unsigned int param) {
        return (float)param;
    }
    static inline float SkIntToScalar(signed long param) {
        return (float)param;
    }
    static inline float SkIntToScalar(unsigned long param) {
        return (float)param;
    }
    static inline float SkIntToScalar(float param) {
        /* If the parameter passed into SkIntToScalar is a float,
         * one of two things has happened:
         * 1. the parameter was an SkScalar (which is typedef'd to float)
         * 2. the parameter was a float instead of an int
         *
         * Either way, it's not good.
         */
        SkASSERT(!"looks like you passed an SkScalar into SkIntToScalar");
        return (float)0;
    }
#else  // not SK_DEBUG
    /** SkIntToScalar(n) returns its integer argument as an SkScalar
    */
    #define SkIntToScalar(n)        ((float)(n))
#endif // not SK_DEBUG
    /** SkFixedToScalar(n) returns its SkFixed argument as an SkScalar
    */
    #define SkFixedToScalar(x)      SkFixedToFloat(x)
    /** SkScalarToFixed(n) returns its SkScalar argument as an SkFixed
    */
    #define SkScalarToFixed(x)      SkFloatToFixed(x)

    #define SkScalarToFloat(n)      (n)
    #define SkFloatToScalar(n)      (n)

    #define SkScalarToDouble(n)      (double)(n)
    #define SkDoubleToScalar(n)      (float)(n)

    /** SkScalarFraction(x) returns the signed fractional part of the argument
    */
    #define SkScalarFraction(x)     sk_float_mod(x, 1.0f)
    /** Rounds the SkScalar to the nearest integer value
    */
    #define SkScalarRound(x)        sk_float_round2int(x)
    /** Returns the smallest integer that is >= the specified SkScalar
    */
    #define SkScalarCeil(x)         sk_float_ceil2int(x)
    /** Returns the largest integer that is <= the specified SkScalar
    */
    #define SkScalarFloor(x)        sk_float_floor2int(x)
    /** Returns the absolute value of the specified SkScalar
    */
    #define SkScalarAbs(x)          sk_float_abs(x)
    /** Return x with the sign of y
     */
    #define SkScalarCopySign(x, y)  sk_float_copysign(x, y)
    /** Returns the value pinned between 0 and max inclusive
    */
    inline SkScalar SkScalarClampMax(SkScalar x, SkScalar max) {
        return x < 0 ? 0 : x > max ? max : x;
    }
    /** Returns the value pinned between min and max inclusive
    */
    inline SkScalar SkScalarPin(SkScalar x, SkScalar min, SkScalar max) {
        return x < min ? min : x > max ? max : x;
    }
    /** Returns the specified SkScalar squared (x*x)
    */
    inline SkScalar SkScalarSquare(SkScalar x) { return x * x; }
    /** Returns the product of two SkScalars
    */
    #define SkScalarMul(a, b)       ((float)(a) * (b))
    /** Returns the product of two SkScalars plus a third SkScalar
    */
    #define SkScalarMulAdd(a, b, c) ((float)(a) * (b) + (c))
    /** Returns the product of a SkScalar and an int rounded to the nearest integer value
    */
    #define SkScalarMulRound(a, b) SkScalarRound((float)(a) * (b))
    /** Returns the product of a SkScalar and an int promoted to the next larger int
    */
    #define SkScalarMulCeil(a, b) SkScalarCeil((float)(a) * (b))
    /** Returns the product of a SkScalar and an int truncated to the next smaller int
    */
    #define SkScalarMulFloor(a, b) SkScalarFloor((float)(a) * (b))
    /** Returns the quotient of two SkScalars (a/b)
    */
    #define SkScalarDiv(a, b)       ((float)(a) / (b))
    /** Returns the mod of two SkScalars (a mod b)
    */
    #define SkScalarMod(x,y)        sk_float_mod(x,y)
    /** Returns the product of the first two arguments, divided by the third argument
    */
    #define SkScalarMulDiv(a, b, c) ((float)(a) * (b) / (c))
    /** Returns the multiplicative inverse of the SkScalar (1/x)
    */
    #define SkScalarInvert(x)       (SK_Scalar1 / (x))
    #define SkScalarFastInvert(x)   (SK_Scalar1 / (x))
    /** Returns the square root of the SkScalar
    */
    #define SkScalarSqrt(x)         sk_float_sqrt(x)
    /** Returns the average of two SkScalars (a+b)/2
    */
    #define SkScalarAve(a, b)       (((a) + (b)) * 0.5f)
    /** Returns the geometric mean of two SkScalars
    */
    #define SkScalarMean(a, b)      sk_float_sqrt((float)(a) * (b))
    /** Returns one half of the specified SkScalar
    */
    #define SkScalarHalf(a)         ((a) * 0.5f)

    #define SK_ScalarSqrt2          1.41421356f
    #define SK_ScalarPI             3.14159265f
    #define SK_ScalarTanPIOver8     0.414213562f
    #define SK_ScalarRoot2Over2     0.707106781f

    #define SkDegreesToRadians(degrees) ((degrees) * (SK_ScalarPI / 180))
    float SkScalarSinCos(SkScalar radians, SkScalar* cosValue);
    #define SkScalarSin(radians)    (float)sk_float_sin(radians)
    #define SkScalarCos(radians)    (float)sk_float_cos(radians)
    #define SkScalarTan(radians)    (float)sk_float_tan(radians)
    #define SkScalarASin(val)   (float)sk_float_asin(val)
    #define SkScalarACos(val)   (float)sk_float_acos(val)
    #define SkScalarATan2(y, x) (float)sk_float_atan2(y,x)
    #define SkScalarExp(x)  (float)sk_float_exp(x)
    #define SkScalarLog(x)  (float)sk_float_log(x)

    inline SkScalar SkMaxScalar(SkScalar a, SkScalar b) { return a > b ? a : b; }
    inline SkScalar SkMinScalar(SkScalar a, SkScalar b) { return a < b ? a : b; }

    static inline bool SkScalarIsInt(SkScalar x) {
        return x == (float)(int)x;
    }
#else
    typedef SkFixed SkScalar;

    #define SK_Scalar1              SK_Fixed1
    #define SK_ScalarHalf           SK_FixedHalf
    #define SK_ScalarInfinity   SK_FixedMax
    #define SK_ScalarMax            SK_FixedMax
    #define SK_ScalarMin            SK_FixedMin
    #define SK_ScalarNaN            SK_FixedNaN
    #define SkScalarIsNaN(x)        ((x) == SK_FixedNaN)
    #define SkScalarIsFinite(x)     ((x) != SK_FixedNaN)

    #define SkIntToScalar(n)        SkIntToFixed(n)
    #define SkFixedToScalar(x)      (x)
    #define SkScalarToFixed(x)      (x)
    #ifdef SK_CAN_USE_FLOAT
        #define SkScalarToFloat(n)  SkFixedToFloat(n)
        #define SkFloatToScalar(n)  SkFloatToFixed(n)

        #define SkScalarToDouble(n) SkFixedToDouble(n)
        #define SkDoubleToScalar(n) SkDoubleToFixed(n)
    #endif
    #define SkScalarFraction(x)     SkFixedFraction(x)
    #define SkScalarRound(x)        SkFixedRound(x)
    #define SkScalarCeil(x)         SkFixedCeil(x)
    #define SkScalarFloor(x)        SkFixedFloor(x)
    #define SkScalarAbs(x)          SkFixedAbs(x)
    #define SkScalarCopySign(x, y)  SkCopySign32(x, y)
    #define SkScalarClampMax(x, max) SkClampMax(x, max)
    #define SkScalarPin(x, min, max) SkPin32(x, min, max)
    #define SkScalarSquare(x)       SkFixedSquare(x)
    #define SkScalarMul(a, b)       SkFixedMul(a, b)
    #define SkScalarMulAdd(a, b, c) SkFixedMulAdd(a, b, c)
    #define SkScalarMulRound(a, b)  SkFixedMulCommon(a, b, SK_FixedHalf)
    #define SkScalarMulCeil(a, b)   SkFixedMulCommon(a, b, SK_Fixed1 - 1)
    #define SkScalarMulFloor(a, b)  SkFixedMulCommon(a, b, 0)
    #define SkScalarDiv(a, b)       SkFixedDiv(a, b)
    #define SkScalarMod(a, b)       SkFixedMod(a, b)
    #define SkScalarMulDiv(a, b, c) SkMulDiv(a, b, c)
    #define SkScalarInvert(x)       SkFixedInvert(x)
    #define SkScalarFastInvert(x)   SkFixedFastInvert(x)
    #define SkScalarSqrt(x)         SkFixedSqrt(x)
    #define SkScalarAve(a, b)       SkFixedAve(a, b)
    #define SkScalarMean(a, b)      SkFixedMean(a, b)
    #define SkScalarHalf(a)         ((a) >> 1)

    #define SK_ScalarSqrt2          SK_FixedSqrt2
    #define SK_ScalarPI             SK_FixedPI
    #define SK_ScalarTanPIOver8     SK_FixedTanPIOver8
    #define SK_ScalarRoot2Over2     SK_FixedRoot2Over2

    #define SkDegreesToRadians(degrees)     SkFractMul(degrees, SK_FractPIOver180)
    #define SkScalarSinCos(radians, cosPtr) SkFixedSinCos(radians, cosPtr)
    #define SkScalarSin(radians)    SkFixedSin(radians)
    #define SkScalarCos(radians)    SkFixedCos(radians)
    #define SkScalarTan(val)        SkFixedTan(val)
    #define SkScalarASin(val)       SkFixedASin(val)
    #define SkScalarACos(val)       SkFixedACos(val)
    #define SkScalarATan2(y, x)     SkFixedATan2(y,x)
    #define SkScalarExp(x)          SkFixedExp(x)
    #define SkScalarLog(x)          SkFixedLog(x)

    #define SkMaxScalar(a, b)       SkMax32(a, b)
    #define SkMinScalar(a, b)       SkMin32(a, b)

    static inline bool SkScalarIsInt(SkFixed x) {
        return 0 == (x & 0xffff);
    }
#endif

#define SK_ScalarNearlyZero         (SK_Scalar1 / (1 << 12))

/*  <= is slower than < for floats, so we use < for our tolerance test
*/

static inline bool SkScalarNearlyZero(SkScalar x,
                                    SkScalar tolerance = SK_ScalarNearlyZero) {
    SkASSERT(tolerance > 0);
    return SkScalarAbs(x) < tolerance;
}

static inline bool SkScalarNearlyEqual(SkScalar x, SkScalar y,
                                     SkScalar tolerance = SK_ScalarNearlyZero) {
    SkASSERT(tolerance > 0);
    return SkScalarAbs(x-y) < tolerance;
}

/** Linearly interpolate between A and B, based on t.
    If t is 0, return A
    If t is 1, return B
    else interpolate.
    t must be [0..SK_Scalar1]
*/
static inline SkScalar SkScalarInterp(SkScalar A, SkScalar B, SkScalar t) {
    SkASSERT(t >= 0 && t <= SK_Scalar1);
    return A + SkScalarMul(B - A, t);
}

/** Interpolate along the function described by (keys[length], values[length])
    for the passed searchKey.  SearchKeys outside the range keys[0]-keys[Length]
    clamp to the min or max value.  This function was inspired by a desire
    to change the multiplier for thickness in fakeBold; therefore it assumes
    the number of pairs (length) will be small, and a linear search is used.
    Repeated keys are allowed for discontinuous functions (so long as keys is
    monotonically increasing), and if key is the value of a repeated scalar in
    keys, the first one will be used.  However, that may change if a binary
    search is used.
*/
SkScalar SkScalarInterpFunc(SkScalar searchKey, const SkScalar keys[],
                            const SkScalar values[], int length);

#endif

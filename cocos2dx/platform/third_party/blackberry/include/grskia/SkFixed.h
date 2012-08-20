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

#ifndef SkFixed_DEFINED
#define SkFixed_DEFINED

#include "SkMath.h"

/** \file SkFixed.h

    Types and macros for 16.16 fixed point
*/

/** 32 bit signed integer used to represent fractions values with 16 bits to the right of the decimal point
*/
typedef int32_t             SkFixed;
#define SK_Fixed1           (1 << 16)
#define SK_FixedHalf        (1 << 15)
#define SK_FixedMax         (0x7FFFFFFF)
#define SK_FixedMin         (-SK_FixedMax)
#define SK_FixedNaN         ((int) 0x80000000)
#define SK_FixedPI          (0x3243F)
#define SK_FixedSqrt2       (92682)
#define SK_FixedTanPIOver8  (0x6A0A)
#define SK_FixedRoot2Over2  (0xB505)

#ifdef SK_CAN_USE_FLOAT
    #define SkFixedToFloat(x)   ((x) * 1.5258789e-5f)
#if 1
    #define SkFloatToFixed(x)   ((SkFixed)((x) * SK_Fixed1))
#else
    // pins over/under flows to max/min int32 (slower than just a cast)
    static inline SkFixed SkFloatToFixed(float x) {
        int64_t n = x * SK_Fixed1;
        return (SkFixed)n;
    }
#endif

    #define SkFixedToDouble(x)  ((x) * 1.5258789e-5)
    #define SkDoubleToFixed(x)  ((SkFixed)((x) * SK_Fixed1))
#endif

/** 32 bit signed integer used to represent fractions values with 30 bits to the right of the decimal point
*/
typedef int32_t             SkFract;
#define SK_Fract1           (1 << 30)
#define Sk_FracHalf         (1 << 29)
#define SK_FractPIOver180   (0x11DF46A)

#ifdef SK_CAN_USE_FLOAT
    #define SkFractToFloat(x)   ((float)(x) * 0.00000000093132257f)
    #define SkFloatToFract(x)   ((SkFract)((x) * SK_Fract1))
#endif

/** Converts an integer to a SkFixed, asserting that the result does not overflow
    a 32 bit signed integer
*/
#ifdef SK_DEBUG
    inline SkFixed SkIntToFixed(int n)
    {
        SkASSERT(n >= -32768 && n <= 32767);
        return n << 16;
    }
#else
    //  force the cast to SkFixed to ensure that the answer is signed (like the debug version)
    #define SkIntToFixed(n)     (SkFixed)((n) << 16)
#endif

/** Converts a SkFixed to a SkFract, asserting that the result does not overflow
    a 32 bit signed integer
*/
#ifdef SK_DEBUG
    inline SkFract SkFixedToFract(SkFixed x)
    {
        SkASSERT(x >= (-2 << 16) && x <= (2 << 16) - 1);
        return x << 14;
    }
#else
    #define SkFixedToFract(x)   ((x) << 14)
#endif

/** Returns the signed fraction of a SkFixed
*/
inline SkFixed SkFixedFraction(SkFixed x)
{
    SkFixed mask = x >> 31 << 16;
    return (x & 0xFFFF) | mask;
}

/** Converts a SkFract to a SkFixed
*/
#define SkFractToFixed(x)   ((x) >> 14)
/** Round a SkFixed to an integer
*/
#define SkFixedRound(x)     (((x) + SK_FixedHalf) >> 16)
#define SkFixedCeil(x)      (((x) + SK_Fixed1 - 1) >> 16)
#define SkFixedFloor(x)     ((x) >> 16)
#define SkFixedAbs(x)       SkAbs32(x)
#define SkFixedAve(a, b)    (((a) + (b)) >> 1)

// The same as SkIntToFixed(SkFixedFloor(x))
#define SkFixedFloorToFixed(x)  ((x) & ~0xFFFF)

SkFixed SkFixedMul_portable(SkFixed, SkFixed);
SkFract SkFractMul_portable(SkFract, SkFract);
inline SkFixed SkFixedSquare_portable(SkFixed value)
{
    uint32_t a = SkAbs32(value);
    uint32_t ah = a >> 16;
    uint32_t al = a & 0xFFFF;
    SkFixed result = ah * a + al * ah + (al * al >> 16);
    if (result >= 0)
        return result;
    else // Overflow.
        return SK_FixedMax;
}

#define SkFixedDiv(numer, denom)    SkDivBits(numer, denom, 16)
SkFixed SkFixedDivInt(int32_t numer, int32_t denom);
SkFixed SkFixedMod(SkFixed numer, SkFixed denom);
#define SkFixedInvert(n)            SkDivBits(SK_Fixed1, n, 16)
SkFixed SkFixedFastInvert(SkFixed n);
#define SkFixedSqrt(n)              SkSqrtBits(n, 23)
SkFixed SkFixedMean(SkFixed a, SkFixed b);  //*< returns sqrt(x*y)
int SkFixedMulCommon(SkFixed, int , int bias);  // internal used by SkFixedMulFloor, SkFixedMulCeil, SkFixedMulRound

#define SkFractDiv(numer, denom)    SkDivBits(numer, denom, 30)
#define SkFractSqrt(n)              SkSqrtBits(n, 30)

SkFixed SkFixedSinCos(SkFixed radians, SkFixed* cosValueOrNull);
#define SkFixedSin(radians)         SkFixedSinCos(radians, NULL)
inline SkFixed SkFixedCos(SkFixed radians)
{
    SkFixed cosValue;
    (void)SkFixedSinCos(radians, &cosValue);
    return cosValue;
}
SkFixed SkFixedTan(SkFixed radians);
SkFixed SkFixedASin(SkFixed);
SkFixed SkFixedACos(SkFixed);
SkFixed SkFixedATan2(SkFixed y, SkFixed x);
SkFixed SkFixedExp(SkFixed);
SkFixed SkFixedLog(SkFixed);

#define SK_FixedNearlyZero          (SK_Fixed1 >> 12)

inline bool SkFixedNearlyZero(SkFixed x, SkFixed tolerance = SK_FixedNearlyZero)
{
    SkASSERT(tolerance > 0);
    return SkAbs32(x) < tolerance;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Now look for ASM overrides for our portable versions (should consider putting this in its own file)

#ifdef SkLONGLONG
    inline SkFixed SkFixedMul_longlong(SkFixed a, SkFixed b)
    {
        return (SkFixed)((SkLONGLONG)a * b >> 16);
    }
    inline SkFract SkFractMul_longlong(SkFract a, SkFract b)
    {
        return (SkFixed)((SkLONGLONG)a * b >> 30);
    }
    inline SkFixed SkFixedSquare_longlong(SkFixed value)
    {
        return (SkFixed)((SkLONGLONG)value * value >> 16);
    }
    #define SkFixedMul(a,b)     SkFixedMul_longlong(a,b)
    #define SkFractMul(a,b)     SkFractMul_longlong(a,b)
    #define SkFixedSquare(a)    SkFixedSquare_longlong(a)
#endif

#if defined(__arm__) && !defined(__thumb__)
    /* This guy does not handle NaN or other obscurities, but is faster than
       than (int)(x*65536) when we only have software floats
    */
    inline SkFixed SkFloatToFixed_arm(float x)
    {
        register int32_t y, z;
        asm("movs    %1, %3, lsl #1         \n"
            "mov     %2, #0x8E              \n"
            "sub     %1, %2, %1, lsr #24    \n"
            "mov     %2, %3, lsl #8         \n"
            "orr     %2, %2, #0x80000000    \n"
            "mov     %1, %2, lsr %1         \n"
            "rsbcs   %1, %1, #0             \n"
            : "=r"(x), "=&r"(y), "=&r"(z)
            : "r"(x)
            : "cc"
            );
        return y;
    }
    inline SkFixed SkFixedMul_arm(SkFixed x, SkFixed y)
    {
        register int32_t t;
        asm("smull  %0, %2, %1, %3          \n"
            "mov    %0, %0, lsr #16         \n"
            "orr    %0, %0, %2, lsl #16     \n"
            : "=r"(x), "=&r"(y), "=r"(t)
            : "r"(x), "1"(y)
            :
            );
        return x;
    }
    inline SkFixed SkFixedMulAdd_arm(SkFixed x, SkFixed y, SkFixed a)
    {
        register int32_t t;
        asm("smull  %0, %3, %1, %4          \n"
            "add    %0, %2, %0, lsr #16     \n"
            "add    %0, %0, %3, lsl #16     \n"
            : "=r"(x), "=&r"(y), "=&r"(a), "=r"(t)
            : "%r"(x), "1"(y), "2"(a)
            :
            );
        return x;
    }
    inline SkFixed SkFractMul_arm(SkFixed x, SkFixed y)
    {
        register int32_t t;
        asm("smull  %0, %2, %1, %3          \n"
            "mov    %0, %0, lsr #30         \n"
            "orr    %0, %0, %2, lsl #2      \n"
            : "=r"(x), "=&r"(y), "=r"(t)
            : "r"(x), "1"(y)
            :
            );
        return x;
    }
    #undef SkFixedMul
    #undef SkFractMul
    #define SkFixedMul(x, y)        SkFixedMul_arm(x, y)
    #define SkFractMul(x, y)        SkFractMul_arm(x, y)
    #define SkFixedMulAdd(x, y, a)  SkFixedMulAdd_arm(x, y, a)

    #undef SkFloatToFixed
    #define SkFloatToFixed(x)  SkFloatToFixed_arm(x)
#endif

/////////////////////// Now define our macros to the portable versions if they weren't overridden

#ifndef SkFixedSquare
    #define SkFixedSquare(x)    SkFixedSquare_portable(x)
#endif
#ifndef SkFixedMul
    #define SkFixedMul(x, y)    SkFixedMul_portable(x, y)
#endif
#ifndef SkFractMul
    #define SkFractMul(x, y)    SkFractMul_portable(x, y)
#endif
#ifndef SkFixedMulAdd
    #define SkFixedMulAdd(x, y, a)  (SkFixedMul(x, y) + (a))
#endif

#endif

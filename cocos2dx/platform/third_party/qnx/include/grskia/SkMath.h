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

#ifndef SkMath_DEFINED
#define SkMath_DEFINED

#include "SkTypes.h"

//! Returns the number of leading zero bits (0...32)
int SkCLZ_portable(uint32_t);

/** Computes the 64bit product of a * b, and then shifts the answer down by
    shift bits, returning the low 32bits. shift must be [0..63]
    e.g. to perform a fixedmul, call SkMulShift(a, b, 16)
*/
int32_t SkMulShift(int32_t a, int32_t b, unsigned shift);

/** Computes numer1 * numer2 / denom in full 64 intermediate precision.
    It is an error for denom to be 0. There is no special handling if
    the result overflows 32bits.
*/
int32_t SkMulDiv(int32_t numer1, int32_t numer2, int32_t denom);

/** Computes (numer1 << shift) / denom in full 64 intermediate precision.
    It is an error for denom to be 0. There is no special handling if
    the result overflows 32bits.
*/
int32_t SkDivBits(int32_t numer, int32_t denom, int shift);

/** Return the integer square root of value, with a bias of bitBias
*/
int32_t SkSqrtBits(int32_t value, int bitBias);

/** Return the integer square root of n, treated as a SkFixed (16.16)
*/
#define SkSqrt32(n)         SkSqrtBits(n, 15)

/** Return the integer cube root of value, with a bias of bitBias
 */
int32_t SkCubeRootBits(int32_t value, int bitBias);

/** Returns -1 if n < 0, else returns 0
*/
#define SkExtractSign(n)    ((int32_t)(n) >> 31)

/** If sign == -1, returns -n, else sign must be 0, and returns n.
    Typically used in conjunction with SkExtractSign().
*/
static inline int32_t SkApplySign(int32_t n, int32_t sign) {
    SkASSERT(sign == 0 || sign == -1);
    return (n ^ sign) - sign;
}

/** Return x with the sign of y */
static inline int32_t SkCopySign32(int32_t x, int32_t y) {
    return SkApplySign(x, SkExtractSign(x ^ y));
}

/** Returns (value < 0 ? 0 : value) efficiently (i.e. no compares or branches)
*/
static inline int SkClampPos(int value) {
    return value & ~(value >> 31);
}

/** Given an integer and a positive (max) integer, return the value
    pinned against 0 and max, inclusive.
    @param value    The value we want returned pinned between [0...max]
    @param max      The positive max value
    @return 0 if value < 0, max if value > max, else value
*/
static inline int SkClampMax(int value, int max) {
    // ensure that max is positive
    SkASSERT(max >= 0);
    if (value < 0) {
        value = 0;
    }
    if (value > max) {
        value = max;
    }
    return value;
}

/** Given a positive value and a positive max, return the value
    pinned against max.
    Note: only works as long as max - value doesn't wrap around
    @return max if value >= max, else value
*/
static inline unsigned SkClampUMax(unsigned value, unsigned max) {
#ifdef SK_CPU_HAS_CONDITIONAL_INSTR
    if (value > max) {
        value = max;
    }
    return value;
#else
    int diff = max - value;
    // clear diff if diff is positive
    diff &= diff >> 31;

    return value + diff;
#endif
}

///////////////////////////////////////////////////////////////////////////////

#if defined(__arm__)
    #define SkCLZ(x)    __builtin_clz(x)
#endif

#ifndef SkCLZ
    #define SkCLZ(x)    SkCLZ_portable(x)
#endif

///////////////////////////////////////////////////////////////////////////////

/** Returns the smallest power-of-2 that is >= the specified value. If value
    is already a power of 2, then it is returned unchanged. It is undefined
    if value is <= 0.
*/
static inline int SkNextPow2(int value) {
    SkASSERT(value > 0);
    return 1 << (32 - SkCLZ(value - 1));
}

/** Returns the log2 of the specified value, were that value to be rounded up
    to the next power of 2. It is undefined to pass 0. Examples:
         SkNextLog2(1) -> 0
         SkNextLog2(2) -> 1
         SkNextLog2(3) -> 2
         SkNextLog2(4) -> 2
         SkNextLog2(5) -> 3
*/
static inline int SkNextLog2(uint32_t value) {
    SkASSERT(value != 0);
    return 32 - SkCLZ(value - 1);
}

/** Returns true if value is a power of 2. Does not explicitly check for
    value <= 0.
 */
static inline bool SkIsPow2(int value) {
    return (value & (value - 1)) == 0;
}

///////////////////////////////////////////////////////////////////////////////

/** SkMulS16(a, b) multiplies a * b, but requires that a and b are both int16_t.
    With this requirement, we can generate faster instructions on some
    architectures.
*/
#if defined(__arm__) \
  && !defined(__thumb__) \
  && !defined(__ARM_ARCH_4T__) \
  && !defined(__ARM_ARCH_5T__)
    static inline int32_t SkMulS16(S16CPU x, S16CPU y) {
        SkASSERT((int16_t)x == x);
        SkASSERT((int16_t)y == y);
        int32_t product;
        asm("smulbb %0, %1, %2 \n"
            : "=r"(product)
            : "r"(x), "r"(y)
            );
        return product;
    }
#else
    #ifdef SK_DEBUG
        static inline int32_t SkMulS16(S16CPU x, S16CPU y) {
            SkASSERT((int16_t)x == x);
            SkASSERT((int16_t)y == y);
            return x * y;
        }
    #else
        #define SkMulS16(x, y)  ((x) * (y))
    #endif
#endif

/** Return a*b/255, truncating away any fractional bits. Only valid if both
    a and b are 0..255
*/
static inline U8CPU SkMulDiv255Trunc(U8CPU a, U8CPU b) {
    SkASSERT((uint8_t)a == a);
    SkASSERT((uint8_t)b == b);
    unsigned prod = SkMulS16(a, b) + 1;
    return (prod + (prod >> 8)) >> 8;
}

/** Return a*b/255, rounding any fractional bits. Only valid if both
    a and b are 0..255
 */
static inline U8CPU SkMulDiv255Round(U8CPU a, U8CPU b) {
    SkASSERT((uint8_t)a == a);
    SkASSERT((uint8_t)b == b);
    unsigned prod = SkMulS16(a, b) + 128;
    return (prod + (prod >> 8)) >> 8;
}

/** Return (a*b)/255, taking the ceiling of any fractional bits. Only valid if
    both a and b are 0..255. The expected result equals (a * b + 254) / 255.
 */
static inline U8CPU SkMulDiv255Ceiling(U8CPU a, U8CPU b) {
    SkASSERT((uint8_t)a == a);
    SkASSERT((uint8_t)b == b);
    unsigned prod = SkMulS16(a, b) + 255;
    return (prod + (prod >> 8)) >> 8;
}

/** Return a*b/((1 << shift) - 1), rounding any fractional bits.
    Only valid if a and b are unsigned and <= 32767 and shift is > 0 and <= 8
*/
static inline unsigned SkMul16ShiftRound(unsigned a, unsigned b, int shift) {
    SkASSERT(a <= 32767);
    SkASSERT(b <= 32767);
    SkASSERT(shift > 0 && shift <= 8);
    unsigned prod = SkMulS16(a, b) + (1 << (shift - 1));
    return (prod + (prod >> shift)) >> shift;
}

/** Just the rounding step in SkDiv255Round: round(value / 255)
 */
static inline unsigned SkDiv255Round(unsigned prod) {
    prod += 128;
    return (prod + (prod >> 8)) >> 8;
}

#endif


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

#ifndef SkFloatingPoint_DEFINED
#define SkFloatingPoint_DEFINED

#include "SkTypes.h"

#ifdef SK_CAN_USE_FLOAT

#include <math.h>
#include <float.h>
#include "SkFloatBits.h"

// If math.h had powf(float, float), I could remove this wrapper
static inline float sk_float_pow(float base, float exp) {
    return static_cast<float>(pow(static_cast<double>(base),
                                  static_cast<double>(exp)));
}

static inline float sk_float_copysign(float x, float y) {
    int32_t xbits = SkFloat2Bits(x);
    int32_t ybits = SkFloat2Bits(y);
    return SkBits2Float((xbits & 0x7FFFFFFF) | (ybits & 0x80000000));
}

#ifdef SK_BUILD_FOR_WINCE
    #define sk_float_sqrt(x)        (float)::sqrt(x)
    #define sk_float_sin(x)         (float)::sin(x)
    #define sk_float_cos(x)         (float)::cos(x)
    #define sk_float_tan(x)         (float)::tan(x)
    #define sk_float_acos(x)        (float)::acos(x)
    #define sk_float_asin(x)        (float)::asin(x)
    #define sk_float_atan2(y,x)     (float)::atan2(y,x)
    #define sk_float_abs(x)         (float)::fabs(x)
    #define sk_float_mod(x,y)       (float)::fmod(x,y)
    #define sk_float_exp(x)         (float)::exp(x)
    #define sk_float_log(x)         (float)::log(x)
    #define sk_float_floor(x)       (float)::floor(x)
    #define sk_float_ceil(x)        (float)::ceil(x)
#else
    #define sk_float_sqrt(x)        sqrtf(x)
    #define sk_float_sin(x)         sinf(x)
    #define sk_float_cos(x)         cosf(x)
    #define sk_float_tan(x)         tanf(x)
    #define sk_float_floor(x)       floorf(x)
    #define sk_float_ceil(x)        ceilf(x)
#ifdef SK_BUILD_FOR_MAC
    #define sk_float_acos(x)        static_cast<float>(acos(x))
    #define sk_float_asin(x)        static_cast<float>(asin(x))
#else
    #define sk_float_acos(x)        acosf(x)
    #define sk_float_asin(x)        asinf(x)
#endif
    #define sk_float_atan2(y,x) atan2f(y,x)
    #define sk_float_abs(x)         fabsf(x)
    #define sk_float_mod(x,y)       fmodf(x,y)
    #define sk_float_exp(x)         expf(x)
    #define sk_float_log(x)         logf(x)
    #define sk_float_isNaN(x)       _isnan(x)
#endif

#ifdef SK_USE_FLOATBITS
    #define sk_float_floor2int(x)   SkFloatToIntFloor(x)
    #define sk_float_round2int(x)   SkFloatToIntRound(x)
    #define sk_float_ceil2int(x)    SkFloatToIntCeil(x)
#else
    #define sk_float_floor2int(x)   (int)sk_float_floor(x)
    #define sk_float_round2int(x)   (int)sk_float_floor((x) + 0.5f)
    #define sk_float_ceil2int(x)    (int)sk_float_ceil(x)
#endif

#endif
#endif

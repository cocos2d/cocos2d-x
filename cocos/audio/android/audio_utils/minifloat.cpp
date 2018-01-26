/*
 * Copyright (C) 2014 The Android Open Source Project
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

#include <cmath>
#include "audio/android/audio_utils/include/audio_utils/minifloat.h"

#define EXPONENT_BITS   3
#define EXPONENT_MAX    ((1 << EXPONENT_BITS) - 1)
#define EXCESS          ((1 << EXPONENT_BITS) - 2)

#define MANTISSA_BITS   13
#define MANTISSA_MAX    ((1 << MANTISSA_BITS) - 1)
#define HIDDEN_BIT      (1 << MANTISSA_BITS)
#define ONE_FLOAT       ((float) (1 << (MANTISSA_BITS + 1)))

#define MINIFLOAT_MAX   ((EXPONENT_MAX << MANTISSA_BITS) | MANTISSA_MAX)

#if EXPONENT_BITS + MANTISSA_BITS != 16
#error EXPONENT_BITS and MANTISSA_BITS must sum to 16
#endif

extern "C" {

gain_minifloat_t gain_from_float(float v)
{
    if (std::isnan(v) || v <= 0.0f)
    {
        return 0;
    }
    if (v >= 2.0f)
    {
        return MINIFLOAT_MAX;
    }
    int exp;
    float r = frexpf(v, &exp);
    if ((exp += EXCESS) > EXPONENT_MAX)
    {
        return MINIFLOAT_MAX;
    }
    if (-exp >= MANTISSA_BITS)
    {
        return 0;
    }
    int mantissa = (int) (r * ONE_FLOAT);
    return exp > 0 ? (exp << MANTISSA_BITS) | (mantissa & ~HIDDEN_BIT) :
           (mantissa >> (1 - exp)) & MANTISSA_MAX;
}

float float_from_gain(gain_minifloat_t a)
{
    int mantissa = a & MANTISSA_MAX;
    int exponent = (a >> MANTISSA_BITS) & EXPONENT_MAX;
    return ldexpf((exponent > 0 ? HIDDEN_BIT | mantissa : mantissa << 1) / ONE_FLOAT,
                  exponent - EXCESS);
}

} // extern "C" {

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

#ifndef COCOS_AUDIO_MINIFLOAT_H
#define COCOS_AUDIO_MINIFLOAT_H

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/* A single gain expressed as minifloat */
typedef uint16_t gain_minifloat_t;

/* A pair of gain_minifloat_t packed into a single word */
typedef uint32_t gain_minifloat_packed_t;

/* The nominal range of a gain, expressed as a float */
#define GAIN_FLOAT_ZERO         0.0f
#define GAIN_FLOAT_UNITY        1.0f

/* Unity gain expressed as a minifloat */
#define GAIN_MINIFLOAT_UNITY    0xE000

/* Pack a pair of gain_mini_float_t into a combined gain_minifloat_packed_t */
static inline gain_minifloat_packed_t gain_minifloat_pack(gain_minifloat_t left,
        gain_minifloat_t right)
{
    return (right << 16) | left;
}

/* Unpack a gain_minifloat_packed_t into the two gain_minifloat_t components */
static inline gain_minifloat_t gain_minifloat_unpack_left(gain_minifloat_packed_t packed)
{
    return packed & 0xFFFF;
}

static inline gain_minifloat_t gain_minifloat_unpack_right(gain_minifloat_packed_t packed)
{
    return packed >> 16;
}

/* A pair of unity gains expressed as a gain_minifloat_packed_t */
#define GAIN_MINIFLOAT_PACKED_UNITY gain_minifloat_pack(GAIN_MINIFLOAT_UNITY, GAIN_MINIFLOAT_UNITY)

/* Convert a float to the internal representation used for gains.
 * The nominal range [0.0, 1.0], but the hard range is [0.0, 2.0).
 * Negative and underflow values are converted to 0.0,
 * and values larger than the hard maximum are truncated to the hard maximum.
 *
 * Minifloats are ordered, and standard comparisons may be used between them
 * in the gain_minifloat_t representation.
 *
 * Details on internal representation of gains, based on mini-floats:
 * The nominal maximum is 1.0 and the hard maximum is 1 ULP less than 2.0, or +6 dB.
 * The minimum non-zero value is approximately 1.9e-6 or -114 dB.
 * Negative numbers, infinity, and NaN are not supported.
 * There are 13 significand bits specified, 1 implied hidden bit, 3 exponent bits,
 * and no sign bit.  Denormals are supported.
 */
gain_minifloat_t gain_from_float(float f);

/* Convert the internal representation used for gains to float */
float float_from_gain(gain_minifloat_t gain);

__END_DECLS

#endif  // COCOS_AUDIO_MINIFLOAT_H

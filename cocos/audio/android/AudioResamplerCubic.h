/*
 * Copyright (C) 2007 The Android Open Source Project
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

#pragma once

#include <stdint.h>
#include <sys/types.h>

#include "audio/android/AudioResampler.h"
#include "audio/android/AudioBufferProvider.h"

namespace cocos2d { namespace experimental {
// ----------------------------------------------------------------------------

class AudioResamplerCubic : public AudioResampler {
public:
    AudioResamplerCubic(int inChannelCount, int32_t sampleRate) :
        AudioResampler(inChannelCount, sampleRate, MED_QUALITY) {
    }
    virtual size_t resample(int32_t* out, size_t outFrameCount,
            AudioBufferProvider* provider);
private:
    // number of bits used in interpolation multiply - 14 bits avoids overflow
    static const int kNumInterpBits = 14;

    // bits to shift the phase fraction down to avoid overflow
    static const int kPreInterpShift = kNumPhaseBits - kNumInterpBits;
    typedef struct {
        int32_t a, b, c, y0, y1, y2, y3;
    } state;
    void init();
    size_t resampleMono16(int32_t* out, size_t outFrameCount,
            AudioBufferProvider* provider);
    size_t resampleStereo16(int32_t* out, size_t outFrameCount,
            AudioBufferProvider* provider);
    static inline int32_t interp(state* p, int32_t x) {
        return (((((p->a * x >> 14) + p->b) * x >> 14) + p->c) * x >> 14) + p->y1;
    }
    static inline void advance(state* p, int16_t in) {
        p->y0 = p->y1;
        p->y1 = p->y2;
        p->y2 = p->y3;
        p->y3 = in;
        p->a = (3 * (p->y1 - p->y2) - p->y0 + p->y3) >> 1;
        p->b = (p->y2 << 1) + p->y0 - (((5 * p->y1 + p->y3)) >> 1);
        p->c = (p->y2 - p->y0) >> 1;
    }
    state left, right;
};

// ----------------------------------------------------------------------------
}} // namespace cocos2d { namespace experimental {

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

#ifndef ANDROID_AUDIO_RESAMPLER_SINC_H
#define ANDROID_AUDIO_RESAMPLER_SINC_H

#include <stdint.h>
#include <sys/types.h>
//#include <cutils/log.h>

#include "audio/android/AudioResampler.h"
#include "audio/android/AudioBufferProvider.h"

namespace cocos2d { namespace experimental {


typedef const int32_t * (*readCoefficientsFn)(bool upDownSample);
typedef int32_t (*readResampleFirNumCoeffFn)();
typedef int32_t (*readResampleFirLerpIntBitsFn)();

// ----------------------------------------------------------------------------

class AudioResamplerSinc : public AudioResampler {
public:
    AudioResamplerSinc(int inChannelCount, int32_t sampleRate,
            src_quality quality = HIGH_QUALITY);

    virtual ~AudioResamplerSinc();

    virtual size_t resample(int32_t* out, size_t outFrameCount,
            AudioBufferProvider* provider);
private:
    void init();

    virtual void setVolume(float left, float right);

    template<int CHANNELS>
    size_t resample(int32_t* out, size_t outFrameCount,
            AudioBufferProvider* provider);

    template<int CHANNELS>
    inline void filterCoefficient(
            int32_t* out, uint32_t phase, const int16_t *samples, uint32_t vRL);

    template<int CHANNELS>
    inline void interpolate(
            int32_t& l, int32_t& r,
            const int32_t* coefs, size_t offset,
            int32_t lerp, const int16_t* samples);

    template<int CHANNELS>
    inline void read(int16_t*& impulse, uint32_t& phaseFraction,
            const int16_t* in, size_t inputIndex);

    int16_t *mState;
    int16_t *mImpulse;
    int16_t *mRingFull;
    int32_t mVolumeSIMD[2];

    const int32_t * mFirCoefs;
    static const uint32_t mFirCoefsDown[];
    static const uint32_t mFirCoefsUp[];

    // ----------------------------------------------------------------------------
    static const int32_t RESAMPLE_FIR_NUM_COEF       = 8;
    static const int32_t RESAMPLE_FIR_LERP_INT_BITS  = 7;

    struct Constants {
        int coefsBits;
        int cShift;
        uint32_t cMask;
        int pShift;
        uint32_t pMask;
        // number of zero-crossing on each side
        unsigned int halfNumCoefs;
    };

    static Constants highQualityConstants;
    static Constants veryHighQualityConstants;
    const Constants *mConstants;    // points to appropriate set of coefficient parameters

    static void init_routine();
};

// ----------------------------------------------------------------------------
}} // namespace cocos2d { namespace experimental {

#endif /*ANDROID_AUDIO_RESAMPLER_SINC_H*/

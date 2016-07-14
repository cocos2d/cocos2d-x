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

#define LOG_TAG "AudioResamplerSinc"
//#define LOG_NDEBUG 0

#define __STDC_CONSTANT_MACROS
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>

//#include <cutils/compiler.h>
//#include <cutils/properties.h>

#include "audio/android/cutils/log.h"
#include "audio/android/audio_utils/include/audio_utils/primitives.h"

#include "audio/android/AudioResamplerSinc.h"

#if 0//cjhdefined(__clang__) && !__has_builtin(__builtin_assume_aligned)
#define __builtin_assume_aligned(p, a) \
	(((uintptr_t(p) % (a)) == 0) ? (p) : (__builtin_unreachable(), (p)))
#endif

#if 0//cjh defined(__arm__) && !defined(__thumb__)
#define USE_INLINE_ASSEMBLY (true)
#else
#define USE_INLINE_ASSEMBLY (false)
#endif

#if 0//cjh defined(__aarch64__) || defined(__ARM_NEON__)
#include <arm_neon.h>
#define USE_NEON
#else
#undef USE_NEON
#endif

#define UNUSED(x) ((void)(x))

namespace cocos2d { namespace experimental {
// ----------------------------------------------------------------------------


/*
 * These coeficients are computed with the "fir" utility found in
 * tools/resampler_tools
 * cmd-line: fir -l 7 -s 48000 -c 20478
 */
const uint32_t AudioResamplerSinc::mFirCoefsUp[] __attribute__ ((aligned (32))) = {
#include "audio/android/AudioResamplerSincUp.h"
};

/*
 * These coefficients are optimized for 48KHz -> 44.1KHz
 * cmd-line: fir -l 7 -s 48000 -c 17189
 */
const uint32_t AudioResamplerSinc::mFirCoefsDown[] __attribute__ ((aligned (32))) = {
#include "audio/android/AudioResamplerSincDown.h"
};

// we use 15 bits to interpolate between these samples
// this cannot change because the mul below rely on it.
static const int pLerpBits = 15;

static pthread_once_t once_control = PTHREAD_ONCE_INIT;
static readCoefficientsFn readResampleCoefficients = NULL;

/*static*/ AudioResamplerSinc::Constants AudioResamplerSinc::highQualityConstants;
/*static*/ AudioResamplerSinc::Constants AudioResamplerSinc::veryHighQualityConstants;

void AudioResamplerSinc::init_routine()
{
    // for high quality resampler, the parameters for coefficients are compile-time constants
    Constants *c = &highQualityConstants;
    c->coefsBits = RESAMPLE_FIR_LERP_INT_BITS;
    c->cShift = kNumPhaseBits - c->coefsBits;
    c->cMask = ((1<< c->coefsBits)-1) << c->cShift;
    c->pShift = kNumPhaseBits - c->coefsBits - pLerpBits;
    c->pMask = ((1<< pLerpBits)-1) << c->pShift;
    c->halfNumCoefs = RESAMPLE_FIR_NUM_COEF;

    // for very high quality resampler, the parameters are load-time constants
    veryHighQualityConstants = highQualityConstants;

    // Open the dll to get the coefficients for VERY_HIGH_QUALITY
    void *resampleCoeffLib = dlopen("libaudio-resampler.so", RTLD_NOW);
    ALOGV("Open libaudio-resampler library = %p", resampleCoeffLib);
    if (resampleCoeffLib == NULL) {
        ALOGE("Could not open audio-resampler library: %s", dlerror());
        return;
    }

    readResampleFirNumCoeffFn readResampleFirNumCoeff;
    readResampleFirLerpIntBitsFn readResampleFirLerpIntBits;

    readResampleCoefficients = (readCoefficientsFn)
            dlsym(resampleCoeffLib, "readResamplerCoefficients");
    readResampleFirNumCoeff = (readResampleFirNumCoeffFn)
            dlsym(resampleCoeffLib, "readResampleFirNumCoeff");
    readResampleFirLerpIntBits = (readResampleFirLerpIntBitsFn)
            dlsym(resampleCoeffLib, "readResampleFirLerpIntBits");

    if (!readResampleCoefficients || !readResampleFirNumCoeff || !readResampleFirLerpIntBits) {
        readResampleCoefficients = NULL;
        dlclose(resampleCoeffLib);
        resampleCoeffLib = NULL;
        ALOGE("Could not find symbol: %s", dlerror());
        return;
    }

    c = &veryHighQualityConstants;
    c->coefsBits = readResampleFirLerpIntBits();
    c->cShift = kNumPhaseBits - c->coefsBits;
    c->cMask = ((1<<c->coefsBits)-1) << c->cShift;
    c->pShift = kNumPhaseBits - c->coefsBits - pLerpBits;
    c->pMask = ((1<<pLerpBits)-1) << c->pShift;
    // number of zero-crossing on each side
    c->halfNumCoefs = readResampleFirNumCoeff();
    ALOGV("coefsBits = %d", c->coefsBits);
    ALOGV("halfNumCoefs = %d", c->halfNumCoefs);
    // note that we "leak" resampleCoeffLib until the process exits
}

// ----------------------------------------------------------------------------

static inline
int32_t mulRL(int left, int32_t in, uint32_t vRL)
{
#if USE_INLINE_ASSEMBLY
    int32_t out;
    if (left) {
        asm( "smultb %[out], %[in], %[vRL] \n"
             : [out]"=r"(out)
             : [in]"%r"(in), [vRL]"r"(vRL)
             : );
    } else {
        asm( "smultt %[out], %[in], %[vRL] \n"
             : [out]"=r"(out)
             : [in]"%r"(in), [vRL]"r"(vRL)
             : );
    }
    return out;
#else
    int16_t v = left ? int16_t(vRL) : int16_t(vRL>>16);
    return int32_t((int64_t(in) * v) >> 16);
#endif
}

static inline
int32_t mulAdd(int16_t in, int32_t v, int32_t a)
{
#if USE_INLINE_ASSEMBLY
    int32_t out;
    asm( "smlawb %[out], %[v], %[in], %[a] \n"
         : [out]"=r"(out)
         : [in]"%r"(in), [v]"r"(v), [a]"r"(a)
         : );
    return out;
#else
    return a + int32_t((int64_t(v) * in) >> 16);
#endif
}

static inline
int32_t mulAddRL(int left, uint32_t inRL, int32_t v, int32_t a)
{
#if USE_INLINE_ASSEMBLY
    int32_t out;
    if (left) {
        asm( "smlawb %[out], %[v], %[inRL], %[a] \n"
             : [out]"=r"(out)
             : [inRL]"%r"(inRL), [v]"r"(v), [a]"r"(a)
             : );
    } else {
        asm( "smlawt %[out], %[v], %[inRL], %[a] \n"
             : [out]"=r"(out)
             : [inRL]"%r"(inRL), [v]"r"(v), [a]"r"(a)
             : );
    }
    return out;
#else
    int16_t s = left ? int16_t(inRL) : int16_t(inRL>>16);
    return a + int32_t((int64_t(v) * s) >> 16);
#endif
}

// ----------------------------------------------------------------------------

AudioResamplerSinc::AudioResamplerSinc(
        int inChannelCount, int32_t sampleRate, src_quality quality)
    : AudioResampler(inChannelCount, sampleRate, quality),
    mState(0), mImpulse(0), mRingFull(0), mFirCoefs(0)
{
    /*
     * Layout of the state buffer for 32 tap:
     *
     * "present" sample            beginning of 2nd buffer
     *                 v                v
     *  0              01               2              23              3
     *  0              F0               0              F0              F
     * [pppppppppppppppInnnnnnnnnnnnnnnnpppppppppppppppInnnnnnnnnnnnnnnn]
     *                 ^               ^ head
     *
     * p = past samples, convoluted with the (p)ositive side of sinc()
     * n = future samples, convoluted with the (n)egative side of sinc()
     * r = extra space for implementing the ring buffer
     *
     */

    mVolumeSIMD[0] = 0;
    mVolumeSIMD[1] = 0;

    // Load the constants for coefficients
    int ok = pthread_once(&once_control, init_routine);
    if (ok != 0) {
        ALOGE("%s pthread_once failed: %d", __func__, ok);
    }
    mConstants = (quality == VERY_HIGH_QUALITY) ?
            &veryHighQualityConstants : &highQualityConstants;
}


AudioResamplerSinc::~AudioResamplerSinc() {
    free(mState);
}

void AudioResamplerSinc::init() {
    const Constants& c(*mConstants);
    const size_t numCoefs = 2 * c.halfNumCoefs;
    const size_t stateSize = numCoefs * mChannelCount * 2;
    mState = (int16_t*)memalign(32, stateSize*sizeof(int16_t));
    memset(mState, 0, sizeof(int16_t)*stateSize);
    mImpulse  = mState   + (c.halfNumCoefs-1)*mChannelCount;
    mRingFull = mImpulse + (numCoefs+1)*mChannelCount;
}

void AudioResamplerSinc::setVolume(float left, float right) {
    AudioResampler::setVolume(left, right);
    // convert to U4_28 (rounding down).
    // integer volume values are clamped to 0 to UNITY_GAIN.
    mVolumeSIMD[0] = u4_28_from_float(clampFloatVol(left));
    mVolumeSIMD[1] = u4_28_from_float(clampFloatVol(right));
}

size_t AudioResamplerSinc::resample(int32_t* out, size_t outFrameCount,
            AudioBufferProvider* provider)
{
    // FIXME store current state (up or down sample) and only load the coefs when the state
    // changes. Or load two pointers one for up and one for down in the init function.
    // Not critical now since the read functions are fast, but would be important if read was slow.
    if (mConstants == &veryHighQualityConstants && readResampleCoefficients) {
        mFirCoefs = readResampleCoefficients( mInSampleRate <= mSampleRate );
    } else {
        mFirCoefs = (const int32_t *)
                ((mInSampleRate <= mSampleRate) ? mFirCoefsUp : mFirCoefsDown);
    }

    // select the appropriate resampler
    switch (mChannelCount) {
    case 1:
        return resample<1>(out, outFrameCount, provider);
    case 2:
        return resample<2>(out, outFrameCount, provider);
    default:
        LOG_ALWAYS_FATAL("invalid channel count: %d", mChannelCount);
        return 0;
    }
}


template<int CHANNELS>
size_t AudioResamplerSinc::resample(int32_t* out, size_t outFrameCount,
        AudioBufferProvider* provider)
{
    const Constants& c(*mConstants);
    const size_t headOffset = c.halfNumCoefs*CHANNELS;
    int16_t* impulse = mImpulse;
    uint32_t vRL = mVolumeRL;
    size_t inputIndex = mInputIndex;
    uint32_t phaseFraction = mPhaseFraction;
    uint32_t phaseIncrement = mPhaseIncrement;
    size_t outputIndex = 0;
    size_t outputSampleCount = outFrameCount * 2;
    size_t inFrameCount = getInFrameCountRequired(outFrameCount);

    while (outputIndex < outputSampleCount) {
        // buffer is empty, fetch a new one
        while (mBuffer.frameCount == 0) {
            mBuffer.frameCount = inFrameCount;
            provider->getNextBuffer(&mBuffer,
                                    calculateOutputPTS(outputIndex / 2));
            if (mBuffer.raw == NULL) {
                goto resample_exit;
            }
            const uint32_t phaseIndex = phaseFraction >> kNumPhaseBits;
            if (phaseIndex == 1) {
                // read one frame
                read<CHANNELS>(impulse, phaseFraction, mBuffer.i16, inputIndex);
            } else if (phaseIndex == 2) {
                // read 2 frames
                read<CHANNELS>(impulse, phaseFraction, mBuffer.i16, inputIndex);
                inputIndex++;
                if (inputIndex >= mBuffer.frameCount) {
                    inputIndex -= mBuffer.frameCount;
                    provider->releaseBuffer(&mBuffer);
                } else {
                    read<CHANNELS>(impulse, phaseFraction, mBuffer.i16, inputIndex);
                }
            }
        }
        int16_t const * const in = mBuffer.i16;
        const size_t frameCount = mBuffer.frameCount;

        // Always read-in the first samples from the input buffer
        int16_t* head = impulse + headOffset;
        for (size_t i=0 ; i<CHANNELS ; i++) {
            head[i] = in[inputIndex*CHANNELS + i];
        }

        // handle boundary case
        while (CC_LIKELY(outputIndex < outputSampleCount)) {
            filterCoefficient<CHANNELS>(&out[outputIndex], phaseFraction, impulse, vRL);
            outputIndex += 2;

            phaseFraction += phaseIncrement;
            const size_t phaseIndex = phaseFraction >> kNumPhaseBits;
            for (size_t i=0 ; i<phaseIndex ; i++) {
                inputIndex++;
                if (inputIndex >= frameCount) {
                    goto done;  // need a new buffer
                }
                read<CHANNELS>(impulse, phaseFraction, in, inputIndex);
            }
        }
done:
        // if done with buffer, save samples
        if (inputIndex >= frameCount) {
            inputIndex -= frameCount;
            provider->releaseBuffer(&mBuffer);
        }
    }

resample_exit:
    mImpulse = impulse;
    mInputIndex = inputIndex;
    mPhaseFraction = phaseFraction;
    return outputIndex / CHANNELS;
}

template<int CHANNELS>
/***
* read()
*
* This function reads only one frame from input buffer and writes it in
* state buffer
*
**/
void AudioResamplerSinc::read(
        int16_t*& impulse, uint32_t& phaseFraction,
        const int16_t* in, size_t inputIndex)
{
    impulse += CHANNELS;
    phaseFraction -= 1LU<<kNumPhaseBits;

    const Constants& c(*mConstants);
    if (CC_UNLIKELY(impulse >= mRingFull)) {
        const size_t stateSize = (c.halfNumCoefs*2)*CHANNELS;
        memcpy(mState, mState+stateSize, sizeof(int16_t)*stateSize);
        impulse -= stateSize;
    }

    int16_t* head = impulse + c.halfNumCoefs*CHANNELS;
    for (size_t i=0 ; i<CHANNELS ; i++) {
        head[i] = in[inputIndex*CHANNELS + i];
    }
}

template<int CHANNELS>
void AudioResamplerSinc::filterCoefficient(int32_t* out, uint32_t phase,
         const int16_t *samples, uint32_t vRL)
{
    // NOTE: be very careful when modifying the code here. register
    // pressure is very high and a small change might cause the compiler
    // to generate far less efficient code.
    // Always sanity check the result with objdump or test-resample.

    // compute the index of the coefficient on the positive side and
    // negative side
    const Constants& c(*mConstants);
    const int32_t ONE = c.cMask | c.pMask;
    uint32_t indexP = ( phase & c.cMask) >> c.cShift;
    uint32_t lerpP  = ( phase & c.pMask) >> c.pShift;
    uint32_t indexN = ((ONE-phase) & c.cMask) >> c.cShift;
    uint32_t lerpN  = ((ONE-phase) & c.pMask) >> c.pShift;

    const size_t offset = c.halfNumCoefs;
    indexP *= offset;
    indexN *= offset;

    int32_t const* coefsP = mFirCoefs + indexP;
    int32_t const* coefsN = mFirCoefs + indexN;
    int16_t const* sP = samples;
    int16_t const* sN = samples + CHANNELS;

    size_t count = offset;

#ifndef USE_NEON
    int32_t l = 0;
    int32_t r = 0;
    for (size_t i=0 ; i<count ; i++) {
        interpolate<CHANNELS>(l, r, coefsP++, offset, lerpP, sP);
        sP -= CHANNELS;
        interpolate<CHANNELS>(l, r, coefsN++, offset, lerpN, sN);
        sN += CHANNELS;
    }
    out[0] += 2 * mulRL(1, l, vRL);
    out[1] += 2 * mulRL(0, r, vRL);
#else
    UNUSED(vRL);
    if (CHANNELS == 1) {
        int32_t const* coefsP1 = coefsP + offset;
        int32_t const* coefsN1 = coefsN + offset;
        sP -= CHANNELS*3;

        int32x4_t sum;
        int32x2_t lerpPN;
        lerpPN = vdup_n_s32(0);
        lerpPN = vld1_lane_s32((int32_t *)&lerpP, lerpPN, 0);
        lerpPN = vld1_lane_s32((int32_t *)&lerpN, lerpPN, 1);
        lerpPN = vshl_n_s32(lerpPN, 16);
        sum = vdupq_n_s32(0);

        int16x4_t sampleP, sampleN;
        int32x4_t samplePExt, sampleNExt;
        int32x4_t coefsPV0, coefsPV1, coefsNV0, coefsNV1;

        coefsP = (const int32_t*)__builtin_assume_aligned(coefsP, 16);
        coefsN = (const int32_t*)__builtin_assume_aligned(coefsN, 16);
        coefsP1 = (const int32_t*)__builtin_assume_aligned(coefsP1, 16);
        coefsN1 = (const int32_t*)__builtin_assume_aligned(coefsN1, 16);
        for (; count > 0; count -= 4) {
            sampleP = vld1_s16(sP);
            sampleN = vld1_s16(sN);
            coefsPV0 = vld1q_s32(coefsP);
            coefsNV0 = vld1q_s32(coefsN);
            coefsPV1 = vld1q_s32(coefsP1);
            coefsNV1 = vld1q_s32(coefsN1);
            sP -= 4;
            sN += 4;
            coefsP += 4;
            coefsN += 4;
            coefsP1 += 4;
            coefsN1 += 4;

            sampleP = vrev64_s16(sampleP);

            // interpolate (step1)
            coefsPV1 = vsubq_s32(coefsPV1, coefsPV0);
            coefsNV1 = vsubq_s32(coefsNV1, coefsNV0);
            samplePExt = vshll_n_s16(sampleP, 15);
            // interpolate (step2)
            coefsPV1 = vqrdmulhq_lane_s32(coefsPV1, lerpPN, 0);
            coefsNV1 = vqrdmulhq_lane_s32(coefsNV1, lerpPN, 1);
            sampleNExt = vshll_n_s16(sampleN, 15);
            // interpolate (step3)
            coefsPV0 = vaddq_s32(coefsPV0, coefsPV1);
            coefsNV0 = vaddq_s32(coefsNV0, coefsNV1);

            samplePExt = vqrdmulhq_s32(samplePExt, coefsPV0);
            sampleNExt = vqrdmulhq_s32(sampleNExt, coefsNV0);
            sum = vaddq_s32(sum, samplePExt);
            sum = vaddq_s32(sum, sampleNExt);
        }
        int32x2_t volumesV, outV;
        volumesV = vld1_s32(mVolumeSIMD);
        outV = vld1_s32(out);

        //add all 4 partial sums
        int32x2_t sumLow, sumHigh;
        sumLow = vget_low_s32(sum);
        sumHigh = vget_high_s32(sum);
        sumLow = vpadd_s32(sumLow, sumHigh);
        sumLow = vpadd_s32(sumLow, sumLow);

        sumLow = vqrdmulh_s32(sumLow, volumesV);
        outV = vadd_s32(outV, sumLow);
        vst1_s32(out, outV);
    } else if (CHANNELS == 2) {
        int32_t const* coefsP1 = coefsP + offset;
        int32_t const* coefsN1 = coefsN + offset;
        sP -= CHANNELS*3;

        int32x4_t sum0, sum1;
        int32x2_t lerpPN;

        lerpPN = vdup_n_s32(0);
        lerpPN = vld1_lane_s32((int32_t *)&lerpP, lerpPN, 0);
        lerpPN = vld1_lane_s32((int32_t *)&lerpN, lerpPN, 1);
        lerpPN = vshl_n_s32(lerpPN, 16);
        sum0 = vdupq_n_s32(0);
        sum1 = vdupq_n_s32(0);

        int16x4x2_t sampleP, sampleN;
        int32x4x2_t samplePExt, sampleNExt;
        int32x4_t coefsPV0, coefsPV1, coefsNV0, coefsNV1;

        coefsP = (const int32_t*)__builtin_assume_aligned(coefsP, 16);
        coefsN = (const int32_t*)__builtin_assume_aligned(coefsN, 16);
        coefsP1 = (const int32_t*)__builtin_assume_aligned(coefsP1, 16);
        coefsN1 = (const int32_t*)__builtin_assume_aligned(coefsN1, 16);
        for (; count > 0; count -= 4) {
            sampleP = vld2_s16(sP);
            sampleN = vld2_s16(sN);
            coefsPV0 = vld1q_s32(coefsP);
            coefsNV0 = vld1q_s32(coefsN);
            coefsPV1 = vld1q_s32(coefsP1);
            coefsNV1 = vld1q_s32(coefsN1);
            sP -= 8;
            sN += 8;
            coefsP += 4;
            coefsN += 4;
            coefsP1 += 4;
            coefsN1 += 4;

            sampleP.val[0] = vrev64_s16(sampleP.val[0]);
            sampleP.val[1] = vrev64_s16(sampleP.val[1]);

            // interpolate (step1)
            coefsPV1 = vsubq_s32(coefsPV1, coefsPV0);
            coefsNV1 = vsubq_s32(coefsNV1, coefsNV0);
            samplePExt.val[0] = vshll_n_s16(sampleP.val[0], 15);
            samplePExt.val[1] = vshll_n_s16(sampleP.val[1], 15);
            // interpolate (step2)
            coefsPV1 = vqrdmulhq_lane_s32(coefsPV1, lerpPN, 0);
            coefsNV1 = vqrdmulhq_lane_s32(coefsNV1, lerpPN, 1);
            sampleNExt.val[0] = vshll_n_s16(sampleN.val[0], 15);
            sampleNExt.val[1] = vshll_n_s16(sampleN.val[1], 15);
            // interpolate (step3)
            coefsPV0 = vaddq_s32(coefsPV0, coefsPV1);
            coefsNV0 = vaddq_s32(coefsNV0, coefsNV1);

            samplePExt.val[0] = vqrdmulhq_s32(samplePExt.val[0], coefsPV0);
            samplePExt.val[1] = vqrdmulhq_s32(samplePExt.val[1], coefsPV0);
            sampleNExt.val[0] = vqrdmulhq_s32(sampleNExt.val[0], coefsNV0);
            sampleNExt.val[1] = vqrdmulhq_s32(sampleNExt.val[1], coefsNV0);
            sum0 = vaddq_s32(sum0, samplePExt.val[0]);
            sum1 = vaddq_s32(sum1, samplePExt.val[1]);
            sum0 = vaddq_s32(sum0, sampleNExt.val[0]);
            sum1 = vaddq_s32(sum1, sampleNExt.val[1]);
        }
        int32x2_t volumesV, outV;
        volumesV = vld1_s32(mVolumeSIMD);
        outV = vld1_s32(out);

        //add all 4 partial sums
        int32x2_t sumLow0, sumHigh0, sumLow1, sumHigh1;
        sumLow0 = vget_low_s32(sum0);
        sumHigh0 = vget_high_s32(sum0);
        sumLow1 = vget_low_s32(sum1);
        sumHigh1 = vget_high_s32(sum1);
        sumLow0 = vpadd_s32(sumLow0, sumHigh0);
        sumLow0 = vpadd_s32(sumLow0, sumLow0);
        sumLow1 = vpadd_s32(sumLow1, sumHigh1);
        sumLow1 = vpadd_s32(sumLow1, sumLow1);

        sumLow0 = vtrn_s32(sumLow0, sumLow1).val[0];
        sumLow0 = vqrdmulh_s32(sumLow0, volumesV);
        outV = vadd_s32(outV, sumLow0);
        vst1_s32(out, outV);
    }
#endif
}

template<int CHANNELS>
void AudioResamplerSinc::interpolate(
        int32_t& l, int32_t& r,
        const int32_t* coefs, size_t offset,
        int32_t lerp, const int16_t* samples)
{
    int32_t c0 = coefs[0];
    int32_t c1 = coefs[offset];
    int32_t sinc = mulAdd(lerp, (c1-c0)<<1, c0);
    if (CHANNELS == 2) {
        uint32_t rl = *reinterpret_cast<const uint32_t*>(samples);
        l = mulAddRL(1, rl, sinc, l);
        r = mulAddRL(0, rl, sinc, r);
    } else {
        r = l = mulAdd(samples[0], sinc, l);
    }
}
// ----------------------------------------------------------------------------
}} // namespace cocos2d { namespace experimental {

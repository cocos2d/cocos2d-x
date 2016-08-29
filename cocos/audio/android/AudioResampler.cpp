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

#define LOG_TAG "AudioResampler"
//#define LOG_NDEBUG 0

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <new>
#include "audio/android/cutils/log.h"
#include "audio/android/utils/Utils.h"
//#include <cutils/properties.h>
#include "audio/android/audio_utils/include/audio_utils/primitives.h"
#include "audio/android/AudioResampler.h"
//#include "audio/android/AudioResamplerSinc.h"
#include "audio/android/AudioResamplerCubic.h"


//#include "AudioResamplerDyn.h"

//cjh #ifdef __arm__
//    #define ASM_ARM_RESAMP1 // enable asm optimisation for ResamplerOrder1
//#endif



namespace cocos2d { namespace experimental {

// ----------------------------------------------------------------------------

class AudioResamplerOrder1 : public AudioResampler {
public:
    AudioResamplerOrder1(int inChannelCount, int32_t sampleRate) :
        AudioResampler(inChannelCount, sampleRate, LOW_QUALITY), mX0L(0), mX0R(0) {
    }
    virtual size_t resample(int32_t* out, size_t outFrameCount,
            AudioBufferProvider* provider);
private:
    // number of bits used in interpolation multiply - 15 bits avoids overflow
    static const int kNumInterpBits = 15;

    // bits to shift the phase fraction down to avoid overflow
    static const int kPreInterpShift = kNumPhaseBits - kNumInterpBits;

    void init() {}
    size_t resampleMono16(int32_t* out, size_t outFrameCount,
            AudioBufferProvider* provider);
    size_t resampleStereo16(int32_t* out, size_t outFrameCount,
            AudioBufferProvider* provider);
#ifdef ASM_ARM_RESAMP1  // asm optimisation for ResamplerOrder1
    void AsmMono16Loop(int16_t *in, int32_t* maxOutPt, int32_t maxInIdx,
            size_t &outputIndex, int32_t* out, size_t &inputIndex, int32_t vl, int32_t vr,
            uint32_t &phaseFraction, uint32_t phaseIncrement);
    void AsmStereo16Loop(int16_t *in, int32_t* maxOutPt, int32_t maxInIdx,
            size_t &outputIndex, int32_t* out, size_t &inputIndex, int32_t vl, int32_t vr,
            uint32_t &phaseFraction, uint32_t phaseIncrement);
#endif  // ASM_ARM_RESAMP1

    static inline int32_t Interp(int32_t x0, int32_t x1, uint32_t f) {
        return x0 + (((x1 - x0) * (int32_t)(f >> kPreInterpShift)) >> kNumInterpBits);
    }
    static inline void Advance(size_t* index, uint32_t* frac, uint32_t inc) {
        *frac += inc;
        *index += (size_t)(*frac >> kNumPhaseBits);
        *frac &= kPhaseMask;
    }
    int mX0L;
    int mX0R;
};

/*static*/
const double AudioResampler::kPhaseMultiplier = 1L << AudioResampler::kNumPhaseBits;

bool AudioResampler::qualityIsSupported(src_quality quality)
{
    switch (quality) {
    case DEFAULT_QUALITY:
    case LOW_QUALITY:
    case MED_QUALITY:
    case HIGH_QUALITY:
    case VERY_HIGH_QUALITY:
        return true;
    default:
        return false;
    }
}

// ----------------------------------------------------------------------------

static pthread_once_t once_control = PTHREAD_ONCE_INIT;
static AudioResampler::src_quality defaultQuality = AudioResampler::DEFAULT_QUALITY;

void AudioResampler::init_routine()
{
    int resamplerQuality = getSystemProperty("af.resampler.quality");
    if (resamplerQuality > 0) {
        defaultQuality = (src_quality) resamplerQuality;
        ALOGD("forcing AudioResampler quality to %d", defaultQuality);
        if (defaultQuality < DEFAULT_QUALITY || defaultQuality > VERY_HIGH_QUALITY) {
            defaultQuality = DEFAULT_QUALITY;
        }
    }
}

uint32_t AudioResampler::qualityMHz(src_quality quality)
{
    switch (quality) {
    default:
    case DEFAULT_QUALITY:
    case LOW_QUALITY:
        return 3;
    case MED_QUALITY:
        return 6;
    case HIGH_QUALITY:
        return 20;
    case VERY_HIGH_QUALITY:
        return 34;
//    case DYN_LOW_QUALITY:
//        return 4;
//    case DYN_MED_QUALITY:
//        return 6;
//    case DYN_HIGH_QUALITY:
//        return 12;
    }
}

static const uint32_t maxMHz = 130; // an arbitrary number that permits 3 VHQ, should be tunable
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static uint32_t currentMHz = 0;

AudioResampler* AudioResampler::create(audio_format_t format, int inChannelCount,
        int32_t sampleRate, src_quality quality) {

    bool atFinalQuality;
    if (quality == DEFAULT_QUALITY) {
        // read the resampler default quality property the first time it is needed
        int ok = pthread_once(&once_control, init_routine);
        if (ok != 0) {
            ALOGE("%s pthread_once failed: %d", __func__, ok);
        }
        quality = defaultQuality;
        atFinalQuality = false;
    } else {
        atFinalQuality = true;
    }

    /* if the caller requests DEFAULT_QUALITY and af.resampler.property
     * has not been set, the target resampler quality is set to DYN_MED_QUALITY,
     * and allowed to "throttle" down to DYN_LOW_QUALITY if necessary
     * due to estimated CPU load of having too many active resamplers
     * (the code below the if).
     */
    if (quality == DEFAULT_QUALITY) {
//cjh        quality = DYN_MED_QUALITY;
    }

    // naive implementation of CPU load throttling doesn't account for whether resampler is active
    pthread_mutex_lock(&mutex);
    for (;;) {
        uint32_t deltaMHz = qualityMHz(quality);
        uint32_t newMHz = currentMHz + deltaMHz;
        if ((qualityIsSupported(quality) && newMHz <= maxMHz) || atFinalQuality) {
            ALOGV("resampler load %u -> %u MHz due to delta +%u MHz from quality %d",
                    currentMHz, newMHz, deltaMHz, quality);
            currentMHz = newMHz;
            break;
        }
        // not enough CPU available for proposed quality level, so try next lowest level
        switch (quality) {
        default:
        case LOW_QUALITY:
            atFinalQuality = true;
            break;
        case MED_QUALITY:
            quality = LOW_QUALITY;
            break;
        case HIGH_QUALITY:
            quality = MED_QUALITY;
            break;
        case VERY_HIGH_QUALITY:
            quality = HIGH_QUALITY;
            break;
//        case DYN_LOW_QUALITY:
//            atFinalQuality = true;
//            break;
//        case DYN_MED_QUALITY:
//            quality = DYN_LOW_QUALITY;
//            break;
//        case DYN_HIGH_QUALITY:
//            quality = DYN_MED_QUALITY;
//            break;
        }
    }
    pthread_mutex_unlock(&mutex);

    AudioResampler* resampler;

    switch (quality) {
    default:
    case LOW_QUALITY:
        ALOGV("Create linear Resampler");
        LOG_ALWAYS_FATAL_IF(format != AUDIO_FORMAT_PCM_16_BIT, "invalid pcm format");
        resampler = new (std::nothrow) AudioResamplerOrder1(inChannelCount, sampleRate);
        break;
    case MED_QUALITY:
        ALOGV("Create cubic Resampler");
        LOG_ALWAYS_FATAL_IF(format != AUDIO_FORMAT_PCM_16_BIT, "invalid pcm format");
        resampler = new (std::nothrow) AudioResamplerCubic(inChannelCount, sampleRate);
        break;
    case HIGH_QUALITY:
        ALOGV("Create HIGH_QUALITY sinc Resampler");
        LOG_ALWAYS_FATAL_IF(format != AUDIO_FORMAT_PCM_16_BIT, "invalid pcm format");
        ALOG_ASSERT(false, "HIGH_QUALITY isn't supported");
        // Cocos2d-x only uses MED_QUALITY, so we could remove Sinc relative files
//        resampler = new (std::nothrow) AudioResamplerSinc(inChannelCount, sampleRate);
        break;
    case VERY_HIGH_QUALITY:
        ALOGV("Create VERY_HIGH_QUALITY sinc Resampler = %d", quality);
        LOG_ALWAYS_FATAL_IF(format != AUDIO_FORMAT_PCM_16_BIT, "invalid pcm format");
        // Cocos2d-x only uses MED_QUALITY, so we could remove Sinc relative files
//        resampler = new (std::nothrow) AudioResamplerSinc(inChannelCount, sampleRate, quality);
        ALOG_ASSERT(false, "VERY_HIGH_QUALITY isn't supported");
        break;
    }

    // initialize resampler
    resampler->init();
    return resampler;
}

AudioResampler::AudioResampler(int inChannelCount,
        int32_t sampleRate, src_quality quality) :
        mChannelCount(inChannelCount),
        mSampleRate(sampleRate), mInSampleRate(sampleRate), mInputIndex(0),
        mPhaseFraction(0), mLocalTimeFreq(0),
        mPTS(AudioBufferProvider::kInvalidPTS), mQuality(quality) {

    const int maxChannels = 2;//cjh quality < DYN_LOW_QUALITY ? 2 : 8;
    if (inChannelCount < 1
            || inChannelCount > maxChannels) {
        LOG_ALWAYS_FATAL("Unsupported sample format %d quality %d channels",
                quality, inChannelCount);
    }
    if (sampleRate <= 0) {
        LOG_ALWAYS_FATAL("Unsupported sample rate %d Hz", sampleRate);
    }

    // initialize common members
    mVolume[0] = mVolume[1] = 0;
    mBuffer.frameCount = 0;
}

AudioResampler::~AudioResampler() {
    pthread_mutex_lock(&mutex);
    src_quality quality = getQuality();
    uint32_t deltaMHz = qualityMHz(quality);
    int32_t newMHz = currentMHz - deltaMHz;
    ALOGV("resampler load %u -> %d MHz due to delta -%u MHz from quality %d",
            currentMHz, newMHz, deltaMHz, quality);
    LOG_ALWAYS_FATAL_IF(newMHz < 0, "negative resampler load %d MHz", newMHz);
    currentMHz = newMHz;
    pthread_mutex_unlock(&mutex);
}

void AudioResampler::setSampleRate(int32_t inSampleRate) {
    mInSampleRate = inSampleRate;
    mPhaseIncrement = (uint32_t)((kPhaseMultiplier * inSampleRate) / mSampleRate);
}

void AudioResampler::setVolume(float left, float right) {
    // TODO: Implement anti-zipper filter
    // convert to U4.12 for internal integer use (round down)
    // integer volume values are clamped to 0 to UNITY_GAIN.
    mVolume[0] = u4_12_from_float(clampFloatVol(left));
    mVolume[1] = u4_12_from_float(clampFloatVol(right));
}

void AudioResampler::setLocalTimeFreq(uint64_t freq) {
    mLocalTimeFreq = freq;
}

void AudioResampler::setPTS(int64_t pts) {
    mPTS = pts;
}

int64_t AudioResampler::calculateOutputPTS(int outputFrameIndex) {

    if (mPTS == AudioBufferProvider::kInvalidPTS) {
        return AudioBufferProvider::kInvalidPTS;
    } else {
        return mPTS + ((outputFrameIndex * mLocalTimeFreq) / mSampleRate);
    }
}

void AudioResampler::reset() {
    mInputIndex = 0;
    mPhaseFraction = 0;
    mBuffer.frameCount = 0;
}

// ----------------------------------------------------------------------------

size_t AudioResamplerOrder1::resample(int32_t* out, size_t outFrameCount,
        AudioBufferProvider* provider) {

    // should never happen, but we overflow if it does
    // ALOG_ASSERT(outFrameCount < 32767);

    // select the appropriate resampler
    switch (mChannelCount) {
    case 1:
        return resampleMono16(out, outFrameCount, provider);
    case 2:
        return resampleStereo16(out, outFrameCount, provider);
    default:
        LOG_ALWAYS_FATAL("invalid channel count: %d", mChannelCount);
        return 0;
    }
}

size_t AudioResamplerOrder1::resampleStereo16(int32_t* out, size_t outFrameCount,
        AudioBufferProvider* provider) {

    int32_t vl = mVolume[0];
    int32_t vr = mVolume[1];

    size_t inputIndex = mInputIndex;
    uint32_t phaseFraction = mPhaseFraction;
    uint32_t phaseIncrement = mPhaseIncrement;
    size_t outputIndex = 0;
    size_t outputSampleCount = outFrameCount * 2;
    size_t inFrameCount = getInFrameCountRequired(outFrameCount);

    // ALOGE("starting resample %d frames, inputIndex=%d, phaseFraction=%d, phaseIncrement=%d",
    //      outFrameCount, inputIndex, phaseFraction, phaseIncrement);

    while (outputIndex < outputSampleCount) {

        // buffer is empty, fetch a new one
        while (mBuffer.frameCount == 0) {
            mBuffer.frameCount = inFrameCount;
            provider->getNextBuffer(&mBuffer,
                                    calculateOutputPTS(outputIndex / 2));
            if (mBuffer.raw == NULL) {
                goto resampleStereo16_exit;
            }

            // ALOGE("New buffer fetched: %d frames", mBuffer.frameCount);
            if (mBuffer.frameCount > inputIndex) break;

            inputIndex -= mBuffer.frameCount;
            mX0L = mBuffer.i16[mBuffer.frameCount*2-2];
            mX0R = mBuffer.i16[mBuffer.frameCount*2-1];
            provider->releaseBuffer(&mBuffer);
            // mBuffer.frameCount == 0 now so we reload a new buffer
        }

        int16_t *in = mBuffer.i16;

        // handle boundary case
        while (inputIndex == 0) {
            // ALOGE("boundary case");
            out[outputIndex++] += vl * Interp(mX0L, in[0], phaseFraction);
            out[outputIndex++] += vr * Interp(mX0R, in[1], phaseFraction);
            Advance(&inputIndex, &phaseFraction, phaseIncrement);
            if (outputIndex == outputSampleCount) {
                break;
            }
        }

        // process input samples
        // ALOGE("general case");

#ifdef ASM_ARM_RESAMP1  // asm optimisation for ResamplerOrder1
        if (inputIndex + 2 < mBuffer.frameCount) {
            int32_t* maxOutPt;
            int32_t maxInIdx;

            maxOutPt = out + (outputSampleCount - 2);   // 2 because 2 frames per loop
            maxInIdx = mBuffer.frameCount - 2;
            AsmStereo16Loop(in, maxOutPt, maxInIdx, outputIndex, out, inputIndex, vl, vr,
                    phaseFraction, phaseIncrement);
        }
#endif  // ASM_ARM_RESAMP1

        while (outputIndex < outputSampleCount && inputIndex < mBuffer.frameCount) {
            out[outputIndex++] += vl * Interp(in[inputIndex*2-2],
                    in[inputIndex*2], phaseFraction);
            out[outputIndex++] += vr * Interp(in[inputIndex*2-1],
                    in[inputIndex*2+1], phaseFraction);
            Advance(&inputIndex, &phaseFraction, phaseIncrement);
        }

        // ALOGE("loop done - outputIndex=%d, inputIndex=%d", outputIndex, inputIndex);

        // if done with buffer, save samples
        if (inputIndex >= mBuffer.frameCount) {
            inputIndex -= mBuffer.frameCount;

            // ALOGE("buffer done, new input index %d", inputIndex);

            mX0L = mBuffer.i16[mBuffer.frameCount*2-2];
            mX0R = mBuffer.i16[mBuffer.frameCount*2-1];
            provider->releaseBuffer(&mBuffer);

            // verify that the releaseBuffer resets the buffer frameCount
            // ALOG_ASSERT(mBuffer.frameCount == 0);
        }
    }

    // ALOGE("output buffer full - outputIndex=%d, inputIndex=%d", outputIndex, inputIndex);

resampleStereo16_exit:
    // save state
    mInputIndex = inputIndex;
    mPhaseFraction = phaseFraction;
    return outputIndex / 2 /* channels for stereo */;
}

size_t AudioResamplerOrder1::resampleMono16(int32_t* out, size_t outFrameCount,
        AudioBufferProvider* provider) {

    int32_t vl = mVolume[0];
    int32_t vr = mVolume[1];

    size_t inputIndex = mInputIndex;
    uint32_t phaseFraction = mPhaseFraction;
    uint32_t phaseIncrement = mPhaseIncrement;
    size_t outputIndex = 0;
    size_t outputSampleCount = outFrameCount * 2;
    size_t inFrameCount = getInFrameCountRequired(outFrameCount);

    // ALOGE("starting resample %d frames, inputIndex=%d, phaseFraction=%d, phaseIncrement=%d",
    //      outFrameCount, inputIndex, phaseFraction, phaseIncrement);
    while (outputIndex < outputSampleCount) {
        // buffer is empty, fetch a new one
        while (mBuffer.frameCount == 0) {
            mBuffer.frameCount = inFrameCount;
            provider->getNextBuffer(&mBuffer,
                                    calculateOutputPTS(outputIndex / 2));
            if (mBuffer.raw == NULL) {
                mInputIndex = inputIndex;
                mPhaseFraction = phaseFraction;
                goto resampleMono16_exit;
            }
            // ALOGE("New buffer fetched: %d frames", mBuffer.frameCount);
            if (mBuffer.frameCount >  inputIndex) break;

            inputIndex -= mBuffer.frameCount;
            mX0L = mBuffer.i16[mBuffer.frameCount-1];
            provider->releaseBuffer(&mBuffer);
            // mBuffer.frameCount == 0 now so we reload a new buffer
        }
        int16_t *in = mBuffer.i16;

        // handle boundary case
        while (inputIndex == 0) {
            // ALOGE("boundary case");
            int32_t sample = Interp(mX0L, in[0], phaseFraction);
            out[outputIndex++] += vl * sample;
            out[outputIndex++] += vr * sample;
            Advance(&inputIndex, &phaseFraction, phaseIncrement);
            if (outputIndex == outputSampleCount) {
                break;
            }
        }

        // process input samples
        // ALOGE("general case");

#ifdef ASM_ARM_RESAMP1  // asm optimisation for ResamplerOrder1
        if (inputIndex + 2 < mBuffer.frameCount) {
            int32_t* maxOutPt;
            int32_t maxInIdx;

            maxOutPt = out + (outputSampleCount - 2);
            maxInIdx = (int32_t)mBuffer.frameCount - 2;
                AsmMono16Loop(in, maxOutPt, maxInIdx, outputIndex, out, inputIndex, vl, vr,
                        phaseFraction, phaseIncrement);
        }
#endif  // ASM_ARM_RESAMP1

        while (outputIndex < outputSampleCount && inputIndex < mBuffer.frameCount) {
            int32_t sample = Interp(in[inputIndex-1], in[inputIndex],
                    phaseFraction);
            out[outputIndex++] += vl * sample;
            out[outputIndex++] += vr * sample;
            Advance(&inputIndex, &phaseFraction, phaseIncrement);
        }


        // ALOGE("loop done - outputIndex=%d, inputIndex=%d", outputIndex, inputIndex);

        // if done with buffer, save samples
        if (inputIndex >= mBuffer.frameCount) {
            inputIndex -= mBuffer.frameCount;

            // ALOGE("buffer done, new input index %d", inputIndex);

            mX0L = mBuffer.i16[mBuffer.frameCount-1];
            provider->releaseBuffer(&mBuffer);

            // verify that the releaseBuffer resets the buffer frameCount
            // ALOG_ASSERT(mBuffer.frameCount == 0);
        }
    }

    // ALOGE("output buffer full - outputIndex=%d, inputIndex=%d", outputIndex, inputIndex);

resampleMono16_exit:
    // save state
    mInputIndex = inputIndex;
    mPhaseFraction = phaseFraction;
    return outputIndex;
}

#ifdef ASM_ARM_RESAMP1  // asm optimisation for ResamplerOrder1

/*******************************************************************
*
*   AsmMono16Loop
*   asm optimized monotonic loop version; one loop is 2 frames
*   Input:
*       in : pointer on input samples
*       maxOutPt : pointer on first not filled
*       maxInIdx : index on first not used
*       outputIndex : pointer on current output index
*       out : pointer on output buffer
*       inputIndex : pointer on current input index
*       vl, vr : left and right gain
*       phaseFraction : pointer on current phase fraction
*       phaseIncrement
*   Output:
*       outputIndex :
*       out : updated buffer
*       inputIndex : index of next to use
*       phaseFraction : phase fraction for next interpolation
*
*******************************************************************/
__attribute__((noinline))
void AudioResamplerOrder1::AsmMono16Loop(int16_t *in, int32_t* maxOutPt, int32_t maxInIdx,
            size_t &outputIndex, int32_t* out, size_t &inputIndex, int32_t vl, int32_t vr,
            uint32_t &phaseFraction, uint32_t phaseIncrement)
{
    (void)maxOutPt; // remove unused parameter warnings
    (void)maxInIdx;
    (void)outputIndex;
    (void)out;
    (void)inputIndex;
    (void)vl;
    (void)vr;
    (void)phaseFraction;
    (void)phaseIncrement;
    (void)in;
#define MO_PARAM5   "36"        // offset of parameter 5 (outputIndex)

    asm(
        "stmfd  sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}\n"
        // get parameters
        "   ldr r6, [sp, #" MO_PARAM5 " + 20]\n"    // &phaseFraction
        "   ldr r6, [r6]\n"                         // phaseFraction
        "   ldr r7, [sp, #" MO_PARAM5 " + 8]\n"     // &inputIndex
        "   ldr r7, [r7]\n"                         // inputIndex
        "   ldr r8, [sp, #" MO_PARAM5 " + 4]\n"     // out
        "   ldr r0, [sp, #" MO_PARAM5 " + 0]\n"     // &outputIndex
        "   ldr r0, [r0]\n"                         // outputIndex
        "   add r8, r8, r0, asl #2\n"               // curOut
        "   ldr r9, [sp, #" MO_PARAM5 " + 24]\n"    // phaseIncrement
        "   ldr r10, [sp, #" MO_PARAM5 " + 12]\n"   // vl
        "   ldr r11, [sp, #" MO_PARAM5 " + 16]\n"   // vr

        // r0 pin, x0, Samp

        // r1 in
        // r2 maxOutPt
        // r3 maxInIdx

        // r4 x1, i1, i3, Out1
        // r5 out0

        // r6 frac
        // r7 inputIndex
        // r8 curOut

        // r9 inc
        // r10 vl
        // r11 vr

        // r12
        // r13 sp
        // r14

        // the following loop works on 2 frames

        "1:\n"
        "   cmp r8, r2\n"                   // curOut - maxCurOut
        "   bcs 2f\n"

#define MO_ONE_FRAME \
    "   add r0, r1, r7, asl #1\n"       /* in + inputIndex */\
    "   ldrsh r4, [r0]\n"               /* in[inputIndex] */\
    "   ldr r5, [r8]\n"                 /* out[outputIndex] */\
    "   ldrsh r0, [r0, #-2]\n"          /* in[inputIndex-1] */\
    "   bic r6, r6, #0xC0000000\n"      /* phaseFraction & ... */\
    "   sub r4, r4, r0\n"               /* in[inputIndex] - in[inputIndex-1] */\
    "   mov r4, r4, lsl #2\n"           /* <<2 */\
    "   smulwt r4, r4, r6\n"            /* (x1-x0)*.. */\
    "   add r6, r6, r9\n"               /* phaseFraction + phaseIncrement */\
    "   add r0, r0, r4\n"               /* x0 - (..) */\
    "   mla r5, r0, r10, r5\n"          /* vl*interp + out[] */\
    "   ldr r4, [r8, #4]\n"             /* out[outputIndex+1] */\
    "   str r5, [r8], #4\n"             /* out[outputIndex++] = ... */\
    "   mla r4, r0, r11, r4\n"          /* vr*interp + out[] */\
    "   add r7, r7, r6, lsr #30\n"      /* inputIndex + phaseFraction>>30 */\
    "   str r4, [r8], #4\n"             /* out[outputIndex++] = ... */

        MO_ONE_FRAME    // frame 1
        MO_ONE_FRAME    // frame 2

        "   cmp r7, r3\n"                   // inputIndex - maxInIdx
        "   bcc 1b\n"
        "2:\n"

        "   bic r6, r6, #0xC0000000\n"             // phaseFraction & ...
        // save modified values
        "   ldr r0, [sp, #" MO_PARAM5 " + 20]\n"    // &phaseFraction
        "   str r6, [r0]\n"                         // phaseFraction
        "   ldr r0, [sp, #" MO_PARAM5 " + 8]\n"     // &inputIndex
        "   str r7, [r0]\n"                         // inputIndex
        "   ldr r0, [sp, #" MO_PARAM5 " + 4]\n"     // out
        "   sub r8, r0\n"                           // curOut - out
        "   asr r8, #2\n"                           // new outputIndex
        "   ldr r0, [sp, #" MO_PARAM5 " + 0]\n"     // &outputIndex
        "   str r8, [r0]\n"                         // save outputIndex

        "   ldmfd   sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}\n"
    );
}

/*******************************************************************
*
*   AsmStereo16Loop
*   asm optimized stereo loop version; one loop is 2 frames
*   Input:
*       in : pointer on input samples
*       maxOutPt : pointer on first not filled
*       maxInIdx : index on first not used
*       outputIndex : pointer on current output index
*       out : pointer on output buffer
*       inputIndex : pointer on current input index
*       vl, vr : left and right gain
*       phaseFraction : pointer on current phase fraction
*       phaseIncrement
*   Output:
*       outputIndex :
*       out : updated buffer
*       inputIndex : index of next to use
*       phaseFraction : phase fraction for next interpolation
*
*******************************************************************/
__attribute__((noinline))
void AudioResamplerOrder1::AsmStereo16Loop(int16_t *in, int32_t* maxOutPt, int32_t maxInIdx,
            size_t &outputIndex, int32_t* out, size_t &inputIndex, int32_t vl, int32_t vr,
            uint32_t &phaseFraction, uint32_t phaseIncrement)
{
    (void)maxOutPt; // remove unused parameter warnings
    (void)maxInIdx;
    (void)outputIndex;
    (void)out;
    (void)inputIndex;
    (void)vl;
    (void)vr;
    (void)phaseFraction;
    (void)phaseIncrement;
    (void)in;
#define ST_PARAM5    "40"     // offset of parameter 5 (outputIndex)
    asm(
        "stmfd  sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}\n"
        // get parameters
        "   ldr r6, [sp, #" ST_PARAM5 " + 20]\n"    // &phaseFraction
        "   ldr r6, [r6]\n"                         // phaseFraction
        "   ldr r7, [sp, #" ST_PARAM5 " + 8]\n"     // &inputIndex
        "   ldr r7, [r7]\n"                         // inputIndex
        "   ldr r8, [sp, #" ST_PARAM5 " + 4]\n"     // out
        "   ldr r0, [sp, #" ST_PARAM5 " + 0]\n"     // &outputIndex
        "   ldr r0, [r0]\n"                         // outputIndex
        "   add r8, r8, r0, asl #2\n"               // curOut
        "   ldr r9, [sp, #" ST_PARAM5 " + 24]\n"    // phaseIncrement
        "   ldr r10, [sp, #" ST_PARAM5 " + 12]\n"   // vl
        "   ldr r11, [sp, #" ST_PARAM5 " + 16]\n"   // vr

        // r0 pin, x0, Samp

        // r1 in
        // r2 maxOutPt
        // r3 maxInIdx

        // r4 x1, i1, i3, out1
        // r5 out0

        // r6 frac
        // r7 inputIndex
        // r8 curOut

        // r9 inc
        // r10 vl
        // r11 vr

        // r12 temporary
        // r13 sp
        // r14

        "3:\n"
        "   cmp r8, r2\n"                   // curOut - maxCurOut
        "   bcs 4f\n"

#define ST_ONE_FRAME \
    "   bic r6, r6, #0xC0000000\n"      /* phaseFraction & ... */\
\
    "   add r0, r1, r7, asl #2\n"       /* in + 2*inputIndex */\
\
    "   ldrsh r4, [r0]\n"               /* in[2*inputIndex] */\
    "   ldr r5, [r8]\n"                 /* out[outputIndex] */\
    "   ldrsh r12, [r0, #-4]\n"         /* in[2*inputIndex-2] */\
    "   sub r4, r4, r12\n"              /* in[2*InputIndex] - in[2*InputIndex-2] */\
    "   mov r4, r4, lsl #2\n"           /* <<2 */\
    "   smulwt r4, r4, r6\n"            /* (x1-x0)*.. */\
    "   add r12, r12, r4\n"             /* x0 - (..) */\
    "   mla r5, r12, r10, r5\n"         /* vl*interp + out[] */\
    "   ldr r4, [r8, #4]\n"             /* out[outputIndex+1] */\
    "   str r5, [r8], #4\n"             /* out[outputIndex++] = ... */\
\
    "   ldrsh r12, [r0, #+2]\n"         /* in[2*inputIndex+1] */\
    "   ldrsh r0, [r0, #-2]\n"          /* in[2*inputIndex-1] */\
    "   sub r12, r12, r0\n"             /* in[2*InputIndex] - in[2*InputIndex-2] */\
    "   mov r12, r12, lsl #2\n"         /* <<2 */\
    "   smulwt r12, r12, r6\n"          /* (x1-x0)*.. */\
    "   add r12, r0, r12\n"             /* x0 - (..) */\
    "   mla r4, r12, r11, r4\n"         /* vr*interp + out[] */\
    "   str r4, [r8], #4\n"             /* out[outputIndex++] = ... */\
\
    "   add r6, r6, r9\n"               /* phaseFraction + phaseIncrement */\
    "   add r7, r7, r6, lsr #30\n"      /* inputIndex + phaseFraction>>30 */

    ST_ONE_FRAME    // frame 1
    ST_ONE_FRAME    // frame 1

        "   cmp r7, r3\n"                       // inputIndex - maxInIdx
        "   bcc 3b\n"
        "4:\n"

        "   bic r6, r6, #0xC0000000\n"              // phaseFraction & ...
        // save modified values
        "   ldr r0, [sp, #" ST_PARAM5 " + 20]\n"    // &phaseFraction
        "   str r6, [r0]\n"                         // phaseFraction
        "   ldr r0, [sp, #" ST_PARAM5 " + 8]\n"     // &inputIndex
        "   str r7, [r0]\n"                         // inputIndex
        "   ldr r0, [sp, #" ST_PARAM5 " + 4]\n"     // out
        "   sub r8, r0\n"                           // curOut - out
        "   asr r8, #2\n"                           // new outputIndex
        "   ldr r0, [sp, #" ST_PARAM5 " + 0]\n"     // &outputIndex
        "   str r8, [r0]\n"                         // save outputIndex

        "   ldmfd   sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, pc}\n"
    );
}

#endif  // ASM_ARM_RESAMP1


// ----------------------------------------------------------------------------

}} // namespace cocos2d { namespace experimental {

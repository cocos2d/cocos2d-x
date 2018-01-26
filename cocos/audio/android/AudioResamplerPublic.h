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

#pragma once

#include <stdint.h>
#include <math.h>

namespace cocos2d { namespace experimental {

// AUDIO_RESAMPLER_DOWN_RATIO_MAX is the maximum ratio between the original
// audio sample rate and the target rate when downsampling,
// as permitted in the audio framework, e.g. AudioTrack and AudioFlinger.
// In practice, it is not recommended to downsample more than 6:1
// for best audio quality, even though the audio framework permits a larger
// downsampling ratio.
// TODO: replace with an API
#define AUDIO_RESAMPLER_DOWN_RATIO_MAX 256

// AUDIO_RESAMPLER_UP_RATIO_MAX is the maximum suggested ratio between the original
// audio sample rate and the target rate when upsampling.  It is loosely enforced by
// the system. One issue with large upsampling ratios is the approximation by
// an int32_t of the phase increments, making the resulting sample rate inexact.
#define AUDIO_RESAMPLER_UP_RATIO_MAX 65536

// AUDIO_TIMESTRETCH_SPEED_MIN and AUDIO_TIMESTRETCH_SPEED_MAX define the min and max time stretch
// speeds supported by the system. These are enforced by the system and values outside this range
// will result in a runtime error.
// Depending on the AudioPlaybackRate::mStretchMode, the effective limits might be narrower than
// the ones specified here
// AUDIO_TIMESTRETCH_SPEED_MIN_DELTA is the minimum absolute speed difference that might trigger a
// parameter update
#define AUDIO_TIMESTRETCH_SPEED_MIN    0.01f
#define AUDIO_TIMESTRETCH_SPEED_MAX    20.0f
#define AUDIO_TIMESTRETCH_SPEED_NORMAL 1.0f
#define AUDIO_TIMESTRETCH_SPEED_MIN_DELTA 0.0001f

// AUDIO_TIMESTRETCH_PITCH_MIN and AUDIO_TIMESTRETCH_PITCH_MAX define the min and max time stretch
// pitch shifting supported by the system. These are not enforced by the system and values
// outside this range might result in a pitch different than the one requested.
// Depending on the AudioPlaybackRate::mStretchMode, the effective limits might be narrower than
// the ones specified here.
// AUDIO_TIMESTRETCH_PITCH_MIN_DELTA is the minimum absolute pitch difference that might trigger a
// parameter update
#define AUDIO_TIMESTRETCH_PITCH_MIN    0.25f
#define AUDIO_TIMESTRETCH_PITCH_MAX    4.0f
#define AUDIO_TIMESTRETCH_PITCH_NORMAL 1.0f
#define AUDIO_TIMESTRETCH_PITCH_MIN_DELTA 0.0001f


//Determines the current algorithm used for stretching
enum AudioTimestretchStretchMode : int32_t {
    AUDIO_TIMESTRETCH_STRETCH_DEFAULT            = 0,
    AUDIO_TIMESTRETCH_STRETCH_SPEECH             = 1,
    //TODO: add more stretch modes/algorithms
};

//Limits for AUDIO_TIMESTRETCH_STRETCH_SPEECH mode
#define TIMESTRETCH_SONIC_SPEED_MIN 0.1f
#define TIMESTRETCH_SONIC_SPEED_MAX 6.0f

//Determines behavior of Timestretch if current algorithm can't perform
//with current parameters.
// FALLBACK_CUT_REPEAT: (internal only) for speed <1.0 will truncate frames
//    for speed > 1.0 will repeat frames
// FALLBACK_MUTE: will set all processed frames to zero
// FALLBACK_FAIL:  will stop program execution and log a fatal error
enum AudioTimestretchFallbackMode : int32_t {
    AUDIO_TIMESTRETCH_FALLBACK_CUT_REPEAT     = -1,
    AUDIO_TIMESTRETCH_FALLBACK_DEFAULT        = 0,
    AUDIO_TIMESTRETCH_FALLBACK_MUTE           = 1,
    AUDIO_TIMESTRETCH_FALLBACK_FAIL           = 2,
};

struct AudioPlaybackRate {
    float mSpeed;
    float mPitch;
    enum AudioTimestretchStretchMode  mStretchMode;
    enum AudioTimestretchFallbackMode mFallbackMode;
};

static const AudioPlaybackRate AUDIO_PLAYBACK_RATE_DEFAULT = {
        AUDIO_TIMESTRETCH_SPEED_NORMAL,
        AUDIO_TIMESTRETCH_PITCH_NORMAL,
        AUDIO_TIMESTRETCH_STRETCH_DEFAULT,
        AUDIO_TIMESTRETCH_FALLBACK_DEFAULT
};

static inline bool isAudioPlaybackRateEqual(const AudioPlaybackRate &pr1,
        const AudioPlaybackRate &pr2) {
    return fabs(pr1.mSpeed - pr2.mSpeed) < AUDIO_TIMESTRETCH_SPEED_MIN_DELTA &&
           fabs(pr1.mPitch - pr2.mPitch) < AUDIO_TIMESTRETCH_PITCH_MIN_DELTA &&
           pr2.mStretchMode == pr2.mStretchMode &&
           pr2.mFallbackMode == pr2.mFallbackMode;
}

static inline bool isAudioPlaybackRateValid(const AudioPlaybackRate &playbackRate) {
    if (playbackRate.mFallbackMode == AUDIO_TIMESTRETCH_FALLBACK_FAIL &&
            (playbackRate.mStretchMode == AUDIO_TIMESTRETCH_STRETCH_SPEECH ||
                    playbackRate.mStretchMode == AUDIO_TIMESTRETCH_STRETCH_DEFAULT)) {
        //test sonic specific constraints
        return playbackRate.mSpeed >= TIMESTRETCH_SONIC_SPEED_MIN &&
                playbackRate.mSpeed <= TIMESTRETCH_SONIC_SPEED_MAX &&
                playbackRate.mPitch >= AUDIO_TIMESTRETCH_PITCH_MIN &&
                playbackRate.mPitch <= AUDIO_TIMESTRETCH_PITCH_MAX;
    } else {
        return playbackRate.mSpeed >= AUDIO_TIMESTRETCH_SPEED_MIN &&
                playbackRate.mSpeed <= AUDIO_TIMESTRETCH_SPEED_MAX &&
                playbackRate.mPitch >= AUDIO_TIMESTRETCH_PITCH_MIN &&
                playbackRate.mPitch <= AUDIO_TIMESTRETCH_PITCH_MAX;
    }
}

// TODO: Consider putting these inlines into a class scope

// Returns the source frames needed to resample to destination frames.  This is not a precise
// value and depends on the resampler (and possibly how it handles rounding internally).
// Nevertheless, this should be an upper bound on the requirements of the resampler.
// If srcSampleRate and dstSampleRate are equal, then it returns destination frames, which
// may not be true if the resampler is asynchronous.
static inline size_t sourceFramesNeeded(
        uint32_t srcSampleRate, size_t dstFramesRequired, uint32_t dstSampleRate) {
    // +1 for rounding - always do this even if matched ratio (resampler may use phases not ratio)
    // +1 for additional sample needed for interpolation
    return srcSampleRate == dstSampleRate ? dstFramesRequired :
            size_t((uint64_t)dstFramesRequired * srcSampleRate / dstSampleRate + 1 + 1);
}

// An upper bound for the number of destination frames possible from srcFrames
// after sample rate conversion.  This may be used for buffer sizing.
static inline size_t destinationFramesPossible(size_t srcFrames, uint32_t srcSampleRate,
        uint32_t dstSampleRate) {
    if (srcSampleRate == dstSampleRate) {
        return srcFrames;
    }
    uint64_t dstFrames = (uint64_t)srcFrames * dstSampleRate / srcSampleRate;
    return dstFrames > 2 ? dstFrames - 2 : 0;
}

static inline size_t sourceFramesNeededWithTimestretch(
        uint32_t srcSampleRate, size_t dstFramesRequired, uint32_t dstSampleRate,
        float speed) {
    // required is the number of input frames the resampler needs
    size_t required = sourceFramesNeeded(srcSampleRate, dstFramesRequired, dstSampleRate);
    // to deliver this, the time stretcher requires:
    return required * (double)speed + 1 + 1; // accounting for rounding dependencies
}

// Identifies sample rates that we associate with music
// and thus eligible for better resampling and fast capture.
// This is somewhat less than 44100 to allow for pitch correction
// involving resampling as well as asynchronous resampling.
#define AUDIO_PROCESSING_MUSIC_RATE 40000

static inline bool isMusicRate(uint32_t sampleRate) {
    return sampleRate >= AUDIO_PROCESSING_MUSIC_RATE;
}

}} // namespace cocos2d { namespace experimental {

// ---------------------------------------------------------------------------

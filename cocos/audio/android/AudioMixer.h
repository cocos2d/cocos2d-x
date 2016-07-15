/*
**
** Copyright 2007, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#pragma once

#include <stdint.h>
#include <sys/types.h>
#include <pthread.h>

#include "audio/android/AudioBufferProvider.h"
#include "audio/android/AudioResamplerPublic.h"

#include "audio/android/AudioResampler.h"
#include "audio/android/audio.h"

// FIXME This is actually unity gain, which might not be max in future, expressed in U.12
#define MAX_GAIN_INT AudioMixer::UNITY_GAIN_INT

namespace cocos2d { namespace experimental {

// ----------------------------------------------------------------------------

class AudioMixer
{
public:
    AudioMixer(size_t frameCount, uint32_t sampleRate,
               uint32_t maxNumTracks = MAX_NUM_TRACKS);

    /*virtual*/ ~AudioMixer();  // non-virtual saves a v-table, restore if sub-classed


    // This mixer has a hard-coded upper limit of 32 active track inputs.
    // Adding support for > 32 tracks would require more than simply changing this value.
    static const uint32_t MAX_NUM_TRACKS = 32;
    // maximum number of channels supported by the mixer

    // This mixer has a hard-coded upper limit of 8 channels for output.
    static const uint32_t MAX_NUM_CHANNELS = 8;
    static const uint32_t MAX_NUM_VOLUMES = 2; // stereo volume only
    // maximum number of channels supported for the content
    static const uint32_t MAX_NUM_CHANNELS_TO_DOWNMIX = AUDIO_CHANNEL_COUNT_MAX;

    static const uint16_t UNITY_GAIN_INT = 0x1000;
    static const CONSTEXPR float UNITY_GAIN_FLOAT = 1.0f;

    enum { // names

        // track names (MAX_NUM_TRACKS units)
        TRACK0          = 0x1000,

        // 0x2000 is unused

        // setParameter targets
        TRACK           = 0x3000,
        RESAMPLE        = 0x3001,
        RAMP_VOLUME     = 0x3002, // ramp to new volume
        VOLUME          = 0x3003, // don't ramp
        TIMESTRETCH     = 0x3004,

        // set Parameter names
        // for target TRACK
        CHANNEL_MASK    = 0x4000,
        FORMAT          = 0x4001,
        MAIN_BUFFER     = 0x4002,
        AUX_BUFFER      = 0x4003,
        DOWNMIX_TYPE    = 0X4004,
        MIXER_FORMAT    = 0x4005, // AUDIO_FORMAT_PCM_(FLOAT|16_BIT)
        MIXER_CHANNEL_MASK = 0x4006, // Channel mask for mixer output
        // for target RESAMPLE
        SAMPLE_RATE     = 0x4100, // Configure sample rate conversion on this track name;
                                  // parameter 'value' is the new sample rate in Hz.
                                  // Only creates a sample rate converter the first time that
                                  // the track sample rate is different from the mix sample rate.
                                  // If the new sample rate is the same as the mix sample rate,
                                  // and a sample rate converter already exists,
                                  // then the sample rate converter remains present but is a no-op.
        RESET           = 0x4101, // Reset sample rate converter without changing sample rate.
                                  // This clears out the resampler's input buffer.
        REMOVE          = 0x4102, // Remove the sample rate converter on this track name;
                                  // the track is restored to the mix sample rate.
        // for target RAMP_VOLUME and VOLUME (8 channels max)
        // FIXME use float for these 3 to improve the dynamic range
        VOLUME0         = 0x4200,
        VOLUME1         = 0x4201,
        AUXLEVEL        = 0x4210,
        // for target TIMESTRETCH
        PLAYBACK_RATE   = 0x4300, // Configure timestretch on this track name;
                                  // parameter 'value' is a pointer to the new playback rate.
    };


    // For all APIs with "name": TRACK0 <= name < TRACK0 + MAX_NUM_TRACKS

    // Allocate a track name.  Returns new track name if successful, -1 on failure.
    // The failure could be because of an invalid channelMask or format, or that
    // the track capacity of the mixer is exceeded.
    int         getTrackName(audio_channel_mask_t channelMask,
                             audio_format_t format, int sessionId);

    // Free an allocated track by name
    void        deleteTrackName(int name);

    // Enable or disable an allocated track by name
    void        enable(int name);
    void        disable(int name);

    void        setParameter(int name, int target, int param, void *value);

    void        setBufferProvider(int name, AudioBufferProvider* bufferProvider);
    void        process(int64_t pts);

    uint32_t    trackNames() const { return mTrackNames; }

    size_t      getUnreleasedFrames(int name) const;

    static inline bool isValidPcmTrackFormat(audio_format_t format) {
        switch (format) {
        case AUDIO_FORMAT_PCM_8_BIT:
        case AUDIO_FORMAT_PCM_16_BIT:
        case AUDIO_FORMAT_PCM_24_BIT_PACKED:
        case AUDIO_FORMAT_PCM_32_BIT:
        case AUDIO_FORMAT_PCM_FLOAT:
            return true;
        default:
            return false;
        }
    }

private:

    enum {
        // FIXME this representation permits up to 8 channels
        NEEDS_CHANNEL_COUNT__MASK   = 0x00000007,
    };

    enum {
        NEEDS_CHANNEL_1             = 0x00000000,   // mono
        NEEDS_CHANNEL_2             = 0x00000001,   // stereo

        // sample format is not explicitly specified, and is assumed to be AUDIO_FORMAT_PCM_16_BIT

        NEEDS_MUTE                  = 0x00000100,
        NEEDS_RESAMPLE              = 0x00001000,
        NEEDS_AUX                   = 0x00010000,
    };

    struct state_t;
    struct track_t;

    typedef void (*hook_t)(track_t* t, int32_t* output, size_t numOutFrames, int32_t* temp,
                           int32_t* aux);
    static const int BLOCKSIZE = 16; // 4 cache lines

    struct track_t {
        uint32_t    needs;

        // TODO: Eventually remove legacy integer volume settings
        union {
        int16_t     volume[MAX_NUM_VOLUMES]; // U4.12 fixed point (top bit should be zero)
        int32_t     volumeRL;
        };

        int32_t     prevVolume[MAX_NUM_VOLUMES];

        // 16-byte boundary

        int32_t     volumeInc[MAX_NUM_VOLUMES];
        int32_t     auxInc;
        int32_t     prevAuxLevel;

        // 16-byte boundary

        int16_t     auxLevel;       // 0 <= auxLevel <= MAX_GAIN_INT, but signed for mul performance
        uint16_t    frameCount;

        uint8_t     channelCount;   // 1 or 2, redundant with (needs & NEEDS_CHANNEL_COUNT__MASK)
        uint8_t     unused_padding; // formerly format, was always 16
        uint16_t    enabled;        // actually bool
        audio_channel_mask_t channelMask;

        // actual buffer provider used by the track hooks, see DownmixerBufferProvider below
        //  for how the Track buffer provider is wrapped by another one when dowmixing is required
        AudioBufferProvider*                bufferProvider;

        // 16-byte boundary

        mutable AudioBufferProvider::Buffer buffer; // 8 bytes

        hook_t      hook;
        const void* in;             // current location in buffer

        // 16-byte boundary

        AudioResampler*     resampler;
        uint32_t            sampleRate;
        int32_t*           mainBuffer;
        int32_t*           auxBuffer;

        // 16-byte boundary

        /* Buffer providers are constructed to translate the track input data as needed.
         *
         * TODO: perhaps make a single PlaybackConverterProvider class to move
         * all pre-mixer track buffer conversions outside the AudioMixer class.
         *
         * 1) mInputBufferProvider: The AudioTrack buffer provider.
         * 2) mReformatBufferProvider: If not NULL, performs the audio reformat to
         *    match either mMixerInFormat or mDownmixRequiresFormat, if the downmixer
         *    requires reformat. For example, it may convert floating point input to
         *    PCM_16_bit if that's required by the downmixer.
         * 3) downmixerBufferProvider: If not NULL, performs the channel remixing to match
         *    the number of channels required by the mixer sink.
         * 4) mPostDownmixReformatBufferProvider: If not NULL, performs reformatting from
         *    the downmixer requirements to the mixer engine input requirements.
         * 5) mTimestretchBufferProvider: Adds timestretching for playback rate
         */
        AudioBufferProvider*     mInputBufferProvider;    // externally provided buffer provider.
//cjh        PassthruBufferProvider*  mReformatBufferProvider; // provider wrapper for reformatting.
//        PassthruBufferProvider*  downmixerBufferProvider; // wrapper for channel conversion.
//        PassthruBufferProvider*  mPostDownmixReformatBufferProvider;
//        PassthruBufferProvider*  mTimestretchBufferProvider;

        int32_t     sessionId;

        audio_format_t mMixerFormat;     // output mix format: AUDIO_FORMAT_PCM_(FLOAT|16_BIT)
        audio_format_t mFormat;          // input track format
        audio_format_t mMixerInFormat;   // mix internal format AUDIO_FORMAT_PCM_(FLOAT|16_BIT)
                                         // each track must be converted to this format.
        audio_format_t mDownmixRequiresFormat;  // required downmixer format
                                                // AUDIO_FORMAT_PCM_16_BIT if 16 bit necessary
                                                // AUDIO_FORMAT_INVALID if no required format

        float          mVolume[MAX_NUM_VOLUMES];     // floating point set volume
        float          mPrevVolume[MAX_NUM_VOLUMES]; // floating point previous volume
        float          mVolumeInc[MAX_NUM_VOLUMES];  // floating point volume increment

        float          mAuxLevel;                     // floating point set aux level
        float          mPrevAuxLevel;                 // floating point prev aux level
        float          mAuxInc;                       // floating point aux increment

        audio_channel_mask_t mMixerChannelMask;
        uint32_t             mMixerChannelCount;

        AudioPlaybackRate    mPlaybackRate;

        bool        needsRamp() { return (volumeInc[0] | volumeInc[1] | auxInc) != 0; }
        bool        setResampler(uint32_t trackSampleRate, uint32_t devSampleRate);
        bool        doesResample() const { return resampler != NULL; }
        void        resetResampler() { if (resampler != NULL) resampler->reset(); }
        void        adjustVolumeRamp(bool aux, bool useFloat = false);
        size_t      getUnreleasedFrames() const { return resampler != NULL ?
                                                    resampler->getUnreleasedFrames() : 0; };

        status_t    prepareForDownmix();
        void        unprepareForDownmix();
        status_t    prepareForReformat();
        void        unprepareForReformat();
        bool        setPlaybackRate(const AudioPlaybackRate &playbackRate);
        void        reconfigureBufferProviders();
    };

    typedef void (*process_hook_t)(state_t* state, int64_t pts);

    // pad to 32-bytes to fill cache line
    struct state_t {
        uint32_t        enabledTracks;
        uint32_t        needsChanged;
        size_t          frameCount;
        process_hook_t  hook;   // one of process__*, never NULL
        int32_t         *outputTemp;
        int32_t         *resampleTemp;
//cjh        NBLog::Writer*  mLog;
        int32_t         reserved[1];
        // FIXME allocate dynamically to save some memory when maxNumTracks < MAX_NUM_TRACKS
        track_t         tracks[MAX_NUM_TRACKS] __attribute__((aligned(32)));
    };

    // bitmask of allocated track names, where bit 0 corresponds to TRACK0 etc.
    uint32_t        mTrackNames;

    // bitmask of configured track names; ~0 if maxNumTracks == MAX_NUM_TRACKS,
    // but will have fewer bits set if maxNumTracks < MAX_NUM_TRACKS
    const uint32_t  mConfiguredNames;

    const uint32_t  mSampleRate;

//cjh    NBLog::Writer   mDummyLog;
public:
//cjh    void            setLog(NBLog::Writer* log);
private:
    state_t         mState __attribute__((aligned(32)));

    // Call after changing either the enabled status of a track, or parameters of an enabled track.
    // OK to call more often than that, but unnecessary.
    void invalidateState(uint32_t mask);

    bool setChannelMasks(int name,
            audio_channel_mask_t trackChannelMask, audio_channel_mask_t mixerChannelMask);

    static void track__genericResample(track_t* t, int32_t* out, size_t numFrames, int32_t* temp,
            int32_t* aux);
    static void track__nop(track_t* t, int32_t* out, size_t numFrames, int32_t* temp, int32_t* aux);
    static void track__16BitsStereo(track_t* t, int32_t* out, size_t numFrames, int32_t* temp,
            int32_t* aux);
    static void track__16BitsMono(track_t* t, int32_t* out, size_t numFrames, int32_t* temp,
            int32_t* aux);
    static void volumeRampStereo(track_t* t, int32_t* out, size_t frameCount, int32_t* temp,
            int32_t* aux);
    static void volumeStereo(track_t* t, int32_t* out, size_t frameCount, int32_t* temp,
            int32_t* aux);

    static void process__validate(state_t* state, int64_t pts);
    static void process__nop(state_t* state, int64_t pts);
    static void process__genericNoResampling(state_t* state, int64_t pts);
    static void process__genericResampling(state_t* state, int64_t pts);
    static void process__OneTrack16BitsStereoNoResampling(state_t* state,
                                                          int64_t pts);

    static int64_t calculateOutputPTS(const track_t& t, int64_t basePTS,
                                      int outputFrameIndex);

    static uint64_t         sLocalTimeFreq;
    static pthread_once_t   sOnceControl;
    static void             sInitRoutine();

    /* multi-format volume mixing function (calls template functions
     * in AudioMixerOps.h).  The template parameters are as follows:
     *
     *   MIXTYPE     (see AudioMixerOps.h MIXTYPE_* enumeration)
     *   USEFLOATVOL (set to true if float volume is used)
     *   ADJUSTVOL   (set to true if volume ramp parameters needs adjustment afterwards)
     *   TO: int32_t (Q4.27) or float
     *   TI: int32_t (Q4.27) or int16_t (Q0.15) or float
     *   TA: int32_t (Q4.27)
     */
    template <int MIXTYPE, bool USEFLOATVOL, bool ADJUSTVOL,
        typename TO, typename TI, typename TA>
    static void volumeMix(TO *out, size_t outFrames,
            const TI *in, TA *aux, bool ramp, AudioMixer::track_t *t);

    // multi-format process hooks
    template <int MIXTYPE, typename TO, typename TI, typename TA>
    static void process_NoResampleOneTrack(state_t* state, int64_t pts);

    // multi-format track hooks
    template <int MIXTYPE, typename TO, typename TI, typename TA>
    static void track__Resample(track_t* t, TO* out, size_t frameCount,
            TO* temp __unused, TA* aux);
    template <int MIXTYPE, typename TO, typename TI, typename TA>
    static void track__NoResample(track_t* t, TO* out, size_t frameCount,
            TO* temp __unused, TA* aux);

    static void convertMixerFormat(void *out, audio_format_t mixerOutFormat,
            void *in, audio_format_t mixerInFormat, size_t sampleCount);

    // hook types
    enum {
        PROCESSTYPE_NORESAMPLEONETRACK,
    };
    enum {
        TRACKTYPE_NOP,
        TRACKTYPE_RESAMPLE,
        TRACKTYPE_NORESAMPLE,
        TRACKTYPE_NORESAMPLEMONO,
    };

    // functions for determining the proper process and track hooks.
    static process_hook_t getProcessHook(int processType, uint32_t channelCount,
            audio_format_t mixerInFormat, audio_format_t mixerOutFormat);
    static hook_t getTrackHook(int trackType, uint32_t channelCount,
            audio_format_t mixerInFormat, audio_format_t mixerOutFormat);
};

// ----------------------------------------------------------------------------
}} // namespace cocos2d { namespace experimental {

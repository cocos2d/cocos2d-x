/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#define LOG_TAG "AudioMixerController"

#include "audio/android/AudioMixerController.h"
#include "audio/android/AudioMixer.h"
#include "audio/android/Track.h"
#include "audio/android/OpenSLHelper.h"

#include <stdlib.h>
#include <algorithm>

namespace cocos2d { namespace experimental {

AudioMixerController::AudioMixerController(int bufferSizeInFrames, int sampleRate, int channelCount)
        : _bufferSizeInFrames(bufferSizeInFrames)
        , _sampleRate(sampleRate)
        , _channelCount(channelCount)
        , _mixer(nullptr)
        , _isPaused(false)
        , _isMixingFrame(false)
{
    ALOGV("In the constructor of AudioMixerController!");

    _mixingBuffer.size = (size_t) bufferSizeInFrames * 2 * channelCount;
    // Don't use posix_memalign since it was added from API 16, it will crash on Android 2.3
    // Therefore, for a workaround, we uses memalign here.
    _mixingBuffer.buf = memalign(32, _mixingBuffer.size);
    memset(_mixingBuffer.buf, 0, _mixingBuffer.size);
}

AudioMixerController::~AudioMixerController()
{
    destroy();

    if (_mixer != nullptr)
    {
        delete _mixer;
        _mixer = nullptr;
    }

    free(_mixingBuffer.buf);
}

bool AudioMixerController::init()
{
    _mixer = new (std::nothrow) AudioMixer(_bufferSizeInFrames, _sampleRate);
    return _mixer != nullptr;
}

bool AudioMixerController::addTrack(Track* track)
{
    ALOG_ASSERT(track != nullptr, "Shouldn't pass nullptr to addTrack");
    bool ret = false;

    std::lock_guard<std::mutex> lk(_activeTracksMutex);

    auto iter = std::find(_activeTracks.begin(), _activeTracks.end(), track);
    if (iter == _activeTracks.end())
    {
        _activeTracks.push_back(track);
        ret = true;
    }

    return ret;
}

template <typename T>
static void removeItemFromVector(std::vector<T>& v, T item)
{
    auto iter = std::find(v.begin(), v.end(), item);
    if (iter != v.end())
    {
        v.erase(iter);
    }
}

void AudioMixerController::initTrack(Track* track, std::vector<Track*>& tracksToRemove)
{
    if (track->isInitialized())
        return;

    uint32_t channelMask = audio_channel_out_mask_from_count(2);
    int32_t name = _mixer->getTrackName(channelMask, AUDIO_FORMAT_PCM_16_BIT,
                                        AUDIO_SESSION_OUTPUT_MIX);
    if (name < 0)
    {
        // If we could not get the track name, it means that there're MAX_NUM_TRACKS tracks
        // So ignore the new track.
        tracksToRemove.push_back(track);
    }
    else
    {
        _mixer->setBufferProvider(name, track);
        _mixer->setParameter(name, AudioMixer::TRACK, AudioMixer::MAIN_BUFFER,
                             _mixingBuffer.buf);
        _mixer->setParameter(
                name,
                AudioMixer::TRACK,
                AudioMixer::MIXER_FORMAT,
                (void *) (uintptr_t) AUDIO_FORMAT_PCM_16_BIT);
        _mixer->setParameter(
                name,
                AudioMixer::TRACK,
                AudioMixer::FORMAT,
                (void *) (uintptr_t) AUDIO_FORMAT_PCM_16_BIT);
        _mixer->setParameter(
                name,
                AudioMixer::TRACK,
                AudioMixer::MIXER_CHANNEL_MASK,
                (void *) (uintptr_t) channelMask);
        _mixer->setParameter(
                name,
                AudioMixer::TRACK,
                AudioMixer::CHANNEL_MASK,
                (void *) (uintptr_t) channelMask);

        track->setName(name);
        _mixer->enable(name);

        std::lock_guard<std::mutex> lk(track->_volumeDirtyMutex);
        gain_minifloat_packed_t volume = track->getVolumeLR();
        float lVolume = float_from_gain(gain_minifloat_unpack_left(volume));
        float rVolume = float_from_gain(gain_minifloat_unpack_right(volume));

        _mixer->setParameter(name, AudioMixer::VOLUME, AudioMixer::VOLUME0, &lVolume);
        _mixer->setParameter(name, AudioMixer::VOLUME, AudioMixer::VOLUME1, &rVolume);

        track->setVolumeDirty(false);
        track->setInitialized(true);
    }
}

void AudioMixerController::mixOneFrame()
{
    _isMixingFrame = true;
    _activeTracksMutex.lock();

    auto mixStart = clockNow();

    std::vector<Track*> tracksToRemove;
    tracksToRemove.reserve(_activeTracks.size());

    // FOR TESTING BEGIN
//        Track* track = _activeTracks[0];
//
//        AudioBufferProvider::Buffer buffer;
//        buffer.frameCount = _bufferSizeInFrames;
//        status_t r = track->getNextBuffer(&buffer);
////        ALOG_ASSERT(buffer.frameCount == _mixing->size / 2, "buffer.frameCount:%d, _mixing->size/2:%d", buffer.frameCount, _mixing->size/2);
//        if (r == NO_ERROR)
//        {
//            ALOGV("getNextBuffer succeed ...");
//            memcpy(_mixing->buf, buffer.raw, _mixing->size);
//        }
//        if (buffer.raw == nullptr)
//        {
//            ALOGV("Play over ...");
//            tracksToRemove.push_back(track);
//        }
//        else
//        {
//            track->releaseBuffer(&buffer);
//        }
//
//        _mixing->state = BufferState::FULL;
//        _activeTracksMutex.unlock();
    // FOR TESTING END

    Track::State state;
    // set up the tracks.
    for (auto&& track : _activeTracks)
    {
        state = track->getState();

        if (state == Track::State::PLAYING)
        {
            initTrack(track, tracksToRemove);

            int name = track->getName();
            ALOG_ASSERT(name >= 0);

            std::lock_guard<std::mutex> lk(track->_volumeDirtyMutex);

            if (track->isVolumeDirty())
            {
                gain_minifloat_packed_t volume = track->getVolumeLR();
                float lVolume = float_from_gain(gain_minifloat_unpack_left(volume));
                float rVolume = float_from_gain(gain_minifloat_unpack_right(volume));

                ALOGV("Track (name: %d)'s volume is dirty, update volume to L: %f, R: %f", name, lVolume, rVolume);

                _mixer->setParameter(name, AudioMixer::VOLUME, AudioMixer::VOLUME0, &lVolume);
                _mixer->setParameter(name, AudioMixer::VOLUME, AudioMixer::VOLUME1, &rVolume);

                track->setVolumeDirty(false);
            }
        }
        else if (state == Track::State::RESUMED)
        {
            initTrack(track, tracksToRemove);

            if (track->getPrevState() == Track::State::PAUSED)
            {
                _mixer->enable(track->getName());
                track->setState(Track::State::PLAYING);
            }
            else
            {
                ALOGW("Previous state (%d) isn't PAUSED, couldn't resume!", static_cast<int>(track->getPrevState()));
            }
        }
        else if (state == Track::State::PAUSED)
        {
            initTrack(track, tracksToRemove);

            if (track->getPrevState() == Track::State::PLAYING || track->getPrevState() == Track::State::RESUMED)
            {
                _mixer->disable(track->getName());
            }
            else
            {
                ALOGW("Previous state (%d) isn't PLAYING, couldn't pause!", static_cast<int>(track->getPrevState()));
            }
        }
        else if (state == Track::State::STOPPED)
        {
            if (track->isInitialized())
            {
                _mixer->deleteTrackName(track->getName());
            }
            else
            {
                ALOGV("Track (%p) hasn't been initialized yet!", track);
            }
            tracksToRemove.push_back(track);
        }

        if (track->isPlayOver())
        {
            if (track->isLoop())
            {
                track->reset();
            }
            else
            {
                ALOGV("Play over ...");
                _mixer->deleteTrackName(track->getName());
                tracksToRemove.push_back(track);
                track->setState(Track::State::OVER);
            }
        }
    }

    bool hasAvailableTracks = _activeTracks.size() - tracksToRemove.size() > 0;

    if (hasAvailableTracks)
    {
        ALOGV_IF(_activeTracks.size() > 8,  "More than 8 active tracks: %d", (int) _activeTracks.size());
        _mixer->process(AudioBufferProvider::kInvalidPTS);
    }
    else
    {
        ALOGV("Doesn't have enough tracks: %d, %d", (int) _activeTracks.size(), (int) tracksToRemove.size());
    }

    // Remove stopped or playover tracks for active tracks container
    for (auto&& track : tracksToRemove)
    {
        removeItemFromVector(_activeTracks, track);

        if (track != nullptr && track->onStateChanged != nullptr)
        {
            track->onStateChanged(Track::State::DESTROYED);
        }
        else
        {
            ALOGE("track (%p) was released ...", track);
        }
    }

    _activeTracksMutex.unlock();

    auto mixEnd = clockNow();
    float mixInterval = intervalInMS(mixStart, mixEnd);
    ALOGV_IF(mixInterval > 1.0f, "Mix a frame waste: %fms", mixInterval);

    _isMixingFrame = false;
}

void AudioMixerController::destroy()
{
    while (_isMixingFrame)
    {
        usleep(10);
    }
    usleep(2000); // Wait for more 2ms
}

void AudioMixerController::pause()
{
    _isPaused = true;
}

void AudioMixerController::resume()
{
    _isPaused = false;
}

bool AudioMixerController::hasPlayingTacks()
{
    std::lock_guard<std::mutex> lk (_activeTracksMutex);
    if (_activeTracks.empty())
        return false;

    for (auto&& track : _activeTracks)
    {
        Track::State state = track->getState();
        if (state == Track::State::IDLE || state == Track::State::PLAYING || state == Track::State::RESUMED)
        {
            return true;
        }
    }

    return false;
}

}} // namespace cocos2d { namespace experimental {

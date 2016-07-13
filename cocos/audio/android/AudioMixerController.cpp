/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.

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

#include <algorithm>
#include <stdlib.h> // for posix_memalign

namespace cocos2d {

AudioMixerController::AudioMixerController(int bufferSizeInFrames, int sampleRate, int channelCount)
        : _bufferSizeInFrames(bufferSizeInFrames)
        , _sampleRate(sampleRate)
        , _channelCount(channelCount)
//        , _mixingThread(nullptr)
        , _mixer(nullptr)
        , _isDestroy(false)
        , _isPaused(false)
{
    ALOGV("In the constructor of AudioMixerController!");
    for (int i = 0; i < ARRAY_SIZE(_buffers); ++i)
    {
        _buffers[i].size = (size_t) bufferSizeInFrames * 2 * channelCount;
        // Don't use posix_memalign since it was added from API 16, it will crash on Android 2.3
        // Therefore, for a workaround, we uses memalign here.
        _buffers[i].buf = memalign(32, _buffers[i].size);
//        posix_memalign(&_buffers[i].buf, 32, _buffers[i].size);
        memset(_buffers[i].buf, 0, _buffers[i].size);
//        _buffers[i].state = BufferState::EMPTY;
    }

//    _busy = &_buffers[0];
    _current = &_buffers[0];
//    _next = &_buffers[2];
//    _afterNext = &_buffers[3];
    _mixing = nullptr;
}

AudioMixerController::~AudioMixerController()
{
    destroy();
//    if (_mixingThread != nullptr)
//    {
//        _mixingThread->join();
//        delete _mixingThread;
//        _mixingThread = nullptr;
//    }

    if (_mixer != nullptr)
    {
        delete _mixer;
        _mixer = nullptr;
    }

    for (int i = 0; i < sizeof(_buffers) / sizeof(_buffers[0]); ++i)
    {
        free(_buffers[i].buf);
    }
}

bool AudioMixerController::init()
{
    _mixer = new (std::nothrow) AudioMixer(_bufferSizeInFrames, _sampleRate);
//    _mixingThread = new (std::nothrow) std::thread(&AudioMixerController::mixingThreadLoop, this);
    return true;
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
//        _mixingCondition.notify_one();
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

void AudioMixerController::mixOneFrame()
{
    _isMixingFrame = true;
//    _switchMutex.lock();
    _activeTracksMutex.lock();

    auto mixStart = clockNow();

//    if (_current->state == BufferState ::EMPTY)
    {
        _mixing = _current;
    }
//    else if (_next->state == BufferState::EMPTY)
//    {
//        _mixing = _next;
//    }
//    else if (_afterNext->state == BufferState::EMPTY)
//    {
//        _mixing = _afterNext;
//    }

//    _switchMutex.unlock();

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

        if (state == Track::State::IDLE)
        {
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
                                     _mixing->buf);
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

                gain_minifloat_packed_t volume = track->getVolumeLR();
                float lVolume = float_from_gain(gain_minifloat_unpack_left(volume));
                float rVolume = float_from_gain(gain_minifloat_unpack_right(volume));

                _mixer->setParameter(name, AudioMixer::VOLUME, AudioMixer::VOLUME0, &lVolume);
                _mixer->setParameter(name, AudioMixer::VOLUME, AudioMixer::VOLUME1, &rVolume);
                _mixer->enable(name);

                track->setState(Track::State::PLAYING);
                track->setName(name);
                track->setVolumeDirty(false);
            }
        }
        else if (state == Track::State::PLAYING)
        {
            ALOG_ASSERT(track->getName() >= 0);
            int name = track->getName();
            // If we don't use multiple buffers, no need to reset the MAIN_BUFFER for mixer.
//                _mixer->setParameter(name, AudioMixer::TRACK, AudioMixer::MAIN_BUFFER, _mixing->buf);
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
            if (track->getPrevState() == Track::State::PAUSED)
            {
                _mixer->enable(track->getName());
                track->setState(Track::State::PLAYING);
            }
            else
            {
                ALOGW("Previous state (%d) isn't PAUSED, couldn't resume!", track->getPrevState());
            }
        }
        else if (state == Track::State::PAUSED)
        {
            if (track->getPrevState() == Track::State::PLAYING || track->getPrevState() == Track::State::RESUMED)
            {
                _mixer->disable(track->getName());
            }
            else
            {
                ALOGW("Previous state (%d) isn't PLAYING, couldn't pause!", track->getPrevState());
            }
        }
        else if (state == Track::State::STOPPED)
        {
            if (track->getPrevState() != Track::State::IDLE)
            {
                _mixer->deleteTrackName(track->getName());
            }
            else
            {
                ALOGV("Stop track (%p) while it's in IDLE state!", track);
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
//    _activeTracksMutex.unlock();

    if (hasAvailableTracks)
    {
        ALOGV_IF(_activeTracks.size() > 8,  "More than 8 active tracks: %d", (int) _activeTracks.size());
        _mixer->process(AudioBufferProvider::kInvalidPTS);
//        _mixing->state = BufferState::FULL;
    }
    else
    {
        ALOGV("Doesn't have enough tracks: %d, %d", (int) _activeTracks.size(), (int) tracksToRemove.size());
    }

//    _activeTracksMutex.lock();

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

//void AudioMixerController::mixingThreadLoop()
//{
//    auto doWait = [this](){
//        std::unique_lock<std::mutex> lk(_mixingMutex);
//        _switchMutex.unlock();
//        _activeTracksMutex.unlock();
//
//        _mixingCondition.wait(lk);
//
//        _switchMutex.lock();
//        _activeTracksMutex.lock();
//    };
//
//    for (;;)
//    {
//        _switchMutex.lock();
//        _activeTracksMutex.lock();
//
//        if (_isPaused)
//        {
//            doWait();
//        }
//
//        if (_activeTracks.empty())
//        {
//            doWait();
//        }
//
//        if  (_current->state == BufferState::FULL && _next->state == BufferState::FULL && _afterNext->state == BufferState::FULL)
//        {
//            ALOGD("Yeah, all buffers are full, waiting ...");
//            doWait();
//        }
//
//        if (_isDestroy)
//        {
//            _switchMutex.unlock();
//            _activeTracksMutex.unlock();
//            _isDestroy = false;
//            return;
//        }
//
////       mixOneFrame();
//    }
//}
//
//void AudioMixerController::switchBuffers()
//{
//    ALOGD("AudioMixerController::switchBuffers ...");
//    _switchMutex.lock();
//    OutputBuffer* tmp = _busy;
//    _busy = _current; _busy->state = BufferState::BUSY;
//    _current = _next; // Don't change current state
//    _next = _afterNext; // Don't change next state
//    _afterNext = tmp; _afterNext->state = BufferState::EMPTY;
//    _switchMutex.unlock();
//
//    _mixingCondition.notify_one();
//    _current->state = BufferState::EMPTY;
//}

void AudioMixerController::destroy()
{
//    _isDestroy = true;
//    while(_isDestroy)
//    {
//        _mixingCondition.notify_one();
//        usleep(100);
//    }
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
//    _mixingCondition.notify_one();
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
} // namespace cocos2d
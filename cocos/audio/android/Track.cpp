/****************************************************************************
Copyright (c) 2016-2017 Chukong Technologies Inc.

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

#define LOG_TAG "Track"

#include "audio/android/cutils/log.h"
#include "audio/android/Track.h"

#include <math.h>

namespace cocos2d { namespace experimental {

Track::Track(const PcmData &pcmData)
        : onStateChanged(nullptr)
        , _pcmData(pcmData)
        , _prevState(State::IDLE)
        , _state(State::IDLE)
        , _name(-1)
        , _volume(1.0f)
        , _isVolumeDirty(true)
        , _isLoop(false)
        , _isInitialized(false)
        , _isAudioFocus(true)
{
    init(_pcmData.pcmBuffer->data(), _pcmData.numFrames, _pcmData.bitsPerSample / 8 * _pcmData.numChannels);
}

Track::~Track()
{
    ALOGV("~Track(): %p", this);
}

gain_minifloat_packed_t Track::getVolumeLR()
{
    float volume = _isAudioFocus ? _volume : 0.0f;
    gain_minifloat_t v = gain_from_float(volume);
    return gain_minifloat_pack(v, v);
}

bool Track::setPosition(float pos)
{
    _nextFrame = (size_t) (pos * _numFrames / _pcmData.duration);
    _unrel = 0;
    return true;
}

float Track::getPosition() const
{
    return _nextFrame * _pcmData.duration / _numFrames;
}

void Track::setVolume(float volume)
{
    std::lock_guard<std::mutex> lk(_volumeDirtyMutex);
    if (fabs(_volume - volume) > 0.00001)
    {
        _volume = volume;
        setVolumeDirty(true);
    }
}

float Track::getVolume() const
{
    return _volume;
}

void Track::setAudioFocus(bool isFocus)
{
    _isAudioFocus = isFocus;
    setVolumeDirty(true);
}

void Track::setState(State state)
{
    std::lock_guard<std::mutex> lk(_stateMutex);
    if (_state != state)
    {
        _prevState = _state;
        _state = state;
        onStateChanged(_state);
    }
};

}} // namespace cocos2d { namespace experimental {
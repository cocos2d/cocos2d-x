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

#pragma once

#include "audio/android/PcmData.h"
#include "audio/android/IVolumeProvider.h"
#include "audio/android/PcmBufferProvider.h"

#include <functional>
#include <mutex>

namespace cocos2d { namespace experimental {

class Track : public PcmBufferProvider, public IVolumeProvider
{
public:
    enum class State
    {
        IDLE,
        PLAYING,
        RESUMED,
        PAUSED,
        STOPPED,
        OVER,
        DESTROYED
    };

    Track(const PcmData &pcmData);
    virtual ~Track();

    inline State getState() const { return _state; };
    void setState(State state);

    inline State getPrevState() const { return _prevState; };

    inline bool isPlayOver() const { return _state == State::PLAYING && _nextFrame >= _numFrames;};
    inline void setName(int name) { _name = name; };
    inline int getName() const { return _name; };

    void setVolume(float volume);
    float getVolume() const;

    bool setPosition(float pos);
    float getPosition() const;

    virtual gain_minifloat_packed_t getVolumeLR() override ;

    inline void setLoop(bool isLoop) { _isLoop = isLoop; };
    inline bool isLoop() const { return _isLoop; };

    std::function<void(State)> onStateChanged;

private:
    inline bool isVolumeDirty() const
    { return _isVolumeDirty; };

    inline void setVolumeDirty(bool isDirty)
    { _isVolumeDirty = isDirty; };

    inline bool isInitialized() const
    { return _isInitialized; };

    inline void setInitialized(bool isInitialized)
    { _isInitialized = isInitialized; };

private:
    PcmData _pcmData;
    State _prevState;
    State _state;
    std::mutex _stateMutex;
    int _name;
    float _volume;
    bool _isVolumeDirty;
    std::mutex _volumeDirtyMutex;
    bool _isLoop;
    bool _isInitialized;

    friend class AudioMixerController;
};

}} // namespace cocos2d { namespace experimental {

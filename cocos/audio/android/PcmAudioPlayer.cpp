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

#define LOG_TAG "PcmAudioPlayer"

#include "audio/android/cutils/log.h"
#include "audio/android/PcmAudioPlayer.h"
#include "audio/android/AudioMixerController.h"
#include "audio/android/ICallerThreadUtils.h"

namespace cocos2d { namespace experimental {

PcmAudioPlayer::PcmAudioPlayer(AudioMixerController * controller, ICallerThreadUtils* callerThreadUtils)
        : _id(-1)
        , _track(nullptr)
        , _playEventCallback(nullptr)
        , _controller(controller)
        , _callerThreadUtils(callerThreadUtils)
{
    ALOGV("PcmAudioPlayer constructor: %p", this);
}

PcmAudioPlayer::~PcmAudioPlayer()
{
    ALOGV("In the destructor of PcmAudioPlayer (%p)", this);
    delete _track;
}

bool PcmAudioPlayer::prepare(const std::string &url, const PcmData &decResult)
{
    _url = url;
    _decResult = decResult;

    _track = new (std::nothrow) Track(_decResult);

    std::thread::id callerThreadId = _callerThreadUtils->getCallerThreadId();

    _track->onStateChanged = [this, callerThreadId](Track::State state) {
        // It maybe in sub thread
        auto func = [this, state](){
            // It's in caller's thread
            if (state == Track::State::OVER)
            {
                if (_playEventCallback != nullptr)
                {
                    _playEventCallback(State::OVER);
                }
            }
            else if (state == Track::State::STOPPED)
            {
                if (_playEventCallback != nullptr)
                {
                    _playEventCallback(State::STOPPED);
                }
            }
            else if (state == Track::State::DESTROYED)
            {
                delete this;
            }
        };

        if (callerThreadId == std::this_thread::get_id())
        {
            func();
        }
        else
        {
            _callerThreadUtils->performFunctionInCallerThread(func);
        }
    };

    setVolume(1.0f);

    return true;
}

void PcmAudioPlayer::rewind()
{
    ALOGW("PcmAudioPlayer::rewind isn't supported!");
}

void PcmAudioPlayer::setVolume(float volume)
{
    _track->setVolume(volume);
}

float PcmAudioPlayer::getVolume() const
{
    return _track->getVolume();
}

void PcmAudioPlayer::setLoop(bool isLoop)
{
    _track->setLoop(isLoop);
}

bool PcmAudioPlayer::isLoop() const
{
    return _track->isLoop();
}

float PcmAudioPlayer::getDuration() const
{
    return _decResult.duration;
}

float PcmAudioPlayer::getPosition() const
{
    return _track->getPosition();
}

bool PcmAudioPlayer::setPosition(float pos)
{
    return _track->setPosition(pos);
}

void PcmAudioPlayer::setPlayEventCallback(const PlayEventCallback &playEventCallback)
{
    _playEventCallback = playEventCallback;
}

void PcmAudioPlayer::play()
{
    // put track to AudioMixerController
    ALOGV("PcmAudioPlayer (%p) play (%s) ...", this, _url.c_str());
    _controller->addTrack(_track);
    _track->setState(Track::State::PLAYING);
}

void PcmAudioPlayer::pause()
{
    ALOGV("PcmAudioPlayer (%p) pause ...", this);
    _track->setState(Track::State::PAUSED);
}

void PcmAudioPlayer::resume()
{
    ALOGV("PcmAudioPlayer (%p) resume ...", this);
    _track->setState(Track::State::RESUMED);
}

void PcmAudioPlayer::stop()
{
    ALOGV("PcmAudioPlayer (%p) stop ...", this);
    _track->setState(Track::State::STOPPED);
}

IAudioPlayer::State PcmAudioPlayer::getState() const
{
    IAudioPlayer::State state = State::INVALID;

    if (_track != nullptr)
    {
        switch (_track->getState())
        {
            case Track::State::IDLE:
                state = State::INITIALIZED;
                break;

            case Track::State::PLAYING:
                state = State::PLAYING;
                break;

            case Track::State::RESUMED:
                state = State::PLAYING;
                break;

            case Track::State::PAUSED:
                state = State::PAUSED;
                break;

            case Track::State::STOPPED:
                state = State::STOPPED;
                break;

            case Track::State::OVER:
                state = State::OVER;
                break;

            default:
                state = State::INVALID;
                break;
        }
    }
    return state;
}

}} // namespace cocos2d { namespace experimental {

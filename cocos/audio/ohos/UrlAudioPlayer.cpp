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

#define LOG_TAG "UrlAudioPlayer"

#include "UrlAudioPlayer.h"
#include "ICallerThreadUtils.h"
#include <vector>
#include "Macros.h"
#include <cmath>
#include <algorithm> // for std::find

namespace {

std::mutex __playerContainerMutex;//NOLINT(bugprone-reserved-identifier,readability-identifier-naming)
std::vector<cocos2d::experimental::UrlAudioPlayer *> __playerContainer;//NOLINT(bugprone-reserved-identifier,readability-identifier-naming)
std::once_flag __onceFlag;//NOLINT(bugprone-reserved-identifier,readability-identifier-naming)

} // namespace

namespace cocos2d { namespace experimental {

class SLUrlAudioPlayerCallbackProxy {
public:
    static void playEventCallback(SLPlayItf caller, void *context, SLuint32 playEvent) {
        auto *thiz = reinterpret_cast<UrlAudioPlayer *>(context);
        // We must use a mutex for the whole block of the following function invocation.
        std::lock_guard<std::mutex> lk(__playerContainerMutex);
        auto iter = std::find(__playerContainer.begin(), __playerContainer.end(), thiz);
        if (iter != __playerContainer.end()) {
            thiz->playEventCallback(caller, playEvent);
        }
    }
};

UrlAudioPlayer::UrlAudioPlayer(SLEngineItf engineItf, SLObjectItf outputMixObject, ICallerThreadUtils *callerThreadUtils)
: _engineItf(engineItf), _outputMixObj(outputMixObject), _callerThreadUtils(callerThreadUtils), _id(-1), _assetFd(nullptr), _playObj(nullptr), _playItf(nullptr), _seekItf(nullptr), _volumeItf(nullptr), _volume(0.0F), _duration(0.0F), _isLoop(false), _isAudioFocus(true), _state(State::INVALID), _playEventCallback(nullptr), _isDestroyed(std::make_shared<bool>(false)) {
    std::call_once(__onceFlag, []() {
        __playerContainer.reserve(10);
    });

    __playerContainerMutex.lock();
    __playerContainer.push_back(this);
    ALOGV("Current UrlAudioPlayer instance count: %d", (int)__playerContainer.size());
    __playerContainerMutex.unlock();

    _callerThreadId = callerThreadUtils->getCallerThreadId();
}

UrlAudioPlayer::~UrlAudioPlayer() {
    ALOGV("~UrlAudioPlayer(): %p", this);

    __playerContainerMutex.lock();

    auto iter = std::find(__playerContainer.begin(), __playerContainer.end(), this);
    if (iter != __playerContainer.end()) {
        __playerContainer.erase(iter);
    }

    __playerContainerMutex.unlock();
}

void UrlAudioPlayer::playEventCallback(SLPlayItf caller, SLuint32 playEvent) {
    CC_UNUSED_PARAM(caller);
    // Note that it's on sub thread, please don't invoke OpenSLES API on sub thread
    if (playEvent == SL_PLAYEVENT_HEADATEND) {
        std::shared_ptr<bool> isDestroyed = _isDestroyed;

        auto func = [this, isDestroyed]() {
            // If it was destroyed, just return.
            if (*isDestroyed) {
                ALOGV("The UrlAudioPlayer (%p) was destroyed!", this);
                return;
            }

            //Note that It's in the caller's thread (Cocos Thread)
            // If state is already stopped, ignore the play over event.

            if (_state == State::STOPPED) {
                return;
            }

            //fix issue#8965:AudioEngine can't looping audio on Android 2.3.x
            if (isLoop()) {
                play();
            } else {
                setState(State::OVER);
                if (_playEventCallback != nullptr) {
                    _playEventCallback(State::OVER);
                }

                ALOGV("UrlAudioPlayer (%p) played over, destroy self ...", this);
                destroy();
                delete this;
            }
        };

        if (_callerThreadId == std::this_thread::get_id()) {
            func();
        } else {
            _callerThreadUtils->performFunctionInCallerThread(func);
        }
    }
}

void UrlAudioPlayer::setPlayEventCallback(const PlayEventCallback &playEventCallback) {
    _playEventCallback = playEventCallback;
}

void UrlAudioPlayer::stop() {
    ALOGV("UrlAudioPlayer::stop (%p, %d)", this, getId());
    SLresult r = (*_playItf)->SetPlayState(_playItf, SL_PLAYSTATE_STOPPED);
    SL_RETURN_IF_FAILED(r, "UrlAudioPlayer::stop failed");

    if (_state == State::PLAYING || _state == State::PAUSED) {
        setLoop(false);
        setState(State::STOPPED);

        if (_playEventCallback != nullptr) {
            _playEventCallback(State::STOPPED);
        }

        destroy();
        delete this;
    } else {
        ALOGW("UrlAudioPlayer (%p, state:%d) isn't playing or paused, could not invoke stop!", this, static_cast<int>(_state));
    }
}

void UrlAudioPlayer::pause() {
    if (_state == State::PLAYING) {
        SLresult r = (*_playItf)->SetPlayState(_playItf, SL_PLAYSTATE_PAUSED);
        SL_RETURN_IF_FAILED(r, "UrlAudioPlayer::pause failed");
        setState(State::PAUSED);
    } else {
        ALOGW("UrlAudioPlayer (%p, state:%d) isn't playing, could not invoke pause!", this, static_cast<int>(_state));
    }
}

void UrlAudioPlayer::resume() {
    if (_state == State::PAUSED) {
        SLresult r = (*_playItf)->SetPlayState(_playItf, SL_PLAYSTATE_PLAYING);
        SL_RETURN_IF_FAILED(r, "UrlAudioPlayer::resume failed");
        setState(State::PLAYING);
    } else {
        ALOGW("UrlAudioPlayer (%p, state:%d) isn't paused, could not invoke resume!", this, static_cast<int>(_state));
    }
}

void UrlAudioPlayer::play() {
    if (_state == State::INITIALIZED || _state == State::PAUSED) {
        SLresult r = (*_playItf)->SetPlayState(_playItf, SL_PLAYSTATE_PLAYING);
        SL_RETURN_IF_FAILED(r, "UrlAudioPlayer::play failed");
        setState(State::PLAYING);
    } else {
        ALOGW("UrlAudioPlayer (%p, state:%d) isn't paused or initialized, could not invoke play!", this, static_cast<int>(_state));
    }
}

void UrlAudioPlayer::setVolumeToSLPlayer(float volume) {
    int dbVolume = static_cast<int>(2000 * log10(volume));
    if (dbVolume < SL_MILLIBEL_MIN) {
        dbVolume = SL_MILLIBEL_MIN;
    }
    SLresult r = (*_volumeItf)->SetVolumeLevel(_volumeItf, dbVolume);
    SL_RETURN_IF_FAILED(r, "UrlAudioPlayer::setVolumeToSLPlayer %d failed", dbVolume);
}

void UrlAudioPlayer::setVolume(float volume) {
    _volume = volume;
    if (_isAudioFocus) {
        setVolumeToSLPlayer(_volume);
    }
}

float UrlAudioPlayer::getVolume() const {
    return _volume;
}

void UrlAudioPlayer::setAudioFocus(bool isFocus) {
    _isAudioFocus = isFocus;
    float volume = _isAudioFocus ? _volume : 0.0F;
    setVolumeToSLPlayer(volume);
}

float UrlAudioPlayer::getDuration() const {
    if (_duration > 0) {
        return _duration;
    }

    SLmillisecond duration;
    SLresult r = (*_playItf)->GetDuration(_playItf, &duration);
    SL_RETURN_VAL_IF_FAILED(r, 0.0F, "UrlAudioPlayer::getDuration failed");

    if (duration == SL_TIME_UNKNOWN) {
        return -1.0F;
    } else {// NOLINT(readability-else-after-return)
        const_cast<UrlAudioPlayer *>(this)->_duration = duration / 1000.0F;

        if (_duration <= 0) {
            return -1.0F;
        }
    }
    return _duration;
}

float UrlAudioPlayer::getPosition() const {
    SLmillisecond millisecond;
    SLresult r = (*_playItf)->GetPosition(_playItf, &millisecond);
    SL_RETURN_VAL_IF_FAILED(r, 0.0F, "UrlAudioPlayer::getPosition failed");
    return millisecond / 1000.0F;
}

bool UrlAudioPlayer::setPosition(float pos) {
    SLmillisecond millisecond = 1000.0F * pos;
    SLresult r = (*_seekItf)->SetPosition(_seekItf, millisecond, SL_SEEKMODE_ACCURATE);
    SL_RETURN_VAL_IF_FAILED(r, false, "UrlAudioPlayer::setPosition %f failed", pos);
    return true;
}

bool UrlAudioPlayer::prepare(const std::string &url, SLuint32 locatorType, std::shared_ptr<AssetFd> assetFd, int start,
                             int length) {
    _url = url;
    _assetFd = std::move(assetFd);
    // OH上不支持，直接返回true
    return true;
}

void UrlAudioPlayer::rewind() {
    // Not supported currently. since cocos audio engine will new -> prepare -> play again.
}

void UrlAudioPlayer::setLoop(bool isLoop) {
    _isLoop = isLoop;

    SLboolean loopEnable = _isLoop ? SL_BOOLEAN_TRUE : SL_BOOLEAN_FALSE;
    SLresult r = (*_seekItf)->SetLoop(_seekItf, loopEnable, 0, SL_TIME_UNKNOWN);
    SL_RETURN_IF_FAILED(r, "UrlAudioPlayer::setLoop %d failed", _isLoop ? 1 : 0);
}

bool UrlAudioPlayer::isLoop() const {
    return _isLoop;
}

void UrlAudioPlayer::stopAll() {
    // To avoid break the for loop, we need to copy a new map
    __playerContainerMutex.lock();
    auto temp = __playerContainer;
    __playerContainerMutex.unlock();

    for (auto &&player : temp) {
        player->stop();
    }
}

void UrlAudioPlayer::destroy() {
    if (!*_isDestroyed) {
        *_isDestroyed = true;
        ALOGV("UrlAudioPlayer::destroy() %p", this);
        SL_DESTROY_OBJ(_playObj);
        ALOGV("UrlAudioPlayer::destroy end");
    }
}

}} // namespace cocos2d { namespace experimental

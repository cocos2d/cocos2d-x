#include "BigAudioPlayer.h"
#include "cutils/log.h"
#include "ICallerThreadUtils.h"

namespace cocos2d { namespace experimental {

BigAudioPlayer::BigAudioPlayer()
: _id(-1), _track(nullptr), _playEventCallback(nullptr), _service(nullptr) {
    ALOGV("BigAudioPlayer constructor: %p", this);
}

BigAudioPlayer::~BigAudioPlayer() {
    ALOGV("In the destructor of BigAudioPlayer (%p)", this);
    delete _track;
    delete _service;
}

bool BigAudioPlayer::prepare(const std::string &url, const PcmData &decResult)
{
    _url = url;
    _duration = decResult.duration;
    _track = new Track(decResult);

    _track->onStateChanged = [this](Track::State state) {
        Track::State prevState = _track->getPrevState();
        ALOGE("PcmAudioPlayer %{public}p onStateChanged: preState = %{public}d, state = %{public}d", this, (int)prevState, (int)state);
        if (state == Track::State::OVER && prevState != Track::State::STOPPED) {
            if (_playEventCallback != nullptr) {
                _playEventCallback(State::OVER);
            }
        } else if (state == Track::State::STOPPED) {
            if (_playEventCallback != nullptr) {
                _playEventCallback(State::STOPPED);
            }
        } else if (state == Track::State::DESTROYED) {
            delete this;
        }
    };

    setVolume(1.0f);
    
    _service = new BigAudioService();
    _service->init(decResult);

    return true;
}

void BigAudioPlayer::rewind() {
    ALOGW("BigAudioPlayer::rewind isn't supported!");
}

void BigAudioPlayer::setVolume(float volume) {
    _track->setVolume(volume);
}

float BigAudioPlayer::getVolume() const {
    return _track->getVolume();
}

void BigAudioPlayer::setAudioFocus(bool isFocus) {
    _track->setAudioFocus(isFocus);
}

void BigAudioPlayer::setLoop(bool isLoop) {
    _track->setLoop(isLoop);
}

bool BigAudioPlayer::isLoop() const {
    return _track->isLoop();
}

float BigAudioPlayer::getDuration() const {
    return _duration;
}

float BigAudioPlayer::getPosition() const {
    return _track->getPosition();
}

bool BigAudioPlayer::setPosition(float pos) {
    return _track->setPosition(pos);
}

void BigAudioPlayer::setPlayEventCallback(const PlayEventCallback &playEventCallback) {
    _playEventCallback = playEventCallback;
}

void BigAudioPlayer::play() {
    ALOGV("BigAudioPlayer (%{public}p) play, url: %{public}s", this, _url.c_str());
    _track->setState(Track::State::PLAYING);
    _service->setTrack(_track);
}

void BigAudioPlayer::pause() {
    ALOGV("BigAudioPlayer (%{public}p) pause, url: %{public}s", this, _url.c_str());
    _service->pause();
}

void BigAudioPlayer::resume() {
    ALOGV("BigAudioPlayer (%{public}p) resume, url: %{public}s", this, _url.c_str());
    _service->resume();
}

void BigAudioPlayer::stop() {
    ALOGV("BigAudioPlayer (%{public}p) stop, url: %{public}s", this, _url.c_str());
    
    setLoop(false);
    _track->setState(Track::State::STOPPED);
}

IAudioPlayer::State BigAudioPlayer::getState() const {
    IAudioPlayer::State state = State::INVALID;

    if (_track != nullptr) {
        switch (_track->getState()) {
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

}} // namespace cocos2d { namespace experimental

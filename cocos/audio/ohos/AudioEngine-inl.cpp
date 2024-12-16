/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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
#include <rawfile/raw_file.h>
#define LOG_TAG "AudioEngineImpl"

#include "AudioEngine-inl.h"

#include <unistd.h>


#include <sys/types.h>
#include <mutex>
#include <thread>


#include "audio/include/AudioEngine.h"

#include "platform/ohos/CCFileUtils-ohos.h"
#include "AudioDecoder.h"
#include "AudioDecoderProvider.h"
#include "AudioPlayerProvider.h"
#include "IAudioPlayer.h"
#include "ICallerThreadUtils.h"
#include "UrlAudioPlayer.h"
#include "cutils/log.h"

#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCEventListenerCustom.h"


using namespace cocos2d;
using namespace cocos2d::experimental; //NOLINT

namespace {
    AudioEngineImpl *gAudioImpl = nullptr;
    int outputSampleRate = 48000;

// TODO(hack) : There is currently a bug in the opensles module,
// so openharmony must configure a fixed size, otherwise the callback will be suspended
    int              bufferSizeInFrames = 2048;


    void getAudioInfo() {

    }
} // namespace

class CallerThreadUtils : public ICallerThreadUtils {
public:
    void performFunctionInCallerThread(const std::function<void()> &func) override {
        cocos2d::Director::sharedDirector()->getScheduler()->performFunctionInCocosThread(func);

    };

    std::thread::id getCallerThreadId() override {
        return _tid;
    };

    void setCallerThreadId(std::thread::id tid) {
        _tid = tid;
    };

private:
    std::thread::id _tid;
};

static CallerThreadUtils gCallerThreadUtils;

static int fdGetter(const std::string &url, off_t *start, off_t *length) {
    int fd = -1;

    RawFileDescriptor descriptor;
    FileUtilsOhos *utils = dynamic_cast<FileUtilsOhos*>(FileUtils::getInstance());
    utils->getRawFileDescriptor(url, descriptor);
    fd = descriptor.fd;

    if (fd <= 0) {
        ALOGE("Failed to open file descriptor for '%{public}s'", url.c_str());
    }

    return fd;
};

//====================================================
AudioEngineImpl::AudioEngineImpl()
        : _engineObject(nullptr),
          _engineEngine(nullptr),
          _outputMixObject(nullptr),
          _audioPlayerProvider(nullptr),
          _onPauseListener(nullptr),
          _onResumeListener(nullptr),
          _audioIDIndex(0),
          _lazyInitLoop(true) {
    gCallerThreadUtils.setCallerThreadId(std::this_thread::get_id());
    gAudioImpl = this;
    getAudioInfo();
}

AudioEngineImpl::~AudioEngineImpl() {
    if (_audioPlayerProvider != nullptr) {
        delete _audioPlayerProvider;
        _audioPlayerProvider = nullptr;
    }

    if (_outputMixObject) {
        (*_outputMixObject)->Destroy(_outputMixObject);
    }
    if (_engineObject) {
        (*_engineObject)->Destroy(_engineObject);
    }

    if (_onPauseListener != nullptr)
    {
        cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(_onPauseListener);
    }

    if (_onResumeListener != nullptr)
    {
        cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(_onResumeListener);
    }

    gAudioImpl = nullptr;
}

bool AudioEngineImpl::init() {
    bool ret = false;
    do {
        // create engine
        auto result = slCreateEngine(&_engineObject, 0, nullptr, 0, nullptr, nullptr);
        if (SL_RESULT_SUCCESS != result) {
            ALOGE("create opensl engine fail");
            break;
        }

        // realize the engine
        result = (*_engineObject)->Realize(_engineObject, SL_BOOLEAN_FALSE);
        if (SL_RESULT_SUCCESS != result) {
            ALOGE("realize the engine fail");
            break;
        }

        // get the engine interface, which is needed in order to create other objects
        result = (*_engineObject)->GetInterface(_engineObject, SL_IID_ENGINE, &_engineEngine);
        if (SL_RESULT_SUCCESS != result) {
            ALOGE("get the engine interface fail");
            break;
        }

         _audioPlayerProvider = new AudioPlayerProvider(_engineEngine, outputSampleRate, fdGetter, &gCallerThreadUtils);

        _onPauseListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_COME_TO_BACKGROUND, CC_CALLBACK_1(AudioEngineImpl::onEnterBackground, this));

        _onResumeListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_COME_TO_FOREGROUND, CC_CALLBACK_1(AudioEngineImpl::onEnterForeground, this));


        ret = true;
    } while (false);

    return ret;
}

void AudioEngineImpl::onEnterBackground(EventCustom* event)
{
    // _audioPlayerProvider->pause() pauses AudioMixer and PcmAudioService,
    // but UrlAudioPlayers could not be paused.
    if (_audioPlayerProvider != nullptr)
    {
        _audioPlayerProvider->pause();
    }

    // pause UrlAudioPlayers which are playing.
    for (auto&& e : _audioPlayers)
    {
        auto player = e.second;
        if (dynamic_cast<UrlAudioPlayer*>(player) != nullptr
            && player->getState() == IAudioPlayer::State::PLAYING)
        {
            _urlAudioPlayersNeedResume.emplace(e.first, player);
            player->pause();
        }
    }
}

void AudioEngineImpl::onEnterForeground(EventCustom* event)
{
    // _audioPlayerProvider->resume() resumes AudioMixer and PcmAudioService,
    // but UrlAudioPlayers could not be resumed.
    if (_audioPlayerProvider != nullptr)
    {
        _audioPlayerProvider->resume();
    }

    // resume UrlAudioPlayers
    for (auto&& iter : _urlAudioPlayersNeedResume)
    {
        iter.second->resume();
    }
    _urlAudioPlayersNeedResume.clear();
}


void AudioEngineImpl::setAudioFocusForAllPlayers(bool isFocus) {
    for (const auto &e : _audioPlayers) {
        e.second->setAudioFocus(isFocus);
    }
}

int AudioEngineImpl::play2d(const std::string &filePath, bool loop, float volume) {
    ALOGE("play2d, _audioPlayers.size=%{public}d", (int)_audioPlayers.size());
    auto audioId = AudioEngine::INVALID_AUDIO_ID;

    do {
        if (_audioPlayerProvider == nullptr) {
            break;
        }

        auto fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);

        audioId = _audioIDIndex++;

        auto *player = _audioPlayerProvider->getAudioPlayer(fullPath);
        if (player != nullptr) {
            player->setId(audioId);
            _audioPlayers.insert(std::make_pair(audioId, player));

            player->setPlayEventCallback([this, player, filePath](IAudioPlayer::State state) {
                if (state != IAudioPlayer::State::OVER && state != IAudioPlayer::State::STOPPED) {
                    ALOGV("Ignore state: %{public}d", static_cast<int>(state));
                    return;
                }

                int id = player->getId();

                ALOGE("Removing player id=%{public}d, state:%{public}d", id, (int)state);

                AudioEngine::remove(id);
                if (_audioPlayers.find(id) != _audioPlayers.end()) {
                    _audioPlayers.erase(id);
                }
                if (_urlAudioPlayersNeedResume.find(id) != _urlAudioPlayersNeedResume.end()) {
                    _urlAudioPlayersNeedResume.erase(id);
                }

                auto iter = _callbackMap.find(id);
                if (iter != _callbackMap.end()) {
                    if (state == IAudioPlayer::State::OVER) {
                        iter->second(id, filePath);
                    }
                    _callbackMap.erase(iter);
                }
            });

            player->setLoop(loop);
            player->setVolume(volume);
            player->play();
        } else {
            ALOGE("Oops, player is null ...");
            return AudioEngine::INVALID_AUDIO_ID;
        }

        AudioEngine::_audioIDInfoMap[audioId].state = AudioEngine::AudioState::PLAYING;

    } while (false);

    return audioId;
}

void AudioEngineImpl::setVolume(int audioID, float volume) {
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        player->setVolume(volume);
    }
}

void AudioEngineImpl::setLoop(int audioID, bool loop) {
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        player->setLoop(loop);
    }
}

void AudioEngineImpl::pause(int audioID) {
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        player->pause();
    }
}

void AudioEngineImpl::resume(int audioID) {
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        player->resume();
    }
}


void AudioEngineImpl::stop(int audioID) {
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        player->stop();
    }
}


void AudioEngineImpl::rewindMusic(int audioID) {
    stop(audioID);
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        player->play();
    }
}

bool AudioEngineImpl::isMusicPlaying(int audioID)
{
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        auto state = player->getState();
        return state == IAudioPlayer::State::PLAYING;
    }
    return false;
}

float AudioEngineImpl::getMusicVolume(int audioID)
{
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        return player->getVolume();
    }
    return 0;
}


void AudioEngineImpl::stopAll() {
    if (_audioPlayers.empty()) {
        return;
    }

    // Create a temporary vector for storing all players since
    // p->stop() will trigger _audioPlayers.erase,
    // and it will cause a crash as it's already in for loop
    std::vector<IAudioPlayer *> players;
    players.reserve(_audioPlayers.size());

    for (const auto &e : _audioPlayers) {
        players.push_back(e.second);
    }

    for (auto *p : players) {
        p->stop();
    }
}

float AudioEngineImpl::getDuration(int audioID) {
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        return player->getDuration();
    }
    return 0.0F;
}

float AudioEngineImpl::getDurationFromFile(const std::string &filePath) {
    if (_audioPlayerProvider != nullptr) {
        auto fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        return _audioPlayerProvider->getDurationFromFile(fullPath);
    }
    return 0;
}

float AudioEngineImpl::getCurrentTime(int audioID) {
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        return player->getPosition();
    }
    return 0.0F;
}

bool AudioEngineImpl::setCurrentTime(int audioID, float time) {
    auto iter = _audioPlayers.find(audioID);
    if (iter != _audioPlayers.end()) {
        auto *player = iter->second;
        return player->setPosition(time);
    }
    return false;
}

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void(int, const std::string &)> &callback) {
    _callbackMap[audioID] = callback;
}

void AudioEngineImpl::preload(const std::string &filePath, const std::function<void(bool)> &callback) {
    if (_audioPlayerProvider != nullptr) {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        _audioPlayerProvider->preloadEffect(fullPath, [callback](bool succeed, const PcmData & /*data*/) {
            if (callback != nullptr) {
                callback(succeed);
            }
        });
    } else {
        if (callback != nullptr) {
            callback(false);
        }
    }
}

void AudioEngineImpl::uncache(const std::string &filePath) {
    if (_audioPlayerProvider != nullptr) {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        _audioPlayerProvider->clearPcmCache(fullPath);
    }
}

void AudioEngineImpl::uncacheAll() {
    if (_audioPlayerProvider != nullptr) {
        _audioPlayerProvider->clearAllPcmCaches();
    }
}

void AudioEngineImpl::onPause() {
    if (_audioPlayerProvider != nullptr) {
        _audioPlayerProvider->pause();
    }
}

void AudioEngineImpl::onResume() {
    if (_audioPlayerProvider != nullptr) {
        _audioPlayerProvider->resume();
    }
}

PCMHeader AudioEngineImpl::getPCMHeader(const char *url) {
    PCMHeader header{};
    std::string fileFullPath = FileUtils::getInstance()->fullPathForFilename(url);
    if (fileFullPath.empty()) {
        ALOGD("file %{public}s does not exist or failed to load", url);
        return header;
    }
    if (_audioPlayerProvider->getPcmHeader(url, header)) {
        ALOGD("file %{public}s pcm data already cached", url);
        return header;
    }

    AudioDecoder *decoder = AudioDecoderProvider::createAudioDecoder(_engineEngine, fileFullPath, bufferSizeInFrames, outputSampleRate, fdGetter);

    if (decoder == nullptr) {
        ALOGD("decode %{public}s failed, the file formate might not support", url);
        return header;
    }
    if (!decoder->start()) {
        ALOGD("[Audio Decoder] Decode failed %{public}s", url);
        return header;
    }
    // Ready to decode
    do {
        PcmData data = decoder->getResult();
        header.bytesPerFrame = data.bitsPerSample / 8;
        header.channelCount = data.numChannels;
        header.dataFormat = AudioDataFormat::SIGNED_16;
        header.sampleRate = data.sampleRate;
        header.totalFrames = data.numFrames;
    } while (false);

    AudioDecoderProvider::destroyAudioDecoder(&decoder);
    return header;
}

std::vector<uint8_t> AudioEngineImpl::getOriginalPCMBuffer(const char *url, uint32_t channelID) {
    std::string fileFullPath = FileUtils::getInstance()->fullPathForFilename(url);
    std::vector<uint8_t> pcmData;
    if (fileFullPath.empty()) {
        ALOGD("file %{public}s does not exist or failed to load", url);
        return pcmData;
    }
    PcmData data;
    if (_audioPlayerProvider->getPcmData(url, data)) {
        ALOGD("file %{public}s pcm data already cached", url);
    } else {
        AudioDecoder *decoder = AudioDecoderProvider::createAudioDecoder(_engineEngine, fileFullPath, bufferSizeInFrames, outputSampleRate, fdGetter);
        if (decoder == nullptr) {
            ALOGD("decode %{public}s failed, the file formate might not support", url);
            return pcmData;
        }
        if (!decoder->start()) {
            ALOGD("[Audio Decoder] Decode failed %{public}s", url);
            return pcmData;
        }
        data = decoder->getResult();
        _audioPlayerProvider->registerPcmData(url, data);
        AudioDecoderProvider::destroyAudioDecoder(&decoder);
    }
    do {
        const uint32_t channelCount = data.numChannels;
        if (channelID >= channelCount) {
            ALOGE("channelID invalid, total channel count is %{public}d but %{public}d is required", channelCount, channelID);
            break;
        }
        // bytesPerSample  = bitsPerSample / 8, according to 1 byte = 8 bits
        const uint32_t bytesPerFrame = data.numChannels * data.bitsPerSample / 8;
        const uint32_t numFrames = data.numFrames;
        const uint32_t bytesPerChannelInFrame = bytesPerFrame / channelCount;

        pcmData.resize(bytesPerChannelInFrame * numFrames);
        uint8_t *p = pcmData.data();
        char *tmpBuf = data.pcmBuffer->data(); // shared ptr
        for (int itr = 0; itr < numFrames; itr++) {
            memcpy(p, tmpBuf + itr * bytesPerFrame + channelID * bytesPerChannelInFrame, bytesPerChannelInFrame);
            p += bytesPerChannelInFrame;
        }
    } while (false);

    return pcmData;
}

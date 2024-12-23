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

#include <memory>
#include "PcmData.h"
#include "audio_utils/AudioDef.h"
#include "cutils/log.h"
#define LOG_TAG "AudioPlayerProvider"

#include <algorithm> // for std::find_if
#include <cstdlib>
#include <utility>
#include <rawfile/raw_file_manager.h>
#include "platform/ohos/CCFileUtils-ohos.h"
#include "AudioDecoder.h"
#include "AudioDecoderProvider.h"
#include "AudioMixerController.h"
#include "AudioPlayerProvider.h"
#include "ICallerThreadUtils.h"
#include "PcmAudioPlayer.h"
#include "PcmAudioService.h"
#include "UrlAudioPlayer.h"
#include "utils/Utils.h"
#include "CCThreadPool.h"



#include <algorithm> // for std::find_if
#include <cstdlib>
#include <utility>

namespace cocos2d { namespace experimental {

static int getSystemAPILevel() {
    // TODO(qgh): On the openharmony platform, pcm streaming must be used
    return std::numeric_limits<int>::max();
}

struct AudioFileIndicator {
    std::string extension;
    int smallSizeIndicator;
};

static AudioFileIndicator gAudioFileIndicator[] = {
    {"default", 128000}, // If we could not handle the audio format, return default value, the position should be first.
    {".wav", 1024000},
    {".ogg", 128000},
    {".mp3", 160000}};

AudioPlayerProvider::AudioPlayerProvider(SLEngineItf engineItf, int deviceSampleRate,
 
                                         const FdGetterCallback &fdGetterCallback, //NOLINT(modernize-pass-by-value)
                                         ICallerThreadUtils *callerThreadUtils)
: _engineItf(engineItf), _deviceSampleRate(deviceSampleRate), _fdGetterCallback(fdGetterCallback), _callerThreadUtils(callerThreadUtils), _pcmAudioService(nullptr), _mixController(nullptr), _threadPool(LegacyThreadPool::newCachedThreadPool(1, 8, 5, 2, 2)) {
    ALOGI("deviceSampleRate: %d", _deviceSampleRate);
    if (getSystemAPILevel() >= 17) {
        _mixController = new AudioMixerController(_deviceSampleRate, 2);
        _pcmAudioService = new PcmAudioService();
        _pcmAudioService->init(_mixController, CHANNEL_NUMBERS, deviceSampleRate, &_bufferSizeInFrames);
        _mixController->init(_bufferSizeInFrames);
    }

    ALOG_ASSERT(callerThreadUtils != nullptr, "Caller thread utils parameter should not be nullptr!");
}

AudioPlayerProvider::~AudioPlayerProvider() {
    ALOGV("~AudioPlayerProvider()");
    UrlAudioPlayer::stopAll();

    SL_SAFE_DELETE(_pcmAudioService);
    SL_SAFE_DELETE(_mixController);
    SL_SAFE_DELETE(_threadPool);
}

IAudioPlayer *AudioPlayerProvider::getAudioPlayer(const std::string &audioFilePath) {
    // Pcm data decoding by OpenSLES API only supports in API level 17 and later.
    if (getSystemAPILevel() < 17) {
        AudioFileInfo info = getFileInfo(audioFilePath);
        if (info.isValid()) {
            return dynamic_cast<IAudioPlayer*>(createUrlAudioPlayer(info));
        }

        return nullptr;
    }

    IAudioPlayer *player = nullptr;

    _pcmCacheMutex.lock();
    auto iter = _pcmCache.find(audioFilePath);
    if (iter != _pcmCache.end()) { // Found pcm cache means it was used to be a PcmAudioService
        PcmData pcmData = iter->second;
        _pcmCacheMutex.unlock();
        player = dynamic_cast<IAudioPlayer*>(obtainPcmAudioPlayer(audioFilePath, pcmData));
        ALOGV_IF(player == nullptr, "%{public}s, %{public}d: player is nullptr, path: %{public}s", __FUNCTION__, __LINE__, audioFilePath.c_str());
    } else {
        _pcmCacheMutex.unlock();
        // Check audio file size to determine to use a PcmAudioService or UrlAudioPlayer,
        // generally PcmAudioService is used for playing short audio like game effects while
        // playing background music uses UrlAudioPlayer
        AudioFileInfo info = getFileInfo(audioFilePath);
        if (info.isValid()) {
            if (isSmallFile(info)) {
                // Put an empty lambda to preloadEffect since we only want the future object to get PcmData
                auto pcmData = std::make_shared<PcmData>();
                auto isSucceed = std::make_shared<bool>(false);
                auto isReturnFromCache = std::make_shared<bool>(false);
                auto isPreloadFinished = std::make_shared<bool>(false);

                std::thread::id threadId = std::this_thread::get_id();

                void *infoPtr = &info;
                std::string url = info.url;
                preloadEffect(
                    info, [infoPtr, url, threadId, pcmData, isSucceed, isReturnFromCache, isPreloadFinished](bool succeed, PcmData data) {
                        // If the callback is in the same thread as caller's, it means that we found it
                        // in the cache
                        *isReturnFromCache = std::this_thread::get_id() == threadId;
                        *pcmData = std::move(data);
                        *isSucceed = succeed;
                        *isPreloadFinished = true;
                        ALOGV("FileInfo (%{public}p), Set isSucceed flag: %{public}d, path: %{public}s", infoPtr, succeed, url.c_str());
                    },
                    true);

                if (!*isReturnFromCache && !*isPreloadFinished) {
                    std::unique_lock<std::mutex> lck(_preloadWaitMutex);
                    // Wait for 2 seconds for the decoding in sub thread finishes.
                    ALOGV("FileInfo (%{public}p), Waiting preload (%{public}s) to finish ...", &info, audioFilePath.c_str());
                    _preloadWaitCond.wait_for(lck, std::chrono::seconds(2));
                    ALOGV("FileInfo (%{public}p), Waitup preload (%{public}s) ...", &info, audioFilePath.c_str());
                }

                if (*isSucceed) {
                    if (pcmData->isValid()) {
                        player = dynamic_cast<IAudioPlayer*>(obtainPcmAudioPlayer(info.url, *pcmData));
                        ALOGV_IF(player == nullptr, "%{public}s, %{public}d: player is nullptr, path: %{public}s", __FUNCTION__, __LINE__, audioFilePath.c_str());
                    } else {
                        ALOGE("pcm data is invalid, path: %{public}s", audioFilePath.c_str());
                    }
                } else {
                    ALOGE("FileInfo (%{public}p), preloadEffect (%{public}s) failed", &info, audioFilePath.c_str());
                }
            } else {
                player = dynamic_cast<IAudioPlayer*>(createUrlAudioPlayer(info));
                ALOGV_IF(player == nullptr, "%{public}s, %{public}d: player is nullptr, path: %{public}s", __FUNCTION__, __LINE__, audioFilePath.c_str());
            }
        } else {
            ALOGE("File info is invalid, path: %{public}s", audioFilePath.c_str());
        }
    }

    ALOGV_IF(player == nullptr, "%{public}s, %{public}d return nullptr", __FUNCTION__, __LINE__);
    return player;
}

void AudioPlayerProvider::preloadEffect(const std::string &audioFilePath, const PreloadCallback &callback) {
    // Pcm data decoding by OpenSLES API only supports in API level 17 and later.
    if (getSystemAPILevel() < 17) {
        PcmData data;
        callback(true, data);
        return;
    }

    _pcmCacheMutex.lock();
    auto &&iter = _pcmCache.find(audioFilePath);
    if (iter != _pcmCache.end()) {
        ALOGV("preload return from cache: (%{public}s)", audioFilePath.c_str());
        _pcmCacheMutex.unlock();
        callback(true, iter->second);
        return;
    }
    _pcmCacheMutex.unlock();

    auto info = getFileInfo(audioFilePath);
    preloadEffect(
        info, [this, callback, audioFilePath](bool succeed, const PcmData &data) {
            _callerThreadUtils->performFunctionInCallerThread([this, succeed, data, callback]() {
                callback(succeed, data);
            });
        },
        false);
}

// Used internally
void AudioPlayerProvider::preloadEffect(const AudioFileInfo &info, const PreloadCallback &callback, bool isPreloadInPlay2d) {
    PcmData pcmData;

    if (!info.isValid()) {
        callback(false, pcmData);
        return;
    }

    if (isSmallFile(info)) {
        std::string audioFilePath = info.url;

        // 1. First time check, if it wasn't in the cache, goto 2 step
        _pcmCacheMutex.lock();
        auto &&iter = _pcmCache.find(audioFilePath);
        if (iter != _pcmCache.end()) {
            ALOGV("1. Return pcm data from cache, url: %{public}s", info.url.c_str());
            _pcmCacheMutex.unlock();
            callback(true, iter->second);
            return;
        }
        _pcmCacheMutex.unlock();

        {
            // 2. Check whether the audio file is being preloaded, if it has been removed from map just now,
            // goto step 3
            std::lock_guard<std::mutex> lck(_preloadCallbackMutex);

            auto &&preloadIter = _preloadCallbackMap.find(audioFilePath);
            if (preloadIter != _preloadCallbackMap.end()) {
                ALOGV("audio (%{public}s) is being preloaded, add to callback vector!", audioFilePath.c_str());
                PreloadCallbackParam param;
                param.callback = callback;
                param.isPreloadInPlay2d = isPreloadInPlay2d;
                preloadIter->second.push_back(std::move(param));
                return;
            }

            // 3. Check it in cache again. If it has been removed from map just now, the file is in
            // the cache absolutely.
            _pcmCacheMutex.lock();
            auto &&iter = _pcmCache.find(audioFilePath);
            if (iter != _pcmCache.end()) {
                ALOGV("2. Return pcm data from cache, url: %{public}s", info.url.c_str());
                _pcmCacheMutex.unlock();
                callback(true, iter->second);
                return;
            }
            _pcmCacheMutex.unlock();

            PreloadCallbackParam param;
            param.callback = callback;
            param.isPreloadInPlay2d = isPreloadInPlay2d;
            std::vector<PreloadCallbackParam> callbacks;
            callbacks.push_back(std::move(param));
            _preloadCallbackMap.insert(std::make_pair(audioFilePath, std::move(callbacks)));
        }

        _threadPool->pushTask([this, audioFilePath](int /*tid*/) {
            ALOGV("AudioPlayerProvider::preloadEffect: (%{public}s)", audioFilePath.c_str());
            PcmData d;
            AudioDecoder *decoder = AudioDecoderProvider::createAudioDecoder(_engineItf, audioFilePath, _bufferSizeInFrames, _deviceSampleRate, _fdGetterCallback);
            bool ret = decoder != nullptr && decoder->start();
            if (ret) {
                d = decoder->getResult();
                std::lock_guard<std::mutex> lck(_pcmCacheMutex);
                _pcmCache.insert(std::make_pair(audioFilePath, d));
            } else {
                ALOGE("decode (%{public}s) failed!", audioFilePath.c_str());
            }

            ALOGV("decode %{public}s", (ret ? "succeed" : "failed"));

            std::lock_guard<std::mutex> lck(_preloadCallbackMutex);
            auto &&preloadIter = _preloadCallbackMap.find(audioFilePath);
            if (preloadIter != _preloadCallbackMap.end()) {
                auto &&params = preloadIter->second;
                ALOGV("preload (%{public}s) callback count: %{public}d", audioFilePath.c_str(), (int)params.size());
                PcmData result = decoder->getResult();
                for (auto &&param : params) {
                    param.callback(ret, result);
                    if (param.isPreloadInPlay2d) {
                        _preloadWaitCond.notify_one();
                    }
                }
                _preloadCallbackMap.erase(preloadIter);
            }

            AudioDecoderProvider::destroyAudioDecoder(&decoder);
        });
    } else {
        ALOGV("File (%{public}s) is too large, ignore preload!", info.url.c_str());
        callback(true, pcmData);
    }
}

AudioPlayerProvider::AudioFileInfo AudioPlayerProvider::getFileInfo(const std::string &audioFilePath) 
{
    AudioFileInfo info;
    long fileSize = 0; //NOLINT(google-runtime-int)
    off_t start = 0;
    int assetFd = -1;

    if(audioFilePath[0]!='/'){
        RawFileDescriptor descriptor;
        FileUtilsOhos *utils = dynamic_cast<FileUtilsOhos *>(FileUtils::getInstance());
        FileUtils::Status result = utils->getRawFileDescriptor(audioFilePath, descriptor);
        if(result != FileUtils::Status::OK|| descriptor.fd <= 0){
            ALOGE("Failed to open file descriptor for '%s'", audioFilePath.c_str());
            return info;
        }
        assetFd = descriptor.fd;
        start = descriptor.start;
        fileSize = descriptor.length;
    }else{
        FILE *fp = fopen(audioFilePath.c_str(),"rb");
        if(fp!=nullptr){
            fseek(fp,0,SEEK_END);
            fileSize = ftell(fp);
            fclose(fp);
        }else{
            return info;
        }
    }
    info.url = audioFilePath;
    info.assetFd = std::make_shared<AssetFd>(assetFd);
    info.start = start;
    info.length = fileSize;
    ALOGI("AudioPlayerProvide::getFileInfo(%{public}s) file size:%{public}ld,fd is %d",audioFilePath.c_str(), fileSize,assetFd);
    return info;
}

bool AudioPlayerProvider::isSmallFile(const AudioFileInfo &info) { //NOLINT(readability-convert-member-functions-to-static)
    //REFINE: If file size is smaller than 100k, we think it's a small file. This value should be set by developers.
    auto &audioFileInfo = const_cast<AudioFileInfo &>(info);
    if(audioFileInfo.url[0] == '/') {
        // avplayer does not support playing audio files in sandbox path currently.
         return true;
    }
    size_t judgeCount = sizeof(gAudioFileIndicator) / sizeof(gAudioFileIndicator[0]);
    size_t pos = audioFileInfo.url.rfind('.');
    std::string extension;
    if (pos != std::string::npos) {
        extension = audioFileInfo.url.substr(pos);
    }
    auto *iter = std::find_if(std::begin(gAudioFileIndicator), std::end(gAudioFileIndicator),
                             [&extension](const AudioFileIndicator &judge) -> bool {
                                 return judge.extension == extension;
                             });

    if (iter != std::end(gAudioFileIndicator)) {
        //        ALOGV("isSmallFile: found: %{public}s: ", iter->extension.c_str());
        return info.length < iter->smallSizeIndicator;
    }

    //    ALOGV("isSmallFile: not found return default value");
    return info.length < gAudioFileIndicator[0].smallSizeIndicator;
}

float AudioPlayerProvider::getDurationFromFile(const std::string &filePath) {
    std::lock_guard<std::mutex> lck(_pcmCacheMutex);
    auto iter = _pcmCache.find(filePath);
    if (iter != _pcmCache.end()) {
        return iter->second.duration;
    }
    return 0;
}

void AudioPlayerProvider::clearPcmCache(const std::string &audioFilePath) {
    std::lock_guard<std::mutex> lck(_pcmCacheMutex);
    auto iter = _pcmCache.find(audioFilePath);
    if (iter != _pcmCache.end()) {
        ALOGV("clear pcm cache: (%{public}s)", audioFilePath.c_str());
        _pcmCache.erase(iter);
    } else {
        ALOGW("Couldn't find the pcm cache: (%{public}s)", audioFilePath.c_str());
    }
}

void AudioPlayerProvider::clearAllPcmCaches() {
    std::lock_guard<std::mutex> lck(_pcmCacheMutex);
    _pcmCache.clear();
}

PcmAudioPlayer *AudioPlayerProvider::obtainPcmAudioPlayer(const std::string &url,
                                                          const PcmData &pcmData) {
    PcmAudioPlayer *pcmPlayer = nullptr;
    if (pcmData.isValid()) {
        pcmPlayer = new PcmAudioPlayer(_mixController, _callerThreadUtils);
        if (pcmPlayer != nullptr) {
            pcmPlayer->prepare(url, pcmData);
        }
    } else {
        ALOGE("obtainPcmAudioPlayer failed, pcmData isn't valid!");
    }
    return pcmPlayer;
}

UrlAudioPlayer *AudioPlayerProvider::createUrlAudioPlayer(
    const AudioPlayerProvider::AudioFileInfo &info) {
    if (info.url.empty()) {
        ALOGE("createUrlAudioPlayer failed, url is empty!");
        return nullptr;
    }

    auto *urlPlayer = new (std::nothrow) UrlAudioPlayer(_callerThreadUtils);
    bool ret = urlPlayer->prepare(info.url, info.assetFd, info.start, info.length);
    if (!ret) {
        if (urlPlayer != nullptr) { 
            delete urlPlayer;
            urlPlayer = nullptr; 
        }
    }
    return urlPlayer;
}

void AudioPlayerProvider::pause() {
    if (_mixController != nullptr) {
        _mixController->pause();
    }

    if (_pcmAudioService != nullptr) {
        _pcmAudioService->pause();
    }
}

void AudioPlayerProvider::resume() {
    if (_mixController != nullptr) {
        _mixController->resume();
    }

    if (_pcmAudioService != nullptr) {
        _pcmAudioService->resume();
    }
}
void AudioPlayerProvider::registerPcmData(const std::string &audioFilePath, PcmData &data) {
    std::lock_guard<std::mutex> lck(_pcmCacheMutex);
    if (_pcmCache.find(audioFilePath) != _pcmCache.end()){
        ALOGE("file %{public}s pcm data is already cached.", audioFilePath.c_str());
        return;
    }
    _pcmCache.emplace(audioFilePath, data);
}

bool AudioPlayerProvider::getPcmHeader(const std::string &audioFilePath, PCMHeader &header) {
    std::lock_guard<std::mutex> lck(_pcmCacheMutex);
    auto &&iter = _pcmCache.find(audioFilePath);
    if (iter != _pcmCache.end()) {
        ALOGV("get pcm header from cache, url: %{public}s", audioFilePath.c_str());
        // On Android, all pcm buffer is resampled to sign16.
        header.bytesPerFrame = iter->second.bitsPerSample / 8;
        header.channelCount = iter->second.numChannels;
        header.dataFormat = AudioDataFormat::SIGNED_16;
        header.sampleRate = iter->second.sampleRate;
        header.totalFrames = iter->second.numFrames;
        return true;
    }
    return false;
}
bool AudioPlayerProvider::getPcmData(const std::string &audioFilePath, PcmData &data) {
    std::lock_guard<std::mutex> lck(_pcmCacheMutex);
    auto &&iter = _pcmCache.find(audioFilePath);
    if (iter != _pcmCache.end()) {
        ALOGV("get pcm buffer from cache, url: %{public}s", audioFilePath.c_str());
        // On Android, all pcm buffer is resampled to sign16.
        data = iter->second;
        return true;
    }
    return false;
}
}} // namespace cocos2d { namespace experimental
